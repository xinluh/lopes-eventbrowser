Lopes-Eventbrowser is qt-based browser for the [LOPES](http://www.astro.ru.nl/lopes/) collaboration at Forschungszentrum Karlsruhe, designed to simplify data analysis of data obtained from both the LOPES antennas as well as the KASCADE-Grande stations. This program provides a QT-powered, easily extensible user interface for browsing data stored in ROOT files, using ROOT as the backend.

## What's New? ##

  * Aug 23, 2008 - Experimental support for QT4 is added; QT3 support is thus dropped in the trunk and the QT3 branch is moved to branches/qt3-branch.

## Purpose ##

This project is started as a 3-month-long [DAAD RISE](http://www.daad.de/rise/en/) project with student Xinlu Huang and supervisor P. Gina Isar. The initial intent of the project is to provide a graphical interface to visualize the data coming from the LOPES experiment, similar to another browser display which was done also by a DAAD RISE project in summer 2007 for the KASCADE-Grande experiment.

As the development evolves, the project became more general in its input, namely, as of the end of the initial project in summer 2008, the eventbrowser is accepting any ROOT file containing ROOT tree of arbitrary data, and provides a graphical interface to analyze the data. As the program has a design goal to be flexible, it is also potentially useful for data coming from other sources - as long as it comes in the form of a ROOT file.

## Get Started ##

To run Lopes-Eventbrowser, you have 3 options:
  * 1. _Get a pre-compiled version **QT3 only**_: a download link should be on the right side of this page under "Featured Downloads". Untar the package and follow directions in the included [README](http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/docs/README-for-compiled-package) file.
  * 2. _Compile from source, QT3 version_: check out the code using svn command
```
 svn checkout http://lopes-eventbrowser.googlecode.com/svn/branches/qt3-branch lopes-eventbrowser-qt3
```
> and then follow directions in CompilingEventBrowser. The library dependencies are described [here](LibraryDependencyQT3.md).
  * 3. _Compile from source, bleeding-edge version (QT4)_: **Warning: this is NOT a stable version!** Check out the code using svn command
```
 svn checkout http://lopes-eventbrowser.googlecode.com/svn/trunk lopes-eventbrowser
```
> and then follow directions in CompilingEventBrowser. The library dependencies are described [here](LibraryDependency.md).

The compiled version relies on two external libraries: QT3 runtime libraries and ROOT 5.18 with QT support. The former should come with standard linux distributions, and the latter one can either obtain the suitable binaries from the [ROOT website](http://root.cern.ch/root/Version518.html) or compile ROOT 5.18 from source with suitable flags to enable QT support as described in the ROOT documentations.

For a quick glance on how the program works, see QuickStartGuide.

For a list of what the program can do, see ProgramFeatures.

## Using the program ##

QuickStartGuide will, well, give you a quick start on the program.

There is a [Frequently Asked Questions](FAQ.md) page, if you have problems.

There are also other wiki pages that describe a specific feature of the program:
  * ConfigSettingFiles: describes the various setting files (`*`.cfg) used by the program, their format, and how they are used.
  * MainDialog: describes the layout of the main dialog, the major entry point to the program.

You can also check the [list of wiki pages](http://code.google.com/p/lopes-eventbrowser/w/list) for pages of interest.

## Start hacking! ##

To modify the code to your own need, you (obviously!) need a copy of the code, which you can get via SVN following direction [here](http://code.google.com/p/lopes-eventbrowser/source/checkout), and you might also want commit right to the repository - contact the project owners/members listed on the right of this page.

A good start is the wiki page CodeStructure, which should give a broad overview of how the code in this project is structured. If you decide to add code, please also have a look at NamingConventionAndFormatting, and follow the conventions listed there. There are also specialized pages for adding specific features to the program:
  * AddingNewGraphType

If you have nothing better to do ;p, check the [issue tracker](http://code.google.com/p/lopes-eventbrowser/issues/list) for unresolved issues; there are also "todo" comments all over the source code waiting for someone to fix...

## Contact / Support ##

Use the [issue tracker](http://code.google.com/p/lopes-eventbrowser/issues/list) to report bugs or request features.

The members of the project are happy to answer questions and to hear suggestions/comments. You can find their emails on the right side of this page.