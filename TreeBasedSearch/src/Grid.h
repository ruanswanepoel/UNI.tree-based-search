#pragma once

#include <vector>
#include <string>
#include <map>

#include "StepType.h"
#include "Coord.h"
#include "Helpers.h"

/// <summary>
/// A grid of inididual nodes/cells that are defined as either empty cells or walls.
/// Also keeps track of agent and goal positions.
/// </summary>
class Grid {

public:
    /// <summary>
    /// Initialises and loads this grid's configuration based on the given
    /// lines of instructions.
    /// </summary>
    /// <param name="lines">Lines of instructions.</param>
    void Load(std::vector<std::string>& lines);
    std::vector<std::string> ToString();

    inline Coord GetAgentPosition() const { return m_agentPosition; }
    inline bool IsGoalPosition(Coord node) { return vector_contains(m_goalPositions, node); }

    std::vector<Coord> GetNeighboringEmptyCoords(Coord);
    StepType GetStepDirection(Coord, Coord);

    inline void SetNodeAsPath(Coord node) { m_nodes[node.Row()][node.Col()] = CellType::path; }

    enum class CellType { empty, wall, path };

private:
    Coord m_size;                                   // rows, cols
    Coord m_agentPosition;                          // row, col
    std::vector<Coord> m_goalPositions;             // row, col
    std::vector<std::vector<CellType>> m_nodes;     // rows * cols

    inline bool agent_at(int row, int col) { return m_agentPosition == Coord(row, col); }
    bool goal_at(int row, int col);
    bool pos_available(int row, int col);

};
