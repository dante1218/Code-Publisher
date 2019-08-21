
/////////////////////////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs - a client GUI which integrated with Message Communication   //
//                     by C++/CLI translater. User can click on the GUI to call    //
//                     functions to send request to server for naviagating         //
//                     directories, publishing path, viewing/downloading files.    //
// ver 1.0                                                                         //
// Language:     C++, Visual Studio 2017                                           //
// Application:  Project4, CSE687 - OOD Spring 2019                                //
// Author:       Yishi Lu, Syracuse University, EECS                               //
//               ylu154@syr.edu                                                    //
/////////////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * It is a client GUI, which integrated with Message Communication by C++/CLI translater. 
 * Methods will be called when user perform actions on the GUI to send request to server.
 * It contains several views:
 * Directory Nagivation view: list all directory and files in the current path of server, 
 * user can doubly click on selected directory to navigate to other directory of server. Moreover,
 * user can right click a directory by mouse to select the directory, and user can 
 * also supply a pattern in the input field. Once user click button "Publish", a request
 * will be send to server to process the given path with given pattern
 * Converted File List view: if there is converted files on server, it will be display on this view as 
 * list. User can right click a converted file in this list by mouse, then a ContextMenu will
 * be displayed. User can select different view on the menu. There three views: Browser View,
 * source view, and Chrome view
 * Browser View: display the selected file under tab "Browser view" as a real browser view
 * Source View: display the selected file in a popup window, and show its source code
 * Chrome View: open the selected file by default browser
 *
 * This package provides functions:
 * MainWindow()					            initialize WPF window
 * addClientProc()                          add client processing for message with key
 * processMessages()                        processing message which are received from server
 * acceptCommandLineArgs()					accept command line arguments from user
 * Window_Loaded(str)				        initialize client GUI, send message to server to fetch all directories and files in project root, and also set pattern and selected current path on GUI
 * DispatcherLoadGetDirs()                  load getDirs processing into dispatcher dictionary
 * DispatcherLoadGetFiles()                 load getFiles processing into dispatcher dictionary
 * DispatcherLoadConvertedFile()            receive converted files' name list from server, and display them under tab "Converted File List"
 * DispatcherPublishResult()                receive publishing feedback from server
 * Dirs_MouseDoubleClick()                  triggered by double click on directoy name under tab "Directory Navigation", send messages to server to fetch subdirectories' name and files' name
 * Select_Path()                            triggered by click right menu with option "select" on a directory under "Directory Navigation", select the directory as target path to be analyzed for CodePublisher
 * Add_Pattern()                            triggered by click button of submit under "Directory Navigation", set the pattern to be used in CodePublisher
 * Publish()                                send message to server to convert files in a given path with given pattern, then send message to server to fetch converted files' name
 * sendDownloadRequest()                    send download file request to server with a file name
 * Display_Browser()                        send message to server to download file, then display the file in browser view of the client GUI
 * Display_Source()                         send message to server to download file, then display the file source code in popup window
 * Display_RealBrowser()                    send message to server to download file, then display the file by default browser
 * runAutoTest()                            function for auto test
 * sendCommandForAutoTest()                 function for auto test to send requests to server
 * displayForAutoTest()                     function for auto test to display converted in different views
 * log(str)							        print message to console
 *
 * Required Files:
 * ---------------
 * MainWindow.xaml, MainWindow.xaml.cs
 * Translater.dll
 *
 * Build Process:
 * --------------
 * devenv Project4.sln /ReBuild
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 30 April 2019
 * - first release
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Security;
using System.Security.Permissions;
using System.Security.AccessControl;
using MsgPassingCommunication;
using System.Threading;

