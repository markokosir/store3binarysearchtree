/***********************************
*
*       file.c
*
***********************************/

#include "file.h"

int CheckExist(const char *file_name)
{
        FILE *d;

        d = fopen(file_name, "r");
        if(d == NULL)
        {
                return 0;
        }
        else
        {
                fclose(d);
                return 1;
        }
}

void SaveProd(goods **root)
{
        int j = 0;
        int e = 0;
        char file_name[20];
        char option;

        FILE *p;

        SetCursorType(NO_CURSOR);
        ClrScr();
        if(*root == NULL)
		{
				printf("No products to save.");
				getch();
				goto out;
		}

        change:;
        ClrScr();
        SetCursorType(NORMAL_CURSOR);
        printf("SAVE\n\n");
        printf("Save as: ");
        GetStr(file_name, 15);
        for(j = 0; j < 17; j++)
        {
                if(file_name[j] == 0)
                {
                        file_name[j] = '.';
                        file_name[j+1] = 't';
                        file_name[j+2] = 'x';
                        file_name[j+3] = 't';
                        file_name[j+4] = 0;
                        break;
                }
        }
        e = CheckExist(file_name);
        if(e == 1)
        {
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s already exist, do you want to replace it?(Y/N)", file_name);
                option = getch();
                if(option == 'Y' || option == 'y')
                {
                        goto overwrite;
                }
                else
                {
                        goto change;
                }
        }
        else
        {
                overwrite:;
                p = fopen(file_name, "w");
                if(p == NULL)
                {
                        SetCursorType(NO_CURSOR);
                        ClrScr();
                        printf("File %s can not be opened!", file_name);
                        getch();
                }
                //save products in database
                else
                {
                        //save products with help of recursion
                        RecSave(*root, p);
                        z = 1;
                        SetCursorType(NO_CURSOR);
                        ClrScr();
                        printf("File %s saved!", file_name);
                        getch();
                }
                fclose(p);
        }
        out:;
        SetCursorType(NORMAL_CURSOR);
}

int RecSave(goods *root, const FILE *p)
{
        int q = 0;

        if(root == NULL)
        {
                return 0;
        }
        RecSave(root->left, p);
        for(q = 0; root->product_name[q] != 0; q++)
        {
                if(root->product_name[q] == ' ')
                {
                        root->product_name[q] = '_';
                }
        }
        fprintf(p, "%16s\t%d\t%f\t%d\n", root->product_name, root->code, root->price, root->supply);
        for(q = 0; root->product_name[q] != 0; q++)
        {
                if(root->product_name[q] == '_')
                {
                        root->product_name[q] = ' ';
                }
        }
        RecSave(root->right, p);
}
        
void LoadProd(goods **root)
{
        int j = 0;
        int q = 0;
        int keep_on = 1;
        char choice;
        char file_name[20];
        goods *product;
        goods *search;
        goods *last;
        goods *lastp;
        goods **prev;

        FILE *k;

        ClrScr();
        printf("LOAD\n\n");
        printf("Open file: ");
        GetStr(file_name, 15);
        for(j = 0; j < 17; j++)
        {
                if(file_name[j] == 0)
                {
                        file_name[j] = '.';
                        file_name[j+1] = 't';
                        file_name[j+2] = 'x';
                        file_name[j+3] = 't';
                        file_name[j+4] = 0;
                        break;
                }
        }
        k = fopen(file_name, "r");
        if(k == NULL)
        {
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s can not be opened!", file_name);
                getch();
        }
        else
        {
                ClrScr();
                while(keep_on == 1)
                {
                        search = *root;
                        prev = root;
                        product = NULL;
                        product = malloc(sizeof(struct goods));
                        if(product != NULL)
                        {
                                if(fscanf(k, "%16s\t%d\t%f\t%d\n", product->product_name, &product->code, &product->price, &product->supply) == 4)
                                {
                                        product->left = NULL;
                                        product->right = NULL;
                                        keep_on = 1;

                                        for(q = 0; product->product_name[q] != 0; q++)
                                        {
                                                if(product->product_name[q] == '_')
                                                {
                                                        product->product_name[q] = ' ';
                                                }
                                        }
                                        
                                        //check if there are any duplicates
                                        while(search != NULL)
                                        {
                                                if(search->code == product->code)
                                                {
                                                        printf("-------------------------------------------------------------\n");
                                                        printf("Code %d already exist.\n", search->code);
                                                        printf("Current product: %s, %d, %.2f, %d\n", search->product_name, search->code, search->price, search->supply);
                                                        printf("Product from file (%s): %s, %d, %.2f, %d\n", file_name, product->product_name, product->code, product->price, product->supply);
                                                        printf("Replace current product?(Y/N)\n");
                                                        choice = getch();
                                                        //replace product with the new one
                                                        if(choice == 'Y' || choice == 'y')
                                                        {
                                                                //delete current product
                                                                //product has no right child
                                                                if(search->right == NULL )
                                                                {
                                                                        *prev = search->left;
                                                                        free(search);
                                                                        break;
                                                                }
                                                                //product has a right child but it's right child has no left child
                                                                else if(search->right->left == NULL)
                                                                {
                                                                        search->right->left = search->left;
                                                                        *prev = search->right;
                                                                        free(search);
                                                                        break;
                                                                }
                                                                //node has a right child and it's right child has a left child
                                                                else
                                                                {
                                                                        //swap deleting node with a smallest value from a right subtree
                                                                        last = search->right;
                                                                        while(last->left != NULL)
                                                                        {
                                                                                lastp = last;
                                                                                last = last->left;
                                                                        }
                                                                        lastp->left = last->right;
                                                                        last->left = search->left;
                                                                        last->right = search->right;
                                                                        *prev = last;
                                                                        free(search);
                                                                        break;
                                                                }
                                                        }
                                                        //do not replace current product
                                                        else
                                                        {
                                                                free(product);
                                                                goto next_prod;
                                                        }
                                                }
                                                else if(search->code < product->code)
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
                                        //insert current product
                                        prev = root;
                                        search = *root;
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
                                        keep_on = 0;
                                }
                        }
                        else
                        {
                                printf("Out of memory!");
                                getch();
                                goto out;
                        }
                        next_prod:;
                }
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s successfully loaded!", file_name);
                getch();
                out:;
                z = 0;
                fclose(k);
        }
        SetCursorType(NORMAL_CURSOR);
}

void CheckSave(const int save, goods **root)
{
        char option;
		COORD scrCoordinates = {0};

		scrCoordinates.X = 30;
		scrCoordinates.Y = 10;

        if(save == 0)
        {
                ClrScr();
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), scrCoordinates);
                printf("Save changes?(Y/N)");
                option = getch();
                if(option == 'Y' || option == 'y')
                {
                        SaveProd(&*root);
                }
        }
}