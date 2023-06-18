/*******************************************************************************************************
Napisi program koji iz datoteke(ime se unosi u programu) cita podatke u binarno stablo za
pretrazivanje u kojem se sortiraju po prezimenu, pa zatim po imenu osobe.Binarno stablo za
pretrazivanje je definirano strukturom:

struct _person;
typedef struct _person *PersonPosition;
typedef struct _person
{

  char firstName[MAX_NAME];
  char lastName[MAX_NAME];
  Word word;

  PersonPosition left;
  PersonPosition right;
} Person;

Pri tome Word word je clan strukture Person koja predstavlja glavu vezane liste, te je definirana kao:

struct _word;
typedef struct _word *WordPosition;
typedef struct _word
{
  char word[MAX_NAME];
  WordPosition next;
} Word;

Podaci u datoteci su organizirani na nacin da prve dvije rijeci u retku predstavljaju ime i prezime, dok
ostatak rijeci u retku predstavljaju recenicu te osobe.
Recenicu je potrebno za svaku osobu upisati u vezanu listu Word i to;
*vezana lista se formira u proizvoljnom rasporedu - za ocjenu 2;
*vezana lista se formira tako da recenica ima smisla - za ocjenu 5.
Program ispisuje osobe i njihove recenice in order.

Na kraju programa potrebno je osloboditi svu dinamicki alociranu memoriju.
**********************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define BUFFER 1024
#define MAX_NAME 1024

struct _word;
typedef struct _word *WordPosition;
typedef struct _word
{
	char word[MAX_NAME];
	WordPosition next;
} Word;

struct _person;
typedef struct _person *PersonPosition;
typedef struct _person
{

	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	WordPosition cvor;

	PersonPosition left;
	PersonPosition right;
} Person;


PersonPosition citaj_iz_datoteke(PersonPosition);
PersonPosition read_from_file(PersonPosition);
PersonPosition dodaj(PersonPosition, char*, char*, char *);
PersonPosition insert(PersonPosition, char*, char*, char*);
int Inorder(PersonPosition);
int Ispis(WordPosition);



int main(void)
{

	PersonPosition root = NULL;
	PersonPosition root2 = NULL;

	root = citaj_iz_datoteke(root);
	printf("\nSortirano po prezimenu:\n");
	Inorder(root);

	root2 = read_from_file(root2);
	printf("\n\nSortirano po imenu:\n");
	Inorder(root2);


	return 0;
}

PersonPosition citaj_iz_datoteke(PersonPosition p)
{

	FILE *fp = NULL;
	char *fileName = NULL;
	char ime[MAX_NAME], prezime[MAX_NAME];
	char rijeci[MAX_NAME];


	fileName = (char *)malloc(BUFFER * sizeof(char));
	if (fileName == NULL)
	{
		printf("Alokacija datoteke neuspjesna!\n");
	}

	printf("Unesite ime datoteke za citanje: ");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == 0)
	{
		strcat(fileName, ".txt");
	}


	fp = fopen(fileName, "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %[^\n]s", ime, prezime, rijeci);

		p = dodaj(p, ime, prezime, rijeci);

	}



	fclose(fp);
	return p;
}

PersonPosition dodaj(PersonPosition p, char *ime, char *prezime, char *rijeci)
{


	if (p == NULL)
	{
		p = (PersonPosition)malloc(sizeof(Person));
		if (p == NULL)
		{
			printf("Alokacija stabla neuspjesna!\n");
			return NULL;
		}

		strcpy(p->firstName, ime);
		strcpy(p->lastName, prezime);


		p->cvor = (WordPosition)malloc(sizeof(Word));
		if (p->cvor == NULL)
		{
			printf("Alokacija cvora neuspjesna!\n");
		}

		strcpy(p->cvor->word, rijeci);
		p->cvor->next = NULL;

		p->left = NULL;
		p->right = NULL;

	}
	else if (strcmp(p->lastName, prezime) > 0)
	{
		p->left = dodaj(p->left, ime, prezime, rijeci);
	}
	else if (strcmp(p->lastName, prezime) < 0)
	{
		p->right = dodaj(p->right, ime, prezime, rijeci);
	}
	else if (strcmp(p->lastName, prezime) == 0)
	{
		if (strcmp(p->firstName, ime) > 0)
		{
			p->left = dodaj(p->left, ime, prezime, rijeci);
		}
		else if (strcmp(p->firstName, ime) < 0)
		{
			p->right = dodaj(p->right, ime, prezime, rijeci);
		}
	}



	return p;
}

PersonPosition read_from_file(PersonPosition p)
{
	FILE *fp = NULL;
	char *fileName = NULL;
	char ime[MAX_NAME], prezime[MAX_NAME];
	char rijeci[MAX_NAME];


	fileName = (char *)malloc(BUFFER * sizeof(char));
	if (fileName == NULL)
	{
		printf("Alokacija datoteke neuspjesna!\n");
	}

	printf("Unesite ime datoteke za citanje: ");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == 0)
	{
		strcat(fileName, ".txt");
	}


	fp = fopen(fileName, "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %[^\n]s", ime, prezime, rijeci);

		p = insert(p, ime, prezime, rijeci);

	}



	fclose(fp);
	return p;


}

PersonPosition insert(PersonPosition p, char *ime, char *prezime, char *rijeci)
{

	if (p == NULL)
	{
		p = (PersonPosition)malloc(sizeof(Person));
		if (p == NULL)
		{
			printf("Alokacija stabla neuspjesna!\n");
			return NULL;
		}

		strcpy(p->firstName, ime);
		strcpy(p->lastName, prezime);


		p->cvor = (WordPosition)malloc(sizeof(Word));
		if (p->cvor == NULL)
		{
			printf("Alokacija cvora neuspjesna!\n");
		}

		strcpy(p->cvor->word, rijeci);
		p->cvor->next = NULL;

		p->left = NULL;
		p->right = NULL;

	}
	else if (strcmp(p->firstName, ime) > 0)
	{
		p->left = dodaj(p->left, ime, prezime, rijeci);
	}
	else if (strcmp(p->firstName, ime) < 0)
	{
		p->right = dodaj(p->right, ime, prezime, rijeci);
	}
	else if (strcmp(p->firstName, ime) == 0)
	{
		if (strcmp(p->lastName, prezime) > 0)
		{
			p->left = dodaj(p->left, ime, prezime, rijeci);
		}
		else if (strcmp(p->lastName, prezime) < 0)
		{
			p->right = dodaj(p->right, ime, prezime, rijeci);
		}
	}



	return p;
}


int Inorder(PersonPosition p)
{

	if (p != NULL)
	{
		Inorder(p->left);
		printf("%s %s ", p->firstName, p->lastName);
		Ispis(p->cvor);
		Inorder(p->right);
	}


	return 0;
}

int Ispis(WordPosition w)
{
	printf("%s\n", w->word);

	return 0;
}


