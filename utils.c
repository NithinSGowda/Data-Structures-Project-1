#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "header.h"
extern int totalPeople;
extern char inputString[20];


terminal* createTerminals(int i,int sizeOfTerminal)
{
    terminal *temp=(terminal *)malloc(sizeof(terminal));
    if(temp==NULL){
        printf("Memory Allocation of terminal %d failed\n",i);
        exit(10);
    }
    if(sizeOfTerminal<1){
        printf("Sorry you have entered the wrong input for size of terminals\nMaking max size as 1\n");
        sizeOfTerminal=1;
    }
    temp->maxCapacity=sizeOfTerminal;           //initialisation of terminal metadata to default values
    temp->curStatus=0;
    temp->functional=0;
    temp->terminalNumber=i;
    temp->q=NULL;
    temp->waitingTime=0;        //moves to the next terminal
    temp->next=NULL;            //last terminal's next will be NULL
    return temp;                //returns the newly created terminal list's head pointer
}

void updateWaitingTime(terminal *head)
{
    terminal *temp=head;
    person *tempQ;
    while(temp!=NULL)       //loops over all the terminals
    {
        tempQ=temp->q;
        temp->waitingTime=0;
        temp->curStatus=0;
        while(tempQ!=NULL)          
        {
            temp->waitingTime+=tempQ->time;
            temp->curStatus++;
            printf("%d(%d) ",tempQ->time,tempQ->priority);            //adds waiting time of all people
            tempQ=tempQ->next;
        }
        printf("\n");
        temp=temp->next;
    }
}

terminal* beginner()
{
    system("@cls||clear");
    printf("Welcome to Airport Check-in terminal simulator\n\n");
    printf("Press ENTER to start\n");
    getchar();
    system("@cls||clear");          //clears the terminal screen

    char tempString[30];
    int numOfTerminals,sizeOfTerminal;
    printf("Enter number of terminals to create : ");
    scanf("%s",tempString);
    numOfTerminals=atoi(tempString);
    printf("Enter max size for a queue at terminal : ");
    scanf("%s",tempString);
    sizeOfTerminal=atoi(tempString);
    int i=1;
    terminal* head=NULL;
    head=createTerminals(i,sizeOfTerminal);
    i++;
    terminal* temp=head;
    if(numOfTerminals<1){
        printf("Sorry you have entered the wrong input for number of terminals\nCreating a terminal for you\n");
        numOfTerminals=1;
    }
    while(i<=numOfTerminals)
    {
        temp->next=createTerminals(i,sizeOfTerminal);
        temp=temp->next;
        i++;
    }
    return head;          //This is returned to the main function
}

terminal* initialise(terminal *head)
{
    terminal* temp=head;
    int i,j=1,wTime;
    while(temp!=NULL)         //lops over all the terminals
    {
        srand(time(NULL)+rand());           //to set a random seed value for 
        i=1;
        temp->q=addPersonToQueue(temp->q,(rand()%10)+1,(rand()%4)+1,&wTime); 
        temp->functional=1;
        temp->curStatus++;
        i++;
        while(i<(rand()%temp->maxCapacity))           //loops random number of times to add random number of people to the queue
        {
            temp->q=addPersonToQueue(temp->q,(rand()%10)+1,(rand()%4)+1,&wTime);  
            temp->curStatus++;          //increments terminal's metadata
            i++;
        }
        temp=temp->next;    //moves on to next terminal
        j++;
    }
    printf("\nInitialisation successful\n");
    //updateWaitingTime(head);
    return head;
}



terminal* initialisePrompt(terminal *head)
{
    char c;
    printf("\nDo you want to initialise the terminals with test passengers[y/n] : ");
    scanf(" %c",&c);
    if(c=='y')
        return initialise(head);
    else
        return head;
}

terminal* displayQueues(terminal *head)
{
    terminal *temp=head;
    updateWaitingTime(head);
    printf("\n");
    while(temp!=NULL)
    {
        printf("Terminal number : %d\n",temp->terminalNumber);
        printf("Total number of people in the queue are %d\n",temp->curStatus);
        printf("Estimated waiting time is %d minutes\n\n",temp->waitingTime);        
        temp=temp->next;
    }
    return head;
}


