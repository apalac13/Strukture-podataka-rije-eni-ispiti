/*****************************************************************************************************

Zadana je datoteka sa popisom studenata, njihovim ocjenama i pripadajućim  ECTS-ovima.
Svaki redak datoteke sadrži ime, prezime, ocjenu
Napisati program koji učitava podatke u hash tablicu dužine 23 i pri tome:
	* Svaki element hash tablice označava glavu vezane liste.
	* Ulazni podaci iz datoteke se raspršuju na način da se zbroje ASCII vrijednosti prva tri slova
	  imena i prezimena.
	* Svaka vezana lista je sortirana po prezimenu, zatim po imenu studenata
	* Ukoliko se pojavi student s već postojećim imenom i prezimenom ne uosi se ponovo
	* Čvor vezane liste je definiran sljedećim poljima:
				struct _student;
				typedef struct _student *StudentPosition;
				typedef struct _student{
					char firstName[MAX_NAME];
					char lastName[MAX_NAME];
					int total;
					int totalEcts;
					StudentPosition next;
				} Student;
Varijabla total je suma umnožaka ocjena s pripadajućim ECTS-om, a totalEcts je suma svih ECTS-ova.
Npr. ukoliko su ulazni podaci za studenta Ivu Matića:
(ime)   (prezime)   (ocjena)    (ECTS)
---------------------------------------------------------
---------------------------------------------------------
Ivo     Matića          4         7
Ivo     Matića          5         2
...
Tada čvor vezane liste treba sadržavati podatke:
{
	firstName: Ivo
	lastName: Matić
	totalEcts: 38
	totalEcts: 9
	next: ...
}

Za ocjenu 2:
	* Iz hash tablice upisati sve studente u datoteku zajedno s njihovim relevantnim prosjekom,
	* Pobrisati svu dinamički rezerviranu memoriju i zatvoriti datoteke
Za ocjenu 3:
	* Iz hash tablice upisati u datoteku samo one studente (zajedno s njihovim relevantnim prosjekom)
	  koji ispunjavaju dva uvjeta za stipendiju:
		* Relativni prosjek veći ili jednak 3.5
		* Broj položenih ECTS-ova veći ili jednak 55
	* Pobrisati svu dinamički rezerviranu memoriju i zatvoriti datoteke
Za ocjenu 5:
	* Studente iz koji zadovoljavaju uvjete za stipendiju u datoteku upisati od najvećeg prema
	  najmanjem relativnom prosjeku.

**********************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER 1024
#define MAX_NAME 50


struct _student;
typedef struct _student *StudentPosition;
typedef struct _student {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int total;
	int totalEcts;
	StudentPosition next;
} Student;


struct hashT;
typedef struct hashT *hashTab;
struct hashT
{
	int vel;
	StudentPosition *hashListe;
};

int citaj_iz_datoteke(StudentPosition);
hashTab inicijalizacija_tablice(hashTab, int);
int preslikavanje(char *, int);
int napravi_tablicu(hashTab, StudentPosition);
int ispisi_tablicu(hashTab);


int main(void)
{
	hashTab H = NULL;
	int vel_tab = 23;
	Student s;
	s.next = NULL;
	s.total = 0;
	s.totalEcts = 0;

	citaj_iz_datoteke(&s);

	H = inicijalizacija_tablice(H, vel_tab);
	napravi_tablicu(H, &s);
	printf("\nIspis hash_tablice\n");
	ispisi_tablicu(H);


	return 0;
}

int citaj_iz_datoteke(StudentPosition s)
{
	FILE *fp = NULL;
	char *fileName = NULL;
	StudentPosition g = NULL;
	StudentPosition temp = s;


	fileName = (char *)malloc(BUFFER * sizeof(char));
	if (fileName == NULL)
	{
		printf("\nAlokacija datoteke neuspjesna!\n");
		return 1;
	}

	printf("Unesite ime datoteke za citanje: ");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == 0)
	{
		strcat(fileName, ".txt");
	}


	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("\nGreska pri otvaranju datoteke!\n");
		return 1;
	}

	while (!feof(fp))
	{
		g = (StudentPosition)malloc(sizeof(Student));
		if (g == NULL)
		{
			printf("\nAloakcija liste studenata neuspjesna!\n");
			return 1;
		}
		g->total = 0;
		g->totalEcts = 0;

		fscanf(fp, "%s %s %d %d", g->firstName, g->lastName, &g->total, &g->totalEcts);
		g->total = (g->total*g->totalEcts);

		s = temp;
		while (s->next != NULL && strcmp(s->firstName, g->firstName) != 0 && strcmp(s->lastName, g->lastName) != 0)
		{
			s = s->next;
		}

		if (s->next != NULL && strcmp(s->firstName, g->firstName) == 0 && strcmp(s->lastName, g->lastName) == 0)
		{
			s->total += g->total;
			s->totalEcts += g->totalEcts;
			free(g);
		}
		else
		{
			g->next = s->next;
			s->next = g;
		}


	}


	fclose(fp);
	return 0;
}

hashTab inicijalizacija_tablice(hashTab H, int n)
{
	int i;

	H = (hashTab)malloc(sizeof(struct hashT));
	if (H == NULL)
	{
		printf("\nInicijalizacija tablice neuspjesna!\n");
		return NULL;
	}

	H->vel = n;
	H->hashListe = (StudentPosition *)malloc(sizeof(StudentPosition));
	if (H->hashListe == NULL)
	{
		printf("\nAlokacija cvorova neuspjesna!\n");
		return NULL;
	}

	for (i = 0; i < H->vel; i++)
	{
		H->hashListe[i] = (StudentPosition)malloc(sizeof(Student));
		if (H->hashListe[i] == NULL)
		{
			printf("\nAlokacija liste neuspjesna\n");
			return NULL;
		}
		H->hashListe[i]->next = NULL;
	}


	return H;
}

int napravi_tablicu(hashTab H, StudentPosition s)
{

	s = s->next;
	int i;
	StudentPosition g = NULL;

	while (s != NULL)
	{
		g = (StudentPosition)malloc(sizeof(Student));
		if (g == NULL)
		{
			printf("\nAlokacija neuspjesna!\n");
			return 1;
		}

		strcpy(g->firstName, s->firstName);
		strcpy(g->lastName, s->lastName);
		g->total = s->total;
		g->totalEcts = s->totalEcts;

		i = preslikavanje(s->lastName, H->vel);
		g->next = H->hashListe[i]->next;
		H->hashListe[i]->next = g;


		s = s->next;
	}


	return 0;
}

int preslikavanje(char *prez, int n)
{
	int i;
	int kljuc = 0;

	for (i = 0; i < 3; i++)
	{
		kljuc += (int)(prez[0] + prez[1] + prez[2]);
	}


	return (kljuc%n);
}

int ispisi_tablicu(hashTab H)
{
	int i;


	for (i = 0; i < H->vel; i++)
	{
		printf("%s %s %d %d\n", H->hashListe[i]->firstName, H->hashListe[i]->lastName, H->hashListe[i]->total, H->hashListe[i]->totalEcts);

	}




	return 0;
}
