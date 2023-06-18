/****************************************************************************************************
Napisati program koji generira slučajne brojeve u opsegu od 50-80. Ukoliko je generirani broj paran 
sprema se u vezanu listu parnih brojeva i to u padajućem redoslijedu (od najvećeg prema najmanjem).
Ukoliko je broj neparan sprema se u vezanu listu neparnih brojeva, također u padajućem redoslijedu.

Niti jedna vezana lista ne smije sadržavati dva ista elementa. Unos traje sve dok obje liste ne sadrže
10 elemenata. Treba ispisivati koji se broj generira i na kraju ispisati obje liste. 
******************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define BUFFER 1024

typedef struct brojevi *slucajni;
struct brojevi
{
    int el;
    slucajni next;
};

int sl_br(int, int);
int spremiBr(slucajni, slucajni);
int Ispisi(slucajni);

int main(void)
{
    struct brojevi parni, neparni;
    parni.next = NULL;
    neparni.next = NULL;
    
    srand((unsigned)time(NULL));
    
    spremiBr(&parni, &neparni);
    
    printf("\nIspis parnih:\n");
    Ispisi(&parni);
    
    printf("\nIspis neparnih:\n");
    Ispisi(&neparni);
    
    
    
    return 0;
}

int sl_br(int min, int max)
{
    return rand()%(max - min) + min;
}

int Ispisi(slucajni s)
{
    s = s->next;
    
    while(s!=NULL)
    {
        printf("%d ", s->el);
        s = s->next;
    }
    
    return 0;    
}

int spremiBr(slucajni p, slucajni n)
{
    
    int x = 0, y = 0;
    slucajni temp1, temp2;
    temp1 = p;
    temp2 = n;
    slucajni g;
    
    while(x!=10 || y!= 10)
    {
        g = (slucajni)malloc(sizeof(struct brojevi));
        g->el = sl_br(50, 80);
        printf("Izgenerirao se broj %d\n", g->el);
        
        
        if(g->el%2 == 0 && x < 10)
        {
            while(p->next!=NULL && p->next->el > g->el)
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
                x++;
                
            }
            p = temp1;
        }
        else if(g->el%2 == 1 && y < 10)
        {
            
            while(n->next!=NULL && n->next->el > g->el)
            {
                n = n->next;
            }
            
            if(n->next!=NULL && n->next->el == g->el)
            {
                free(g);
            }
            else
            {
                g->next = n->next;
                n->next = g;
                y++;
            }
            n = temp2;
        }
        
        
    }
    
    
    
    return 0;
}

