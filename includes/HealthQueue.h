#ifndef HEALTH_QUEUE_H
    #define HEALTH_QUEUE_H

    #include <stdbool.h> // "bool", "true" e "false"
    #define BUF_SIZE 101

    // Tudo que tem inicial "L", se refere a lista (list)
    // Tudo que tem inicial "Q", se refere a fila (queue)

    typedef struct LCellule *LPointer;
    typedef struct QCellule *QPointer;
    
    typedef struct
    {
        int id;
        char rg[BUF_SIZE];
        char name[BUF_SIZE];
        char address[BUF_SIZE];
        int age;
        char risk[BUF_SIZE];
    } Patient;

    typedef struct
    {
        QPointer front;
        QPointer back;
    } Queue;

    typedef struct 
    {
        int id;
        char cnpj[BUF_SIZE];
        char name[BUF_SIZE];
        char address[BUF_SIZE];
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

    void clearScreen();
    void clearBuffer();
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
    void userMenu();
    // "F" de "function", como prefixo, para evitar conflitos com as constantes da enumeracao
    Hospital FRegisterHospital(Hospital *Hospital);
    Patient FRegisterPatient(Patient *patient);

    enum USER_MENU
    {
        registerHospital = 1,
        registerPatient,
        showHospitals,
        showPatients,
        attendPatient,
        quit
    };
#endif // HEALTH_QUEUE_H