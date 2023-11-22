// Name: Arjun Saini
// Seneca Student ID: 106182223
// Seneca email: asaini82@myseneca.ca
// Date of completion: 21/11/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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
                // Variables for utilities class
                Utilities U{};
                Utilities::setDelimiter('|');
                size_t pos = 0;
                bool more = true;
                bool nextExists = false;

                while (!f.eof()) {
                    std::string line{};

                    // First we get the line from the file
                    std::getline(f, line);

                    /*
                     * Next exists is false because we don't know if there is a next station, so we assume there isn't
                     * but the following code helps us determine whether there is or not. More is used with extractToken.
                     * We assume that there will be more to the string, the function will tell us otherwise.
                     */
                    nextExists = false;
                    more = true;

                    /*
                     * These two strings will hold our current station and next station if there is one
                     */
                    std::string activeStationString = U.extractToken(line, pos, more);
                    std::string nextStationString{};

                    // If extractToken sets more to true, we know there is a next station, and we can extract it
                    if (more) {
                        nextStationString = U.extractToken(line, pos, more);
                        nextExists = true;
                    };

                    // First find the active station in the stations vector
                    auto active = std::find_if(stations.begin(), stations.end(), [=](const Workstation* station) {
                        return activeStationString == station->getItemName();
                    });

                    // Once we find the active station, we add it to the vector
                    m_activeLine.push_back(*active);

                    // If there is a next station, we find that and add it to the active station
                    if (nextExists) {
                        // Find the next station in the stations vector
                        auto next = std::find_if(stations.begin(), stations.end(), [=](const Workstation *station) {
                            return nextStationString == station->getItemName();
                        });
                        (*active)->setNextStation(*next);
                    } else {
                        (*active)->setNextStation(nullptr);
                    }
                }

                /*
                 * After adding all the records, we need to find the first station
                 */

                /*
                 * For each station in the active line, we compare with the entire vector.
                 * If NONE OF the stations in the line, = the current station in the outer loop, the method will return
                 * true, meaning none of the stations next station == the outer station which also means its the first
                 * node. If any of the stations in the none_of loop do = the station in the outer loop, the lambda returns
                 * false. (This can also be done by doing !std::any_of, but none of just makes more sense)
                 */
                std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
                    if (std::none_of(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* other){return other->getNextStation() == station;})) {
                        m_firstStation = station;
                    };
                });

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
            // This works because each time we add a new item, its added to the back of the vector, so each
            // station that is pointed to by the prior one will be at the end of the vector
            auto next = temp.back()->getNextStation();
            temp.push_back(next);

            // Do this till the item at the end points to nothing indicating the last node
        } while(temp.back()->getNextStation() != nullptr);

        // Assign the active line to the ordered vector
        m_activeLine = temp;
    };

    bool LineManager::run(std::ostream &os) {

        // Keeps track of how many times we run this function
        static size_t functionCalls = 0;

        // Increments on every call
        functionCalls++;

        os << "Line Manager Iteration: " << functionCalls << std::endl;

        // If the pending vector is not empty move the element at the front of the pending to the first station
        // also remove it from the pending since its now being fullfilled
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        };

        // Fill each order from the start of the active line to the end
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
            station->fill(os);
        });

        // Attempt to move each order
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
           station->attemptToMoveOrder();
        });

        // If the number of cust orders = number of filled and not filled, we return true
        return (m_cntCustomerOrder == g_completed.size() + g_incomplete.size());
    };

    void LineManager::display(std::ostream &os) const {
        // For each station, call the display function
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* station){
            station->display(os);
        });
    };
}