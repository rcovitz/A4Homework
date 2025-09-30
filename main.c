#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    // Node with value and pointer to next
    int value;
    struct Node* next;
} Node;

typedef struct LinkedList {
    // Create dummy head for better scanning
    Node* dummy;
} LinkedList;

Node* createNode(int value) {
    // Create memory
    Node* node = malloc(sizeof(Node));
    // Set node's value
    node->value = value;
    // Set node's next to NULL
    node->next = NULL;
    return node;
}

LinkedList* createLinkedList() {
    // Create memory
    LinkedList* list = malloc(sizeof(LinkedList));
    // Create dummy head with useless value
    list->dummy = createNode(-1);
    return list;
}

void addWindow(LinkedList* list, int value) {
    // Create node first
    Node* temp = createNode(value);
    // Setting node next to previous first
    temp->next = list->dummy->next;
    // Setting dummy to point to new
    list->dummy->next = temp;
}

void removeWindow(LinkedList* list, int value) {
    // Identify scan nodes
    Node* temp = list->dummy->next;
    Node* prev = list->dummy;

    // Until end of list
    while (temp != NULL) {
        // If value is found
        if (temp->value == value) {
            // Set prev's next to temp's next (skip temp)
            prev->next = temp->next;
            // Remove memory
            free(temp);
            return;
        }
        // Advance both pointers one node
        prev = temp;
        temp = temp->next;
    }
}

void switchWindow(LinkedList* list, int new_value) {
    // Identify scan nodes
    Node* temp = list->dummy->next;
    Node* prev = list->dummy;

    // Until end of list
    while (temp != NULL) {
        // If value is found
        if (temp->value == new_value) {
            // Set prev's next to temp's next (skip temp)
            prev->next = temp->next;
            temp->next = list->dummy->next;
            // Set dummy's next to temp (first value)
            list->dummy->next = temp;
            return;
        }
        // Advance both pointers one node
        prev = temp;
        temp = temp->next;
    }
}

void interpretCommand(LinkedList* list, char* command) {
    // Buffer for command
    char action[20];
    // Buffer for value
    int value;
    // Parse command to action and value
    sscanf(command, "%s %d", action, &value);

    // Call functions based on action
    if (strcmp(action, "open") == 0) {
        addWindow(list, value);
    } else if (strcmp(action, "close") == 0) {
        removeWindow(list, value);
    } else if (strcmp(action, "switch") == 0) {
        switchWindow(list, value);
    }
}

void freeList(LinkedList* list) {
    // Identify temp
    Node* temp = list->dummy->next;
    // Until end of list
    while (temp != NULL) {
        // Save next pointer
        Node* next = temp->next;
        // Free memory
        free(temp);
        // Advance
        temp = next;
    }
    // Free dummy and overall list
    free(list->dummy);
    free(list);
}

int main() {
    // Create list and buffer for commands
    LinkedList* list = createLinkedList();
    char input[100];

    // Until end of input or no windows left
    while (fgets(input, sizeof(input), stdin) != NULL) {
        // Interpret command
        interpretCommand(list, input);

        // If windows left
        if (list->dummy->next != NULL) {
            printf("%d\n", list->dummy->next->value);
        } else {
            // If no windows left
            freeList(list);
            return 0;
        }
    }

    // Just in case
    freeList(list);
    return 0;
}
