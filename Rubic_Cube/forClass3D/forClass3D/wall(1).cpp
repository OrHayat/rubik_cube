#include "wall.h"
#include <iostream>

wall::wall(int wallindex[], std::vector<Cube*> *array, int axis, int n)
{
	this->n = n;
	this->wall_index=new std::vector<Cube*>(n*n);
	this->axis = axis;
	this->wallindex = new std::vector<int>(n*n);
	for (int i = 0; i < n*n; i++) {
		this->wallindex->at(i) = wallindex[i];
	}

	this->cube_array = array;
	this->angle = 0;
}

void wall::update()
{

	for (int i = 0; i < n*n;i++)
	{
		wall_index->at(i) = this->cube_array->at(wallindex->at(i));

	}
	}

void wall::rotate1(glm::mat4 rot, float angle) {
	int ns = n*n;
	std::cout << std::endl;
	std::vector<Cube*> tmp = std::vector<Cube*>(ns);
	std::vector<int> indexsint = std::vector<int>(n*n);

	if (!this->lock) {
		int c = 1;
		if (abs(angle) >= 180)
			c = 2;
		update();
		this->angle += angle;

		for (int i = 0; i < ns; i++)
		{
			wall_index->at(i)->rotate(rot, angle);
		}

		for (int l = 0; l < c; l++) {
			if (this->angle >= 90) {
				this->angle -= 90;
				//print_wall();
				//print_array();

				for (int i = 0; i < ns; i++)
				{
					indexsint[i] = wall_index->at(i)->get_index();
				}

				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						tmp.at(i + n * j) = wall_index->at((n - 1) - j + n * i);

					}
				}
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						wall_index->at(i + n * j)->set_index(indexsint[(n - 1) - j + n * i]);

					}
				}

				for (int i = 0; i < ns; i++)
				{
					this->wall_index->at(i) = tmp.at(i);
				}
				for (int i = 0; i < n*n; i++)
				{
					cube_array->at(wallindex->at(i)) = this->wall_index->at(i);

				}
				update();
				//print_wall();
				//print_array();

			}
			if (this->angle <= -90)
			{
				this->angle += 90;
				//print_wall();
				//print_array();

				for (int i = 0; i < ns; i++)
				{
					indexsint[i] = wall_index->at(i)->get_index();
				}
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						tmp.at(i + n*j) = wall_index->at(j + ((n - 1) - i) * n);

					}
				}


				for (int i = 0; i < ns; i++)
				{
					this->wall_index->at(i) = tmp.at(i);
				}
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						wall_index->at(i + (n - 1) * j)->set_index(indexsint[j + ((n - 1) - i) * n]);

					}
				}
				for (int i = 0; i < n*n; i++)
				{
					cube_array->at(wallindex->at(i)) = this->wall_index->at(i);

				}
				
				update();
				//print_wall();
				//print_array();
			}
		}
	}
}

void wall::print_array() {
	std::cout << std::endl;
	std::cout << cube_array->size() << std::endl;
	for (int i = 0; i < cube_array->size(); i++) {
		printf("%.2d  ", i);
	}
	std::cout << std::endl;
	for (int i = 0; i < cube_array->size(); i++) {
		printf("%.2d  ", cube_array->at(i)->getStartIndex());
	}
}

void wall::print_wall() {
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
		{
			std::cout << "wall at index=" << i << "," << j << "=" << wall_index->at(n * i + j)->getStartIndex();
		}
		std::cout << std::endl;
	}
}
bool wall::rotating() {
	for (int i = 0; i < n*n; i++)
	{
		if (this->wall_index->at(i)->rotating)
		{
			return true;
		}
	}
	return false;
}
void wall::swap(Cube* x, Cube* y)
{

	int oldx = x->get_index();
	int oldy = y->get_index();
	x->set_index(oldy);
	y->set_index(oldx);
	this->cube_array->at(oldy) = x;
	this->cube_array->at(oldx) = y;
}


wall::~wall()
{
}
