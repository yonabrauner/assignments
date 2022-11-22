#include "Party.h"
#include "JoinPolicy.h"
class JoinPolicy;

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp),
 mState(Waiting),timer(0),offers()
{   
    
}

//destructor
Party::~Party(){
    // this->mName.erase();
    // // this->offers.clear();
    // this->offers.~vector();
    // delete mJoinPolicy;
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
        this->cleanup();
        this->mName = other.getName();
        this->mId = other.getId();
        this->mMandates = other.getMandates();
        this->mJoinPolicy = other.mJoinPolicy;//create a getter
        this->mState = other.getState();
        this->timer = other.getTime();
        this->offers = other.offers;
        // this->mName = nullptr;
        other.mJoinPolicy = nullptr;
        // other.offers;

        // this->mName.erase();
        // // delete this->mJoinPolicy;
        // this->offers.clear();
        // this->offers.~vector();
        // this->mId = other.mId;
        // this->mName = other.mName;
        // this->mMandates = other.mMandates;
        // this->mJoinPolicy = other.mJoinPolicy->cloneMe();
        // this->mState = other.mState;
        // this->timer = other.timer;
        // this->offers = other.offers;
        // other.mName.erase();
        // // delete other.mJoinPolicy;
        // other.offers.clear();
        // other.offers.~vector();
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
        if(timer == 3){
        mJoinPolicy->chooseCol(offers,*this,s);
        setState(Joined);
        offers.clear();
    }
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
void Party::cleanup(){
    this->mName.erase();
    mJoinPolicy =nullptr;
    this->offers.~vector();
}

