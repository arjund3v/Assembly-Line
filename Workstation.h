#include <iostream>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

namespace sdds {

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : Station {
    private:
        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{};
    public:
        Workstation(const Workstation& other) = delete;
        Workstation(Workstation&& other) = delete;
        Workstation& operator=(const Workstation& other) = delete;
        Workstation& operator=(Workstation&& other) = delete;

        Workstation() = default;
        Workstation(const std::string& token);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
        ~Workstation() = default;
    };

}

#endif
