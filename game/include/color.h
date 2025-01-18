#pragma once

struct color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

color operator*(color color, float t) {
	auto r = color.r * t;
	auto g = color.g * t;
	auto b = color.b * t;

	if (r > 255.0f) {
		r = 255.0f;
	}
	if (g > 255.0f) {
		g = 255.0f;
	}
	if (b > 255.0f) {
		b = 255.0f;
	}

	if (r < 0.0f) {
		r = 0.0f;
	}
	if (g < 0.0f) {
		g = 0.0f;
	}
	if (b < 0.0f) {
		b = 0.0f;
	}

	return { uint8_t(r), uint8_t(g), uint8_t(b) };
}

color operator+(color color1, color color2) {
	auto r = color1.r + color2.r;
	auto g = color1.g + color2.g;
	auto b = color1.b + color2.b;

	if (r > 255) {
		r = 255;
	}
	if (g > 255) {
		g = 255;
	}
	if (b > 255) {
		b = 255;
	}

	if (r < 0) {
		r = 0;
	}
	if (g < 0) {
		g = 0;
	}
	if (b < 0) {
		b = 0;
	}

	return { uint8_t(r), uint8_t(g), uint8_t(b) };
}

Color raylibColor(const color& color) {
	return Color(color.r, color.g, color.b, 255);
}