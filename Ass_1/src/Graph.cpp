#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}
const vector<Party> Graph::getNeighbors(int partyId)const{
    vector<Party> neighbors;
    for (int i = 0; i < getNumVertices();i++){
        if(getEdgeWeight(i,partyId) != 0 ){
            neighbors.push_back(getParty(i));
        }
    }
    return neighbors;
}