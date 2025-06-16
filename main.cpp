#include <iostream>
#include <fstream>
#include <cstring>
#include "abiturients.h"
#include "stringtasks.h"
#include "cmath"


using namespace std;

// Константы

//void LinkedList() {
//    ifstream in1("test1.txt");
//    int n;
//    cout << "Введите n -> ";
//    cin >> n;
//    Node **arrlist = new Node *[n];
//    for (int i = 0; i < n; ++i) {
//        arrlist[i] = createLinkedList(in1);
//    }
//    for (int i = 0; i < n; ++i) {
//        cout << "List" << i + 1 << " ";
//        printLinkedList(arrlist[i], cout);
//        cout << endl;
//    }
//    bool flag = true;
//    for (int i = 0; i < n && flag; ++i) {
//        if (!isPositiveLinkedList(arrlist[i])) {
//            flag = false;
//        }
//    }
//    int c;
//    if (flag) {
//        c = 0;
//
//        for (int i = 0; i < n; ++i) {
//            c += minLinkedList(arrlist[i]);
//        }
//    } else {
//        c = 1;
//        for (int i = 0; i < n; ++i) {
//            c *= proisvPrimesLinkedList(arrlist[i]);
//        }
//    }
//    cout << c;
//}

//struct Stack {
//    tdata *mas;
//    int top;
//    int n;
//};
//
//bool empty(Stack stack) {
//    return stack.top == -1;
//}
//
//Stack create(int n) {
//    Stack stack;
//    stack.top = -1;
//    stack.n = n;
//    stack.mas = new tdata[stack.n];
//
//    return stack;
//}
//
//void push(Stack &stack, tdata x) {
//    if (stack.top == stack.n) {
//        cout << "Стек переполнен" << endl;
//    } else {
//        stack.mas[++stack.top] = x;
//    }
//}
//
//tdata pop(Stack &stack) {
//    if (!empty(stack)) {
//        return stack.mas[stack.top--];
//    } else {
//        cout << "Стек пуст" << endl;
//    }
//}
//

void task() {
    ifstream in("in.txt");
    ofstream out("out.txt");
    ofstream extraout("extraout.txt");

    if (!in || !out || !extraout) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    int n; // Количество мест
    cin >> n;

    Applicant applicants[1000];
    int count = 0;

    char line[500];
    while (in.getline(line, sizeof(line)) && count < 1000) {
        readApplicant(line, applicants[count]);
        count++;
    }

    sortApplicants(applicants, count);

    int lastAcceptedIndex = 0;
    for (int i = 0; i < n && i < count; ++i) {
        writeApplicant(out, applicants[i]);
        lastAcceptedIndex = i;
    }

    if (lastAcceptedIndex < count - 1 &&
        applicants[lastAcceptedIndex].totalScore == applicants[lastAcceptedIndex + 1].totalScore) {
        for (int i = lastAcceptedIndex + 1; i < count; ++i) {
            if (applicants[i].totalScore == applicants[lastAcceptedIndex].totalScore) {
                writeApplicant(extraout, applicants[i]);
            } else {
                break;
            }
        }
    }

    in.close();
    out.close();
    extraout.close();
}

double operat(int n, double *arr, char oper[3]) {
    double arr_min = 10000000000.0;
    double arr_max = -100000000000.0;
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
        if (arr[i] > arr_max) {
            arr_max = arr[i];
        }
        if (arr[i] < arr_min) {
            arr_min = arr[i];
        }
    }
    if (oper[2] == 'N') {
        return arr_min;
    } else if (oper[2] == 'X') {
        return arr_max;
    } else {
        return sum;
    }
}

int txt_to_bin() {
    int count = 0;
    ifstream txtin("task1.txt");
    ofstream binout("task1.bin", ios::binary);
    int n;
    while (txtin >> n) {
        auto *arr = new double[n];
        for (int i = 0; i < n; ++i) {
            txtin >> arr[i];
        }
        auto *op = new char[3];
        txtin >> op;
        count++;
        binout.write((char *) &n, sizeof(n));
        binout.write((char *) arr, sizeof(double) * n);
        binout.write((char *) op, sizeof(char) * 3);
        delete[] arr;
        delete[] op;
    }
    txtin.close();
    binout.close();
    return count;
}

