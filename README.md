<h1>QGraphics</h1>
This C++ graphics library for windoows offers a wide range of functions to facilitate building 3D graphics programs, including creating windows, creating 3D assets, materials and lighting.

<h2>Getting Started in Visual Studio</h2>
Clone this repo from the main page my clicking Code -> Download ZIP.

Unzip the folder, open the project and build it.

Open the project you want to include the library in, and open the project properties (Project -> Properties on the menu bar).
In the C++ section, add 'FOLDER\QGraphics\QGraphics;' and 'FOLDER\QGraphics\QGraphics\Dependencies\Freetype' to the Additional Include Directories, replacing FOLDER with the location you unzipped to.

In the Linker section, add 'FOLDER\QGraphics\bin\Debug-x64\QGraphics' to the Additional Library Directories.

You can now use the library in any CPP file simply by adding

#include <QGraphics.h>

to the top of the file.
