#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "header.h"

terminal* createTerminals(int numOfTerminals,int sizeOfTerminal)
{
    terminal *head=(terminal *)malloc(sizeof(terminal));
    if(head==NULL){
        printf("malloc() Error\n");
        exit(10);
    }
    terminal *temp=head;
    int i=1;
    while(i<=numOfTerminals)        //creates user defined number of terminals
    {
        terminal *temp2=(terminal *)malloc(sizeof(terminal));
        if(temp2==NULL){
        printf("malloc() Error\n");
        exit(10);
        }
        temp->next=temp2;
        temp->maxCapacity=sizeOfTerminal;           //initialisation of terminal metadata to default values
        temp->curStatus=0;
        temp->functional=0;
        temp->terminalNumber=i;
        temp->waitingTime=0;
        temp=temp2;         //moves to the next terminal
        i++;
    }
    temp->next=NULL;            //last terminal's next will be NULL
    return head;                //returns the newly created terminal list's head pointer
}

void updateWaitingTime(terminal *head)
{
    terminal *temp=head;
    person *tempQ;
    while(temp!=NULL)       //loops over all the terminals
    {
        tempQ=temp->q;
        temp->waitingTime=0;
        while(tempQ!=NULL)          
        {
            temp->waitingTime+=tempQ->time;             //adds waiting time of all people
            tempQ=tempQ->next;
        }
        temp=temp->next;
    }
}

terminal* beginner()
{
    printf("Welcome to Airport Check-in terminal simulator\n\n");
    printf("Press any to start\n");
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
    return createTerminals(numOfTerminals,sizeOfTerminal);          //This is returned to the main function
}

terminal* initialise(terminal *head)
{
    terminal *temp=head;
    int i;
    while(temp!=NULL)         //lops over all the terminals
    {
        i=0;
        srand(time(NULL)+rand());           //to set a random seed value for rand() function
        while(i<(rand()%head->maxCapacity)+1)           //loops random number of times to add random number of people to the queue
        {
            addPersonToQueue(&temp->q,((rand()%100)/10)+1,4);           //adds a person with a given random probablity 
            temp->curStatus++;          //increments terminal's metadata
            i++;
        }
        temp=temp->next;        //moves on to next terminal
    }
    updateWaitingTime(head);
    printf("\nInitialisation successful\n");
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
    while(temp->next!=NULL)
    {
        printf("Terminal number : %d\n",temp->terminalNumber);
        printf("Total number of people in the queue are %d\n",temp->curStatus);
        printf("Estimated waiting time is %d minutes\n\n",temp->waitingTime);
        /*while(temp->q!=NULL)
        {
            printf("%d ",temp->q->time);
            temp->q=temp->q->next;
        }        
        printf("\n\n");*/
        temp=temp->next;
    }
}

terminal* checkIfTerminalisFull(terminal *head)
{
    //If all queues are full with the specified maximum limit a new terminal is created
    terminal *tempTerminal=head,*prevTerminal;
    int totalTerminals=0,fullTerminals=0;
    while(tempTerminal!=NULL)
        {
            if(tempTerminal->curStatus==tempTerminal->maxCapacity)
            {
                fullTerminals+=1;
            }
            totalTerminals+=1;
            prevTerminal=tempTerminal;
            tempTerminal=tempTerminal->next;
        }
    if(fullTerminals==totalTerminals)
    {
        prevTerminal->next=(terminal *)malloc(sizeof(terminal));
        tempTerminal=prevTerminal->next;
        tempTerminal->maxCapacity=prevTerminal->maxCapacity;           //initialisation of terminal metadata to default values
        tempTerminal->curStatus=0;
        tempTerminal->functional=1;
        tempTerminal->terminalNumber=prevTerminal->terminalNumber+1;
        tempTerminal->waitingTime=0;
        tempTerminal->next=NULL;
        return tempTerminal;
    }
    return NULL;
}

