#### **Q: Why is the labels on the graph are oversized, placed in wrong positions, or in general ugly looking?** ####
A: Likely you don't have some fonts installed. Check the console window where you started the program to see if ROOT issued some warnings like
```
`The font "symbol.ttf" was not installed yet
 Substitute it with "Arial"
 Make sure your local "~/.fonts.conf" or "/etc/fonts/fonts.conf" file points to "$ROOOTSYS/fonts" directory to get the proper support for ROOT TLatex class`
```

#### **Q: Why do I know what version of the program I have?** ####
A: If you compiled the program yourself, the SVN version you checked out is the version. If you downloaded a compiled version, the tarball should have the suffix -r`*` (like `lopes-eventbrowser-r25`), where `*` is the SVN version number.

#### **Q: Why do I know whether I have the latest version?** ####
A: See question above to find out which version you have, then check [this page](http://code.google.com/p/lopes-eventbrowser/source/list) for the recent commits. If your version number matches the largest revision in the page, you have the latest version.

#### **Q: Why do I get messages like "sorry, this is not implemented"?** ####
A: Well, as the message says, the feature you try to use is not implemented. Maybe it will be some time in the future...

If you have read somewhere (on the wiki maybe) that the feature is actually present, check if you have the latest version. See question above for how.

### **Your question not answered?** ###
Ask support by emailing the project owners/members; their emails are listed in the right side of the [project home page](http://code.google.com/p/lopes-eventbrowser/).