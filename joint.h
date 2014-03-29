/*
 * =====================================================================================
 *
 *       Filename:  joint.h
 *
 *    Description:  Implementation of the Joints of a Skeleton to be used in OpenGL 
 *                  Animation
 *
 *        Version:  1.0
 *        Created:  03/21/2014 07:44:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aaron Caldwell
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _JOINT_H
#define _JOINT_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;


enum param_code {
    eOffset,
    eBoxmin,
    eBoxmax,
    ePose,
    eRotxlmt,
    eRotylmt,
    eRotzlmt,
    eNone
};               /* ----------  end of enum param_code  ---------- */

typedef enum param_code Param_code;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  hashit
 *  Description:  Hash given string to enum types
 *    Arguments:  <in_string>: string to hash
 *       Return:  <param_code>: The hash value of the string
 * =====================================================================================
 */
inline param_code
hashit ( string const& in_string )
{
    if((in_string.find("offset")) != string::npos) return eOffset;
    if((in_string.find("boxmin")) != string::npos) return eBoxmin;
    if((in_string.find("boxmax")) != string::npos) return eBoxmax;
    if((in_string.find("pose")) != string::npos) return ePose;
    if((in_string.find("rotxlimit")) != string::npos) return eRotxlmt;
    if((in_string.find("rotylimit")) != string::npos) return eRotylmt;
    if((in_string.find("rotzlimit")) != string::npos) return eRotzlmt;
    return eNone;
}       /* -----  end of function hashit  ----- */


/*
 * =====================================================================================
 *        Class:  Joint
 *  Description:  Individual Joints of the skeleton
 * =====================================================================================
 */
class Joint {
	private:
		string _name;             // The name of the joint,
		string _type;
		vector<float> _offset;    // The joint offset from the root
		vector<float> _boxmin;    // The box min corner of the joint
		vector<float> _boxmax;    // The box max corner of the joint
		float _x_limit_min;       // The min x rotation limit
		float _x_limit_max;       // The max x rotation limit
		float _y_limit_min;       // The min y rotation limit
		float _y_limit_max;       // The max y rotation limit
		float _z_limit_min;       // The min z rotation limit
		float _z_limit_max;       // The max z rotation limit
		vector<float> _pose;      // the optional pose information
		vector<Joint*> _children; // The children of this joint
		Joint *_parent;           // The parent of this joint, possibly itself

	public:
	    // Constructor
	    Joint();
		Joint(string, string, vector<float>, vector<float>, vector<float>,
			  vector<float>, vector<float>, vector<float>, vector<float>);
		// Destructor
		~Joint();

		// Joint Methods

		string get_name() const;                  // Get the Joint name
		void set_name(string);		              // Set the Joint name
		string get_type() const;                  // Get the Joint type
		void set_type(string);		              // Set the Joint type
		vector<Joint*> get_children() const;      // Get the Children of this Joint
		void set_children(vector<Joint *>);		  // Set the Children of this Joint
		vector<float> get_offset() const;		  // Get the Joint offset
		void set_offset(vector<float>);			  // Set offset of this Joint
		vector<float> get_boxmin() const;		  // Get the Joint boxmin
		void set_boxmin(vector<float>);			  // Set boxmin of this Joint
		vector<float> get_boxmax() const;		  // Get the Joint boxmax
		void set_boxmax(vector<float>);			  // Set boxmax of this Joint
		vector<float> get_x_limit() const;	      // Get the Joint x rotation limits
		void set_x_limit(vector<float>);		  // Set x rotation limit of this Joint
		vector<float> get_y_limit() const;	      // Get the Joint y rotation limits
		void set_y_limit(vector<float>);		  // Set y rotation limit of this Joint
		vector<float> get_z_limit() const;	      // Get the Joint z rotation limits
		void set_z_limit(vector<float>);          // Set z rotation limit of this Joint
		vector<float> get_pose() const;		      // Get the Joint pose
		void set_pose(vector<float>);             // Set pose of this Joint

		Joint * get_parent();			   // Get the Parent of the Joint
		Joint * get_child_by_name(string); // Get Child of this Joint by name
		void add_child(Joint *);           // Add child to this joint
		void add_parent(Joint *);          // Add Parent to child

		int num_children();                // Get the number of Children that belong to this Joint

		// Overloaded functions
		friend ostream& operator<<(ostream&, Joint*);

};

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get _name
 *--------------------------------------------------------------------------------------
 */
inline string
Joint::get_name (  ) const
{
    return _name;
}		/* -----  end of method Joint::get_name  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set _name
 *--------------------------------------------------------------------------------------
 */
