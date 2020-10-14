#pragma once
#include "ObjParser.h"
#include "bmpfuncs.h"

#define M_PI       3.14159265358979323846

ObjParser lego[11] = { "1_1 lego.obj","1_2.obj" ,"2_2 lego.obj","4_2 lego.obj","nihun_lego.obj","corn.obj" ,"sphere_round.obj", "cylinender2.obj","cylinender.obj" ,"propellershape1.obj","boat.obj" };
GLuint textureName[2];
GLuint texiron;
GLuint fish1;
GLuint gamefloor;
GLuint head_texture;
GLuint flagtexture;
ObjParser flag;
ObjParser flagstick;
ObjParser lego1_1;
ObjParser island;
ObjParser floor_back;
ObjParser lego1_2;
ObjParser square;
ObjParser fish;
ObjParser fishing;

ObjParser leg1;
ObjParser leg2;
ObjParser arm1_1;
ObjParser arm1_2;
ObjParser arm2_1;
ObjParser arm2_2;
ObjParser body;
ObjParser head;
ObjParser sil1;
ObjParser sil2;
ObjParser sil3;
ObjParser sil4;
ObjParser sil5;
ObjParser sil6;
ObjParser sil7;
ObjParser sil8;
ObjParser sil9;
ObjParser sil10;

ObjParser sil11;
ObjParser sil12;
ObjParser sil13;
ObjParser sil14;
ObjParser sil15;
ObjParser sil16;
ObjParser sil17;
ObjParser sil18;
ObjParser sil19;
ObjParser sil20;
ObjParser sil21;
ObjParser sil22;
ObjParser sil23;
ObjParser sil24;
ObjParser sil25;
ObjParser sil26;
ObjParser sil27;
ObjParser sil28;

ObjParser fi_su1;
ObjParser fi_su2;
ObjParser fi_su3;
ObjParser fi_su4;
ObjParser fi_su5;
ObjParser fi_su6;
ObjParser fi_su7;

ObjParser fi_su8;
ObjParser fi_su9;
ObjParser fi_su10;
ObjParser fi_su11;
ObjParser fi_su12;
ObjParser fi_su13;
ObjParser fi_su14;
ObjParser fi_su15;
ObjParser fi_su16;
ObjParser fi_su17;
ObjParser fi_su18;

ObjParser mission_s1;
ObjParser mission_s2;
ObjParser mission_s3;
ObjParser mission_u;
ObjParser mission_c1;
ObjParser mission_c2;
ObjParser mission_e;

ObjParser emot1;
ObjParser emot2;

ObjParser drop1;
ObjParser drop2;

int fish_arm1 = 0;
int fish_arm2 = 0;
int sil_scale = 0;

double theta = 45.0;
double phi = 45.0;
int radius = 30;
double theta2 = 10.0;
double phi2 = 30.0;
int radius2 = 200;
double game_theta = -7;
double game_phi = 1;
double game_radius = 60;
double upVector = cos(phi*M_PI / 180);
bool gamemode = false;
bool person_find = false;
bool fishing_mode = false;
bool fishing_mode2 = false;
bool object_check = false;

int fish2_move_x = 0;

int arm_move = 0;
bool fish_sphere = false;
bool drop_state = false;

bool color_state = false;
int sil_state = 0;
int co = 0;

struct state {
	int color = 0;
	int shape = 0;
	int trans_x = 0;
	int trans_y = 0;
	int trans_z = 0;
	int angle = 0;
	bool color_st = false;
	int texNumber = 0;
	int min_x = -1;
	int min_y = -1;
	int min_z = -1;
	int max_x = 1;
	int max_y = 1;
	int max_z = 1;
	int length_x = 1;
	int length_y = 1;
	int length_z = 1;
	int x_pos = 0;
	int y_pos = 0;
	int z_pos = 0;
};

struct f_crush {
	float x = 0;
	float y = 0;
	float z = 0;
	int rad = 4;
};

f_crush fi;
vector<f_crush> stick1;
vector<f_crush> fish_loc;

vector<state> v1;
vector<state> s1;
int ship_x = 0;
int ship_y = 0;
int ship_z = 0;
int ship_angle = 0;
int vertexindex = 0;
state st;

int shape1 = 0;
int textureNum = 0;
/* camera location */
double eyex, eyey, eyez;

int angle_prop = 0;

int versave[99999][6] = { 0 };

GLuint g_mCubeTex;
GLuint gamebackground;
GLuint cubebackground[6];
void skyboxMapping();
void gameboxMapping();
void setTextureMapping();
GLUquadricObj* qobj = gluNewQuadric();

GLuint texName3;

int current_width;
int current_height;

float fish1_move_x = 0;
float fish1_move_y = 0;
float fish1_move_z = 0;
int fish1_rotate = 0;
int fish1input = 1;
int fish_count = 0;

int mission_fish_count = 0;
int mission_maxmium = 2;
int mission_dr_state = 1;
bool mission_state = false;


int ywidth = 200;
int xwidth = 100;
int zwidth = 200;

int test_tr = 0;
float menu_alph = 1.0f;
bool menu_state = false;
bool menu_off = false;
bool add = false;
bool fish_add = false;
bool emotion = false;
int emotion_state = 0;

bool xpositive = false;
bool xnegative = false;
bool ypositive = false;
bool ynegative = false;
bool zpositive = false;
bool znegative = false;

bool succ_fishing = false;
bool check_fishing = false;
bool sil_timer = false;
int fish_state = 0;

bool susu = false;
int susu_state = 0;

bool fin_fish = false;

bool side = false;
int side_state = 0;
bool data1_st = false;


//int dist = 0;

float clo[10][3] = {
{ 1.0, 0.0, 0.0 },
{ 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 },
{ 1.0, 0.0, 1.0 },
{ 0.0, 1.0, 1.0 },
{ 0.5, 0.0, 0.5 },
{ 0.0, 0.5, 0.5 },
{ 0.0, 0.0, 0.5 },
{ 0.8, 0.8, 0.8 },
{ 0.0, 0.9, 0.5 },
};


void crashinit();
void light_default();
void antialiasing();
void setTextureMapping();
void draw_string(void * font, const char *str, int x, int y);
void draw_text();
void motion(int x, int y);
void mouseWheel(int but, int dir, int x, int y);
void draw_obj(ObjParser *objParser);
void draw_iron(ObjParser *objParser);
void draw_obj_lego(ObjParser *objParser, int i);
void draw_obj_color(ObjParser *objParser);
void setDefault();
void specialkeyboard(int key, int x, int y);
BOOL CheckOBBCollision(state le1, state le2);
void keyboard(unsigned char key, int x, int y);
void draw_axis(void);
void skyboxMapping();
void gameboxMapping();
void draw_look();
void draw_lego();
void draw_skybox();
void draw_gamebox();
void sub_menu_function(int option);
void main_menu_function(int option);
void cubeTextureMapping();
void draw_textureCube();
void draw_floor(ObjParser *objParser);
void draw_Cube();
void draw_cube_textures();
void game_cube();
bool gluInvertMatrix(const GLfloat m[16], GLfloat invOut[16]);
void draw_game_lego();
void draw_obj_game(ObjParser *objParser, int i);
void draw_person();
void draw_flag();
void draw_line();
void draw_sil();
void fish_location();
void per_location();
bool fishing_crush(f_crush f, f_crush fs);
void draw_succes_fi();
void draw_emotion();
void draw_mission_complete();
void draw_mission_text();
void draw_drop();