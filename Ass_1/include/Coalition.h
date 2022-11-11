#pragma once

#include <vector>
#include "Party.h"
#include "Graph.h"



using std::vector;

class Coalition
{
public:
    Coalition(int partyID);
    vector<int> col;
    int mandates;
};

