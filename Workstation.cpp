#include <iostream>
#include <algorithm>
#include "Workstation.h"

namespace sdds {

    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    Workstation::Workstation(const std::string& token) : Station(token) {

    };

    void Workstation::fill(std::ostream& os){
        if (!m_orders.empty()){
            m_orders.front().fillItem(*this, os);
        }
    };

    bool Workstation::attemptToMoveOrder(){

        bool moved = false;

        // First check if the order has been filled and the inventory is = 0
        // If the order is filled (no more service required) OR insufficient quantity, move to the next station
        if (!m_orders.empty()) {
            if (m_orders.front().isItemFilled(getItemName()) || !getQuantity()) {

                // Check if the next station is not NULLPTR
                if (m_pNextStation) {
                    *m_pNextStation += std::move(m_orders.front());
                } else {

                    /*
                     * If there is no next station, we need to check if the front orders meets the requirements of completed
                     * or incompleted
                     */

                    // If the order is filled, move it to g_completed
                    if (m_orders.front().isOrderFilled()) {
                        // Since g_completed is a customer order type, there is not += overload
                        g_completed.push_back(std::move(m_orders.front()));
                    } else {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                }
                // We have to remove the element in the front because its no longer apart of this station since its filled.
                m_orders.pop_front();
                moved = true;
            };
        }

        return moved;
    };

    void Workstation::setNextStation(Workstation* station){
        if (station != nullptr){
            m_pNextStation = station;
        }
    };

    Workstation* Workstation::getNextStation() const{
        return m_pNextStation;
    };

    void Workstation::display(std::ostream& os) const {
        if (os){
            os << getItemName() << " --> ";
            if (getNextStation() != nullptr){
                os << m_pNextStation->getItemName();
            } else {
                os << "End of Line";
            }
            os << std::endl;
        }
    };

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder){
        m_orders.push_back(std::move(newOrder));
        return *this;
    };
}