terminal* searchFastestTerminal(terminal *head)
{
    //Searches the terminal with least waiting time for a new person to be added
    terminal *temp=head;
    terminal *minTerminal=head;
    int foundTerminal=1;
    int minWaitingTime=head->waitingTime;
    while(temp!=NULL)
    {
        if(temp->curStatus < temp->maxCapacity)
        {
            if(temp->waitingTime < minWaitingTime)
            {
            minWaitingTime=temp->waitingTime;
            minTerminal=temp;
            foundTerminal=1;
            }
        }
        temp=temp->next;
    }
    if(foundTerminal==1)
    return minTerminal;
    else
    return checkIfTerminalisFull(head);     //If all terminals are full a new terminal creation is done
}


//Adds up the waiting time of everyone infront of the given person
int findWaitingTime(terminal *root, person *person)
{
    int waitingTime=0;
    terminal *head=root;
    while(head->q!=NULL)
    {
        if(head->q==person)
            return waitingTime+head->q->time;
        else
        {
            waitingTime+=head->q->time;
            head->q=head->q->next;
        }
    }
    return waitingTime;         //Waiting time for the given person is returned
}


void actualSimulation(terminal *head)
{
    char inputString;
    int choice;
    person *tempPerson;
    terminal *tempTerminal=head;
    terminal *allocatedTerminal=searchFastestTerminal(head);            //Searches the terminal with least waiting time for a new person to be added
    if(allocatedTerminal==NULL)printf("NULL terminal assigned");
    
    printf("\n1] Add a person\n2] fast forward time\n3] Quit\n\n Enter your choice [1/2/3] : ");
    scanf("  %d",&choice);
    if(choice==1){
        printf("Enter the person detail [ VIP(V) / pregnant_women(P) / old(O) / handicapped(H) / normal(N)] : ");       //Priority V:0 , P:1 , O:2 , H:3 , N:4
        inputString=getchar();
        inputString = getchar();

        switch (inputString)
            {
            case 'V' :
                tempPerson = addPersonToQueue(&allocatedTerminal->q,((rand()%100)/10)+1,0);         //Random time is assingned for the new person
                break;
            case 'P' :
                tempPerson = addPersonToQueue(&allocatedTerminal->q,((rand()%100)/10)+1,1);         //Newly added person is returned in tempPerson
                break;
            case 'O' :
                tempPerson = addPersonToQueue(&allocatedTerminal->q,((rand()%100)/10)+1,2);
                break;
            case 'H' :
                tempPerson = addPersonToQueue(&allocatedTerminal->q,((rand()%100)/10)+1,3);
                break;
            default :
                tempPerson = addPersonToQueue(&allocatedTerminal->q,((rand()%100)/10)+1,4);
                break;
            }
        allocatedTerminal->curStatus++;
        printf("\nPerson added to terminal number %d.\nPlease ask the person to go to terminal terminal %d\nHis/her waiting time is %d minutes.\n\n\n",allocatedTerminal->terminalNumber,allocatedTerminal->terminalNumber,findWaitingTime(allocatedTerminal,tempPerson));
        printf("(Added person with time %d and priority %d)\n\n",tempPerson->time,tempPerson->priority);
        updateWaitingTime(head);
        displayQueues(head);
    }
    else if(choice==2){
        int time,removedTime=0,removedPeople=0;
        printf("Enter the amount of time to fast forward [in mins] : ");
        scanf(" %d",&time);
        tempTerminal=head;
        while(tempTerminal!=NULL && tempTerminal->waitingTime!=0)
        {
            removedTime=0;
            removedPeople=0;
            while((isEmpty(&tempTerminal->q)!=1) && (removedTime+peek(&tempTerminal->q))<time)
            {
                removedTime+=pop(&tempTerminal->q);
                removedPeople++;
            }
            tempTerminal->q->time=time-removedTime;
            tempTerminal->curStatus-=removedPeople;
            tempTerminal->waitingTime-=time;
            tempTerminal=tempTerminal->next;
        }
        displayQueues(head);
    }
    else
        exit(0);
    
}
