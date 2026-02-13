//
// * ENGINE-X
//
// + Types.h
// representations of: 2D vector with floats, 2D vector with integers and RBGA color as four bytes
//

#pragma once

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exVector2
{
	float x, y;

	exVector2() : x(0.0f), y(0.0f)
	{
	};

	exVector2(float InX, float InY) : x(InX), y(InY)
	{
	}

	exVector2 operator+=(const exVector2& OtherVector)
	{
		x += OtherVector.x;
		y += OtherVector.y;
		return *this;
	}

	exVector2 operator-=(const exVector2& OtherVector)
	{
		x -= OtherVector.x;
		y -= OtherVector.y;
		return *this;
	}

	exVector2 operator*=(const float& OtherFloat)
	{
		x *= OtherFloat;
		y *= OtherFloat;
		return *this;
	}

	exVector2 operator+(const exVector2& OtherVector)
	{
		exVector2 Result(x + OtherVector.x, y + OtherVector.y);
		return Result;
	}

	exVector2 operator-(const exVector2& OtherVector)
	{
		exVector2 Result(x - OtherVector.x, y - OtherVector.y);
		return Result;
	}

	exVector2 operator*(const float& OtherFloat)
	{
		exVector2 Result(x * OtherFloat, y * OtherFloat);
		return Result;
	}

	bool operator==(const exVector2& OtherVector)
	{
		return (x == OtherVector.x && y == OtherVector.y);
	}

};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exIntegerVector2
{
	int x, y;
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exColor
{
	unsigned char mColor[4]; // RGBA Values
};
