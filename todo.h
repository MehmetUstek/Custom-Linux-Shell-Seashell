#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"
#include "linkedList.h"
#ifndef TODO_H_
#define TODO_H_

void sortByDate(node_t * head);
struct Queue* searchProject(char* name);
void searchProjectWithLinkedList(char* name);
void listProject(char* project);
void setAlarm(int month,int day,char* desc, char* project);


void sortByDate(node_t * head)
{
    node_t * current = head;
    bubbleSort(current);
    print_list(current);

}
struct Queue* searchProject(char* name)
{
    FILE *fp;
    char temp[512];
    char* token;
    int line=1;
    struct Queue* queue = createQueue(1000);
    int count=0;
    fp = fopen ("todos.txt","r");
    if(fp==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(temp, 512, fp) != NULL) {
        token= strtok(temp,",");
        // printf("%s\n",token);
        if(strcmp(token,name)==0){
            enqueue(queue,line);
            count++;
        }
        line++;
    }
    fclose(fp);
    return queue;
}
void searchProjectWithLinkedList(char* name)
{
    FILE *fp;
    char temp[512];
    char* temp1 = malloc(512* sizeof(char));
    char* token;
    char* project = malloc(512* sizeof(char));
    int month=1;
    int day=1;
    char* desc = malloc(512* sizeof(char));
    int line=1;
    node_t * head = NULL;
    head = (node_t *) malloc(sizeof(node_t));
    int count=0;
    fp = fopen ("todos.txt","r");
    if(fp==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(temp, 512, fp) != NULL) {
        token= strtok(temp,",");
        strcpy(project,token);
        token= strtok(NULL,",");
        strcpy(desc,token);
        token= strtok(NULL,",");
        token= strtok(token,".");
        strcpy(temp1,token);
        day= atoi(temp1);
        token= strtok(NULL,".");
        strcpy(temp1,token);
        month= atoi(temp1);
        
        if(strcmp(project,name)==0){
            push(head,month,day,desc,project);
            count++;
        }
        line++;
    }
    
    fclose(fp);
    sortByDate(head);
    freeList(head);
    free(project);
    free(temp1);
    free(desc);
    
    // return head;
}
bool containsInArray(int line, int* arr, int size){
    // for(int i=0;i<(sizeof(arr)/sizeof(int))-1;i++){
    size_t length= sizeof(arr)/sizeof(int)-1;
    if(size==length || size > length){
        return false;
    }
    if(line==arr[size]){
        return true;
    }
    else{
        size++;
        containsInArray(line,arr,size);
    }
        
    // }
}
int searchTodo(char* name){
    FILE *fp;
    char temp[512];
    char* token  = malloc(512* sizeof(char));
    int line=0;
    char* desc  = malloc(512* sizeof(char));
    // node_t * head = NULL;
    // head = (node_t *) malloc(sizeof(node_t));

    fp = fopen ("todos.txt","r");
    if(fp==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(temp, 512, fp) != NULL) {
        token= strtok(temp,",");
        token= strtok(NULL,",");
        strcpy(desc,token);
        line++;
        // printf("%s \n",desc);
        // printf("%s",name);
        if(strcmp(desc,name)==0){
            fclose(fp);
            // free(desc);
            // free(token);
            return line;
        }
    }
    // free(desc);
    // free(token);
    fclose(fp);
    return -1;
}

