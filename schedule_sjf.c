#include "cpu.h"
#include "list.h"
#include "task.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct node *head = NULL;

bool comesBefore(char *a, char *b) { return strcmp(a, b) < 0; }

void add(char *name, int priority, int burst) {
  // Create new Task
  Task *newTask = (Task *)malloc(sizeof(Task));
  newTask->name = name;
  newTask->priority = priority;
  newTask->burst = burst;

  // inseart at head
  if (head == NULL) {
    head = (struct node *)malloc(sizeof(struct node));
    head->task = newTask;
    head->next = NULL;
  } else {
    // insert at the end of the list
    struct node *temp = head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = (struct node *)malloc(sizeof(struct node));
    temp->next->task = newTask;
    temp->next->next = NULL;
  }
}

void schedule() {
  printf("SHORTEST JOB FIRST\n");
  int totalTime = 0;
  int burst = 1000;
  int switching = 0;

  struct task *minBurst;
  struct node *temp;

  while (head != NULL) {
    temp = head;
    while (temp != NULL) {
      if (temp->task->burst < burst) {
        burst = temp->task->burst;
        minBurst = temp->task;
      } else if (temp->task->burst == burst) {
        if (comesBefore(temp->task->name,
                        minBurst->name)) { // lexicographical order
          minBurst = temp->task;
        }
      }
      temp = temp->next;
    }
    run(minBurst, minBurst->burst);
    delete (&head, minBurst);
    totalTime += burst;
    switching++;
    printf("\tTime is now: %d\n", totalTime);
    burst = 1000;
  }
  int cpuTime = totalTime + (switching - 1);
  double cpuUtilization = ((double)totalTime / cpuTime) * 100;
  printf("CPU Utilization: %.2lf%%\n", cpuUtilization);
}