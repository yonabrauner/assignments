#include <iostream>
#include "Coalition.h"
#include "Party.h"
#include "Simulation.h"
#include <vector>

class Coalition;

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents),mCoalitions()
{
    for (Agent& agent: mAgents){
        Party p = mGraph.getParty(agent.getPartyId());
        Coalition* coNew = new Coalition(p.getId(),p.getMandates());
        mCoalitions.push_back(coNew);
        agent.setCol(agent.getId());
    }
}

void Simulation::step()
{
    int numOfParties = mGraph.getNumVertices();
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
    for (const Coalition* col: mCoalitions){
        n = col->getNumMandates();
        if(n>60){
            return true;
        }
        sum = sum + n;
    }
    if(sum == 120){
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
void Simulation:: addAgent(Agent &a){
    mAgents.push_back(a);
}

// vector<Coalition*> &Simulation::getCoalitions() const
// {
//     return mCoalitions;
// }

Coalition* Simulation::getCoalitionById(int colId){
    return mCoalitions.at(colId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> output;
    for(const Coalition* col : mCoalitions){
        output.push_back(col->getCoalitionVector());
    }
    return output;
}
