#include "Stack.h"

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
    Stack stackObj;
    std::string prefixFormula = prefixOrder(T, ss);
    std::cout << "Prefix Formula: " << prefixFormula << '\n';
    for (int i = prefixFormula.length(); i > -1; --i)
    {
        if (isOperator(prefixFormula[i]))
        {
            std::string temp;
            std::string op1 = stackObj.peek();   
            stackObj.pop();
            std::string op2 = stackObj.peek();   
            stackObj.pop();
            if (op1[0] == derivativeVar || op2[0] == derivativeVar)
            {
                switch (prefixFormula[i])
                {
                    case '+':
                    {
                        temp = "1";
                        break;
                    }
                    case '-':
                    {
                        temp = "1";
                        break;
                    }
                    case '*':
                    {
                        if (op1[0] == derivativeVar)
                            temp = op2;
                        else temp = op1;
                        break;
                    }
                    case '^':
                    {   if (op1[0] == derivativeVar)
                            temp = "(" + op2 + "*" + "(" + derivativeVar + "^" + std::to_string(std::stoi(op2) - 1) + ")" + ")";
                        else
                            temp = "(" + op1 + "*" + "(" + derivativeVar + "^" + std::to_string(std::stoi(op1) - 1) + ")" + ")";
                        break;
                    }

                }
            }
            else
                temp = "(" + op1 + prefixFormula[i] + op2 + ")";
            stackObj.push(temp);
        }
        else
        {
            stackObj.push(std::string(1,prefixFormula[i]));
        }
    }
    std::string infixFormula = stackObj.peek();
    if (infixFormula.length())
    {
        result = true;
        std::cout << "Infix Formula: " << infixFormula << '\n';
        Tree T1 = Build_Formula(infixFormula, 0);
        std::cout << "Tree T1 successfully created!\n";
    }
    else
        std::cout << "Tree T1 was not created...\n";

    return result;
}

int main()
{

    std::ifstream file("formula.txt");
    Tree T = Build_Formula(file);
    Tree T1;
    /*std:: cout << T->info;*/

    if (task1(T, T1, 'x'))
        print_to_string(T1);

    /* Stack pt(3);

    pt.push(1);
    pt.push(2);

    pt.pop();
    pt.pop();

    pt.push(3);

    std::cout << "The top element is " << pt.peek() << std::endl;
    std::cout << "The stack size is " << pt.size() << std::endl;

    pt.pop();

    if (pt.isEmpty()) {
        std::cout << "The stack is empty\n";
    }
    else {
        std::cout << "The stack is not empty\n";
    }*/
}
