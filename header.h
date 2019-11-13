typedef struct QUEUE{
    int *person;
    int queueSize;
    int waitingTime;
}queue;

typedef struct TERMINAL{
    int maxCapacity;
    int curStatus;
    unsigned int functional;
    int terminalNumber;
    queue q;
    struct TERMINAL *next;
}terminal;

typedef struct people{
    int time;
    int priority;
    struct people *next;
}person;

terminal* createTerminals(int,int);
terminal* beginner();
person* addPersonToQueue(person *,int);
terminal* initialisePrompt(terminal*);
terminal* initialise(terminal*);

