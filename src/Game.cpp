//
// Created by steinraf on 09/02/2022.
//

#include "Game.h"

std::random_device Game::rd;
std::mt19937 Game::gen(rd());

std::uniform_int_distribution<> Game::distrib{0, num_answers - 1};

Game::Game()
    : correct_guess{answers[distrib(gen)]}    {

}

bool Game::valid_guess(const std::string& g) const{
    for(auto c : answers){
        if(c == g) return true;
    }
    for(auto c : valid_guesses){
        if(c == g) return true;
    }
    return false;
}


std::string Game::guess(const std::string &g) const{
    if(!valid_guess(g)){
        //std::cout << "Invalid guess, try again.\n";
        return "-----";
    }
    if(g == correct_guess){
        //std::cout << "Congrats, the correct solution was " << correct_guess;
        return "22222";
    }
    std::string ret(5, '0');
    for(auto i = 0; i < 6; ++i){
        if(g[i] == correct_guess[i]) ret[i] = '2';
        else if(correct_guess.contains(g[i])) ret[i] = '1';
    }
//    std::cout << ret  << " " << correct_guess << "\n";
    ++num_guesses;
    return ret;
}

