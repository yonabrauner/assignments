#pragma once
#include <vector>
#include "Coalition.h"
#include <string>

using std::vector;
class Agent;

class JoinPolicy
{
public:
    virtual void chooseCol(vector<Agent*> req,Party &p,Simulation &s) = 0;
};

class MandatesJoinPolicy : public JoinPolicy
{
public:
    virtual void chooseCol(vector<Agent*> req,Party &p,Simulation &s);
};

class LastOfferJoinPolicy : public JoinPolicy
{
public:
    virtual void chooseCol(vector<Agent*> req,Party &p,Simulation &s);
};