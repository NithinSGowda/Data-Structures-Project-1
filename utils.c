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
            addPersonToQueue(&temp->q,((rand()%100)/10)+1,((rand()%5)+1));           //adds a person with a given random probablity 
            temp->curStatus++;          //increments terminal's metadata
            i++;
        }
        temp=temp->next;        //moves on to next terminal
    }
    printf("\nInitialisation successful\n");
    return head;

}

/*person* addPersonToQueue(person *head,int priority)
{
    person *temp=head;
    person *tempPerson=(person *)malloc(sizeof(person)),*tempNext;
    srand(time(NULL)+rand());
    tempPerson->time=(rand()%100)/10;           //random time is assigned to each individual
    tempPerson->priority=priority;              
    if(head==NULL)              //If the person is the first person
    {
        tempPerson->next=NULL;          //Next person will be set to NULL and this person would be returned back
        return tempPerson;
    }
    while(temp->next!=NULL)         //Loops all over the queue to find the right position to insert
    {
        if(temp->next->priority<priority)       //If the next person's priority is lesser than the new person, the new person must chek the next person and loop repeats
        {
            temp=temp->next;
        }
        else
        {
            tempNext=temp->next;
            temp->next=tempPerson;              //Newperson is inserted in between if his priority is less than next one
            tempPerson->next=tempNext;
            return head;
        }
    }
    return head;            //The new head of the queue is returned
}
*/


/*person* addPersonToQueue(person *head,int priority)
{
    srand(time(NULL)+rand());
    push(&head,(rand()%100)/10,priority) ;
    return head;
}
*/


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
        totalTime=0;
        while(tempPerson->next!=NULL)
        {
            totalTime+=tempPerson->time;
            tempPerson=tempPerson->next;
        }
        printf("Terminal number : %d\n",temp->terminalNumber);
        printf("Total number of people in the queue are %d\n",temp->curStatus);
        printf("Estimated waiting time is %d minutes\n\n",totalTime);
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
    /*
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
    */  
}
