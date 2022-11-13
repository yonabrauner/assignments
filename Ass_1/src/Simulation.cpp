#include "Simulation.h"
#include <iostream>
#include "Coalition.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents)
{
    for (Agent& agent: mAgents){
        agent.create_Coaliton(graph);
        mCoalitions.push_back(agent.getCoalition());
        Party party = mGraph.getParty(agent.getPartyId());
        party.setState(Joined);
    }
}

void Simulation::step()
{
    int numOfParties = mGraph.getNumVertices();
    std::cout << numOfParties;
    for (int i = 0; i<numOfParties; i++){
        Party party = (mGraph.getParty(i));
        party.step(*this);
    }
    for(Agent& agent: mAgents){
        agent.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    int sum = 0;
    int n;
    for (const Coalition& col: mCoalitions){
        n = col.getNumMandates();
        if(n>60){
            return true;
        }
        sum = sum + n;
    }
    if(sum = 120){
        return true;
    }
    return false;
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

const vector<Coalition> &Simulation::getCoalitions() const
{
    return mCoalitions;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return vector<vector<int>>();
}
