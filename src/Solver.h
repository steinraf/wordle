//
// Created by steinraf on 09/02/2022.
//

#pragma once

#include "Game.h"
#include "Statistics.h"

#include <chrono>

void benchmark_solver(unsigned int num_iterations);

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

class Timer{
private:
    std::chrono::time_point<std::chrono::steady_clock> start { std::chrono::steady_clock::now() };

public:
    double elapsed() const{
        return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1> >>
            (std::chrono::steady_clock::now() - start).count();
    }
};




