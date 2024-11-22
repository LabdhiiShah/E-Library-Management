#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BOOK_FILE "library_books.txt"
#define ISSUED_BOOKS_FILE "issued_books.txt"

void addbk();
void displaybk();
int searchbk();
void issuebk();
void issuerlist();
void exitProgram();

struct books
{
    int id;
    char title[100];
    char aut[100];

};

struct issueDetails
{
    int id;
    char dateOfip[100];
    char dateOfop[100];

};

int main()
{
    struct books b;
    int ch;
    while(1)
    {
        printf("\n---Library Management---\n");
        printf("1.Add Book\n");
        printf("2.Available Books List\n");
        printf("3.Search Book\n");
        printf("4.Issue Book\n");
        printf("5.Issued Book List\n");
        printf("6.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
        case 1:
            addbk();
            break;

        case 2:
            displaybk();
            break;

        case 3:
            searchbk();
            break;

        case 4:
            issuebk();
            break;

        case 5:
            issuerlist();
            break;

        case 6:
             exitProgram();
             break;

        default: printf("Invalid Choice!");
        }
    }
}

void addbk()
{
    struct books b;
    printf("---Adding Book---\n");
    printf("Enter Book ID: ");
    scanf("%d",&b.id);

    printf("Enter Book Name: ");
    scanf(" %[^\n]",b.title);

    printf("Enter Author Name: ");
    scanf(" %[^\n]",b.aut);

    FILE *fp = fopen(BOOK_FILE, "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(fp,"%d, %s, %s\n",b.id,b.title,b.aut);
    fclose(fp);

    printf("Book added successfully.\n");
}

void displaybk()
{
    struct books b;
    FILE *fp = fopen(BOOK_FILE, "r");
    if (fp == NULL) {
        printf("No books available or error opening file.\n");
        return;
    }
    printf("\n---Available Books---\n\n");
    printf("%-10s  %-20s %-30s\n\n","Book id" , "Book Name" , "Author Name");

  while (fscanf(fp, "%d, %49[^,], %49[^\n]\n",&b.id, b.title, b.aut) == 3) {
        printf("%-10d  %-20s  %-30s\n", b.id, b.title, b.aut);
    }

    fclose(fp);
}

int searchbk()
{
   char n[100];
   int bookFound = 0;
    struct books b;
    printf("\n---Searching a Book---\n");
    printf("\nEnter the Title or Author of the Book: ");
    scanf("%s", n);
    printf("You searched for: %s\n", n);

    FILE *fp = fopen(BOOK_FILE, "r");
    if (fp == NULL) {
        printf("No books available or error opening file.\n");
        return;
    }
     printf("%-10s  %-20s %-30s","Book id" , "Book Name" , "Author Name");
     while (fscanf(fp, "\n %d, %[^,], %[^\n]\n", &b.id, b.title, b.aut) == 3) {
        if (strcmp(b.title, n) == 0 || strcmp(b.aut, n) == 0) {
            printf("\n%-10d  %-20s  %-30s\n", b.id, b.title, b.aut);
            bookFound = 1;
            fclose(fp);
            return b.id;
        }
    }
    return 0;
}

void issuebk()
{
    int available = searchbk();
    struct issueDetails i;
    if(available)
     {
        FILE *fp = fopen(ISSUED_BOOKS_FILE,"r");
        if (fp == NULL) {
        printf("Error opening file.\n");
        }
        printf("\n---Issuing a Book---\n");
        while (fscanf(fp, "%d ,%49[^,] , %49[^\n]\n", &i.id, i.dateOfip, i.dateOfop) == 3) {
            if (available == i.id) {
                if (strcmp(i.dateOfop, "N/A") == 0) {
                    printf("\nCurrently unavailable\n");
                }else{
                    printf("\nAvailable to issue\n");
                }
            }
        }
        fclose(fp);
     }
     else
     {
         printf("Book is not available in the library");
     }
}

void issuerlist(){
        struct issueDetails i;
       FILE *fp = fopen(ISSUED_BOOKS_FILE,"r");
       if (fp == NULL) {
            printf("Error opening file.\n");
        }
        printf("\n---Issuer List---\n");
        while (fscanf(fp, "%d , %49[^,] , %49[^\n]\n", &i.id, i.dateOfip, i.dateOfop) == 3) {
            if (!(strcmp(i.dateOfip, "N/A") == 0)) {
                printf("%d , %s , %s\n", i.id, i.dateOfip, i.dateOfop);
            }
        }
        fclose(fp);
}

void exitProgram()
{
    printf("Exiting the Code!!!");
    exit(0);
}
