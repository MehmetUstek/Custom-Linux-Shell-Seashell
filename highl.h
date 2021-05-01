#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef HIGHL_H_
#define HIGHL_H_

// enum color{r,g,b};

void highlight(char* word, char*  color, char* filename){
    FILE *fp;
    char cwd[1024];
    char* dir = getcwd(cwd, sizeof(cwd));
    char* token;
    char temp[512];
    char temp1[512];
    bool flag=false;
    char* colorstr  = malloc(strlen("\033[0;31m")+1);
    if(strcmp(color,"r")==0){
        // strcpy(colorstr,"\033[0;31m");
        colorstr="\033[0;31m";
    }else if(strcmp(color,"b")==0){
        colorstr="\033[0;34m";
    }else if(strcmp(color,"g")==0){
        colorstr="\033[0;32m";
    }

    for(int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
    fp = fopen (filename,"r");
    if(fp==NULL){
        printf("There is no relatable file in this directory. Please check the directory! Or use the one that has been created for you in this directory\n");
        fp = fopen (filename,"w");
        fclose(fp);
    }else{
        fp = fopen (filename,"r");
        if(fp==NULL){
            printf("INVALID FILE. EXITING\n");
            exit(EXIT_FAILURE);
        }
        while(fgets(temp, 512, fp) != NULL) {
            // strcpy(temp1,temp);
            token= strtok(temp," ");
            while(token!=NULL){
                for(int i = 0; token[i]; i++){
                    token[i] = tolower(token[i]);
                }
                if(strcmp(token,word)==0){
                    flag=true;
                    strcpy(temp1,colorstr);
                    // printf("\033[0;31m");
                    // printf("%s ",token);
                    strcat(temp1," ");
                    strcat(temp1,token);
                    strcat(temp1," ");
                    // printf("%s\n",temp1);
                    // printf("\033[0m");
                    strcat(temp1,"\033[0m");
                    token= strtok(NULL," ");
                }
                // printf("%s ",token);
                // strcat(temp1," ");
                strcat(temp1,token);
                strcat(temp1," ");
                // strcat(temp1," ");
                // if(flag==true){
                //     token= strtok(NULL," ");
                //     printf("%s\n",temp);
                //     flag=false;
                // }else{
                    token= strtok(NULL," ");
                // }
                
            }
            if(flag==true){
                printf("%s",temp1);
            }
            flag=false;
            strcpy(temp1,"");
           
        }
        // free(token);
        fclose(fp);
        printf("\n");
    }
}


#endif