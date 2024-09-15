#include <iostream>
using namespace std;

struct Node {
    int src;
    int dest;
    Node* next;

    Node(int srcVal, int destVal) : src(srcVal), dest(destVal), next(NULL) {}
};

const int adjSize = 6;
Node* adjList[adjSize];
void showAdjList();
void addEdge();
void insertAdj(int src, int dest, Node*& head, Node*& tail);
bool isSelfLoop(int src, int dest);

int main() {
    int choose;

    // Initialize adjList to NULL
    for (int i = 0; i < adjSize; i++) {
        adjList[i] = NULL;
    }

    do {
        cout << "========MENU======\n"
             << "1) Input adjacency list\n"
             << "2) Show self loop from adjacency list\n"
             << "3) Exit\n";
        cout << "Please choose > ";
        cin >> choose;

        switch (choose) {
            case 1:
                addEdge();
                showAdjList();
                break;

            case 2:
                for (int i = 0; i < adjSize; i++) {
                    Node* p = adjList[i];
                    while (p != NULL) {
                        if (isSelfLoop(p->src, p->dest)) {
                            cout << "Self loop: " << p->src << endl;
                            break;
                        }
                        p = p->next;
                    }
                }
                break;

            case 3:
                cout << "End!!";
                break;
        }
        cout << endl;

    } while (choose != 3);

    return 0;
}

void addEdge() {
    int dest;

    for (int src = 0; src < adjSize; src++) {
        Node* tail;
        cout << "Enter # " << src << " : ";
        cin >> dest;

        Node* head = NULL;
        tail = NULL;

        while (dest != -1) {
            insertAdj(src, dest, head, tail);
            cin >> dest;
        }

        adjList[src] = head;
    }
}

void insertAdj(int src, int dest, Node*& head, Node*& tail) {
    Node* newNode = new Node(src, dest);

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void showAdjList() {
    for (int i = 0; i < adjSize; i++) {
        Node* p = adjList[i];
        if (p != NULL) {
            cout << "#" << p->src << ": ";
            while (p != NULL) {
                cout << p->dest << " ";
                p = p->next;
            }
            cout << endl;
        }
    }
}

bool isSelfLoop(int src, int dest) {
    return src == dest;
}
