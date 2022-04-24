# invreturn
A program that calculates returns from compound interest.

# Compiling
Compiling the program is simple. Although I haven't tested it on Windows, I believe the process would be roughly the same. Simply compile the two files of ``invreturn.c`` and ``interesttools.c`` with your compiler of choice while passing the ``-lm`` and ``-lncurses`` flag. This will create a binary that uses the two ``.c`` files, allowing the program to run correctly. You'll also need to install the package for NCurses and developing with NCurses; for Ubuntu, those would be ``libncurses5`` and ``libncurses5-dev``, if I'm not mistaken.

# Usage
This program uses NCurses. The "Main Menu" screen will ask if you want to calculate one or two investments, using a simple menu-bar. Use the arrow keys to navigate and the enter key to select your choice. Then, enter the relevant information as its requested, pressing the enter key to confirm your input. After inputting all the needed info, you can press the up and down arrow keys to see the investments pan out. Simply press the enter key on this screen to exit the program.

# Credits
Special thanks to users ``b-fuze (Mike32)`` and ``Xen`` on the Ubuntu Hideout Discord server for helping me fix all the bugs, from SegFaults to issues with Pointers. Further thanks to ``DWD (Daniel) - The Danfather``, also from the Ubuntu Hideout server, for assisting with the additions of color to the program.

# Updates
_Version 2.2.1_ (April 24th, 2022)
- Fixed year-highlight algorithim through simplification, placement of the window that displays the years passed is now in a fixed position.

_Version 2.2_ (April 23rd, 2022)
- Added a feature that highlights when a year has passed, will state how many years have passed in the calculations.

_Version 2.1_ (April 19th, 2022)
- Color has arrived!
- Cleaned up the code; standardized spacing, added helpful comments, etc.
- Improved the menu in the main function. Now provides information on licensing and has a link to the Github page.
- Fixed bug with the page system; Week 0 will now display on every week as intended.

_Version 2.0_ (April 12th, 2022)
- Added NCurses Support
- Removed limit for calcuations; it's all handled within the page system.
