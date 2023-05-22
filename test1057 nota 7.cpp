#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <malloc.h>
#include <cstdio>
#include <stdlib.h>

#define DIMENSIUNE_TABELA 3

struct Comanda {
	unsigned int id;
	char* dataComanda;
	char* dataLivrare;
	char* numeClient;
	float suma;
};

struct Nod {
	Comanda* cmd;
	Nod* next;
};

void parcurgereLista(Nod* lst)
{
	while (lst != NULL)
	{
		printf("id= %d, dataComanda = %s, dataLivrare = %s, numeClient = %s, suma = %f\n",
			lst->cmd->id, lst->cmd->dataComanda, lst->cmd->dataLivrare, lst->cmd->numeClient, lst->cmd->suma);
		lst = lst->next;
	}
}

int pozitie(const char* numeClient)
{
	unsigned char suma = 0;
	for (int i = 0; i < strlen(numeClient); i++)
	{
		suma += numeClient[i];
	}
	return suma % DIMENSIUNE_TABELA;
}

void inserareTabela(Comanda &cmd, Nod** tabela)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	int poz = pozitie(cmd.numeClient);

	nod->cmd = &cmd;
	nod->next = NULL;

	if (tabela[poz] == NULL)
	{
		tabela[poz] = nod;
	}
	else
	{
		nod->next = tabela[poz];
		tabela[poz] = nod;
	}
}

void parcurgereTabela(Nod** tabela)
{
	for (int i = 0; i < DIMENSIUNE_TABELA; i++)
	{
		printf("Pozitia %d din tabela\n", i);
		parcurgereLista(tabela[i]);
	}
}

void main()
{
	Comanda* c1 = (Comanda*)malloc(sizeof(Comanda));
	c1->id = 1;
	c1->dataComanda = (char*)malloc(sizeof(strlen("24/04/2023")) + 1);
	strcpy(c1->dataComanda, "24/04/2023");
	c1->dataLivrare = (char*)malloc(sizeof(strlen("27/04/2023")) + 1);
	strcpy(c1->dataLivrare, "24/04/2023");
	c1->numeClient = (char*)malloc(sizeof(strlen("Popescu Darius")) + 1);
	strcpy(c1->numeClient, "Popescu Darius");
	c1->suma = 400.5;

	Comanda* c2 = (Comanda*)malloc(sizeof(Comanda));
	c2->id = 2;
	c2->dataComanda = (char*)malloc(sizeof(strlen("21/02/2023")) + 1);
	strcpy(c2->dataComanda, "21/02/2023");
	c2->dataLivrare = (char*)malloc(sizeof(strlen("23/02/2023")) + 1);
	strcpy(c2->dataLivrare, "23/02/2023");
	c2->numeClient = (char*)malloc(sizeof(strlen("Sergiu Milea")) + 1);
	strcpy(c2->numeClient, "Sergiu Milea");
	c2->suma = 213.2;

	Comanda* c3 = (Comanda*)malloc(sizeof(Comanda));
	c3->id = 3;
	c3->dataComanda = (char*)malloc(sizeof(strlen("01/01/2023")) + 1);
	strcpy(c3->dataComanda, "01/01/2023");
	c3->dataLivrare = (char*)malloc(sizeof(strlen("09/01/2023")) + 1);
	strcpy(c3->dataLivrare, "09/01/2023");
	c3->numeClient = (char*)malloc(sizeof(strlen("Mija Mondialu")) + 1);
	strcpy(c3->numeClient, "Mija Mondialu");
	c3->suma = 999.3;

	Comanda* c4 = (Comanda*)malloc(sizeof(Comanda));
	c4->id = 4;
	c4->dataComanda = (char*)malloc(sizeof(strlen("05/03/2022")) + 1);
	strcpy(c4->dataComanda, "05/03/2022");
	c4->dataLivrare = (char*)malloc(sizeof(strlen("09/03/2022")) + 1);
	strcpy(c4->dataLivrare, "09/03/2022");
	c4->numeClient = (char*)malloc(sizeof(strlen("Volkswagen Passat B8")) + 1);
	strcpy(c4->numeClient, "Volkswagen Passat B8");
	c4->suma = 470.1;

	Comanda* c5 = (Comanda*)malloc(sizeof(Comanda));
	c5->id = 5;
	c5->dataComanda = (char*)malloc(sizeof(strlen("13/12/2022")) + 1);
	strcpy(c5->dataComanda, "13/12/2022");
	c5->dataLivrare = (char*)malloc(sizeof(strlen("19/12/2022")) + 1);
	strcpy(c5->dataLivrare, "19/12/2022");
	c5->numeClient = (char*)malloc(sizeof(strlen("Andrei FCSB")) + 1);
	strcpy(c5->numeClient, "Andrei FCSB");
	c5->suma = 470.1;

	Nod** tabela = (Nod**)malloc(sizeof(Nod*));
	for (int i = 0; i < DIMENSIUNE_TABELA; i++)
	{
		tabela[i] = NULL;
	}

	inserareTabela(*c1, tabela);
	inserareTabela(*c2, tabela);
	inserareTabela(*c3, tabela);
	inserareTabela(*c4, tabela);
	inserareTabela(*c5, tabela);

	parcurgereTabela(tabela);

	scanf("");
}