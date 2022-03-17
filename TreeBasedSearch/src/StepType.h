#pragma once

enum class StepType {
    Up, Left, Down, Right
};

inline const char* stepTypeToString(StepType st) {

    if (st == StepType::Up)
        return "Up";
    else if (st == StepType::Left)
        return "Left";
    else if (st == StepType::Down)
        return "Down";
    return "Right";

}