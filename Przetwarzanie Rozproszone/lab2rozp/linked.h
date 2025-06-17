typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int data);
void insertAtFront(Node** head, int data);
void insertAtEnd(Node** head, int data);
void insertAtPosition(Node** head, int data, int position);
void deleteFromFront(Node** head);
void deleteFromEnd(Node** head);
void deleteFromPosition(Node** head, int position);
void traverseList(Node* head);
void freeList(Node* head);