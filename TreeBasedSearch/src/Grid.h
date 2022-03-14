#pragma once

#include <vector>
#include <string>
#include <map>

#include "StepType.h"
#include "Coord.h"
#include "Helpers.h"

class Grid {

public:
    void load(std::vector<std::string>&);
    std::vector<std::string> to_string();

    std::vector<Coord> get_movable_coords(Coord);
    std::map<StepType, Coord> get_movable_steps(Coord);
    inline Coord get_agent_position() const { return m_agentPosition; }
    bool is_goal_position(Coord);

    enum class CellType { empty, wall };

private:
    Coord m_size;                                   // rows, cols
    Coord m_agentPosition;                          // row, col
    std::vector<Coord> m_goalPositions;             // row, col
    std::vector<std::vector<CellType>> m_nodes;     // rows * cols

    bool agent_at(int, int);
    bool goal_at(int, int);
    bool pos_available(int, int);

};
