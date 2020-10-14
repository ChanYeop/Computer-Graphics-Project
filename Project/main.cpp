#include <GL/glut.h>
#include <GL/freeglut.h>
#include "GL/glext.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

#include "ObjParser.h"
#include "bmpfuncs.h"
#include "variable.h"
#include "basicfun.h"
#include "crash.h"
#include "draw.h"
#include "game.h"

#define DIMX 32
#define DIMZ 16
#define sizX 200
#define sizZ 200

typedef struct {
	GLfloat x, y, z, yy;
}vec;

vec buf[DIMX + 1][DIMZ + 1];

void Creat_Grid() {
	int x, z;
	double n = 0;
	for (z = 0; z < DIMZ; z++) {
		for (x = 0; x < DIMX; x++) {
			buf[x][z].x = x * sizX / DIMX - sizX / 2;
			buf[x][z].y = sin(n*M_PI / 180) / 2;
			buf[x][z].yy = -4 + sin(n*M_PI / 180) / 3;
			buf[x][z].z = z * sizZ / DIMZ - sizZ / 2;
		}
		n += 360 / DIMX;
	}
}
void ScrollQuad(void) {
	int x, z;
	double tt, tty;
	for (x = 0; x < DIMX; x++) {
		tt = buf[x][0].y;
		tty = buf[x][0].yy;
		for (z = 0; z < DIMZ - 1; z++) {
			buf[x][z].y = buf[x][z + 1].y;
			buf[x][z].yy = buf[x][z + 1].yy;
		}
		buf[x][DIMZ - 1].y = tt;
		buf[x][DIMZ - 1].yy = tty;
	}
}

void idle(void) {
	angle_prop = angle_prop + 1.0;
	if (angle_prop > 360)
		angle_prop -= 360;
	if (menu_state && !menu_off) {
		if (test_tr >= 200) {
			test_tr = 200;
		}
		else {
			test_tr += 3;
		}
	}
	if(menu_state && menu_off) {
		if (test_tr <= 0) {
			test_tr = 0;
			menu_state = false;
			menu_off = false;
		}
		else {
			test_tr -= 3;
		}
	}
	if (fishing_mode) {
		if (arm_move >= 90)
			arm_move = 90;
		else
			arm_move += 2;
	}

	switch (fish1input) {
	case 1:
		if (fish1_move_x >= -30) {
			fish_add = true;
			fish1_move_x= fish1_move_x - 0.5;
		}
		else {
				fish1input = 2;
		}
		break;
	case 2:
		if (fish1_move_x <= 0) {
			fish_add = true;
			fish1_move_x= fish1_move_x + 0.5;
		}
		else {
				fish1input = 1;
		}
		break;
	case 3:
		if (fish1_move_x <= 0) {
			fish1_move_x++;
		}
		else {
			if (fish1_rotate <= 90) {
				fish1_rotate += 2;
			}
			else {
				fish1input = 4;
			}
		}
		break;
	case 4:
		if (fish1_move_z >= 0) {
			fish1_move_z--;
		}
		else {
			if (fish1_rotate >= 0) {
				fish1_rotate -= 2;
			}
			else {
				fish1_rotate = 0;
				fish1input = 1;
			}
		}
		break;
	}
	if (fishing_mode && !fishing_mode2) {
		if (fish_arm1 <= -90) {
			if (fish_arm2 <= -90) {
				fishing_mode2 = true;
			}
			else {
				fish_arm2--;
			}
		}
		else {
			fish_arm1--;
		}
	}
	else if (fishing_mode && fishing_mode2) {
		if (fish_arm2 <= -45) {
			if (fish_arm1 >= 90) {
				if (!succ_fishing) {
					if (sil_state == 27) {
						fish_sphere = true;
						check_fishing = true;
					}
					else {
						sil_state++;
					}
				}
				else {
					emotion = true;
				}
			}
			else {
				fish_arm1+=6;
			}
		}
		else {
			fish_arm2+=6;
		}
	}

	glutPostRedisplay();
}



