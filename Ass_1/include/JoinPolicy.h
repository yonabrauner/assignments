#pragma once
#include <vector>
#include "Coalition.h"
#include <string>

using std::vector;
class Agent;

class JoinPolicy
{
public:
    virtual void chooseCol(vector<int> req,Party &p,Simulation &s) = 0;
    virtual ~JoinPolicy() = default;
    virtual JoinPolicy* cloneMe() = 0;
};

class MandatesJoinPolicy : public JoinPolicy
{
public:
    virtual void chooseCol(vector<int> req,Party &p,Simulation &s);
    virtual JoinPolicy* cloneMe();
    // virtual ~JoinPolicy() = default;
};

class LastOfferJoinPolicy : public JoinPolicy
{
public:
    virtual void chooseCol(vector<int> req,Party &p,Simulation &s);
    virtual JoinPolicy* cloneMe();
    // virtual ~JoinPolicy() = default;

};