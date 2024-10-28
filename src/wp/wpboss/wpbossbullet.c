#include <wp/weapon.h>
#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t 
lWPBossBulletNormalWeaponAttributes;        // 0x00000774
extern intptr_t
lWPBossBulletHardWeaponAttributes;          // 0x000007A8

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

WPCreateDesc dWPBossBulletNormalWeaponDesc =
{
    0x01,                                   // Render flags?
    nWPKindBulletNormal,                   // Weapon Kind
    &gFTDataBossMainMotion,               // Pointer to character's loaded files?
    &lWPBossBulletNormalWeaponAttributes,   // Offset of weapon attributes in loaded files

    // DObj transformation struct
    {
        nGCTransformTraRotRpyRSca,      // Main matrix transformations
        nGCTransformNull,               // Secondary matrix transformations?
        0,                                  // ???
    },

    NULL,                                   // Proc Update
    wpBossBulletProcMap,                    // Proc Map
    wpBossBulletProcHit,                    // Proc Hit
    wpBossBulletProcHit,                    // Proc Shield
    wpBossBulletProcHop,                    // Proc Hop
    wpBossBulletProcHit,                    // Proc Set-Off
    wpBossBulletProcReflector,              // Proc Reflector
    wpBossBulletProcHit                     // Proc Absorb
};

WPCreateDesc dWPBossBulletHardWeaponDesc =
{
    0x01,                                   // Render flags?
    nWPKindBulletHard,                     // Weapon Kind
    &gFTDataBossMainMotion,               // Pointer to character's loaded files?
    &lWPBossBulletHardWeaponAttributes,     // Offset of weapon attributes in loaded files

    // DObj transformation struct
    {
        nGCTransformTraRotRpyRSca,      // Main matrix transformations
        nGCTransformNull,               // Secondary matrix transformations?
        0,                                  // ???
    },

    NULL,                                   // Proc Update
    wpBossBulletProcMap,                    // Proc Map
    wpBossBulletProcHit,                    // Proc Hit
    wpBossBulletProcHit,                    // Proc Shield
    wpBossBulletProcHop,                    // Proc Hop
    wpBossBulletProcHit,                    // Proc Set-Off
    wpBossBulletProcReflector,              // Proc Reflector
    wpBossBulletProcHit                     // Proc Absorb
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8016DC00
sb32 wpBossBulletExplodeProcUpdate(GObj *weapon_gobj)
{
    if (wpMainDecLifeCheckExpire(wpGetStruct(weapon_gobj)) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
} 

// 0x8016DC2C
void wpBossBulletExplodeInitWeaponVars(GObj *weapon_gobj)
{
    WPStruct *wp = wpGetStruct(weapon_gobj);

    wp->atk_coll.hit_sfx = nSYAudioFGMExplodeL;

    wp->atk_coll.can_rehit_item = TRUE;
    wp->atk_coll.can_hop = FALSE;
    wp->atk_coll.can_reflect = FALSE;

    wp->atk_coll.element = nGMHitElementFire;

    wp->lifetime = WPYUBIBULLET_EXPLODE_LIFETIME;

    wp->physics.vel_air.x = wp->physics.vel_air.y = wp->physics.vel_air.z = 0.0F;

    wp->atk_coll.size = WPYUBIBULLET_EXPLODE_SIZE;

    DObjGetStruct(weapon_gobj)->display_ptr = NULL;

    wp->proc_update = wpBossBulletExplodeProcUpdate;
    wp->proc_map = NULL;
    wp->proc_hit = NULL;
    wp->proc_shield = NULL;
    wp->proc_hop = NULL;
    wp->proc_setoff = NULL;
    wp->proc_reflector = NULL;
}

// 0x8016DCB0
sb32 wpBossBulletProcMap(GObj *weapon_gobj)
{
    if (wpMapTestAllCheckCollEnd(weapon_gobj) != FALSE)
    {
        wpBossBulletExplodeInitWeaponVars(weapon_gobj);
        func_800269C0_275C0(nSYAudioFGMExplodeS);
        efManagerSparkleWhiteMultiExplodeMakeEffect(&DObjGetStruct(weapon_gobj)->translate.vec.f);

        return TRUE;
    }
    else return FALSE;
}

// 0x8016DD04
sb32 wpBossBulletProcHit(GObj *weapon_gobj)
{
    efManagerSparkleWhiteMultiExplodeMakeEffect(&DObjGetStruct(weapon_gobj)->translate.vec.f);

    return TRUE;
}

// 0x8016DD2C
sb32 wpBossBulletProcHop(GObj *weapon_gobj)
{
    WPStruct *wp = wpGetStruct(weapon_gobj);

    func_80019438(&wp->physics.vel_air, &wp->shield_collide_dir, wp->shield_collide_angle * 2);
    wpMainReflectorRotateWeaponModel(weapon_gobj);

    return FALSE;
}

// 0x8016DD7C
sb32 wpBossBulletProcReflector(GObj *weapon_gobj)
{
    WPStruct *wp = wpGetStruct(weapon_gobj);
    FTStruct *fp = ftGetStruct(wp->owner_gobj);

    wpMainReflectorSetLR(wp, fp);
    wpMainReflectorRotateWeaponModel(weapon_gobj);

    return FALSE;
}

// 0x8016DDB4
GObj* wpBossBulletNormalMakeWeapon(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *weapon_gobj = wpManagerMakeWeapon(fighter_gobj, &dWPBossBulletNormalWeaponDesc, pos, (WEAPON_FLAG_COLLPROJECT | WEAPON_FLAG_PARENT_FIGHTER));
    WPStruct *wp;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    wp = wpGetStruct(weapon_gobj);

    wp->physics.vel_air.x = WPYUBIBULLETVEL_X * wp->lr;
    wp->physics.vel_air.y = WPYUBIBULLETVEL_Y;

    wpMainReflectorRotateWeaponModel(weapon_gobj);

    return weapon_gobj;
}

// 0x8016DE28
GObj* wpBossBulletHardMakeWeapon(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *weapon_gobj = wpManagerMakeWeapon(fighter_gobj, &dWPBossBulletHardWeaponDesc, pos, (WEAPON_FLAG_COLLPROJECT | WEAPON_FLAG_PARENT_FIGHTER));
    WPStruct *wp;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    wp = wpGetStruct(weapon_gobj);

    wp->physics.vel_air.x = WPYUBIBULLETVEL_X * wp->lr;
    wp->physics.vel_air.y = WPYUBIBULLETVEL_Y;

    wpMainReflectorRotateWeaponModel(weapon_gobj);

    return weapon_gobj;
}
