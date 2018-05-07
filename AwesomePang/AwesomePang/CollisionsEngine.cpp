#include "stdafx.h"
#include "core.h"
#include "CollisionsEngine.h"

float distance(const vec2 vector, const vec2 vector2) {
	float a = vector.x - vector2.x;
	float b = vector.y - vector2.y;

	float dist = sqrt(a * a + b * b);

	return dist;
}

bool checkCollisionCircleCircle(const vec2& pos1, float radius1, const vec2& pos2, float radius2) {
	float distanceBetweenCenters = distance(pos1, pos2);

	if (distanceBetweenCenters < (radius1 + radius2)) {
		return true;
	}
	else {
		return false;
	}
}