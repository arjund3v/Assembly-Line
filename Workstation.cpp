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

    };

    void Workstation::setNextStation(Workstation* station){

    };

    Workstation* Workstation::getNextStation() const{
        return m_pNextStation;
    };

    void Workstation::display(std::ostream& os) const{

    };

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder){
        return *this;
    };
}