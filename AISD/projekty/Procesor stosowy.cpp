// aisdproject1.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
#include <iostream>
#include <cstdlib>

using namespace std;

struct Node;

struct list {
    Node* head;
    int isInitialized;
};

union Data {
    char sign;
    list List;
};

struct Node {
    Data data;
    Node* next;
    Node* prev;
};


Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Blad przy przydzielaniu pamieci!\n");
        exit(1);
    }
    newNode->data.sign = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Node* ListCreateNode(list data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Blad przy przydzielaniu pamieci!\n");
        exit(1);
    }
    newNode->data.List = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}


void insertAtFront(Node** head, char data) {
    Node* newNode = createNode(data);
    newNode->next = NULL;
    newNode->prev = NULL;
    if (*head != NULL) {
        newNode->next = *head;

        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertAtEnd(Node** head, char data) {
    if (*head == NULL) {
        *head = createNode(data);
        return;
    }

    if ((*head)->next == NULL) {
        Node* newNode = createNode(data);
        (*head)->next = newNode;
        newNode->prev = *head;
        return;
    }

    insertAtEnd(&(*head)->next, data);
}




void ListInsertAtFront(Node** head, list data) {
    Node* newNode = ListCreateNode(data);
    //newNode->next = *head;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (*head != NULL) {
        newNode->next = *head;
        (*head)->prev = newNode;
    }
    *head = newNode;
}


/*void ListInsertAtEnd(Node** head, list data) {
    Node* newNode = ListCreateNode(data);
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
}*/



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


Node* convert(int ascii, Node* newListHead)
{
    if (ascii < 0)
    {
        insertAtFront(&newListHead, '-');
        ascii *= -1;
        return convert(ascii, newListHead);
    }
    if (ascii == 0 ) {
       
        
        return newListHead;
    }
    else {
        if (ascii != 0) {
            char digit = (ascii % 10) + '0';
            insertAtEnd(&newListHead, digit);
            ascii /= 10;
            return convert(ascii, newListHead);

        }
    }

    return newListHead;
}

long long convertToInt(Node* node, long long idx, bool* sign)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->data.sign == '-')
    {
        *sign = true;

    }

    return (node->data.sign == '-' ? 0 : ((node->data.sign - '0') * idx)) + convertToInt(node->next, idx * 10, sign);

}

bool isZero(Node* node)
{
    if (node == NULL || node->data.sign !='0')
    {
        return false;
    }

    if (node->data.sign == '0' && node->next == NULL)
    {
        return true;
    }

    return isZero(node->next);
}
struct program
{
    long long ip;
    long long MaxInst;
    char instructions[20000];
    Node* stack = NULL;
};


void ListAbs(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->data.sign == '-' && node->next == NULL)
    {
        if (node->prev != NULL)
            node->prev->next = NULL;
        free(node);
        return;
    }

    ListAbs(node->next);
}

void ListNeg(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->data.sign == '-' && node->next == NULL)
    {
        if (node->prev != NULL)
            node->prev->next = NULL;
        free(node);
        return;
    }

    if (node->next == NULL)
    {
        Node* tmp = (Node*)malloc(sizeof(Node));
        tmp->prev = node;
        tmp->next = NULL;
        tmp->data.sign = '-';
        node->next = tmp;
        return;
    }

    ListNeg(node->next);
}

void copyList(Node* oldNode, Node* newNode, Node** first)
{
    if (oldNode == NULL)
        return;

    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->prev = NULL;
    tmp->next = NULL;
    tmp->data = oldNode->data;

    if (newNode != NULL)
    {
        tmp->prev = newNode;
        newNode->next = tmp;


    }

    else
    {
        newNode = tmp;
        *first = newNode;
    }


    copyList(oldNode->next, tmp, first);

}

Node* getNodeAtPosition(Node* node, long long index) {
    if (node == NULL) {
        printf("Blad: indeks poza zakresem stosu!\n");
        exit(1);
    }
    if (index == 0) return node;
    return getNodeAtPosition(node->next, index - 1);
}

void printList(Node* head) {
    if (head == NULL) {
        return;
    }

    cout << head->data.sign;
    printList(head->next);
}

