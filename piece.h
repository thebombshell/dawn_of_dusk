
/**
 * map_pieces.h
 */

#ifndef MAP_PIECES_H
#define MAP_PIECES_H

#include "typedef.h"

typedef dod_uword dod_piece_type;
typedef dod_uword dod_piece_part_one_type;
typedef dod_uword dod_piece_part_two_type;

typedef union {
	
	dod_uword value;
	struct {
		
		dod_bool reserved : 1;
		
	} flags;
	
} dod_piece_info;

typedef struct {
	
	dod_piece_type type;
	dod_uword part_one;
	dod_uword part_two;
	dod_piece_info info;
	
} dod_piece;

void dod_piece_init(dod_piece* t_map_piece);

void dod_piece_init_as(dod_piece* t_map_piece, dod_piece_type t_type);

dod_piece_part_one_type dod_map_piece_get_part_one(dod_piece_type t_type);

dod_piece_part_two_type dod_map_piece_get_part_two(dod_piece_type t_type);

#define MAP_PIECE_NONE 											0x00000000
#define MAP_PIECE_BEDROCK										0x00000001
#define MAP_PIECE_ROCK											0x00000002
#define MAP_PIECE_DIRT											0x00000003
#define MAP_PIECE_SAND											0x00000004

#define MAP_PIECE_PART_ONE_NONE 								0x00000000
#define MAP_PIECE_PART_ONE_DURABILITY							0x00000001

#define MAP_PIECE_PART_TWO_NONE 								0x00000000

#endif