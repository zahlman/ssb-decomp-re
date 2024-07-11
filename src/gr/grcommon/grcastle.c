#include <gr/ground.h>
#include <it/item.h>

extern void func_8000DF34_EB34(GObj*);
extern void func_8000BD8C_C98C(GObj*, void*, f32);

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t lGRCastleMapHead;               // 0x00000000

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8010B340
void grCastleBumperProcUpdate(GObj *ground_gobj)
{
    Vec3f *ground_pos = &DObjGetStruct(ground_gobj)->translate.vec.f;

    if (gGroundStruct.castle.bumper_gobj != NULL)
    {
        Vec3f *bumper_pos = &DObjGetStruct(gGroundStruct.castle.bumper_gobj)->translate.vec.f;

        bumper_pos->x = ground_pos->x + gGroundStruct.castle.bumper_pos.x;
    }
}

// 0x8010B378
void grCastleInitAll(void)
{
    void *map_head;
    GObj *ground_gobj;
    Vec3f yakumono_pos;
    Vec3f vel;
    s32 pos_id;
    DObj *dobj;

    gGroundStruct.castle.map_head = map_head = (void*)((uintptr_t)gGroundInfo->map_nodes - (intptr_t)&lGRCastleMapHead);

    ground_gobj = omMakeGObjSPAfter(GObj_Kind_Ground, NULL, GObj_LinkID_Ground, GOBJ_LINKORDER_DEFAULT);

    omAddGObjCommonProc(ground_gobj, grCastleBumperProcUpdate, GObjProcess_Kind_Proc, 4);

    dobj = omAddDObjForGObj(ground_gobj, NULL);
    dobj->translate.vec.f.x = dobj->translate.vec.f.y = dobj->translate.vec.f.z = 0.0F;

    omAddGObjCommonProc(ground_gobj, func_8000DF34_EB34, GObjProcess_Kind_Proc, 5);

    func_8000BD8C_C98C(ground_gobj, gGroundInfo->map_nodes, 0.0F);
    func_8000DF34_EB34(ground_gobj);

    mpCollision_GetMPointIDsKind(mpMPoint_Kind_Bumper, &pos_id);
    mpCollision_GetMPointPositionID(pos_id, &yakumono_pos);

    gGroundStruct.castle.bumper_pos = yakumono_pos;

    vel.x = 0.0F;
    vel.y = 0.0F;
    vel.z = 0.0F;

    gGroundStruct.castle.bumper_gobj = itManagerMakeItemSetupCommon(NULL, It_Kind_GBumper, &yakumono_pos, &vel, ITEM_MASK_SPAWN_GROUND);
}

// 0x8010B4AC
GObj* grCastleMakeGround(void)
{
    grCastleInitAll();

    return NULL;
}
