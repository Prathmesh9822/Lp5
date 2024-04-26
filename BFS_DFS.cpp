#include <iostream>
#include <queue>
#include <omp.h>
#include <stack>

using namespace std;

class node {
public:
    node* left;
    node* right;
    int data;
    int N;
};

class Breadthfs {
private:
    node* root = nullptr;

public:
    node* insert(int);
    void bfs();
    void dfs();
};

node* Breadthfs::insert(int data) {
    if (!root) {
        root = new node;
        root->left = nullptr;
        root->right = nullptr;
        root->data = data;
        return root;
    }
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        node* temp = q.front();
        q.pop();
        if (temp->left == nullptr) {
            temp->left = new node;
            temp->left->left = nullptr;
            temp->left->right = nullptr;
            temp->left->data = data;
            return root;
        } else {
            q.push(temp->left);
        }
        if (temp->right == nullptr) {
            temp->right = new node;
            temp->right->left = nullptr;
            temp->right->right = nullptr;
            temp->right->data = data;
            return root;
        } else {
            q.push(temp->right);
        }
    }
}

void Breadthfs::bfs() {
    if (!root) {
        cout << "Tree is empty." << endl;
        return;
    }
    queue<node*> q;
    q.push(root);
    int qSize;
    while (!q.empty()) {
        qSize = q.size();
        
#pragma omp parallel for
        for (int i = 0; i < qSize; i++) {
            node* currNode;
#pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << "\t" << currNode->data;
            }
#pragma omp critical
            {
                if (currNode->left)
                    q.push(currNode->left);
                if (currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}

void Breadthfs::dfs() 
{
    if (!root) {
        cout << "Tree is empty." << endl;
        return;
    }
    stack<node*> s;
    s.push(root);
    while (!s.empty()) {
        int stackSize = s.size(); // Store the current size of the stack
        #pragma omp parallel for
        for (int i = 0; i < stackSize; ++i) {
            node* currNode;
            #pragma omp critical
            {
                currNode = s.top();
                s.pop();
            }
            cout << "\t" << currNode->data; // Print the value of the node
            #pragma omp critical
            {
                if (currNode->right)
                    s.push(currNode->right);
                if (currNode->left)
                    s.push(currNode->left);
            }
        }
    }
}


int main() {
    Breadthfs tree;
    int data;
    char ans;
    int N;
    cout<<"Enter the Number of Nodes in the Tree:- ";
    cin>>N;
    for (int i=0;i<N;i++) {
        cout << "\nEnter the value/number => ";
        cin >> data;
        tree.insert(data);    
    } 
    cout<<"The BFS of the Given Tree is:- ";
    tree.bfs();
    cout<<"\n";
    cout<<"The DFS of the Given Tree is:- ";
    tree.dfs();

    return 0;
}
