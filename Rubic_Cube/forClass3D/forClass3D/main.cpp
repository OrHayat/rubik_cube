#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "inputManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include<vector>
#include "Cube.h"
#include <math.h>
#include "GLFW\glfw3.h"
#include "wall.h"
#include "translateRotate.h"

using namespace glm;

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
float rotate_x = 0;
float rotate_angle = -90.0f;


float rotate_y = 0;
wall* wallT;
wall* wallB;
wall* wallD;
wall* wallR;
wall* wallL;
wall* wallF;
std::vector<Cube*> *array;
bool rotate_direction = false;

wall* wall180 = NULL;
bool rotate180 = false;
float angle180 = -90;
int sign180 = 0;


bool check()
{
	for (int i = 0; i < 27; i++)
	{
		if (i != array->at(i)->getStartIndex())
		{
			return false;
		}
	}
	return true;

}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int sign;
	if (rotate_direction == true)
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	case GLFW_KEY_UP:
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			rotate_y = fmod((rotate_y + 2.9f), 360);
		}
		break;
	case GLFW_KEY_DOWN:
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			rotate_y = fmod((rotate_y - 2.9f), 360);
		}
		break;
	case GLFW_KEY_RIGHT:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			rotate_x = fmod((rotate_x + 2.9f), 360);
		break;
	case GLFW_KEY_LEFT:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			rotate_x = fmod((rotate_x - 2.9f), 360);
		break;

	case GLFW_KEY_R:
		if (action == GLFW_PRESS) {
			if (abs(wallT->get_angle()) < 0.0001 &&
				abs(wallL->get_angle()) < 0.0001&&
				abs(wallB->get_angle()) < 0.0001
				&&abs(wallD->get_angle()) < 0.0001
				&&abs(wallF->get_angle()) < 0.0001) {
				if (rotate_angle >= 180) {
					wallR->rotate1(glm::rotate(-90.0f, vec3(1, 0, 0)), sign*abs(90.0f));
					wallR->rotate1(glm::rotate(-90.0f, vec3(1, 0, 0)), sign*abs(90.0f));
				}
				else {
					wallR->rotate1(glm::rotate(-rotate_angle, vec3(1, 0, 0)), sign*abs(rotate_angle));
				}
			}
		}
		break;


	case GLFW_KEY_L:
		if (action == GLFW_PRESS) {
			if (abs(wallT->get_angle()) < 0.0001 &&
				abs(wallR->get_angle()) < 0.0001&&
				abs(wallB->get_angle()) < 0.0001
				&&abs(wallD->get_angle()) < 0.0001
				&&abs(wallF->get_angle()) < 0.0001) {
				if (rotate_angle >= 180) {
					wallL->rotate1(glm::rotate(90.0f, vec3(1, 0, 0)), sign*abs(90.0f));
					wallL->rotate1(glm::rotate(90.0f, vec3(1, 0, 0)), sign*abs(90.0f));

				}
				else {
					wallL->rotate1(glm::rotate(rotate_angle, vec3(1, 0, 0)), sign* abs(rotate_angle));
				}
			}
		}
		break;


	case GLFW_KEY_U:
		if (action == GLFW_PRESS) {
			if (abs(wallR->get_angle()) < 0.0001 &&
				abs(wallL->get_angle()) < 0.0001&&
				abs(wallB->get_angle()) < 0.0001
				&&abs(wallD->get_angle()) < 0.0001
				&&abs(wallF->get_angle()) < 0.0001) {
				if (abs(rotate_angle) >= 180) {
					wall180 = wallT;
					rotate180 = true;
					angle180 = -90;
					sign180 = sign;
					wallT->rotate1(glm::rotate(90.0f, vec3(0, 1, 0)), sign*abs(90.0f));
					wallT->rotate1(glm::rotate(90.0f, vec3(0, 1, 0)), sign*abs(90.0f));

				}
				else {
					wallT->rotate1(glm::rotate(rotate_angle, vec3(0, 1, 0)), sign*abs(rotate_angle));
				}
			}
		}
		break;


	case GLFW_KEY_D:
		if (action == GLFW_PRESS) {
			if (abs(wallT->get_angle()) < 0.0001 &&
				abs(wallL->get_angle()) < 0.0001&&
				abs(wallB->get_angle()) < 0.0001
				&&abs(wallR->get_angle()) < 0.0001
				&&abs(wallF->get_angle()) < 0.0001) {
				if (rotate_angle >= 180) {
					wallD->rotate1(glm::rotate(-90.0f, vec3(0, 1, 0)), sign*abs(90.0f));
					wallD->rotate1(glm::rotate(-90.0f, vec3(0, 1, 0)), sign*abs(90.0f));

				}
				else {
					wallD->rotate1(glm::rotate(-rotate_angle, vec3(0, 1, 0)), sign*abs(rotate_angle));
				}

			}
		}break;


	case GLFW_KEY_F:
		if (action == GLFW_PRESS) {
			if (abs(wallT->get_angle()) < 0.0001 &&
				abs(wallL->get_angle()) < 0.0001&&
				abs(wallB->get_angle()) < 0.0001
				&&abs(wallD->get_angle()) < 0.0001
				&&abs(wallR->get_angle()) < 0.0001) {
				if (rotate_angle >= 180) {
					wallF->rotate1(glm::rotate(-90.0f, vec3(0, 0, 1)), sign*abs(90.0f));
					wallF->rotate1(glm::rotate(-90.0f, vec3(0, 0, 1)), sign*abs(90.0f));

				}
				else {
					wallF->rotate1(glm::rotate(-rotate_angle, vec3(0, 0, 1)), sign*abs(rotate_angle));
				}
			}
		}
		break;
	case GLFW_KEY_B:
		if (action == GLFW_PRESS) {
			if (abs(wallT->get_angle()) < 0.0001 &&
				abs(wallL->get_angle()) < 0.0001&&
				abs(wallR->get_angle()) < 0.0001
				&&abs(wallD->get_angle()) < 0.0001
				&&abs(wallF->get_angle()) < 0.0001) {
				if (rotate_angle >= 180) {
					wallB->rotate1(glm::rotate(90.0f, vec3(0, 0, 1)), sign*abs(90.0f));
					wallB->rotate1(glm::rotate(90.0f, vec3(0, 0, 1)), sign*abs(90.0f));

				}
				else {
					wallB->rotate1(glm::rotate(rotate_angle, vec3(0, 0, 1)), sign*abs(rotate_angle));

				}
			}
		}
		break;

	case GLFW_KEY_LEFT_CONTROL:
	{if (action == GLFW_PRESS) {
		bool b = check();
		std::cout << std::boolalpha;
		std::cout << b;
		break;
	}
	case GLFW_KEY_Z:
		if (action == GLFW_PRESS) {
			rotate_angle = rotate_angle / 2;
		}
		break;
	}
	case GLFW_KEY_A:
		if (action == GLFW_PRESS) {
			if (rotate_angle * 2 <= -180.0f)
			{
				rotate_angle = -180.0f;
			}
			else if (rotate_angle * 2 >= 180.0f)
			{
				rotate_angle = 180.0f;
			}
			else
			{
				rotate_angle = rotate_angle * 2;
			}
		}
		break;
	case GLFW_KEY_SPACE:
	{
		if (action == GLFW_PRESS)
		{
			rotate_angle *= -1;
			rotate_direction = !rotate_direction;
			wallB->set_direction(rotate_direction);
			wallT->set_direction(rotate_direction);
			wallF->set_direction(rotate_direction);
			wallR->set_direction(rotate_direction);
			wallL->set_direction(rotate_direction);
			wallD->set_direction(rotate_direction);
		}
		break;
	}
	default:
		break;
	}

}



