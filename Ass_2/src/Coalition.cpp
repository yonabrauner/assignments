#include <vector>
#include "Coalition.h"
#include "Party.h"

class party;

//constructor1
Coalition::Coalition() : mMandates(),col(){
    mMandates = 0;
}

//constructor2
Coalition::Coalition(int partyId,int numOfM): mMandates(),col() {
    mMandates = numOfM;
    col.push_back(partyId);
}

//destructor
Coalition::~Coalition(){this->col.clear();}

//copy constructor
Coalition::Coalition(const Coalition &other) : mMandates(),col(){
        this->mMandates = other.getNumMandates();
        this->col = other.getCoalitionVector();
}

// copy assignment operator
Coalition& Coalition:: operator=(const Coalition& other)
	{
		if (this != &other) {
			delete &col;
            col = other.col;
            mMandates = other.mMandates; 
	    	
		}
        return *this;
	}

//move constructor
Coalition::Coalition(Coalition&& other) noexcept : mMandates(other.mMandates),col(other.col)
{
    other.col.clear();
    other.col.~vector();
}

//move assignment operator -FIXME
Coalition& Coalition::operator=(Coalition&& other) noexcept{
    if (this != &other){
        this->col.clear();
        this->col = other.col; //deep copy?
        //need to change the vector pointer before clearing it?
        this->mMandates = other.mMandates;
    }
    return *this;
}


const vector<int> Coalition::getCoalitionVector()const{
    return col;
}

int Coalition::getNumMandates()const{
    return mMandates;
}

const void Coalition::addToCoaltion(int partyId, int numOfM) {
    col.push_back(partyId);
    mMandates = mMandates + numOfM;
}