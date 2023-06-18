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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024

struct gradovi;
typedef struct gradovi *stablo;
struct gradovi
{
    char grad[BUFFER];
    int id;
    
    stablo l;
    stablo d;
};

struct drzave;
typedef struct drzave *pozicija;
struct drzave
{
    char drzava[BUFFER];
    int ID;
    stablo cvor;
    
    pozicija next;    
};

int citaj_drzave(pozicija);
int Ispis_drzava(pozicija);
int citaj_gradove(pozicija);
stablo dodaj(stablo, char *, int);
int Ispis_gradova(stablo);


int main(void)
{
    struct drzave head;
    head.next = NULL;
    
    
    citaj_drzave(&head);
    printf("\nIspis drzava:\n");
    Ispis_drzava(&head);
    
    citaj_gradove(&head);
    printf("\nIspis drzava i gradova:\n");
    Ispis_drzava(&head);
    
    
    
    return 0;
}

int citaj_drzave(pozicija p)
{
    pozicija g = NULL;
    pozicija temp = p;
    FILE *fp = NULL;
    char *fileName = NULL;
    
    fileName = (char *)malloc(BUFFER * sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija datoteke drzava neuspjesna!\n");
        return 1;
    }
    printf("Unesite ime datoteke: ");
    scanf("%s", fileName);
    
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
        g = (pozicija)malloc(sizeof(struct drzave));
        if(g == NULL)
        {
            printf("Alokacija liste drzava neuspjena!\n");
            return 1;
        }
        
        fscanf(fp, "%s %d", g->drzava, &g->ID);
        g->cvor = NULL;
        
        p = temp;
        while(p->next!=NULL && strcmp(p->next->drzava, g->drzava) < 0)
        {
            p = p->next;
        }
        
        g->next = p->next;
        p->next = g;
    }
    
    
    fclose(fp);
    return 0;
}

int Ispis_drzava(pozicija p)
{
    p = p->next;
    
    while(p!=NULL)
    {
        printf("%s %d ", p->drzava, p->ID);
        if(p->cvor!=NULL)
        {
            printf("-");
            Ispis_gradova(p->cvor);
        }
        printf("\n");
        p = p->next;
    }
    
    
    return 0;
}

int citaj_gradove(pozicija p)
{	
	//p = p->next
    FILE *fp = NULL;
    char *fileName = NULL;
    pozicija temp = p;
    char ime[BUFFER];
    int x;
    
    fileName = (char *)malloc(BUFFER * sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija datoteke drzava neuspjesna!\n");
        return 1;
    }
    printf("Unesite ime datoteke: ");
    scanf("%s", fileName);
    
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
        fscanf(fp, "%s %d", ime, &x);    
        
        p = temp;
        while(p->next!=NULL && p->next->ID != x) //radi ako je p ne p->next
        {
            p = p->next;
        }
        
        if(p->next!=NULL && p->next->ID == x)
        {
            p->next->cvor = dodaj(p->next->cvor, ime, x);    
        }
        

    }
    
    
    fclose(fp);
    return 0;
}

stablo dodaj(stablo s, char *ime, int n)
{
    if(s==NULL)
    {
        s = (stablo)malloc(sizeof(struct gradovi));
        if(s == NULL)
        {
            printf("Alokacija stabla neuspjesna!\n");
            return NULL;
        }
        
        strcpy(s->grad, ime);
        s->id = n;
        s->l = NULL;
        s->d = NULL;
    }
    else if(strcmp(s->grad, ime) > 0)
    {
        s->l = dodaj(s->l, ime, n);
    }
    else if(strcmp(s->grad, ime) < 0)
    {
        s->d = dodaj(s->d, ime, n);
    }
    
    
    return s;
}

int Ispis_gradova(stablo s)
{
    if(s!=NULL)
    {
        Ispis_gradova(s->l);
        Ispis_gradova(s->d);
        printf("->%s ", s->grad);
    }
    
    
    return 0;
}
