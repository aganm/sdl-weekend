#include <math/math_helpers.h>
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

void soa_apply_camera_3d(
	soa_position3 *e_position,
	const usize entity_count,
	const f32v2 viewport,
	const f32v3 camera)
{
	for (usize e = 0; e < entity_count; ++e) {
		const f32v3 pos = { e_position->x[e], e_position->y[e], e_position->z[e] };
		const f32v2 projected = project_3d_to_2d(pos, viewport, camera);
		e_position->x[e] = projected.x;
		e_position->y[e] = projected.y;
	}

}
