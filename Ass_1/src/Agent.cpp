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
    this->mColId = other.getCoalitionId();
}

//copy assignment operator
Agent& Agent::operator=(const Agent& other){
    if (this != &other){
        this->mAgentId = other.mAgentId;
        this->mPartyId = other.mPartyId;
        this->mSelectionPolicy = other.mSelectionPolicy;
        this->mColId = other.getCoalitionId();
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
    int numOfM = (g.getParty(mPartyId)).getMandates();
    mColId = this->getId();
    Coalition* newCol = new Coalition(mPartyId,numOfM);
    return newCol;
}


void Agent::clone(Simulation &s,Party &p){
    Agent cloned = Agent(*this);
    cloned.setPartyId(p.getId());
    cloned.setId(s.getAgents().size());
    cloned.mSelectionPolicy = this->mSelectionPolicy->cloneMe();
    s.addAgent(cloned);
}

void Agent::setPartyId(int id){
    mPartyId = id;
}

void Agent::setId(int id){
    mAgentId = id;
}

int Agent:: getCoalitionId()const{
    return mColId;
}

