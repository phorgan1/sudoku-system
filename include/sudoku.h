#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <initializer_list>
#include <algorithm>
#include <exception>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <cmath>
//#include <sys/time.h>
#include <assert.h>
#include <ncurses.h>


// the escape sequences seen below are recognized by most terminals in linux to
// make text bold and to stop bolding text.  This allows us to give more 
// information, for example when printing a board, we can bold the original 
// numbers given in the puzzle and not numbers found during solution.  If you
// want to capture output in a text file, however, it might look like a bunch
// of gobbledegook in your editor.  At that point you might want to comment
// out the next line.  Alternatively, on linux you can look at it with escape
// escape codes intact with less -R

#define USE_ANSI_ESCAPES
#ifdef USE_ANSI_ESCAPES
    std::string bold		{ "\x1b[1m" };
    std::string unbold		{ "\x1b[22m" };
    std::string toblack		{ "\x1b[0;30m" };
    std::string toyellow	{ "\x1b[1;33m" };
    std::string topurple	{ "\x1b[1;35m" };
    std::string toorange	{ "\x1b[0;33m" };
    std::string toblue		{ "\x1b[0;34m" };
    std::string tored		{ "\x1b[0;31m" };
    std::string togreen		{ "\x1b[0;32m" };
    void
    cursor2(std::ostream& os, size_t row,size_t col)
    {
	os << "\x1b[" << row << ';' << col << 'H';
    }

#else 
    const char *bold="";
    const char *unbold="";
    const char *toyellow="";
    const char *topurple="";
    const char *toorange="";
    const char *toblue="";
    const char *tored="";
    const char *toblack="";
    const char *togreen="";
    void
    cursor2(std::ostream& os, size_t row,size_t col) { }
#endif

//! This enum holds colors for coloring algorithms.
enum color {
    none,
    yellow,
    purple,
    orange,
    blue,
    green,
    red
};
//! holds color names corresponding to the color enum
std::vector<std::string> color_names {
	"none",
	"yellow",
	"purple",
	"orange",
	"blue",
	"green",
	"red"
};

//! convert enum into escape string
/*! given a color enum, returns the ansi escape string that will make
 * that color appear when sent to a terminal
 * \param c the color as an enum
 * \return std::string the escape string to ask the terminal to dislay color
 */
std::string
color2string(color c)
{
    switch(c){
	case color::yellow:
	    return toyellow;
	    break;
	case color::purple:
	    return topurple;
	    break;
	case color::orange:
	    return toorange;
	    break;
	case color::blue:
	    return toblue;
	    break;
	case color::red:
	    return tored;
	    break;
	case color::green:
	    return togreen;
	    break;
	default:
	    return toblack;
	    break;
    }
}

// RESPATH shows all the solution steps if defined
//#define SHOW_RESPATH // N.B. all RESPATH print 1 based, not 0 based
//#define SHOW_RESPATH_PRINT_PUZZLE

// uncomment appropriate SHOW_XXX lines below to see debugging information about
// the corresponding section

//#define SHOW_BRUTE_DEBUG
//#define SHOW_RUNNING_BRUTE_DEBUG
//#define SHOW_BRUTE_CHECK_DEBUG
//#define SHOW_CHECK_PVAL_SET_DEBUG
//#define SHOW_CHOOSE_VAL_DEBUG
//#define SHOW_GENERATE_DEBUG
//#define SHOW_DIG_DEBUG
//#define SHOW_PRUNING_DEBUG
//#define SHOW_BOARD_CONSTRUCT_DEBUG
//#define SHOW_HEURISTIC_DEBUG
//#define SHOW_SUDOKU_METHOD_DEBUG
//#define SHOW_REGISTER_STRATEGY_DEBUG
//#define SHOW_STRATEGY_SORT_LEVEL_DEBUG 
//#define SHOW_VALIDATE_DEBUG

//#define SHOW_NAKED_SINGLE_DEBUG
//#define SHOW_HIDDEN_SINGLE_DEBUG
//#define SHOW_NAKED_DOUBLE_DEBUG
//#define SHOW_HIDDEN_DOUBLE_DEBUG
//#define SHOW_NAKED_TRIPLE_DEBUG
//#define SHOW_HIDDEN_TRIPLE_DEBUG
//#define SHOW_NAKED_QUAD_DEBUG
//#define SHOW_HIDDEN_QUAD_DEBUG
//#define SHOW_INTERSECTION_DEBUG
//#define SHOW_DISCERN_INTERSECTION_DEBUG
//#define SHOW_X_WING_DEBUG
//#define SHOW_Y_WING_DEBUG
//#define SHOW_Y_WING_APPLY_DEBUG
//#define SHOW_SWORDFISH_DEBUG
//#define SHOW_JELLYFISH_DEBUG
//#define SHOW_XY_CHAIN_DEBUG
//#define SHOW_XY_CHAIN_FILT_DEBUG
//#define SHOW_SIMPLE_COLOR_DEBUG
//#define SHOW_SIMPLE_COLOR_LARGE_PRINT_DEBUG

//#define SHOW_HIDDEN_APPLY_DEBUG
//#define SHOW_NAKED_APPLY_DEBUG
//#define SHOW_INTERLOCK_APPLY_DEBUG

//#define SHOW_DISCERN_HIDDEN_DEBUG
//#define SHOW_DISCERN_NAKED_DEBUG
//#define SHOW_DISCERN_INTERLOCK_DEBUG

//#define SHOW_PURGE_BLOCK_EXCEPT_DEBUG
//#define SHOW_PURGE_SET_DEBUG
//#define SHOW_PURGE_FROM_SET_DEBUG
//#define SHOW_REDUCE_TO_SET_DEBUG
//#define SHOW_GENPVALS_DEBUG
//#define SHOW_CLEAR_PVAL_VAL_DEBUG
//#define SHOW_APPLIED_DEBUG

#if defined(SHOW_RESPATH)
#define RESPATH
#else
#define RESPATH if(0)
#endif
#if defined(SHOW_RESPATH_PRINT_PUZZLE)
#if defined(SHOW_RESPATH)
#define RESPATH_PRINT_PUZZLE
#else
#define RESPATH_PRINT_PUZZLE if(0)
#endif
#endif
#if defined(SHOW_VALIDATE_DEBUG)
#define VALIDATE_DEBUG
#else
#define VALIDATE_DEBUG if(0)
#endif
#if defined(SHOW_DISCERN_HIDDEN_DEBUG)
#define DISCERN_HIDDEN_DEBUG
#else
#define DISCERN_HIDDEN_DEBUG if(0)
#endif
#if defined(SHOW_DISCERN_NAKED_DEBUG)
#define DISCERN_NAKED_DEBUG
#else
#define DISCERN_NAKED_DEBUG if(0)
#endif
#if defined(SHOW_DISCERN_INTERLOCK_DEBUG)
#define DISCERN_INTERLOCK_DEBUG
#else
#define DISCERN_INTERLOCK_DEBUG if(0)
#endif
#if defined(SHOW_REDUCE_TO_SET_DEBUG)
#define REDUCE_TO_SET_DEBUG
#else
#define REDUCE_TO_SET_DEBUG if(0)
#endif
#if defined(SHOW_SUDOKU_METHOD_DEBUG)
#define SUDOKU_METHOD_DEBUG
#else
#define SUDOKU_METHOD_DEBUG if(0)
#endif
#if defined(SHOW_REGISTER_STRATEGY_DEBUG)
#define REGISTER_STRATEGY_DEBUG
#else
#define REGISTER_STRATEGY_DEBUG if(0)
#endif
#if defined(SHOW_STRATEGY_SORT_LEVEL_DEBUG)
#define STRATEGY_SORT_LEVEL_DEBUG
#else
#define STRATEGY_SORT_LEVEL_DEBUG if(0)
#endif
#if defined(SHOW_CLEAR_PVAL_VAL_DEBUG)
#define CLEAR_PVAL_VAL_DEBUG
#else
#define CLEAR_PVAL_VAL_DEBUG if(0)
#endif
#if defined(SHOW_PURGE_BLOCK_EXCEPT_DEBUG)
#define PURGE_BLOCK_EXCEPT_DEBUG
#else
#define PURGE_BLOCK_EXCEPT_DEBUG if(0)
#endif
#if defined(SHOW_PURGE_SET_DEBUG)
#define PURGE_SET_DEBUG
#else
#define PURGE_SET_DEBUG if(0)
#endif
#if defined(SHOW_PURGE_FROM_SET_DEBUG)
#define PURGE_FROM_SET_DEBUG
#else
#define PURGE_FROM_SET_DEBUG if(0)
#endif
#if defined(SHOW_BRUTE_DEBUG)
#define BRUTE_DEBUG
#else
#define BRUTE_DEBUG if(0)
#endif
#if defined(SHOW_BRUTE_CHECK_DEBUG)
#define BRUTE_CHECK_DEBUG
#else
#define BRUTE_CHECK_DEBUG if(0)
#endif
#if defined(SHOW_RUNNING_BRUTE_DEBUG)
#define RUNNING_BRUTE_DEBUG
#else
#define RUNNING_BRUTE_DEBUG if(0)
#endif
#if defined(SHOW_CHECK_PVAL_SET_DEBUG)
#define CHECK_PVAL_SET_DEBUG
#else
#define CHECK_PVAL_SET_DEBUG if(0)
#endif
#if defined(SHOW_PRUNING_DEBUG)
#define PRUNING_DEBUG
#else
#define PRUNING_DEBUG if(0)
#endif
#if defined(SHOW_GENPVALS_DEBUG)
#define GENPVALS_DEBUG
#else
#define GENPVALS_DEBUG if(0)
#endif
#if defined(SHOW_CHOOSE_VAL_DEBUG)
#define CHOOSE_VAL_DEBUG
#else
#define CHOOSE_VAL_DEBUG if(0)
#endif
#if defined(SHOW_GENERATE_DEBUG)
#define GENERATE_DEBUG
#else
#define GENERATE_DEBUG if(0)
#endif
#if defined(SHOW_DIG_DEBUG)
#define DIG_DEBUG
#else
#define DIG_DEBUG if(0)
#endif
#if defined(SHOW_NAKED_SINGLE_DEBUG)
#define NAKED_SINGLE_DEBUG
#else
#define NAKED_SINGLE_DEBUG if(0)
#endif
#if defined(SHOW_HIDDEN_SINGLE_DEBUG)
#define HIDDEN_SINGLE_DEBUG
#else
#define HIDDEN_SINGLE_DEBUG if(0)
#endif
#if defined(SHOW_NAKED_DOUBLE_DEBUG)
#define NAKED_DOUBLE_DEBUG
#else
#define NAKED_DOUBLE_DEBUG if(0)
#endif
#if defined(SHOW_HIDDEN_DOUBLE_DEBUG)
#define HIDDEN_DOUBLE_DEBUG
#else
#define HIDDEN_DOUBLE_DEBUG if(0)
#endif
#if defined(SHOW_HIDDEN_APPLY_DEBUG)
#define HIDDEN_APPLY_DEBUG
#else
#define HIDDEN_APPLY_DEBUG if(0)
#endif
#if defined(SHOW_NAKED_APPLY_DEBUG)
#define NAKED_APPLY_DEBUG
#else
#define NAKED_APPLY_DEBUG if(0)
#endif
#if defined(SHOW_INTERLOCK_APPLY_DEBUG)
#define INTERLOCK_APPLY_DEBUG
#else
#define INTERLOCK_APPLY_DEBUG if(0)
#endif
#if defined(SHOW_NAKED_TRIPLE_DEBUG)
#define NAKED_TRIPLE_DEBUG
#else
#define NAKED_TRIPLE_DEBUG if(0)
#endif
#if defined(SHOW_HIDDEN_TRIPLE_DEBUG)
#define HIDDEN_TRIPLE_DEBUG
#else
#define HIDDEN_TRIPLE_DEBUG if(0)
#endif
#if defined(SHOW_NAKED_QUAD_DEBUG)
#define NAKED_QUAD_DEBUG
#else
#define NAKED_QUAD_DEBUG if(0)
#endif
#if defined(SHOW_HIDDEN_QUAD_DEBUG)
#define HIDDEN_QUAD_DEBUG
#else
#define HIDDEN_QUAD_DEBUG if(0)
#endif
#if defined(SHOW_INTERSECTION_DEBUG)
#define INTERSECTION_DEBUG
#else
#define INTERSECTION_DEBUG if(0)
#endif
#if defined(SHOW_DISCERN_INTERSECTION_DEBUG)
#define DISCERN_INTERSECTION_DEBUG
#else
#define DISCERN_INTERSECTION_DEBUG if(0)
#endif
#if defined(SHOW_X_WING_DEBUG)
#define X_WING_DEBUG
#else
#define X_WING_DEBUG if(0)
#endif
#if defined(SHOW_Y_WING_DEBUG)
#define Y_WING_DEBUG
#else
#define Y_WING_DEBUG if(0)
#endif
#if defined(SHOW_Y_WING_APPLY_DEBUG)
#define Y_WING_APPLY_DEBUG
#else
#define Y_WING_APPLY_DEBUG if(0)
#endif
#if defined(SHOW_SWORDFISH_DEBUG)
#define SWORDFISH_DEBUG
#else
#define SWORDFISH_DEBUG if(0)
#endif
#if defined(SHOW_JELLYFISH_DEBUG)
#define JELLYFISH_DEBUG
#else
#define JELLYFISH_DEBUG if(0)
#endif
#if defined(SHOW_XY_CHAIN_DEBUG)
#define XY_CHAIN_DEBUG
#else
#define XY_CHAIN_DEBUG if(0)
#endif
#if defined(SHOW_XY_CHAIN_FILT_DEBUG)
#define XY_CHAIN_FILT_DEBUG
#else
#define XY_CHAIN_FILT_DEBUG if(0)
#endif
#if defined(SHOW_SIMPLE_COLOR_DEBUG)
#define SIMPLE_COLOR_DEBUG
#else
#define SIMPLE_COLOR_DEBUG if(0)
#endif
#if defined(SHOW_SIMPLE_COLOR_LARGE_PRINT_DEBUG)
#define SIMPLE_COLOR_LARGE_PRINT_DEBUG
#else
#define SIMPLE_COLOR_LARGE_PRINT_DEBUG if(0)
#endif
#if defined(SHOW_BOARD_CONSTRUCT_DEBUG)
#define BOARD_CONSTRUCT_DEBUG
#else
#define BOARD_CONSTRUCT_DEBUG if(0)
#endif
#if defined(SHOW_HEURISTIC_DEBUG)
#define HEURISTIC_DEBUG
#else
#define HEURISTIC_DEBUG if(0)
#endif
#if defined(SHOW_APPLIED_DEBUG)
#define APPLIED_DEBUG
#else
#define APPLIED_DEBUG if(0)
#endif

#include <random>

//! singleton reference to std::default_random_engine
/*! Singleton source for a std::default_random_engine, so we get a procession
 * of values instead of starting over again and again and again.
 * \return a reference to our static std::default_random_engine
 */
//
std::default_random_engine&
get_engine()
{
    // if we start using threads we will have to control access to this
    // std::default_random_engine is c++11
    static std::default_random_engine e;
    return e;
}

void
inline
seed(unsigned int aseed=0)
{
    /*!
     * seed the random number generator with a seed if passed in, else use
     * a seed derived from the current time.  You are allowed to specify a
     * seed in order to replace randomness with repeatability for debugging.
     * \param aseed 0 means use current time to seed, else use aseed
     */
    if(aseed != 0){
	// if we get passed a seed, then use it
	get_engine().seed(aseed);
    }else{
	// chrono is c++11
	unsigned seed=
	    std::chrono::steady_clock::now().time_since_epoch().count();
	get_engine().seed(seed);
    }
}

int
inline
rand_n(size_t n)
{
    //! return a random number [0,n)
    /*!
     * generate a number between [0,n) as in integer.
     * i.e. if n==7, there's an equal change of returning {0,1,2,3,4,5,6} 
     * \param n the non-inclusive upper bound
     * \return an integer [0,n)
     */
    // uniform_int_distribution is c++11
    std::uniform_int_distribution<int> d(0,n-1);
    return d(get_engine());
}

//! keeps information about each square of the sudoku board
/*! This class is used by class board to keep track of set values,
 * and of possible values based on other square's values.
 */

class square
{
    friend std::ostream& operator<<(std::ostream& os,square&sq);
public:
    square();
    square(const square&);
    ~square()
    {
	for(auto a : applied_stuff){
	    delete a;
	}
    }

    std::ostream&
    print_color(std::ostream& os, color c)
    {
	os << color_names[c];
	return os;
    }

    //! This enum holds the types of algorithms that may touch a square.
    //! The purpose is to avoid time waste or loops, from finding the same
    //! thing more than once.
    enum class matched_type : std::uint8_t {
	// square's mt field get marked with these as the corresponding
	// algorithms are successfully applied.  So we don't try to apply
	// the same algorithm to the same squares over and over wasting time, or
	// for some of the algorithms, so we don't create an infinite loop.
	// Later, if pvals change in any way, we clear the mt field again.
	// n.b. we do not note hidden or naked singles because this result in
	// values being set immediately and make the squares no longer of 
	// interest to other heuristics.
	AM_NONE,
	AM_NAKED_DOUBLE,
	AM_HIDDEN_DOUBLE,
	AM_NAKED_TRIPLE,
	AM_HIDDEN_TRIPLE,
	AM_NAKED_QUAD,
	AM_HIDDEN_QUAD,
	AM_ROW_BLOCK_INTERSECTION,
	AM_COLUMN_BLOCK_INTERSECTION,
	AM_BLOCK_ROW_INTERSECTION,
	AM_BLOCK_COLUMN_INTERSECTION,
	AM_X_WING,
	AM_SWORDFISH,
	AM_JELLYFISH,
	AM_Y_WING,
	AM_XY_CHAIN,
	AM_SIMPLE_COLOR
    };
    /*!
      make a string representation of a matched type
      \param mt The type to represent
      \return the representation as a std::string
      */
    static std::string mt2string(matched_type mt)
    {
	std::vector<std::string> AM_NAMES={
	    "AM_NONE",
	    "AM_NAKED_DOUBLE",
	    "AM_HIDDEN_DOUBLE",
	    "AM_NAKED_TRIPLE",
	    "AM_HIDDEN_TRIPLE",
	    "AM_NAKED_QUAD",
	    "AM_HIDDEN_QUAD",
	    "AM_ROW_BLOCK_INTERSECTION",
	    "AM_COLUMN_BLOCK_INTERSECTION",
	    "AM_BLOCK_ROW_INTERSECTION",
	    "AM_BLOCK_COLUMN_INTERSECTION",
	    "AM_X_WING",
	    "AM_SWORDFISH",
	    "AM_JELLYFISH",
	    "AM_Y_WING",
	    "AM_XY_CHAIN",
	    "AM_SIMPLE_COLOR"
	};
	return AM_NAMES[static_cast<size_t>(mt)];
    }
    //! The parent class for classes that remember methods applied to squares
    class applied
    {
    public:
	//! The main constructor for applied
	applied(matched_type t):type(t){}
	applied()=delete;
	virtual ~applied(){}
	matched_type type; //!< the method applied to the square
        virtual std::ostream& print(std::ostream& os)
	{
	    os << "applied(" << square::mt2string(type) << ")";
	    return os;
	}
    };

    //! a class to keep information about an applied heuristic
    /*! In the square, there's a vector of things derived from applied
     * that keep track of what heuristics have been applied to the square.
     * this one keeps track of the matched type, and a set of squares
     * involved in the heuristic, for example for a hidden double the
     * set of squares would hold the two squares.
     */
    class applied_y_wing: public applied
    {
    public:
	applied_y_wing()=delete;
	//! our main constructor
	/*! This constructor is called to initialize our applied_y_wing class
	 * initiallizes our base class passing param t, the pivot and the
	 * two wings
	 * \param t the method applied
	 * \param wing1 reference to the first wing
	 * \param pivot reference to the pivot
	 * \param wing2 reference to the second wing
	 */
	applied_y_wing(matched_type t,square& w1,square& p, square& w2):applied(t),wing1(w1),pivot(p),wing2(w2){};
	virtual std::ostream&
	print(std::ostream& os)
	{
	    os << "applied_y_wing(";
	    applied::print(os);
	    return os;
	}
	//! equality operator for applied_y_wing
	bool
	operator==(applied_y_wing& other)
	{
	    if(type==other.type && wing1==other.wing1 &&
		    pivot==other.pivot && wing2==other.wing2){
		return true;
	    }
	    return false;
	}
	//! our copy of the set of pointers to applied squares
	square &wing1, &pivot, &wing2;
    };

    //! a class to keep information about an applied heuristic
    /*! In the square, there's a vector of things derived from applied
     * that keep track of what heuristics have been applied to the square.
     * this one keeps track of the matched type, and a set of squares
     * involved in the heuristic, for example for a hidden double the
     * set of squares would hold the two squares.
     */
    class applied_set: public applied
    {
    public:
	applied_set()=delete;
	//! our main constructor
	/*! This constructor is called to initialize our applied_set class
	 * initiallizes our base class passing param t and our sqs member
	 * \param t the method applied
	 * \param sqs a set of pointers to squares in our dance party
	 */
	applied_set(matched_type t,std::set<square*>sqs):applied(t),sqs(sqs){};
	//! equality operator for applied_set
	bool
	operator==(applied_set& other)
	{
	    if(type==other.type &&
		    sqs==other.sqs){
		return true;
	    }
	    return false;
	}
	//! our copy of the set of pointers to applied squares
	std::set<square*> sqs;
    };

    //! a class to keep information about an applied heuristic
    /*! In the square, there's a vector of things derived from applied
     * that keep track of what heuristics have been applied to the square.
     * this one keeps track of the matched type, a pval, and a vector of squares
     * involved in the heuristic, for an intersection, the
     * vector of squares would hold the two or three squares.
     */
    class applied_intersection: public applied
    {
    public:
	applied_intersection()=delete;
	//! our main constructor
	/*! This constructor is called to initialize our applied_intersection
	 * class
	 * initiallizes our base class passing param t and our sqs member
	 * \param t the method applied
	 * \param sqs a intersection of pointers to squares in our dance party
	 */
	applied_intersection(matched_type t,size_t pval, std::vector<square*>sqs):applied(t),pval(pval),sqs(sqs){};
	//! equality operator for applied_intersection
	bool
	operator==(applied_intersection& other)
	{
	    if(type==other.type
		    && sqs==other.sqs
		    && pval==other.pval){
		return true;
	    }
	    return false;
	}
	//! the pval the intersection happened on
	size_t pval;
	//! our copy of the vector of pointers to applied squares
	std::vector<square*> sqs;
    };

    //! a class to keep information about an applied interlock heuristic
    /*! In the square, there's a vector of things derived from applied
     * that keep track of what heuristics have been applied to the square.
     * This particular one keeps track of applied x-wings, swordfish,
     * and jellyfish. They just need to remember the type, (one of
     * AM_X_WING, AM_SWORDFISH, or AM_JELLYFISH, the value, the selt
     * of rows and the set of columns involved.
     */
    class applied_interlock: public applied
    {
    public:
	//! our main constructor for applied_interlock
	/*! constructor for applied interlock. Initializes our parent
	 * applied class with t and sets our rows and cols to r and c
	 * \param t a matched type for heuristic applied to a square
	 * \param v the value on which we interlocked
	 * \param r the set of rows involved in the interlock
	 * \param c the set of columns involved in the interlock
	 */
	applied_interlock(matched_type t, size_t v, const std::set<size_t>& r, const std::set<size_t>& c): applied(t), val(v), rows(r), cols(c){ APPLIED_DEBUG std::cerr << "applied_interlock constructor\n"; }
	applied_interlock()=delete;
	//! our equality operator, used to check to see if this already applied to square
	bool
	operator==(applied_interlock& other)
	{
	    if( type==other.type &&
		val==other.val &&
		rows==other.rows &&
		cols==other.cols){
		return true;
	    }
	    return false;
	}
	//! the value the interlock locked on
	size_t val;
	//! the rows involved in the interlock
	std::set<size_t> rows;
	//! the columns involved in the interlock
	std::set<size_t> cols;
    };
 
    //! a class to keep information about an applied simple_color heuristic
    /*! In the square, there's a vector of things derived from applied
     * that keep track of what heuristics have been applied to the square.
     * This particular one keeps track of applied x-wings, swordfish,
     * and jellyfish. They just need to remember the type, (one of
     * AM_X_WING, AM_SWORDFISH, or AM_JELLYFISH, the value, the selt
     * of rows and the set of columns involved.
     */
    class applied_simple_color: public applied
    {
    public:
	//! our main constructor for applied_simple_color
	/*! constructor for applied simple_color. Initializes our parent
	 * applied class with t and sets our rows and cols to r and c
	 * \param t a matched type for heuristic applied to a square
	 * \param v the value on which we simple_colored
	 * \param r the set of rows involved in the simple_color
	 * \param c the set of columns involved in the simple_color
	 */
	applied_simple_color(size_t pv): applied(matched_type::AM_SIMPLE_COLOR), pval(pv)
	{
	    APPLIED_DEBUG std::cerr << "applied_simple_color constructor\n";
	}
	applied_simple_color()=delete;
	//! our equality operator, used to check to see if this already applied to square
	bool
	operator==(applied_simple_color& other)
	{
	    if( type==other.type && pval==other.pval){
		return true;
	    }
	    return false;
	}
	//! the candidate value the simple_color marked on
	size_t pval;
    };
    square&
    operator=(const square&);
    square(size_t rw, size_t cl, std::vector<unsigned int> pv);
    square(size_t rw, size_t cl, size_t vl, std::vector<unsigned int> pv);
    //! default filter used by get_neighbors() always returns true
    bool
    true_filt(square*){return true;}
    //! filter for get_neighbors returns true for squares with 2 members of pvals
    bool
    two_filt(square*sq){if(sq->size()==2) return true;return false;}
    //! filter for get_neighbors returns true for squares with 8 members of pvals
    bool
    eight_filt(square*sq){if(sq->size()==8) return true;return false;}
    //! filter for get_neighbors returns true for squares with 9 members of pvals
    bool
    nine_filt(square*sq){if(sq->size()==9) return true;return false;}
    //! filter for get_neighbors returns true for squares with no color
    bool
    no_color_filt(square*sq)
    {
	return sq->get_color()==color::none?true:false;
    }

    /*! filter for get_neighbors.  Called when we have two pvals and have
     *  claimed one of them for ourselves.  We're looking for squares that
     *  also have two pvals, and that matches the pval we claim.
     *  \param sq a pointer to the square to be checked to see if it has
     *         two pvals and one of them matches the one we own
     *  \return true if the square has 2 pvals one of which matches the one
     *         we own.
     */
    bool
    xy_chain_filt(square*sq)
    {
	XY_CHAIN_FILT_DEBUG std::cout << "xy_chain_filt passed in square: " << *sq;
	XY_CHAIN_FILT_DEBUG std::cout << "  our square: " << *this;
	if(pvals.size()!=2){
	    // paranoia, we shouldn't be called on a square without 2 pvals
	    std::cerr << "  pvals.size() != 2 returning false\n";
	    return false;
	}
	if(val!=0){
	    // paranoia, we shouldn't be called on a square already set
	    std::cerr << "  val already set, returning false\n";
	    return false;
	}

	// get the value of the pval that this square owns
	size_t xy_owned=get_xy_owned();
	XY_CHAIN_FILT_DEBUG std::cout << "  we own: " << xy_owned << '\n';

	if(sq->size()==2){	// only squares w/2 pvals need apply
	    // we compare sq's two pvals to see if one matched the
	    // pval we have claimed
	    if(sq->pvals[0]==xy_owned || sq->pvals[1]==xy_owned){
		XY_CHAIN_FILT_DEBUG std::cout << "  found a next link, returning true\n";
		return true;
	    }
	    XY_CHAIN_FILT_DEBUG std::cout << "  Neither pval matched next, returning false\n";
	    return false;
	}
	// if they don't have two pvals, return false.
	XY_CHAIN_FILT_DEBUG std::cout << "  square passed in didn't have 2 pvals returning false\n";
	return false;
    }
    //! expect to set owned to either 0 or 1 since this is used by xy_chain
    /*! set_owned is used for chains of squares with two pvals. This sets
     * whether the square "owns" the first (value 0) or the second (value 1).
     * \param o either 0 or 1
     * \return none
     */
    void
    set_owned(size_t o){ owned=o; };
    //! get a color and set it in square
    /*! We use this in coloring algorithms to tell the squares what they are
     */
    void
    set_color(color in_color){ c=in_color;};
    //! get a color and set it in square
    /*! We use this in coloring algorithms to find out color of square
     */
    color get_color(){ return c;};


