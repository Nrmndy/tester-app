#include "cable.h"

namespace domain {

Cable::Cable() {}

void Cable::AddConnection(const WireConnection &connection) {
    connections_.push_back(std::move(connection));
}

void Cable::Clear() {
    connections_.clear();
}

qsizetype Cable::GetConnectionsCount() {
    return connections_.count();
}

int Cable::GetCircuitsCount() {
    int counter = 0;
    foreach (const auto& con, connections_) {
        counter += con.GetTo()->count();
    }
    return counter;
}

} // namespace domain
