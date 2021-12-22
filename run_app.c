#include<stdio.h>
#include<stdlib.h>//used for exit
#include<getopt.h>
#include<string.h>

#define str_in_dt_sz 1024 //string input data size

/*--------------Read txt file and parse it into the linked list-----Start---Above Main Fn-----------------*/
void error_message(){
    printf("Required: -f <fileInName.txt> | -o f<ileOutName.txt>\n");
    exit(2);
}

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
/*--------------Read txt file and parse it into the linked list-----End--------------------*/


/*--------------Interface-----Start---Prototype declaration & variables-----------------*/
int s_m_vl = 0, p_m_vl = 0, quantum = 0;//scheduling method value, premptive method value, quantum time
char sch_vl[10], premt_vl[10];//sch_vl = {None, FCFS, SJF, Priority, RR} || premt_vl = {1 : ON, 2 : OFF}

int rr_time();//prompt for the quantum time
void firstMenu(int *s_m_arg, int *p_m_arg);//display the main menu
void schedulingMethod();
void premptive();//
void algorithmExecution(int sched, int prem);//Repository of various algorithm
/*--------------Interface-----End---Prototype declaration & variables-----------------*/
int main(int argc, char *argv[]){

    if(argc < 4){//ensures that the number of arguments is not less than 4
        error_message();
    }
    
    int optionInput;//Getopt var. holder
    char *in_fl, *out_fl;
    struct process *header = NULL;
    
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
    
    build_llist(in_fl, header);//Handle reading from file and fill linkedlist
    firstMenu(&s_m_vl, &p_m_vl);//calling the interface function


    exit(0);
}

/*--------------Interface-----Start---Function implementation-----------------*/
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

/*--------------Interface-----Start---Function implementation-----------------*/
int rr_time(){// Calculate the rr quantum time
    int dur = 0;//duration
    printf("You have selected RR, now insert the duration: ");
    scanf("%d", &dur);
    quantum = dur;
    return dur;
}

void firstMenu(int *s_m_arg, int *p_m_arg){// Displays the main menu
    
    int u_choice = 0;

    // Types of scheduling method
    switch (*s_m_arg)
    {
    case 0:
        strcpy(sch_vl, "None");
        break;
    case 1:
        strcpy(sch_vl, "FCFS");
        break;
    case 2:
        strcpy(sch_vl, "SJF");
        break;
    case 3:
        strcpy(sch_vl, "Priority");
        break;
    case 4:
        strcpy(sch_vl, "RR");
        break;
    
    default:
        strcpy(sch_vl, "None");
        break;
    }

    //printf("premt: %d\n", p_m_vl);
    switch (*p_m_arg)
    {
    case 0:
        strcpy(premt_vl, "Off");
        break;
    case 1:
        strcpy(premt_vl, "ON");
        break;
    
    default:
        strcpy(premt_vl, "Off");
        break;
    }

    if(*s_m_arg == 4)
    
        printf("\n\tCPU Scheduler Simulator\n1) Scheduling Method (%s - %d)\n2) Preemptive Mode (%s)\n3) Show Result\n4) End Program\nOption >", sch_vl, quantum, premt_vl);
    else
        printf("\n\tCPU Scheduler Simulator\n1) Scheduling Method (%s)\n2) Preemptive Mode (%s)\n3) Show Result\n4) End Program\nOption >", sch_vl, premt_vl);
    scanf("%d", &u_choice);

    switch (u_choice)
    {
    case 1:
        puts("You chose: Scheduling Method(None) ");
        schedulingMethod();//returns #

        break;
    case 2:
        puts("You chose: Preemptive Mode");
        premptive();
        break;
    case 3:
        //printf("")
        puts("You chose: Show Result");
       
        //algorithmExecution(s_m_vl, p_m_vl);
        break;
    case 4:
        puts("You chose: End the program");
        //Should display the avg and waiting time of each process and write to the output.txt
        break;
    
    default:
        printf("ERROR: cpu_scheduler_simulator takes only integers from 1 to 4\n");
        break;
    }
}

void schedulingMethod(){// Various scheduling methods
    int u_choice = 0;//user choice

    //output string
    char o_str[] = "\tCPU Scheduler Simulator\n1) First Come, First Served Scheduling\n2) Shortest-Job-First Scheduling\n3) Priority Scheduling\n4) Round-Robin Scheduling (You should also obtain time quantum value)\nOption >";
    printf("\n%s", o_str);
    scanf("%d", &u_choice);

    switch (u_choice)
    {
    case 1:
        puts("You chose: FCFS ");
        
        break;
    case 2:
        puts("You chose: SJF");
        break;
    case 3:
        puts("You chose: Priority");
        break;
    case 4:
        printf("You chose: RR(%d)\n", rr_time());
        break;
    
    default:
        printf("ERROR: cpu_scheduler_simulator takes only integers from 1 to 4");
        break;
    }

    s_m_vl = u_choice;
    firstMenu(&s_m_vl, &p_m_vl);//Takes you back to the main menu
}

void premptive(){//Returns the boolean equivalent of the preemptive option
    int isPremptive = 0;

    char o_str[] = "\tCPU Scheduler Simulator\n1) Preemptive ON\n2) Preemptive OFF\nOption >";
    printf("\n%s", o_str);
    scanf("%d", &isPremptive);

    switch(isPremptive)
    {
    case 1:
        printf("\nPreemptive on");
        isPremptive = 1;
        break;
    case 2:
        isPremptive = 0;
        printf("\nPreemptive OFF");
        break;
    
    default:
        printf("\nCan only take 1 or 2 are option\n");
        break;
    }
    p_m_vl = isPremptive;
    //printf("isPremtive: %d", p_m_vl);
    firstMenu(&s_m_vl, &p_m_vl);//Takes you back to the main menu
}
/*--------------Interface-----End---Function implementation-----------------*/

