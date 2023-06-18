/*************************************************************************************************************
Kreirati dvije datoteke i u njih upisati 10 slučajno generiranih brojeva iz opsega od 20-35.
Svaku od datoteka pročitati i spremiti u vezanu listu (kreiraju se dvije vezane liste, npr. L1 i L2). 
Ispisati ih. Iz ove dvije vezane liste se kreiraju dvije nove vezane liste koje sadrže: 
a) presjek parnih članova listi L1 i L2; 
b) uniju neparnih članova listi L1 i L2.
Kod kreiranja listi pod a) i b) se ne smije koristiti malloc, već uzeti postojeće elemente iz listi L1 i L2
i preusmjeriti pokazivače. Ispisati sve četiri liste. U listama pod a) i b) ne smije biti duplih vrijednosti
i vrijednosti moraju bit složene uzlaznim redoslijedom. 
**************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define BUFFER 1024

typedef struct lista *pozicija;
struct lista
{
    int el;
    
    pozicija next;
};

int sl_br(int, int);
int upisi_u_datoteku(void);
int ispis_iz_datoteke(pozicija);
int Ispis(pozicija);
int unija(pozicija, pozicija, pozicija);
int presjek(pozicija, pozicija, pozicija);


int main(void)
{
    struct lista head1, head2, u, p;
    head1.next = NULL;
    head2.next = NULL;
    u.next = NULL;
    p.next = NULL;
    
    
    srand((unsigned)time(NULL));
    
    printf("Upis u prvu datoteku:\n");
    upisi_u_datoteku();
    
    printf("\nUpis u drugu datoteku:\n");
    upisi_u_datoteku();
    
    printf("Ispis prve liste:\n");
    ispis_iz_datoteke(&head1);
    Ispis(&head1);
    
    printf("\nIspis druge liste:\n");
    ispis_iz_datoteke(&head2);
    Ispis(&head2);
    
    printf("\nPresjek:\n");
    presjek(&head1, &head2, &p);
    Ispis(&p);
    
    
    printf("\nUnija:\n");
    unija(&head1, &head2, &u);
    Ispis(&u);


    
    return 0;
}

int upisi_u_datoteku(void)
{
    FILE *fp = NULL;
    char *fileName = NULL;
    int i, x;
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija datoteke neuspjesna!\n");
        return 1;
    }
    
    printf("Unesite ime datoteke u koju zelite zapisat brojeve: ");
    scanf(" %s", fileName);
    
    if(strchr(fileName, '.') == 0)
    {
        strcat(fileName, ".txt");
    }
    
    fp = fopen(fileName, "w");
    if(fp == NULL)
    {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }
    
    
    for(i = 0; i < 10; i++)
    {
        x = sl_br(20, 35);
        
        fprintf(fp, "%d ", x);
    }
    
    
    
    fclose(fp);
    return 0;
}

int sl_br(int min, int max)
{
    return rand()%(max - min) + min;
}

int ispis_iz_datoteke(pozicija p)
{
    FILE *fp = NULL;
    char *fileName = NULL;
    pozicija g, temp = p;
    
    fileName = (char *)malloc(BUFFER*sizeof(char));
    if(fileName == NULL)
    {
        printf("Alokacija datoteke neuspjesna!\n");
        return 1;
    }
    
    printf("Unesite ime datoteke iz koje zelite procitati: ");
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
            printf("Alokacija neuspjesna!\n");
        }
        
        fscanf(fp, "%d", &g->el);
        
        
        while(p->next!=NULL && p->next->el < g->el)
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
        
        printf("%d ", p->el);
        p = p->next;
    }
    
    
    return 0;
}

int presjek(pozicija l1, pozicija l2, pozicija p) //ja cu koristit malloc
{
    l1 = l1->next;
    l2 = l2->next;
    pozicija g;
    pozicija temp = l2;
    pozicija pom = p;
    
    while(l1!=NULL)
    {
        while(l2!=NULL)
        {
            if(l1->el%2 == 0 && l2->el%2 == 0 && l1->el == l2->el)
            {
                g = (pozicija)malloc(sizeof(struct lista));
                g->el = l1->el;
                
                while(p->next!=NULL && p->next->el < g->el)
                {
                    p = p->next;
                }
                
                if(p->next!=NULL && p->next->el == g->el)
                {
                    free(g);
                }
                else
                {
                    g->next = p->next;
                    p->next = g;
                }
                
                p = pom;
            }
            
            l2 = l2->next;
        }
        
        l2 = temp;
        l1 = l1->next;
    }
    
    
    return 0;
}

int unija(pozicija l1, pozicija l2, pozicija u)  //malloc
{
    l1 = l1->next;
    l2 = l2->next;
    
    pozicija g;
    pozicija temp;
    pozicija pom = u;
    
    
    while(l1!=NULL && l2!=NULL)
    {
        g = (pozicija)malloc(sizeof(struct lista));
        if(g == NULL)
        {
            printf("Alokacija neuspjesna!\n");
        }
        
        if(l1->el%2 == 1 && l1->el < l2->el)
        {
            g->el = l1->el;
            l1 = l1->next;
        }
        else if(l2->el%2 == 1 && l2->el < l1->el)
        {
            g->el = l2->el;
            l2 = l2->next;
        }
        else if(l1->el%2 == 0 && l2->el == 0)
        {
            l1 = l1->next;
            l2 = l2->next;
        }
        else if(l2->el%2 == 1 && l2->el == l1->el)
        {
            g->el = l2->el;
            l2 = l2->next;
            l1 = l1->next;
        }
        
        u = pom;
        while(u->next!=NULL && u->next->el < g->el)
        {
            u = u->next;
        }
        
        if(u->next!=NULL && u->next->el == g->el)
        {
            free(g);
        }
        else
        {
            g->next = u->next;
            u->next = g;
        }
        
        
    }
    
    
    if(l1!=NULL) temp = l1;
    else temp = l2;
    
    
    while(temp!=NULL)
    {
       g = (pozicija)malloc(sizeof(struct lista));
        if(g == NULL)
        {
            printf("Alokacija neuspjesna!\n");
        } 
        
        
        g->el = temp->el;
        
        u = pom;
        while(u->next!=NULL && u->next->el < g->el)
        {
            u = u->next;
        }
        
        if(u->next!=NULL && u->next->el == g->el)
        {
            free(g);
        }
        else
        {
            g->next = u->next;
            u->next = g;
        }
        
        temp = temp->next;
        
    }
    
    
    
    return 0;
}

