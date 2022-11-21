#include "Party.h"
#include "JoinPolicy.h"
class JoinPolicy;

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp),
 mState(Waiting),timer(0),offers()
{   
    
}

//destructor
Party::~Party(){
    this->mName.erase();
    delete this->mJoinPolicy;
    this->offers.clear();
    this->offers.~vector();
}                     

//copy constructor 
Party::Party(const Party& other):mId(), mName(), mMandates(), mJoinPolicy(),
 mState(),timer(),offers(){
    this->mId = other.mId;
    this->mName = other.mName;
    this->mMandates = other.mMandates;
    this->mJoinPolicy = other.mJoinPolicy->cloneMe();
    this->mState = other.mState;
    this->timer = other.timer;
    this->offers = other.offers;
}            

//copy assignment operator
Party& Party:: operator=(const Party& other){
    if (this != &other){
        this->mName.erase();
        delete this->mJoinPolicy;
        this->offers.clear();
        this->offers.~vector();
        this->mId = other.mId;
        this->mName = other.mName;
        this->mMandates = other.mMandates;
        this->mJoinPolicy = other.mJoinPolicy->cloneMe();
        this->mState = other.mState;
        this->timer = other.timer;
        this->offers = other.offers;
    }
    return *this;
}

//move constructor
Party::Party(Party&& other) noexcept : mId(other.mId), mName(other.mName), mMandates(other.mMandates),mJoinPolicy(),
 mState(other.mState),timer(other.timer), offers(other.offers){
    this->mJoinPolicy = other.mJoinPolicy->cloneMe();
    other.mName.erase();
    delete other.mJoinPolicy;
    other.offers.clear();
    other.offers.~vector();
}         

//move assignment operator
Party& Party:: operator=(Party&& other) noexcept {
    if (this != &other){
        this->mName.erase();
        delete this->mJoinPolicy;
        this->offers.clear();
        this->offers.~vector();
        this->mId = other.mId;
        this->mName = other.mName;
        this->mMandates = other.mMandates;
        this->mJoinPolicy = other.mJoinPolicy->cloneMe();
        this->mState = other.mState;
        this->timer = other.timer;
        this->offers = other.offers;
        other.mName.erase();
        delete other.mJoinPolicy;
        other.offers.clear();
        other.offers.~vector();
    }
    return *this;
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

