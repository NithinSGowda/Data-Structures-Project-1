#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"
int totalPeople=0;
char inputString[20];

int main()
{
    terminal *head;
    head=beginner();
    head=initialisePrompt(head);
    head=displayQueues(head);    
    while(1){
        actualSimulation(head);
    }
    return 0;
}
