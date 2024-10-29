#include <it/item.h>
#include <ft/fighter.h>
#include <sc/scene.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t lITMSBombItemAttributes;    // 0x000003BC
extern intptr_t lITMSBombHitEvents;         // 0x00000404

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

ITCreateDesc dITMSBombItemDesc =
{
    nITKindMSBomb,                          // Item Kind
    &gITManagerFileData,                    // Pointer to item file data?
    &lITMSBombItemAttributes,               // Offset of item attributes in file?

    // DObj transformation struct
    {
        nGCTransformNull,                   // Main matrix transformations
        nGCTransformNull,                   // Secondary matrix transformations?
        0                                   // ???
    },

    nGMAttackStateOff,                      // Hitbox Update State
    itMSBombFallProcUpdate,                 // Proc Update
    itMSBombFallProcMap,                    // Proc Map
    NULL,                                   // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Damage
};

ITStatusDesc dITMSBombStatusDescs[/* */] =
{
    // Status 0 (Ground Wait)
    {
        NULL,                               // Proc Update
        itMSBombWaitProcMap,                // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 1 (Air Wait Fall)
    {
        itMSBombFallProcUpdate,             // Proc Update
        itMSBombFallProcMap,                // Proc Map
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
        itMSBombThrownProcUpdate,           // Proc Update
        itMSBombThrownProcMap,              // Proc Map
        itMSBombCommonProcHit,              // Proc Hit
        itMSBombCommonProcHit,              // Proc Shield
        itMainCommonProcHop,                // Proc Hop
        itMSBombCommonProcHit,              // Proc Set-Off
        itMainCommonProcReflector,          // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 4 (Fighter Drop)
    {
        itMSBombFallProcUpdate,             // Proc Update
        itMSBombDroppedProcMap,             // Proc Map
        itMSBombCommonProcHit,              // Proc Hit
        itMSBombCommonProcHit,              // Proc Shield
        itMainCommonProcHop,                // Proc Hop
        itMSBombCommonProcHit,              // Proc Set-Off
        itMainCommonProcReflector,          // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 5 (Ground Attach)
    {
        itMSBombAttachedProcUpdate,         // Proc Update
        itMSBombAttachedProcMap,            // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        itMSBombCommonProcDamage            // Proc Damage
    },

    // Status 6 (Air Detach from Surface)
    {
        itMSBombDetachedProcUpdate,         // Proc Update
        itMSBombDroppedProcMap,             // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        itMSBombCommonProcDamage            // Proc Damage
    },

    // Status 7 (Neutral Explosion)
    {
        itMSBombExplodeProcUpdate,          // Proc Update
        NULL,                               // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    }
};

// // // // // // // // // // // //
//                               //
//          ENUMERATORS          //
//                               //
// // // // // // // // // // // //


enum itMSBombStatus
{
    nITMSBombStatusWait,
    nITMSBombStatusFall,
    nITMSBombStatusHold,
    nITMSBombStatusThrown,
    nITMSBombStatusDropped,
    nITMSBombStatusAttached,
    nITMSBombStatusDetached,
    nITMSBombStatusExplode,
    nITMSBombStatusEnumMax
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80176450
sb32 itMSBombFallProcUpdate(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);
    DObj *dobj = DObjGetStruct(item_gobj);

    itMainApplyGravityClampTVel(ip, ITMSBOMB_GRAVITY, ITMSBOMB_TVEL);
    itVisualsUpdateSpin(item_gobj);

    dobj->child->sib_next->rotate.vec.f.z = dobj->rotate.vec.f.z;

    return FALSE;
}

// 0x801764A8
sb32 itMSBombWaitProcMap(GObj *item_gobj)
{
    itMapCheckLRWallProcGround(item_gobj, itMSBombFallSetStatus);

    return FALSE;
}

// 0x801764D0
sb32 itMSBombFallProcMap(GObj *item_gobj)
{
    return itMapCheckDestroyDropped(item_gobj, ITMSBOMB_MAP_REBOUND_COMMON, ITMSBOMB_MAP_REBOUND_GROUND, itMSBombWaitSetStatus);
}

// 0x80176504
void itMSBombWaitSetStatus(GObj *item_gobj)
{
    itMainSetGroundAllowPickup(item_gobj);
    itMainSetItemStatus(item_gobj, dITMSBombStatusDescs, nITMSBombStatusWait);
}

// 0x80176538
void itMSBombFallSetStatus(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    itMapSetAir(ip);
    itMainSetItemStatus(item_gobj, dITMSBombStatusDescs, nITMSBombStatusFall);
}

// 0x8017657C
void itMSBombHoldSetStatus(GObj *item_gobj)
{
    itMainSetItemStatus(item_gobj, dITMSBombStatusDescs, nITMSBombStatusHold);
}

// 0x801765A4
sb32 itMSBombThrownProcUpdate(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);
    DObj *dobj = DObjGetStruct(item_gobj);

    itMainApplyGravityClampTVel(ip, ITMSBOMB_GRAVITY, ITMSBOMB_TVEL);
    itVisualsUpdateSpin(item_gobj);

    dobj->child->sib_next->rotate.vec.f.z = dobj->rotate.vec.f.z;

    return FALSE;
}

// 0x801765FC
sb32 itMSBombThrownProcMap(GObj *item_gobj)
{
    return itMapCheckMapProcAll(item_gobj, itMSBombAttachedSetStatus);
}

// 0x80176620
sb32 itMSBombCommonProcHit(GObj *item_gobj)
{
    itMainVelSetRebound(item_gobj);

    return FALSE;
}

// 0x80176644
void itMSBombThrownSetStatus(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);

    ip->coll_data.obj_coll.top = ITMSBOMB_COLL_SIZE;
    ip->coll_data.obj_coll.center = 0.0F;
    ip->coll_data.obj_coll.bottom = -ITMSBOMB_COLL_SIZE;
    ip->coll_data.obj_coll.width = ITMSBOMB_COLL_SIZE;

    itMainSetItemStatus(item_gobj, dITMSBombStatusDescs, nITMSBombStatusThrown);
}

// 0x80176694
sb32 itMSBombDroppedProcMap(GObj *item_gobj)
{
    return itMapCheckMapProcAll(item_gobj, itMSBombAttachedSetStatus);
}

// 0x801766B8
void itMSBombDroppedSetStatus(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);

    ip->coll_data.obj_coll.top = ITMSBOMB_COLL_SIZE;
    ip->coll_data.obj_coll.center = 0.0F;
    ip->coll_data.obj_coll.bottom = -ITMSBOMB_COLL_SIZE;
    ip->coll_data.obj_coll.width = ITMSBOMB_COLL_SIZE;

    itMainSetItemStatus(item_gobj, dITMSBombStatusDescs, nITMSBombStatusDropped);
}

// 0x80176708
void itMSBombAttachedUpdateSurface(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);
    MPCollData *coll_data = &ip->coll_data;
    Vec3f angle;
    DObj *dobj = DObjGetStruct(item_gobj);

    if ((coll_data->coll_mask_current & MPCOLL_FLAG_CEIL) || (coll_data->coll_mask_current & MPCOLL_FLAG_GROUND))
    {
        if (coll_data->coll_mask_current & MPCOLL_FLAG_CEIL)
        {
            angle = coll_data->ceil_angle;

            ip->attach_line_id = coll_data->ceil_line_id;
        }
        if (coll_data->coll_mask_current & MPCOLL_FLAG_GROUND)
        {
            angle = coll_data->ground_angle;

            ip->attach_line_id = coll_data->ground_line_id;
        }
    }
    else
    {
        if (coll_data->coll_mask_current & MPCOLL_FLAG_LWALL)
        {
            angle = coll_data->lwall_angle;

            ip->attach_line_id = coll_data->lwall_line_id;
        }
        if (coll_data->coll_mask_current & MPCOLL_FLAG_RWALL)
        {
            angle = coll_data->rwall_angle;

            ip->attach_line_id = coll_data->rwall_line_id;
        }
    }
    dobj->rotate.vec.f.z = atan2f(angle.y, angle.x) - F_CST_DTOR32(90.0F);
}

