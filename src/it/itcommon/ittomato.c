#include <it/item.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t lITTomatoItemAttributes;    // 0x000000B8

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

itCreateDesc dITTomatoItemDesc =
{
    nITKindTomato,                         // Item Kind
    &gITManagerFileData,                           // Pointer to item file data?
    &lITTomatoItemAttributes,               // Offset of item attributes in file?

    // DObj transformation struct
    {
        nOMTransformTraRotRpyR,         // Main matrix transformations
        nOMTransformNull,               // Secondary matrix transformations?
        0                                   // ???
    },

    nGMHitUpdateDisable,     // Hitbox Update State
    itTomatoFallProcUpdate,                // Proc Update
    itTomatoFallProcMap,                   // Proc Map
    NULL,                                   // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Damage
};

itStatusDesc dITTomatoStatusDescs[/* */] =
{
    // Status 0 (Ground Wait)
    {
        NULL,                               // Proc Update
        itTomatoWaitProcMap,               // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 1 (Air Wait Fall)
    {
        itTomatoFallProcUpdate,            // Proc Update
        itTomatoFallProcMap,               // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 2 (Fighter Drop)
    {
        itTomatoFallProcUpdate,            // Proc Update
        itTomatoDroppedProcMap,               // Proc Map
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

enum itTomatoStatus
{
    itStatus_Tomato_Wait,
    itStatus_Tomato_Fall,
    itStatus_Tomato_Dropped,
    itStatus_Tomato_EnumMax
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x801744C0
sb32 itTomatoFallProcUpdate(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    itMainApplyGravityClampTVel(ip, ITTOMATO_GRAVITY, ITTOMATO_TVEL);
    itVisualsUpdateSpin(item_gobj);

    return FALSE;
}

// 0x801744FC
sb32 itTomatoWaitProcMap(GObj *item_gobj)
{
    itMapCheckLRWallProcGround(item_gobj, itTomatoFallSetStatus);

    return FALSE;
}

// 0x80174524
sb32 itTomatoFallProcMap(GObj *item_gobj)
{
    return itMapCheckThrownLanding(item_gobj, 0.3F, 0.5F, itTomatoWaitSetStatus);
}

// 0x80174554
void itTomatoWaitSetStatus(GObj *item_gobj)
{
    itMainSetGroundAllowPickup(item_gobj);
    itMainSetItemStatus(item_gobj, dITTomatoStatusDescs, itStatus_Tomato_Wait);
}

// 0x80174588
void itTomatoFallSetStatus(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    itMapSetAir(ip);
    itMainSetItemStatus(item_gobj, dITTomatoStatusDescs, itStatus_Tomato_Fall);
}

// 0x801745CC
sb32 itTomatoDroppedProcMap(GObj *item_gobj)
{
    return itMapCheckThrownLanding(item_gobj, 0.3F, 0.5F, itTomatoWaitSetStatus);
}

// 0x801745FC
void itTomatoDroppedSetStatus(GObj *item_gobj)
{
    itMainSetItemStatus(item_gobj, dITTomatoStatusDescs, itStatus_Tomato_Dropped);
}

// 0x80174624
GObj* itTomatoMakeItem(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManagerMakeItem(spawn_gobj, &dITTomatoItemDesc, pos, vel, flags);
    DObj *joint;
    Vec3f translate;
    itStruct *ip;

    if (item_gobj != NULL)
    {
        joint = DObjGetStruct(item_gobj);
        ip = itGetStruct(item_gobj);
        translate = joint->translate.vec.f;

        omAddOMMtxForDObjFixed(joint, 0x2E, 0);

        joint->translate.vec.f = translate;

        ip->is_unused_item_bool = TRUE;

        ip->indicator_gobj = ifCommonItemArrowMakeInterface(ip);
    }
    return item_gobj;
}
