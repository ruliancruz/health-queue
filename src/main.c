#include "libs/HealthQueue/HealthQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	List list;
	Queue queue;
	Patient patient;
	Hospital hospital;
	Hospital *hospitalPointer;
	LPointer Aux;
	int auxiliary = 0;
	int option;

	makeEmptyList(&list);
	makeEmptyQueue(&queue);

	do 
	{
    	userMenu();

    	printf("Opcao: ");
    	scanf("%d", &option);
    	printf("\n");

    	switch(option)
		{
        	case registerHospital:
            	clearBuffer();
            	hospital = FRegisterHospital(&hospital);
            	insertItem(&list, hospital);
            	break;
        	case registerPatient:
            	clearBuffer();

            	if(LIsEmpty(list))
				{
                	printf("Não existem hospitais cadastrados.\n\n");
				}
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
						{
                        	Aux = Aux->next;
						}
                	}

                	if(Aux == NULL)
					{
                    	auxiliary = -1;
					}

                	if(auxiliary != -1)
					{
                    	patient = FRegisterPatient(&patient);
                    	enqueueItem(&hospitalPointer->patientQueue, patient);
                	}
					else
					{
                    	printf("\nNão existe nenhum hospital com esse Id.\n");
					}
            	}

            	break;
        	case showHospitals:
            	printList(list);
            	break;
        	case showPatients:
        		if(LIsEmpty(list))
				{
                	puts("Não existem hospitais e nem pacientes cadastrados.\n\n");
				}
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
				{
                	printf("Não existem hospitais e nem pacientes cadastrados.\n\n");
				}
				else
				{
            		clearBuffer();
            		printList(list);

                	printf("Digite o id do hospital no qual deseja atender um paciente da fila: ");
                	scanf("%d", &auxiliary);

                	Aux = list.first->next;

                	while (Aux != NULL) {
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
						{
                        	Aux = Aux->next;
						}
                	}

                	if(Aux == NULL)
					{
                    	auxiliary = -1;
					}

                	if(auxiliary != -1)
					{
                    	dequeueItem(&hospitalPointer->patientQueue, &hospitalPointer->patientQueue.front->next->item);
                	}
					else
					{
                    	puts("\nNão existe nenhum hospital com esse id.\n");
					}
            	}

            	break;
        	case quit:
				printf("Saindo...\n");
            	sleep(1);
            	clearScreen();

            	return EXIT_SUCCESS;
        	default:
				clearScreen();
            	puts("Erro: opcão inválida!");
			return EXIT_FAILURE;
    	}
	} while(option != quit);

	return EXIT_SUCCESS;
}