void init(void) {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glClearDepth(1.0f);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
	glEnable(GL_DEPTH_TEST);

	antialiasing();

	//////////////////////////////////
	light_default();
	per_location();
	fish_location();

	glEnable(GL_TEXTURE_2D);
	skyboxMapping();
	gameboxMapping();
	cubeTextureMapping();
	setTextureMapping();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	///////////////////////////////////
}

void ViewQuad_texture() {
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);

	int x, z;
	float fx, fz;
	fx = (float)1 / DIMX;
	fz = (float)1 / DIMZ;
	for (z = 0; z < DIMZ - 1; z++) {
		for (x = 0; x < DIMX - 1; x++) {
			glBindTexture(GL_TEXTURE_2D, gamefloor);
			glBegin(GL_QUADS);
			glTexCoord2d((float)x*fx, (float)z*fz);
			glVertex3f(buf[x][z].x, buf[x][z].y, buf[x][z].z);

			glTexCoord2d((float)x*fx + fx, (float)z*fz);
			glVertex3f(buf[x + 1][z].x, buf[x + 1][z].y, buf[x + 1][z].z);

			glTexCoord2d((float)x*fx + fx, (float)z*fz + fz);
			glVertex3f(buf[x + 1][z + 1].x, buf[x + 1][z + 1].y, buf[x + 1][z + 1].z);

			glTexCoord2d((float)x*fx, (float)z*fz + fz);
			glVertex3f(buf[x][z + 1].x, buf[x][z + 1].y, buf[x][z + 1].z);
			glEnd();
		}
	}
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_LIGHTING);
}

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	current_width = width;
	current_height = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)width / (double)height, 1, 500);
	glMatrixMode(GL_MODELVIEW);
}


/////////////////////////////////////////////////////


void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	light_default();
	
	if (!gamemode) {
		glPushMatrix();
		glViewport(0, 0, current_width, current_height);
		eyex = radius * sin(theta*M_PI / 180)*cos(phi*M_PI / 180);
		eyey = radius * sin(phi*M_PI / 180);
		eyez = radius * cos(theta*M_PI / 180)*cos(phi*M_PI / 180);
		upVector = cos(phi*M_PI / 180); 
		gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, upVector, 0);

		GLfloat light_position[] = { 0, 40, 0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		draw_skybox();
		glFrontFace(GL_CCW);
		draw_lego();

		glPopMatrix();

		glPushMatrix();
		draw_look();
		glPopMatrix();

		if (menu_state) {
			glPushMatrix();
			draw_text();
			glPopMatrix();
		}
	}
	else {
		
		glPushMatrix();
		glViewport(0, 0, current_width, current_height);
		eyex = game_radius * sin(game_theta*M_PI / 180)*cos(game_phi*M_PI / 180);
		eyey = game_radius * sin(game_phi*M_PI / 180);
		eyez = game_radius * cos(game_theta*M_PI / 180)*cos(game_phi*M_PI / 180);
		upVector = cos(game_phi*M_PI / 180); 

		GLfloat light_position[] = { eyex, eyey, eyez,1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, upVector, 0);

		draw_gamebox();

		glPushMatrix();
		glColor3f(1, 1, 1);
		ScrollQuad();
		ViewQuad_texture();
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();

		glPushMatrix();
		glRotatef(ship_angle, 0, 1, 0);
		glTranslatef(ship_x, ship_y, ship_z);
		glRotatef(-ship_angle, 0, 1, 0);
		glRotatef(ship_angle, 0, 1, 0);
		glPushMatrix();
		
		if (!stick1.empty() && add) {
			per_location();
			stick1[0].x = stick1[0].x + (ship_x*cos(ship_angle));
			stick1[0].z = stick1[0].z + (ship_x * sin(ship_angle));
			add = false;
		}

		draw_game_lego();
		if (object_check && data1_st) {
			glPushMatrix();
			glTranslatef(-5, 8, 0);
			glRotatef(-90, 0, 1, 0);
			draw_flag();
			glPopMatrix();
		}
		if (fish_sphere) {
			glPushMatrix();
			glTranslatef(-1, -20, 15);
			draw_sp();
			glPopMatrix();
		}
		
		glPopMatrix();


		if (person_find && !fishing_mode) {
			glPushMatrix();
			glTranslatef(0, 4, 0);
			draw_person();
			glPopMatrix();
		}

		if (fishing_mode && person_find) {
			glPushMatrix();
			glTranslatef(-1, 4, 3.5);
			glRotatef(90, 0, 1, 0);
			draw_fishing_person();
			glPopMatrix();

		}
		glPopMatrix();
	


		glPushMatrix();
		glTranslatef(0, -50, 0);
		draw_sea(&square);
		glPopMatrix();

		glPushMatrix();
		draw_fish1();
		glPopMatrix();
		/*
		if (mission_state && fin_fish) {
			glPushMatrix();
			glRotatef(-90, 0, 1, 0);
			glTranslatef(8, 0, 3);
			draw_mission_complete();
			glPopMatrix();
		}
		*/
		glPopMatrix();

		glPushMatrix();
		draw_game_text();
		glPopMatrix();

		glPushMatrix();
		draw_mission_text();
		glPopMatrix();

		glPopMatrix();

		if (fishing_mode && person_find && !succ_fishing && check_fishing) {

			for (int i = 0; i < 6; i++) {
				if (fishing_crush(stick1[0], fish_loc[i])) {
					printf("fishing crash\n");
					fish_count++;
					mission_fish_count++;
					succ_fishing = true;
				}
				else
					printf("not fish\n");
			}
		}
	}


	glFlush();
	glutSwapBuffers();
}

