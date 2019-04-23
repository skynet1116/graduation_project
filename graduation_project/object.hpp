#pragma once
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include "spring.hpp"
#include "mass.hpp"
class object {
public:
	glm::vec3 origin;
	std::vector<std::vector<std::vector<Mass>>> mass;
	std::vector<Spring> spring;
	std::vector<glm::vec3> mesh;
	std::vector<unsigned int> EBO;
	object(glm::vec3);
	void sample(int slice, float step);
	void generateSpring();
	void getEBO();
	void getMesh();
	void update(float);
};
object::object(glm::vec3 origin)
{
	this->origin = origin;
}
void object::sample(int slice,float step) {
	std::vector<std::vector<std::vector<Mass>>> 
		temp(slice, std::vector<std::vector<Mass>>(slice, std::vector<Mass>(slice,Mass(origin))));
	mass = temp;
	for (int i = 0; i < slice; i++) {
		for (int j = 0; j < slice; j++) {
			for (int k = 0; k < slice; k++) {
				glm::vec3 pos = origin + step*glm::vec3((float)i, (float)j, (float)k);
				mass[i][j][k] = Mass(pos);
			}
		}
	}
	

}

void object::getMesh() {
	for (auto i = 0; i < mass.size();i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size()-1;
				if (i == 0) {
					mesh.push_back(mass[i][j][k].getPosition());
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (i == size) {
					mesh.push_back(mass[i][j][k].getPosition());
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (j == 0) {
					mesh.push_back(mass[i][j][k].getPosition());
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (j == size) {
					mesh.push_back(mass[i][j][k].getPosition());
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (k == 0) {
					mesh.push_back(mass[i][j][k].getPosition());
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (k == size) {
					mesh.push_back(mass[i][j][k].getPosition());
				}
			}
		}
	}
}
void object::getEBO() {
	auto size = mass.size();
	unsigned int index = 0;
	for (int t = 0; t < 6; t++) {
		for (int i = 0; i < size-1; i++) {
			for (int j = 0; j < size-1; j++) {
				EBO.push_back(index);
				EBO.push_back(index + 1);
				EBO.push_back(index + size);

				EBO.push_back(index + size);
				EBO.push_back(index + 1);
				EBO.push_back(index + size + 1);
				index += 1;
			}
			index += 1;
		}
		index +=size;
	}
}
void object::generateSpring() {
	for (int i = 0; i < mass.size(); i++) {
		for (int j = 0; j < mass.size(); j++) {
			for (int k = 0; k < mass.size(); k++) {
				if (k + 1 < mass.size())
				{
					spring.push_back(Spring(&mass[i][j][k], &mass[i][j][k + 1], 1));
					std::cout << i << ' ' << j << ' ' << k << std::endl;
					std::cout << i << ' ' << j << ' ' << k+1 << std::endl;
					std::cout << std::endl;
				}
				if (j + 1 < mass.size())
				{
					spring.push_back(Spring(&mass[i][j][k], &mass[i][j + 1][k], 1));
					std::cout << i << ' ' << j << ' ' << k << std::endl;
					std::cout << i << ' ' << j+1 << ' ' << k  << std::endl;
					std::cout << std::endl;
				}
				if (i + 1 < mass.size())
				{
					spring.push_back(Spring(&mass[i][j][k], &mass[i + 1][j][k], 1));
					std::cout << i << ' ' << j << ' ' << k << std::endl;
					std::cout << i +1<< ' ' << j << ' ' << k  << std::endl;
					std::cout << std::endl;
				}
				if (k + 1 < mass.size()&&j+1 < mass.size())
				{
					spring.push_back(Spring(&mass[i][j][k], &mass[i][j+1][k + 1], 1));
					std::cout << i << ' ' << j << ' ' << k << std::endl;
					std::cout << i << ' ' << j +1<< ' ' << k + 1 << std::endl;
					std::cout << std::endl;
				}
				if (k + 1 < mass.size() && i + 1 < mass.size())
				{
					spring.push_back(Spring(&mass[i][j][k], &mass[i+1][j][k + 1], 1));
					std::cout << i << ' ' << j << ' ' << k << std::endl;
					std::cout << i+1 << ' ' << j << ' ' << k + 1 << std::endl;
					std::cout << std::endl;
				}
				if (i + 1 < mass.size() && j + 1 < mass.size())
				{
					spring.push_back(Spring(&mass[i][j][k], &mass[i+1][j + 1][k], 1));
					std::cout << i << ' ' << j << ' ' << k << std::endl;
					std::cout << i+1 << ' ' << j + 1 << ' ' << k<< std::endl;
					std::cout << std::endl;
				}
				if (k + 1 < mass.size() && j + 1 < mass.size()&&i+1<mass.size())
				{
					spring.push_back(Spring(&mass[i][j][k], &mass[i+1][j+1][k + 1], 1));
					std::cout << i << ' ' << j << ' ' << k << std::endl;
					std::cout << i + 1 << ' ' << j + 1 << ' ' << k + 1 << std::endl;
					std::cout << std::endl;
				}
			}
		}
	}
}
void object::update(float time_step) {
	for (auto i : spring) {
		i.update();
	}
	for (auto &i : mass) {
		for (auto &j : i) {
			for (auto &k : j) {
				k.update(time_step);
				//std::cout << k.getPosition().x << " " << k.getPosition().y << " " << k.getPosition().z << " " << std::endl;
			}
		}
	}
	mesh = {};
	getMesh();
}