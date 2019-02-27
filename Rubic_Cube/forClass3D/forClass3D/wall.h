#pragma once
#include "Cube.h"
class wall
{
public:
	wall(int wallindex[], std::vector<Cube*> *array, int axis, int n);
	~wall();
	void rotate1(glm::mat4 rotate, float angle);
	void wall::update();
	int axis;
	void print_array();
	void set_direction(bool rotate_direction) { this->rotate_direction = rotate_direction; }
	bool get_lock() { return this->lock; }
	void set_lock(bool lock) { this->lock = lock; }
	float get_angle() {
		return this->angle;
	}
	bool rotating();

private:

	bool lock = false;//not locked
	bool rotate_direction = false;
	std::vector<Cube*> *cube_array;
	void swap(Cube* x, Cube* y);
	std::vector<Cube*> *wall_index;
	void print_wall();
	float angle;
	int n;
	std::vector<int> *wallindex;

};

