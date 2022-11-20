#include "Agent.h"
#include "Coalition.h"
#include "Graph.h"
#include "SelectionPolicy.h"
#include "Simulation.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
    

}
//copy constructor
Agent::Agent(const Agent& other){
    this->mAgentId = other.getId();
    this->mPartyId = other.getPartyId();
    this->mSelectionPolicy = other.mSelectionPolicy;
    this->myCoaltion = other.getCoalition();
}

//copy assignment operator
Agent& Agent::operator=(const Agent& other){
    if (this != &other){
        this->mAgentId = other.mAgentId;
        this->mPartyId = other.mPartyId;
        this->mSelectionPolicy = other.mSelectionPolicy;
        this->myCoaltion = other.getCoalition();
    }
    return *this;
}

//move constructor
Agent::Agent::Agent(Agent&& other) noexcept{
    this->mAgentId = other.mAgentId;
    this->mPartyId = other.mPartyId;

}
//destructor    
Agent::~Agent(){
    delete myCoaltion;
    myCoaltion = nullptr;
    delete mSelectionPolicy;
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
    mSelectionPolicy->makeOffer(*this,sim);
}

Coalition* Agent ::create_Coaliton(Graph g){
    Party party = (g.getParty(mPartyId));
    Party* qwe = &party;
    mycol = this->getId();
    return &Coalition(qwe);
}

Coalition* Agent::getCoalition() const{
    return myCoaltion;
}

void Agent::clone(Simulation &s,Party &p){
    Agent cloned = Agent(*this);
    //need to change id from info from mAgents and need to change mParty
    cloned.mPartyId = p.getId();
    cloned.mAgentId = s.getAgents().size();
    cloned.mSelectionPolicy = this->mSelectionPolicy;
    s.addAgent(cloned);
}

