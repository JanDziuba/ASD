#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int numberOfProjects;
int numberOfProjectDependencies;
int requiredNumberOfProjects;

const static int MAX_NUMBER_OF_PROJECTS = 100000;

vector<long> projects (MAX_NUMBER_OF_PROJECTS);

vector<vector<int>> dependenciesOut (MAX_NUMBER_OF_PROJECTS);
vector<vector<int>> dependenciesIn (MAX_NUMBER_OF_PROJECTS);

// ordered by first
priority_queue <pair<long, int>, vector<pair<long, int>>, greater<pair<long, int>>> independentProjects;


void getInput() {
    cin >> numberOfProjects;
    cin >> numberOfProjectDependencies;
    cin >> requiredNumberOfProjects;

    for (int i = 0; i < numberOfProjects; i++) {
        cin >> projects.at(i);
    }

    int dependent;
    int dependingOn;

    for (int i = 0; i < numberOfProjectDependencies; i++) {
        cin >> dependent;
        cin >> dependingOn;

        dependent--;
        dependingOn--;

        dependenciesIn.at(dependent).push_back(dependingOn);
        dependenciesOut.at(dependingOn).push_back(dependent);
    }
}

void fillQueue() {
    for (int i = 0; i < numberOfProjects; i++) {
        if (dependenciesIn.at(i).empty()) {
            independentProjects.push(make_pair(projects.at(i), i));
        }
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    getInput();
    fillQueue();

    long numberOfRequiredWorkers = 0;
    int numberOfMadeProjects = 0;
    int projectIndex;
    pair<long, int> topProject;

    while (numberOfMadeProjects < requiredNumberOfProjects) {
        topProject = independentProjects.top();
        independentProjects.pop();
        if (topProject.first > numberOfRequiredWorkers) {
            numberOfRequiredWorkers = topProject.first;
        }
        projectIndex = topProject.second;

        vector<int> &dependentOnTopProject = dependenciesOut.at(projectIndex);

        for (int dependent : dependentOnTopProject) {
            vector<int> &dependenciesInDependent = dependenciesIn.at(dependent);

            dependenciesInDependent.erase(remove(dependenciesInDependent.begin(), dependenciesInDependent.end(),
                    projectIndex), dependenciesInDependent.end());

            if (dependenciesIn.at(dependent).empty()) {
                independentProjects.push(make_pair(projects.at(dependent), dependent));
            }
        }
        numberOfMadeProjects++;
    }

    cout << numberOfRequiredWorkers << endl;

    return 0;
}