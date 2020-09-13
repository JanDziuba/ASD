#include <iostream>
#include <algorithm>

#define DIVISOR 1000000007

using namespace std;

struct Node {
    int priority;
    int key;
    bool isRoman;
    long long numberOfSelections;
    long long numberOfSelectionsEnd0;
    long long numberOfSelectionsStart0;
    long long numberOfSelectionsStart0End0;
    Node *left;
    Node *right;
    bool reversed;
    

    Node(int priority, int key, bool isRoman) :
            priority(priority),
            key(key),
            isRoman(isRoman),
            left(nullptr),
            right(nullptr),
            reversed(false),
            numberOfSelections(-1),
            numberOfSelectionsStart0End0(-1),
            numberOfSelectionsStart0(-1),
            numberOfSelectionsEnd0(-1) {}
};

void heapify(Node *root) {
    if (!root) return;
    Node *max = root;
    if (root->left != nullptr && root->left->priority > max->priority)
        max = root->left;
    if (root->right != nullptr && root->right->priority > max->priority)
        max = root->right;
    if (max != root) {
        swap (root->priority, max->priority);
        heapify (max);
    }
}

Node *build(bool *isRomanArray, int n) {
    if (n == 0) return nullptr;
    int mid = n / 2;
    Node *treap = new Node (rand(), n, isRomanArray[mid]);
    treap->left = build (isRomanArray, mid);
    treap->right = build(isRomanArray + mid + 1, n - mid - 1);
    heapify (treap);
    return treap;
}

void buildSelections(Node *root);

void reverse(Node *root) {
    root->reversed = !root->reversed;
}

void reverseChildren(Node *root) {
    root->reversed = !root->reversed;

    swap(root->left, root->right);

    if (root->left != nullptr) {
        reverse(root->left);
    }
    if (root->right != nullptr) {
        reverse(root->right);
    }

    swap(root->numberOfSelectionsStart0, root->numberOfSelectionsEnd0);
}

void buildChildren(Node *root) {

    if (root->reversed) {
        reverseChildren(root);
    }

    if (root->left != nullptr) {

        if (root->left->reversed) {
            reverseChildren(root->left);
        }

        Node *left = root->left;
        if ((left->numberOfSelections == -1) || (left->numberOfSelectionsStart0 == -1) ||
        (left->numberOfSelectionsEnd0 == -1) || (left->numberOfSelectionsStart0End0 == -1)) {
            buildSelections(left);
        }
    }

    if (root->right != nullptr) {

        if (root->right->reversed) {
            reverseChildren(root->right);
        }

        Node *right = root->right;
        if ((right->numberOfSelections == -1) || (right->numberOfSelectionsStart0 == -1) ||
        (right->numberOfSelectionsEnd0 == -1) || (right->numberOfSelectionsStart0End0 == -1)) {
            buildSelections(right);
        }
    }
}

