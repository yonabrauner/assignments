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
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);  //constructor
    ~Agent();                                   //destructor
    Agent(const Agent& other);                  //copy constructor
    Agent& operator=(const Agent& other);       //copy assignment operator
    Agent(Agent&& other) noexcept;              //move constructor  
    Agent& operator=(Agent&& other) noexcept;   //move assignment operator
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
