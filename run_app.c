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
    int wainting_time;
    int turn_a_t;
    struct process *next;
}p;
static int num = 0;//Assign an id to a newly created process

//Function Prototype
struct process *createNode(int b_t, int a_t, int priorty); 
struct process *insertBack(struct process *header, int b_t, int a_t, int priorty);
void display(struct process *header);
struct process * build_llist(char *in_txt, struct process *hdr);//gets data from file and fills up the linked list
/*--------------Read txt file and parse it into the linked list-----End--------------------*/


/*--------------Interface-----Start---Prototype declaration & variables-----------------*/
int s_m_vl = 0, p_m_vl = 0, quantum = 0;//scheduling method value, premptive method value, quantum time
char sch_vl[10], premt_vl[10];//sch_vl = {None, FCFS, SJF, Priority, RR} || premt_vl = {1 : ON, 2 : OFF}
struct process *header = NULL;//original linked list root
struct process *cp_h;//cloned linked list

int rr_time();//prompt for the quantum time
void firstMenu(int *s_m_arg, int *p_m_arg);//display the main menu
void schedulingMethod();
void premptive();//

/*--------------Interface-----End---Prototype declaration & variables-----------------*/

struct process *cloneList(struct process *head); /*--------------Cloning LL----------*/

/*---------Schduling Algorithm---Start---Prototype-------------*/
void algorithmExecution(int sch_choice, int premtp_choice);//Perform various algorithms based on the user's choice
void FCFS();
void SJF_Preempt(struct process *cp);
void SJF_N_Preempt();
void Priority_Preempt(struct process *cp);
void Priority_N_Preempt();
void RR();
/*---------Schduling Algorithm---End---Prototype-------------*/

/*-----------SJF Non Preemptive Fn Prototype.----------------*/
void swap(struct process *a, struct process *b);
void sortProcess(struct process *h);
void FCFS_Algo(struct process *h);

/*--------------Priority Non Preemptive prototype*/
void sortPriority(struct process *h);

//-------FCFS-----
int waitingtimeFCFS(struct process *);
int turnaroundtimeFCFS( struct process *);
int avgtimeFCFS( struct process *);
void quickFCFS(struct process *);