void buildSelections(Node *root) {
    buildChildren(root);

    if (root->left == nullptr && root->right == nullptr) {

        root->numberOfSelections = 1;
        if (root->isRoman == true) {
            root->numberOfSelectionsEnd0 = 0;
            root->numberOfSelectionsStart0 = 0;
            root->numberOfSelectionsStart0End0 = 0;
        } else {
            root->numberOfSelectionsEnd0 = 1;
            root->numberOfSelectionsStart0 = 1;
            root->numberOfSelectionsStart0End0 = 1;
        }

    }
    else if (root->left == nullptr) {

        if (root->isRoman == true) {
            root->numberOfSelections = (root->right->numberOfSelections * 2 + 1) % DIVISOR;
            root->numberOfSelectionsStart0 = root->right->numberOfSelectionsStart0;
            root->numberOfSelectionsEnd0 = (root->right->numberOfSelectionsEnd0 * 2) % DIVISOR;
            root->numberOfSelectionsStart0End0 = root->right->numberOfSelectionsStart0End0;
        } else {
            root->numberOfSelections = ((root->right->numberOfSelections * 2 + 1 - root->right->numberOfSelectionsStart0) % DIVISOR + DIVISOR) % DIVISOR;
            root->numberOfSelectionsStart0 = (root->right->numberOfSelections + 1) % DIVISOR;
            root->numberOfSelectionsEnd0 = ((root->right->numberOfSelectionsEnd0 * 2 + 1 - root->right->numberOfSelectionsStart0End0) % DIVISOR + DIVISOR) % DIVISOR;
            root->numberOfSelectionsStart0End0 = (root->right->numberOfSelectionsEnd0 + 1) % DIVISOR;
        }

    }
    else if (root->right == nullptr) {

        if (root->isRoman == true) {
            root->numberOfSelections = (root->left->numberOfSelections * 2 + 1) % DIVISOR;
            root->numberOfSelectionsStart0 = (root->left->numberOfSelectionsStart0 * 2) % DIVISOR;
            root->numberOfSelectionsEnd0 = root->left->numberOfSelectionsEnd0;
            root->numberOfSelectionsStart0End0 = root->left->numberOfSelectionsStart0End0;
        } else {
            root->numberOfSelections = ((root->left->numberOfSelections * 2 + 1 - root->left->numberOfSelectionsEnd0) % DIVISOR + DIVISOR) % DIVISOR;
            root->numberOfSelectionsStart0 = ((root->left->numberOfSelectionsStart0 * 2 + 1 - root->left->numberOfSelectionsStart0End0) % DIVISOR + DIVISOR) % DIVISOR;
            root->numberOfSelectionsEnd0 = (root->left->numberOfSelections + 1) % DIVISOR;
            root->numberOfSelectionsStart0End0 = (root->left->numberOfSelectionsStart0 + 1) % DIVISOR;
        }

    }
    else {

        long long tmpSelections;
        long long tmpSelectionsStart0;
        long long tmpSelectionsEnd0;
        long long tmpSelectionsStart0End0;
        
        Node *left = root->left;
        Node *right = root->right;
        
        // lączę lewe z korzeniem
        if (root->isRoman == true) {
            tmpSelections = (left->numberOfSelections * 2 + 1) % DIVISOR;
            tmpSelectionsStart0 = (left->numberOfSelectionsStart0 * 2) % DIVISOR;
            tmpSelectionsEnd0 = left->numberOfSelectionsEnd0;
            tmpSelectionsStart0End0 = left->numberOfSelectionsStart0End0;
        } else {
            tmpSelections = ((left->numberOfSelections * 2 + 1 - left->numberOfSelectionsEnd0) % DIVISOR + DIVISOR) % DIVISOR;
            tmpSelectionsStart0 = ((left->numberOfSelectionsStart0 * 2 + 1 - left->numberOfSelectionsStart0End0) % DIVISOR + DIVISOR) % DIVISOR;
            tmpSelectionsEnd0 = (left->numberOfSelections + 1) % DIVISOR;
            tmpSelectionsStart0End0 = (left->numberOfSelectionsStart0 + 1) % DIVISOR;
        }

        //dalej łącze połączenie z prawym
        root->numberOfSelections = (((tmpSelections + 1) * (right->numberOfSelections + 1) - 1 -
                (tmpSelectionsEnd0 * right->numberOfSelectionsStart0)) % DIVISOR + DIVISOR) % DIVISOR;
        
        root->numberOfSelectionsStart0 = ((right->numberOfSelectionsStart0 + tmpSelectionsStart0 *
                (right->numberOfSelections + 1) - tmpSelectionsStart0End0 * right->numberOfSelectionsStart0) % DIVISOR + DIVISOR) % DIVISOR;

        root->numberOfSelectionsEnd0 = ((tmpSelectionsEnd0 + (tmpSelections + 1) * right->numberOfSelectionsEnd0 -
                                        tmpSelectionsEnd0 * right->numberOfSelectionsStart0End0) % DIVISOR + DIVISOR) % DIVISOR;
        
        root->numberOfSelectionsStart0End0 = ((tmpSelectionsStart0End0 + right->numberOfSelectionsStart0End0 +
                tmpSelectionsStart0 * right->numberOfSelectionsEnd0 - tmpSelectionsStart0End0 * right->numberOfSelectionsStart0End0) % DIVISOR + DIVISOR) % DIVISOR;
    }
}

