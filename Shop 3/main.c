/********************************************************************************************************
Program: Store 3 - Binary Search Tree
Author: Marko Kosir

This is a compilation of a store programs I wrote for academic purposes using three different 
data structures from scratch. Store 3 is implemented using binary search tree. 
When the program starts it allocates memory for 4 products on heap. Since 
this version is implemented using binary  search tree, therefore it is possible 
to allocate memory during runtime. To keep things simple I decided to sort products 
by a code value, so when displaying products on the screen, they will be printed out in
an increasing order.

Files included:
                - products.txt	                sample database
                - codes.txt						codes for products
                - main.h & main.c				heart of a program
                - product.h & product.c	        general functions for working with products
                - file.h & file.c				functions for working with files
                - utils.h & utils.c				utilities functions

Note: All the code is written in pure C programming language, however header file conio.h is
      inlcuded in this program(windows.h is also included for rendering reasons), which is 
      not part of ANSI C standard.               

This program was made entirely by Marko Kosir, it is freeware,
feel free to use this code or change it in any way you like.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

email: kosir.mar@gmail.com               

Tested - Windows XP
Compiled - Microsoft Visual Studio 2005
		   MVS 2005 compiler gives you warnings about some of the functions and suggest that you
		   should use ISO C++ functions and replace deprecated ones, if you want feel free to do it.

Released: July 29th, 2005

Upgrade log:
ported to MVS 2010  (18.9.2010)
********************************************************************************************************/
#include "main.h"

int z = 1;

int main()
{
        goods *root = NULL;//pointer to the root product of the tree
        goods **prev;
        goods *product;
        goods *search;
        //pointers for freeing memory
        goods *delete1;
        goods *delete2;
        int value;//star location
        int q;

        for(q = 0; q < 4; q++)
        {
                //save some products in memory
                product = NULL;
                product = malloc(sizeof(struct goods));
                if(product != NULL)
                {
                        if(q == 0)
                        {
                                strcpy(product->product_name, "APPLES");
                                product->code = 852;
                                product->price = 1.25;
                                product->supply = 30;
                        }
                        if(q == 1)
                        {
                                strcpy(product->product_name, "MILK");
                                product->code = 123;
                                product->price = 2;
                                product->supply = 30;
                        }
                        if(q == 2)
                        {
                                strcpy(product->product_name, "JUICE");
                                product->code = 121;
                                product->price = 2.39;
                                product->supply = 30;
                        }
                        if(q == 3)
                        {
                                strcpy(product->product_name, "CHOCOLATE");
                                product->code = 567;
                                product->price = 1.5;
                                product->supply = 30;
                        }
                        product->left = NULL;
                        product->right = NULL;
                        
                        prev = &root;
                        search = root;
                        while(search != NULL)
                        {
                                if(search->code < product->code)
                                {
                                        prev = &search->right;
                                        search = search->right;
                                }
                                else if(search->code > product->code)
                                {
                                        prev = &search->left;
                                        search = search->left;
                                }
                        }
                        *prev = product;
                }
                else
                {
                        printf("Not enough memory to start program!");
                        getch();
                        goto out;
                }
        }

        do
        {
                value = Menu();
                //turn on cursor
                SetCursorType(NORMAL_CURSOR);
                switch(value)
                {
                        case 0: EnterProd(&root);
                                break;
                        case 1: DeleteProd(&root);
                                break;
                        case 2: FindProd(&root);
                                break;
                        case 3: SellProd(&root);
                                break;
                        case 4: DisplayProd(&root);
                                break;
                        case 5: LoadProd(&root);
                                break;
                        case 6: SaveProd(&root);
                                break;
                        case 7: CheckSave(z, &root);
                                break;
                }
        }while(value != 7);

        out:;
        //free allocated memory for all products with a help of recursion
        FreeBST(root);
        root = NULL;

        return 0;
}

void FreeBST(goods *product)
{
        if(product == NULL)
        {
                return;
        }
        FreeBST(product->left);
        FreeBST(product->right);
        free(product);
}