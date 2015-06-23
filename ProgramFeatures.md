## Features ##

Lopes-Eventbrowser will read any abitrary ROOT tree produced by a compatible version of ROOT and use the data in the ROOT tree for analysis.

The current notable features are:

  * **User interface**
    * Provides a tabbed interface for easy switching between multiple canvases.
    * Provides an option (in the main dialog) "Draw in new tabbed window" to draw each sucessive graph in a new tab, making graphing multiple graphs convenient.
    * Tabs can be saved either one by one or altogether in formats supported by ROOT, such as postscript, pdf, ROOT, c++ macro, images, etc.
    * Program functions are accessible through user interface for quick access; some completions are supported, such as the branch names from the ROOT file, to minimize typos.
    * Provides a table view of data in ROOT file with customizable columns.

  * **Graphing**
    * Can use data from any compatible ROOT tree for customizable graphing. The parameters are taken from user input, therefore convenient for testing out several conditions.
    * See [graph types](Available.md) for graph types currently available.
    * The code structure around graph types are designed to be extensible; therefore it's straightforward to extend the program to include more graph types. See AddingNewGraphType.

  * **ROOT file manipulation**
    * Can handle abitrary ROOT file or files (using `TChain`) containing ROOT `TTree`, independent of the structure inside the root tree. The relevant information such as branches present is discovered programatically.
    * Provides a convenient interface for applying event cuts to ROOT tree: feedback such as number of events after cut are given immediately, and the resulting events after cut can be saved in a new ROOT file. Event cuts can be saved to facilitate switching between different cuts.
    * Reading of ROOT tree is customizable through a config file which can specify selected branches for reading - useful for saving a subset of branches in a ROOT tree to a new ROOT tree. See ConfigSettingFiles, section "Root branches configuration file".
    * Data in a ROOT tree can be displayed in the user interface in a table.

  * **Importing/Exporting**
    * The canvases created during a session of the program can be exported to a text file, which can be imported later by the program for further editing. This is useful for persisting information between program sessions as well as working on multiple groups of canvases. The text file is also easily editable by hand, creating possibility for other uses. ConfigSettingFiles, section "Canvas definition file".
    * The canvases can also be saved in other useful formats supported by ROOT, namely, postscript, EPS, PDF, JPEG, GIF, c++ macro, and ROOT binary. For the format postscript, there is also an option to save all canvases to a single file.

#### Available graph types ####

You are not limited to any of the single options listed below; by checking the option "Draw multiple graphs on the same canvas" in the main dialog, you can combine graphs - for example, to see visually where the incoming showers are relative to the LOPES antennas, you can draw the antennas position then draw the x-position vs. y-position of incoming showers on top of that.

  * **1D Histogram**: plain normal histogram; one can specify the min and max as well as the bin numbers of the axis.
  * **2D Graph**: The typical x vs. y graph; one can also specify error bars for either or both x and y values (to use error bars for only x or y values, enter `0` for the other error).
  * **Polar Graph**: The typical polar graph of r vs. theta values; one can also specify errors bars values.
  * **Shower Angles**: This is a specialized graph which shows the incoming air shower angles in a color coded polar graph. The values for r and theta, as well as the value with which to color, can be specified by the user.
  * **Hardware Layouts**: plot the positions of either the LOPES antennas or the Grande Stations.
  * You are welcome to add more! See [here](AddingNewGraphType.md) for a step-by-step HOWTO.


---


## Limitations ##

  * Currently when reading from a ROOT file, only data types `float` and `int` will be recognized; other data types such as string, double, etc. will be ignored. Additionally, when evaluating expressions for graphing purposes, only `float` is supported - that is, the program will generate an error if one attempts to do mathematical operations on an integer type.
    * One can overcome the second limitation (i.e. cannot evaluate integer expressions) by defining the symbol `TREAT_INTEGER_AS_FLOAT` in file [ReadRootTree.cpp](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/ReadRootTree.cpp), but be aware that there will be loss in precision.
  * When exporting the canvases to a config file, only the last graph drawn on a canvas will be exported if one has drawn several graphs on the same canvas using the "Draw multiple graphs on the same canvas" option in the main dialog.