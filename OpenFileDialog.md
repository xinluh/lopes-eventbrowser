This dialog will open every time you start Lopes-Eventbrowser, and when you choose File -> Open from the [main dialog](MainDialog.md).

Screenshot:

[![](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/dialog_openfile.png)](http://lopes-eventbrowser.googlecode.com/svn/wiki/pic/large/dialog_openfile.png##) (click to enlarge)

When the program is first started, any file with extension .root locating in the startup directory of the program is automatically recognized and added to the list of files to be opened. If this dialog is invoked from the menu in [main dialog](MainDialog.md), the ROOT file(s) currently opened will be in the list instead.

To open other files, click "Browse..." and select one or more files (by holding down SHIFT or CTRL key). Multiple files will be opened as a root chain.

_Note: This program will read any root trees created by compatible versions of ROOT._

Once the files are added to the list, the list of root trees present in the root file is automatically detected, and one can select one from the drop-down list. The first ROOT tree found is selected by default.

After you selected a ROOT tree to open, there are two options for reading branches from a root tree. The easiest one is the "Default" option, which reads all compatible branches (i.e. branches of integer or float data type). But one can also use a text file, which is handy when one needs only a subset of branches. The use of this config file is explained in ConfigSettingFiles.

Click OK to proceed.