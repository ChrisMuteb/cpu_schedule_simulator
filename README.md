# cpu_schedule_simulator
Writing a program that simulates the service of jobs (process) by the CPU of a multi-user computer. Inputs should be taken from text file with command arguments. And results also should be written to output file and screen.

## subTopic A: Getting started with the getopt()
Running the program: 
	* gcc run_app.c -o run_app
	* ./run_app -f input.txt -o output.txt
Functionality:
	* The program can read any number of input since dynamic memory is used and they are all inserted from the back
	* main UI prompting the user to select the method type, preemptive, result, end program is call up until you select option 4
	* Only the FCFS, SJF non preemtive, Priority non preemptive were implemented are fully functional. 
  ![FCFS 2](https://user-images.githubusercontent.com/31598690/148296560-f8d1e9ed-dc30-4b56-9517-fc218d34bbd9.png)
![Priority 2](https://user-images.githubusercontent.com/31598690/148296572-8ef7bf76-fdc6-458c-93ec-61a0b98447da.png)
![SJF 2](https://user-images.githubusercontent.com/31598690/148296583-e7e4eb15-360a-4d73-9cd7-3c9a6cd93542.png)
