# Naming convention #
In general the names of variables, functions, etc. follow the format of starting with lower case with each subsequent word capitalized, e.g. oneLongVariableName. Constants and enum members are all capital letters using underscore as separator, e.g. ENUM\_NAME. Classes are named similiar to the variable except the first letter is capitalized. The names are usually descriptive unless it is a counting or local variable.

## UI elements ##
All UI elements/widgets, except labels which does not show up in the code, are named using the Hungarian notation, e.g. btnApply, with prefixes:
  * txt = lineEdit or textEdit
  * cmb = comboBox
  * btn = button
  * lbl = label
  * lv  = listView
  * gb  = groupBox
  * ckb = checkBox

# Code Formatting #
The formatting follows the standard c++ code formatting. Lines are kept under 80 characters long for easy reading, and spaces (instead of tab) are used for indenting.