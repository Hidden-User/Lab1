#pragma once

struct F2
{
	float x;
	float y;
};

class Point
{
public:
	Point();
	~Point();

	Point& operator=(const F2& f) {
		this->x = f.x;
		this->y = f.y;
		return *this;
	}

	void set(float x, float y);
	void mov(float x, float y);
	void set(Point a, Point b);

	F2 getPos();

private:
	float x;
	float y;

};
