**NOTE: this page only describes the library dependency for the newest, QT4 version of the program. For library dependency of the stable branch qt3-branch, see LibraryDependencyQT3.**

## ROOT ##

This project requires [ROOT](http://root.cern.ch/) compiled with QT support. Only ROOT version 5.18 or above is supported.

The easiest way to get ROOT with QT support is to use the script http://root.bnl.gov/QtRoot/INSTALL_QTROOT.sh, which will download and install ROOT plus QtROOT in a directory of choice (not interfering with existent ROOT and QT installations).


## QT ##

QT version 4.3 or above is needed.

One can get QT from [TrollTech](http://trolltech.org/), but the runtime libraries should be included in most linux distributions. To compile Lopes-Eventbrowser, one will also need the development libraries of QT 4.3 or above.


## muParser ##

This is a mathematical library for parsing formulas, see http://muparser.sourceforge.net/. muParser is used extensively within the program to provide flexibility, and make graphing much more customizable and convenient.

The muParser code version 1.30 is included in the source tree under [muParserLib](http://code.google.com/p/lopes-eventbrowser/source/browse#svn/trunk/muParserLib), and it is compiled along with the rest of the program.

_A slight change is made to the original source code which on can get from its website: the default datatype is changed from double to float to better adapt to the normal usage of the event browser. One can locate the change in source file [muParserDef.h](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/muParserLib/muParserDef.h) under the define MUP\_BASETYPE._