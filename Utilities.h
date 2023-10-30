// Name: Arjun Saini
// Seneca Student ID: 106182223
// Seneca email: asaini82@myseneca.ca
// Date of completion: 29/03/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

namespace sdds {

    class Utilities {
    private:
        int m_widthField = 1;
        inline static char m_delimiter{};
    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        std::string removeWhitespaces(std::string str)const;
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };

}

#endif
