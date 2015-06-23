The code in this project can be roughly divides into three main components:
  * [Wrapper to ROOT](CodeStructure#Wrapper_to_ROOT.md) (drawing and interaction with root files)
  * [User interface](CodeStructure#User_interface.md)
  * [Program state persistence](CodeStructure#Program_state_persistence.md)


---


## Wrapper to ROOT ##

The two main classes are [ReadRootTree](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/ReadRootTree.h) and [Draw](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/Draw.h).

These classes are designed to provide convenient access to the methods and classes of ROOT so that the rest of the program do not need to interact with ROOT directly (the user interface part of the program use these classes instead of ROOT directly).

### _class ReadRootTree_ ###

This class interacts with root files and root trees by providing methods to access root trees, apply event cut, and get data from root trees. Once substantiated with appropriate information (see documentation for the contructor), class ReadRootTree provides the following important methods:

  * `setEventCut()` - apply event cut to the root tree
  * `saveToNewFile()` - save the events after a event cut into a new root file
  * `fillValues()` - the most important methods which works using a callback (function pointer) interface to provide data from a root tree for plotting, drawing, etc.

For other methods, see the [header file](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/ReadRootTree.h) for documentation.

### _class Draw_ ###

This the class where all the drawing takes place, and it also interfaces methods for TCanvas such as set current TCanvas, clear TCanvas, save to file, etc.

The drawing part of the class takes information from a `ReadRootTree` object, which is set using method `setSourceRootTree()`. A variety of drawing methods exists, such as `draw2DGraph()`, `drawPolarGraph()` etc., and one can also add new drawing methods.

The Draw class keeps a private member variable `*canvas` which points to the current TCanvas; therefore to use the Draw class, one has to keep this pointer updated as to where to draw the graph/plot on, using method `setCanvas()`. In the main user interface in this program (which coordinates several TCanvases), the form calls the `setCanvas()` every time the user changes to another tab (thus to a different TCanvas).

#### Adding a new drawing method ####
One can have two kinds of drawing methods:
  1. Simple drawing method. In this kind of method, one simply draws on the `*canvas` pointer using the normal root drawing routines. For exmaples, refer to the methods `drawAntennaPosition()` and `drawGrandeCoordinates()`.
  1. Drawing methods that takes data from a root tree. This kind of drawing method makes use of the ReadRootTree class and the `fillValues()` function from that class. Each such drawing method has one or more associated callback function whose names have prefix `getValues_`. The callback function is passed on to the ReadRootTree object when `ReadRootTree::fillValues()` is called, and then inside the `fillValues()` method, the callback function is called for every event read from the root tree/chain (until the last event available or until the callback function returns a non-zero value). The callback method gets a reference object (like a TGraph) and adds the point to the graph each time it is called. See methods `draw2DGraph()` and its accompanying `getValue_2DTGraphErrors()` for an example of how this callback interface works. The procedures for adding a new drawing method is follows:
    * Create a member function in the class `Draw`, and in the method declare and use a ROOT object like TGraphErrors like usual in a ROOT macro. The information like which Root tree to use (via the object ReadRootTree, which can be initialized with` setSourceRootTree()`), which TCanvas to drawn on, etc. should be already set earlier.
    * When it is time to get the data on the graph, instead of using a `for` loop or similiar constructs, call `ReadRootTree::fillValues()`. This function takes three parameters, the first is a pointer to a callback function, which will be described below, the second is any abitrary object (NULL is fine, too) which will be passed onto the callback function, and the third a vector of strings. The vector of strings, `arg`, should contains mathematical expressions involving the branch names in the ROOT tree.
    * For each event in the ROOT tree remaining after an event cut (if any), the `ReadRootTree::fillValues()` function will read the event and evaluate each of the string in the `arg` parameter using the values from the ROOT tree, and results are stored in a vector of floats of the same size and in the same order as the vector of strings `arg`. The callback function will then be called with the results along with the object passed on earlier and some other helpful parameters.
    * The callback function should have the signature `(void* obj, int& index, vector<float>& values, long& total_n)`, where `obj` is the abitrary object passed on earlier to the `fillValues()` function, `index` is the event number, values are the results after evaluating the vector of strings `arg`, and `total_n` is the total number of events. The callback function should return 0, if everything is normal, or any other integer, if it wants to signal that the fillValues() function should stop. (One use of it in the program is in the View Data dialog, where the callback function return non-zero value when `index` is is greater than a certain number so that the user interface won't be freezed when trying to display a huge ROOT file).
    * Inside the callback function, one can do anything with the values given. A common use, of course, is to add the data points on the graph. For example, the callback function associated with `draw2DGraph()` casts the `void* obj` into a `TGraphError*` and set points and errors on the `TGraphError*` every time it was called.

### _Using the wrapper classes in external projects_ ###

The wrapper layer of the program can be used indepedently of the rest of the program; just include the following files in the Makefile:
  * ReadRootTree.cpp, ReadRootTree.h
  * Draw.cpp, Draw.h
  * all files under the directory /muParserLib

It could be possible as well to use these two classes in the ROOT interpreter, since there are no external dependency except muParser, although this use is untested.


---


## User interface ##

The user interface consists of several forms, all of which are under the directory [forms/](http://code.google.com/p/lopes-eventbrowser/source/browse#svn/trunk/forms). As customary in QT3 programming, each "form", which is simply a dialog with its code, composes of a .ui file and an optional .ui.h file.
  * The .ui file is a xml file containing the layout of the dialog and is generated and edited by the `designer` program which comes with the QT3 development package. One should not edit this file by hand; instead, open this file in the designer program, which one can start by typing `designer` in the terminal if the QT3 development package is installed properly.
  * The .ui.h file is rather strange - it is a header file, as it has the extension .h and is included whenever the form is compiled, but it actually contains definitions of the functions used by the form.

_Note: To change and modify the user interface part of the program, one needs to understand the QT concept of [signals and slots](http://doc.trolltech.com/3.3/signalsandslots.html), which connects the user actions such as clicking a button to a function._

Before the program compiles, a QT tool qmake actually generates a C++ source code from the .ui and .ui.h files, which can be found under the `build` directory after compilation. Note: in the include's, one sometimes finds files that do not seem to exist in the source tree (like "mainform.h", which is included in [main.cpp](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/main.cpp)); that is because the file mainform.h is generated before compilation by the qmake program.

The main user interface dialog is mainform.ui. The usual startup place for a c++ program, main() (located in [main.cpp](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/main.cpp)), simply substantiate an instance of the class mainform, and starts the mainform dialog. From the mainform dialog, several other dialogs might be called depending on the usage.

### _mainform_ ###
This dialog maintains a tabbed-interface consists of a [QListView](http://doc.trolltech.com/3.3/qlistview.html), which is the "tab" part of the interface, and a [QWidgetStack](http://doc.trolltech.com/3.3/qwidgetstack.html), which contains the actual widgets. Each of the widget in the QWidgetStack contains a TQWidget, the ROOT widget.


---


## Program state persistence ##
This part of the program is responsible of saving the state of the program so that program settings, etc. can be recovered after the program is restarted. The relevant classes are [Canvas](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/Canvas.h),[CanvasCollection](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/CanvasCollection.h), [ColumnCollection](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/ColumnCollection.h), and a header file [GraphInfo.h](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/GraphInfos.h), which contains definitions for several types of graphs the program can draw.