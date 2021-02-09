#include "IASLexer.h"

void invalpha::script::IASLexer::init()
{
    keymap["if"] = IASTokenType::TOKEN_KW_IF;
    keymap["continue"] = IASTokenType::TOKEN_KW_CONTINUE;
    keymap["break"] = IASTokenType::TOKEN_KW_BREAK;
    keymap["while"] = IASTokenType::TOKEN_KW_WHILE;
    keymap["variable"] = IASTokenType::TOKEN_KW_VARIABLE;
    keymap["with"] = IASTokenType::TOKEN_KW_WITH;
    keymap["else"] = IASTokenType::TOKEN_KW_ELSE;
    keymap["return"] = IASTokenType::TOKEN_KW_RETURN;
    keymap["create"] = IASTokenType::TOKEN_KW_CREATE;
    keymap["for"] = IASTokenType::TOKEN_KW_FOR;
}

void invalpha::script::IASLexer::loadSource(const std::string& file_path)
{
    std::ifstream fin(file_path);
    std::stringstream ssm;
    if (fin)
    {
        ssm << fin.rdbuf();
        source = std::move(ssm.str());
        fin.close();
    }
    else
        std::cout << "[LexerError] Unable to load source at " << file_path << std::endl;
}

void invalpha::script::IASLexer::skipChars(const IASuint32& offset)
{
    read_index += offset;
}

void invalpha::script::IASLexer::skipWhiteSpaces()
{
    while (read_index < source.size())
    {
        if (test("|")) skipComment();
        else if (test("\r\n") || test("\n\r"))
        {
            skipChars(2);
            ++line;
        }
        else if (isNewLine(source[read_index]))
        {
            skipChars(1);
            ++line;
        }
        else if (isWhiteSpace(source[read_index]))
        {
            skipChars(1);
        }
        else break;
    }
}

void invalpha::script::IASLexer::skipComment()
{
    skipChars(1);
    while (read_index < source.size() && !isNewLine(source[read_index]))
        skipChars(1);
}

bool invalpha::script::IASLexer::isWhiteSpace(const IASint8& ch)
{
    switch (ch)
    {
    case '\t':
        return true;
    case '\n':
        return true;
    case '\v':
        return true;
    case '\f':
        return true;
    case '\r':
        return true;
    case ' ':
        return true;
    default: return false;
    }
}

bool invalpha::script::IASLexer::isNewLine(const IASint8& ch)
{
    return ch == '\r' || ch == '\n';
}

bool invalpha::script::IASLexer::isDigit(const IASint8& ch)
{
    return ch >= '0' && ch <= '9';
}

bool invalpha::script::IASLexer::isLetter(const IASint8& ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool invalpha::script::IASLexer::test(const std::string& prefix)
{
    auto index = read_index;
    for (const auto& ch : prefix)
    {
        if (!(index < source.size() && ch == source[index]))
            return false;
    }
    return true;
}

void invalpha::script::IASLexer::nextToken()
{
    switch (source[read_index])
    {
    case '(':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_LPAREN;
        break;
    case ')':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_RPAREN;
        break;
    case '[':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_LBRACK;
        break;
    case ']':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_RBRACK;
        break;
    case '{':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_LCURLY;
        break;
    case '}':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_RCURLY;
        break;
    case '~':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_WAVE;
        break;
    case '+':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_ADD;
        break;
    case '-':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_MINUS;
        break;
    case '*':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_MUL;
        break;
    case '/':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_DIV;
        break;
    case '<':
        if (test("<="))
        {
            skipChars(2);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_LE;
        }
        else
        {
            skipChars(1);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_LT;
        }
        break;
    case '>':
        if (test(">="))
        {
            skipChars(2);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_GE;
        }
        else
        {
            skipChars(1);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_GT;
        }
        break;
    case '=':
        if (test("=="))
        {
            skipChars(2);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_EQ;
        }
        else
        {
            skipChars(1);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_ASSIGN;
        }
        break;
    case '.':
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_DOT;
        break;
    case '"':
        skipChars(1);
        nextString();
        break;
    case '\'':
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_S_QUOTATION;
        break;
    }

    if (isDigit(source[read_index]))
        nextNumber();
    if (isLetter(source[read_index]))
        nextIdentifier();

#ifdef IAS_DEBUG
    std::cout << "[Line " << next_token.line << "]";
#endif
}

void invalpha::script::IASLexer::nextString()
{
    next_token.line = line;
    next_token.type = IASTokenType::TOKEN_STRING;
    next_token.literal_index = literals.size();
    IASuint32 right_quotation_index = read_index;
    while (right_quotation_index < source.size())
    {
        if (source[read_index] != '"')
            ++right_quotation_index;
    }
    literals.push_back(source.substr(read_index, right_quotation_index - read_index));
    read_index = right_quotation_index + 1;
}

void invalpha::script::IASLexer::nextNumber()
{
}

void invalpha::script::IASLexer::nextIdentifier()
{
}
