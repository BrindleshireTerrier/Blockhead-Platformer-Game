#pragma once


class Entity {

private:

	float posX;
	float centerPosX;
	float centerPosY;
	float posY;
	float width;
	float height;
	float speed;


	

public:


	Entity(float initialPosX, float initialPosY, float speed, float width, float height);
	Entity();




	float getPosX();
	float getPosY();
	float getWidth();
	float getHeight();
	float getSpeed();
	float getSpeedY();
	float getCenterPosX();
	float getCenterPosY();

	void setPosX(float updatedPosX);
	void setPosY(float updatedPosY);
	void setWidth(float updatedWidth);
	void setHeight(float updatedHeight);
	void setSpeed(float updatedSpeed);

};

// constructor
inline Entity::Entity(float initialPosX, float initialPosY, float speed, float width, float height) {
	this->posX = initialPosX;
	this->posY = initialPosY;
	this->speed = speed;
	this->width = width;
	this->height = height;
}
inline Entity::Entity() {
	this->posX = 0.0f;
	this->posY = 0.0f;
	this->speed = 0.005f;
	this->width = 0.0f;
	this->height = 0.0f;
}

// accessors
inline float Entity::getPosX() {
	return this->posX;
}
inline float Entity::getPosY() {
	return this->posY;
}
inline float Entity::getWidth() {
	return this->width;
}
inline float Entity::getHeight() {
	return this->height;
}
inline float Entity::getSpeed() {
	return this->speed;
}
inline float Entity::getCenterPosX() {
	this->centerPosX = (this->width - this->posX) / 2;
	return this->centerPosX;
}
inline float Entity::getCenterPosY() {
	this->centerPosY = (this->height - this->posY) / 2;
	return this->centerPosY;
}


// 
inline void Entity::setPosX(float updatedPosX) {
	this->posX = updatedPosX;
}

inline void Entity::setPosY(float updatedPosY) {
	this->posY = updatedPosY;
}

inline void Entity::setHeight(float updatedHeight) {
	this->height = updatedHeight;
}
inline void Entity::setWidth(float updatedWidth) {
	this->width = updatedWidth;
}
inline void Entity::setSpeed(float updatedSpeed) {
	this->speed = updatedSpeed;
}