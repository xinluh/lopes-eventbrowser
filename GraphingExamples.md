### Drawing a 2D graph ###

First define a cut if a cut is needed (see [cuts](Event.md)).

Then select "2D Graph" from the "Graph Type" drop-down list:

![http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_partial_2dgraph.png](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_partial_2dgraph.png)

Then Fill in the expressions for x- and y-axis; the expressions can be any reasonable expression involving the values of branches shown under the drop-down list "Availabe Branches".

If error bars are desired, check the checkbox "Use Errors" and fill in the appropriate values.

Then click "Draw" to plot the graph:

[![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_2dgraph.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/dialog_main_2dgraph.png##) (click to enlarge)

Notice that the canvas title under the list of canvases is automatically changed to _x-axis_ - _y-axis_.

### Drawing shower angles ###
Select "Shower Angles" from the "Graph Type" drop-down list:

![http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_partial_showerangles.png](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_partial_showerangles.png)

Fill in expressions for "r-axis" and "theta-axis", remember that the latter has to be entered in radians (multiply by 3.14159/180 to convert from degrees to radians).

One can also manipulate the theta angle so that the directions north, east, etc. are shown in the normal way: use 360 - angle (in degree) to graph the points clockwise (instead of counterclockwise, which is customary for polar graphs), and use angle + 90 to rotate the graphs so that 0 degree corresponds to north.

The shower angles graph is color coded; the points on the graph is given color in a rainbow fashion depending on the values of the field "color code by"; the color code is also shown on the graph in a legend on the right.

A sample graph using the parameters in the screenshot above:

[![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_main_partial_showerangles1.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/dialog_main_partial_showerangles1.png##) (click to enlarge)