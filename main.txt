#include "epis.cpp"
#include "Question1.cpp"

// int main(int argc, char *argv[])
// {
//         string BooleanExpressionInput = "";
//         vector<minterms> PI;

//         cout << "NOTE : AND = *, OR = +, NOT = !" << endl;
//         cout << "NOTE : Include ( ) When Negating" << endl;
//         cout << "Enter a Boolean Expression : ";
//         getline(cin, BooleanExpressionInput);

//         if (BooleanExpressionInput.empty()) {

//             cout << "ERROR : No Boolean Expression Entered!" << endl;
//         }
//         else if (isValidBooleanExpression(BooleanExpressionInput) && containsOperator(BooleanExpressionInput)) {
//             cout << "---------------------------------------" << endl;
//             removeDoubleNegations(BooleanExpressionInput);
//             map<char, string> stringCharPairs = MakePairs(BooleanExpressionInput);
//             evaluateExpression(BooleanExpressionInput, stringCharPairs);
//             string SOP = canonicalSOP(stringCharPairs);
//             string POS = canonicalPOS(stringCharPairs);
//             for (auto& x : stringCharPairs) {
//                 cout << x.first << "\t";
//             }

//             // Print table rows
//             int numRows = stringCharPairs.begin()->second.length();
//             for (int i = numRows; i >= 0; i--) {
//                 for (auto& x : stringCharPairs) {
//                     cout << x.second[i] << "\t";
//                 }

//                 cout << endl;
//             }
//             cout << "---------------------------------------" << endl;
//             cout << "Canonical SOP : " << SOP << endl;
//             cout << "Canonical POS : " << POS << endl;
//             cout << "---------------------------------------" << endl;

//             vector<string> mntrms = toBinary(SOP);
//             PI = PIGenerator(mntrms);



//             // KarnaughMap(stringCharPairs, BooleanExpressionInput);

//         }
//         else {

//             cout << "ERROR : Invalid Boolean Expression!" << endl;
//         }

//     vector<int> onset = setOnset(PI);
//     for(auto it = PI.begin(); it != PI.end(); it++)
//     {
//         for(auto it2 = it->decimals.begin(); it2 != it->decimals.end(); it2++)
//         {
//             if(find(onset.begin(), onset.end(), *it2) == onset.end())
//             {
//                 set<int>::iterator it3 = find(it->decimals.begin(), it->decimals.end(), *it2);
//                 it->decimals.erase(it3);
//             }
//         }
//     }
    
//     bool c = true;
//     vector<minterms> epi;
//     vector<minterms> out;
//     findMinExpression(PI, onset, c, out, true);

//     return 0;
// }