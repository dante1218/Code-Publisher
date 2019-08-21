
/////////////////////////////////////////////////////////////////////////////
// Popup.xaml.cs -     a client GUI window which is used to display soruce //
//                     code of a selected file                             //
// ver 1.0                                                                 //
// Language:     C++, Visual Studio 2017                                   //
// Application:  Project4, CSE687 - OOD Spring 2019                        //
// Author:       Yishi Lu, Syracuse University, EECS                       //
//               ylu154@syr.edu                                            //
/////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * It is a client GUI, which is used to display soruce code of a selected file 
 *
 * This package provides functions:
 * Popup()                  initialize a popup WPF window 
 * setMainWindow()          display content (source code) of selected file in this window
 * 
 *
 * Required Files:
 * ---------------
 * Popup.xaml.cs, Popup.xaml
 * PublisherTranslater package
 *
 * Build Process:
 * --------------
 * devenv Project3.sln /ReBuild
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 08 April 2019
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
using System.Windows.Shapes;
using System.IO;

namespace ClientGUI
{
    /// <summary>
    /// Interaction logic for Popup.xaml
    /// </summary>
    public partial class Popup : Window
    {
        MainWindow mainWin = null;
        private string filename { get; set; }

        //----< initialize a popup WPF window >----------------------------------------------
        public Popup(string file)
        {
            InitializeComponent();
            filename = file;
            this.Title = "Popup - " + filename;
        }

        //----< display content (source code) of selected file in this window >----------------------------------------------
        public void setMainWindow(MainWindow mainW)
        {
            mainWin = mainW;
            string content = File.ReadAllText(filename);
            con.Text = content;
        }
    }
}
