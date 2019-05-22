Two_Opt::Two_Opt(const Graph & graph) : graph(graph), dfs(graph), astar(graph) { }


// Performs  iterations in attempt to improve current solution until no improvement is found
vector<u_int> Two_Opt::performImprovement(vector<u_int> visitOrder, double visitOrderWeight) {
    double bestWeight = visitOrderWeight;
    vector<u_int> bestVisitOrder = visitOrder;

    u_int startNodeId = visitOrder.at(0);
    u_int finishNodeId = visitOrder.at(visitOrder.size()-1);

    // Start and Finish node can't be included, since they have fixed positions in the visit order
    u_int numNodesForSwap = visitOrder.size() - 2;

    double lastBestWeight = -1;

    // Repeat until no improvement
    while (lastBestWeight != bestWeight) {

        lastBestWeight = bestWeight;

        for (u_int i=1 ; i<=numNodesForSwap-1 ; i++){
            for (u_int k=i+1 ; k<=numNodesForSwap ; k++) {
                visitOrder = twoOptSwap(bestVisitOrder, i, k);

                if (!isVisitOrderValid(visitOrder)) {
                    continue;
                }

                visitOrderWeight = calcPathWeight(visitOrder);

                if (visitOrderWeight < bestWeight) {
                    bestVisitOrder = visitOrder;
                    bestWeight = visitOrderWeight;
                }
            }
        }
    }

    return bestVisitOrder;
}

vector<u_int> Two_Opt::twoOptSwap(vector<u_int> visitOrder, u_int i, u_int k) const {
    // Swap the vector elements between the range [i,k]
    while (i<k) {
        visitOrder.at(i) ^= visitOrder.at(k);
        visitOrder.at(k) ^= visitOrder.at(i);
        visitOrder.at(i) ^= visitOrder.at(k);
        i++;
        k--;
    }

    return visitOrder;
}
