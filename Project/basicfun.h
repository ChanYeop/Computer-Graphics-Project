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
#include "crash.h"


void light_default() {
	glClearColor(0, 0, 0, 1.0f);

	GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	GLfloat ambient_lego[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse_lego[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular_lego[] = { 0.9f, 0.9f, 0.9f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_lego);
	glMaterialfv(GL_FRONT, GL_AMBIENT, diffuse_lego);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_lego);
	glMateriali(GL_FRONT, GL_SHININESS, 32);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void antialiasing() {
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void setTextureMapping() {
	int imgWidth, imgHeight, channels;
	uchar* img;

	int texNum = 2;
	glGenTextures(texNum, textureName);
	glBindTexture(GL_TEXTURE_2D, textureName[0]);
	img = readImageData("tree.bmp", &imgWidth, &imgHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, textureName[1]);
	img = readImageData("sky.bmp", &imgWidth, &imgHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	texNum = 1;
	glGenTextures(texNum, &texiron);
	glBindTexture(GL_TEXTURE_2D, texiron);
	img = readImageData("iron.bmp", &imgWidth, &imgHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	glGenTextures(texNum, &fish1);
	glBindTexture(GL_TEXTURE_2D, fish1);
	img = readImageData("fish.bmp", &imgWidth, &imgHeight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	img = readImageData("floor.bmp", &imgWidth, &imgHeight, &channels);
	glGenTextures(texNum, &gamefloor);
	glBindTexture(GL_TEXTURE_2D, gamefloor);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	img = readImageData("head3.bmp", &imgWidth, &imgHeight, &channels);
	glGenTextures(texNum, &head_texture);
	glBindTexture(GL_TEXTURE_2D, head_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	img = readImageData("flag2.bmp", &imgWidth, &imgHeight, &channels);
	glGenTextures(texNum, &flagtexture);
	glBindTexture(GL_TEXTURE_2D, flagtexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void motion(int x, int y) {
	printf("Mouse is moving! (%d, %d)\n", x, y);
}

void mouseWheel(int but, int dir, int x, int y)
{
	if (gamemode) {
		if (dir > 0) {
			game_radius--;
		}
		else {
			game_radius++;
		}
	}
	else {
		if (dir > 0) {
			radius--;
			radius2--;
		}
		else {
			radius++;
			radius2++;
		}
	}
	glutPostRedisplay();
}

void setDefault() {
	radius = 10;
	theta = 45.0;
	phi = 45.0;
}

void specialkeyboard(int key, int x, int y) {

	if (gamemode) {
		switch (key) {
		case GLUT_KEY_LEFT:
			game_theta -= 1;
			if (game_theta <= -360) game_theta = 0.0;
			break;
		case GLUT_KEY_RIGHT:
			game_theta += 1;
			if (game_theta >= 360) game_theta = 0.0;
			break;
		case GLUT_KEY_DOWN:
			game_phi -= 1;
			if (abs((int)game_phi) % 360 == 0) game_phi = 0.0;
			break;
		case GLUT_KEY_UP:
			game_phi += 1;
			if (abs((int)game_phi) % 360 == 0) game_phi = 0.0;
			break;
		case 5:
			setDefault();
			break;
		default:
			printf("%d is pressed\n", key);
			break;
		}
	}
	else {
		switch (key) {
		case GLUT_KEY_LEFT:
			theta -= 1;
			if (theta <= -360) theta = 0.0;
			break;
		case GLUT_KEY_RIGHT:
			theta += 1;
			if (theta >= 360) theta = 0.0;
			break;
		case GLUT_KEY_DOWN:
			phi -= 1;
			if (abs((int)phi) % 360 == 0) phi = 0.0;
			break;
		case GLUT_KEY_UP:
			phi += 1;
			if (abs((int)phi) % 360 == 0) phi = 0.0;
			break;
		case 5:
			setDefault();
			break;
		default:
			printf("%d is pressed\n", key);
			break;
		}
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'g') {
		if (gamemode) {
			PlaySound(NULL, 0, 0);
			gamemode = false;
			//PlaySound(TEXT("not_gamemode.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		}
		else {
			PlaySound(NULL, 0, 0);
			gamemode = true;
			PlaySound(TEXT("gamemode.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		}
	}

	if (key == 'y') {
		if (gamemode && fishing_mode) {
			fishing_mode = false;
			emotion = false;
			sil_state = false;
			fishing_mode2 = false;
			add = false;
			fish_add = false;
			succ_fishing = false;
			check_fishing = false;
			sil_state = 0;
			emotion_state = 0;
			fish_state = 0;
			sil_timer = false;
			susu = false;
			susu_state = 0;
			fin_fish = false;
		}

	}

	if (key == 'f') {
		if (fishing_mode)
			fishing_mode = false;
		else
			fishing_mode = true;
	}

	if (key == 'u') {
		if (!v1.empty()) {
			v1.pop_back();
			printf("Undo");
		}
	}

	if (key == 'm') {
		if (!gamemode) {
			if (!menu_state) {
				menu_state = true;
			}
			else if (menu_state && !menu_off) {
				menu_off = true;
			}
		}
	}
	if (key == 'c') {
		if (!gamemode) {
			if (color_state) {
				co++;
				if (co > 9)
					co = 0;
			}
			if (!color_state)
				color_state = true;
		}
	}
	if (key == 't') {
		if (!gamemode) {
			if (!color_state) {
				textureNum++;
				if (textureNum > 2)
					textureNum = 0;
			}
			if (color_state)
				color_state = false;
		}
	}
	if (key == 'z') {
		if (!gamemode) {
			shape1++;
			if (shape1 > 10)
				shape1 = 0;
		}
	}
	if (key == 'i') {
		if (!gamemode) {
			st.shape = shape1;
			st.color_st = color_state;
			if (st.color_st) {
				st.texNumber = 0;
				st.color = co;
			}
			else {
				st.texNumber = textureNum;
				st.color = 0;
			}

			crashinit();
			st.trans_y = 0;
			st.trans_x = 0;
			st.trans_z = 0;
			st.angle = 0;
			int size;

			v1.push_back(st);
		}

	}
	if (key == 'w') {
		if (!gamemode) {
			if (!ypositive) {
				v1[v1.size() - 1].trans_y++;
				v1[v1.size() - 1].y_pos++;
				v1[v1.size() - 1].max_y++;
				v1[v1.size() - 1].min_y++;
				cout << "max x : " << v1[v1.size() - 1].max_x << "   " << "max y : " << v1[v1.size() - 1].max_y << "   " << "max z : " << v1[v1.size() - 1].max_z << endl;
				cout << "min x : " << v1[v1.size() - 1].min_x << "   " << "min y : " << v1[v1.size() - 1].min_y << "   " << "min z : " << v1[v1.size() - 1].min_z << endl;
				if (v1.size() >= 2) {
					for (int j = 0; j < v1.size(); j++) {
						if ((v1.size() - 1) != j) {
							CheckOBBCollision(v1[v1.size() - 1], v1[j]);
							if (CheckOBBCollision(v1[v1.size() - 1], v1[j])) {
								PlaySound(TEXT("block_cr.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
								v1[v1.size() - 1].trans_y = v1[j].trans_y - 2;
								v1[v1.size() - 1].min_y--;
								v1[v1.size() - 1].max_y--;
							}
						}
					}
				}
			}
		}

		else {
			ship_x++;
			add = true;
		}
	}
	if (key == 's') {
		if (!gamemode) {
			if (!ynegative) {
				v1[v1.size() - 1].trans_y--;
				v1[v1.size() - 1].max_y--;
				v1[v1.size() - 1].min_y--;
				v1[v1.size() - 1].y_pos--;
				cout << "max x : " << v1[v1.size() - 1].max_x << "   " << "max y : " << v1[v1.size() - 1].max_y << "   " << "max z : " << v1[v1.size() - 1].max_z << endl;
				cout << "min x : " << v1[v1.size() - 1].min_x << "   " << "min y : " << v1[v1.size() - 1].min_y << "   " << "min z : " << v1[v1.size() - 1].min_z << endl;
				if (v1.size() >= 2) {
					for (int j = 0; j < v1.size(); j++) {
						if ((v1.size() - 1) != j) {
							CheckOBBCollision(v1[v1.size() - 1], v1[j]);
							if (CheckOBBCollision(v1[v1.size() - 1], v1[j])) {
								if (CheckOBBCollision(v1[v1.size() - 1], v1[j])) {
									PlaySound(TEXT("block_cr.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
									v1[v1.size() - 1].trans_y = v1[j].trans_y + 2;
									v1[v1.size() - 1].min_y++;
									v1[v1.size() - 1].max_y++;
								}
							}
						}
					}
				}
			}
		}
		else {
			ship_x--;
			add = true;
		}
	}
	if (key == 'd') {
		if (!gamemode) {
			v1[v1.size() - 1].trans_x++;
			v1[v1.size() - 1].max_x++;
			v1[v1.size() - 1].min_x++;
			v1[v1.size() - 1].x_pos++;
			cout << "max x : " << v1[v1.size() - 1].max_x << "   " << "max y : " << v1[v1.size() - 1].max_y << "   " << "max z : " << v1[v1.size() - 1].max_z << endl;
			cout << "min x : " << v1[v1.size() - 1].min_x << "   " << "min y : " << v1[v1.size() - 1].min_y << "   " << "min z : " << v1[v1.size() - 1].min_z << endl;
			if (v1.size() >= 2) {
				for (int j = 0; j < v1.size(); j++) {
					if ((v1.size() - 1) != j) {
						if (CheckOBBCollision(v1[v1.size() - 1], v1[j])) {
							if (CheckOBBCollision(v1[v1.size() - 1], v1[j])) {
								PlaySound(TEXT("block_cr.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
								v1[v1.size() - 1].trans_x = v1[j].trans_x - (v1[v1.size() - 1].length_x + v1[j].length_x);
								v1[v1.size() - 1].min_x--;
								v1[v1.size() - 1].max_x--;
							}
						}
					}
				}
			}
		}
		else {
			ship_angle += 2;
			if (ship_angle > 360)
				ship_angle = 0;
		}
	}
	if (key == 'a') {
		if (!gamemode) {
			if (!xnegative) {
				v1[v1.size() - 1].trans_x--;
				v1[v1.size() - 1].max_x--;
				v1[v1.size() - 1].min_x--;
				v1[v1.size() - 1].x_pos--;
				cout << "max x : " << v1[v1.size() - 1].max_x << "   " << "max y : " << v1[v1.size() - 1].max_y << "   " << "max z : " << v1[v1.size() - 1].max_z << endl;
				cout << "min x : " << v1[v1.size() - 1].min_x << "   " << "min y : " << v1[v1.size() - 1].min_y << "   " << "min z : " << v1[v1.size() - 1].min_z << endl;
				if (v1.size() >= 2) {
					for (int j = 0; j < v1.size(); j++) {
						if ((v1.size() - 1) != j) {
							if (CheckOBBCollision(v1[v1.size() - 1], v1[j])) {
								PlaySound(TEXT("block_cr.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
								v1[v1.size() - 1].trans_x = v1[j].trans_x + (v1[v1.size() - 1].length_x + v1[j].length_x);
								v1[v1.size() - 1].min_x++;
								v1[v1.size() - 1].max_x++;
							}
						}
					}
				}
			}
		}
		else {
			ship_angle -= 2;
			if (ship_angle < -360)
				ship_angle = 0;
		}
		
	}
	if (key == 'e') {
		if (!gamemode) {
			if (!zpositive) {
				v1[v1.size() - 1].trans_z++;
				v1[v1.size() - 1].max_z++;
				v1[v1.size() - 1].min_z++;
				v1[v1.size() - 1].z_pos++;
				cout << "max x : " << v1[v1.size() - 1].max_x << "   " << "max y : " << v1[v1.size() - 1].max_y << "   " << "max z : " << v1[v1.size() - 1].max_z << endl;
				cout << "min x : " << v1[v1.size() - 1].min_x << "   " << "min y : " << v1[v1.size() - 1].min_y << "   " << "min z : " << v1[v1.size() - 1].min_z << endl;
				if (v1.size() >= 2) {
					for (int j = 0; j < v1.size(); j++) {
						if ((v1.size() - 1) != j) {
							CheckOBBCollision(v1[v1.size() - 1], v1[j]);
							if (CheckOBBCollision(v1[v1.size() - 1], v1[j])) {
								PlaySound(TEXT("block_cr.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
								v1[v1.size() - 1].trans_z = v1[j].trans_z - (v1[v1.size() - 1].length_z + v1[j].length_z);
								v1[v1.size() - 1].min_z--;
								v1[v1.size() - 1].max_z--;
							}
						}
					}
				}
			}
		}
	}
	if (key == 'q') {
		if (!gamemode) {
			if (!znegative) {
				v1[v1.size() - 1].trans_z--;
				v1[v1.size() - 1].max_z--;
				v1[v1.size() - 1].min_z--;
				v1[v1.size() - 1].z_pos--;
				cout << "max x : " << v1[v1.size() - 1].max_x << "   " << "max y : " << v1[v1.size() - 1].max_y << "   " << "max z : " << v1[v1.size() - 1].max_z << endl;
				cout << "min x : " << v1[v1.size() - 1].min_x << "   " << "min y : " << v1[v1.size() - 1].min_y << "   " << "min z : " << v1[v1.size() - 1].min_z << endl;
				if (v1.size() >= 2) {
					for (int j = 0; j < v1.size(); j++) {
						if ((v1.size() - 1) != j) {
							if (CheckOBBCollision(v1[v1.size() - 1], v1[j])) {
								PlaySound(TEXT("block_cr.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
								v1[v1.size() - 1].trans_z = v1[j].trans_z + (v1[v1.size() - 1].length_z + v1[j].length_z);
								v1[v1.size() - 1].min_z++;
								v1[v1.size() - 1].max_z++;
							}
						}
					}
				}
			}
		}
	}
	if (key == 'r') {
		if (!gamemode) {
			v1[v1.size() - 1].angle += 90;
			if (v1[v1.size() - 1].angle > 360)
				v1[v1.size() - 1].angle = 0;

			double change = v1[v1.size() - 1].length_x;
			v1[v1.size() - 1].length_x = v1[v1.size() - 1].length_z;
			v1[v1.size() - 1].length_z = change;

			v1[v1.size() - 1].min_x = v1[v1.size() - 1].x_pos - v1[v1.size() - 1].length_x;
			v1[v1.size() - 1].max_x = v1[v1.size() - 1].x_pos + v1[v1.size() - 1].length_x;
			v1[v1.size() - 1].min_z = v1[v1.size() - 1].z_pos - v1[v1.size() - 1].length_z;
			v1[v1.size() - 1].max_z = v1[v1.size() - 1].z_pos + v1[v1.size() - 1].length_z;

			cout << "max x : " << v1[v1.size() - 1].max_x << "   " << "max y : " << v1[v1.size() - 1].max_y << "   " << "max z : " << v1[v1.size() - 1].max_z << endl;
			cout << "min x : " << v1[v1.size() - 1].min_x << "   " << "min y : " << v1[v1.size() - 1].min_y << "   " << "min z : " << v1[v1.size() - 1].min_z << endl;
			if (v1.size() >= 2) {
				for (int j = 0; j < v1.size(); j++) {
					if ((v1.size() - 1) != j) {
						if (CheckOBBCollision(v1[v1.size() - 1], v1[j]) == true) {
							PlaySound(TEXT("block_cr.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
							v1[v1.size() - 1].min_x = v1[v1.size() - 1].x_pos + v1[v1.size() - 1].length_x;
							v1[v1.size() - 1].max_x = v1[v1.size() - 1].x_pos - v1[v1.size() - 1].length_x;
							v1[v1.size() - 1].min_z = v1[v1.size() - 1].z_pos + v1[v1.size() - 1].length_z;
							v1[v1.size() - 1].max_z = v1[v1.size() - 1].z_pos - v1[v1.size() - 1].length_z;
							v1[v1.size() - 1].angle -= 90;
						}
					}
				}
			}
		}
		else {
			ship_angle += 2;
			if (ship_angle > 360)
				ship_angle = 0;
		}

	}
	if (key == 'p') {
		if (!gamemode) {
			st.trans_y = v1[v1.size() - 1].trans_y;
			st.trans_x = v1[v1.size() - 1].trans_x;
			st.trans_z = v1[v1.size() - 1].trans_z;
			st.angle = v1[v1.size() - 1].angle;
			st.max_x = v1[v1.size() - 1].max_x;
			st.max_y = v1[v1.size() - 1].max_y;
			st.max_z = v1[v1.size() - 1].max_z;
			st.min_x = v1[v1.size() - 1].min_x;
			st.min_y = v1[v1.size() - 1].min_y;
			st.min_z = v1[v1.size() - 1].min_z;
			st.length_x = v1[v1.size() - 1].length_x;
			st.length_y = v1[v1.size() - 1].length_y;
			st.length_z = v1[v1.size() - 1].length_z;
			st.x_pos = v1[v1.size() - 1].x_pos;
			st.y_pos = v1[v1.size() - 1].y_pos;
			st.z_pos = v1[v1.size() - 1].z_pos;
			v1[v1.size() - 1] = st;
			vertexindex++;
		}
	}
}

void fish_location() {
	if (!fish_loc.empty())
		fish_loc.clear();
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			fi.x = 0;
			fi.y = -40;
			fi.z = 0;
			fi.rad = 4;
			fish_loc.push_back(fi);
		}
		
		else if (i == 1) {
			fi.x = -20;
			fi.y = -40;
			fi.z = 20;
			fi.rad = 4;
			fish_loc.push_back(fi);
		}
		else if (i == 2) {
			fi.x = 20;
			fi.y = -40;
			fi.z = 20;
			fi.rad = 4;
			fish_loc.push_back(fi);
		}
		else if (i == 3) {
			fi.x = -20;
			fi.y = -40;
			fi.z = 40;
			fi.rad = 4;
			fish_loc.push_back(fi);
		}
		else if (i == 4) {
			fi.x = 20;
			fi.y = -40;
			fi.z = 40;
			fi.rad = 4;
			fish_loc.push_back(fi);
		}
		else if (i == 5) {
			fi.x = -1;
			fi.y = -20;
			fi.z = 15;
			fi.rad = 4;
			fish_loc.push_back(fi);
		}
		
	}
	
}

void per_location() {
	if (!stick1.empty())
		stick1.clear();
	fi.x = -1;
	fi.y = -20;
	fi.z = 15;
	fi.rad = 4;
	stick1.push_back(fi);
}

bool fishing_crush(f_crush f, f_crush fs) {
	int distance = sqrt(pow((fs.x - f.x), 2) + pow((fs.y - f.y), 2) + pow((fs.z - f.z), 2));
	int r1 = f.rad;
	int r2 = fs.rad;
	if (r1 + r2 >= distance) {
		return true;
	}
	else {
		return false;
	}
}

