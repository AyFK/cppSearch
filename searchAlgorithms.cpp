


#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include <chrono>

#include <deque> // for breadthFirstSearch
#include <stack> // for depthFirstSearch


#include "exports.h"


void randomRewardRiskProducts() {
    std::cout << "implamentation coming!\n";
}


genericNode* searchAlgos::breadthFirstSearch(std::map<double, double> dict,
                                         double constraint, bool revisitation) {
    auto start_time = std::chrono::high_resolution_clock::now(); // TIMER START

    // b : maximum node breadth
    // d : minimum depth solution

    // TIME   COMPLEXITY  : O(b^d)
    // SPACE COMPLEXITY  : O(b^d)
    // OPTIMALITY       : NO GUARANTEE
    // FIFO OPERATIONS : push_front (idx: 0), pop_back (idx: -1)

    // 'revisitation' implamentation coming soon!

    std::map<double, double>::iterator iter;
    std::deque<genericNode*> dStruct;

    genericNode* root = new genericNode();
    genericNode* optimalSolution = new genericNode();
    genericNode* currentNode;

    int additionalReward;
    int additionalRisk;
    int currentRisk;

    std::vector<int> edges;
    int edgeId;
    bool explored;

    dStruct.push_front(root);

    while(dStruct.size() != 0) {
        currentNode = dStruct.back();
        dStruct.pop_back();

        iter = dict.begin();
        edgeId = 0;

        while (iter != dict.end()) {
            additionalReward = iter -> first;
            additionalRisk = iter -> second;
            currentRisk = currentNode -> riskTotal;

            edges = currentNode -> edgesExplored;
            explored = std::find(edges.begin(), edges.end(), edgeId)
                                 != edges.end();

            if (revisitation == false && explored == false) {
                currentRisk += additionalRisk;

                if (currentRisk <= constraint) {
                    genericNode* childNode = new genericNode();
                    edges.push_back(edgeId);

                    childNode -> edgesExplored = edges;

                    childNode -> rewardTotal = currentNode -> rewardTotal +
                                               additionalReward;

                    childNode -> riskTotal = currentNode -> riskTotal +
                                             additionalRisk;

                    dStruct.push_front(childNode);

                    if (childNode -> rewardTotal >
                        optimalSolution -> rewardTotal) {
                        optimalSolution = childNode;
                    }
                }

            }
            else {
                break;
            }
            iter++;
            edgeId++;
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now(); // TIMER END
    std::chrono::duration<double, std::milli> run_time = end_time - start_time;
    std::cout << "BFS EXECUTION TIME: " << run_time.count() / 1000 << "s \n";

    return optimalSolution;
}


genericNode* searchAlgos::depthFirstSearch(std::map<double, double> dict,
                                         double constraint, bool revisitation) {
    auto start_time = std::chrono::high_resolution_clock::now(); // TIMER START


    // TIME   COMPLEXITY  : O()
    // SPACE COMPLEXITY  : O()
    // OPTIMALITY       : NO GUARANTEE
    // LIFO OPERATIONS : push (idx: 0), pop (idx: 0)

    // 'revisitation' implamentation coming soon!

    std::map<double, double>::iterator iter;
    std::stack<genericNode*> dStruct;

    genericNode* root = new genericNode();
    genericNode* optimalSolution = new genericNode();
    genericNode* currentNode;

    int additionalReward;
    int additionalRisk;
    int currentRisk;

    std::vector<int> edges;
    int edgeId;
    bool explored;

    dStruct.push(root);

    while (dStruct.size() != 0) {
        currentNode = dStruct.top();
        dStruct.pop();

        iter = dict.begin();
        edgeId = 0;

        while (iter != dict.end()) {
            additionalReward = iter -> first;
            additionalRisk = iter -> second;
            currentRisk = currentNode -> riskTotal;

            edges = currentNode -> edgesExplored;
            explored = std::find(edges.begin(), edges.end(), edgeId)
                                 != edges.end();

            if (revisitation == false && explored == false) {
                currentRisk += additionalRisk;

                if (currentRisk <= constraint) {
                    genericNode* childNode = new genericNode();
                    edges.push_back(edgeId);

                    childNode -> edgesExplored = edges;

                    childNode -> rewardTotal = currentNode -> rewardTotal +
                                               additionalReward;

                    childNode -> riskTotal = currentNode -> riskTotal +
                                             additionalRisk;

                    dStruct.push(childNode);

                    if (childNode -> rewardTotal >
                        optimalSolution -> rewardTotal) {
                        optimalSolution = childNode;
                    }
                }

            }
            else {
                break;
            }
            iter++;
            edgeId++;
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // TIMER END
    std::chrono::duration<double, std::milli> run_time = end_time - start_time;
    std::cout << "DFS EXECUTION TIME: " << run_time.count() / 1000 << "s \n";
    return optimalSolution;
}






int main() {

    // map structure is auto sorted based on key size
    std::map<double, double> dict;
	dict.insert(std::make_pair(19, 14));
	dict.insert(std::make_pair(49, 40));
	dict.insert(std::make_pair(50, 50));
	dict.insert(std::make_pair(100, 100));
	dict.insert(std::make_pair(12, 13));
	dict.insert(std::make_pair(2, 3));
	dict.insert(std::make_pair(24, 32));
	dict.insert(std::make_pair(17, 9));
	dict.insert(std::make_pair(1, 2));
	dict.insert(std::make_pair(25, 35));
	dict.insert(std::make_pair(80, 12));


    searchAlgos OBJ;

    genericNode* BFSoptimalSolution = OBJ.breadthFirstSearch(dict, 100);
    genericNode* DFSoptimalSolution = OBJ.depthFirstSearch(dict, 100);


    std::vector<int> BFSitems = BFSoptimalSolution -> edgesExplored;
    std::vector<int>::iterator BFSit;
    std::cout << "\nitems   : ";
    for (auto BFSit = BFSitems.rbegin(); BFSit != BFSitems.rend(); BFSit++) {
        std::cout << *BFSit << " ";
    }
    std::cout << "\nbenefit : " << BFSoptimalSolution -> rewardTotal << "\n";
    std::cout << "weight  : " << BFSoptimalSolution -> riskTotal << "\n";


    std::vector<int> DFSitems = BFSoptimalSolution -> edgesExplored;
    std::vector<int>::iterator DFSit;
    std::cout << "\nitems   : ";
    for (auto DFSit = DFSitems.rbegin(); DFSit != DFSitems.rend(); DFSit++) {
        std::cout << *DFSit << " ";
    }
    std::cout << "\nbenefit : " << DFSoptimalSolution -> rewardTotal << "\n";
    std::cout << "weight  : " << DFSoptimalSolution -> riskTotal << "\n";



    return 0;
}
