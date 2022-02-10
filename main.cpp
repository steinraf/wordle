#include "src/Game.h"
#include "src/Solver.h"


int main() {

    Timer t;

    benchmark_solver(10000);

    std::cout << "Time to execute was " << t.elapsed() << " seconds";

    return EXIT_SUCCESS;
}
