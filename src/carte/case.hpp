#pragma once

// on peut rajouter des Type a notre convenance 
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