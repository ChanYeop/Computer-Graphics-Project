#pragma once
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "GL/glext.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "ObjParser.h"
#include "bmpfuncs.h"
#include "variable.h"

void crashinit() {
	if (shape1 == 0) {
		st.min_x = -1;
		st.max_x = 1;
		st.min_y = -1;
		st.max_y = 1;
		st.min_z = -1;
		st.max_z = 1;
		st.length_x = 1;
		st.length_z = 1;
	}
	else if (shape1 == 1) {
		st.min_x = -1;
		st.max_x = 1;
		st.min_y = -1;
		st.max_y = 1;
		st.min_z = -2;
		st.max_z = 2;
		st.length_x = 1;
		st.length_z = 2;
	}
	else if (shape1 == 2) {
		st.min_x = -2;
		st.max_x = 2;
		st.min_y = -1;
		st.max_y = 1;
		st.min_z = -2;
		st.max_z = 2;
		st.length_x = 2;
		st.length_z = 2;
	}
	else if (shape1 == 3) {
		st.min_x = -2;
		st.max_x = 2;
		st.min_y = -1;
		st.max_y = 1;
		st.min_z = -4;
		st.max_z = 4;
		st.length_x = 2;
		st.length_z = 4;
	}
	else if (shape1 == 4) {
		st.min_x = -3;
		st.max_x = 3;
		st.min_y = -2;
		st.max_y = 2;
		st.min_z = -1;
		st.max_z = 1;
		st.length_x = 3;
		st.length_y = 2;
	}
	else if (shape1 == 5) {
		st.min_x = -1;
		st.max_x = 1;
		st.min_y = -1;
		st.max_y = 1;
		st.min_z = -1;
		st.max_z = 1;
		st.length_x = 1;
		st.length_z = 1;
	}
	else if (shape1 == 7) {
		st.min_x = -1;
		st.max_x = 1;
		st.min_y = -2;
		st.max_y = 2;
		st.min_z = -1;
		st.max_z = 1;
		st.length_y = 2;
		st.length_z = 1;
	}
	else if (shape1 == 8) {
		st.min_x = -1;
		st.max_x = 1;
		st.min_y = -1;
		st.max_y = 1;
		st.min_z = -1;
		st.max_z = 1;
		st.length_x = 1;
		st.length_z = 1;
	}
	else if (shape1 == 9) {
		st.min_x = -2;
		st.max_x = 4;
		st.min_y = -2;
		st.max_y = 2;
		st.min_z = -1;
		st.max_z = 1;
		st.length_x = 3;
		st.length_y = 2;
	}
	st.x_pos = (st.min_x + st.max_x) / 2;
	st.y_pos = (st.min_y + st.max_y) / 2;
	st.z_pos = (st.min_z + st.max_z) / 2;
}

BOOL CheckOBBCollision(state le1, state le2) {
	if (((le1.max_y <= le2.max_y) && (le1.max_y >= le2.min_y)) || ((le1.max_y >= le2.max_y) && (le1.min_y <= le2.max_y))) {
		if (((le1.max_z <= le2.max_z) && (le1.max_z >= le2.min_z)) || ((le1.max_z >= le2.max_z) && (le1.min_z <= le2.max_z))) {
			if (((le1.max_x <= le2.max_x) && (le1.max_x >= le2.min_x)) || ((le1.max_x >= le2.max_x) && (le1.min_x <= le2.max_x))) {
				printf("collision\n");
				return true;
			}
		}
	}

	return false;
}

