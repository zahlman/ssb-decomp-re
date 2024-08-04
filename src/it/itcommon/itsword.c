#include <it/item.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t lITSwordItemAttributes;     // 0x00000190

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

itCreateDesc dITSwordITemDesc =
{
    nITKindSword,                          // Item Kind
    &gITManagerFileData,                           // Pointer to item file data?
    &lITSwordItemAttributes,                // Offset of item attributes in file?

    // DObj transformation struct
    {
        nOMTransformTraRotRpyRSca,      // Main matrix transformations
        nOMTransformNull,               // Secondary matrix transformations?
        0                                   // ???
    },

    nGMHitUpdateDisable,     // Hitbox Update State
    itSwordFallProcUpdate,                 // Proc Update
    itSwordFallProcMap,                    // Proc Map
    NULL,                                   // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Damage
};

itStatusDesc dITSwordStatusDescs[/* */] = 
{
    // Status 0 (Ground Wait)
    {
        NULL,                               // Proc Update
        itSwordWaitProcMap,                // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 1 (Air Wait Fall)
    {
        itSwordFallProcUpdate,             // Proc Update
        itSwordFallProcMap,                // Proc Map
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
        itSwordFallProcUpdate,             // Proc Update
        itSwordThrownProcMap,               // Proc Map
        itSwordThrownProcHit,               // Proc Hit
        itSwordThrownProcHit,               // Proc Shield
        itMainCommonProcHop,                // Proc Hop
        itSwordThrownProcHit,               // Proc Set-Off
        itMainCommonProcReflector,          // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 4 (Fighter Drop)
    {
        itSwordFallProcUpdate,             // Proc Update
        itSwordDroppedProcMap,                // Proc Map
        itSwordThrownProcHit,               // Proc Hit
        itSwordThrownProcHit,               // Proc Shield
        itMainCommonProcHop,                // Proc Hop
        itSwordThrownProcHit,               // Proc Set-Off
        itMainCommonProcReflector,          // Proc Reflector
        NULL                                // Proc Damage
    }
};

// // // // // // // // // // // //
//                               //
//          ENUMERATORS          //
//                               //
// // // // // // // // // // // //

enum itSwordStatus
{
    itStatus_Sword_Wait,
    itStatus_Sword_Fall,
    itStatus_Sword_Hold,
    itStatus_Sword_Thrown,
    itStatus_Sword_Dropped,
    itStatus_Sword_EnumMax
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80174B50
sb32 itSwordFallProcUpdate(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    itMainApplyGravityClampTVel(ip, ITSWORD_GRAVITY, ITSWORD_TVEL);
    itVisualsUpdateSpin(item_gobj);

    return FALSE;
}

// 0x80174B8C
sb32 itSwordWaitProcMap(GObj *item_gobj)
{
    itMapCheckLRWallProcGround(item_gobj, itSwordFallSetStatus);

    return FALSE;
}

// 0x80174BB4
sb32 itSwordFallProcMap(GObj *item_gobj)
{
    return itMapCheckMapCollideThrownLanding(item_gobj, 0.2F, 0.5F, itSwordWaitSetStatus);
}

// 0x80174BE4
void itSwordWaitSetStatus(GObj *item_gobj)
{
    itMainSetGroundAllowPickup(item_gobj);
    itMainSetItemStatus(item_gobj, dITSwordStatusDescs, itStatus_Sword_Wait);
}

// 0x80174C18
void itSwordFallSetStatus(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    itMapSetAir(ip);
    itMainSetItemStatus(item_gobj, dITSwordStatusDescs, itStatus_Sword_Fall);
}

// 0x80174C5C
void itSwordHoldSetStatus(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->rotate.vec.f.y = F_CST_DTOR32(0.0F);

    itMainSetItemStatus(item_gobj, dITSwordStatusDescs, itStatus_Sword_Hold);
}

// 0x80174C90
sb32 itSwordThrownProcMap(GObj *item_gobj)
{
    return itMapCheckMapCollideThrownLanding(item_gobj, 0.2F, 0.5F, itSwordWaitSetStatus);
}

// 0x80174CC0
sb32 itSwordThrownProcHit(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    ip->item_hit.update_state = nGMHitUpdateDisable;

    itMainVelSetRebound(item_gobj);

    return FALSE;
}

// 0x80174CE8
void itSwordThrownSetStatus(GObj *item_gobj)
{
    itMainSetItemStatus(item_gobj, dITSwordStatusDescs, itStatus_Sword_Thrown);

    DObjGetStruct(item_gobj)->child->rotate.vec.f.y = F_CST_DTOR32(90.0F);
}

// 0x80174D2C
sb32 itSwordDroppedProcMap(GObj *item_gobj)
{
    return itMapCheckMapCollideThrownLanding(item_gobj, 0.2F, 0.5F, itSwordWaitSetStatus);
}

// 0x80174D5C
void itSwordDroppedSetStatus(GObj *item_gobj)
{
    itMainSetItemStatus(item_gobj, dITSwordStatusDescs, itStatus_Sword_Dropped);

    DObjGetStruct(item_gobj)->child->rotate.vec.f.y = F_CST_DTOR32(90.0F);
}

// 0x80174DA0
GObj* itSwordMakeItem(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManagerMakeItem(spawn_gobj, &dITSwordITemDesc, pos, vel, flags);

    if (item_gobj != NULL)
    {
        itStruct *ip = itGetStruct(item_gobj);

        DObjGetStruct(item_gobj)->rotate.vec.f.y = F_CST_DTOR32(90.0F);

        ip->is_unused_item_bool = TRUE;

        ip->indicator_gobj = ifCommonItemArrowMakeInterface(ip);
    }
    return item_gobj;
}
