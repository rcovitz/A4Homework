#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node;

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* dummy;
} LinkedList;

Node* createNode(int value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

LinkedList* createLinkedList() {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->dummy = createNode('\0');
    return list;
}

void addWindow(LinkedList* list, int value) {
    Node* temp = createNode(value);
    temp->next = list->dummy->next;
    list->dummy->next = temp;
}

void removeWindow(LinkedList* list, int value) {
    Node* temp = list->dummy->next;
    Node* prev = list->dummy;

    while (temp != NULL) {
        if (temp->value == value) {
            prev->next = temp->next;
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void switchWindow(LinkedList* list, int new_value) {
    Node* temp = list->dummy->next;
    Node* prev = list->dummy;

    while (temp != NULL) {
        if (temp->value == new_value) {
            prev->next = temp->next;
            temp->next = list->dummy->next;
            list->dummy->next = temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void interpretCommand(LinkedList* list, char* command) {
    char action[10];
    int value;
    sscanf(command, "%s %d", action, &value);
    if (strcmp(action, "open") == 0) {
        addWindow(list, value);
    } else if (strcmp(action, "close") == 0) {
        removeWindow(list, value);
    } else if (strcmp(action, "switch") == 0) {
        switchWindow(list, value);
    }
}

void freeList(LinkedList* list) {
    Node* temp = list->dummy->next;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(list->dummy);
    free(list);
}

int main() {
    LinkedList* list = createLinkedList();
    char input[100];

    while (fgets(input, sizeof(input), stdin) != NULL) {
        interpretCommand(list, input);
        if (list->dummy->next != NULL) {
            printf("%d\n", list->dummy->next->value);
        } else {
            freeList(list);
            return 0;
        }
    }

    // Just in case
    freeList(list);
    return 0;
}
