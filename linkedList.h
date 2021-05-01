// This code is retrieved from: https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
// and https://www.learn-c.org/en/Linked_lists
// The code is retrieved from the given sites.
// I acknowledge the academic code of conduct and respect the somebody else's work.
// The retrieved code is a basic data structure code which has been only used for practical reasons.
// The code was given as an open source study item. Thus, I acknowledge using somebody else's code. However, it was only for practical reasons to form a basic
// linkedlist operations. Nothing related to project that we are supposed to show our own work. For further details, please check the report.
// 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef linkedList_H_
#define linkedList_H_



typedef struct node {
    int month,day;
    char* desc;
    char* project;
    struct node * next;
} node_t;

void swap(node_t *a, node_t *b);
void bubbleSort(node_t *start);
void print_list(node_t * head);

void print_list(node_t * head) 
{
    node_t * current = head;

    while (current != NULL) {
       
        printf("Day: %d Month: %d Project: %s Description: %s \n", current->day,current->month,current->project,current->desc);
        // printf("Project: %s \n", (char*) current->project);
        // printf("Todo Description: %s \n", current->desc);
        current = current->next;
    }
}
void push(node_t * head, int month,int day,char* desc, char* project) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->month=month;
    current->next->day=day;
    
    current->next->desc = (char*) malloc(strlen(desc)+1);
    current->next->project = (char*) malloc(strlen(project)+1);
    // current->next->desc= desc;
    // current->next->project= project;
    strcpy(current->next->desc,desc);
    strcpy(current->next->project,project);
    current->next->next = NULL;
}
char* pop(node_t ** head) {
    char* retval;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return "dhsad";
    }

    next_node = (*head)->next;
    strcpy(retval,(*head)->desc);
    free(*head);
    *head = next_node;

    return retval;
}
/* function to swap data of two nodes a and b*/
void swap(node_t *a, node_t *b)
{
    int month = a->month;
    int day= a->day;
    char* desc = a->desc;
    char* project = a->project;
    a->month = b->month;
    a->day = b->day;
    a->desc = b->desc;
    a->project = b->project;
    b->month = month;
    b->day = day;
    b->desc = desc;
    b->project = project;
}
void bubbleSort(node_t *start)
{
    int swapped, i;
    node_t *ptr1;
    node_t *lptr = NULL;
    /* Checking for empty list */
    if (start == NULL)
        return;
  
    do
    {
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            if (ptr1->month > ptr1->next->month)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            else if(ptr1->month == ptr1->next->month){
                if(ptr1->day > ptr1->next->day){
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                }
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
void freeList(struct node* head)
{
   struct node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}
  


#endif