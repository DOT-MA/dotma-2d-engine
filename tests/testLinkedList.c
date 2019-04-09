#include <stdio.h>
#include <stdlib.h>

/**
 * A node in our linked list.
 */
typedef struct Node {
    int value;
    struct Node* next;
} Node;

/**
 * One directional linked list.
 */
typedef struct LinkedList {
    Node* start;
    size_t size;
} LinkedList;

/**
 * Initialize the linked list with a single member.
 */
LinkedList initializeLinkedList(void) {
    Node* start = (Node*) malloc(sizeof(Node));
    start->value = 0;
    return (LinkedList) {
        .start = start,
        .size = 1
    };
}

/**
 * Add another node to our linked list at the position provided.
 */
Node* addNode(LinkedList* list, Node* node) {
    node->next = (Node*) malloc(sizeof(Node));
    node->next->value = node->value + 1;
    node->next->next = NULL;
    list->size++;
    return node->next;
}

/**
 * Add a number of nodes to the linked list at a given index.
 */
int addNodes(LinkedList* list, Node* start, int number) {
    for (int i = 0; i < number; i++) {
        start = addNode(list, start);
    }
    return start->value;
}

/**
 * Free provided node.
 */
void freeNode(LinkedList* list, Node* current) {
    Node* next = current->next;
    free(current);
    current = next;
    list->size--;
}

/**
 * Free all nodes after and including provided start node.
 */
int freeNodes(LinkedList* list, Node* start) {
    int count = 0;
    do {
        freeNode(list, start);
        count++;
    } while (start->next != NULL);
    return count;
}

/**
 * Free a subsection of nodes given a provided range,
 * return the Node at the index of the start.
 */
Node* freeSubsection(Node* start, int begin, int end) {
    Node* current = start;
    int position = 0;
    Node* rhs = NULL;
    while (current->next != NULL) {
        if (position == begin - 1) {
            rhs = current;
        }
        if (position < begin) {
            position++;
            current = current->next;
            continue;
        }
        if (position >= begin && position <= end) {
            Node* next = current->next;
            free(current);
            current = next;
            position++;
            continue;
        }
        if (position > end) {
            rhs->next = current;
            break;
        }
    }
    return rhs;
}

/**
 * Linked list tests.
 */
int main(int argc, char** argv) {
    LinkedList list = initializeLinkedList();
    int val = addNodes(&list, list.start, 1000);
    printf("Value of last node added: %d\n", val);
    Node* subsection = freeSubsection(list.start, 10, 25);
    printf("Value before, value after: %d %d\n", subsection->value, subsection->next->value);
    int freed = freeNodes(&list, list.start);
    printf("Freed %d nodes succesfully!\n", freed);
    return 0;
}

