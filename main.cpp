#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <map>

std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> token_vector;
    for (int i = 0 ; i < input.size() ; i++) {
        auto isOperator = [](char c, char previous_char) {
            static const std::array<char, 7> operators {'+', '-', '=', '/', '*', '(', ')'};
            bool is_in_operators = std::find(operators.begin(), operators.end(), c) != operators.end();
            bool is_operator = is_in_operators && (isalnum(previous_char) || previous_char == '(' || previous_char == ')');
            return is_operator;
        };
        char first_char = input[i];
        if (isalnum(first_char) || first_char == '-') {
            std::string current_token;
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
            token_vector.push_back(std::string(1, input[i]));
        }
    }

    for (const auto& tok : token_vector) {
        std::cout << tok << "\n";
    }

    return token_vector;
}

double evaluate(std::vector<std::string> expression) {
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc != 2) {
        return 0;
    }
    std::string input = argv[1];
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());

    auto token_list = tokenize(input);

    std::map<std::string, double> variables;
    bool is_assignement = false;
    for (const auto& token : token_list) {
        if (token == "=") {
            is_assignement = true;
            break;
        }
    }

    if (is_assignement) {
        auto expression = std::vector<std::string>(token_list.begin() + 2, token_list.end());
        variables[token_list[0]] = evaluate(expression);
    } else {
        evaluate(token_list);
    }

    return 0;
}