void DoTimer2(int value)
{
	if (mission_fish_count == mission_maxmium && fin_fish) {
		if (mission_dr_state == 1 || mission_dr_state == 2 || mission_dr_state == 5 || mission_dr_state == 6 || mission_dr_state == 7 || mission_dr_state == 8) {
			mission_state = true;
			mission_dr_state++;
		}
		else if (mission_dr_state == 3 || mission_dr_state == 4) {
			mission_state = false;
			mission_dr_state++;
		}
		else {
			mission_state = false;
			mission_dr_state = 1;
			mission_fish_count = 0;
			mission_maxmium += 2;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(400, DoTimer2, 1);   
}

void DoTimer3(int value)
{
	if (sil_timer && !susu && side) {
		if (susu_state >= 20) {
			susu = true;
			drop_state = false;
		}
		else {
			drop_state = true;
			susu_state++;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, DoTimer3, 1);
}

void DoTimer4(int value)
{
	if (sil_timer && !susu && !side) {
		if (side_state >= 10) {
			side = true;
		}
		else {
			side_state= side_state + 1;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, DoTimer4, 1);
}

void DoTimer1(int value)
{
	if (emotion) {
		if (emotion_state >= 1) {
			sil_timer = true;
		}
		else {
			emotion_state++;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(80, DoTimer1, 1);  
}

void DoTimer(int value)
{
	if (sil_timer && susu) {
			if (fish_state == 17) {
				emotion = false;
				emotion_state = 0;
				fin_fish = true;
			}
			else {
				fish_state++;
			}
	}
	glutPostRedisplay();
	glutTimerFunc(80, DoTimer, 1);       // 30밀리초마다 호출
}

void DoTimer5(int value)
{
	if (sil_timer && susu) {
		if (sil_state == 3) {
		}
		else {
			fish_sphere = false;
			sil_state--;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, DoTimer5, 1);       // 30밀리초마다 호출
}


////////////////////////파일 저장 //////////////////////////////

/*파일 저장*/
void file_save(int option) {
	if (option == 1) {
		ofstream out("data1.txt", ios::trunc);
		if (out.is_open()) {
			for (int i = 0; i < v1.size(); i++) {
				out << v1[i].angle << endl;
				out << v1[i].color << endl;
				out << v1[i].shape << endl;
				out << v1[i].trans_x << endl;
				out << v1[i].trans_y << endl;
				out << v1[i].trans_z << endl;
				out << v1[i].color_st << endl;
				out << v1[i].texNumber << endl;
			}
			printf("data1 save\n");
		}
		else printf("파일이 없습니다.\n");
		out.close();
	}
	else if (option == 2) {
		ofstream out("data2.txt", ios::trunc);
		if (out.is_open()) {
			for (int i = 0; i < v1.size(); i++) {
				out << v1[i].angle << endl;
				out << v1[i].color << endl;
				out << v1[i].shape << endl;
				out << v1[i].trans_x << endl;
				out << v1[i].trans_y << endl;
				out << v1[i].trans_z << endl;
				out << v1[i].color_st << endl;
				out << v1[i].texNumber << endl;
			}
			printf("data2 save\n");
		}
		else printf("파일이 없습니다.\n");
		out.close();
	}
}

/*파일 불러오기*/
void file_open(int option) {
	if (option == 1) {
		string s;
		printf("입력하세요\n");
		cin >> s;
		ifstream in(s);
		if (in.is_open()) {
			s1.clear();
			for (int i = 0, j = 0;; j++) {
				if (in.eof()) break;
				if (j == 0)
					in >> st.angle;
				if (j == 1)
					in >> st.color;
				if (j == 2)
					in >> st.shape;
				if (j == 3)
					in >> st.trans_x;
				if (j == 4)
					in >> st.trans_y;
				if (j == 5)
					in >> st.trans_z;
				if (j == 6)
					in >> st.color_st;
				if (j == 7)
					in >> st.texNumber;
				if (j == 7) {
					s1.push_back(st);
					j = -1;
				}
			}

			printf("data1 open\n");
			data1_st = true;
			draw();
		}
		else {
			printf("파일이 없습니다.\n");
		}
		in.close();
	}
	else if (option == 2) {
		string s;
		printf("입력하세요\n");
		cin >> s;
		ifstream in(s);
		if (in.is_open()) {
			s1.clear();
			for (int i = 0, j = 0;; j++) {
				if (in.eof()) break;
				if (j == 0)
					in >> st.angle;
				if (j == 1)
					in >> st.color;
				if (j == 2)
					in >> st.shape;
				if (j == 3)
					in >> st.trans_x;
				if (j == 4)
					in >> st.trans_y;
				if (j == 5)
					in >> st.trans_z;
				if (j == 6)
					in >> st.color_st;
				if (j == 7)
					in >> st.texNumber;
				if (j == 7) {
					s1.push_back(st);
					j = -1;
				}
			}

			printf("data2 open\n");
			draw();
		}
		else {
			printf("파일이 없습니다.\n");
		}
		in.close();
	}
}

void sub_menu_function(int option) {
	printf("Submenu %d has been selected\n", option);
	if (option == 1) {
		file_save(1);
	}
	else if (option == 2) {
		file_save(2);
	}
	else if (option == 3) {
	}
	else if (option == 4) {
	}
	glutPostRedisplay();
} //메뉴 처리 함수 

void sub_menu(int option) {
	if (option == 1) {
		file_open(1);
		object_check = true;
	}
	else if (option == 2) {
		file_open(2);
		object_check = true;
	}
	else if (option == 3) {
		person_find = true;
	}
	else if (option == 4) {
	}
	glutPostRedisplay();
}

void main_menu_function(int option) {
	if (option == 11) {
	}
	else if (option == 999) { //999에 해당하는 값이 들어오면 조건문에 들어오게 되고 종료
		exit(0);
	}
	else if (option == 5) {
		//file_save(1);
	}

	else if (option == 6) {
		file_open(1);
	}
	glutPostRedisplay();
} // 메뉴 처리 함수
////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
	//PlaySound(TEXT("not_gamemode.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	
	fish = ("fish.obj");
	lego1_2 = ("propellershape3.obj");
	island = ("island.obj");
	floor_back = ("plane.obj");
	square = ("square.obj");
	leg1 = ("leg1.obj");
	leg2 = ("leg2.obj");
	arm1_1 = ("arm1.obj");
	arm1_2 = ("arm1_2.obj");
	arm2_1 = ("arm2.obj");
	arm2_2 = ("arm2_2.obj");
	body = ("body.obj");
	head = ("head.obj");
	fishing = ("fishing.obj");
	flag = ("flag.obj");
	flagstick = ("flagstick.obj");
	sil1 = ("sil1.obj");
	sil2 = ("sil2.obj");
	sil3 = ("sil3.obj");
	sil4 = ("sil4.obj");
	sil5 = ("sil5.obj");
	sil6 = ("sil6.obj");
	sil7 = ("sil7.obj");
	sil8 = ("sil8.obj");
	sil9 = ("sil9.obj");
	sil10 = ("sil10.obj");

	sil11 = ("sil11.obj");
	sil12 = ("sil12.obj");
	sil13 = ("sil13.obj");
	sil14 = ("sil14.obj");
	sil15 = ("sil15.obj");
	sil16 = ("sil16.obj");
	sil17 = ("sil17.obj");
	sil18 = ("sil18.obj");
	sil19 = ("sil19.obj");
	sil20 = ("sil20.obj");
	sil21 = ("sil21.obj");
	sil22 = ("sil22.obj");
	sil23 = ("sil23.obj");
	sil24 = ("sil24.obj");
	sil25 = ("sil25.obj");
	sil26 = ("sil26.obj");
	sil27 = ("sil27.obj");
	sil28 = ("sil28.obj");

	drop1 = ("drop1.obj");
	drop2 = ("drop2.obj");

	fi_su1 = ("fisi1.obj");
	fi_su2 = ("fisi2.obj");
	fi_su3 = ("fisi3.obj");
	fi_su4 = ("fisi4.obj");
	fi_su5 = ("fisi5.obj");
	fi_su6 = ("fisi6.obj");
	fi_su7 = ("fisi7.obj");

	fi_su8 = ("f1.obj");
	fi_su9 = ("f2.obj");
	fi_su10 = ("f3.obj");
	fi_su11 = ("f4.obj");
	fi_su12 = ("f5.obj");
	fi_su13 = ("f6.obj");
	fi_su14 = ("f7.obj");
	fi_su15 = ("f8.obj");
	fi_su16 = ("f9.obj");
	fi_su17 = ("f10.obj");
	fi_su18 = ("f11.obj");

	emot1 = ("emo1.obj");
	emot2 = ("emo2.obj");

	mission_c1 = ("c1.obj");
	mission_c2 = ("c2.obj");
	mission_u = ("u.obj");
	mission_s1 = ("s1.obj");
	mission_s2 = ("s2.obj");
	mission_s3 = ("s3.obj");
	mission_e = ("e.obj");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Mini_project");
	Creat_Grid();

	
	////////////////////////menu
	int submenu1;
	submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("BOAT1", 1);
	glutAddMenuEntry("BOAT2", 2);

	int submenu2;
	submenu2 = glutCreateMenu(sub_menu);
	glutAddMenuEntry("BOAT1", 1);
	glutAddMenuEntry("BOAT2", 2);
	glutAddMenuEntry("PERSON", 3);

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Quit", 999);
	glutAddMenuEntry("Clear", 11);
	glutAddSubMenu("BOAT_SAVE", submenu1);
	glutAddSubMenu("LOAD", submenu2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	///////////////////////////////////////////
	init();
	glutIdleFunc(idle);
	glutDisplayFunc(draw);
	glutTimerFunc(10, DoTimer, 1);
	glutTimerFunc(10, DoTimer1, 1);
	glutTimerFunc(10, DoTimer2, 1);
	glutTimerFunc(10, DoTimer3, 1);
	glutTimerFunc(10, DoTimer4, 1);
	glutTimerFunc(10, DoTimer5, 1);
	glutPostRedisplay();
	glutReshapeFunc(resize);
	glutMouseWheelFunc(mouseWheel);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	glutMainLoop();
	return 0;
}