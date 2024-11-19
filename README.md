# Drawing application
This is a small and simple drawing application. The project was mainly created for educational purposes. It's one of my first small projects i developed in c++....
Its a 32 bit application.

# Images of the application
![Main screen](doc/images/main.png)
![Menu](doc/images/menu.png)
![New image dialog](doc/images/new-image-dialog.png)
![File selector dialog](doc/images/file-selector.png)

# Features
- Create new image with custom size
- Save / load images
- Select images for loading/saving via file selector
- Change the brush size and the brush color
- Zoom into the image via scroll wheel up/down 
- Move the image view around via moving the mouse while holding down right mouse button

# Download
Please take a look at the releases tab here in github

# Development informations
## Setup (under windows + visual studio code)
1. Install [MSYS2](https://www.msys2.org/) on your system - For easiest setup use the default directory given by the installer (C:\MSYS2)
2. Open "MSYS2 MINGW32" (you should find it via your windows application search)
3. Install the mingw32 toolchain via 'pacman -S mingw-w64-i686-toolchain'
4. Clone this project into a place of your choice
5. Open the directory in visual studio code
6. Have fun with it!

## For those who didn't install MSYS2 into the default directory (C:\MSYS2)
Please replace all directory paths in the .vscode directory from C:\MSYS2 to your custom directory. The path should also end with the MSYS2 folder (e.g D:\MY\CUSTOM\PATH\MSYS2). One of the easiest way is to use the search tab in visual studio code.