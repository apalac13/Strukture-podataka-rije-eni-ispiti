/**************************************************************************************
Napisati program koji iz dvije datoteke (jedna sadrži ocjenu 1. kolokvija,a druga 
ocjenu 2. kolokvija) kreira vezanu listu studenata koji su položili ispit i ta se 
nova vezana lista slaže po ocjenama. Način pretvorbe bodova u ocjenu je dan u tablici.
***************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define BUFFER 1024
#define LIMIT 20

typedef struct student *pozicija;
struct student
{
    char ime[LIMIT];
    char prezime[LIMIT];
    int bodovi;
    float ocjena;
    
    pozicija next;
};

int citaj_iz_datoteke(pozicija);
int Ispis(pozicija);
int polozeno(pozicija, pozicija, pozicija);


int main(void)
{
    struct student head1, head2, head3;
    head1.next = NULL;
    head2.next = NULL;
    head3.next = NULL;
    
    printf("Studenti koji su polozili prvi kolokvij:\n");
    citaj_iz_datoteke(&head1);
    Ispis(&head1);
    
    printf("\nStudenti koji su polozili drugi kolokvij:\n");
    citaj_iz_datoteke(&head2);
    Ispis(&head2);
    
    printf("\nStudenti koji su polozili ispit:\n");
    polozeno(&head1, &head2, &head3);
    Ispis(&head3);
    
    
    return 0;
}

int Ispis(pozicija p)
{
    p = p->next;
    
    while(p!=NULL)
    {
        printf("%s %s %.2f\n", p->ime, p->prezime, p->ocjena);
        p = p->next;
    }
    
    
    
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
        printf("Alokacija neuspjesna!\n");
        return 1;
    }
    
    printf("Unesite datoeku iz koje zelite procitati sadrzaj: ");
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
        g = (pozicija)malloc(sizeof(struct student));
        if(g == NULL)
        {
            printf("Alokacija neuspjena!\n");
            return 1;
        }
        
        fscanf(fp, "%s %s %d", g->ime, g->prezime, &g->bodovi);
        
        if(g->bodovi>=50 && g->bodovi<60)
        {
            g->ocjena = 2.00;
        }
        else if(g->bodovi>=60 && g->bodovi<74)
        {
            g->ocjena = 3.00;
        }
        else if(g->bodovi>=74 && g->bodovi<87)
        {
            g->ocjena = 4.00;
        }
        else
        {
            g->ocjena = 5.00;
        }
        
        while(p->next!=NULL && p->next->ocjena > g->ocjena)
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

int polozeno(pozicija p, pozicija d, pozicija i)
{
    
    p = p->next;
    d = d->next;
    
    pozicija g;
    pozicija temp = d;
    pozicija zam = i;
    
    while(p!=NULL)
    {
        while(d!=NULL)
        {
            
            if(strcmp(p->ime, d->ime) == 0 && strcmp(p->prezime, d->prezime) == 0)
            {
                g = (pozicija)malloc(sizeof(struct student));
                if(g == NULL)
                {
                    printf("Alokacija neuspjesna!\n");
                    return 1;
                }
                
                strcpy(g->ime, d->ime);
                strcpy(g->prezime, d->prezime);
                
                g->ocjena = (p->ocjena + d->ocjena)/2.0;
                
                while(i->next!=NULL && i->next->ocjena > g->ocjena)
                {
                    i = i->next;
                }
                
                g->next = i->next;
                i->next = g;
                
                i = zam;
            }
            
            d = d->next;
        }
        
        d = temp; 
        p = p->next;
    }
    
    
    
    return 0;
}



