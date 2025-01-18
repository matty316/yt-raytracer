#pragma once

const int w = 1200;
const int h = 1200;
const glm::vec2 viewport_size(1.0f, 1.0f);
const float projection_plane_d = 1.0f;

glm::vec3 canvas_to_viewport(int x, int y) {
	return glm::vec3(x * viewport_size.x / w, y * viewport_size.y / h, projection_plane_d);
}

glm::vec3 reflect_ray(glm::vec3 ray, glm::vec3 normal) {
	return 2.0f * normal * glm::dot(normal, ray) - ray;
}

color trace_ray(const glm::vec3& origin, const glm::vec3& direction, float t_min, float t_max, size_t recursion_depth) {
	sphere closest_sphere;
	float closest_t;
	bool hit = closest_intersection(origin, direction, t_min, t_max, closest_sphere, closest_t);

	if (!hit)
		return color(0, 0, 0);

	auto point = origin + closest_t * direction;
	auto normal = point - closest_sphere.center;
	normal = normal / glm::length(normal);
	color local_color = closest_sphere.color * compute_lighting(point, normal, -direction, closest_sphere.specular);

	auto reflective = closest_sphere.reflective;
	if (recursion_depth <= 0 || reflective <= 0.0f) {
		return local_color;
	}

	auto reflected_ray = glm::reflect(-direction, normal);
	auto reflected_color = trace_ray(point, reflected_ray, epsilon, INFINITY, recursion_depth - 1);
  	return local_color * (1.0f - reflective) + reflected_color * reflective;
}

void put_pixel(const color& color, int x, int y) {
	x = w / 2 + x;
	y = h / 2 - y - 1;
	DrawPixel(x, y, raylibColor(color));
}
