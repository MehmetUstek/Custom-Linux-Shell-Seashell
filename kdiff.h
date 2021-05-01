#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef KDIFF_H_
#define KDIFF_H_


char* searchLineText(char* filename,int lineNum){
    FILE *fp;
    char temp[512];
    int line=1;
    char *temp1= malloc(512 * sizeof(char));
    fp = fopen (filename,"r");
    if(fp==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(temp, 512, fp) != NULL) {
        if(line==lineNum){
            strcpy(temp1,temp);
            return temp1;
        }
        line++;
    }
    fclose(fp);
    return " ";
}

void kdiff(char* filename1,char* filename2){
    FILE *fp1;
    FILE *fp2;
    char temp1[512];
    char temp2[512];
    int count=0;
    int *linearr = malloc(1000 * sizeof(int));
    int line=1;

    fp1 = fopen (filename1,"r");
    fp2 = fopen (filename2,"r");
    if(fp1==NULL || fp2==NULL){
        printf("INVALID FILE. EXITING\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(temp1, 512, fp1) != NULL
    && fgets(temp2, 512, fp2) != NULL){
        if(strcmp(temp1,temp2)!=0){
            linearr[count]= line;
            count++;
        }
        line++;
    
    }
    fclose(fp1);
    fclose(fp2);
    if(count==0){
        printf("%s\n","The two files are identical");
    }
    else{
        size_t length= sizeof(linearr)/sizeof(int);
        printf("%ld\n",length);
        for(int i=0;i<length;i++){
            printf("%s: line:%d %s\n",filename1,linearr[i],searchLineText(filename1,linearr[i]));
            printf("%s: line:%d %s\n",filename2,linearr[i],searchLineText(filename2,linearr[i]));
        }
    }

    free(linearr);
    

}

void kdiffB(char* filename1,char* filename2){
    long size1;
    long size2;
    FILE *fp1;
    FILE *fp2;

    fp1= fopen(filename1,"rb");
    fp2= fopen(filename2,"rb");
    if(fp1==NULL || fp2==NULL){
        return;
    }
    fseek(fp1,0,SEEK_END);
    size1= ftell(fp1);
    fclose(fp1);

    fseek(fp2,0,SEEK_END);
    size2= ftell(fp2);
    fclose(fp2);

    if(size1==size2){
        printf("%s\n","The two files are identical");
    }
    else{
        printf("The two files are different by:%d \n",abs(size1-size2));
    }

}

#endif