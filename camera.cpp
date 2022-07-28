#include "camera.h"


float Camera::FieldOfViewY(float focalLengs, float sensor) {

	return 2 * atan(sensor / (2 * focalLengs));

}