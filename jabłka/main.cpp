#include <iostream>
#include <vector>

#define DIVISOR 1000000000

using namespace std;

typedef struct BranchType {

    int leftBranchType;
    int rightBranchType;
}BranchType;

void getInput(int &numberOfBranchTypes, int &lengthOfLadder, vector<BranchType> &branchTypes) {

    int numberOfNonZeroBranchTypes;

    cin >> numberOfNonZeroBranchTypes;
    cin >> lengthOfLadder;

    numberOfBranchTypes = numberOfNonZeroBranchTypes + 1;

    branchTypes.resize(numberOfBranchTypes);

    int branchType = 0;

    branchTypes.at(branchType).rightBranchType = -1;
    branchTypes.at(branchType).leftBranchType = -1;

    branchType++;

    for (; branchType < numberOfBranchTypes; branchType++) {

        cin >> branchTypes.at(branchType).leftBranchType;
        cin >> branchTypes.at(branchType).rightBranchType;
    }
}

int main() {

    int numberOfBranchTypes;
    int lengthOfLadder;
    vector<BranchType> branchTypes;

    getInput(numberOfBranchTypes, lengthOfLadder, branchTypes);

    vector<int> sumOfApplesOnBranchType1(numberOfBranchTypes, 0);

    sumOfApplesOnBranchType1.at(0) = 1;

    for (int branchType = 1; branchType < numberOfBranchTypes; branchType++) {

        sumOfApplesOnBranchType1.at(branchType) =
                (sumOfApplesOnBranchType1.at(branchTypes.at(branchType).leftBranchType) +
                 sumOfApplesOnBranchType1.at(branchTypes.at(branchType).rightBranchType) + 1) % DIVISOR;
    }

    vector<int> sumOfApplesOnBranchType2 (numberOfBranchTypes,0);

    for (int length = 1; length <= lengthOfLadder; length++) {

        if (length % 2 == 0) {
            sumOfApplesOnBranchType1.at(0) = 0;

            for (int branchType = 1; branchType < numberOfBranchTypes; branchType++) {

                sumOfApplesOnBranchType1.at(branchType) =
                        (sumOfApplesOnBranchType2.at(branchTypes.at(branchType).leftBranchType) +
                         sumOfApplesOnBranchType2.at(branchTypes.at(branchType).rightBranchType)) % DIVISOR;
            }
        } else {
            sumOfApplesOnBranchType2.at(0) = 0;

            for (int branchType = 1; branchType < numberOfBranchTypes; branchType++) {

                sumOfApplesOnBranchType2.at(branchType) =
                        (sumOfApplesOnBranchType1.at(branchTypes.at(branchType).leftBranchType) +
                         sumOfApplesOnBranchType1.at(branchTypes.at(branchType).rightBranchType)) % DIVISOR;
            }
        }
    }

    if (lengthOfLadder % 2 == 0) {
        cout << sumOfApplesOnBranchType1.at(numberOfBranchTypes - 1);
    } else {
        cout << sumOfApplesOnBranchType2.at(numberOfBranchTypes - 1);
    }

    return 0;
}