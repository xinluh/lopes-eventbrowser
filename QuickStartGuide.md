_This assumes that one already has a compiled binary version and has the necessary libraries correctly linked. If not, see CompilingEventBrowser and LibraryDependency._

To start the program, from a terminal, cd to the directory where the program is located, and use command:
```
./browser
```

If you downloaded the compiled version, use instead:
```
. browser.run
```
as the script `browser.run` sets the enviromental variables pointing to a known working version of ROOT 5.18 in the IK.FZK cluster.

A sample ROOT file [test\_root\_file\_tree-ka104ev.root](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/test_root_file_tree-ka104ev.root) should be included in both the source code and the compiled tarball. The guide below will use this sample file.


### Open File Dialog ###

First one will be greeted by a dialog asking for the ROOT files to be opened:

[![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_openfile.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/dialog_openfile.png##) (click to enlarge)

The sample ROOT file should show up in the list of files to open, as all files with extension .root locating in the same directory of the program are automatically detected when the program is first started.

Simply click Ok to continue.

For more explanation on the options on this dialog, see OpenFileDialog.


---


### Main Dialog ###

Then you will be presented the [main dialog](MainDialog.md):

[![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/dialog_main.png##) (click to enlarge)

The ROOT files selected will be opened (the title of the window will reflect this), and now one is ready for making analysis of the data in the ROOT trees.

Instead of creating some new graph now, let's look at some example. Go to the menu of this dialog, choose File -> Import Canvases, and from dialog then popped up, choose the file "sample\_canvases.cfg", which is included in both the source code and the compiled tarball:

[![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_partial_import_canvases.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/dialog_main_partial_import_canvases.png##) (click to enlarge)

The program should then contains some canvases imported from the sample\_canvases.cfg:

[![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_sample_canvases.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/dialog_main_sample_canvases.png##) (click to enlarge).

You can now click on the names of the canvases and play around a little bit.

Now let's create a new canvas. You can see a screen shot illustrating the various steps:

[![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_tutorial.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/dialog_main_tutorial.png##) (click to enlarge)

Click the ![http://lopes-eventbrowser.googlecode.com/svn/trunk/bitmaps/list-add.png](http://lopes-eventbrowser.googlecode.com/svn/trunk/bitmaps/list-add.png) button on the upper right hand corner in the dialog. You will notice a "Untitled Canvas" is created.

Let's say that we want to plot a normal 2D graph (x vs. y), so choose a "2D Graph" in the "Graph Type" drop-down list, and you will be presented with some options. For now we are only interested "x-axis" and "y-axis" (if you want error bars, check the checkbox "Use Errors" and enter information for the errors). Enter "XC" and "YC" in the textbox, respectively. "XC" and "YC" are two branches present in the sample ROOT file, and we are now plotting them.

To make a cut in the event selection, simply enter a cut in the Events textbox or select one from the "Saved cuts" drop-down list, and click "Apply cut."

Notice that the "Apply cut" button is greyed out after applying the cut, signifying that the cut has been applied, and also notice that the number of events after cut is displayed in the lower right hand corner.
![http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_partial_eventnumber.png](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_partial_eventnumber.png)

Now click "Draw" and voila, you have a 2D plot on the canvas.

For more explanations on options on this dialog, see MainDialog.

For see more examples of graphing, see GraphingExamples.