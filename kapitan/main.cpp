#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include<climits>

using namespace std;

#define MAX_ISLAND_AMOUNT 200000

struct Island {
    int xCoordinate;
    int yCoordinate;
    int xCoordinateIndex;
    int yCoordinateIndex;

};

// first of pair = x coordinate, second = island number 
vector< pair <int,int> > islandsSortedByXCoordinate (MAX_ISLAND_AMOUNT);

// first of pair = y coordinate, second = island number 
vector< pair <int,int> > islandsSortedByYCoordinate (MAX_ISLAND_AMOUNT);

vector<Island> islands (MAX_ISLAND_AMOUNT);

// distances in djikstra
vector<int> distances (MAX_ISLAND_AMOUNT);

int islandAmount;

void sortVectors() {

    sort(islandsSortedByXCoordinate.begin(), islandsSortedByXCoordinate.begin() + islandAmount);

    sort(islandsSortedByYCoordinate.begin(), islandsSortedByYCoordinate.begin() + islandAmount);
}

void getInput() {
    
    cin >> islandAmount;
    
    int xCoordinate;
    int yCoordinate;
    
    for (int islandNumber = 0; islandNumber < islandAmount; islandNumber++) {
        
        cin >> xCoordinate;
        cin >> yCoordinate;

        islands.at(islandNumber).xCoordinate = xCoordinate;
        islands.at(islandNumber).yCoordinate = yCoordinate;
        
        islandsSortedByXCoordinate.at(islandNumber) = make_pair(xCoordinate, islandNumber);

        islandsSortedByYCoordinate.at(islandNumber) = make_pair(yCoordinate, islandNumber);
    }

    sortVectors();
}

void getIndexes() {

    for (int index = 0; index < islandAmount; index++) {

        int xCoordinateIslandNumber = islandsSortedByXCoordinate.at(index).second;
        int yCoordinateIslandNumber = islandsSortedByYCoordinate.at(index).second;

        islands.at(xCoordinateIslandNumber).xCoordinateIndex = index;
        islands.at(yCoordinateIslandNumber).yCoordinateIndex = index;
    }
}

void setStartDistances() {

    for (int index = 1; index < islandAmount; index++) {
        distances.at(index) = INT_MAX;
    }
}

int calculateDistance() {

    setStartDistances();

    // first = distance, second = island number
    priority_queue< pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > pq;


    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(make_pair(0, 0));
    distances.at(0) = 0;

    int minIsland = -1;

    /* Looping till priority queue becomes empty (or all
      distances are not finalized) */
    while (minIsland != islandAmount - 1) {

        minIsland = pq.top().second;
        pq.pop();

        int indexOfXCoordinate = islands.at(minIsland).xCoordinateIndex;
        int indexOfYCoordinate = islands.at(minIsland).yCoordinateIndex;

        int minIslandXCoordinate = islands.at(minIsland).xCoordinate;
        int minIslandYCoordinate = islands.at(minIsland).yCoordinate;


        if (indexOfXCoordinate > 0) {

            int xSmallNeighbour = islandsSortedByXCoordinate.at(indexOfXCoordinate - 1).second;

            int xSmallNeighbourXCoordinate = islands.at(xSmallNeighbour).xCoordinate;

            int xSmallNeighbourYCoordinate = islands.at(xSmallNeighbour).yCoordinate;

            int distanceDifference = min(abs(xSmallNeighbourXCoordinate - minIslandXCoordinate),
                    abs(xSmallNeighbourYCoordinate - minIslandYCoordinate));

            if (distances.at(xSmallNeighbour) > distances.at(minIsland) + distanceDifference) {

                distances.at(xSmallNeighbour) = distances.at(minIsland) + distanceDifference;
                pq.push(make_pair(distances.at(xSmallNeighbour), xSmallNeighbour));
            }
        }

        if (indexOfXCoordinate < islandAmount - 1) {

            int xBigNeighbour = islandsSortedByXCoordinate.at(indexOfXCoordinate + 1).second;

            int xBigNeighbourXCoordinate = islands.at(xBigNeighbour).xCoordinate;

            int xBigNeighbourYCoordinate = islands.at(xBigNeighbour).yCoordinate;

            int distanceDifference = min(abs(xBigNeighbourXCoordinate - minIslandXCoordinate),
                                         abs(xBigNeighbourYCoordinate - minIslandYCoordinate));

            if (distances.at(xBigNeighbour) > distances.at(minIsland) + distanceDifference) {

                distances.at(xBigNeighbour) = distances.at(minIsland) + distanceDifference;
                pq.push(make_pair(distances.at(xBigNeighbour), xBigNeighbour));
            }
        }

        if (indexOfYCoordinate > 0) {

            int ySmallNeighbour = islandsSortedByYCoordinate.at(indexOfYCoordinate - 1).second;

            int ySmallNeighbourXCoordinate = islands.at(ySmallNeighbour).xCoordinate;

            int ySmallNeighbourYCoordinate = islands.at(ySmallNeighbour).yCoordinate;

            int distanceDifference = min(abs(ySmallNeighbourXCoordinate - minIslandXCoordinate),
                                         abs(ySmallNeighbourYCoordinate - minIslandYCoordinate));

            if (distances.at(ySmallNeighbour) > distances.at(minIsland) + distanceDifference) {

                distances.at(ySmallNeighbour) = distances.at(minIsland) + distanceDifference;
                pq.push(make_pair(distances.at(ySmallNeighbour), ySmallNeighbour));
            }
        }

        if (indexOfYCoordinate < islandAmount - 1) {

            int yBigNeighbour = islandsSortedByYCoordinate.at(indexOfYCoordinate + 1).second;

            int yBigNeighbourXCoordinate = islands.at(yBigNeighbour).xCoordinate;

            int yBigNeighbourYCoordinate = islands.at(yBigNeighbour).yCoordinate;

            int distanceDifference = min(abs(yBigNeighbourXCoordinate - minIslandXCoordinate),
                                         abs(yBigNeighbourYCoordinate - minIslandYCoordinate));

            if (distances.at(yBigNeighbour) > distances.at(minIsland) + distanceDifference) {

                distances.at(yBigNeighbour) = distances.at(minIsland) + distanceDifference;
                pq.push(make_pair(distances.at(yBigNeighbour), yBigNeighbour));
            }
        }
    }
    return distances.at(islandAmount - 1);
}

int main() {

    getInput();
    getIndexes();

    cout << calculateDistance();

    return 0;
}