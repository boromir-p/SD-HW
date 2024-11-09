#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

struct Token
{
    enum TokenType {open_par, number, oper, close_par, fl_numb};
    TokenType type;
    std::string val;
};

std::ostream& operator << (std::ostream &out, const Token &t)
{
    out << "Token(" << t.type << "," << t.val << ")";
    return out;
}

bool isOperator(char c)
{
    return c == '+' || 
           c == '-' || 
           c == '*' || 
           c == '/';
}

Token nextToken(std::istream &in)
{
    char c = in.peek();
    if (isdigit(c))
    {
        bool floatigPointNumber = false;
        std::string num;
        while (isdigit(c) || c == '.')
        {
            if(c == '.'){
                if(floatigPointNumber){
                    std::cerr << "char=" << c << "\n" << std::endl;
                    throw std::runtime_error("Invalid character in number");
                }
                floatigPointNumber = true;
            }
            num += c;
            in.get();
            c = in.peek();
        }
        
        return floatigPointNumber ? Token{Token::fl_numb,num} : Token{Token::number,num};
    } 
    else if (c == '(')
    {
        in.get();
        return Token{Token::open_par, "("};
    } else if (c == ')')
    {
        in.get();
        return Token{Token::close_par, ")"};
    } else if (isOperator(c))
    {
        in.get();
        return Token{Token::oper, std::string("") + c};
    } else
    {
        return Token{Token::number, ""};
    }

}

std::vector<Token> tokenize(std::istream &in)
{
    std::vector<Token> tokens;
    
    while (in.peek() != EOF && in.good())
    {
        if (in.peek() == '\n') {
            in.get();
            continue;
        }

        Token t = nextToken(in);
        
        if (t.val.empty()) {
            std::cerr << "Invalid token encountered" << std::endl;
            break; 
        }

        tokens.push_back(t); 
    }
    
    return tokens;
}



int main()
{
    std::ifstream in("expression.exis");
    
    std::vector<Token> tokens = tokenize(in);
    // do something with parsed

    for (Token t : tokens)
    {
        std::cout << t;
    }

    std::cout << std::endl;

    return 0;
}