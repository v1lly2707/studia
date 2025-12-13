#include <iostream>

using namespace std;

struct Node 
{
        Node** children;
        int k;

        Node() : children(nullptr), k(0) {}

        Node(int kVal, int n) : k(kVal) 
        {
                children = new Node * [n];
                for (int i = 0; i < n; ++i) 
                        children[i] = nullptr;
                
        }

        ~Node() 
        {
                delete[] children;
        }
};

void search(int x, int key, Node* node, int m, int k) 
{
        int div = key / m;
        int mod = key % m;

        if (node->k == x)
                cout << x << " exist\n";
        else if (node->children[mod] == nullptr)
                node->children[mod] = new Node(x, k);
        else
                search(x, div, node->children[mod], k, k);
}

void find(int x, int key, Node* tree, int m, int k) 
{
        int div = key / m;
        int mod = key % m;

        if (tree->k == x)
                cout << x << " exist\n";
        else if (tree->children[mod] == nullptr)
                cout << x << " not exist\n";
        else
                find(x, div, tree->children[mod], k, k);
}

bool findLeaf(Node* tree, int modul, int k, int& del) 
{
        for (int i = 0; i < modul; i++) 
        {
                if (tree->children[i] != nullptr) 
                {
                        bool ifExist = false;
                        for (int j = 0; j < k; j++) 
                        {
                                if (tree->children[i]->children[j] != nullptr) 
                                {
                                        ifExist = true;
                                        break;
                                }
                        }

                        if (ifExist) 
                        {
                                if (findLeaf(tree->children[i], k, k, del))
                                        return true;
                        }
                        else 
                        {
                                del = tree->children[i]->k;
                                delete tree->children[i];
                                tree->children[i] = nullptr;
                                return true;
                        }
                }
        }
        return false;
}

void Delete(int x, int key, Node* tree, int m, int k, Node* parent = nullptr, int childIndex = -1) {
        int div = key / m;
        int mod = key % m;

        if (tree->k == x) 
        {
                bool ifExist = false;
                for (int i = 0; i < m; i++) 
                {
                        if (tree->children[i] != nullptr) 
                        {
                                ifExist = true;
                                break;
                        }
                }
                if (ifExist) 
                {
                        int del = -1;
                        findLeaf(tree, m, k, del);
                        tree->k = del;
                }
                else 
                {
                        if (parent)
                                parent->children[childIndex] = nullptr;
                        delete tree;
                }
        }
        else if (tree->children[mod] == nullptr)
                cout << x << " not exist" << endl;
        else
                Delete(x, div, tree->children[mod], k, k, tree, mod);
}

void f(Node* node, int modul, int k) 
{
        if (!node)
                return;

        cout << node->k << " ";

        for (int i = 0; i < modul; i++)
                if (node->children[i] != nullptr)
                        f(node->children[i], k, k);
}

void showTrie(Node* root, int n, int k) 
{
        f(root, n, k);
        cout << "\n";
}

int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int t;
        int Min, Max;
        int n, k;
        int x;
        char instruction;

        Node* node = nullptr;

        cin >> t;
        cin >> Min >> Max;
        cin >> n >> k;

        for (int i = 0; i < t; i++) 
        {
                cin >> instruction;

                switch (instruction) 
                {
                case 'I':
                        cin >> x;
                        if (node == nullptr)
                                node = new Node(x, n);
                        else
                                search(x, x, node, n, k);
                        break;

                case 'L':
                        cin >> x;
                        if (node != nullptr)
                                find(x, x, node, n, k);
                        else
                                cout << x << " not exist\n";
                        break;

                case 'P':
                        if (node != nullptr)
                                showTrie(node, n, k);
                        break;

                case 'D':
                        cin >> x;
                        if (node != nullptr)
                                Delete(x, x, node, n, k);
                        break;

                default:
                        cout << "Unknown command\n";
                        break;
                }
        }

        return 0;
}
