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
        Station(std::string rec);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };

}

#endif
