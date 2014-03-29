/*
 * =====================================================================================
 *
 *       Filename:  joint.cpp
 *
 *    Description:  This is the implementation file of the Joint object
 *
 *        Version:  1.0
 *        Created:  03/20/2014 12:48:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aaron Caldwell, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include "joint.h"

using namespace std;

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  Joint :: Joint
 * Description:  This is the Joint constructor
 *
 *   Arguments:  <nm>: The name of the Joint, this will be the key
 *			     <offset>: The offset of the Joint
 *			     <boxmin>: The min box corner
 *			     <boxmax>: The max box corner
 *			     <x_lim>: The Rotational limits around the X-axis
 *			     <y_lim>: The Rotational limits around the Y-axis
 *			     <z_lim>: The Rotational limits around the Z-axis
 *			     <pose>: Optional pose information 
 *--------------------------------------------------------------------------------------
 */
Joint::Joint(string nm, string type, vector<float> offset,
			 vector<float> boxmin, vector<float> boxmax,
			 vector<float> x_lim, vector<float> y_lim,
			 vector<float>z_lim, vector<float> pose=vector<float>(3,0))
{
	_name = nm;
	_type = type;
	if (offset.size() > 0) {
		_offset = offset;
	} else {
		_offset.assign(3, 0.0);
	}

	if (boxmin.size() > 0) {
		_boxmin = boxmin;
	} else {
		_boxmin.assign(3, -1.0);
	}

	if (boxmax.size() > 0) {
		_boxmax = boxmax;
	} else {
		_boxmax.assign(3, 1.0);
	}

	if (x_lim.size() > 0) {
		_x_limit_min = x_lim[0];
		_x_limit_max = x_lim[1];
	} else {
		_x_limit_min = -100000;
		_x_limit_max =  100000;
	}

	if (y_lim.size() > 0 ) {
		_y_limit_min = y_lim[0];
		_y_limit_max = y_lim[1];
	} else {
		_y_limit_min = -100000;
		_y_limit_max =  100000;
	}

	if (z_lim.size() > 0 ) {
		_z_limit_min = z_lim[0];
		_z_limit_max = z_lim[1];
	} else {
		_z_limit_min = -100000;
		_z_limit_max =  100000;
	}
	
	_pose = pose;
}       /*  -----  end function Joint  -----  */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  Joint :: ~Joint
 * Description:  This is the Joint destructor
 *--------------------------------------------------------------------------------------
 */
Joint::~Joint() { } /*  -----  end function ~Joint  -----  */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  Joint :: get_child_by_name
 * Description:  Get a Child of this Joint by name
 *   Arguments:  <nm>: Name of the child
 *      Return:  <child>: The child of this Joint
 *--------------------------------------------------------------------------------------
 */
Joint *
Joint::get_child_by_name(string nm) {
	int i = 0;
	int num_children = (int)_children.size();

	for (i = 0; i<num_children; i++) {
		Joint *child = _children[i];
		if(child->get_name() == nm){
			return child;
		}
	}

	cout << "Child <" << nm << ">: Not Found." << endl;
	return NULL;
}       /*  -----  end of function get_child_by_name  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Joint
 *      Method:  Joint :: num_children
 * Description:  Get the number of Children of this Joint
 *
 *      Return:  <_children.size>: The number of children of this joint
 *--------------------------------------------------------------------------------------
 */
int
Joint::num_children ( )
{
    return _children.size();
}       /* -----  end of function num_children  ----- */

ostream& operator<<(ostream& out, Joint* j) {
    int i=0;
    vector<float> offset = j->get_offset();
    vector<float> boxmin = j->get_boxmin();
    vector<float> boxmax = j->get_boxmax();
    vector<float> rotxlim = j->get_x_limit();
    vector<float> rotylim = j->get_y_limit();
    vector<float> rotzlim = j->get_z_limit();
    vector<float> pose = j->get_pose();
    int offset_size = (int)offset.size();
    int boxmin_size = (int)boxmin.size();
    int boxmax_size = (int)boxmax.size();
    int pose_size = (int)pose.size();

    out << "\nJoint: " << j->get_name();
	out << " Type: " << j->get_type();
    out << "\n\tOffset: ";
    for(i=0; i<offset_size; i++) {out << offset[i] << " ";}
    out << "\n\tBoxmin: ";
    for(i=0; i<boxmin_size; i++) {out << boxmin[i] << " ";}
    out << "\n\tBoxmax: ";
    for(i=0; i<boxmax_size; i++) {out << boxmax[i] << " ";}
    out << "\n\tx_limit_min: " << rotxlim[0] << " x_limit_max: " << rotxlim[1];
    out << "\n\ty_limit_min: " << rotylim[0] << " y_limit_max: " << rotylim[1];
    out << "\n\tz_limit_min: " << rotzlim[0] << " z_limit_max: " << rotzlim[1];
    out << "\n\tPose: ";
    for(i=0; i<pose_size; i++) {out << pose[i] << " ";}


    int num_child = (int)j->num_children();
    out << "\n\tNumber of Children: " << num_child;

    if(num_child > 0) {
        out << "\n\t" << j->get_name() << " Child(ren):";
        int i;
        
        vector<Joint *> children = j->get_children();
        for ( i = 0; i < num_child; i += 1 ) {
            out << children[i];
        }

        out << "\n\tEnd " << j->get_name() << " Child(ren)";
    }

    
    out << endl;

	return out;
}
