To view the data in a ROOT tree, choose from the menu of the [main dialog](MainDialog.md) "Tools - View data in ROOT tree", or click the "View Data" button in the [main dialog](MainDialog.md) underneath the Event cut textbox. This will direct you to this dialog:

[![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_viewevents.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/dialog_viewevents.png##) (click to enlarge)

Here you are shown a table of the data in the ROOT tree, with the columns as the ROOT tree branches. **NOTE**: If the ROOT tree contains lots of events, only the first 500 are shown (otherwise the user interface will easily freeze!). To change this limit, you can change the define `MAX_NUM_EVENTS` in source file [forms/formviewdata.ui.h](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/forms/formviewdata.ui.h), but this is not recommended, since this table view is only designed to give a snapshot of how the data look like.

From this dialog you can apply event cuts and save the events after cut in a new ROOT file.