#pragma once

#include <vector>
#include "Party.h"
#include "Graph.h"


class Party;
using std::vector;

class Coalition
{

public:
    Coalition(int partyId,int numOfM);
    Coalition();
    Coalition(Coalition &);
    ~Coalition();
    Coalition(const Coalition& other);
    Coalition& operator=(const Coalition& other);
    Coalition(Coalition&& other) noexcept;
    Coalition& operator=(Coalition&& other) noexcept;
    const vector <int> getCoalitionVector()const;
    int getNumMandates() const;
    const void addToCoaltion(int partyId, int numOfM);

private:
    int mMandates;
    vector<int> col;
};

