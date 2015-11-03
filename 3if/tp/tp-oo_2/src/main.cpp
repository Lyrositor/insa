#include <iostream>
#include <string>
#include "City.h"
#include "Event.h"

int main () {
    City* city = new City();
    std::string command;
    for (;;) {
        if (std::cin.eof())
            break;
        std::cin >> command;

        // ADD <id> <yyyy> <mm> <dd> <h> <m> <d7> <trafic>
        // Adds a new event to the city's list of events.
        if (command == "ADD") {
            // Get the input params.
            unsigned int sensorId;
            unsigned short year, month, day, hour, minute, day7;
            unsigned char state;
            std::cin >> sensorId;
            std::cin >> year >> month >> day >> hour >> minute >> day7;
            std::cin >> state;

            // Check for errors.
            if (year != YEAR || month < START_MONTH || month > END_MONTH
                    || day < 1 || day > MONTH_DAYS[month - START_MONTH]
                    || hour > 23 || minute > 59 || day7 < 1 || day7 > 7)
                continue;
            unsigned short stateNum = 4;
            for (unsigned short i = 0; i < 4; i++)
                if (STATES[i] == state) {
                    stateNum = i;
                    break;
                }
            if (stateNum == 4)
                continue;

            // Save the event.
            city->addEvent(
                    sensorId, stateNum, month, day, hour, minute,
                    (unsigned short) (day7 - 1));

        // STATS_C <idCaptor>
        // Displays the statistics for a specific sensor.
        } else if (command == "STATS_C") {
            unsigned int sensorId;
            std::cin >> sensorId;
            city->displaySensorStateStats(sensorId);

        // JAM_DH <D7>
        // Displays the statistics for traffic jams per week-day and per hour.
        } else if (command == "JAM_DH") {
            unsigned short day7;
            std::cin >> day7;
            if (day7 < 1 || day7 > 7)
                continue;
            city->displayDayTrafficJamStats((unsigned short) (day7 - 1));

        // STATS_D7 <D7>
        // Displays the statistics for a day of the week.
        } else if (command == "STATS_D7") {
            unsigned short day7;
            std::cin >> day7;
            if (day7 < 1 || day7 > 7)
                continue;
            city->displayDayStateStats((unsigned short) (day7 - 1));

        // OPT <D7> <H_start> <H_end> <seg_count> <seg_1> ... <seg_n>
        // Displays the optimal departure time for a journey.
        } else if (command == "OPT") {
            unsigned short day7, hStart, hEnd;
            unsigned int segCount;
            std::cin >> day7 >> hStart >> hEnd >> segCount;
            unsigned int* segments = new unsigned int[segCount];
            for (unsigned int i = 0; i < segCount; i++)
                std::cin >> segments[i];
            if (day7 < 1 || day7 > 7 || hStart > 23 || hEnd > 23)
                continue;
            city->displayOptimalDepartureTime(
                    (unsigned short) (day7 - 1), hStart, hEnd, segCount,
                    segments);
            delete[] segments;

        // EXIT
        // Closes the application.
        } else if (command == "EXIT")
            break;
    }
    delete city;
    return 0;
}

