#include <iostream>
#include <string>
#include <stdlib.h>
#include <set>
#include <vector>
#include <cmath>

using namespace std;

struct minterms
{
    string binRep;
    set<int> decimals;
    set<int> posOf_;
    bool isPrime = true;
};

string XOR(string a, string b)
{
    if (a.length() != b.length())
    {

        exit(1);
    }
    string result = "";
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == b[i])
        {
            result += '0';
        }
        else
        {
            result += '1';
        }
    }
    return result;
}

vector<string> splitString(const string &str, char mark)
{
    vector<string> result;
    string word;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == mark)
        {
            result.push_back(word);
            word.clear();
        }
        else
        {
            word += str[i];
        }
    }
    result.push_back(word);
    return result;
}

string binToDec(string bin)
{
    string result = "";
    int temp = 0;
    for (int i = 0; i < bin.length(); i++)
    {
        if (bin[i] == '1')
        {
            temp += pow(2, bin.length() - i - 1);
        }
    }
    result = to_string(temp);
    return result;
}

vector<string> toBinary(string SOP)
{
    vector<string> minterms = splitString(SOP, '+');
    vector<string> result;
    string temp = "";
    for (int i = 0; i < minterms.size(); i++)
    {
        for (int j = 0; j < minterms[i].length(); j++)
        {
            if (minterms[i][j] == '!')
            {
                temp += '0';
                j++;
            }
            else
            {
                temp += '1';
            }
        }
        result.push_back(temp);
        temp = "";
    }
    return result;
}

vector<vector<minterms>> firstStage(vector<string> mntrms)
{
    int sizeOfBits = mntrms[0].length();
    vector<vector<minterms>> result(sizeOfBits + 1, vector<minterms>());
    minterms temp;
    int group = 0;

    for (int i = 0; i < mntrms.size(); i++)
    {
        for (int j = 0; j < mntrms[i].length(); j++)
        {
            if (mntrms[i][j] == '1')
            {
                group++;
            }
        }
        temp.binRep = mntrms[i];
        temp.decimals = {};
        temp.decimals.erase(temp.decimals.begin(), temp.decimals.end());
        temp.decimals.insert(stoi(binToDec(mntrms[i])));
        temp.posOf_.insert(-1);
        result[group].push_back(temp);
        group = 0;
    }

    for (int i = 0; i < result.size(); i++)
    {
        if (result[i].size() == 0)
        {
            result.erase(result.begin() + i);
            i--;
        }
    }

    return result;
}

int sumOfOnes(string bin)
{
    int result = 0;
    for (int i = 0; i < bin.length(); i++)
    {
        if (bin[i] == '1')
        {
            result++;
        }
    }
    return result;
}

vector<vector<minterms>> NthStage(vector<vector<minterms>> prevStage, vector<minterms> &PI)
{

    vector<vector<minterms>> result(prevStage.size());
    vector<minterms> temp;
    string XORBin;
    int logDist = 0;
    float sizeOfBits = prevStage[0][0].binRep.length();
    minterms tempMinterm;
    vector<vector<minterms>> stageIp1;

    for (int i = 0; i < prevStage.size(); i++)
    {
        for (int j = 0; j < prevStage[i].size(); j++)
        {
            prevStage[i][j].isPrime = true;
        }
    }

    for (int i = 0; i < prevStage.size() - 1; i++)
    {
        for (int j = 0; j < prevStage[i].size(); j++)
        {
            for (int k = 0; k < prevStage[i + 1].size(); k++)
            {
                XORBin = XOR(prevStage[i][j].binRep, prevStage[i + 1][k].binRep);
                logDist = sumOfOnes(XORBin);
                if (logDist == 1)
                {
                    prevStage[i][j].isPrime = false;
                    prevStage[i + 1][k].isPrime = false;
                    tempMinterm.binRep = prevStage[i][j].binRep;
                    tempMinterm.binRep[XORBin.find('1')] = '_';

                    tempMinterm.decimals = prevStage[i][j].decimals;
                    tempMinterm.decimals.insert(prevStage[i + 1][k].decimals.begin(), prevStage[i + 1][k].decimals.end());

                    tempMinterm.posOf_.insert(int(XORBin.find('1')));
                    tempMinterm.isPrime = true;
                    temp.push_back(tempMinterm);

                }
            }
            if (temp.size() != 0)
            {
                stageIp1.push_back(temp);
                temp.clear();
            }
        }
    }
    for (int i = 0; i < stageIp1.size(); i++)
    {
        for (int j = 0; j < stageIp1[i].size(); j++)
        {
            if (stageIp1[i][j].isPrime)
            {
                PI.push_back(stageIp1[i][j]);
            }
        }
    }

    if (stageIp1.size() != 0)
    {
        result = NthStage(stageIp1, PI);
    }
    else
    {
        for (int i = 0; i < prevStage.size(); i++)
        {
            for (int j = 0; j < prevStage[i].size(); j++)
            {
                PI.push_back(prevStage[i][j]);
            }
        }
    }

    return result;
}

