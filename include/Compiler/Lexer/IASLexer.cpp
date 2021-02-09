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

bool invalpha::script::IASLexer::isNumber(const IASint8& ch)
{
    return isDigit(ch) || ch == '.';
}

bool invalpha::script::IASLexer::test(const std::string& prefix)
{
    auto index = read_index;
    for (const auto& ch : prefix)
    {
        if (!(index < source.size() && ch == source[index]))
            return false;
        ++index;
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
        next_token.data = "(";
        goto scan_done;
    case ')':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_RPAREN;
        next_token.data = ")";
        goto scan_done;
    case '[':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_LBRACK;
        next_token.data = "[";
        goto scan_done;
    case ']':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_RBRACK;
        next_token.data = "]";
        goto scan_done;
    case '{':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_LCURLY;
        next_token.data = "{";
        goto scan_done;
    case '}':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_RCURLY;
        next_token.data = "}";
        goto scan_done;
    case '~':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_WAVE;
        next_token.data = "~";
        goto scan_done;
    case '+':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_ADD;
        next_token.data = "+";
        goto scan_done;
    case '-':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_MINUS;
        next_token.data = "-";
        goto scan_done;
    case '*':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_MUL;
        next_token.data = "*";
        goto scan_done;
    case '/':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_OP_DIV;
        next_token.data = "/";
        goto scan_done;
    case '<':
        if (test("<="))
        {
            skipChars(2);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_LE;
            next_token.data = "<=";
        }
        else
        {
            skipChars(1);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_LT;
            next_token.data = "<";
        }
        goto scan_done;
    case '>':
        if (test(">="))
        {
            skipChars(2);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_GE;
            next_token.data = ">=";
        }
        else
        {
            skipChars(1);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_GT;
            next_token.data = ">";
        }
        goto scan_done;
    case '=':
        if (test("=="))
        {
            skipChars(2);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_EQ;
            next_token.data = "==";
        }
        else
        {
            skipChars(1);
            next_token.line = line;
            next_token.type = IASTokenType::TOKEN_OP_ASSIGN;
            next_token.data = "=";
        }
        goto scan_done;
    case '.':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_DOT;
        next_token.data = ".";
        goto scan_done;
    case '"':
        skipChars(1);
        nextString();
        goto scan_done;
    case '\'':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_S_QUOTATION;
        next_token.data = "\'";
        goto scan_done;
    case ',':
        skipChars(1);
        next_token.line = line;
        next_token.type = IASTokenType::TOKEN_SEP_COMMA;
        next_token.data = "\'";
        goto scan_done;
    case ':': // discard
        skipChars(1);
        return;
    case '_': // discard
        skipChars(1);
        return;
    case '#': // discard
        skipChars(1);
        return;
    case ';': // discard
        skipChars(1);
        return;
    case '&': // discard
        skipChars(1);
        return;
    case '!': // discard
        skipChars(1);
        return;
    default: break;
    }
    if (isDigit(source[read_index]))
        nextNumber();
    if (isLetter(source[read_index]))
        nextIdentifier();
scan_done:
#ifdef IAS_DEBUG
    auto token_type = (IASuint8)next_token.type;
    if (token_type < 2)
        std::cout << "[ NUL, ";
    else if (token_type < 11)
        std::cout << "[ SEP, " << next_token.data;
    else if (token_type < 25)
        std::cout << "[ OP, " << next_token.data;
    else if (token_type < 35)
        std::cout << "[ KEYWORD, " << next_token.data;
    else if (token_type == 35)
        std::cout << "[ ID, " << next_token.data;
    else
        std::cout << "[ LITERAL, " << next_token.data;
    std::cout << " ] " << std::flush;
#else ;
#endif
}

void invalpha::script::IASLexer::dbg_analyzeAll()
{
    while (true)
    {
        skipWhiteSpaces();
        if (read_index < source.size())
            nextToken();
        else
            break;
    }
}

void invalpha::script::IASLexer::nextString()
{
    next_token.line = line;
    next_token.type = IASTokenType::TOKEN_STRING;
    IASuint32 right_quotation_index = read_index;
    while (right_quotation_index < source.size())
    {
        if (source[right_quotation_index] != '"')
            ++right_quotation_index;
        else break;
    }
    next_token.data = source.substr(read_index, right_quotation_index - read_index);
    read_index = right_quotation_index + 1;
}

void invalpha::script::IASLexer::nextNumber()
{
    next_token.line = line;
    next_token.type = IASTokenType::TOKEN_NUMBER;
    IASuint32 num_end_index = read_index;
    while (num_end_index < source.size())
    {
        if (isNumber(source[num_end_index]))
            ++num_end_index;
        else break;
    }
    next_token.data = source.substr(read_index, num_end_index - read_index);
    read_index = num_end_index;
}

void invalpha::script::IASLexer::nextIdentifier()
{
    next_token.line = line;
    next_token.type = IASTokenType::TOKEN_IDENTIFIER;
    IASuint32 id_end_index = read_index;
    while (id_end_index < source.size())
    {
        if (isLetter(source[id_end_index]) || isDigit(source[id_end_index]))
            ++id_end_index;
        else break;
    }
    next_token.data = source.substr(read_index, id_end_index - read_index);
    auto iter = keymap.find(next_token.data);
    if (iter != keymap.end())
        next_token.type = iter->second;
    read_index = id_end_index;
}
