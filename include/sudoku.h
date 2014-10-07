#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>
#include <assert.h>
#include <algorithm>
#include <ncurses.h>

// the escape sequences seen below are recognized by most terminals in linux to
// make text bold and to stop bolding text.  This allows us to give more 
// information, for example when printing a board, we can bold the original 
// numbers given in the puzzle and not numbers found during solution.  If you
// want to capture output in a text file, however, it might look like a bunch
// of gobbledegook in your editor.  At that point you might want to comment
// out the next line.
//#define USE_TTY_BOLD
#ifdef USE_TTY_BOLD
    const char bold[]={ 27,'[','1','m',0 };
    const char unbold[]={ 27,'[','0','m',0 };
#else 
    const char *bold="";
    const char *unbold="";
#endif

#define SHOW_RESPATH // N.B. all RESPATH print 1 based, not 0 based

// uncomment appropriate SHOW_XXX lines below to see debugging information about
// the corresponding section

//#define SHOW_BRUTE_DEBUG
//#define SHOW_BRUTE_CHECK_DEBUG
//#define SHOW_CHOOSE_VAL_DEBUG
//#define SHOW_GENERATE_DEBUG
//#define SHOW_DIG_DEBUG
//#define SHOW_PRUNING_DEBUG
//#define SHOW_BOARD_CONSTRUCT_DEBUG
//#define SHOW_HEURISTIC_DEBUG
//#define SHOW_SUDOKU_METHOD_DEBUG
//#define SHOW_REGISTER_STRATEGY_DEBUG
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
//#define SHOW_X_WING_DEBUG
//#define SHOW_Y_WING_DEBUG
//#define SHOW_Y_WING_APPLY_DEBUG
//#define SHOW_SWORDFISH_DEBUG
//#define SHOW_JELLYFISH_DEBUG
//#define SHOW_XY_CHAIN_DEBUG
//#define SHOW_XY_CHAIN_FILT_DEBUG

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

#if defined(SHOW_RESPATH)
#define RESPATH
#else
#define RESPATH if(0)
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
    struct timeval tv;
    if(aseed != 0){
	// if we get passed a seed, then use it
	srandom(aseed);
    }else{
	gettimeofday(&tv,NULL);
	srandom(tv.tv_sec*tv.tv_usec);
    }
}

int
inline
rand_n(size_t n)
{
    /*!
     * generate a number between [0 - n) as in integer.
     * i.e. if n==7, there's an equal change of returning {0,1,2,3,4,5,6} 
     * \param n the non-inclusive upper bound
     * \return an integer [0 - n)
     */
    return int((double(random()) / double(RAND_MAX)) * n);
}

//! keeps information about each square of the sudoku board
/*!
 * This class is used by class board to keep track of set values, and of possible
 * values based on other square's values.
 */
class square
{
    friend std::ostream& operator<<(std::ostream& os, square&sq);
public:
    square();
    square(const square&);
    //! This enum holds the types of algorithms that may touch a square.
    //! The purpose is to avoid time waste or loops, from finding the same
    //! thing more than once.
    enum matched_type{
	// square's mt field get marked with these as the corresponding
	// algorithms are successfully applied.  So we don't try to apply
	// the same algorithm to the same squares over and over wasting time, or
	// for some of the algorithms, so we don't create an infinite loop.
	// Later, if pvals change in any way, we clear the mt field again.
	// n.b. we do not note hidden or naked singles because this result in
	// values being set immediately and make the squares no longer of 
	// interest to other heuristics.
	AM_NONE=0,
	AM_NAKED_DOUBLE=1,
	AM_HIDDEN_DOUBLE=2,
	AM_NAKED_TRIPLE=4,
	AM_HIDDEN_TRIPLE=8,
	AM_NAKED_QUAD=16,
	AM_HIDDEN_QUAD=32,
	AM_ROW_BLOCK_INTERSECTION=64,
	AM_COLUMN_BLOCK_INTERSECTION=128,
	AM_BLOCK_ROW_INTERSECTION=256,
	AM_BLOCK_COLUMN_INTERSECTION=512,
	AM_X_WING=1024,
	AM_SWORDFISH=2048,
	AM_JELLYFISH=4096,
	AM_Y_WING=8192,
	AM_XY_CHAIN=16384

    };

    /*!
      make a string representation of a matched type
      \param mt The type to represent
      \return the representation as a std::string
      */
    std::string mt2string(matched_type mt){
	std::vector<std::string> AM_NAMES={
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
	    "AM_XY_CHAIN"
	};
	size_t tmpmt=mt;
	if(!tmpmt){
	    return "AM_NONE";
	}else{
	    for(size_t ctr=0;tmpmt;ctr++){
		if(tmpmt&1){
		    return AM_NAMES[ctr];
		}
		tmpmt>>=1;
	    }
	}	
	return "AM_NOT_FOUND!!!";
    }
    square&
    operator=(const square&);
    square(size_t rw, size_t cl, std::vector<unsigned int> pv);
    square(size_t rw, size_t cl, size_t vl, std::vector<unsigned int> pv);
    //! default filter used by get_neighbors() always returns true
    bool
    true_filt(square*){return true;};
    //! filter for get_neighbors returns true for squares with 2 members of pvals
    bool
    two_filt(square*sq){if(sq->size()==2) return true;return false;};
    //! filter for get_neighbors returns true for squares with 8 members of pvals
    bool
    eight_filt(square*sq){if(sq->size()==8) return true;return false;};
    //! filter for get_neighbors returns true for squares with 9 members of pvals
    bool
    nine_filt(square*sq){if(sq->size()==9) return true;return false;};

    /*! filter for get_neighbors.  Called when we have two pvals and have
     *  claimed one of them for ourselfs.  We're looking for squares that
     *  also have two pvals, and that matches the pval we claim.
     *  \param sq a pointer to the square to be checked to see if it has
     *         two pvals and one of them matches the one we own
     *  \return true if the square has 2 pvals one of which matches the one
     *         we own.
     */
    bool
    xy_chain_filt(square*sq){
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
    void
    set_owned(size_t o){ owned=o; };
    //!get pvals[owned]
    size_t
    get_xy_owned(){ return pvals[owned]; };
    //!get pval[1-matched], i.e. the other of the pair that is not owned
    size_t
    get_xy_next(){ return pvals[1-owned]; };
    //! assigns the passed in vector to our pvals and clears mt
    void
    assign_pvals(std::vector<unsigned int>& vals);
    //! removes everything from our pvals and clears mt
    void
    clear_pvals();
    //! returns whatever is in our val, 0 for unset, else 1-N
    unsigned int get_val() const { return val; }
    //! sets our value if not already locked
    void set_val(unsigned int v,bool set_pval=true){
	if(!locked){
	    val=v;
	    // did have code to clear pvals and set it to just the set value, 
	    // but that broke brute force which relies on being able to use 
	    // pvals to try one value after another.  So I added another argument,
	    // set_pval defaulted to true, so heuristic methods can set a val
	    // and also set pvals to the same thing, but brute force can use 
	    // another argument set to false to avoid setting pvals.
	    if(set_pval){
		mt=AM_NONE;
		pvals.clear();
		pvals.push_back(val);
	    }
	}
    }
    size_t get_row() const { return row; }//!< accessor for row of the square
    size_t get_column() const { return col; }//!< accessor for column of the square
    bool is_locked()const { return locked;}//!<locked means val set can't change
    void set_locked(bool d){ locked=d;mt=AM_NONE; }//!<make square locked
    bool choose_val(bool rand=true);//!<chooses from pvals
    bool in_vals(size_t) const;//!<return true of input is in pvals
    bool check_pval_set(std::set<size_t>);//!<return true iff pvals is identical to input
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
	 returned by std::find to erase that value.  If we DO find it,
	 \param in_val the value to be removed
	 \return true if in_val was in our pvals, and we had to clear it. else if we did nothing, return false.
     */
    bool
    clear_pval_val(size_t in_val){
	std::vector<unsigned int>::iterator it;
	it=std::find(pvals.begin(),pvals.end(),in_val);
	CLEAR_PVAL_VAL_DEBUG std::cerr << "square::clear_pval_val(" << in_val << "): " << *this << '\n';
	if(it!=pvals.end()){
	    mt=AM_NONE;
	    pvals.erase(it);
	    CLEAR_PVAL_VAL_DEBUG std::cerr << "square::clear_pval_val(" << in_val << "): true " << *this << '\n';
	    CLEAR_PVAL_VAL_DEBUG std::cerr <<"square::clear_pval_val(" << in_val << "): exiting true\n";
	    return true;
	}
	CLEAR_PVAL_VAL_DEBUG std::cerr << "square::clear_pval_val(" << in_val << "): exiting false\n";
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
    //! sets the matched type used to tell what algorithm has been applied
    void
    set_matched_type(const matched_type in_mt){if(in_mt==AM_NONE) mt=AM_NONE; else mt=matched_type(mt|in_mt);}
    //! pull a matched type bit out of the mt bitset
    void
    clear_matched_type(const matched_type in_mt){if(mt&in_mt) mt=matched_type(mt-in_mt);}
    //! check to see if a particular bit is set in our matched type bitset
    bool
    check_matched_type(const matched_type in_mt) const {return mt&in_mt;}
    /*!
     * allow access to the pvals by index
     * \param which 0 based index into pvals
     * \return -1 if out of range, else pvals[which]
     */
    ssize_t
    operator[](size_t which){
	return which<pvals.size()?pvals[which]:-1;
    }
    //! returns size of pvals
    size_t
    size(){return pvals.size();};
private:
    bool locked; //!< if true, square is immutable, for example given clue
    unsigned int val;	//!< The value of the square in the board
    size_t row;//!< row in board.  Really board's info but convenient here
    size_t col;//!< column in board.
    std::vector<unsigned int> pvals;//!<possible values for an unset square
    std::vector<unsigned int> saved_vals;//!<unused
    bool valid;//!<false when two squares that can see each other have same value
    matched_type mt;//!<bitset of algorithms that used this square
    size_t owned; // which of 2 pvals we own for xy-chain.
};

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
    val=0;
    pvals.clear();
    pvals={ 1,2,3,4,5,6,7,8,9 };
    locked=false;
    valid=true;
    mt=AM_NONE;
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
    pvals=pv;
    val=0;
    row=rw;
    col=cl;
    mt=AM_NONE;
    locked=false;
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
    pvals=pv;
    val=vl;
    row=rw;
    col=cl;
    mt=AM_NONE;
    locked=false;
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
    pvals=other.pvals;
    locked=other.locked;
    mt=other.mt;
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
    pvals=other.pvals;
    locked=other.locked;
    mt=other.mt;
    return *this;
}
/*!
 * copies vals to our pvals and as a side-effect, clears mt
 * \param vals the values to copy to our pvals
 */
void
square::assign_pvals(std::vector<unsigned int>& vals)
{
    pvals=vals;
    mt=AM_NONE;
}

/*!
 * clears our pvals and as a side effect sets mt to AM_NONE
 */
void
square::clear_pvals()
{
    pvals.clear();
    mt=AM_NONE;
}

/*!
 * when passed a set of numbers, checks to make sure pvals contains
 * all of the numbers and no others.
 * \param pvs a set of size_t to be compared to our pvals
 * \return true if there is an exact match, i.e. sets are identical
 */
bool
inline
square::check_pval_set(std::set<size_t>pvs)
{

    std::set<size_t> excludes={1,2,3,4,5,6,7,8,9};
    std::set<size_t>::iterator eit;
    std::set<size_t>::iterator pit;
    for(pit=pvs.begin();pit!=pvs.end();pit++){
	if((eit=std::find(excludes.begin(),excludes.end(),*pit))!=excludes.end()){
	    excludes.erase(eit);
	}
	if(std::find(pvals.begin(),pvals.end(),*pit)==pvals.end()){
	    return false;
	}
    }
    for(eit=excludes.begin();eit!=excludes.end();eit++){
	if(std::find(pvals.begin(),pvals.end(),*eit)!=pvals.end()){
	    return false;
	}
    }
    return true;

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
operator<<(std::ostream& os, square&sq){
    /*!
     * dump a square to the passed in stream
     * \param os the stream to dump to
     * \param sq the square to dump
     * \return os
     */
    os << "square[" << sq.row << "][" << sq.col << "]"
       << ", val: " << sq.val
       << ", locked: " << std::boolalpha << sq.is_locked()
       << ", pvals: {";
    std::vector<unsigned int>::iterator it;
    bool first=true;
    for(it=sq.pvals.begin();it!=sq.pvals.end();it++){
	if(!first) os << ", ";
	first=false;
	os << *it;
    }
    os << "}";
    HEURISTIC_DEBUG{
	std::vector<std::string> AM_NAMES={
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
	    "AM_XY_CHAIN"

	};
	first=true;
	os << " mt {";
	if(!sq.mt){
	    os << "AM_NONE";
	}else{
	    size_t tmpmt=sq.mt;
	    for(size_t ctr=0;tmpmt;ctr++){
		if(tmpmt&1){
		    if(!first){
			os << " | ";
		    }
		    os<<AM_NAMES[ctr];
		    first=false;
		}
		tmpmt>>=1;
	    }
	}
	os << "}";
    }
    os << '\n';
    return os;
}
    
enum grouptype{GT_ROW, GT_COLUMN, GT_BLOCK};
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
    sudoku_method():count(0){ SUDOKU_METHOD_DEBUG std::cerr << "sudoku_method()\n"; };
    //! Called by each of our child classes each time they successfully apply
    void
    incr_count(){count++;};
    //! Called to get the count of times our child successfully applied
    size_t
    get_count(){return count;};
    //! Called to clear the count of times our child successfully applied
    void
    clear_count(){count=0;};
    //! Our children must implement apply
    //! Our children must implement apply
    virtual
    bool
    apply()=0;
    //! Our children must each implement their own register_strategy
    virtual
    void register_strategy(board<N>*)=0;
protected:
    //! Keeps track of times our child successfully applied
    size_t count;
    //! class board calls our register_strategy passing in his address which we save here
    board<N>* b;
private:
};

/*!
 * This class registers and implements the naked single method
 * A naked single (also called forced digit and sole candidate) is a square
 * with only one possible value.  Of course it must be set to that value.
 */
template<const unsigned int N>
class naked_single:public sudoku_method<N>
{
public:
    naked_single(){
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
		square& sq=b->b[row][col];
		NAKED_SINGLE_DEBUG std::cerr << "  naked_single loop--row: " << row << ", col: " << col << ", possibilities: " << sq.size() << ", value: " << sq.get_val() << ", locked: " << sq.is_locked() << "\n";
		if(!sq.is_locked()
			&& sq.get_val()==0
			&& sq.size()==1 ){
		    RESPATH{
			std::cerr << "naked-single                    ==> "
			    << "r" << row+1 << "c" << col+1 << " = "
			    << sq[0] << ' ';
		    }
		    b->set_val(sq.get_row(),sq.get_column(),sq[0]);
		    NAKED_SINGLE_DEBUG std::cerr << "  [" << row << "][" << col << "] set value to " << sq.get_val() << '\n';
		    b->update_pvals_for_square(row,col);
		    RESPATH std::cerr << '\n';
		    sudoku_method<N>::incr_count();
		    return true;
		}
	    }
	}
	return false;
    };

    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(0,\"naked single\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(0,"naked single", this);
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
    hidden_single(){
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
			RESPATH std::cerr << "hidden-single-in-row r" << row+1 << "         ==> r" << row+1 << "c" << sq.get_column()+1 << " = " << val << ' ';
			b->set_val(row,sq.get_column(),val);
			b->update_pvals_for_square(row,sq.get_column());
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
			RESPATH std::cerr << "hidden-single-in-column c" << col+1 << "      ==> r" << sq.get_row()+1 << "c" << col+1 << " = " << val << ' ';
			b->set_val(sq.get_row(),col,val);
			b->update_pvals_for_square(sq.get_row(),col);
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
			RESPATH std::cerr << "hidden-single-in-block b" << block_num+1 << "       ==> r" << sq.get_row()+1 << "c" << sq.get_column()+1 << " = " << val << ' ';
			b->set_val(sq.get_row(),sq.get_column(),val);
			b->update_pvals_for_square(sq.get_row(),sq.get_column());
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

    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(0,\"hidden single\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(0,"hidden single", this);
    };
};

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
    naked_double(){
	NAKED_DOUBLE_DEBUG std::cerr << "naked_double()\n";
    }
    virtual
    bool
    apply(){
	NAKED_DOUBLE_DEBUG std::cerr << "naked_double.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->naked_apply(2)){
	    sudoku_method<N>::incr_count();
	    NAKED_DOUBLE_DEBUG std::cerr << "success\n";
	    return true;
	}
	return false;
    }

    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(1,\"naked double\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"naked double", this);
    };
};


