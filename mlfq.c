#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define ALLOCATED_TIME 5

//Job
typedef struct{
    char name;
    int total_CPU_time;
    int remaining_time;
    int turnaround_time;
    int priority;
} Job;

//MLFQ Queue
typedef struct{
    Job *Jobs[MAX];
    int front;
    int rear;
    int count;
} Queue;

void createQ(Queue *q){
    q->front=0;
    q->rear=-1;
    q->count=0;
}

int isEmpty(Queue *q){
    return q->count==0;
}

int isFull(Queue *q){
    return q->count==MAX;
}

void enqueue(Queue *q, Job *p){
    if (!isFull(q)){
        q->rear=(q->rear+1)%MAX;
        q->Jobs[q->rear]=p;
        q->count++;
    }
}

Job *dequeue(Queue *q){
    if (!isEmpty(q)){
        Job *p=q->Jobs[q->front];
        q->front=(q->front+1)%MAX;
        q->count--;
        return p;
    }
    return NULL;
}

Queue queues[4];
int total_jobs;

//Job execution
void execJob(Job *p){
    if (p->remaining_time>0){
        int exec_time=(p->remaining_time>ALLOCATED_TIME) ? ALLOCATED_TIME : p->remaining_time;
        p->remaining_time-=exec_time;
    }
}

//Sort queue 
//Q2 -> priority: flag=1
//Q3 -> remaining time: flag=0
void sortQ(Queue *q, int flag){
    for (int i=0; i < q->count-1; i++){
        for (int j=0; j < q->count-i-1; j++){
            Job *p1=q->Jobs[(q->front + j)%MAX];
            Job *p2=q->Jobs[(q->front+j+1)%MAX];

            int condition=flag ? (p1->total_CPU_time>p2->total_CPU_time) : (p1->remaining_time>p2->remaining_time);
            if (condition){
                q->Jobs[(q->front+j)%MAX]=p2;
                q->Jobs[(q->front+j+1)%MAX]=p1;
            }
        }
    }
}

// MLFQ scheduling function
void mlfqScheduling(Job Jobs[], int n){
    for (int i=0; i<4; i++){
        createQ(&queues[i]);
    }

    for (int i=0; i<n; i++){
        enqueue(&queues[0], &Jobs[i]);
    }

    int completed_jobs=0;
    int current_time=0;

    while (completed_jobs<n){
        for (int q=0; q<4; q++){
            if (q==2){
                sortQ(&queues[q], 1); //Priority Scheduling
            } 
            else if (q==3){
                sortQ(&queues[q], 0); //Shortest Job First
            }

            int size=queues[q].count;
            for (int i=0; i<size; i++){
                Job *p=dequeue(&queues[q]);

                int exec_time=(p->remaining_time > ALLOCATED_TIME) ? ALLOCATED_TIME : p->remaining_time;
                p->remaining_time-=exec_time;
                current_time+=exec_time;

                if (p->remaining_time>0){
                    if (q < 3){
                        enqueue(&queues[q + 1], p);
                    } 
                    else{
                        enqueue(&queues[0], p);
                    }
                }
                else{
                    p->turnaround_time=current_time; //Completion time
                    completed_jobs++;
                    //printf("Job %c has completed execution. Turnaround Time: %d ms\n", p->name, p->turnaround_time);
                }
            }
        }
    }

    //Calculate average turnaround time
    int total_turnaround_time=0;
    for (int i=0; i<n; i++){
        total_turnaround_time+=Jobs[i].turnaround_time;
    }
    float avg_turnaround_time=(float)total_turnaround_time/n;
    printf("\nAverage Turnaround Time: %.2f ms\n", avg_turnaround_time);
}

int main(){
    printf("Enter the number of Jobs: ");
    scanf("%d", &total_jobs);

    Job Jobs[total_jobs];

    for (int i=0; i<total_jobs; i++){
        printf("Enter Job name and total CPU time needed: ");
        scanf(" %c %d", &Jobs[i].name, &Jobs[i].total_CPU_time);
        Jobs[i].remaining_time=Jobs[i].total_CPU_time;
        Jobs[i].turnaround_time=0;
        Jobs[i].priority=i; //for now
    }

    mlfqScheduling(Jobs, total_jobs);
    return 0;
}