#include<stdio.h>
#include<stdlib.h>//used for exit
#include<getopt.h>
#include<string.h>

#define str_in_dt_sz 100 //string input data size

char str[str_in_dt_sz];//holds the input data from the input txt file

void error_message(){
    printf("Required: -f <fileInName.txt> | -o f<ileOutName.txt>\n");
    exit(2);
}
//open the input file and returns a string of all data in the file
void in_fl_openFile(char *in_txt, char str[]){

    FILE *f_i;

    f_i = fopen(in_txt,"r");

    if(f_i != NULL){
        char c;
        char s[100];

        int i = 0;
        while((c=fgetc(f_i)) != EOF){
           if(c == '\n'){
               c = '#';
               s[i] = c;
           }
           if(c != '\n'){
               s[i] = c;
           }
           i++;
            //putchar(c);
        }
        fclose(f_i);
        strcpy(str, s);
        //printf("CHris: %s",str);
    }else printf("Error opening file.\n");

}

int main(int argc, char *argv[]){
    if(argc < 4){
        //show error message
        error_message();
    }
    //Variable declaration
    int optionInput;//Getopt var. holder
    char *in_fl, *out_fl;


    //Implementation
    
    while((optionInput = getopt(argc, argv, "f:o:")) != -1){
        
        switch (optionInput)
        {
        case 'f':
            in_fl = optarg;
            break;
        case 'o':
            out_fl = optarg;
            break;
        default:
            error_message();
            break;
        }
        
    }
    //printf("f: %s\n", in_fl);
    in_fl_openFile(in_fl, str);// str hold data frm input.txt==> 5:2:3#4:1:2# ...
    printf("CHris: %s",str);
    //printf("o: %s\n", out_fl);


    exit(0);
    
}