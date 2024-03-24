#include <soa_components_physics.h>
#include <soa_components_transform.h>
#include <soa_systems_physics.h>

void soa_reset_velocity(
	soa_velocity2 *e_velocity,
	const usize entity_count)
{
	for (usize e = 0; e < entity_count; e++) {
		e_velocity->x[e] = 0.f;
		e_velocity->y[e] = 0.f;
	}
}

void soa_apply_forwards_velocity(
	soa_position2 *e_position,
	const soa_velocity2 *e_velocity,
	const usize entity_count,
	const f32seconds dt)
{
	for (usize e = 0; e < entity_count; e++) {
		e_position->x[e] += e_velocity->x[e] * dt.seconds;
		e_position->y[e] += e_velocity->y[e] * dt.seconds;
	}
}
