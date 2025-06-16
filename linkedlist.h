//
// Created by Keller3D on 06.05.2025.
//

#ifndef PROGA2_STACK_H
#define PROGA2_STACK_H
#include <cmath>
#endif //PROGA2_STACK_H
struct Node {
    int data;
    Node *next;
};

void printLinkedList(Node *head, ostream &out) {
    Node *p = head;
    while (p != nullptr) {
        out << p->data << " ";
        p = p->next;

    }
    out << endl;
}

int getlenLinkedList(Node *head) {
    Node *p = head;
    int c = 0;
    while (p != nullptr) {
        c++;
        p = p->next;

    }
    return c;
}

Node *createLinkedList(ifstream &in) {
    Node *top = nullptr;
    int m;
    in >> m;
    if (m == 0) return top;
    top = new Node;
    in >> top->data;

    if (m == 1) {
        top->next = nullptr;
    } else {
        top->next = new Node;
        Node *p = top;
        for (int i = 0; i < m - 1; i++) {
            p->next = new Node;
            p = p->next;
            in >> p->data;
            p->next = nullptr;

        }
    }
    return top;
}


int maxLinkedList(Node *head) {
    Node *p = head;
    int mx = INT_MIN;
    while (p != nullptr) {
        mx = max(mx, p->data);
        p = p->next;
    }
    return mx;
}

int minLinkedList(Node *head) {
    if (!head) return 0;
    Node *p = head;
    int mx = INT_MAX;
    while (p != nullptr) {
        mx = min(mx, p->data);
        p = p->next;
    }
    return mx;
}

bool isPositiveLinkedList(Node *head) {
    Node *p = head;
    while (p != nullptr) {
        if (p->data <= 0) {
            return false;
        }
        p = p->next;
    }
    return true;
}

bool findLinkedList(Node *head, int val) {
    Node *p = head;

    while (p != nullptr) {
        if (p->data == val) {
            return true;
        }
        p = p->next;
    }
    return false;
}

void swapMinMaxLinkedList(Node *&head) {
    Node *pmax = head;
    Node *pmin = head;
    Node *p = head->next;
    while (p != nullptr) {
        if (pmax->data < p->data) pmax = p;
        if (pmin->data > p->data) pmin = p;
        p = p->next;
    }
    swap(pmax->data, pmin->data);
}

bool isAscendingLinkedList(Node *head) {
    Node *p = head->next;
    while (p && p->next) {
        if (p->data > p->next->data) {
            return false;
        }
        p = p->next;
    }
    return true;
}

void newheadLinkedList(Node *&head, int x) {
    Node *q = new Node;
    q->data = x;
    q->next = head;
    head = q;
}

void insertLinkedList(Node *&p, int x) {
    Node *q = new Node;
    q->data = x;
    q->next = p->next;
    p->next = q;
}

void deleteheadLinkedList(Node *&head) {
    Node *p = head;
    head = head->next;
    delete p;
}

void deletenodeLinkedList(Node *&p) {
    Node *q = p->next;
    p->next = p->next->next;
    delete q;
}

void deleteLinkedList(Node *&head) {
    while (head) {
        deleteheadLinkedList(head);
    }
}

void deleteAllxNodes(Node *&head, int x) {
    while (head->data == x) {
        deleteheadLinkedList(head);
    }
    Node *p = head;
    while (p->next) {
        if (p->next->data == x) {
            deletenodeLinkedList(p);
        }
        p = p->next;
    }
}

void insertNodeAfter(Node *&head, int x, int y) {
    Node *p = head;
    while (p) {
        if (p->data == x) {
            insertLinkedList(p, y);
        }
        p = p->next;
    }
}
bool is_prime(int x){
    if (x <= 1){
        return false;
    }
    if (x == 2){
        return true;
    }
    if (x % 2 == 0){
        return false;
    }
    for (int i = 3; i <= sqrt(x); i+=2){
        if (x % i == 0){
            return false;
        }
    }
    return true;
}
void EndToStart(Node *&head) {
    Node *p = head;
    while (!p->next->next) {
        p = p->next;
    }
    newheadLinkedList(head, p->next->data);
    deletenodeLinkedList(p);
}
int proisvPrimesLinkedList(Node *head){
    int proisv = 1;
    Node *p = head;
    while (p != nullptr) {
        if (is_prime(p->data)) {
            proisv *= p->data;
        }
        p = p->next;
    }
    return proisv;
}