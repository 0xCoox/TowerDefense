#pragma once

enum class CaseType {
    Wall,
    Chemin,
    Spawn,
    Base,
    TowerSpace
};

struct Case {
    CaseType type = CaseType::Wall;
    int x = 0;
    int y = 0;
};