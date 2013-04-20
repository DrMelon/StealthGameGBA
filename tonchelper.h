#pragma once

// ToncHelper.h - this exposes various tonc functionalities in easier to remember functions.
#include "tonclib/include/tonc.h"

// Object Stuff

extern OBJ_ATTR obj_buffer[128]; // Object Buffer declared here, does not need to be separately declared elsewhere.

INLINE void InitializeObjects()
{
	oam_init(obj_buffer, 128);
}

INLINE void UpdateObjects()
{
	oam_copy(oam_mem, obj_buffer, 1);
}

INLINE void SetObject(int objectID, u16 attribute0, u16 attribute1, u16 attribute2)
{
	OBJ_ATTR *theObject = &obj_buffer[objectID];
	obj_set_attr(theObject, attribute0, attribute1, attribute2);
}

INLINE void SetObjectPosition(int objectID, int X, int Y)
{
	OBJ_ATTR *theObject = &obj_buffer[objectID];
	obj_set_pos(theObject, X, Y);
}