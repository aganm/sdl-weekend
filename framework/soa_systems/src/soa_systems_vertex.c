#include <soa.h>
#include <soa_components_color.h>
#include <soa_components_graphics.h>
#include <soa_components_transform.h>
#include <soa_systems_vertex.h>

void soa_do_shit_with_vertex(
	soa_position2 *e_position,
	soa_color *e_color,
	soa_texcoord *e_texcoord,
	const usize entity_count)
{
	(void)e_position;
	(void)e_color;
	(void)e_texcoord;

	for (usize e = 0; e < entity_count; ++e) {
	}
}
