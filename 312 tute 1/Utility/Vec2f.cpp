#include "Vec2f.h"


Vec2f::Vec2f(float a, float b)
{
	x=a;
	y=b;
}

void Vec2f::operator=(const Vec2f& vec)
{
	x=vec.x;
	y=vec.y;
}

bool Vec2f::operator==(const Vec2f& vec)
{
	if((x==vec.x)&&(y==vec.y))
	{
		return true;
	}
	return false;
}
	

bool Vec2f::operator!=(const Vec2f& vec)
{
	if((x==vec.x)&&(y==vec.y))
	{
		return false;
	}
	return true;
}