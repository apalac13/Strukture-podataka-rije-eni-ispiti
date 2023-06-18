/************************************************************************************************
Napisati program koji čita iz datoteke dio teksta, te kreira binarno stablo pretraživanja.
Binarno stablo se kreira na način da se u njega upisuju sve različite riječi iz teksta koji
je zapisan u datoteci s pripadajućim duljinama unesene riječi. 
struct _Cvor{char *rijec; int length; struct _Cvor *Left; struct _Cvor *Right;}; 

Potrebno je izračunati prosječnu duljinu svake riječi zapisane u binarnom stablu. 
Napisati program koji iz tako kreiranog binarnog stabla u vezanu listu puni samo one riječi koje
su dulje od prosječne duljine svih riječi, te ispisati tu vezanu listu
*************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024
#define LIMIT 20

typedef struct cvor *stablo;
struct cvor
{
    char *rijec;
    int length;
    
    stablo l;
    stablo d;
};

typedef struct lista *pozicija;
struct lista
{
    char niz[LIMIT];
    
    pozicija next;
};

stablo citaj_iz_datoteke(stablo);
stablo dodaj(stablo, char *, int);
int Postorder(stablo);
float prosjek_rijeci(stablo);
int stvori_listu(stablo, pozicija, float);
int Ispis(pozicija);


int main(void)
{
    stablo root = NULL;
    float n;
    struct lista head;
    head.next = NULL;
    
    root = citaj_iz_datoteke(root);
    printf("Ispis stabla:\n");
    Postorder(root);
    
    n = prosjek_rijeci(root);
    printf("Prosjecna duljina rijeci je %.2f\n", n);
    
    stvori_listu(root, &head, n);
    printf("Ispis liste:\n");
    Ispis(&head);
    
    
    
    
    return 0;
}

stablo citaj_iz_datoteke(stablo s)
{
    FILE *fp = NULL;
    char *fileName = NULL;
    char niz[LIMIT];
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija datoteke neuspjesna!\n");
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
    }
    
    
    while(!feof(fp))
    {
        fscanf(fp, "%s", niz);
        
        s = dodaj(s, niz, strlen(niz));
        
    }
    
    
    
    fclose(fp);
    return s;
}

stablo dodaj(stablo s, char *ime, int n)
{
    
    if(s == NULL)
    {
        s = (stablo)malloc(sizeof(struct cvor));
        if(s == NULL)
        {
            printf("Alokacija stabla neuspjesna!\n");
        }
        
        s->rijec = (char *)malloc((n+1)*sizeof(char));
        strcpy(s->rijec, ime);
        s->length = n;
        s->l = NULL;
        s->d = NULL;
    }
    else if(strcmp(s->rijec, ime) > 0)
    {
        s->l = dodaj(s->l, ime, n);
    }
    else if(strcmp(s->rijec, ime) < 0)
    {
        s->d = dodaj(s->d, ime, n);
    }
    
    
    
    return s;
}

int Postorder(stablo s)
{
    if(s!=NULL)
    {
        Postorder(s->l);
        Postorder(s->d);
        printf("%s %d\n", s->rijec, s->length);
    }
    
    
    return 0;
}

float prosjek_rijeci(stablo s)
{
    static float prosjek = 0.0;
    static float x = 0.0;
    
    if(s!=NULL)
    {
        prosjek_rijeci(s->l);
        prosjek_rijeci(s->d);
        
        prosjek += (float)s->length;
        ++x;
    }
    
    
   return (prosjek/x); 
}

int stvori_listu(stablo s, pozicija p, float x)
{
    pozicija g;
    
    if(s!=NULL)
    {
        stvori_listu(s->l, p, x);
        stvori_listu(s->d, p, x);
        
        if(s->length > x)
        {
            
            g = (pozicija)malloc(sizeof(struct lista));
            if(g == NULL)
            {
                printf("Neuspjesna alokacija liste!\n");
                return 1;
            }
            
            strcpy(g->niz, s->rijec);
            g->next = p->next;
            p->next = g;
            
        }
        
    }
    
    
    return 0;
}

int Ispis(pozicija p)
{
    p = p->next;
    
    while(p!=NULL)
    {
        printf("%s ", p->niz);
        p = p->next;
    }
    
    
    return 0;
}



