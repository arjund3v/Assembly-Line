#include <iostream>
#include "Workstation.h"

namespace sdds {

    Workstation::Workstation(const std::string& token) : Station(token) {

    };

    void Workstation::fill(std::ostream& os){

    };

    bool Workstation::attemptToMoveOrder(){
        return true;
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