Store 3 - Binary Search Tree
============================

This is a compilation of a store programs I wrote for academic purposes using three different data structures from scratch.Store 3 is implemented using binary search tree. When the program starts it allocates memory for 4 products on heap. Since this version is implemented using binary  search tree, therefore it is possible to allocate memory during runtime. To keep things simple I decided to sort products by a code value, so when displaying products on the screen, they will be printed out in an increasing order.

Files included:
* products.txt - sample database
* codes.txt - codes for products
* main.h & main.c - heart of a program
* product.h & product.c - general functions for working with products
* file.h & file.c - functions for working with files
* utils.h & utils.c - utilities functions

Note: All the code is written in pure C programming language, however header file conio.h is inlcuded in this program(windows.h is also included for rendering reasons), which is not part of ANSI C standard.

This program was made entirely by Marko Kosir, it is freeware, feel free to use this code or change it in any way you like. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Tested - Windows XP  
Compiled - Microsoft Visual Studio 2005  
MVS 2005 compiler gives you warnings about some of the functions and suggest that you should use ISO C++ functions and replace deprecated ones, if you want feel free to do it.

Upgrade log:  
-ported to MVS 2010  (18.9.2010)

![screenshot](https://github.com/markokosir/store3binarysearchtree/blob/master/readmeScreenshot.JPG)