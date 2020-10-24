#pragma once
#include "Entity.h"


class Enemy : public Entity {

private:

	int damage;
	int health;
	bool onScreen;
	bool left;


public:

	Enemy(float initialPosX, float initialPosY, float speed, float width, float height, int health = 3, int damage = 1) : Entity(initialPosX, initialPosY, speed, width, height) {
		this->damage = damage;
		this->health = health;
	}
	int getDamage() {
		return this->damage;
	}
	bool getOnScreen() {
		return this->onScreen;
	}
	bool getLeft() {
		return this->left;
	}
	float getHealth() {
		return this->health;
	}

	void setHealth(int accel) {
		this->health = health;
	}
	void setOnScreen(bool onScreen) {
		this->onScreen = onScreen;
	}
	void setLeft(bool left) {
		this->left = left;
	}


	void takeHit(int damage) {
		this->health -= damage;
	}
};



