#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

const int MAX_SIZE = 16;

struct Node
{
    char sequence[MAX_SIZE];
    struct Node* next;
    int arg;
};

struct CommasNode
{
    int counter;
    struct CommasNode* next;
};

//------------------------------------------STACK-------------------------------
struct Stack
{
    struct Node* top;
};

void StackInitialization(struct Stack* stack)
{
    stack->top = NULL;
}


void PushToTheStack(struct Stack* _Stack, char* AddedValue) // pushing element to the stack
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    int idx = 0;

    while ((AddedValue[idx]) != '\0')
    {
        node->sequence[idx] = (AddedValue[idx]);
        idx++;
    }
    node->sequence[idx] = '\0';
    node->next = _Stack->top;
    _Stack->top = node;

}

Node PopFromTheStack(struct Stack* _Stack) // deleting elements from the stack
{
    struct Node node;
    if (_Stack->top == nullptr)
        cout << "Stack is empty!\n";
    else
    {
        node = *(_Stack->top);
        Node* temp = _Stack->top;
        _Stack->top = _Stack->top->next;
        free(temp);
    }

    return node;

}


void DisplayTheStack(struct Node* top) // displaying elements of the stack
{
    struct Node* first;

    if (top != nullptr)
    {
        first = top;

        while (first != nullptr)
        {
            cout << first->sequence << ' ';
            first = first->next;

        }
    }
    cout << "\n";
}


//------------------------------------------LIST--------------------------------
struct MyList
{
    struct Node* head;
    struct Node* tail;
};


void ListInitialization(struct MyList* list)
{
    list->head = NULL;
    list->tail = NULL;
}

void AddToTheList(struct MyList* list, char* AddedValue) // adding elements to the stack
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    int idx = 0;

    while (*(AddedValue + idx) != '\0')
    {
        node->sequence[idx] = *(AddedValue + idx);
        idx++;
    }
    node->sequence[idx] = '\0';
    node->next = NULL;

    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        return;
    }

    list->tail->next = node;
    list->tail = node;



}
void AddToTheList2(struct MyList* list, char* AddedValue, int arg) // adding elements to the stack
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    int idx = 0;

    while (*(AddedValue + idx) != '\0')
    {
        node->sequence[idx] = *(AddedValue + idx);
        idx++;
    }
    node->sequence[idx] = '\0';
    node->next = NULL;
    node->arg = arg;


    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        return;
    }

    list->tail->next = node;
    list->tail = node;



}

Node DeleteFromTheList(struct MyList* list) // deleting elements from the stack
{
    struct Node node;
    if (list->head == nullptr)
        cout << "List is empty\n";
    else
    {
        node = *(list->head);
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    }

    return node;

}

void DisplayTheList(struct Node* top) // displaying elements of the stack
{
    struct Node* first;

    if (top != nullptr)
    {
        first = top;

        while (first != nullptr)
        {

            if (first->sequence[0] == 'M')
                cout << first->sequence << first->arg << ' ';

            else
                cout << first->sequence << ' ';
            first = first->next;

        }

    }
    cout << '\n';
}


//-----------------------------COMMAS STACK-----------------

struct CommasStack
{
    struct CommasNode* top;
};

void CommasStackInitialization(struct CommasStack* stack)
{
    stack->top = NULL;
}


void PushToTheCommasStack(struct CommasStack* _Stack, int AddedValue) // pushing element to the stack
{
    struct CommasNode* node = (struct CommasNode*)malloc(sizeof(struct CommasNode));
    int idx = 0;


    node->counter = AddedValue;



    node->next = _Stack->top;
    _Stack->top = node;

}

CommasNode PopFromTheCommasStack(struct CommasStack* _Stack) // deleting elements from the stack
{
    struct CommasNode node;
    if (_Stack->top == nullptr)
        cout << "Stack is empty!\n";
    else
    {
        node = *(_Stack->top);
        CommasNode* temp = _Stack->top;
        _Stack->top = _Stack->top->next;
        free(temp);
    }

    return node;

}


void DisplayTheCommasStack(struct Node* top) // displaying elements of the stack
{
    struct Node* first;

    if (top != nullptr)
    {
        first = top;

        while (first != nullptr)
        {
            cout << first->sequence << ' ';
            first = first->next;

        }
    }
    cout << "\n";
}



//----------------------------------------------------------
char DetectOperand(char SingleChar) // checking if inserted char is an operand
{
    if (SingleChar >= '0' && SingleChar <= '9')
        return true;
    else return false;

}

char DetectRightPar(char SingleChar) // checking if inserted char is a right parenthesis
{
    if (SingleChar == ')')
        return true;
    else return false;

}

char DetectLeftPar(char SingleChar) // checking if inserted char is a left parenthesis
{
    if (SingleChar == '(')
        return true;
    else return false;

}

int SetPriority(char SingleChar) // setting priority of the operators
{
    if (SingleChar == '+' || SingleChar == '-')
        return 1;

    else if (SingleChar == '*' || SingleChar == '/')
        return 2;

    else if (SingleChar == 'I' || SingleChar == 'N' || SingleChar == 'M')
        return 3;

    else if (SingleChar == '(' || SingleChar == ')')
        return 4;

    else
        return 0;

}

int SimpleCalculation(int first, int second, char _Operator) // calculation of + - * /
{
    if (_Operator == '+')
        return first + second;

    else if (_Operator == '-')
        return first - second;

    else if (_Operator == '*')
        return first * second;

    else if (_Operator == '/')
        return first / second;

    else
        return 0;

}

