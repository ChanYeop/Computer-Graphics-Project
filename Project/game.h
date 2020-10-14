#pragma once
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "GL/glext.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

#include "ObjParser.h"
#include "bmpfuncs.h"
#include "variable.h"
#include "crash.h"

void gameboxMapping() {
	glGenTextures(1, &gamebackground);
	int width, height, channels;
	uchar * img0 = readImageData("background4.bmp", &width, &height, &channels);
	uchar * img1 = readImageData("background3.bmp", &width, &height, &channels);
	uchar * img2 = readImageData("background6.bmp", &width, &height, &channels);
	uchar * img3 = readImageData("background1.bmp", &width, &height, &channels);
	uchar * img4 = readImageData("background2.bmp", &width, &height, &channels);
	uchar * img5 = readImageData("background5.bmp", &width, &height, &channels);

	glBindTexture(GL_TEXTURE_CUBE_MAP, gamebackground);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);

	glBindTexture(GL_TEXTURE_CUBE_MAP, gamebackground);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);
}


void draw_gamebox() {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, gamebackground);
	float g_nSkySize = 160.0f;
	glBegin(GL_QUADS);
	//px
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
	
	//nx
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	//py
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
	
	//ny
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);

	//pz
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);

	//nz
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);

	glEnd();
}

void draw_floor(ObjParser *objParser) {
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, gamebackground);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}

void draw_cube_textures()
{
	int size = 2;
	glBindTexture(GL_TEXTURE_CUBE_MAP, gamebackground);
	glBegin(GL_QUADS);
	//Quad 1
	glNormal3f(1.0f, 0.0f, 0.0f);   //N1
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
  //Quad 2
	glNormal3f(0.0f, 0.0f, -1.0f);  //N2
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
  //Quad 3
	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
  //Quad 4
	glNormal3f(0.0f, 0.0f, 1.0f);   //N4
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
  //Quad 5
	glNormal3f(0.0f, 1.0f, 0.0f);   //N5
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
  //Quad 6
	glNormal3f(1.0f, -1.0f, 0.0f);  //N6
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glEnd();
}

void game_cube() {
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);

	draw_cube_textures();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
}

void draw_fish1() {

	glPushMatrix();
	glTranslatef((float)fish1_move_x, (float)fish1_move_y, (float)fish1_move_z);

	if (!fish_loc.empty() && fish_add) {
		fish_location();
		for (int i = 0; i < 6; i++) {
			fish_loc[i].x = fish_loc[i].x + fish1_move_x;
		}
		fish_add = false;
	}

	glPushMatrix();
	glTranslatef(0, -40, 0);
	draw_fish(&fish);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-20, -40, 20);
	draw_fish(&fish);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20, -40, 20);
	draw_fish(&fish);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-20, -40, 40);
	draw_fish(&fish);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20, -40, 40);
	draw_fish(&fish);
	glPopMatrix();
	if (!susu) {
		glPushMatrix();
		glTranslatef(-1, -20, 15);
		draw_fish(&fish);
		glPopMatrix();
	}

	glPopMatrix();

}

void draw_obj_game(ObjParser *objParser, int i) {
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, textureName[s1[i].texNumber]);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);


		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}


void draw_game_lego() {
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);

	for (int i = 0; i < s1.size(); i++) {
		if (s1.empty()) {
			continue;
		}
		if (!s1[i].color_st) {
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);
			glPushMatrix();
			glTranslatef(s1[i].trans_x, s1[i].trans_y, s1[i].trans_z);
			glRotatef(s1[i].angle, 0, 1, 0);
			glColor3f(1.f, 1.f, 1.f);
			if (s1[i].shape == 10) {
				glTranslatef(0, 2, 0);
				draw_obj_game(&lego[s1[i].shape], i);
			}
			else {
				draw_obj_game(&lego[s1[i].shape], i);
			}
			if (s1[i].shape == 9) {
				glPushMatrix();
				glRotatef(180, 0, 1, 0);
				glTranslatef(0, 0, 2);
				glRotatef(angle_prop, 0.0, 0.0, 1.0);
				draw_iron(&lego1_2);
				glPopMatrix();
			}

			if (s1[i].shape == 10) {
				glPushMatrix();
				glRotatef(90, 0, 1, 0);
				glTranslatef(0, -2, -11);
				glRotatef(angle_prop, 0.0, 0.0, 1.0);
				draw_iron(&lego1_2);
				glPopMatrix();
			}
			glRotatef(-s1[i].angle, 0, 1, 0);
			glTranslatef(-s1[i].trans_x, -s1[i].trans_y, -s1[i].trans_z);
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslatef(s1[i].trans_x, s1[i].trans_y, s1[i].trans_z);
			glRotatef(s1[i].angle, 0, 1, 0);
			glColor3f(clo[s1[i].color][0], clo[s1[i].color][1], clo[s1[i].color][2]);
			draw_obj_color(&lego[s1[i].shape]);
			glColor3f(1.f, 1.f, 1.f);
			if (s1[i].shape == 9) {
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_LIGHTING);
				glPushMatrix();
				glRotatef(180, 0, 1, 0);
				glTranslatef(0, 0, 2);
				//glTranslatef(0, 0, 0.05);
				glRotatef(angle_prop, 0.0, 0.0, 1.0);
				//glTranslatef(0, 0, -0.05);
				//glRotatef(90, 0.0, 0.0, 1.0);
				draw_iron(&lego1_2);
				glPopMatrix();
			}
			glRotatef(-s1[i].angle, 0, 1, 0);
			glTranslatef(-s1[i].trans_x, -s1[i].trans_y, -s1[i].trans_z);
			glPopMatrix();
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
}