    //!get pvals[owned]
    /*! expecting that the square has two pvals, and that owned has been
     * previously set, returns pvals[0] or pvals[1] depending on the
     * setting of owned
     */
    size_t
    get_xy_owned(){ return pvals[owned]; };
    //!get pval[1-matched], i.e. the other of the pair that is not owned
    size_t
    get_xy_next(){ return pvals[1-owned]; };
    //! assigns the passed in vector to our pvals and clears applied methods
    void
    assign_pvals(std::vector<unsigned int>& vals);
    //! removes everything from our pvals and clears applied methods
    void
    clear_pvals();
    //! returns whatever is in our val, 0 for unset, else one of [1,N)
    unsigned int get_val() const { return val; }
    //! sets our value if not already locked
    /*! sets our value to the passed in value and if set_pval is true
     * (the default), additionally clears pvals and pushed our new val
     * onto pvals
     * \param v the value to be set
     * \param set_pval a boolean, if true sets pvals, if false no
     */
    void set_val(unsigned int v,bool set_pval=true){
	if(!locked){
	    val=v;
	    // did have code to clear pvals and set it to just the set value, 
	    // but that broke brute force which relies on being able to use 
	    // pvals to try one value after another.  So I added another
	    // argument, set_pval, defaulted to true, so heuristic methods
	    // can set a val and also set pvals to the same thing, but brute
	    // force can use another argument set to false to avoid setting
	    // pvals so they can use it to keep track of untried values.
	    // TODO: board's set_val clears these additional pvals one by
	    // one before calling us, as they keep the possibility vectors
	    // for row column and block in sync, so that this is superfluous
	    // in that case. Wasted effort?
	    if(set_pval){
		if(applied_stuff.size()){
		    clear_applied_stuff();
		}
		pvals.clear();
		pvals.push_back(val);
	    }
	}
    }
    size_t get_row() const { return row; }//!< accessor for row of the square
    size_t get_column() const { return col; }//!< accessor for column of the square
    bool is_locked()const { return locked;}//!<locked means val set can't change
    void set_locked(bool d)
    {
	locked=d;
	if(applied_stuff.size()){
	    clear_applied_stuff();
	}
    }//!<make square locked
    bool choose_val(bool rand=true);//!<chooses from pvals
    bool in_vals(size_t) const;//!<return true of input is in pvals
    void
    reset();//!<put a square into a known but empty state
    //! mark a square as holding invalid state
    void
    set_invalid(){valid=false;};
    //! mark square valid
    void
    set_valid(){valid=true;};
    //!is the square valid?
    bool
    get_valid() const {return valid;};
    //! mark square as immutable
    void
    lock(){locked=true;};
    //!mark square as mutable
    void
    unlock(){locked=false;};
    /*! try to find the val in our pvals and if found use the iterator
	returned by std::find to erase that value.  If we find it, as
	a side effect we clear information about applied heuristics.
	\param in_val the value to be removed
	\return true if in_val was in our pvals, and we had to clear it. else if we did nothing, return false.
     */
    bool
    clear_pval_val(size_t in_val){
	std::vector<unsigned int>::iterator it;
	it=std::find(pvals.begin(),pvals.end(),in_val);
	CLEAR_PVAL_VAL_DEBUG{
	    std::cerr << "square::clear_pval_val("
		<< in_val << "): " << *this;
	}
	if(it!=pvals.end()){
	    if(applied_stuff.size()){
		clear_applied_stuff();
	    }
	    pvals.erase(it);
	    CLEAR_PVAL_VAL_DEBUG{
		std::cerr << "  exiting true\n";
	    }
	    return true;
	}
	CLEAR_PVAL_VAL_DEBUG{
	    std::cerr << "  exiting false\n";
	}
	return false;

    };

    /*!
     * compare this->pvals and other.pvals and returns true iff they have
       the same content
       \param other is the square to be compared to us
       \return true iff other square has same pvals as us
   */
    bool
    same_pvals(const square& other){
	std::vector<unsigned int>::iterator it;
	if(pvals.size()!=other.pvals.size()) return false;
	for(it=pvals.begin();it!=pvals.end();it++){
	    if(!other.in_vals(*it)) return false;
	}
	return true;
    }

    //! sets the row and column
    void
    set_rowcol(size_t therow, size_t thecol){ row=therow; col=thecol; }

    bool
    check_applied_y_wing(square& wing1, square& pivot, square& wing2)
    {
	APPLIED_DEBUG{
	    std::cerr << "check_applied_y_wing:\n"
		<< "  walking through list of applied stuff\n";
	}
	for(applied* a : applied_stuff){
	    if(a->type==matched_type::AM_Y_WING){
		applied_y_wing* as=dynamic_cast<applied_y_wing*>(a);
		if(pivot==as->pivot &&
		    ((wing1==as->wing1 && wing2==as->wing2)
		  || (wing1==as->wing2 && wing2==as->wing1))){
		    APPLIED_DEBUG{
			std::cerr << "found y-wing already in applied list\n";
		    }
		    return true;
		}
	    }
	}
	APPLIED_DEBUG std::cerr << "didn't find the y-wing in applied list\n";
	return false;
    }

    bool
    set_applied_y_wing(square& wing1, square& pivot, square& wing2)
    {
	if(!pivot.check_applied_y_wing(wing1,pivot,wing2)){
	    applied_stuff.push_back(new applied_y_wing(matched_type::AM_Y_WING,wing1,pivot,wing2));
	    return true;
	}else{
	    APPLIED_DEBUG std::cerr << "tried to apply set_applied_y_wing but already set\n";
	}
	return false;
    }
 
    //! remembers that the heuristic mt has been applied with set sqs
    /*! this is called to remember that the heuristic mt has been applied
     * with the set of squares sqs. It doubles as a check to see if this
     * exact request has been already made, returning false if it finds 
     * an applied_set on our applied_stuff vector already with exactly
     * mt and sqs in it.
     * \param mt type of heuristic applied
     * \param sqs set of pointers to squares for all the squares that participated in the heuristic
     * \return bool false for already applied true for successfully applied
     */
    bool
    set_applied_set(const matched_type mt, std::set<square *>sqs)
    {
	APPLIED_DEBUG {
	    std::cerr << "set_applied_set(" << mt2string(mt) << "): returning ";
	}
	// first look through this square's list of applied heuristics and
	// if we find one with the same matched_type and same set members
	// return  false.
	// If not we push a new applied_set with mt and sqs in it on to
	// our list of aplied heuristics
	for(applied* a : applied_stuff){
	    if(a->type==mt){
		applied_set* as=dynamic_cast<applied_set*>(a);
		if(as->sqs==sqs){
		    APPLIED_DEBUG std::cerr << "false\n";
		    return false;
		}
	    }
	}
	applied_stuff.push_back(new applied_set(mt,sqs));
	APPLIED_DEBUG std::cerr << "true\n";
	return true;
    }

    //! remembers that the heuristic mt has been applied with intersection of sqs for a pval
    /*! this is called to remember that the heuristic mt has been applied
     * with the intersection of squares sqs for a particular pval. It doubles
     * as a check to see if this exact request has been already made,
     * returning false if it finds an applied_intersection on our
     * applied_stuff intersection already with exactly mt and sqs and pval.
     * \param mt type of heuristic applied
     * \param pval the candidate the intersection occured on
     * \param sqs pointers to squares for all squares that participated in the intersection
     * \return bool false for already applied true for successfully applied
     */
    bool
    set_applied_intersection(const matched_type mt, size_t pval, std::vector<square *>sqs)
    {
	APPLIED_DEBUG {
	    std::cerr << "set_applied_intersection(" << mt2string(mt) << "): returning ";
	}
	// first look through this square's list of applied heuristics and
	// if we find one with the same matched_type and same intersection members
	// return  false.
	// If not we push a new applied_intersection with mt and sqs in it on to
	// our list of aplied heuristics
	for(applied* a : applied_stuff){
	    if(a->type==mt){
		applied_intersection* as=dynamic_cast<applied_intersection*>(a);
		if(as->pval==pval && as->sqs==sqs){
		    APPLIED_DEBUG std::cerr << "false\n";
		    return false;
		}
	    }
	}
	applied_stuff.push_back(new applied_intersection(mt,pval,sqs));
	APPLIED_DEBUG std::cerr << "true\n";
	return true;
    }

    //! sets the combo of applied type and vector of squares applied
    bool
    set_applied_interlock(const matched_type mt, size_t val, std::set<size_t>rows, std::set<size_t>cols)
    {
	for(applied* a : applied_stuff){
	    if(a->type==mt){
		applied_interlock* ai=dynamic_cast<applied_interlock*>(a);
		if(ai->val == val && ai->rows==rows && ai->cols==cols){
		    return false;
		}
	    }
	}
	applied_stuff.push_back(new applied_interlock(mt,val,rows,cols));
	return true;
    }
    //! checks to see if simple color was found on this pval
    bool
    check_applied_simple_color(size_t pval)
    {
	for(applied* a : applied_stuff){
	    if(a->type==matched_type::AM_SIMPLE_COLOR){
		applied_simple_color* ai=dynamic_cast<applied_simple_color*>(a);
		if(ai->pval == pval){
		    return true;
		}
	    }
	}
	return false;
    }
    //! sets color found on this square on this pval
    bool
    set_applied_simple_color(size_t pval)
    {
	if(check_applied_simple_color(pval)){
	    // not setting because already set
	    return false;
	}
	applied_stuff.push_back(new applied_simple_color(pval));
	return true;
    }
    //! clears information about applied heuristics
    /*! walks through the square's applied_stuff vector and deletes all of
     * the various applied_interlock or applied_squares or whatever
     */
    void clear_applied_stuff()
    { 
	APPLIED_DEBUG std::cerr << "CLEARING APPLIED STUFF, there are " << applied_stuff.size() << " entries\n";
	for(auto a : applied_stuff){
	    APPLIED_DEBUG{
		std::cerr << "  clearing: ";
		a->print(std::cerr) << '\n';
	    }
	    delete a;
	}
	applied_stuff.clear();
    }
    /*!
     * allow access to the pvals by index
     * \param which 0 based index into pvals
     * \return -1 if out of range, else pvals[which]
     */
    ssize_t
    operator[](size_t which){
	if(which>=pvals.size()) std::cout << "Found -1\n";
	return which<pvals.size()?pvals[which]:-1;
    }
    std::vector<unsigned int>::iterator begin(){ return pvals.begin(); }
    std::vector<unsigned int>::iterator end(){ return pvals.end(); }
    //! returns size of pvals
    size_t
    size(){return pvals.size();};

    std::ostream&
    print_pvals(std::ostream& os)
    {
	bool first=true;
	os << '{';
	for(auto pval : pvals){
	    if(!first) os << ", ";
	    first=false;
	    os << pval;
	}
	os << "}";
	return os;
    }

    bool
    operator==(square& other)
    {
	if(row==other.row && col==other.col){
	    return true;
	}
	return false;
    }

private:
    // private data
    std::vector<applied*> applied_stuff;
    bool locked; //!< if true, square is immutable, for example given clue
    unsigned int val;	//!< The value of the square in the board
    size_t row;//!< row in board.  Really board's info but convenient here
    size_t col;//!< column in board.
    std::vector<unsigned int> pvals;//!<possible values for an unset square
    std::vector<unsigned int> saved_vals;//!<unused
    bool valid;//!<false when two squares that can see each other have same value
    size_t owned; // which of 2 pvals we own for xy-chain.
    color c;
    // private methods
};

class p_square_helper
{
public:
    p_square_helper(square* sq,bool prc=true,bool ppv=false,
	    bool pc=false,bool add_one=false):
		 sq(sq),prc(prc),ppv(ppv),pc(pc),add_one(add_one){}
    square* sq;	// the square whose info will be printed
    bool prc;	// print row column?
    bool ppv;	// print pvals?
    bool pc;	// print color?
    bool add_one;	// add one to row and columne?
};

inline
class p_square_helper
print_sq_rc(square *sq)
{
    return p_square_helper(sq,true,false,false,false);
}

inline
class p_square_helper
print_sq_rc_plus(square *sq)
{
    return p_square_helper(sq,true,false,false,true);
}

inline
class p_square_helper
print_sq_rcp(square *sq)
{
    return p_square_helper(sq,true,true,false,false);
}

inline
class p_square_helper
print_sq_rcp_color(square *sq)
{
    return p_square_helper(sq,true,true,true,false);
}

std::ostream&
operator<<(std::ostream& os, p_square_helper h)
{
    std::string retval;
    std::ostringstream ss(retval);
    size_t addit=h.add_one?1:0;
    
    ss << color2string(h.sq->get_color());
    ss << "r" << h.sq->get_row()+addit << 'c' << h.sq->get_column()+addit;
    ss << toblack;
    if(h.ppv){
	ss << " pvals:";
	h.sq->print_pvals(ss);
    }
    if(h.pc){
	ss << " color: ";
	h.sq->print_color(ss,h.sq->get_color());
    }
    os << ss.str();
    return os;
}
/*!
 * constructor just calls the reset() method
 */
square::square()
{
    this->reset();
}

/*!
 * sets square to empty and available to any value.  If logging, the square
 * is dumped
 */
void
square::reset()
{
    //std::cerr << "square::reset()\n" << *this;
    val=0;
    pvals.clear();
    for(size_t ctr=1;ctr<10;ctr++){
	pvals.push_back(ctr);
    }
    //pvals={ 1,2,3,4,5,6,7,8,9 };
    locked=false;
    valid=true;
    if(applied_stuff.size()){
	clear_applied_stuff();
    }
    c=color::none;
}

/*!
 * this is used in testing to create squares with particular pvals that
 * that are passed in rather than being set based on the content of other
 * squares.  Using this we can create anything we want to test for.
 * \param rw the row of the square to have pvals set
 * \param cl the column of the square to have pvals set
 * \param pv the pvals to be set
 */
square::square(size_t rw, size_t cl, std::vector<unsigned int> pv)
{
    reset();
    row=rw;
    col=cl;
    pvals.clear();
    for(auto val : pv){
	pvals.push_back(val);
    }
}

/*!
 * this is used in testing to create squares with particular pvals that
 * that are passed in rather than being set based on the content of other
 * squares.  Using this we can create anything we want to test for.
 * \param vl the val to be set into the square
 * \param rw the row of the square to have pvals set
 * \param cl the column of the square to have pvals set
 * \param pv the pvals to be set
 */
square::square(size_t rw, size_t cl, size_t vl, std::vector<unsigned int> pv)
{
    reset();
    row=rw;
    col=cl;
    val=vl;
    pvals.clear();
    for(auto val : pv){
	pvals.push_back(val);
    }
}

/*!
 * copy constructor of the square class
 * \param other the square who's values will set ours
 */
square::square(const square& other)
{
    val=other.val;
    row=other.row;
    col=other.col;
    pvals.clear();
    for(auto val : other.pvals){
	pvals.push_back(val);
    }
    //pvals=other.pvals; // hasn't segfaulted but looks same as where it does
    locked=other.locked;
    valid=other.valid;
    /* // probably don't have to do anything with this
    if(other.applied_stuff.size()){
    }
    */
    c=other.c;
}

//! A generic print of vectors that prints every element of the vector
template<typename T>
std::ostream&
operator<<(std::ostream& os, std::vector<T> v)
{
    for(auto i : v){
	os << i << ',';
    }
    return os;
}
/*!
 * assignment operator for a square
 * \param other the square to be assigned to us
 * \return *this as a reference to square
 */
square&
square::operator=(const square& other)
{
    val=other.val;
    row=other.row;
    col=other.col;
    pvals.clear();
    //std::cerr << "pvals.capacity: " << pvals.capacity() << '\n';
    for(auto val : other.pvals){
	pvals.push_back(val);
    }
    //pvals=other.pvals;   // segfault here problem is with my pvals
    			 // maybe better to do push_back? Maybe resize to
			 // 9 at construction? Nope neither helped
    locked=other.locked;
    return *this;
}

/*!
 * copies vals to our pvals and as a side-effect, clears applied stuff
 * \param vals the values to copy to our pvals
 */
void
square::assign_pvals(std::vector<unsigned int>& vals)
{
    pvals.clear();
    for(auto val : vals){
	pvals.push_back(val);
    }
    //pvals=vals;
    if(applied_stuff.size()){
	clear_applied_stuff();
    }
}

/*!
 * clears our pvals and as a side effect and clears applied stuff
 */
void
square::clear_pvals()
{
    pvals.clear();
    if(applied_stuff.size()){
	clear_applied_stuff();
    }
}

bool
inline
square::in_vals(size_t val) const
{
    /*!
     * Check to see if a particular value is in our pvals
     * \param val the value to search for
     * \return true if the val is in our pvals else false
     */
    return std::find(pvals.begin(),pvals.end(),val)!=pvals.end();
}

bool
square::choose_val(bool rand)
{
    /*!
     * chooses a value from our pval and sets it as our value randomly
     * N.B. does NOT remove the value from pvals.
     * \return true if pvals was non-empty, else false
     */
    CHOOSE_VAL_DEBUG std::cerr << "  choose_val(" << std::boolalpha << rand << "):\n";
    CHOOSE_VAL_DEBUG std::cerr << "    pvals.size(): " << pvals.size() << '\n';
    if(locked){
	return true;
    }
    if(pvals.size()==0){
	CHOOSE_VAL_DEBUG std::cerr << "    chose: NONE, empty pvals\n";
	return false;
    }else if(pvals.size()==1){
	val=pvals[0];
	CHOOSE_VAL_DEBUG std::cerr << "    chose: " << val << '\n';
	return true;
    }
    size_t which=rand_n(pvals.size());
    std::vector<unsigned int>::iterator it=pvals.begin();
    std::advance(it,which);
    val=*it;
    CHOOSE_VAL_DEBUG std::cerr << "    chose: " << val << '\n';
    return true;
}

std::ostream&
operator<<(std::ostream& os, square&sq)
{
    /*!
     * dump a square to the passed in stream
     * \param os the stream to dump to
     * \param sq the square to dump
     * \return os
     */
    os << "square[" << sq.row << "][" << sq.col << "]"
       << ", val: " << sq.val
       << ", locked: " << std::boolalpha << sq.is_locked()
       << ", color: " << sq.c
       << ", pvals: ";
    sq.print_pvals(os);
    os << '\n';
    return os;
}
    
//! enum  for heuristic routines to tell each other what to operate on
enum grouptype{GT_ROW, GT_COLUMN, GT_BLOCK};

//! for debugging printing of grouptype enums
std::vector<std::string> grouptype_names { "GT_ROW", "GT_COLUMN", "GT_BLOCK" };
//! for debugging printing of grouptype enums
std::vector<std::string> grouptype_2_name { "row", "column", "block" };

std::ostream&
operator<<(std::ostream&os, grouptype gt)
{
    os << grouptype_names[gt];
    return os;
}

template<const unsigned int N> class board; //!< forward reference to board

//! parent class of all solving methods
/*!
 * This class specifies a set of interfaces to allow solving algorithms to be
 * accessed by the board and to keep track of how many times they're called.
 * Not instantiatable directly
 */
template<const unsigned int N>
class sudoku_method
{
public:
    //! main constructor
    /*! The only used constructor
     * \param s name of method
     * \param l level of method
     */
    sudoku_method(std::string s,size_t l):name(s),level(l){};
    sudoku_method()=delete;

    //! add to our count of times method applied
    /*! adds s to the count of times the method applied
     * \param s the number of times to add
     */
    void
    count_add(size_t s){count+=s;};
    //! Called by each of our child classes each time they successfully apply
    void
    incr_count(){count++;};
    //! Called to get the count of times our child successfully applied
    size_t
    get_count(){return count;};
    //! Called to clear the count of times our child successfully applied
    void
    clear_count(){count=0;};
    //!getter for name
    const std::string& get_name(){return name;}
    //!getter for sort level
    size_t get_sort_level(){return sort_level;}
    //! setter for sort level
    void set_sort_level(size_t level){
	sort_level=level; 
    }
    //! getter for level
    size_t get_level(){return level;}
    /*! for each algorithm, the apply method implements it.
     * Our children must implement apply
     */
    virtual
    bool
    apply()=0;
    /*!  Our children must each implement their own register_strategy
     *   to tell the board about themselves. The board calls this for
     *   each strategy, passing them a pointer to the board (they need
     *   to call methods of the board and the sort level the board 
     *   wants them to have (that controls the order in which heuristics
     *   are called and even IF they are called).
     *   \param board a pointer to the board
     */
    virtual
    void register_strategy(board<N>*,size_t sort_level)=0;
protected:
    // we and our descendents, the individual methods, see this stuff
    // directly, everyone else has to use the setters and getters
    //! The name of the method used in setting sort levels
    std::string name;
    //! Keeps track of times our child successfully applied
    size_t count;
    //! class board calls our register_strategy passing in his address which we save here
    board<N>* b;
    //! sort level sets the order of application, with 1 soonest (and 0 means disabled)
    size_t sort_level;
    //! felt sense of difficulty
    size_t level;
};

std::ostream&
operator<<(std::ostream& os,sudoku_method<9>* m)
{
    std::cout << "sudoku method: "
	<< std::left << std::setw(14) << m->get_name();
    std::cout << " sort_level: " << std::right << std::setw(2) <<  m->get_sort_level();
    std::cout << ", level: " << m->get_level();
    return os;
}

/*!
 * This class registers and implements the naked single method
 * A naked single (also called forced digit and sole candidate) is a square
 * with only one possible value.  Of course it must be set to that value.
 */
template<const unsigned int N>
class naked_single:public sudoku_method<N>
{
public:
    naked_single():sudoku_method<N>("naked single",1){
	NAKED_SINGLE_DEBUG std::cerr << "naked_single()\n";
    }
    virtual
    bool
    apply(){
	/*! for each algorithm, the apply method implements it.  This one is the
	 * simplest, merely walking the board until finding a square with only
	 * one number in its pvals.  Then val is set to that value
	 */
	NAKED_SINGLE_DEBUG std::cerr << "naked_single.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	NAKED_SINGLE_DEBUG std::cerr << "before apply\n";
	NAKED_SINGLE_DEBUG b->print_large();
	for(size_t row=0;row<N;row++){
	    for(size_t col=0;col<N;col++){
		//std::vector<square>& therow=b->[row];
		//square& sq=therow[col];
		square& sq=(*b)[row][col];
		NAKED_SINGLE_DEBUG std::cerr << "  naked_single loop--row: " << row << ", col: " << col << ", possibilities: " << sq.size() << ", value: " << sq.get_val() << ", locked: " << sq.is_locked() << "\n";
		if(!sq.is_locked() && sq.get_val()==0 && sq.size()==1 ){
		    RESPATH{
			std::cerr << "naked-single ==> "
			    << "r" << row+1 << "c" << col+1 << " = "
			    << sq[0] << ' ';
		    }
		    // set the square's value to it's only pval
		    b->set_val(row,col,sq[0]);
		    NAKED_SINGLE_DEBUG{
			std::cerr << "  [" << row << "][" << col
			    << "] set value to " << sq.get_val() << '\n';
		    }
		    RESPATH std::cerr << '\n';
		    sudoku_method<N>::incr_count();
		    return true;
		}
	    }
	}
	return false;
    };

    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*!
* Hidden Single - A cell may have more than one possibility, but in one of its
* groups, row, column, or square, it's the only one that provides one of the
* numbers, for example, in column 6 there may be only one square with the
* number 3 in it's possibilities, so the 3 will have to go there.
* n.b. also called pinned digit
*/
template<const unsigned int N>
class hidden_single:public sudoku_method<N>
{
public:
    hidden_single():sudoku_method<N>("hidden single",1){
	HIDDEN_SINGLE_DEBUG std::cerr << "hidden_single() constructor\n";
    }
    virtual
    bool
    apply(){
	HIDDEN_SINGLE_DEBUG std::cerr << "hidden_single.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	// check for hidden single in rows
	HIDDEN_SINGLE_DEBUG std::cerr << "  checking rows\n";
	for(size_t row=0;row<N;row++){
	    HIDDEN_SINGLE_DEBUG std::cerr << "    checking row: " << row << "\n";
	    std::map<size_t,std::vector<square*>>& mvs=
		b->get_possibilities(GT_ROW,row);
	    for(size_t val=1;val<N+1;val++){
		HIDDEN_SINGLE_DEBUG std::cerr << "      checking val: " << val << "\n";
		if(mvs[val].size()==1){
		    square& sq=*mvs[val][0];
		    if(sq.get_val()==0){
			RESPATH{
			    std::cerr << "hidden-single-in-row r"
				<< row+1 << " ==> " << print_sq_rc_plus(&sq)
				<< " = " << val << ' ';
			}
			b->set_val(row,sq.get_column(),val);
			RESPATH std::cerr << "\n";
			sudoku_method<N>::incr_count();
			HIDDEN_SINGLE_DEBUG std::cerr << "    [" << row << "][" << sq.get_column() << "] hidden in row, set value to " << val << '\n';
			return true;
		    }
		}
	    }
	}
	// check for hidden single in columns
	HIDDEN_SINGLE_DEBUG std::cerr << "  checking columns\n";
	for(size_t col=0;col<N;col++){
	    HIDDEN_SINGLE_DEBUG std::cerr << "    checking column: " << col << "\n";
	    std::map<size_t,std::vector<square*>>& mvs=
		b->get_possibilities(GT_COLUMN,col);
	    for(size_t val=1;val<N+1;val++){
		HIDDEN_SINGLE_DEBUG std::cerr << "      checking val: " << val << "\n";
		if(mvs[val].size()==1){
		    square& sq=*mvs[val][0];
		    if(sq.get_val()==0){
			RESPATH{
			    std::cerr << "hidden-single-in-column c"
				<< col+1 << " ==> "
				<< print_sq_rc_plus(&sq)
				<< " = " << val << ' ';
			}
			b->set_val(sq.get_row(),col,val);
			sudoku_method<N>::incr_count();
			RESPATH std::cerr << "\n";
			HIDDEN_SINGLE_DEBUG std::cerr << "    [" << sq.get_row() << "][" << col << "] hidden in column, set value to " << val << '\n';
			return true;
		    }
		}
	    }
	}
	// check for hidden in block
	HIDDEN_SINGLE_DEBUG std::cerr << "  checking blocks\n";
	for(size_t block_num=0;block_num<N;block_num++){
	    std::map<size_t,std::vector<square*>>& mvs=
		b->get_possibilities(GT_BLOCK,block_num);
	    HIDDEN_SINGLE_DEBUG std::cerr << "    checking block: " << block_num << "\n";
	    for(size_t val=1;val<N+1;val++){
		HIDDEN_SINGLE_DEBUG std::cerr << "      checking val: " << val << "\n";
		if(mvs[val].size()==1){
		    square& sq=*mvs[val][0];
		    if(sq.get_val()==0){
			RESPATH{
			    std::cerr << "hidden-single-in-block b"
				<< block_num+1 << " ==> "
				<< print_sq_rc_plus(&sq)
				<< " = " << val << ' ';
			}
			b->set_val(sq.get_row(),sq.get_column(),val);
			RESPATH std::cerr << "\n";
			sudoku_method<N>::incr_count();
			HIDDEN_SINGLE_DEBUG std::cerr << "    [" << sq.get_row() << "][" << sq.get_column() << "] hidden in column, set value to " << val << '\n';
			return true;
		    }
		}
	    }
	}
	return false;	// didn't find a singleton
    }