/*! hidden Double - There are two numbers that only appear in two squares in a
 * 	group, although those squares may have other possibilities.  That means
 * 	that we can not only remove any other possibilities from those two 
 * 	squares, but that we can also remove those two possibilities from any
 * 	other squares in the group.
 */
template<const unsigned int N>
class hidden_double:public sudoku_method<N>
{

public:
    hidden_double(){
	HIDDEN_DOUBLE_DEBUG std::cerr << "hidden_double()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	HIDDEN_DOUBLE_DEBUG std::cerr << "hidden_double.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->hidden_apply(2)){
	    sudoku_method<N>::incr_count();
	    return true;
	}
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(1,\"hidden double\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"hidden double", this);
    };
};

/*! Naked triple - Three cells in a group each have only the same three numbers as
 * 	possibilities (although they don't have to each have all three).
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
    naked_triple(){
	NAKED_TRIPLE_DEBUG std::cerr << "naked_triple()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	NAKED_TRIPLE_DEBUG std::cerr << "naked_triple.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->naked_apply(3)){
	    sudoku_method<N>::incr_count();
	    NAKED_TRIPLE_DEBUG std::cerr << "naked triple success\n";
	    return true;
	}
	NAKED_TRIPLE_DEBUG std::cerr << "naked triple failure\n";
	return false;
    }


    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(1,\"naked triple\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"naked triple", this);
    };
};

/*! hidden triple - There are two numbers that only appear in two squares in a
 * 	group, although those squares may have other possibilities.  That means
 * 	that we can not only remove any other possibilities from those two 
 * 	squares, but that we can also remove those two possibilities from any
 * 	other squares in the group.
 */
template<const unsigned int N>
class hidden_triple:public sudoku_method<N>
{
public:
    hidden_triple(){
	HIDDEN_TRIPLE_DEBUG std::cerr << "hidden_triple()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	HIDDEN_TRIPLE_DEBUG std::cerr << "hidden_triple.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->hidden_apply(3)){
	    sudoku_method<N>::incr_count();
	    HIDDEN_TRIPLE_DEBUG std::cerr << "hidden triple success\n";
	    return true;
	}
	HIDDEN_TRIPLE_DEBUG std::cerr << "hidden triple failure\n";
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(1,\"hidden triple\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"hidden triple", this);
    };
};

/*! Naked quad - Three cells in a group each have only the same three numbers as
 * 	possibilities (although they don't have to each have all three).
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
class naked_quad:public sudoku_method<N>
{

public:
    naked_quad(){
	NAKED_QUAD_DEBUG std::cerr << "naked_quad()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	NAKED_QUAD_DEBUG std::cerr << "naked_quad.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->naked_apply(4)){
	    sudoku_method<N>::incr_count();
	    NAKED_QUAD_DEBUG std::cerr << "naked quad success\n";
	    return true;
	}
	NAKED_QUAD_DEBUG std::cerr << "naked quad failure\n";
	return false;
    }


    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(1,\"naked quad\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"naked quad", this);
    };
};

/*! hidden quad - There are two numbers that only appear in two squares in a
 * 	group, although those squares may have other possibilities.  That means
 * 	that we can not only remove any other possibilities from those two 
 * 	squares, but that we can also remove those two possibilities from any
 * 	other squares in the group.
 */
