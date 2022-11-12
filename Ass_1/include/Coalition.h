#pragma once

#include <vector>
#include "Party.h"
#include "Graph.h"



using std::vector;

class Coalition
{

public:
    int mMandates;
    vector<int> col;
    Coalition(int partyID);
    Coalition()
    ~Coalition()
    Coalition(const Coalition &other);
    getCoalitionVector();
    getNumMandates();
    addToCoaltion(int partyID);
};

