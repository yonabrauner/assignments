// #include <vector>
#include "Coalition.h"


//constructor
Coalition::Coalition(){
    col = new vector<int>
    mMandates = new int(0);
}
Coalition::Coalition(int partyID) {
    mMandates = new int(0);
    col = new vector<int>
    col.push_back(partyID);
}
//destructor
Coalition::~Coalition(){delete col;delete mMandates}
//copy constructor
Coalition:: Coalition(Coalition &other){
        this = new Coalition();
        this = other;
}
//copy assignment operator
Coalition::Coalition &operator=(const Coalition &other){
    if(this != other){
        this.mMandates = other.getNumMandates();
        *col = *(other.getCoalitionVector());
    }
}
vector<int> Coalition::getCoalitionVector(){
    // return col
}

int Coalition::getNumMandates(){
    return mMandates;
}

void Coalition::addToCoaltion(int partyID){
    //push the id into coalition
    //update mMandates
}

