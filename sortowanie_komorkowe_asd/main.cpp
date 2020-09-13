#include <iostream>
#include <vector>

#define DIVIDER 1000000000

using namespace std;

void getResultForSequenceWithLastElementAddedLast(vector<vector<int>>& lastVectors,
                                                  int sequenceStart, int sequenceEnd, const vector<int>& bigSequence, vector<vector<int>>& FirstVectors);

const vector<int> getSequence() {

    vector<int> sequence;
    int numberOfNumbersInSequence;
    int currentNumber;

    cin >> numberOfNumbersInSequence;

    for (int i = 0; i < numberOfNumbersInSequence; i++) {

        cin >> currentNumber;
        sequence.push_back(currentNumber);
    }

    return sequence;
}

vector<vector<int>> generateVectorsForSubstrings(int sizeOfSequence) {

    vector<vector<int>> vectorOfvectorsOfSubstrings;

    for (int sequenceStart = 0; sequenceStart < sizeOfSequence; sequenceStart++) {

        vector<int> vectorOfSubstrings;

        for (int sequenceEnd = 0; sequenceEnd < sizeOfSequence - sequenceStart; sequenceEnd++) {
            vectorOfSubstrings.push_back(-1);
        }

        vectorOfvectorsOfSubstrings.push_back(vectorOfSubstrings);
    }

    return vectorOfvectorsOfSubstrings;
}

void getResultForSequenceWithFirstElementAddedLast(vector<vector<int>>& FirstVectors,
        int sequenceStart, int sequenceEnd, const vector<int>& bigSequence, vector<vector<int>>& lastVectors) {

    FirstVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) = 0;

    if (sequenceStart > sequenceEnd) {
        printf("Not logical value at line number %d\n", __LINE__);
    }

    if (sequenceStart == sequenceEnd) {

        FirstVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) = 1;
        return;
    }

    if (bigSequence.at(sequenceStart) > bigSequence.at(sequenceEnd)) {
        return;
    }

    if (lastVectors.at(sequenceStart + 1).at(sequenceEnd - sequenceStart - 1) == -1) {

        getResultForSequenceWithLastElementAddedLast(lastVectors, sequenceStart + 1,
                                                     sequenceEnd, bigSequence, FirstVectors);
    }

    FirstVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) +=
            lastVectors.at(sequenceStart + 1).at(sequenceEnd - sequenceStart - 1);

    FirstVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) %= DIVIDER;

    if (bigSequence.at(sequenceStart + 1) > bigSequence.at(sequenceStart)) {

        if (FirstVectors.at(sequenceStart + 1).at(sequenceEnd - (sequenceStart + 1)) == -1) {

            getResultForSequenceWithFirstElementAddedLast(FirstVectors, sequenceStart + 1,
                                                         sequenceEnd, bigSequence, lastVectors);
        }

        FirstVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) +=
                FirstVectors.at(sequenceStart + 1).at(sequenceEnd - sequenceStart - 1);

        FirstVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) %= DIVIDER;
    }

}

void getResultForSequenceWithLastElementAddedLast(vector<vector<int>>& lastVectors,
        int sequenceStart, int sequenceEnd, const vector<int>& bigSequence, vector<vector<int>>& FirstVectors) {

    lastVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) = 0;

    if (sequenceStart > sequenceEnd) {
        printf("Not logical value at line number %d\n", __LINE__);
    }

    if (sequenceStart == sequenceEnd) {

        // dla first jest 1
        return;
    }

    if (bigSequence.at(sequenceStart) > bigSequence.at(sequenceEnd)) {
        return;
    }

    if (FirstVectors.at(sequenceStart).at(sequenceEnd - sequenceStart - 1) == -1) {

        getResultForSequenceWithFirstElementAddedLast(FirstVectors, sequenceStart,
                                                     sequenceEnd - 1, bigSequence, lastVectors);
    }


    lastVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) +=
            FirstVectors.at(sequenceStart).at(sequenceEnd - sequenceStart - 1);

    lastVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) %= DIVIDER;

    if (bigSequence.at(sequenceEnd - 1) < bigSequence.at(sequenceEnd)) {

        if (lastVectors.at(sequenceStart).at(sequenceEnd - sequenceStart - 1) == -1) {

            getResultForSequenceWithLastElementAddedLast(lastVectors, sequenceStart,
                                                         sequenceEnd - 1, bigSequence, FirstVectors);
        }

        lastVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) +=
                lastVectors.at(sequenceStart).at(sequenceEnd - sequenceStart - 1);

        lastVectors.at(sequenceStart).at(sequenceEnd - sequenceStart) %= DIVIDER;
    }

}


int getResult(const vector<int>& sequence, vector<vector<int>>& FirstVectors,
              vector<vector<int>>& lastVectors) {

    int sizeOfSequence = sequence.size();

    if(FirstVectors.at(0).at(sizeOfSequence - 1) == -1) {
        getResultForSequenceWithFirstElementAddedLast(FirstVectors, 0, sizeOfSequence - 1, sequence, lastVectors);
    }

    if(lastVectors.at(0).at(sizeOfSequence - 1) == -1) {
        getResultForSequenceWithLastElementAddedLast(lastVectors, 0, sizeOfSequence - 1, sequence, FirstVectors);
    }

    return (FirstVectors.at(0).at(sizeOfSequence - 1) + lastVectors.at(0).at(sizeOfSequence - 1)) % DIVIDER;

}

int main() {

    const vector<int> sequence = getSequence();
    vector<vector<int>> FirstVectors = generateVectorsForSubstrings(sequence.size());
    vector<vector<int>> lastVectors = generateVectorsForSubstrings(sequence.size());

    int result = getResult(sequence, FirstVectors, lastVectors);

    std::cout << result << std::endl;
    return 0;
}