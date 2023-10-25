#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct minterms
{
    string binRep;
    set<int> decimals;
    set<int> posOf_;
};

// Function to perform Quine McCluskey method and find the essential prime implicants
set<int> findEssentialPrimeImplicants(vector<minterms> primeImplicants, const vector<int>& onset) {
    set<int> essentialImplicants;  // Set to store the indices of essential prime implicants

    // Step 1: Initialize the coverage count for each minterm
    vector<int> coverageCount(onset.size(), 0);

    // Step 2: Count the number of times each minterm is covered by the prime implicants
    for (int i = 0; i < primeImplicants.size(); i++) {
        for (int j = 0; j < onset.size(); j++) {
            if (primeImplicants[j].decimals.find(onset[i]) != primeImplicants[j].decimals.end())
                coverageCount[j]++;
        }
    }

    // Step 3: Check for essential prime implicants
    for (int j = 0; j < onset.size(); j++) {
        if (coverageCount[j] == 1) {
            // Find the index of the prime implicant covering the minterm
            for (int i = 0; i < primeImplicants.size(); i++) {
                if (primeImplicants[i].decimals.find(onset[j]) != primeImplicants[j].decimals.end()) {
                    essentialImplicants.insert(i);
                    break;
                }
            }
        }
    }

    // Step 4: Remove covered onset and prime implicants
    for (auto it = essentialImplicants.begin(); it != essentialImplicants.end(); ++it) {
        for (int j = 0; j < onset.size(); j++) {
            primeImplicants.erase(primeImplicants.begin() + *it);
            // if (primeImplicants[*it] == '1' && coverageCount[j] > 0) {
            //     // Reduce the coverage count for covered onset
            //     coverageCount[j]--;
            // }
        }
    }

    // Step 5: Remove redundant prime implicants
    bool implicantsRemoved;
    do {
        implicantsRemoved = false;
        for (size_t i = 0; i < primeImplicants.size(); i++) {
            if (essentialImplicants.count(i) == 0) {
                for (size_t j = 0; j < onset.size(); j++) {
                    if (primeImplicants[i][j] == '1' && coverageCount[j] == 1) {
                        // Remove the prime implicant if it covers a minterm with coverage count 1
                        essentialImplicants.insert(i);
                        implicantsRemoved = true;

                        // Reduce the coverage count for covered onset
                        for (size_t k = 0; k < onset.size(); k++) {
                            if (primeImplicants[i][k] == '1' && coverageCount[k] > 0) {
                                coverageCount[k]--;
                            }
                        }
                        break;
                    }
                }
            }
        }
    } while (implicantsRemoved);

    return essentialImplicants;
}

int main() {
    // Example usage
    vector<minterms> primeImplicants;// = {"1001", "0101", "0110", "1100"};
    vector<int> onset = {1, 3, 5, 6, 7};

    set<int> essentialImplicants = findEssentialPrimeImplicants(primeImplicants, onset);

    cout << "Essential Prime Implicants: ";
    for (int implicant : essentialImplicants) {
        cout << implicant << " ";
    }
    cout << endl;

    return 0;
}