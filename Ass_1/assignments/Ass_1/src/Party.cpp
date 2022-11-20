#include "Party.h"
#include "JoinPolicy.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp),
 mState(Waiting),timer(0),req()
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
        mJoinPolicy->chooseCol(req,*this,s);
        setState(Joined);
    }
}

int Party::getId() const{
    return mId;
}

int Party::getTime() const{
    return timer;
}
vector<Agent*> Party::getOffers()const{
    return req;
}

void Party::makeOffer(Agent &a){
    req.push_back(&a);
}

