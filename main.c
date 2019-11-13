#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"

int main()
{
    terminal *head;
    head=beginner();
    head=initialisePrompt(head);
    displayQueues(head);

    return 0;
}
