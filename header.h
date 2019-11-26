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
void updatewaitingTime(terminal*);
terminal* beginner();
terminal* initialisePrompt(terminal*);
terminal* initialise(terminal*);
terminal* displayQueues(terminal*);
terminal* searchFastestTerminal(terminal*);
void actualSimulation(terminal*);

//Queue Functions
person* newPerson(int, int);
int peek(person**);
int pop(person**);
person* addPersonToQueue(person*, int, int,int*); 
int isEmpty(person**); 
