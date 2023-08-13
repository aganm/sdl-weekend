#include "systems_tilemap.h"

f32v2 tile_position_to_position(i32v2 tile_position, i32v2 tile_size)
{
	return (f32v2){
		tile_position.x * tile_size.w,
		tile_position.y * tile_size.h,
	};
}
