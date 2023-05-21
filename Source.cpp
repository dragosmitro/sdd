#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <malloc.h>
#include <cstdio>
#include <stdlib.h>

struct Magazin {
	int id;
	char* denumire;
	char* localitate;
	float suprafata;
	int numar_angajati;
};

struct Nod {
	Magazin* mgz;
	Nod* next;
};

Nod* inserareTabelaDispersie(Nod** tabela, Magazin mgz, int poz, int null)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));

	nod->mgz = (Magazin*)malloc(sizeof(Magazin));
	nod->mgz->id = mgz.id;
	nod->mgz->denumire = (char*)malloc(sizeof(mgz.denumire) + 1);
	strcpy(nod->mgz->denumire, mgz.denumire);
	nod->mgz->localitate = (char*)malloc(sizeof(mgz.localitate) + 1);
	strcpy(nod->mgz->localitate, mgz.localitate);
	nod->mgz->suprafata = mgz.suprafata;
	nod->mgz->numar_angajati = mgz.numar_angajati;
	nod->next = NULL;

	if (null == 1)
	{
		return nod;
	}

	if (null == 0)
	{
		nod->next = tabela[poz];
		return nod;
	}
}

int pozitieTabela(const char* localitate)
{
	unsigned char suma = 0;
	for (int i = 0; i < strlen(localitate); i++)
	{
		suma += localitate[i];
	}
	return suma % 4;
}

float nrMediuAngajati(const char* localitate, Nod* lista)
{
	int nrAngajati = 0;
	int nrMagazineLocalitate = 0;
	while (lista != NULL)
	{
		if (strcmp(lista->mgz->localitate, localitate) == 0)
		{
			nrAngajati += lista->mgz->numar_angajati;
			nrMagazineLocalitate++;
		}
		lista = lista->next;
	}
	return (float)nrAngajati / nrMagazineLocalitate;
}

int schimbareDenumire(const char* denumireVeche, const char* localitate, const char* denumireNoua, Nod* lista)
{
	while (lista != NULL)
	{
		if (strcmp(lista->mgz->denumire, denumireVeche) == 0 && strcmp(lista->mgz->localitate, localitate) == 0)
		{
			free(lista->mgz->denumire);
			lista->mgz->denumire = (char*)malloc(sizeof(denumireNoua) + 1);
			strcpy(lista->mgz->denumire, denumireNoua);
			return 0;
		}
		lista = lista->next;
	}
	return 1;
}

void parcurgereLista(Nod* lista)
{
	while (lista != NULL)
	{
		printf("id = %d, denumire = %s, localitate = %s, suprafata = %f, numar_angajati = %d\n",
			lista->mgz->id, lista->mgz->denumire, lista->mgz->localitate, lista->mgz->suprafata, lista->mgz->numar_angajati);
		lista = lista->next;
	}
}

void parcurgereTabela(Nod** tabela)
{
	for (int i = 0; i < 4; i++)
	{
		printf("\nPozitia %d din tabela\n", i);
		parcurgereLista(tabela[i]);
		printf("\n");
	}
}

Nod* inserareNodLista(Nod* lista, Magazin &mgz)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	Nod* startLista = lista;

	nod->mgz = &mgz;
	nod->next = NULL;

	if (lista == NULL)
	{
		return nod;
	}

	if (lista->mgz->id > mgz.id)
	{
		nod->next = lista;
		return nod;
	}

	Nod* precedent = NULL;
	while (lista != NULL)
	{
		if (lista->mgz->id > nod->mgz->id)
		{
			nod->next = lista;
			precedent->next = nod;
			return startLista;
		}
		precedent = lista;
		lista = lista->next;
	}

	precedent->next = nod;

	return startLista;
}

void dezalocareLista(Nod* lista)
{
	Nod* tmp;

	while (lista != NULL)
	{
		tmp = lista;
		lista = lista->next;
		free(tmp);
	}
}

void dezalocareTabela(Nod** tabela)
{
	for (int i = 0; i < 4; i++)
	{
		dezalocareLista(tabela[i]);
	}
	free(tabela);
}

int main()
{
	FILE* f = fopen("magazine.txt", "r");
	char buffer[256], seps[] = ",\n";
	Nod* listaNoduri = NULL;

	while (fgets(buffer, 256, f))
	{
		Magazin *m = (Magazin*)malloc(sizeof(Magazin));
		m->denumire = NULL;
		m->localitate = NULL;

		char* token;
		token = strtok(buffer, seps);
		m->id = atoi(token);

		token = strtok(NULL, seps);
		m->denumire = (char*)malloc(sizeof(token) + 1);
		strcpy(m->denumire, token);

		token = strtok(NULL, seps);
		m->localitate = (char*)malloc(sizeof(token) + 1);
		strcpy(m->localitate, token);

		token = strtok(NULL, seps);
		m->suprafata = atof(token);

		token = strtok(NULL, seps);
		m->numar_angajati = atoi(token);

		listaNoduri = inserareNodLista(listaNoduri, *m);
	}
	fclose(f);

	parcurgereLista(listaNoduri);

	int test;
	test = schimbareDenumire("Selgross", "Insuratei", "Selgros Cash&Carry", listaNoduri);
	if (test == 1)
	{
		printf("\nNu a fost facuta nici o schimbare asupra listei!\n");
	}
	else
	{
		printf("\n");
		parcurgereLista(listaNoduri);
	}

	float nrMediu = nrMediuAngajati("Insuratei", listaNoduri);
	printf("\nIn localitatea specificata exista %f angajati\n", nrMediu);

	Nod** tabelaDispersie = (Nod**)malloc(4 * sizeof(Nod**));
	for (int i = 0; i < 4; i++)
	{
		tabelaDispersie[i] = NULL;
	}

	Nod* lista = listaNoduri;
	while (listaNoduri != NULL)
	{
		int pozitie = pozitieTabela(listaNoduri->mgz->localitate);

		if (tabelaDispersie[pozitie] == NULL)
		{
			tabelaDispersie[pozitie] =
				inserareTabelaDispersie(tabelaDispersie, *listaNoduri->mgz, pozitie, 1);
		}
		else
		{
			if (pozitie != 0)
			{
				pozitie--;
			}
			tabelaDispersie[pozitie] =
				inserareTabelaDispersie(tabelaDispersie, *listaNoduri->mgz, pozitie, 0);
		}
		printf("%d", pozitie);
		listaNoduri = listaNoduri->next;
	}

	parcurgereTabela(tabelaDispersie);

	dezalocareLista(lista);
	dezalocareTabela(tabelaDispersie);
	scanf("");
	return 0;
}