int _Negation(int first)
{
    return -first;
}


int IfCalculation(int first, int second, int third)
{
    if (first > 0)
        return second;
    else return third;
}

void ConvertResult(int result, char* ConvertedResult) // converting the result
{
    sprintf_s(ConvertedResult, MAX_SIZE, "%d", result);
}



void ResultCalculation(struct MyList formula) // ONP calculation
{
    struct Stack output;

    StackInitialization(&output);

    int result = 0;
    while (formula.head != nullptr)
    {
        struct Node node = DeleteFromTheList(&formula);

        if (DetectOperand(node.sequence[0]))
            PushToTheStack(&output, node.sequence);
        else
        {
            cout << node.sequence;

            if (node.sequence[0] == 'M')
                cout << node.arg;

            cout << ' ';


            char* AdditionalPtr;

            char ConvertedResult[16];

            DisplayTheStack(output.top);

            if (node.sequence[0] == '+' || node.sequence[0] == '-' || node.sequence[0] == '*' || node.sequence[0] == '/')
            {

                int first = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);
                int second = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);
                if (node.sequence[0] == '/' && first == 0)
                {
                    cout << "ERROR\n";
                    //break;
                    return;
                }

                result = SimpleCalculation(second, first, node.sequence[0]);

            }
            else if (node.sequence[0] == 'N')
            {
                int first = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);
                result = _Negation(first);
            }

            else if (node.sequence[0] == 'I')
            {
                int first = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);
                int second = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);
                int third = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);

                result = IfCalculation(third, second, first);
            }

            else if (node.sequence[0] == 'M')
            {
                if (node.sequence[1] == 'I')
                {
                    int n = node.arg;
                    int _MIN = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);
                    n--;
                    while (n--)
                    {
                        int first = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);
                        if (first < _MIN)
                            _MIN = first;
                    }
                    result = _MIN;
                }
                else if (node.sequence[1] == 'A')
                {
                    int n = node.arg;
                    int _MAX = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);
                    n--;
                    while (n--)
                    {
                        int first = strtol(PopFromTheStack(&output).sequence, &AdditionalPtr, 10);
                        if (first > _MAX)
                            _MAX = first;
                    }
                    result = _MAX;
                }
            }





            ConvertResult(result, ConvertedResult);
            PushToTheStack(&output, ConvertedResult);
        }

    }

    cout << result << '\n';
    PopFromTheStack(&output);





}







int main()
{
    int n; // number of formulas
    cin >> n;

    MyList _List; // declaration of a list
    Stack _Stack;  // declaration of a stack
    CommasStack CStack; // declaration of a stack of commas


    while (n--)
    {
        ListInitialization(&_List);
        StackInitialization(&_Stack);

        char formula[16];

        while (1)
        {
            cin >> formula;

            if (formula[0] == '.')
                break;


            else if (DetectLeftPar(formula[0]))
                PushToTheStack(&_Stack, formula);

            else if (DetectOperand(formula[0]))
                AddToTheList(&_List, formula);

            else if (formula[0] == 'N')
                PushToTheStack(&_Stack, formula);

            else if (formula[0] == 'I' || formula[0] == 'M')
            {
                PushToTheStack(&_Stack, formula);
                int counter = 1;
                PushToTheCommasStack(&CStack, counter);


            }




            else if (DetectRightPar(formula[0]) || formula[0] == ',')
            {

                while (_Stack.top != nullptr)
                {
                    struct Node node = PopFromTheStack(&_Stack);

                    if (DetectLeftPar(node.sequence[0]))
                        break;
                    else
                    {
                        if (node.sequence[0] == 'I' || node.sequence[0] == 'M')
                        {
                            int cnt = PopFromTheCommasStack(&CStack).counter;
                            AddToTheList2(&_List, node.sequence, cnt);
                        }
                        else
                            AddToTheList(&_List, node.sequence);

                    }
                }
            }

            else
            {
                int priority = SetPriority(formula[0]);
                while (_Stack.top != nullptr)
                {
                    struct Node node = PopFromTheStack(&_Stack);

                    if (DetectLeftPar(node.sequence[0]) || SetPriority(node.sequence[0]) < priority)
                    {

                        PushToTheStack(&_Stack, node.sequence);
                        // cout << node.sequence << "dddd\n";
                        break;

                    }



                    if (node.sequence[0] == 'I' || node.sequence[0] == 'M')
                    {
                        int cnt = PopFromTheCommasStack(&CStack).counter;
                        AddToTheList2(&_List, node.sequence, cnt);
                    }
                    else
                        AddToTheList(&_List, node.sequence);
                    //cout << node.sequence << "dddd\n";
                }

                PushToTheStack(&_Stack, formula);
                //cout << formula << "sss\n";

            }


            if (formula[0] == ',')
            {
                formula[0] = '(';
                formula[1] = '\0';
                PushToTheStack(&_Stack, formula);

                CStack.top->counter++;
            }



        }

        while (_Stack.top != nullptr)
        {
            struct Node node = PopFromTheStack(&_Stack);
            if (node.sequence[0] == 'I' || node.sequence[0] == 'M')
            {
                int cnt = PopFromTheCommasStack(&CStack).counter;
                AddToTheList2(&_List, node.sequence, cnt);
            }
            else
                AddToTheList(&_List, node.sequence);

        }

        //-------------AFTER CONVERSION----------------------------

        DisplayTheList(_List.head);


        ResultCalculation(_List);

    }
    return 0;
}