namespace ClientGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string Path { get; set; }
        private string ConvertedFilePath = "../clientStorage";
        private string SelectedPath { get; set; }
        private string UserPattern { get; set; }
        private string ConvertedDir { get; set; }
        private Popup Popup { get; set; } = null;
        private string AutoTest { get; set; } = null;

        private Translater translater;
        private Stack<string> pathStack_ = new Stack<string>();
        private CsEndPoint endPoint_;
        private Thread rcvThrd = null;
        private Dictionary<string, Action<CsMessage>> dispatcher_ = new Dictionary<string, Action<CsMessage>>();
        private string serverAddress;
        private int serverPort;
        private string hostAddress;
        private int hostPort;

        //----< initialize WPF window >----------------------------------------------
        public MainWindow()
        {
            System.IO.Directory.CreateDirectory(ConvertedFilePath);
            InitializeComponent();
            acceptCommandLineArgs();
        }

        //----< accept command line arguments from user >----------------------------------------------
        private void acceptCommandLineArgs()
        {
            String[] arguments = Environment.GetCommandLineArgs();
            if (arguments.Length > 7)
            {
                serverAddress = arguments[1];
                serverPort = Convert.ToInt32(arguments[2]);
                hostAddress = arguments[3];
                hostPort = Convert.ToInt32(arguments[4]);
                Path = arguments[5];
                UserPattern = arguments[6];
                AutoTest = arguments[7];
                log("Command Line argument1 (server address): " + serverAddress + "\n");
                log("Command Line argument2 (server port): " + serverPort + "\n");
                log("Command Line argument3 (client address): " + hostAddress + "\n");
                log("Command Line argument4 (client port): " + hostPort + "\n");
                log("Command Line argument5 (folder path): \"" + Path + "\", using it as starting path\n");
                log("Command Line argument6 (pattern): \"" + UserPattern + "\", using it as pattern\n");
                log("Command Line argument7 (Auto Test): " + AutoTest + " (1 for turning on, 0 for turning off)\n");
            }
            else
            {
                serverAddress = "localhost";
                serverPort = 8098;
                hostAddress = "localhost";
                hostPort = 8088;
                Path = "..";
                UserPattern = ".*";
                AutoTest = "0";
                log("Command line arguments are not properly given by user, using default parameter to initialize the program\n");
                log("server address and port: localhost 8098");
                log("client address and port: localhost 8088");
                log("folder path: root of the project directory (" + Path + ")");
                log("pattern: " + UserPattern);
                log("autoTest: " + AutoTest + " (1 for turning on, 0 for turning off)\n");
            }
        }

        //----< processing message which are received from server >------
        private void processMessages()
        {
            ThreadStart thrdProc = () => {
                while (true)
                {
                    try
                    {
                        CsMessage msg = translater.getMessage();
                        string msgId = msg.value("command");
                        if (dispatcher_.ContainsKey(msgId))
                            dispatcher_[msgId].Invoke(msg);
                    }
                    catch
                    {
                        continue;
                    }
                }
            };
            rcvThrd = new Thread(thrdProc);
            rcvThrd.IsBackground = true;
            rcvThrd.Start();
        }

        //----< add client processing for message with key >---------------
        private void addClientProc(string key, Action<CsMessage> clientProc)
        {
            dispatcher_[key] = clientProc;
        }

        //----< load getDirs processing into dispatcher dictionary >-------
        private void DispatcherLoadGetDirs()
        {
            Action<CsMessage> getDirs = (CsMessage rcvMsg) =>
            {
                Action clrDirs = () =>
                {
                    Dirs.Items.Clear();
                };
                Dispatcher.Invoke(clrDirs, new Object[] { });
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("dir"))
                    {
                        Action<string> doDir = (string dir) =>
                        {
                            Dirs.Items.Add(dir);
                        };
                        Dispatcher.Invoke(doDir, new Object[] { enumer.Current.Value });
                    }
                }
                Action insertUp = () =>
                {
                    Dirs.Items.Insert(0, "..");
                };
                Dispatcher.Invoke(insertUp, new Object[] { });
            };
            addClientProc("getDirs", getDirs);
        }

        //----< load getFiles processing into dispatcher dictionary >------
        private void DispatcherLoadGetFiles()
        {
            Action<CsMessage> getFiles = (CsMessage rcvMsg) =>
            {
                Action clrFiles = () =>
                {
                    DirFiles.Items.Clear();
                };
                Dispatcher.Invoke(clrFiles, new Object[] { });
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("file"))
                    {
                        Action<string> doFile = (string file) =>
                        {
                            DirFiles.Items.Add(file);
                        };
                        Dispatcher.Invoke(doFile, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getFiles", getFiles);
        }

        //----< receive publishing feedback from server >--------------------------------------
        private void DispatcherPublishResult()
        {
            Action<CsMessage> publishDirs = (CsMessage rcvMsg) =>
            {
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("publishResult"))
                    {
                        Action<string> doResult = (string result) =>
                        {
                            if (result == "1") log("Publushing is successful\n");
                            else log("ERROR: No matching file is found or Invalid path/pattern, please try again\n");
                        };
                        Dispatcher.Invoke(doResult, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("publishDirs", publishDirs);
        }

        //----< receive converted files' name list from server, and display them under tab "Converted File List" >---------------------
        private void DispatcherLoadConvertedFile()
        {
            Action<CsMessage> getConvertedList = (CsMessage rcvMsg) =>
            {
                Action clrResults = () =>
                {
                    Files.Items.Clear();
                };
                Dispatcher.Invoke(clrResults, new Object[] { });
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("convertedList"))
                    {
                        Action<string> doResult = (string file) =>
                        {
                            Files.Items.Add(file);
                        };
                        Dispatcher.Invoke(doResult, new Object[] { enumer.Current.Value });
                    }
                }
            };
            addClientProc("getConvertedList", getConvertedList);
        }

        //----< initialize client GUI, send message to server to fetch all directories and files in project root, and also set pattern and selected current path on GUI  >----------------------------------------------
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            PatternValue.Text = UserPattern;
            CurrPath.Text = Path;

            // start Comm
            endPoint_ = new CsEndPoint();
            endPoint_.machineAddress = hostAddress;
            endPoint_.port = hostPort;
            translater = new Translater();
            translater.listen(endPoint_);

            processMessages();

            DispatcherLoadGetDirs();
            DispatcherLoadGetFiles();
            DispatcherLoadConvertedFile();
            DispatcherPublishResult();

            CsEndPoint serverEndPoint = new CsEndPoint();
            serverEndPoint.machineAddress = serverAddress;
            serverEndPoint.port = serverPort;

            pathStack_.Push(Path);
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getDirs");
            msg.add("path", pathStack_.Peek());
            translater.postMessage(msg);
            msg.remove("command");
            msg.add("command", "getFiles");
            translater.postMessage(msg);
            msg.remove("command");
            msg.add("command", "getConvertedFile");
            translater.postMessage(msg);

            if (AutoTest == "1") runAutoTest();
            else log("Automated Test turns off, you can play around the GUI.\n");
        }

        //----< triggered by double click on directoy name under tab "Directory Navigation", send messages to server to fetch subdirectories' name and files' name >--------
        private void Dirs_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            try
            {
                // build path for selected dir
                string selectedDir = (string)Dirs.SelectedItem;
                if (selectedDir == null)
                    return;
                string path;
                if (selectedDir == "..")
                {
                    if (pathStack_.Count > 1)
                        pathStack_.Pop();
                    else
                    {
                        log("ERROR: Operation Forbidden. Due to security consideration, user can only navigate inside the project dirctory of the server.\n");
                        return;
                    }
                }
                else
                {
                    path = pathStack_.Peek() + "/" + selectedDir;
                    pathStack_.Push(path);
                }
                // display path in Dir TextBlcok
                CurrPath.Text = pathStack_.Peek();

                // build message to get dirs and post it
                CsEndPoint serverEndPoint = new CsEndPoint();
                serverEndPoint.machineAddress = serverAddress;
                serverEndPoint.port = serverPort;
                CsMessage msg = new CsMessage();
                msg.add("to", CsEndPoint.toString(serverEndPoint));
                msg.add("from", CsEndPoint.toString(endPoint_));
                msg.add("command", "getDirs");
                msg.add("path", pathStack_.Peek());
                translater.postMessage(msg);

                // build message to get files and post it
                msg.remove("command");
                msg.add("command", "getFiles");
                translater.postMessage(msg);
                log("Navigate to directory " + selectedDir + "\n");
            }
            catch
            {
                return;
            }
        }

        //----< triggered by click right menu with option "select" on a directory under "Directory Navigation", select the directory as target path to be published by server in future >----------------------------------------------
        private void Select_Path(object sender, RoutedEventArgs e)
        {
            try
            {
                string selectedDir = pathStack_.Peek() + "/" + Dirs.SelectedItem.ToString();
                if (selectedDir == "..") return;
                else
                {
                    SelectPath.Text = selectedDir;
                    SelectedPath = selectedDir;
                    log("Select Directory: " + SelectedPath + " as next processing directory.\n");
                }
            }
            catch
            {
                return;
            }
        }

        //----< triggered by click button of submit under "Directory Navigation", set the pattern to be used in CodePublisher >------------------
        private void Add_Pattern(object sender, RoutedEventArgs e)
        {
            UserPattern = Pattern.Text;
            PatternValue.Text = UserPattern;
            log("Change pattern to " + UserPattern + ".\n");
        }

        //----< send message to server to convert files in a given path with given pattern, then send message to server to fetch converted files' name >-------------
        private void Publish(object sender, RoutedEventArgs e)
        {
            CsEndPoint serverEndPoint = new CsEndPoint();
            serverEndPoint.machineAddress = serverAddress;
            serverEndPoint.port = serverPort;
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "publishDirs");
            msg.add("path", SelectedPath);
            msg.add("pattern", UserPattern);
            translater.postMessage(msg);

            msg.remove("command");
            msg.remove("path");
            msg.remove("pattern");
            msg.add("command", "getConvertedFile");
            translater.postMessage(msg);

            ConvertTab.IsSelected = true;
            log("Sent Publish request to Server with path: " + SelectedPath + " and pattern: " + UserPattern + "\n");
        }

        //----< send download file request to server with a file name >----------------------------------------------
        private string sendDownloadRequest()
        {
            string fileName = Files.SelectedItem.ToString();
            CsEndPoint serverEndPoint = new CsEndPoint();
            serverEndPoint.machineAddress = serverAddress;
            serverEndPoint.port = serverPort;
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "downloadFile");
            msg.add("fileName", fileName);
            translater.postMessage(msg);
            Thread.Sleep(100);

            return fileName;
        }

        //----< send message to server to download file, then display the file in browser view of the client GUI >----------------------------------------------
        private void Display_Browser(object sender, RoutedEventArgs e)
        {
            try
            {
                string fileName = sendDownloadRequest();

                string selectedFile = ConvertedFilePath + "\\" + fileName;
                selectedFile = System.IO.Path.GetFullPath(selectedFile);
                DisplayFile.Text = selectedFile;
                wpfBrowser.Source = new Uri(selectedFile);
                log("Display converted file " + selectedFile + " in Browser View\n");

                DisplayTab.IsSelected = true;
            }
            catch
            {
                return;
            }
        }

        //----< send message to server to download file, then display the file source code in popup window >----------------------------------------------
        private void Display_Source(object sender, RoutedEventArgs e)
        {
            try
            {
                string fileName = sendDownloadRequest();

                string selectedFile = ConvertedFilePath + "\\" + fileName;
                selectedFile = System.IO.Path.GetFullPath(selectedFile);
                Popup = new Popup(selectedFile);
                Popup.setMainWindow(this);
                Popup.Show();
                log("Display converted file " + selectedFile + "'s source code in popup window\n");
            }
            catch
            {
                return;
            }
        }

        //----< send message to server to download file, then display the file by default browser >----------------------------------------------
        private void Display_RealBrowser(object sender, RoutedEventArgs e)
        {
            try
            {
                string fileName = sendDownloadRequest();

                string selectedFile = ConvertedFilePath + "\\" + fileName;
                selectedFile = System.IO.Path.GetFullPath(selectedFile);
                System.Diagnostics.Process.Start(selectedFile);
                log("Display converted file " + selectedFile + "'s source code in real browser\n");
            }
            catch
            {
                return;
            }
        }

        //----< function for auto test >----------------------------------------------
        private void runAutoTest()
        {
            log("Demonstration of Requierment #8: Automated Test starts here");
            log("-----------------------------------------------------------\n");

            SelectPath.Text = "../show";
            SelectedPath = "../show";
            log("Select Directory: " + SelectedPath + " as next processing directory.\n");

            UserPattern = "[S].*";
            PatternValue.Text = UserPattern;
            log("Change pattern to " + UserPattern + ".\n");

            string fileName = sendCommandForAutoTest();
            displayForAutoTest(fileName);

            Console.Write("  Demonstration of Requierment #8: Automated Test ends here\n");
            Console.Write("  ---------------------------------------------------------\n");
            Console.Write("  You can play around the ClientGUI now\n\n");
        }

        //----< function for auto test to send requests to server >----------------------------------------------
        private string sendCommandForAutoTest()
        {
            CsEndPoint serverEndPoint = new CsEndPoint();
            serverEndPoint.machineAddress = serverAddress;
            serverEndPoint.port = serverPort;
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "publishDirs");
            msg.add("path", SelectedPath);
            msg.add("pattern", UserPattern);
            translater.postMessage(msg);
            msg.remove("command");
            msg.add("command", "getConvertedFile");
            translater.postMessage(msg);
            ConvertTab.IsSelected = true;
            log("Sent Publish request to Server with path: " + SelectedPath + " and pattern: " + UserPattern + "\n");
            Thread.Sleep(1000);

            msg.remove("command");
            msg.remove("path");
            msg.remove("pattern");
            string fileName = "Show.cpp.html";
            msg.add("command", "downloadFile");
            msg.add("fileName", fileName);
            translater.postMessage(msg);
            log("Sent file download request to server, downloaded file: " + fileName + "\n");
            Thread.Sleep(100);

            return fileName;
        }

        //----< function for auto test to display converted in different views >----------------------------------------------
        private void displayForAutoTest(string fileName)
        {
            string selectedFile = ConvertedFilePath + "\\" + fileName;
            selectedFile = System.IO.Path.GetFullPath(selectedFile);
            DisplayFile.Text = selectedFile;
            wpfBrowser.Source = new Uri(selectedFile);
            DisplayTab.IsSelected = true;
            log("Display converted file " + selectedFile + " in Browser View\n");

            selectedFile = System.IO.Path.GetFullPath(selectedFile);
            Popup = new Popup(selectedFile);
            Popup.setMainWindow(this);
            Popup.Show();
            log("Display converted file " + selectedFile + "'s source code in popup window\n");

            selectedFile = System.IO.Path.GetFullPath(selectedFile);
            System.Diagnostics.Process.Start(selectedFile);
            log("Display converted file " + selectedFile + "'s source code in real browser\n");
        }

        //----< print message to console >----------------------------------------------
        private void log(String msg)
        {
            Console.Write("  " + msg + "\n");
        }
    }
}
