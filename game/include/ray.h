#pragma once

void intersect_ray_sphere(const glm::vec3& origin, const glm::vec3& direction, const sphere& sphere, float& t1, float& t2) {
	auto radius = sphere.radius;

	auto co = origin - sphere.center;

	auto a = glm::dot(direction, direction);
	auto b = 2.0f * glm::dot(co, direction);
	auto c = glm::dot(co, co) - radius * radius;

	auto discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f) {
		t1 = INFINITY;
		t2 = INFINITY;
		return;
	}

	t1 = (-b + glm::sqrt(discriminant)) / (2.0f * a);
	t2 = (-b - glm::sqrt(discriminant)) / (2.0f * a);
}

bool closest_intersection(const glm::vec3& origin, const glm::vec3& direction, float t_min, float t_max, sphere& closest_sphere, float& closest_t) {
	closest_t = INFINITY;
	bool hit = false;

	for (auto& sphere : spheres) {
		float t1, t2;
		intersect_ray_sphere(origin, direction, sphere, t1, t2);
		if (t1 > t_min && t1 < t_max && t1 < closest_t) {
			closest_t = t1;
			closest_sphere = sphere;
			hit = true;
		}

		if (t2 > t_min && t2 < t_max && t2 < closest_t) {
			closest_t = t2;
			closest_sphere = sphere;
			hit = true;
		}
	}

	return hit;
}