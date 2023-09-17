#include <soa_components_transform.h>
#include <soa_systems_camera.h>

void soa_apply_camera_2d(
	soa_position2 *e_position,
	const usize entity_count,
	const f32v2 camera)
{
	for (usize e = 0; e < entity_count; ++e) {
		e_position->x[e] -= camera.x;
		e_position->y[e] -= camera.y;
	}
}
