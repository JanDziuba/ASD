#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//1 rzymianin
//0 gal

int maxLength = 7;

// first index - sequence length - 1
// second index - sequene index
// third index - sequene element index
vector<vector<vector<int>>> sequences (maxLength);

void generateNextIndexes(int length, int index, vector<int> sequence, int value) {

    sequence.at(index) = value;

    if (length > index + 1) {
        generateNextIndexes(length, index + 1, sequence, 1);
        generateNextIndexes(length, index + 1, sequence, 0);
    } else {
        sequences.at(length - 1).push_back(sequence);
    }
}

void generateWithLength(int length) {
    vector<int> sequence (length);

    if (length > 0) {
        generateNextIndexes(length, 0, sequence, 1);
        generateNextIndexes(length, 0, sequence, 0);
    }
}

void generateAll() {
    for (int i = 1; i <= maxLength; i++) {
        generateWithLength(i);
    }
}

bool checkIfSequenceIsGood(const vector<int>& sequence) {

    if (sequence.empty()) {
        return false;
    }

    int previousNumber = 1;

    for (int number : sequence) {
        if (number == 0 && previousNumber == 0) {
            return false;
        }
        previousNumber = number;
    }

    return true;
}

vector<int> generateSequence(vector<int> sequence, vector<int> generatingSequence) {
    vector<int> generatedSequence;

    assert(sequence.size() == generatingSequence.size());

    for (int i = 0; i < generatingSequence.size(); i++) {
        if (generatingSequence.at(i) == 1) {
            generatedSequence.push_back(sequence.at(i));
        }
    }

    return generatedSequence;
}

vector<vector<int>> generateSequences(const vector<int>& sequence, const vector<vector<int>>& generatingSequences) {
    vector<vector<int>> generatedSequences;
    vector<int> generatedSequence;

    for (const auto& generatingSequence : generatingSequences) {
        generatedSequence = generateSequence(sequence, generatingSequence);
        generatedSequences.push_back(generatedSequence);
    }
    return generatedSequences;
}

int countNumberOfSelections(const vector<int>& sequence) {

    int numberOfSelections = 0;
    vector<vector<int>> generatingSequences = sequences.at(sequence.size() - 1);

    vector<vector<int>> generatedSequences = generateSequences(sequence, generatingSequences);

    for (const auto & generatedSequence : generatedSequences) {
        if (checkIfSequenceIsGood(generatedSequence)) {
            numberOfSelections++;
        }
    }

    return numberOfSelections;
}

int main() {

    generateAll();
    std::cout << "Hello, World!" << std::endl;
    vector<int> sequence;

    for (auto & i : sequences) {
        for (const auto & j : i) {
            sequence = j;

            if (sequence.size() == maxLength &&
            (sequence.at(0) == 1 || sequence.at(sequence.size() - 1) == 1)) {
                continue;
            }

            int numberOfSelections = countNumberOfSelections(sequence);
            for (int element : sequence) {
                cout << element;
            }
            cout << " - " << numberOfSelections;
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
