#pragma once

#include <utility>

class Coord {

public:
    Coord() : m_coord(std::pair<int, int>()) {}
    Coord(int row, int col) : m_coord(std::pair<int, int>(row, col)) {}

    inline int Row() const { return m_coord.first; }
    inline int Col() const { return m_coord.second; }

    inline bool operator< (const Coord& other) const { return m_coord < other.m_coord; }
    inline bool operator==(const Coord& other) const { return m_coord == other.m_coord; }
    inline bool operator!=(const Coord& other) const { return m_coord != other.m_coord; }

private:
    std::pair<int, int> m_coord;

};
