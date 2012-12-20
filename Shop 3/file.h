/***********************************
*
*       file.h
*
***********************************/

#ifndef FILE_H
#define FILE_H

#include "main.h"

//function prototypes
int CheckExist(const char *file_name);
void SaveProd(struct goods **root);
int RecSave(struct goods *root, const FILE *p);
void LoadProd(struct goods **root);
void CheckSave(const int save, struct goods **root);

#endif //FILE_H