inline void
Joint::set_name ( string value )
{
    _name	= value;
    return ;
}		/* -----  end of method Joint::set_name  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get _type
 *--------------------------------------------------------------------------------------
 */
inline string
Joint::get_type (  ) const
{
    return _type;
}		/* -----  end of method Joint::get_type  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set _type
 *--------------------------------------------------------------------------------------
 */
inline void
Joint::set_type ( string value )
{
    _type	= value;
    return ;
}		/* -----  end of method Joint::set_name  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get _children
 *--------------------------------------------------------------------------------------
 */
inline vector<Joint *>
Joint::get_children (  ) const
{
    return _children;
}		/* -----  end of method Joint::get_children  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set _children
 *--------------------------------------------------------------------------------------
 */
    inline void
Joint::set_children ( vector<Joint *> value )
{
    int i = 0;
    int num = value.size();
    for ( i = 0; i < num; i += 1 ) {
        _children.push_back(value[i]);
    }
    return ;
}		/* -----  end of method Joint::set_children  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get_offset
 *--------------------------------------------------------------------------------------
 */
inline vector<float>
Joint::get_offset (  ) const
{
    return _offset;
}		/* -----  end of method Joint::get_offset  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set_offset
 *--------------------------------------------------------------------------------------
 */
inline void
Joint::set_offset ( vector<float> value )
{
    _offset	= value;
    return ;
}		/* -----  end of method Joint::set_offset  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get_boxmin
 *--------------------------------------------------------------------------------------
 */
inline vector<float>
Joint::get_boxmin (  ) const
{
    return _boxmin;
}		/* -----  end of method Joint::get_boxmin  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set_boxmin
 *--------------------------------------------------------------------------------------
 */
    inline void
Joint::set_boxmin ( vector<float> value )
{
    _boxmin	= value;
    return ;
}		/* -----  end of method Joint::set_boxmin  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get_boxmax
 *--------------------------------------------------------------------------------------
 */
inline vector<float>
Joint::get_boxmax (  ) const
{
    return _boxmax;
}		/* -----  end of method Joint::get_boxmax  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set_boxmax
 *--------------------------------------------------------------------------------------
 */
    inline void
Joint::set_boxmax ( vector<float> value )
{
    _boxmax	= value;
    return ;
}		/* -----  end of method Joint::set_boxmax  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get_x_limit
 *--------------------------------------------------------------------------------------
 */
inline vector<float>
Joint::get_x_limit (  ) const
{
    vector<float> x_limit;
    x_limit.push_back(_x_limit_min);
    x_limit.push_back(_x_limit_max);
    return x_limit;
}		/* -----  end of method Joint::get_x_limit  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set_x_limit
 *--------------------------------------------------------------------------------------
 */
    inline void
Joint::set_x_limit ( vector<float> value )
{
	_x_limit_min = value[0];
	_x_limit_max = value[1];
    return ;
}		/* -----  end of method Joint::set_x_limit  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get_y_limit
 *--------------------------------------------------------------------------------------
 */
inline vector<float>
Joint::get_y_limit (  ) const
{
    vector<float> y_limit;
    y_limit.push_back(_y_limit_min);
    y_limit.push_back(_y_limit_max);
    return y_limit;
}		/* -----  end of method Joint::get_y_limit  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set_y_limit
 *--------------------------------------------------------------------------------------
 */
inline void
Joint::set_y_limit ( vector<float> value )
{
	_y_limit_min = value[0];
	_y_limit_max = value[1];
    return ;
}		/* -----  end of method Joint::set_y_limit  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get_z_limit
 *--------------------------------------------------------------------------------------
 */
inline vector<float>
Joint::get_z_limit (  ) const
{
    vector<float> z_limit;
    z_limit.push_back(_z_limit_min);
    z_limit.push_back(_z_limit_max);
    return z_limit;
}		/* -----  end of method Joint::get_z_limit  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set_z_limit
 *--------------------------------------------------------------------------------------
 */
inline void
Joint::set_z_limit ( vector<float> value )
{
	_z_limit_min = value[0];
	_z_limit_max = value[1];
    return ;
}		/* -----  end of method Joint::set_y_limit  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  get_boxmax
 *--------------------------------------------------------------------------------------
 */
inline vector<float>
Joint::get_pose (  ) const
{
    return _pose;
}		/* -----  end of method Joint::get_pose  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  set_pose
 *--------------------------------------------------------------------------------------
 */
    inline void
Joint::set_pose ( vector<float> value )
{
    _pose	= value;
    return ;
}		/* -----  end of method Joint::set_pose  ----- */

#endif
