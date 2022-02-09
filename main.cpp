

#include "src/Game.h"
#include "src/Solver.h"


int main() {

    std::map<unsigned int, unsigned int> m;
    unsigned int win_rate = 0, num_iter = 100;
#pragma omp parallel for
    for(unsigned int i = 0; i < num_iter; ++i){
        Game wordle;

        Solver solver{wordle};
        unsigned tmp = solver.solve(false);
#pragma omp critical
        {
            ++m[tmp];
            if(tmp <= 6) ++win_rate;
        }

    }
    std::cout << "Winrate of " << win_rate * 100.0 / num_iter << "%\n";
    unsigned avg = 0;
    for(auto[key, value] : m){
        avg += key*value;
        std::cout << key << "\t:" << std::string(std::ceil(value*100/num_iter), '-') << '\n';
    }
    std::cout << "Total average of " << avg*1.0/num_iter;

    return EXIT_SUCCESS;
}
