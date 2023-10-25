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
};

vector<string> splitString(const string &str, char mark)
{
    vector<string> result;
    string word;
    for (char c : str)
    {
        if (c == mark)
        {
            result.push_back(word);
            word.clear();
        }
        else
        {
            word += c;
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
    for (string minterm : minterms)
    {
        for (int i = 0; i < minterm.length(); i++)
        {
            if (minterm[i + 1] == '\'')
            {
                temp += '0';
                i++;
            }
            else
            {
                temp += '1';
            }
        }
        cout << temp << endl;
        result.push_back(temp);
        temp.clear();
    }
    return result;
}

vector<vector<minterms>> firstStage(vector<string> mntrms)
{
    int sizeOfBits = mntrms[0].length();
    vector<vector<minterms>> result(sizeOfBits, vector<minterms>());
    minterms temp;
    int group = 0;

    cout << "size: " << mntrms.size() << endl;

    for (string minterm : mntrms)
    {
        for (char c : minterm)
        {
            if (c == '1')
            {
                group++;
            }
        }
        temp.binRep = minterm;
        temp.decimals.insert(stoi(binToDec(minterm)));
        temp.posOf_.insert(-1);
        result[group].push_back(temp);
        group = 0;
    }

    for (int i = 0; i < result.size(); i++)
    {
        if (result[i].size() == 0)
        {
            result.erase(result.begin() + i);
        }
    }
    return result;
}

vector<vector<minterms>> IthStage(vector<vector<minterms>> prevStage)
{
    vector<vector<minterms>> result(prevStage.size());
    vector<minterms> temp;

}

vector<minterms> IPGenerator(vector<string> mntrms)
{
    vector<minterms> IP;

    vector<vector<minterms>> stageI = firstStage(mntrms);




    return IP;
}

int main()
{

    return 0;
}