template<const unsigned int N>
class hidden_quad:public sudoku_method<N>
{
public:
    hidden_quad(){
	HIDDEN_QUAD_DEBUG std::cerr << "hidden_quad()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	HIDDEN_QUAD_DEBUG std::cerr << "hidden_quad.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	if(b->hidden_apply(4)){
	    sudoku_method<N>::incr_count();
	    HIDDEN_QUAD_DEBUG std::cerr << "hidden quad success\n";
	    return true;
	}
	HIDDEN_QUAD_DEBUG std::cerr << "hidden quad success\n";
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(1,\"hidden quad\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"hidden quad", this);
    };
};

/*! intersection - when all of the possibilities for a value in a group (a row,
 * column, or block), are also in another group, then that value can be
 * removed from the second group, for example:
 * \verbatim
 * .-------.-------.-------.
 * | * * * | * * * | X X X | X : A cell which may have the value X
 * |       |       | - - - | - : A cell which does not contain a candidate X
 * |       |       | - - - | * : Cells from which we can eliminate X
 * '-------'-------'-------'
 *    also call pointing
 * \endverbatim
 * Since the only copies of X (there can be 2 or three and it works the same
 * --conceivably there could be one copy of X but then we'd call that a hidden
 *  or naked single),
 * in the block are in the same row, then they have to occur in the row in the
 * block.  That means we KNOW that they can not occur in the same row in any
 * other block and all cells marked * can have X removed from their pvals (list
 * of possible values).
 * This works the same if the two or three are the only copy in a row or column,
 * and are also all in a block--you can remove X from the pvals of every cell
 * in the block:
 * \verbatim
 * .-------.-------.-------.
 * | - - - | - - - | X X X | X : A cell which may have the value X
 * |       |       | * * * | - : A cell which does not contain a candidate X
 * |       |       | * * * | * : Cells from which we can eliminate X
 * '-------'-------'-------'
 * also call claiming or box-line reduction
 * \verbatim
 * .-------.
 * |     - |
 * |     - |
 * |     - |
 * '-------'
 * | * * X | X : A cell which may have the value X
 * | * * X | - : A cell which does not contain a candidate X
 * | * * X | * : Cells from which we can eliminate X
 * '-------'
 * |     - |
 * |     - |
 * |     - |
 * '-------'
 * \endverbatim
 * We note that there are four types, row-box, column-box, box-row, and box-column
 * where whichever group is noted first, i.e. row, in row-box, is the one that
 * only has two or three squares with a particular value, the the one mentioned
 * second, if those squares a all in that group, can have the value removed
 * from their pvals.
 *
 */
template<const unsigned int N>
class intersection:public sudoku_method<N>
{
public:
    intersection(){
	INTERSECTION_DEBUG std::cerr << "intersection()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	INTERSECTION_DEBUG std::cerr << "intersection.apply()\n";
	board<N>* b=sudoku_method<N>::b;
	// check row, column block
	// first row
	for(size_t row=0;row<N;row++){
	    std::map<size_t,std::vector<square*>>& mvs=
		b->get_possibilities(GT_ROW,row);
	    for(size_t val=0;val<N+1;val++){
		size_t sz=mvs[val].size();
		if(sz==2 || sz==3){
		    std::vector<square*>& sqs=mvs[val]; // convenience
		    bool already_set=true;
		    for(size_t ctr=0;ctr<sqs.size();ctr++){
			if(!sqs[ctr]->check_matched_type(square::AM_ROW_BLOCK_INTERSECTION)){
			    already_set=false;
			}
		    }
		    if(!already_set){
			// a pair or triple on a row, if all in same block, can purge
			// that value from other squares in the block
			size_t bnum=b->get_block_num(sqs[0]->get_row(),sqs[0]->get_column());
			bool can_reduce=true;
			INTERSECTION_DEBUG std::cerr << "Following squares in same row have same pval: " << val << ":\n";
			INTERSECTION_DEBUG std::cerr << *sqs[0];
			for(size_t ctr=1;ctr<sz;ctr++){
			    INTERSECTION_DEBUG std::cerr << *sqs[ctr];
			    if(b->get_block_num(sqs[ctr]->get_row(),sqs[ctr]->get_column())!=bnum){
				can_reduce=false;
				break;
			    }
			}
			INTERSECTION_DEBUG std::cerr << "-\n";
			if(can_reduce){
			    INTERSECTION_DEBUG std::cerr << "row: " << row << ", block: " << bnum << " intersection\n";
			    RESPATH std::cerr << "row-block-intersection"
				<< " r" << row+1 << " b" << bnum+1;
			    b->purge_block_except(bnum, sqs,val);
			    RESPATH std::cerr << "\n";
			    for(size_t ctr=0;ctr<sz;ctr++){
				// after the purge, the block will also only have
				// 2 or three.  To avoid having it get picked up
				// again, we flag it as both
				sqs[ctr]->set_matched_type(square::AM_ROW_BLOCK_INTERSECTION);
				sqs[ctr]->set_matched_type(square::AM_BLOCK_ROW_INTERSECTION);
			    }
			    sudoku_method<N>::incr_count();
			    INTERSECTION_DEBUG std::cerr << "row v block intersection success\n";
			    return true;
			}
		    }
		}
	    }
	}
	for(size_t col=0;col<N;col++){
	    std::map<size_t,std::vector<square*>>& mvs=
		b->get_possibilities(GT_COLUMN,col);
	    for(size_t val=0;val<N+1;val++){
		size_t sz=mvs[val].size();
		if(sz==2 || sz==3){
		    std::vector<square*>& sqs=mvs[val]; // convenience
		    bool already_set=true;
		    for(size_t ctr=0;ctr<sqs.size();ctr++){
			if(!sqs[ctr]->check_matched_type(square::AM_COLUMN_BLOCK_INTERSECTION)){
			    already_set=false;
			}
		    }
		    if(!already_set){
			// a pair or triple in a column, if all in same block, can purge
			// that value from other squares in the block
			size_t bnum=b->get_block_num(sqs[0]->get_row(),sqs[0]->get_column());
			bool can_reduce=true;
			INTERSECTION_DEBUG std::cerr << "Following squares in same column have same pval: " << val << ":\n";
			INTERSECTION_DEBUG std::cerr << *sqs[0];
			for(size_t ctr=1;ctr<sz;ctr++){
			    INTERSECTION_DEBUG std::cerr << *sqs[ctr];
			    if(b->get_block_num(sqs[ctr]->get_row(),sqs[ctr]->get_column())!=bnum){
				can_reduce=false;
				break;
			    }
			}
			INTERSECTION_DEBUG std::cerr << "-\n";
			if(can_reduce){
			    INTERSECTION_DEBUG std::cerr << "col: " << col << ", block: " << bnum << " intersection\n";
			    RESPATH std::cerr << "column-block-intersection c"
				<< col+1 << " b" << bnum+1;
			    b->purge_block_except(bnum, sqs,val);
			    RESPATH std::cerr << '\n';
			    for(size_t ctr=0;ctr<sz;ctr++){
				// after the purge, the block will also only have
				// 2 or three.  To avoid having it get picked up
				// again, we flag it as both
				sqs[ctr]->set_matched_type(square::AM_COLUMN_BLOCK_INTERSECTION);
				sqs[ctr]->set_matched_type(square::AM_BLOCK_COLUMN_INTERSECTION);
			    }
			    sudoku_method<N>::incr_count();
			    INTERSECTION_DEBUG std::cerr << "column v block intersection success\n";
			    return true;
			}
		    }
		}
	    }
	}
	for(size_t block=0;block<N;block++){
	    std::map<size_t,std::vector<square*>>& mvs=
		b->get_possibilities(GT_BLOCK,block);
	    for(size_t val=0;val<N+1;val++){
		size_t sz=mvs[val].size();
		if(sz==2 || sz==3){
		    std::vector<square*>& sqs=mvs[val]; // convenience
		    bool already_set=true;
		    for(size_t ctr=0;ctr<sqs.size();ctr++){
			if(!sqs[ctr]->check_matched_type(square::AM_BLOCK_ROW_INTERSECTION)){
			    already_set=false;
			}
		    }
		    if(!already_set){
			// a pair or triple in a block, if all in same row, can purge
			// that value from other squares in the row
			size_t row=sqs[0]->get_row();
			bool can_reduce=true;
			INTERSECTION_DEBUG std::cerr << "Following squares in same block have same pval: " << val << ":\n";
			INTERSECTION_DEBUG std::cerr << *sqs[0];
			for(size_t ctr=1;ctr<sz;ctr++){
			    INTERSECTION_DEBUG std::cerr << *sqs[ctr];
			    if(sqs[ctr]->get_row()!=row){
				can_reduce=false;
				break;
			    }
			}
			INTERSECTION_DEBUG std::cerr << "-\n";
			if(can_reduce){
			    RESPATH{
				std::cerr << "block b" << block+1 << 
				    " row r" << row+1 << " intersection";
				std::cerr << " n" << val << "{";
				bool first_time=true;
				for(size_t ctr=0;ctr<sz;ctr++){
				    if(!first_time){
					std::cerr << ' ';
				    }
				    first_time=false;
				    std::cerr << "r" << sqs[ctr]->get_row()+1
					<< "c" << sqs[ctr]->get_column()+1;
				}
				std::cerr << '}';
			    }

			    b->purge_row_except(row,sqs,val);
			    RESPATH std::cerr << "\n";
			    for(size_t ctr=0;ctr<sz;ctr++){
				// after the purge, the row will also only have
				// 2 or three.  To avoid having it get picked up
				// again, we flag it as both
				sqs[ctr]->set_matched_type(square::AM_BLOCK_ROW_INTERSECTION);
				sqs[ctr]->set_matched_type(square::AM_ROW_BLOCK_INTERSECTION);
			    }
			    sudoku_method<N>::incr_count();
			    INTERSECTION_DEBUG std::cerr << "block v row intersection success\n";
			    return true;
			}
		    }
		}
	    }
	}
	for(size_t block=0;block<N;block++){
	    std::map<size_t,std::vector<square*>>& mvs=
		b->get_possibilities(GT_BLOCK,block);
	    for(size_t val=0;val<N+1;val++){
		size_t sz=mvs[val].size();
		std::vector<square*>& sqs=mvs[val]; // convenience
		bool already_set=true;
		for(size_t ctr=0;ctr<sqs.size();ctr++){
		    if(!sqs[ctr]->check_matched_type(square::AM_BLOCK_COLUMN_INTERSECTION)){
			already_set=false;
		    }
		}
		if((sz==2 || sz==3) && !already_set){
		    // a pair or triple in a block, if all in same column, can purge
		    // that value from other squares in the column
		    size_t col=sqs[0]->get_column();
		    bool can_reduce=true;
		    INTERSECTION_DEBUG std::cerr << "Following squares have same val: " << val << ":\n";
		    INTERSECTION_DEBUG std::cerr << *sqs[0];
		    for(size_t ctr=1;ctr<sz;ctr++){
			INTERSECTION_DEBUG std::cerr << *sqs[ctr];
			if(sqs[ctr]->get_column()!=col){
			    can_reduce=false;
			    break;
			}
		    }
		    INTERSECTION_DEBUG std::cerr << "-\n";
		    if(can_reduce){
			RESPATH{
			    std::cerr << "block-column-intersection";
			    std::cerr << " b" << block+1;
			    std::cerr << " c" << col+1;
			    std::cerr << " n" << val << "{";
			    bool first_time=true;
			    for(size_t ctr=0;ctr<sz;ctr++){
				if(!first_time){
				    std::cerr << ' ';
				}
				first_time=false;
				std::cerr << "r" << sqs[ctr]->get_row()+1
				    << "c" << sqs[ctr]->get_column()+1;
			    }
			    std::cerr << '}';
			}
			b->purge_column_except(col,sqs,val);
			RESPATH std::cerr << "\n";
			for(size_t ctr=0;ctr<sz;ctr++){
			    // after the purge, the column will also only have
			    // 2 or three.  To avoid having it get picked up
			    // again, we flag it as both
			    sqs[ctr]->set_matched_type(square::AM_BLOCK_COLUMN_INTERSECTION);
			    sqs[ctr]->set_matched_type(square::AM_COLUMN_BLOCK_INTERSECTION);
			}
			sudoku_method<N>::incr_count();
			INTERSECTION_DEBUG std::cerr << "block v column intersection success\n";
			return true;
		    }
		}
	    }
	}

	INTERSECTION_DEBUG std::cerr << "intersection failure\n";
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(1,\"intersection\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"intersection", this);
    };
};

/*! x-wing looks for interlocking pairs of rows and columns each containing the
 * same pair of possibilities.  It calls interlock_apply() to do the work, which
 * treats x-wing as a member of the class of interlock algorithms like swordfish
 * and jellyfish
 */
template<const unsigned int N>
class x_wing:public sudoku_method<N>
{
public:
    x_wing(){
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
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(2,\"x-wing\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"x-wing", this);
    };
};

/*! The y-wing class implements the algorithm to search for three cells each 
 * with 2 members of their pvals, but between them only three pvals.  One of
 * the cells is the pivot and shares a member of pvals with each of the other
 * two.  They in turn, share a third pval.  For example, the three squares,
 * (with the pivot in the middle) could have pvals {1,3} {3,7} {1,7}.  
 * The first has to be in a group with the second, and the second in a group
 * with the third (row, column or block is a group), but all three can't be in
 * the same group.  If all that is true, then in the intersection of squares
 * visible from the first and the third, we can remove their shared value (in
 * the example, the 1) from all the square's pvals.
 */
template<const unsigned int N>
class y_wing:public sudoku_method<N>
{
public:
    y_wing(){
	Y_WING_DEBUG std::cerr << "y_wing()\n";
    }
    //! Called by block<N>::heuristic_solution 
    virtual
    bool
    apply(){
	Y_WING_DEBUG std::cerr << "y_wing.apply()\n";
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
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(2,\"y-wing\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"y-wing", this);
    };
};

/*! 
 * The solution class swordfish, like x-wing, calls interlock_apply() to do
 * the dirty work.  The only difference is that x-wings have interlocking
 * pairs of column and rows with the same pairs of possibilities, and
 * swordfish has interlocking triples of everything, etc...
 */
template<const unsigned int N>
class swordfish:public sudoku_method<N>
{
public:
    swordfish(){
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
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(2,\"swordfish\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"swordfish", this);
    };
};

/*! 
 * The solution class jellyfish, like x-wing, and swordfish, calls
 * interlock_apply() to do the dirty work.  The only difference is that x-wings
 * have interlocking pairs of column and rows with the same pairs of
 * possibilities, swordfish have interlocking triples of everything, and
 * jellyfish have interlocking quads of everything.
 */
template<const unsigned int N>
class jellyfish:public sudoku_method<N>
{
public:
    jellyfish(){
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
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(2,\"jellyfish\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"jellyfish", this);
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
 * if at any point a square asserts ownership of the same value as
 * the original square, and they can see each other, then a proof by
 * contradiction has occured that the first square must use the other pval,
 * in this case 3.
 */
template<const unsigned int N>
class xy_chain:public sudoku_method<N>
{
public:
    xy_chain(){
	XY_CHAIN_DEBUG std::cerr << "xy_chain() constructed\n";
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
		for(size_t c=0;c<2;c++){
		    square &sq=b->b[row][col];
		    if(sq.size()==2){
			// yay, found the head of a chain.
			// owned will be 0 and then 1
			sq.set_owned(c);
			chain.push_back(&sq);
			if(b->xy_chain_apply(chain)){
			    // yay, found one!
			    sudoku_method<N>::incr_count();
			    XY_CHAIN_DEBUG std::cerr << "success\n";
			    XY_CHAIN_DEBUG b->print_large();
			    return true;
			}
			chain.pop_back();
		    }
		}
	    }
	}
	XY_CHAIN_DEBUG std::cerr << "failed\n";
	return false;
    }

    //! Called by block to pass in a pointer to board and have class call back to register
    virtual
    void register_strategy(board<N>* b)
    {
	REGISTER_STRATEGY_DEBUG std::cerr << "register_strategy(2,\"xy-chain\")\n";
	sudoku_method<N>::b=b;
	b->register_strategy(1,"xy-chain", this);
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
    	ST_ROT90=16,ST_ROT180=32,ST_ROT270=64,ST_MDIAG=128,ST_ADIAG=256,ST_MADIAG=512};
    std::vector<std::string> symtype_st={"ST_NONE","ST_HORIZ","ST_VERT","ST_HV","ST_ROT","ST_ROT90","ST_ROT180","ST_ROT270","ST_MDIAG","ST_ADIAG","ST_MADIAG"};
    friend naked_single<N>;//!<friend for direct access to board
    friend hidden_single<N>;//!<friend for direct access to board
    friend naked_double<N>;//!<friend for direct access to board
    friend hidden_double<N>;//!<friend for direct access to board
    friend naked_triple<N>;//!<friend for direct access to board
    friend hidden_triple<N>;//!<friend for direct access to board
    friend naked_quad<N>;//!<friend for direct access to board
    friend xy_chain<N>;//!<friend for direct access to board
    template<const unsigned int>
    friend
    std::ostream& operator<<(std::ostream&,symtype);
    board(); //!< default constructor
    board(std::string);//!<constructor which takes list of values and blanks
    board(const board&); //!< copy constructor
    board(std::vector<square>); //!< constructor which takes vectors of squares
    board&
    operator=(const board&); //!< assignment operator
    void
    print(); //!< print to std::cerr a simple representation of the board
    void
    print_large(); //!< print to std::cerr the values and pvals
    void
    print_just_pvals(); //!< print to std::cerr the values and pvals
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
    bool
    generate(); //!< create a complete board with all squares set
    void
    inline
    dig_one(size_t row,size_t col, board& brd, symtype st);
    bool
    dig_puzzle(symtype,size_t,bool);
    //! generate possible values for one square at row and col
    void
    generate_pvals(unsigned int row, unsigned int col,bool);
    //! update data structure which keeps track of maps of values to squares
    void
    update_possibilities();
    //! Update all the pvals on the board
    void
    update_pvals();
    //! For 2 squares remove a pval from their shared neighbors
    bool
    update_pval_for_squares(square& sq1,square& sq2, size_t val);
    //! When a square has been set, all squares which can see that square have
    //! the square's val removed form their pvals
    void
    update_pvals_for_square(size_t row, size_t col);
    //! remove set values in square's column from pvals
    void
    prune_column_pvals(unsigned int row, unsigned int col,std::vector<unsigned int> &sq,bool);
    //! remove set values in square's row from pvals
    void
    prune_row_pvals(unsigned int row, unsigned int col,std::vector<unsigned int> &sq,bool);
    //! remove set values in square's block from pvals
    void
    prune_block_pvals(unsigned int row, unsigned int col,std::vector<unsigned int> &sq,bool);
    //! Check if square at row and col has pvals equal to input set pvs
    bool
    check_pval_set(size_t row,size_t col,std::set<size_t>pvs){
	return b[row][col].check_pval_set(pvs);
    };
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
    bool
    brute_force_solution();
    //! solve the puzzle using a brute force solution with back up and try alternatives.
    size_t
    brute_force_check(bool);
    //! solve the puzzle by trying the same things a person would do
    bool
    heuristic_solution(bool);
    //! return number of set squares
    size_t
    count();
    //! return the number of times we have set squares
    size_t
    get_count();
    //! return number of times we've backed up in brute force
    size_t get_backed_count(){ return backed_count; }
    //! call register_strategies on all solution classes
    void
    register_strategies();
    //! call back method called by each solution class
    void
    register_strategy(size_t level,std::string name,sudoku_method<N>*);
    //! how many time strategies of a particular level have been applied
    size_t
    get_strategy_counts(size_t level);
    //! make all strategy counts 0
    void
    clear_strategy_counts();
    //! how many time a particular strategy has been applied
    size_t
    get_strategy_count(std::string);
    //! returns true if squares share block, column, or row
    bool
    can_see(const square& sq1,const square& sq2){
	if((get_block_num(sq1)==get_block_num(sq2)
		    || sq1.get_row()==sq2.get_row()
		    || sq1.get_column()==sq2.get_column())){
	    return true;
	}
	return false;
    }
    //! given a row and column number return a block number 0-8
    size_t
    get_block_num(size_t row, size_t col){ return root*(row/root)+col/root; };
    size_t
    get_block_num(const square&sq){ return get_block_num(sq.get_row(),sq.get_column());};
    //! helper routine called by all hidden_XXX strategies except for hidden single via hidden_apply
    bool
#if defined(SHOW_RESPATH)
    discern_hidden(size_t, std::map<size_t,std::vector<square*>>&,grouptype);
#else
    discern_hidden(size_t, std::map<size_t,std::vector<square*>>&);
#endif
    //! helper routine called by all naked_XXX strategies except for naked single via naked_apply
    bool
#if defined(SHOW_RESPATH)
    discern_naked(size_t, std::vector<square*>,grouptype);
#else
    discern_naked(size_t, std::vector<square*>);
#endif

	//if(discern_naked(level, get_squares(GT_ROW,row))){
    //! helper routine called by x-wing, swordfish, and jellyfish via interlock apply
    bool
    discern_interlock(size_t, grouptype);
    //! calls discern_hidden() for each row, column, and block as appropriate until one succeeds or all fail
    bool
    hidden_apply(size_t level);
    //! calls discern_naked() for each row, column, and block as appropriate until one succeeds or all fail
    bool
    naked_apply(size_t level);
    //! calls discern_interlock twice, once for rows, once for columns as appropriate
    bool
    interlock_apply(size_t level);
    //! xy_chain_apply
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
    get_neighbors(square* sq,bool (square::*)(square*),bool);
    operator std::string();
    
private:
    //! Wrapper around square::clear_pval_val(val) that also keeps possibilities in sync
    bool
    clear_pval_val(size_t row,size_t col,size_t val);
    //! Wrapper around square::set_val(val,set_pval) which keeps count in sync
    void
    set_val(size_t row,size_t col,size_t val,bool set_pval);
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
    //! all the solution strategies used by heurist_solution mapped by level
    std::map<size_t, std::map<std::string, class sudoku_method<N>*>> strategies;
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
    //! Routine called by our constructors to do common initialization
    void init();
    //! map of vals to map of rows to vector of squares in each row with val in pvals
    std::map<size_t,std::map<size_t,std::vector<square*>>> row_possibilities;
    //! map of vals to map of columns to vector of squares in each column with val in pvals
    std::map<size_t,std::map<size_t,std::vector<square*>>> column_possibilities;
    //! map of vals to map of blocks to vector of squares in each block with val in pvals
    std::map<size_t,std::map<size_t,std::vector<square*>>> block_possibilities;
    //! Count of squares that have been set
    size_t set_squares;
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
 * From a given square find all the other squares in the same row, column,
 * or block, and pass them each in turn to the fn argument for vetting.  If
 * the function returns true, then add them to a std::set<square *>.  When
 * done, return the set.
 * \param sq a pointer to the square whose neighbors will be inspected and
 * 	potentially returned in the set
 * \param fn a pointer to a square member method that takes a pointer to a
 *      square and returns a bool
 * \return std::set<square*> all the neighbors of sq that caused fn to return
 *      true
 */
template<const unsigned int N>
std::set<square*>
board<N>::get_neighbors(square* sq,bool (square::*fn)(square*)=&square::true_filt,bool not_self=true)
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
 * return a representation of the board as a string with each character
 * representing a square of the board with values '1'-'9' to represent set
 * cells, and '0' to represent an unset cell.  The order, left to right is
 * r0c0-8 then r1c0-8, etc...
 */
template<const unsigned int N>
board<N>::operator std::string()
{
    std::string retval="";
    for(size_t ctr=0;ctr<N*N;ctr++){
	size_t row=ctr/N, col=ctr%N;
	retval+='0'+b[row][col].get_val();
    }
    return retval;
}

template<const unsigned int N>
void
board<N>::register_strategies(void)
{
    hs.register_strategy(this);
    ns.register_strategy(this);
    nd.register_strategy(this);
    hd.register_strategy(this);
    nt.register_strategy(this);
    ht.register_strategy(this);
    nq.register_strategy(this);
    hq.register_strategy(this);
    intr.register_strategy(this);
    xw.register_strategy(this);
    yw.register_strategy(this);
    sf.register_strategy(this);
    jf.register_strategy(this);
    cpc.register_strategy(this);
}

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
board<N>::get_squares(grouptype what,size_t which)
{
    std::vector<square*> retval;
    switch(what){
	case GT_ROW:
	    for(size_t col=0;col<N;col++){
		retval.push_back(&b[which][col]);
	    }
	    break;
	case GT_COLUMN:
	    for(size_t row=0;row<N;row++){
		retval.push_back(&b[row][which]);
	    }
	    break;
	case GT_BLOCK:
	    size_t row_min=root*(which/root),
		   row_max=row_min+root,
		   col_min=root*(which%root),
		   col_max=col_min+root;
	    for(size_t row=row_min;row<row_max;row++){
		for(size_t col=col_min;col<col_max;col++){
		    retval.push_back(&b[row][col]);
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
 * \param possibilities from some particular row, column, or block, this is a map of pval values, 1-N to vectors of pointers to squares in that row, column or block that contain that number in their pvals.
 * \return bool true if we found what we were looking for and as a result made some change in some square's pvals.  If we find a hidden whatever, but no pval values get cleared, or if we don't find a hidden whatever, we return false.
 *
 */
template<const unsigned int N>
bool
#if defined(RESPATH)
board<N>::discern_hidden(size_t depth, std::map<size_t,std::vector<square*>>& possibilities,grouptype gt)
#else
board<N>::discern_hidden(size_t depth, std::map<size_t,std::vector<square*>>& possibilities)
#endif
{
    // at this point we should have pointers to all the squares with the value
    // 1 in their list of possible values in a vector mapped to 1 etc.  This
    // information is for only one row, one column, or one block
    std::vector<size_t> vals; // walks through all vals 1-N
    std::vector<size_t> sizes;
    std::vector<std::set<square*>> sets;
    // next we reserve space for the data that will be in the various vectors
    // so that we can assign like: vals[2]=  without crashing.
    vals.resize(depth);
    sets.resize(depth);
    sizes.resize(depth);

    std::map<size_t,square::matched_type> matched_map={
	{2,square::AM_HIDDEN_DOUBLE},
	{3,square::AM_HIDDEN_TRIPLE},
	{4,square::AM_HIDDEN_QUAD}
    };

    DISCERN_HIDDEN_DEBUG std::cerr << "DISCERN_HIDDEN--depth: " << depth << "\n";
    size_t d=0;
    vals[0]=1;
    while(true){
	DISCERN_HIDDEN_DEBUG std::cerr << "TOP OF LOOP--d: " << d << ", val: " << vals[d] << "\n";

	// vals[d] will count from 1-N, so to start, the next line will get a
	// vector of pointers to all squares with a 1 in their pvals
	std::vector<square *>& vs=possibilities[vals[d]];  // convenience
	sizes[d]=vs.size();	// how many squares have that val

	DISCERN_HIDDEN_DEBUG std::cerr << "  possibilities[" << vals[d] << "].size(): " << sizes[d] << "\n";

	if(sizes[d]>=2 && sizes[d]<=depth){
	    // if 2 to N squares have this value in their pvals
	    DISCERN_HIDDEN_DEBUG std::cerr << "found a candidate\n";
	    		
	    if(d>0){
		// remember the squares from the previous level if any
		sets[d]=sets[d-1];
	    }
	    for(size_t ctr=0;ctr<sizes[d];ctr++){
		// add to it the squares from this level in the hopes that
		// when we get to the ultimate depth, we will have found a
		// group of size depth of squares.
		sets[d].insert(possibilities[vals[d]][ctr]);
		DISCERN_HIDDEN_DEBUG std::cerr << "adding sq: " << *possibilities[vals[d]][ctr] << " to sets[" << d << "]\n";
	    }
	    DISCERN_HIDDEN_DEBUG std::cerr << "size of sets[" << d << "]: " << sets[d].size() << "\n";
	    if(d==depth-1){
		// d==depth-1 is our maximum depth, i.e. if depth is four, we
		// go through d=0, d=1, d=2, d=3
		DISCERN_HIDDEN_DEBUG std::cerr << "d==depth-1\n";
		DISCERN_HIDDEN_DEBUG std::cerr << "sets[d].size(): " << sets[d].size() << '\n';
		if(sets[d].size()==depth){ 
		    // if depth is four and we found four squares, might be it!
		    DISCERN_HIDDEN_DEBUG std::cerr << "d: " << d << ", maybe found?\n";
		    bool already_found=true;
		    bool found_hidden=false;
		    std::set<square*>::iterator it;
		    std::set<size_t> valset;
		    // check to see if all of the squares are already marked
		    // as hidden double or triple or quad as appropriate.  If
		    // so, we'll not consider this a win.
		    for(it=sets[d].begin();it!=sets[d].end();it++){
			DISCERN_HIDDEN_DEBUG std::cerr << " checking square against matched_map[" << d << "]: " << (*it)->mt2string(matched_map[depth]) << "--" << **it << '\n';
			if(!(*it)->check_matched_type(matched_map[depth])){
			    already_found=false;
			}
		    }
		    if(!already_found){
			// maybe found hidden.  Check to see if at least one square
			// has any val in pval other than the ones our vals.
			DISCERN_HIDDEN_DEBUG std::cerr << "valset={";

			for(size_t vc=0;vc<depth;vc++){
			    // vals[0] is the val for which we found 2-depth-1
			    // squares, vals[1] is another, etc...
			    valset.insert(vals[vc]);
			    DISCERN_HIDDEN_DEBUG std::cerr << vals[vc] << ",";
			}
			// Now we've got a list of the vals for which at each
			// depth, we've found 2-depth-1 squares with that val
			DISCERN_HIDDEN_DEBUG std::cerr << "}\n";

			for(it=sets[d].begin();it!=sets[d].end();it++){
			    for(size_t ctr=0;ctr<(*it)->size();ctr++){
				DISCERN_HIDDEN_DEBUG std::cerr << "checking for (*it)[ctr]: " << (**it)[ctr] << " in valset\n";
				if(std::find(valset.begin(),valset.end(),(**it)[ctr])==valset.end()){
				    DISCERN_HIDDEN_DEBUG std::cerr << "found an element not in the set of vals, so setting found_hidden true.\n";
				    found_hidden=true;
				    break;
				}
			    }
			    if(found_hidden){
				break;
			    }
			}
		    }
		    if(found_hidden && !already_found){

			DISCERN_HIDDEN_DEBUG std::cerr << "found a hidden " << depth << "\n";
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
			    std::cerr << "-in-a-";
			    switch(gt){
				case GT_ROW:
				    std::cerr << "row";
				    break;
				case GT_COLUMN:
				    std::cerr << "column";
				    break;
				case GT_BLOCK:
				    std::cerr << "block";
				    break;
			    }
			    std::cerr << " {";
			    std::set<size_t>::iterator it;
			    bool first_time=true;
			    for(it=valset.begin();it!=valset.end();it++){
				if(!first_time){
				    std::cerr << ' ';
				}
				first_time=false;
				std::cerr << "n" << *it;
			    }
			    std::cerr << "}";
			    std::set<square *>::iterator sit;
			    switch(gt){
				case GT_ROW:
				    std::cerr << "r" << (*(sets[d].begin()))->get_row()+1;
				    std::cerr << "{";
				    first_time=true;
				    for(sit=sets[d].begin();sit!=sets[d].end();sit++){
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
				    for(sit=sets[d].begin();sit!=sets[d].end();sit++){
					if(!first_time){
					    std::cerr << ' ';
					}
					std::cout << "r" << (*sit)->get_row()+1;
				    }
				    std::cerr << "}c" << (*(sets[d].begin()))->get_column()+1;
				    break;
				case GT_BLOCK:
				    std::cerr << "{";
				    first_time=true;
				    for(sit=sets[d].begin();sit!=sets[d].end();sit++){
					if(!first_time){
					    std::cerr << ' ';
					}
					first_time=false;
					std::cerr << "r" << (*sit)->get_row()+1 << "c" << (*sit)->get_column()+1;
				    }
				    std::cerr << "}";
			    }
			}
			// get rid of any thing not in set of vals, i.e. turns
			// a hidden triple to a naked triple.
			reduce_to_set(sets[d],valset);
			RESPATH std::cerr << '\n';
			// you'd think that this next call, to purge_from_set
			// which will get rid of the vals in the hidden N from
			// the appropriate row, column, and block, would be
			// unneccessary, since hidden, means nothing else in
			// the group has any of those.  The reason it is still
			// required is that squares can be a hidden group in a
			// row, but not in their block, yet, once recognized as
			// a hidden group, and reduced to a naked N, then we
			// can use them to purge their shared vals from any
			// other group they share.  So, they might be the only
			// squares in a row with 3 and 7 for example, but if
			// they are also in the same block, we can purge 3 and
			// 7 from any other squares in the block.  The same 
			// applies also if they are hidden in a block, if they
			// are colinear in a row or column, we can purge there.
			//purge_from_set(sets[d], valset);
			for(it=sets[d].begin();it!=sets[d].end();it++){
			    // After being purged they change from a hidden to
			    // a naked so we set both so we don't find them as
			    // either since the work is already done.
			    switch(depth){
				case 2:
				    //(*it)->set_matched_type(square::AM_NAKED_DOUBLE);
				    (*it)->set_matched_type(square::AM_HIDDEN_DOUBLE);
				    break;
				case 3:
				    //(*it)->set_matched_type(square::AM_NAKED_TRIPLE);
				    (*it)->set_matched_type(square::AM_HIDDEN_TRIPLE);
				    break;
				case 4:
				    //(*it)->set_matched_type(square::AM_NAKED_QUAD);
				    (*it)->set_matched_type(square::AM_HIDDEN_QUAD);
				    break;
			    }
			}
			return true;
		    }else{
			DISCERN_HIDDEN_DEBUG std::cerr << " nope!  None had more than d pvals so they weren't hidden\n";
		    }
		}else{
		    DISCERN_HIDDEN_DEBUG std::cerr << "sets[d].size()!=depth (squares didn't match up, so sets[d].size() is " << sets[d].size() << ")\n";
		}
	    }else{ // if(d==depth-1){}
		DISCERN_HIDDEN_DEBUG std::cerr << "d!=depth-1\n";
		// we aren't at max depth, so we set up for the next depth
		DISCERN_HIDDEN_DEBUG std::cerr << "bumping up d because it is not depth-1, but rather: " << d << "\n";

		++d;
		vals[d]=vals[d-1]; // start our loop counter at the next val
		if(d==depth){
		    // didn't find it
		    return false;
		}
	    }// if(d==depth-1){} else{}
	} // if(sizes[d]>=2 && sizes[d]<=depth){} 
	while(++vals[d]==(N+1)){ // bump up vals and if done deal with it
	    DISCERN_HIDDEN_DEBUG std::cerr << "end of val loop for d==" << d << ", vals[d]: " << vals[d] << '\n';
	    if(d==0){
		DISCERN_HIDDEN_DEBUG std::cerr << "returning false\n";
		return false;
	    }else{
		d--;
		sets[d].clear();
		DISCERN_HIDDEN_DEBUG std::cerr << "backing up to level: " << d << "\n";
	    }
	}
    } // while(true)
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
 * \param sqs a vector of all the squares in a particular row, column, or block
 */
template<const unsigned int N>
bool
#if defined(SHOW_RESPATH)
board<N>::discern_naked(size_t depth, std::vector<square*> sqs,grouptype gt)
#else
board<N>::discern_naked(size_t depth, std::vector<square*> sqs)
#endif
{
    // at this point we should have pointers to all the squares with the value
    // 1 in their list of possible values in a vector mapped to 1 etc.
    std::vector<size_t> ctrs;
    std::vector<size_t> sizes;
    std::vector<std::set<size_t>> sets;
    ctrs.resize(depth);
    sets.resize(depth);
    sizes.resize(depth);
    std::map<size_t,square::matched_type> matched_map={
	{2,square::AM_NAKED_DOUBLE},
	{3,square::AM_NAKED_TRIPLE},
	{4,square::AM_NAKED_QUAD}
    };
    
    DISCERN_NAKED_DEBUG std::cerr << "DISCERN_NAKED--depth: " << depth << "\n";
    size_t d=0;
    ctrs[0]=0;
    while(true){
	DISCERN_NAKED_DEBUG std::cerr << "TOP OF LOOP--d: " << d << ", ctrs[d]: " << ctrs[d] << "\n";

	size_t sz=sqs[ctrs[d]]->size(); // size() returns #pvals in a square
	bool already_set=true;
	for(size_t chk=0;chk<=d;chk++){
	    // we check that all of the squares have AM_NAKED_DOUBLE or
	    // TRIPLE or QUAD set because one might be involved with other
	    // squares in a different group.  If all are set it's much more
	    // likely that we're looking at the same thing over again.
	    if(!sqs[ctrs[chk]]->check_matched_type(matched_map[depth])){
		already_set=false;
	    }
	}

	if(!already_set && sz>=2 && sz<=depth){
	    DISCERN_NAKED_DEBUG std::cerr << "found a candidate\n";
	    DISCERN_NAKED_DEBUG std::cerr << *sqs[ctrs[d]];
	    sets[d].clear();
	    if(d>0){
		sets[d]=sets[d-1];
	    }
	    for(size_t ctr=0;ctr<sz;ctr++){
		sets[d].insert((*sqs[ctrs[d]])[ctr]);
		DISCERN_NAKED_DEBUG std::cerr << "adding val: " << (*sqs[ctrs[d]])[ctr] << " to sets[" << d << "]\n";
	    }
	    DISCERN_NAKED_DEBUG std::cerr << "size of sets[" << d << "]: " << sets[d].size() << "\n";
	    if(d==depth-1){
		DISCERN_NAKED_DEBUG std::cerr << "d==depth-1\n";
		if(sets[d].size()==depth){ 
		    // found naked.
		    // make the set of square *s we'll use for purge_from_set()
		    // and to mark the squares as being already used for
		    // NAKED N
		    std::set<square*> sq_set;
		    for(size_t ctr=0;ctr<depth;ctr++){
			sq_set.insert(sqs[ctrs[ctr]]);
		    }

		    DISCERN_NAKED_DEBUG std::cerr << "found a naked " << depth << "\n";
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
			std::cerr << "-in-a-";
			switch(gt){
			    case GT_ROW:
				std::cerr << "row";
				break;
			    case GT_COLUMN:
				std::cerr << "column";
				break;
			    case GT_BLOCK:
				std::cerr << "block";
				break;
			}
			std::cerr << " {";
			std::set<size_t>::iterator it;
			bool first_time=true;
			for(it=sets[d].begin();it!=sets[d].end();it++){
			    if(!first_time){
				std::cerr << ' ';
			    }
			    first_time=false;
			    std::cerr << "n" << *it;
			}
			std::cerr << "}";
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
			std::cerr << " ==>";
		    }
		    bool did_something=purge_from_set(sq_set, sets[d]);
		    RESPATH std::cerr << "\n";
		    std::set<square*>::iterator it;
		    for(it=sq_set.begin();it!=sq_set.end();it++){
			switch(depth){
			    case 2:
				(*it)->set_matched_type(square::AM_NAKED_DOUBLE);
				break;
			    case 3:
				(*it)->set_matched_type(square::AM_NAKED_TRIPLE);
				break;
			    case 4:
				(*it)->set_matched_type(square::AM_NAKED_QUAD);
				break;
			}
		    }
		    return did_something;
		}
	    }else{
		DISCERN_NAKED_DEBUG std::cerr << "d!=depth-1\n";
		// we aren't at max depth, so we set up for the next depth
		DISCERN_NAKED_DEBUG std::cerr << "bumping up d because it is not depth-1, but rather: " << d << "\n";

		++d;
		ctrs[d]=ctrs[d-1];
		if(d==depth){
		    return false;
		}
	    }
	}else{
	    DISCERN_NAKED_DEBUG std::cerr << "square not a candidate: check_matched_type: " << sqs[ctrs[d]]->check_matched_type(matched_map[depth]) << ", size of pvals: " << sz << '\n';
	}
	while(++ctrs[d]==N){ // bump up vals and if done deal with it
	    DISCERN_NAKED_DEBUG std::cerr << "end of val loop for d==" << d << '\n';
	    if(d==0){
		DISCERN_NAKED_DEBUG std::cerr << "returning false\n";
		return false;
	    }else{
		d--;
		sets[d].clear();
		DISCERN_NAKED_DEBUG std::cerr << "backing up a level\n";
	    }
	}
    }
    return false;
}

template<const unsigned int N>
bool
board<N>::discern_interlock(size_t depth,grouptype which)
{
    // depth is two for x-wing, three for swordfish, etc.
    // which is either GT_ROW or GT_COLUMN, the two group types this applies to
    //
    std::vector<size_t> rows;
    std::vector<size_t> cols;
    std::vector<std::set<size_t>> colsets;
    std::vector<std::set<size_t>> rowsets;
    //std::vector<std::map<size_t,std::vector<square*>>> mvss;
    std::vector<std::vector<square*>> mvss;
    rows.resize(depth);
    cols.resize(depth);
    colsets.resize(depth);
    rowsets.resize(depth);
    mvss.resize(depth);
    std::map<size_t,square::matched_type> flags{
	{2,square::AM_X_WING},
	{3,square::AM_SWORDFISH},
	{4,square::AM_JELLYFISH}
    };

    // what I want
    // for a given depth, if a candidate is found, and we aren't at max depth
    // go to a deeper depth.  If a interlock-N is not found, we will return to 
    // our depth, and continue.
    DISCERN_INTERLOCK_DEBUG std::cerr << "DISCERN_INTERLOCK--depth: " << depth << "\n";

    size_t d=0;
    rows[0]=0;
    cols[0]=0;

    for(size_t val=1;val<N+1;val++){
	d=0;
	rows[d]=0;
	bool continueon=true;
	while(continueon){
	    DISCERN_INTERLOCK_DEBUG{
		if(which==GT_ROW){
		    std::cerr << "TOP OF LOOP--d: " << d << ", rows[d]: " << rows[d] << ", val: " << val << "\n";
		}else{
		    std::cerr << "TOP OF LOOP--d: " << d << ", cols[d]: " << cols[d] << ", val: " << val << "\n";
		}
	    }
	    if(which==GT_ROW){
		mvss[d]=get_possibilities(GT_ROW,rows[d])[val];
	    }else{
		mvss[d]=get_possibilities(GT_COLUMN,cols[d])[val];
	    }
	    size_t the_size=mvss[d].size();
	    bool already_set=true;
	    if(the_size){
		for(size_t ctr=0;ctr<the_size;ctr++){
		    if(!mvss[d][ctr]->check_matched_type(flags[depth])){
			already_set=false;
		    }
		}
	    }
	    if(the_size>=2 && the_size<=depth && !already_set){
		DISCERN_INTERLOCK_DEBUG std::cerr << "2 < size < " << depth << '\n';
		DISCERN_INTERLOCK_DEBUG{
		    if(which==GT_ROW){
			std::cerr << "Got possibilities for row " << rows[d] << " and val " << val << "\n";
		    }else{
			std::cerr << "Got possibilities for col " << cols[d] << " and val " << val << "\n";
		    }
		    for(size_t ctr=0;ctr<mvss[d].size();ctr++){
			std::cerr << " " << *(mvss[d][ctr]);
		    }
		}
		size_t setsize;
		if(which==GT_ROW){
		    if(d>0){
			colsets[d]=colsets[d-1];
		    }
		    for(size_t ctr=0;ctr<mvss[d].size();ctr++){
			colsets[d].insert(mvss[d][ctr]->get_column());
		    }
		    setsize=colsets.size();
		}else{
		    if(d>0){
			rowsets[d]=rowsets[d-1];
		    }
		    for(size_t ctr=0;ctr<mvss[d].size();ctr++){
			rowsets[d].insert(mvss[d][ctr]->get_row());
		    }
		    setsize=rowsets.size();
		}
		if(setsize<=depth){
		    DISCERN_INTERLOCK_DEBUG std::cerr << "row/colsets.size() <=depth (" << setsize << ")\n";
		    if(d==depth-1){
			DISCERN_INTERLOCK_DEBUG std::cerr << "d==depth-1, so check for final win!!!\n";
			std::set<size_t> rowset;
			std::set<size_t> colset;
			for(size_t adepth=0;adepth<depth;adepth++){
			    for(size_t ctr=0;ctr<mvss[adepth].size();ctr++){
				rowset.insert(mvss[adepth][ctr]->get_row());
				colset.insert(mvss[adepth][ctr]->get_column());
			    }
			}
			if(rowset.size()==depth && colset.size()==depth){
			    bool did_something=false;
			    DISCERN_INTERLOCK_DEBUG std::cerr << "row/colsets.size()==depth so we have found our interlock of depth " << depth << '\n';
			    // found it!!!
			    // mark mvss[0-depth-1][0 up to depth]
			    // as set_matched_type(flags[depth]);
			    // pass all rows and all columns and val to
			    // a method that will walk the columns, skipping the
			    // rows, and purge the val from the squares.
			    // return true;

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
			    }
			    RESPATH{
				std::cerr << "{";
				bool first_time=true;
				for(size_t adepth=0;adepth<depth;adepth++){
				    for(size_t ctr=0;ctr<mvss[adepth].size();ctr++){
					if(!first_time){
					    std::cerr << ' ';
					}
					first_time=false;
					std::cerr << "r" << mvss[adepth][ctr]->get_row()+1 << "c" << mvss[adepth][ctr]->get_column()+1;
				    }
				}
				std::cerr << "}  ==>";
			    }
			    for(size_t adepth=0;adepth<depth;adepth++){
				for(size_t ctr=0;ctr<mvss[adepth].size();ctr++){
				    mvss[adepth][ctr]->set_matched_type(flags[depth]);
				}
			    }
			    did_something=purge_row_col_sets(which,rowset,colset,val);
			    RESPATH  std::cerr << "\n";
			    return did_something;
			}else{
			    DISCERN_INTERLOCK_DEBUG std::cerr << "nope, we didn't find it\n";
			}
		    }else{
			DISCERN_INTERLOCK_DEBUG std::cerr << "Not a maximum depth, so just bump of d and at new level set row to 1 more than our row\n";
			++d;
			if(which==GT_ROW){
			    rows[d]=rows[d-1];
			}else{
			    cols[d]=cols[d-1];
			}
			if(d==depth){
			    return false;
			}
		    }
		}
	    }

	    if(which==GT_ROW){
		while(++rows[d]==(N+1)){ // bump up rows and if done deal with it
		    DISCERN_INTERLOCK_DEBUG std::cerr << "end of row loop for d==" << d << ", rows[d]: " << rows[d] << '\n';
		    if(d==0){
			DISCERN_INTERLOCK_DEBUG std::cerr << "backed up to d0, falling through to do val++;\n";
			rows[0]=0;
			continueon=false;

			break;
		    }else{
			d--;
			colsets[d].clear();
			DISCERN_INTERLOCK_DEBUG std::cerr << "backing up a level\n";
		    }
		}
	    }else{
		while(++cols[d]==(N+1)){
		    DISCERN_INTERLOCK_DEBUG std::cerr << "end of col loop for d==" << d << ", cols[d]: " << cols[d] << '\n';
		    if(d==0){
			DISCERN_INTERLOCK_DEBUG std::cerr << "backed up to d0, falling through to do val++;\n";
			cols[0]=0;
			continueon=false;

			break;
		    }else{
			d--;
			rowsets[d].clear();
			DISCERN_INTERLOCK_DEBUG std::cerr << "backing up a level\n";
		    }
		}
	    }
	}
    }
    return false;
}

template<const unsigned int N>
bool
board<N>::hidden_apply(size_t level)
{
    HIDDEN_APPLY_DEBUG std::cerr << "hidden_apply()\n";

    // check each row for hidden doubles
    HIDDEN_APPLY_DEBUG std::cerr << "  checking rows for hidden level: " << level << "\n";
    for(size_t row=0;row<N;row++){
	HIDDEN_APPLY_DEBUG std::cerr << "    row: " << row << '\n';
#if defined(RESPATH)
	if(discern_hidden(level, get_possibilities(GT_ROW,row),GT_ROW)){
#else
	if(discern_hidden(level, get_possibilities(GT_ROW,row))){
#endif
	    HIDDEN_APPLY_DEBUG std::cerr << "      found\n";
	    return true;
	}
    }
    // check each column for hidden doubles
    HIDDEN_APPLY_DEBUG std::cerr << "  checking columns for hidden level: " << level << "\n";
    for(size_t col=0;col<N;col++){
	HIDDEN_APPLY_DEBUG std::cerr << "    col: " << col << '\n';
#if defined(RESPATH)
	if(discern_hidden(level, get_possibilities(GT_COLUMN,col),GT_COLUMN)){
#else
	if(discern_hidden(level, get_possibilities(GT_COLUMN,col))){
#endif
	    HIDDEN_APPLY_DEBUG std::cerr << "      found\n";
	    return true;
	}
    }
    // check each block for hidden doubles
    HIDDEN_APPLY_DEBUG std::cerr << "  checking blocks for hidden level: " << level << "\n";
    for(size_t block=0;block<N;block++){
	HIDDEN_APPLY_DEBUG std::cerr << "    block: " << block << '\n';
#if defined(RESPATH)
	if(discern_hidden(level, get_possibilities(GT_BLOCK,block),GT_BLOCK)){
#else
	if(discern_hidden(level, get_possibilities(GT_BLOCK,block))){
#endif
	    HIDDEN_APPLY_DEBUG std::cerr << "      found\n";
	    return true;
	}
    }
    return false;
}

template<const unsigned int N>
bool
board<N>::y_wing_apply()
{
    Y_WING_APPLY_DEBUG std::cerr << "y_wing_apply()\n";
    for(size_t ctr1=0;ctr1<N*N;ctr1++){
	size_t row1=ctr1/N;
	size_t col1=ctr1%N;
	if(b[row1][col1].check_matched_type(square::AM_Y_WING)){
	    Y_WING_APPLY_DEBUG std::cerr << "found square already Y_WING: " << b[row1][col1] << "--skipping\n";
	    continue;
	}
	if(b[row1][col1].size()!=2){
	    // only look at squares with 2 pvals
	    continue;
	}
	Y_WING_APPLY_DEBUG  std::cerr << "y-wing apply: found a cell with 2 pvals: " << b[row1][col1] << "--going to check neighbors with two pvals\n";
	std::set<square*> sqs1=get_neighbors(&b[row1][col1],&square::two_filt);
	Y_WING_APPLY_DEBUG std::cerr << "found " << sqs1.size() << " neighbors with two pvals\n";
	if(sqs1.size()>0){
	    std::set<square*>::iterator it1;
	    for(it1=sqs1.begin();it1!=sqs1.end();it1++){
		// we are iterating through the neighbors of b[row1][col1] w/2 pvals
		Y_WING_APPLY_DEBUG std::cerr << "checking for neighbors of " << **it1 << " with 2 pvals\n";
		std::set<square*> sqs2=get_neighbors(*it1,&square::two_filt);
		Y_WING_APPLY_DEBUG std::cerr << "found " << sqs2.size() << " neighbors with two pvals\n";
		// we have neighbors of a neighbor of b[row1][col1]
		if(sqs2.size()>1){
		    // must have original plus one more
		    std::set<square*>::iterator it2;
		    for(it2=sqs2.begin();it2!=sqs2.end();it2++){
			if((*it2)->get_row()!=row1 || (*it2)->get_column()!=col1){
			    Y_WING_APPLY_DEBUG std::cerr << "found 3rd square: " << **it2 << '\n';
			    // not our original so we have a chain of three
			    // b[row1][row2]->**it1->**it2 squares each with only
			    // two pvals
			    // Now we check if between them they only have three
			    // pvals
			    std::set<size_t> pvals;
			    pvals.insert(b[row1][col1][0]);
			    pvals.insert(b[row1][col1][1]);
			    pvals.insert((**it1)[0]);
			    pvals.insert((**it1)[1]);
			    pvals.insert((**it2)[0]);
			    pvals.insert((**it2)[1]);
			    Y_WING_APPLY_DEBUG std::cerr << "looking for total of 3 pvals between the three cells, found: " << pvals.size() << '\n';
			    if(pvals.size()==3){
				// now check to make sure two don't have same
				// pvals
				if(b[row1][col1].same_pvals(**it1) 
				    ||b[row1][col1].same_pvals(**it2) 
				    ||(**it1).same_pvals(**it2)){
				    Y_WING_APPLY_DEBUG std::cerr << "found 3 but two are duplicates, skipping\n";
				    continue;
				}
				if((b[row1][col1].get_row()==(**it1).get_row() 
				    &&b[row1][col1].get_row()==(**it2).get_row())
				|| (b[row1][col1].get_column()==(**it1).get_column() 
				    &&b[row1][col1].get_column()==(**it2).get_column())){
				    Y_WING_APPLY_DEBUG std::cerr << "co-linear, skipping\n";
				    continue;
				}
				Y_WING_APPLY_DEBUG std::cerr << "right number of pvals, not co-linear, no duplicates--looking hopeful!\n";
				std::set<square*> sqs3=get_neighbors(*it2,&square::two_filt);
				std::vector<square*> inter;
				std::vector<square*>::iterator vi;
				std::set<square*> sqs1i=get_neighbors(&b[row1][col1]);
				std::set<square*> sqs3i=get_neighbors(*it2);
				
				inter.resize(sqs1i.size()+sqs3i.size());
				vi=std::set_intersection(sqs1i.begin(),sqs1i.end(),sqs3i.begin(),sqs3i.end(),inter.begin());
				inter.resize(vi-inter.begin());
				Y_WING_APPLY_DEBUG std::cerr << "checking size of intersection between first and third: " << inter.size() << "\n";
				if(inter.size()>1){
				    size_t shared_val=0;
				    if(b[row1][col1][0]==(**it2)[0] || b[row1][col1][0]==(**it2)[1]){
					shared_val=b[row1][col1][0];
				    }else if(b[row1][col1][1]==(**it2)[0] || b[row1][col1][1]==(**it2)[1]){
					shared_val=b[row1][col1][1];
				    }
				    Y_WING_APPLY_DEBUG std::cerr << "first and third share " << shared_val << '\n';

				    RESPATH{
					square& sq1=b[row1][col1],
					    &sq2=**it1, &sq3=**it2;
					std::cerr << "y-wing "
					    << "{n" << sq1[0] << " n" << sq1[1]
					    << "}{r" << row1
					    << "c" << col1 << "}"
					    << " {n" << sq2[0] << " n" << sq2[1]
					    << "}{r" << sq2.get_row()
					    << "c" << sq2.get_column() << "}"
					    << " {n" << sq3[0] << " n" << sq3[1]
					    << "}{r" << sq3.get_row()
					    << "c" << sq3.get_column() << "}"
					    << " ==>";
				    }
				    bool did_something=false;
				    for(size_t ctr=0;ctr<inter.size();ctr++){
					//  purge the shared val from all shared
					//  neighbors
					if(inter[ctr]!=*it1){
					    did_something|=clear_pval_val(inter[ctr]->get_row(),inter[ctr]->get_column(),shared_val);
					}
				    }
				    if(did_something){
					Y_WING_APPLY_DEBUG std::cerr << "found a y-wing:\n";
					Y_WING_APPLY_DEBUG std::cerr << b[row1][col1] << **it1 << **it2;
					Y_WING_APPLY_DEBUG std::cerr << "middle one is the pivot\n";
					Y_WING_APPLY_DEBUG std::cerr << "shared val is: " << shared_val << '\n';
					Y_WING_APPLY_DEBUG std::cerr << "cleared something, setting AM_Y_WING on three squares and returning true\n";
					b[row1][col1].set_matched_type(square::AM_Y_WING);
					(**it1).set_matched_type(square::AM_Y_WING);
					(**it2).set_matched_type(square::AM_Y_WING);
					RESPATH std::cerr << "\n";
					return true;
				    }
				    RESPATH std::cerr << "\n";
				}
			    }
			}else{
			    Y_WING_APPLY_DEBUG std::cerr << " found our original, skipping\n";
			}
		    }
		}
	    }
	}
    }
    return false;
}

template<const unsigned int N>
bool
board<N>::naked_apply(size_t level)
{
    NAKED_APPLY_DEBUG std::cerr << "naked_apply()\n";

    // check each row for naked N
    NAKED_APPLY_DEBUG std::cerr << "  checking rows for naked level: " << level << "\n";
    for(size_t row=0;row<N;row++){
	NAKED_APPLY_DEBUG std::cerr << "    row: " << row << '\n';
#if defined(SHOW_RESPATH)
	if(discern_naked(level, get_squares(GT_ROW,row),GT_ROW)){
#else
	if(discern_naked(level, get_squares(GT_ROW,row))){
#endif
	    NAKED_APPLY_DEBUG std::cerr << "      found\n";
	    return true;
	}
    }
    // check each column for naked N
    NAKED_APPLY_DEBUG std::cerr << "  checking columns for naked level: " << level << "\n";
    for(size_t col=0;col<N;col++){
	NAKED_APPLY_DEBUG std::cerr << "    col: " << col << '\n';
#if defined(SHOW_RESPATH)
	if(discern_naked(level, get_squares(GT_COLUMN,col),GT_COLUMN)){
#else
	if(discern_naked(level, get_squares(GT_COLUMN,col))){
#endif
	    NAKED_APPLY_DEBUG std::cerr << "      found\n";
	    return true;
	}
    }
    // check each block for naked N
    NAKED_APPLY_DEBUG std::cerr << "  checking blocks for naked level: " << level << "\n";
    for(size_t block=0;block<N;block++){
	NAKED_APPLY_DEBUG std::cerr << "    block: " << block << '\n';
#if defined(SHOW_RESPATH)
	if(discern_naked(level, get_squares(GT_BLOCK,block),GT_BLOCK)){
#else
	if(discern_naked(level, get_squares(GT_BLOCK,block))){
#endif
	    NAKED_APPLY_DEBUG std::cerr << "      found\n";
	    return true;
	}
    }
    return false;
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
	XY_CHAIN_DEBUG std::cout << "xy_chain_apply  chain.size()==0 returning false\n";
	return false;
    }
    XY_CHAIN_DEBUG {
    std::cout << "xy_chain_apply ";
    for(size_t i=0;i<chain.size();i++){
	size_t lo=chain[i]->get_xy_owned();
	std::cout
	    << 'r' << chain[i]->get_row()
	    << 'c' << chain[i]->get_column()
	    << " {";
	if(lo==(*chain[i])[0]){
	    std::cout << "|" << (*chain[i])[0] << "|"
	    << "," << (*chain[i])[1] << "} ";
	}else{
	    std::cout << (*chain[i])[0]
	    << ",|" << (*chain[i])[1] << "|} ";
	}
    }
    std::cout << '\n';
    }
    square *last_square=chain.back();
    XY_CHAIN_DEBUG std::cout << "last_square: " << *last_square << '\n';

    XY_CHAIN_DEBUG std::cout << "calling get_neighbors for: " << *last_square << '\n';
    std::set<square*> cands=get_neighbors(last_square,&square::xy_chain_filt);
    XY_CHAIN_DEBUG std::cout << "  there are " << cands.size() << " candidates for the next link\n";
    size_t last_owned=last_square->get_xy_owned();
    size_t next_matched=last_square->get_xy_next();

    for(auto it=cands.begin();it!=cands.end();it++){
	square* sq=*it;
	XY_CHAIN_DEBUG std::cout << "candidate: " << *sq << '\n';
	if(std::find(chain.begin(),chain.end(),sq)==chain.end()){
	    XY_CHAIN_DEBUG std::cout << "NOT FOUND IN CHAIN ALREADY\n";
	    // only look if cand square not already in chain to avoid loops
	    XY_CHAIN_DEBUG std::cout << "last owned: " << last_owned << '\n';
	    if((*sq)[0]==last_owned){
		sq->set_owned(1);
	    }else if((*sq)[1]==last_owned){
		sq->set_owned(0);
	    }else{
		// should never happen
		XY_CHAIN_DEBUG std::cout << "should never happen, next_matched: " << next_matched << "doesn't match either pval in square: " << *sq << "\n";
		continue;
	    }
	    chain.push_back(sq);
	    if(chain.size()>2){
		if(chain[0]->get_xy_next()==sq->get_xy_owned()){
		    size_t row1,row2,col1,col2,blk1,blk2,owned;
		    row1=chain[0]->get_row();
		    col1=chain[0]->get_column();
		    row2=sq->get_row();
		    col2=sq->get_column();
		    blk1=get_block_num(row1,col1);
		    blk2=get_block_num(row2,col2);
		    owned=sq->get_xy_owned();
		    if((row1==row2)||(col1==col2)||blk1==blk2){
			RESPATH{
			    // this will print the xy-chain even if no pvals
			    // will be cleared
			    std::cerr << "xy-chain type1 ";

			    for(size_t i=0;i<chain.size();i++){
				size_t lo=chain[i]->get_xy_owned();
				std::cout
				    << 'r' << chain[i]->get_row()+1
				    << 'c' << chain[i]->get_column()+1
				    << "{";
				if(lo==(*chain[i])[0]){
				    std::cout << "|" << (*chain[i])[0] << "|"
				    << "," << (*chain[i])[1] << "} ";
				}else{
				    std::cout << (*chain[i])[0]
				    << ",|" << (*chain[i])[1] << "|} ";
				}
			    }
			    std::cerr << " ==>";
			}
			bool rtval=update_pval_for_squares(*chain[0],*sq,owned);
			RESPATH std::cerr << "\n";
			if(rtval){
			    XY_CHAIN_DEBUG std::cout << "cleared some pvals\n";
			    return true;
			}
		    }
		}else{
		    size_t rmval=0;
		    if(sq->in_vals(chain[0]->get_xy_next())){
			rmval=chain[0]->get_xy_next();
		    }else if(sq->in_vals(chain[0]->get_xy_owned())){
			rmval=chain[0]->get_xy_owned();
		    }
		    if(rmval && can_see(*chain[0],*sq)){ 
			RESPATH{
			    // this will print the xy-chain even if no pvals
			    // will be cleared
			    std::cerr << "xy-chain type2 ";

			    for(size_t i=0;i<chain.size();i++){
				size_t lo=chain[i]->get_xy_owned();
				std::cout
				    << 'r' << chain[i]->get_row()+1
				    << 'c' << chain[i]->get_column()+1
				    << "{";
				if(lo==(*chain[i])[0]){
				    std::cout << "|" << (*chain[i])[0] << "|"
				    << "," << (*chain[i])[1] << "} ";
				}else{
				    std::cout << (*chain[i])[0]
				    << ",|" << (*chain[i])[1] << "|} ";
				}
			    }
			    std::cerr << " ==>";
			}
			bool rtval=clear_pval_val(chain[0]->get_row(),chain[0]->get_column(),rmval);
			RESPATH std::cerr << '\n';
			if(rtval){
			    XY_CHAIN_DEBUG std::cout << "cleared some pvals\n";
			    return true;
			}
		    }
		}
	    }
	    if(xy_chain_apply(chain)){
		XY_CHAIN_DEBUG std::cout << "recursive returned true so returning true\n";
		return true;
	    }else{
		chain.pop_back();
	    }
	}else{
	    XY_CHAIN_DEBUG std::cout << "FOUND IN CHAIN ALREADY SO SKIPPING\n";
	}
    }
    XY_CHAIN_DEBUG std::cout << "returning false\n";
    return false;
}

template<const unsigned int N>
bool
board<N>::interlock_apply(size_t depth)
{
    assert(depth>=2);
    INTERLOCK_APPLY_DEBUG std::cerr << "interlock_apply()\n";

    if(discern_interlock(depth,GT_ROW)){
	INTERLOCK_APPLY_DEBUG std::cerr << "      found\n";
	return true;
    }
    if(discern_interlock(depth,GT_COLUMN)){
	INTERLOCK_APPLY_DEBUG std::cerr << "      found\n";
	return true;
    }
    return false;
}

template<const unsigned int N>
void
board<N>::init()
{
    root=sqrt(double(N));
    assert(root*root==N);
    backed_count=0;
    set_squares=0;
    // the resizes result in default constructors for elements being called.
    b.resize(N);
    for(size_t ctr=0;ctr<N;ctr++){
	b[ctr].resize(N);
    }
    for(size_t val=1;val<N;val++){
	row_possibilities[val];
	column_possibilities[val];
	block_possibilities[val];
    }
    BOARD_CONSTRUCT_DEBUG std::cerr << "sizes reserved for board\n";
    // We set row and column early so that we can log changes
    for(size_t row=0;row<N;row++){
	for(size_t col=0;col<N;col++){
	    b[row][col].set_rowcol(row,col);
	}
    }
    valid=true;
    //clear();
    register_strategies();
}

template<const unsigned int N>
board<N>::board():valid(true)
{
    bool ssup=suppress_output;
    suppress_output=true;
    BOARD_CONSTRUCT_DEBUG std::cerr << "~~~ board()\n";
    init();
    suppress_output=ssup;
}

template<const unsigned int N>
board<N>::board(std::vector<square> sqs)
{
    bool ssup=suppress_output;
    suppress_output=true;
    init();
    for(size_t ctr=0;ctr<sqs.size();ctr++){
	b[sqs[ctr].get_row()][sqs[ctr].get_column()]=sqs[ctr];
    }
    update_possibilities();
    suppress_output=ssup;
}

template<const unsigned int N>
board<N>::board(std::string in)
{
    bool ssup=suppress_output;
    suppress_output=true;
    BOARD_CONSTRUCT_DEBUG std::cerr << "~~~ board(std::string in)\n";
    init();
    assert(N*N==in.size());
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
	    b[rctr][cctr]=other.b[rctr][cctr];
	}
    }
    valid=other.valid;
    root=other.root;
    return *this;
}

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

template<const unsigned int N>
bool
board<N>::validate_columns()
{
    // checks to see if all numbers 0-N+1 are in each column
    std::vector<unsigned int> pvals;
    for(size_t cctr=0;cctr<N;cctr++){
	pvals={ 1,2,3,4,5,6,7,8,9 };
	for(size_t rctr=0;rctr<N;rctr++){
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

template<const unsigned int N>
bool
board<N>::validate_rows()
{
    // checks to see if all numbers 0-N+1 are in each row
    std::vector<unsigned int> pvals;
    for(size_t rctr=0;rctr<N;rctr++){
	pvals={ 1,2,3,4,5,6,7,8,9 };
	for(size_t cctr=0;cctr<N;cctr++){
	    std::vector<unsigned int>::iterator it;
	    it=std::find(pvals.begin(),pvals.end(),b[rctr][cctr].get_val());
	    pvals.erase(it);
	}
	if(pvals.size()!=0){
	    VALIDATE_DEBUG std::cerr << "row " << rctr << " is not correct\n";
	    solved=false;
	    return false;
	}
    }
    return true;
}

template<const unsigned int N>
bool
board<N>::validate_blocks()
{
    // checks to see if all numbers 0-N+1 are in each block
    std::vector<unsigned int> pvals;
    for(size_t block_num=0; block_num<N;block_num++){
	pvals={ 1,2,3,4,5,6,7,8,9 };
	size_t row_min=root*(block_num/root),
	       row_max=row_min+root,
	       col_min=root*(block_num%root),
	       col_max=col_min+root;
	for(size_t rctr=row_min;rctr<row_max;rctr++){
	    for(size_t cctr=col_min;cctr<col_max;cctr++){
		std::vector<unsigned int>::iterator it;
		it=std::find(pvals.begin(),pvals.end(),b[rctr][cctr].get_val());
		pvals.erase(it);
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

template<const unsigned int N>
void
board<N>::print(){
    std::string bdr="+";
    for(size_t i=0;i<N;i++){
	bdr+="-+";
    }
    for(size_t i=0;i<N;i++){
	if(i%3==0){
	    std::cerr << bold;
	    std::cerr << bdr << "\n|";
	    std::cerr << unbold;
	}else{
	    std::cerr << bdr << "\n" << bold << "|" << unbold;
	}
	for(size_t j=0;j<N;j++){
	    size_t val=b[i][j].get_val();
	    if(val==0){
		std::cerr << " ";
	    }else{
		if(b[i][j].is_locked()){
		    std::cerr << bold << val << unbold;
		}else{
		    std::cerr << val;
		}

	    }
	    if((j+1)%3==0){
		std::cerr << bold << '|' << unbold;
	    }else{
		std::cerr << '|';
	    }
	}
	std::cerr << '\n';
    }
    std::cerr << bold << bdr << unbold << "\n";
}

template<const unsigned int N>
void
board<N>::print_large(){
    std::string bdr="+";
    for(size_t i=0;i<N;i++){
	bdr+="---+";
    }
    std::cerr << bold << bdr << unbold << "\n";
    for(size_t row=0;row<N;row++){
	for(size_t subrow=0;subrow<root;subrow++){
	    for(size_t col=0;col<N;col++){
		if(!(col%root)){
		    std::cerr << bold << '|' << unbold;
		}else{
		    std::cerr << '|';
		}

		for(size_t subcol=0;subcol<root;subcol++){
		    if(b[row][col].get_val()==0){
			size_t val=(subrow)*root+subcol+1;
			if(b[row][col].in_vals(val)){
			    std::cerr << val;
			}else{
			    std::cerr << ' ';
			}
		    }else if(subcol==(root)/2 && subrow==(root)/2){
			std::cerr << bold << b[row][col].get_val() << unbold;
		    }else{
#if !defined(USE_TTY_BOLD)
			std::cerr << '*';
#else
			std::cerr << ' ';
#endif
		    }
		}
	    }
	    std::cerr << "|\n";
	}
	if(!((row+1)%root)){
	    std::cerr << bold << bdr << unbold << "\n";
	}else{
	    std::cerr << bdr << '\n';
	}
    }
}

template<const unsigned int N>
void
board<N>::print_just_pvals(){
    std::string bdr="+";
    for(size_t i=0;i<N;i++){
	bdr+="---+";
    }
    std::cerr << bold << bdr << unbold << "\n";
    for(size_t row=0;row<N;row++){
	for(size_t subrow=0;subrow<root;subrow++){
	    for(size_t col=0;col<N;col++){
		if(!(col%root)){
		    std::cerr << bold << '|' << unbold;
		}else{
		    std::cerr << '|';
		}

		for(size_t subcol=0;subcol<root;subcol++){
		    size_t val=(subrow)*root+subcol+1;
		    if(b[row][col].in_vals(val)){
			std::cerr << val;
		    }else{
			std::cerr << ' ';
		    }
		}
	    }
	    std::cerr << "|\n";
	}
	if(!((row+1)%root)){
	    std::cerr << bold << bdr << unbold << "\n";
	}else{
	    std::cerr << bdr << '\n';
	}
    }
}

template<const unsigned int N>
inline
void
board<N>::prune_column_pvals(unsigned int row, unsigned int col, std::vector<unsigned int> &pv,bool mark_invalid=true)
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
board<N>::prune_row_pvals(unsigned int row, unsigned int col, std::vector<unsigned int> &pv,bool mark_invalid=true)
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
board<N>::prune_block_pvals(unsigned int row, unsigned int col, std::vector<unsigned int> &pv,bool mark_invalid=true)
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
	    std::cerr << "r" << sqs[sctr]->get_row()+1
		<< "c" << sqs[sctr]->get_column()+1;
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
    RESPATH std::cerr << " ==>";
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
    RESPATH std::cerr << " ==>";
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
board<N>::set_val(size_t row, size_t col,size_t val,bool set_pval=true)
{
    /*! This is intended to be the only place that board sets values, so that
     * count can be kept accurate.
     * \param row which row of the board is the square in
     * \param col which column of the board is the square in
     * \param val the value to set the square to
     */
    if(b[row][col].get_val()==0 && val!=0){
	set_squares++;
    }
    if(set_pval){
	// You might think, that if set_pval is set and we pass it to
	// square::set_val, it will just clear the pvals and then set
	// the single one matching the value being set.  You'd be right.  BUT!
	// Then we wouldn't maintain our other data structure
	std::vector<size_t> spv;
	for(size_t ctr=0;ctr<b[row][col].size();ctr++){
	    // we make a copy of the squares pvals to avoid the invalidated
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
}

/*! does two things.
 * 1) Has the square at b[row][col] take val out of pvals if it exists.
 * 2) If it did exist, adjust the three possibility vectors, rows_possibilities
 *    column_possibilities, and block_possibilities, but removing the
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

    // ask the square to clear the val, retval means val was set before clearing
    bool retval=b[row][col].clear_pval_val(val);
    RESPATH{
	if(retval && !suppress_output){
	    std::cerr << " r" << row+1 << "c" << col+1 << " ≠ " << val;
	}
    }
    std::vector<square*>::iterator i;

    if(retval){
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
    return retval;
}

/*!
 * given two squares and a pval, remove that pval from any square visible
 * from both of the squares.
 * \param sq1 Square the first
 * \param sq2 Square the second
 * \parem val The pval to be removed
 * \return true if any were found and removed
 */
template<const unsigned int N>
bool
board<N>::update_pval_for_squares(square& sq1,square& sq2, size_t val)
{
    bool retval=false;
    size_t row1,row2,col1,col2,blk1,blk2;
    row1=sq1.get_row();
    row2=sq2.get_row();
    col1=sq1.get_column();
    col2=sq2.get_column();
    blk1=get_block_num(row1,col1);
    blk2=get_block_num(row2,col2);

    if(row1==row2){
	// walk through all squares not us in our shared row and remove the val
	// from their pvals if there.  retval will get a true or'd into it if so
	for(size_t col=0;col<N;col++){
	    if(col!=col1&&col!=col2){
		retval|=clear_pval_val(row1,col,val);
	    }
	}
    }
    if(col1==col2){
	// walk through all squares not us in our shared column and remove the
	// val from their pvals if there.  retval will get a true or'd into it
	// if so
	for(size_t row=0;row<N;row++){
	    if(row!=row1&&row!=row2){
		retval|=clear_pval_val(row,col1,val);
	    }
	}
    }
    if(blk1==blk2){
	// walk through all squares not us in our shared block and remove the
	// val from their pvals if found.  retval will get a true or'd into it
	// if so
	size_t row_min=root*(row1/root),
	       row_max=row_min+root,
	       col_min=root*(col1/root),
	       col_max=col_min+root;
	for(size_t row=row_min;row<row_max;row++){
	    for(size_t col=col_min;col<col_max;col++){
		if((col1!=col||row1!=row) && (col2!=col||row2!=row)){
		    retval|=clear_pval_val(row,col,val);
		}
	    }
	}
    }
    return retval;
}

/*!
 * given a row and column, remove the val set in the square at that row and
 * column from every other square that shares a row, column, or block with
 * the square at the row and column
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
 * given a set of squares and a set of vals, remove from each square in the
 * square set each val in the val set.
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
    //std::map<size_t,std::map<size_t,std::vector<square*>>> row_possibilities;
    //! map of vals to map of columns to vector of squares in each column with val in pvals
    //std::map<size_t,std::map<size_t,std::vector<square*>>> column_possibilities;
    //! map of vals to map of blocks to vector of squares in each block with val in pvals
    //std::map<size_t,std::map<size_t,std::vector<square*>>> block_possibilities;
    //! Count of squares that have been set
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
board<N>::generate_pvals(unsigned int row, unsigned int col,bool mark_invalid=true)
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
 * \todo dig into the result to create a puzzle
 * \return true if success (which we always expect)
 * Currently on an old dell inspiron 1420 with linux on it, it can
 * generate more than 20,000 puzzles/second with this method at a rate
 * of about 46µs/board building with g++ with -O3 (with -O0 about
 * 400µs/board).
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
    set_squares=N*N;
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
 * \return true if success (which we always expect)
 *
 * \par Comments
 * n.b. squares in this program are numbered horizontally and vertically 0-N-1,
 * which for N of 9, i.e. a usual sudoku puzzle, is 0-8,
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
 6*.......@6  @ - rotated cells
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
 6.........6  @ - rotated cells
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
 2.........2  @ (1,6), (1,7), (0,6) (horizontal reflection of *)
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
 6@........6  @ - rotated cells
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
 6.........6  @ - rotated cells
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
 6.........6  @ - rotated cells
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
 6@........6  @ - rotated cells
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
 5........@5  @ - rotated cells
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
 6.........6  @ - rotated cells
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
 7...*.....7  @ - rotated cells
 8....***..8
  012345678
 \endcode
 *
 */
template<const unsigned int N>
bool
board<N>::dig_puzzle(symtype st,size_t max_clues=32,bool status=false)
{
    DIG_DEBUG std::cerr << "dig_puzzle(";
    DIG_DEBUG print_st(std::cerr,st);
    DIG_DEBUG std::cerr << "," << max_clues << ")\n";
    size_t low_count=N*N;
    board<N> b,tmp1;
    b.generate();
    DIG_DEBUG std::cerr << "after generate()~~~~~~~~~~~~~\n";
    size_t solutions; //=b.brute_force_check();
    DIG_DEBUG std::cerr << "solutions: " << solutions << '\n';
    DIG_DEBUG b.print_large();
    DIG_DEBUG std::cerr << "after generate()~~~~~~~~~~~~~\n";
    DIG_DEBUG std::cerr << "bfc: " << b.brute_force_check() << '\n';

    tmp1=b;
    while(true){
	if(status) std::cerr << '.';
	size_t row=rand_n(N);
	size_t col=rand_n(N);
	dig_one(row,col,tmp1,st);
	if(tmp1.count()<low_count) low_count=tmp1.count();
	DIG_DEBUG std::cerr << "count is: " << tmp1.count() << ", low count: " << low_count << "\n";
	if(tmp1.count()<max_clues){
	    DIG_DEBUG std::cerr << "calling bfc\n";
	    tmp1.update_pvals();
	    DIG_DEBUG tmp1.print();
	    size_t solutions=tmp1.brute_force_check();
	    DIG_DEBUG std::cerr << "called bfc, solutions: " << solutions << "\n";
	    if(solutions>1 || solutions==0){
		DIG_DEBUG std::cerr << "not 1 solutions, but: " << solutions << ", starting over\n";
		tmp1=b;
		if(status) std::cerr << "starting over, " << solutions << " solutions\n";
	    }else {
		*this=tmp1;
		DIG_DEBUG std::cerr << "returning a solution\n";
		update_possibilities();
		count();
		return true;
	    }
	}
    }
    count();
    return true;
}

/*! using the register name, ("x-wing", "hidden double", etc...), look
 * to see how many times the apply method was successfully applied.  Of 
 * course this will make most sense after calling the heuristic_solution()
 * method and solving a puzzle
 * \param s the name of the method as registered
 * \return the number of times the method was successfully invoked with 
 * success meaning that it cause a change in val and/or pvals for one or
 * more squares. i.e. just because we find a naked double doesn't mean
 * that we'll find pvals that we can clear.  If we don't clear them, then
 * the "naked double" count does not get incremented.
 */
template<const unsigned int N>
size_t
board<N>::get_strategy_count(std::string s)
{
    typename std::map<size_t, std::map<std::string, class sudoku_method<N>*>>::iterator it1;
    for(it1=strategies.begin();it1!=strategies.end();it1++){
	typename std::map<std::string, class sudoku_method<N>*>::iterator it2;
	if((it2=it1->second.find(s))!=it1->second.end()){
	    return it2->second->get_count();
	}
    }
    return 0;
}

/*! return a running count.  This is the same as the value returned from
 * count() for a heuristic solution, but hugely larger for the brute
 * force solution which may set a square many times before finding the
 * final solution
 * \return the count
 */
template<const unsigned int N>
size_t
board<N>::get_count()
{
    return set_squares;
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
    set_squares=retval;
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
board<N>::heuristic_solution(bool preserve_pvals=false)
{
    HEURISTIC_DEBUG std::cerr << "heuristic_solution()\n";

    if(!preserve_pvals){
	// normally of course, we'd always want to make sure that our pvals are
	// all correct, but in testing, we set up abnormal situations,
	// i.e. combinations of pvals and vals, to trigger particular paths
	// through the code, and in that case we do NOT want to update the pvals
	update_pvals();
    }
    clear_strategy_counts();

    HEURISTIC_DEBUG{
	std::cerr << "  before heuristic\n";
	print_large();
    }

    bool progressing=true;

    while(progressing && count()!=N*N){
	progressing=false;
#if 0
	if(ns.apply()		// naked single
		|| hs.apply()	// hidden single
		|| intr.apply()	// intersections
		|| nd.apply()	// naked double
		|| hd.apply()	// hidden double
		|| nt.apply()	// naked triple
		|| ht.apply()	// hidden triple
		|| nq.apply()	// naked quad
		|| hq.apply()	// hidden quad
		|| xw.apply()	// x-wing
		|| yw.apply()	// y-wing
		|| sf.apply()	// swordfish
		|| jf.apply()	// jellyfish
		|| cpc.apply()  // xy-chain
		){
#endif
	HEURISTIC_DEBUG{
	    std::cerr << "calling naked single apply\n";
	}
	if(ns.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling hidden single apply\n";
	}
	if(hs.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling intersection apply\n";
	}
	if(intr.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling naked double apply\n";
	}
	if(nd.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling hidden double apply\n";
	}
	if(hd.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling naked triple apply\n";
	}
	if(nt.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling hidden triple apply\n";
	}
	if(ht.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling naked quad apply\n";
	}
	if(nq.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling hidden quad apply\n";
	}
	if(hq.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling x-wing apply\n";
	}
	if(xw.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling y-wing apply\n";
	}
	if(yw.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling swordfish apply\n";
	}
	if(sf.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling jellyfish apply\n";
	}
	if(jf.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
	HEURISTIC_DEBUG{
	    std::cerr << "calling xy-chain apply\n";
	}
	if(cpc.apply()){
	    progressing=true;
	    HEURISTIC_DEBUG{
		std::cerr << "--and apply SUCCEEDED!\n";
	    }
	    continue;
	}else{
	    HEURISTIC_DEBUG std::cerr << "--and apply failed\n";
	}
    }
    HEURISTIC_DEBUG{
	std::cerr << "  after heuristic\n";
	print_large();
    }
    return is_solved();
}

/*!
 * this method walks cell by cell filling in squares from the first pval
 * and then backing up when it hits a square with 0 pvals.  After backing
 * up, it tries a different pval until it runs out and then backs again.
 * Locked cells, those that were specified as part of the original puzzle
 * are passed over both setting and backing.  If you want to know how
 * many times brute_force_solution() had to back up, you can use the
 * board<N>::get_backed_count() method.  A typical amount on a difficult
 * puzzle will be around five or six thousand times.
 * \return bool always true if success.  It will always succeed if the 
 * puzzle was valid.
 */
template<const unsigned int N>
bool
board<N>::brute_force_solution()
{
    bool backed=false;
    size_t row, col;
    ssize_t which=0;
    const ssize_t max=N*N;

    BRUTE_DEBUG std::cerr << "brute force solution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    if(valid){
	while(which!=max){
	    BRUTE_DEBUG std::cerr << " which: " << which << '\n';
	    row=which/N;
	    col=which%N;
	    BRUTE_DEBUG std::cerr << "square[row: " << row << "][col: " << col << "], locked: " << std::boolalpha << b[row][col].is_locked() << "\n";
	    if(!b[row][col].is_locked()){
		BRUTE_DEBUG std::cerr << "square not locked\n";
		if(!backed){
		    BRUTE_DEBUG std::cerr << "calling generate_pvals\n";
		    // this takes up a lot of the execution time...but when
		    // we get here, we've either just added a square, or,
		    // possibly, we've taken away a bunch.
		    generate_pvals(row,col,false);
		}else{
		    // here backed was true, so we are dealing with the existing
		    // pvals with the last used val taken out, so we don't call
		    // generate_pvals because that would mess it up!  We do set
		    // backed to false, so as we walk forward we can generate
		    // pvals for successive squares until we either get a 
		    // solution, or hit a square with 0 possible values and
		    // have to back up again and try something different.
		    BRUTE_DEBUG std::cerr << "not calling generate_pvals() since we backed\n";
		    backed=false;
		}
		if(!b[row][col].size()){
		    BRUTE_DEBUG std::cerr << "square has no more pvals, rewinding: " << b[row][col];
		    // There's no more vals, we'll have to rewind.
		    backed=true;
		    do{
			which--;
			backed_count++;
			row=which/N;
			col=which%N;
			square& sq=b[row][col];
			BRUTE_DEBUG std::cerr << "    backed up: now square[" << row << "][" << col << "]";
			if(!sq.is_locked() && sq.size() > 1){
			    // backing up we skip locked since we can't change
			    // them, and cells with only one value since we
			    // would have already tried them.
			    // Then on the cell we backed up to, we pull the
			    // value we tried out of pvals and set the val to
			    // zero so that at the top of the loop we'll try a
			    // different value.
			    BRUTE_DEBUG std::cerr << "...found next    -- clearing to 0 and breaking out.\n";
			    sq.clear_pval_val(sq.get_val());
			    sq.set_val(0,false);
			    break;
			}else if(sq.is_locked()){
			    BRUTE_DEBUG std::cerr << "...square locked -- backing again\n";
			}else if(b[row][col].size()==1){
			    // for aesthetics while printing boards
			    BRUTE_DEBUG std::cerr << "...size(1)       -- clearing to 0, backing again.\n";
			    b[row][col].set_val(0,false);
			}else{
			    BRUTE_DEBUG std::cerr << "DANGER DANGER WILL ROBINSON\n";
			}
		    }while(which>=0);
		    if(which==-1){
			// we failed and backed up off the front!
			BRUTE_DEBUG std::cerr << "Backed up off the front returning false\n";
			BRUTE_DEBUG std::cerr << "valid: " << valid << '\n';
			return false;
		    }
		    continue;	// skip incrementing which since we backed.
		} else{
		    square& sq=b[row][col];
		    sq.set_val(sq[0],false);
		}
	    }
	    which++;

	    // cell was locked or chose a value, go to next cell
	}
    }
    set_squares=N*N;
    return true;
}

/*!
 * This routine uses the same algorithm as brute_forch_solution, but after
 * finding one solution, it remembers it and then trys to remove the previous
 * found value from each square that isn't locked in turn to see if we find
 * another solution.  You might actually find a lot of solutions if you 
 * set stopafter2 false, but you are unlikely to find all solutions, since that
 * would take a more complex algorithm.  We really don't care to find ALL
 * solutions, this is used when digging out a generated board to see if we've
 * dug out too many and have created a puzzle with more than one solution.  We
 * don't need to know more than that there is more than one solution, so the
 * additional data structures and execution time to find all is not required.
 * \param stopafter2 this bool, defaulting to true tells the checker to quit after finding 2 solutions if true, or to look for all if false.
 * \return size_t the number of found solutions--this is always 0, 1, or 2 unless you set stopafter2 false.
 */
template<const unsigned int N>
size_t
board<N>::brute_force_check(bool stopafter2=true)
{
    BRUTE_CHECK_DEBUG std::cerr << "brute force check ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    BRUTE_CHECK_DEBUG std::cerr << "brute_force_check() got this board: \n";
    BRUTE_CHECK_DEBUG print_large();
    BRUTE_CHECK_DEBUG print_just_pvals();

    std::vector<std::vector<size_t>> sols;
    bool backed=false;
    size_t row, col, solutions=0;
    ssize_t which=0,firstwhich=0;
    const ssize_t max=N*N;
    board<N> checkb=*this;
    // now find first square not locked with more than 1 possibility
    for(firstwhich=0;firstwhich<max;firstwhich++){
	square& sq=checkb.b[firstwhich/N][firstwhich%N];
	if(sq.size()>1 && !sq.is_locked()){
	    // we found first place to change.  Note if locked, there should only
	    // be one, so the check is redundant, but something may change later,
	    // so I code defensively.
	    break;
	}
    }
    BRUTE_CHECK_DEBUG std::cerr << "first firstwhich is " << firstwhich << '\n';

    if(valid){
	BRUTE_CHECK_DEBUG std::cerr << "top of loop outside of while valid\n";
	while((solutions<2||!stopafter2)){
	    while(which!=max){
		row=which/N;
		col=which%N;
		square& whichsq=checkb.b[row][col];
		BRUTE_CHECK_DEBUG std::cerr << "looking at " << whichsq;
		if(!whichsq.is_locked()){
		    // square not locked, so try to deal with it.
		    BRUTE_CHECK_DEBUG std::cerr << "square not locked\n";
		    if(!backed){
			BRUTE_CHECK_DEBUG std::cerr << "backed is false, calling generate_pvals\n";
			checkb.generate_pvals(row,col,false);
			if(which==firstwhich && sols.size()!=0){ //i.e. did we already find one solution
			    BRUTE_CHECK_DEBUG std::cerr << "Pulling values from other solutions from this square: ";
				for(size_t ctr=0;ctr<sols.size();ctr++){
				    whichsq.clear_pval_val(sols[ctr][which]);
				    BRUTE_CHECK_DEBUG std::cerr << ' ' << sols[ctr][which];
				}
				BRUTE_CHECK_DEBUG std::cerr << "--should be pulled now: " << whichsq;
			}
		    }else{
			BRUTE_CHECK_DEBUG std::cerr << "not calling generate_pvals() since backed is true--setting backed back to false\n";
			backed=false;
		    }
		    if(!whichsq.size()){
			BRUTE_CHECK_DEBUG std::cerr << "square has no more pvals, rewinding: " << whichsq;
			// There's no more vals, we'll have to rewind.
			backed=true;
			do{
			    which--;
			    if(which>=0){
				backed_count++;
				row=which/N;
				col=which%N;
				square &whichsq=checkb.b[row][col];
				BRUTE_CHECK_DEBUG std::cerr << "    backed up: now : " << whichsq;
				if(!whichsq.is_locked() && whichsq.size()>1){
				    // backing up we skip locked since we can't
				    // change them, and cells with only one value
				    // since we would have already tried them.
				    // Then on the cell we backed up to, we pull
				    // the // value we tried out of pvals and set
				    // the val to zero so that at the top of the
				    // loop we'll try a different value.
				    BRUTE_CHECK_DEBUG std::cerr << "...found next: " << whichsq << "    -- clearing val from pvals, setting val to 0 and breaking out.\n";
				    whichsq.clear_pval_val(whichsq.get_val());
				    whichsq.set_val(0,false);
				    break;
				}else if(whichsq.size()==1){
				    // n.b. we set val to 0 so generate_pvals will
				    // work correctly, but don't break out, we're
				    // not done backing up.
				    BRUTE_CHECK_DEBUG std::cerr << "...square has one pval, setting val to 0, backing again\n";
				    whichsq.set_val(0,false);
				}else if(whichsq.is_locked()){
				    BRUTE_CHECK_DEBUG std::cerr << "...square locked -- backing again\n";
				}else{
				    // not locked or locked and size <1--shouldn't 
				    // ever happen
				    BRUTE_CHECK_DEBUG std::cerr << "DANGER DANGER WILL ROBINSON\n";
				}
			    }
			}while(which>=0);
			// When we fall out, it's either because which is -1 because we couldn't find a solution,
			// or because we broke because we'd backed to a good candidate for change
			if(which==-1){
			    // we failed and backed up off the front!
			    BRUTE_CHECK_DEBUG{
				std::cerr << "backed off of front\n";
			    }
			    for(++firstwhich;firstwhich<max;firstwhich++){
				square& sq=b[firstwhich/N][firstwhich%N];
				if(sq.size()>1 && !sq.is_locked()){
				    // we found first place to change.  Note if
				    // locked, there should only be one, so the
				    // check is redundant, but something may
				    // change later, so I code defensively.
				    break;
				}
			    }
			    if(firstwhich>=max){
				BRUTE_CHECK_DEBUG std::cerr << "backed up maxed out firstwhich: " << firstwhich << "\n";
				return solutions;
			    }
			    which=0;
			    checkb=*this;
			    backed=false;
			    BRUTE_CHECK_DEBUG{
				std::cerr << "backed off front, firstwhich now: "
				    << firstwhich << " set which to 0 and "
				    << " checkb back to *this\n";
			    }
			}
			continue; // skip incrementing which since we backed or
					// are starting over.
		    } else{
			// target square has pvals try next val
			whichsq.set_val(whichsq[0],false);
		    }
		}
		which++;
		// cell was locked or chose a value, go to next cell
	    } // while(which!=max)
	    if(which==max){
		BRUTE_CHECK_DEBUG std::cerr << "brute check found a potential solution (number: " << solutions+1 << ")\n";
		BRUTE_CHECK_DEBUG checkb.print();
		std::vector<size_t> the_solution;
		for(size_t ctr=0;ctr<N*N;ctr++){
		    the_solution.push_back(checkb.b[ctr/N][ctr%N].get_val());
		}
		BRUTE_CHECK_DEBUG{
		    std::cerr << "looking at solution: \"";
		    for(size_t ctr=0;ctr<the_solution.size();ctr++){
			std::cerr << the_solution[ctr];
		    }
		    std::cerr << "\"\n";
		}
		if(std::find(sols.begin(),sols.end(),the_solution)==sols.end()){
		    BRUTE_CHECK_DEBUG std::cerr << "not already saved\n";
		    sols.push_back(the_solution);
		    solutions++;
		}else{
		    BRUTE_CHECK_DEBUG std::cerr << "already saved\n";
		}
		for(++firstwhich;firstwhich<max;firstwhich++){
		    square& sq=b[firstwhich/N][firstwhich%N];
		    if(sq.size()>1 && !sq.is_locked()){
			// we found first place to change.  Note if
			// locked, there should only be one, so the
			// check is redundant, but something may
			// change later, so I code defensively.
			break;
		    }
		}
		if(firstwhich>=max){
		    BRUTE_CHECK_DEBUG std::cerr << "found solution, maxed out firstwhich: " << firstwhich << '\n';
		    return solutions;
		}
		checkb=*this;
		which=0;
		backed=false;
		BRUTE_CHECK_DEBUG{
		    std::cerr << "after found solution, set firstwhich: "
			<< firstwhich
			<< ", set backed false, checkb to *this, and which 0\n";
		}
	    }
	}
    }
    BRUTE_CHECK_DEBUG std::cerr << "fell off bottom, maxed out firstwhich: " << firstwhich << '\n';
    return solutions;
}

/*!
 * This routine is called back from the various solution strategies so
 * that we can associate a level and a name with each method.
 * \param level intended to be a difficulty level to help with categorizing puzzles
 * \param name whatever name we want to use, things like "x-wing" and "naked triple"
 * \param ssp a pointer to the solution method
 */
template<const unsigned int N>
void
board<N>::register_strategy(size_t level,std::string name,sudoku_method<N>* ssp)
{
    REGISTER_STRATEGY_DEBUG std::cerr << "board<" << N << ">::register_strategy(" << level << ", \"" << name << "\", ssp)\n";
    if(strategies.find(level)==strategies.end()){
	REGISTER_STRATEGY_DEBUG std::cerr << "  creating strategies[" << level << "]\n";
	strategies[level];
    }
    if(strategies[level].find(name)==strategies[level].end()){
	REGISTER_STRATEGY_DEBUG std::cerr << "  creating strategies[" << level << "][\"" << name << "\"]\n";
	strategies[level][name]=ssp;
	REGISTER_STRATEGY_DEBUG std::cerr << "  strategies[" << level << "].size(): " << strategies[level].size() << '\n';
    }
}

/*!
 * For a given level of solution strategies, as specified when registering
 * the strategy, it returns the count of all the times they were 
 * successfully applied where success means that something, either val or
 * pvals changed in one or more squares
 * \param level the level to get the count for
 */
template<const unsigned int N>
size_t
board<N>::get_strategy_counts(size_t level)
{
    size_t retval=0;

    if(strategies.find(level)==strategies.end()){
	return 0;
    }else{
	typename std::map<std::string,class sudoku_method<N>*>::iterator it;
	for(it=strategies[level].begin();it!=strategies[level].end();it++){
	    std::cerr << it->first << " has a count of " << it->second->get_count() << '\n';
	    retval+=it->second->get_count();
	}
	return retval;
    }
}

/*!
 * For a given level of solution strategies, as specified when registering
 * the strategy, it returns the count of all the times they were 
 * successfully applied where success means that something, either val or
 * pvals changed in one or more squares
 */
template<const unsigned int N>
void
board<N>::clear_strategy_counts()
{
    for(size_t ctr=0;ctr<strategies.size();ctr++){
	typename std::map<std::string,class sudoku_method<N>*>::iterator it;
	for(it=strategies[ctr].begin();it!=strategies[ctr].end();it++){
	    it->second->clear_count();
	}
    }
}
#endif
