#ifndef _MNTYPES_H_
#define _MNTYPES_H_

#include <ssb_types.h>
#include <macros.h>
#include <sys/obj.h>
#include <gm/generic.h>

#include <mn/mndef.h>

struct MNTitleSpriteDesc
{
	Vec2i pos;
	intptr_t offset;
};

struct MNCongraPicture
{
	u32 bottom_file_id;
	intptr_t bottom_offset;
	u32 top_file_id;
	intptr_t top_offset;
};

#endif