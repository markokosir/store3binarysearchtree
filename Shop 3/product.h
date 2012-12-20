/***********************************
*
*       product.h
*
***********************************/

#ifndef PRODUCT_H
#define PRODUCT_H

#include "main.h"

#define ARROW_UP 328    
#define ARROW_DOWN 336
#define RETURN 13
#define NORMAL_CURSOR 1
#define NO_CURSOR 0

//function prototypes
void EnterProd(struct goods **root);
void DeleteProd(struct goods **root);
void FindProd(struct goods **root);
void SellProd(struct goods **root);
void DisplayProd(struct goods **root);
int RecDisplay(struct goods *root);
int KeyPress(void);
int Menu(void);
void ClrScr(void);
void SetCursorType(int cursor);

//global variables
extern int count;//for counting products


#endif //PRODUCT_H