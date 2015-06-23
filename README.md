Lopes-Eventbrowser is qt-based browser for the [LOPES] collaboration at
Forschungszentrum Karlsruhe, designed to simplify data analysis of data
obtained from both the LOPES antennas as well as the KASCADE-Grande
stations. This program provides a QT-powered, easily extensible user
interface for browsing data stored in ROOT files, using ROOT as the
backend.

What's New?
-----------

* Aug 23, 2008 - Experimental support for QT4 is added; QT3 support is thus dropped in the trunk and the QT3 branch is moved to branches/qt3-branch.`

Purpose
-------

This project is started as a 3-month-long [DAAD RISE] project with
student Xinlu Huang and supervisor P. Gina Isar. The initial intent of
the project is to provide a graphical interface to visualize the data
coming from the LOPES experiment, similar to another browser display
which was done also by a DAAD RISE project in summer 2007 for the
KASCADE-Grande experiment.

As the development evolves, the project became more general in its
input, namely, as of the end of the initial project in summer 2008, the
eventbrowser is accepting any ROOT file containing ROOT tree of
arbitrary data, and provides a graphical interface to analyze the data.
As the program has a design goal to be flexible, it is also potentially
useful for data coming from other sources - as long as it comes in the
form of a ROOT file.

Get Started
-----------

To run Lopes-Eventbrowser, you have 3 options:

* 1. _Get a pre-compiled version *QT3 only*_: a download link should be on the right side of this page under `“`Featured`
`Downloads`”`. Untar the package and follow directions in the included `[`README`]` file. 
* 2. _Compile from source, QT3 version_: check out the code using svn command and then follow directions in CompilingEventBrowser. The library dependencies are described [LibraryDependencyQT3 here].
* 3. _Compile from source, bleeding-edge version (QT4)_: *Warning: this is NOT a stable version!* Check out the code using svn command 
and then follow directions in CompilingEventBrowser. The library dependencies are described [LibraryDependency here].

The compiled version relies on two external libraries: QT3 runtime
libraries and ROOT 5.18 with QT support. The former should come with
standard linux distributions, and the latter one can either obtain the
suitable binaries from the [ROOT website] or compile ROOT 5.18 from
source with suitable flags to enable QT support as described in the ROOT
documentations.

For a quick glance on how the program works, see QuickStartGuide.

For a list of what the program can do, see ProgramFeatures.

  [LOPES]: http://www.astro.ru.nl/lopes/
  [DAAD RISE]: http://www.daad.de/rise/en/
  [`README`]: http://code.google.com/p/lopes-eventbrowser/source/browse/trunk/docs/README-for-compiled-package
  [ROOT website]: http://root.cern.ch/root/Version518.html
