#include <it/item.h>
#include <wp/weapon.h>
#include <ft/fighter.h>

extern void* func_ovl0_800CE8C0(s32, s32, f32, f32, f32, f32, f32, f32);

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t lITFFlowerItemAttributes;   // 0x000002E4
extern intptr_t
lITFFlowerWeaponFlameWeaponAttributes;      // 0x0000032C
extern intptr_t lITFFlowerFlameAngles;      // 0x00000360

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

itCreateDesc dITFFlowerItemDesc = 
{
    nITKindFFlower,                         // Item Kind
    &gITManagerFileData,                    // Pointer to item file data?
    &lITFFlowerItemAttributes,              // Offset of item attributes in file?

    // DObj transformation struct
    {
        nOMTransformTraRotRpyR,             // Main matrix transformations
        nOMTransformNull,                   // Secondary matrix transformations?
        0                                   // ???
    },

    nGMHitUpdateDisable,                    // Hitbox Update State
    itFFlowerFallProcUpdate,                // Proc Update
    itFFlowerFallProcMap,                   // Proc Map
    NULL,                                   // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Damage
};

itStatusDesc dITFFlowerStatusDescs[/* */] =
{
    // Status 0 (Ground Wait)
    {
        NULL,                               // Proc Update
        itFFlowerWaitProcMap,               // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 1 (Air Wait Fall)
    {
        itFFlowerFallProcUpdate,            // Proc Update
        itFFlowerFallProcMap,               // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 2 (Fighter Hold)
    {
        NULL,                               // Proc Update
        NULL,                               // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 3 (Fighter Throw)
    {
        itFFlowerFallProcUpdate,            // Proc Update
        itFFlowerThrownProcMap,             // Proc Map
        itFFlowerCommonProcHit,             // Proc Hit
        itFFlowerCommonProcHit,             // Proc Shield
        itMainCommonProcHop,                // Proc Hop
        itFFlowerCommonProcHit,             // Proc Set-Off
        itMainCommonProcReflector,          // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 4 (Fighter Drop)
    {
        itFFlowerFallProcUpdate,            // Proc Update
        itFFlowerDroppedProcMap,            // Proc Map
        itFFlowerCommonProcHit,             // Proc Hit
        itFFlowerCommonProcHit,             // Proc Shield
        itMainCommonProcHop,                // Proc Hop
        itFFlowerCommonProcHit,             // Proc Set-Off
        itMainCommonProcReflector,          // Proc Reflector
        NULL                                // Proc Damage
    }
};

wpCreateDesc dITFFlowerWeaponFlameWeaponDesc =
{
    0x00,                                   // Render flags?
    nWPKindFFlowerFlame,                    // Weapon Kind
    &gITManagerFileData,                    // Pointer to character's loaded files?
    &lITFFlowerWeaponFlameWeaponAttributes, // Offset of weapon attributes in loaded files

    // DObj transformation struct
    {
        nOMTransformTraRotRpyRSca,          // Main matrix transformations
        nOMTransformNull,                   // Secondary matrix transformations?
        0                                   // ???
    },

    itFFlowerWeaponFlameProcUpdate,         // Proc Update
    itFFlowerWeaponFlameProcMap,            // Proc Map
    itFFlowerWeaponFlameProcHit,            // Proc Hit
    itFFlowerWeaponFlameProcHit,            // Proc Shield
    NULL,                                   // Proc Hop
    itFFlowerWeaponFlameProcHit,            // Proc Set-Off
    itFFlowerWeaponFlameProcReflector,      // Proc Reflector
    NULL                                    // Proc Absorb
};

// // // // // // // // // // // //
//                               //
//          ENUMERATORS          //
//                               //
// // // // // // // // // // // //

enum itFFlowerStatus
{
    nITFFlowerStatusWait,
    nITFFlowerStatusFall,
    nITFFlowerStatusHold,
    nITFFlowerStatusThrown,
    nITFFlowerStatusDropped,
    nITFFlowerStatusEnumMax
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80175B20
sb32 itFFlowerFallProcUpdate(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    itMainApplyGravityClampTVel(ip, ITFFLOWER_GRAVITY, ITFFLOWER_TVEL);
    itVisualsUpdateSpin(item_gobj);

    return FALSE;
}

// 0x80175B5C
sb32 itFFlowerWaitProcMap(GObj *item_gobj)
{
    itMapCheckLRWallProcGround(item_gobj, itFFlowerFallSetStatus);

    return FALSE;
}

// 0x80175B84
sb32 itFFlowerFallProcMap(GObj *item_gobj)
{
    return itMapCheckDestroyDropped(item_gobj, ITFFLOWER_MAP_REBOUND_COMMON, ITFFLOWER_MAP_REBOUND_GROUND, itFFlowerWaitSetStatus);
}

// 0x80175BB0
void itFFlowerWaitSetStatus(GObj *item_gobj)
{
    itMainSetGroundAllowPickup(item_gobj);
    itMainSetItemStatus(item_gobj, dITFFlowerStatusDescs, nITFFlowerStatusWait);
}

// 0x80175BE4
void itFFlowerFallSetStatus(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    itMapSetAir(ip);
    itMainSetItemStatus(item_gobj, dITFFlowerStatusDescs, nITFFlowerStatusFall);
}

// 0x80175C28
void itFFlowerHoldSetStatus(GObj *item_gobj)
{
    itMainSetItemStatus(item_gobj, dITFFlowerStatusDescs, nITFFlowerStatusHold);
}

// 0x80175C50
sb32 itFFlowerThrownProcMap(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    if (ip->it_multi == 0)
    {
        return itMapCheckDestroyLanding(item_gobj, ITFFLOWER_MAP_REBOUND_COMMON);
    }
    else return itMapCheckDestroyDropped(item_gobj, ITFFLOWER_MAP_REBOUND_COMMON, ITFFLOWER_MAP_REBOUND_GROUND, itFFlowerWaitSetStatus);
}

// 0x80175C9C
sb32 itFFlowerCommonProcHit(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    ip->item_hit.update_state = nGMHitUpdateDisable;

    itMainVelSetRebound(item_gobj);

    return FALSE;
}

// 0x80175CC4
void itFFlowerThrownSetStatus(GObj *item_gobj)
{
    itMainSetItemStatus(item_gobj, dITFFlowerStatusDescs, nITFFlowerStatusThrown);
}

// 0x80175CEC
sb32 itFFlowerDroppedProcMap(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    if (ip->it_multi == 0)
    {
        return itMapCheckDestroyLanding(item_gobj, ITFFLOWER_MAP_REBOUND_COMMON);
    }
    else return itMapCheckDestroyDropped(item_gobj, ITFFLOWER_MAP_REBOUND_COMMON, ITFFLOWER_MAP_REBOUND_GROUND, itFFlowerWaitSetStatus);
}

// 0x80175D38
void itFFlowerDroppedSetStatus(GObj *item_gobj)
{
    itMainSetItemStatus(item_gobj, dITFFlowerStatusDescs, nITFFlowerStatusDropped);
}

// 0x80175D60
GObj* itFFlowerMakeItem(GObj *parent_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManagerMakeItem(parent_gobj, &dITFFlowerItemDesc, pos, vel, flags);

    if (item_gobj != NULL)
    {
        itStruct *ip = itGetStruct(item_gobj);

        ip->it_multi = ITFFLOWER_AMMO_MAX;

        ip->is_unused_item_bool = TRUE;

        ip->indicator_gobj = ifCommonItemArrowMakeInterface(ip);
    }
    return item_gobj;
}

// 0x80175DDC
sb32 itFFlowerWeaponFlameProcUpdate(GObj *weapon_gobj)
{
    wpStruct *wp = wpGetStruct(weapon_gobj);

    if (wpMainDecLifeCheckExpire(wp) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

// 0x801750E8
sb32 itFFlowerWeaponFlameProcMap(GObj *weapon_gobj)
{
    if (wpMapTestAllCheckCollEnd(weapon_gobj) != FALSE)
    {
        efManagerDustExpandSmallMakeEffect(&DObjGetStruct(weapon_gobj)->translate.vec.f, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

// 0x80175E4C
sb32 itFFlowerWeaponFlameProcHit(GObj *weapon_gobj)
{
    func_800269C0_275C0(nSYAudioFGMExplodeS);
    efManagerSparkleWhiteMakeEffect(&DObjGetStruct(weapon_gobj)->translate.vec.f);

    return FALSE;
}

// 0x80175E84
sb32 itFFlowerWeaponFlameProcReflector(GObj *weapon_gobj)
{
    wpStruct *wp = wpGetStruct(weapon_gobj);
    ftStruct *fp = ftGetStruct(wp->owner_gobj);
    Vec3f *translate;

    wp->lifetime = ITFFLOWER_AMMO_LIFETIME;

    wpMainReflectorSetLR(wp, fp);

    translate = &DObjGetStruct(weapon_gobj)->translate.vec.f;

    func_ovl0_800CE8C0(gITManagerParticleBankID | 8, 2, translate->x, translate->y, 0.0F, wp->phys_info.vel_air.x, wp->phys_info.vel_air.y, 0.0F);
    func_ovl0_800CE8C0(gITManagerParticleBankID | 8, 0, translate->x, translate->y, 0.0F, wp->phys_info.vel_air.x, wp->phys_info.vel_air.y, 0.0F);

    return FALSE;
}

// 0x80175F48
GObj* itFFlowerWeaponFlameMakeWeapon(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *weapon_gobj = wpManagerMakeWeapon(fighter_gobj, &dITFFlowerWeaponFlameWeaponDesc, pos, (WEAPON_FLAG_COLLPROJECT | WEAPON_FLAG_PARENT_FIGHTER));
    wpStruct *wp;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    wp = wpGetStruct(weapon_gobj);

    wp->phys_info.vel_air.x = vel->x * wp->lr;
    wp->phys_info.vel_air.y = vel->y;
    wp->phys_info.vel_air.z = vel->z;

    wp->lifetime = ITFFLOWER_AMMO_LIFETIME;

    func_ovl0_800CE8C0(gITManagerParticleBankID | 8, 2, pos->x, pos->y, 0.0F, wp->phys_info.vel_air.x, wp->phys_info.vel_air.y, 0.0F);
    func_ovl0_800CE8C0(gITManagerParticleBankID | 8, 0, pos->x, pos->y, 0.0F, wp->phys_info.vel_air.x, wp->phys_info.vel_air.y, 0.0F);

    return weapon_gobj;
}

// 0x8017604C
void itFFlowerShootFlame(GObj *fighter_gobj, Vec3f *pos, s32 index, s32 ammo_sub)
{
    itStruct *ip = itGetStruct(ftGetStruct(fighter_gobj)->item_hold);
    Vec3f vel;
    f32 *angle = (f32*) ((uintptr_t)*dITFFlowerItemDesc.p_file + (intptr_t)&lITFFlowerFlameAngles); // Linker thing

    vel.x = __cosf(angle[index]) * ITFFLOWER_AMMO_VEL;
    vel.y = __sinf(angle[index]) * ITFFLOWER_AMMO_VEL;
    vel.z = 0.0F;

    itFFlowerWeaponFlameMakeWeapon(fighter_gobj, pos, &vel);

    ip->it_multi -= ammo_sub;
}
