// Name: Arjun Saini
// Seneca Student ID: 106182223
// Seneca email: asaini82@myseneca.ca
// Date of completion: 06/11/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Station.h"
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

namespace sdds {

    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& src) : m_itemName(src) {};
    };

    class CustomerOrder {
    private:
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item** m_lstItem{};
        inline static size_t m_widthField{};
    public:
        CustomerOrder() = default;
        CustomerOrder(const std::string& token);
        CustomerOrder(const CustomerOrder& other);
        CustomerOrder(CustomerOrder&& other) noexcept;
        CustomerOrder& operator=(const CustomerOrder& other) = delete;
        CustomerOrder& operator=(CustomerOrder&& other) noexcept;
        bool isOrderFilled()const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
        ~CustomerOrder();
    };

}

#endif
