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
        if (!p.getState() == Joined)
        {
            if(SelectionPolicy::isItFirstOffer(me,p)){
                if(p.getMandates() > bestM){
                    best = &p;
                }
            }
        }
    }
    if(best){
        best->makeOffer(me);
    }
}

void EdgeWeightSelectionPolicy::makeOffer(Agent &me,Simulation&s){
    int mine = me.getPartyId();
    const Graph* g = &(s.getGraph());
    int bestE = 0;
    Party* best = 0;
    for (Party p : g->getNeighbors(me.getPartyId())){
        if (!p.getState() == Joined && g->getEdgeWeight(mine,p.getId()) > bestE)
        {
            if(SelectionPolicy::isItFirstOffer(me,p)){
                best = &p;
            }
        }
    }
    if(best){
        best->makeOffer(me);
        best->setState(CollectingOffers);
    }
}

bool SelectionPolicy::isItFirstOffer(Agent &me, Party &p) const{
    vector<Agent*> offers = p.getOffers();
    for (Agent* a : offers){
        if(a->getCoalitionId()==me.getCoalitionId()){
            return false;
        }
    }
    return true;
}

//copy assignment operator
SelectionPolicy* MandatesSelectionPolicy::cloneMe(){
    MandatesSelectionPolicy* pol = new MandatesSelectionPolicy;
    return pol;
}

SelectionPolicy* EdgeWeightSelectionPolicy::cloneMe(){
    EdgeWeightSelectionPolicy* pol = new EdgeWeightSelectionPolicy;
    return pol;
}
