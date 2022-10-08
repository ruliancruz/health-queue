#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#define LENGTH 101

// Tudo que tem inicial "L", se refere a lista (list)
// Tudo que tem inicial "Q", se refere a fila (queue)

int length;
int lastId = 0;
int lastIdPatient = 0;
typedef struct LCellule *LPointer;
typedef struct QCellule *QPointer;

typedef struct
{
	int id;
	char rg[LENGTH];
	char name[LENGTH];
	char address[LENGTH];
	int age;
	char risk[LENGTH];
} Patient;

typedef struct
{
	QPointer front;
	QPointer back;
} Queue;

typedef struct
{
	int id;
	char cnpj[LENGTH];
	char name[LENGTH];
	char address[LENGTH];
	Queue patientQueue;
} Hospital;

typedef struct LCellule
{
	Hospital item;
	LPointer next;
} LCellule;

typedef struct QCellule
{
	Patient item;
	QPointer next;
} QCellule;

typedef struct
{
	LPointer first, last;
} List;

void makeEmptyList(List *list);
void makeEmptyQueue(Queue *queue);
void insertItem(List *list, Hospital item);
void removeItem(LPointer auxiliary, List *list, Hospital *item);
void enqueueItem(Queue *queue, Patient item);
void dequeueItem(Queue *queue, Patient *item);
bool LIsEmpty(List list);
bool QIsEmpty(Queue queue);
void printList(List list);
void printQueue(Queue queue, int idHospital);
Hospital FSearchHospital(List list, int id); // Procura hospital com esse id na lista
void userMenu(void); // "void function(void)" eh diferente de "void function()"
Hospital FRegisterHospital(Hospital *Hospital);
Patient FRegisterPatient(Patient *patient);
// "F" de "function", como prefixo, para evitar conflitos com as constantes da enumeracao
void FShowHospitals(void);
void FShowPatients(void);
void FAttendPatient(Hospital *hospital, Patient *item);

enum USER_MENU
{
	registerHospital = 1,
	registerPatient,
	showHospitals,
	showPatients,
	attendPatient,
	quit
} option;

int main(int argc, char **argv)
{
	List list;
	Queue queue;
	Patient patient;
	Hospital hospital;
	Hospital *hospitalPointer;
	LPointer Aux;
	int auxiliary = 0;

	makeEmptyList(&list);
	makeEmptyQueue(&queue);

	do
	{
    	userMenu();
    	printf("Opcao: ");
    	scanf("%d", &auxiliary);

		// Armazenar na variavel "option" diretamente pelo "scanf", gera um aviso
    	option = auxiliary;
    	puts("");

    	switch(option)
    	{
        	case registerHospital:
            	fflush(stdin);
            	hospital = FRegisterHospital(&hospital);
            	insertItem(&list, hospital);
            	break;
        	case registerPatient:
            	fflush(stdin);

            	if(LIsEmpty(list))
                	puts("Nao existem hospitais cadastrados.\n\n");
            	else
            	{
                	printList(list);
                	printf("Digite o id do hospital no qual deseja cadastrar o paciente: ");
                	scanf("%d", &auxiliary);

                	Aux = list.first->next;

                	while (Aux != NULL)
                	{
                    	if(Aux->item.id >= auxiliary)
                    	{
                        	if(Aux->item.id == auxiliary)
                        	{
                            	hospitalPointer = &Aux->item;
                            	break;
                        	}
                        	else
                        	{
                            	auxiliary = -1;
                            	break;
                        	}
                    	}
                    	else
                        	Aux = Aux->next;
                	}

                	if(Aux == NULL)
                    	auxiliary = -1;

                	if(auxiliary != -1)
                	{
                    	patient = FRegisterPatient(&patient);
                    	enqueueItem(&hospitalPointer->patientQueue, patient);
                	}
                	else
                    	puts("\nNao existe nenhum hospital com esse Id.\n");
            	}

            	break;
        	case showHospitals:
            	printList(list);
            	break;
        	case showPatients:
        		if(LIsEmpty(list))
                	puts("Nao existem hospitais e nem pacientes cadastrados.\n\n");
            	else
            	{
            		printList(list);
            		printf("Digite o Id do hospital o qual deseja consultar a fila de pacientes: ");
            		scanf("%d", &auxiliary);
            		hospital = FSearchHospital(list, auxiliary);
            		printQueue(hospital.patientQueue, hospital.id);
            	}

            	break;
        	case attendPatient:
        		if(LIsEmpty(list))
                	puts("Nao existem hospitais e nem pacientes cadastrados.\n\n");
            	else
            	{
            		fflush(stdin);
            		printList(list);
                	printf("Digite o id do hospital no qual deseja atender um paciente da fila: ");
                	scanf("%d", &auxiliary);

                	Aux = list.first->next;

                	while (Aux != NULL)
                	{
                    	if(Aux->item.id >= auxiliary)
                    	{
                        	if(Aux->item.id == auxiliary)
                        	{
                            	hospitalPointer = &Aux->item;
                            	break;
                        	}
                        	else
                        	{
                            	auxiliary = -1;
                            	break;
                        	}
                    	}
                    	else
                        	Aux = Aux->next;
                	}

                	if(Aux == NULL) {
                    	auxiliary = -1;
					}

                	if(auxiliary != -1)
                	{
                    	dequeueItem(&hospitalPointer->patientQueue, &hospitalPointer->patientQueue.front->next->item);
                	}
                	else
                    	puts("\nNao existe nenhum hospital com esse id.\n");
            	}
            	break;
        	case quit:
            	puts("Saindo...");
            	sleep(1);
            	system("cls");
            	return EXIT_SUCCESS;
        	default:
				system("cls");
            	puts("Erro: opcao invalida!");
			return EXIT_FAILURE;
    	}
	} while(option != quit);

	return EXIT_SUCCESS;
}

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
    	puts("Erro: lista vazia ou posicao nao existe");
    	return; // so para sair da funcao
	}

	target = auxiliary->next;
	*item = target->item;
	auxiliary->next = target->next;

	if(auxiliary->next == NULL)
    	list->last = auxiliary;

	free(target);
}

