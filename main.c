#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<windows.h>

#define GREEN 2
#define BLUE 3
#define RED 12
#define WHITE 15
#define MAGENTA 13

void set_color(int color_code) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}


void sag(int realpoz, int sagpoz){
         if(realpoz == sagpoz)
            {
                set_color(GREEN);
                printf("---->");
            }
         else
            printf("     ");
}

int verif_numele(char n[])
{
    int nr=0, i;
 if(strlen(n)>20 || strlen(n)<3 || (n[0]<'a' && n[0]>'z'))
       return 0;
    else
        { for(i=1;i<strlen(n);i++)
            if(n[i]>='a' && n[i]<='z')
                 nr++;
          if(nr==strlen(n)-1)
            return 1;
          else
            return 0;
        }
}

int verificare_data(int ziua, int luna, int an)
{

    if(an >= 2022 && an<= 2025)
    {
        if(luna>=1 && luna<=12)
        {
            if((ziua>=1 && ziua<=31) && (luna==1 || luna==3 || luna==5 || luna==7 || luna==8 || luna==10 || luna==12))
                return 1;
            else if((ziua>=1 && ziua<=30) && (luna==4 || luna==6 || luna==9 || luna==11))
                return 1;
            else if((ziua>=1 && ziua<=28) && (luna==2))
                return 1;
            else if(ziua==29 && luna==2 && (an%400==0 ||(an%4==0 && an%100!=0)))
                return 1;
            else
                return 0;
        }
        else
            return 0;

    }
    else
       return 0;
}

int verif_ora(int ora)
{
    if (ora<8 || ora>=22)
        return 0;
    else return 1;
}
int id=1;
void rezerva_masa(){

    FILE * filePointer;
    filePointer = fopen("mese.txt", "a");
         char nume[50],prenume[50];
         int ziua,an,luna,ora,nr_pers;

set_color(RED);
         printf("--PENTRU A ADAUGA MASA--\n");
         set_color(BLUE);
         printf("Introduceti numele de familie:\n" );
         scanf("%s",nume);
          while (verif_numele(nume) == 0)
              {
               set_color(RED);
               printf("Nume invalid.Va rugam reincercati!\n");
               set_color(BLUE);
               scanf("%s", nume);
               }
           printf("Introduceti prenumele:\n" );
           scanf("%s",prenume);
          while (verif_numele(prenume) == 0)
              {
               set_color(RED);
               printf("Prenume invalid.Va rugam reincercati!\n");
               set_color(BLUE);
               scanf("%s",prenume);
               }

        printf("Introduceti numarul de persoane:\n" );
        scanf("%d",&nr_pers);
        while(nr_pers > 10)
        {
             set_color(RED);
             printf("Nu este permis un numar mai mare de 10 persoane la o masa\n");
             set_color(BLUE);
             scanf("%d",&nr_pers);
        }

        printf("Introduceti data(ZZ/LL/AAAA):\n" );
        printf("Ziua: ");
        scanf("%d",&ziua);
        printf("Luna: ");
        scanf("%d",&luna);
        printf("Anul: ");
        scanf("%d",&an);
        while (verificare_data( ziua, luna, an) == 0)
        {
                set_color(RED);
                printf("Nu ati introdus o data valida. Va rugam reincercati!\n");
                set_color(BLUE);
                printf("Ziua: ");
                scanf("%d",&ziua);
                printf("Luna: ");
                scanf("%d",&luna);
                printf("Anul: ");
                scanf("%d",&an);
        }
        printf("Programul restaurantului este de la ora 8 la 22, va rugam alegeti o ora in acest interval \n");
        printf("Introduceti ora:\n");
        scanf("%d",&ora);
        while ( verif_ora(ora) == 0)
        {
              set_color(RED);
              printf("Ora invalida,va rugam incercati din nou\n");
              set_color(BLUE);
              scanf("%d",&ora);
        }
         printf("Rezervarea a fost facuta\n");

    if (filePointer == NULL )
    {
        printf( "Fisierul nu poate fi accesat." ) ;
    }
    else
    {
        fprintf(filePointer, "%s %s : %d/%d/%d ,ora: %d\n",nume,prenume,ziua,luna,an,ora);
        fclose(filePointer) ;
    }
    printf("ID-ul mesei este:%d \n", id);
    printf("Persoana %s a fost adaugata in fisier\n", nume);
    id++;

}
void mese_rezervate(){

    FILE * filePointer;
    filePointer = fopen("mese.txt", "r");

    printf("Rezervari:\n");

    if ( filePointer == NULL )
    {
        printf( "Fisierul nu poate fi accesat." ) ;
    }
    else
    {
        char c = fgetc(filePointer);
        while (c!= EOF)
        {
            printf ("%c", c);
            c = fgetc(filePointer);
        }

        fclose(filePointer);
    }

}
void anuleaza_rezervarea()
{
    FILE *fptr1, *fptr2;
    fptr1 = fopen("mese.txt","r");
    fptr2 = fopen("temp.txt", "w");
    char x;
    int del, line_nr = 0;
    set_color(MAGENTA);
    printf("Va rugam introduceti id-ul mesei rezervate: ");
    scanf("%d", &del);

    x = getc(fptr1);
    if(x!=EOF) {
            line_nr =1;
               }
    while(1){
      if(del != line_nr)
        putc(x, fptr2);
        x = getc(fptr1);
        if(x =='\n') line_nr++;
        if(x == EOF) break;
          }
    fclose(fptr1);
    fclose(fptr2);
    remove("mese.txt");
    rename("temp.txt", "mese.txt");

    printf("Rezervarea a fost anulata!\n");
}

void submenu()
{
    system("cls");
    int pozitie = 1;
    int keyPressed = 0;
    while(keyPressed!=13)
  {
         system("cls");
    set_color(GREEN);
    printf("     -MENU-\n\n");
    sag(1,pozitie); printf("|| REZERVA MASA\n");
    sag(2,pozitie); printf("|| VIZUALIZATI TOATE MESELE REZERVATE\n");
    sag(3,pozitie); printf("|| ANULEAZA REZERVAREA\n");
   keyPressed = getch();

    if(keyPressed == 80 && pozitie != 3)
    {
            pozitie++;
       }else if(keyPressed == 72 && pozitie != 1){
            pozitie--;
       }else
       {
           pozitie=pozitie;
       }

    }
}

void back(){
    int keyPressed;
    printf("Back\n");
   if(keyPressed == 8)
           submenu() ;
   else
    if(keyPressed == 13)
        printf("EXIT!\n");

}


void menu()
{
    system("cls");
    int pozitie = 1;
    int keyPressed = 0;
    while(keyPressed!=13){
         system("cls");
    set_color(GREEN);
    printf("     -MENU-\n\n");
    sag(1,pozitie); printf("|| REZERVA MASA\n");
    sag(2,pozitie); printf("|| VIZUALIZATI TOATE MESELE REZERVATE\n");
    sag(3,pozitie); printf("|| ANULEAZA REZERVAREA\n");
   keyPressed = getch();

    if(keyPressed == 80 && pozitie != 3)
    {
            pozitie++;
       }else if(keyPressed == 72 && pozitie != 1){
            pozitie--;
       }else
       {
           pozitie=pozitie;
       }

    }

system("cls");
    if(pozitie == 1 && keyPressed==13)
    {
           rezerva_masa();
           back();
    }

    if(pozitie == 2 && keyPressed==13)
    {
        mese_rezervate();
        back();
    }

    if(pozitie == 3 && keyPressed==13)
    {
       anuleaza_rezervarea();
       back();

    }

}

int main()
{
    menu();
    return 0;
}