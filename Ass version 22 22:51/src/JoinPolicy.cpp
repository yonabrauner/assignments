#include "JoinPolicy.h"
#include <iostream>
#include <string>
#include <vector>
#include "Coalition.h"
#include "Simulation.h"

using std::string;
using std::vector;
class JoinPolicy;

 void MandatesJoinPolicy::chooseCol(vector<int> req,Party &p,Simulation &s){
    //make sure we dont go in an empty vector
    vector<Agent> allAgents = s.getAgents();
    Agent best = allAgents.at(req.back());
    req.pop_back();
    int numOfM = s.getCoalitionById(best.getCoalitionId())->getNumMandates();
    while(!req.empty()){
        Agent curr = allAgents.at(req.back());
        if(s.getCoalitionById(curr.getCoalitionId())->getNumMandates() >= numOfM){
            best = curr;
        }
        req.pop_back();
    }
    Coalition* newcol = s.getCoalitionById(best.getCoalitionId());
    newcol->addToCoaltion(p.getId(),p.getMandates());
    best.clone(s,p);
    req.clear();
};

void LastOfferJoinPolicy::chooseCol(vector<int> req,Party &p,Simulation &s){
    // vector<Agent> allAgents = s.getAgents();
    // Agent best = allAgents.at(req.back());
    // Coalition* newcol = s.getCoalitionById(best.getCoalitionId());
    // newcol->addToCoaltion(p.getId(),p.getMandates());
    // best.clone(s,p);
    // req.clear();
    int bestId = req.back();
    s.acceptOffer(bestId,p.getId());
}

JoinPolicy* MandatesJoinPolicy::cloneMe(){
    JoinPolicy* pol = new MandatesJoinPolicy(*this);
    return pol ;
}

JoinPolicy* LastOfferJoinPolicy::cloneMe(){
    JoinPolicy* pol = new LastOfferJoinPolicy(*this);
    return pol;
}