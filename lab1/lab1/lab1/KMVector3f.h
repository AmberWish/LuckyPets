#pragma once

class KMVector3f
{
public:
	KMVector3f();
	KMVector3f(float x, float y, float z, float w);
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	float getZ();
	void setZ(float z);
	float getW();
	void setW(float w);
	KMVector3f operator+(const KMVector3f& vector);
	~KMVector3f();
private:
	float mX;
	float mY;
	float mZ;
	float mW;
};