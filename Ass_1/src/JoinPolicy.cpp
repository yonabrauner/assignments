#include "JoinPolicy.h"
#include <iostream>
#include <string>
#include <vector>

using std::string;


JoinPolicy:: JoinPolicy(string &e){
    if(e == "M"){
        JoinPolicy M = MandatesJoinPolicy();
        return M;
    }
    JoinPolicy L = LastOfferJoinPolicy();
    return L;
}

MandatesJoinPolicy:: MandatesJoinPolicy(){

};
LastOfferJoinPolicy:: LastOfferJoinPolicy(){

};
