#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


struct minterms
{
    string binRep;
    set<int> decimals; //minterms;
    set<int> posOf_;
};


vector<minterms> findEPIs(vector<minterms> primeImplicants, vector<int> onSet)
{
    
    vector<minterms> EPI;
    int onSetCoverageCount[onSet.size()];
    for(int i = 0; i < onSet.size(); i++)
    {
        onSetCoverageCount[i] = 0;
    }

    //update coverage count
    for(int i = 0; i < primeImplicants.size(); i++)
    {
        for(int j = 0; j < onSet.size(); j++)
        {
            if(primeImplicants[i].decimals.find(onSet[j]) != primeImplicants[i].decimals.end())
            {
                onSetCoverageCount[j]++;
            }
        }

    }

    for(int it = 0; it < onSet.size(); it++)
    {
        if(onSetCoverageCount[it] == 1)
        {
            for(int i = 0; i < primeImplicants.size(); i++)
            {
                if(primeImplicants[i].decimals.find(onSet[it]) != primeImplicants[i].decimals.end())
                    EPI.push_back(primeImplicants[i]);
            }
        }
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

bool mintermsNotCovered(vector<minterms> epi, vector<int> onSet)
{
    set<int> mintermsCovered;
    for(auto it = epi.begin(); it != epi.end(); it++)
    {
        set<int> temp = it->decimals;
        for(auto it2 = temp.begin(); it2 != temp.end(); it2++)
        {
            int minterm = *it2;
            mintermsCovered.insert(minterm);
        }
    }

    for(int i = 0; i < onSet.size(); i++)
    {
        if(mintermsCovered.find(onSet[i]) == mintermsCovered.end())
        {
            cout << onSet[i] << "   ";
        }
    }

    cout << endl;
    return true;
}

bool isDominatingColumn(vector<minterms> primeImplicants, vector<int> onSet, int column)
{
    vector<set<int>> columns;
    for(int i = 0; i < primeImplicants.size(); i++)
    {
        for(auto it = primeImplicants[i].decimals.begin(); it != primeImplicants[i].decimals.end(); it++)
            columns[*it].insert(i);
    }

    int count = -1;
    for(auto it = columns.begin(); it != columns.end(); it++)
    {
        count ++;
        if(includes(columns[column].begin(), columns[column].end(),it->begin(), it->end()) && column != count)
            return true;
    }

    return false;
}

bool isDominatedRow(vector<minterms> primeImplicants, vector<int> onSet, int row)
{
    int count = -1;
    for(auto it = primeImplicants.begin(); it != primeImplicants.end(); it++)
    {
        count ++;
        if(includes(it->decimals.begin(), it->decimals.end(), primeImplicants[row].decimals.begin(), primeImplicants[row].decimals.end()) && row != count)
            return true;
    }

    return false;
}

vector<minterms> findMinExpression(vector<minterms> &primeImplicants, vector<int> &onSet, bool changeHappened, vector<minterms> &output, bool firstEnter)
{
    if(changeHappened == false)
    {
        cout << "m";
        return output;
    }

    vector<minterms> temp;
    temp.clear();
    temp = findEPIs(primeImplicants, onSet);

    if(firstEnter)
    {
        mintermsNotCovered(temp, onSet);
        firstEnter = false;
    }

    if(temp.size() > 0)
    {
        for(auto it = temp.begin();  it != temp.end(); it++)
        {
            output.push_back(*it);

            for(auto it2 = it->decimals.begin(); it2 != it->decimals.end(); it2++)
            {
                for(auto it3 = onSet.begin(); it3 != onSet.end(); it3++)
                {
                    if(*it3 == *it2)
                    {
                        onSet.erase(it3);
                        //cout << *it3 << " ";
                    }
                }
            }

            for(auto it2  = primeImplicants.begin(); it2 != primeImplicants.end(); it2++)
            {
                if(it2->binRep == it->binRep)
                {
                    primeImplicants.erase(it2);
                }
            }
            
            // for(auto it2  = onSet.begin(); it2 != onSet.end(); it2++)
            // {
            //     cout << (*it2) << " ";
            // }
            //     cout << endl;

            findMinExpression(primeImplicants, onSet, true, output, firstEnter);
        }

    } 
    else if (temp.size() == 0){
        bool changed = false;

        auto it = primeImplicants.begin();
        for(int i = 0; i < primeImplicants.size(); i++)
        {
            if(isDominatedRow(primeImplicants, onSet, i))
            {
                primeImplicants.erase(it);
                changed = true;
            }
            it++;
        }

        auto it2 = onSet.begin();
        for(int i = 0; i < onSet.size(); i++)
        {
            if(isDominatingColumn(primeImplicants, onSet, i))
            {
                onSet.erase(it2);
                changed = true;
            }
            it2++;
        }

        if(changed)
        {
            findMinExpression(primeImplicants, onSet, true, output, firstEnter);
        }
        else
        {
            findMinExpression(primeImplicants,onSet, false, output, firstEnter);
        }

    }

}

int main()
{
    vector<minterms> primeImplicants;
    minterms m1;
    m1.decimals.insert(4);
    m1.decimals.insert(0);
    m1.binRep = "0_00";

    minterms m2;
    m2.decimals.insert(0);
    m2.decimals.insert(8);
    m2.binRep = "_000";

    minterms m3;
    m3.decimals.insert(8);
    m3.decimals.insert(9);
    m3.binRep = "100_";

    minterms m4;
    m4.decimals.insert(8);
    m4.decimals.insert(10);
    m4.binRep = "10_0";

    minterms m5;
    m5.decimals.insert(9);
    m5.decimals.insert(13);
    m5.binRep = "1_01";

    minterms m6;
    m6.decimals.insert(4);
    m6.decimals.insert(5);
    m6.decimals.insert(6);
    m6.decimals.insert(7);
    m6.binRep = "01__";

    minterms m7;
    m7.decimals.insert(5);
    m7.decimals.insert(7);
    m7.decimals.insert(13);
    m7.decimals.insert(15);
    m7.binRep = "_1_1";

    primeImplicants.push_back(m1);
    primeImplicants.push_back(m2);
    primeImplicants.push_back(m3);
    primeImplicants.push_back(m4);
    primeImplicants.push_back(m5);
    primeImplicants.push_back(m6);
    primeImplicants.push_back(m7);

    vector<int> onset;
    onset.push_back(4);
    onset.push_back(5);
    onset.push_back(6);
    onset.push_back(8);
    onset.push_back(9);
    onset.push_back(10);
    onset.push_back(13);

    vector<minterms> epi;
    vector<minterms> out;
    epi = findMinExpression(primeImplicants, onset, true, out, true);

    for(auto it = epi.begin(); it != epi.end(); it++)
    {
        booleanRep(*it);
    }

    cout << endl;

}
