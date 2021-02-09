#pragma once

namespace invalpha
{
    namespace script
    {
        enum class IASTokenType :unsigned char
        {
            TOKEN_UNDEFINED,
            TOKEN_EOF,
            TOKEN_SEP_DOT, // .
            TOKEN_SEP_LPAREN, // (
            TOKEN_SEP_RPAREN, // )
            TOKEN_SEP_LBRACK, // [
            TOKEN_SEP_RBRACK, // ]
            TOKEN_SEP_LCURLY, // {
            TOKEN_SEP_RCURLY, // }
            TOKEN_SEP_S_QUOTATION, // '
            TOKEN_OP_WAVE, // ~
            TOKEN_OP_ASSIGN, // =
            TOKEN_OP_MINUS, // -
            TOKEN_OP_ADD, // +
            TOKEN_OP_MUL, // *
            TOKEN_OP_DIV, // /
            TOKEN_OP_LT, // <
            TOKEN_OP_LE, // <=
            TOKEN_OP_GT, // >
            TOKEN_OP_GE, // >=
            TOKEN_OP_EQ, // ==
            TOKEN_OP_AND, // and
            TOKEN_OP_OR, // or
            TOKEN_OP_NOT, // not
            TOKEN_KW_BREAK, // break
            TOKEN_KW_IF, // if
            TOKEN_KW_CONTINUE, // continue
            TOKEN_KW_WHILE, // while
            TOKEN_KW_VARIABLE, // variable
            TOKEN_KW_WITH, // with
            TOKEN_KW_ELSE, // else
            TOKEN_KW_RETURN, // return
            TOKEN_KW_CREATE, // create
            TOKEN_KW_FOR, // for
            TOKEN_IDENTIFIER,
            TOKEN_NUMBER,
            TOKEN_STRING
        };

        struct IASToken
        {
            IASTokenType type = IASTokenType::TOKEN_UNDEFINED;
            IASuint32 line = 0;
            IASuint32 literal_index = 0;
        };
    }
}