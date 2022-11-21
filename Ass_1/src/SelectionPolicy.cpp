#include "SelectionPolicy.h"
#include <vector>
#include "Party.h"
#include "Simulation.h"

class Simulation;
class Party;


void MandatesSelectionPolicy::makeOffer(Agent &me,Simulation &s){
    const Graph* g = &(s.getGraph());
    int bestM = 0;
    Party* best = 0;
    for (Party p : g->getNeighbors(me.getPartyId())){
        if (!(p.getState() == Joined))
        {
            if(isItFirstOffer(me,p,s)){
                if(p.getMandates() > bestM){
                    best = &p;
                }
            }
        }
    }
    if(best){
        best->submitAnOffer(me.getId());
    }
}

void EdgeWeightSelectionPolicy::makeOffer(Agent &me,Simulation& s){
    int mine = me.getPartyId();
    const Graph* g = &(s.getGraph());
    int bestE = 0;
    Party* best = 0;
    for (Party p : g->getNeighbors(me.getPartyId())){
        if (!(p.getState() == Joined) && g->getEdgeWeight(mine,p.getId()) > bestE)
        {
            if(isItFirstOffer(me,p,s)){
                best = &p;
            }
        }
    }
    if(best){
        best->submitAnOffer(me.getId());
        best->setState(CollectingOffers);
    }
}

bool SelectionPolicy::isItFirstOffer(Agent &me, Party &p,Simulation &s) const{
    vector<int> offers = p.getOffers();
    vector<Agent> allAgent = s.getAgents();
    for (int id : offers){
        if(allAgent.at(id).getCoalitionId() == me.getCoalitionId()){
            return false;
        }
    }
    return true;
}

SelectionPolicy* MandatesSelectionPolicy::cloneMe(){
    MandatesSelectionPolicy* pol = new MandatesSelectionPolicy;
    return pol;
}

SelectionPolicy* EdgeWeightSelectionPolicy::cloneMe(){
    EdgeWeightSelectionPolicy* pol = new EdgeWeightSelectionPolicy;
    return pol;
}
