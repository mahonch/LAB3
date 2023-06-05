#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
    int data;
    Node* left, * right;
};


Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


void recursiveTraversal(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    recursiveTraversal(root->left);
    recursiveTraversal(root->right);
}

void iterativeTraversal(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left != NULL) q.push(curr->left);
        if (curr->right != NULL) q.push(curr->right);
    }
}


Node* insertNode(Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data) root->left = insertNode(root->left, data);
    else if (data > root->data) root->right = insertNode(root->right, data);
    return root;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) return root;
    if (data < root->data) root->left = deleteNode(root->left, data);
    else if (data > root->data) root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = root->right;
        while (temp->left != NULL) temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int nodesOnLevel(Node* root, int level) {
    if (root == NULL) return 0;
    if (level == 1) return 1;
    return nodesOnLevel(root->left, level - 1) + nodesOnLevel(root->right, level - 1);
}

int main() {

    setlocale(LC_ALL, "Ru");
    Node* root = NULL;
    int option, value;

    do {
        cout << "\n1. Добавить элемент\n2. Удалить элемент\n3. Рекурсивный вывод дерева\n4. Нерекурсивный вывод дерева\n5. Количество узлов на выбранном уровне\n6. Выход\n";
        cin >> option;

        switch (option) {
        case 1:
            cout << "Введите значение: ";
            cin >> value;
            root = insertNode(root, value);
            break;
        case 2:
            cout << "Введите значение: ";
            cin >> value;
            root = deleteNode(root, value);
            break;
        case 3:
            recursiveTraversal(root);
            cout << endl;
            break;
        case 4:
            iterativeTraversal(root);
            cout << endl;
            break;
        case 5:
            int level;
            cout << "Введите уровень: ";
            cin >> level;
            cout << "Количество узлов на уровне " << level << ": " << nodesOnLevel(root, level) << endl;
            break;
        case 6:
            cout << "До свидания!\n";
            break;
        default:
            cout << "Некорректный ввод!\n";
        }
    } while (option != 6);

    return 0;
}