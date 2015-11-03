#include <iostream>

#include "config.h"
#include "City.h"

int main() {
    City* city = new City();
    for (unsigned int i = 0; i < MAX_EVENTS;) {
        unsigned short j;
        for (j = 0; j < MAX_SENSORS; j++)
            city->addEvent(j, (unsigned short) (j % 4), 4, 30, 23, 59, 5);
        i += j;
    }

    city->displaySensorStateStats(1348);
    bool b = false;
    std::cin >> b;
    return 0;
}