void solution(int count) {
    ifstream binin("task1.bin", ios::binary);
    ofstream txtout("task1final.txt");
    int n;
    for (int i = 0; i < count; ++i) {
        binin.read((char *) &n, sizeof(int));
        auto *arr = new double[n];
        auto *op = new char[3];
        binin.read((char *) arr, sizeof(double) * n);
        binin.read((char *) op, sizeof(char) * 3);
        cout << operat(n, arr, op) << endl;
        txtout << n << " ";
        for (int j = 0; j < n; j++) {
            txtout << arr[j] << " ";
        }
        for (int j = 0; j < 3; j++) {
            txtout << op[j];
        }
        txtout << endl;
        delete[] arr;
        delete[] op;
    }
    txtout.close();
    binin.close();
};

void task_first() {
    int a = txt_to_bin();
    solution(a);
}

void automat() {
    ifstream in("class1.txt");
    char c;
    int state = 0;
    char par;
    int a = 0;
    int b = 0;
    bool f = true;
    int sign = 1;
    while (in.get(c) && f) {
        switch (state) {
            case -1:
                f = false;
                break;
            case 0:
                if (c == '(' or c == '[') {
                    par = c;
                    state = 1;
                } else {
                    state = -1;
                }
                break;
            case 1:
                if (c == '+') {
                    state = 2;
                    break;

                } else if (c == '-') {
                    state = 2;
                    sign = -1;
                    break;

                } else if ('0' <= c and c <= '9') {
                    a = c - '0';
                    state = 2;
                    break;

                } else {
                    state = -1;
                    break;
                }
            case 2:
                if ('0' <= c and c <= '9') {
                    a = a * 10 + (c - '0');
                    break;
                } else if (c == ',') {
                    a *= sign;
                    state = 3;
                    sign = 1;
                    break;
                } else {
                    state = -1;
                    break;
                }
            case 3:

                if (c == '+') {
                    state = 4;
                    break;

                } else if (c == '-') {
                    state = 4;
                    sign = -1;
                    break;

                } else if ('0' <= c and c <= '9') {
                    b = c - '0';
                    state = 4;
                    break;

                } else {
                    state = -1;
                    break;
                }
            case 4:
                if ('0' <= c and c <= '9') {
                    b = b * 10 + (c - '0');
                    break;
                } else if (c == ')' or c == ']') {
                    b *= sign;
                    state = 5;
                    if (par == '[' and c == ']' and a == b) {
                        state = 5;
                    } else if (a < b) {
                        state = 5;
                    } else {
                        state = -1;
                    }
                    break;
                } else {
                    state = -1;
                    break;
                }
            case 5:
                state = -1;
        }
    }
    if (state == -1) {
        cout << "NO";
    } else {
        cout << "YES";
    }
    in.close();
}

void diagram3() {
    bool f = true;
    char c;
    ifstream in("diagram2.txt");
    in.get(c);
    if (c == '0') {
        f = !in.get(c);
    } else if (c == '+' || c == '-') {
        in.get(c);
        if (!(c >= '1' && c <= '9')) {
            f = false;
        }
    } else if (!(c >= '1' && c <= '9')) f = false;

    while (f && in.get(c)) {
        if (!(c >= '0' && c <= '9')) {
            f = false;
        }
    }
    if (f) {
        cout << "YES";
    } else {
        cout << "NO";
    }

}

void printarray(char *arr) {
    for (int i = 0; i < strlen(arr); i++) {
        cout << arr[i];

    }
    cout << '\n';
}


bool isletter(char symbol) {
    return 'a' <= symbol && symbol <= 'z';
}


