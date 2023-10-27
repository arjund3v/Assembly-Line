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
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };

}

#endif
