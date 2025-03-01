#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int id;
    char title[50];
    char description[200];
    int priority;
    int completed;
    struct Task* next;
} Task;

Task* head = NULL;
int taskCount = 1;

void addTask() {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->id = taskCount++;
    newTask->completed = 0;
    newTask->next = NULL;

    printf("Enter Task Title: ");
    getchar();
    fgets(newTask->title, sizeof(newTask->title), stdin);
    newTask->title[strcspn(newTask->title, "\n")] = 0;

    printf("Enter Task Description: ");
    fgets(newTask->description, sizeof(newTask->description), stdin);
    newTask->description[strcspn(newTask->description, "\n")] = 0;

    printf("Enter Task Priority (1 = High, 2 = Medium, 3 = Low): ");
    scanf("%d", &newTask->priority);

    if (head == NULL) {
        head = newTask;
    } else {
        Task* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
    printf("Task Added Successfully!\n");
}

void viewTasks() {
    if (head == NULL) {
        printf("No tasks available.\n");
        return;
    }

    Task* temp = head;
    printf("\n--- Task List ---\n");
    while (temp != NULL) {
        printf("ID: %d | Title: %s | Priority: %d | Status: %s\n",
               temp->id, temp->title, temp->priority, temp->completed ? "Completed" : "Pending");
        printf("Description: %s\n", temp->description);
        printf("--------------------------\n");
        temp = temp->next;
    }
}

void deleteTask() {
    if (head == NULL) {
        printf("No tasks available to delete.\n");
        return;
    }

    int id;
    printf("Enter Task ID to delete: ");
    scanf("%d", &id);

    Task *temp = head, *prev = NULL;

    if (temp != NULL && temp->id == id) {
        head = temp->next;
        free(temp);
        printf("Task Deleted Successfully!\n");
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Task ID not found!\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Task Deleted Successfully!\n");
}

void updateTask() {
    if (head == NULL) {
        printf("No tasks available to update.\n");
        return;
    }

    int id;
    printf("Enter Task ID to update: ");
    scanf("%d", &id);

    Task* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Enter New Title: ");
            getchar();
            fgets(temp->title, sizeof(temp->title), stdin);
            temp->title[strcspn(temp->title, "\n")] = 0;

            printf("Enter New Description: ");
            fgets(temp->description, sizeof(temp->description), stdin);
            temp->description[strcspn(temp->description, "\n")] = 0;

            printf("Enter New Priority (1 = High, 2 = Medium, 3 = Low): ");
            scanf("%d", &temp->priority);

            printf("Task Updated Successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Task ID not found!\n");
}

void markTaskCompleted() {
    if (head == NULL) {
        printf("No tasks available to mark as completed.\n");
        return;
    }

    int id;
    printf("Enter Task ID to mark as completed: ");
    scanf("%d", &id);

    Task* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->completed = 1;
            printf("Task Marked as Completed!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Task ID not found!\n");
}

void menu() {
    int choice;
    while (1) {
        printf("\nTask Manager (To-Do List)\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Update Task\n");
        printf("5. Mark Task as Completed\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: deleteTask(); break;
            case 4: updateTask(); break;
            case 5: markTaskCompleted(); break;
            case 6: printf("Exiting Program.\n"); exit(0);
            default: printf("Invalid Choice! Try Again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
