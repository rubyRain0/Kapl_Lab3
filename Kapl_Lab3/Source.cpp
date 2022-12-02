#include "FormulaTree.h"

bool isOperator(char x) {
    switch (x) {
    case '+':
    case '-':
    case '*':
    case '^':
        return true;
    }
    return false;
}

std::string prefixOrder(const Tree& node, std::stringstream& ss)
{
    if (node != 0)
    {
        ss << node->info;

        prefixOrder(node->left, ss);
        prefixOrder(node->right, ss);
    }
    return ss.str();
}

bool task1(const Tree& T,Tree& T1, char derivativeVar)
{   
    bool result = false;
    std::stringstream ss; 
    Stack<std::string> stackObj;
    std::string prefixFormula = prefixOrder(T, ss);
    std::cout << "Prefix Formula: " << prefixFormula << '\n';
    bool emptyDerivative = true;
    std::string derivative;
    int coeffCounter = 0;
    for (int i = prefixFormula.length(); i > -1; --i)
    {
        if (isOperator(prefixFormula[i]))
        {   
            bool containsVar1 = false;
            bool containsVar2 = false;
            int varIndex1, varIndex2;
            std::string op1 = stackObj.peek();
            stackObj.pop();
            std::string op2 = stackObj.peek();
            stackObj.pop();
            for (size_t i = 0; i < op1.length(); i++)
            {
                if (op1[i] == derivativeVar)
                {
                    containsVar1 = true;
                    varIndex1 = i;
                }
            }
            for (size_t i = 0; i < op2.length(); i++)
            {
                if (op2[i] == derivativeVar)
                {
                    containsVar2 = true;
                    varIndex2 = i;
                }
            }
            if (op1[0] == derivativeVar || op2[0] == derivativeVar ||
                containsVar1 || containsVar2)
            {
                emptyDerivative = false;
                switch (prefixFormula[i])
                {
                    case '+':
                    case '-':
                    {
                        if (containsVar1 && !containsVar2)
                        {
                            std::cout << "1: " << op1 << "\n2: " << op2 << '\n';
                            if (op1[varIndex1+1])
                            {
                                derivative = op1;
                                break;
                            }
                            else
                            {   
                                derivative = "1";
                                coeffCounter++;
                                break;
                            }
                        }
                        else if (containsVar2 && !containsVar1)
                        {
                            std::cout << "1: " << op1 << "\n2: " << op2 << '\n';
                            if (op2[varIndex2+1])
                            {
                                derivative = op2;
                                break;
                            }
                            else
                            {
                                derivative = "1";
                                coeffCounter++;
                                break;
                            }
                        }
                    }
                    case '*':
                    {
                        if (containsVar1 && !containsVar2)
                        {
                            std::cout << "1: " << op1 << "\n2: " << op2 << '\n';
                            if (op1[varIndex1 + 1])
                            {
                                derivative = "(" + op1 + prefixFormula[i] + op2 + ")";
                                break;
                            }
                            else
                            {
                                derivative = op2;
                                break;
                            }
                        }
                        else if (containsVar2 && !containsVar1)
                        {
                            std::cout << "1: " << op1 << "\n2: " << op2 << '\n';
                            if (op2[varIndex2 + 1])
                            {
                                derivative = "(" + op1 + prefixFormula[i] + op2 + ")";
                                break;
                            }
                            else
                            {
                                derivative = op1;
                                break;
                            }
                        }
                        break;
                    }
                    case '^':
                    {   
                        derivative = "(" + op2 + "*" + "(" + derivativeVar + 
                            "^" + std::to_string(std::stoi(op2) - 1) + ")" + ")";
                        break;
                    }

                }
            }  
            stackObj.push(derivative);
        }
        else
        {
            stackObj.push(std::string(1,prefixFormula[i]));
        }
    }
    std::string infixFormula;
    if (!emptyDerivative)
    {
        if (coeffCounter == 0)
            infixFormula = derivative;
        else
            infixFormula = "(" + derivative + "+" + std::to_string(coeffCounter) + ")";
    }
        
    else infixFormula = "0";

    if (infixFormula != "0")
    {
        result = true;
        std::cout << "Infix Formula (Derivative) : " << infixFormula << '\n';
        std::ofstream outputFile("resultFormula.txt");
        outputFile << infixFormula;
        outputFile.close();
        std::ifstream inputFile("resultFormula.txt");
        T1 = Build_Formula(inputFile);
    }
    else
    {
        result = false;
        std::cout << "Infix Formula (Derivative) : " << infixFormula << '\n';
        T1 = new NODE('0');
    }

    return result;
}

int main()
{

    std::ifstream file("formula.txt");
    Tree T = Build_Formula(file);
    Tree T1;

    if (task1(T, T1, 'x'))
    {
        std::cout << "Tree T1 successfully created!\n";
        std::stringstream ss;
        std::cout << treeFormulaToString(T1, ss);
    }
    else
        std::cout << "Derivative equals 0...\n";

    std::cin.get();
}
