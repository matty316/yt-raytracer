#pragma once

struct sphere {
	glm::vec3 center;
	float radius;
	color color;
	int16_t specular;
	float reflective;
};

const sphere red = { 
	.center = glm::vec3(0.0f, -1.0f, 3.0f), 
	.radius = 1.0f, 
	.color = color(255, 0, 0), 
	.specular = 500,
	.reflective = 0.2f
};
const sphere green = { 
	.center = glm::vec3(-2.0f, 0.0f, 4.0f), 
	.radius = 1.0f, 
	.color = color(0, 255, 0), 
	.specular = 10, 
	.reflective = 0.3f
};
const sphere blue = {
	.center = glm::vec3(2.0f, 0.0f, 4.0f),
	.radius = 1.0f,
	.color = color(0, 0, 255),
	.specular = 500,
	.reflective = 0.4f
};
const sphere yellow = { 
	.center = glm::vec3(0.0f, -5001.0f, 0.0f),
	.radius = 5000.0f, 
	.color = color(255, 255, 0), 
	.specular = 1000, 
	.reflective = 0.5f
};
const std::array<sphere, 4> spheres{red, green, blue, yellow};
