#include<stdio.h>
#include<stdlib.h>//used for exit
#include<getopt.h>
#include<string.h>

#define str_in_dt_sz 1024 //string input data size

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
////incoming-------20 Dec
typedef struct process{
    int title;//Stores process ID
    int burt_time;
    int arrival_time;
    int priority;
    struct process *next;
}p;
static int num = 0;//Assign an id to a newly created process

//Function Prototype
struct process *createNode(int b_t, int a_t, int priorty); 
struct process *insertBack(struct process *header, int b_t, int a_t, int priorty);
void display(struct process *header);
void build_llist(char *in_txt, struct process *hdr);//gets data from file and fills up the linked list

int main(int argc, char *argv[]){

    if(argc < 4){//ensures that the number of arguments is not less than 4
        //show error message
        error_message();
    }
    
    int optionInput;//Getopt var. holder
    char *in_fl, *out_fl;
    struct process *header = NULL;


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
    
    build_llist(in_fl, header);


    exit(0);
    
}

void build_llist(char *in_txt, struct process *hdr){
    FILE *spin;
    int b_t, a_t, priority;
    char in[str_in_dt_sz];
   


    spin = fopen(in_txt, "r");//open file in reading mode

    if(!spin){
        printf("Could not open file\n");
        exit(1);
    }
 
    while(fgets(in, 1024, spin)){

        b_t = atoi(strtok(in, ":"));//stores digits bfr the ':'
        a_t = atoi(strtok(NULL, ":"));//stores digits bfr the ':' starting at the point it left off
        priority = atoi(strtok(NULL, "\n"));
        hdr = insertBack(hdr, b_t, a_t, priority);
    }

    display(hdr);

}
struct process *createNode(int b_t, int a_t, int priorty){
    struct process *temp;
    temp = (struct  process*)malloc(sizeof(struct process));
    temp->title = ++num;
    temp->burt_time = b_t;
    temp->arrival_time = a_t;
    temp->priority = priorty;
    temp->next = NULL;

    return temp;
}
struct process *insertBack(struct process *header, int b_t, int a_t, int priorty){

    //create node
    struct process *temp = createNode(b_t, a_t, priorty);
    struct process *headertemp;//start a 1st node
    if(header == NULL){
        header = temp;
        return header;
    }
    //Find the end of list
    headertemp = header;
    while (headertemp->next != NULL){
        headertemp = headertemp->next;
    }
    
    headertemp->next = temp;
    return header;
}
void display(struct process *header){
    
  if(header == NULL)
        puts("List is emplty");
    struct process *temp = header;
    while (temp != NULL)
    {
        printf("Process%d: %d-%d-%d -->", temp->title, temp->burt_time, temp->arrival_time, temp->priority);
        temp = temp->next;
    }
    puts("");
}