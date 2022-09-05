


struct genericNode {

    std::vector<int> edgesExplored;
    double rewardTotal = 0;
    double riskTotal = 0;

};

struct searchAlgos {

    genericNode* breadthFirstSearch(std::map<double, double> dict,
                                    double constraint,
                                    bool revisitation=false);


    genericNode* depthFirstSearch(std::map<double, double> dict,
                                  double constraint,
                                  bool revisitation=false);
};
