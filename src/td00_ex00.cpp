#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <stack>
#include <iostream>
#include <cctype>

bool is_floating(std::string const &s)
{
    if (s.empty())
        return false;

    for (char el : s)
    {
        if (el != '.')
        {
            if (!std::isdigit(static_cast<unsigned char>(el)))
            {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::string> split_string(std::string const &s)
{
    std::istringstream in(s);
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());
}

float npi_evaluate(std::vector<std::string> const &tokens)
{
    std::stack<float> numbers_stack{};

    for (std::string const &token : tokens)
    {
        if (is_floating(token))
        {
            numbers_stack.push(std::stof(token));
        }
        else
        {
            if (numbers_stack.size() < 2)
                throw std::runtime_error("invalid RPN expression");

            float rightOperand = numbers_stack.top();
            numbers_stack.pop();
            float leftOperand = numbers_stack.top();
            numbers_stack.pop();

            float result{};
            if (token == "+")
                result = leftOperand + rightOperand;
            else if (token == "-")
                result = leftOperand - rightOperand;
            else if (token == "*")
                result = leftOperand * rightOperand;
            else if (token == "/")
                result = leftOperand / rightOperand;
            else
                throw std::runtime_error("unknown operator: " + token);

            numbers_stack.push(result);
        }
    }

    if (numbers_stack.empty())
        throw std::runtime_error("empty result");

    return numbers_stack.top();
}

int main()
{
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> elements(split_string(input));
    float result = npi_evaluate(elements);
    std::cout << result << std::endl;

    return 0;
}






