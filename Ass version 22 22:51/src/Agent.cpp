#include "Agent.h"
#include "Coalition.h"
#include "Graph.h"
#include "SelectionPolicy.h"
#include "Simulation.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy),
mColId()
{
    // You can change the implementation of the constructor, but not the signature!
}

//destructor    
Agent::~Agent(){
    delete mSelectionPolicy;
}

//copy constructor
Agent::Agent(const Agent& other): mAgentId(), mPartyId(), mSelectionPolicy(),
mColId(){
    this->mAgentId = other.getId();
    this->mPartyId = other.getPartyId();
    this->mSelectionPolicy = other.mSelectionPolicy->cloneMe();
    this->mColId = other.getCoalitionId();
}

//copy assignment operator
Agent& Agent::operator=(const Agent& other){
    if (this != &other){
        this->mAgentId = other.mAgentId;
        this->mPartyId = other.mPartyId;
        this->mSelectionPolicy = other.mSelectionPolicy->cloneMe();
        this->mColId = other.getCoalitionId();
    }
    return *this;
}

//move constructor
Agent::Agent(Agent&& other) noexcept : mAgentId(), mPartyId(), mSelectionPolicy(),
mColId() 
{
    this->mAgentId = other.mAgentId;
    this->mPartyId = other.mPartyId;
    this->mSelectionPolicy = other.mSelectionPolicy->cloneMe();
    this->mColId = other.mColId;
    other.mSelectionPolicy = nullptr;
}

//move assignment operator
Agent& Agent::operator=(Agent&& other) noexcept{
    if (this != &other){
        delete this->mSelectionPolicy;
        this->mAgentId = other.mAgentId;
        this->mColId = other.mColId;
        this->mPartyId = other.mPartyId;
        this->mSelectionPolicy = other.mSelectionPolicy;
        other.mSelectionPolicy = nullptr;
    }
    return *this;
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

void Agent:: setCol(int colId){
    mColId = colId;
}