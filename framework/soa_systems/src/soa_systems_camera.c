#include <cglm/cglm.h>
#include <math/m3d.h>
#include <math/math_helpers.h>
#include <soa_components_transform.h>
#include <soa_systems_camera.h>

void soa_apply_camera_2d(
	soa_position2 *e_position,
	const usize entity_count,
	f32v2 camera)
{
	for (usize e = 0; e < entity_count; ++e) {
		e_position->x[e] -= camera.x;
		e_position->y[e] -= camera.y;
	}
}

void soa_apply_camera_3d(
	soa_position3 *e_position,
	const usize entity_count,
	f32v3 camera,
	f32v2 viewport)
{
	f32v3 target = camera;
	target.z += 1.f;
	mat4 model, view, proj, vp, mvp;
	glm_mat4_identity(model);
	glm_lookat(camera.raw, target.raw, (vec3){ 0, 1, 0 }, view);
	glm_perspective(10.f, viewport.width / viewport.height, 0.001f, 100.f, proj);
	glm_mat4_mul(proj, view, vp);
	glm_mat4_mul(vp, model, mvp);

	for (usize e = 0; e < entity_count; ++e) {
		f32v4 pos = { e_position->x[e], e_position->y[e], e_position->z[e], 1.f };
		f32v4 projected;
		glm_mat4_mulv(mvp, pos.raw, projected.raw);
		f32v2 ndc = {
			projected.x / projected.w,
			projected.y / projected.w,
		};
		f32v2 screen = {
			(ndc.x + 1.f) * 0.5f * viewport.width,
			(1.f - ndc.y) * 0.5f * viewport.height,
		};
		e_position->x[e] = screen.x;
		e_position->y[e] = screen.y;
	}
}
