#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
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
                    auto active = std::find_if(stations.begin(), stations.end(), [=](const Workstation* station) {
                        return activeStationString == station->getItemName();
                    });

                    auto next = std::find_if(stations.begin(), stations.end(), [=](const Workstation* station) {
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

                // Looking for the other whose next station is not equal to station
                auto first = std::find_if(m_activeLine.begin(), m_activeLine.end(), [=](const Workstation* station) {
                    // We check to find which of the others do not equal the station in the outer loop
                    return std::none_of(m_activeLine.begin(), m_activeLine.end(), [=](const Workstation* other) {
                        return other->getNextStation() == station;
                    });
                });

                // We assign m_firstStation to the first node we found
                m_firstStation = *first;

                // Update the size
                m_cntCustomerOrder = g_pending.size();


            }
        } catch (...) {
            throw std::string("An error occurred in the LineManager Constructor...");
        }


    };

    void LineManager::reorderStations() {

        // We initialize the temp vector to have the first station in the first position
        std::vector<Workstation*> temp{};
        temp.push_back(m_firstStation);

        do  {

            // We find the next station, by going to the back of the vector.
            // This works because each time we add a new item, its added to the back of the vector
            auto next = temp.back()->getNextStation();
            temp.push_back(next);

            // Do this till the item at the end points to nothing indicating the last node
        } while(temp.back()->getNextStation() != nullptr);

        // Assign the active line to the ordered vector
        m_activeLine = temp;
    };

    bool LineManager::run(std::ostream &os) {


        static size_t calls = 0;

        // represents number of calls to function
        calls++;

        os << "Line Manager Iteration: " << calls << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        };

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
            station->fill(os);
        });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
           station->attemptToMoveOrder();
        });

        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    };

    void LineManager::display(std::ostream &os) const {
        for (auto& station: m_activeLine) {
            station->display(os);
        };
    };
}