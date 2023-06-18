/************************************************************************************************
Napisati program koji  
a) iz datoteke čita podatke (dva int, prvi je vrijednost a drugi prioritet (od 1- 5))
i sprema ih u red s prioritetom. Što je veći prioritet to je podatak bliže vrhu reda. 
b) Podaci unutar istog prioriteta moraju biti sortirani po veličini od najmanjeg prema najvećem. 
(Napomena: U datoteci treba biti najmanje 20 parova.) 
*************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 1024

typedef struct lista *pozicija;
struct lista
{
    int el;
    int prioritet;
    
    pozicija next;
};

int citaj_iz_datoteke(pozicija);
int Ispis(pozicija);


int main(void)
{
    struct lista head;
    head.next = NULL;
    
    
    citaj_iz_datoteke(&head);
    printf("\nLista:\n");
    Ispis(&head);
    
    
    
    return 0;
}

int citaj_iz_datoteke(pozicija p)
{
    pozicija g;
    pozicija temp = p;
    FILE *fp = NULL;
    char *fileName = NULL;
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Neuspjesna alokacija datoteke!\n");
        return 1;
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
        printf("Greska pri otvaranju datoteka!\n");
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
        
        fscanf(fp, "%d %d", &g->el, &g->prioritet);
        
        p = temp;
        while(p->next!=NULL && p->next->prioritet < g->prioritet)
        {
            p = p->next;
        }
        
        if(p->next!=NULL && p->next->prioritet == g->prioritet)
        {
            while(p->next!=NULL && p->next->prioritet == g->prioritet && p->next->el < g->el)
            {
                p = p->next;
            }
            
			if (p->next != NULL && p->next->prioritet == g->prioritet && p->next->el == g->el)
			{
				free(g);
			}
			else
			{
				g->next = p->next;
				p->next = g;
			}
            
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
        printf("%d %d\n", p->el, p->prioritet);
        p = p->next;
    }
    
    return 0;
}
