#pragma once

#include <vector>
#include "Graph.h"
#include "Coalition.h"

class Graph;
class Simulation;
class SelectionPolicy;
class Coalition;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(const Agent& other);
    Agent& operator=(const Agent& other);
    Agent(Agent&& other) noexcept;
    Agent& operator=(Agent&& other) noexcept;
    ~Agent();
    int getPartyId() const;
    int getId() const;
    int getCoalitionId() const;
    void step(Simulation &);
    void clone(Simulation &s,Party &p);
    void setCol(int colId);
private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int mColId;
    void setPartyId(int id);
    void setId(int id);
};
