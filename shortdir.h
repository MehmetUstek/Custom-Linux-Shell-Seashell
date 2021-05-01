#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#ifndef SHORTDIR_H_
#define SHORTDIR_H_


int searchLine(char* name){
    char cwd[1024];
    char* dir = getcwd(cwd, sizeof(cwd));
    FILE *fp;
    char temp[512];
    char* token;
    int line=0;
    char* path= (char*) malloc(strlen(getenv("HOME"))+strlen("/directories.txt")+1);
    strcpy(path,getenv("HOME"));
    strcat(path,"/directories.txt");
    fp = fopen (path,"r");
    if(fp==NULL){
       return -1;
    }
    while(fgets(temp, 512, fp) != NULL) {
        token= strtok(temp,",");
        line++;
        if(strcmp(token,name)==0){
            fclose(fp);
            free(path);
            return line;
        }
    }
    free(path);
    fclose(fp);
    // free(token);
    return -1;
}
void setName(char* name){
    char cwd[1024];
    char* dir = getcwd(cwd, sizeof(cwd));
    FILE *fp;
    FILE *fp1;
    char temp[512];
    int line;
    char* path= malloc(strlen(getenv("HOME"))+strlen("/directories.txt")+1);
    char* tempPath= malloc(strlen(getenv("HOME"))+strlen("/directoriestemp.txt")+1);
    strcpy(path,getenv("HOME"));
    strcat(path,"/directories.txt");
    strcpy(tempPath,getenv("HOME"));
    strcat(tempPath,"/directoriestemp.txt");
    line= searchLine(name);
    if(line==-1){
        
        fp = fopen (path,"a");
        fprintf(fp,"%s,%s\n",name,dir);
        fclose(fp);
    }else{
        int i=0;
        fp = fopen (path,"r");
        if(fp==NULL){
            printf("INVALID FILE. EXITING\n");
            printf("%s \n", path);
            exit(EXIT_FAILURE);
        }
        
        fp1 = fopen (tempPath,"w");
        if(fp1==NULL){
            printf("INVALID FILE. EXITING in\n");
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
        dir=getcwd(cwd, sizeof(cwd));
        fprintf(fp1,"%s,%s\n",name,dir);
        fclose(fp1);
        remove(path);
        rename(tempPath,path);
        free(path);
        free(tempPath);
        
    }
    
}
void delName(char* name){
    char cwd[1024];
    char* dir = getcwd(cwd, sizeof(cwd));
    FILE *fp;
    FILE *fp1;
    char temp[512];
    int line;
    int i=0;
    char* path= malloc(strlen(getenv("HOME"))+strlen("/directories.txt")+1);
    char* tempPath= malloc(strlen(getenv("HOME"))+strlen("/directoriestemp.txt")+1);
    strcpy(path,getenv("HOME"));
    strcat(path,"/directories.txt");
    strcpy(tempPath,getenv("HOME"));
    strcat(tempPath,"/directoriestemp.txt");

    line= searchLine(name);
    if(line==-1){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    fp = fopen (path,"r");
    if(fp==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    fp1 = fopen (tempPath,"w");
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
    remove(path);
    rename(tempPath,path);
    // free(path);
    // free(tempPath);
}

void clearName(){
    FILE *fp;
    char* path= malloc(strlen(getenv("HOME"))+strlen("/directories.txt")+1);
    strcpy(path,getenv("HOME"));
    strcat(path,"/directories.txt");

    remove(path);
    fp = fopen (path,"w");
    if(fp==NULL){
        printf("COULD NOT OPEN THE FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}
char * trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}
void jumpName(char* name){
    char cwd[1024];
    char* dir = getcwd(cwd, sizeof(cwd));
    FILE *fp;
    char temp[512];
    char* token;
    int line=0;
    char buf[PATH_MAX+1];
    char* path= malloc(strlen(getenv("HOME"))+strlen("/directories.txt")+1);
    strcpy(path,getenv("HOME"));
    strcat(path,"/directories.txt");

    printf("%s ",path);
    fp = fopen (path,"r");
    if(fp==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(temp, 512, fp) != NULL) {
        token= strtok(temp,",");
        if(strcmp(token,name)==0){
            token= strtok(NULL,",");
            
            strcpy(dir,token);
            printf("%s",dir);
            fclose(fp);
            
        }
    }
    free(path);
    fclose(fp);
    dir= trimwhitespace(dir);
    ///TODO:
    chdir(dir);
   

}

void listName(){
    FILE *fp;
    char temp[512];
    int line;
    char* token;
    char* path= malloc(strlen(getenv("HOME"))+strlen("/directories.txt")+1);
    strcpy(path,getenv("HOME"));
    strcat(path,"/directories.txt");

    fp = fopen (path,"r");
    if(fp==NULL){
        printf("There is no relatable file in this directory. Please check the directory!! EXITING\n");
        exit(EXIT_FAILURE);
    }
    int i=1;
    while(fgets(temp, 512, fp) != NULL) {
        printf("%d : %s", i , temp);
        i++;
    }
    fclose(fp);

}




#endif