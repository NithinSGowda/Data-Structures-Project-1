#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "header.h"

int main()
{
    terminal *head;
    head=beginner();
    head=initialisePrompt(head);

    return 0;
}




/*srand(time(NULL)+rand());   //To set random seed value for rand() function
printf("%d\n",rand()%10 + 1);
*/