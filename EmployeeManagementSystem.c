#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
 // template for employee record
struct employee
{
    int empid;
    char name[30];
    float salary;
};
typedef struct employee record;
 // Global Variables
record emp;
FILE *fp = NULL;
 // Function prototypes
 void printLogo(void);
int passWord(char *);
void addRec(void);
void displayAll(void);
int countRec(void);
void searchById(void);
void searchByName(void);
void deleteRec(void);
void updateRec(void);
int main()
{
    char choice, ch;
    printLogo();
    int wrn = 0;
    // Checking password
    printf("\t\t\tEnter Password: ");
    while (1)
    {
        if (passWord("123abc") == 0)
        {
            system("cls");
            wrn++;
            if (wrn == 3)
            {
                system("cls");
                printLogo();printf("\n\t\t\t    Wrong ");
            printf("\n\t\t\tRe-enter password ");
        }
        else
        {
            break;
        }
    }
 while (1)
    {
        system("cls");
        printLogo();
        printf("\t\t\tAvailable Choices are:\n");
printf("\t\t\t1. Add a New Record in Database.\n");
printf("\t\t\t2. Display All Record(s).\n");
printf("\t\t\t3. Count Total Record(s).\n");
printf("\t\t\t4. Search a Record.\n");
printf("\t\t\t5. Delete a Record.\n");
printf("\t\t\t6. Update a Record.\n");
printf("\t\t\t8. Exit.\n\n");
printf("\t\t\tSelect a choice: ");
scanf("%d", &choice);
  switch (choice)
        {
        case 1:
            system("cls");
            printLogo();
            addRec();
            getch();
            break;
          case 2:
            system("cls");
            printLogo();
            displayAll();
            getch();
            break;
            case 3:
            system("cls");
            printLogo();
            printf("\t\t\tTotal Record(s): %d\n", countRec());
            printf("\n\t\t\t");
            getch();
    break;
  case 4:
            system("cls");
            printLogo();
            printf("\t\t\tSelect a Choice:\n");
            printf("\t\t\t1. Search By ID.\n");
            printf("\t\t\t2. Search By Name.\n\n");
            printf("\t\t\tEnter choice: ");
            scanf("%d", &ch);
            switch (ch)
            {
            case 1:
                system("cls");
                printLogo();
                searchById();
                getch();
                break;
       case 2:
                system("cls");
                printLogo();
                searchByName();
                getch();
                break;
      default:
                printf("\t\t\tWrong Choice.");
                getch();
            } // End of inner switch
            getch();
            break;
     case 5:
            system("cls");
            printLogo();
            deleteRec();
            getch();
            break;
      case 6:
            system("cls");
            printLogo();
            updateRec();
            getch();
            break;
  case 8:
            system("cls");
            printLogo();
            printf("\t\t\tThank you for visit us.");
            getch();
            system("cls");
            exit(0);
 
        default:
            printf("\t\t\tThis choice is NOT available.");
            getch();
 } // end of the switch
    }     // end of while
    return 0;
}
// Function definitions
void printLogo(void)
{
    system("cls");
    printf("\n\t\t\t   EMPLOYEE MANAGEMENT SYSTEM\n");
    printf("\n\t\t----------------------------------------------------\n"); int passWord(char *p)
{
    char ch;
    int i, flag = 1;
    for (i = 0; i < strlen(p); i++)
    {
        ch = getch();
        putchar('*');
        if (ch != p[i])
        {
            flag = 0;
        }
    }
    return flag;
}
 void addRec(void)
{
    fp = fopen("database.bin", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tFile Opening Error....");
        return;
    }
    fflush(stdin);
    printf("\t\t\tEnter Employee Name   : ");
    fgets(emp.name, 29, stdin);
    printf("\t\t\tEnter Employee ID     :");
    scanf("%d", &emp.empid);
    printf("\t\t\tEnter Employee Salary :");
    scanf("%f", &emp.salary);
    fwrite(&emp, sizeof(emp), 1, fp);
    fclose(fp);
    printLogo();
    printf("\t\t\tRecord is Added Successfully.");
}
void displayAll(void)
{
    fp = fopen("database.bin", "rb");
    if (fp == NULL)
    {
        printf("\t\t\tFile Opening Error....");
        return;
    }
    printf("\n\n\t\tRecord(s) in Database:\n\n");
    printf("%25s |%20s |%17s\n", "Emp ID", "Name", "Salary");
    printf("%27s%22s%19s", "----------|", "--------------------|", "------------------");
    while (fread(&emp, sizeof(emp), 1, fp) == 1)
    {
        printf("\n%25d |", emp.empid);
        printf("%20.*s |", strlen(emp.name) - 1, emp.name);
        printf("%17.2f", emp.salary);
       // printf("\n\t\t\tNAME  : %s",emp.name);
        // printf("\t\t\tID    : %d\n",emp.empid);
        // printf("\t\t\tSalary: %.2f",emp.salary);
    }
 printf("\n%27s%22s%19s", "___|", "______|", "_______");
    fclose(fp);
}
 int countRec(void)
{
    int count = 0;
    fp = fopen("database.bin", "rb");
    fseek(fp, 0, 2);
    count = ftell(fp) / sizeof(emp);
     // if(fp == NULL)
    // {
    //     printf("\t\t\tFile Opening Error....");
    //     return;
    // }
    // while ( fread(&emp, sizeof(emp),1, fp) == 1)
    // {
    //     count++;
    // }
   fclose(fp);
    return count;
}
void searchById(void)
{
    int id;
    printf("\t\t\tEnter employee id: ");
    scanf("%d", &id);
    system("cls");
     printLogo();
  fp = fopen("database.bin", "rb");
    if (fp == NULL)
    {
        printf("\t\t\tFile Opening Error....");
        return;
    }
    while (fread(&emp, sizeof(emp), 1, fp) == 1)
    {
        if (id == emp.empid)   {
            printf("\n\t\t\tNAME  : %s", emp.name);
            printf("\t\t\tID    : %d\n", emp.empid);
            printf("\t\t\tSalary: %.2f", emp.salary);
            fclose(fp);
            return;
        }
    }
    printf("\t\t\tThis record does not exist.");
    fclose(fp);
}
 void searchByName(void)
{
    char name[30];
    fflush(stdin);
    printf("\t\t\tEnter employee Name: ");
    fgets(name, 29, stdin);
    system("cls");
    printLogo();
    fp = fopen("database.bin", "rb");
    if (fp == NULL)
    {
        printf("\t\t\tFile Opening Error....");
        return;
    } while (fread(&emp, sizeof(emp), 1, fp) == 1)
    {
        if (strcmp(name, emp.name) == 0)
        {
            printf("\n\t\t\tNAME  : %s", emp.name);
            printf("\t\t\tID    : %d\n", emp.empid);
            printf("\t\t\tSalary: %.2f", emp.salary);
            fclose(fp);
            return;
        }
    }
    printf("\t\t\tThis record does not exist.");
    fclose(fp);
}
 void deleteRec(void)
{
    int id;
    int flag = 0;
    char YN;
    FILE *tempf = fopen("temp.bin", "wb+");
    fp = fopen("database.bin", "rb");
    if (tempf == NULL || fp == NULL)
    {
        printf("\t\t\tFile Opening Error....");
        return;
    }
    printf("\t\t\tEnter employee id: ");
    scanf("%d", &id);
    printf("\t\t\tDo you want to permanently delete this file?  (y/n)  ");
    fflush(stdin);
    scanf("%c", &YN);
    YN = toupper(YN);
    if (YN == 'Y')
    {
        while ((fread(&emp, sizeof(emp), 1, fp)) == 1)
        {
            if (emp.empid == id)
            {
                flag = 1;
                continue;
            }
            fwrite(&emp, sizeof(emp), 1, tempf);
        }
        fclose(fp);
        fclose(tempf);
        system("cls");
        printLogo();
        //_fcloseall();
        if (flag == 1)
        {
            remove("database.bin");
            rename("temp.bin", "database.bin");
            printf("\t\t\tRecord is deleted:");
        }
        else
        {
            printf("\t\t\tRecord does not exist.");
            remove("temp.bin");
        }
    }
    else
    {
        printf("\nFile Delition Ternimated.\n");
        fclose(fp);
        return;
    }
}
 void updateRec(void)
{
    int id;
    int flag = 0;
    FILE *tempf = fopen("temp.bin", "wb+");
    fp = fopen("database.bin", "rb");
    if (tempf == NULL || fp == NULL)
    {
        printf("\t\t\tFile Opening Error....");
        return;
    }
    printf("\t\t\tEnter employee id: ");
    scanf("%d", &id);
    while ((fread(&emp, sizeof(emp), 1, fp)) == 1)
    {
        if (emp.empid == id)
        {
            flag = 1;
            printf("\t\t\tEnter updated empid : ");
            scanf("%d", &emp.empid);
            printf("\t\t\tEnter updated name  : ");
            fflush(stdin);
            fgets(emp.name, 29, stdin);
            printf("\t\t\tEnter updated Salary:");
            scanf("%f", &emp.salary);
            fwrite(&emp, sizeof(emp), 1, tempf);
            continue;
        }
        fwrite(&emp, sizeof(emp), 1, tempf);
    }
    fclose(fp);
    fclose(tempf);
    system("cls");
    printLogo();
    //_fcloseall();
    if (flag == 1)
    {
        remove("database.bin");
        rename("temp.bin", "database.bin");
        printf("\t\t\tRecord is Updated:");
    }
    else
    {
        printf("\t\t\tRecord does not exist.");
        remove("temp.bin");
    }
} 
