#pragma once
#include <glm\vec3.hpp>
#include <mutex>
class Mass {
private:
	float m;
	glm::vec3 position;
	glm::vec3 vel;
	glm::vec3 force;
	mutable std::mutex force_mutex;

public:
	Mass( glm::vec3 pos,float m);
	~Mass();
	void setPosition(glm::vec3 newPosition);
	glm::vec3 getPosition();
	float getMass();
	glm::vec3 getForce();
	glm::vec3 getVel();
	void setVel(glm::vec3);
	void addForce(glm::vec3 f);
	void setForce(glm::vec3 f);
	void update(float dt);
	Mass(const Mass&);
	Mass& operator=(const Mass&);
};
Mass::Mass(glm::vec3 pos,float m) {
	this->m = 1;
	position = pos;
	force = glm::vec3(0.f, 0.f, 0.f);
	vel = glm::vec3(.1f, .5f, .1f);
}
Mass::~Mass(){
}
void Mass::setPosition(glm::vec3 newPosition) {
	position = newPosition;
}
glm::vec3 Mass::getPosition() {
	return position;
}
float Mass::getMass() {
	return m;
}
glm::vec3 Mass::getForce() {
	return force;
}
glm::vec3 Mass::getVel() {
	return vel;
}
void Mass::setVel(glm::vec3 v){
	vel = v;
}
void Mass::addForce(glm::vec3 f) {
	std::lock_guard<std::mutex> lock(force_mutex);
	force += f;
}
void Mass::setForce(glm::vec3 f) {
	force = f;
}

void Mass::update(float dt) {
	glm::vec3 acc = force / m;
	vel += acc * dt;

	position += vel * dt;
	//force = glm::vec3(0.f, -1.f, 0.f);
}

inline Mass::Mass(const Mass& other)
{
	m = other.m;
	force = other.force;
	vel = other.vel;
	position = other.position;
}

inline Mass& Mass::operator=(const Mass& other)
{
	m = other.m;
	force = other.force;
	vel = other.vel;
	position = other.position;
	return *this;
}


