## Introduction ##

Part of the design goal of this program is that it could be easily extended, and one of the anticipated most common extension to this program is to add a new type of graphs. Currently the program is capable of graphing graphs described in ProgramFeatures, but it is relatively easy to add more types. This documents describes how.

## To begin ##

  * Test the graph you want first in a c++ macro with the ROOT interpreter.
  * The various steps described below are detailed in the code. Check out the comment in the code that begins with `##` - those are intended to facilitate adding a new graph type. The text surrounded by underscores like `_text to be replace_` are usually intended to be replaced by appropriate values specific to the new graph you are adding.

## Step by step ##

  1. Tell the source that you are adding a new graph type:
    * Add a new enum member to the `enum graphTypes` in [Canvas.h](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/Canvas.h). This enum member is for identification purpose, so give it a descriptive but unique name and capitalize the name as per [convention](NamingConventionAndFormatting.md) in this project. Don't mess with the member LAST\_ITEM, and leave it last.
    * Add the description of the new graph to the array `graphTypeDescriptions` in the same place you added the enum member above. The two enum/array should be in sync in position.
    * After doing above, when the program compiled and ran, the user will see a new option in the "Graph Types" drop-down list in the main dialog for your new graph type, but when selected, will be informed that this is not yet implemented.
    * Search (or grep if you like) [Canvas.cpp](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/Canvas.cpp) for addtional comments containing `##` for additional tasks to do. These are usually in some kind of switch statement, which unfortunately cannot be programatically adapted to the newly added graph types.
  1. Define a new struct inheriting from `struct infoGraph` in [GraphInfos.h](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/GraphInfos.h). The struct will contain information that you might need for the graphing (for example, to draw a 2D graph one might need the expression for the x- and y-axis) and also important methods for drawing and saving.
    * A template of how to define the struct in at the very end of the file; copy and uncomment the template and start working from there. You can also look at the other structs in the same files for example.
    * This part might involve some tedious copy&paste, especially for the saving to/reading from file part, so make sure that you have a competent text editor! (The copy/paste rectangle functionality in Emacs comes very handy).
  1. Define how the graph will be drawn. Of course, this is the most important part. Depending on from where the graph is getting data, you might be able to just copy and paste a ROOT c++ macro or have to modify it. See ["Adding a new drawing method"](CodeStructure#Adding_a_new_drawing_method.md) for more information how to do this part.
  1. Define the user interface. The program will need to know somehow what the user input are, and this is done in the main dialog.
    * Fire up `designer` (which should come with the QT3 development package), and open the file [forms/mainform.ui](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/forms/mainform.ui) in designer:
    * 
> [![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/designer_graphtype_widgetstack.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/designer_graphtype_widgetstack.png##)
> (click to enlarge)
    * 
    * Right click on the small arrows in the upper right hand corner of the WidgetStack and choose the item "Add Page" to add a new widget to the stack, then rename the widget to something sensible (for example, the 2Dgraph widget is named tabGraph2D). This new widget is where you will ask the user for information, and you can do so by adding QLineEdit, QLabel, etc. It would be much clearer if the widgets that will be used later are named descriptively (it's easier to tell what txtXAxis is than lineEdit1). See also [naming convention](NamingConventionAndFormatting.md).
    * Read ["User interface"](CodeStructure#User_interface.md) for more information on the user interface in this program, and read the help files from QT if you want more information on widgets, how to use designer, and user interface programming in QT in general.
  1. Now the preliminary parts are done, it's time for connecting the user's input to the program output.
    * Search the source file [forms/mainform.ui.h](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/forms/mainform.ui.h) for comments containing `##` and follow the instructions in those comments. This mainly is to get the information from the user interface into the infoGraph struct which you defined earlier.
  1. Cleaning up: search the entire source tree for comments containing `##` to see if you forgot to do something.

**That's all! You are finished, now compile and run the program!**