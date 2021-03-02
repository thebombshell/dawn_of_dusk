
#include "piece.h"

static dod_piece g_piece_lookup[5] = {
	{ 0, 0, 0, .info.value = 0},
	{ 1, 0, 0, .info.value = 0},
	{ 2, 20, 0, .info.value = 0},
	{ 3, 10, 0, .info.value = 0},
	{ 4, 10, 0, .info.value = 0}
};

static dod_piece_part_one_type g_part_one_lookup[5] = {
	MAP_PIECE_PART_ONE_NONE,
	MAP_PIECE_PART_ONE_NONE,
	MAP_PIECE_PART_ONE_DURABILITY,
	MAP_PIECE_PART_ONE_DURABILITY,
	MAP_PIECE_PART_ONE_DURABILITY
};

static dod_piece_part_two_type g_part_two_lookup[5] = {
	MAP_PIECE_PART_TWO_NONE,
	MAP_PIECE_PART_TWO_NONE,
	MAP_PIECE_PART_TWO_NONE,
	MAP_PIECE_PART_TWO_NONE,
	MAP_PIECE_PART_TWO_NONE
};

void dod_map_piece_init(dod_piece* t_map_piece)
{
	*t_map_piece = g_piece_lookup[0];
}

void dod_map_piece_init_as(dod_piece* t_map_piece, dod_piece_type t_type)
{
	*t_map_piece = g_piece_lookup[t_type];
}

dod_piece_part_one_type dod_map_piece_get_part_one(dod_piece_type t_type)
{
	return g_part_one_lookup[t_type];
}

dod_piece_part_two_type dod_map_piece_get_part_two(dod_piece_type t_type)
{
	return g_part_two_lookup[t_type];
}