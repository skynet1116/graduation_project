#pragma once
#include <glm\vec3.hpp>
class Mass {
private:
	float m;
	glm::vec3 position;
	glm::vec3 vel;
	glm::vec3 force;
	float dampingRatio=0.f;
public:
	Mass( glm::vec3 pos);
	~Mass();
	void setPosition(glm::vec3 newPosition);
	glm::vec3 getPosition();
	float getMass();
	glm::vec3 getForce();
	glm::vec3 getVel();
	void addForce(glm::vec3 f);

	void setForce(glm::vec3 f);

	void update(float dt);


};
Mass::Mass(glm::vec3 pos) {
	this->m = 1;
	position = pos;
	force = glm::vec3(0.f, 0.f, 0.f);
	vel = glm::vec3(0.f, 0.f, 0.f);
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

void Mass::addForce(glm::vec3 f) {
	force += f;
}
void Mass::setForce(glm::vec3 f) {
	force = f;
}

void Mass::update(float dt) {
	auto dampingForce = dampingRatio * vel;
	force -= dampingForce;
	glm::vec3 acc = force / m;
	vel += acc * dt;
	position += vel * dt;
}
