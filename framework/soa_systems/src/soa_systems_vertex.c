#include <math/math_helpers.h>
#include <soa.h>
#include <soa_components_color.h>
#include <soa_components_graphics.h>
#include <soa_components_shape.h>
#include <soa_components_transform.h>
#include <soa_systems_vertex.h>

void soa_make_cube(
	soa_position3 *v_position,
	soa_color1 *v_color,
	soa_texcoord *v_texcoord,
	soa_entity_t *vertex_entity,
	f32v3 position,
	f32 size)
{
	(void)v_texcoord;

	static const f32v3 vertices[8] = {
		{ -1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, -1.0f },
		{ 1.0f, 1.0f, -1.0f },
		{ -1.0f, 1.0f, -1.0f },
		{ -1.0f, -1.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f }
	};
	static const int indices[36] = {
		0, 1, 2, 2, 3, 0,
		1, 5, 6, 6, 2, 1,
		5, 4, 7, 7, 6, 5,
		4, 0, 3, 3, 7, 4,
		3, 2, 6, 6, 7, 3,
		4, 5, 1, 1, 0, 4
	};
	for (usize i = 0; i < 36; ++i) {
		const usize v = soa_new_slot1(vertex_entity).idx;
		const f32v3 cube_vertex = vertices[indices[i]];
		v_position->x[v] = cube_vertex.x * size + position.x;
		v_position->y[v] = cube_vertex.y * size + position.y;
		v_position->z[v] = cube_vertex.z * size + position.z;
		v_color->val[i] = (u8v4) {
			(i + 0) * 100,
			(i + 1) * 100,
			(i + 2) * 100,
			255,
		};
	}
}

void soa_make_sprite_vertices(
	const soa_position2 *e_position,
	const soa_rotation1 *e_rotation,
	const soa_size2 *e_size,
	const soa_clip *e_clip,
	const soa_color *e_color,
	usize entity_count,
	soa_position2 *v_position,
	soa_color1 *v_color,
	soa_texcoord *v_texcoord,
	soa_entity_t *vertex_entity,
	f32v2 texture_size)
{
	for (usize e = 0; e < entity_count; ++e) {
		const usize v0 = soa_new_slot1(vertex_entity).idx;
		const usize v1 = soa_new_slot1(vertex_entity).idx;
		const usize v2 = soa_new_slot1(vertex_entity).idx;
		const usize v3 = soa_new_slot1(vertex_entity).idx;
		const usize v4 = soa_new_slot1(vertex_entity).idx;
		const usize v5 = soa_new_slot1(vertex_entity).idx;

		/* Vertex positions. */
		const f32 w = e_size->w[e];
		const f32 h = e_size->h[e];
		const f32 x = e_position->x[e] - w * 0.5f;
		const f32 y = e_position->y[e] - h;
		const f32 rad = e_rotation->x[e];

		f32v2 p0 = { x, y };
		f32v2 p1 = { x, y + h };
		f32v2 p2 = { x + w, y };
		f32v2 p3 = { x + w, y + h };
		if (rad != 0.f) {
			const bool is_centered = true;
			const f32v2 origin = {
				is_centered ? x + w * 0.5f : x,
				is_centered ? y + h * 0.5f : y,
			};
			p0 = rotate_about(p0, origin, rad);
			p1 = rotate_about(p1, origin, rad);
			p2 = rotate_about(p2, origin, rad);
			p3 = rotate_about(p3, origin, rad);
		}

		v_position->x[v0] = p0.x;
		v_position->y[v0] = p0.y;
		v_position->x[v1] = p1.x;
		v_position->y[v1] = p1.y;
		v_position->x[v2] = p2.x;
		v_position->y[v2] = p2.y;
		v_position->x[v3] = p1.x;
		v_position->y[v3] = p1.y;
		v_position->x[v4] = p3.x;
		v_position->y[v4] = p3.y;
		v_position->x[v5] = p2.x;
		v_position->y[v5] = p2.y;

		/* Texture coordinates. */
		const f32rect tex = {
			(e_clip->x[e] / texture_size.x),
			(e_clip->y[e] / texture_size.y),
			(e_clip->w[e] / texture_size.x),
			(e_clip->h[e] / texture_size.y),
		};
		const f32 s1 = tex.x;
		const f32 s2 = tex.x + tex.w;
		const f32 t1 = tex.y;
		const f32 t2 = tex.y + tex.h;

		v_texcoord->s[v0] = s1;
		v_texcoord->t[v0] = t1;
		v_texcoord->s[v1] = s1;
		v_texcoord->t[v1] = t2;
		v_texcoord->s[v2] = s2;
		v_texcoord->t[v2] = t1;
		v_texcoord->s[v3] = s1;
		v_texcoord->t[v3] = t2;
		v_texcoord->s[v4] = s2;
		v_texcoord->t[v4] = t2;
		v_texcoord->s[v5] = s2;
		v_texcoord->t[v5] = t1;

		/* Color. */
		const u8v4 rgba = {
			e_color->r[e],
			e_color->g[e],
			e_color->b[e],
			e_color->a[e],
		};

		v_color->val[v0] = rgba;
		v_color->val[v1] = rgba;
		v_color->val[v2] = rgba;
		v_color->val[v3] = rgba;
		v_color->val[v4] = rgba;
		v_color->val[v5] = rgba;
	}
}

