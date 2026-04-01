#ifndef WIRE_CONNECTION_H
#define WIRE_CONNECTION_H

#include "qlist.h"

namespace domain {

class WireConnection {
public:
    WireConnection() = default;

    void SetFrom(int pin) {
        fromPin = pin;
    }

    template<typename... Args>
    void SetTo(Args... pins) {
        toPins = {pins...};
    }

    void AddTo(int pin) {
        toPins.append(pin);
    }

    int GetFrom() const {
        return fromPin;
    }

    auto GetTo() const {
        return &toPins;
    }

    void Clean() {
        fromPin = 0;
        toPins = {};
    }

private:
    int fromPin;
    QList<int> toPins;
};

} //namespace domain;


#endif // WIRE_CONNECTION_H
