#ifndef CABLE_H
#define CABLE_H

#include "wire_connection.h"

namespace domain {

class Cable
{
public:
    Cable();

    void AddConnection(const WireConnection& connection);

    void Clear();

    std::optional<const QList<int>*> GetDestinationPins(int fromPin) const {
        foreach (const auto& conn, connections_) {
            if (conn.GetFrom() == fromPin) {
                return conn.GetTo();
            }
        }
        return std::nullopt;
    }

    qsizetype GetConnectionsCount();

    int GetCircuitsCount();

    const auto& GetConnection(int i) const {
        return connections_[i];
    }

private:
    QList<WireConnection> connections_;
};

} // namespace domain

#endif // CABLE_H
