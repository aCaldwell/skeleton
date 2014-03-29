/*
 * =====================================================================================
 *
 *       Filename:  skeleton.h
 *
 *    Description:  The skeleton objects header file
 *
 *        Version:  1.0
 *        Created:  03/21/2014 09:59:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aaron Caldwell
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _SKEL_H
#define _SKEL_H
#include "joint.h"
#include <string>


/*
 * =====================================================================================
 *        Class:  Skeleton
 *  Description:  The Skeleton object that the main  program will interactive with, and
 *                will be drawn to the screen.
 * =====================================================================================
 */
class Skeleton {
	private:
		Joint *root;    // A pointer to the root of the Skeleton
	public:
	    Skeleton();                // Default constructor
		Skeleton(char * filename); // Constructor that accepts filename
		~Skeleton();               // Destructor

        // Accessors
        Joint * get_root() const;
        void set_root(Joint *);


		// Overloaded function
       friend ostream& operator<<(ostream&, Skeleton*); 

};

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Skeleton
 *      Method:  get_root
 *--------------------------------------------------------------------------------------
 */
inline Joint *
Skeleton::get_root (  ) const
{
    return root;
}		/* -----  end of method Skeleton::get_root  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Skeleton
 *      Method:  set_root
 *--------------------------------------------------------------------------------------
 */
    inline void
Skeleton::set_root ( Joint * value )
{
    root	= value;
    return ;
}		/* -----  end of method Skeleton::set_root  ----- */

#endif 
