#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <map>
#include <cstdlib>

using std::string;
using std::vector;

string evaluate_unit(const string& operand1, const string& operateur, const string& operand2) {
    std::cout << operand1 << std::endl;
    std::cout << operand2 << std::endl;
    double op1 = std::stod(operand1);
    double op2 = std::stod(operand2);

    char operateur_char = operateur[0];
    switch (operateur_char) {
    case '^':
        return std::to_string(std::pow(op1, op2));
        break;
    case '*':
        return std::to_string(op1 * op2);
        break;
    case '/':
        return std::to_string(op1 / op2);
        break;
    case '+':
        return std::to_string(op1 + op2);
        break;
    case '-':
        return std::to_string(op1 - op2);
        break;
    }

}

vector<string> tokenize(const string& input) {
    vector<string> token_vector;
    for (int i = 0 ; i < input.size() ; i++) {
        auto isOperator = [](char c, char previous_char) {
            static const std::array<char, 7> operators {'+', '-', '=', '/', '*', '(', ')'};
            bool is_in_operators = std::find(operators.begin(), operators.end(), c) != operators.end();
            bool is_operator = is_in_operators && (isalnum(previous_char) || previous_char == '(' || previous_char == ')');
            return is_operator;
        };
        char first_char = input[i];
        if (isalnum(first_char) || first_char == '-') {
            string current_token;
            if (i == 0) {
                current_token.push_back(input[i]);
                i++;
            }
            for ( ; !isOperator(input[i], input[i-1]) && i < input.size() ; i++) {
                current_token.push_back(input[i]);
            }
            token_vector.push_back(current_token);
        }

        if (i < input.size()) {
            token_vector.push_back(string(1, input[i]));
        }
    }

    for (const auto& tok : token_vector) {
        std::cout << tok << "\n";
    }

    return token_vector;
}

double evaluate(const vector<string>& expression) {
    int i = 0;
    while (i < expression.size()) {

        i++;
    }
    return 0;
}

bool firstIsHigherPriority(const string& operateur1, const string& operateur2) {
    const std::array<string, 5> operators_by_priority_asc {"-", "+", "/", "*", "^"};
    auto it1 = std::find(operators_by_priority_asc.begin(), operators_by_priority_asc.end(), operateur1);
    auto it2 = std::find(operators_by_priority_asc.begin(), operators_by_priority_asc.end(), operateur2);
    return (true);
}

string evaluate_simple_expression(const vector<string>& expression) {
    string operande1, operateur, operande2;
    int unit_index;
    for (int i = 0 ; i < expression.size() - 2 ; i += 2) {
        std::cout << "in here" << std::endl;
        if (firstIsHigherPriority(expression[i+1], operateur)) {
            operande1 = expression[i];
            operateur = expression[i+1];
            operande2 = expression[i+2];
            unit_index = i;
        }
    }
    for (auto s : expression) {
        std::cout << s << ";";
    }
    string result = evaluate_unit(operande1, operateur, operande2);
    auto simplified_expression = expression;
    simplified_expression.erase(expression.begin() + unit_index, expression.begin() + unit_index + 2);
    simplified_expression.insert(expression.begin() + unit_index, result);
    if (simplified_expression.size() == 1) {
        std::cout << "result: " << simplified_expression[0] << std::endl;
        return simplified_expression[0];
    } else {
        return evaluate_simple_expression(simplified_expression);
    }
}



int main(int argc, char* argv[])
{
    if(argc != 2) {
        return 0;
    }
    string input = argv[1];
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());

    auto token_list = tokenize(input);

    std::map<string, double> variables;
    bool is_assignement = false;
    for (const auto& token : token_list) {
        if (token == "=") {
            is_assignement = true;
            break;
        }
    }

    if (is_assignement) {
        auto expression = vector<string>(token_list.begin() + 2, token_list.end());
        //variables[token_list[0]] = evaluate_simple_expression(expression);
    } else {
        evaluate_simple_expression(token_list);
    }

    return 0;
}


