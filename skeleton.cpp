/*
 * =====================================================================================
 *
 *       Filename:  skeleton.cpp
 *
 *    Description:  Reads in a .skel file and builds the joints and skeleton 
 *                  tree. Will also control any extra animation of the skeleton 
 *
 *        Version:  1.0
 *        Created:  03/21/2014 08:05:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aaron Caldwell
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

#include "skeleton.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  checkCloseBracket
 *  Description:  Check for matching close bracket
 *    Arguments:  <buf>: The string to look through
 *                <open_pos>: Where to start looking in the string (Must be after 
 *                            known open bracket
 *       Return:  <close_pos>: The position of the close bracket
 * =====================================================================================
 */
size_t checkCloseBracket(string buf, size_t open_pos) {
	size_t close_pos = open_pos;
	int counter = 1;
	while (counter > 0) {
		char c = buf[++close_pos];
		if (c == '}') {
			counter--;
		}
		if (c == '{') {
			counter++;
		}
	}
	return close_pos;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  checkOpenBracket
 *  Description:  Check for matching open bracket
 *    Arguments:  <buf>: The string to look through
 *                <close_pos>: Where to start looking in the string (Must be before
 *                             known close bracket
 *       Return:  <open_pos>: The position of the open bracket
 * =====================================================================================
 */
size_t checkOpenBracket(string buf, size_t close_pos) {
	size_t open_pos = close_pos;
	int counter = 1;
	while (counter > 0) {
		char c = buf[--open_pos];
		if (c == '}') {
			counter++;
		}
		if (c == '{') {
			counter--;
		}
	}
	return open_pos;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  find_joint
 *  Description:  Search for Joint description in provided string, if a child of a node
 *                is found, then we recursivly call this function till we have hit the 
 *                deepest embeded Joint. This will then set up the Child/Parent linking
 *    Arguments:  <text_file>: The .skel file in memory to be searched through
 *                <start>:     Where to start looking in the string
 *                <end>:       Where to finish looking in the string
 *       Return:  <Joint *>:   A pointer to the joint that was just constructed from the
 *                             given .skel file
 * =====================================================================================
 */
Joint * find_joint(string text_file, size_t start, size_t end) {
	
	string name;
	string type;
	vector<float> offset;
	vector<float> boxmin;
	vector<float> boxmax;
	vector<float> rotxlimit;
	vector<float> rotylimit;
	vector<float> rotzlimit;
	vector<float> pose;
	vector<Joint*> children;

    bool child=false;

	int cur_depth = 0;
	int depth = 0;

	size_t pos  = 0;
	// The first line should be the joint type and name
	size_t prev = text_file.find('\n', start) + 1;
	size_t first_brack = text_file.find('{', start); // Find the openening bracket
    size_t start_child = 0;
    size_t end_child = 0;

	// get current node name
    if(first_brack != string::npos) {
        size_t first_sp = text_file.find(' ', start);
        size_t last_sp = text_file.find(' ', first_sp+1);
        name = text_file.substr(first_sp+1, last_sp-first_sp-1);
		size_t strBegin = text_file.find_first_not_of('\t',start);
		type = text_file.substr(strBegin, first_sp-strBegin);
        cur_depth++;
        depth++;
    }
            
	// get just the lines
	while ((pos = text_file.find('\n', prev)) != string::npos) {
	    // Check if we are done looking at this joint
	    if(pos >= end) {
            break;
        }

        // get next line
	    string cur_line = text_file.substr(prev, pos-prev);

	    // Check for if looking at a child of the current joint
	    if((start_child = cur_line.find('{')) != string::npos) {
	        depth++;
	        // If the depth increased only by 1 and a child has not been found
            if((depth-cur_depth) == 1 && !child) {
                // Child joint found
                // get where child node ends
                end_child = checkCloseBracket(text_file, start_child+prev);
                child = true;
                // recursively call to find children of children
                children.push_back(find_joint(text_file, prev, end_child));
            }else if ((depth-cur_depth) == 1 && child) {
                // Done looking at Child
                child = false;
            }

        }
        
        // Check for closing bracket reducing the depth of search
        if(cur_line.find('}') != string::npos) {
            depth--;
            if(child) {
                child = false;
            }
        }

        // If we have not found a Child Joint get this Joints information
        if(depth-cur_depth == 0) { 
            // get joint information
            vector<string> params;
            string word;
            stringstream stream(cur_line);
            while ( getline(stream, word, ' ') ) {
                if(word != "" && word.size() >= 1 ) {
                    params.push_back(word);
                }
            }

            // Fill the appropriate paramaters
            unsigned int i = 1;
            switch (hashit(params[0])) {
                case eOffset:
                    for(i=1; i < params.size(); i++) {
                        offset.push_back(atof(params[i].c_str()));
                    }
                    break;
                case eBoxmin:
                    for(i=1; i<params.size(); i++) {
                        boxmin.push_back(atof(params[i].c_str()));
                    }
                    break;
                case eBoxmax:
                    for(i=1; i<params.size(); i++) {
                        boxmax.push_back(atof(params[i].c_str()));
                    }
                    break;
                case ePose:
                    for(i=1; i<params.size(); i++) {
                        pose.push_back(atof(params[i].c_str()));
                    }
                    break;
                case eRotxlmt:
                    for(i=1; i<params.size(); i++) {
                        rotxlimit.push_back(atof(params[i].c_str()));
                    }
                    break;
                case eRotylmt:
                    for(i=1; i<params.size(); i++) {
                        rotylimit.push_back(atof(params[i].c_str()));
                    }
                    break;
                case eRotzlmt:
                    for(i=1; i<params.size(); i++) {
                        rotzlimit.push_back(atof(params[i].c_str()));
                    }
                    break;
                default:
                    break;
            }
        }

        // Increament prev by pos+1
        prev = pos + 1;
    }
    
    // build joint
    Joint* joint = new Joint(name, type, offset, boxmin, boxmax, rotxlimit, rotylimit, rotzlimit, pose);

    // If children where found, add them to the Joints Child list
	if (children.size() > 0)  {
		joint->set_children(children);
	}

    return joint;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  parseJoints
 *  Description:  Parse out the Joints from the .skel file
 *    Arguments:  <file>: The .skel file
 *       Return:  <Joint *>: Pointer to the root Joint found in the .skel file
 * =====================================================================================
 */
Joint * parseJoints(char * file) {
    string    ifs_file_name = file;               /* input  file name */
    ifstream  ifs;                                /* create ifstream object */

    ifs.open ( ifs_file_name.c_str() );           /* open ifstream */
    if (!ifs) {
        cerr << "\nERROR : failed to open input  file " << ifs_file_name << endl;
        exit (EXIT_FAILURE);
    }
	// Read the entire file into memory
	string s;
	string t;
	while (getline( ifs, t ))
		s += t + '\n';
    ifs.close ();                                 /* close ifstream */
	// find the root joint
    return find_joint(s, 0, s.length());
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Skeleton
 *      Method:  Skeleton :: Skeleton
 * Description:  The constructor of the skeleton object
 *
 *   Arguments:  <filename>: The name of the .skel file
 *--------------------------------------------------------------------------------------
 */
Skeleton::Skeleton(char * filename) {
	root = parseJoints(filename); // Initialize the root Joint
}


ostream& operator<<(ostream& out, Skeleton* s) {
    Joint * r = s->get_root();
    out << r << endl;
    return out;
}
