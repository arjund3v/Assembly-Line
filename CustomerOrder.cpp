#include <iostream>
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
        for (auto i = 0; i < m_cntItem; ++i) {
            m_lstItem[i] = new Item(items[i]);
        };

        if (m_widthField < u.getFieldWidth()){
            m_widthField = u.getFieldWidth();
        }

    };

    CustomerOrder::CustomerOrder(const CustomerOrder& other){
        throw std::runtime_error("The copy assignment operator should not be used.");
    };

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept{
        *this = std::move(other);
    };

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other){
            m_name = other.m_name;
            m_product = other.m_product;
            m_widthField = other.m_widthField;

            for (auto i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
                m_lstItem = nullptr;
            }

            delete[] m_lstItem;
            m_lstItem = nullptr;

            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
            other.m_product = "";
            other.m_name = "";
            other.m_widthField = 0;
        }
        return *this;
    };

    bool CustomerOrder::isOrderFilled()const{

        bool filled = false;
        for (auto i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_isFilled){
                filled = true;
            } else {
                filled = false;
                break;
            }
        }

        return filled;
    };

    bool CustomerOrder::isItemFilled(const std::string& itemName) const{

    };

    void CustomerOrder::fillItem(Station& station, std::ostream& os){
        
    };

    void CustomerOrder::display(std::ostream& os) const{

    };

    CustomerOrder::~CustomerOrder(){
        for (auto i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
            m_lstItem[i] = nullptr;
        }

        delete[] m_lstItem;
        m_lstItem = nullptr;
    };


}