vector<minterms> PIGenerator(vector<string> mntrms)
{
    vector<minterms> PI;
    string XORBin;
    int logDist = 0;
    int sizeOfBits = mntrms[0].length();
    vector<vector<minterms>> stageIp1;
    vector<minterms> temp;
    minterms tempMinterm;
    vector<vector<minterms>> stageI;
    stageI = firstStage(mntrms);


    for (int i = 0; i < stageI.size() - 1; i++)
    {
        for (int j = 0; j < stageI[i].size(); j++)
        {
            for (int k = 0; k < stageI[i + 1].size(); k++)
            {
                XORBin = XOR(stageI[i][j].binRep, stageI[i + 1][k].binRep);
                logDist = sumOfOnes(XORBin);
                if (logDist == 1)
                {
                    stageI[i][j].isPrime = false;
                    stageI[i + 1][k].isPrime = false;
                    tempMinterm.binRep = stageI[i][j].binRep;
                    tempMinterm.binRep[XORBin.find('1')] = '_';
                    tempMinterm.decimals = stageI[i][j].decimals;
                    tempMinterm.decimals.insert(stageI[i + 1][k].decimals.begin(), stageI[i + 1][k].decimals.end());
                    tempMinterm.posOf_.insert(int(XORBin.find('1')));
                    tempMinterm.isPrime = true;
                    temp.push_back(tempMinterm);
                }
            }
            if (temp.size() != 0)
            {
                stageIp1.push_back(temp);
                temp.clear();
            }
        }
    }



    for (int i = 0; i < stageI.size(); i++)
    {
        for (int j = 0; j < stageI[i].size(); j++)
        {
            if (stageI[i][j].isPrime)
            {
                PI.push_back(stageI[i][j]);

            }
        }
    }


    if (stageIp1.size() != 0)
    {
        stageI = NthStage(stageIp1, PI);

    }
    else
    {
        for(int i = 0; i < stageI.size(); i++)
        {
            for(int j = 0; j < stageI[i].size(); j++)
            {
                PI.push_back(stageI[i][j]);
            }
        }
    }

    return PI;
}

// int main(int argc, char *argv[])
// {
//     string SOP = "!A!B!C!D+!A!B!CD+A!B!C!D+A!BC!D+!AB!C!D+!ABC!D+AB!C!D+ABC!D"; // minterms: 0, 1, 8, 10, 4, 6, 12, 14
//     // string SOP = "ABCD+!A!B!C!D+!AB!CD+A!BC!D+!A!BCD+AB!C!D";
//     // string SOP = "AB!C+ABC";
//     vector<string> mntrms = toBinary(SOP);
//     vector<minterms> PI;
//     PI = PIGenerator(mntrms);

//     for (int i = 0; i < PI.size(); i++)
//     {
//         cout << PI[i].binRep << "\tdec:\t";
//         for (auto it = PI[i].decimals.begin(); it != PI[i].decimals.end(); it++)
//         {
//             cout << *it << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }