#pragma once


class Vec4f
{
public:

    float x;
    float y;
    float z;
	float w;

	Vec4f(float X, float Y, float Z, float W) { x = X; y = Y; z = Z; w = W; }
	operator float*(){ return (float*) this; } 
};