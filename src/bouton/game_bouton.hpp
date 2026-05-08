#ifndef GAME_BOUTTON_HPP
#define GAME_BOUTTON_HPP

#include "boutton.hpp"
#include <iostream>

class BouttonLevelUp : public Boutton {
public:
    using Boutton::Boutton;
    void action() override {
        std::cout << "Action : Ameliorer la tour !" << std::endl;
    }
};

class BouttonVendre : public Boutton {
public:
    using Boutton::Boutton;
    void action() override {
        std::cout << "Action : Tour vendue !" << std::endl;
    }
};

class BouttonVague : public Boutton {
public:
    using Boutton::Boutton;
    void action() override {
        std::cout << "Action : Prochaine vague !" << std::endl;
    }
};

#endif