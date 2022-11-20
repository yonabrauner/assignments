#pragma once


class Agent;
class Party;


class SelectionPolicy {
    public:
    bool isItFirstOffer(Agent &me,Party &p) const;
    virtual void makeOffer(Agent &me,Simulation &s);
    virtual SelectionPolicy* cloneMe();
 };

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
    virtual void makeOffer(Agent &me,Simulation &s);
    virtual SelectionPolicy* cloneMe();

 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    public:
    virtual void makeOffer(Agent &me,Simulation &s);
    virtual SelectionPolicy* cloneMe();
 };