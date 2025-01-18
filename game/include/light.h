#pragma once

enum light_type {
	AMBIENT, POINT, DIRECTIONAL
};

struct light {
	light_type type;
	float intensity;
	glm::vec3 position;
	glm::vec3 direction;
};

const light ambient_light{ .type = AMBIENT, .intensity = 0.2f };
const light point_light{ .type = POINT, .intensity = 0.6f, .position = glm::vec3(2.0f, 1.0f, 0.0f) };
const light directional_light{ .type = DIRECTIONAL, .intensity = 0.2f, .direction = glm::vec3(1.0f, 4.0f, 4.0f) };
const std::array<light, 3> lights = { ambient_light, point_light, directional_light };

float compute_lighting(glm::vec3 point, glm::vec3 normal,  glm::vec3 view, int16_t specular) {
	float i = 0.0f;
	for (auto& light : lights) {
		if (light.type == AMBIENT) {
			i += light.intensity;
		}
		else {
			glm::vec3 light_direction;
			float t_max;
			if (light.type == POINT) {
				light_direction = light.position - point;
				t_max = 1.0f;
			}
			else {
				light_direction = light.direction;
				t_max = INFINITY;
			}

			//Shadows
			sphere shadow_sphere;
			float closest_t;
			auto hit = closest_intersection(point, light_direction, epsilon, t_max, shadow_sphere, closest_t);
			if (hit) {
				continue;
			}

			//Diffuse
			auto n_dot_l = glm::dot(normal, light_direction);
			if (n_dot_l > 0) {
				i += light.intensity * n_dot_l / (glm::length(normal) * glm::length(light_direction));
			}

			//Specular
			if (specular != -1) {
				auto reflection = 2.0f * normal * n_dot_l - light_direction;
				auto r_dot_v = glm::dot(reflection, view);
				if (r_dot_v > 0.0f) {
					i += light.intensity * glm::pow(r_dot_v / (glm::length(reflection) * glm::length(view)), specular);
				}
			}
		}
	}
	return i;
}