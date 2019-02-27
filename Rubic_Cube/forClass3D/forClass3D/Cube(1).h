#pragma once
#include "Mesh.h"
#include <vector> 
#include "translateRotate.h"

class Cube
{
public:

	Cube(Mesh* mesh, int index, translateRotate transRotate);
	void Draw();
	~Cube();
	int getStartIndex();
	glm::mat4 update(float angle);
	glm::mat4 getLastRotation();

	//glm::vec3 getLastTranslate() const;
	void Cube::rotate(glm::mat4 rot, float to_rotate);
	int get_index() { return this->index; }
	void set_index(int x) {
		this->index = x;
	}
	glm::vec3 Cube::getLastTranslate();
	bool rotating = false;



private:
	Mesh* mesh;
	int index;
	float tmp = 0;
	int indexstart;
	glm::mat4 rotation;
	float to_rotate;
	translateRotate transRotate;
};

