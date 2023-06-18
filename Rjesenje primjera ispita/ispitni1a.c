/******************************************************************************************************
Napisati program koji:
a) Iz datoteke „drzave.txt“ čita popis država i njihov ID od pročitanih
država izgraditi vezanu listu država na sortirani način od početka prema kraju abecede (treba raditi
sortirani unos, a ne naknadno sortirati). Uz pokazivač na sljedeću državu struktura od koje se gradi 
vezana lista mora sadržavati i pokazivač na stablo gradova koji su u toj državi (trenutno NULL) - za 2

b) Iz datoteke „gradovi.txt“ pročitati ime grada i ID države u kojoj se nalazi. Pronaći odgovarajuću 
državu u gornjoj listi, te dodati pročitani grad u stablo gradova te države. Za zadanu državu ispisati 
sve njene gradove po abecedi. – za 5
********************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024
#define LIMIT 50

typedef struct gradovi *stablo;
typedef struct drzave *pozicija;

struct gradovi
{
    char grad[LIMIT];
    
    stablo l;
    stablo d;
};


struct drzave
{
    char drzava[LIMIT];
    int ID;
    pozicija next;
    
    stablo cvor;
};

int citaj_drzave(pozicija);
int citaj_gradove(pozicija);
stablo dodaj(stablo, char*);
int Ispis(pozicija);
int IspiST(stablo);

int main(void)
{
    
    struct drzave head;
    head.next = NULL;
    
    printf("Drzave:\n");
    citaj_drzave(&head);
    Ispis(&head);
    
    printf("\nGradovi:\n");
    citaj_gradove(&head);
    Ispis(&head);
    
    return 0;
}

int citaj_drzave(pozicija p)
{
    FILE *fp = NULL;
    char *fileName = NULL;
    pozicija g;
    pozicija temp = p;
    
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija neuspjesna!\n");
        return 1;
    }
    
    printf("Unesite datoteku za citanje: ");
    scanf(" %s", fileName);
    
    if(strchr(fileName,'.') == 0)
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
        g = (pozicija)malloc(sizeof(struct drzave));
        if(g == NULL)
        {
            printf("Alokacija neuspjesna!\n");
            return 1;
        }
        
        fscanf(fp, "%s %d", g->drzava, &g->ID);
        g->cvor = NULL;
        
        while(p->next!=NULL && strcmp(p->next->drzava, g->drzava) < 0)
        {
            p = p->next;
        }
        
        g->next = p->next;
        p->next = g;
                
        p = temp;
    }
    
    
    
    fclose(fp);
    return 0;
}

int Ispis(pozicija p)
{
    p = p->next;
    
    while(p!=NULL)
    {
        printf("%s %d\n", p->drzava, p->ID);
        if(p->cvor!=NULL)
        {
            IspiST(p->cvor);
            printf("\n");
        }
        p = p->next;
    }
    
    
    return 0;
}

int citaj_gradove(pozicija p)
{
    p = p->next;
    FILE *fp = NULL;
    char *fileName = NULL;
    char gr[LIMIT];
    int id;
    pozicija temp = p;
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija neuspjesna!\n");
        return 1;
    }
    
    printf("Unesite ime datoteke za citanje gradova: ");
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
        
        fscanf(fp, "%s %d", gr, &id);
        
        while(p!=NULL && p->ID != id)
        {
            p = p->next;
        }
        
        if(p->ID == id)
        {
            p->cvor = dodaj(p->cvor, gr);
        }
        
        
        p = temp;
    }
    
    
    fclose(fp);
    return 0;
}

stablo dodaj(stablo s, char *ime)
{
    if(NULL == s)
    {
        s = (stablo)malloc(sizeof(struct gradovi));
        if(s == NULL)
        {
            printf("Alokacija neuspjesna!\n");
            
        }
        
        strcpy(s->grad, ime);
        s->l = NULL;
        s->d = NULL;
    }
    else if(strcmp(s->grad, ime) > 0)
    {
        s->l = dodaj(s->l, ime);
    }
    else if(strcmp(s->grad, ime) < 0)
    {
        s->d = dodaj(s->d, ime);    
    }
    
    
    
    return s;
}

int IspiST(stablo s)
{
    if(s!=NULL)
    {
        IspiST(s->l);
        IspiST(s->d);
        
        printf("%s ", s->grad);
    }
    
    return 0;
}

