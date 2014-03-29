#ifndef __Vector3_INC
#define __Vector3_INC
#include <iostream>

using namespace std;


/* 
 * =====================================================================================
 *        Class:  Vector3
 *  Description:  3D vector class
 * =====================================================================================
 */

template < class T >
class Vector3
{
    public:
        // ====================  LIFECYCLE     =======================================
        Vector3 ();                           /* constructor      */
        Vector3 ( const Vector3 &other ); /* copy constructor */
        ~Vector3 ();                          /* destructor       */

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */

        Vector3& operator = ( const Vector3 &other ); // assignment operator

    protected:
        /* ====================  METHODS       ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */

    private:
        /* ====================  METHODS       ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
        static const int size = 3;
        T *p;

}; /* -----  end of template class Vector3  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Vector3
 *      Method:  Vector3
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Vector3::Vector3 ()
{
    for(int i = 0; i < size; i++ ) {
        p[i] = 0
    }
}  /* -----  end of method Vector3::Vector3  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Vector3
 *      Method:  Vector3
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Vector3::Vector3 ( const Vector3 &other )
{
    for(int i=0; i<size; i++ ){
        p[i] = other.get_p(i);
    }
}  /* -----  end of method Vector3::Vector3  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Vector3
 *      Method:  ~Vector3
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Vector3::~Vector3 ()
{
}  /* -----  end of method Vector3::~Vector3  (destructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Vector3
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
    Vector3&
Vector3::operator = ( const Vector3 &other )
{
    if ( this != &other ) {
        
    }
    return *this;
}  /* -----  end of method Vector3::operator =  (assignment operator)  ----- */


#endif
