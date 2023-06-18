/******************************************************************************************************************
Napisati program koji iz datoteke čita podatke o broju bodova koje je jedan student dobio na ispitu 
(struct _student{char ime[128];char prezime[128];int  broj_bodova; int relativni_broj_bodova;struct _student *left;
;struct _student *right;}) i sprema ih u binarno stablo pretraživanja. (Napomena : 0 < broj_bodova <= 100).
Ispisati binarno stablo na „inorder“ način.

U tako kreiranom binarnom stablu potrebno je za svakog od studenata izračunati i relativan broj bodova po formuli: 
relativan_broj_bodova=( broj_bodova / MAX(broj_bodova) ). Ispisati binarno stablo na „preorder“ način. 
********************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024

typedef struct student *stablo;
struct student
{
  char ime[128];
  char prezime[128];
  int broj_bodova;
  float rel_br_bodova;

  stablo l;
  stablo d;   
};

stablo citaj_iz_datoteke(stablo);
stablo dodaj(stablo, char *, char *, int);
int Inorder(stablo);
int Preorder(stablo);


int main(void)
{
    
    stablo root = NULL;
    
    printf("Citanje iz  datoteke:\n");
    root = citaj_iz_datoteke(root);
    
    printf("Inorder ispis:\n");
    Inorder(root);
    
    printf("\nPreorder ispis:\n");
    Preorder(root);
    
    return 0;
}
stablo citaj_iz_datoteke(stablo s)
{
    FILE *fp = NULL;
    char *fileName = NULL;
    char niz1[128], niz2[128];
    int x;
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija neuspjesna!\n");
        return NULL;
    }
    
    printf("Ukucajte datoteku za citanje: ");
    scanf(" %s", fileName);
    
    if(strchr(fileName, '.') == 0)
    {
        strcat(fileName, ".txt");
    }
    
    fp = fopen(fileName, "r");
    if(fp == NULL)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return NULL;
    }
    
    while(!feof(fp))
    {
        fscanf(fp, "%s %s %d", niz1, niz2, &x);
        s = dodaj(s, niz1, niz2, x);
    }
    
    
    fclose(fp);
    return s;
}

stablo dodaj(stablo s, char *niz1, char *niz2, int n)
{
    
    if(NULL == s)
    {
        s = (stablo)malloc(sizeof(struct student));
        if(s == NULL)
        {
            printf("Alokacija neuspjesna\n");
            
        }
        
        strcpy(s->ime, niz1);
        strcpy(s->prezime, niz2);
        s->broj_bodova = n;
        s->rel_br_bodova = (float)s->broj_bodova/100.0;
    }
    else if(n > s->broj_bodova)
    {
        s->d = dodaj(s->d, niz1, niz2, n);
    }
    else if(n < s->broj_bodova)
    {
        s->l = dodaj(s->l, niz1, niz2, n);
    }
    
    
    
    return s;
}

int Inorder(stablo s)
{
    if(s!=NULL)
    {
        Inorder(s->l);
        printf("%s %s %d\n", s->ime, s->prezime, s->broj_bodova);
        Inorder(s->d);
    }
    
    
    return 0;
}

int Preorder(stablo s)
{
    if(s!=NULL)
    {
        printf("%s %s %d %.2f\n", s->ime, s->prezime, s->broj_bodova, s->rel_br_bodova);
        Preorder(s->l);
        Preorder(s->d);
    }
    
    
    return 0;
}
