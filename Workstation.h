// Name: Arjun Saini
// Seneca Student ID: 106182223
// Seneca email: asaini82@myseneca.ca
// Date of completion: 18/11/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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

    class Workstation : public Station {
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
    };

}

#endif
