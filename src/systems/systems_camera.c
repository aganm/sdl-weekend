#include "systems_camera.h"

f32v2 camera_center_offset(
	f32v2 viewport,
	f32v2 center)
{
	return (f32v2){
		center.x - viewport.w / 2.f,
		center.y - viewport.h / 2.f,
	};
}
