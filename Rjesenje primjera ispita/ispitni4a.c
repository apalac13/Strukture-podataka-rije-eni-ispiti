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

typedef struct cvorStabla *stablo;
struct cvorStabla
{
	int br;

	stablo l;
	stablo d;
};


int sl_br(int, int);
int spremiBr(pozicija);
int Ispis(pozicija);
int minimum(pozicija);
int maksimum(pozicija);
int prebaci(pozicija, pozicija, int);
int najblizi_el(pozicija, int);
stablo dodaj(stablo, int);
stablo dodaj_ostale(pozicija, stablo, int);
int postOrder(stablo);


int main(void)
{
	stablo root = NULL;
	struct lista head, head2;
	head.next = NULL;
	head2.next = NULL;
	int min, max, sr;
	int element;

	srand((unsigned)time(NULL));

	printf("Lista:\n");
	spremiBr(&head);
	Ispis(&head);


	min = minimum(&head);
	printf("\nMinimalna vrijednost je %d:\n", min);

	max = maksimum(&head);
	printf("Maksimalna vrijednost je %d:\n", max);

	sr = (max + min) / 2;
	printf("Srednja vrijednost je %d\n", sr);

	printf("Rezultantna lista:\n");
	prebaci(&head, &head2, sr);
	Ispis(&head2);

	element = najblizi_el(&head2, sr);
	printf("\nNajblizi element je %d\n", element);

	printf("Ispis stabla:\n");
	root = dodaj(root, element);
	root = dodaj_ostale(&head2, root, element);
	postOrder(root);


	return 0;
}

int spremiBr(pozicija p)
{
	int a = 0;
	int x;
	pozicija g;
	pozicija temp = p;

	while (a != 15)
	{
		g = (pozicija)malloc(sizeof(struct lista));
		if (g == NULL)
		{
			printf("Alokacija liste neuspjesna!\n");
			return 1;
		}

		g->el = sl_br(100, 120);
		printf("Izgenerirao se broj %d\n", g->el);

		while (p->next != NULL && p->next->el != g->el)
		{
			p = p->next;
		}

		if (p->next != NULL && p->next->el == g->el)
		{
			free(g);
		}
		else
		{
			while (p->next != NULL)
			{
				p = p->next;
			}

			g->next = p->next;
			p->next = g;
			a++;
		}

		p = temp;

	}


	return 0;
}

int sl_br(int min, int max)
{
	return rand() % (max - min) + min;
}

int Ispis(pozicija p)
{
	p = p->next;

	while (p != NULL)
	{
		printf("%d ", p->el);
		p = p->next;
	}


	return 0;
}

int minimum(pozicija p)
{
	p = p->next;

	pozicija min = p;

	while (p != NULL)
	{
		if (p->el < min->el)
		{
			min = p;
		}

		p = p->next;
	}


	return min->el;
}

int maksimum(pozicija p)
{
	p = p->next;

	pozicija max = p;

	while (p != NULL)
	{
		if (p->el > max->el)
		{
			max = p;
		}

		p = p->next;
	}


	return max->el;
}

int prebaci(pozicija p, pozicija n, int x)
{
	p = p->next;
	pozicija temp = n;
	pozicija g;

	while (p != NULL)
	{
		g = (pozicija)malloc(sizeof(struct lista));
		if (g == NULL)
		{
			printf("Alokacija neuspjesna!\n");
			return 1;
		}

		g->el = p->el;

		if (g->el < x)
		{
			n = temp;
			g->next = n->next;
			n->next = g;

		}
		else if (g->el >= x)
		{
			n = temp;

			while (n->next != NULL && n->next->el <= x)
			{
				n = n->next;
			}

			g->next = n->next;
			n->next = g;
		}

		p = p->next;
	}



	return 0;
}

int najblizi_el(pozicija p, int x)
{
	p = p->next;
	pozicija element = p;


	while (p != NULL)
	{
		if (p->el >= (x - 1) && p->el <= (x + 1))
		{
			element = p;
		}
		p = p->next;
	}

	return element->el;
}

stablo dodaj(stablo s, int x)
{
	if (s == NULL)
	{
		s = (stablo)malloc(sizeof(struct cvorStabla));
		if (s == NULL)
		{
			printf("Alokacija stabla neuspjesna!\n");
		}

		s->br = x;
		s->l = NULL;
		s->d = NULL;
	}
	else if (x < s->br)
	{
		s->l = dodaj(s->l, x);
	}
	else if (x > s->br)
	{
		s->d = dodaj(s->d, x);
	}



	return s;
}

stablo dodaj_ostale(pozicija p, stablo s, int x)
{

	p = p->next;


	while (p != NULL)
	{
		if (p->el == x)
		{
			p = p->next;
		}

		s = dodaj(s, p->el);

		p = p->next;
	}


	return s;
}

int postOrder(stablo s)
{

	if (s != NULL)
	{
		postOrder(s->l);
		postOrder(s->d);
		printf("%d ", s->br);
	}


	return 0;
}