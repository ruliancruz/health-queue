#include "HealthQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// variáveis globais
int length;
int lastId = 0;
int lastIdPatient = 0;

// ajustes de portabilidade
#ifdef _WIN32 // windows x64/x86
	#include <locale.h>
	#include <windows.h>

	setlocale(LC_ALL, "Portuguese");

	void clearScreen()
	{
		system("cls");
	}

	void clearBuffer()
	{
		fflush(stdin);
	}
#else // linux/mac
	#include <stdio_ext.h>
	#include <unistd.h>

	void clearScreen()
	{
		system("clear");
	}
	
	void clearBuffer()
	{
		__fpurge(stdin);
	}
#endif

void makeEmptyList(List *list)
{
	/* Existe mais uma celula, para evitar comparacoes na insercao, aumentando a performance */
	list->first = (LPointer) malloc(sizeof(LCellule));
	list->last = list->first;
	list->first->next = NULL;
}

void makeEmptyQueue(Queue *queue)
{
	/* Existe mais uma celula, para evitar comparacoes no enfileiramento, aumentando a performance */
	queue->front = (QPointer) malloc(sizeof(QCellule));
	queue->back = queue->front;
	queue->front->next = NULL;
}

void insertItem(List *list, Hospital item)
{
	list->last->next = (LPointer) malloc(sizeof(LCellule));
	list->last = list->last->next;
	list->last->item = item;
	list->last->next = NULL;
}

void removeItem(LPointer auxiliary, List *list, Hospital *item)
{
	// O item a ser removido eh o seguinte ao apontado por "auxiliary"
	LPointer target;

	if(LIsEmpty(*list) || auxiliary == NULL || auxiliary->next == NULL)
	{
    	puts("Erro: lista vazia ou posição não existe");
    	return; // so para sair da funcao
	}

	target = auxiliary->next;
	*item = target->item;
	auxiliary->next = target->next;

	if(auxiliary->next == NULL)
	{
    	list->last = auxiliary;
	}

	free(target);
}

void enqueueItem(Queue *queue, Patient item)
{
	queue->back->next = (QPointer) malloc(sizeof(QCellule));
	queue->back = queue->back->next;
	queue->back->item = item;
	queue->back->next = NULL;
}

void dequeueItem(Queue *queue, Patient *item)
{
	QPointer target;

	if (QIsEmpty(*queue))
	{
    	puts("Erro: fila vazia");
    	return;
	}

	target = queue->front;
	queue->front = queue->front->next;
	*item = queue->front->item;
	free(target);
}

bool LIsEmpty(List list)
{
	return (list.first == list.last);
}

bool QIsEmpty(Queue queue)
{
	return (queue.front == queue.back);
}

void printList(List list)
{
	printf("Hospitais Cadastrados\n");
	LPointer Aux;
	Aux = list.first->next;

	while (Aux != NULL)
	{
    	printf("Id %d\n", Aux->item.id);
    	printf("Nome: %s\n", Aux->item.name);
    	printf("Endereço: %s\n", Aux->item.address);
    	printf("CNPJ: %s\n", Aux->item.cnpj);
    	Aux = Aux->next;
	}
}

void printQueue(Queue queue, int idHospital)
{
	QPointer Aux;
	Aux = queue.front->next;
	int counter = 0;
	printf("\nPacientes do Hospital %d\n\n", idHospital);

	while (Aux != NULL)
	{
    	printf("Paciente %d\n", counter);
    	printf("Nome: %s", Aux->item.name);
    	printf("Idade: %d\n", Aux->item.age);
    	printf("Endereço: %s", Aux->item.address);
    	printf("Risco: %s", Aux->item.risk);
    	printf("RG: %s\n", Aux->item.rg);
    	Aux = Aux->next;
    	counter++;
	}

	printf("\n");
}

void userMenu()
{
	printf("O que você deseja fazer?\n\n"\
     	   "\t[1] - Cadastrar hospital\n"\
     	   "\t[2] - Cadastrar paciente\n"\
     	   "\t[3] - Mostrar hospitais\n"\
     	   "\t[4] - Mostrar pacientes\n"\
     	   "\t[5] - Atender paciente\n"\
     	   "\t[6] - Sair\n\n");
}

Patient FRegisterPatient(Patient *patient)
{
	patient->id = lastId;
	lastId++;

	clearBuffer();
	printf("Nome: ");
	fgets(patient->name, BUF_SIZE, stdin);
	// Remove o caractere de nova linha "\n" armazenado com a string
	length = strlen(patient->name);
	patient->name[length] = '\0';

	printf("Idade: ");
	scanf("%d", &patient->age);

	clearBuffer();
	printf("Endereço: ");
	fgets(patient->address, BUF_SIZE, stdin);
	length = strlen(patient->address);
	patient->address[length] = '\0';

	clearBuffer();
	printf("Risco: ");
	fgets(patient->risk, BUF_SIZE, stdin);
	length = strlen(patient->risk);
	patient->risk[length] = '\0';

	clearBuffer();
	printf("RG: ");
	fgets(patient->rg, BUF_SIZE, stdin);
	length = strlen(patient->rg);
	patient->rg[length] = '\0';
	puts("");

	return *patient;
}

Hospital FSearchHospital(List list, int id)
{
	LPointer Aux;
	Hospital hospital;

	Aux = list.first->next;
	hospital.id = -1;

	while (Aux != NULL)
	{
    	if(Aux->item.id >= id)
		{
        	if(Aux->item.id == id)
			{
            	return Aux->item;
			}
			else
			{
            	return hospital;
			}
    	}
		else
		{
        	Aux = Aux->next;
		}
	}

	return hospital;
}

Patient FSearchPatient(Hospital hospital, int id)
{
	QPointer Aux;
	Patient patient;

	Aux = hospital.patientQueue.front->next;
	patient.id = -1;

	while (Aux != NULL)
	{
    	if(Aux->item.id >= id)
		{
        	if(Aux->item.id == id)
			{
            	return Aux->item;
			}
			else
			{
            	return patient;
			}
    	}
		else
		{
        	Aux = Aux->next;
		}
	}

	return patient;
}

Hospital FRegisterHospital(Hospital *hospital)
{
	hospital->id = lastIdPatient;
	lastIdPatient++;

	makeEmptyQueue(&hospital->patientQueue);

	printf("Nome: ");
	fgets(hospital->name, BUF_SIZE, stdin);
	length = strlen(hospital->name);
	hospital->name[length] = '\0';

	printf("Endereço: ");
	fgets(hospital->address, BUF_SIZE, stdin);
	length = strlen(hospital->address);
	hospital->address[length] = '\0';

	printf("CNPJ: ");
	fgets(hospital->cnpj, BUF_SIZE, stdin);
	length = strlen(hospital->cnpj);
	hospital->cnpj[length] = '\0';
	printf("\n");

	return *hospital;
}