#pragma once
#include <vector>
#include "glm\glm.hpp"


class translateRotate
{
public:
	translateRotate();
	~translateRotate();
	void insertTranslet(glm::vec3 metTrans);
	void insertRotate(glm::mat4 metRotate);
	glm::vec3 getTranslet();
	glm::mat4 getRotate();

private:
	glm::vec3 metTrans = glm::vec3(0, 0, 0);
	glm::mat4 metRotate=glm::mat4();

};

