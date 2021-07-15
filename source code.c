#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> 
#include <string.h>


COORD coord = {0,0};

void gotoxy(int x,int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main(){
    FILE *fp, *ft; 
    char another, choice;
    
    struct emp{
        char name[40]; 
        int age; 
        float bs; 
    };

    struct emp e; //structure variable creation

    char empname[40]; 

    long int recsize; 

    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL){
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL){
            printf("Cannot open file");
            exit(1);
        }
    }

    recsize = sizeof(e);

 
    while(1)
    {
        system("cls"); 
        gotoxy(30,10); 
        printf("1. Add"); 
        gotoxy(30,12);
        printf("2. List"); 
        gotoxy(30,14);
        printf("3. Modify"); 
        gotoxy(30,16);
        printf("4. Delete"); 
        gotoxy(30,18);
        printf("5. Exit"); 
        gotoxy(30,20);
        printf("Choice: "); // enter the choice 1, 2, 3, 4, 5
        fflush(stdin); 
        choice  = getche(); // get the input from keyboard
        switch(choice)
        {
        case '1':  
            system("cls");
            fseek(fp,0,SEEK_END); 

            another = 'y';
            while(another == 'y')  
            {
                printf("\nname: ");
                scanf("%s",e.name);
                printf("\nage: ");
                scanf("%d", &e.age);
                printf("\nsalary: ");
                scanf("%f", &e.bs);

                fwrite(&e,recsize,1,fp);

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':
            system("cls");
            rewind(fp); 
            while(fread(&e,recsize,1,fp)==1)  
            {
                printf("\n%s %d %.2f",e.name,e.age,e.bs); 
            }
            getch();
            break;

        case '3':  
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Employee name to modify: ");
                scanf("%s", empname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1) 
                {
                    if(strcmp(e.name,empname) == 0)  
                    {
                        printf("\nEnter new name,age and salary: ");
                        scanf("%s%d%f",e.name,&e.age,&e.bs);
                        fseek(fp,-recsize,SEEK_CUR); 
                        fwrite(&e,recsize,1,fp); 
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nName of employee to be deleted: ");
                scanf("%s",empname);
                ft = fopen("Temp.dat","wb");  // temporary storage
                rewind(fp); 
                while(fread(&e,recsize,1,fp) == 1)  
                {
                    if(strcmp(e.name,empname) != 0)  
                    {
                        fwrite(&e,recsize,1,ft); 
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); 
                rename("Temp.dat","EMP.DAT"); 
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '5':
            fclose(fp);  
            exit(0); 
        }
    }
    return 0;
}