void draw_line() {
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3i(0,60,0);
	glVertex3i(0, 150,0);
	glEnd();
}

void draw_sp() {
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(2, 30, 50);
	glColor3f(1.0f, 1.0f, 1.0f);
}

void draw_person() {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);

	glPushMatrix();

	glPushMatrix();
	glColor3f((float)204 / 255, 0, 0);
	draw_obj_color(&body);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	draw_obj_color(&leg1);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	draw_obj_color(&leg2);
	glColor3f(1, 1, 1);
	glPopMatrix();

	
	glPushMatrix();
	glColor3f(1, 1, 0);
	draw_obj_color(&arm1_1);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	draw_obj_color(&arm1_2);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	draw_obj_color(&arm2_1);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	draw_obj_color(&arm2_2);
	glColor3f(1, 1, 1);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1, 1, 0);
	draw_obj_color(&head);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void draw_fishing_person() {
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);

	glPushMatrix();
	
	glPushMatrix();
	glColor3f((float)204/255, 0, 0);
	draw_obj_color(&body);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	draw_obj_color(&leg1);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	draw_obj_color(&leg2);
	glColor3f(1, 1, 1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 1.3, 0);
	glRotatef(fish_arm2, 0, 0, 1);
	glTranslatef(0, -1.2, 0);
	glColor3f(1, 1, 0);
	draw_obj_color(&arm1_1);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0, 0.9, 0);
	glRotatef(fish_arm1, 0, 0, 1);
	glTranslatef(0, -0.9, 0);
	draw_obj_color(&arm1_2);
	glColor3f(1, 1, 1);
	glColor3f(0.8, 0.8, 0);
	draw_obj_color(&fishing);
	glColor3f(1, 1, 1);

	
	glColor3f(0, 0, 0);
	draw_sil();
	glColor3f(1, 1, 1);
	

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_2D);
	draw_succes_fi();
	draw_emotion();
	draw_drop();
	if (mission_state && fin_fish) {
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glTranslatef(8, 0, 3);
		draw_mission_complete();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);

	glPopMatrix();
	
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	draw_obj_color(&arm2_1);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	draw_obj_color(&arm2_2);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	draw_obj_color(&head);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void draw_mission_complete() {
	glEnable(GL_LIGHTING);
	glPushMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	draw_obj_color(&mission_c1);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	draw_obj_color(&mission_c2);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	draw_obj_color(&mission_s1);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	draw_obj_color(&mission_s2);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	draw_obj_color(&mission_s3);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	draw_obj_color(&mission_u);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	draw_obj_color(&mission_e);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_LIGHTING);
}

void draw_flag() {

	draw_iron(&flagstick);
	glTranslatef(0, 0, -1);
	glRotatef(90, 1, 0, 0);
	draw_flag(&flag);

}

void draw_fishing() {
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	glTranslatef(0, 4.5, 0);
	glColor3f(1, 1, 0);
	draw_head(&fishing);
	
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_TEXTURE_2D);
}

