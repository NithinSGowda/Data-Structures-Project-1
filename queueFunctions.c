#include <stdio.h> 
#include <stdlib.h> 
#include"header.h"
 
person* newPerson(int time, int priority) 
{ 
    person* temp = (person*)malloc(sizeof(person)); 
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
    return temp->time;
} 
  
// Function to push according to priority 
void addPersonToQueue(person** head, int time, int priority) 
{ 
    person* start = (*head); 
    // Create new person 
    person* temp = newPerson(time, priority); 
    
    if(*head==NULL)
        (*head) = temp;
    else{
        // Special Case: The head of list has lesser 
    // priority than new person. So insert new 
    // person before head person and change head person. 
    if ((*head)->priority > priority) { 
  
        // Insert New person before head 
        temp->next = *head; 
        (*head) = temp; 
    } 
    else { 
  
        // Traverse the list and find a 
        // position to insert new person 
        while (start->next != NULL && 
               start->next->priority < priority) { 
            start = start->next; 
        } 
  
        // Either at the ends of the list 
        // or at required position 
        temp->next = start->next; 
        start->next = temp; 
    }
    }
} 
  
// Function to check is list is empty 
int isEmpty(person** head) 
{ 
    return (*head) == NULL; 
}