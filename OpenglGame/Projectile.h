#pragma once
#include "Entity.h"


class Projectile : public Entity {

private:

	int damage;
	float accel;
	bool onScreen;
	bool left;


public:

	Projectile(float initialPosX, float initialPosY, float speed, float width, float height, int damage = 1, float accel = 0.0) : Entity(initialPosX = 0.0f, initialPosY = 0.0f, speed = 0.01f, width = 0.0f, height = 0.0f) {
		this->damage = damage;
		this->accel = accel;
	}
	Projectile() : Entity() {
		this->damage = 1;
		this->accel = 0.0f;
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
	float getAccel() {
		return this->accel;
	}

	void setAccel(float accel) {
		this->accel = accel;
	}
	void setOnScreen(bool onScreen) {
		this->onScreen = onScreen;
	}
	void setLeft(bool left) {
		this->left = left;
	}

};



