# OS-Project-S4

Question:
In this assignment, you will implement an MLFQ scheduling algorithm for a problem mentioned below.

An operating system implements multilevel feedback queue scheduling with four queues. The top-level queue (highest priority) (Q0) employs round-robin scheduling. The second-level queue (Q1) first-come, first-served scheduling. The third-level queue (Q2) uses priority scheduling, where priority is taken as the inverse of the time needed by the jobs present in this queue. The last level queue (Q3) employs runs the shortest job first scheduling. Each job is allotted a maximum of 5ms in each queue. That means each job in any queue runs for 5ms on the CPU regardless of the algorithm’s nature and then each job is moved to the next lower level queue. If the job are not finished after the completion of execution of all jobs in the last queue, then all remaining jobs are put back to the topmost queue (Q0) again. The scheduling in a particular queue happens only after all the processes arrive in each queue. The process will repeat until all the jobs are completed. Calculate the average turnaround time taken for the sample workload given below. (Assumption: all the algorithms are assumed to be preemptive.)

The CPU execution of each job may be simulated as a a reduction of time required by the amount of allocation from the total time required.

Process &nbsp; Total CPU time needed

A     &nbsp;      300

B     &nbsp;      150

C     &nbsp;      250

D     &nbsp;      350

E     &nbsp;      450

You 'may' implement the solution in C using multithreading. You should have option to take CPU time needed for each job as the user input. The output should also display the individual job’s total turnaround time. The workload and allocation time should be chosen wisely.


How to run the file:
- Download the file mlfq.c
- If you are using Windows
    1. Install a C compiler
    2. Open a command prompt
    3. Navigate to the file directory containing mlfq.c
    4. Use gcc to compile the file, type in the command - 'gcc mlfq.c -o mlfq_out'
    5. Execute the compiled program, type in the command - 'mlfq_out'
- If you are using Linux
    1. Install a C compiler
    2. Open a terminal
    3. Navigate to the file directory containing mlfq.c
    4. Use gcc to compile the file, type in the command - 'gcc mlfq.c'
    5. Run the program, type in the command - ./a.out
- You will now have the program up and running
- Enter the numbers of jobs
- Enter the process(must be a character) and the total CPU time for each in the given prompt. (Eg.Enter Job name and total CPU time needed: A 30)
- You should get an output of the form 'Average Turnaround Time: N ms'
