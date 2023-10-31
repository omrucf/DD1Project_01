#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
// #include "QM.cpp"

using namespace std;
struct minterms
{
    string binRep;
    set<int> decimals;
    set<int> posOf_;
    bool isPrime = true;
};

vector<int> onSet;

vector<minterms> findEPIs(vector<minterms> primeImplicants, vector<int> onSet)
{

    vector<minterms> EPI;
    int onSetCoverageCount[onSet.size()];
    for (int i = 0; i < onSet.size(); i++)
    {
        onSetCoverageCount[i] = 0;
    }

    // update coverage count
    for (int i = 0; i < primeImplicants.size(); i++)
    {
        for (int j = 0; j < onSet.size(); j++)
        {
            if (primeImplicants[i].decimals.find(onSet[j]) != primeImplicants[i].decimals.end())
            {
                onSetCoverageCount[j]++;
            }
        }
    }

    for (int it = 0; it < onSet.size(); it++)
    {
        if (onSetCoverageCount[it] == 1)
        {
            for (int i = 0; i < primeImplicants.size(); i++)
            {
                if (primeImplicants[i].decimals.find(onSet[it]) != primeImplicants[i].decimals.end())
                    EPI.push_back(primeImplicants[i]);
            }
        }
    }

    // for(int i = 0; i < EPI.size(); i++)
    //     cout << EPI[i].binRep << " ";

    return EPI;
}

bool booleanRep(minterms input)
{
    for (int i = 0; i < input.binRep.size(); i++)
    {
        if (input.binRep[i] == '1')
        {
            cout << char(i + 65);
        }
        else if (input.binRep[i] == '0')
        {
            string temp;
            // temp += '(';
            temp += char(33);
            temp += char(i + 65);
            // temp += ')';
            cout << temp;
        }
        else if (input.binRep[i] == '_')
        {
            continue;
        }
    }

    cout << "   ";
    return true;
}

bool mintermsNotCovered(vector<minterms> epi, vector<int> onSet)
{
    set<int> mintermsCovered;
    for (auto it = epi.begin(); it != epi.end(); it++)
    {
        set<int> temp = it->decimals;
        for (auto it2 = temp.begin(); it2 != temp.end(); it2++)
        {
            int minterm = *it2;
            mintermsCovered.insert(minterm);
        }
    }

    for (int i = 0; i < onSet.size(); i++)
    {
        if (mintermsCovered.find(onSet[i]) == mintermsCovered.end())
        {
            cout << onSet[i] << "   ";
        }
    }

    cout << endl;
    return true;
}

// bool isDominatingColumn(vector<minterms> primeImplicants, vector<int> onSet, int column)
// {
//     vector<set<int>> columns;
//     for(int i = 0; i < primeImplicants.size(); i++)
//     {
//         for(auto it = primeImplicants[i].decimals.begin(); it != primeImplicants[i].decimals.end(); it++)
//             columns[*it].insert(i);
//     }

//     int count = -1;
//     for(auto it = columns.begin(); it != columns.end(); it++)
//     {
//         count ++;
//         if(includes(columns[column].begin(), columns[column].end(),it->begin(), it->end()) && column != count)
//             return true;
//     }

//     return false;
// }

// bool isDominatedRow(vector<minterms> primeImplicants, vector<int> onSet, int row)
// {
//     int count = -1;
//     for(auto it = primeImplicants.begin(); it != primeImplicants.end(); it++)
//     {
//         count ++;
//         if(includes(it->decimals.begin(), it->decimals.end(), primeImplicants[row].decimals.begin(), primeImplicants[row].decimals.end()) && row != count)
//             return true;
//     }

//     return false;
// }