char *in_fl, *out_fl;//input and output file
int main(int argc, char *argv[]){

    if(argc < 4){//ensures that the number of arguments is not less than 4
        error_message();
    }
    
    int optionInput;//Getopt var. holder
    
    
    
    while((optionInput = getopt(argc, argv, "f:o:")) != -1){//prompt the user for the input and output file
        
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
    
    header = build_llist(in_fl, header);//Handle reading from file and fill linkedlist
    firstMenu(&s_m_vl, &p_m_vl);//calling the interface function
    //display(header); //Test and ensure that header has a copy of the original data
    cp_h = cloneList(header);
    //display(cp_h); //cp_h has cloned successfully header
    //printf("\nYou selected-Method:%d &&Option: %d\n", s_m_vl, p_m_vl);
    


    exit(0);
}

/*--------------Interface-----Start---Function implementation-----------------*/
struct process * build_llist(char *in_txt, struct process *hdr){
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

    //display(hdr);//Test 
    return hdr;

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
        algorithmExecution(s_m_vl, p_m_vl);
        s_m_vl = p_m_vl = 0;
        firstMenu(&s_m_vl, &p_m_vl);//takes us back to the main menu
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

/*---------Cloning the Linkedlist---Start---Function implementation-------------*/
struct process *cloneList(struct process *head){

    struct process *current = head;
    struct process *newList = NULL;
    struct process *tail = NULL;

    while(current != NULL){
        if(newList == NULL){
            newList = (struct process *)malloc(sizeof(struct process));
            newList->title = current->title;
            newList->burt_time = current->burt_time;
            newList->arrival_time = current->arrival_time;
            newList->priority = current->priority;

            newList->next = NULL;
            tail = newList;
        }else{
            tail->next = (struct process *)malloc(sizeof(struct process));
            tail = tail->next;
            tail->title = current->title;
            tail->burt_time = current->burt_time;
            tail->arrival_time = current->arrival_time;
            tail->priority = current->priority;
            tail->next = NULL;
        }
        current = current->next;
    }
    return newList;
}
/*---------Cloning the Linkedlist---End---Function implementation-------------*/

/*---------Schduling Algorithm---Start---Function implementation-------------*/
void algorithmExecution(int sch_choice, int premtp_choice){

    if(sch_choice == 1 && premtp_choice == 0){//FCFS 
        
        FCFS();
    }else if(sch_choice == 1 && premtp_choice == 1){
        puts("\nFCFS can never be preempted");
    }else if(sch_choice == 2 && premtp_choice == 0){
        SJF_N_Preempt();
    }else if(sch_choice == 2 && premtp_choice == 1){
        SJF_Preempt(cp_h);
    }
    else if(sch_choice == 3 && premtp_choice == 1){
        Priority_Preempt(cp_h);
    }else if(sch_choice == 3 && premtp_choice == 0){
        Priority_N_Preempt(cp_h);
    }else if(sch_choice == 4 ){
        RR();
    }
    
}

void FCFS(){
    struct process *cp = cloneList(header);
    struct process *temp = NULL;
    temp = cp;
    //------------------
    
    //waitingtimeFCFS(cp);
    //turnaroundtimeFCFS(cp);
    //avgtimeFCFS(cp);
    quickFCFS(cp);
    
    //------------------

    /*int sum_wt = 0, prev_bt = 0, num_proc = 0;
    float avg = 0;

    while(temp != NULL){
        if(temp == cp){
            temp->wainting_time = 0;
            prev_bt = temp->burt_time;
    }else{
            temp->wainting_time = prev_bt;
            sum_wt += temp->wainting_time;
            prev_bt += temp->burt_time;
    }
        printf("P%d: ", temp->title);
        printf("%d ms\n", temp->wainting_time);
        temp = temp->next;
        num_proc++;
    }
    avg = (float)sum_wt/(float)num_proc;
    printf("Average Waiting Time: %.1f\n", avg);*/
}
void quickFCFS(struct process *cp){
    // Function to find the waiting time for all processes
    waitingtimeFCFS(cp);
// Function to calculate turn around time
    turnaroundtimeFCFS(cp);
//Function to calculate average time
    avgtimeFCFS(cp);
}

int avgtimeFCFS( struct process *cp) {
   int total_wt = 0, total_tat = 0, n=0;
   int i;
   //Function to find waiting time of all processes
   waitingtimeFCFS(cp);
   //Function to find turn around time for all processes
   turnaroundtimeFCFS(cp);
   // Calculate total waiting time and total turn
   // around time
   
  
   for ( i=0; cp != NULL; i++) {
      total_wt = total_wt + cp->wainting_time;
      total_tat = total_tat + cp->turn_a_t;
      printf("\n%d\t  %d\t\t %d \t\n", cp->title, cp->burt_time, cp->wainting_time);
      n++;
      cp = cp->next;
   }
   printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
   
   return 0;
}
int turnaroundtimeFCFS( struct process *cp) {
   // calculating turnaround time by adding
   // burst_time[i] + wait_time[i]
   struct process *ht = NULL;
   ht = cp;
   int i;
   for ( i = 0; ht != NULL ; i++){
       ht->turn_a_t = ht->burt_time + ht->wainting_time;
       ht = ht->next;
   }
   
   return 0;
}
int waitingtimeFCFS(struct process *cp) {
   // waiting time for first process is 0
   struct process *ht = NULL;
   ht = cp;
   ht->wainting_time = 0;
   // calculating waiting time

   //ht = ht->next;
   struct process *h = NULL;
   h = ht;
   ht = ht->next;
   while( ht != NULL ){
       ht->wainting_time = h->burt_time + h->wainting_time;
       h = h->next;
       ht = ht->next;
   }
        
   return 0;
}

void SJF_N_Preempt(){
    puts("SJF Non Preempt.");
    struct process *cp = NULL;
    cp = cloneList(header);
    sortProcess(cp);
    FCFS_Algo(cp);
}
void SJF_Preempt(struct process *cp){
    puts("SJF Preempt");
}
void Priority_Preempt(struct process *cp){
    puts("Priority Preempt.");
}
void Priority_N_Preempt(){
    puts("Priority Non Preempt.");
    struct process *cp = NULL;
    cp = cloneList(header);
    sortPriority(cp);
    FCFS_Algo(cp);
    
}
void RR(){
    printf("Round robin\n");
}
/*---------Schduling Algorithm---End---Function implementation-------------*/

/*------------SJF relying fn implementation*/
void swap(struct process *a, struct process *b)
{
    int t_title = a->title;//Stores process number
    int t_burt_time = a->burt_time;
    int t_arrival_time = a->arrival_time;
    int t_priority = a->priority;
    int t_w_t = a->wainting_time;
    

    
    a->title = b->title;
    a->burt_time = b->burt_time;
    a->arrival_time = b->arrival_time;
    a->priority = b->priority;
    a->wainting_time = b->wainting_time;

    
    b->title = t_title;
    b->burt_time = t_burt_time;
    b->arrival_time = t_arrival_time;
    b->priority = t_priority;
    b->wainting_time = t_w_t;
}
void sortProcess(struct process *h){
    struct process *ht;//header temp
    struct process *an = NULL;//after node
    int is_sp;
  
    /* Checking for empty list */
    if (ht == NULL)
        return;
  
    do
    {//outter loop
        is_sp = 0;
        ht = h;
  
        while (ht->next != an)
        {//inner loop
            if (ht->burt_time > ht->next->burt_time)
            { 
                swap(ht, ht->next);
                is_sp = 1;
            }
            ht = ht->next;
        }
        an = ht;
    }
    while (is_sp);
}

void FCFS_Algo(struct process *h){
    struct process *cp = cloneList(h);

    struct process *temp = NULL;
    temp = cp;
    int sum_wt = 0, prev_bt = 0, num_proc = 0;
    float avg = 0;

    while(temp != NULL){
        if(temp == cp){
            temp->wainting_time = 0;
            prev_bt = temp->burt_time;
    }else{
            temp->wainting_time = prev_bt;
            sum_wt += temp->wainting_time;
            prev_bt += temp->burt_time;
    }
        printf("P%d: ", temp->title);
        printf("%d ms\n", temp->wainting_time);
        temp = temp->next;
        num_proc++;
    }
    avg = (float)sum_wt/(float)num_proc;
    printf("Average Waiting Time: %.1f\n", avg);
}

void sortPriority(struct process *h)
{
    //int i;
    struct process *ht;//header temp
    struct process *an = NULL;//after node
    int is_sp;
  
    /* Checking for empty list */
    if (ht == NULL)
        return;
  
    do
    {//outter loop
        is_sp = 0;
        ht = h;
  
        while (ht->next != an)
        {//inner loop
            if (ht->priority > ht->next->priority)
            { 
                swap(ht, ht->next);
                is_sp = 1;
            }
            ht = ht->next;
        }
        an = ht;
    }
    while (is_sp);
}