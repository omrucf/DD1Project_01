#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include<algorithm>
#include<map>

using namespace std;
//extracts all the varibles from a boolean expression
vector<char> extractVaribles(string expression) {

    vector<char> temp;

    for (char c : expression) {
        // Check if the character is an alphabet character
        if (isalpha(c)) { 
            temp.push_back(c);
        }
        
    }
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    return temp;
}
//Genrates all possible combinations in a truth table
void generateCombinations(int numVariables, vector<vector<int>>& truthTable, vector<int> currentRow) {
    if (numVariables == 0) {
        truthTable.push_back(currentRow);
        return;
    }

    // Generate all possible combinations for the current variable (1 and 0)
    currentRow.push_back(1);
    generateCombinations(numVariables - 1, truthTable, currentRow);
    currentRow.pop_back();
    currentRow.push_back(0);
    generateCombinations(numVariables - 1, truthTable, currentRow);
    currentRow.pop_back();
}

map<char, string> MakePairs (string expression) {
    map<char, string> variableBinary;
  

    vector<char> varibles = extractVaribles(expression);
    vector<vector<int>> truthTable;
    vector<int> currentRow;

    generateCombinations(varibles.size(), truthTable, currentRow);
    int numCombinations = pow(2, varibles.size());
   
        string bitString = "";
        for (int i = 0; i < varibles.size(); ++i) {
            for (auto& row : truthTable) {
                bitString += to_string(row[i]);
            }

            variableBinary.insert(make_pair(varibles[i], bitString));
            bitString = "";
        }

        return variableBinary;

}
//AND
string bitwiseAND( string str1, string str2) {
    string result;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] == '1' && str2[i] == '1') {
            result += '1';
        }
        else {
            result += '0';
        }
    }
    return result;
}
//OR
string bitwiseOR(string str1, string str2) {
   string result;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] == '1' || str2[i] == '1') {
            result += '1';
        }
        else {
            result += '0';
        }
    }
    return result;
}
string bitwiseNOT(string& operand) {
    string result = "";

    for (char bit : operand) {
        if (bit == '0') {
            result += '1';  
        }
        else if (bit == '1') {
            result += '0';
        }
        else {
            result += bit;
        }
    }

    return result;
}
// Function to evaluate a boolean expression 
void evaluateExpression(string expression,  map<char,string>& variableMap) {
    vector<string> operandStack;
    vector<char> operatorStack;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == '(') {
            operatorStack.push_back(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!operatorStack.empty() && operatorStack.back() != '(') {
                char op = operatorStack.back();
                operatorStack.pop_back();

                if (op == '*') {
                    string op2 = operandStack.back();
                    operandStack.pop_back();
                    string op1 = operandStack.back();
                    operandStack.pop_back();
                    operandStack.push_back(bitwiseAND(op1, op2));
                }
                else if (op == '+') {
                    string op2 = operandStack.back();
                    operandStack.pop_back();
                    string op1 = operandStack.back();
                    operandStack.pop_back();
                    operandStack.push_back(bitwiseOR(op1, op2));
                }
            }
            operatorStack.pop_back(); // Pop the '('
        }
        else if (expression[i] == '!') {
            // Handle NOT operation
            if (i + 1 < expression.length() && isalpha(expression[i + 1])) {
                string op1 = variableMap.at(expression[i + 1]);
                operandStack.push_back(bitwiseNOT(op1));
                i++; // Skip the variable
            }
        }
        else if (isalpha(expression[i]) || islower(expression[i])) {
            if (variableMap.find(expression[i]) != variableMap.end()) {
                operandStack.push_back(variableMap.at(expression[i]));
            }
        }
        else if (expression[i] == '*' || expression[i] == '+') {
            operatorStack.push_back(expression[i]);
        }
    }

    while (!operatorStack.empty()) {
        char op = operatorStack.back();
        operatorStack.pop_back();

        if (op == '*') {
            string op2 = operandStack.back();
            operandStack.pop_back();
            string op1 = operandStack.back();
            operandStack.pop_back();
            operandStack.push_back(bitwiseAND(op1, op2));
        }
        else if (op == '+') {
            string op2 = operandStack.back();
            operandStack.pop_back();
            string op1 = operandStack.back();
            operandStack.pop_back();
            operandStack.push_back(bitwiseOR(op1, op2));
        }
    }

    variableMap.insert(make_pair('F', operandStack.back()));
    
}
string canonicalPOS(map<char, string> variableMap) {
    vector<int> indices;
    string temp = "";
    string result = "";
    char bit;

    // Find the indices where '0' is present in the 'F' variable.
    for (auto& x : variableMap) {
        if (x.first == 'F') {
            temp = x.second;
        }
    }

    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '0') {
            indices.push_back(i);
        }
    }

    for (int i = 0; i < indices.size(); i++) {
        result.append("(");

        for (auto& x : variableMap) {
            
            if (x.first != 'F') {
                bit = x.second.at(indices[i]);
                if (bit != '1') {
                   
                    result.append("!");
                    result += x.first;
                   
                    result.append("+");
                   
                    continue;
                }
                else {
                   
                    result += x.first;
                    result.append("+");
                    continue;
                }
            }
        }
        result.pop_back();
        if (i < indices.size() - 1) {
            result.append(")");
            result += '*';
        }

    }
    result.append(")");
    return result;
}
string canonicalSOP(map<char, string> variableMap) {
    vector<int> indices;
    string temp = "";
    string result = "";
    char bit;

    // Find the indices where '1' is present in the 'F' variable.
    for (auto& x : variableMap) {
        if (x.first == 'F') {
            temp = x.second;
        }
    }

    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '1') {
            indices.push_back(i);
        }
    }

    for (int i = 0; i < indices.size(); i++) {
    
    
        for (auto& x : variableMap) {
            if (x.first != 'F') {
                bit = x.second.at(indices[i]);
                if (bit != '1') {
                    char c = x.first;
                    result.append("!");
                    result += x.first;
                    continue;
                }
                else {

                    result += x.first;
                    continue;
                }
            }
        }
        if (i < indices.size() - 1) {
            result += '+';
        }
    
    }
    return result;
}
string removeDoubleNegations(string& expression) {
    string temp;
    bool insideNegation = false;
    for (char c : expression) {
        if (c == '!') {
            insideNegation = !insideNegation;
        }
        else {
            if (insideNegation) {
                if (c != '!') {
                    temp += '!';
                }
                insideNegation = false;
            }
            temp += c;
        }
    }
    return temp;
}
//Utility Function For Validating Boolean Expression By checking if the input is from A-Z.
bool isValidVariable(char c) {
    return (isalpha(c) && islower(c)) || (isalpha(c) && isupper(c));
}
//Validates Boolean Expression.
bool isValidBooleanExpression(string expression) {
    stack<char> parenthesesStack;

    for (char c : expression) {
        if (c == '(') {
            parenthesesStack.push(c);
        }
        else if (c == ')') {
            if (parenthesesStack.empty() || parenthesesStack.top() != '(') {
                return false; 
            }
            parenthesesStack.pop();
        }
        else if (isValidVariable(c) || c == '!' || c == '+' || c == '*') {
            continue; 
        }
        else {
            return false;
        }
    }
    return parenthesesStack.empty();
}
int main() {
	string BooleanExpressionInput = "";
	
    cout << "NOTE : AND = *, OR = +, NOT = !" << endl;
    cout << "NOTE : Include ( ) When Negating" << endl;
	cout << "Enter a Boolean Expression : ";
	getline(cin, BooleanExpressionInput);
    BooleanExpressionInput =  removeDoubleNegations(BooleanExpressionInput);

    
    if (isValidBooleanExpression(BooleanExpressionInput)) {
        cout << "---------------------------------------" << endl;

        map<char, string> stringCharPairs = MakePairs(BooleanExpressionInput);
        evaluateExpression(BooleanExpressionInput, stringCharPairs);
        string SOP = canonicalSOP(stringCharPairs);
        string POS = canonicalPOS(stringCharPairs);
        for (auto& x : stringCharPairs) {
            cout << x.first << "\t";
        }

        // Print table rows
        int numRows = stringCharPairs.begin()->second.length();
        for (int i = numRows; i >= 0; i--) {
            for (auto& x : stringCharPairs) {
                cout << x.second[i] << "\t";
            }

            cout << endl;
        }
        cout << "---------------------------------------" << endl;
        cout << "Canonical SOP : " << SOP;
        cout << endl;
        cout << "Canonical POS : " << POS;
        
       
    }
    else {
    
        cout << "ERROR : Invalid Boolean Expression!" << endl;
    }
   


}


