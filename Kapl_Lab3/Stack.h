#pragma once
#include "FormulaTree.h"

#define SIZE 100 // defining stack size.

using StackInfo = std::string;

class Stack
{
    StackInfo* arr;
    int top;
    int capacity;

public:
    Stack(int size = SIZE);
    ~Stack();

    void push(StackInfo);
    StackInfo pop();
    StackInfo peek();
    int size();
    bool isEmpty();
    bool isFull();
};

Stack::Stack(int size)
{
    arr = new StackInfo[size];
    capacity = size;
    top = -1;
}

Stack::~Stack() {
    delete[] arr;
}

void Stack::push(StackInfo x)
{
    if (isFull())
    {
        std::cout << "Stack Overflow\n";
        exit(EXIT_FAILURE);
    }
    arr[++top] = x;
}

StackInfo Stack::pop()
{
    if (isEmpty())
    {
        std::cout << "Stack Underflow\n";
        exit(EXIT_FAILURE);
    }
    return arr[top--];
}

StackInfo Stack::peek()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        std::cout << "Stack is empty...\n";
        exit(EXIT_FAILURE);
    }
}

int Stack::size() {
    return top + 1;
}

bool Stack::isEmpty() {
    return top == -1;   
}

bool Stack::isFull() {
    return top == capacity - 1;     
}