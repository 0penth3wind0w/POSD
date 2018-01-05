#include <iostream>
#include <stream>
#include <algorithm>

#include "scanner.h"
#include "parser.h"
#include "scanner.h"

using namespace std;

int main(){    
    while (true)
    {
        string context = "";
        string input;
        do{
            if (context == "")
                cout << "?- ";
            else
                cout << "|   ";
            getline(cin, input);
            context += input;
        } while (input == "" || context.back() != '.');
        if (context == "halt."){
            break;
        }
        
        Parser *parser;
        parser = new Parser(Scanner(context));
        try{
            cout << parser->buildExpression()->result() << endl;
        }
        catch (string &msg){
            cout << msg << endl;
        }
        return 0;
    }
}