void addTodo(char* project, char* description, char* date){
    FILE *fp;
    FILE *fp1;
    char temp[512];
    int line=0;
    int month;
    int day;
    char* token;
    line= searchTodo(description);
    if(line==-1){
        fp = fopen ("todos.txt","a");
        fprintf(fp,"%s,%s,%s\n",project,description, date);
        fclose(fp);
    }else{
        int i=0;
        fp = fopen ("todos.txt","r");
        if(fp==NULL){
            printf("INVALID FILE. EXITING\n");
            exit(EXIT_FAILURE);
        }
        fp1 = fopen ("todostemp.txt","w");
        if(fp1==NULL){
            printf("INVALID FILE. EXITING\n");
            exit(EXIT_FAILURE);
        }
        while(fgets(temp, 512, fp) != NULL) {
            i++;
            if(i!=line){
                fputs(temp,fp1);
            }
        }


        // fprintf(fp,"%s,%s\n",name,dir);
        fclose(fp);
        fprintf(fp1,"%s,%s,%s\n",project,description, date);
        fclose(fp1);
        remove("todos.txt");
        rename("todostemp.txt","todos.txt");
        // printf("%d %d %s %s",month,day,description,project);
        token= strtok(date,".");
        day=atoi(token);
        token= strtok(NULL,".");
        month= atoi(token);
        setAlarm(month,day,description,project);
    }
}
void delProject(char* project){
    FILE *fp;
    FILE *fp1;
    char temp[512];
    int line;
    int i=0;
    struct Queue* linearr = malloc(1000 * sizeof(int));
    linearr= searchProject(project);

    // struct Queue* queue = createQueue(1000);

    if(linearr==NULL){
        return;
    }
    fp = fopen ("todos.txt","r");
    if(fp==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    fp1 = fopen ("todostemp.txt","w");
    if(fp1==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    
    while(fgets(temp, 512, fp) != NULL) {
        i++;
        if(linearr->array[linearr->front]!=i){
            fputs(temp,fp1);
        }
        else{
            dequeue(linearr);
        }
    }
    // free(linearr);
    fclose(fp);
    fclose(fp1);
    remove("todos.txt");
    rename("todostemp.txt","todos.txt");
}
void delTodo(char* description){
    FILE *fp;
    FILE *fp1;
    char temp[512];
    int line;
    int i=0;
    line= searchTodo(description);
    if(line==-1){
        return;
        ///TODO:
    }
    fp = fopen ("todos.txt","r");
    if(fp==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    fp1 = fopen ("todostemp.txt","w");
    if(fp1==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(temp, 512, fp) != NULL) {
        i++;
        if(i!=line){
            fputs(temp,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("todos.txt");
    rename("todostemp.txt","todos.txt");
}
void listToday(char* project){

}
// void allListToday(){
//     ///TODO: Get today's date.
//     int date;
//     listDate(date);
// }
void listDate(char* date){
    // int month;
    // int day;
    // char* token;
    // token= strtok(date,".");
    // // printf("%s\n",token);
    // month= atoi(token);
    // // printf("%d",hour);
    // token= strtok(NULL,".");
    // day= atoi(token);
}
// void listProject(char* project){
//     FILE *fp;
//     char temp[512];
//     int line;
//     int i=1;
//     char* date = malloc(512* sizeof(char));
//     char* desc = malloc(512* sizeof(char));
//     char* token;
//     struct Queue* linearr = createQueue(1000);
//     linearr= searchProject(project);

//     if(linearr==NULL){
//         return;
//         ///TODO: 
//     }
//     fp = fopen ("todos.txt","r");
//     if(fp==NULL){
//         printf("INVALID FILE. EXITING\n");
//         exit(EXIT_FAILURE);
//     }
//     printf("Todos for project: %s\n",project);
//     while(fgets(temp, 512, fp) != NULL) {
//             token = strtok(temp,",");
//             token= strtok(NULL,",");
//             strcpy(desc,token);
//             token= strtok(NULL,",");
//             strcpy(date,token);
//             if(linearr->array[linearr->front]==i){
//                 printf("Todo Date: %s  Todo Description: %s\n",date,desc);
//                 ///TODO: Sort by date.
//                 dequeue(linearr);
//             }
            
//         i++;
//     }
//     printf("\n");
//     free(linearr);
//     fclose(fp);
// }
void listProject(char* project)
{
    // FILE *fp;
    // char temp[512];
    // int line;
    // int i=1;
    // node_t * head;
    searchProjectWithLinkedList(project);
    // printf("%s",head->desc);
    
}

void sortAllTodos(){
    FILE *fp;
    char temp[512];
    char* temp1 = malloc(512* sizeof(char));
    char* token;
    char* project = malloc(512* sizeof(char));
    int month=1;
    int day=1;
    char* desc = malloc(512* sizeof(char));
    int line=1;
    node_t * head = NULL;
    head = (node_t *) malloc(sizeof(node_t));
    int count=0;
    fp = fopen ("todos.txt","r");
    if(fp==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(temp, 512, fp) != NULL) {
        token= strtok(temp,",");
        strcpy(project,token);
        token= strtok(NULL,",");
        strcpy(desc,token);
        token= strtok(NULL,",");
        token= strtok(token,".");
        strcpy(temp1,token);
        day= atoi(temp1);
        token= strtok(NULL,".");
        strcpy(temp1,token);
        month= atoi(temp1);
        push(head,month,day,desc,project);
        count++;
        line++;
    }
    
    fclose(fp);
    sortByDate(head);
    freeList(head);
    free(project);
    free(temp1);
    free(desc);
}
void setAlarm(int month,int day,char* desc, char* project)
{
    // printf("%d\n",minute);

    // if((info->tm_hour== hour) && (info->tm_min== minute)){
    //     printf("%d %d ",hour,minute);
    //     playSong(filename);
    // }
    FILE *fp = fopen("crontab.txt", "a");
    if(fp==NULL){
        printf("Crontab file is busy now. Please try again later");
    }
    else{
        fprintf(fp,"%s ","* *");
        fprintf(fp,"%d ",day);
        fprintf(fp,"%d ",month);
        fprintf(fp,"%s ","*");
        fprintf(fp,"%s ","DISPLAY=:0.0");
        fprintf(fp,"%s ","DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus");
        fprintf(fp,"/usr/bin/notify-send %s '%s' \n", project,desc);
        char* path=realpath("crontab.txt",NULL);
        char *argv[3];
        argv[0]="crontab";
        argv[1]=path;
        argv[2]=NULL;
        int pid= fork();
        if(pid==0){
            execvp("crontab",argv);
        }
    }
    fclose(fp);
}



#endif