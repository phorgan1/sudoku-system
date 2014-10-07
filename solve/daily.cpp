#include <iostream>
#include <sudoku.h>

const size_t sz=9;
void
print_counts(board<sz> &b)
{
    std::cout << "  counts:\n";
    std::cout << "   naked single: " << b.get_strategy_count("naked single") << '\n';
    std::cout << "   hidden single: " << b.get_strategy_count("hidden single") << '\n';
    std::cout << "   intersection: " << b.get_strategy_count("intersection") << '\n';
    std::cout << "   naked double: " << b.get_strategy_count("naked double") << '\n';
    std::cout << "   hidden double: " << b.get_strategy_count("hidden double") << '\n';
    std::cout << "   naked triple: " << b.get_strategy_count("naked triple") << '\n';
    std::cout << "   hidden triple: " << b.get_strategy_count("hidden triple") << '\n';
    std::cout << "   naked quad: " << b.get_strategy_count("naked quad") << '\n';
    std::cout << "   hidden quad: " << b.get_strategy_count("hidden quad") << '\n';
    std::cout << "   x-wing: " << b.get_strategy_count("x-wing") << '\n';
    std::cout << "   y-wing: " << b.get_strategy_count("y-wing") << '\n';
    std::cout << "   swordfish: " << b.get_strategy_count("swordfish") << '\n';
    std::cout << "   jellyfish: " << b.get_strategy_count("jellyfish") << '\n';
    std::cout << "   xy-chain: " << b.get_strategy_count("xy-chain") << '\n';
}

