//
// Created by steinraf on 09/02/2022.
//

#include "Statistics.h"


size_t Statistics::filter(std::function<bool(const std::string&)> pred){
    std::vector<Word> tmp{};
    for(auto word : possible_guesses){
        if(pred(word)) tmp.push_back(word);
    }
    if(tmp.size() == 0) return 0;
    possible_guesses = tmp;
    return possible_guesses.size();
}

std::vector<std::pair<char, unsigned int>> Statistics::histogram(){
    std::map<char, int> m{};
    for(const std::string& str : possible_guesses){
        for(const char& c : str){
            ++m[c];
        }
    }
    std::vector<std::pair<char, unsigned int>> res{};
    for(char c = 'a'; c <= 'z'; ++c){
        res.push_back({c, m[c]});
    }
    std::sort(res.begin(), res.end(), [](auto a, auto b){
        return a.second > b.second;
    });
    return res;
}