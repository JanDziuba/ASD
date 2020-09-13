#include <iostream>

typedef struct MostExpensiveCombinationOfProducts {

    int indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices;
    int indexOfCheapestOddPriceInCombinationInArrayOfOddPrices;

    long long priceSum;

} MostExpensiveCombinationOfProducts;



void getProductsInShop(int *pointerToNumberOfProductsInShop, int **pointerToSortedArrayOfPrices) {

    int *sortedArrayOfPrices = NULL;

    int numberOfProductsInShop;

    std::cin >> numberOfProductsInShop;

    sortedArrayOfPrices = new int[numberOfProductsInShop];

    for (int index = 0; index < numberOfProductsInShop; index++) {
        std::cin >> sortedArrayOfPrices[index];
    }

    *pointerToNumberOfProductsInShop = numberOfProductsInShop;
    *pointerToSortedArrayOfPrices = sortedArrayOfPrices;
}

void getEvenAndOddPrices(int *pointerToNumberOfEvenPrices, int **pointerToSortedArrayOfEvenPrices,
        int *pointerToNumberOfOddPrices, int **pointerToSortedArrayOfOddPrices, const int numberOfProductsInShop,
        const int *sortedArrayOfPrices) {

    int *sortedArrayOfEvenPrices = NULL;
    int *sortedArrayOfOddPrices = NULL;

    int numberOfEvenPrices = 0;
    int numberOfOddPrices = 0;

    for (int index = 0; index < numberOfProductsInShop; index++) {

        if (sortedArrayOfPrices[index] % 2 == 0) {
            numberOfEvenPrices++;
        }
        else {
            numberOfOddPrices++;
        }
    }

    sortedArrayOfEvenPrices = new int[numberOfEvenPrices];
    sortedArrayOfOddPrices = new int[numberOfOddPrices];

    int indexOfEvenPrices = 0;
    int indexOfOddPrices = 0;

    for (int index = 0; index < numberOfProductsInShop; index++) {

        if (sortedArrayOfPrices[index] % 2 == 0) {
            sortedArrayOfEvenPrices[indexOfEvenPrices] = sortedArrayOfPrices[index];
            indexOfEvenPrices++;
        }
        else {
            sortedArrayOfOddPrices[indexOfOddPrices] = sortedArrayOfPrices[index];
            indexOfOddPrices++;
        }
    }

    *pointerToNumberOfEvenPrices = numberOfEvenPrices;
    *pointerToSortedArrayOfEvenPrices = sortedArrayOfEvenPrices;
    *pointerToNumberOfOddPrices = numberOfOddPrices;
    *pointerToSortedArrayOfOddPrices = sortedArrayOfOddPrices;
}

void getMostExpensiveCombinationsOfProducts(
        MostExpensiveCombinationOfProducts **pointerToMostExpensiveCombinationsOfProductsIndexedByNumberOfProducts,
        const int numberOfProductsInShop, const int numberOfEvenPrices, const int *sortedArrayOfEvenPrices,
        const int numberOfOddPrices, const int *sortedArrayOfOddPrices) {

    MostExpensiveCombinationOfProducts *mostExpensiveCombinationsOfProductsIndexedByNumberOfProducts = NULL;
    int numberOfProductsInCombination;
    MostExpensiveCombinationOfProducts combination;
    int indexOfEvenPrices;
    int indexOfOddPrices;

    mostExpensiveCombinationsOfProductsIndexedByNumberOfProducts = new MostExpensiveCombinationOfProducts[numberOfProductsInShop + 1];

    combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices = -1;
    combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices = -1;
    combination.priceSum = 0;

    mostExpensiveCombinationsOfProductsIndexedByNumberOfProducts[0] = combination;

    indexOfEvenPrices = numberOfEvenPrices - 1;
    indexOfOddPrices = numberOfOddPrices - 1;

    numberOfProductsInCombination = 0;

    while ((indexOfEvenPrices >= 0) || (indexOfOddPrices >= 0)) {

        numberOfProductsInCombination++;

        combination = mostExpensiveCombinationsOfProductsIndexedByNumberOfProducts[numberOfProductsInCombination - 1];


        if (indexOfEvenPrices < 0) {

            combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices = indexOfOddPrices;
            combination.priceSum += sortedArrayOfOddPrices[indexOfOddPrices];
            indexOfOddPrices--;

        } else if (indexOfOddPrices < 0){

            combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices = indexOfEvenPrices;
            combination.priceSum += sortedArrayOfEvenPrices[indexOfEvenPrices];
            indexOfEvenPrices--;

        } else {

            if (sortedArrayOfEvenPrices[indexOfEvenPrices] > sortedArrayOfOddPrices[indexOfOddPrices]) {

                combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices = indexOfEvenPrices;
                combination.priceSum += sortedArrayOfEvenPrices[indexOfEvenPrices];
                indexOfEvenPrices--;
            } else {
                combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices = indexOfOddPrices;
                combination.priceSum += sortedArrayOfOddPrices[indexOfOddPrices];
                indexOfOddPrices--;
            }
        }

        mostExpensiveCombinationsOfProductsIndexedByNumberOfProducts[numberOfProductsInCombination] = combination;
    }

    *pointerToMostExpensiveCombinationsOfProductsIndexedByNumberOfProducts = mostExpensiveCombinationsOfProductsIndexedByNumberOfProducts;
}

long long getMaxLongLong(long long number1, long long number2) {
    
    if (number1 > number2) {
        return number1;
    } else {
        return number2;
    }
}

