/*Student Name: Wil Permenter
Student NetID: wbp120
Compiler Used: GCC
Program Description:Does the thing*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 4

int main(int argc, char *argv[]){
    int i, inputFd;
    ssize_t numRead;
    int total = 0;
    int *values;
    int cnt = 60;
    
    inputFd = open("flowData.dat", O_RDONLY);
    values = (int * ) calloc(10, sizeof(int));
    while(1){
        numRead = read(inputFd, values, 10*sizeof(int));
        if (numRead > 0){
            for ( i = 0; i < numRead/sizeof(int); i++){
                printf("%d\n", values[i]);
                total ++;
                if(total == cnt) break;
            }
        }
        else{
            break;
        }
        if(total == cnt) break;
    }
    free(values);
    close(inputFd);
    return 0;
}