


#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>

#include <chrono> // raplce w/ ctime?

#include <deque> // for breadthFirstSearch
#include <stack> // for depthFirstSearch


#include "exports.h"


std::map<double, double> randomRewardRiskProducts(int numProducts,
                         double rewardMin=0, double rewardMax=100,
                         double riskMin=1, double riskMax=100) {
    std::map<double, double> dict;
    double reward;
    double risk;

    int seed = rand();
    std::default_random_engine generator(seed);


    for (int i = 0; i < numProducts; i++) {
        std::uniform_real_distribution<double> riskDist(riskMin, riskMax);
        std::uniform_real_distribution<double> rewardDist(rewardMin, rewardMax);
        dict.insert(std::make_pair(rewardDist(generator), riskDist(generator)));
    }

    return dict;
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
    srand(time(NULL)); // set random seed

    // map structure is auto sorted based on key size
    // BFS and DFS should in theory therefor yield identical results
    std::map<double, double> dict = randomRewardRiskProducts(60);

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
