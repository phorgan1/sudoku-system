 This project implements a C++ template library for creating representing and solving sudoku boards. Two solvers are included, a brute force solver that will solve any valid puzzle, and a heuristic solver that uses the kinds of techniques that a person would use to solve most puzzles. Since there exists at least one extant puzzle that no one's heuristic solver has solved, until a possible breakthrough in the science, there is no guarantee that the heuristic solver will complete. If there's no progress after trying all techniques in a pass through the puzzle, the heuristic solver will quit. There are heuristic solvers that solve more puzzles than this one, but it is quite competitive. If you want to extend it, I would love that:)

Just include sudoku.h to use it. Example use follows and lots of example code is included in the repository.

Example use follows:

    #include <iostream>
    #include <iomanip>
    #include "sudoku.h"
    void
    print_counts(board<9> &b)
    {
	std::cout << "counts:\n";
	std::cout << std::setw(16) << "naked single: " << std::setw(3) << b.get_strategy_count("naked single") << '\n';
	std::cout << std::setw(16) << "hidden single: " << std::setw(3) << b.get_strategy_count("hidden single") << '\n';
	std::cout << std::setw(16) << "intersection: " << std::setw(3) << b.get_strategy_count("intersection") << '\n';
	std::cout << std::setw(16) << "naked double: " << std::setw(3) << b.get_strategy_count("naked double") << '\n';
	std::cout << std::setw(16) << "hidden double: " << std::setw(3) << b.get_strategy_count("hidden double") << '\n';
	std::cout << std::setw(16) << "naked triple: " << std::setw(3) << b.get_strategy_count("naked triple") << '\n';
	std::cout << std::setw(16) << "hidden triple: " << std::setw(3) << b.get_strategy_count("hidden triple") << '\n';
	std::cout << std::setw(16) << "naked quad: " << std::setw(3) << b.get_strategy_count("naked quad") << '\n';
	std::cout << std::setw(16) << "hidden quad: " << std::setw(3) << b.get_strategy_count("hidden quad") << '\n';
	std::cout << std::setw(16) << "x-wing: " << std::setw(3) << b.get_strategy_count("x-wing") << '\n';
	std::cout << std::setw(16) << "swordfish: " << std::setw(3) << b.get_strategy_count("swordfish") << '\n';
	std::cout << std::setw(16) << "jellyfish: " << std::setw(3) << b.get_strategy_count("jellyfish") << '\n';
	std::cout << std::setw(16) << "y-wing: " << std::setw(3) << b.get_strategy_count("y-wing") << '\n';
    }
    int
    main()
    {
	board<9> b( "000" "079" "065"
		    "000" "003" "002"
		    "005" "060" "093"
	b.print_large();
	b.heuristic_solution();
	print_counts(b); 
	b.print_large();
    }
