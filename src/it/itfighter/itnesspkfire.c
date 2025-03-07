#include <it/item.h>
#include <wp/weapon.h>
#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t lITNessPKFireItemAttributes;// 0x00000034

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

ITCreateDesc dITNessPKFireItemDesc = 
{
    nITKindNessPKFire,                      // Item Kind
    &gFTNessFileSpecial1,                   // Pointer to item file data?
    &lITNessPKFireItemAttributes,           // Offset of item attributes in file?

    // DObj transformation struct
    {
        nGCMatrixKindTraRotRpyRSca,          // Main matrix transformations
        nGCMatrixKindNull,                   // Secondary matrix transformations?
        0                                   // ???
    },

    nGMAttackStateNew,                      // Hitbox Update State
    itNessPKFireCommonProcUpdate,           // Proc Update
    NULL,                                   // Proc Map
    NULL,                                   // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Damage
};

ITStatusDesc dITNessPKFireStatusDescs[/* */] =
{
    // Status 0 (Ground Wait)
    {
        itNessPKFireWaitProcUpdate,         // Proc Update
        itNessPKFireWaitProcMap,            // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        itNessPKFireCommonProcDamage        // Proc Damage
    },

    // Status 1 (Air Wait Fall)
    {
        itNessPKFireFallProcUpdate,         // Proc Update
        itNessPKFireFallProcMap,            // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        itNessPKFireCommonProcDamage        // Proc Damage
    }
};

// // // // // // // // // // // //
//                               //
//          ENUMERATORS          //
//                               //
// // // // // // // // // // // //

enum itPKFireStatus
{
    nITNessPKFireStatusWait,
    nITNessPKFireStatusFall,
    nITNessPKFireStatusEnumCount
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80185350
sb32 itNessPKFireCommonProcUpdate(GObj *item_gobj)
{
    itNessPKFireFallSetStatus(item_gobj);

    return FALSE;
}

// 0x80185374
sb32 itNessPKFireCommonUpdateAllCheckDestroy(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);
    ITAttributes *attr;
    f32 unused;
    f32 half = 0.5;
    f32 lifetime_scale = ((ip->lifetime * half) / 100.0F) + half;
    LBTransform *tfm = ip->item_vars.pkfire.tfm;

    DObjGetStruct(item_gobj)->scale.vec.f.x = DObjGetStruct(item_gobj)->scale.vec.f.y = DObjGetStruct(item_gobj)->scale.vec.f.z = lifetime_scale;

    attr = ip->attr;

    ip->attack_coll.offsets[0].x = attr->attack_offset0_x * lifetime_scale;
    ip->attack_coll.offsets[0].y = attr->attack_offset0_y * lifetime_scale;
    ip->attack_coll.offsets[0].z = attr->attack_offset0_z * lifetime_scale;
    ip->attack_coll.offsets[1].x = attr->attack_offset1_x * lifetime_scale;
    ip->attack_coll.offsets[1].y = attr->attack_offset1_y * lifetime_scale;
    ip->attack_coll.offsets[1].z = attr->attack_offset1_z * lifetime_scale;

    ip->attack_coll.size = attr->size * 0.5F * lifetime_scale;

    ip->damage_coll.offset.x = attr->damage_coll_offset.x * lifetime_scale;
    ip->damage_coll.offset.y = attr->damage_coll_offset.y * lifetime_scale;
    ip->damage_coll.offset.z = attr->damage_coll_offset.z * lifetime_scale;
    ip->damage_coll.size.x = attr->damage_coll_size.x * 0.5F * lifetime_scale;
    ip->damage_coll.size.y = attr->damage_coll_size.y * 0.5F * lifetime_scale;
    ip->damage_coll.size.z = attr->damage_coll_size.z * 0.5F * lifetime_scale;

    if (tfm != NULL)
    {
        tfm->scale.x = DObjGetStruct(item_gobj)->scale.vec.f.x;
        tfm->scale.y = DObjGetStruct(item_gobj)->scale.vec.f.y;
        tfm->scale.z = DObjGetStruct(item_gobj)->scale.vec.f.z;

        tfm->translate = DObjGetStruct(item_gobj)->translate.vec.f;
    }
    ip->lifetime--;

    if (ip->lifetime < 0)
    {
        efManagerDustExpandSmallMakeEffect(&DObjGetStruct(item_gobj)->translate.vec.f, 1.0F);

        if (tfm != NULL)
        {
            lbParticleEjectStructID(tfm->generator_id, 0);
        }
        return TRUE;
    }
    else return FALSE;
}

