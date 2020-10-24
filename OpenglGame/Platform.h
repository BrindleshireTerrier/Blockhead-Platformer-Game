#pragma once
#include <vector>



class Platform {

private:

	std::vector<float> points;
	bool isMoving;
	float speed;
	float width;
	float height;
	float xStart;
	float yStart;
	float centerPosX;
	float centerPosY;
	int damage;
	bool hasPlayer;


public: 

	Platform(float width, float height, float xStart, float yStart) {
		this->width = width;
		this->height = height;
		this->xStart = xStart;
		this->yStart = yStart;

		// 0 & 1 contain initial points
		points.push_back(xStart);
		points.push_back(yStart);

		// second vertex 
		points.push_back(xStart);
		points.push_back(yStart + height);

		// third vertex
		points.push_back(xStart + width);
		points.push_back(yStart + height);

		// fourht vertex
		points.push_back(xStart + width);
		points.push_back(yStart);

	}



	// accessor
	inline std::vector<float> getPoints() {
		return points;
	}
	inline bool getIsMoving() {
		return isMoving;
	}
	inline float getSpeed() {
		return speed;
	}
	inline float getWidth() {
		return width;
	}
	inline float getHeight() {
		return height;
	}
	inline float getXStart() {
		return xStart;
	}
	inline float getYStart() {
		return yStart;
	}
	inline float getCenterPosX() {
		this->centerPosX = (this->width - this->xStart) / 2;
		return this->centerPosX;
	}
	inline float getCenterPosY() {
		this->centerPosX = (this->height - this->yStart) / 2;
		return this->centerPosY;
	}

	inline bool getHasPlayer() {
		return this->hasPlayer;
	}
	inline int getDamage() {
		return this->damage;
	}

	// setter
	void setMoving(bool isMoving) {
		this->isMoving = isMoving;
	}
	void setPoints(std::vector<float> points) {
		this->points = points;
	}
	void setSpeed(float speed) {
		this->speed = speed;
	}
	void setWidth(float width) {
		this->width = width;
	}
	void setHeight(float height) {
		this->height = height;
	}
	void setXStart(float xStart) {
		this->xStart = xStart;
	}
	void setYStart(float yStart) {
		this->yStart = yStart;
	}
	void setHasPlayer(bool hasPlayer) {
		this->hasPlayer = hasPlayer;
	}
	void setDamage(int damage) {
		this->damage = damage;
	}

};