void set_rotate_x(float x)
{
	rotate_x = x;
}
void set_rotate_y(float y)
{
	rotate_y = y;
}



void init(float n)
{
	array= new std::vector<Cube*>(n*n*n);
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	Vertex vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0))
	};

	unsigned int indices[] = { 0, 1, 2,
		0, 2, 3,

		6, 5, 4,
		7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		22, 21, 20,
		23, 22, 20
	};
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Shader shader("./res/shaders/basicShader");
	Mesh mesh1(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	vec3 pos = vec3(0, 0, -20);
	vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
	vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	mat4 P = glm::perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	mat4 M = glm::rotate(0.0f, vec3(1, 1, 1));//glm::mat4(1);
	P = P * glm::lookAt(pos, pos + forward, up);
	mat4 MVP = P*M;
	//MVP =glm::scale(MVP, glm::vec3(0.5f));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				Mesh* m = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
				int index = i + n* (j + n * k);
				translateRotate* trarot = new translateRotate();
				trarot->insertTranslet(vec3((i-(n-1)/2)*-2.0, (j- (n - 1) / 2)*-2.0, (k- (n - 1) / 2)*2.0));
				(*array)[index] = new Cube(m, index, *trarot);
			}
		}
	}

	//FRONT
	if (n == 3) {
		int wallf[] = { 0,1,2,3,4,5,6,7,8 };
		wallF = new wall(wallf, array, 2, 3);
		//BACK
		int wallb[] = { 24,25,26,21,22,23,18,19,20 };
		wallB = new wall(wallb, array, 2, 3);
		//RIGHT
		int wallr[] = { 2,11,20,5,14,23,8,17,26 };

		wallR = new wall(wallr, array, 0, 3);
		//LEFT

		int walll[] = { 18,9,0,21,12,3,24,15,6 };

		wallL = new wall(walll, array, 0, 3);
		//TOP
		int wallt[] = { 18,19,20,9,10,11,0,1,2 };

		wallT = new wall(wallt, array, 1, 3);
		//DOWN
		int walld[] = { 6,7,8,15,16,17,24,25,26 };


		wallD = new wall(walld, array, 1, 3);
	}

	if (n == 2) {
		int wallf[] = { 0,1,2,3};
		wallF = new wall(wallf, array, 2, 2);
		//BACK
		int wallb[] = {5,4,7,6};
		wallB = new wall(wallb, array, 2, 2);
		//RIGHT
		int wallr[] = {1,5,3,7 };

		wallR = new wall(wallr, array, 0, 2);
		//LEFT

		int walll[] = { 4,0,6,2};

		wallL = new wall(walll, array, 0, 2);
		//TOP
		int wallt[] = { 4,5,0,1};

		wallT = new wall(wallt, array, 1, 2);
		//DOWN
		int walld[] = { 6,7,2,3};


		wallD = new wall(walld, array, 1, 2);

	}

	if (n == 4) {
		int wallf[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
		wallF = new wall(wallf, array, 2, 4);
		//BACK
		int wallb[] = {51,50,49,48,55,54,53,52,59,58,57,56,63,62,61,60};
		wallB = new wall(wallb, array, 2, 4);
		//RIGHT
		int wallr[] = {3,19,35,51,7,23,39,55,11,27,43,59,15,31,47,63};

		wallR = new wall(wallr, array, 0, 4);
		//LEFT

		int walll[] = { 48,32,16,0,52,36,20,4,56,40,24,8,60,44,28,12};

		wallL = new wall(walll, array, 0, 4);
		//TOP
		int wallt[] = {48,49,50,51,32,33,34,35,16,17,18,19,0,1,2,3};

		wallT = new wall(wallt, array, 1, 4);
		//DOWN
		int walld[] = {12,13,14,15,28,29,30,31,44,45,46,47,60,61,62,63};


		wallD = new wall(walld, array, 1, 4);

	}

	if (n == 5) {
		int wallf[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
		wallF = new wall(wallf, array, 2, 5);
		//BACK
		int wallb[] = { 104,103,102,101,100,109,108,107,106,105,114,113,112,111,110,119,118,117,116,115,124,123,122,121,120};
		wallB = new wall(wallb, array, 2, 5);
		//RIGHT
		int wallr[] = {4,29,54,79,104,9,34,59,84,109,14,39,64,89,114,19,44,69,94,119,24,49,74,99,124 };

		wallR = new wall(wallr, array, 0, 5);
		//LEFT

		int walll[] = {100,75,50,25,0,105,80,55,30,5,110,85,60,35,10,115,90,65,40,15,120,95,70,45,20};

		wallL = new wall(walll, array, 0, 5);
		//TOP
		int wallt[] = { 100,101,102,103,104,75,76,77,78,79,50,51,52,53,54,25,26,27,28,29,0,1,2,3,4};

		wallT = new wall(wallt, array, 1, 5);
		//DOWN
		int walld[] = {20,21,22,23,24,45,46,47,48,49,70,71,72,73,74,95,96,97,98,99,120,121,122,123,124};


		wallD = new wall(walld, array, 1, 5);

	}





	glfwSetKeyCallback(display.m_window, key_callback);

	shader.Bind();
	while (!glfwWindowShouldClose(display.m_window))
	{
		Sleep(3);
		//M = glm::rotate(M,0.1f,up);
		//MVP = P*M;
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		//mesh.Draw();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					int index = i + n * (j + n * k);
					glm::vec3 x = (array->at(index)->getLastTranslate());
					MVP = P*glm::rotate(rotate_x, vec3(0, 1, 0));
					MVP = MVP*glm::rotate(rotate_y, vec3(1, 0, 0));
					MVP = MVP*array->at(index)->getLastRotation();
					MVP = glm::translate(MVP, x);

					 
						shader.Update(MVP, M);
						array->at(index)->Draw();
					
				}
			}
		}

		//mesh1.Draw();
		//shader.Update(MVP, M);
		//monkey.Draw();

		display.SwapBuffers();
		glfwPollEvents();

	}
	delete wallB;
	delete wallT;
	delete wallL;
	delete wallR;
	delete wallF;
	delete wallD;

}



int main(int argc, char** argv)
{

	init(3);


	return 0;
}
