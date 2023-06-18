/*********************************************************************************************************************
Napisati program koji generira 15 slučajnih brojeva u opsegu od 100 - 120 i sprema ih u vezanu listu,
po redoslijedu generiranja, a ne sortirano. U listi ne smije biti duplih vrijednosti.
a) Potrebno je pronaći minimalnu i maksimalnu vrijednost, te iz njih izračunati srednju vrijednost ((min+max)/2)
i nakon toga sve vrijednosti koje su veće od srednje prebaciti na kraj liste. Ispisati minimalnu, maksimalnu i
srednju vrijednost kao i rezultantnu listu.

b) Pronaći vrijednost u listi koja je najbliža srednjoj vrijednosti i nju postaviti kao root element binarnog stabla
za pretraživanje. Nakon toga sve elemente iz liste prebaciti u stablo i gotovo stablo ispisati na level order način.
**********************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER 1024

struct nodeTree;
typedef struct nodeTree *tree;
struct nodeTree
{
    int br;
    
    tree l;
    tree r;
};


struct list;
typedef struct list *position;
struct list
{
    int el;
    position next;
};

int rand_num(int, int);
int create_list(position);
int print_list(position);
int max_value(position);
int min_value(position);
int create_new_list(position, position, float);
int closest_value(position, float);
tree add_el(tree, int);
tree create_tree(tree, position, int);
int print_tree(tree);



int main(void)
{
    tree root = NULL;
    struct list head, glava;
    head.next = NULL;
    glava.next = NULL;
    
    int max, min, close;
    float mid;
    
    srand((unsigned)time(NULL));    
    
    create_list(&head);
    printf("\nPrinted list:\n");
    print_list(&head);
    
    max = max_value(&head);
    printf("\nMax value is %d\n", max);
    
    min = min_value(&head);
    printf("Min value is %d\n", min);
    
    mid = ((float)(max + min))/2.00;
    printf("Middle value is %.2f\n", mid);
    
    create_new_list(&head, &glava, mid);
    printf("\nNew list:\n");
    print_list(&glava);
    
    close = closest_value(&head, mid);
    printf("\nClosest value of middle one is %d\n", close);
    
    root = add_el(root, close);
    root = create_tree(root, &head, close);
    printf("\nPrinted tree:\n");
    print_tree(root);
    
    
    
    return 0;
}

int rand_num(int min, int max)
{
    return rand()%(max - min) + min;
}

int create_list(position p)
{
    position g = NULL;
    position temp = p;
    int a = 0;    
    
    while(a!=15)
    {
        g = (position)malloc(sizeof(struct list));
        if(g == NULL)
        {
            printf("\nAlocation of list is unsuccessful!\n");
            return 1;
        }
        
        g->el = rand_num(100, 120);
        printf("Generate number is %d\n", g->el);
        
        p = temp;
        while(p->next!=NULL && p->next->el != g->el)
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
            
            ++a;
        }
        
    }
    
    
    
    return 0;
}

int print_list(position p)
{
    p = p->next;
    
    while(p!=NULL)
    {
        printf("%d ", p->el);
        p = p->next;
    }
    
    
    return 0;
}

int max_value(position p)
{
    p = p->next;
    position max = p;
    
    while(p!=NULL)
    {
        if(p->el > max->el)
        {
            max->el = p->el;
        }
        
        p = p->next;
    }
    
    
    return max->el;
}

int min_value(position p)
{
    p = p->next;
    position min = p;
    
    while(p!=NULL)
    {
        if(p->el < min->el)
        {
            min->el = p->el;
        }
        
        p = p->next;
    }
    
    
    return min->el;
}

int create_new_list(position p, position n, float x)
{
    p = p->next;
    position temp = p;
    position beg = n;
    position g = NULL;
    
    while(p != NULL)
    {
        
        g = (position)malloc(sizeof(struct list));
        if(g == NULL)
        {
            printf("Alocation of new list is unsuccessful");
            return 1;
        }
        g->el = p->el;
        
        if(p->el < x)
        {
            n = beg;
            
        }
        else if(p->el > x)
        {
            n = beg;
            while(n->next!=NULL)
            {
                n = n->next;
            }
            
        }
        else
        {
            n = beg;
            while(n->next!=NULL && n->next->el < x)
            {
                n = n->next;
            }
            
        }
        
        g->next = n->next;
        n->next = g;
        
        p = p->next;
    }
    
    
    
    
    return 0;
}

int closest_value(position p, float x)
{
    p = p->next;
    position close = p;
    
    while(p!=NULL)
    {
        if(p->el >= (x - 1) && p->el <= (x + 1))
        {
            close->el = p->el;
        }
        
        p = p->next;
    }
    
    
    return close->el;
}

tree add_el(tree t, int x)
{
    if(t == NULL)
    {
        t =(tree)malloc(sizeof(struct nodeTree));
        if(t == NULL)
        {
            printf("\nAlocation of tree is unsuccessful!\n");
            return NULL;
        }
        
        t->br = x;
        t->l = NULL;
        t->r = NULL;
    }
    else if(x < t->br)
    {
        t->l = add_el(t->l, x);
    }
    else if(x > t->br)
    {
        t->r = add_el(t->r, x);
    }
    
    
    return t;
}

tree create_tree(tree t, position p, int x)
{
    p = p->next;
    
    while(p!=NULL)
    {
        if(p->el == x)
        {
            p = p->next;
        }
        
        t = add_el(t, p->el);
        p = p->next;
    }
    
    
    return t;
}

int print_tree(tree t)
{
    if(t!=NULL)
    {
        print_tree(t->l);
        print_tree(t->r);
        printf("%d ", t->br);
    }
    
    
    
    return 0;
}
