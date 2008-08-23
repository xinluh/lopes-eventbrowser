TEMPLATE = app
INCLUDEPATH += . build muParserLib

# Input
HEADERS += forms/mainform.ui.h \
           Draw.h ReadRootTree.h \
           Canvas.h \
           global.h \
           Helper.h \
           forms/formviewdata.ui.h \
           forms/formOpenFile.ui.h \
           ColumnCollection.h \
           CanvasCollection.h
#The following line was changed from INTERFACES to FORMS3 by qt3to4
FORMS3 += forms/mainform.ui\
              forms/formviewdata.ui \
              forms/formChooseDisplayColumns.ui \
              forms/formAbout.ui \
              forms/formOpenFile.ui
SOURCES += main.cpp \
           Draw.cpp \
           ReadRootTree.cpp \
           Canvas.cpp \
           Helper.cpp \
           ColumnCollection.cpp \
           CanvasCollection.cpp
SOURCES += muParserLib/muParserBase.cpp \
           muParserLib/muParser.cpp \
           muParserLib/muParserBytecode.cpp \
           muParserLib/muParserCallback.cpp \
           muParserLib/muParserError.cpp \
           muParserLib/muParserTokenReader.cpp 

LIBS	+= -L$(ROOTSYS)/lib -lCore -lCint -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -pthread -lm -ldl

include ($(ROOTSYS)/include/rootcint.pri)

unix {
  UI_DIR = build/
  MOC_DIR = build/
  OBJECTS_DIR = build/
}

DEFINES += DEBUG

#The following line was inserted by qt3to4
QT +=  qt3support 
#The following line was inserted by qt3to4
CONFIG += uic3