void stack2() {
    ifstream in("stack2.txt");
    char c;
    bool f = true;
    char stack[50];
    int top = -1;
    while (in.get(c) && f) {
        if (top == -1) {
            if (c == '(') {
                stack[++top] = c;
            } else {
                f = false;
            }
        } else if (stack[top] == '(') {
            if (c == '(') {
                stack[++top] = c;
            } else if (stack[top] == ')') {
                top--;
            } else if (isletter(stack[top])) {
                stack[++top] = 'L';
            } else {
                f = false;
            }
        } else if (stack[top] == 'L') {
            if (c == ',') {
                stack[++top] = c;
            } else if (c == ')') {
                if (stack[top - 1] == '(') {
                    top -= 2;
                }
            } else {
                f = false;
            }
        } else if (stack[top] == ',') {
            if (stack[top] == '(') {
                if (c == '(') {
                    stack[++top] = c;
                } else if (isletter(c)) {
                    if (isletter(stack[top - 1])) {
                        top -= 1;
                    }
                } else {
                    f = false;
                }
            }
        } else if (stack[top] == ')') {
            if (c == ',') {
                stack[++top] = c;
            } else {
                f = false;
            }
        } else {
            f = false;
        }
    }
    cout << f;
}

typedef int tdata;


struct TreeNode {
    tdata data;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *createNode(tdata x) {
    TreeNode *q = new TreeNode;
    q->data = x;
    q->left = nullptr;
    q->right = nullptr;
    return q;
}

void insert(TreeNode *&root, tdata x) {
    if (root == nullptr) {
        root = createNode(x);
        return;
    } else {
        TreeNode *q = root;
        while (q) {
            if (x < q->data) {
                if (q->left) {
                    q = q->left;
                } else {
                    q->left = createNode(x);
                    return;
                }
            } else if (x > q->data) {
                if (q->right) {
                    q = q->right;
                } else {
                    q->right = createNode(x);
                    return;
                }
            } else {
                cout << "Невозможно добавить, так как элемент уже в дереве";
                return;
            }
        }
    }
}

TreeNode *createTree(ifstream &in) {
    tdata x;
    TreeNode *root = nullptr;
    while (in >> x) {
        insert(root, x);
    }
    return root;
}

bool search(TreeNode *root, tdata x) {
    if (root == nullptr) return false;
    TreeNode *q = root;
    while (q) {
        if (x == q->data) {
            return true;
        } else if (x < q->data) {
            if (q->left) {
                q = q->left;
            } else {
                return false;
            }
        } else {
            if (q->right) {
                q = q->right;
            } else {
                return false;
            }
        }
    }
    return false;
}

/*
void klp(TreeNode *root) {
    cout << root->data << " ";
    if (root->left) {
        klp(root->left);
    }
    if (root->right) {
        klp(root->right);
    }
}

void lkp(TreeNode *root) {
    cout << root->data << " ";
    if (root->left) {
        klp(root->left);
    }
    if (root->right) {
        klp(root->right);
    }
}

void lpk(TreeNode *root) {
    cout << root->data << " ";
    if (root->left) {
        klp(root->left);
    }
    if (root->right) {
        klp(root->right);
    }
}
*/
struct Stack {
    TreeNode *data;
    Stack *next;

};

Stack *createStack() {
    return nullptr;
}

bool empty(Stack *stack) {
    return stack == nullptr;
}

void push(Stack *&stack, TreeNode *x) {
    Stack *p = new Stack;
    p->data = x;
    p->next = stack;
    stack = p;
}

TreeNode *pop(Stack *&stack) {
    TreeNode *x = stack->data;
    Stack *p = stack;
    stack = stack->next;
    delete p;
    return x;
}

void klp(TreeNode *&root) {
    if (root == nullptr) return;
    TreeNode *p;
    Stack *stack = createStack();
    push(stack, root);
    while (!empty(stack)) {
        p = pop(stack);
        cout << p->data << " ";
        if (p->right) {
            push(stack, p->right);
        }
        if (p->left) {
            push(stack, p->left);
        }
    }
}

void lkp(TreeNode *root) {
    if (root == nullptr) return;
    TreeNode *p = root;
    Stack *stack = createStack();
    while (!empty(stack) || p) {
        while (p) {
            push(stack, p);
            p = p->left;

        }
        TreeNode *q = pop(stack);
        cout << q->data << " ";
        p = q->right;

    }
}

void lpk(TreeNode *root) {
    if (root == nullptr) return;
    TreeNode *p;
    Stack *stack = createStack();
    Stack *skebob = createStack();
    push(stack, root);
    while (!empty(stack)) {
        p = pop(stack);
        push(skebob, p);
        if (p->left) push(stack, p->left);
        if (p->right) push(stack, p->right);

    }
    while (!empty(skebob)) {
        p = pop(skebob);
        cout << p->data << " ";

    }
}

struct queue_node {
    TreeNode *data;
    queue_node *next;
};
struct queue {
    queue_node *head;
    queue_node *tail;
};

queue qcreate() {
    queue q;
    q.head = nullptr;
    q.tail = nullptr;
    return q;
}

bool qempty(queue q) {
    return q.head == nullptr;
}


void bfs(TreeNode *root) {

}

void treetest() {
    ifstream in("tree.txt");
    TreeNode *root = createTree(in);
    lpk(root);
}

TreeNode *find(TreeNode *root, TreeNode *&pred, tdata x) {
    bool f = false;
    TreeNode *p = root;
    pred = root;
    while (p && !f) {
        if (p->data == x) f = true;
        else if (p->data < x) {
            pred = p;
            p = p->right;
        } else if (p->data > x) {
            pred = p;
            p = p->left;
        }
    }
    if (f) return p;
    else return nullptr;
}

TreeNode *maxi(TreeNode *root, TreeNode *&pred) {
    TreeNode *p = root;
    while (p->right) {
        pred = p;
        p = p->right;
    }
    return p;
}

TreeNode *mixi(TreeNode *root, TreeNode *&pred) {
    TreeNode *p = root;
    while (p->left) {
        pred = p;
        p = p->left;
    }
    return p;
}

void deletenode(TreeNode *&p, TreeNode *pred) {
    if (!p->left && !p->right) {
        if (p == pred->left) {
            pred->left = nullptr;
            delete p;
        } else {
            pred->right = nullptr;
            delete p;
        }
    } else if ((p->left && !p->right) || (!p->left && p->right)) {
        if (p->left) {
            if (p == pred->left) {
                TreeNode *p1 = p;
                pred->left = p->left;
                delete p1;
            } else {
                TreeNode *p1 = p;
                pred->right = p->left;
                delete p1;
            }
        }else{
            if (p == pred->left) {
                TreeNode *p1 = p;
                pred->left = p->right;
                delete p1;
            } else {
                TreeNode *p1 = p;
                pred->right = p->right;
                delete p1;
            }
        }
    }else{
        TreeNode* maxx = maxi(p->left, pred);
        p->data = maxx->data;
        pred->right = nullptr;
        delete maxx;

    }
}

void deletex(TreeNode *&root, tdata x) {
    TreeNode *pred;
    TreeNode *p = find(root, pred, x);
    if (p) deletenode(p, pred);
    else cout << "Ошибкв";
}
void insert_rec(TreeNode *&root, tdata x){
    if (root== nullptr){
        root = createNode(x);
        return;
    }if (root->data == x){
        return;
    }
    if (root->data < x) insert_rec(root->right, x);
    if (root->data > x) insert_rec(root->left, x);
}
bool search_x_rec(TreeNode *&root, tdata x){
    if (root == nullptr) return false;
    if (root->data == x) return true;
    if(root->data > x) return search_x_rec(root->right, x);
    if(root->data < x) return search_x_rec(root->left, x);
}
void klp_rec(TreeNode *&root){
    
}
int main() {
    treetest();

    system("chcp 65001");
    return 0;
}
