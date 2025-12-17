#include <stdio.h>
#include <stdlib.h>

// Struktura dla wÄ™zĹ‚a listy
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Funkcja do tworzenia nowego wÄ™zĹ‚a
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

void menu()
{
    cout << "----------MENU----------\n";
    cout << "----------Choose one option from the list----------\n
            1. Insert an element at the end of the list\n
            2. Insert an element at the beggining of the list\n
            3. Insert an element at the position (element, position)\n
            4. Delete an element from the end of the list\n
            5. Delete an element from the beggining of the list\n
            6. Delete an element from the position\n
            7. Show the list\n
            8. Show the menu\n";
}

// Funkcja do wstawiania na poczÄ…tek listy
void insertAtFront(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Funkcja do wstawiania na koniec listy
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

// Funkcja do wstawiania na konkretnÄ… pozycjÄ™
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

// Funkcja do usuwania z poczÄ…tku listy
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

// Funkcja do usuwania z koĹ„ca listy
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
        *head = NULL;  // JeĹ›li lista ma tylko jeden element
    }
    free(temp);
}

// Funkcja do usuwania z konkretnej pozycji
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

// Funkcja do przechodzenia po liĹ›cie i wypisywania jej zawartoĹ›ci
void traverseList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Funkcja do zwolnienia pamiÄ™ci listy
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;
    int option;
    int position;
    int element;


    menu();
            


    while(1)
    {
        switch (option)
        {
            case 1:
                cin >> element;
                insertAtEnd(&head,element);
                break;
            
            case 2:
                cin >> element;
                insertAtFront(&head, element);
                break;
            
            case 3:
                cin >> element >> position;
                insertAtPosition(&head, element, position);
                break;
            
            case 4:
                cin >> element;
                deleteFromEnd(&head, element);
                break;
            
            case 5:
                cin >> element;
                deleteFromFront(&head, element);
                break;

            case 6:
                cin >> position;
                deleteFromPosition(&head, position);
                break;
            
            case 7:
                cout << "Here's the double - linked list\n"
                traverseList(head);
            
            case 8:
                menu();
        }

            

                
    }

    /*// Wstawianie elementĂłw
    insertAtFront(&head, 10);  // Lista: 10
    insertAtEnd(&head, 20);    // Lista: 10 <-> 20
    insertAtFront(&head, 5);   // Lista: 5 <-> 10 <-> 20
    insertAtPosition(&head, 15, 3);  // Lista: 5 <-> 10 <-> 15 <-> 20

    // Przechodzenie po liĹ›cie
    printf("Lista po wstawieniu:\n");
    traverseList(head);

    // Usuwanie elementĂłw
    deleteFromFront(&head);   // Lista: 10 <-> 15 <-> 20
    deleteFromEnd(&head);     // Lista: 10 <-> 15
    deleteFromPosition(&head, 2);  // Lista: 10

    // Przechodzenie po liĹ›cie po usuniÄ™ciu
    printf("Lista po usuniÄ™ciu:\n");
    traverseList(head);*/

    // Zwolnienie pamiÄ™ci
    freeList(head);
    return 0;
}