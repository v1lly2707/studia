#include <stdio.h>
#include <stdlib.h>
#include "linked.h"


char garbage[] = "Ezbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4PEzbj2BJY896HfgrsAtGtdotiublhUw4P";



Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Blad przy przydzielaniu pamieci!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtFront(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtPosition(Node** head, int data, int position) {
    if (position < 1) {
        printf("NieprawidĹ‚owa pozycja!\n");
        return;
    }

    Node* newNode = createNode(data);
    if (position == 1) {
        insertAtFront(head, data);
        return;
    }

    Node* temp = *head;
    int currentPos = 1;
    while (temp != NULL && currentPos < position - 1) {
        temp = temp->next;
        currentPos++;
    }

    if (temp == NULL) {
        printf("Pozycja przekracza rozmiar listy!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteFromFront(Node** head) {
    if (*head == NULL) {
        printf("Lista jest pusta!\n");
        return;
    }

    Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

void deleteFromEnd(Node** head) {
    if (*head == NULL) {
        printf("Lista jest pusta!\n");
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        *head = NULL;  
    }
    free(temp);
}

void deleteFromPosition(Node** head, int position) {
    if (position < 1 || *head == NULL) {
        printf("NieprawidĹ‚owa pozycja lub lista jest pusta!\n");
        return;
    }

    Node* temp = *head;
    int currentPos = 1;

    if (position == 1) {
        deleteFromFront(head);
        return;
    }

    while (temp != NULL && currentPos < position) {
        temp = temp->next;
        currentPos++;
    }

    if (temp == NULL) {
        printf("Pozycja przekracza rozmiar listy!\n");
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
}

void traverseList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
