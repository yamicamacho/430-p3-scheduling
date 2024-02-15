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
  printf("FIRST COME FIRST SERVED\n");
  int totalTime = 0;
  int switching = 0;

  struct task *first;
  struct node *temp;


  while (head != NULL) {
    temp = head;
    first = temp->task;
    while (temp != NULL) {
      if (comesBefore(temp->task->name, first->name)) { // lexicographical order
        first = temp->task;
      }
      temp = temp->next;
    }
    run(first, first->burst);
    switching++;
    totalTime += first->burst;
    delete (&head, first);
    printf("\tTime is now: %d\n", totalTime);
  }
  int cpuTime = totalTime + (switching - 1);
  double cpuUtilization = ((double)totalTime / cpuTime) * 100;
  printf("CPU Utilization: %.2lf%%\n", cpuUtilization);
}