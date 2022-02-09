//
// Created by steinraf on 09/02/2022.
//

#include "Solver.h"

std::ostream & operator<<(std::ostream& out, std::vector<std::pair<char, unsigned int> > hist){
    for(const auto& pair : hist){
        out << "(" << pair.first << "," << pair.second << ")\n";
    }
    return out;
}

Solver::Solver(const Game &g)
    :game(g), stats{}{

}

std::string Solver::find_ideal_word() {
    Statistics local_stats = stats;
    std::string best_word = "_____";
    for(auto &c : best_word){
        auto hist = local_stats.histogram();
        bool found_char = false;
        for(size_t j = 0; j < hist.size(); ++j){

            char g = hist[j].first;
            if(!best_word.contains(g)){
                if(hist[j].second == 0) {
                    if(!found_char) continue;
                    j = 0;
                    g = hist[0].first;
                }else{
                    found_char = true;
                }
                if(local_stats.filter([g](const std::string &str){
                    return str.contains(g);
                }) > 0){
                    c = g;
                    break;
                }

            }
        }
    }

    return local_stats.valid_guess();
}

void Solver::filter_statistics(const std::string &response, const std::string &best_guess) {
    for(unsigned int i = 0; i < 5; ++i){
        size_t status;
        switch(response[i]){
            break;case '2':
                status = stats.filter([&best_guess, &i](const std::string& str){
                    bool a = str[i] == best_guess[i];
                    return str[i] == best_guess[i];
                });
                break;case '1':
                status = stats.filter([&best_guess, &i](const std::string& str){
                    bool a = str[i] != best_guess[i] && str.contains(best_guess[i]);
                    return str[i] != best_guess[i] && str.contains(best_guess[i]);
                });
                break;case '0':
                status = stats.filter([&best_guess, &i](const std::string& str){
                    bool a = !str.contains(best_guess[i]);
                    return !str.contains(best_guess[i]);
                });
                break;
        }
        assert(status != -1);
    }
}


unsigned int Solver::solve(bool should_output){
    unsigned num_iter = 0;
    while(++num_iter){

        std::string best_guess = find_ideal_word();

        if(should_output) std::cout << "Guessing " << best_guess <<'\n';

        auto response = game.guess(best_guess);

        if(response == "22222") return num_iter;

        filter_statistics(response, best_guess);
    }

}