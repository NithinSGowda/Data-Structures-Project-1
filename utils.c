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
    while(i<=numOfTerminals)        //creates user defined number of terminals
    {
        terminal *temp2=(terminal *)malloc(sizeof(terminal));
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
    while(temp!=NULL)
    {
        tempQ=temp->q;
        temp->waitingTime=0;
        while(tempQ!=NULL)
        {
            temp->waitingTime+=tempQ->time;
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
            addPersonToQueue(&temp->q,((rand()%100)/10)+1,5);           //adds a person with a given random probablity 
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
    int totalTime=0;
    while(temp->next!=NULL)
    {
        printf("Terminal number : %d\n",temp->terminalNumber);
        printf("Total number of people in the queue are %d\n",temp->curStatus);
        printf("Estimated waiting time is %d minutes\n\n",temp->waitingTime);        
        temp=temp->next;
    }
}

terminal* searchFastestTerminal(terminal *head)
{
    terminal *temp=head;
    terminal *minTerminal=head;
    int minWaitingTime=head->waitingTime;
    while(temp->next!=NULL)
    {
        if(temp->waitingTime < minWaitingTime)
        {
            minWaitingTime=temp->waitingTime;
            minTerminal=temp;
        }
        temp=temp->next;
    }
    return minTerminal;
}

int findWaitingTime(terminal *root, person *person)
{
    int waitingTime=0;
    terminal *head=root;
    while(head->q!=NULL)
    {
        if(head->q==person)
            return waitingTime+head->q->next->time;
        else
        {
            waitingTime+=head->q->time;
            head->q=head->q->next;
        }
    }
}


void actualSimulation(terminal *head)
{
    char inputString;
    int choice;
    person *tempPerson;
    terminal *tempTerminal=head;
    terminal *allocatedTerminal=searchFastestTerminal(head);
    printf("\n1] Add a person\n2] fast forward time\n\n Enter your choice [1/2] : ");
    scanf("  %d",&choice);
    if(choice==1){
        printf("Enter the person detail [ VIP(V) / pregnant_women(P) / old(O) / handicapped(H) / normal(N)] : ");
        inputString=getchar();
        inputString = getchar();

        switch (inputString)
            {
            case 'V' :
                tempPerson = addPersonToQueue(&allocatedTerminal->q,((rand()%100)/10)+1,0);
                break;
            case 'P' :
                tempPerson = addPersonToQueue(&allocatedTerminal->q,((rand()%100)/10)+1,1);
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
        //printf("%d\n",tempPerson->priority);
        printf("\nPerson added to terminal number %d.\nPlease ask the person to go to terminal terminal %d\nHis/her waiting time is %d minutes.\n\n\n",allocatedTerminal->terminalNumber,allocatedTerminal->terminalNumber,findWaitingTime(allocatedTerminal,tempPerson));
        updateWaitingTime(head);
        displayQueues(head);
    }
    else{
        int time,removedTime=0,removedPeople=0;
        printf("Enter the amount of time to fast forward [in mins] : ");
        scanf(" %d",&time);
        while(tempTerminal!=NULL && tempTerminal->waitingTime!=0)
        {
            removedTime=0;
            removedPeople=0;
            while(removedTime<time)
            {
                removedTime+= pop(&tempTerminal->q);
                removedPeople++;
            }
            tempTerminal->curStatus-=removedPeople;
            tempTerminal->waitingTime-=removedTime;
            tempTerminal=tempTerminal->next;
        }
        displayQueues(head);
    }
    
}
