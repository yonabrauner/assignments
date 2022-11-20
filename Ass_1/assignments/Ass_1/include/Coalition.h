#pragma once

#include <vector>
#include "Party.h"
#include "Graph.h"



using std::vector;

class Coalition
{

public:
    Coalition(Party*);
    Coalition();
    Coalition(Coalition &);
    ~Coalition();
    Coalition(const Coalition& other);
    Coalition& operator=(const Coalition& other);
    Coalition::Coalition(Coalition&& other) noexcept;
    Coalition& Coalition::operator=(Coalition&& other) noexcept;
    const vector <Party*> getCoalitionVector()const;
    const vector <int> getOutputVector(Coalition &me)const;
    int getNumMandates() const;
    const void addToCoaltion(Party* Party);

private:
    int mMandates;
    vector<Party*> col;
};