vector<minterms> findMinExpression(vector<minterms> &primeImplicants, vector<int> &onSet, bool &changeHappened, vector<minterms> output, bool firstEnter)
{
    if (changeHappened == false)
    {
        cout << "o";
        // cout << output.size();
        return output;
    }

    vector<minterms> temp;

    temp = findEPIs(primeImplicants, onSet);
    // cout << "t" << temp.size() << " ";

    if (firstEnter)
    {
        mintermsNotCovered(temp, onSet);
        firstEnter = false;
    }
    cout << "m";
    if (temp.size() > 0)
    {
        // cout << onSet.size();

        bool change = false;
        for (auto it = temp.begin(); it != temp.end(); it++)
        {

            output.push_back(*it);
            vector<int> toRemove;

            for (auto it2 = it->decimals.begin(); it2 != it->decimals.end(); it2++)
            {
                for (auto it3 = onSet.begin(); it3 != onSet.end(); it3++)
                {
                    if (*it3 == *it2)
                    {
                        toRemove.push_back(*it3);
                        onSet.erase(it3);
                        change = true;
                        it3--;
                    }
                }
            }

            if (onSet.size() == 0)
            {
                for (auto it = output.begin(); it != output.end(); it++)
                {
                    booleanRep(*it);
                }

                return output;
            }

            for (auto it2 = primeImplicants.begin(); it2 != primeImplicants.end(); it2++)
            {
                if (it2->binRep == it->binRep)
                {
                    primeImplicants.erase(it2);
                    change = true;
                    it2--;
                }

                for (int i = 0; i < toRemove.size(); i++)
                {
                    if (it2->decimals.find(toRemove[i]) != it2->decimals.end())
                    {
                        it2->decimals.erase(toRemove[i]);
                        it2--;
                    }
                }
            }

            auto i = primeImplicants.begin();
            while (i != primeImplicants.end())
            {
                if (i->decimals.size() == 0)
                {
                    i = primeImplicants.erase(i);
                    i--;
                }
                else
                    i++;
            }
        }

        if (onSet.size() < 2)
        {
            cout << "y";
            return output;
        }

        findMinExpression(primeImplicants, onSet, change, output, firstEnter);
    }
    else if (temp.size() == 0)
    {

        bool changed = false;
        vector<minterms> rm;
        for (auto it2 = primeImplicants.begin(); it2 != primeImplicants.end(); it2++)
        {
            for (auto it = primeImplicants.begin(); it != primeImplicants.end(); it++)
            {
                if (includes(it2->decimals.begin(), it2->decimals.end(), it->decimals.begin(), it->decimals.end()) && (it2 != it))
                {
                    rm.push_back(*it);
                    changed = true;
                }
            }
        }

        vector<minterms>::iterator it = primeImplicants.begin();
        for (int i = 0; i < rm.size(); i++)
        {
            while (it != primeImplicants.end())
            {
                if (it->binRep == rm[i].binRep)
                {
                    it = primeImplicants.erase(it);
                    it--;
                }
                else
                {
                    ++it;
                }
            }
        }

        if (changed)
        {
            // cout << "x";
            findMinExpression(primeImplicants, onSet, changed, output, firstEnter);
        }

        map<int, set<string>> c;

        for (auto it2 = primeImplicants.begin(); it2 != primeImplicants.end(); it2++)
        {
            for (auto it = it2->decimals.begin(); it != it2->decimals.end(); it++)
            {
                if (c.find(*it) == c.end())
                {

                    set<string> *temp = new set<string>;
                    temp->insert(it2->binRep);
                    c.insert(pair<int, set<string>>(*it, *temp));
                }
                else
                {
                    c[*it].insert(it2->binRep);
                }
            }
        }

        for (auto x = c.begin(); x != c.end(); x++)
        {
            for (auto y = c.begin(); y != c.end(); y++)
            {
                if (includes(x->second.begin(), x->second.end(), y->second.begin(), y->second.end()) && (x->first != y->first))
                {
                    changed = true;
                    for (auto i = onSet.begin(); i < onSet.end(); i++)
                    {
                        if (*i == x->first)
                        {
                            onSet.erase(i);
                            i--;
                        }
                    }
                }
            }
        }

        // or all of them if all are needed

        // for(auto it = c.begin(); it != c.end(); it++)
        // {
        //     delete &(it->second);
        // }

        if (onSet.size() == 1 || primeImplicants.size() == 0)
        {
            output.push_back(primeImplicants[0]);
            return output;
        }
        // for(auto i = primeImplicants.begin(); i != primeImplicants.end(); i++)
        //     {
        //         for(auto it = i->decimals.begin(); it != i->decimals.end(); it++)
        //         {
        //             cout << *it << " ";
        //         }
        //         cout << endl;
        //     }

        // if 1 then return append it to output and return
        findMinExpression(primeImplicants, onSet, changed, output, firstEnter);
    }

    return output;
}

vector<int> setOnset(vector<minterms> PI)
{
    for (minterms minterm : PI)
    {
        for (auto it = minterm.decimals.begin(); it != minterm.decimals.end(); it++)
        {
            onSet.push_back(*it);
        }
    }

    vector<int> result;
    // store all onSet values in a vector
    for (int i = 0; i < onSet.size(); i++)
    {
        result.push_back(onSet[i]);
    }

    return result;
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

    // for(auto it = primeImplicants.begin(); it != primeImplicants.end(); it++)
    // {
    //     for(auto it2 = it->decimals.begin(); it2 != it->decimals.end(); it2++)
    //     {
    //         if(find(onset.begin(), onset.end(), *it2) == onset.end())
    //         {
    // cout << "-------------------" << endl;
    //             set<int>::iterator it3 = find(it->decimals.begin(), it->decimals.end(), *it2);
    //             it->decimals.erase(it3);
    //         }
    //     }
    // }

    vector<minterms> epi;
    vector<minterms> out;
    bool c = true;
    findMinExpression(primeImplicants, onset, c, out, true);

    for (auto it = out.begin(); it != out.end(); it++)
    {
        cout << it->binRep;
        booleanRep(*it);
    }

    cout << endl;
}
