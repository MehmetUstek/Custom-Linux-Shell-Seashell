#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#ifndef GOOD_MORNING_H_
#define GOOD_MORNING_H_


void good_morning(char* given_time,char* filename){
    struct timeval tv;
    time_t t;
    struct tm *info;
    char* write_msg;
    int hour;
    int minute;
    char* token;
    //Current time
    // gettimeofday(&tv, NULL);
    // t = tv.tv_sec;
    // info = localtime(&t);
    // strcpy(write_msg,asctime (info));
    
    // printf("%s\n",given_time);
    token= strtok(given_time,".");
    // printf("%s\n",token);
    hour= atoi(token);
    // printf("%d",hour);
    token= strtok(NULL,".");
    minute= atoi(token);
    // printf("%d\n",minute);

    // if((info->tm_hour== hour) && (info->tm_min== minute)){
    //     printf("%d %d ",hour,minute);
    //     playSong(filename);
    // }
    FILE* fp = fopen("crontab.txt", "a");
    if(fp==NULL){
        printf("Crontab file is busy now. Please try again later");
    }
    else{
        fprintf(fp,"%d ",minute);
        fprintf(fp,"%d ",hour);
        fprintf(fp,"%s","* * * ");
        fprintf(fp,"%s ","DISPLAY=:0.0");
        fprintf(fp,"%s ","/usr/bin/rhythmbox-client --play");
        fprintf(fp,"%s\n",filename);
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

    // free(token);
    // free(write_msg);
    // free(info);
    
}


#endif