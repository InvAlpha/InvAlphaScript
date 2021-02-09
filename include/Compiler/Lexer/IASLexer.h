#pragma once
#define IAS_DEBUG
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>

#include "../../IASDataType.h"
#include "IASToken.h"

//#include "../../Dependencies/re2/re2.h"

namespace invalpha
{
    namespace script
    {
        class IASLexer
        {
        public:
            void init();
            void loadSource(const std::string& file_path);

            void skipChars(const IASuint32& offset);
            void skipWhiteSpaces();
            void skipComment();
            bool isWhiteSpace(const IASint8& ch);
            bool isNewLine(const IASint8& ch);
            bool isDigit(const IASint8& ch);
            bool isLetter(const IASint8& ch);
            bool test(const std::string& prefix);
            void nextString();
            void nextNumber();
            void nextIdentifier();
            void nextToken();
        private:
            IASuint32 read_index = 0;
            IASToken next_token;
            std::string source;
            IASuint32 line = 0;
            std::unordered_map<std::string, IASTokenType> keymap;
            std::vector<std::string> literals;
        };
    }
}