#include "Parser.h"
#include "TokenType.h"
#include "Token.h"

#include <exception>
#include <function>
#include <initializer_list>
#include <iterator>
#include <vector>


namespace boop {

Parser::Parser(const std::vector<Token>& _tokens, ErrorHandler &_error):
    m_tokens(_tokens), m_error_handler(_error) {
        this-> m_current_iter;
    }

}