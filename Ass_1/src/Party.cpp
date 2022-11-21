#include "Party.h"
#include "JoinPolicy.h"
class JoinPolicy;

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp),
 mState(Waiting),timer(0),offers()
{   
    
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{   
    if(getState() == CollectingOffers){
        timer++;
    }
    if(timer == 3){
        mJoinPolicy->chooseCol(offers,*this,s);
        setState(Joined);
    }
}

int Party::getId() const{
    return mId;
}

int Party::getTime() const{
    return timer;
}
vector<int> Party::getOffers()const{
    return offers;
}

void Party::submitAnOffer(int agentId){
    offers.push_back(agentId);
}