void draw_succes_fi() {
	if (fish_state == 1) {
		glPushMatrix();
		draw_fish(&fi_su8);
		glPopMatrix();
	}
	else if (fish_state == 2) {
		glPushMatrix();
		draw_fish(&fi_su9);
		glPopMatrix();
	}
	else if (fish_state == 3) {
		glPushMatrix();
		draw_fish(&fi_su10);
		glPopMatrix();
	}
	else if (fish_state == 4) {
		glPushMatrix();
		draw_fish(&fi_su11);
		glPopMatrix();
	}
	else if (fish_state == 5) {
		glPushMatrix();
		draw_fish(&fi_su12);
		glPopMatrix();
	}
	else if (fish_state == 6) {
		glPushMatrix();
		draw_fish(&fi_su13);
		glPopMatrix();
	}
	else if (fish_state == 7) {
		glPushMatrix();
		draw_fish(&fi_su14);
		glPopMatrix();
	}
	else if (fish_state == 8) {
		glPushMatrix();
		draw_fish(&fi_su15);
		glPopMatrix();
	}
	else if (fish_state == 9) {
		glPushMatrix();
		draw_fish(&fi_su16);
		glPopMatrix();
	}
	else if (fish_state == 10) {
		glPushMatrix();
		draw_fish(&fi_su17);
		glPopMatrix();
	}
	else if (fish_state == 11) {
		glPushMatrix();
		draw_fish(&fi_su18);
		glPopMatrix();
	}
	else if (fish_state == 11) {
		glPushMatrix();
		draw_fish(&fi_su1);
		glPopMatrix();
	}
	else if (fish_state == 12) {
		glPushMatrix();
		draw_fish(&fi_su2);
		glPopMatrix();
	}
	else if (fish_state == 13) {
		glPushMatrix();
		draw_fish(&fi_su3);
		glPopMatrix();
	}
	else if (fish_state == 14) {
		glPushMatrix();
		draw_fish(&fi_su4);
		glPopMatrix();
	}
	else if (fish_state == 15) {
		glPushMatrix();
		draw_fish(&fi_su5);
		glPopMatrix();
	}
	else if (fish_state == 16) {
		glPushMatrix();
		draw_fish(&fi_su6);
		glPopMatrix();
	}
	else if (fish_state == 17) {
		glPushMatrix();
		draw_fish(&fi_su7);
		glPopMatrix();
	}
}

void draw_emotion() {
	glDisable(GL_LIGHTING);
	if (emotion_state == 1) {
		glPushMatrix();
		glColor3f(1, 0, 0);
		draw_obj_color(&emot1);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
	
}

void draw_drop() {
	//glDisable(GL_LIGHTING);
	if (drop_state) {
		glPushMatrix();
		glColor3f(0, 0, 1);
		draw_obj_color(&drop1);
		glColor3f(1, 1, 1);
		glColor3f(0, 0, 1);
		draw_obj_color(&drop2);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	//glEnable(GL_LIGHTING);

}

void draw_sil() {
	if (sil_state == 1) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	else if (sil_state == 2) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 3) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 4) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 5) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 6) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 7) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 8) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 9) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 10) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 12) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 13) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 14) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if(sil_state == 15) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 16) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 17) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 18) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();

	}
	if (sil_state == 19) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil19);
		glColor3f(1, 1, 1);
		glPopMatrix();

	}
	if (sil_state == 20) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil19);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil20);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 21) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil19);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil20);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil21);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 22) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil19);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil20);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil21);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil22);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 23) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil19);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil20);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil21);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil22);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil23);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (sil_state == 24) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil19);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil20);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil21);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil22);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil23);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil24);
		glColor3f(1, 1, 1);
		glPopMatrix();
		
	}
	if (sil_state == 25) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil19);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil20);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil21);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil22);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil23);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil24);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil25);
		glColor3f(1, 1, 1);
		glPopMatrix();

		
	}
	if (sil_state == 26) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil19);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil20);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil21);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil22);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil23);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil24);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil25);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil26);
		glColor3f(1, 1, 1);
		glPopMatrix();
		
	}
	if (sil_state == 27) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil1);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil2);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil3);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil4);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil5);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil6);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil7);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil8);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil9);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil11);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil12);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil13);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil14);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil15);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil16);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil17);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil18);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil19);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil20);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil21);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil22);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil23);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil24);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil25);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil26);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil27);
		glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
		draw_obj_color(&sil28);
		glColor3f(1, 1, 1);
		glPopMatrix();
		
	}
}


bool gluInvertMatrix(const GLfloat m[16], GLfloat invOut[16])
{
	GLfloat inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;

	return true;
}

void draw_game_text() {
	char sc[50];
	char * s = itoa(fish_count, sc, 10);

	glViewport(500, 470,300, 300);
	glLoadIdentity();
	glPushMatrix();
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, sc, 10, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Total number of fish : ", -5, 0);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glFlush();
}

void draw_mission_text() {
	char sc[50];
	char * s = itoa(mission_fish_count, sc, 10);
	char sc2[50];
	char *a = itoa(mission_maxmium, sc2, 10);

	glViewport(20, 500, 200, 200);
	glLoadIdentity();
	glPushMatrix();
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, sc, 6, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "/", 8, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, sc2, 9, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, ")", 10, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "mission : ( ", -5, 0);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glFlush();
}