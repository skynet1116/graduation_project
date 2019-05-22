#pragma once
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include "spring.hpp"
#include "mass.hpp"
#include <thread>
#include <functional>

class object {
public:
	glm::vec3 origin;
	std::vector<std::vector<std::vector<Mass>>> mass;
	std::vector<Spring> spring;
	std::vector<Mass*> surface;
	std::vector<glm::vec3> mesh;
	std::vector<unsigned int> EBO;
	float cube_volume;
	std::vector < std::vector<Mass*>> cubes;
	object(glm::vec3);
	void sample(int slice, float step);
	void generateSpring();
	void getEBO();
	void getSurface();
	void getMesh();
	void fall(float,float);
	void getCube();
	void addVCF(float);
	void update(float);
};
object::object(glm::vec3 origin)
{
	this->origin = origin;
}
void object::sample(int slice,float step) {
	std::vector<std::vector<std::vector<Mass>>> 
		temp(slice, std::vector<std::vector<Mass>>(slice, std::vector<Mass>(slice,Mass(origin, 1.f / (slice * slice * slice)))));
	mass = temp;
	for (int i = 0; i < slice; i++) {
		for (int j = 0; j < slice; j++) {
			for (int k = 0; k < slice; k++) {
				glm::vec3 pos = origin + step*glm::vec3((float)i, (float)j, (float)k);
				mass[i][j][k].setPosition(pos);
			}
		}
	}
	

}

void object::getSurface() {
	for (auto i = 0; i < mass.size();i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size()-1;
				if (i == 0) {
					surface.push_back(&mass[i][j][k]);
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (i == size) {
					surface.push_back(&mass[i][j][k]);
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (j == 0) {
					surface.push_back(&mass[i][j][k]);
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (j == size) {
					surface.push_back(&mass[i][j][k]);
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (k == 0) {
					surface.push_back(&mass[i][j][k]);
				}
			}
		}
	}
	for (auto i = 0; i < mass.size(); i++) {
		for (auto j = 0; j < mass.size(); j++) {
			for (auto k = 0; k < mass.size(); k++) {
				auto size = mass.size() - 1;
				if (k == size) {
					surface.push_back(&mass[i][j][k]);
				}
			}
		}
	}
}
void object::getMesh() {
	mesh = {};
	for (auto i : surface) {
		mesh.push_back(i->getPosition());
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
				//edge springs
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i).at(j).at(k + 1), 100.f));
				}
				catch (const std::out_of_range & e) {
				}
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i).at(j+1).at(k), 100.f));
				}
				catch (const std::out_of_range & e) {
				}
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i+1).at(j).at(k), 100.f));
				}
				catch (const std::out_of_range & e) {	
				}
				//face springs
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i).at(j + 1).at(k+1), 100.f));
				}
				catch (const std::out_of_range & e) {
				}
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i + 1).at(j+1).at(k), 100.f));
				}
				catch (const std::out_of_range & e) {
				}
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i + 1).at(j).at(k + 1), 100.f));
				}
				catch (const std::out_of_range & e) {
				}
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i).at(j + 1).at(k - 1), 100.f));
				}
				catch (const std::out_of_range & e) {
				}
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i +1).at(j - 1).at(k), 100.f));
				}
				catch (const std::out_of_range & e) {
				}
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i + 1).at(j).at(k - 1), 100.f));
				}
				catch (const std::out_of_range & e) {
				}
				//inner spring
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i+1).at(j + 1).at(k + 1), 300.f));
				}
				catch (const std::out_of_range & e) {
				}
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i - 1).at(j + 1).at(k + 1), 300.f));
				}
				catch (const std::out_of_range & e) {
				}

				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i - 1).at(j - 1).at(k + 1), 300.f));
				}
				catch (const std::out_of_range & e) {
				}
				try {
					spring.push_back(Spring(&mass.at(i).at(j).at(k), &mass.at(i + 1).at(j - 1).at(k + 1), 300.f));
				}
				catch (const std::out_of_range & e) {
				}
			}
		}
		cube_volume = spring[0].origin_length * spring[0].origin_length * spring[0].origin_length;
	}
	std::cout << "springs: " << spring.size() << std::endl;
}
void object::update(float time_step) {

	int slice = spring.size() / 8;
	auto update_spring = [](std::vector<Spring>::iterator a, std::vector<Spring>::iterator b)
	{
		for (auto i = a; i < b; i++)
		{
			(*i).update();
		}
	};
	auto begin = spring.begin();
	std::thread thread0(update_spring, begin, begin + slice - 1);
	begin += slice;
	std::thread thread1(update_spring, begin, begin + slice - 1);
	begin += slice;
	std::thread thread2(update_spring, begin, begin + slice - 1);
	begin += slice;
	std::thread thread3(update_spring, begin, begin + slice - 1);
	begin += slice;
	std::thread thread4(update_spring, begin, begin + slice - 1);
	begin += slice;
	std::thread thread5(update_spring, begin, begin + slice - 1);
	begin += slice;
	std::thread thread6(update_spring, begin, begin + slice - 1);
	begin += slice;
	std::thread thread7(update_spring, begin, spring.end());
	thread0.join();
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	thread5.join();
	thread6.join();
	thread7.join();
	fall(0.f, 1.f);
	for (auto &i : mass) {
		for (auto &j : i) {
			for (auto &k : j) {
				k.update(time_step);
			}
		}
	}
	mesh = {};
	getMesh();
	for (auto& i : mass) {
		for (auto& j : i) {
			for (auto& k : j) {
				k.setForce(glm::vec3(0.f, -1.f, 0.f)*k.getMass());
			}
		}
	}
	addVCF(1.f);

}
void object::fall(float groundHeight,float mu) {
	for (auto &i : mass) {
		for (auto &j : i) {
			for (auto &k : j) {
				if (k.getPosition().y <= groundHeight) {
					k.setPosition(glm::vec3(k.getPosition().x, groundHeight- k.getPosition().y, k.getPosition().z));
					k.setVel(glm::vec3(k.getVel().x, -1.f*k.getVel().y, k.getVel().z));
					float downForce = std::abs(k.getForce().y);
					k.addForce(glm::vec3(0.f, -downForce, 0.f));
					auto direction = glm::vec3(k.getVel().x, 0.f, k.getVel().z);
					if (glm::length(k.getVel())!=0) {
						auto friction = downForce * mu * (-direction);
						k.addForce(friction);
					}
						
					//k.setForce(glm::vec3(0.f, 0.f, 0.f));
				}
			}
		}
	}
}

