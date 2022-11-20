#pragma once


class Agent;
class Party;


class SelectionPolicy {
    public:
    virtual void makeOffer(Agent &me,Simulation &s);
    bool isItFirstOffer(Agent &me,Party &p) const;
 };

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
    virtual void makeOffer(Agent &me,Simulation &s);
 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    public:
    virtual void makeOffer(Agent &me,Simulation &s);
 };