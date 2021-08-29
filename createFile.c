/*
Student Name: Wil Permenter
Student NetID: wbp120
Compiler Used: GCC
Program Description:Does the thing
*/


#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 4

int getRand();
int outputValueToFile(int *out,int num,char* fn);
void outputValuesToTerm(int *out,int num);

union dtob
{
    int value;
    char bytes[4];
};


int main(int argc, char *argv[]){
    char *fileName = "flowData.dat";
    int num = 60;
    int lowVal = 5;
    int midVal = 10;
    int highVal = 15;

    if(argc == 1){
        printf("Option 1\n");
    }else if(argc == 3){
        printf("Option 2\n");
        fileName = argv[1];
        num = atoi(argv[2]);
    }else if(argc == 6){
        printf("Option 3\n");
        fileName = argv[1];
        num = atoi(argv[2]);
        lowVal = atoi(argv[3]);
        midVal = atoi(argv[4]);
        highVal = atoi(argv[5]);
    }else{
        printf("Usage: createFile *<filename> *<number> **<low value> **<middle value> **<high value>");
        return 0;
    }
        //Multiply by 10 here so we can just keep it all [int]
        lowVal *= 100;
        midVal *= 100;
        highVal *= 100;
        int *values = (int * )calloc(num,sizeof(int));


    for(int i = 0; i <= num; ++i){

        int rndOne = getRand();
        int rndTwo = getRand()- 50;

        //printf("\n%d,%d\n", rndOne, rndTwo);

        if(rndOne < 85){

            values[i] = highVal + rndTwo;

        }else if(rndOne > 15){

            values[i] = lowVal + rndTwo;

        }else{

            values[i] = midVal + rndTwo;

        }
    }
    outputValueToFile(values,num,fileName);
    free(values);
}

void outputValuesToTerm(int *out,int num){
    for(int i = 0; i<num; ++i){
        printf("%d:%d\n",i,out[i]);
    }
}

int outputValueToFile(int *out,int num,char* fn){
    //create buffer
    union dtob outBytes;

    int outputFd, openFlags;
    mode_t filePerms;

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IWOTH;
   
    outputFd = open(fn, openFlags, filePerms);
    if(outputFd == -1){
        printf("open for write error");
        return -1;
    }

    //write

    for(int i = 0; i<num; ++i){
        outBytes.value = out[i];

        if(write(outputFd, outBytes.bytes, 4) != 4){
            printf("write Error");
            return -1;
        }
    }
    close(outputFd);
}

//Slow but kinda pseudo random
    //Fun Fact 997,101 are highest / lowest 3 digit primes
int getRand(){
  time_t T;
  return rand()% 997 * abs((int)&T %101 + 5) % 100;
}
