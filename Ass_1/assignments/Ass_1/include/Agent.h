#pragma once

#include <vector>
#include "Graph.h"
#include "Coalition.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(const Agent& other);
    Agent& operator=(const Agent& other);
    Agent::Agent(Agent&& other) noexcept;
    Agent& Agent::operator=(Agent&& other) noexcept;
    ~Agent();
    int getPartyId() const;
    int getId() const;
    int getCoalitionId() const;
    void step(Simulation &);
    Coalition* create_Coaliton(Graph g);
    void clone(Simulation &s,Party &p);
private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int mColId;
    void setPartyId(int id);
    void setId(int id);

};
