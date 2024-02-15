#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "list.h"
#include "task.h"

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
  printf("ROUND ROBIN\n");
  int totalTime = 0;
  int switching = 0;
  int quantum = 10;

  struct task *first;
  struct node *temp;

  while (head != NULL) {

    temp = head;
    first = temp->task;
    if (first->burst == 0) {
      delete (&head, first);
    } else if (first->burst < quantum) {
      run(first, first->burst);
      totalTime += first->burst;
      switching++;
      delete (&head, first);
      printf("\tTime is now: %d\n", totalTime);
    } else {
      run(first, quantum);
      totalTime += quantum;
      switching++;
      delete (&head, first);
      add(first->name, first->priority, (first->burst - quantum));
      printf("\tTime is now: %d\n", totalTime);
    }
  }
  int cpuTime = totalTime + (switching - 1);
  double cpuUtilization = ((double)totalTime / cpuTime) * 100;
  printf("CPU Utilization: %.2lf%%\n", cpuUtilization);
}
