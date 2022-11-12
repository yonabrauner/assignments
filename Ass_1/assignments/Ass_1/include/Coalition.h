#pragma once

#include <vector>
#include "Party.h"
#include "Graph.h"



using std::vector;

class Coalition
{

public:
    int mMandates;
    std::vector<Party> col;
    Coalition(Party Party);
    Coalition();
    Coalition(Coalition &other);
    ~Coalition();
    const vector <Party> getCoalitionVector();
    const vector <int> getOutputVector(Coalition me);
    int getNumMandates() const;
    void addToCoaltion(Party Party);
};

