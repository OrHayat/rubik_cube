#include "Cube.h"
#include <stdio.h>
#include <glm/gtx/matrix_interpolation.hpp>
#include <iostream>

Cube::Cube(Mesh* mesh, int index, translateRotate transRotate)
{
	this->mesh = mesh;
	this->index = index;
	this->indexstart = index;
	this->transRotate = transRotate;
}

int Cube::getStartIndex() {
	return this->indexstart;
}
void Cube::Draw()
{
	this->mesh->Draw();
}

void Cube::rotate(glm::mat4 rot, float to_rotate) {
	glm::mat4 t = this->transRotate.getRotate();
	this->rotation = t;
	this->transRotate.insertRotate(rot*t);
	this->to_rotate = to_rotate;
	this->tmp = 0;
	this->rotating = true;

}


glm::mat4 Cube::getLastRotation() {
	return this->transRotate.getRotate();
}



glm::mat4 Cube::update(float angle) {
	int sign = 1;
	if (this->to_rotate < 0)
		sign = -1;

	glm::mat4 x = glm::interpolate(this->rotation, this->transRotate.getRotate(), glm::clamp(this->tmp / to_rotate, 0.0f, 1.0f));

	this->tmp += angle*sign;
	if (tmp > this->to_rotate)
		this->rotating = false;
	return x;
}

glm::vec3 Cube::getLastTranslate() {
	return this->transRotate.getTranslet();
}

Cube::~Cube()
{
	delete mesh;
}


