#include <iostream>
#include <string>
#include "Utilities.h"

namespace sdds {

    void Utilities::setFieldWidth(size_t newWidth){
        m_widthField = newWidth;
    };

    size_t Utilities::getFieldWidth() const{
        return m_widthField;
    };

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){

        std::string temp{};
        // Get the position of the first delim in the string
        next_pos = str.std::string::find(m_delimiter, next_pos);

        if (next_pos != std::string::npos){
            more = true;
            temp = str.substr(next_pos);
        } else {
            more = false;
            temp = str.substr(next_pos);
        }

        return temp;
    };

    void Utilities::setDelimiter(char newDelimiter){
        m_delimiter = newDelimiter;
    };

    char Utilities::getDelimiter(){
        return m_delimiter;
    };
}