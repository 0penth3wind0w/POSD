#include <iostream>
#include <stream>
#include <algorithm>

#include "scanner.h"
#include "parser.h"

using std::string;

int main(){
    string input = "";
    string context = "";

    while(context != "halt."){
        do{
            if (context == ""){
                cout << "?- ";
            }
            else{
                cout << "|   ";
            }
            getline(cin, input);
            if (input != ""){
                input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
            }
            context += input;
        } while (input == "" || context.back() != '.');
        parser = new Parser(Scanner(context));
        try{
            cout << parser->buildExpression()->getResult() << endl;
        }
        catch (string &msg){
            cout << msg << endl;
        }
        context = "";
    }
    return 0;
}