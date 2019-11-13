#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "header.h"

terminal* createTerminals(int numOfTerminals,int sizeOfTerminal)
{
    printf("createterminals start\n\n");

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
        temp->q.queueSize=0;
        temp=temp2;
        i++;
    }
    temp->next=NULL;

    printf("createterminals done\n\n");
    return head;
}


terminal* beginner()
{
    printf("Started beginner\n\n");

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

    printf("Ended beginner\n\n");
    return createTerminals(numOfTerminals,sizeOfTerminal);
}

terminal* initialise(terminal *head)
{
    printf("Started initialise\n\n");

    terminal *temp=head;
    int i=0;
    while(temp!=NULL)
    {
        i=0;
        srand(time(NULL)+rand());
        while(i<rand()%head->maxCapacity)
        {
            printf("%d",rand()%head->maxCapacity);
            temp->q.person=addPersonToQueue(temp->q.person,(rand()%5));
            temp->q.queueSize++;
            i++;
        }
        temp=temp->next;
    }
    
    printf("Ended initialise\n\n");
    return head;

}

person* addPersonToQueue(person *head,int priority)
{
    printf("Started addPersonToQueue\n\n");

    person *temp=head;
    person *tempPerson=(person *)malloc(sizeof(person)),*tempPrev;
    srand(time(NULL)+rand());
    tempPerson->time=(rand()%100)/10;
    tempPerson->priority=priority;
    if(head==NULL)
    {
        tempPerson->next=NULL;
        printf("Ended addPersonToQueue 1\n\n");
        return tempPerson;
    }
    while(temp!=NULL)
    {
        if(temp->priority<priority)
        {
            tempPrev=temp;
            temp=temp->next;
        }
        else
        {
            tempPrev->next=tempPerson;
            tempPerson->next=temp;
            return head;
        }
    }

    printf("Ended addPersonToQueue\n\n");

    return head;
}

terminal* initialisePrompt(terminal *head)
{
    printf("Started initialisePrompt\n\n");
    
    char c;
    printf("Do you want to initialise the terminals with test passengers[y/n]\n");
    scanf(" %c",&c);


    printf("Ended initialisePrompt\n\n");

    if(c=='y')
        return initialise(head);
    else
        return head;
}