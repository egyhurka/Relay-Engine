#ifndef COLOR_H
#define COLOR_H

#include <glfw3.h>

struct ColorRGB {
	GLfloat r, g, b;
	ColorRGB(GLfloat Red, GLfloat Green, GLfloat Blue) : r(Red), g(Green), b(Blue) {}
};

struct ColorRGBA {
	GLfloat r, g, b, a;
	ColorRGBA(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha) : r(Red), g(Green), b(Blue), a(Alpha) {}
};

#endif // !COLOR_H
