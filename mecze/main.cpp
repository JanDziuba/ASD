#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void simulateMatch(vector<long long> &players, long long &matchIdentifyingNumber) {

    int playerNumber;
    int halfPlayersSize = players.size() / 2;

    for (int i = 0; i < halfPlayersSize; i++) {
        cin >> playerNumber;

        players.at(playerNumber - 1) += matchIdentifyingNumber;
    }

//    for (int i = 0; i < halfPlayersSize; i++) {
//        cin >> playerNumber;
//    }

    string tekst;

    getline(cin, tekst);

}

bool getIfSortedVectorValuesAreDistinct(vector<long long> &vector) {

    long long previousValue = vector.at(0);
    bool isVectorDistinct = true;

    for (int i = 1; i < vector.size(); i++) {

        if (vector.at(i) == previousValue) {
            isVectorDistinct = false;
            return isVectorDistinct;
        }
        previousValue = vector.at(i);
    }

    return isVectorDistinct;
}

int main() {

    vector<long long> players;
    int numberOfPlayers;
    int numberOfMatches;
    long long matchIdentifyingNumber = 1;
    bool areThere2PlayersWhoWereAlwaysOnTheSameTeam;

    cin >> numberOfPlayers;

    players.resize(numberOfPlayers);

    cin >> numberOfMatches;

    for (int i = 0; i < numberOfMatches; i++) {
        simulateMatch(players, matchIdentifyingNumber);

        matchIdentifyingNumber *= 2;
    }

    sort (players.begin(), players.end());

    areThere2PlayersWhoWereAlwaysOnTheSameTeam = !getIfSortedVectorValuesAreDistinct(players);

    if (areThere2PlayersWhoWereAlwaysOnTheSameTeam == true) {
        cout << "NIE" << endl;
    } else {
        cout << "TAK" << endl;
    }

    return 0;
}