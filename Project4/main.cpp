#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;

#define MAX 1000000
struct Node {
    int key;
    Node *left, *right;
};
Node* insert(int val, Node* root);
Node* deletion(int val, Node* root);
bool search(int val, Node* root);
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);
int depth(Node* root);
void levelorder(Node* root);
void currentlevel(Node* root, int i);
Node* head = NULL;
int nodes;



Node* newNode(int val) {
    Node* temp = new Node;
    temp->key = val;
    temp->left = temp->right = NULL;
    nodes++;
    if(nodes == 1) {
        head = temp;
    }
    return temp;
}

int main() {
    int queries;
    cout << "Insert number of queries: ";
    cin >> queries;
    cin.ignore();

    for (int i = 0; i < queries; i++) {
        string input;
        getline(cin, input);

        int pos = input.find(" ");
        string function = input.substr(0, pos);
        string number = input.substr(pos + 1);



        if(function == "Insert") {
            int key = stoi(number);
            insert(key, head);
        }
        else if(function == "Delete") {
            int key = stoi(number);
            deletion(key, head);
        }
        else if(function == "Search") {
            int key = stoi(number);
            (search(key, head)) ? cout << true : cout << false;
        }
        else {
            function = input;
        if(function == "Inorder") {
            inorder(head);
            cout << endl;
        }
        else if(function == "Preorder"){
            preorder(head);
            cout << endl;
        }
        else if(function == "Postorder") {
            postorder(head);
            cout << endl;
        }
        else if(function == "Levelorder") {
            levelorder(head);
            cout << endl;
        }
        else {
            cout << "Not A Function";
            i--;
        }
        }
    }
}

void inorder(Node* root) {
    if(root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->key <<" ";
    inorder(root->right);
}

void preorder(Node* root) {
    if(root == NULL) {
        return;
    }
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);

}

void postorder(Node* root) {
    if(root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

void levelorder(Node* root) {
    int dep = depth(root);
    for(int i = 0; i < dep; i++) {
        currentlevel(root, i);
    }
}

void currentlevel(Node* root, int i) {
    if(root == NULL) {
        return;
        if(i == 0) {
            cout << root->key << " ";
        }
        else {
            currentlevel(root->left, i--);
            currentlevel(root->right, i--);
        }
    }
}

int depth(Node* root) {
    if(root == NULL) {
        return  0;
    }
    int ldepth = depth(root->left);
    int rdepth = depth(root->right);
    if(ldepth > rdepth) {
        return ldepth + 1;
    }
    else {
        return rdepth + 1;
    }

}




Node* insert(int val, Node* root) {
    if(root == NULL) {
        return newNode(val);
    }

    if(val < root->key) {
        root->left = insert(val, root->left);
    }
    else {
        root->right = insert(val, root->right);
    }
    return root;
}

Node* deletion(int val, Node* root) {
    if(root == NULL) {
        return root;
    }

    if(root->key > val) {
        root->left = deletion(val, root->left);
        return root;
    }
    else if(root->key < val) {
        root->right = deletion(val, root->right);
        return root;
    }

    if(root->left == NULL) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    else if(root->right == NULL) {
        Node* temp = root->left;
        delete root;
        return temp;
    }

    else {
        Node* successor = root->right;

        while(successor != NULL) {
            successor = successor->left;
        }
    }

}

bool search(int val, Node* root) {
    for(int i = 0; i < nodes; i++) {
        if(val == root->key) {
            return true;
        }
        if(val > root->key) {
            root = root->right;
        }
        else root = root->left;
    }
    return false;
}