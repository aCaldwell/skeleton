#include <stdio.h>
#include <iostream>
#include "skeleton.h"
#include "Vector3.h"

using namespace std;

int main(/* int argc, char **argv*/) {
	int i;
	//Skeleton *skel = new Skeleton((char *)"test.skel");

	Vector3<float> vect = Vector3<float>(0.0, 1.0, 0.5);
	Vector3<float> vect1 = Vector3<float>(0.0, -1.0, 0.5);
	Vector3<float> vect2;
	vect2 = vect;

	cout << "Vect is " << vect << endl;
	cout << "Vect1 is " << vect1 << endl;
	cout << "Vect2 is " << vect2 << endl;

	cout << "Vect[0] is " << vect[0] << endl;
	cout << "Vect[1] is " << vect[1] << endl;
	cout << "Vect[2] is " << vect[2] << endl;

	vect.insert(7.1, 1);
	cout << "Vect[1] is " << vect[1] << endl;
	
	vect2+=vect;
	cout << "Vect2 is " << vect2 << endl;




	//Vector3<float> vect2 = vect + vect1;
	//cout << "Vect2 is " << vect2 << endl;

	cin >> i;
	return 0;
}
