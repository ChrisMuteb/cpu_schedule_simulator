#include<stdio.h>
#include<stdlib.h>//used for exit
#include<getopt.h>

void error_message(){
    printf("Required: -f fileInName.txt | tem -o fileOutName.txt\n");
    exit(2);// exit with an error code of 2
}

int main(int argc, char *argv[]){
    if(argc == 4){
        //show error message
        error_message();
    }
    //Variable declaration
    int optionInput;
    //Implementation
    
    while((optionInput = getopt(argc, argv, "f:o:")) != -1){
        printf("Arguments %s", optarg);
        //printf("argv: %s", *argv);
        optionInput = -1;
    }
    
}