void getMostExpensiveOddCombinationsOfProducts(
        const MostExpensiveCombinationOfProducts *mostExpensiveCombinationsOfProductsIndexedByNumberOfProducts,
        const int numberOfProductsInShop, long long **pointerToMostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts,
        const int numberOfEvenPrices, const int *sortedArrayOfEvenPrices,
        const int numberOfOddPrices, const int *sortedArrayOfOddPrices) {

    int numberOfProductsInCombination = 0;
    auto *mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts = new long long[numberOfProductsInShop + 1];
    long long number1;
    long long number2;
    MostExpensiveCombinationOfProducts combination;
    long long oddCombination;

    mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts[0] = -1;

    for (numberOfProductsInCombination = 1; numberOfProductsInCombination <= numberOfProductsInShop; numberOfProductsInCombination++) {

        combination = mostExpensiveCombinationsOfProductsIndexedByNumberOfProducts[numberOfProductsInCombination];
        
        if (combination.priceSum % 2 == 1) {

            oddCombination = combination.priceSum;
            
        } else {
            
            if ((numberOfEvenPrices == 0) || (numberOfOddPrices == 0)) {
                oddCombination = -1;
            }
            else {

                if (combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices == -1) {

                    oddCombination = combination.priceSum + sortedArrayOfEvenPrices[numberOfEvenPrices - 1] -
                            sortedArrayOfOddPrices[combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices];
                }
                else if (combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices == -1) {

                    oddCombination = combination.priceSum + sortedArrayOfOddPrices[numberOfOddPrices - 1] -
                            sortedArrayOfEvenPrices[combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices];
                }
                else {
                    if ((combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices == 0) &&
                        (combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices == 0)) {
                        oddCombination = -1;
                    }
                    else if (combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices == 0) {

                        oddCombination = combination.priceSum + (sortedArrayOfOddPrices[combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices - 1] -
                                                                 sortedArrayOfEvenPrices[combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices]);
                    }
                    else if (combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices == 0) {

                        oddCombination = combination.priceSum + (sortedArrayOfEvenPrices[combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices - 1] -
                                                                 sortedArrayOfOddPrices[combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices]);
                    }
                    else {
                        number1 = (sortedArrayOfEvenPrices[combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices - 1] -
                                   sortedArrayOfOddPrices[combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices]);

                        number2 = (sortedArrayOfOddPrices[combination.indexOfCheapestOddPriceInCombinationInArrayOfOddPrices - 1] -
                                   sortedArrayOfEvenPrices[combination.indexOfCheapestEvenPriceInCombinationInArrayOfEvenPrices]);

                        oddCombination = combination.priceSum + getMaxLongLong(number1, number2);
                    }
                }
                
            }
            
        }

        mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts[numberOfProductsInCombination] = oddCombination;
        
    }

    *pointerToMostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts = mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts;
}

void writeResults(const long long *mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts) {

    int numberOfDays;
    int numberOfProductsBought;

    std::cin >> numberOfDays;

    for (int index = 0; index < numberOfDays; index++) {
        std::cin >> numberOfProductsBought;

        std::cout << mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts[numberOfProductsBought] << std::endl;
    }
}

void freeMemory(int *sortedArrayOfPrices, int *sortedArrayOfEvenPrices, int *sortedArrayOfOddPrices,
        MostExpensiveCombinationOfProducts *mostExpensiveCombinationsOfProductsSortedByNumberOfProducts,
        long long *mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts) {

    delete[] sortedArrayOfPrices;
    delete[] sortedArrayOfEvenPrices;
    delete[] sortedArrayOfOddPrices;
    delete[] mostExpensiveCombinationsOfProductsSortedByNumberOfProducts;
    delete[] mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts;
}

int main() {

    int numberOfProductsInShop;
    int *sortedArrayOfPrices = NULL;

    int numberOfEvenPrices;
    int *sortedArrayOfEvenPrices = NULL;

    int numberOfOddPrices;
    int *sortedArrayOfOddPrices = NULL;

    MostExpensiveCombinationOfProducts *mostExpensiveCombinationsOfProductsSortedByNumberOfProducts = NULL;
    long long *mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts = NULL;


    getProductsInShop(&numberOfProductsInShop, &sortedArrayOfPrices);

    getEvenAndOddPrices(&numberOfEvenPrices, &sortedArrayOfEvenPrices, &numberOfOddPrices, &sortedArrayOfOddPrices,
            numberOfProductsInShop, sortedArrayOfPrices);

    getMostExpensiveCombinationsOfProducts(&mostExpensiveCombinationsOfProductsSortedByNumberOfProducts,
            numberOfProductsInShop, numberOfEvenPrices, sortedArrayOfEvenPrices, numberOfOddPrices, sortedArrayOfOddPrices);

    getMostExpensiveOddCombinationsOfProducts(mostExpensiveCombinationsOfProductsSortedByNumberOfProducts,
            numberOfProductsInShop, &mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts, numberOfEvenPrices,
            sortedArrayOfEvenPrices, numberOfOddPrices, sortedArrayOfOddPrices);

    writeResults(mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts);

    freeMemory(sortedArrayOfPrices, sortedArrayOfEvenPrices, sortedArrayOfOddPrices,
            mostExpensiveCombinationsOfProductsSortedByNumberOfProducts,
            mostExpensiveOddCombinationsOfProductsIndexedByNumberOfProducts);

    return 0;
}