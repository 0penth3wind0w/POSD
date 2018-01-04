#include <iostream>
#include <string>

#include "scanner.h"
#include "parser.h"

int main(){
    string input, context = "";
    Parser *parser;
    while (true)
    {
        do
        {
            if (context == "")
                cout << "?- ";
            else
                cout << "|   ";
            getline(cin, input);
            if (input != "")
                while (input[0] == ' ')
                    input = input.substr(1, input.size() - 1);
            context += input;
        } while (input == "" || context.back() != '.');
        if (context == "halt.")
            break;
        parser = new Parser(Scanner(context));
        try
        {
            cout << parser->buildExpression()->getResult() << endl;
        }
        catch (string &msg)
        {
            cout << msg << endl;
        }
        context = "";
    }
    return 0;
}