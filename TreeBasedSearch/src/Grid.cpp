#include "Grid.h"

constexpr char EMPTY_CHAR = (char)250;
constexpr char WALL_CHAR = (char)254;
constexpr char AGENT_CHAR = (char)175;
constexpr char GOAL_CHAR = (char)237;

void Grid::load(std::vector<std::string>& lines) {

    // Grid size
    std::string mapSizeStr = get_string_between(lines[0], '[', ']');
    std::vector<std::string> mapSize = string_split(mapSizeStr, ',');
    int rows = stoi(mapSize[0]);
    int cols = stoi(mapSize[1]);
    m_size = Coord(rows, cols);

    // Agent position
    std::string agentPosStr = get_string_between(lines[1], '(', ')');
    std::vector<std::string> agentPos = string_split(agentPosStr, ',');
    int agentCol = stoi(agentPos[0]);
    int agentRow = stoi(agentPos[1]);
    m_agentPosition = Coord(agentRow, agentCol);

    // Goal positions
    std::vector<std::string> goalPosStrings = string_split(lines[2], '|');
    for (std::string goalPosStrRaw : goalPosStrings) {
        std::string goalPosStr = get_string_between(goalPosStrRaw, '(', ')');
        std::vector<std::string> goalPos = string_split(goalPosStr, ',');
        int goalCol = stoi(goalPos[0]);
        int goalRow = stoi(goalPos[1]);
        m_goalPositions.push_back(Coord(goalRow, goalCol));
    }

    // Initialise grid nodes as all empty
    for (int i = 0; i < rows; i++) {
        m_nodes.push_back(std::vector<CellType>());
        for (int j = 0; j < cols; j++) {
            m_nodes[i].push_back(CellType::empty);
        }
    }

    // Add walls to grid nodes
    for (size_t i = 3; i < lines.size(); i++) {
        std::string wallBoundsStr = get_string_between(lines[i], '(', ')');
        std::vector<std::string> wallBounds = string_split(wallBoundsStr, ',');
        int wallCol = stoi(wallBounds[0]);
        int wallRow = stoi(wallBounds[1]);
        int wallWidth = stoi(wallBounds[2]);
        int wallHeight = stoi(wallBounds[3]);
        for (int j = wallRow; j < wallRow + wallHeight; j++) {
            for (int k = wallCol; k < wallCol + wallWidth; k++) {
                m_nodes[j][k] = CellType::wall;
            }
        }
    }

}

std::vector<std::string> Grid::to_string() {

    std::vector<std::string> result;

    for (size_t row = 0; row < m_nodes.size(); row++) {
        std::string line;
        for (size_t col = 0; col < m_nodes[0].size(); col++) {
            char character = EMPTY_CHAR;
            if (agent_at(row, col))
                character = AGENT_CHAR;
            else if (goal_at(row, col))
                character = GOAL_CHAR;
            else if (m_nodes[row][col] == CellType::wall)
                character = WALL_CHAR;
            line.push_back(character);
            line.push_back(' ');
        }
        result.push_back(line);
    }

    return result;

}

std::vector<Coord> Grid::get_movable_coords(Coord pos) {

    std::vector<Coord> result;

    Coord up = Coord(pos.Row() - 1, pos.Col());
    Coord left = Coord(pos.Row(), pos.Col() - 1);
    Coord down = Coord(pos.Row() + 1, pos.Col());
    Coord right = Coord(pos.Row(), pos.Col() + 1);

    if (pos_available(up.Row(), up.Col()))
        result.push_back(up);
    if (pos_available(left.Row(), left.Col()))
        result.push_back(left);
    if (pos_available(down.Row(), down.Col()))
        result.push_back(down);
    if (pos_available(right.Row(), right.Col()))
        result.push_back(right);

    return result;

}

std::map<StepType, Coord> Grid::get_movable_steps(Coord pos) {

    std::map<StepType, Coord> result;

    Coord up = Coord(pos.Row() - 1, pos.Col());
    Coord left = Coord(pos.Row(), pos.Col() - 1);
    Coord down = Coord(pos.Row() + 1, pos.Col());
    Coord right = Coord(pos.Row(), pos.Col() + 1);

    if (pos_available(up.Row(), up.Col()))
        result.insert({ StepType::Up, up });
    if (pos_available(left.Row(), left.Col()))
        result.insert({ StepType::Left, left });
    if (pos_available(down.Row(), down.Col()))
        result.insert({ StepType::Down, down });
    if (pos_available(right.Row(), right.Col()))
        result.insert({ StepType::Right, right });

    return result;

}

bool Grid::is_goal_position(Coord node) {

    return vector_contains(m_goalPositions, node);

}

bool Grid::agent_at(int row, int col) {

    return m_agentPosition == Coord(row, col);

}

bool Grid::goal_at(int row, int col) {

    Coord coord = Coord(row, col);

    for (Coord goalPos : m_goalPositions) {
        if (goalPos == coord)
            return true;
    }

    return false;

}

bool Grid::pos_available(int row, int col) {

    if (row < 0 || row >= m_size.Row() || col < 0 || col >= m_size.Col())
        return false;

    return m_nodes[row][col] == CellType::empty;

}
