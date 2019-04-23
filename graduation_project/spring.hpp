#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "mass.hpp"

class Spring {
public:
	Mass* node_a;
	Mass* node_b;
	float origin_length;
	float current_length;
	float k;
	float dampingRatio=5e-2;
	Spring(Mass* a, Mass* b, float k);
	void deformate(std::vector<glm::vec3>& Fa, std::vector<glm::vec3>& Fb);
	void update();
};
Spring::Spring(Mass* a, Mass* b,  float k) {
	node_a = a;
	node_b = b;
	origin_length = glm::length(a->getPosition()-b->getPosition());
	current_length = origin_length;
	this->k=k;
}
void Spring::deformate(std::vector<glm::vec3>& Fa,std::vector<glm::vec3>& Fb){
	glm::vec3 direction = node_a->getPosition() - node_b->getPosition();
	float force_a=0, force_b=0;
	for (auto force : Fa) {
		float cos_angle = glm::dot(force, direction) / (glm::length(force)*glm::length(direction));
		float f_on_spring = glm::length(force) * cos_angle;
		force_a += f_on_spring;
	}
	for (auto force : Fb) {
		float cos_angle = glm::dot(force, direction) / (glm::length(force)*glm::length(direction));
		float f_on_spring = glm::length(force) * cos_angle;
		force_b += f_on_spring;
	}
	float sumforce = force_b - force_a;
	float delta_length=sumforce / k;
	current_length += delta_length;
	node_a->setPosition(node_a->getPosition() + delta_length / 2);
	node_b->setPosition(node_b->getPosition() + delta_length/2);
	float springForce = delta_length * k;
	node_a->addForce(springForce*direction);
	node_b->addForce(-springForce*direction);
}
void Spring::update() {
	current_length = glm::length(node_a->getPosition() - node_b->getPosition());
	glm::vec3 direction = node_a->getPosition() - node_b->getPosition();

	auto deltaV_a = 0.5f * node_a->getVel() - 0.5f * node_b->getVel();
	auto deltaV_b = 0.5f * node_b->getVel() - 0.5f * node_a->getVel();
	auto dampingForce_a = dampingRatio * deltaV_a;
	auto dampingForce_b = dampingRatio * deltaV_b;

	auto forceOut = k * (current_length-origin_length);
	node_a->addForce(-forceOut*direction);
	node_b->addForce(forceOut * direction);
	if (glm::length(dampingForce_a)<=glm::length(forceOut * direction)) {
		node_a->addForce(-dampingForce_a);
	}
	if (glm::length(dampingForce_b) <= glm::length(forceOut * direction)) {
		node_b->addForce(-dampingForce_b);
	}
}