terminal* searchFastestTerminal(terminal *head)
{
    terminal *temp=head,*temp1=head;
    terminal *minTerminal=head;
    int minWaitingTime=head->waitingTime;
    int foundTerminal=0;
    while(temp!=NULL)
    {
        temp1=temp;
        if(temp->curStatus < temp->maxCapacity)
        {
            if(temp->waitingTime <=  minWaitingTime)
            {
                minWaitingTime=temp->waitingTime;
                minTerminal=temp;
                foundTerminal=1;
            }
        }
        temp=temp->next;
    }
    if(foundTerminal==0)
    {
        printf("\n\nAll terminals are full\n");
        printf("Creating a new terminal number %d for you ...\n",temp1->terminalNumber+1);
        temp1->next=createTerminals(temp1->terminalNumber+1,temp1->maxCapacity);
        temp1=temp1->next;
        minTerminal=temp1;
    }
    return minTerminal;
}


void actualSimulation(terminal *head)
{
    int inputNumber;
    int choice,wTime;
    terminal *tempTerminal=head;
    terminal *allocatedTerminal=NULL;
    int Time=-1;
    printf("\n1] Add a person\n2] fast forward time\n3] Quit\n\n Enter your choice [1/2/3] : ");
    scanf("%s",inputString);
    choice=atoi(inputString);
    // while()
    if(choice==1){
        printf("Enter the person detail [ VIP(0) / pregnant_women(1) / old(2) / handicapped(3) / normal(4 or any other number)] : ");
        scanf("%s",inputString);
        inputNumber=atoi(inputString);
        srand(time(NULL)+rand());
        allocatedTerminal=searchFastestTerminal(head);
        Time=rand()%10+1;
        switch (inputNumber)
        {
            case 0 :
                allocatedTerminal->q = addPersonToQueue(allocatedTerminal->q,Time,0,&wTime);
                break;
            case 1 :
                allocatedTerminal->q = addPersonToQueue(allocatedTerminal->q,Time,1,&wTime);
                break;
            case 2 :
                allocatedTerminal->q = addPersonToQueue(allocatedTerminal->q,Time,2,&wTime);
                break;
            case 3 :
                allocatedTerminal->q = addPersonToQueue(allocatedTerminal->q,Time,3,&wTime);
                break;
            default :
                allocatedTerminal->q = addPersonToQueue(allocatedTerminal->q,Time,inputNumber,&wTime);
                break;
        }
        printf("\nPerson added to terminal number %d.\nPlease ask the person to go to terminal terminal %d\nHis/her waiting time is %d minutes.\n\n\n",allocatedTerminal->terminalNumber,allocatedTerminal->terminalNumber,wTime);
        //printf("(Added person with time %d and priority %d)\n\n",tempPerson->time,tempPerson->priority);
        displayQueues(head);
    }
    else if(choice==2){
        int time,removedTime=0;
        printf("Enter the amount of time to fast forward [in mins] : ");
        scanf(" %s",inputString);
        time=atoi(inputString);
        tempTerminal=head;
        while(tempTerminal!=NULL)
        {
            if(tempTerminal->waitingTime!=0)
            {
            removedTime=0;
            while(!isEmpty(&tempTerminal->q) && (removedTime+peek(&tempTerminal->q))<time)
            {
                removedTime+=pop(&tempTerminal->q);
            }
            if(removedTime<time && !isEmpty(&tempTerminal->q))
            tempTerminal->q->time-=time-removedTime;
            /*tempTerminal->q->time=time-removedTime;
            tempTerminal->curStatus-=removedPeople;
            tempTerminal->waitingTime-=time;*/
            }
            tempTerminal=tempTerminal->next;
        }
        displayQueues(head);
    }
    else{
        terminal *temp;
        person *tempq;
        while(head!=NULL)
        {
            while(head->q!=NULL)
            {
                tempq=head->q->next;
                free(head->q);
                head->q=tempq;
            }
            temp=head->next;
            free(head);
            head=temp;
        }
        printf("\n\nTotal people handled today : %d\n",totalPeople);
        printf("Thanks for using out terminal simulator\n\n");
        exit(0);
    }
    
}
