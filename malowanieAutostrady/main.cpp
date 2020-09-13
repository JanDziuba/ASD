#include <iostream>
#include <vector>

using namespace std;

struct Interval {

    bool allBlack;
    bool allWhite;
    int numberOfWhite;
    int intervalStart;
    int intervalEnd;
};

// recursive
void setIntervalsInIntervalTree(vector<Interval> &roadIntervalTree, int &index, int &roadLength, int &intervalStart, int &maxIntervalEnd) {

    if (maxIntervalEnd > roadLength) {
        roadIntervalTree.at(index).intervalStart = intervalStart;
        roadIntervalTree.at(index).intervalEnd = roadLength;
    } else {
        roadIntervalTree.at(index).intervalStart = intervalStart;
        roadIntervalTree.at(index).intervalEnd = maxIntervalEnd;
    }

    if (maxIntervalEnd > intervalStart) {

        int leftIndex = index * 2 + 1;
        int leftIntervalEnd = (intervalStart + maxIntervalEnd) / 2;
        setIntervalsInIntervalTree(roadIntervalTree, leftIndex, roadLength, intervalStart, leftIntervalEnd);

        int rightIndex = index * 2 + 2;
        int rightIntervalStart = (intervalStart + maxIntervalEnd + 1) / 2;
        setIntervalsInIntervalTree(roadIntervalTree, rightIndex, roadLength, rightIntervalStart, maxIntervalEnd);
    }
}

vector<Interval> getRoadIntervalTree(int roadLength) {

    int treeSize = 1;

    while (treeSize < roadLength) {
        treeSize *= 2;
    }
    int maxIntervalEnd = treeSize;
    treeSize = treeSize * 2 - 1;

    vector<Interval> roadIntervalTree (treeSize);

    int index = 0;
    int intervalStart = 1;
    setIntervalsInIntervalTree(roadIntervalTree, index, roadLength, intervalStart, maxIntervalEnd);

    Interval &root = roadIntervalTree.at(0);

    root.allBlack = true;
    root.allWhite = false;
    root.numberOfWhite = 0;

    return roadIntervalTree;
}

void addChangeOfColorToIntervalTree(vector<Interval> &roadIntervalTree, int index, int changeOfWhite) {

    while (index >= 0) {

        roadIntervalTree.at(index).numberOfWhite += changeOfWhite;

        if (index % 2 == 1) {
            index = (index - 1) / 2;
        } else {
            index = (index - 2) / 2;
        }
    }
}

void divideUnicoloredNode(Interval &node, Interval &leftNode, Interval &rightNode) {

    if (node.allWhite) {
        leftNode.allWhite = true;
        leftNode.allBlack = false;
        leftNode.numberOfWhite = leftNode.intervalEnd - leftNode.intervalStart + 1;

        rightNode.allWhite = true;
        rightNode.allBlack = false;
        rightNode.numberOfWhite = rightNode.intervalEnd - rightNode.intervalStart + 1;

        node.allWhite = false;
    } else if (node.allBlack) {
        leftNode.allWhite = false;
        leftNode.allBlack = true;
        leftNode.numberOfWhite = 0;

        rightNode.allWhite = false;
        rightNode.allBlack = true;
        rightNode.numberOfWhite = 0;

        node.allBlack = false;
    }
}

//recursive
void changeColorOfIntervalInIntervalTreeElement(int intervalStart, int intervalEnd, char color, vector<Interval> &roadIntervalTree, int index) {

    Interval &node = roadIntervalTree.at(index);

    if ((node.allWhite) && (color == 'B')) {
        return;
    }

    if ((node.allBlack) && (color == 'C')) {
        return;
    }

    if ((node.intervalStart == intervalStart) && (node.intervalEnd == intervalEnd)) {

        int newNumberOfWhite;
        int changeOfWhite;
        
        if (color == 'B') {
            newNumberOfWhite = intervalEnd - intervalStart + 1;
            node.allWhite = true;
            node.allBlack = false;
        } else {
            newNumberOfWhite = 0;
            node.allWhite = false;
            node.allBlack = true;
        }
        changeOfWhite = newNumberOfWhite - node.numberOfWhite;
        addChangeOfColorToIntervalTree(roadIntervalTree, index, changeOfWhite);
        return;
    }

    Interval &leftNode = roadIntervalTree.at(index * 2 + 1);
    Interval &rightNode = roadIntervalTree.at(index * 2 + 2);

    divideUnicoloredNode(node, leftNode, rightNode);

    if (intervalEnd <= leftNode.intervalEnd) {
        changeColorOfIntervalInIntervalTreeElement(intervalStart, intervalEnd, color, roadIntervalTree, index * 2 + 1);
    } else if (intervalStart >= rightNode.intervalStart) {
        changeColorOfIntervalInIntervalTreeElement(intervalStart, intervalEnd, color, roadIntervalTree, index * 2 + 2);
    } else {
        changeColorOfIntervalInIntervalTreeElement(intervalStart, leftNode.intervalEnd, color, roadIntervalTree, index * 2 + 1);
        changeColorOfIntervalInIntervalTreeElement(rightNode.intervalStart, intervalEnd, color, roadIntervalTree, index * 2 + 2);
    }

}

void changeColorOfIntervalInIntervalTree(int intervalStart, int intervalEnd, char color, vector<Interval> &roadIntervalTree) {

    changeColorOfIntervalInIntervalTreeElement(intervalStart, intervalEnd, color, roadIntervalTree, 0);
}

void doAction(vector<Interval> &roadIntervalTree) {

    int intervalStart;
    int intervalEnd;
    char color;

    cin >> intervalStart;
    cin >> intervalEnd;
    cin >> color;

    changeColorOfIntervalInIntervalTree(intervalStart, intervalEnd, color, roadIntervalTree);

    cout << roadIntervalTree.at(0).numberOfWhite << endl;
}

int main() {

    int roadLength;
    cin >> roadLength;

    vector<Interval> roadIntervalTree = getRoadIntervalTree(roadLength);

    int numberOfActions;
    cin >> numberOfActions;

    for (int i = 0; i < numberOfActions; i++) {
        doAction(roadIntervalTree);
    }

    return 0;
}