/***********************************
*
*       product.c
*
***********************************/

#include "product.h"

int count = 0;

void EnterProd(goods **root)
{
        int code = 0;
        char choice;
        char option;
        goods *product;
        goods *search;
        goods **prev;

        ClrScr();
        do
        {
                product = NULL;
                product = malloc(sizeof(struct goods));
                if(product != NULL)
				{
                        begin_input:;
                        search = *root;                    
                        SetCursorType(NORMAL_CURSOR);
                        ClrScr();
                        z = 0;
                        printf("ENTER PRODUCT\n\n");
                        printf("Product: ");
                        GetStr(product->product_name, 13);
                        printf("Code: ");
                        if(GetNum("%d" ,&code, 5) == NULL)
                        {
                                goto begin_input;
                        }
                        //check if code already exist
                        while(search != NULL)
                        {
                                if(search->code == code)
                                {
                                        printf("Code %d already exist.", code);
                                        getch();
                                        goto begin_input;
                                }
                                else if(search->code < code)
                                {
                                        search = search->right;
                                }
                                else if(search->code > code)
                                {
                                        search = search->left;
                                }
                        }
                        product->code = code;
                        printf("Price: ");
                        if(GetNum("%f" , &product->price, 4) == NULL)
                        {
                                goto begin_input;
                        }
                        printf("Supply: ");
                        if(GetNum("%d", &product->supply, 5) == NULL)
                        {
                                goto begin_input;
                        }
                        product->left = NULL;
                        product->right = NULL;

                        prev = root;
                        search = *root;
                        while(search != NULL)
                        {
                                if(search->code < code)
                                {
                                        prev = &search->right;
                                        search = search->right;
                                }
                                else if(search->code > code)
                                {
                                        prev = &search->left;
                                        search = search->left;
                                }
                        }
                        *prev = product;
                        
                        printf("\nEnter another product?(Y/N)");
                        option = getch();
                }
                else
                {
                        printf("Out of memory!");
                        getch();
                        option = 'n';
                }
        }while(option == 'Y' || option == 'y');
}

void DeleteProd(goods **root)
{
        int code;
        char option;
        goods *search;
        goods *last;
        goods *lastp;
        goods **prev;

        ClrScr();
        SetCursorType(NO_CURSOR);
        if(*root == NULL)
        {
                printf("No products to delete.");
				getch();
                goto out;
        }
        do
        {
                search = *root;
                prev = root;
                begin_input:;
                ClrScr();
                SetCursorType(NORMAL_CURSOR);
                printf("DELETE PRODUCT\n\n");
                printf("Code: ");
                if(GetNum("%d" , &code, 5) == NULL)
                {
                        goto begin_input;
                }
                while(search != NULL)
                {
                        if(search->code == code)
                        {
								z = 0;
                                //product has no right child
                                if(search->right == NULL )
                                {
                                        *prev = search->left;
                                        free(search);
                                        printf("Product has been deleted.\n");
                                        printf("Delete another product?(Y/N)");
                                        option = getch();
                                        break;
                                }
                                //product has a right child but it's right child has no left child
                                else if(search->right->left == NULL)
                                {
                                        search->right->left = search->left;
                                        *prev = search->right;
                                        free(search);
                                        printf("Product has been deleted.\n");
                                        printf("Delete another product?(Y/N)");
                                        option = getch();
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
                                        printf("Product has been deleted.\n");
                                        printf("Delete another product?(Y/N)");
                                        option = getch();
                                        break;
                                }
                        }
                        if(search->code < code)
                        {
                                prev = &search->right;
                                search = search->right;
                        }
                        else if(search->code > code)
                        {
                                prev = &search->left;
                                search = search->left;
                        }
                }
                if(search == NULL)
                {
                        printf("Code %d doesn't belong to any product.\n", code);
                        printf("Delete another product?(Y/N)");
                        option = getch();
                }
        }while(option == 'Y' || option == 'y');
        out:;
}

void FindProd(goods **root)
{
        int code;
        char option;
        goods *search;

        ClrScr();
        if(*root == NULL)
        {
                SetCursorType(NO_CURSOR);
                printf("No products to find.");
				getch();
                goto out;
        }
        do
        {
                begin_input:;
                ClrScr();
                SetCursorType(NORMAL_CURSOR);
                search = *root;
                printf("FIND PRODUCT\n\n");
                printf("Code: ");
                if(GetNum("%d" , &code, 5) == NULL)
                {
                        goto begin_input;
                }
                while(search != NULL)
                {
                        if(search->code == code)
                        {
                                printf("%s, %.2f €,  %d pieces.\n\n", search->product_name, search->price, search->supply);
                                printf("Find another product?(Y/N)");
                                option = getch();
                                break;
                        }
                        else if(search->code < code)
                        {
                                search = search->right;
                        }
                        else if(search->code > code)
                        {
                                search = search->left;
                        }
                        if(search == NULL)
                        {
                                printf("Code %d doesn't belong to any product.\n", code);
                                printf("Find another product?(Y/N)");
                                option = getch();
                                break;
                        }
                }
        }while(option == 'Y' || option == 'y');
        out:;
}

