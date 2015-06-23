**NOTE: this page is for the Qt3 branch of the program ONLY. Some information on this page is outdated for the newest developmental version; see page LibraryDependency for the current library dependency.**

## ROOT 5.18 ##

This project requires [ROOT](http://root.cern.ch/) compiled with QT3 support. Only **ROOT 5.18** is supported in the qt3-branch version, as the older versions of ROOT have bugs that prevent program from running properly, and the newer versions (>5.18) have dropped QT3 and support only QT4.

One can get the source and the compiled binaries (which has been compiled with QT3 support) [here](http://root.cern.ch/root/Version518.html).


## QT ##

QT version >= 3.3 and < 4.0 is needed.

One can get QT3 from [TrollTech](http://trolltech.org/), but the runtime libraries should be included in most linux distributions. To compile Lopes-Eventbrowser, one will also need the development libraries of QT 3.


## muParser ##

This is a mathematical library for parsing formulas, see http://muparser.sourceforge.net/. muParser is used extensively within the program to provide flexibility, and make graphing much more customizable and convenient.

The muParser code version 1.30 is included in the source tree under [muParserLib](http://code.google.com/p/lopes-eventbrowser/source/browse#svn/trunk/muParserLib), and it is compiled along with the rest of the program.

_A slight change is made to the original source code which on can get from its website: the default datatype is changed from double to float to better adapt to the normal usage of the event browser. One can locate the change in source file [muParserDef.h](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/muParserLib/muParserDef.h) under the define MUP\_BASETYPE._