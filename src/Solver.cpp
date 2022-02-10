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
        for(size_t j = 0; j < hist.size(); ++j){
            char g = hist[j].first; //histogram entry with the highest occurrence
            if(!best_word.contains(g)){ //try to avoid duplicates
                if(hist[j].second == 0) { //when avoiding dupes is impossible, use highest char
                    j = 0;
                    g = hist[0].first;
                }
                if(local_stats.filter([g](const std::string &str){
                    return str.contains(g);
                }) >= 1){ //check if adding char results in at least one valid word
                    c = g;
                    break;
                }
            }
        }
    }

    return local_stats.valid_guess(); //return one of the valid guesses
}

void Solver::filter_statistics(const std::string &response, const std::string &best_guess) {
    for(unsigned int i = 0; i < 5; ++i){
        size_t status;
        switch(response[i]){
            break;case '2': //Char is at correct location
                status = stats.filter([&best_guess, &i](const std::string& str){
                    bool a = str[i] == best_guess[i];
                    return str[i] == best_guess[i];
                });
                break;case '1': //Char is valid but at incorrect location
                status = stats.filter([&best_guess, &i](const std::string& str){
                    bool a = str[i] != best_guess[i] && str.contains(best_guess[i]);
                    return str[i] != best_guess[i] && str.contains(best_guess[i]);
                });
                break;case '0': //Char not in word
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
    throw std::runtime_error("NumIterator overflowed");
}

void benchmark_solver(unsigned int num_iterations){

    Histogram<unsigned int, unsigned int> histogram;

#pragma omp parallel for // run iterations in parallel
    for(unsigned int i = 0; i < num_iterations; ++i){
        Game wordle;
        Solver solver{wordle};
        unsigned tmp = solver.solve(false);

    #pragma omp critical
        { //prevent race conditions
        histogram.add(tmp, 1);
        }
    }
    std::cout << histogram;
}


