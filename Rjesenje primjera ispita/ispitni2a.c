/*****************************************************************************************************************
Napisati program koji iz datoteke „text.txt“ čita zadani tekst. Od pročitanih riječi se gradi binarno stablo
pretraživanja, s tim da ukoliko se pronađe riječ koja se već nalazi u stablu potrebno ju je dodati u vezanu listu
istih riječi za određeni čvor. Ispisati stablo. Za odabranu riječ ispitat koliko se puta ponavlja. 
******************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024
#define LIMIT 30

typedef struct lista *pozicija;
typedef struct rijeci *stablo;

struct lista
{
  char niz[LIMIT];
  
  pozicija next;  
};

struct rijeci
{
    char rijec[LIMIT];
    
    stablo l;
    stablo d;
    
    pozicija cvor;
};

stablo citaj_iz_datoteke(stablo);
stablo dodaj(stablo, char *);
int Ispis(stablo);
int IspiST(pozicija);

int main(void)
{
    stablo root = NULL;
    struct lista head;
    head.next = NULL;
    
    root = citaj_iz_datoteke(root);
    if(root == NULL)
    {
        printf("Datoteka je prazna!\n");
    }
    Ispis(root);
    
    
    return 0;
}

stablo citaj_iz_datoteke(stablo s)
{
    FILE *fp = NULL;
    char *fileName = NULL;
    char niz2[LIMIT];
    
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija neuspjesna!\n");
        return NULL;
    }
    printf("Unesite datoteku za citanje: ");
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
        fscanf(fp, "%s", niz2);
        
        s = dodaj(s,niz2);
        
    }
    
    
    fclose(fp);
    return s;
}

stablo dodaj(stablo s, char *ime)
{
    pozicija g;
    
    if(s == NULL)
    {
        s = (stablo)malloc(sizeof(struct rijeci));
        if(s == NULL)
        {
            printf("Alokacija stabla neuspjesna!\n");
        }
        
        strcpy(s->rijec, ime);
        s->l = NULL;
        s->d = NULL;
        s->cvor = NULL;
    }
    else if(strcmp(s->rijec, ime) > 0)
    {
        s->l = dodaj(s->l, ime);
    }
    else if(strcmp(s->rijec, ime) < 0)
    {
        s->d = dodaj(s->d, ime);
    }
    else if(strcmp(s->rijec, ime) == 0)
    {
       g = (pozicija)malloc(sizeof(struct lista));
       if(g == NULL)
       {
           printf("Alokacija liste neuspjesna!\n");
       }
       
       strcpy(g->niz, ime);
       
       if(s->cvor == NULL)
       {
           s->cvor = (pozicija)malloc(sizeof(struct lista));
           s->cvor->next = NULL;
           
       }
        
       g->next = s->cvor->next;
       s->cvor->next = g;
        
    }
    
    
    return s;
}

int Ispis(stablo s)
{
    if(s!=NULL)
    {
        Ispis(s->l);
        Ispis(s->d);
        
        printf("%s ", s->rijec);
        if(s->cvor !=NULL)
        {
            IspiST(s->cvor);
        }
        
    }
    
    return 0;
}
int IspiST(pozicija p)
{
    p = p->next;
    
    while(p!=NULL)
    
    {   printf("->");
        printf("%s ", p->niz);
        p = p->next;
    }
    
    return 0;
}


