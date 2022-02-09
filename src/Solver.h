//
// Created by steinraf on 09/02/2022.
//

#pragma once

#include "Game.h"
#include "Statistics.h"

class Solver {
private:
    const Game &game;

    Statistics stats;

public:
    Solver(const Game &g);

    unsigned solve(bool should_output = false);
    std::string find_ideal_word();
    void filter_statistics(const std::string &response, const std::string &best_guess);
};

