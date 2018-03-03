#pragma once
#include <cstdlib>
#include <cstdint>
#include <vector>



class TVertex {
public:
    TVertex();
    TVertex(int64_t, double, double);
    int64_t id;
    double latitude;
    double longitude;
    void clear();
    std::vector<std::pair<int64_t, double>> neighbors;
    friend bool operator<(const TVertex& lhs, const TVertex& rhs);
    friend bool operator>(const TVertex& lhs, const TVertex& rhs);
    friend bool operator<=(const TVertex& lhs, const TVertex& rhs);
    friend bool operator>=(const TVertex& lhs, const TVertex& rhs);
    friend bool operator==(const TVertex& lhs, const TVertex& rhs);
    friend bool operator<(const TVertex& lhs, const int64_t id);
    friend bool operator>(const TVertex& lhs, const int64_t id);
    friend bool operator<=(const TVertex& lhs, const int64_t id);
    friend bool operator>=(const TVertex& lhs, const int64_t id);
    friend bool operator==(const TVertex& lhs, const int64_t id);
    ~TVertex();
};

