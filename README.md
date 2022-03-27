# invreturn
A program that calculates returns from compound interest.

# Compiling
Compiling the program is simple. Although I haven't tested it on Windows, I believe the process would be the same. Simply compile the two files of ``invreturn.c`` and ``interesttools.c`` with your compiler of choice while passing the ``-lm`` flag. This will create a binary that uses the two ``.c`` files, allowing the program to run correctly.

# Usage
The program is currently exclusively CLI. After being prompted to select ``1`` or ``2`` investments, you will be asked to enter the initial investment, intrest rate, and period in weeks for either one or two investments. Then, you will be requested to enter the amount of weeks that will be calculated by the program. After this, the program will output the returns from the investment by week. If two investments were selected,the investments' final returns will be calculated, with the greater return being divided by the smaller return, and the program will proceed to output the percentage.

# Credits
Special thanks to users ``b-fuze (Mike32)`` and ``Xen`` on the Ubuntu Hideout Discord server for helping me fix all the bugs, from SegFaults to issues with Pointers.