void SellProd(goods **root)
{
        int code;
        char option;
        goods *search;

        ClrScr();
        if(*root == NULL)
        {
                SetCursorType(NO_CURSOR);
                printf("No products to sell.");
				getch();
                goto out;
        }
        do
        {
                begin_input:;
                ClrScr();
                SetCursorType(NORMAL_CURSOR);
                search = *root;
                printf("SELL PRODUCT\n\n");
                printf("Code: ");
                if(GetNum("%d" , &code, 5) == NULL)
                {
                        goto begin_input;
                }
                while(search != NULL)
                {
                        if(search->code == code)
                        {
                                if(search->supply == 0)
                                {
                                        printf("This product is not available.\n\n");
                                        printf("Sell another product?(Y/N)");
                                        option = getch();
                                        break;
                                }
                                z = 0;
                                search->supply--;
                                printf("Product sold.\n");
                                printf("Supply: %d\n\n", search->supply);
                                printf("Sell another product?(Y/N)");
                                option = getch();
                                break;
                        }
                        else if(search->code < code)
                        {
                                search = search->right;
                        }
                        else if(search->code > code)
                        {
                                search = search->left;
                        }
                        if(search == NULL)
                        {
                                printf("Code %d doesn't belong to any product.\n", code);
                                printf("Sell another product?(Y/N)");
                                option = getch();
                                break;
                        }
                }
        }while(option == 'Y' || option == 'y');
        out:;
}

void DisplayProd(goods **root)
{
        int num_prod = 0;

        ClrScr();
        SetCursorType(NO_CURSOR);
		if(*root == NULL)
		{
				printf("No products to display.");
				getch();
				goto out;
		}
        printf("DISPLAY ALL PRODUCTS\n\n");
        printf("|       Product|  Code|     Price|       Supply|\n");
        printf("------------------------------------------------\n");
        //always initialize to zero
        count = 0;
        //print out products with help of recursion
        num_prod = RecDisplay(*root);
        printf("\nTotal number of products: %d", num_prod);
        out:;
        getch();
        SetCursorType(NORMAL_CURSOR);
}

int RecDisplay(goods *product)
{
        if(product == NULL)
        {
                return 0;
        }
        count++;
        RecDisplay(product->left);
        printf("| %13s| %5d| %7.2f €| %5d pieces|\n", product->product_name, product->code, product->price, product->supply);
        RecDisplay(product->right);
        return count;
}

int KeyPress(void)
{
        int key = getch();

        if(key == 0 || key == 224)
        {
                key = 256 + getch();
        }
        return key;
}

int Menu(void)
{
        int j = 0;
        int i = 0;
        int key;
        char shop[] = "                                 *** STORE 3 ***                                 ";
        char display[8][30] = {{"* Enter product"},
                               {"  Delete product"},
                               {"  Find product"},
                               {"  Sell product"},
                               {"  Display all products"},
                               {"  Load"},
                               {"  Save"},
                               {"  Exit"}};

        //display menu
        while(1)
        {  
                //necessary delay for 50 miliseconds
                Delay(50);
                ShowCursor(0);
                ClrScr();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
                SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
                printf("--------------------------------------------------------------------------------");
                //move text every 100 miliseconds
                if(j == 2)
                {
                        MoveStr(shop, shop[0]);
                        printf("%s", shop);
                        j = 0;
                }
                else
                {
                        printf("%s", shop);
                        j++;
                }
                printf("--------------------------------------------------------------------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
                printf("\n\n\n");
				puts(display[0]);
                puts(display[1]);
                puts(display[2]);
                puts(display[3]);
                puts(display[4]);
                puts(display[5]);
                puts(display[6]);
                puts(display[7]);
                if(kbhit())
                {
                        key = KeyPress();
                        //change star location - up
                        if(key == ARROW_UP)
                        {
                                for(i = 0; i < 8; i++)
                                {
                                        if(display[i][0] == '*')
                                        {
                                                if( i == 0)
                                                {
                                                        i = 7;
                                                        display[0][0] = ' ';
                                                        display[7][0] = '*';
                                                        break;
                                                }
                                                display[i][0] = ' ';
                                                display[i-1][0] = '*';
                                                i--;
                                                break;
                                        }
                                }
                        }
                        //change star location - down
                        else if(key == ARROW_DOWN)
                        {
                                for(i = 0; i < 8; i++)
                                {
                                        if(display[i][0] == '*')
                                        {
                                                if(i == 7)
                                                {
                                                        i = 0;
                                                        display[7][0] = ' ';
                                                        display[0][0] = '*';
                                                        break;
                                                }
                                                display[i][0] = ' ';
                                                display[i+1][0] = '*';
                                                i++;
                                                break;
                                        }
                                }
                        }
                        //return star location
                        else if(key == RETURN)
                        {
                                return i;
                        }
                }
        }
}

void ClrScr(void)
{
		//get the top left position
	    COORD scrCoordinates = {0};                        
	    //visible characters
	    DWORD charsLenght;
	    DWORD d;                      
	    CONSOLE_SCREEN_BUFFER_INFO buff;

	    //get a handle to the console
	    HANDLE scrHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	    GetConsoleScreenBufferInfo(scrHandle, &buff);

	    //get number of characters
	    charsLenght = buff.dwSize.X * buff.dwSize.Y;

	    //put whitespaces into the screen buffer
	    FillConsoleOutputCharacter(scrHandle, TEXT(' '), charsLenght, scrCoordinates, &d);
	    GetConsoleScreenBufferInfo(scrHandle, &buff);
	    FillConsoleOutputAttribute(scrHandle, buff.wAttributes, charsLenght, scrCoordinates, &d);

	    //put cursor back to the top left position
	    SetConsoleCursorPosition(scrHandle, scrCoordinates);
}

void SetCursorType(int cursor)
{
	CONSOLE_CURSOR_INFO cursorInfo = {0};

	//show cursor
	if(cursor)
	{
		cursorInfo.dwSize = 30;
		cursorInfo.bVisible = TRUE;
		SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &cursorInfo);		
	}
	//hide cursor
	else 
	{
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &cursorInfo);
	}
}