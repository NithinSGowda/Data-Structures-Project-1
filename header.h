typedef struct people{
    int time;
    int priority;
    struct people *next;
}person;

typedef struct TERMINAL{
    int maxCapacity;
    int curStatus;
    unsigned int functional;
    int terminalNumber;
    person *q;
    int waitingTime;
    struct TERMINAL *next;
}terminal;



terminal* createTerminals(int,int);
terminal* beginner();
person* addPersonToQueue(person *,int);
terminal* initialisePrompt(terminal*);
terminal* initialise(terminal*);
void displayQueues(terminal*);
void actualSimulation(terminal*);