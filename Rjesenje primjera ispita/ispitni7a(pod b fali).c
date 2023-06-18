/*********************************************************************************
Napisati program kojim se
a) Slučajnim uzorkom generira 100 brojeva iz opsega od 300 do 700, te ih sprema u 
binarno stablo pretraživanja. Zatim ispišemo to stablo u preorder načinu ispisa.

b) Iz generiranog stabla pretraživanja izbrisati sve elemente koji su zapisani u 
proizvoljno definiranoj datoteci. 
**********************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define BUFFER 1024

typedef struct cvorStabla *stablo;
struct cvorStabla
{
    int el;
    
    stablo l;
    stablo d;
};

int sl_br(int, int);
stablo dodaj(stablo, int);
int Preorder(stablo);


int main(void)
{
    
    stablo root = NULL;
    int i, x;
    
    for(i = 0; i < 100; i++)
    {
        x = sl_br(300, 700);
        
        root = dodaj(root, x);
    }
    
    printf("Ispis u Preorder nacinu:\n");
    Preorder(root);
    
    
    return 0;
}

int sl_br(int min, int max)
{
    return rand()%(max - min) + min;
}

stablo dodaj(stablo s, int x)
{
    if(s == NULL)
    {
        s = (stablo)malloc(sizeof(struct cvorStabla));
        if(s == NULL)
        {
            printf("Neuspjesna alokacija stabla!\n");
        }
        
        s->el = x;
        s->l = NULL;
        s->d = NULL;
    }
    else if(s->el < x)
    {
        s->l = dodaj(s->l, x);
    }
    else if(s->el > x)
    {
        s->d = dodaj(s->d, x);
    }
    
    
    return s;
}

int Preorder(stablo s)
{
    if(s!=NULL)
    {
        printf("%d ", s->el);
        Preorder(s->l);
        Preorder(s->d);
    }
    
    
    return 0;
}