void updateKey(Node *root) {
    int key = 1;

    if (root->left != nullptr) {
        key += root->left->key;
    }

    if (root->right != nullptr) {
        key += root->right->key;
    }

    root->key = key;
}

void split(Node *root, int index, Node *&leftSplit, Node *&rightSplit) {

    if (!root) {
        leftSplit = nullptr;
        rightSplit = nullptr;
        return;
    }

    if (root->reversed) {
        reverseChildren(root);
    }

    int leftKey;

    if (root->left == nullptr) {
        leftKey = 0;
    } else {
        leftKey = root->left->key;
    }

    if (index < leftKey) {
        rightSplit = root;
        split(root->left, index, leftSplit, rightSplit->left);
    } else if (index > leftKey) {
        leftSplit = root;
        split(root->right, index - leftKey - 1, leftSplit->right, rightSplit);
    } else {
        leftSplit = root;
        rightSplit = root->right;
        leftSplit->right = nullptr;
    }
    buildSelections(root);
    updateKey(root);
}

void merge(Node *&root, Node *leftSplit, Node *rightSplit) {

    if (leftSplit != nullptr && leftSplit->reversed) {
        reverseChildren(leftSplit);
    }

    if (rightSplit != nullptr && rightSplit->reversed) {
        reverseChildren(rightSplit);
    }

    if (!leftSplit || !rightSplit) {
        if (leftSplit) root = leftSplit;
        else root = rightSplit;
    } else {
        if (leftSplit->priority > rightSplit->priority) {
            root = leftSplit;
            merge(root->right, leftSplit->right, rightSplit);
        } else {
            root = rightSplit;
            merge(root->left, leftSplit, rightSplit->left);
        }
    }
    buildSelections(root);
    updateKey(root);
}

void reverseInterval(Node *&root, int startIndex, int endIndex) {

    Node *leftFromStart;
    Node *interval;
    Node *rightFromStart;
    Node *rightFromEnd;

    split(root, startIndex - 1, leftFromStart, rightFromStart);

    split(rightFromStart, endIndex - startIndex, interval, rightFromEnd);

    reverse(interval);

    reverseChildren(interval);

    Node *tmp;

    merge(tmp, leftFromStart, interval);
    merge(root, tmp, rightFromEnd);
}

long long getIntervalSelections(Node *&root, int startIndex, int endIndex) {

    Node *leftFromStart;
    Node *interval;
    Node *rightFromStart;
    Node *rightFromEnd;
    long long numberOfSelections;

    split(root, startIndex - 1, leftFromStart, rightFromStart);

    split(rightFromStart, endIndex - startIndex, interval, rightFromEnd);

    numberOfSelections = interval->numberOfSelections;

    Node *tmp;

    merge(tmp, leftFromStart, interval);
    merge(root, tmp, rightFromEnd);

    return numberOfSelections;
}

void getInput(int &n, int &m, bool *&isRomanArray) {

    cin >> n;
    cin >> m;

    isRomanArray = new bool[n];

    char character;

    for (int i = 0; i < n; i++) {
        cin >> character;

        if(character == 'R') {
            isRomanArray[i] = true;
        } else if (character == 'G') {
            isRomanArray[i] = false;
        } else {
            cout << "błąd";
            exit(1);
        }
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int m;
    bool *isRomanArray = nullptr;

    getInput(n, m, isRomanArray);

    Node *root = build(isRomanArray, n);
    buildSelections(root);

    char command;
    int startIndex;
    int endIndex;

    for (int i = 0; i < m; i++) {
        cin >> command;
        cin >> startIndex;
        startIndex--;
        cin >> endIndex;
        endIndex--;

        if (command == '?') {
            cout << getIntervalSelections(root, startIndex, endIndex) << endl;
        } else if (command == 'O') {
            reverseInterval(root, startIndex, endIndex);
        } else {
            cout << "bład " << command << endl;
        }
    }
    return 0;
}
