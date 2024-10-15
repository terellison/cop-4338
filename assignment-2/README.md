<div align="center">

# COP-4338 System Programming

### Programming Assignment 2:

### C Pointers and Strings

### FIU Knight Foundation School of Comp. & Info Sciences
</div>

</br>

In this assignment, you will write a program that gets a pattern string from command-
line arguments, receives multiple lines from the standard input stream, and finally prints out
the lines containing the pattern string.

## 1. Program Command Line Arguments

The program must support the following command-line arguments:

- (10 points) -n: prints out the line numbers that contain the pattern string. Please note
    that line-numbering starts from 1.
- (10 points) -x: prints out the lines that do not contain the pattern string; i.e. it
    excludes the lines containing the pattern string.
- (10 points) -s: prints out the lines in alphabetical order. Without this fag, the default
    order is FIFO.
- (10 points) -r: prints out the lines in the reverse order (the line that appears last in
    stdin will appear first in stdout). Please note that you must make sure that user does
    not use -s and -r fags at the same time. If user wants to use both -s and -r fags, your
    program must get terminated after giving proper error message to the user.
- (10 points) -m: finds the pattern string only if it matches the whole word. You can
    assume that words are separated by white-space character only.
- (5 points) -c: ignores the case when finding the pattern string.
- (15 points) -f: prints out the index of the first occurrence of pattern string in each line.
    Please note that you must make sure that user does not use -f and -x fags at the same
    time. If user wants to use both -f and -x fags, your program must get terminated after
    giving proper error message to the user.
- (20 points) -p: partially prints out each line containing the pattern. To print out
    each line partially, you need to print the first 10 characters of the line, followed by an
    ellipsis (... ), followed by the pattern followed by another ellipsis, followed by the last 
    five characters of the line. You can remove the first ellipsis if the pattern overlaps the
    first 11 characters. Also, you can remove the second ellipsis if the pattern overlaps
    the last six characters. Additionally, you can print the whole sentence if the length
    of sentence is not greater than the pattern length plus 15. Please note that you must
    make sure that user does not use -p and -x fags at the same time. If user wants to
    use both -p and -x fags, your program must get terminated after giving proper error
    message to the user.

</br>

## 2. Input/Output of Your Program

Your program must accept a sequence of lines followed by an EOF character from standard
input stream. Here is an example of program input:

I’m very interested in Computer Science ←- </br>
This is a test statement ←- </br>
I’m in ←- </br>
In-N-Out has great burgers in fact ←- </br>
Last sentence In `Ctrl +D`

The output is given under different combinations of command-line arguments:


| CLAs      | Expected Output                           |
| --------- | ----------------------------------------- |
| `./find in`| I’m very interested in Computer Science   |
|           | I’m in                                    |
|           | In-N-Out has great burgers in fact        |
|`./find -fmcr in`|   @14: Last sentence In                     |
|                  |  @27: In-N-Out has great burgers in fact |
|                  |  @4: I'm in                              |
|                  |  @20: I'm very interested in Computer Science! |
| `./find -pxsn is`| fatal error: can't use -p and -x in the same execution |
| `./find -pnm in` | 1. I'm very i...in...ence! |
|                  |  3. I'm in                 |
|                  |  4. In-N-Out h...in fact   |

## 3. Submissions

You need to submit a .zip fle compressing the followings:

- all .c and .h fles

- (10 points) makefle which organizes the compilation process of your program. Use
    the word “fnd” to name the executable of your program.


