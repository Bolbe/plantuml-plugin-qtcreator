# plantuml-plugin-qtcreator
[PlantUML](http://plantuml.com/) plugin for [QtCreator](https://github.com/qt-creator/qt-creator)

Clone [qt-creator project](https://github.com/qt-creator/qt-creator), open it with QtCreator, and build the project.

Clone [plantuml-plugin-qtcreator](http://plantuml.com/), open it with QtCreator.

Before building, you need to set the path to the qtcreator source and qtcreator build folders. Go to "Projects" panel > "Build enviroment" section, and add two variables:

QTC_BUILD and set its value to the path to the qt-creator folder created when cloning qt-creator project.

QTC_SOURCE and set its value to the path to the build folder created when you built qt-creator project. By default, this folder name is something like build-qtcreator-Desktop_Qt.....

These two paths can also be set in the plantuml.pro file (lines IDE_SOURCE_TREE and IDE_BUILD_TREE)

Run plantuml-plugin-qtcreator. You will be asked where the qt creator executable is. Give the path to the binary created when you built qt-creator project (for example, for me on macOS, it was build-qtcreator-Desktop_Qt_5_10_1_clang_64bit-Debug/bin/Qt Creator.app)

Another QtCreator will start with the plantUML plugin activated.

If you want to include this plugin in your Qt Creator, get the dynamic library created :


