// Name: Arjun Saini
// Seneca Student ID: 106182223
// Seneca email: asaini82@myseneca.ca
// Date of completion: 29/03/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
    Station::Station(std::string rec){
        Utilities u{};
        size_t pos{};
        bool more = true;

        m_idGen++;
        m_stationID = m_idGen;
        m_itemName = u.extractToken(rec, pos, more);
        m_serial = std::stoul(u.extractToken(rec, pos, more));
        m_numItems = std::stoul(u.extractToken(rec, pos, more));


        if (m_widthField < u.getFieldWidth()){
            m_widthField = u.getFieldWidth();
        };

        m_desc = u.extractToken(rec, pos, more);

    };

    const std::string& Station::getItemName() const{
        return m_itemName;
    };

    size_t Station::getNextSerialNumber(){
        return m_serial++;
    };

    size_t Station::getQuantity() const{
        return m_numItems;
    };

    void Station::updateQuantity(){
        if ((m_numItems - 1) >= 0){
            m_numItems--;
        }
    };

    void Station::display(std::ostream& os, bool full) const{

        os << std::right << std::setfill('0') << std::setw(3) << m_stationID << " | ";
        os << std::left << std::setfill(' ') << std::setw(m_widthField) << m_itemName << " | ";
        os << std::right << std::setfill('0') << std::setw(6) << m_serial << " | ";

        if (full){
            os << std::right << std::setfill(' ') << std::setw(4) << m_numItems << " | ";
            os << std::left << m_desc << std::endl;
        } else {
            os << std::endl;
        }

    };
}