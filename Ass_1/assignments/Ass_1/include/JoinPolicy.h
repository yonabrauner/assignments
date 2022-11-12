#pragma once

class JoinPolicy {
    void chooseCol(vector<Coalition>);
};

class MandatesJoinPolicy : public JoinPolicy {
    void chooseByM(vector<Coalition>);
};

class LastOfferJoinPolicy : public JoinPolicy {
    void chooseByL(vector<Coalition>);

};