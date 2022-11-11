#include "Simulation.h"
#include <iostream>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    for (Agent& agent: mAgents){
        agent.createCoalition();
    }
}

void Simulation::step()
{
    int numOfParties = mGraph.getNumVertices();
    std::cout << numOfParties;
    //for each party:
    //  take a step
    //for each agent:
    //  step
    //if "should terminate" - terminate
}

bool Simulation::shouldTerminate() const
{
    // if all parties are in joined,
    // if there is a coalition 
    return true;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return vector<vector<int>>();
}
