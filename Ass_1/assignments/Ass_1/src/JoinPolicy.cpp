#include "JoinPolicy.h"
#include <iostream>
#include <string>
#include <vector>
#include "Coalition.h"
#include "Simulation.h"

using std::string;
using std::vector;


void MandatesJoinPolicy::chooseCol(vector<Agent*> req,Party &p,Simulation &s){
    Agent* best = 0;
    best = (req.back());
    req.pop_back();
    int numOfM = s.getCoalitionById(best->getCoalitionId())->getNumMandates();
    while(!req.empty()){
        Agent* curr = req.back();
        if(s.getCoalitionById(best->getCoalitionId())->getNumMandates() >= numOfM){
            best = curr;
        }
        req.pop_back();
    }
    Coalition* newcol = s.getCoalitionById(best->getCoalitionId());
    newcol->addToCoaltion(&p);
    best->clone(s,p);
};

void LastOfferJoinPolicy::chooseCol(vector<Agent*> req,Party &p,Simulation &s){
    Agent* best = 0;
    best = (req.back());
    Coalition* newcol = s.getCoalitionById(best->getCoalitionId());
    newcol->addToCoaltion(&p);
    best->clone(s,p);
    req.clear();
}

