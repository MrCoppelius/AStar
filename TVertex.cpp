#include "TVertex.h"

TVertex::TVertex() {
}


TVertex::TVertex(int64_t id, double latitude, double longitude) {
    (*this).id = id;
    (*this).latitude = latitude;
    (*this).longitude = longitude;

}

void TVertex::clear() {
    neighbors.clear();
}

bool operator<(const TVertex& lhs, const TVertex& rhs) {
    return lhs.id < rhs.id;
}
bool operator>(const TVertex& lhs, const TVertex& rhs) {
    return rhs.id < lhs.id;
}
bool operator<=(const TVertex& lhs, const TVertex& rhs) {
    return !(lhs > rhs);
}
bool operator>=(const TVertex& lhs, const TVertex& rhs) {
    return !(lhs < rhs);
}
bool operator==(const TVertex& lhs, const TVertex& rhs) {
    return lhs.id == rhs.id;
}
bool operator<(const TVertex& lhs, const int64_t id) {
    return lhs.id < id;
}
bool operator>(const TVertex& lhs, const int64_t id) {
    return id < lhs.id;
}
bool operator<=(const TVertex& lhs, const int64_t id) {
    return !(lhs > id);
}
bool operator>=(const TVertex& lhs, const int64_t id) {
    return !(lhs < id);
}
bool operator==(const TVertex& lhs, const int64_t id) {
    return lhs.id == id;
}

TVertex::~TVertex() {
}
