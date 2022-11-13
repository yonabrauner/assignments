#pragma once

class JoinPolicy {
    JoinPolicy(String &e);
    virtual void chooseCol(vector<Coalition> req){};
};

class MandatesJoinPolicy : public JoinPolicy {
public:

    MandatesJoinPolicy();
    vitural void chooseCol(vector<Coalition> req);
};

class LastOfferJoinPolicy : public JoinPolicy {
public:

    LastOfferJoinPolicy();
    virtual void chooseCol(vector<Coalition> req);
};