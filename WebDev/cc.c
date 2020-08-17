#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "AticleworldLibBookS.bin"
// Macro related to the books info
#define MAX_BOOK_NAME   50
#define MAX_AUTHOR_NAME 50
#define MAX_STUDENT_NAME 50
#define MAX_STUDENT_ADDRESS 300
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
//structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;
typedef struct// to call in program
{
    unsigned int books_id; // declare the integer data type
    char bookName[MAX_BOOK_NAME];// declare the character data type
    char authorName[MAX_AUTHOR_NAME];// declare the charecter data type
    char studentName[MAX_STUDENT_NAME];// declare the character data type
    char studentAddr[MAX_STUDENT_ADDRESS];// declare the character data type
    Date bookIssueDate;// declare the integer data type
    int priceBuy;//price of buying the book
    int priceRent;//price of renting the book for a month	
} s_BooksInfo;
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############             A C LANGUAGE MINI PROJECT             ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
void welcomeMessage()
{
    headMessage("E - LIBB SYSTEM");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =              E-LIBB SYSTEM                =");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t        =       AN LIBRARY MANAGEMENT PROGRAM       =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}

int first_menu()
{	
	int i;
	int ch;
	ch = 0;
	do
	{
		headMessage("LOGIN:");
		printf("\n\t\t\t                          1. ADMIN");
		printf("\n\t\t\t                          2. USER");
		printf("\n\t\t\t                          3. Exit\n");
		scanf("%d", &i);
		if (i >= 1 && i <= 3)
		{
			ch = 1;
		}
		else
		{
			printf("\n\n\t\t\t                          Please Re-enter:");
		}
	}while(ch == 0);
	return i;
}

int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
// Add books in list
void addBookInDataBase()
{
    int days;
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW BOOKS");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tBook ID NO  = ");
    fflush(stdin);
    scanf("%u",&addBookInfoInDataBase.books_id);
    do
    {
        printf("\n\t\t\tBook Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.bookName,MAX_BOOK_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.bookName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tAuthor Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.authorName,MAX_AUTHOR_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.authorName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tStudent Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.studentName,MAX_STUDENT_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.studentName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&addBookInfoInDataBase.bookIssueDate.dd,&addBookInfoInDataBase.bookIssueDate.mm,&addBookInfoInDataBase.bookIssueDate.yyyy);
        //check date validity
        status = isValidDate(&addBookInfoInDataBase.bookIssueDate);
	  printf("\n\t\t\tEnter price for renting the book for a month: ");

	  scanf("%d", &addBookInfoInDataBase.priceRent);
 	  printf("\n\t\t\tEnter price for buying the book: ");
	  scanf("%d", &addBookInfoInDataBase.priceBuy);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, fp);
    fclose(fp);
}
// search books
void searchBooks()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH BOOKS");
    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Book Name to search:");
    fflush(stdin);
    fgets(bookName,MAX_BOOK_NAME,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(!strcmp(addBookInfoInDataBase.bookName, bookName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tBook id = %u\n",addBookInfoInDataBase.books_id);
        printf("\t\t\tBook name = %s",addBookInfoInDataBase.bookName);
        printf("\t\t\tBook authorName = %s",addBookInfoInDataBase.authorName);
        printf("\t\t\tBook issue date(day/month/year) =  (%d/%d/%d)",addBookInfoInDataBase.bookIssueDate.dd,
               addBookInfoInDataBase.bookIssueDate.mm, addBookInfoInDataBase.bookIssueDate.yyyy);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}
// v books function
void viewBooks()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int countBook = 1;
    headMessage("VIEW BOOKS DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        printf("\n\t\t\tBook Count = %d\n\n",countBook);
        printf("\t\t\tBook id = %u",addBookInfoInDataBase.books_id);
        printf("\n\t\t\tBook name = %s",addBookInfoInDataBase.bookName);
        printf("\t\t\tBook authorName = %s",addBookInfoInDataBase.authorName);
        printf("\t\t\tBook issue date(day/month/year) =  (%d/%d/%d)\n\n",addBookInfoInDataBase.bookIssueDate.dd,
               addBookInfoInDataBase.bookIssueDate.mm, addBookInfoInDataBase.bookIssueDate.yyyy);
        found = 1;
        ++countBook;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
// delete function
void deleteBooks()
{
    int found = 0;
    int bookDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    headMessage("Delete Books Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tEnter Book ID NO. for delete:");
    scanf("%d",&bookDelete);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(addBookInfoInDataBase.books_id != bookDelete)
        {
            fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}
void updateCredential(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\ttLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}
void menu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Add Books");
        printf("\n\t\t\t2.Search Books");
        printf("\n\t\t\t3.View Books");
        printf("\n\t\t\t4.Delete Book");
        printf("\n\t\t\t5.Update Password");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addBookInDataBase();
            break;
        case 2:
            searchBooks();
            break;
        case 3:
            viewBooks();
            break;
        case 4:
            deleteBooks();
            break;
        case 5:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}

void rentBooks()
{
	int flag = 0;
	int flag2 = 0;
	int amt = 0;
	do
	{
		int found = 0;
    		char bookName[MAX_BOOK_NAME] = {0};
    	s_BooksInfo Book = {0};
    	FILE *fp = NULL;
    	int status = 0;
    	fp = fopen(FILE_NAME,"rb");
    	if(fp == NULL)
    	{
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    	}
    	headMessage("SEARCH BOOKS TO RENT");
    	//put the control on books detail
    	if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    	{
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    	}
    		printf("\n\n\t\t\tEnter Book Name to search:");
    		fflush(stdin);
    		fgets(bookName,MAX_BOOK_NAME,stdin);
    		while (fread (&book, sizeof(book), 1, fp))
    		{
        		if(!strcmp(Book.bookName, bookName))
        		{
            		found = 1;
            		break;
        		}
   		}
    		if(found)
    		{
	   		printf("REQUIRED BOOK");
        		printf("Book ID : %u\n",Book.books_id);
        		printf("Book name : %s\n",addBookInfoInDataBase.bookName);
        		printf("AuthorName : %s\n",Book.authorName);
        		printf("Book issue date(day/month/year) =  (%d/%d/%d)\n",Book.bookIssueDate.dd,
               Book.bookIssueDate.mm, Book.bookIssueDate.yyyy);
			amt = amt + Book.priceRent;
			printBill(1,flag2,amt,Book);
			flag2 = 1;
    		}
    		else
    		{
        		printf("\n\t\t\tNo Record");
    		}
		printf("Do you want to rent another book(y/n)?");
		char ch;
		scanf("%c",&ch);
		if(ch == 'n' || ch == 'N')  
			flag = 1;
		fclose(fp);
	}while(flag==0);
	flag2 = 2;
	printBil(1,flag2,amt,Book);

}

void buyBooks()
{
	int flag = 0;
	int flag2 = 0;
	int amt = 0;
	do
	{
		int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo Book = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH BOOKS TO BUY");
    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Book Name to search:");
    fflush(stdin);
    fgets(bookName,MAX_BOOK_NAME,stdin);
    while (fread (&book, sizeof(book), 1, fp))
    {
        if(!strcmp(Book.bookName, bookName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
	   printf("REQUIRED BOOK");
        printf("Book ID : %u\n",Book.books_id);
        printf("Book name : %s\n",addBookInfoInDataBase.bookName);
        printf("AuthorName : %s\n",Book.authorName);
        printf("Book issue date(day/month/year) =  (%d/%d/%d)\n",Book.bookIssueDate.dd,
               Book.bookIssueDate.mm, Book.bookIssueDate.yyyy);
	   amt = amt + Book.priceBuy;
	   printBill(2,flag2,amt,Book);
	   flag2 = 1;

    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
	printf("Do you want to buy another book(y/n)?");
	char ch;
	scanf("%c",&ch);
	if(ch == 'n' || ch == 'N')
		flag = 1;
	}while(flag==0);
	flag2 = 2;
	printBill(2,flag2,Book);
}

void printBill(int option, int flag, int amt, s_BooksInfo Books)
{
	if(flag == 0)
	{
		printf("\n\nStudent ID: %u",studentName);
		printf("\nStudent Address: %u",studentAddr);
		printf("\n\nBook Name\t\tAuthor's Name\t\tPrice");
		printf("\n\t\t-----------\t\t\n");
	}
	if(flag == 1)
	{
		printf("\n%s\t\t%s\t\t",Books.bookName,Books.authorName);
		if(option == 1)
			printf("%d",Books.priceRent);
		else
			printf("%d",Books.priceBuy);
	}
	if(flag == 2)
	{
		printf("\n\nFinal amount to be paid: %d",amt);
	}
}
void menuUser()
{
	int choice = 0;
     do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Rent Books");
        printf("\n\t\t\t2.Buy Books");
        printf("\n\t\t\t3.Save Books Offline");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            rentBooks();
            break;
        case 2:
            buyBooks();
            break;
        case 3:
            saveBooks();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //SwitchEnded
    }
    while(choice!=0);                                        
}
//login password
void Admin_login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}

void user_init()
{
	FILE *fp = NULL;
    int status = 0, L = 0;
    headMessage("USER SIGNUP");
    unsigned char username[MAX_SIZE_USER_NAME] = {0};
    unsigned char password1[MAX_SIZE_PASSWORD] = {0};
    unsigned char password2[MAX_SIZE_PASSWORD] = {0};
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(username,MAX_SIZE_USER_NAME,stdin);
        fgets(username,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password1,MAX_SIZE_PASSWORD,stdin);
        printf("\n\t\t\t\tRe-enter Password:");
        fgets(password2,MAX_SIZE_PASSWORD,stdin);
        if(!strcmp(password1,password2))
        {
            sFileHeader fileHeaderInfo = {0};
		    status = isFileExists(FILE_NAME);
		    //create the binary file
	        fp = fopen(FILE_NAME,"wb");
	        if(fp != NULL)
	        {
	            // password
		        strncpy(fileHeaderInfo.password,password1,sizeof(password1));
	            strncpy(fileHeaderInfo.username,username,sizeof(username));
	            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
		        fclose(fp);
		        menuUser();
	        }
        }
        else
        {
        	headMessage("USER SIGNUP");
            printf("\t\t\t\tSignup Failed Enter Same Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Signup Failed");
        getch();
        system("cls");
    }
}

void user_login()
{
	
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    char c;
    scanf("%c", &c);
    int L=0, i=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    do
    {
    	headMessage("LOGIN");
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        fseek(fp, 0, SEEK_SET);
        i = 0;
        while ((c=fgetc(fp))!=EOF)
		{        	
			fseek(fp, i*sizeof(sFileHeader), SEEK_SET);
			fread(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
			if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
	        {
	            menuUser();
	        }
	        i++;	        
		}
        printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
        L++;
    }while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        fclose(fp);
        getch();
        system("cls");
    }
}

void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="12345\n";
    const char defaultPassword[] ="12345\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}
int main()
{
    welcomeMessage();
    int opt = first_menu();
    init();
    if (opt == 1)
    	Admin_login();
    else if (opt == 2)
    {
    	int n, i;
    	n = 0;
    	do
    	{
	    	headMessage("User");
	    	printf("\n\t\t\t1. LOGIN");
	    	printf("\n\t\t\t2. SIGNUP");
	    	printf("\n\t\t\t3. EXIT\n");
	    	scanf("%d", &i);
	    	if (i > 0 && i < 4)
	    	{
	    		n = 1;
	    	}
	    	else
	    	{
	    		printf("\n\t\t\tRE-ENTER THE RIGHT OPTION");	
			}
	    }while(n == 0);
	    if (i == 1)
	    {
	    	user_login();
		}
		else if (i == 2)
		{
			user_init();
		}
	}
    	
    return 0;
}
