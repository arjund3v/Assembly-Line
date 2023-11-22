// Name: Arjun Saini
// Seneca Student ID: 106182223
// Seneca email: asaini82@myseneca.ca
// Date of completion: 21/11/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Workstation.h"
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

namespace sdds {

    class LineManager {
    private:
        std::vector<Workstation*> m_activeLine{};
        size_t m_cntCustomerOrder{};
        Workstation* m_firstStation{};
    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };

}

#endif