    /*! each of the suduko_method<>s has a register_strategy method that
     * is called from the board at initialization. That lets us find out
     * the address of the board, and our sort level (affects the order
     * in which the heuristics are called).
     * We then in turn close the loop by calling the board's register
     * strategy method to give them the address of this method. It isn't
     * required, but it makes it possible to simply and cleanly implement
     * calling all the heuristics in a loop. All of them live in the board
     * class anyway so he could just take everyone's address and build
     * the same data struct, so the call back is technically not neccessary.
     * It's just elegant. The board pointer is really important, because
     * the heuristics call methods on the board all of the time. The sort
     * level is for the convenience of the board, so that he can sort us
     * (a sort level of 0 though means that we are deactivated, board will
     * never call us.)
     */
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

//! A class to find naked doubles on a board
/*! Naked Double - Two cells in a group each have only the same two numbers as
 * 	possibilities.  Since each must have one or the other, all other cells
 * 	in the group can have those numbers removed.  This can work for row,
 * 	column, or square.  For example if two cells in a group had only 1 and
 * 	7 in their possibility list, then 1 and 7 could be removed from the 
 * 	possibility list of every other cell in the group.
 */
template<const unsigned int N>
class naked_double:public sudoku_method<N>
{
public:
    naked_double():sudoku_method<N>("naked double",3){
	NAKED_DOUBLE_DEBUG std::cerr << "naked_double()\n";
    }
    virtual
    bool
    apply(){
	NAKED_DOUBLE_DEBUG std::cerr << "naked_double.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	size_t count;
	if((count=b->naked_apply(2))){
	    sudoku_method<N>::count_add(count);
	    NAKED_DOUBLE_DEBUG std::cerr << "success\n";
	    return true;
	}
	return false;
    }

    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};


//! Find cases of a row/block/column with two numbers in only two squares
/*! This heuristic looks for cases where there are two numbers that only
 * appear in two squares in a group, although those squares may have other
 * possibilities. i.e. in row 7, in columns 2 the square could hold values
 * 3, 7, 8, and 9, and in column 5, the square could could values 2, 4, 7,
 * and 8. If these are the only two squares in row 7 that could hold a 7 or
 * 8, then we have found a hidden double. Since one has to hold 7 and the
 * other 8, (we don't know which is which yet), we can remove the 3, and the
 * 9 from the square in column 2 and the 2 and the 4 from the one in column 5.
 * Since each of them is on the same row now, with only 7 and 8 in their
 * possible values, we've turned them into a naked double.
 */
template<const unsigned int N>
class hidden_double:public sudoku_method<N>
{

public:
    hidden_double():sudoku_method<N>("hidden double",3){
	HIDDEN_DOUBLE_DEBUG std::cerr << "hidden_double()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	HIDDEN_DOUBLE_DEBUG std::cerr << "hidden_double.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	size_t cnt;
	if((cnt=b->hidden_apply(2))){
	    sudoku_method<N>::count_add(cnt);
	    return true;
	}
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! Naked triple - Three cells in a group each have only the same three numbers 
 * 	as possibilities (although they don't have to each have all three).
 * 	Since each MUST have one of the three, no other cells in the group can
 * 	have any of the three possible values, so those numbers can be removed
 * 	from the other cells in the group.
 * 	This can work for row, column, or square.  For example if three cells in
 * 	a group had only 1, 2, and 7 in their possibility list, then 1, 2, and 7
 * 	could be removed from the possibility list of every other cell in the
 * 	group.
 * 	N.B. It's possible for the cells to be in-line with each other AND in a
 * 	     block, so we could clear the possibilities from the block and the
 * 	     row or column they are in.
 */
template<const unsigned int N>
class naked_triple:public sudoku_method<N>
{
public:
    naked_triple():sudoku_method<N>("naked triple",3){
	NAKED_TRIPLE_DEBUG std::cerr << "naked_triple()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	NAKED_TRIPLE_DEBUG std::cerr << "naked_triple.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	size_t count=0;
	if((count=b->naked_apply(3))){
	    sudoku_method<N>::count_add(count);
	    NAKED_TRIPLE_DEBUG std::cerr << "naked triple success\n";
	    return true;
	}
	NAKED_TRIPLE_DEBUG std::cerr << "naked triple failure\n";
	return false;
    }


    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! hidden triple - There are two numbers that only appear in three squares in a
 * 	group, although those squares may have other possibilities.  That means
 * 	that we can not only remove any other possibilities from those three 
 * 	squares, but that we can also remove those three possibilities from any
 * 	other squares in the group.
 */
template<const unsigned int N>
class hidden_triple:public sudoku_method<N>
{
public:
    hidden_triple():sudoku_method<N>("hidden triple",3){
	HIDDEN_TRIPLE_DEBUG std::cerr << "hidden_triple()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	HIDDEN_TRIPLE_DEBUG std::cerr << "hidden_triple.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	size_t cnt;
	if((cnt=b->hidden_apply(3))){
	    sudoku_method<N>::count_add(cnt);
	    HIDDEN_TRIPLE_DEBUG std::cerr << "hidden triple success\n";
	    return true;
	}
	HIDDEN_TRIPLE_DEBUG std::cerr << "hidden triple failure\n";
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! Naked quad - Four cells in a group each have only the same four numbers as
 * 	possibilities (although they don't have to each have all four).
 * 	Since each MUST have one of the four, no other cells in the group can
 * 	have any of the four possible values, so those numbers can be removed
 * 	from the other cells in the group.
 * 	This can work for row, column, or square.  For example if four cells in
 * 	a group had only 1, 2, 5, and 7 in their possibility list, then 1, 2, 5,
 * 	and 7 could be removed from the possibility list of every other cell in
 * 	the group.
 */
template<const unsigned int N>
class naked_quad:public sudoku_method<N>
{

public:
    naked_quad():sudoku_method<N>("naked quad",3){
	NAKED_QUAD_DEBUG std::cerr << "naked_quad()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	NAKED_QUAD_DEBUG std::cerr << "naked_quad.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	size_t count=0;
	if((count=b->naked_apply(4))){
	    sudoku_method<N>::count_add(count);
	    NAKED_QUAD_DEBUG std::cerr << "naked quad success\n";
	    return true;
	}
	NAKED_QUAD_DEBUG std::cerr << "naked quad failure\n";
	return false;
    }


    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! hidden quad - There are four numbers that only appear in four squares in a
 * 	group, although those squares may have other possibilities.  That means
 * 	that we can not only remove any other possibilities from those four 
 * 	squares.
 */
template<const unsigned int N>
class hidden_quad:public sudoku_method<N>
{
public:
    hidden_quad():sudoku_method<N>("hidden quad",3){
	HIDDEN_QUAD_DEBUG std::cerr << "hidden_quad()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	HIDDEN_QUAD_DEBUG std::cerr << "hidden_quad.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	size_t cnt;
	if((cnt=b->hidden_apply(4))){
	    sudoku_method<N>::count_add(cnt);
	    HIDDEN_QUAD_DEBUG std::cerr << "hidden quad success\n";
	    return true;
	}
	HIDDEN_QUAD_DEBUG std::cerr << "hidden quad success\n";
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! intersection - when all of the possibilities (either two or three) for a
 * value in a group (a row, column, or block), are also in another group, then
 * that value can be removed from the second group. One of the things that
 * intersect will always be a block, and the other will be either a row or
 * column. That means that there are four possible types, row-block, block-row,
 * column-block, and block-column. If the block is the one that only has two or
 * three of the value in its possibilities, then the name starts with block-,
 * otherwise it starts with row- or column-, for example:
 * \verbatim
 * .-------.-------.-------.
 * | * * * | * * * | - X X |
 * |       |       | - - - | block-row intersection
 * |       |       | - - - | block contains value in two places both in
 * '-------'-------'-------' the row
 *
 *  X : A cell which may have the value X
 *  - : A cell which does not contain a candidate X
 *  * : Cells from which we can eliminate X
 * 
 *         It works the same when the shared cells are the only ones in the row
 * .-------.-------.-------.
 * | - - - | - - - | X - X |
 * |       |       | * * * | row-block intersection
 * |       |       | * * * | row can only contain value in two possible places
 * '-------'-------'-------'
 *         And the same works for columns as well, of course.
 * .-------.                    .-------.
 * |     - |                    |   *   |
 * |     - | column-block       |   *   | block-column
 * |     - | intersection       |   *   | intersection
 * .-------'                    '-------'
 * | * * X | column only has 3  | - X - | block only has two possible locations
 * | * * X | possible locations | - X - | for the value, both also in the column
 * | * * X | for value all in   | - - - |
 * '-------' the block          '-------'
 * |     - |                    |   *   |
 * |     - |                    |   *   |
 * |     - |                    |   *   |
 * '-------'                    '-------'
 * \endverbatim
 * We note that there are four types, row-block, column-block, block-row, and block-column
 * where whichever group is noted first, i.e. row, in row-block, is the one that
 * only has two or three squares with a particular value, the the one mentioned
 * second, if those squares a all in that group, can have the value removed
 * from their pvals.
 *
 */
template<const unsigned int N>
class intersection:public sudoku_method<N>
{
public:
    intersection():sudoku_method<N>("intersection",2){
	INTERSECTION_DEBUG std::cerr << "intersection()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	INTERSECTION_DEBUG std::cerr << "intersection.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	// check row-block, column-block, block-row, block-column
	// first row
	size_t count=0;
	bool retval=false;
	INTERSECTION_DEBUG std::cerr << "  checking for row-block-intersection\n";
	for(size_t row=0;row<N;row++){
	    if(count+=b->discern_intersection(GT_ROW,row,GT_BLOCK)){
		retval=true;
	    }
	}
	INTERSECTION_DEBUG std::cerr << "  finished rows\n";
	INTERSECTION_DEBUG std::cerr << "  checking for column-block-intersection\n";
	for(size_t col=0;col<N;col++){
	    if(count+=b->discern_intersection(GT_COLUMN,col,GT_BLOCK)){
		retval=true;
	    }
	}
	INTERSECTION_DEBUG std::cerr << "  finished columns\n";
	INTERSECTION_DEBUG std::cerr << "  checking for block-row-intersection\n";
	for(size_t block=0;block<N;block++){
	    if(count+=b->discern_intersection(GT_BLOCK,block,GT_ROW)){
		retval=true;
	    }
	}
	INTERSECTION_DEBUG std::cerr << "  finished block-rows\n";
	INTERSECTION_DEBUG std::cerr << "  checking for block-column-intersection\n";
	for(size_t block=0;block<N;block++){
	    if(count+=b->discern_intersection(GT_BLOCK,block,GT_COLUMN)){
		retval=true;
	    }
	}
	INTERSECTION_DEBUG std::cerr << "  finished block-columns\n";
	INTERSECTION_DEBUG std::cerr << "intersection().apply() finished; found " << count << " intersections, returning\n";
	sudoku_method<N>::count_add(count);
	return retval;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! x-wing looks for interlocking pairs of rows and columns each containing the
 * same possibility.  It calls interlock_apply() to do the work, which
 * treats x-wing as a member of the class of interlock algorithms like swordfish
 * and jellyfish.
 *
 * if there are only two cells with possible 4s in row 3, in columns 3 and 6
 * and also only two cells with possible     4s in row 8, in columns 3 and 6
 * then any other 4s in columns 3 and 6 can be removed.
 * Conversely,
 * if there are only two cells with possible 4s in column 3, in rows 3 and 6
 * and also only two cells with possible     4s in column 8, in rows 3 and 6
 * then any other 4s in rows 3 and 6 can be removed.
 *
 *       any 2s in columns 3 and 6 can be removed
 *                  /        \
 * rows   1   2   3   4   5   6   7   8   9
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   1  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   2  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   3  |   |   |4-----------4  |   |   |   | only 2 4s on this row
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   4  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   5  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   6  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   7  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   8  |   |   |4-----------4  |   |   |   | only 2 4s on this row
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   9  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 */
template<const unsigned int N>
class x_wing:public sudoku_method<N>
{
public:
    x_wing():sudoku_method<N>("x-wing",4){
	X_WING_DEBUG std::cerr << "x_wing()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	X_WING_DEBUG std::cerr << "x_wing.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->interlock_apply(2)){
	    sudoku_method<N>::incr_count();
	    return true;
	}
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! The y-wing class looks for three cells each 
 * with 2 members of their pvals, but between them only three pvals.  One of
 * the cells is the pivot and shares a member of pvals with each of the other
 * two.  They in turn, share a third pval.  For example, the three squares,
 * (with the pivot in the middle) could have pvals {1,8} {1,6} {6,8}.  
 * The first has to be in a group with the second, and the second in a group
 * with the third (row, column or block is a group), but all three can't be in
 * the same group.  If all that is true, then in the intersection of squares
 * visible from the first and the third, we can remove their shared value (in
 * the example, the 8) from all the square's pvals.
 *
 * The actual work is done by board::y_wing_apply()
 */
template<const unsigned int N>
class y_wing:public sudoku_method<N>
{
public:
    y_wing():sudoku_method<N>("y-wing",4){
	Y_WING_DEBUG std::cerr << "y_wing()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	Y_WING_DEBUG std::cerr << "y_wing::apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->y_wing_apply()){
	    Y_WING_DEBUG std::cerr << "success\n";
	    sudoku_method<N>::incr_count();
	    return true;
	}
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! 
 * The solution class swordfish, like x-wing, calls interlock_apply() to do
 * the dirty work.  The only difference is that x-wings have interlocking
 * pairs of column and rows with the same number, and
 * swordfish has interlocking triples of rows and columns with triples of the
 * same number.
 * 
 * Assume the marked cells are the only ones in their rows with 4s
 * 	row 1 has a 4 in columns 1 and 5
 * 	row 5 has a 4 in columns 5 and 9
 * 	row 8 has a 4 in columns 1 and 9
 * This is a swordfish in rows, i.e. three rows with pairs
 * that happen between them to only occupy the same three columns
 * If that happens, we can remove any other 4s from columns 1,5,9
 *
 *        Any number of 4s in columns 1, 5, and 9.
 *                      cols
 * rows   1   2   3   4   5   6   7   8   9
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   1  |*---------------*  |   |   |   |   | only 2 4s in this row
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   2  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   3  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   4  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   5  |   |   |   |   |*---------------*  | only 2 4s in this row
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   6  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   7  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   8  |*-------------------------------*  | only 2 4s in this row
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |
 *   9  |   |   |   |   |   |   |   |   |   |
 *      |   |   |   |   |   |   |   |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 */
template<const unsigned int N>
class swordfish:public sudoku_method<N>
{
public:
    swordfish():sudoku_method<N>("swordfish",4){
	SWORDFISH_DEBUG std::cerr << "swordfish()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	SWORDFISH_DEBUG std::cerr << "swordfish.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->interlock_apply(3)){
	    sudoku_method<N>::incr_count();
	    return true;
	}
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! 
 * The solution class jellyfish, like x-wing, and swordfish, calls
 * interlock_apply() to do the dirty work.  The only difference is that x-wings
 * have interlocking pairs of column and rows with the same possibile number
 * swordfish have interlocking triples of of rows and columns with the same
 * possibility, and jellyfish have interlocking quads of rows and columns
 * with the same possibility.
 */
template<const unsigned int N>
class jellyfish:public sudoku_method<N>
{
public:
    jellyfish():sudoku_method<N>("jellyfish",4){
	JELLYFISH_DEBUG std::cerr << "jellyfish()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	JELLYFISH_DEBUG std::cerr << "jellyfish.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->interlock_apply(4)){
	    sudoku_method<N>::incr_count();
	    return true;
	}
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! 
 * The solution class xy-chain, walks through the board and for each
 * square with only two pvals
 * 1) foreach pval
 * 2)     assert ownership of that pval
 * 3)     look for visible squares, with two pvals and which share the owned
 *        pval with the previous square, assert ownership of the other pval
 * 3)     walk from those  squares in turn doing the same, forming chains of
 *        implication, i.e.
 *    square pval1  pval2
 *     sq1   |1|     3     || bars means asserts ownership of 1
 *     sq2   |3|     1     also has one asserts 3
 *     sq3    3     |6|    also has 3 asserts 6
 *     sq4   |1|     6     also has 6 asserts 1 AND CAN SEE SQUARE 1
 * if atany point a square asserts ownership of the same value as
 * the original square, and they can see each other, then a proof by
 * contradiction has occured that the first square must use the other pval,
 * in this case 3.
 */
template<const unsigned int N>
class xy_chain:public sudoku_method<N>
{
public:
    xy_chain():sudoku_method<N>("xy-chain",5){
	XY_CHAIN_DEBUG std::cerr << "xy_chain()\n";
    }
    
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	std::vector<square*>chain;
	XY_CHAIN_DEBUG std::cerr << "xy_chain.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	for(size_t row=0;row<N;row++){
	    for(size_t col=0;col<N;col++){
		square &sq=b->b[row][col];
		if(sq.size()==2){
		    chain.push_back(&sq);
		    // yay, found the head of a chain.
		    // owned will be 0 and then 1
		    for(size_t c=0;c<2;c++){
			sq.set_owned(c);
			if(b->xy_chain_apply(chain)){
			    // yay, found one!
			    sudoku_method<N>::incr_count();
			    XY_CHAIN_DEBUG std::cerr << "success\n";
			    XY_CHAIN_DEBUG b->print_large();
			    return true;
			}
		    }
		    chain.pop_back();
		}
	    }
	}
	XY_CHAIN_DEBUG std::cerr << "failed\n";
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};

/*! 
 * The solution class simple_color, looking for rows, columns and blocks
 * with only two squares with that pval.
 * for val in 1-9
 *     find a row column or block with only two squares with that pval
 *     color one and push it on the stack
 *     while stack not empty
 *         pop a square from stack
 *         push at end of vector
 *         for row col block find only two of val in pval and
 *             color other square not my color
 *             push color on stack
 *     now that stack is empty we'll deal with vector
 *     for ctr=0; ctr < vector.len; ctr++
 *         for ctr2=ctr+1;ctr2<vector.len;ctr2++
 *             if(vector[ctr2] is different color from vector[ctr]
 *                 find shared neighbors of vector[ctr] and vector[ctr2]
 *                 any of them that aren't colored and have val in pvals
 *                     clear val from pvals
 *         
 */
template<const unsigned int N>
class simple_color:public sudoku_method<N>
{
public:
    simple_color():sudoku_method<N>("simple color",5){
	SIMPLE_COLOR_DEBUG std::cerr << "simple_color()\n";
    }
    
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	SIMPLE_COLOR_DEBUG std::cerr << "simple_color.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	// clear all colors to none
	b->clear_colors();
	SIMPLE_COLOR_LARGE_PRINT_DEBUG{
	    std::cerr << toorange << "board before simple color\n" << toblack;
	    b->print_large();
	}
	bool retval=false;
	for(size_t pval=1;pval<N+1;pval++){
	    SIMPLE_COLOR_DEBUG std::cerr << "  checking pval " << pval << '\n';
	    // look for any candidate we can seed the stack with
	    bool found_first=false;
	    std::map<size_t,std::vector<square*>> mvs;
	    for(size_t gt=GT_ROW;gt<GT_BLOCK+1;gt++){
		SIMPLE_COLOR_DEBUG{
		    std::cerr << "    walking through " << grouptype_2_name[gt] << '\n';
		}
		for(size_t which=0;which<N;which++){
		    mvs=b->get_possibilities(static_cast<grouptype>(gt),which);
		    if(mvs[pval].size()==2
			    && mvs[pval][0]->get_color()==color::none
			    && !mvs[pval][0]->check_applied_simple_color(pval)){
			SIMPLE_COLOR_DEBUG{
			    std::cerr << "    found candidates on " 
				<< grouptype_2_name[gt] << ' '
				<< which << ", pval " << pval << '\n';
			    for(auto sq : mvs[pval]){
				std::cerr << "      "
				    << print_sq_rcp(sq) << '\n';
			    }
			}
			found_first=true;
			break;
		    }
		}
		if(found_first) break;
	    }
	    if(!found_first){
		SIMPLE_COLOR_DEBUG{
		    std::cerr << "    found no rows/block/columns"
			" with only two squares with pval " << pval << '\n';
		}
		continue;
	    }
	    std::stack<square *> sqs;
	    mvs[pval][0]->set_color(color::red);
	    sqs.push(mvs[pval][0]);
	    SIMPLE_COLOR_DEBUG{
		std::cerr << "    first candidate on stack\n";
		std::cerr << "      " << print_sq_rcp(sqs.top()) << '\n';
	    }
	    std::vector<square*> chain;
	    while(!sqs.empty()){
		square* sq=sqs.top();
		sqs.pop();
		chain.push_back(sq);
		SIMPLE_COLOR_DEBUG{
		    std::cerr << "  top of loop\n"
			         "    o popping a square\n"
				 "    o pushing it on the chain\n"
				 "    o and looking for more links to color and push on stack\n";
		    std::cerr << "    popped "
			<< print_sq_rcp_color(sq)
			<< " from the stack\n"
			<< "      stack size now: " << sqs.size() << '\n'
			<< "      chain size is: " << chain.size() << '\n';
		}
		color curcolor=sq->get_color(), othercolor;
		if(curcolor==color::red){
		    othercolor=color::green;
		}else if(curcolor==color::green){
		    othercolor=color::red;
		}else{
		    SIMPLE_COLOR_DEBUG{
			std::cerr << "popped a square off of the stack and it was neither red or green! Aborting.\n"
			    << print_sq_rcp_color(sq) << '\n';
		    }
		    continue;
		}

		for(size_t gt=GT_ROW;gt<GT_BLOCK+1;gt++){
		    SIMPLE_COLOR_DEBUG{
			std::cerr << "    walking through " << grouptype_2_name[gt] << '\n';
		    }
		    switch(gt){
			case GT_ROW:
			    mvs=b->get_possibilities(static_cast<grouptype>(gt),sq->get_row());
			    break;
			case GT_COLUMN:
			    mvs=b->get_possibilities(static_cast<grouptype>(gt),sq->get_column());
			    break;
			case GT_BLOCK:
			    mvs=b->get_possibilities(static_cast<grouptype>(gt),
				b->get_block_num(sq));
			    break;
		    }
		    square* other=0;
		    if(mvs[pval].size()==2){
			if(mvs[pval][0]==sq){
			    other=mvs[pval][1];
			}else if(mvs[pval][1]==sq){
			    other=mvs[pval][0];
			}else{
			    SIMPLE_COLOR_DEBUG{
				std::cerr << "neither square is sq!\n";
				std::cerr << "sq: "
				    << print_sq_rcp_color(sq) << '\n'
				    << print_sq_rcp_color(mvs[pval][0]) << '\n'
				    << print_sq_rcp_color(mvs[pval][1]) << '\n';
			    }
			    break;
			}
			if(other->get_color()!=color::none){
			    SIMPLE_COLOR_DEBUG{
				std::cerr << "      found another square : "
				    << print_sq_rcp_color(other) << '\n'
				    << "        but it is already colored, skipping\n";
			    }
			    other=0;
			}
			    
		    }
		    if(other){
			SIMPLE_COLOR_DEBUG{
			    std::cerr << "      found another square: "
				<< print_sq_rcp_color(other) << '\n';
			    std::cerr << "        setting to ";
			    other->print_color(std::cerr,othercolor);
			    std::cerr << " and pushing on stack\n";
			}
			other->set_color(othercolor);
			sqs.push(other);
		    }
		}

	    } // while (!sqs.empty())
	    SIMPLE_COLOR_DEBUG{
		std::cerr << "    popped all of the stack, chain length "
		    << chain.size() << " on pval "
		    << pval << "\n";
		size_t chainval=0;
		for(square* sq : chain){
		    sq->set_applied_simple_color(pval);
		    std::cerr << "    chain[" << chainval << "] "
			<< print_sq_rcp_color(sq) << '\n';
		    ++chainval;
		}
	    }
	    if(chain.size()<3){
		for(square* sq : chain){
		    sq->set_color(color::none);
		}
		SIMPLE_COLOR_DEBUG{
		    std::cerr << "    chain size too small (" << chain.size()
			<< ") for a simple color chain (need 3 or more)\n";
		}
		continue;
	    }
	    RESPATH{
		std::cerr << "simple-color n" << pval << '{';
		bool firsttime=true;
		for(square* sq : chain){
		    if(!firsttime){
			std::cerr << ' ';
		    }
		    firsttime=false;
		    std::cerr << print_sq_rc_plus(sq);
		}
		std::cerr << "} ==>";
	    }
	    for(size_t ctr1=0;ctr1<chain.size()-1;ctr1++){
		color our_color=chain[ctr1]->get_color();

		for(size_t ctr2=ctr1+1;ctr2<chain.size();ctr2+=1){

		    if(chain[ctr2]->get_color()!=our_color){
			SIMPLE_COLOR_DEBUG{
			    std::cerr << "    looking for common neighbors of:\n";
			    std::cerr << "      chain[" << ctr1 << "] ("
				<< print_sq_rcp_color(chain[ctr1]) << ")\n"
				<< "      chain[" << ctr2 << "] ("
				<< print_sq_rcp_color(chain[ctr2]) << ")\n";
			}
			std::vector<square*> inter;
			std::vector<square*>::iterator vi;
			std::set<square*> sqs1i=b->get_neighbors(chain[ctr1],&square::no_color_filt);
			std::set<square*> sqs2i=b->get_neighbors(chain[ctr2],&square::no_color_filt);
			inter.resize(sqs1i.size()+sqs2i.size());
			vi=std::set_intersection(sqs1i.begin(),sqs1i.end(),sqs2i.begin(),sqs2i.end(),inter.begin());
			inter.resize(vi-inter.begin());
			SIMPLE_COLOR_DEBUG{
			    std::cerr << "      they share "
				<< inter.size() << " neighbors, looking"
			    		" for pval: " << pval << "\n";
			}
			bool did_something=false;
			for(square * sq : inter){
			    SIMPLE_COLOR_DEBUG{
				std::cerr << "        "
				    << print_sq_rcp_color(sq) << '\n';
			    }
			    did_something|=b->clear_pval_val(sq->get_row(),sq->get_column(),pval);
			}
			if(did_something){
			    SIMPLE_COLOR_DEBUG{
				std::cerr << "    cleared one or more pvals!\n";
				for(square* sq : inter){
				    std::cerr << "        "
					<< print_sq_rcp_color(sq) << '\n';
				}
			    }
			    sudoku_method<N>::incr_count();
			    retval=true;
			}
		    } //if(chain[ctr2]->get_color()!=our_color)
		} // ctr2
	    } // ctr1
	    RESPATH{
		std::cerr << '\n';
	    }
	} //for(size_t pval=1;pval<N+1;pval++)
	SIMPLE_COLOR_LARGE_PRINT_DEBUG{
	    std::cerr << topurple << "board after simple color\n" << toblack;
	    b->print_large();
	}
	b->clear_colors();
	SIMPLE_COLOR_DEBUG std::cerr << "failed\n";
	return retval;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b,size_t l)
    {
	SIMPLE_COLOR_DEBUG std::cerr << "registering simple_color\n";
	sudoku_method<N>::b=b;
	sudoku_method<N>::sort_level=l;
	b->register_strategy(this);
    };
};


/*!
 * This class contains the data about the puzzle as a vector of vectors of squares
 * and controls the running of solution methods
 */
template<const unsigned int N>
class board
{
public:
    /*! This enumerated type contains the values passed to dig_puzzle to
     * dig out cells with symmetry
     */
    enum symtype{ ST_NONE=0, ST_HORIZ=1, ST_VERT=2, ST_HV=4,ST_ROT=8,
    	ST_ROT90=16,ST_ROT180=32,ST_ROT270=64,ST_MDIAG=128,
	ST_ADIAG=256,ST_MADIAG=512
    };
    //! this vector is used to debug print symtype
    std::vector<std::string> symtype_st={"ST_NONE","ST_HORIZ","ST_VERT",
	"ST_HV","ST_ROT","ST_ROT90","ST_ROT180","ST_ROT270","ST_MDIAG",
	"ST_ADIAG","ST_MADIAG"
    };
    template<const unsigned int>
    friend
    std::ostream& operator<<(std::ostream&,symtype); //!<friend for access to board
    //friend naked_single<N>;//!<friend for direct access to board
    friend hidden_single<N>;//!<friend for direct access to board
    friend intersection<N>;//!<friend for direct access to board
    friend naked_double<N>;//!<friend for direct access to board
    friend hidden_double<N>;//!<friend for direct access to board
    friend naked_triple<N>;//!<friend for direct access to board
    friend hidden_triple<N>;//!<friend for direct access to board
    friend naked_quad<N>;//!<friend for direct access to board
    friend hidden_quad<N>;//!<friend for direct access to board
    friend xy_chain<N>;//!<friend for direct access to board
    friend simple_color<N>;//!<friend for direct access to board
    friend y_wing<N>;//!<friend for direct access to board
    friend x_wing<N>;//!<friend for direct access to board
    friend swordfish<N>;//!<friend for direct access to board
    friend jellyfish<N>;//!<friend for direct access to board

    // next two used by constructor for board that takes a string
    //! exception if constructor with string has a short string
    class board_shortstring: public std::exception{};
    //! exception if constructor with string has a long string
    class board_longstring: public std::exception{};

    board(); //!< default constructor
    board(std::string);//!<constructor which takes list of values and blanks
    board(const board&); //!< copy constructor
    board(std::vector<square>); //!< constructor which takes vectors of squares
    board(std::initializer_list<square>); //!< constructor for initializer list
    board&
    operator=(const board&); //!< assignment operator
    void
    print_counts(); //!< print to std::cout counts of heuristic application
    void
    print() const; //!< print to std::cout a simple representation of the board
    void
    print_large(); //!< print to std::cout the board with values and pvals
    bool
    generate(); //!< create a complete board with all squares set
    /*! a routine to dig out a cell from a completed board while respecting
     * symmetry, i.e. if there is horizontal symettry, after generating
     * a random square, it will also generate the same square reflected
     * across the x-axes.
     */
    bool
    dig_puzzle(symtype,size_t max_clues=32,bool status=false);
    //! return true if the puzzle is correct with all squares filled in
    bool
    is_solved();
    //! return bool for validity (i.e. if two squares in same row are 7 board is not valid)
    bool
    get_valid() const { return valid; };
    //! return the value of the square at row and col
    size_t
    get_val(size_t row, size_t col){ return b[row][col].get_val();}
    //! solve the puzzle using a brute force solution with back up.
    /*! 
     */
    size_t
    brute_force_solution(ssize_t how_many,bool return_board=false);
    //! solve the puzzle using a brute force solution with back up and try alternatives.
    size_t
    brute_force_check(bool stopafter2=true);
    //! solve the puzzle by trying the same things a person would do
    bool
    heuristic_solution(bool preserve_pvals=false);
    //! return number of set squares
    size_t
    count();
    //! return number of times we've backed up in brute force
    size_t get_backed_count(){ return backed_count; }
    size_t
    get_strategy_count(std::string);
    //! convert board to std::string
    operator std::string(){ return to_string(); };
    //! look for strategy with name and sets level then resorts
    bool
    set_strategy_sort_level(std::string name,size_t level);
    //! call back method called by each solution class
    void
    register_strategy(sudoku_method<N>*);
    std::vector<square>&
    operator[](size_t which){ return b[which]; };
    //! Wrapper around square::set_val(val,set_pval) which keeps count in sync
    void
    set_val(size_t row,size_t col,size_t val,bool set_pval=true);
    size_t
    size(){return b.size(); }
    std::vector<std::vector<square>>::iterator
    begin(){ return b.begin(); };
    std::vector<std::vector<square>>::iterator
    end(){ return b.end(); };

private:
    // private methods
    //! A helper routine for brute_force_solution()
    /* This routine walks through the board starting from r0c0 and looks
     * for the first square that has more than one pval and is unlocked
     * \param first_target tells us the place to start looking
     * \param checkb the board to check
     * \return the index of the new first target
     */
    size_t
    get_first_target(size_t first_target,board& checkb)
    {
	size_t max=N*N;
	for(;first_target<max;first_target++){
	    size_t row=first_target/N, col=first_target%N;
	    square& sq=checkb.b[row][col];
	    BRUTE_CHECK_DEBUG{
		std::cerr << "  square(" << row << ", " << col << ") " << sq.size();
		std::cerr << (sq.size()==1?" possibility, ":" possibilities, ");
		std::cerr << (sq.is_locked()?"locked":"not locked");
	    }
	    if(sq.size()>1 && !sq.is_locked()){
		BRUTE_CHECK_DEBUG std::cerr << " HIT!!!\n";
		// we found first place to change. Note if locked, there should only
		// be one, so the check is redundant, but something may change
		// later, so I code defensively.
		break;
	    }
	    BRUTE_CHECK_DEBUG std::cerr << '\n';
	}
	return first_target;
    }

    //! generate possible values for one square at row and col
    void
    generate_pvals(unsigned int row, unsigned int col,bool mark_invalid=true);
    //! update data structure which keeps track of maps of values to squares
    void
    update_possibilities();
    //! Update all the pvals on the board then call update_possibilities()
    void
    update_pvals();
    //! When a square has been set, all squares which can see that square have
    //! the square's val removed form their pvals
    void
    update_pvals_for_square(size_t row, size_t col);
    //! check for the pvals of a square being equal to a set of pvals
    /*! this test is used in test to check to see if something that
     * was supposed to affect the pvals in a certain way actually did
     * \param row the row of the square
     * \param col the column of the square
     * \param pvals a set of all the pvals we expect to find
     * \return true iff the pvals of the square exactly match pvals
     */
#if defined(SUDOKU_TESTING)
    // normally no one needs access to this outside of board and friends
    // but when testing they they to check effects of pvals of various things
public:
#endif
    bool
    check_pval_set(size_t row, size_t col, std::set<size_t> pvals)
    {
	CHECK_PVAL_SET_DEBUG{
	    std::cerr << "pvals: ";
	    for(size_t val : pvals){
		std::cerr << std::setw(2) << val;
	    }
	    std::cerr << '\n';
	}
	square& sq=b[row][col];
	CHECK_PVAL_SET_DEBUG std::cerr << sq;
	if(sq.size() != pvals.size()) return false;
	for(size_t ctr=0;ctr<sq.size();ctr++){
	    if(pvals.find(sq[ctr])==pvals.end()){
		return false;
	    }
	}
	return true;
    }
#if defined(SUDOKU_TESTING)
private:
#endif
    //! remove set values in square's column from pvals. called from generate_pvals
    void
    inline
    prune_column_pvals(unsigned int row, unsigned int col,std::vector<unsigned int> &sq,bool mark_invalid=true);
    //! remove set values in square's row from pvals. called from generate_pvals
    void
    inline
    prune_row_pvals(unsigned int row, unsigned int col,std::vector<unsigned int> &sq,bool mark_invalid=true);
    //! remove set values in square's block from pvals. called from generate_pvals
    void
    inline
    prune_block_pvals(unsigned int row, unsigned int col,std::vector<unsigned int> &sq,bool mark_invalid=true);
    //! Set color to none on whole board
    void
    clear_colors(){
	for(size_t row=0;row<N;row++){
	    for(size_t col=0;col<N;col++){
		b[row][col].set_color(color::none);
	    }
	}
    }
    //! helper routine so we don't have to duplicated this code two places
    /* this routine passes to std::sort beginning and ending iterators for
     * sorted strategies as well as a comparison routine to tell them if
     * one is less than another.
     */
    void
    sort_strategies()
    {
	std::sort(sorted_strategies.begin(),sorted_strategies.end(),
	    [](sudoku_method<N>*m1,sudoku_method<N>*m2){
		return m1->get_sort_level() < m2->get_sort_level();
	    }
	);
    }
    //! call register_strategies on all solution classes
    void
    register_strategies();
    //! how many time a particular strategy has been applied
    //! given a row and column number return a block number 0-8
    size_t
    get_block_num(size_t row, size_t col){ return root*(row/root)+col/root; }
    //! given a reference to a square return a block number 0-8
    size_t
    get_block_num(const square&sq){ return get_block_num(sq.get_row(),sq.get_column());}
    //! given a pointer to a square return a block number 0-8
    size_t
    get_block_num(const square*sq){ return get_block_num(*sq); }
    //! call to_string() and return a std::string representation of the board
    //! helper routine called by all hidden_XXX strategies except for hidden single via hidden_apply
    bool
    discern_hidden(size_t, grouptype, size_t);
    //! helper routine called by all naked_XXX strategies except for naked single via naked_apply
    bool
    discern_naked(size_t, grouptype, size_t);
    //! helper routine called by intersection's apply method to avoid having the same code four times.
    size_t
    discern_intersection(grouptype,size_t, grouptype);
    //! helper routine called by x-wing, swordfish, and jellyfish via interlock apply
    bool
    discern_interlock(size_t, grouptype);
    //! calls discern_hidden() for each row, column, and block as appropriate until one succeeds or all fail
    size_t
    hidden_apply(size_t level);
    //! calls discern_naked() for each row, column, and block as appropriate until one succeeds or all fail
    size_t
    naked_apply(size_t level);
    //! calls discern_interlock twice, once for rows, once for columns as appropriate
    bool
    interlock_apply(size_t level);
    //! xy_chain_apply proof by chains of implications that end in contradiction
    bool
    xy_chain_apply(std::vector<square*>& sv);
    //! walk each cell until a y-wing is found and applied or all cells are checked
    bool
    y_wing_apply();
    //! returns the right row of row/column/or block possibilities map as requested
    std::map<size_t,std::vector<square*>>&
    get_possibilities(grouptype what,size_t which);
    //! helper routine used by naked_apply to get argument to pass to discern naked 
    std::vector<square*>
    get_squares(grouptype what,size_t which,size_t depth,size_t min=2);
    //! helper routine used by naked_apply to get argument to pass to discern naked 
    std::vector<square*>
    get_squares(grouptype what,size_t which);
    //! purges val from pvals of all squares in block not in svect
    bool
    purge_block_except(size_t block, std::vector<square*> svect,size_t val);
    //! purges val from pvals of all squares in row not in svect
    bool
    purge_row_except(size_t row, std::vector<square*> svect,size_t val);
    //! purges val from pvals of all squares in column not in svect
    bool
    purge_column_except(size_t col, std::vector<square*>svect,size_t val);
    //! given a set of sqs, if they all share a row, col, and/or block, remove vals in set v from all other squares in shared group
    bool
    purge_from_set(std::set<square*>& sqs, std::set<size_t>& v);
    //! given grouptype of GT_ROW, for each row in rowset, walk all columns and for those not in colset remove v from their pvals, for grouptype of GT_COL do the opposite 
    bool
    purge_row_col_sets(grouptype,std::set<size_t> rowset,std::set<size_t> colset,size_t val);
    //! Dump all possibilities
    void
    dump_all_possibilities();
    //! Given a row/column/block possibilities, pretty print it for debugging
    void
    dump_possibilities(std::map<size_t,std::vector<square*>>);
    //! Given a row, dump just that row of row_possibilities for debugging
    void
    dump_row_possibilities(size_t row);
    //! Given a column, dump just that column of column_possibilities for debugging
    void
    dump_column_possibilities(size_t row);
    //! Given a block, dump just that block of block_possibilities for debugging
    void
    dump_block_possibilities(size_t row);
    //! return a set of all squares in the same row, column, or block as sq possibly filtered
    std::set<square*>
    get_neighbors(square* sq,bool (square::*)(square*)=&square::true_filt,bool not_self=true);
    //! Wrapper around square::clear_pval_val(val) that also keeps possibilities in sync
    bool
    clear_pval_val(size_t row,size_t col,size_t val);
    //! purge all vals in set s from the square[row][col]
    bool
    purge_set(size_t row, size_t col, std::set<size_t> s);
    //! for each square in sqs, remove and val not in vals from their pvals
    void
    reduce_to_set(std::set<square*>& sqs,std::set<size_t>& vals);
    //! calls square::reset on every square in the board
    void
    clear();
    //! returns false if any row does not have 1 through N else true
    bool
    validate_rows();
    //! returns false if any column does not have 1 through N else true
    bool
    validate_columns();
    //! returns false if any block does not have 1 through N else true
    bool
    validate_blocks();
    /*! creates a string representation of a board with set vals being 
     * themselves, and unknown squares being represented by '.'
     * our conversion operator std::string() just calls this.
     */
    std::string
    to_string()
    {
	std::string retval;
	std::ostringstream ss(retval);

	for( auto r : b){
	    for( auto s : r){
		size_t v=s.get_val();
		if(v){
		    ss << v;	
		} else {
		    ss << '.';
		}
	    }
	}
	return ss.str();
    }
    /*! helper routine to print symmetry types used when digging
     * \param os the stream to print to
     * \param st the symtype value to print
     */
    void
    print_st(std::ostream& os,symtype st)
    {
	if(!st){
	    os << "ST_NONE";
	}else{
	    bool first=true;
	    for(size_t ctr=1;st;ctr++){
		if(st&1){
		    if(!first){
			os << '|';
		    }
		    first=false;
		    os<<symtype_st[ctr];
		}
		st=symtype(st>>1);
	    }
	}
    }
    //! Routine called by our constructors to do common initialization
    void init();
    void
    inline
    dig_one(size_t row,size_t col, board& brd, symtype st);
    // private data
    //! This is the actual board data structure
    std::vector<std::vector<square>> b;
    //! Set to square root of N in init()
    size_t root;
    //! true of no row/column/or block contains 2 of the same number else false
    bool valid;
    //! true if valid is true and all cells are set to values
    bool solved;
    //! incremented by brute_solution each time it must back up. Can be HUGE because we can back up past the same place many times
    size_t backed_count;
    //! all the solution strategies used by heuristic_solution mapped by level
    //std::map<size_t, std::map<std::string, class sudoku_method<N>*>> strategies;
    //! all the solution strategies used by heuristic_solution sorted
    std::vector<class sudoku_method<N>*> sorted_strategies;
    //! The class that implements the naked single strategy
    naked_single<N> ns;
    //! The class that implements the hidden single strategy
    hidden_single<N> hs;
    //! The class that implements the naked double strategy
    naked_double<N> nd;
    //! The class that implements the hidden double strategy
    hidden_double<N> hd;
    //! The class that implements the naked triple strategy
    naked_triple<N> nt;
    //! The class that implements the hidden triple strategy
    hidden_triple<N> ht;
    //! The class that implements the naked quad strategy
    naked_quad<N> nq;
    //! The class that implements the hidden quad strategy
    hidden_quad<N> hq;
    //! The class that implements the intersection family of strategies
    intersection<N> intr;
    //! The class that implements the x-wing strategy
    x_wing<N> xw;
    //! The class that implements the y-wing strategy
    y_wing<N> yw;
    //! The class that implements the swordfish strategy
    swordfish<N> sf;
    //! The class that implements the jellyfish strategy
    jellyfish<N> jf;
    //! The class that implements the xy-chain strategy
    xy_chain<N> cpc;
    //! The class that implements the xy-chain strategy
    simple_color<N> sc;
    //! map of vals to map of rows to vector of squares in each row with val in pvals
    std::map<size_t,std::map<size_t,std::vector<square*>>> row_possibilities;
    //! map of vals to map of columns to vector of squares in each column with val in pvals
    std::map<size_t,std::map<size_t,std::vector<square*>>> column_possibilities;
    //! map of vals to map of blocks to vector of squares in each block with val in pvals
    std::map<size_t,std::map<size_t,std::vector<square*>>> block_possibilities;
    //! suppress_output is just so clear_pval_val() won't spit out any information when we are setting up a board.
    bool suppress_output=false;
};

template<const unsigned int N>
std::ostream&
operator<<(std::ostream& os,typename board<N>::symtype st)
{
    if(!st){
	os << "ST_NONE";
    }else{
	bool first=true;
	for(size_t ctr=1;st;ctr++){
	    if(!first) os << '|';
	    if(st&1){
		os<<board<N>::symtype_st[ctr];
	    }
	    st=st>>1;
	}
    }
    return os;
}

/*!
 * From a given square find all the other squares that share a row, column,
 * or block with it, and then pass each of those squares in turn to the fn
 * argument for vetting.
 * If the function returns true, then add them to a std::set<square *>.  When
 * done, return the set.
 * \param sq a pointer to the square whose neighbors will be inspected and
 * 	potentially returned in the set
 * \param fn a pointer to a square member method that takes a pointer to a
 *      square and returns a bool
 * \param not_self if true (default) don't include myself in the set of 
 *      neighbors, else do
 * \return std::set<square*> all the neighbors of sq that caused fn to return
 *      true
 */
template<const unsigned int N>
std::set<square*>
board<N>::get_neighbors(square* sq,bool (square::*fn)(square*),bool not_self)
{
    std::set<square*> sr;
    size_t row=sq->get_row();
    size_t col=sq->get_column();
    size_t block=get_block_num(row,col);
    // row/col min and max are within the block the square is in
    size_t row_min=root*(block/root),
	   row_max=row_min+root,
	   col_min=root*(block%root),
	   col_max=col_min+root;

    // look through the columns of the row the square is on
    for(size_t lcol=0;lcol<N;lcol++){
	// if we don't want to see ourselfs in the set skip us.
	if(not_self&&col==lcol) continue;
	// everyone else, if fn(square) is true, then
	if((sq->*fn)(&b[row][lcol])){
	    // add it to the output set
	    sr.insert(&b[row][lcol]);
	}
    }
    // Now look through all the squares in our column
    for(size_t lrow=0;lrow<N;lrow++){
	// if we don't want to return ourself in the set, skip us
	if(not_self && row==lrow) continue;
	// else, if fn(thesquare) returns true--
	if((sq->*fn)(&b[lrow][col])){
	    // add it to the set.
	    sr.insert(&b[lrow][col]);
	}
    }
    // now walk through the block the square is in
    for(size_t lrow=row_min;lrow<row_max;lrow++){
	for(size_t lcol=col_min;lcol<col_max;lcol++){
	    // skip us if we aren't including us in neighbors
	    if(not_self && row==lrow && col==lcol) continue;
	    // otherwise, if the fn(oursquare) is true
	    if((sq->*fn)(&b[lrow][lcol])){
		// add the square to the return set.
		sr.insert(&b[lrow][lcol]);
	    }
	}
    }
    // return the set of our neighbors
    return sr;
}

/*!
 * This routine is called back from the various solution strategies so
 * \param ssp a pointer to the solution method
 */
template<const unsigned int N>
inline
void
board<N>::register_strategy(sudoku_method<N>* ssp)
{
    REGISTER_STRATEGY_DEBUG{
	std::cerr << "  register_strategy from \"" << ssp->get_name() << "\"\n";
    }
    sorted_strategies.push_back(ssp);
}

//! contact all of the heuristics, give them us, and wake them up
/*!
 * This is only called from board<N>::init and is separated here just to 
 * make it cleaner there;) It passes to each of the heuristics two things, 
 * a pointer to the board, so that the heuristics can get to routines they
 * need to find stuff on the board, and the sort order. The heuristics sort
 * their sort order so that the board doesn't need an extra data structure
 * to associate the sort order with the heuristic. Why shouldn't they shoulder
 * that burden? They are already carrying information. They all inherit from
 * sudoku_method, and actually just pass the burden to her when they construct
 * her as parent.
 *
 * Finally we sort them into the order in which they will be invoked, with
 * smaller number heuristics always being tried before big number ones (except
 * that a sort order of zero disables a heuristic).
 */
template<const unsigned int N>
inline
void
board<N>::register_strategies(void)
{
    // here we are giving them a pointer to the board, and telling them
    // their sort order
    REGISTER_STRATEGY_DEBUG {
	std::cout << "asking all of the strategies to register\n";
    }
    hs.register_strategy(this,100);
    ns.register_strategy(this,105);
    intr.register_strategy(this,110);
    nd.register_strategy(this,120);
    hd.register_strategy(this,130);
    nt.register_strategy(this,140);
    ht.register_strategy(this,150);
    nq.register_strategy(this,160);
    hq.register_strategy(this,170);
    xw.register_strategy(this,180);
    yw.register_strategy(this,190);
    sf.register_strategy(this,200);
    jf.register_strategy(this,210);
    cpc.register_strategy(this,220);
    sc.register_strategy(this,230);
    sort_strategies();
    REGISTER_STRATEGY_DEBUG {
	std::cout << "  sorted strategies after all the registrations:\n";
	for(auto s : sorted_strategies){
	    std::cout << "    " << s << "\n";
	}
    }
}

//! set the sort level for a heuristic and resort the invokation order
/*!
 * This method allows someone, anyone, who knows, with access to a board
 * to change the order in which heuristics are invoked, or even to disable
 * certain heuristics. If you want a heuristic to be invoked early, give it
 * a low positive non-zero number. Zero disables a heuristic. We start all
 * with 100+, so you can move things first by giving them sort numbers < 100.
 * As an example, if you wanted to run hidden variants first for a board for
 * which you had a pointer b, you could do
 * something like:
\code
    b->set_strategy_sort_level("hidden quad",1);
    b->set_strategy_sort_level("hidden triple",3);
    b->set_strategy_sort_level("hidden double",5);
    b->set_strategy_sort_level("hidden single",7);
\endcode
 * \param name the name of a heuristic
 * \param level the desired new sort level or order of a heuristic
 * \return bool true if the heuristic existed and we set the sort order, or false if it didn't exist
 */
template<const unsigned int N>
bool
board<N>::set_strategy_sort_level(std::string name,size_t level)
{
    STRATEGY_SORT_LEVEL_DEBUG {
	std::cout << "set_strategy_sort_level(" << name << "," << level << ")\n";
    }
    bool success=false;
    for(auto s : sorted_strategies){
	if(s->get_name() == name){
	    STRATEGY_SORT_LEVEL_DEBUG{
		std::cout << "  found " << s->get_name()
		    << ", setting level\n\n";
	    }
	    s->set_sort_level(level);
	    success=true;
	    break;
	}
    }
    sort_strategies();
    return success;
}

/*!
 * \param what - one of GT_ROW, GT_COLUMN, or GT_BLOCK
 * \param which - a value 0 through 8 asking for a map for
 * that particular row/column/block of pvals (1-9) to vectors of squares
 * 
 * \return a reference to a map of pvals (possible values) to vector<square*>
 * in which each of the possible values 1-9 is mapped to a vector of squares
 * in a row/column/block containing that possibility in their pvals, for example
 * mvs=b->get_possibilities(GT_ROW,7) returns us a map for row 7
 * such that mvs[2] returns us a vector<square*> of all the squares
 * on row 7 with 2 in their pvals (possible values). Since they are returned
 * by reference there are no copies made.
 */
template<const unsigned int N>
inline
std::map<size_t,std::vector<square*>>&
board<N>::get_possibilities(grouptype what,size_t which)
{
    switch(what){
	case GT_ROW:
	    return row_possibilities[which];
	    break;
	case GT_COLUMN:
	    return column_possibilities[which];
	    break;
	case GT_BLOCK:
	    return block_possibilities[which];
	    break;
    }
    return block_possibilities[which];
}

template<const unsigned int N>
inline
std::vector<square*>
board<N>::get_squares(grouptype what,size_t which,size_t depth,size_t min)
{
    std::vector<square*> retval;
    size_t size;
    switch(what){
	case GT_ROW:
	    for(size_t col=0;col<N;col++){
		size=b[which][col].size();
		if(size>=min && size<=depth){
		    retval.push_back(&b[which][col]);
		}
	    }
	    break;
	case GT_COLUMN:
	    for(size_t row=0;row<N;row++){
		size=b[row][which].size();
		if(size>=min && size<=depth){
		    retval.push_back(&b[row][which]);
		}
	    }
	    break;
	case GT_BLOCK:
	    size_t row_min=root*(which/root),
		   row_max=row_min+root,
		   col_min=root*(which%root),
		   col_max=col_min+root;
	    for(size_t row=row_min;row<row_max;row++){
		for(size_t col=col_min;col<col_max;col++){
		    size=b[row][col].size();
		    if(size>=min && size<=depth){
			retval.push_back(&b[row][col]);
		    }
		}
	    }
	    break;
    }
    return retval;
}

/*!
 * discern hidden looks for pairs, triples, or quads of squares in the same
 * group that are the only two, three, or four respectively that have the
 * same group of 2, 3, or 4 pvals (n.b. they don't all have to have the whole
 * group, just 2 or more, (technically 1 or more but those are caught as naked
 * or hidden singles with special purpose code), but there has to be 3 vals in
 * total, for example, for the hidden triples that are shared among three
 * squares each of which has at least two, and no other squares in the group
 * can have any of them.
 * For example if one square in a column has pvals { 1,3,7,9 }, another has
 * {1,3,8}, another has {3,7}, but no other squares in that column, have 1,
 * 3, or 7 in their pvals, we should find a hidden triple on 1, 3, and 7.
 * As a result, the three squares should have their pvals stripped of everything
 * but 1, 3, and 7, i.e. become: { 1,3,7 }, {1,3}, and {3,7}.  We have already
 * discerned that the other six squares in the column do not have 1, 3, or 7
 * in them.  Additionally, we check to see if the three squares with the 
 * hidden triple are in the same block, and if so, all the squares in that
 * block have 1, 3, and 7 removed from them.  At exit, the three squares now
 * look like a naked triple.  The same applies analogously to doubles and
 * quads.  We don't go higher than quads, although the code would work just
 * fine for it, because if we know two values in a row, a hidden 5 would 
 * leave a naked double, a hidden quad leaves a naked triple, etc...
 * N.B. this routine is an unrolled recursive routine
 * \param depth How many we need to make a group, we only use 2, 3, or 4 for hidden double, triple, or quad.
 * \param gt one of GT_ROW, GT_COLUMN, or GT_BLOCK
 * \param which the row, column, or block number
 * \return bool true if we found what we were looking for and as a result made some change in some square's pvals.  If we find a hidden whatever, but no pval values get cleared, or if we don't find a hidden whatever, we return false.
 *
 */
template<const unsigned int N>
bool
board<N>::discern_hidden(size_t depth, grouptype gt, size_t which)
{
    std::vector<size_t> vals; // walks through all vals 1-N
    std::vector<size_t> sizes;
    std::vector<std::set<square*>> sets;
    // next we reserve space for the data that will be in the various vectors
    // so that we can assign like: vals[2]=  without crashing.
    vals.resize(depth);
    sets.resize(depth);
    sizes.resize(depth);

    std::map<size_t,square::matched_type> matched_map={
	{2,square::matched_type::AM_HIDDEN_DOUBLE},
	{3,square::matched_type::AM_HIDDEN_TRIPLE},
	{4,square::matched_type::AM_HIDDEN_QUAD}
    };
    std::map<size_t,std::string> matched_names={
	{2,"hidden double"},
	{3,"hidden triple"},
	{4,"hidden quad"}
    };
    std::map<size_t,std::vector<square*>>&
	possibilities = get_possibilities(gt,which);
    std::vector<size_t> candidate_vals;
    DISCERN_HIDDEN_DEBUG{
	std::cerr << "discern_hidden(depth: " << depth << " (" << matched_names[depth]
	    << "), grouptype: " << grouptype_names[gt] << ", which: " 
	    << which << ")\n\n"
	    << "  checking for vals with [2, " << depth << "] "
	       "candidate squares with the val in their pvals\n";
    }
    for(size_t cand=1;cand<=N;cand++){
	size_t sz=possibilities[cand].size();
	DISCERN_HIDDEN_DEBUG{
	    std::cerr << "    " << cand
		<< " – " << sz
	        << " squares have " << cand << " in their pvals";
	}
	if(sz>=2 && sz<=depth){
	    DISCERN_HIDDEN_DEBUG std::cerr << " — pushing on candidate_vals";
	    candidate_vals.push_back(cand);
	}
	DISCERN_HIDDEN_DEBUG std::cerr << '\n';
    }
    size_t the_size=candidate_vals.size();
    DISCERN_HIDDEN_DEBUG{
	std::cerr << "  there are " << the_size << " candidates\n";
    }
    if(the_size < depth){
	DISCERN_HIDDEN_DEBUG{
	    std::cerr << "    that's not enough for a " << matched_names[depth]
		<< ", so taking a quick exit, return false\n\n";
	}
	return false;
    }
    std::vector<size_t> slots; // indices into vector of candidate valse;
    for(size_t i=0;i<depth;i++){
	// set to look at the first depth vals first
	slots.push_back(i);
    }
    size_t tomod=depth-1;	// start by looking at last slot
    DISCERN_HIDDEN_DEBUG std::cerr << '\n';
    while(true){
	DISCERN_HIDDEN_DEBUG{
	    std::cerr << "top of main loop\n";
	    std::cerr << "  slots:   ";
	    for(auto slot : slots){
		std::cerr << ' ' << slot;
	    }
	    std::cerr << '\n';
	    std::cerr << "          ";
	    for(size_t i=0;i<depth;i++){
		std::cerr << "  ";
	    }
	    std::cerr << "^\n";
	}
	// check for hidden depth
	std::set<square*> test_vals;
	for(size_t slot : slots){
	    for(square* s : possibilities[candidate_vals[slot]]){
		test_vals.insert(s);
	    }
	}
	if(test_vals.size()==depth){
	    bool real_hidden=false;
	    for(square* sq : test_vals){
		// bad test. we can be <= depth and still have a pval not in
		// candidate_vals
		DISCERN_HIDDEN_DEBUG std::cerr << "    " << *sq;
		if(sq->size() > depth){
		    real_hidden=true;
		    DISCERN_HIDDEN_DEBUG std::cerr << "      size " << sq->size() << " is greater than depth: " << depth << '\n';
		}
	    }
	    if(real_hidden){
		// found a hidden variant
		DISCERN_HIDDEN_DEBUG std::cerr << "hidden!!!!\n";
		// first!  We have to see if this exact set of squares has
		// already been found.
		// set_applied_set
		bool applied_sets=true;
		for(auto sq : test_vals){
		    if(!sq->set_applied_set(matched_map[depth],test_vals)){
			applied_sets=false;
			break;
		    }
		}
		if(applied_sets){
		    // here we know that we hadn't already found them
		    // now purge extra pvals
		    // std::vector<size_t> candidate_vals;
		    // anything that ISN'T in candidate_vals has to be removed 
		    // from std::set<square*> test_vals;
		    DISCERN_HIDDEN_DEBUG std::cerr << "not already found\n";
		    DISCERN_HIDDEN_DEBUG{
			std::cerr << "  what do you know! found it!\n";
			for(square* sq : test_vals){
			    std::cerr << "    " << *sq;
			}
			std::cerr << "    vals are";
			for(size_t slot : slots){
			    std::cerr << " " << candidate_vals[slot];
			}
			std::cerr << '\n';
		    }
		    std::set<size_t> the_vals;
		    for(size_t slot: slots){
			the_vals.insert(candidate_vals[slot]);
		    }
		    RESPATH{
			std::cerr << "hidden-";
			switch(depth){
			    case 2:
				std::cerr << "pairs";
				break;
			    case 3:
				std::cerr << "triples";
				break;
			    case 4:
				std::cerr << "quads";
				break;
			}
			std::cerr << "-in-a-" << grouptype_2_name[gt];
			std::cerr << " {";
			std::set<size_t>::iterator it;
			bool first_time=true;
			for(it=the_vals.begin();it!=the_vals.end();it++){
			    if(!first_time){
				std::cerr << ' ';
			    }
			    first_time=false;
			    std::cerr << "n" << *it;
			}
			std::cerr << "}";
			std::set<square *>::iterator sit;
#if defined(SHOW_RESPATH)
			switch(gt){
			    case GT_ROW:
				std::cerr << "r" << (*(test_vals.begin()))->get_row()+1;
				std::cerr << "{";
				first_time=true;
				for(sit=test_vals.begin();sit!=test_vals.end();sit++){
				    if(!first_time){
					std::cerr << ' ';
				    }
				    std::cerr << "c" << (*sit)->get_column()+1;
				}
				std::cerr << '}';
				break;
			    case GT_COLUMN:
				std::cerr << "{";
				first_time=true;
				for(sit=test_vals.begin();sit!=test_vals.end();sit++){
				    if(!first_time){
					std::cerr << ' ';
				    }
				    std::cout << "r" << (*sit)->get_row()+1;
				}
				std::cerr << "}c" << (*(test_vals.begin()))->get_column()+1;
				break;
			    case GT_BLOCK:
				std::cerr << "{";
				first_time=true;
				for(sit=test_vals.begin();sit!=test_vals.end();sit++){
				    if(!first_time){
					std::cerr << ' ';
				    }
				    first_time=false;
				    std::cerr << "r" << (*sit)->get_row()+1 << "c" << (*sit)->get_column()+1;
				}
				std::cerr << "}";
			}
#endif
		    }
		    // get rid of any thing not in set of vals, i.e. turns
		    // a hidden triple to a naked triple.
		    reduce_to_set(test_vals,the_vals);
		    RESPATH std::cerr << '\n';
		    return true;
		}else{
		    // here we know we already found this one
		    DISCERN_HIDDEN_DEBUG std::cerr << "already found\n";
		}
	    }else{
		// Found a naked variant but we won't do anything about it
		// it will be found and counted as a nekkid variant in
		// discern_naked.
		// This is a hard choice. We know what is going on right
		// now and could claim this.  The work is already done.
		// The only reason I don't is because if I start shooting
		// from the hip like that, instead of dealing with each thing
		// in its place I will surely create weird bugs. It's a
		// tradeoff between efficiency and maintainability. The 
		// small increase in efficiency is not worth the hit in
		// maintainability to me.
		DISCERN_HIDDEN_DEBUG std::cerr << "nekkid!!!!\n";
	    }
	}else{

	    // didn't succeed, fix it;
	    DISCERN_HIDDEN_DEBUG std::cerr << "    Nope. There are " << test_vals.size() << " squares that share the pval\n";
	}
	DISCERN_HIDDEN_DEBUG{
	    std::cerr << "  Didn't find a " << matched_names[depth]
		<< " bumping up the slots\n"
		<< "  checking for slots[tomod]: " << slots[tomod]
		<< " == the_size-1: " << the_size-1 << " (number of candidates)\n"
		<< "    (which would mean that we are at the end of the internal loop)\n";
	}
	if(slots[tomod] == the_size-1){
	    DISCERN_HIDDEN_DEBUG std::cerr << "  yes, end of internal loop\n";
	    ssize_t tmptomod=tomod-1;
	    DISCERN_HIDDEN_DEBUG{
		std::cerr << "    backing tmptomod: "
			<< "  " << std::setw(2) << tmptomod << '\n';
	    }
	    while(tmptomod>=0 && slots[tmptomod]==slots[tmptomod+1]-1){
		DISCERN_HIDDEN_DEBUG std::cout << "    backing tmptomod: ";
		--tmptomod;
		DISCERN_HIDDEN_DEBUG std::cout << "  " << std::setw(2) << tmptomod << '\n';
	    }
	    DISCERN_HIDDEN_DEBUG{
		std::cerr << "    slot #   -1 0 1 2 3\n"
			  << "    ~~~~~~~~~~~~~~~~~~~\n"
			  << "    slots   :  ";
		for( size_t slot : slots){
		    std::cerr << ' ' << slot;
		}
		std::cerr << '\n';
	    }
	    
	    if(tmptomod==-1){
		DISCERN_HIDDEN_DEBUG{
		    std::cerr << "              x\n";
		    std::cerr << "    backed off front, no more, quitting\n";
		}
		break;
	    }else{
		DISCERN_HIDDEN_DEBUG{
		    std::cerr << "                ";
		    for(ssize_t i=0;i<tmptomod;i++){
			std::cerr << "  ";
		    }
		    std::cerr << "^\n";
		}
		++slots[tmptomod];
		for(++tmptomod;tmptomod<static_cast<ssize_t>(depth);++tmptomod){
		    slots[tmptomod]=slots[tmptomod-1]+1;
		    DISCERN_HIDDEN_DEBUG{
			std::cerr << "               ";
			for( size_t slot : slots){
			    std::cerr << ' ' << slot;
			}
			std::cerr << '\n';
			std::cerr << "                ";
			for(ssize_t i=0;i<tmptomod;i++){
			    std::cerr << "  ";
			}
			std::cerr << "^\n";
		    }
		}
	    }
	}else{
	    ++slots[tomod];
	    DISCERN_HIDDEN_DEBUG{
		std::cerr << "    Just bumped up slots[tomod]"
		    << ", slots[" << tomod << "] is now: "
		    << slots[tomod] << '\n';
	    }
	}
	DISCERN_HIDDEN_DEBUG{
	    std::cerr << "  done with internal loop adjustments\n";
	    std::cerr << "end of main loop slots are: ";
	    for(auto slot : slots){
		std::cerr << ' ' << slot;
	    }
	    std::cerr << "\n\n";
	}
    }
    return false;
}

/*!
 * The routine finds examples of naked subsets.  A naked subset is a set of K
 * squares in a group that between them have K digits in their pvals (possible
 * values).  If K==2, we have a naked double, etc... For K>2, the squares don't
 * each have to have all the possible values in the set, for example a naked
 * triple could be three squares in a row, column, or block, with values 1, 3,
 * and 7 distributed between the three cells as {1,7}, {1,3}, and {3,7}.  It
 * could also be {1,3,7}, {1,3,7}, {1,3,7}.  Each naked subset corresponds to
 * a hidden subset, for example if there are seven unsolved squares in a row,
 * two squares solved for 2 and 9, and a naked subset on 1,3, and 7, there
 * would be a hidden quad on 4, 5, 6, and 8.
 * \param depth 2 for naked double, 3 for naked triple, or 4 for naked quad
 * \param gt tells us whether to look at rows, columns or blocks
 * \param which tells us which row column or block to look at
 * \return bool true if we found a naked double triple or quad and as a result, some pvals were removed from one or more squares
 */
template<const unsigned int N>
bool
board<N>::discern_naked(size_t depth, grouptype gt, size_t which)
{
    std::map<size_t,square::matched_type> matched_map={
	{2,square::matched_type::AM_NAKED_DOUBLE},
	{3,square::matched_type::AM_NAKED_TRIPLE},
	{4,square::matched_type::AM_NAKED_QUAD}
    };
    std::map<size_t,std::string> matched_names={
	{2,"naked double"},
	{3,"naked triple"},
	{4,"naked quad"}
    };
    // fetch only the squares with [2,depth] pvals
    std::vector<square*> the_squares=get_squares(gt,which,depth);
    std::vector<size_t> slots;// indices of current candidates into the_squares
    for(size_t ctr=0;ctr<depth;ctr++){
	// first default to 0,1...depth-1
	slots.push_back(ctr);
    }
    size_t the_size=the_squares.size(); // how many squares with 2-depth pvals
    if(the_size < depth){
	// quick exit if there aren't enough candidates for depth
	DISCERN_NAKED_DEBUG{
	    std::cerr << "discern_naked for " << matched_names[depth]
	        << ", " << the_size
		<< " candidate square"
		<< (the_size==1?"":"s")
		<< " but depth is " << depth
		<< " return false\n";
	}
	return false;
    }

    DISCERN_NAKED_DEBUG{
	std::cerr << "DISCERN_NAKED--looking for: " << matched_names[depth] << "\n";
    }
    size_t tomod=depth-1;	// start by looking at last slot
    while(true){
	DISCERN_NAKED_DEBUG{
	    std::cerr << "top of main loop\n";
	    std::cerr << "  slots:   ";
	    for(auto slot : slots){
		std::cerr << ' ' << slot;
	    }
	    std::cerr << '\n';
	    std::cerr << "          ";
	    for(size_t i=0;i<depth;i++){
		std::cerr << "  ";
	    }
	    std::cerr << "^\n";
	}
	std::set<size_t> test_pvals;
	// first test for solution by shoving the pvals of the squares
	// indexed by slot into a set.
	DISCERN_NAKED_DEBUG{
	    std::cerr << "  checking all the pvals to see if there"
		" are exactly depth (" << depth
		<< ") of them.\n    If so, it is a "
		<< matched_names[depth] << '\n';
	}
	for(size_t slot : slots){
	    for(size_t ctr=0;ctr<the_squares[slot]->size();ctr++){
		test_pvals.insert((*the_squares[slot])[ctr]);
	    }
	}
	DISCERN_NAKED_DEBUG{
	    std::cerr << "    pvals {";
	    for(size_t val : test_pvals){
		std::cerr << ' ' << val;
	    }
	    std::cerr << " }\n";
	}
	// a naked double will have 2 pvals, triple 3, and quad 4
	if(test_pvals.size() == depth){
	    DISCERN_NAKED_DEBUG{
		std::cerr << "  found a " << matched_names[depth] << '\n';
		for(size_t slot : slots){
		    std::cerr << "    "
			<< print_sq_rcp(the_squares[slot]) << '\n';
		}
	    }
	    // found naked.
	    // make the set of square *s we'll use for purge_from_set()
	    // and to mark the squares as being already used for
	    // NAKED N
	    std::set<square*> sq_set;
	    for(size_t slot : slots){
		sq_set.insert(the_squares[slot]);
	    }
	    bool applied_sets=true;
	    for(auto sq : sq_set){
		if(!sq->set_applied_set(matched_map[depth],sq_set)){
		    applied_sets=false;
		    break;
		}
	    }
	    if(applied_sets){
		RESPATH {
		    std::cerr << "naked-";
		    switch(depth){
			case 2:
			    std::cerr << "pairs";
			    break;
			case 3:
			    std::cerr << "triples";
			    break;
			case 4:
			    std::cerr << "quads";
			    break;
		    }
		    std::cerr << "-in-a-" << grouptype_2_name[gt];
		    std::cerr << " {";
		    std::set<size_t>::iterator it;
		    bool first_time=true;
		    for(it=test_pvals.begin();it!=test_pvals.end();it++){
			if(!first_time){
			    std::cerr << ' ';
			}
			first_time=false;
			std::cerr << "n" << *it;
		    }
		    std::cerr << "}";

#if defined(SHOW_RESPATH)
		    switch(gt){
			case GT_ROW:
			    {
			    std::set<square*>::iterator it;
			    std::cerr << "r" << (*sq_set.begin())->get_row()+1 << "{";
			    bool first_time=true;
			    for(it=sq_set.begin();it!=sq_set.end();it++){
				if(!first_time){
				    std::cerr << ' ';
				}
				first_time=false;
				std::cerr << "c" << (*it)->get_column()+1;
			    }
			    std::cerr << "}";
			    }
			    break;
			case GT_COLUMN:
			    {
				std::cerr << '{';
				std::set<square*>::iterator it;
				bool first_time=true;
				for(it=sq_set.begin();it!=sq_set.end();it++){
				    if(!first_time){
					std::cerr << ' ';
				    }
				    first_time=false;
				    std::cerr << "r" << (*it)->get_row()+1;
				}
				std::cerr << "}c" << (*sq_set.begin())->get_column()+1;
			    }

			    break;
			case GT_BLOCK:
			    {
				std::cerr << '{';
				std::set<square*>::iterator it;
				bool first_time=true;
				for(it=sq_set.begin();it!=sq_set.end();it++){
				    if(!first_time){
					std::cerr << ' ';
				    }
				    first_time=false;
				    std::cerr << "r" << (*it)->get_row()+1
					<< "c" << (*it)->get_column()+1;
				}
				std::cerr << "}";
			    }
			    break;
		    }
#endif
		    std::cerr << " ==>";
		}
		bool did_something=purge_from_set(sq_set, test_pvals);
		RESPATH std::cerr << "\n";
		DISCERN_NAKED_DEBUG{
		    std::cerr << "discern naked found something, "
			  << (did_something?"and cleared some pvals":
				  "but cleared no pvals")
			  << ", returning\n";
		}
		return did_something;
	    }else{
		DISCERN_NAKED_DEBUG{
		std::cerr << "  these squares were already found, skipping\n";
		}
	    }
	}else{
	    DISCERN_NAKED_DEBUG std::cerr << "    Nope. There are " << test_pvals.size() << " pvals between all the squares.\n";
	}
	DISCERN_NAKED_DEBUG{
	    std::cerr << "  Didn't find a " << matched_names[depth]
		<< " bumping up the slots\n"
		<< "  checking for slots[tomod]: " << slots[tomod]
		<< " == the_size-1: " << the_size-1 << " (number of candidates)\n"
		<< "    (which would mean that we are at the end of the internal loop)\n";
	}
	if(slots[tomod] == the_size-1){
	    DISCERN_NAKED_DEBUG std::cerr << "  yes, end of internal loop\n";
	    ssize_t tmptomod=tomod-1;
	    DISCERN_NAKED_DEBUG{
		std::cerr << "    backing tmptomod: " << std::right
			<< "  " << std::setw(2) << tmptomod << '\n';
	    }
	    while(tmptomod>=0 && slots[tmptomod]==slots[tmptomod+1]-1){
		--tmptomod;
		DISCERN_NAKED_DEBUG{
		    std::cerr << "    backing tmptomod: "
			    << "  " << std::setw(2) << tmptomod << '\n';
		}
	    }
	    DISCERN_NAKED_DEBUG{
		std::cerr << "    slot #   -1 0 1 2 3\n"
			  << "    ~~~~~~~~~~~~~~~~~~~\n"
			  << "    slots   :  ";
		for( size_t slot : slots){
		    std::cerr << ' ' << slot;
		}
		std::cerr << '\n';
	    }
	    
	    if(tmptomod==-1){
		DISCERN_NAKED_DEBUG{
		    std::cerr << "              x\n";
		    std::cerr << "    backed off front, no more, quitting\n";
		}
		break;
	    }else{
		DISCERN_NAKED_DEBUG{
		    std::cerr << "                ";
		    for(ssize_t i=0;i<tmptomod;i++){
			std::cerr << "  ";
		    }
		    std::cerr << "^\n";
		}
		++slots[tmptomod];
		for(++tmptomod;tmptomod<static_cast<ssize_t>(depth);++tmptomod){
		    slots[tmptomod]=slots[tmptomod-1]+1;
		    DISCERN_NAKED_DEBUG{
			std::cerr << "               ";
			for( size_t slot : slots){
			    std::cerr << ' ' << slot;
			}
			std::cerr << '\n';
			std::cerr << "                ";
			for(ssize_t i=0;i<tmptomod;i++){
			    std::cerr << "  ";
			}
			std::cerr << "^\n";
		    }
		}
	    }
	}else{
	    ++slots[tomod];
	    DISCERN_NAKED_DEBUG{
		std::cerr << "    Just bumped up slots[tomod]"
		    << ", slots[" << tomod << "] is now: "
		    << slots[tomod] << '\n';
	    }
	}
	DISCERN_NAKED_DEBUG{
	    std::cerr << "  done with internal loop adjustments\n";
	    std::cerr << "end of main loop slots are: ";
	    for(auto slot : slots){
		std::cerr << ' ' << slot;
	    }
	    std::cerr << "\n\n";
	}
    }
    return false;
}

//! discern_intersection is called by intersection apply to find intersections
/*!
 * discern_intersection looks for one of
 * row-block-intersection, column-block-intersection,
 * block-row-intersection, block-column-intersection
 * For block-column-intersection, primary will be GT_BLOCK, and secondary
 * will be GT_COLUMN. which refers to the primary, i.e. if the primary is
 * GT_ROW, which tells us which row we're looking at. 
 * For each possible pval, [1,9], we look in which for pvals which only
 * have two or three occuring in primary[which]. For those we find, we
 * check to see if they also all occur in the secondary, i.e. if
 * primary == GT_COLUMN, which == 7, and secondary == GT_BLOCK we look
 * through column 7 for each possible pval and if there are two or three
 * we then check to see if they also share a block. If so, we have found
 * our intersection.
 * \param primary One of GT_BLOCK, GT_ROW, or GT_COLUMN
 * \param which which instance of block row or column, i.e. it would be a row number
 * \param secondary One of GT_BLOCK, GT_ROW, or GT_COLUMN. N.B. a primary
 * 			of GT_BLOCK must have one of GT_ROW or GT_COLUMN as
 * 			secondary. A primary of GT_ROW or GT_COLUMN must
 * 			have GT_BLOCK as secondary.
 * \return count of found intersection that caused pvals to be 
 *              cleared somewhere on the board
 */
template<const unsigned int N>
size_t
board<N>::discern_intersection(grouptype primary,size_t which, grouptype secondary)
{
    size_t count=0;
    struct gt_info{
	std::string name;
	std::string shortname;
    };
    std::map<grouptype,gt_info> gts {
	{GT_ROW, { "row","r" }},
	{GT_COLUMN, { "column","c" }},
	{GT_BLOCK, { "block", "b" }}
    };
    DISCERN_INTERSECTION_DEBUG{
	std::cerr << "  " << gts[primary].name << ": " << which << " - "
	<< gts[secondary].name << "\n";
    }
    // row val vector
    //  0   1  { sq1, sq2, ... }
    //      2  { sq1, sq2, ... }
    //      .
    //      .
    //      . 
    //      9  { sq1, sq2, ... }
    //
    //        mvs is all this, a map from all the vals to vectors of 
    //       ________/\_______    pointers to squares that hold that
    //      /                 \   val in their pvals. They will all
    //  1   1  { sq1, sq2, ... }  already be on the same row (or
    //      2  { sq1, sq2, ... }  column or block)
    //      .
    //      .
    //      .
    //      9  { sq1, sq2, ... }
    //          \_____  ______/
    //                \/
    //              sqs (below) is just this, the vector for one
    //              row(or column or block), and one val
    //              .
    //              .
    //              .
    // 8    9  { sq1, sq2, ...}

    // for one row (or column or block) mvs is a map from the 9
    // possible values, to 9 vectors of pointers to squares for 
    // the squares that contain that val in their pvals. 
    // N.B. if a square on row 1 contains the pvals {3,7,9}, a
    // pointer to it will be in three of the map entries for
    // row one, the map from 3, the map from 7 and the map from 9.
    // For example
    // mvs=b->get_possibilities(GT_ROW,7) returns us a map for row 7
    // mvs[2] returns us a vector<square*> of all the squares
    // on row 7 with 2 in their pvals (possible values). Since we
    // are looking for possible values that only occur in two or
    // three cells so we can check to see if they are in the same
    // block, we can conveniently ask the size of the vector for all
    // the squares that have 2 in their pvals, so that if
    // mvs[2].size() is two or three we know to investigate further

    std::map<size_t,std::vector<square*>>& mvs=
				    get_possibilities(primary,which);
    // now we have the map for the given row, and will walk through
    // all of the values to see the number of squares with that value
    // in their pvals
    for(size_t val=1;val<N+1;val++){
	DISCERN_INTERSECTION_DEBUG std::cerr << "    pval: " << val;
	// walk through each val in turn
	size_t sz=mvs[val].size(); // squares on row with val in pvals
	if(sz==2 || sz==3){
	    // two or three might be an intersection if they are
	    // all in the same block
	    std::vector<square*>& sqs=mvs[val]; // convenience
	    // a pair or triple on a row, if all in same block, can
	    // purge that value from other squares in the block
	    DISCERN_INTERSECTION_DEBUG{
		std::cerr << " - " << sz << " squares have the same "
		    << gts[primary].name << " and pval " << val << "\n";
		for( auto sq : sqs){
		    std::cerr << "      "
			<< print_sq_rcp(sq) << '\n';
		}
	    }
	    bool foundit=true;
	    size_t whichnum=0;
	    switch(secondary){
		case GT_BLOCK: // for row-block or column-block
		    whichnum=get_block_num(sqs[0]);
		    for(size_t ctr=1;ctr<sz;ctr++){
			if(get_block_num(sqs[ctr])!=whichnum){
			    foundit=false;
			    DISCERN_INTERSECTION_DEBUG{
				std::cerr << "        not same " << gts[secondary].name << ", no intersection\n";
			    }
			    break; // break out of for, no point now
			}
		    }
		    break;
		case GT_ROW:
		    whichnum=sqs[0]->get_row();
		    foundit=true;
		    for(size_t ctr=1;ctr<sz;ctr++){
			if(sqs[ctr]->get_row()!=whichnum){
			    foundit=false;
			    DISCERN_INTERSECTION_DEBUG{
				std::cerr << "        not same " << gts[secondary].name << ", no intersection\n";
			    }
			    break;
			}
		    }
		    break;
		case GT_COLUMN:
		    whichnum=sqs[0]->get_column();
		    foundit=true;
		    for(size_t ctr=1;ctr<sz;ctr++){
			if(sqs[ctr]->get_column()!=whichnum){
			    foundit=false;
			    DISCERN_INTERSECTION_DEBUG{
				std::cerr << "        not same " << gts[secondary].name << ", no intersection\n";
			    }
			    break;
			}
		    }
		    break;
	    }
	    if(foundit){
		DISCERN_INTERSECTION_DEBUG{
		    std::cerr << "        found intersection on "
			<< gts[primary].name << " "
			<< which << ", "
			<< gts[secondary].name << " " << whichnum << " for pval " << val << "\n";
		}
		//set_applied_intersection returns false for already there
		bool already_set=false;
		for(auto sq : sqs){
		    if(primary==GT_ROW || secondary==GT_ROW){
			if(!sq->set_applied_intersection(square::matched_type::AM_ROW_BLOCK_INTERSECTION,val,sqs)){
			    already_set=true;
			    break;
			};
			if(!sq->set_applied_intersection(square::matched_type::AM_BLOCK_ROW_INTERSECTION,val,sqs)){
			    already_set=true;
			    break;
			};
		    }else if(primary==GT_COLUMN || secondary==GT_COLUMN){
			if(!sq->set_applied_intersection(square::matched_type::AM_COLUMN_BLOCK_INTERSECTION,val,sqs)){
			    already_set=true;
			    break;
			};
			if(!sq->set_applied_intersection(square::matched_type::AM_BLOCK_COLUMN_INTERSECTION,val,sqs)){
			    already_set=true;
			    break;
			};
		    }
		}
		if(!already_set){
		    bool did_something=false;
		    RESPATH{
			std::cerr << gts[primary].name << "-"
			    << gts[secondary].name << "-intersection"
			    << " " << gts[primary].shortname << which+1
			    << " " << gts[secondary].shortname << whichnum+1;
		    }
		    switch(secondary){
			case GT_BLOCK:
			    did_something=purge_block_except(whichnum, sqs,val);
			    break;
			case GT_ROW:
			    did_something=purge_row_except(whichnum,sqs,val);
			    break;
			case GT_COLUMN:
			    did_something=purge_column_except(whichnum,sqs,val);
			    break;
		    }
		    RESPATH std::cerr << "\n";
		    if(did_something){
			count++;
			DISCERN_INTERSECTION_DEBUG{
			    std::cerr << "          "
			    << gts[primary].name
			    << " v block intersection cleared pvals, bumping count\n";
			}
		    }else{
			DISCERN_INTERSECTION_DEBUG std::cerr << "          didn't clear any pvals continuing\n";
		    }
		}else{
		    DISCERN_INTERSECTION_DEBUG std::cerr << "          already found that one, going on\n";
		}
	    } // if(foundit)
	}else{ // if(sz==2 || sz==3)
	    DISCERN_INTERSECTION_DEBUG std::cerr << "\n";
	}
    } // for(size_t val=1;val<N+1;val++)
    DISCERN_INTERSECTION_DEBUG{
	std::cerr << "  finished "
	    << gts[primary].name << " " << which << " - "
	    << gts[secondary].name << " without finding anything\n";
    }
    return count;
}

//! look for an x-wing, swordfish, or jellyfish
/*! looks for an x wing, a swordfish, or a jellyfish in rows or columns
 * \param depth two for x-wing, three for swordfish, four for jellyfish
 * \param which either GT_ROW or GT_COLUMN, the two group types this applies to
 * \return true if found an interlock and as a result one or more pvals
 *    were removed from one or more squares
 */
template<const unsigned int N>
bool
board<N>::discern_interlock(size_t depth,grouptype which)
{
    std::vector<size_t> rows_or_cols;
    std::vector<std::vector<square*>> mvss;
    rows_or_cols.resize(depth);
    mvss.resize(depth);
    // the flags are used to mark squares as having had particular things
    // applied and to check if they are already applied. This map just maps
    // the values to the depth so that I can grab the one I want without 
    // having to do any decision making.
    std::map<size_t,square::matched_type> flags{
	{2,square::matched_type::AM_X_WING},
	{3,square::matched_type::AM_SWORDFISH},
	{4,square::matched_type::AM_JELLYFISH}
    };

#if defined(SHOW_DISCERN_INTERLOCK_DEBUG)
    std::map<size_t,std::string> AM_NAMES{
	{2,"x-wing"},
	{3,"swordfish"},
	{4,"jellyfish"}
    };
#else
    char AM_NAMES[1];
#endif
    DISCERN_INTERLOCK_DEBUG{
	std::cerr << "discern_interlock() of type " << AM_NAMES[depth] << " (depth is " << depth << ")--for " << which << "\n";
    }

    // what I want:
    //
    // we want depth rows (or columns, but I'll just say rows to keep it 
    // simpler), that have 2 <= N <= depth squares that are the only squares
    // on their row that have the candidate number we're looking for. So if
    // we're working on 7, we want
    //              number rows    number squares with 7 in pvals
    // x-wing            2                      2
    // swordfish         3                    2 or 3
    // jellyfish         4                  2, 3 or 4
    //
    // So we make a loop on number, 1-9, and then inside the loop
    // we use num_row to keep track of which of our 2 or 3 or 4 rows
    // we are looking at.  We also keep a vector of length 2, 3, or 4 (depth)
    // and if, for example we're working on 7 and we find a candidate row,
    // say 6, with num_row 0, we set rows_or_cols[num_row] to 6, and bump
    // up num_row and go back up and start looking again from row 7.
    // go to a deeper depth.  If a interlock-N is not found, we will return to 
    // our depth, and continue to see if there is another candidate at our
    // depth that has 
    //
    // for all possible values we will set d, our index into our list of
    // possible rows that have 2 <= n <=depth squares with the current val
    // in their pvals. i.e. if depth is 2, (x-wing), and val is 3 and which
    // is GT_ROW, we are looking for two rows, that have only two squares
    // with pvals containing 3.
    // If instead, depth is 3, (swordfish), we are looking for three rows
    // that have either 2, or 3 squares only with 3 in their pvals.
    // If instead, depth is 4, (jellyfish), we are looking for four rows
    // that have either 2, 3, or 4 squares only with 3 in their pvals.
    // To do this, for each val, 1 through 9, we set d to zero and start
    // walking the rows. If we find a candidate, we note it and bump up d.
    // Suppose that there was a swordfish on 2 in rows 3, 5, and 6. Then
    // rows[0] would contain 3
    // rows[1] would contain 5
    // rows[2] would contain 6

    for(size_t val=1;val<N+1;val++){
	// get a list of all of the row (or column) numbers that contain
	// only 2 < n < depth squares with this val in their pval
	DISCERN_INTERLOCK_DEBUG{
	    std::cerr << "top of loop, val is " << val << '\n';
	}
	std::vector<size_t> all_rows_or_cols; // all rows with 2,depth of val
	std::vector<std::vector<square*>> aroc_vs;
	for(size_t ctr=0;ctr<N;ctr++){
	    size_t sz;
	    if(which==GT_ROW){
		sz=get_possibilities(GT_ROW,ctr)[val].size();
	    }else{
		sz=get_possibilities(GT_COLUMN,ctr)[val].size();
	    }
	    if(sz>=2 && sz<=depth){
		all_rows_or_cols.push_back(ctr);
	    }
	}
	size_t the_size=all_rows_or_cols.size(); // number of candidate rows
	DISCERN_INTERLOCK_DEBUG{
	    std::cout << "  " << the_size << ' '
		<< (which==GT_ROW?"rows":"columns")
		<< " have [2, " << depth << "] squares with val " << val <<
		" in their pvals\n";
	}
	if(the_size < depth){
	    DISCERN_INTERLOCK_DEBUG{
		std::cout << "    that's not enough for a " << AM_NAMES[depth] 
		    << " (depth " << depth << "), continuing\n";
	    }
	    continue;
	}
	for( size_t aval : all_rows_or_cols){
	    DISCERN_INTERLOCK_DEBUG{
		std::cerr << "    " << (which==GT_ROW?"row":"column")
		    << " " << aval << ": ";
	    }
	    if(which==GT_ROW){
		aroc_vs.push_back(get_possibilities(GT_ROW,aval)[val]);
	    }else{
		aroc_vs.push_back(get_possibilities(GT_COLUMN,aval)[val]);
	    }
	    DISCERN_INTERLOCK_DEBUG{
		bool firsttime=true;
		for(square* sq : aroc_vs[aroc_vs.size()-1]){
		    if(!firsttime){
			std::cerr << " ";
		    }
		    firsttime=false;
		    std::cerr << "{ "
			<< print_sq_rcp(sq) << " }";
		}
		std::cerr << "\n";
	    }
	}
	std::vector<size_t> slots;
	size_t row_ctr=0;
	for(row_ctr=0;row_ctr<depth;row_ctr++){
	    slots.push_back(row_ctr);
	}
	size_t tomod=depth-1;
	while(true){
	    // check to see if we have an interlock
	    std::set<size_t> rowset;
	    std::set<size_t> colset;
	    for(size_t which_trial=0;which_trial<depth;which_trial++){
		size_t idx=slots[which_trial]; // idx into arov_vs
		for(auto sp : aroc_vs[idx]){
		    rowset.insert(sp->get_row());
		    colset.insert(sp->get_column());
		}
	    }

	    if(rowset.size()==depth && colset.size()==depth){
		bool foundbool=true;
		for(size_t which_trial=0;which_trial<depth;which_trial++){
		    size_t idx=slots[which_trial]; // idx into arov_vs
		    for(auto sp : aroc_vs[idx]){
			if(!sp->set_applied_interlock(flags[depth],
				val,rowset,colset)){
			    // this interlock is already found
			    foundbool=false;
			}
		    }
		}
		if(foundbool){
		    DISCERN_INTERLOCK_DEBUG{
			std::cerr << "    found " << AM_NAMES[depth]
			    << " on " << (which==GT_ROW?"rows":"columns")
			    << " on val " << val << "\n";
			std::cerr << "      rows:";
			for(auto row : rowset){
			    std::cerr << ' ' << row;
			}
			std::cerr << ", columns:";
			for(auto col : colset){
			    std::cerr << ' ' << col;
		
			}
			std::cerr << '\n';
			std::cerr << "        ~~~~";
			for(size_t ctr=1;ctr<depth;ctr++){
			    std::cerr << "~~~~~~";
			}
			std::cerr << '\n';
			std::cerr << std::left;
			for(auto row : rowset){
			    std::cerr << "        ";
			    for(auto col : colset){
				std::cerr << std::setw(6);
				bool foundit=false;
				for(size_t sqidx=0;sqidx<depth;sqidx++){
				    size_t idx=slots[sqidx]; // idx into arov_vs
				    for(auto sp : aroc_vs[idx]){
					if( sp->get_row()==row
					 && sp->get_column()==col){
					    std::cerr << print_sq_rc(sp);
					    foundit=true;
					    break;
					}
				    }
				    if(foundit){
					break;
				    }
				}
				if(!foundit){
				    std::cerr << "----";
				}
			    }
			    std::cerr << '\n';
			}
			std::cerr << "        ~~~~";
			for(size_t ctr=1;ctr<depth;ctr++){
			    std::cerr << "~~~~~~";
			}
			std::cerr << '\n';
		    }
		    RESPATH{
			switch(depth){
			    case 2:
				std::cerr << "x-wing";
				break;
			    case 3:
				std::cerr << "swordfish";
				break;
			    case 4:
				std::cerr << "jellyfish";
			}
			std::cerr << "-in-";
			switch(which){
			    case GT_ROW:
				std::cerr << "rows";
				break;
			    default:
				std::cerr << "columns";
				break;
			}
			std::cerr << " n" << val;
			std::cerr << "{";
			bool first_time=true;
			for(size_t idx : slots){
			    for(square *sq : aroc_vs[idx]){
				if(!first_time){
				    std::cerr << ' ';
				}
				first_time=false;
				std::cerr << "r" << sq->get_row()+1 << "c" << sq->get_column()+1;

			    }
			}
			std::cerr << "} ==>";
		    }
		    bool did_something=false;
		    did_something=purge_row_col_sets(which,rowset,colset,val);
		    RESPATH  std::cerr << "\n";
		    if(did_something){
			DISCERN_INTERLOCK_DEBUG{
			    std::cout << "    interlock did something, returning true\n";
			}
			return true;
		    }else DISCERN_INTERLOCK_DEBUG{
			std::cerr << "    interlock didn't remove any pvals\n";
		    }
		    break;
		}else{
		    DISCERN_INTERLOCK_DEBUG{
		    std::cout << "    found an interlock but we'd already found it\n";
		    }
		}

	    }
	    if(slots[tomod] == the_size-1){
		ssize_t tmptomod=tomod-1;
		while(tmptomod>=0 && slots[tmptomod]==slots[tmptomod+1]-1){
		    --tmptomod;
		}
		if(tmptomod==-1){
		    break;
		}else{
		    ++slots[tmptomod];
		    for(++tmptomod;tmptomod<static_cast<ssize_t>(depth);tmptomod++){
			slots[tmptomod]=slots[tmptomod-1]+1;
		    }
		}

	    }else{
		++slots[tomod];
	    }
	} // end of while true
	DISCERN_INTERLOCK_DEBUG std::cerr << "  no new interlock, going to next val\n";
    } // end of val loop
    DISCERN_INTERLOCK_DEBUG std::cerr << "end of vals, returning false\n\n";
    return false;
}

/*!
 * is called by the apply method of hidden_double, hidden_triple, and
 * hidden_quad. In turn, for each row, and then each column, and then each
 * block, it calls discern hidden. Each time the call to discern_hidden succeeds
 * it adds one to the count of successes.
 * \return count of successes
 * \param level 2, 3, or 4, for hidden double, triple, or quad respectively
 */
template<const unsigned int N>
size_t
board<N>::hidden_apply(size_t level)
{
    size_t retval=0;
    HIDDEN_APPLY_DEBUG std::cerr << "hidden_apply()\n";

    // check each row for hidden doubles
    HIDDEN_APPLY_DEBUG std::cerr << "  checking rows for hidden level: " << level << '\n';
    for(size_t row=0;row<N;row++){
	HIDDEN_APPLY_DEBUG std::cerr << "    row: " << row << '\n';
	if(discern_hidden(level, GT_ROW, row)){
	    HIDDEN_APPLY_DEBUG std::cerr << "      found\n";
	    ++retval;
	    //return true;
	}
    }
    // check each column for hidden doubles
    HIDDEN_APPLY_DEBUG std::cerr << "  checking columns for hidden level: " << level << "\n";
    for(size_t col=0;col<N;col++){
	HIDDEN_APPLY_DEBUG std::cerr << "    col: " << col << '\n';
	if(discern_hidden(level, GT_COLUMN, col)){
	    HIDDEN_APPLY_DEBUG std::cerr << "      found\n";
	    ++retval;
	    //return true;
	}
    }
    // check each block for hidden doubles
    HIDDEN_APPLY_DEBUG std::cerr << "  checking blocks for hidden level: " << level << "\n";
    for(size_t block=0;block<N;block++){
	HIDDEN_APPLY_DEBUG std::cerr << "    block: " << block << '\n';
	if(discern_hidden(level, GT_BLOCK, block)){
	    HIDDEN_APPLY_DEBUG std::cerr << "      found\n";
	    ++retval;
	    //return true;
	}
    }
    return retval;
    //return false;
}

//! This is a heuristic to look for y wings
/*! y_wing_apply implements the algorithm to search for three cells each 
 * with 2 members of their pvals, but between them only three pvals.  One of
 * the cells is the pivot and shares a member of pvals with each of the other
 * two.  They in turn, share a third pval.  For example, the three squares,
 * (with the pivot in the middle) could have pvals {1,8} {1,6} {6,8}.  
 * The first has to be in a group with the second, and the second in a group
 * with the third (row, column or block is a group), but all three can't be in
 * the same group.  If all that is true, then in the intersection of squares
 * visible from the first and the third, we can remove their shared value (in
 * the example, the 8) from all the square's pvals.
 * <small><code><pre style="line-height: 1.0">
 *                                 two cells with 6s same column
 *                                /
 * rows   1   2   3   4   5   6   7   8   9
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |1  |   |
 *   1  |   |   |   |   |   |   |   |   |<--- wing 1
 *      |   |   |   |   |   |   | * | 8 |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |  /|   |   |
 *   2  |   |   |   |   |   |   | / |   |   | 2 cells with 1s in same block
 *      |   |   |   |   |   |   |/  |   |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |1  |   |   |
 *   3  |   |   |pivot cell --> |  6|   |   | pivot cell
 *      |   |   |   |   |   |   |  .|   |   |
 *      +---+---+---+---+---+---+--.+---+---+
 *      |   |   |   |   |   |   |  .|   |   |
 *   4  |   |   |   |   |   |   |  .|   |   |
 *      |   |   |   |   |   |   |  .|   |   |
 *      +---+---+---+---+---+---+--.+---+---+
 *      |   |   |   |   |   |   |  .|   |   |
 *   5  |   |   |   |   |   |   |  .|   |   | 2 cells that can be seen by both
 *      |   |   |   |   |   |   |  .|   |   | wings, r1c7 and r9c8, can have any
 *      +---+---+---+---+---+---+--.+---+---+ 8s removed
 *      |   |   |   |   |   |   |  .|   |   |
 *   6  |   |   |   |   |   |   |  .|   |   |
 *      |   |   |   |   |   |   |  .|   |   |
 *      +---+---+---+---+---+---+--.+---+---+
 *      |   |   |   |   |   |   |  .|   |   |
 *   7  |   |   |   |   |   |   |  .|   |   |
 *      |   |   |   |   |   |   |  .|   |   |
 *      +---+---+---+---+---+---+--.+---+---+
 *      |   |   |   |   |   |   |  .|   |   |
 *   8  |   |   |   |   |   |   |  .|   |   |
 *      |   |   |   |   |   |   |  .|   |   |
 *      +---+---+---+---+---+---+--.+---+---+
 *      |   |   |   |   |   |   |  .|   |   |
 *   9  |   |   |   |   |   |   |  6| <------ wing2
 *      |   |   |   |   |   |   | 8 | * |   |
 *      +---+---+---+---+---+---+---+---+---+
 *      </pre></code></small>
 */
template<const unsigned int N>
bool
board<N>::y_wing_apply()
{
    Y_WING_APPLY_DEBUG std::cerr << "board::y_wing_apply()\n";

    for(size_t ctr1=0;ctr1<N*N;ctr1++){
	size_t row1=ctr1/N;
	size_t col1=ctr1%N;
	square &wing1=b[row1][col1];

	Y_WING_APPLY_DEBUG{
	    std::cerr << "top of loop: wing1 candidate: "
		<< print_sq_rcp(&wing1) << ": ";
	}

	if(wing1.size()!=2){
	    // only look at squares with 2 pvals
	    Y_WING_APPLY_DEBUG std::cerr <<"not 2 pvals, skipping\n";
	    continue;
	}

	Y_WING_APPLY_DEBUG{
	    std::cerr << "2 pvals, checking\n";
	    std::cerr << "  going to check for neighbors with two pvals\n";
	}

	std::set<square*> w1_nbrs=get_neighbors(&wing1,&square::two_filt);

	Y_WING_APPLY_DEBUG{
	    std::cerr << "  found " << w1_nbrs.size()
		<< " checking through them\n";
	}

	for(square* nbr : w1_nbrs){
	    // we are iterating through wing1's neighbors w/2 pvals
	    // looking for a pivot
	    square& pivot=*nbr;		// candidate for pivot

	    Y_WING_APPLY_DEBUG{
		std::cerr << "    pivot candidate: "
		    << print_sq_rcp(&pivot) << "\n"
		    << "      going to check for neighbors with 2 pvals\n";
	    }

	    std::set<square*> pvt_nbrs=get_neighbors(&pivot,&square::two_filt);

	    Y_WING_APPLY_DEBUG{
		std::cerr << "      found " << pvt_nbrs.size() << " checking through them\n";
	    }

	    // we have neighbors of the pivot, potential wing2s 
	    for(square* pvt_nbr : pvt_nbrs){
		square& wing2=*pvt_nbr;		// wing2 candidate
		Y_WING_APPLY_DEBUG{
		    std::cerr << "        wing2 candidate: "
			<< print_sq_rcp(&wing2) << '\n';
		}
		if(wing2==wing1){
		    Y_WING_APPLY_DEBUG{
		    std::cerr << "          looking for wing2 but found wing1 again, continuing\n";
		    }
		    continue;
		}

		// not our original so we have a chain of three
		// wing1->pivot->wing2 squares each with only
		// two pvals
		// Now we check if between them they only have three
		// pvals
		std::set<size_t> pvals;
		pvals.insert(wing1[0]);
		pvals.insert(wing1[1]);
		pvals.insert(pivot[0]);
		pvals.insert(pivot[1]);
		pvals.insert(wing2[0]);
		pvals.insert(wing2[1]);

		Y_WING_APPLY_DEBUG{
		std::cerr << "          pvals among the three candidates: "
		    << pvals.size();
		}
		if(pvals.size()!=3){
		    Y_WING_APPLY_DEBUG{
			std::cerr << ", but need exactly 3, continuing\n";
		    }
		    continue;
		}

		// now check to make sure two don't have same
		// pvals
		//
		Y_WING_APPLY_DEBUG{
		    std::cerr << "\n            exactly 3 pvals between wing1, pivot, and wing2:\n"
			<< "              wing 1: "
			<< print_sq_rcp(&wing1) << '\n'
			<< "              pivot : "
			<< print_sq_rcp(&pivot) << '\n'
			<< "              wing 2: "
			<< print_sq_rcp(&wing2) << '\n';
		}

		if(wing1.same_pvals(pivot)
		    ||wing1.same_pvals(wing2)
		    ||pivot.same_pvals(wing2)){
		    Y_WING_APPLY_DEBUG{
			std::cerr << "                two squares have exactly same pvals, skipping\n";
		    }
		    continue;
		}
		// check, the wings shouldn't share row,
		// column, nor block
		if(wing1.get_row()==wing2.get_row()
		  || wing1.get_column()==wing2.get_column()
		  || get_block_num(wing1)==get_block_num(wing2)){
		    Y_WING_APPLY_DEBUG{
			std::cerr << "                wing1 and wing2 in a group together, skipping\n";
		    }
		    continue;
		}
		Y_WING_APPLY_DEBUG{
		    std::cerr
		    << "                "
		    << "right number of pvals\n"
		    << "                "
		    << "wings in different groups\n"
		    << "                "
		    << "no duplicates--looking hopeful!\n"
		    << "                checking to see if we've already found it\n";
		}

		if(pivot.check_applied_y_wing(wing1, pivot, wing2)){
		    Y_WING_APPLY_DEBUG{
			std::cerr << "                  we've already found it, skipping\n";
		    }
		    continue;
		}else{
		    Y_WING_APPLY_DEBUG{
			std::cerr << "                  We haven't found it before!!! Yay!!!\n";
		    }
		}

		std::vector<square*> inter;
		std::vector<square*>::iterator vi;
		std::set<square*> sqs1i=get_neighbors(&wing1);
		std::set<square*> sqs3i=get_neighbors(&wing2);
		inter.resize(sqs1i.size()+sqs3i.size());
		vi=std::set_intersection(sqs1i.begin(),sqs1i.end(),sqs3i.begin(),sqs3i.end(),inter.begin());
		inter.resize(vi-inter.begin());
		Y_WING_APPLY_DEBUG std::cerr << "                shared neighbors between the wings: " << inter.size() << '\n';
		if(inter.size()>1){
		    // if the wings don't see any squares in
		    // common it's not a y-wing, is it.
		    size_t shared_val=0;
		    if(wing1[0]==wing2[0] || wing1[0]==wing2[1]){
			shared_val=wing1[0];
		    }else{
			shared_val=wing1[1];
		    }
		    Y_WING_APPLY_DEBUG{
		    for( square *si : inter ){
			std::cerr << "                   "
			    << print_sq_rcp(si) << '\n';
		    }
		    std::cerr << "                wings share pval: " << shared_val << '\n';
		    }


		    RESPATH{
			std::cerr << "y-wing "
			    << "{n" << wing1[0] << " n" << wing1[1]
			    << "}{r" << row1+1
			    << "c" << col1+1 << "}"
			    << " {n" << pivot[0] << " n" << pivot[1]
			    << "}{r" << pivot.get_row()+1
			    << "c" << pivot.get_column()+1 << "}"
			    << " {n" << wing2[0] << " n" << wing2[1]
			    << "}{r" << wing2.get_row()+1
			    << "c" << wing2.get_column()+1 << "}"
			    << " ==>";
		    }
		    bool did_something=false;
		    Y_WING_APPLY_DEBUG{
			std::cerr << "                found a y-wing, trying to clear pvals\n";
		    }
		    
		    for(square* sqi : inter){
			//  purge the shared val from all shared
			//  neighbors
			if(sqi!=&pivot){
			    did_something|=clear_pval_val(sqi->get_row(),sqi->get_column(),shared_val);
			}
		    }
		    RESPATH std::cerr << "\n";
		    if(did_something){
			Y_WING_APPLY_DEBUG{
			    std::cerr << "                  cleared something!\n                    set AM_Y_WING on three squares and return true\n\n";
			}
			wing1.set_applied_y_wing( wing1,  pivot,  wing2);
			pivot.set_applied_y_wing( wing1,  pivot,  wing2);
			wing2.set_applied_y_wing( wing1,  pivot,  wing2);
			return true;
		    }else{
			Y_WING_APPLY_DEBUG{
			    std::cerr << "                  didn't clear anything, just continuing\n";
			}
		    }
		}
	    }
	}
    }
    Y_WING_APPLY_DEBUG std::cerr << "Got through the whole board without finding a y-wing!\n";
    return false;
}

/*!
 * is called by the apply method of naked_double, naked_triple, and
 * naked_quad. In turn, for each row, and then each column, and then each
 * block, it calls discern naked. Each time the call to discern_naked succeeds
 * it adds one to the count of successes.
 * \return count of successes
 * \param level 2, 3, or 4, for naked double, triple, or quad respectively
 */
template<const unsigned int N>
size_t
board<N>::naked_apply(size_t level)
{
    size_t retval=0;
    NAKED_APPLY_DEBUG std::cerr << "naked_apply()\n";

    // check each row for naked N
    NAKED_APPLY_DEBUG std::cerr << "  checking rows for naked level: " << level << "\n";
    //bool foundone=false;
    for(size_t row=0;row<N;row++){
	NAKED_APPLY_DEBUG std::cerr << "    row: " << row << '\n';
	if(discern_naked(level, GT_ROW,row)){
	    NAKED_APPLY_DEBUG std::cerr << "      found\n";
	    retval++;
	}
    }
    // check each column for naked N
    NAKED_APPLY_DEBUG std::cerr << "  checking columns for naked level: " << level << "\n";
    for(size_t col=0;col<N;col++){
	NAKED_APPLY_DEBUG std::cerr << "    col: " << col << '\n';
	if(discern_naked(level, GT_COLUMN,col)){
	    NAKED_APPLY_DEBUG std::cerr << "      found\n";
	    retval++;
	}
    }
    // check each block for naked N
    NAKED_APPLY_DEBUG std::cerr << "  checking blocks for naked level: " << level << "\n";
    for(size_t block=0;block<N;block++){
	NAKED_APPLY_DEBUG std::cerr << "    block: " << block << '\n';
	if(discern_naked(level, GT_BLOCK,block)){
	    NAKED_APPLY_DEBUG std::cerr << "      found\n";
	    retval++;
	}
    }
    return retval;
}

template<const unsigned int N>
bool
board<N>::xy_chain_apply(std::vector<square*> &chain)
{
    /*!
     * This routine uses a breadth first search through possible connections.
     * As soon as it finds a cycle with a contradiction it returns true.
     * If it finds none, it returns false.  It uses a recursive implementation.
     * At each length of chain, it asks for all possible connections by calling
     * get_neighbors with the appropiate filter.  Then for each possible
     * candidate, it pushes the candidate on the end of the chain and calls this
     * routine recursively.  If the call returns false, it pops the candidate
     * off and pushes the next one on.  Eventually, we either run out of
     * candidates and return false, or one of our candidates can see the 
     * original square at the head of the chain, and asserts ownership of the 
     * same value, say 6.  Since they can't both be six we've found a
     * contradiction and return true.  Each recursive level returns true, so
     * since nothing gets popped of the chain, when we get back to the
     * original caller of this routine, they will know the original square
     * can't have 6 for its value and will set its other pval as the value.
     */
    if(chain.size()==0){
	XY_CHAIN_DEBUG std::cerr << "xy_chain_apply  chain.size()==0 returning false\n";
	return false;
    }
    XY_CHAIN_DEBUG {
	std::cerr << "xy_chain_apply size " << chain.size() << " ";
	for(size_t i=0;i<chain.size();i++){
	    size_t lo=chain[i]->get_xy_owned();
	    std::cerr << print_sq_rc(chain[i]) << " {";
	    if(lo==static_cast<size_t>((*chain[i])[0])){
		std::cerr << "|" << (*chain[i])[0] << "|"
		<< "," << (*chain[i])[1] << "} ";
	    }else{
		std::cerr << (*chain[i])[0]
		<< ",|" << (*chain[i])[1] << "|} ";
	    }
	}
	std::cerr << '\n';
    }
    square *last_square=chain.back();
    size_t last_owned=last_square->get_xy_owned();
    size_t next_matched=last_square->get_xy_next();
    XY_CHAIN_DEBUG std::cerr << "calling get_neighbors to find neighbors with " << last_owned << "s in their pvals we could rule out\n";
    std::set<square*> cands=get_neighbors(last_square,&square::xy_chain_filt);
    XY_CHAIN_DEBUG{
	std::cerr << "  there are " << cands.size() << " candidates for the next link\n";
	for(auto i=cands.begin();i!=cands.end();i++){
	    std::cerr << **i;
	}
	std::cerr << '\n';
    }

    for(auto it=cands.begin();it!=cands.end();it++){
	square* sq=*it;
	XY_CHAIN_DEBUG std::cerr << "candidate: " << *sq;
	if(std::find(chain.begin(),chain.end(),sq)==chain.end()){
	    XY_CHAIN_DEBUG std::cerr << "  NOT FOUND IN CHAIN ALREADY\n";
	    // only look if cand square not already in chain to avoid loops
	    // we are in a square
	    if(static_cast<size_t>((*sq)[0])==last_owned){
		sq->set_owned(1);
	    }else if(static_cast<size_t>((*sq)[1])==last_owned){
		sq->set_owned(0);
	    }else{
		// should never happen
		XY_CHAIN_DEBUG std::cerr << "should never happen, next_matched: " << next_matched << "doesn't match either pval in square: " << *sq << "\n";
		continue;
	    }
	    XY_CHAIN_DEBUG std::cerr << "  pushing candidate onto chain\n";
	    chain.push_back(sq);
	    if(chain.size()>2){
		if(chain[0]->get_xy_owned()==sq->get_xy_owned()){
		    size_t row1,row2,col1,col2,blk1,blk2,owned;
		    row1=chain[0]->get_row();
		    col1=chain[0]->get_column();
		    row2=sq->get_row();
		    col2=sq->get_column();
		    blk1=get_block_num(row1,col1);
		    blk2=get_block_num(row2,col2);
		    owned=sq->get_xy_owned();
		    if((row1==row2)||(col1==col2)||blk1==blk2){
			XY_CHAIN_DEBUG{
			    if(row1==row2){
				std::cerr << "looks like on same row\n";
			    }else if(col1==col2){
				std::cerr << "looks like on same column\n";
			    }else if(blk1==blk2){
				std::cerr << "looks like on same block\n";
			    }else{
				std::cerr << "WHAT???\n";
			    }
			}

			RESPATH{
			    // this will print the xy-chain even if no pvals
			    // will be cleared
			    std::cerr << "xy-chain ";

			    for(size_t i=0;i<chain.size();i++){
				size_t lo=chain[i]->get_xy_owned();
				std::cerr << print_sq_rc_plus(chain[i]) << "{";
				if(lo==static_cast<size_t>((*chain[i])[0])){
				    std::cerr << "|" << (*chain[i])[0] << "|"
				    << "," << (*chain[i])[1] << "} ";
				}else{
				    std::cerr << (*chain[i])[0]
				    << ",|" << (*chain[i])[1] << "|} ";
				}
			    }
			    std::cerr << " ==>";
			}
			bool rtval=clear_pval_val(chain[0]->get_row(),chain[0]->get_column(),owned);
			RESPATH std::cerr << "\n";
			if(rtval){
			    XY_CHAIN_DEBUG std::cerr << "cleared some pvals\n";
			    return true;
			}
		    }
		}
	    }
	    if(xy_chain_apply(chain)){
		XY_CHAIN_DEBUG std::cerr << "recursive returned true so returning true\n";
		return true;
	    }else{
		chain.pop_back();
	    }
	}else{
	    XY_CHAIN_DEBUG std::cerr << "FOUND IN CHAIN ALREADY SO SKIPPING\n";
	}
    }
    XY_CHAIN_DEBUG std::cerr << "returning false\n";
    return false;
}

/*! the only reason for this routine is so that x-wing swordfish and
 * jellyfish don't have to call discern_interlock twice, once for 
 * rows and once for columns. They just call this guy once, and he
 * calls discern_interlock twice.
 * \param depth 2,3, or 4, for x-wing, swordfish, and jellyfish respectively
 * \return true iff the appropriated depth interlock was found and applying
 * it resulted in fewer pvals somewhere on the board
 */
template<const unsigned int N>
bool
board<N>::interlock_apply(size_t depth)
{
    assert(depth>=2);
    bool foundone=false;
    INTERLOCK_APPLY_DEBUG std::cerr << "interlock_apply()\n";

    INTERLOCK_APPLY_DEBUG std::cerr << "calling discern_interlock(" << depth << ",GT_ROW)\n";
    if(discern_interlock(depth,GT_ROW)){
	INTERLOCK_APPLY_DEBUG std::cerr << "called discern_interlock(" << depth << ",GT_ROW) and found one!!! Yay!!!\n";
	foundone=true;
    }
    INTERLOCK_APPLY_DEBUG std::cerr << "calling discern_interlock(" << depth << ",GT_COLUMN)\n";
    if(discern_interlock(depth,GT_COLUMN)){
	INTERLOCK_APPLY_DEBUG std::cerr << "called discern_interlock(" << depth << ",GT_COLUMN) and found one!!! Yay!!!\n";
	foundone=true;
    }
    return foundone;
}

template<const unsigned int N>
void
board<N>::init()
{
    suppress_output=true;
    root=sqrt(double(N));
    assert(root*root==N);
    backed_count=0;
    // the resizes result in default constructors for elements being called.
    b.resize(N);
    for(size_t ctr=0;ctr<N;ctr++){
	b[ctr].resize(N);
    }
    BOARD_CONSTRUCT_DEBUG std::cerr << "sizes reserved for board\n";
    // We set row and column early so that we can log changes
    for(size_t row=0;row<N;row++){
	for(size_t col=0;col<N;col++){
	    b[row][col].set_rowcol(row,col);
	}
    }
    valid=true;
    register_strategies();
}

//! default constructor
/*! default constructor calls init to set up the board
 */
template<const unsigned int N>
board<N>::board():valid(true)
{
    bool ssup=suppress_output;
    BOARD_CONSTRUCT_DEBUG std::cerr << "~~~ board()\n";
    init();
    suppress_output=ssup;
}

/*! This constructor is used in testing. A vector of squares is passed in
 * with some particular pattern of square values and pvals that will cause
 * some particular path through the code. We construct a default board, then
 * walk through the vector and set those particular squares.
 */
template<const unsigned int N>
board<N>::board(std::vector<square> sqs)
{
    bool ssup=suppress_output;
    init();
    for(size_t ctr=0;ctr<sqs.size();ctr++){
	b[sqs[ctr].get_row()][sqs[ctr].get_column()]=sqs[ctr];
    }
    suppress_output=ssup;
}

template<const unsigned int N>
board<N>::board(std::initializer_list<square> sqs)
{
    bool ssup=suppress_output;
    init();
    for(auto sq : sqs){
	b[sq.get_row()][sq.get_column()]=sq;
    }
    suppress_output=ssup;
}

//! construct board from string
/*! This constructor takes a string of . or 0 for unset, and values for
 * set squares and constructs the appropriate square.
 * \param in a row major representation of a board using . or 0 for unset,
 * and numbers for set squares.
 */
template<const unsigned int N>
board<N>::board(std::string in)
{
    bool ssup=suppress_output;
    BOARD_CONSTRUCT_DEBUG std::cerr << "~~~ board(std::string in)\n";
    init();
    assert(N*N==in.size());
    if(N*N>in.size()) throw board_shortstring();
    if(N*N<in.size()) throw board_longstring();
    for(size_t ctr=0;ctr<N*N;ctr++){
	size_t row=ctr/N, col=ctr%N;

	BOARD_CONSTRUCT_DEBUG std::cerr << "b[" << ctr/N << "][" << ctr%N << "]==";
	if(in[ctr]=='.' || in[ctr]=='0'){
	    set_val(row,col,0);
	    BOARD_CONSTRUCT_DEBUG std::cerr << "0\n"; 
	}else if('1' <= in[ctr] && in[ctr] <= '9'){
	    set_val(row,col,in[ctr]-'0');
	    b[row][col].lock();
	    BOARD_CONSTRUCT_DEBUG std::cerr << (in[ctr]-'0') << "\n"; 
	}else{
	    BOARD_CONSTRUCT_DEBUG{ std::cerr << "found invalid value in[" << ctr << "]=='" << in[ctr] << "'\n";
	    }
	    assert(false);
	}
    }
    BOARD_CONSTRUCT_DEBUG std::cerr << "there are " << count() << " cells set\n";
    BOARD_CONSTRUCT_DEBUG std::cerr << "board valid: " << get_valid() << "\n";
    // update_pvals is just a nested loop iterating all the squares and 
    // calling generate_pvals for each.  It's inline, and fixes up all the
    // pvals to match the reality of the squares we just read in from the
    // string. Then it sets up the three possibility maps.
    update_pvals();
    BOARD_CONSTRUCT_DEBUG std::cerr << "board valid: " << get_valid() << "\n";
    BOARD_CONSTRUCT_DEBUG std::cerr << "board valid: " << get_valid() << "\n";
    suppress_output=ssup;
}

template<const unsigned int N>
board<N>&
board<N>::operator=(const board& other)
{
    for(size_t rctr=0;rctr<N;rctr++){
	for(size_t cctr=0;cctr<N;cctr++){
	    b[rctr][cctr]=other.b[rctr][cctr]; // segfault here 
	}
    }
    for(size_t val=1;val<N;val++){
	row_possibilities[val];
	column_possibilities[val];
	block_possibilities[val];
    }
    update_possibilities();
    valid=other.valid;
    root=other.root;
    return *this;
}

//! copy constructor
/*!
 * copy constructor just copies all the squares
 * \param other the board to be copied
 */
template<const unsigned int N>
board<N>::board(const board& other)
{
    b.resize(N);
    for(size_t ctr=0;ctr<N;ctr++){
	b[ctr].resize(N);
    }
    for(size_t val=1;val<N;val++){
	row_possibilities[val];
	column_possibilities[val];
	block_possibilities[val];
    }
    for(size_t rctr=0;rctr<N;rctr++){
	for(size_t cctr=0;cctr<N;cctr++){
	    b[rctr][cctr]=other.b[rctr][cctr];
	}
    }
    //update_possibilities();
    valid=other.valid;
    root=other.root;
}

template<const unsigned int N>
void
board<N>::clear()
{
    for(size_t rctr=0;rctr<N;rctr++){
	for(size_t cctr=0;cctr<N;cctr++){
	    b[rctr][cctr].reset();
	}
    }
    valid=true;
}

/*! Walk through all of the columns and for each create a vector of 1-N
 * then for each square in the column, remove its value from the vector.
 * At the end, if the vector is empty, then all of the numbers occurred.
 */
template<const unsigned int N>
bool
board<N>::validate_columns()
{
    // checks to see if all numbers 0-N+1 are in each column
    for(size_t cctr=0;cctr<N;cctr++){
	std::vector<unsigned int> pvals { 1,2,3,4,5,6,7,8,9 };
	for(size_t rctr=0;rctr<N;rctr++){
	    // n.b. we don't have to care about std::erase invalidating
	    // iterators since we get a new one each time through the loop,
	    // i.e. we don't reuse a potentially invalidated iterator
	    std::vector<unsigned int>::iterator it;
	    it=std::find(pvals.begin(),pvals.end(),b[rctr][cctr].get_val());
	    if(it!=pvals.end()){
		pvals.erase(it);
	    }
	}
	if(pvals.size()!=0){
	    VALIDATE_DEBUG std::cerr << "col " << cctr << " is not correct\n";
	    solved=false;
	    return false;
	}
    }
    return true;
}

/*! Walk through all of the rows and for each create a vector of 1-N
 * then for each square in the row, remove its value from the vector.
 * At the end, if the vector is empty, then all of the numbers occurred.
 */
template<const unsigned int N>
bool
board<N>::validate_rows()
{
    // checks to see if all numbers 0-N+1 are in each row
    for(size_t rctr=0;rctr<N;rctr++){
	std::vector<unsigned int> pvals { 1,2,3,4,5,6,7,8,9 };
	for(size_t cctr=0;cctr<N;cctr++){
	    // n.b. we don't have to care about std::erase invalidating
	    // iterators since we get a new one each time through the loop,
	    // i.e. we don't reuse a potentially invalidated iterator
	    std::vector<unsigned int>::iterator it;
	    it=std::find(pvals.begin(),pvals.end(),b[rctr][cctr].get_val());
	    if(it!=pvals.end()){
		pvals.erase(it);
	    }
	}
	if(pvals.size()!=0){
	    VALIDATE_DEBUG std::cerr << "row " << rctr << " is not correct\n";
	    solved=false;
	    return false;
	}
    }
    return true;
}

/*! Walk through all of the blocks and for each create a vector of 1-N
 * then for each square in the block, remove its value from the vector.
 * At the end, if the vector is empty, then all of the numbers occurred.
 */
template<const unsigned int N>
bool
board<N>::validate_blocks()
{
    // checks to see if all numbers 0-N+1 are in each block
    for(size_t block_num=0; block_num<N;block_num++){
	std::vector<unsigned int> pvals { 1,2,3,4,5,6,7,8,9 };
	size_t row_min=root*(block_num/root),
	       row_max=row_min+root,
	       col_min=root*(block_num%root),
	       col_max=col_min+root;
	for(size_t rctr=row_min;rctr<row_max;rctr++){
	    for(size_t cctr=col_min;cctr<col_max;cctr++){
		// n.b. we don't have to care about std::erase invalidating
		// iterators since we get a new one each time through the loop,
		// i.e. we don't reuse a potentially invalidated iterator
		std::vector<unsigned int>::iterator it;
		it=std::find(pvals.begin(),pvals.end(),b[rctr][cctr].get_val());
		if(it!=pvals.end()){
		    pvals.erase(it);
		}
	    }
	}
	if(pvals.size()!=0){
	    VALIDATE_DEBUG{
		std::cerr << "block " << block_num << " is not correct\n";
		std::cerr << "pvals.size(): " << pvals.size() << '\n';
	    }
	    solved=false;
	    return false;
	}
    }
    return true;
}

//! return true or false for board solved
/*! Walks through all of the rows, columns, and blocks making sure that they
 * each contain all of the numbers.
 * \return true if all rows columns and blocks contain 1-N
 */
template<const unsigned int N>
bool
board<N>::is_solved()
{
    bool retval;
    retval=validate_columns();
    retval=retval && validate_rows();
    retval=retval && validate_blocks();
    return retval; 
    
}

//! print number of times each strategies used
/*! Walk through all the strategies and display to std::cout the number of
 * times each of them was successfully applied. Successfully means that we
 * not only found a y-wing, for example, but that as a result, the board
 * changed, i.e. one or more squares had one or more pvals go away
 */
template<const unsigned int N>
void
board<N>::print_counts()
{
    std::cout << "counts:\n";
    for(auto s : sorted_strategies){
	std::cout << std::setw(14) << s->get_name() << ": " << std::setw(3) << s->get_count() << '\n';
    }
}

/*! Prints a small representation of a puzzle to std::out. Squares with known
 * values show their values and others are blank.
 */
template<const unsigned int N>
void
board<N>::print() const {
    std::string bdr="-";
    for(size_t i=0;i<N;i++){
	bdr+="--";
    }
    for(size_t i=0;i<N;i++){
	if(i%3==0){
	    std::cout << bold;
	    std::cout << bdr << "\n|";
	    std::cout << unbold;
	}else{
	    std::cout << bdr << "\n" << bold << "|" << unbold;
	}
	for(size_t j=0;j<N;j++){
	    size_t val=b[i][j].get_val();
	    if(val==0){
		std::cout << " ";
	    }else{
		if(b[i][j].is_locked()){
		    std::cout << bold << val << unbold;
		}else{
		    std::cout << val;
		}

	    }
	    if((j+1)%3==0){
		std::cout << bold << '|' << unbold;
	    }else{
		std::cout << '|';
	    }
	}
	std::cout << '\n';
    }
    std::cout << bold << bdr << unbold << "\n";
}

/*! Print to std::cout a representational view of the puzzle with known values
 * in the center of their squares, and the pvals showing in other squares
 */
template<const unsigned int N>
void
board<N>::print_large(){
    std::string bdr="+";
    for(size_t i=0;i<N;i++){
	bdr+="---+";
    }
    std::cout << bold << bdr << unbold << "\n";
    for(size_t row=0;row<N;row++){
	for(size_t subrow=0;subrow<root;subrow++){
	    for(size_t col=0;col<N;col++){
		if(!(col%root)){
		    std::cout << bold << '|' << unbold;
		}else{
		    std::cout << '|';
		}

		for(size_t subcol=0;subcol<root;subcol++){
		    if(b[row][col].get_val()==0){
			size_t val=(subrow)*root+subcol+1;
			if(b[row][col].in_vals(val)){
			    std::cout << color2string(b[row][col].get_color()) << val << toblack;
			}else{
			    std::cout << ' ';
			}
		    }else if(subcol==(root)/2 && subrow==(root)/2){
			std::cout << bold << tored << b[row][col].get_val() << toblack << unbold;
		    }else{
#if !defined(USE_ANSI_ESCAPES)
			std::cout << '*';
#else
			std::cout << ' ';
#endif
		    }
		}
	    }
	    std::cout << bold << "|\n" << unbold;
	}
	if(!((row+1)%root)){
	    std::cout << bold << bdr << unbold << "\n";
	}else{
	    std::cout << bdr << '\n';
	}
    }
}

template<const unsigned int N>
inline
void
board<N>::prune_column_pvals(unsigned int row, unsigned int col, std::vector<unsigned int> &pv,bool mark_invalid)
{
    /*
     * given a cell at (col,row), walks the column and pulls any values found in
     * other cells in that column out of the possible values for this cell.
     */
    PRUNING_DEBUG std::cerr << "prune_column_pvals row: " << row << ", col: " << col << ", valid in : " << b[row][col].get_valid() << ", our val: " << b[row][col].get_val() << "\n";
    square& sq=b[row][col];	// for convenience
    size_t ourval=sq.get_val();
    for(size_t ctr=0;ctr<N;ctr++){
	size_t val=b[ctr][col].get_val();
	if(ourval!=0 && ctr!= row && val==ourval && mark_invalid){
	    // if we find two squares in the column with the same value,
	    // we mark the squares and the board as invalid
	    b[ctr][col].set_invalid();
	    sq.set_invalid();
	    valid=false;
	    PRUNING_DEBUG std::cerr << "  prune_column_pvals: our value is " << ourval << " and the value of b[" << ctr << "][" << col << "] is " << val << " so the column is invalid\n";
	}
	if(ctr!=row && val!=0){
	    // remove the other guys val from the pv (possible vals)
	    std::vector<unsigned int>::iterator it;
	    it=std::find(pv.begin(),pv.end(),val);
	    if(it!=pv.end()){
		pv.erase(it); // invalidates iterator but we're done with it
	    }
	}
    }
    PRUNING_DEBUG std::cerr << "  prune_column[_pvals row: " << row << ", col: " << col << ", valid out: " << b[row][col].get_valid() << "\n";
}

template<const unsigned int N>
inline
void
board<N>::prune_row_pvals(unsigned int row, unsigned int col, std::vector<unsigned int> &pv,bool mark_invalid)
{
    /*
     * given a cell at (col,row), walks the row and pulls any values found in
     * other cells in that row out of the possible values for this cell.
     */

    square& sq=b[row][col];	// for convenience only
    PRUNING_DEBUG std::cerr << "prune_row_pvals row: " << row << ", col: " << col << ", valid in : " << sq.get_valid() << "\n";
    size_t ourval=sq.get_val();
    for(size_t ctr=0;ctr<N;ctr++){
	size_t val=b[row][ctr].get_val();
	if(ourval!=0 && ctr!=col && val==ourval && mark_invalid){
	    // if two squares in the same row have the same value, we mark the
	    // squares and the board as invalid
	    b[row][ctr].set_invalid();
	    sq.set_invalid();
	    valid=false;
	    PRUNING_DEBUG std::cerr << "  prune_row_pvals: our value is " << ourval << " and the value of b[" << row << "][" << ctr << "] is " << val << " so the row and the board are invalid\n";
	}
	if(ctr!=col && val!=0){
	    // if they have a value, remove it from pv
	    std::vector<unsigned int>::iterator it;
	    it=std::find(pv.begin(),pv.end(),val);
	    if(it!=pv.end()){
		PRUNING_DEBUG std::cerr << "  Removing " << val << " from pv\n";
		pv.erase(it);
	    }else{
		PRUNING_DEBUG{
		    std::cerr << "  Wanted to delete "<< val << " from the passed in pv.  pv's values are:\n";
		    for(it=pv.begin();it!=pv.end();it++){
			std::cerr << "      " << *it << '\n';
		    }
		}
	    }
	}
    }
    PRUNING_DEBUG std::cerr << "  prune_row_pvals row: " << row << ", col: " << col << ", valid out: " << sq.get_valid() << "\n";
}

template<const unsigned int N>
inline
void
board<N>::prune_block_pvals(unsigned int row, unsigned int col, std::vector<unsigned int> &pv,bool mark_invalid)
{
    size_t row_min=root*(row/root), row_max=row_min+root,
	   col_min=root*(col/root), col_max=col_min+root;

    square& sq=b[row][col];	// convenience only
    size_t ourval=sq.get_val();

    PRUNING_DEBUG{
	std::cerr << "prune_block_pvals row: " << row << ", col: " << col << ", valid in : " << sq.get_valid() << "\n";
	std::cerr
	    <<"  row    : " << row << ", " << "col    : " << col << '\n'
	    <<"      min: " << row_min << ", " << "    min: " << col_min << '\n'
	    <<"      max: " << row_max << ", "<< "    max: " << col_max << '\n';
    }
    for(size_t rctr=row_min;rctr<row_max;rctr++){
	for(size_t cctr=col_min;cctr<col_max;cctr++){
	    size_t val=b[rctr][cctr].get_val();
	    if(ourval!=0 && (rctr!=row || cctr!=col) && val==ourval && mark_invalid){
		// if we find two cells in the same block with the same
		// value, we mark the squares and the board invalid
		b[rctr][cctr].set_invalid();
		sq.set_invalid();
		valid=false;
		PRUNING_DEBUG std::cerr << "  prune_block_pvals: our value is " << ourval << " and the value of b[" << rctr << "][" << cctr << "] is " << val << " so the block is invalid\n";
	    }
	    if((rctr!=row || cctr!=col) && val!=0){
		std::vector<unsigned int>::iterator it;
		it=std::find(pv.begin(),pv.end(),b[rctr][cctr].get_val());
	
	        PRUNING_DEBUG{
		    std::cerr <<"  erasing " << b[rctr][cctr].get_val() << '\n';
		    std::cerr <<"    it==pv.end(): "<<bool(it==pv.end())<< "\n";
		    std::cerr << std::endl;
		}
		if(it!=pv.end()){
		    pv.erase(it);
		}else{
		    PRUNING_DEBUG{
			std::cerr << "  Wanted to delete "<< b[rctr][cctr].get_val() << " from the passed in pv.  pv's values are:\n";
			for(it=pv.begin();it!=pv.end();it++){
			    std::cerr << "      " << *it << '\n';
			}
		    }
		}
	    }
	}
    }
    PRUNING_DEBUG std::cerr << "  prune_block_pvals row: " << row << ", col: " << col << ", valid out: " << sq.get_valid() << "\n";

}

/*!
 * purges val from all of the cells in the block not in the vector of squares
 * \param block the number of the block, each block being NxN
 * \param sqs the vector of sqs not to touch
 * \param val the value to strip from everyone else's pvals
 * \return true iff we removed a number from some square's pvals successfully
 */
template<const unsigned int N>
bool
board<N>::purge_block_except(size_t block, std::vector<square*> sqs,size_t val)
{
    bool did_something=false;
    size_t row_min=root*(block/root),
	   row_max=row_min+root,
	   col_min=root*(block%root),
	   col_max=col_min+root;
    RESPATH{
	std::cerr << " n" << val << "{";
	bool first_time=true;
	for(size_t sctr=0;sctr<sqs.size();sctr++){
	    if(!first_time){
		std::cerr << ' ';
	    }
	    first_time=false;
	    std::cerr << print_sq_rc_plus(sqs[sctr]);
	}
	std::cerr << "} ==>";
    }
    for(size_t row=row_min;row<row_max;row++){
	for(size_t col=col_min;col<col_max;col++){
	    if(std::find(sqs.begin(),sqs.end(),&b[row][col])==sqs.end()){
		did_something|=clear_pval_val(row,col,val);
	    }
	}
    }
    return did_something;
}

/*!
 * purges val from all of the cells in the row not in the vector of squares
 * \param row the number of the row
 * \param sqs the vector of sqs not to touch
 * \param val the value to strip from everyone else's pvals
 * \return true iff we removed a number from some square's pvals successfully
 */
template<const unsigned int N>
bool
board<N>::purge_row_except(size_t row, std::vector<square*> sqs,size_t val)
{
    bool did_something=false;
    RESPATH{
	std::cerr << " n" << val << "{";
	bool first_time=true;
	for(size_t sctr=0;sctr<sqs.size();sctr++){
	    if(!first_time){
		std::cerr << ' ';
	    }
	    first_time=false;
	    print_sq_rc_plus(sqs[sctr]);
	}
	std::cerr << "} ==>";
    }
    for(size_t col=0;col<N;col++){
	if(std::find(sqs.begin(),sqs.end(),&b[row][col])==sqs.end()){
	    did_something|=clear_pval_val(row,col,val);
	}
    }
    return did_something;
}

/*!
 * purges val from all of the cells in the column not in the vector of squares
 * \param col the number of the column
 * \param sqs the vector of sqs not to touch
 * \param val the value to strip from everyone else's pvals
 * \return true iff we removed a number from some square's pvals successfully
 */
template<const unsigned int N>
bool
board<N>::purge_column_except(size_t col, std::vector<square*> sqs,size_t val)
{
    bool did_something=false;
    RESPATH{
	std::cerr << " n" << val << "{";
	bool first_time=true;
	for(size_t sctr=0;sctr<sqs.size();sctr++){
	    if(!first_time){
		std::cerr << ' ';
	    }
	    first_time=false;
	    std::cerr << print_sq_rc_plus(sqs[sctr]);
	}
	std::cerr << "} ==>";
    }
    for(size_t row=0;row<N;row++){
	if(std::find(sqs.begin(),sqs.end(),&b[row][col])==sqs.end()){
	    did_something|=clear_pval_val(row,col,val);
	}
    }
    return did_something;
}

/*!
 * given a row and column and a set of values, purge all of those values from
 * the pvals of the square at that row and column.
 * \param row the row of the square
 * \param col the column of the square
 * \return true iff we successfully cleared any val from the square's pvals
 */
template<const unsigned int N>
bool
board<N>::purge_set(size_t row, size_t col, std::set<size_t> s)
{
    bool did_something=false, retval;
    std::set<size_t>::iterator i;
    for(i=s.begin();i!=s.end();i++){
	PURGE_SET_DEBUG std::cerr << "purge_set calling clear_pval_val(" << row << ", " << col << ", " << *i << ")\n";
	retval=clear_pval_val(row,col,*i);
	did_something|=retval;
    }
    return did_something;
}

/*!
 * clear all the values NOT in vals from all the squares in sqs
 * used only by discern_hidden() to turn hidden to naked sets
 * \param sqs a set of squares to have pvals trimmed
 * \param vals a set of vals to trim
 */
template<const unsigned int N>
void
board<N>::reduce_to_set(std::set<square*>& sqs,std::set<size_t>& vals)
{
    REDUCE_TO_SET_DEBUG std::cerr << "reduce_to_set: size of square set: " << sqs.size() << ", size of vals set: " << vals.size() << "\n";

    std::set<square*>::iterator sqs_itr;
    std::set<size_t>::iterator vals_itr;
    REDUCE_TO_SET_DEBUG{
	bool first_time=true;
	std::cerr << "vals set{";
	for(vals_itr=vals.begin();vals_itr!=vals.end();vals_itr++){
	    if(!first_time){
		std::cerr << ',';
	    }
	    first_time=false;
	    std::cerr << *vals_itr;
	}
	std::cerr << "}\n";
    }
    assert(sqs.size()==vals.size());

    RESPATH std::cerr << " ==>";
    for(sqs_itr=sqs.begin();sqs_itr!=sqs.end();sqs_itr++){
	REDUCE_TO_SET_DEBUG std::cerr << "square before reducing: \n";
	REDUCE_TO_SET_DEBUG std::cerr << **sqs_itr;
	bool reducing=true;
	while(reducing){
	    reducing=false;
	    square& sq=**sqs_itr; // convenience
	    for(size_t ctr=0;ctr<sq.size();ctr++){
		// sq[ctr] looks in sq at its pvals.  If the value isn't found
		// in the passed in vals, we need to purge it.
		if(vals.find(sq[ctr])==vals.end()){
		    clear_pval_val(sq.get_row(),sq.get_column(),sq[ctr]);
		    // calling erase invalidates the iterator underlying the
		    // square's operator[] so set a flag, and break out of
		    // the loop so it will restart loop to reinitialize
		    // the iterator.
		    reducing=true;
		    break;
		}
	    }
	}
	REDUCE_TO_SET_DEBUG std::cerr << "square after reducing: \n";
	REDUCE_TO_SET_DEBUG std::cerr << **sqs_itr;
    }
}

template<const unsigned int N>
void
board<N>::set_val(size_t row, size_t col,size_t val,bool set_pval)
{
    /*! This is intended to be the only place that board sets values, so that
     * count can be kept accurate.
     * \param row which row of the board is the square in
     * \param col which column of the board is the square in
     * \param val the value to set the square to
     */
    if(set_pval){
	// set_pval is normal case, i.e. the square's pvals will have
	// only one value after this equal to the square's values.
	// For brute force, though, the value is just a tentative value
	// and we don't clear pvals, they are other possibilities

	// You might think, that if set_pval is set and we pass it to
	// square::set_val, it will just clear the pvals and then set
	// the single one matching the value being set.  You'd be right.  BUT!
	// Then we wouldn't maintain our other data structure
	std::vector<size_t> spv;
	for(size_t ctr=0;ctr<b[row][col].size();ctr++){
	    // we make a copy of the square's pvals to avoid the invalidated
	    // iterator in pvals thing.
	    spv.push_back(b[row][col][ctr]);
	}
	// now we'll operate on the copy
	for(size_t ctr=0;ctr<spv.size();ctr++){
	    if(spv[ctr]!=val){
		// clear them individually in the square's pvals, as we walk
		// through our copy.  That way we can keep walking through the
		// copy with invalidating the iterator.
		// We call the board's clear_pval_val to clear one pval at a
		// time, because in addition to clearing the pval, the 
		// possibility structures are maintained
		clear_pval_val(row,col,spv[ctr]);
	    }
	}
    }
    // Finally we set the value
    b[row][col].set_val(val,set_pval);
    // and make the appearance of the value ripple through pvals
    update_pvals_for_square(row,col);
}

/*! does two things.
 * 1) Has the square at b[row][col] take val out of pvals if it exists.
 * 2) If it did exist, adjust the three possibility vectors, rows_possibilities
 *    column_possibilities, and block_possibilities, by removing the
 *    square at b[row][col] from the vector mapped to val in each of the 
 *    possibility arrays.
 * std::map<size_t,std::map<size_t,std::vector<square*>>> row_possibilities;
 *          row             val          squares
 * std::map<size_t,std::map<size_t,std::vector<square*>>> column_possibilities;
 *          col             val          squares
 * std::map<size_t,std::map<size_t,std::vector<square*>>> block_possibilities;
 *          block           val           squares
 * N.B. This is the only method called from ANY board routine that removes
 *    values from pval vectors.  That way we don't have to create the 
 *    possibility vectors over and over again, but can simply keep them 
 *    consistent here.
 * \param row the square is on this
 * \param col the square is on this
 * \param val the pval value to be cleared
 * \return true if something was actually done.
 */
template<const unsigned int N>
bool
board<N>::clear_pval_val(size_t row, size_t col,size_t val)
{
    if(val==0){
	// quick exit - no square has 0 in its pvals
	return false;
    }

    // ask the square to clear the val, cleared means val set before clearing
    bool cleared=b[row][col].clear_pval_val(val);
    RESPATH{
	// we supress this output on board construction
	if(cleared && !suppress_output){
	    std::cerr << ' ' << print_sq_rc_plus(&b[row][col]) << " ≠ " << val;
	}
    }
    std::vector<square*>::iterator i;

    if(cleared){
	// something happened so fix up the row/colum/block possibilities
	std::vector<square *>& sqs_row=row_possibilities[row][val];
	if((i=std::find(sqs_row.begin(),sqs_row.end(),&b[row][col]))!=sqs_row.end()){
	    // if we find the square in possibilities for row and val 86 it
	    sqs_row.erase(i);
	}
	std::vector<square *>& sqs_col=column_possibilities[col][val];
	if((i=std::find(sqs_col.begin(),sqs_col.end(),&b[row][col]))!=sqs_col.end()){
	    // if we find the square in possibilities for col and val 86 it
	    sqs_col.erase(i);
	}
	size_t block=get_block_num(row,col);
	std::vector<square *>& sqs_block=block_possibilities[block][val];
	if((i=std::find(sqs_block.begin(),sqs_block.end(),&b[row][col]))!=sqs_block.end()){
	    // if we find the square in possibilities for block and val 86 it
	    sqs_block.erase(i);
	}

    }
    return cleared;
}

/*!
 * given a row and column, remove the val set in the square at that row and
 * column from every other square that shares a row, column, or block with
 * the square at the row and column
 * called from board<N>::set_val
 * \param row the row in which we find a square
 * \param col the column in which we find a square
 */
template<const unsigned int N>
void
board<N>::update_pvals_for_square(size_t row, size_t col)
{
    // pulls the val of the square at b[row][col] from all the other squares
    // pvals that can see the square, i.e. that share a row, share a column,
    // or share a block.
    // if square not set, just return
    size_t val=b[row][col].get_val();
    if(val==0){
	return;
    }
    // pull square value from the other squares in the row

    for(size_t ctr=0;ctr<N;ctr++){
	if(ctr!=col){
	    clear_pval_val(row,ctr,val);
	}
    }
    // pull square value from the other squares in the column
    for(size_t ctr=0;ctr<N;ctr++){
	if(ctr!=row){
	    clear_pval_val(ctr,col,val);
	}
    }
    // pull square value from the other squares in the block
    // rows are 0-8.
    // We calculate row_min and col_min the same way:
    // We integer divide by root (sq root(N) which for 9x9 is 3)
    // then multiply by root, so 0-2 / 3 gives 0, *3 is 0
    //                           3-5 / 3 gives 1, *3 is 3
    //                           6-8 / 3 gives 2, *3 is 6
    // Then row_max and col_max is just row_min and col_min + root
    // Example row==7, col==4, board is 9x9 so root is 3
    // row_min  = 3 *(7/3) = 3 * 2 = 6, row_max=9
    // col_min  = 3 *(4/3) = 3 * 1 = 3, col_max=6
    size_t row_min=root*(row/root),
	   row_max=row_min+root,
	   col_min=root*(col/root),
	   col_max=col_min+root;
    for(size_t row_ctr=row_min;row_ctr<row_max;row_ctr++){
	for(size_t col_ctr=col_min;col_ctr<col_max;col_ctr++){
	    if(col!=col_ctr||row!=row_ctr){
		// only for squares that are not us
		clear_pval_val(row_ctr,col_ctr,val);
	    }
	}
    }
}

/*!
 * given a set of squares and a set of vals, 
 * 1) Notice if all of the squares are in same row, column, or block
 *    (could be row and block or column and block)
 * 2) If all on same row, loop through that row of the board and for
 *    each square not in the sqs set , remove anything in the v set
 *    from their pvals. Do the same for column or block match
 * used from discern_naked for naked pairs, triple, or quads
 * \param sqs a set of squares to operate on
 * \param v a set of values to be removed
 * \return true iff at least one of the vals existed in at least one of the squares and was successfully removed.
 */
template<const unsigned int N>
bool
board<N>::purge_from_set(std::set<square*>& sqs, std::set<size_t>& v)
{
    bool retval, did_something=false;
    bool do_rows=true,do_cols=true,do_blocks=true;
    std::set<square*>::iterator i=sqs.begin();
    size_t row=(*i)->get_row();
    size_t col=(*i)->get_column();
    size_t block=get_block_num(row,col);
    for(++i;i!=sqs.end();i++){
	if((*i)->get_row()!=row){
	    do_rows=false;
	}
	if((*i)->get_column()!=col){
	    do_cols=false;
	}
	if(get_block_num((*i)->get_row(),(*i)->get_column())!=block){
	    do_blocks=false;
	}
    }
    if(do_rows){
	PURGE_FROM_SET_DEBUG std::cerr << "purging row " << row << '\n';
	for(size_t tmpcol=0;tmpcol<N;tmpcol++){
	    if(std::find(sqs.begin(),sqs.end(),&b[row][tmpcol])==sqs.end()){
		retval=purge_set(row,tmpcol,v);
		did_something|=retval;
	    }
	}
    }
    if(do_cols){
	PURGE_FROM_SET_DEBUG std::cerr << "purging column " << col << '\n';
	for(size_t tmprow=0;tmprow<N;tmprow++){
	    if(std::find(sqs.begin(),sqs.end(),&b[tmprow][col])==sqs.end()){
		retval=purge_set(tmprow,col,v);
		did_something|=retval;
	    }
	}
    }
    if(do_blocks){
	PURGE_FROM_SET_DEBUG std::cerr << "purging block " << block << '\n';
	size_t row_min=root*(block/root),
	       row_max=row_min+root,
	       col_min=root*(block%root),
	       col_max=col_min+root;
	for(size_t row=row_min;row<row_max;row++){
	    for(size_t col=col_min;col<col_max;col++){
		if(std::find(sqs.begin(),sqs.end(),&b[row][col])==sqs.end()){
		    retval=purge_set(row,col,v);
		    did_something|=retval;
		}
	    }
	}
    }
    return did_something;
}

/*!
 * given a group type, either GT_ROW or GT_COLUMN, a set of row numbers, and a
 * set of column numbers, remove from the appropriate squares the value.
 * Appropriate is determined as follows:
 * if group type is GT_ROW, for each column in colset, walk the rows 0-N and
 * if the row is NOT in rowset, remove val from the pvals of the
 * square at row and column.  Conversely for group type of GT_COLUMN.
 * Called from discern interlock for x-wings, jellyfish, and swordfish
 * \param gt the type of group to purge for, one of GT_ROW, GT_COLUMN, or GT_BLOCK
 * \param rowset set of rows participating in an interlock (x-wing, swordfish, or jellyfish)
 * \param colset set of columns participating in an interlock
 * \param val the value shared by cells at the intersections of rows and columns
 * \return true iff we remove some val from some square's pvals
 */
template<const unsigned int N>
bool
board<N>::purge_row_col_sets(grouptype gt,std::set<size_t> rowset,std::set<size_t> colset,size_t val)
{
    bool did_something=false,retval;
    std::set<size_t>::iterator it;
    if(gt==GT_ROW){
	for(it=colset.begin();it!=colset.end();it++){
	    for(size_t row=0;row<N;row++){
		if(std::find(rowset.begin(),rowset.end(),row)==rowset.end()){
		    retval= did_something|=clear_pval_val(row,*it,val);
		    did_something|=retval;
		}
	    }
	}
    }else if(gt==GT_COLUMN){
	for(it=rowset.begin();it!=rowset.end();it++){
	    for(size_t col=0;col<N;col++){
		if(std::find(colset.begin(),colset.end(),col)==colset.end()){
		    retval=clear_pval_val(*it,col,val);
		    did_something|=retval;
		}
	    }
	}
    }
    return did_something;
}

template<const unsigned int N>
void
board<N>::dump_all_possibilities()
{
    /*! for each row, for each value dumps the squares that have that value
     * in their pvals
     *
     * for each colum, for each value dumps the squares that have that value
     * in their pvals
     *
     * for each block, for each value dumps the squares that have that value
     * in their pvals
     */
    std::cout << "~~~~~~~row_possibilities~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(size_t row=0;row<N;row++){
	dump_row_possibilities(row);
    }
    std::cout << "~~~~~~~column_possibilities~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(size_t col=0;col<N;col++){
	dump_column_possibilities(col);
    }
    std::cout << "~~~~~~~block_possibilities~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(size_t block=0;block<N;block++){
	dump_block_possibilities(block);
    }
}

template<const unsigned int N>
void
board<N>::dump_possibilities(std::map<size_t,std::vector<square*>> p)
{
    for(size_t val=1;val<N+1;val++){
	typename std::vector<square *>::iterator it1;
	typename std::vector<square *>::iterator it;
	std::vector<square *>& vs=p[val];  // convenience
	std::cout << "val: " << val << '\n';
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	for(it=vs.begin();it!=vs.end();it++){
	    std::cout << "  " << **it;;
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }
}

template<const unsigned int N>
void
board<N>::dump_row_possibilities(size_t row)
{
    // std::map<size_t,std::map<size_t,std::vector<square*>>> row_possibilities;
    //          row             val          squares
    std::map<size_t,std::vector<square*>> the_row=row_possibilities[row];
    std::cout << "Dumping for row " << row << '\n';
    for(size_t val=1;val<=N;val++){
	std::vector<square*> sqs=the_row[val];
	std::cout << "  val: " << val << '\n';
	std::vector<square*>::iterator i;
	for(i=sqs.begin();i!=sqs.end();i++){
	    std::cout << "    " << **i;
	}
    }
}

template<const unsigned int N>
void
board<N>::dump_column_possibilities(size_t col)
{
    // std::map<size_t,std::map<size_t,std::vector<square*>>> column_possibilities;
    //          col             val          squares
    std::map<size_t,std::vector<square*>> the_col=column_possibilities[col];
    std::cout << "Dumping for column " << col << '\n';
    for(size_t val=1;val<=N;val++){
	std::vector<square*> sqs=the_col[val];
	std::cout << "  val: " << val << '\n';
	std::vector<square*>::iterator i;
	for(i=sqs.begin();i!=sqs.end();i++){
	    std::cout << "    " << **i;
	}
    }
}

template<const unsigned int N>
void
board<N>::dump_block_possibilities(size_t block)
{
    std::map<size_t,std::vector<square*>> the_block=block_possibilities[block];
    std::cout << "Dumping for block " << block << '\n';
    for(size_t val=1;val<=N;val++){
	std::vector<square*> sqs=the_block[val];
	std::cout << "  val: " << val << '\n';
	std::vector<square*>::iterator i;
	for(i=sqs.begin();i!=sqs.end();i++){
	    std::cout << "    " << **i;
	}
    }
}

/*! \verbatim
 * std::map<size_t,std::map<size_t,std::vector<square*>>> row_possibilities;
 *          row             val          squares
 * row 0 -> val 1 -> pointertosquare, pointertosquare2, etc...
 *             .
 *             .
 *          val N -> pointertosquare1, pointerto square2, etc...
 *   .
 *   .
 *   .
 * row N -> val 1 -> pointertosquare1, pointertosquare2, etc...
 *             .
 *             .
 *          val N -> pointertosquare1, pointerto square2, etc...
 * \endverbatim
 * That way, for a particular row, if we want to know what squares have
 * a particular val in their pvals, we can get the vector like:
 *   row_possibilities[row][val];
 * and if we want to know how many have a particular val we can use
 *   row_possibilities[row][val].size();
 * The same, of course applies to columns and blocks
 */
template<const unsigned int N>
inline
void
board<N>::update_possibilities()
{
    row_possibilities.clear();
    for(size_t row=0;row<N;row++){
	for(size_t val=1;val<=N;val++){
	    for(size_t col=0;col<N;col++){
		if(b[row][col].in_vals(val)){
		    row_possibilities[row][val].push_back(&b[row][col]);
		}
	    }
	}
    }
    // std::map<size_t,std::map<size_t,std::vector<square*>>> column_possibilities;
    //          col             val          squares
    column_possibilities.clear();
    for(size_t col=0;col<N;col++){
	for(size_t val=1;val<=N;val++){
	    for(size_t row=0;row<N;row++){
		if(b[row][col].in_vals(val)){
		    column_possibilities[col][val].push_back(&b[row][col]);
		}
	    }
	}
    }
    // std::map<size_t,std::map<size_t,std::vector<square*>>> block_possibilities;
    //          block           val           squares
    block_possibilities.clear();
    for(size_t block=0;block<N;block++){
	size_t row_min=root*(block/root),
	       row_max=row_min+root,
	       col_min=root*(block%root),
	       col_max=col_min+root;
	for(size_t row=row_min;row<row_max;row++){
	    for(size_t col=col_min;col<col_max;col++){
		for(size_t val=1;val<=N;val++){
		    if(b[row][col].in_vals(val)){
			block_possibilities[block][val].push_back(&b[row][col]);
		    }
		}
	    }
	}
    }
}

/*! Does two things.  First, walk the whole board, and for each square
 * set the pvals based on the values visible from that square Second,
 * after they are all set, call board<N>::update_possibilities() to
 * set up three maps (one for rows, one for columns and one for blocks)
 * between vals and pointers to the squares that have
 * those vals. Those maps are used by some of the solution strategies
 * who want to know, for example how many squares in a row have 4 set.
 */
template<const unsigned int N>
inline
void
board<N>::update_pvals()
{
    for(size_t row=0;row<N;row++){
	for(size_t col=0;col<N;col++){
	    generate_pvals(row,col);
	}
    }
    update_possibilities();
}

/*! generate the possible values for this square based on all the other
 * squares we can see, i.e. in the same row, the same column, or in the
 * same block.
 * \param row the row of the square
 * \param col the column of the square
 * \param mark_invalid if true, when finding two of same value in a group mark both squares and the board invalid
 */
template<const unsigned int N>
void
board<N>::generate_pvals(unsigned int row, unsigned int col,bool mark_invalid)
{
    std::vector<unsigned int> tpval;
    GENPVALS_DEBUG std::cerr << "generate_pvals() before: " << b[row][col];
    if(b[row][col].is_locked()){
	// locked as a given in the puzzle so only possible value is our value
	tpval.push_back(b[row][col].get_val());
    }else{
	tpval={ 1,2,3,4,5,6,7,8,9};
	prune_column_pvals(row,col,tpval,mark_invalid);
	prune_row_pvals(row,col,tpval,mark_invalid);
	prune_block_pvals(row,col,tpval,mark_invalid);
    }
    b[row][col].assign_pvals(tpval);
    GENPVALS_DEBUG std::cerr << "generate_pvals after: " << b[row][col];
}

/*! generate a random valid complete board.
 * Currently on an old dell inspiron 1420 with linux on it, it can
 * generate more than 20,000 puzzles/second with this method at a rate
 * of about 46µs/board building with g++ with -O3 (with -O0 about
 * 400µs/board).
 * \return true if success (which we always expect)
 */
template<const unsigned int N>
bool
board<N>::generate()
{
    seed();
    bool backed=false;
    size_t row, col;
    ssize_t which=0;
    const ssize_t max=N*N;

    GENERATE_DEBUG std::cerr << "generate ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    if(valid){
	while(which!=max){
	    row=which/N;
	    col=which%N;
	    square& sq=b[row][col];
	    GENERATE_DEBUG std::cerr << "square[row: " << row << "][col: " << col << "]\n";
	    if(!backed){
		generate_pvals(row,col);
	    }else{
		GENERATE_DEBUG std::cerr << "not calling generate_pvals() since we backed\n";
		backed=false;
	    }
	    if(!sq.choose_val(true)){ // true gets rand memb of pvals
		// false return from choose_val means we couldn't get a val
		backed=true;
		do{
		    which--;
		    row=which/N;
		    col=which%N;
		    square& tmpsq=b[row][col];
		    GENERATE_DEBUG std::cerr << "    backed to square[" << row << "][" << col << "]";
		    if(tmpsq.size() > 1){
			// backing up we skip 
			// cells with only one value since we
			// would have already tried them.
			// Then on the cell we backed up to, we pull the
			// value we tried out of pvals and set the val to
			// zero so that at the top of the loop we'll try a
			// different value.
			GENERATE_DEBUG std::cerr << "...found next    -- clearing to 0 and breaking out.\n";
			tmpsq.clear_pval_val(tmpsq.get_val());
			tmpsq.set_val(0,false);
			break;
		    }else if(tmpsq.size()==1){
			GENERATE_DEBUG std::cerr << "...size(1)       -- clearing to 0, backing again.\n";
			tmpsq.set_val(0,false);
		    }else{
			// this would be a pvals size of zero
			GENERATE_DEBUG std::cerr << "DANGER DANGER WILL ROBINSON\n";
		    }
		}while(which>=0); // we expect to break before this
		if(which==-1){
		    // we failed and backed up off the front!
		    return false;
		}
		b[row][col].set_val(0,false);
		continue;	// continue so we don't bump which--it's on the
				// square we backed up to already.
	    }else{
		GENERATE_DEBUG std::cerr << "set the cell[" << row << "][" << col << "] to " << sq.get_val() << '\n';
	    }
	    // didn't backup, we set a value, go to next cell
	    which++;
	}
    }else{
	GENERATE_DEBUG std::cerr << "Skipped generating because board already marked invalid\n";
	return false;
    }
    for(size_t row=0;row<N;row++){
	for(size_t col=0;col<N;col++){
	    b[row][col].set_locked(true);
	}
    }
    return true;
}

template<const unsigned int N>
void
inline
board<N>::dig_one(size_t row,size_t col, board<N>& brd, symtype st)
{
    const size_t adj=N-1;
    brd.b[row][col].set_locked(false);
    brd.b[row][col].set_val(0);
    
    DIG_DEBUG std::cerr << "dig_one(" << row << "," << col << ",brd,";
    DIG_DEBUG print_st(std::cerr,st);
    DIG_DEBUG std::cerr << ")\n";

    DIG_DEBUG std::cerr << "digging square: " << brd.b[row][col];
    if(st&ST_HORIZ){
	brd.b[row][adj-col].set_locked(false);
	brd.b[row][adj-col].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[row][adj-col];
    }
    if(st&ST_VERT){
	brd.b[adj-row][col].set_locked(false);
	brd.b[adj-row][col].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[adj-row][col];
    }
    if(st&ST_HV){
	brd.b[row][adj-col].set_locked(false);
	brd.b[row][adj-col].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[row][adj-col];
	brd.b[adj-row][col].set_locked(false);
	brd.b[adj-row][col].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[adj-row][col];
	brd.b[adj-row][adj-col].set_locked(false);
	brd.b[adj-row][adj-col].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[adj-row][adj-col];
    }
    if(st&ST_MADIAG){
	brd.b[col][row].set_locked(false);
	brd.b[col][row].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[col][row];
	brd.b[adj-col][adj-row].set_locked(false);
	brd.b[adj-col][adj-row].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[adj-col][adj-row];
	brd.b[adj-row][adj-col].set_locked(false);
	brd.b[adj-row][adj-col].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[adj-row][adj-col];
    }
    if(st&ST_MDIAG){
	brd.b[col][row].set_locked(false);
	brd.b[col][row].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[col][row];
    }
    if(st&ST_ADIAG){
	brd.b[adj-col][adj-row].set_locked(false);
	brd.b[adj-col][adj-row].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[col][row];
    }

    if(st&ST_ROT){
	brd.b[col][adj-row].set_locked(false);
	brd.b[col][adj-row].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[col][adj-row];
	brd.b[adj-row][adj-col].set_locked(false);
	brd.b[adj-row][adj-col].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[adj-row][adj-col];
	brd.b[adj-col][row].set_locked(false);
	brd.b[adj-col][row].set_val(0);
	DIG_DEBUG std::cerr << "digging square: " << brd.b[adj-col][row];
    }
}

/*! generate a random valid complete board.
 * \param st a symmetry type, i.e. when we dig out a square, should we dig other squares related to the first via some sort of symmetry?  one or more of:
 * ST_NONE, ST_HORIZ, ST_VERT, ST_ROT90, ST_ROT180, ST_ROT270, ST_ROT, ST_MDIAG,
 * ST_ADIAG.  The meanings and effects are described below.
 * \param max_clues we dig until we drop to or below this number of clues left
 * \param status a boolean which if true makes the routine print '.' to the screen each time through loop so the user doesn't think it is hung up. Defaults to false
 * \return true if success (which we always expect)
 * \todo instead of trying for multiple solutions when getting down to a 
 * minimum of givens, when eliminating each value, we could substitute all
 * the other values in that cell and see if any of them leads to solutions
 * that way we can quit right away after a bad choice.  Needs research
 *
 * \par Comments
 * n.b. squares in this program are numbered horizontally and vertically 0 - N-1
 * which for N of 9, i.e. a usual sudoku puzzle, is 0 - 8,
 * and we normally denote them (r,c), or RrCc, so that a square at row seven and
 * column three would be denoted as (7,3) or R7C3).  Note also that if we use
 * N for the size of a column or row, i.e. 9 in a usual sudoku puzzle, we use
 * N' to mean N-1, or 8 in a usual sudoku puzzle.
 * \par ST_NONE a cell is dug but that's it
 * \code
 AB                             AB
 CD  no rotation or reflection  CD
 \endcode
 *   So if the square at R7C3 is dug, no others are dug.
 * \par ST_HORIZ when a cell is dug its horizontal reflection is also dug
 * \code
 AB                          BA
 CD  horizontally reflected  DC
 \endcode
 *   So if the square at R7C3 is dug, so is the square at R7C5, or in general, a
 *   square (r,c) is horizontally reflected to (r,N'-c), so that a cell at (7,3)
 *   will reflect to (7,8-3) or (7,5)
 * \code
  012345678
 0.........0
 1.........1  Here we see the cells (3,1), (4,0), (5,0), (6,0)
 2.........2  when horizontally reflected give 
 3.*.....@.3  (3,8-1), (4,8-0), (5,8-0), (6,8-0) or
 4*.......@4  (3,7), (4,8), (5,8), (6,8)
 5*.......@5  * - original cells
 6*.......@6 - rotated cells
 7.........7
 8.........8
  012345678
 \endcode
 *
 * \par ST_VERT when a cell is dug, so is its vertical reflection
 * \code
 AB                          CD
 CD  vertically reflected    AB
 \endcode
 *   So if the square at R7C3 is dug, so is the square at R1C3, or in general, a
 *   square (r,c) is vertically reflected to (N'-r,c), so that a cell at (7,3)
 *   will reflect to (8-7,3) or (1,3)
 * \code
  012345678
 0....@@@..0
 1...@.....1  Here we see the cells (7,3), (8,4), (8,5), (8,6)
 2.........2  when vertically reflected give 
 3.........3  (8-7,3), (8-8,4), (8-8,5), (8-8,6) or
 4.........4  (1,3), (0,4), (0,4), (0,4)
 5.........5  * - original cells
 6.........6 - rotated cells
 7...*.....7
 8....***..8
  012345678
 \endcode
 *
 * \par ST_HV when a cell is dug, so is its vertical reflection and the horizontal reflection of the original cell AND it's vertical reflection.
 * \code
 AB                                           DC
 CD  vertically and horizontally reflected    BA
 \endcode
 *   So if the square at R7C3 is dug, so is the square at R1C3, or in general, a
 *   square (r,c) is vertically reflected to (N'-r,c), so that a cell at (7,3)
 *   will reflect to (8-7,3) or (1,3)
 * \code
  012345678
 0..*...@..0
 1.**...@@.1  * (1,1), (1,2), (0,2)
 2.........2 (1,6), (1,7), (0,6) (horizontal reflection of *)
 3.........3  % (7,1), (7,2), (8,2) (vertical reflection of *)
 4.........4  # (7,6), (7,7), (8,6) (vertical reflection of @)
 5.........5  
 6.........6 
 7.%%...##.7
 8..%...#..8
  012345678
 \endcode
 *
 * \par ST_ROT90 when a cell is dug, so is the cell 90 degrees clockwise
 * \code
 AB              CA
 CD rotated 90°  DB
\endcode
 *   So if the square at R7C3 is dug, then so will the one at R3C1 or in general,
 *   with N being 9, the size of a row or column, if we select a cell (r,c),
 *   then we also dig the cell (c,N'-r)
 * \code
  012345678
 0.........0
 1.........1  Here we see the cells (given as (r,c)) (7,3), (8,4), (8,5), (8,6)
 2.........2  rotated 90° gives (3,8-7), (4,9-1-8), (5,9-1-8), (6,9-1-8) or
 3.@.......3  (3,1), (4,0), (5,0), (6,0)
 4@........4
 5@........5  * - original cells
 6@........6 - rotated cells
 7...*.....7
 8....***..8
  012345678
\endcode
 * \par ST_ROT180 when a cell is dug, so is the cell rotated 180° clockwise
 * \code
 AB              DC
 CD  rotate 180° BA
 * \endcode
 *   So if the square at R7C3 is dug, then so will the one at R1C5 or in general,
 *   if we select a cell (r,c), then we also dig the cell (N'-r,N'-c) 
 *   N.B. This call also be done with a ST_HORIZ followed by a ST_VERT, or vice-
 *   versa.
 \code
  012345678
 0..@@@....0
 1.....@...1  Here we see the cells (7,3), (8,4), (8,5), (8,6)
 2.........2  rotated 180° give (8-7,8-3), (8-8,8-4), (8-8,8-5), (8-8,8-6),
 3.........3  or (1,5), (0,4), (0,3), (0,2)
 4.........4
 5.........5  * - original cells
 6.........6 - rotated cells
 7...*.....7
 8....***..8
  012345678
 \endcode
 *
 * \par ST_ROT270 when a cell is dug, so is the cell rotated 270° clockwise
 * \code
 AB              BD
 CD  rotate 270° AC
 * \endcode
 *   So if the square at R7C3 is dug, then so will the one at R5C7 or in general,
 *   if we select a cell (r,c), then we also dig the cell (N'-c,r) 
 *   N.B. This call also be done with a ST_HORIZ followed by a ST_VERT, or vice-
 *   versa.
 \code
  012345678
 0.........0
 1.........1  Here we see the cells (7,3), (8,4), (8,5), (8,6)
 2........@2  rotated 180° give (8-3,7), (8-4,8), (8-5,8), (8-6,8),
 3........@3  or (5,7), (4,8), (4,8), (4,8)
 4........@4
 5.......@.5  * - original cells
 6.........6 - rotated cells
 7...*.....7
 8....***..8
  012345678
 \endcode
 *
 * \par ST_ROT when a cell is dug, cells 90°, 180° and 270° rotated are dug also.
 * This is used as a shorthand for ST_ROT90|ST_ROT180|ST_ROT270
 * \code
 AB       CA           DC           BD
 CD  +90° DB +90°=180° BA +90°=270° AC
 * \endcode
 \code
  012345678
 0..@@@....0
 1.....@...1  Here we see the cells (7,3), (8,4), (8,5), (8,6)
 2........@2  rotated 180° give (8-7,8-3), (8-8,8-4), (8-8,8-5), (8-8,8-6),
 3.@......@3  or (1,5), (0,4), (0,3), (0,2)
 4@.......@4
 5@......@.5  * - original cells
 6@........6 - rotated cells
 7...*.....7
 8....***..8
  012345678
 \endcode

 \par ST_MDIAG when a cell is dug, a cell is also dug reflected across the main diagonal that runs from the top left to bottom right.
\code
 AB                                     AC
 CD  reflected across the main diagonal BD
\endcode
So if a cell is dug at (7,3), we would also dig the cell at (3,7), or in general,
if a cell at (r,c) is dug, we would also dig the cell at (c,r).  Note that this
is the same as a 90° clockwise rotation followed by a reflection about the Y
axis.
 \code
  012345678
 0.........0
 1.........1  Here we see the cells (7,3), (8,4), (8,5), (8,6)
 2.........2  main reflection gives (3,7), (4,8), (5,8), (6,8),
 3.......@.3
 4........@4  * - original cells
 5........@5 - rotated cells
 6........@6
 7...*.....7
 8....***..8
  012345678
 \endcode

 \par ST_ADIAG when a cell is dug, a cell is also dug reflected across the anti-diagonal that runs from the top right to bottom left.
\code
 AB                                     DB
 CD  reflected across the anti-diagonal CA
\endcode
  So if a cell is dug at (7,3), we would also dig the cell at (5,1), or in general,
  if a cell at (r,c) is dug, we would also dig the cell at (N'-c,N'-r). Note
  that this is the same as a reflection around the Y axis followed by a 90°
  clockwise rotation.
 \code
  012345678
 0.........0
 1.........1  Here we see the cells (7,3), (8,4), (8,5), (8,6)
 2@........2  anti reflection gives (8-3,8-7), (8-4,8-8), (8-5,8-8), (8-6,8-8),
 3@........3  or (5,1), (4,0), (3,0), (2,0)
 4@........4
 5.@.......5  * - original cells
 6.........6 - rotated cells
 7...*.....7
 8....***..8
  012345678
 \endcode

 \par ST_MADIAG when a cell is dug, a cell is also dug reflected across the anti-diagonal that runs from the top right to bottom left, and then that new cell, and the original one are dug reflected across the main diagonal, so for each cell picked, you get four cells.  If instead, you just specified ST_MDIAG|ST_ADIAG, you would only get three cells.
  So if a cell is dug at (7,3), we would also dig the cell at (5,1), at (3,7) and 
  at (1,5) or in general, if a cell at (r,c) is dug, we would also dig the cell
  at (N'-c,N'-r), at (c,r), and at (N'-r,n'-c).
 \code
  012345678
 0..@@@....0
 1.....@...1  Here we see the cells (7,3), (8,4), (8,5), (8,6)
 2@........2  MA reflection (8-3,8-7), (8-4,8-8), (8-5,8-8), (8-6,8-8), (3,7)
 3@......@.3  (4,8), (5,8), (6,8), (8-7,8-3), (8-8,8-4), (8-8,8-5), (8-8,8-6)
 4@.......@4  or (5,2), (4,0), (3,0), (2,0), (3,7), (4,8), (5,8), (6,8),
 5.@......@5  (1,5), (0,4), (0,3), (0,2)
 6........@6  * - original cells
 7...*.....7 - rotated cells
 8....***..8
  012345678
 \endcode
 *
 */
template<const unsigned int N>
bool
board<N>::dig_puzzle(symtype st,size_t max_clues,bool status)
{
   
    DIG_DEBUG std::cerr << "dig_puzzle(";
    DIG_DEBUG print_st(std::cerr,st);
    DIG_DEBUG std::cerr << "," << max_clues << ")\n";
    size_t low_count=N*N;
    board<N> b,tmp1;
    b.generate();
    DIG_DEBUG std::cerr << "after generate()~~~~~~~~~~~~~\n";
    //size_t solutions=b.brute_force_solution(1);
    DIG_DEBUG b.print_large();
    //DIG_DEBUG std::cerr << "bfc: " << b.brute_force_solution(2) << '\n';

    tmp1=b;
    while(true){
	if(status) std::cerr << '.';
	size_t row=rand_n(N);
	size_t col=rand_n(N);
	dig_one(row,col,tmp1,st);
	if(tmp1.count()<low_count) low_count=tmp1.count();
	DIG_DEBUG{
	    std::cerr << "count is: " << tmp1.count()
		   << ", low count: " << low_count << "\n";
	}
	if(tmp1.count() <= max_clues){
	    DIG_DEBUG std::cerr << "calling bfc\n";
	    tmp1.update_pvals();
	    DIG_DEBUG tmp1.print();
	    size_t solutions=tmp1.brute_force_solution(2);
	    DIG_DEBUG{
		std::cerr << "called bfc, solutions: " << solutions << "\n";
	    }
	    if(solutions>1 || solutions==0){
		DIG_DEBUG{
		    std::cerr << "not 1 solutions, but: " << solutions << ", starting over\n";
		}
		if(status){
		    std::cerr << "starting over, down to " << tmp1.count() << " clues, but " << solutions << " solutions\n";
		}
		b.generate();
		tmp1=b;
	    }else {
		*this=tmp1;
		DIG_DEBUG std::cerr << "returning a solution\n";
		update_pvals();
		count();
		return true;
	    }
	}
    }
    count();
    return true;
}

/*! using the registered name, ("x-wing", "hidden double", etc...), look
 * to see how many times the apply method was successfully applied.  Of 
 * course this will make most sense after calling the heuristic_solution()
 * method and solving a puzzle
 * \param name the name of the method as registered
 * \return the number of times the method was successfully invoked with 
 * success meaning that it caused a change in val and/or pvals for one or
 * more squares. i.e. just because we find a naked double doesn't mean
 * that we'll find pvals that we can clear.  If we don't clear them, then
 * the "naked double" count does not get incremented.
 */
template<const unsigned int N>
size_t
board<N>::get_strategy_count(std::string name)
{
    for(auto strategy : sorted_strategies){
	if(strategy->get_name() == name){
	    return strategy->get_count();
	}
    }
    return 0;
}

/*! walk through the board and count the squares with values set.
 * \return size_t the count
 */
template<const unsigned int N>
size_t
board<N>::count()
{
    size_t retval=0;
    for(size_t row=0;row<N;row++){
	for(size_t col=0;col<N;col++){
	    if(b[row][col].get_val()!=0){
		retval++;
	    }
	}
    }
    return retval;
}

/*!
 * apply all of the solution methods one at a time from simplest to
 * more complex until one succeeds.  Then start over.  That means that
 * if we can solve a puzzle by only applying naked_single::apply(),
 * no other methods will be tried. 
 * N.B. this is NOT guaranteed to solve a puzzle.  More difficult
 * puzzles may require methods not yet implemented.  Currently, this
 * can solve any puzzles that people will reasonably solve with pencil
 * and paper.
 * \param preserve_pvals if true, don't call update_pvals() -- used by testing
 */
template<const unsigned int N>
bool
board<N>::heuristic_solution(bool preserve_pvals)
{
    HEURISTIC_DEBUG std::cerr << "heuristic_solution()\n";

    if(!preserve_pvals){
	// normally of course, we'd always want to make sure that our pvals are
	// all correct, but in testing, we set up abnormal situations,
	// i.e. combinations of pvals and vals, to trigger particular paths
	// through the code, and in that case we do NOT want to update the pvals
	// In this case we DO want to update the pvals, and that also updates
	// the possibilities data maps.
	update_pvals();
    }else{
	// even if we aren't updating pvals, we need these data structures
	// to reflect the pvals we got from testing so that the heuristic
	// solution methods that use them will work.
	update_possibilities();
    }
    for(auto s : sorted_strategies){
	s->clear_count();
    }

    HEURISTIC_DEBUG{
	std::cerr << "  before heuristic\n";
	print_large();
    }

    bool progressing=true;

    while(progressing && count()!=N*N){
	progressing=false;
	for( auto m : sorted_strategies){
	    HEURISTIC_DEBUG{
		std::cerr << "calling " << std::left << std::setw(13) << m->get_name() << " apply ... ";
	    }
	    if(m->get_sort_level()==0){
		HEURISTIC_DEBUG{
		    std::cerr << "disabled, skipping\n";
		}
		continue;
	    }
	    if(m->apply()){
		progressing=true;
		HEURISTIC_DEBUG{
		    std::cerr << bold << "succeeded!\n" << unbold;
		}
		break;
	    }else{
		HEURISTIC_DEBUG std::cerr << "failed\n";
	    }
	}
    }
    HEURISTIC_DEBUG{
	std::cerr << "  after heuristic\n";
	print_large();
    }
    return is_solved();
}

/*!
 * This routine looks for solutions using a brute force algorithm. After
 * finding one solution, it optionally 
 * remembers it and then trys to remove the previous
 * found value from each square that isn't locked in turn to see if we find
 * another solution.  You might actually find a lot of solutions if you 
 * set how_many to -1 (like millions and millions!) We really don't care to
 * find ALL * solutions, this is used when digging out a generated board to see
 * if we've * dug out too many and have created a puzzle with more than one
 * solution.  We don't need to know more than that there is more than one
 * solution, so the additional data structures and execution time to find all
 * is not required.
 * \param how_many number of solutions to find. -1 means all, 2 is common just
 * to see if there is more than 1, and 1 is used to find A solution.
 * \param return_board Normally this routine works on a copy of the board
 * leaving the board untouched. If this is set to true (default false) or
 * when how_many is 1, we assign the last found solution to our board
 * \return size_t the number of found solutions--this is always 0, 1, or up
 * to how_many
 */
template<const unsigned int N>
size_t
board<N>::brute_force_solution(ssize_t how_many,bool return_board)
{
    // on entrance pvals are all set because constructors that take strings
    // call update_pvals()
    BRUTE_CHECK_DEBUG std::cerr << "brute force check ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    BRUTE_CHECK_DEBUG std::cerr << "brute_force_check() got this board: \n";
    BRUTE_CHECK_DEBUG print_large();

    bool backed_up=false;
    size_t row, col, solutions=0;
    ssize_t target_square=0,	// idx from first_target to N*N through squares
	    first_target=0;	// First place not locked with possibilities > 1
    const ssize_t max=N*N;	// number of squares in board
    board<N> checkb=*this;	// get copy of board
    // now find first square not locked with more than 1 possibility
    BRUTE_CHECK_DEBUG{
	std::cerr << "calling first_target to look for first unlocked square"
	    " with more than one possibility\n";
    }

    // This part is just an optimization to skip any cells at the beginning
    // that are locked or only have one pval
    first_target=get_first_target(first_target,checkb);
    if(first_target<max){
	row=target_square/N;
	col=target_square%N;
	square& target_square_sq=checkb.b[row][col];
	target_square_sq.set_val(target_square_sq[0],false);
	target_square_sq.clear_pval_val(target_square_sq.get_val());
	target_square=first_target+1;
	BRUTE_CHECK_DEBUG{
	    std::cerr << "first target is " << print_sq_rcp(&target_square_sq)
		<< '\n';
	}
    }else{
	BRUTE_CHECK_DEBUG std::cerr << "first target not found - board already solved? aborting\n";
	return 0;
    }

    if(valid){	// if not a valid puzzle i.e. same num twice on a line no point
	while(solutions<static_cast<size_t>(how_many)){ // our brute solver is in this loop
	    BRUTE_CHECK_DEBUG{
		std::cerr << "solutions main loop outside of solver\n"
		    "there are " << solutions << " solutions so far\n";
	    }
	    while(target_square!=max){ // this loop IS the solver
		row=target_square/N;
		col=target_square%N;
		square& target_square_sq=checkb.b[row][col];
		BRUTE_CHECK_DEBUG{
		    std::cerr << "  " << print_sq_rc(&target_square_sq)
			<< ", locked: " << std::boolalpha
			<< target_square_sq.is_locked() << '\n';
		}
		if(!target_square_sq.is_locked()){
		    // square not locked, so try to deal with it.
		    BRUTE_CHECK_DEBUG{
			std::cerr << "  square not locked so dealing with it\n";
		    }
		    if(!backed_up){
			checkb.generate_pvals(row,col,false);
			BRUTE_CHECK_DEBUG{
			    std::cerr << "    haven't backed, so calling "
				"generate_pvals\n      "
				<< print_sq_rcp(&target_square_sq) << '\n';
			}
		    }else{
			// here backed was true, so we are dealing with the
			// existing pvals with the last used val taken out,
			// so we don't call generate_pvals because that would
			// mess it up! We do set backed to false, so as we
			// walk forward again we can generate pvals for
			// successive squares until we either get a solution
			// or hit a square with 0 possible values and have
			// to back up again and try something different.
			BRUTE_CHECK_DEBUG{
			    std::cerr << "    not calling generate_pvals()"
				" since we backed\n";
			}
			backed_up=false;
		    }
		    if(target_square_sq.size()){
			// target square has pvals try next val
			// we don't take the pval out until it fails
			// that is done while backing up
			BRUTE_CHECK_DEBUG{
			    std::cerr << "      setting val to first pval, "
				<< target_square_sq[0] << '\n';
			}
			target_square_sq.set_val(target_square_sq[0],false);
		    }else{ // backing up
			BRUTE_CHECK_DEBUG{
			    std::cerr << "        no more pvals, rewinding: "
				<< print_sq_rcp(&target_square_sq) << '\n';
			}
			// There's no more vals, we'll have to rewind.
			backed_up=true;
			target_square--;
			while(target_square!=-1){
			    backed_count++;
			    if(target_square>=first_target){
				row=target_square/N;
				col=target_square%N;
				square &target_square_sq=checkb.b[row][col];
				BRUTE_CHECK_DEBUG{
				    std::cerr << "    backed up to "
					<< print_sq_rcp(&target_square_sq)
					<< '\n';
				}
				if(!target_square_sq.is_locked()
					&& target_square_sq.size() > 1){
				    // backing up we skip locked since we can't
				    // change them and cells with only one
				    // value since we already tried that value.
				    // On the cell we back to, we pull out the
				    // value we last tried from pvals and set
				    // val to 0 so that at the top of the loop
				    // we will try a different value.
				    target_square_sq.clear_pval_val(target_square_sq.get_val());
				    target_square_sq.set_val(0,false);
				    BRUTE_CHECK_DEBUG{
					std::cerr << "      found next    --"
					    " clear current pval, set value"
					    " to 0 and break out.\n"
					    << print_sq_rcp(&target_square_sq) 
					    << '\n';
				    }
				    break;
				}else if(target_square_sq.is_locked()){
				    BRUTE_CHECK_DEBUG{
					std::cerr << "      square locked --"
					    " backing again\n";
				    }
				}else if(target_square_sq.size()==1){
				    // if we left a value in the square it 
				    // would affect generation of pvals for
				    // other squares, so as we back past it
				    // we clear its value;
				    BRUTE_CHECK_DEBUG{
					std::cerr << "      size(1)       --"
					    " clearing value to 0, backing"
					    " again\n";
				    }
				    target_square_sq.set_val(0,false);
				}else{
				    BRUTE_CHECK_DEBUG std::cerr << "DANGER DANGER WILL ROBINSON\n";
				}

			    }else { // if haven't backed off front
				// backed past first target, no more solns
				return solutions;
			    }
			    target_square--;
			}
			// When we fall out, it's either because target_square
			// is < first_target because we couldn't find a
			// solution, or because we broke because we'd backed_up
			// to a good candidate for change
			if(target_square<first_target){
			    // we failed and backed_up up off the front!
			    // no more solutions (if any)
			    BRUTE_CHECK_DEBUG{
				std::cerr << "backed_up off of front,"
				    " there are " << solutions
				    << " solutions\n";
			    }
			    return solutions;
			}
			continue; // skip incrementing target_square since
				  // we backed_up or are starting over.
		    }
		}
		target_square++;
		// cell was locked or chose a value, go to next cell
	    } // while(target_square!=max)
	    solutions++;
	    if(solutions<static_cast<size_t>(how_many)){
		// note to future self: This sets us up to keep going
		// looking for future solutions, but if we have already
		// found all we are looking at, we don't want to mess
		// this last one up.  Right now it only really affects
		// the case where how_many==1, so just below we can
		// assign this solved board to the real board and pass
		// it out solved. Later we might do the same with others
		// with maybe a flag to control the behavior.
		target_square--;
		row=target_square/N;
		col=target_square%N;
		square &target_square_sq=checkb.b[row][col];
		backed_up=true;
		target_square_sq.clear_pvals();
		target_square_sq.set_val(0,false);
	    }
	} // while(solutions<how_many)
	if(how_many==1 || return_board){
	    *this=checkb;
	}
    } // if(valid)
    BRUTE_CHECK_DEBUG std::cerr << "fell off bottom, maxed out first_target: " << first_target << '\n';
    return solutions;
}

#endif
