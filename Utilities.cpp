// Name: Arjun Saini
// Seneca Student ID: 106182223
// Seneca email: asaini82@myseneca.ca
// Date of completion: 03/11/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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
        size_t nextDelim{};

        if (more){

            // Find the position of the next delim starting from the next_pos
            nextDelim = str.find_first_of(m_delimiter, next_pos);

            /*
             * If this condition is true, we throw a exception because that means the string could be empty
             */
            if (nextDelim == next_pos){
                more = false;
                throw std::range_error("Delimiter found at the start position");
            } else {

                // If we get npos, that means theres no delimeter which means we are at the last token
                if (nextDelim == std::string::npos){
                    // Setting more to false will essentially break the outer loop
                    more = false;
                }

                // Extract from the next_pos, to the next delimeter
                temp = str.substr(next_pos, (nextDelim - next_pos));

                // Remove any leading/trailing whitespaces
                temp = removeWhitespaces(temp);

                /*
                 * We add 1 extra to the next position because we want the position to be the starting position of the
                 * token not the delimiter, otherwise it will cause a exception
                 */
                next_pos = nextDelim+1;


                // Update the width field
                if (m_widthField < temp.length()){
                    m_widthField = temp.length();
                }

            }
        };

        return temp;
    };

    std::string Utilities::removeWhitespaces(std::string str)const {
        size_t start=0;
        size_t end=0;

        if (!str.empty()) {
            while (start < str.length() && isspace(str[start])) {
                start++;
            }

            str.std::string::erase(0, start);

            end = str.length();

            while(end > 0 && std::isspace(str[end-1])){
                end--;
            }

            str.std::string::erase(end);
        }

        return str;
    };

    void Utilities::setDelimiter(char newDelimiter){
        m_delimiter = newDelimiter;
    };

    char Utilities::getDelimiter(){
        return m_delimiter;
    };
}