// 0x80176840
void itMSBombAttachedInitItemVars(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);
    DObj *dobj = DObjGetStruct(item_gobj);

    ip->coll_data.obj_coll.top = ITMSBOMB_COLL_SIZE;
    ip->coll_data.obj_coll.center = 0.0F;
    ip->coll_data.obj_coll.bottom = -ITMSBOMB_COLL_SIZE;
    ip->coll_data.obj_coll.width = ITMSBOMB_COLL_SIZE;

    ip->physics.vel_air.x = ip->physics.vel_air.y = ip->physics.vel_air.z = 0;

    dobj->child->flags = DOBJ_FLAG_NONE;
    dobj->child->sib_next->flags = DOBJ_FLAG_HIDDEN;

    itMSBombAttachedUpdateSurface(item_gobj);

    ip->is_attach_surface = TRUE;

    ip->dmg_coll.hitstatus = nGMHitStatusNormal;

    ip->atk_coll.atk_state = nGMAttackStateOff;

    if ((ip->player != -1) && (ip->player != GMCOMMON_PLAYERS_MAX))
    {
        GObj *fighter_gobj = gBattleState->players[ip->player].fighter_gobj;

        if (fighter_gobj != NULL)
        {
            ftParamMakeRumble(ftGetStruct(fighter_gobj), 6, 0);
        }
    }
    func_800269C0_275C0(nSYAudioFGMMSBombAttach);

    itMainClearOwnerStats(item_gobj);
}

