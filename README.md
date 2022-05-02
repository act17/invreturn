# invreturn
A program that calculates returns from compound interest.

# Compiling
Compiling the program is simple. Although I haven't tested it on Windows, I believe the process would be roughly the same. Simply compile the files of ``invreturn.c``, ``interesttools.c``, ``oneinterest.c``, ``twointerest.c``, and ``optionmenu.c`` with your compiler of choice while passing the ``-lm`` and ``-lncurses`` flag. This will create a binary that uses the five ``.c`` files, allowing the program to run correctly. You'll also need to install the package for NCurses and developing with NCurses; for Ubuntu, those would be ``libncurses5`` and ``libncurses5-dev``, if I'm not mistaken.

# Usage
This program uses NCurses. The "Main Menu" screen will ask if you want to calculate one or two investments, using a simple menu-bar. Use the arrow keys to navigate and the enter key to select your choice. Then, enter the relevant information as its requested, pressing the enter key to confirm your input. After inputting all the needed info, you can press the up and down arrow keys to see the investments pan out. To return to the Main Menu from this point, simply press the Enter key.
With Version 2.3, there's additional commands the user can issue to the program from the Main Menu. Pressing the "X" key will exit the program, and pressing the "O" key will open the options menu.

# Credits
Special thanks to users ``b-fuze (Mike32)`` and ``Xen`` on the Ubuntu Hideout Discord server for helping me fix all the bugs, from SegFaults to issues with Pointers. Further thanks to ``DWD (Daniel) - The Danfather``, also from the Ubuntu Hideout server, for assisting with the additions of color to the program.

# Updates
_Version 2.4_ (May 2nd, 2022)
- Current time is now displayed and updated every second.
- Fixed a memory leak in the ``oneinterest()`` and ``twointerest()`` functions.
- Fixed (?) issue where the year-count window printed zero for every increase in digits. (E.g., going from year 9 to year 10, then back to year 9 would add an extra zero to the end making it appear as 90.)
- Removed redundant ``initscr()``.
- Corrected header file issues.
- Added a new Makefile.
- Removed a redundant variable.
Special thanks to user ``rene`` on the Linux Mint forums for showing me these issues.

_Version 2.3_ (April 28th, 2022)
- Added an options menu.
- Moved the functions ``oneinterest()`` and ``twointerest()`` to their own seperate files, using one header file titled ``interest.h``.
- Added two new background colours that the user can choose; green and magenta.
- Added a new "extra" window for the Main Menu. Includes the version, current time, and reference for the two new key-based commands.

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
