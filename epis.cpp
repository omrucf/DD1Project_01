#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;


struct minterms
{
    int coverageCount = 0;
    string binRep;
    set<int> decimals; //minterms;
    set<int> posOf_;
};


vector<minterms> findEPIs(vector<minterms> primeImplicants, vector<int> onSet)
{
    
    vector<minterms> EPI;
    //update coverage count
    for(auto i = 0; i < primeImplicants.size(); i++)
    {
        for(int j = 0; j < onSet.size(); j++)
        {
            if(primeImplicants[i].decimals.find(onSet[j]) != primeImplicants[i].decimals.end())
            {
                primeImplicants[i].coverageCount++;
            }
        }

    }

    for(int it = 0; it < primeImplicants.size(); it++)
    {
        int cnt = primeImplicants[it].coverageCount;
        if(cnt == 1)
            EPI.push_back(primeImplicants[it]);
    }

    return EPI;
}

bool booleanRep(minterms input)
{
    for(int i = 0; i < input.binRep.size(); i++)
    {
        if(input.binRep[i] == '1')
        {
            cout << char(i + 65);

        } else if(input.binRep[i] == '0') {
            string temp;
            temp += '(';
            temp += char(33);
            temp += char(i + 65);
            temp += ')';
            cout << temp;
        }
        else if(input.binRep[i] == '_'){
            continue;
        }
    }

    cout << "   ";
    return true;
}

int main()
{
    vector<minterms> primeImplicants;
    minterms m1;
    m1.decimals.insert(10);
    m1.binRep = "1011";

    minterms m2;
    m2.decimals.insert(10);
    m2.binRep = "1101";

    minterms m3;
    m3.decimals.insert(4);
    m3.binRep = "1101";

    primeImplicants.push_back(m1);
    primeImplicants.push_back(m2);
    primeImplicants.push_back(m3);

    vector<int> onset;
    onset.push_back(10);

    vector<minterms> epi;
    epi = findEPIs(primeImplicants, onset);

//    for(auto it = epi.begin(); it != epi.end(); it++)
//     {
//         cout << (*it).binRep;
//     }

    for(auto it = epi.begin(); it != epi.end(); it++)
    {
        //cout << (*it).binRep;

        booleanRep(*it);
    }

}