// 0x80176934
void itMSBombExplodeMakeEffect(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);
    ITAttributes *attributes = ip->attributes;
    DObj *dobj = DObjGetStruct(item_gobj);
    s32 unused[4];

    if (ip->coll_data.coll_mask_current & MPCOLL_FLAG_GROUND)
    {
        Vec3f translate = dobj->translate.vec.f;

        translate.y += attributes->obj_coll_bottom;

        efManagerDustHeavyDoubleMakeEffect(&translate, ip->lr, 1.0F);
    }
}

// 0x801769AC
void itMSBombExplodeInITStatusVars(GObj *item_gobj, sb32 is_make_effect)
{
    LBParticle *ptcl;
    DObj *dobj = DObjGetStruct(item_gobj);

    if (is_make_effect != FALSE)
    {
        itMSBombExplodeMakeEffect(item_gobj);
    }
    ptcl = efManagerSparkleWhiteMultiExplodeMakeEffect(&dobj->translate.vec.f);

    if (ptcl != NULL)
    {
        ptcl->tfrm->scale.x = ITMSBOMB_EXPLODE_SCALE;
        ptcl->tfrm->scale.y = ITMSBOMB_EXPLODE_SCALE;
        ptcl->tfrm->scale.z = ITMSBOMB_EXPLODE_SCALE;
    }
    efManagerQuakeMakeEffect(1);
    itMainRefreshHit(item_gobj);
    itMSBombExplodeSetStatus(item_gobj);

    DObjGetStruct(item_gobj)->flags = DOBJ_FLAG_HIDDEN;
}

// 0x80176A34
sb32 itMSBombCommonProcDamage(GObj *item_gobj)
{
    func_800269C0_275C0(nSYAudioFGMExplodeL);
    itMSBombExplodeInITStatusVars(item_gobj, FALSE);

    return FALSE;
}

// 0x80176A68
sb32 itMSBombAttachedProcUpdate(GObj *item_gobj)
{
    s32 unused[2];
    GObj *fighter_gobj;
    Vec3f *translate;
    Vec3f dist;
    Vec3f fighter_pos;
    DObj *item_dobj = DObjGetStruct(item_gobj);
    ITStruct *ip = itGetStruct(item_gobj);

    if (ip->it_multi < ITMSBOMB_DETECT_FIGHTER_DELAY)
    {
        ip->it_multi++;
    }
    else
    {
        fighter_gobj = gGCCommonLinks[nGCCommonLinkIDFighter];

        translate = &item_dobj->translate.vec.f;

        while (fighter_gobj != NULL)
        {
            FTStruct *fp = ftGetStruct(fighter_gobj);
            DObj *fighter_dobj = DObjGetStruct(fighter_gobj);
            f32 var = fp->attributes->obj_coll.top * 0.5F;

            fighter_pos = fighter_dobj->translate.vec.f;

            fighter_pos.y += var;

            syVectorDiff3D(&dist, &fighter_pos, translate);

            if ((SQUARE(dist.x) + SQUARE(dist.y) + SQUARE(dist.z)) < ITMSBOMB_DETECT_FIGHTER_RADIUS)
            {
                itMSBombExplodeInITStatusVars(item_gobj, TRUE); // We might want to break out of the loop here
            }
            fighter_gobj = fighter_gobj->link_next;
        }
    }
    return FALSE;
}

// 0x80176B94
void itMSBombAttachedSetStatus(GObj *item_gobj)
{
    itMSBombAttachedInitItemVars(item_gobj);
    itMainSetItemStatus(item_gobj, dITMSBombStatusDescs, nITMSBombStatusAttached);
}

// 0x80176BC8
sb32 itMSBombAttachedProcMap(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);

    if (mpCollisionCheckExistLineID(ip->attach_line_id) == FALSE)
    {
        ip->is_attach_surface = FALSE;

        itMSBombDetachedSetStatus(item_gobj);
    }
    return FALSE;
}

void itMSBombExplodeUpdateHitEvent(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);
    ITAttackEvent *ev = itGetHitEvent(dITMSBombItemDesc, lITMSBombHitEvents); // (ITAttackEvent *)((uintptr_t)*dITMSBombItemDesc.p_file + &lITMSBombHitEvents); - Linker thing

    if (ip->it_multi == ev[ip->item_event_id].timer)
    {
        ip->atk_coll.angle  = ev[ip->item_event_id].angle;
        ip->atk_coll.damage = ev[ip->item_event_id].damage;
        ip->atk_coll.size   = ev[ip->item_event_id].size;

        ip->atk_coll.can_rehit_item = TRUE;
        ip->atk_coll.can_hop = FALSE;
        ip->atk_coll.can_reflect = FALSE;
        ip->atk_coll.can_setoff = FALSE;

        ip->atk_coll.element = nGMHitElementFire;

        ip->item_event_id++;

        if (ip->item_event_id == 4)
        {
            ip->item_event_id = 3;
        }
    }
}