void printStack(Node* current, long long position) {
    if (current == NULL) {
        return;
    }
    printStack(current->next, position + 1);

    cout << position << ": ";
    try {
        printList(current->data.List.head);
        cout << endl;
    }
    catch (exception e) {}



}

Node* get_end_of_list(Node* n)
{
    if (n->next == NULL)
        return n;
    return get_end_of_list(n->next);
}

void execute(program& Program)
{
    while (Program.instructions[Program.ip] != '\0')
    {
        // implement execution
        char num;
        Node* first;
        Node* targetNode;
        long long index;
        Node* A;
        long long a, b;
        long long ascii;
        bool sign = false;
        Node* copiedHead;
        Node* newListHead;
        list newList;
        switch (Program.instructions[Program.ip])
        {
        case '\'': // w³ó¿ na stos pust¹ listê 
            ListInsertAtFront(&Program.stack, list{ NULL,1 });
            Program.ip++;
            break;

        case ',': // zdejmij listê ze stosu 
            deleteFromFront(&Program.stack);
            Program.ip++;
            break;

        case ':': //wloz na stos kopie listy z wierzcholka stosu
            first = NULL;

            copyList(Program.stack->data.List.head, NULL, &first);

            newList.head = first;
            newList.isInitialized = 1;
            ListInsertAtFront(&Program.stack, newList);

            Program.ip++;
            break;

        case ';': //zamieñ miejscami listê na wierzcho³ku stosu i listê bezpoœrednio pod nim 
            newList = Program.stack->data.List;
            Program.stack->data.List = Program.stack->next->data.List;
            Program.stack->next->data.List = newList;
            Program.ip++;
            break;

        case '@': //zdejmij ze stosu liczbê A, nastêpnie w³ó¿ na stos kopiê listy na A-tej pozycji na stosie (0 to wierzcho³ek stosu, 1 lista bezpoœrednio pod nim itp.); program '0@ jest równowa¿ny instrukcji :
            sign = false;
            index = convertToInt(Program.stack->data.List.head, 1, &sign);

            deleteFromFront(&Program.stack);

            targetNode = getNodeAtPosition(Program.stack, index);

            copiedHead = NULL;
            copyList(targetNode->data.List.head, NULL, &copiedHead);

            newList.head = copiedHead;
            newList.isInitialized = 1;

            ListInsertAtFront(&Program.stack, newList);

            Program.ip++;
            break;

        case '.': //wczytaj znak ze standardowego wejœcia i do³¹cz go na pocz¹tek listy na wierzcho³ku stosu 

            cin >> num;
            insertAtFront(&Program.stack->data.List.head, num);
            Program.ip++;
            break;


        case '>': //wypisz na standardowe wyjœcie pierwszy znak z listy na wierzcho³ku stosu i zdejmij listê z wierzcho³ka stosu 
            cout << Program.stack->data.List.head->data.sign;
            deleteFromFront(&Program.stack);
            Program.ip++;
            break;

        case '!': // negacja logiczna: je¿eli na wierzcho³ku stosu jest pusta lista lub lista zawieraj¹ca pojedyñczy znak '0', zast¹p j¹ list¹ zawieraj¹c¹ znak '1', w przeciwnym wypadku zast¹p listê z wierzcho³ka stosu list¹ zawieraj¹c¹ znak '0'
            if (isZero(Program.stack->data.List.head) || Program.stack->data.List.head == NULL)
            {
                deleteFromFront(&Program.stack);
                newList.head = NULL;
                insertAtFront(&newList.head, '1');
                ListInsertAtFront(&Program.stack, newList);
            }
            else
            {
                deleteFromFront(&Program.stack);
                newList.head = NULL;
                insertAtFront(&newList.head, '0');
                ListInsertAtFront(&Program.stack, newList);
            }
            Program.ip++;
            break;


        case '<': // zdejmij ze stosu liczbê A, zdejmij ze stosu liczbê B, je¿eli B < A, umieœæ na stosie liczbê 1, w przeciwnym wypadku umieœæ na stosie liczbê 0
            sign = false;
            a = convertToInt(Program.stack->data.List.head, 1, &sign);
            a *= sign ? -1 : 1;
            deleteFromFront(&Program.stack);

            sign = false;
            b = convertToInt(Program.stack->data.List.head, 1, &sign);
            b *= sign ? -1 : 1;
            deleteFromFront(&Program.stack);


            if (b < a)
            {
                newList.head = NULL;
                insertAtFront(&newList.head, '1');
                ListInsertAtFront(&Program.stack, newList);
            }
            else
            {
                newList.head = NULL;
                insertAtFront(&newList.head, '0');
                ListInsertAtFront(&Program.stack, newList);
            }

            Program.ip++;
            break;

        case '=': // zdejmij ze stosu liczbê A, zdejmij ze stosu liczbê B, je¿eli B = A, umieœæ na stosie liczbê 1, w przeciwnym wypadku umieœæ na stosie liczbê 0
            sign = false;
            a = convertToInt(Program.stack->data.List.head, 1, &sign);
            a *= sign ? -1 : 1;
            deleteFromFront(&Program.stack);

            sign = false;
            b = convertToInt(Program.stack->data.List.head, 1, &sign);
            b *= sign ? -1 : 1;
            deleteFromFront(&Program.stack);


            if (b == a)
            {
                newList.head = NULL;
                insertAtFront(&newList.head, '1');
                ListInsertAtFront(&Program.stack, newList);
            }
            else
            {
                newList.head = NULL;
                insertAtFront(&newList.head, '0');
                ListInsertAtFront(&Program.stack, newList);
            }

            Program.ip++;
            break;

        case '~': // umieœæ na stosie liczbê równ¹ numerowi tej instrukcji (wartoœæ wskaŸnika instrukcji) 
            newListHead = NULL;
            
            if (Program.ip == 0)
            {
                insertAtFront(&newListHead, '0');

            }
            else
            {
                
                newListHead = convert(Program.ip, newListHead);
            }
                


            newList.head = newListHead;
            newList.isInitialized = 1;

            ListInsertAtFront(&Program.stack, newList);
            //insertAtFront(&Program.stack, (char)Program.ip);
            Program.ip++;
            break;

        case '?': // skok warunkowy: zdejmij ze stosu liczbê T, zdejmij ze stosu listê W, je¿eli W nie jest pusta i nie zawiera wy³¹cznie znaku '0', wpisz do wskaŸnika instrukcji liczbê T i nie zwiêkszaj wskaŸnika instrukcji;
            sign = false;
            a = convertToInt(Program.stack->data.List.head, 1, &sign);
            a *= sign ? -1 : 1;
            deleteFromFront(&Program.stack);
            if (isZero(Program.stack->data.List.head) || Program.stack->data.List.head == NULL)
            {
                Program.ip = a;
            }
            else
            {
                Program.ip++;
            }
            deleteFromFront(&Program.stack);
            break;



        case '-': // negacja: je¿eli ostatnim znakiem listy na szczycie stosu jest '-' (minus), usuñ go z listy; w przeciwnym wypadku do³¹cz '-' na koniec listy na szczycie stosu
            if (Program.stack->data.List.head == NULL)
            {

                Program.stack->data.List.head = (Node*)malloc(sizeof(Node));
                Program.stack->data.List.head->prev = NULL;
                Program.stack->data.List.head->next = NULL;
                Program.stack->data.List.head->data.sign = '-';
            }

            else {
                if (Program.stack->data.List.head->data.sign == '-' && Program.stack->data.List.head->next == NULL)
                {
                    free(Program.stack->data.List.head);
                    Program.stack->data.List.head = NULL;
                }
                else ListNeg(Program.stack->data.List.head);

            }
            Program.ip++;
            break;

        case '^': // wartoœæ bezwzglêdna: je¿eli ostatnim znakiem listy na szczycie stosu '-' (minus) usuñ go z listy

            if (Program.stack->data.List.head != NULL)
            {
                if (Program.stack->data.List.head->data.sign == '-')
                {
                    free(Program.stack->data.List.head);
                    Program.stack->data.List.head = NULL;
                }
                else ListAbs(Program.stack->data.List.head);
            }
            else ListAbs(Program.stack->data.List.head);

            Program.ip++;
            break;


        case '$': // podzia³: od³¹cz pierwszy znak z listy na szczycie stosu i w³ó¿ go na stos git
            first = Program.stack->data.List.head;
            num = first->data.sign;
            Program.stack->data.List.head = first->next;
            if (Program.stack->data.List.head != NULL)
            {
                Program.stack->data.List.head->prev = NULL;
            }
            free(first);

            //newListHead = NULL;
            newListHead = (Node*)malloc(sizeof(Node));
            newListHead->data.sign = num;
            newListHead->next = NULL;
            newListHead->prev = NULL;

            newList.head = newListHead;
            newList.isInitialized = 1;

            ListInsertAtFront(&Program.stack, newList);


            Program.ip++;
            break;


        case '#': // zdejmij ze stosu listê A; do³¹cz A na koniec listy na szczycie stosu
            A = Program.stack->data.List.head;
            deleteFromFront(&Program.stack);
            targetNode = get_end_of_list(Program.stack->data.List.head);
            targetNode->next = A;
            A->prev = targetNode;
            Program.ip++;
            break;

        case '+': // zdejmij ze stosu liczbê A, zdejmij ze stosu liczbê B, w³ó¿ na stos liczbê A + B
            sign = false;
            a = convertToInt(Program.stack->data.List.head, 1, &sign);
            a *= sign ? -1 : 1;
            deleteFromFront(&Program.stack);

            sign = false;
            b = convertToInt(Program.stack->data.List.head, 1, &sign);
            b *= sign ? -1 : 1;
            deleteFromFront(&Program.stack);



            newList.head = NULL;
            newListHead = NULL;
            ListInsertAtFront(&Program.stack, list{ convert(a + b, newListHead), 1 });





            Program.ip++;
            break;


        case '&': //    wypisz na standardowe wyjœcie zawartoœæ stosu w formacie:n: lista na n - tej pozycji na stosie...1 : lista na drugim miejscu na stosie0 : lista na wierzcho³ku stosu lista powinna byæ przedstawiona jako ci¹g kolejnych znaków z listy(zaczynaj¹c od pierwszego)
            printStack(Program.stack, 0);
            Program.ip++;
            break;

        case ']': // zdejmij ze stosu liczbê A, umieœæ na stosie znak o numerze A w ASCI
            A = Program.stack;
            first = A->data.List.head;

            if (first != NULL)
                num = first->data.sign;
            //ascii = num;

            deleteFromFront(&Program.stack);

            newListHead = NULL;





            newList.head = (Node*)malloc(sizeof(Node));
            newList.head->next = NULL;
            newList.head->prev = NULL;
            newList.head->data.sign = (char)convertToInt(first, 1, &sign);
            newList.isInitialized = 1;

            ListInsertAtFront(&Program.stack, newList);
            Program.ip++;
            break;


        case '[': // zdejmij ze stosu listê A, umieœæ na stosie liczbê równ¹ numerowi ASCII pierwszego znaku z listy A
            A = Program.stack;
            first = A->data.List.head;


            num = first->data.sign;
            ascii = num;

            deleteFromFront(&Program.stack);

            newListHead = NULL;

            newListHead = convert(ascii, newListHead);



            newList.head = newListHead;
            newList.isInitialized = 1;

            ListInsertAtFront(&Program.stack, newList);
            Program.ip++;
            break;








        default:
            num = Program.instructions[Program.ip];
            insertAtFront(&Program.stack->data.List.head, num);
            Program.ip++;
            break;

        }
    }





}



int main()
{
    program Program;
    Program.ip = 0;
    Program.MaxInst = 0;
    Program.stack = NULL;
    //char input[20000];

    /*   Program.stack = (Node*)malloc(sizeof(Node));
       Program.stack->next = NULL;
       Program.stack->prev = NULL;*/

    cin.getline(Program.instructions, 20000);

    int i = 0;
    while (Program.instructions[i] != '\0') {
        i++;
    }
    Program.instructions[i] = '\0';

    execute(Program);
    //cout << Program.ip << " " << Program.instructions;

    return 0;
}
