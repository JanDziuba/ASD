#include <iostream>
#include <string>
#include<bits/stdc++.h>

using namespace std;

string getTapestry() {

    string tapestry;

    cin >> tapestry;

    return tapestry;
}

bool isTapestryMonocoloured(const string tapestry) {

    char firstColour;
    int index = 0;


    while ((index < tapestry.length()) && (tapestry.at(index) == '*')) {
        index++;
    }

    if (index >= tapestry.length()) {
        return true;
    } else {
        firstColour = tapestry.at(index);
    }

    for (; index < tapestry.length(); index++) {

        if ((tapestry.at(index) != firstColour) && (tapestry.at(index) != '*')) {
            return false;
        }
    }
    return true;
}


int getSmallestNumberOfStarsBetweenColours(const string tapestry) {

    int smallestNumberOfStarsBetweenColours = INT_MAX;
    int currentNumberOfStarsBetweenColours = 0;
    int index = 0;
    char currentColour;

    while (tapestry.at(index) == '*') {
        index++;
    }

    currentColour = tapestry.at(index);

    for (; index < tapestry.length(); index++) {

        if (tapestry.at(index) == '*') {
            currentNumberOfStarsBetweenColours++;
        }
        else if (tapestry.at(index) == currentColour) {
            currentNumberOfStarsBetweenColours = 0;
        }
        else {

            if (currentNumberOfStarsBetweenColours < smallestNumberOfStarsBetweenColours) {
                smallestNumberOfStarsBetweenColours = currentNumberOfStarsBetweenColours;
            }

            currentColour = tapestry.at(index);
            currentNumberOfStarsBetweenColours = 0;
        }
    }

    return smallestNumberOfStarsBetweenColours;
}

int getTemplateSize(const string tapestry) {

    int smallestNumberOfStarsBetweenColours;

    if (isTapestryMonocoloured(tapestry) == true) {
        return 1;
    }

    smallestNumberOfStarsBetweenColours = getSmallestNumberOfStarsBetweenColours(tapestry);

    return (tapestry.length() - smallestNumberOfStarsBetweenColours);
}

int main() {

    string tapestry;
    int templateSize;

    tapestry =  getTapestry();

    templateSize = getTemplateSize(tapestry);

    std::cout << templateSize << std::endl;

    return 0;
}