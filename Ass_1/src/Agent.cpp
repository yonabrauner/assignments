#include "Agent.h"
#include "Coalition.h"
#include "Graph.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
    

}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method
}

void Agent ::create_Coaliton(Graph g){
    Party party = g.getParty(mPartyId);
    myCoaltion = Coalition(party);
}

Coalition Agent::getCoalition(){
    return myCoaltion;
}

// void makeSelection(){

// }

