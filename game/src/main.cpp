#include "common.h"

int main() {
	glm::vec3 origin{ 0.0f, 0.0f, 0.0f };

	InitWindow(w, h, "Raytracer");



	while (!WindowShouldClose()) {
		BeginDrawing();
		for (int x = -w / 2; x < w / 2; x++) {
			for (int y = -h / 2; y < h / 2; y++) {
				auto direction = canvas_to_viewport(x, y);
				auto color = trace_ray(origin, direction, 0.0f, INFINITY, 3);
				put_pixel(color, x, y);
			}
		}
		EndDrawing();
	}

	CloseWindow();
}