void enqueueItem(Queue *queue, Patient item)
{
	QPointer Aux;

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
	puts("Hospitais Cadastrados\n");
	LPointer Aux;
	Aux = list.first->next;

	while (Aux != NULL)
	{
    	printf("Id %d\n", Aux->item.id);
    	printf("Nome: %s", Aux->item.name);
    	printf("Endereco: %s", Aux->item.address);
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
    	printf("Endereco: %s", Aux->item.address);
    	printf("Risco: %s", Aux->item.risk);
    	printf("RG: %s\n", Aux->item.rg);
    	Aux = Aux->next;
    	counter++;
	}

	puts("");
}


void userMenu()
{
	puts("O que voce deseja fazer?\n\n"\
     	"\t[1] - Cadastrar hospital\n"\
     	"\t[2] - Cadastrar paciente\n"\
     	"\t[3] - Mostrar hospitais\n"\
     	"\t[4] - Mostrar pacientes\n"\
     	"\t[5] - Atender paciente\n"\
     	"\t[6] - Sair\n");
}

Patient FRegisterPatient(Patient *patient)
{
	patient->id = lastId;
	lastId++;

	fflush(stdin);
	printf("Nome: ");
	fgets(patient->name, LENGTH, stdin);
	// Remove o caractere de nova linha "\n" armazenado com a string
	length = strlen(patient->name);
	patient->name[length] = '\0';

	printf("Idade: ");
	scanf("%d", &patient->age);

	fflush(stdin);
	printf("Endereco: ");
	fgets(patient->address, LENGTH, stdin);
	length = strlen(patient->address);
	patient->address[length] = '\0';

	fflush(stdin);
	printf("Risco: ");
	fgets(patient->risk, LENGTH, stdin);
	length = strlen(patient->risk);
	patient->risk[length] = '\0';

	fflush(stdin);
	printf("RG: ");
	fgets(patient->rg, LENGTH, stdin);
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
            	return Aux->item;
        	else
            	return hospital;
    	}
    	else
        	Aux = Aux->next;
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
            	return Aux->item;
        	else
            	return patient;
    	}
    	else
        	Aux = Aux->next;
	}

	return patient;
}

Hospital FRegisterHospital(Hospital *hospital)
{
	hospital->id = lastIdPatient;
	lastIdPatient++;

	makeEmptyQueue(&hospital->patientQueue);

	printf("Nome: ");
	fgets(hospital->name, LENGTH, stdin);
	length = strlen(hospital->name);
	hospital->name[length] = '\0';

	printf("Endereco: ");
	fgets(hospital->address, LENGTH, stdin);
	length = strlen(hospital->address);
	hospital->address[length] = '\0';

	printf("CNPJ: ");
	fgets(hospital->cnpj, LENGTH, stdin);
	length = strlen(hospital->cnpj);
	hospital->cnpj[length] = '\0';
	puts("");

	return *hospital;
}
