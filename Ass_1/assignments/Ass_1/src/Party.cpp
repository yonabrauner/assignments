#include "Party.h"
#include "JoinPolicy.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp),
 mState(Waiting),timer(0),req() 
{
    // You can change the implementation of the constructor, but not the signature!
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
        makedesicion();
    }
}

int Party::getId() const{
    return mId;
}

void Party:: addReq(Coalition col){

}
void JoinPolicy:: chooseCol(vector<Coalition>){
    if (/* condition */)
    {
        /* code */
    }   
    
}

void MandatesJoinPolicy:: chooseByM(vector<Coalition>){

}
void LastOfferJoinPolicy::chooseByL(vector<Coalition>){
}


