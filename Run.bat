cd Debug
start Server.exe "localhost" 8098
start ClientGUI.exe "localhost" 8098 "localhost" 8088 ".." ".*" 1
start ClientGUI.exe "localhost" 8098 "localhost" 8086 ".." ".*" 1
cd ..