int
main()
{
    struct test
    {
	std::string tst;
	std::string diff;
	std::string name;
	std::string copyright;
    };
    std::vector<struct test> vtests={
	{ "....1...349.......7.1624...16....54.3.9...2.1.87....96...1739.2.......352...5....", "1 star", "", "Knight Features"},
	{ "8...5.2.....7...8..1.2...7.6.19.....79.5.2.18.....76.3.6...8.4..2...5.....5.3...1", "2 star", "", "Knight Features" },
	{ "1....5.....9.67..5..6..37.4.7...9..1..1.5.3..2..1...5.9.56..2..4..53.1.....4....8", "2 star", "", "Knight Features" },
	{ "....9876.9..7..4..72..4....5......3.8.1...2.6.3......7....2..53..4..3..1.7586....", "3 star", "", "Knight Features"},
	{ ".79.2.3.8..2..1..4.3..8.2....5.7...6.4.....2.9...4.8....8.9..5.4..5..7..2.7.6.49.", "3 star", "", "Knight Features" },
	{ "6....2.9.5..6....42.74..8......681...7.....5...297......1..74.87....9..2.2.1....5", "3 star", "", "Knight Features"},
	{ ".4.9...72....7.9..1.....4..73..1.5..8..6.3..7..9.2..34..6.....3..3.4....97...8.4.", "3 star", "", "Knight Features"},
	{ "..8..7...6.....7.9...4.3...4.5....31.3.5.6.2.72....5.4...8.1...3.9.....2...9..1..", "4 star", "", "Knight Features"},
	{ ".76...3..........5....72.61...721...1.23.58.7...869...72.59....3..........9...17.", "4 star", "", "Knight Features"},
	{ "....35...3.1.....8..59...7.2.9..1.3.1.......5.4.8..6.2.9...27..6.....2.9...34....", "4 star", "", "Knight Features"},
	{ "6..7....2.3168...9.....1..5..8......3..458..7......4..8..9.....4...3792.7....2..6", "4 star", "", "Knight Features"},
	{ "92.....4...8.295........7....98.4..5.5.....9.7..5.32....3........496.3...7.....81", "4 star", "", "Knight Features"},
	{ "2...7..3.5..2....8.6...4.....781..9..21...85..9..426.....4...6.7....8..9.1..9...2", "4 star", "", "Knight Features"},
	{ ".7..2...338.7.4.....4...5...52.41...............57.28...6...7.....8.3.191...6..5.", "4 star", "", "Knight Features"},
	{ ".6.19.8..4.2.......8...3...7.8......93..4..87......3.9...3...4.......6.5..7.21.3.", "5 star", "", "Knight Features" },
	{ "4.......5....35.67...6..94.5.1..8....9.....5....7..3.2.19..7...23.84....7.......6", "5 star", "", "Knight Features" },
	{ "....4316..6....2..2.36.....1..4.6.2..5..2..1..7.8.5..4.....74.1..7....5..9153....", "5 star", "", "Knight Features" },
	{ "..45......8.1.47....7.9..3..69.4...8...3.2...2...1.47..5..6.9....39.7.6......15..", "5 star", "", "Knight Features" },
	{ ".73.8.....9............341.52..3...17..1.9..69...6..74.629............9.....4.62.", "5 star", "", "Knight Features" },
	{ "64...2.9...3.7.64.9............43.1.2..6.5..8.3.79............7.28.3.5...6.1...83", "5 star", "", "Knight Features" },
	{ "95.....2.....3.9.....1....6..8..241...7...2...957..6..8....1.....4.6.....2.....73", "5 star", "", "Knight Features" },
	{ "0....56....5.........81...47..4.1.6..36.2.49..4.9.8..74...89.........1....81....3", "5 star", "", "Knight Features" },
	{ "...1...6....4..2...6879..4...681...5.91...42.3...296...5..4873...9..7....7...1...", "5 star", "", "Knight Features" },
	{ ".2..4..1..51..8...8.....4....7..65...8.279.6...65..9....2.....7...7..15..3..1..9.", "5 star", "", "Knight Features" },
	{ "45...3......7..8.52....9.4...281..3.8.......7.4..751...9.5....33.4..7......3...76", "5 star", "", "Knight Features" },
	{ "....8.2....7.14...1......4.9.1..2..53.......27..6..9.8.4......7...92.6....3.5....", "5 star", "", "Knight Features" },
	{ "....6...24...156.....7...9....6..1.7.7.....8.3.6..9....5...8.....149...38...5....", "5 star", "", "Knight Features" },
	{ ".615..97..27.4...535..76....43.....9.........6.....24....75..911...6.73..74..356.", "6 star", "", "Knight Features" },
	{ "..93.5....3..9.5.....4....7.6..52.9.9.3...7.2.4.63..1.1....4.....4.2..5....8.34..", "6 star", "", "Knight Features" },
	{ "........3.9.1.674.7.43..69.5...12..4.........4..86...7.43..18.2.679.8.3.8........", "6 star", "", "Knight Features" },
	{ "..6.9..7..9.7..4.11....5.9...4..3.2...8.4.7...6.5..1...3.2....77.1..6.8..4..8.9..", "6 star", "", "Knight Features" },
	{ "..46.3..83..4...1.8.6.1.....2..67.9...........7.54..8.....7.9.3.6...1..57..8.61..", "6 star", "", "Knight Features" },
	{ "39...1........24.6.....6.8.2.4....789.......385....6.2.7.8.....4.35........3...64", "6 star", "", "Knight Features" },
	{ ".2..7...4.....8219.4.9..5.3.654.3...............7.935.5.8..6.4.2948.....6...3..2.", "6 star", "", "Knight Features" },
	{ "..318.947......5.8...5...62...3....923..7..158....4...96...1...3.2......158.396..", "6 star", "", "Knight Features" }

    };
    for(size_t ctr=0;ctr<vtests.size();ctr++){
	board<sz> *b=new board<sz>(vtests[ctr].tst);
	b->print();
	b->heuristic_solution();
	b->print();
	if(!b->get_valid()){
	    std::cout << "Bad puzzle\n";
	}else if(b->is_solved()){
	    std::cout << "Valid solved puzzle\n";
	}else{
	    std::cout << "Valid but not solved puzzle\n";
	}
	b->print_large();
	std::cout << "Copyright: '" << vtests[ctr].copyright << "', Difficulty " << vtests[ctr].diff << '\n';
	print_counts(*b);
	std::cout << "count: " << b->count() << '\n';
	std::cout << "get_count: " << b->get_count() << '\n';
	std::cout << std::endl;
    }
    exit(0);
}
