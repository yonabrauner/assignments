#include <vector>
#include "Coalition.h"


//constructor
Coalition::Coalition(){
    mMandates = 0;
}
Coalition::Coalition(Party party) {
    mMandates = 0;
    col.push_back(party);
}
//destructor
Coalition::~Coalition(){delete &this->col;}
//copy constructor
Coalition:: Coalition(Coalition  &other){
        mMandates = other.getNumMandates();
        col = other.getCoalitionVector();
}
// copy assignment operator
Coalition&  Coalition:: operator=(const Coalition& other)
	{
		if (this == &other) {
			return *this;
		}
        delete &col;
        col = other.col;
        mMandates = other.mMandates; 
		return *this;
	}
const vector<Party> Coalition::getCoalitionVector(){
    return col;
}
// const vector<int> Coalition::getOutputVector(){
//     vector<int> output;
//     for (Party& party : col){
//         output.push_back(party.getId);
//     }
//     return output;
// }
int Coalition::getNumMandates()const{
    return mMandates;
}

void Coalition::addToCoaltion(Party party){
    col.push_back(party);
    mMandates = mMandates + party.getMandates();
}