// 0x801855E4
sb32 itNessPKFireWaitProcUpdate(GObj *item_gobj)
{
    if (itNessPKFireCommonUpdateAllCheckDestroy(item_gobj) == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}

// 0x80185614
sb32 itNessPKFireFallProcUpdate(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);

    if (itNessPKFireCommonUpdateAllCheckDestroy(item_gobj) == TRUE)
    {
        return TRUE;
    }
    else itMainApplyGravityClampTVel(ip, ITPKFIRE_GRAVITY, ITPKFIRE_TVEL);

    return FALSE;
}

// 0x80185660
sb32 itNessPKFireWaitProcMap(GObj *item_gobj)
{
    itMapCheckLRWallProcGround(item_gobj, itNessPKFireFallSetStatus);

    return FALSE;
}

// 0x80185688
sb32 itNessPKFireFallProcMap(GObj *item_gobj)
{
    itMapCheckLanding(item_gobj, ITPKFIRE_MAP_REBOUND_COMMON, ITPKFIRE_MAP_REBOUND_GROUND, itNessPKFireWaitSetStatus);

    return FALSE;
}

// 0x801856BC
sb32 itNessPKFireCommonProcDamage(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);

    if (ip->lifetime > 0)
    {
        ip->lifetime -= ip->damage_highest * ITPKFIRE_HURT_DAMAGE_MUL;
    }
    if (itNessPKFireCommonUpdateAllCheckDestroy(item_gobj) == TRUE)
    {
        return TRUE;
    }
    else return FALSE;
}

// 0x80185710
void itNessPKFireWaitSetStatus(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);
    GMStatFlags stat_flags;
    u16 stat_count;

    itMapSetGround(ip);

    ip->physics.vel_ground = 0.0F;
    ip->physics.vel_air.x = ip->physics.vel_air.y = 0.0F;

    stat_flags = ip->attack_coll.stat_flags;
    stat_count = ip->attack_coll.stat_count;

    itMainSetItemStatus(item_gobj, dITNessPKFireStatusDescs, nITNessPKFireStatusWait);

    ip->attack_coll.stat_flags = stat_flags;
    ip->attack_coll.stat_count = stat_count;
}

// 0x8018579C
void itNessPKFireFallSetStatus(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);
    GMStatFlags stat_flags;
    u16 stat_count;

    itMapSetAir(ip);

    ip->physics.vel_air.x = ip->physics.vel_air.y = 0.0F;

    stat_flags = ip->attack_coll.stat_flags;
    stat_count = ip->attack_coll.stat_count;

    itMainSetItemStatus(item_gobj, dITNessPKFireStatusDescs, nITNessPKFireStatusFall);

    ip->attack_coll.stat_flags = stat_flags;
    ip->attack_coll.stat_count = stat_count;
}

// 0x80185824
GObj* itNessPKFireMakeItem(GObj *weapon_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *item_gobj;
    WPStruct *wp = wpGetStruct(weapon_gobj);
    ITStruct *ip;
    LBParticle *ptc;
    LBTransform *tfm;

    item_gobj = itManagerMakeItem(weapon_gobj, &dITNessPKFireItemDesc, pos, vel, (ITEM_FLAG_COLLPROJECT | ITEM_FLAG_PARENT_WEAPON));

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = itGetStruct(item_gobj);

    ip->owner_gobj = wp->owner_gobj;

    ip->is_allow_pickup = FALSE;
    ip->is_hold = FALSE;

    ip->team = wp->team;
    ip->player = wp->player;
    ip->handicap = wp->handicap;
    ip->player_number = wp->player_number;

    ip->attack_coll.can_rehit_shield = TRUE;

    ip->attack_coll.stale = wp->attack_coll.stale;
    ip->attack_coll.attack_id = wp->attack_coll.attack_id;
    ip->attack_coll.motion_count = wp->attack_coll.motion_count;
    ip->attack_coll.stat_flags = wp->attack_coll.stat_flags;
    ip->attack_coll.stat_count = wp->attack_coll.stat_count;

    itMapSetAir(ip);
    itProcessUpdateHitPositions(item_gobj);

    ip->lifetime = ITPKFIRE_LIFETIME;

    ptc = lbParticleMakeScriptID(gFTNessParticleBankID, 0);

    if (ptc != NULL)
    {
        tfm = lbParticleAddTransformForStruct(ptc, nLBTransformStatusDefault);

        if (tfm != NULL)
        {
            ip->item_vars.pkfire.tfm = tfm;

            LBParticleProcessStruct(ptc);

            if (tfm->users_num == 0)
            {
                ip->item_vars.pkfire.tfm = NULL;
            }
            else tfm->translate = *pos;
        }
        else
        {
            lbParticleEjectStruct(ptc);

            ip->item_vars.pkfire.tfm = NULL;
        }
    }
    else ip->item_vars.pkfire.tfm = NULL;
    
    return item_gobj;
}