void object::getCube()
{
	for (auto i = 0; i < mass.size()-1; i++) {
		for (auto j = 0; j < mass.size()-1; j++) {
			for (auto k = 0; k < mass.size()-1; k++)
			{
				std::vector<Mass*> temp;
				temp.push_back(&(mass[i][j][k]));
				temp.push_back(&(mass[i+1][j][k]));
				temp.push_back(&(mass[i+1][j+1][k]));
				temp.push_back(&(mass[i][j+1][k]));
				temp.push_back(&(mass[i+1][j][k+1]));
				temp.push_back(&(mass[i][j][k+1]));
				temp.push_back(&(mass[i][j+1][k+1]));
				temp.push_back(&(mass[i+1][j+1][k+1]));
				cubes.push_back(temp);
			}
		}
	}
}

void object::addVCF(float k)
{
	for (auto cube:cubes)
	{
		auto x = 0.25f * (
			+ (cube[1]->getPosition() - cube[0]->getPosition())
			+ (cube[3]->getPosition() - cube[2]->getPosition())
			+ (cube[5]->getPosition() - cube[4]->getPosition())
			+ (cube[6]->getPosition() - cube[7]->getPosition())
			);
		auto y = 0.25f * (
			+ (cube[1]->getPosition() - cube[0]->getPosition())
			+ (cube[3]->getPosition() - cube[2]->getPosition())
			+ (cube[3]->getPosition() - cube[2]->getPosition())
			+ (cube[3]->getPosition() - cube[2]->getPosition())
			);
		auto z = 0.25f * (
			+ (cube[1]->getPosition() - cube[0]->getPosition())
			+ (cube[3]->getPosition() - cube[2]->getPosition())
			+ (cube[3]->getPosition() - cube[2]->getPosition())
			+ (cube[3]->getPosition() - cube[2]->getPosition())
			);
		auto v = glm::dot(x, glm::cross(y, z));
		auto deltaVolume = cube_volume - v;
		auto head = -k * deltaVolume / (4 * cube_volume);
		auto first = glm::cross(y, z);
		auto second = glm::cross(z, x);
		auto third = glm::cross(x, y);
		auto f1 = head * (-first - second - third);
		auto f2 = head * (+first - second - third);
		auto f3 = head * (+first + second - third);
		auto f4 = head * (-first + second - third);

		cube[0]->addForce(f1);
		cube[1]->addForce(f2);
		cube[2]->addForce(f3);
		cube[3]->addForce(f4);
		cube[7]->addForce(-f1);
		cube[6]->addForce(-f2);
		cube[5]->addForce(-f3);
		cube[4]->addForce(-f4);
	}
}
template <typename T>
void multThread(std::vector<T> &data,std::function<void(void)> function)
{
	auto begin = data.begin();
	auto end = data.end();
	auto length = end - begin;
	auto slice = length / 8;
	std::thread thread0(function, begin, begin + slice - 1);
	begin += slice;
	std::thread thread1(function, begin, begin + slice - 1);
	begin += slice;
	std::thread thread2(function, begin, begin + slice - 1);
	begin += slice;
	std::thread thread3(function, begin, begin + slice - 1);
	begin += slice;
	std::thread thread4(function, begin, begin + slice - 1);
	begin += slice;
	std::thread thread5(function, begin, begin + slice - 1);
	begin += slice;
	std::thread thread6(function, begin, begin + slice - 1);
	begin += slice;
	std::thread thread7(function, begin, end);
	thread0.join();
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	thread5.join();
	thread6.join();
	thread7.join();

}

