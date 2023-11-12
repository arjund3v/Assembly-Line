// Name: Arjun Saini
// Seneca Student ID: 106182223
// Seneca email: asaini82@myseneca.ca
// Date of completion: 06/11/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <vector>
#include "Utilities.h"
#include "CustomerOrder.h"

namespace sdds {

    CustomerOrder::CustomerOrder(const std::string token){
        // Initialize local variables
        Utilities u{};
        size_t pos{};
        bool more = true;
        std::vector<std::string>items{};
        std::string itemName{};

        // We can regularly extract the customer name and product name
        m_name = u.extractToken(token, pos, more);
        m_product = u.extractToken(token, pos, more);

        /*
         * Once we get to the items section, we use a loop to extract each item name
         * and add it to the vector of strings
         */

        while (more){
            itemName = u.extractToken(token, pos, more);
            items.push_back(itemName);
        };

        // We assign the size of the vector to the number of items
        m_cntItem = items.size();

        // Allocate a block of memory for the array
        m_lstItem = new Item*[m_cntItem];

        // For each pointer in the array we make it point to a Item object
        for (size_t i = 0; i < m_cntItem; ++i) {
            m_lstItem[i] = new Item(items[i]);
        };

        if (CustomerOrder::m_widthField < u.getFieldWidth()){
            CustomerOrder::m_widthField = u.getFieldWidth();
        }

    };

    CustomerOrder::CustomerOrder(const CustomerOrder& other){
        throw std::logic_error("The copy assignment operator should not be used.");
    };

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        *this = std::move(other);
    };

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other){
            m_name = other.m_name;
            m_product = other.m_product;

            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
                m_lstItem[i] = nullptr;
            }

            delete[] m_lstItem;
            m_lstItem = nullptr;

            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
            other.m_product = "";
            other.m_name = "";
        }
        return *this;
    };

    bool CustomerOrder::isOrderFilled()const{
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled){
                return false;
            }
        }

        return true;
    };

    bool CustomerOrder::isItemFilled(const std::string& itemName) const{

        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName){
                if (!m_lstItem[i]->m_isFilled){
                    return false;
                }
            }
        }

        return true;
    };

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {

        bool filled = false;

        for (size_t i = 0; i < m_cntItem && !filled; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled){
                if (station.getQuantity() > 0){
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " " << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    filled = true;
                }
            } else if (m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isFilled){
                os << "    Unable to fill " << m_name << ",  " << m_product << " " << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
                break;
            }
        }

    };

    void CustomerOrder::display(std::ostream& os) const{
        if (os) {
            os << m_name << " - " << m_product << std::endl;
            for (size_t i = 0; i < m_cntItem; ++i) {
                os << "[" << std::left << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
                os << std::left << std::setw(static_cast<int>(m_widthField)) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
                os << std::right << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
            };
        }
    };

    CustomerOrder::~CustomerOrder(){
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
            m_lstItem[i] = nullptr;
        }

        delete[] m_lstItem;
        m_lstItem = nullptr;
    };


}