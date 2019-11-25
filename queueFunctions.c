#include <stdio.h> 
#include <stdlib.h> 
#include"header.h"
 
person* newPerson(int time, int priority) 
{ 
    person* temp = (person*)malloc(sizeof(person)); 
    if(temp==NULL){
        printf("malloc() Error\n");
        exit(10);
    }
    temp->time = time; 
    temp->priority = priority; 
    temp->next = NULL; 
    return temp; 
} 
  
// Return the value at head 
int peek(person** head) 
{ 
    return (*head)->time; 
} 
  
// Removes the element with the 
// highest priority form the list 
int pop(person** head) 
{ 
    person* temp = *head; 
    (*head) = (*head)->next;
    int time=temp->time;
    free(temp);
    return time;
} 
  
// Function to push according to priority 
person* addPersonToQueue(person** head, int time, int priority) 
{ 
    person *startTemp=(*head);
    person* start = (*head); 
    person* temp = newPerson(time, priority); 
    if(*head==NULL){
        (*head) = temp;
        printf("Added first\n");
    }
    else{
    if ((*head)->priority > priority) { 
        printf("%d\n",(*head)->time);
        temp->next=(*head);
        (*head)=temp;
    } 
    else {
        if(start->next==NULL){
            (*head)->next=temp;
            temp->next=NULL;
        }
        else{
            printf("%dMM%d\n",start->priority,priority);
        while (start->next!=NULL && start->priority <= priority) {
            printf("found here"); 
            start = start->next; 
        } 
        temp->next = start->next; 
        start->next = temp; 
        }
    }
    }
    return temp;
} 
// Function to check is list is empty 
int isEmpty(person** head) 
{ 
    return (*head) == NULL; 
}

