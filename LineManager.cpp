#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream f(file);

        try {


            if (!f) {
                std::invalid_argument("File not open, try again");
            } else {
                // First we want to create a vector of records, so we can iterate over each one using algos or ranged based loops
                std::string line{};
                std::vector<std::string> records{};

                // Variables for utilities class
                Utilities U{};
                size_t pos = 0;
                bool more = true;
                Utilities::setDelimiter('|');

                while (!f.eof()) {
                    std::getline(f, line);
                    records.push_back(line);
                }

                for (auto &record: records) {
                    more = true;
                    bool nextExists = false;

                    std::string activeStationString = U.extractToken(record, pos, more), nextStationString{};

                    if (more) {
                        nextStationString = U.extractToken(record, pos, more);
                        nextExists = true;
                    };

                    // Find both of the stations in the vector provided to us
                    auto active = std::find_if(stations.begin(), stations.end(), [=](const Workstation *station) {
                        return activeStationString == station->getItemName();
                    });

                    auto next = std::find_if(stations.begin(), stations.end(), [=](const Workstation *station) {
                        return nextStationString == station->getItemName();
                    });

                    // Once we find both of the stations, we can push them on to the active line
                    m_activeLine.push_back(*active);

                    // If there is a next station, we update that
                    if (nextExists)
                        (*active)->setNextStation(*next);
                    else
                        (*active)->setNextStation(nullptr);
                }

                // Find the first station
                m_firstStation = m_activeLine.front();

                // Update the size
                m_cntCustomerOrder = g_pending.size();


            }
        } catch (...){
            throw std::string("An error occured in the LineManager Constructor...");
        }


    };

    void LineManager::reorderStations(){

    };

    bool LineManager::run(std::ostream& os){
        return true;
    };

    void LineManager::display(std::ostream& os) const{
        for (auto& station : m_activeLine){
            station->display(os);
        };
    };
}