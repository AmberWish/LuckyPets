#include"KMVector3f.h"

/*******************************/
KMVector3f::KMVector3f(): mX(0), mY(0), mZ(0), mW(0)
{

}
/*******************************/
KMVector3f::KMVector3f(float x, float y, float z, float w) : mX(x), mY(y), mZ(z), mW(w)
{

}
/*******************************/
float KMVector3f::getX()
{
	return mX;
}
/*******************************/
void KMVector3f::setX(float x)
{
	mX = x;
}
/*******************************/
float KMVector3f::getY()
{
	return mY;
}
/*******************************/
void KMVector3f::setY(float y)
{
	mY = y;
}
/*******************************/
float KMVector3f::getZ()
{
	return mZ;
}
/*******************************/
void KMVector3f::setZ(float z)
{
	mZ = z;
}
/*******************************/
float KMVector3f::getW()
{
	return mW;
}
/*******************************/
void KMVector3f::setW(float w)
{
	mW = w;
}
/*******************************/
KMVector3f KMVector3f::operator+(const KMVector3f& vector)
{
	return *this;
}
/*******************************/
KMVector3f::~KMVector3f()
{

}
/*******************************/