void soa_make_sprite_vertices_3d(
	const soa_position2 *e_position,
	const soa_rotation1 *e_rotation,
	const soa_size2 *e_size,
	const soa_clip *e_clip,
	const soa_color *e_color,
	usize entity_count,
	soa_position3 *v_position,
	soa_color1 *v_color,
	soa_texcoord *v_texcoord,
	soa_entity_t *vertex_entity,
	f32v2 texture_size)
{
	for (usize e = 0; e < entity_count; ++e) {
		const usize v0 = soa_new_slot1(vertex_entity).idx;
		const usize v1 = soa_new_slot1(vertex_entity).idx;
		const usize v2 = soa_new_slot1(vertex_entity).idx;
		const usize v3 = soa_new_slot1(vertex_entity).idx;
		const usize v4 = soa_new_slot1(vertex_entity).idx;
		const usize v5 = soa_new_slot1(vertex_entity).idx;

		/* Vertex positions. */
		const f32 w = e_size->w[e];
		const f32 h = e_size->h[e];
		const f32 x = e_position->x[e] - w * 0.5f;
		const f32 y = e_position->y[e] - h;
		const f32 rad = e_rotation->x[e];

		f32v2 p0 = { x, y };
		f32v2 p1 = { x, y + h };
		f32v2 p2 = { x + w, y };
		f32v2 p3 = { x + w, y + h };
		if (rad != 0.f) {
			const bool is_centered = true;
			const f32v2 origin = {
				is_centered ? x + w * 0.5f : x,
				is_centered ? y + h * 0.5f : y,
			};
			p0 = rotate_about(p0, origin, rad);
			p1 = rotate_about(p1, origin, rad);
			p2 = rotate_about(p2, origin, rad);
			p3 = rotate_about(p3, origin, rad);
		}

		v_position->x[v0] = p0.x;
		v_position->y[v0] = p0.y;
		v_position->z[v0] = 0;
		v_position->x[v1] = p1.x;
		v_position->y[v1] = p1.y;
		v_position->z[v1] = 0;
		v_position->x[v2] = p2.x;
		v_position->y[v2] = p2.y;
		v_position->z[v2] = w;
		v_position->x[v3] = p1.x;
		v_position->y[v3] = p1.y;
		v_position->z[v3] = 0;
		v_position->x[v4] = p3.x;
		v_position->y[v4] = p3.y;
		v_position->z[v4] = w;
		v_position->x[v5] = p2.x;
		v_position->y[v5] = p2.y;
		v_position->z[v5] = w;

		/* Texture coordinates. */
		const f32rect tex = {
			(e_clip->x[e] / texture_size.x),
			(e_clip->y[e] / texture_size.y),
			(e_clip->w[e] / texture_size.x),
			(e_clip->h[e] / texture_size.y),
		};
		const f32 s1 = tex.x;
		const f32 s2 = tex.x + tex.w;
		const f32 t1 = tex.y;
		const f32 t2 = tex.y + tex.h;

		v_texcoord->s[v0] = s1;
		v_texcoord->t[v0] = t1;
		v_texcoord->s[v1] = s1;
		v_texcoord->t[v1] = t2;
		v_texcoord->s[v2] = s2;
		v_texcoord->t[v2] = t1;
		v_texcoord->s[v3] = s1;
		v_texcoord->t[v3] = t2;
		v_texcoord->s[v4] = s2;
		v_texcoord->t[v4] = t2;
		v_texcoord->s[v5] = s2;
		v_texcoord->t[v5] = t1;

		/* Color. */
		const u8v4 rgba = {
			e_color->r[e],
			e_color->g[e],
			e_color->b[e],
			e_color->a[e],
		};

		v_color->val[v0] = rgba;
		v_color->val[v1] = rgba;
		v_color->val[v2] = rgba;
		v_color->val[v3] = rgba;
		v_color->val[v4] = rgba;
		v_color->val[v5] = rgba;
	}
}
