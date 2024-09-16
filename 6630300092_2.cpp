#include <iostream>
using namespace std;

struct Node {
    int dest;
    Node* next;

    Node(int destVal) : dest(destVal), next(NULL) {}
};

struct List {
    Node* head;
    Node* tail;

    List() : head(NULL), tail(NULL) {}
};

const int BFS_START = 1;
const int adjSize = 8;
List* adjList[adjSize];
int FORM[adjSize];
int DISTANCE[adjSize];
bool VISITED[adjSize];

void init() {
    for (int i = 0; i < adjSize; i++) {
        adjList[i] = new List();
        FORM[i] = -1;
        DISTANCE[i] = -1;
        VISITED[i] = false;
    }
}

void showAdjList();
void addEdge(int src, int dest);
void enQue(int dest, List*& ls);
void deQue(List*& ls);
void BFS();
int getFront(List* ls);

int main() {
    int choose;
    init();

    do {
        cout << "========MENU======\n"
             << "1) Input adjacency list\n"
             << "2) BFS\n"
             << "3) Search path\n"
             << "4) Exit\n";
        cout << "Please choose > ";
        cin >> choose;

        switch (choose) {
            case 1:
                int dest;
                for (int src = 0; src < adjSize; src++) {
                    cout << "Enter # " << src << " : ";
                    cin >> dest;
                    while (dest != -1) {
                        addEdge(src, dest);
                        cin >> dest;
                    }
                }
                showAdjList();
                break;

            case 2:
                BFS();
                break;

            case 3:

                break;

            case 4:
                cout << "End!!";
                break;
        }
        cout << endl;

    } while (choose != 4);

    return 0;
}

void enQue(int dest, List*& ls) {
    Node* newNode = new Node(dest);

    if (ls->head == NULL) {
        ls->head = newNode;
        ls->tail = newNode;
    } else {
        ls->tail->next = newNode;
        ls->tail = newNode;
    }
}

void deQue(List*& ls) {
    if (ls == NULL || ls->head == NULL)
        return;

    Node* temp = ls->head;
    ls->head = ls->head->next;

    if (ls->head == NULL) {
        ls->tail = NULL;
    }

    delete temp;
}

void showAdjList() {
    for (int i = 0; i < adjSize; i++) {
        Node* p = adjList[i]->head;
        cout << "#" << i << ": ";
        while (p != NULL) {
            cout << p->dest << " ";
            p = p->next;
        }
        cout << endl;
    }
}

int getFront(List* ls) {
    if (ls == NULL || ls->head == NULL) {
        cout << "List is empty" << endl;
        return -1;
    }

    return ls->head->dest;
}

void addEdge(int src, int dest) {
    if (src != dest) {
        enQue(dest, adjList[src]);
    }
}


void BFS() {
    List* ls = new List();
    enQue(BFS_START, ls);

    FORM[BFS_START] = 1;
    DISTANCE[BFS_START] = 0;
    VISITED[BFS_START] = true;

    while (ls->head != NULL) {
        int u = getFront(ls);
        deQue(ls);

        Node* p = adjList[u]->head;
        while (p != NULL) {
            int v = p->dest;
            if (!VISITED[v]) {
                enQue(v, ls);
                FORM[v] = u;
                DISTANCE[v] = DISTANCE[u] + 1;
                VISITED[v] = true;
            }
            p = p->next;
        }
    }

    delete ls;


    cout << "    |   d  |   pred " << endl;
    cout << "=====================" << endl;
    for (int i = 0; i < adjSize; i++) {
        cout << i << "   |" << DISTANCE[i] << "   |   " << FORM[i] << endl;
    }
}
