#include <vector>
#include "Coalition.h"
#include "Party.h"

class party;

//constructor1
Coalition::Coalition(){
    mMandates = 0;
}

//constructor2
Coalition::Coalition(Party* party) {
    mMandates = 0;
    col.push_back(party);
}

//destructor
Coalition::~Coalition(){this->col.clear();}

//copy constructor
Coalition::Coalition(const Coalition &other){
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
	    	return *this;
		}
	}

//move constructor
Coalition::Coalition(Coalition&& other) noexcept : col(other.col), mMandates(other.mMandates)
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


const vector<Party*> Coalition::getCoalitionVector()const{
    return col;
}
const vector<int> Coalition::getOutputVector(Coalition &me)const{
    vector<int> output;
    for (Party* party: col){
        output.push_back(party->getId());
    }
    return output;
}
int Coalition::getNumMandates()const{
    return mMandates;
}

const void Coalition::addToCoaltion(Party* party) {
    col.push_back(party);
    mMandates = mMandates + party->getMandates();
}

//constructor
// Coalition::Coalition(){
//     mMandates = 0;
// }
// Coalition::Coalition(Party party) {
//     mMandates = 0;
//     col.push_back(party);
// }
// //destructor
// Coalition::~Coalition(){delete &this->col;}
// //copy constructor
// Coalition:: Coalition(const Coalition &other){
    

// }
// Coalition:: Coalition(Coalition  &other){
//         mMandates = other.getNumMandates();
//         col = other.getCoalitionVector();
// }
// // copy assignment operator
// Coalition&  Coalition:: operator=(const Coalition& other)
// 	{
// 		if (this == &other) {
// 			return *this;
// 		}
//         delete &col;
//         col = other.col;
//         mMandates = other.mMandates; 
// 		return *this;
// 	}

