#ifndef _ITCOLLISION_H_
#define _ITCOLLISION_H_

#include "ittypes.h"
#include <wp/wptypes.h>
#include <ft/fttypes.h>

// Set type of interaction and record hit target when item's hitbox collides with another GObj
void itCollisionSetHitInteractStats(itHitbox* it_hit, GObj* victim_gobj, s32 hitbox_type, u32 interact_mask);

// Set stuff when item's hurtbox gets hit by a fighter
void itCollisionUpdateDamageStatFighter(ftStruct* fp, ftHitbox* ft_hit, itStruct* ip, itHurtbox* it_hurt,
									  GObj* fighter_gobj, GObj* item_gobj);

// Set stuff when item's hitbox collides with another item's hitbox
void itCollisionUpdateAttackStatItem(itStruct* this_ip, itHitbox* this_hit, s32 this_hit_id, itStruct* victim_ip,
								   itHitbox* victim_hit, s32 victim_hit_id, GObj* this_gobj, GObj* victim_gobj);

// Set stuff when item's hitbox collides with a weapon's hitbox
void itCollisionUpdateAttackStatWeapon(wpStruct* wp, wpHitbox* wp_hit, s32 wp_hit_id, itStruct* ip, itHitbox* it_hit,
									 s32 it_hit_id, GObj* weapon_gobj, GObj* item_gobj);

// Set stuff when item's hurtbox gets hit by another item's hitbox
void itCollisionUpdateDamageStatItem(itStruct* attack_ip, itHitbox* attack_it_hit, s32 hitbox_id, itStruct* defend_ip,
								   itHurtbox* it_hurt, GObj* attack_gobj, GObj* defend_gobj);

// Set  stuff when item's hurtbox gets hit by a weapon's hitbox
void itCollisionUpdateDamageStatWeapon(wpStruct* wp, wpHitbox* wp_hit, s32 hitbox_id, itStruct* ip, itHurtbox* it_hurt,
									 GObj* weapon_gobj, GObj* item_gobj);

// Search for collision with fighter hitbox
void itCollisionSearchFighterHit(GObj* item_gobj);

// Search for collision with item hitbox
void itCollisionSearchItemHit(GObj* this_gobj);

// Search for collision with weapon hitbox
void itCollisionSearchWeaponHit(GObj* item_gobj);

// GObj process for searching hit collision with other entities
void itCollisionProcSearchHitAll(GObj* item_gobj);

// GObj process for updating hit collision events
void itCollisionProcHitCollisions(GObj* item_gobj);

#endif