// 0x80176D00
void itMSBombDetachedInitItemVars(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);

    ip->dmg_coll.hitstatus = nGMHitStatusNormal;
    ip->atk_coll.atk_state = nGMAttackStateOff;

    itMainClearOwnerStats(item_gobj);
}

// 0x80176D2C
sb32 itMSBombDetachedProcUpdate(GObj *item_gobj)
{
    s32 unused[2];
    GObj *fighter_gobj;
    Vec3f *translate;
    Vec3f dist;
    Vec3f fighter_pos;
    DObj *item_dobj = DObjGetStruct(item_gobj);
    ITStruct *ip = itGetStruct(item_gobj);

    itMainApplyGravityClampTVel(ip, ITMSBOMB_GRAVITY, ITMSBOMB_TVEL);

    if (ip->it_multi < ITMSBOMB_DETECT_FIGHTER_DELAY)
    {
        ip->it_multi++;
    }
    else
    {
        fighter_gobj = gGCCommonLinks[nGCCommonLinkIDFighter];

        translate = &item_dobj->translate.vec.f;

        while (fighter_gobj != NULL)
        {
            FTStruct *fp = ftGetStruct(fighter_gobj);
            DObj *fighter_dobj = DObjGetStruct(fighter_gobj);
            f32 offset_y = fp->attributes->obj_coll.top * 0.5F;

            fighter_pos = fighter_dobj->translate.vec.f;

            fighter_pos.y += offset_y;

            syVectorDiff3D(&dist, &fighter_pos, translate);

            if ((SQUARE(dist.x) + SQUARE(dist.y) + SQUARE(dist.z)) < ITMSBOMB_DETECT_FIGHTER_RADIUS)
            {
                itMSBombExplodeInITStatusVars(item_gobj, FALSE); // We might want to break out of the loop here
            }
            fighter_gobj = fighter_gobj->link_next;
        }
    }
    return FALSE;
}

// 0x80176E68
void itMSBombDetachedSetStatus(GObj *item_gobj)
{
    itMSBombDetachedInitItemVars(item_gobj);
    itMainSetItemStatus(item_gobj, dITMSBombStatusDescs, nITMSBombStatusDetached);
}

// 0x80176E9C
void itMSBombExplodeInitItemVars(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);

    ip->it_multi = 0;

    ip->item_event_id = 0;

    ip->atk_coll.throw_mul = ITEM_STALE_DEFAULT;
    ip->atk_coll.hit_sfx = nSYAudioFGMExplodeL;

    ip->dmg_coll.hitstatus = nGMHitStatusNone;

    itMSBombExplodeUpdateHitEvent(item_gobj);
}

// 0x80176EE4
sb32 itMSBombExplodeProcUpdate(GObj *item_gobj)
{
    ITStruct *ip = itGetStruct(item_gobj);

    itMSBombExplodeUpdateHitEvent(item_gobj);

    ip->it_multi++;

    if (ip->it_multi == ITMSBOMB_EXPLODE_LIFETIME)
    {
        return TRUE;
    }
    else return FALSE;
}

// 0x80176F2C
void itMSBombExplodeSetStatus(GObj *item_gobj)
{
    itMSBombExplodeInitItemVars(item_gobj);
    itMainSetItemStatus(item_gobj, dITMSBombStatusDescs, nITMSBombStatusExplode);
}

// 0x80176F60
GObj* itMSBombMakeItem(GObj *parent_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManagerMakeItem(parent_gobj, &dITMSBombItemDesc, pos, vel, flags);
    DObj *dobj;
    ITStruct *ip;
    Vec3f translate;

    if (item_gobj != NULL)
    {
        dobj = DObjGetStruct(item_gobj);

        dobj->child->flags = DOBJ_FLAG_HIDDEN;
        dobj->child->sib_next->flags = DOBJ_FLAG_NONE;

        translate = dobj->translate.vec.f;

        gcAddXObjForDObjFixed(dobj, nGCTransformTraRotRpyR, 0);
        gcAddXObjForDObjFixed(dobj->child->sib_next, 0x46, 0);

        dobj->translate.vec.f = translate;

        ip = itGetStruct(item_gobj);

        ip->it_multi = 0;

        ip->is_unused_item_bool = TRUE;

        ip->arrow_gobj = ifCommonItemArrowMakeInterface(ip);

        dobj->rotate.vec.f.z = 0.0F;
    }
    return item_gobj;
}
