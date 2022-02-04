//
// Created by David on 04-Feb-22.
//
#include <iostream>
#include "string"
#include "limits"
#include "vector"

class Interpreter {
    std::string program;
    int pointer = 0;
    std::vector<unsigned char> array = std::vector<unsigned char>(30000);

    public: Interpreter(std::string program)
    {
        this->program = program;
    }

    public: int run() {
        if (checksumBrackets())
        {
            std::cout << "The generated program could not be interpreted as there is a problem with your bracket structure" << std::endl;
            return -1;
        }
        return parseCode();
    }

    int checksumBrackets() {
        int i = 0;
        int sum = 0;
        while (i < program.length() && sum >= 0) {
            switch (program[i]) {
                case '[':
                    sum++;
                    break;
                case ']':
                    sum--;
                    break;
                default:
                    break;
            }
            i++;
        }
        return sum;
    }

    public: int parseCode()
    {
        int i = 0;
        while (i < program.length()) {
            switch (program[i]) {
                case '+':
                    array[pointer]++; //TODO define increment behavior above 255
                    break;
                case '-':
                    array[pointer]--; //TODO define decrement behavior above 255
                    break;
                case '>':
                    if (pointer > array.size())
                        array.resize(array.size()*2);
                    pointer++;
                    break;
                case '<':
                    if (!pointer)
                        std::cout << "Execution exception: pointer moved out of bounds (below zero) at instruction [" << i+1 << "]." << std::endl;
                    pointer--;
                    break;
                case '.':
                    std::cout << array[pointer]; //TODO print in the same line, even after io flush
                    break;
                case ',':
                    unsigned char buffer; //TODO define behavior when input is outside the ASCII table
                    std::cin >> buffer;
                    array[pointer] = buffer;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    break;
                case '[':
                    if (!array[pointer]) {
                        int layer = 1;
                        while (layer += (program[++i] == '[' ? 1 : (program[i] == ']' ? -1 : 0)));
                    }
                    break;
                case ']':
                    if (array[pointer]) {
                        int layer = 1;
                        while (layer += (program[--i] == '[' ? -1 : (program[i] == ']' ? 1 : 0)));
                    }
                    break;
                default:
                    //Beyond the instruction characters everything is treated as a comment, and thus nothing is executed
                    break;
            }
            i++;
        }
        return 0;
    }
};
