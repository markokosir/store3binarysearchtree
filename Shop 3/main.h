/***********************************
*
*       main.h
*
***********************************/

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include "utils.h"
#include "product.h"
#include "file.h"

typedef struct goods
{
		char product_name[14];
        int code;
        int supply;
		float price;
        struct goods *left;
        struct goods *right;
}goods;

//function prototypes
void FreeBST(goods *product);

//global variables
extern int z;//products saved?

#endif //MAIN_H