/*******************************************************************************
Napisati program koji 
a) Iz datoteke čita stringove (mogu biti imena i mora ih biti min. 10) 
i stvara vezanu listu elemenata sortiranih po abecedi.
b) Elemente iz datoteke ubaciti u binarno stablo i ispisati ga na inorder način. 
*******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024
#define LIMIT 50

typedef struct lista *pozicija;
struct lista
{
    char ime[LIMIT];
    pozicija next;
};

typedef struct cvorStabla *stablo;
struct cvorStabla
{
    char obitelj[LIMIT];
    
    stablo l;
    stablo d;
};

int citaj_iz_datoteke(pozicija);
int Ispis(pozicija);
stablo stvoriStablo(pozicija, stablo);
stablo dodaj(stablo, char *);
int Inorder(stablo);

int main(void)
{
    stablo root = NULL;
    struct lista head;
    head.next = NULL;
    
    printf("Lista:\n");
    citaj_iz_datoteke(&head);
    Ispis(&head);
    
    printf("\nStablo:\n");
    root = stvoriStablo(&head, root);
    Inorder(root);
    
    return 0;
}

int citaj_iz_datoteke(pozicija p)
{
    FILE *fp = NULL;
    char *fileName = NULL;
    pozicija g;
    pozicija temp = p;
    
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija imena datoteke neuspjesna!\n");
        return 1;
    }
    
    printf("Unesite datoteku za citanje imena: ");
    scanf(" %s", fileName);
    
    
    if(strchr(fileName, '.') == 0)
    {
        strcat(fileName, ".txt");
    }
    
    fp = fopen(fileName, "r");
    if(fp == NULL)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }
    
    while(!feof(fp))
    {
        g = (pozicija)malloc(sizeof(struct lista));
        if(g == NULL)
        {
            printf("Alokacija liste neuspjesna!\n");
            return 1;
        }
        
        fscanf(fp, "%s", g->ime);
        
        p = temp;
        
        while(p->next!=NULL && strcmp(p->next->ime, g->ime) < 0)
        {
            p = p->next;
            
        }
        
        if(p->next!=NULL && strcmp(p->next->ime, g->ime) == 0)
        {
            free(g);
        }
        else
        {
            g->next = p->next;
            p->next = g;
            
        }
        
    }
    
    
    
    fclose(fp);
    return 0;
}

int Ispis(pozicija p)
{
    p = p->next;
    
    while(p!=NULL)
    {
        printf("%s ", p->ime);
        p = p->next;
    } 
    
    return 0;
}

stablo stvoriStablo(pozicija p, stablo s)
{
    p = p->next;
    
    while(p!=NULL)
    {
        s = dodaj(s, p->ime);
        p = p->next;
    }
    
    
    return s;
}

stablo dodaj(stablo s, char *niz)
{
    if(s==NULL)
    {
        s = (stablo)malloc(sizeof(struct cvorStabla));
        if(s == NULL)
        {
            printf("Alokacija stabla neuspjesna!\n");
        }
        
        strcpy(s->obitelj, niz);
        s->l = NULL;
        s->d = NULL;
    }
    else if(strcmp(s->obitelj, niz) > 0)
    {
        s->l = dodaj(s->l, niz);
    }
    else if(strcmp(s->obitelj, niz) < 0)
    {
        s->d = dodaj(s->d, niz);
    }
    
    
    
    return s;
}

int Inorder(stablo s)
{
    
    if(s!=NULL)
    {
        Inorder(s->l);
        printf("%s ", s->obitelj);
        Inorder(s->d);
    }
    
    
    return 0;
}
