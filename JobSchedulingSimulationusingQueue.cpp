#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
typedef struct {
    int id;
    char name[30];
    int burstTime;
} Job;
Job queue[MAX];
int front = -1, rear = -1;
int isFull() {
    return rear == MAX - 1;
}
int isEmpty() {
    return front == -1 || front > rear;
}
void enqueue(Job job) {
    if (isFull()) {
        printf("\nQueue is Full! Cannot add more jobs.\n");
        return;
    }
    if (front == -1)
        front = 0;
    queue[++rear] = job;
    printf("? Job '%s' added successfully!\n", job.name);
}
Job dequeue() {
    Job emptyJob = {-1, "", 0};
    if (isEmpty()) {
        printf("\nQueue is Empty! No jobs to execute.\n");
        return emptyJob;
    }
    Job job = queue[front++];
    printf("?? Executing Job: %s (ID: %d, Burst Time: %d)\n", job.name, job.id, job.burstTime);
    return job;
}
void displayQueue() {
    if (isEmpty()) {
        printf("\nNo pending jobs in the queue.\n");
        return;
    }
    printf("\n?? Pending Jobs:\n");
    for (int i = front; i <= rear; i++) {
        printf("  ID: %d | Name: %s | Burst Time: %d\n", queue[i].id, queue[i].name, queue[i].burstTime);
    }
}
int main() {
    int choice, executedCount = 0;
    Job job;
    while (1) {
        printf("\n===== JOB SCHEDULER MENU =====\n");
        printf("1. Add Job\n");
        printf("2. Execute Job\n");
        printf("3. View Pending Jobs\n");
        printf("4. View Executed Job Count\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume newline
        switch (choice) {
            case 1:
                printf("\nEnter Job ID: ");
                scanf("%d", &job.id);
                getchar();
                printf("Enter Job Name: ");
                fgets(job.name, sizeof(job.name), stdin);
                job.name[strcspn(job.name, "\n")] = '\0'; // remove newline
                printf("Enter Burst Time (in ms): ");
                scanf("%d", &job.burstTime);
                enqueue(job);
                break;
            case 2:
                job = dequeue();
                if (job.id != -1) {
                    executedCount++;
                    printf("? Job '%s' completed.\n", job.name);
                }
                break;
            case 3:
                displayQueue();
                break;
			case 4:
                printf("\nTotal Executed Jobs: %d\n", executedCount);
                break;
			case 5:
                printf("\nExiting Job Scheduler. Goodbye!\n");
                exit(0);
			default:
                printf("? Invalid choice! Try again.\n");
        }
    }
    return 0;
}

