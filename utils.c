#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "header.h"

terminal* createTerminals(int numOfTerminals,int sizeOfTerminal)
{
    terminal *head=(terminal *)malloc(sizeof(terminal));
    terminal *temp=head;
    int i=1;
    while(i<=numOfTerminals)
    {
        terminal *temp2=(terminal *)malloc(sizeof(terminal));
        temp->next=temp2;
        temp->maxCapacity=sizeOfTerminal;
        temp->curStatus=0;
        temp->functional=0;
        temp->terminalNumber=i;
        temp->waitingTime=0;
        temp=temp2;
        i++;
    }
    temp->next=NULL;
    return head;
}


terminal* beginner()
{
    printf("Welcome to Airport Check-in terminal simulator\n\n");
    printf("Press any to start\n");
    getchar();
    system("@cls||clear");

    char tempString[30];
    int numOfTerminals,sizeOfTerminal;
    printf("Enter number of terminals to create : ");
    scanf("%s",tempString);
    numOfTerminals=atoi(tempString);
    printf("Enter max size for a queue at terminal : ");
    scanf("%s",tempString);
    sizeOfTerminal=atoi(tempString);
    return createTerminals(numOfTerminals,sizeOfTerminal);
}

terminal* initialise(terminal *head)
{
    terminal *temp=head;
    int i;
    while(temp->next!=NULL)
    {
        i=0;
        srand(time(NULL)+rand());
        while(i<rand()%head->maxCapacity)
        {
            temp->q=addPersonToQueue(temp->q,(rand()%5));
            temp->curStatus++;
            temp->waitingTime+=(rand()%100)/10;
            i++;
        }
        temp=temp->next;
    }
    printf("\nInitialisation successful\n");
    return head;

}

/*person* addPersonToQueue(person *head,int priority)
{
    person *temp=head;
    person *tempPerson=malloc(sizeof(person)),*tempNext;
    srand(time(NULL)+rand());
    tempPerson->time=(rand()%100)/10;
    tempPerson->priority=priority;
    if(head==NULL)
    {
        tempPerson->next=NULL;
        return tempPerson;
    }
    while(temp->next!=NULL)
    {
        if(temp->next->priority>=priority)
        {
            
            tempNext=temp->next;
            temp->next=tempPerson;
            tempPerson->next=tempNext;
            return head;
        }
        temp=temp->next;
    }

    return head;
}*/

person* addPersonToQueue(person *head,int priority)
{
    //printf("Started addPersonToQueue\n\n");

    person *temp=head;
    person *tempPerson=(person *)malloc(sizeof(person)),*tempNext;
    srand(time(NULL)+rand());
    tempPerson->time=(rand()%100)/10;
    tempPerson->priority=priority;
    if(head==NULL)
    {
        tempPerson->next=NULL;
        //  printf("Ended addPersonToQueue 1\n\n");
        return tempPerson;
    }
    while(temp->next!=NULL)
    {
        if(temp->next->priority<priority)
        {
            temp=temp->next;
        }
        else
        {
            tempNext=temp->next;
            temp->next=tempPerson;
            tempPerson->next=tempNext;
            return head;
        }
    }
    
    //printf("Ended addPersonToQueue\n\n");

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

void displayQueues(terminal *head)
{
    terminal *temp=head;
    person *tempPerson;
    int totalTime=0;
    while(temp->next!=NULL)
    {
        tempPerson=temp->q;
        while(tempPerson->next!=NULL)
        {
            printf("%d  ",tempPerson->time);
            totalTime+=tempPerson->time;
            tempPerson=tempPerson->next;
        }
        printf("Terminal number : %d\n",temp->terminalNumber);
        printf("Total number of people in the queue are %d\n",temp->curStatus);
        printf("Estimated waiting time is %d\n\n",temp->waitingTime);
        temp=temp->next;
    }
}


void actualSimulation(terminal *head)
{
    char inputString;
    int choice;
    person *tempPerson;
    terminal *tempTerminal=head;
    printf("\n1] Add a person\n2] fast forward time\n\n Enter your choice [1/2] : ");
    scanf("  %d",&choice);
    if(choice==1){
        printf("Enter the person detail [ VIP(V) / pregnant_women(P) / old(O) / handicapped(H) / normal(N)]");
        scanf(" %c",inputString);

        switch (inputString)
            {
            case 'V' :
                tempPerson=addPersonToQueue(tempTerminal->q,1);
                break;
            case 'P' :
                tempPerson=addPersonToQueue(tempTerminal->q,2);
                break;
            case 'O' :
                tempPerson=addPersonToQueue(tempTerminal->q,4);
                break;
            case 'H' :
                tempPerson=addPersonToQueue(tempTerminal->q,3);
                break;
            default :
                tempPerson=addPersonToQueue(tempTerminal->q,5);
                break;
            }
    }
    else{
        int time;
        printf("Enter the amount of time to fast forward [in mins] : ");
        scanf(" %d",&time);
        while(tempTerminal->next!=NULL)
        {
            tempTerminal->waitingTime-=time;
            if(tempTerminal->waitingTime < 0){
                tempTerminal->waitingTime=0;
                tempTerminal->curStatus=0;
            }
            tempTerminal->curStatus-=((rand()%time)*2);
            if(tempTerminal->curStatus < 0)
                tempTerminal->curStatus=0;
            tempTerminal=tempTerminal->next;
        }
        displayQueues(head);
    }
}