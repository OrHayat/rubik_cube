#include "translateRotate.h"
#include <vector>



translateRotate::translateRotate()
{
	insertRotate(glm::mat4());
	}


void translateRotate::insertRotate(glm::mat4 metRotate){
	this->metRotate=metRotate;
}

void translateRotate::insertTranslet(glm::vec3 metTrans) {
	this->metTrans=metTrans;
}

glm::vec3 translateRotate::getTranslet() {
	return this->metTrans;
}

glm::mat4 translateRotate::getRotate() {
	return this->metRotate;
}

translateRotate::~translateRotate()
{
}

