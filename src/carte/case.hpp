#pragma once

enum class CaseType {
    Wall,
    Chemin,
    Spawn,
    Base,
    TowerSpace
};

struct Case {
    CaseType type;
    int x; 
    int y;
};