#ifndef VEC2_H
#define VEC2_H

struct Vec2i {
	int x, y;
	Vec2i(int x, int y) : x(x), y(y) {}

	Vec2i operator+(const Vec2i& other) const {
		return Vec2i(x + other.x, y + other.y);
	}

	Vec2i operator-(const Vec2i& other) const {
		return Vec2i(x - other.x, y - other.y);
	}
};

struct Vec2f {
	float x, y;
	Vec2f(float x, float y) : x(x), y(y) {}

	Vec2f operator+(const Vec2f& other) const {
		return Vec2f(x + other.x, y + other.y);
	}

	Vec2f operator-(const Vec2f& other) const {
		return Vec2f(x - other.x, y - other.y);
	}
};

#endif // !VEC2_H