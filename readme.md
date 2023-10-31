# Quine-McCluskey Algorithm for Boolean Function Manipulation

## Overview

This C++ program is designed to facilitate the manipulation and analysis of boolean functions using the Quine-McCluskey algorithm. It provides several key features, including:

- Conversion of boolean function to Canonical Sum of Products (SOP) and Product of Sums (POS) forms.
- Generation of a truth table for the given boolean function.
- Construction of Karnaugh Maps (K-Maps) for visualization and simplification.
- Minimization of the boolean function using the Quine-McCluskey algorithm.
- Identification of prime implicants.
- Visualization of the logic circuit for the minimized function.

## Prerequisites

Before using this C++ program, ensure you have the following prerequisites:

- A C++ compiler and development environment (e.g., GCC, Visual Studio).
- Any required libraries or modules mentioned in the program documentation.

## Usage

1. **Input**: The program takes a boolean function as input. You can input the function in various forms, such as a truth table, a boolean expression, or a list of minterms/maxterms.

2. **Canonical Forms**:
   - To obtain the Canonical Sum of Products (SOP) form, run the program with the appropriate command.
   - To obtain the Canonical Product of Sums (POS) form, use the corresponding command.

3. **Truth Table**:
   - Generate a truth table for the given boolean function using the provided command.

4. **K-Map**:
   - Create Karnaugh Maps to visualize the function. Specify the number of variables and other required parameters.

5. **Minimization**:
   - Utilize the Quine-McCluskey algorithm to minimize the boolean function. The minimized function will be displayed.

6. **Prime Implicants**:
   - Identify prime implicants in the minimized function. The program will list these for you.

7. **Logic Circuit**:
   - Visualize the logic circuit for the minimized function. This can help in practical circuit design.

## Example Usage

```shell
# To convert a boolean expression to SOP form
./quine_mccluskey -input "A'BC + AB'C + ABC'" -sop

# To generate a truth table for a boolean expression
./quine_mccluskey -input "A'B + AB'C + ABC'" -truth-table

# To create a K-Map for a 4-variable function
./quine_mccluskey -input "A'BCD + AB'CD + ABC'D + ABCD'" -k-map -variables 4
