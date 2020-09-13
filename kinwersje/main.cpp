#include <iostream>
#include <vector>

#define DIVIDER 1000000000

using namespace std;

void getInput(int &sequenceLength, vector<int> &sequence, int &inversionLength) {

    cin >> sequenceLength;
    sequence.resize(sequenceLength);
    cin >> inversionLength;

    for (int i = 0; i < sequenceLength; i++) {
        cin >> sequence.at(i);
    }

}

void getIndexesOfNumbersInSequence(vector<int> &sequence, vector<int> &indexesOfNumbersInSequence) {

    indexesOfNumbersInSequence.resize(sequence.size() + 1);

    for (int i = 0; i < sequence.size(); i++) {
        indexesOfNumbersInSequence.at(sequence.at(i)) = i;
    }
}

void initializeSequenceTrees(vector<vector<int>> &arrayOfInversionSequenceTrees, int sequenceLength,
        int inversionLength) {

    arrayOfInversionSequenceTrees.resize(inversionLength);

    int sequenceTreeAllocationSize = 1;

    while (sequenceTreeAllocationSize < sequenceLength) {
        sequenceTreeAllocationSize *= 2;
    }

    sequenceTreeAllocationSize = sequenceTreeAllocationSize * 2 - 1;

    for (int i = 0; i < arrayOfInversionSequenceTrees.size(); i++) {
        arrayOfInversionSequenceTrees.at(i).resize(sequenceTreeAllocationSize);
    }
}

void changeValueOfNodeInSequenceTree(vector<int> &inversionSequenceTree, int indexOfNumber, int value, int sequenceEnd) {

    int sequenceStart = 0;
    int indexInInversionSequenceTree = 0;

    while ((sequenceStart < indexOfNumber) || (indexOfNumber < sequenceEnd)) {

        if (indexOfNumber <= (sequenceStart + sequenceEnd) / 2) {

            indexInInversionSequenceTree = indexInInversionSequenceTree * 2 + 1;
            sequenceEnd = (sequenceStart + sequenceEnd) / 2;
        } else {

            indexInInversionSequenceTree = indexInInversionSequenceTree * 2 + 2;
            sequenceStart = (sequenceStart + sequenceEnd) / 2 + 1;
        }
    }

    int changeInValue = value - inversionSequenceTree.at(indexInInversionSequenceTree);

    while (indexInInversionSequenceTree >= 0) {

        inversionSequenceTree.at(indexInInversionSequenceTree) = (inversionSequenceTree.at(indexInInversionSequenceTree) + changeInValue) % DIVIDER;

        if (indexInInversionSequenceTree % 2 == 1) {
            indexInInversionSequenceTree = (indexInInversionSequenceTree - 1) / 2;
        } else {
            indexInInversionSequenceTree = (indexInInversionSequenceTree - 2) / 2;
        }
    }
}

int getSumOfSequence(vector<int> &inversionSequenceTree, int indexOfEndingNumber, int sequenceEnd) {

    int sequenceStart = 0;
    int indexInInversionSequenceTree = 0;
    int sum = 0;

    while ((sequenceStart < indexOfEndingNumber) || (indexOfEndingNumber < sequenceEnd)) {

        if (indexOfEndingNumber <= (sequenceStart + sequenceEnd) / 2) {

            indexInInversionSequenceTree = indexInInversionSequenceTree * 2 + 1;
            sequenceEnd = (sequenceStart + sequenceEnd) / 2;
        } else {

            sum = (sum + inversionSequenceTree.at(indexInInversionSequenceTree * 2 + 1)) % DIVIDER;

            indexInInversionSequenceTree = indexInInversionSequenceTree * 2 + 2;
            sequenceStart = (sequenceStart + sequenceEnd) / 2 + 1;
        }
    }

    sum = (sum + inversionSequenceTree.at(indexInInversionSequenceTree)) % DIVIDER;

    return sum;
}

void fillInversionsEndingOnGivenNumber(vector<vector<int>> &arrayOfInversionSequenceTrees, int indexOfEndingNumber, int sequenceEnd) {

    changeValueOfNodeInSequenceTree(arrayOfInversionSequenceTrees.at(0), indexOfEndingNumber, 1, sequenceEnd);

    int sum = 0;

    for (int i = 1; i < arrayOfInversionSequenceTrees.size(); i++) {

        if (indexOfEndingNumber - 1 >= 0) {
            sum = getSumOfSequence(arrayOfInversionSequenceTrees.at(i - 1), indexOfEndingNumber - 1, sequenceEnd);
        }

        changeValueOfNodeInSequenceTree(arrayOfInversionSequenceTrees.at(i), indexOfEndingNumber, sum, sequenceEnd);
    }
}

void fillSeqenceTrees(vector<vector<int>> &arrayOfInversionSequenceTrees, vector<int> &sequence,
        vector<int> &indexesOfNumbersInSequence) {

    for (int endingNumber = indexesOfNumbersInSequence.size() - 1; endingNumber >= 1; endingNumber--) {

        int indexOfEndingNumber = indexesOfNumbersInSequence.at(endingNumber);

        fillInversionsEndingOnGivenNumber(arrayOfInversionSequenceTrees, indexOfEndingNumber, sequence.size() - 1);
    }
}

int main() {
    int sequenceLength;
    vector<int> sequence;
    int inversionLength;

    getInput(sequenceLength, sequence, inversionLength);

    vector<int> indexesOfNumbersInSequence;
    getIndexesOfNumbersInSequence(sequence, indexesOfNumbersInSequence);

    vector<vector<int>> arrayOfInversionSequenceTrees;
    initializeSequenceTrees(arrayOfInversionSequenceTrees, sequenceLength, inversionLength);

    fillSeqenceTrees(arrayOfInversionSequenceTrees, sequence, indexesOfNumbersInSequence);

    int result = getSumOfSequence(arrayOfInversionSequenceTrees.at(inversionLength - 1), sequenceLength - 1, sequenceLength - 1);

    cout << result << endl;

    return 0;
}
