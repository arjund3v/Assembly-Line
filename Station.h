// Name: Arjun Saini
// Seneca Student ID: 106182223
// Seneca email: asaini82@myseneca.ca
// Date of completion: 03/11/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

namespace sdds {

    class Station {
    private:
        int m_stationID{};
        std::string m_itemName{};
        std::string m_desc{};
        unsigned int m_serial{};
        size_t m_numItems{};
        inline static int m_widthField{};
        inline static int m_idGen{};
    public:
        Station() = default;
        Station(const std::string& rec);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };

}

#endif
