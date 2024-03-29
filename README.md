# Computação Gráfcica para Jogos / Computer Graphics for Games | IST 2020/2021

## Installation
To run this project it is recommended that you use VisualStudio (2019). 
1.	Start by opening the project.
2.	Download both [GLEW](http://glew.sourceforge.net/) and [GLFW](https://www.glfw.org/download.html)\'s binaries
3.	Extract both zips into the **dependencies** folder. Your folder structure should now look like ```CGJ-Engine > dependencies > glew``` and ```CGJ-Engine > dependencies > glfw```
4.	Ensure you have an **include** and **lib** folder within your **glew** folder and an **include** and **lib-vc2019** folder within your **glfw** folder.
5.	Go to **Project Properties** (ALT+Enter after selecting CGJ-Engine in the Solution Explorer)
6.	In **Configuration Properties > C/C++ > General > Additional Include Directories** add the following lines: ```$(ProjectDir)dependencies\glfw\include``` and ```$(ProjectDir)dependencies\glew\include```
7.	In **Configuration Properties > Linker > General > Additional Library Directories** add the following lines: ```$(ProjectDir)dependencies\glew\lib\Release\x64``` and ```$(ProjectDir)dependencies\glfw\lib-vc2019```
8.	In **Configuration Properties > Linker > Input > Additional Dependencies** add the following items: ```opengl32.lib```, ```glew32.lib```, ```glfw3.lib```, ```opengl32.lib```, ```glfw3dll.lib```
9.	Apply all changes made

### Troubleshooting
If you follow the previous instructions but the project still refuses to compile, make sure that you\'re using **x64** as your platform for running and that you defined the Project Properties for this platform

If you\'re getting a "This application has failed to start because glew32.dll was not found. Re-installing the application may fix this problem." error, try one of the following fixes:
-	Add the **glew32.dll** (that comes included in the glew > bin folder) to the project\'s root directory
-	Add the **glew32.dll** to your **x64 > Debug** directory


## Authors

-   **Diogo Silva** - [HerouFenix](https://github.com/HerouFenix)
-   **Daniel Gonçalves** - [4nd3l1](https://github.com/4nd3l1)
-   **Henrique Gaspar** - [HenriqueMetas](https://github.com/HenriqueMetas)
-   **Guilherme Menezes** - [GuilhermeMenezes](https://github.com/GuilhermeMenezes)

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/heroufenix/cgj-rose/blob/master/LICENSE) file for more information
