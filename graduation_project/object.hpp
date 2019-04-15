#pragma once
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include "spring.hpp"
#include "mass.hpp"
class object {
public:
	glm::vec3 origin;
	std::vector<Mass> mass;
	std::vector<Spring> spring;
	std::vector<int> EBO;
	object(glm::vec3);
	void sample(int slice, float step);

};
object::object(glm::vec3 origin)
{
	this->origin = origin;
}
void object::sample(int slice,float step) {
	glm::vec3 x(1.f, 0.f, 0.f);
	glm::vec3 y(0.f, 1.f, 0.f);
	glm::vec3 z(0.f, 0.f, 1.f);

	mass = {Mass(origin)};
	for (int i = 0; i < slice; i++) {
		for (auto j : { x,y,z }) {
			origin +=j*step;
			mass.push_back(Mass(origin + x * step));
			spring.push_back(Spring(&mass.back(),&Mass(origin),1));
			mass.push_back(Mass(origin + y * step));
			spring.push_back(Spring(&mass.back(), &Mass(origin), 1));
			mass.push_back(Mass(origin + z * step));
			spring.push_back(Spring(&mass.back(), &Mass(origin), 1));

			mass.push_back(Mass(origin + (x+y) * step));
			spring.push_back(Spring(&mass.back(), &Mass(origin), 1));
			mass.push_back(Mass(origin + (x+z) * step));
			spring.push_back(Spring(&mass.back(), &Mass(origin), 1));
			mass.push_back(Mass(origin + (y+z) * step));
			spring.push_back(Spring(&mass.back(), &Mass(origin), 1));

			mass.push_back(Mass(origin + (x+y+z) * step));
			spring.push_back(Spring(&mass.back(), &Mass(origin), 1));
			spring.push_back(Spring(&mass[mass.size()-3], &Mass(mass[mass.size()-6]), 1));

		}
			
	}


}