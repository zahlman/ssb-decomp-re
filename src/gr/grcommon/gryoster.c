#include <gr/ground.h>
#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t lGRYosterMapHead;                   // 0x00000100
extern intptr_t D_NF_000001E0;
extern intptr_t D_NF_000004B8;
extern intptr_t lGRYosterCloudDisplayList;          // 0x00000580
extern intptr_t lGRYosterCloudSolidMatAnimJoint;    // 0x00000670
extern intptr_t lGRYosterCloudEvaporateMatAnimJoint;// 0x00000690
extern intptr_t lGRYosterParticleBankHeaderLo;      // 0x00B22980
extern intptr_t lGRYosterParticleBankHeaderHi;      // 0x00B22A00
extern intptr_t lGRYosterParticleBankTextureLo;     // 0x00B22A00
extern intptr_t lGRYosterParticleBankTextureHi;     // 0x00B22C30

extern void func_ovl0_800C88AC(DObj*, void*, void*, f32);
extern void func_8000DF34_EB34(GObj*);
extern void func_8000BD8C_C98C(GObj*, void*, f32);

// // // // // // // // // // // //
//                               //
//        INITALIZED DATA        //
//                               //
// // // // // // // // // // // //

// 0x8012EB20
intptr_t dGRYosterCloudMatAnimJoints[/* */] = { &lGRYosterCloudSolidMatAnimJoint, &lGRYosterCloudEvaporateMatAnimJoint };

// 0x8012EB28
u8 dGRYosterCloudLineIDs[/* */] = { 0x1, 0x2, 0x3 };

// // // // // // // // // // // //
//                               //
//          ENUMERATORS          //
//                               //
// // // // // // // // // // // //

enum grYosterCloudStatus
{
    nGRYosterCloudStatusSolid,
    nGRYosterCloudStatusEvaporate
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80108550
efGenerator* grYosterCloudVaporMakeEffect(Vec3f *pos)
{
    efGenerator *efgen = func_ovl0_800D35DC(gGroundStruct.yoster.particle_bank_id, 0);

    if (efgen != NULL)
    {
        efgen->pos.x = pos->x;
        efgen->pos.y = pos->y;
        efgen->pos.z = pos->z;
    }
    return efgen;
}

// 0x801085A8
sb32 grYosterCheckFighterCloudStand(s32 cloud_id)
{
    GObj *fighter_gobj = gOMObjCommonLinks[GObj_LinkID_Fighter];
    s32 line_id = dGRYosterCloudLineIDs[cloud_id];

    while (fighter_gobj != NULL)
    {
        ftStruct *fp = ftGetStruct(fighter_gobj);

        if (fp->ground_or_air == GA_Ground)
        {
            if ((fp->coll_data.ground_line_id != -2) && (mpCollision_SetDObjNoID(fp->coll_data.ground_line_id) == line_id))
            {
                return TRUE;
            }
        }
        fighter_gobj = fighter_gobj->link_next;
    }
    return FALSE;
}

// 0x80108634
void grYosterUpdateCloudSolid(s32 cloud_id)
{
    Vec3f pos;
    DObj *dobj;

    if (gGroundStruct.yoster.clouds[cloud_id].dobj[0]->mobj->mobj_f0 == AOBJ_FRAME_NULL)
    {
        if (gGroundStruct.yoster.clouds[cloud_id].is_cloud_line_active == FALSE)
        {
            mpCollision_SetYakumonoOnID(dGRYosterCloudLineIDs[cloud_id]);

            gGroundStruct.yoster.clouds[cloud_id].is_cloud_line_active = TRUE;
        }
        if (gGroundStruct.yoster.clouds[cloud_id].pressure_timer == 0)
        {
            gGroundStruct.yoster.clouds[cloud_id].status = nGRYosterCloudStatusEvaporate;
            gGroundStruct.yoster.clouds[cloud_id].anim_id = nGRYosterCloudStatusEvaporate;
            gGroundStruct.yoster.clouds[cloud_id].evaporate_wait = 180;

            pos = DObjGetStruct(gGroundStruct.yoster.clouds[cloud_id].gobj)->translate.vec.f;

            pos.x += (-750.0F);
            pos.y += (-350.0F);

            grYosterCloudVaporMakeEffect(&pos);

            func_800269C0_275C0(alSound_SFX_YosterCloudVapor);
        }
        else
        {
            if (grYosterCheckFighterCloudStand(cloud_id) != FALSE)
            {
                if (gGroundStruct.yoster.clouds[cloud_id].pressure_timer == -1)
                {
                    gGroundStruct.yoster.clouds[cloud_id].pressure_timer = 120;
                }
                gGroundStruct.yoster.clouds[cloud_id].pressure += 5.0F;

                if (gGroundStruct.yoster.clouds[cloud_id].pressure > 180.0F)
                {
                    gGroundStruct.yoster.clouds[cloud_id].pressure = 180.0F;
                }
            }
            else
            {
                gGroundStruct.yoster.clouds[cloud_id].pressure_timer = -1;
                gGroundStruct.yoster.clouds[cloud_id].pressure -= 5.0F;

                if (gGroundStruct.yoster.clouds[cloud_id].pressure < 0.0F)
                {
                    gGroundStruct.yoster.clouds[cloud_id].pressure = 0.0F;
                }
            }
            if (gGroundStruct.yoster.clouds[cloud_id].pressure_timer > 0)
            {
                gGroundStruct.yoster.clouds[cloud_id].pressure_timer--;
            }
        }
    }
    dobj = DObjGetStruct(gGroundStruct.yoster.clouds[cloud_id].gobj);
    dobj->translate.vec.f.y = gGroundStruct.yoster.clouds[cloud_id].altitude - gGroundStruct.yoster.clouds[cloud_id].pressure;

    mpCollision_SetYakumonoPosID(dGRYosterCloudLineIDs[cloud_id], &dobj->translate.vec.f);
}

// 0x80108814
void grYosterUpdateCloudEvaporate(s32 cloud_id)
{
    if (gGroundStruct.yoster.clouds[cloud_id].is_cloud_line_active != FALSE)
    {
        mpCollision_SetYakumonoOffID(dGRYosterCloudLineIDs[cloud_id]);

        gGroundStruct.yoster.clouds[cloud_id].is_cloud_line_active = FALSE;
    }
    if (gGroundStruct.yoster.clouds[cloud_id].evaporate_wait == 0)
    {
        gGroundStruct.yoster.clouds[cloud_id].status = nGRYosterCloudStatusSolid;
        gGroundStruct.yoster.clouds[cloud_id].anim_id = nGRYosterCloudStatusSolid;
        gGroundStruct.yoster.clouds[cloud_id].pressure_timer = -1;
        gGroundStruct.yoster.clouds[cloud_id].pressure = 0.0F;
    }
    else gGroundStruct.yoster.clouds[cloud_id].evaporate_wait--;
}

// 0x80108890
void grYosterUpdateCloudAnim(s32 cloud_id)
{
    s8 anim_id = gGroundStruct.yoster.clouds[cloud_id].anim_id;

    if (anim_id != -1)
    {
        void *map_head = gGroundStruct.yoster.map_head;
        s32 i;

        for (i = 0; i < ARRAY_COUNT(gGroundStruct.yoster.clouds[cloud_id].dobj); i++)
        {
            DObj *dobj = gGroundStruct.yoster.clouds[cloud_id].dobj[i];

            func_ovl0_800C88AC(dobj, NULL, (void*) ((intptr_t)dGRYosterCloudMatAnimJoints[anim_id] + (uintptr_t)map_head), 0.0F);
            func_8000CCBC_D8BC(dobj);
        }
        gGroundStruct.yoster.clouds[cloud_id].anim_id = -1;
    }
}

// 0x80108960
void grYosterProcUpdate(GObj *ground_gobj)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gGroundStruct.yoster.clouds); i++)
    {
        switch (gGroundStruct.yoster.clouds[i].status)
        {
        case nGRYosterCloudStatusSolid:
            grYosterUpdateCloudSolid(i);
            break;

        case nGRYosterCloudStatusEvaporate:
            grYosterUpdateCloudEvaporate(i);
            break;
        }
        grYosterUpdateCloudAnim(i);
    }
}

// 0x801089F4
void grYosterInitAll(void)
{
    DObj *cloud_dobj;
    GObj *map_gobj;
    DObj *coll_dobj;
    void *map_head;
    s32 i, j;

    map_head = (uintptr_t)gGroundInfo->map_nodes - (intptr_t)&lGRYosterMapHead;
    gGroundStruct.yoster.map_head = map_head;

    for (i = 0; i < ARRAY_COUNT(gGroundStruct.yoster.clouds); i++)
    {
        map_gobj = omMakeGObjSPAfter(GObj_Kind_Ground, NULL, GObj_LinkID_Ground, GOBJ_LINKORDER_DEFAULT);

        gGroundStruct.yoster.clouds[i].gobj = map_gobj;

        omAddGObjRenderProc(map_gobj, odRenderDObjTreeForGObj, 6, GOBJ_DLLINKORDER_DEFAULT, -1);
        func_8000F590(map_gobj, (intptr_t)&lGRYosterMapHead + (uintptr_t)map_head, NULL, OMMtx_Transform_Tra, OMMtx_Transform_Null, 0); // Make this OMMtx_Transform_TraRotRpyRSca to add static cloud animation

        omAddGObjCommonProc(map_gobj, func_8000DF34_EB34, GObjProcess_Kind_Proc, 5);

        func_8000BD8C_C98C(map_gobj, (uintptr_t)map_head + (intptr_t)&D_NF_000001E0, 0);

        coll_dobj = DObjGetStruct(map_gobj);
        coll_dobj->translate.vec.f = gMPRooms->room_dobj[dGRYosterCloudLineIDs[i]]->translate.vec.f;

        gGroundStruct.yoster.clouds[i].altitude = coll_dobj->translate.vec.f.y;

        coll_dobj = coll_dobj->child;

        for (j = 0; j < ARRAY_COUNT(gGroundStruct.yoster.clouds[i].dobj); j++, coll_dobj = coll_dobj->sib_next)
        {
            cloud_dobj = omAddChildForDObj(coll_dobj, (uintptr_t)map_head + (intptr_t)&lGRYosterCloudDisplayList);
            gGroundStruct.yoster.clouds[i].dobj[j] = cloud_dobj;

            omAddOMMtxForDObjFixed(cloud_dobj, OMMtx_Transform_Tra, 0);
            omAddOMMtxForDObjFixed(cloud_dobj, 0x30, 0);
            func_ovl0_800C9228(cloud_dobj, (uintptr_t)map_head + (intptr_t)&D_NF_000004B8);
        }
        func_8000DF34_EB34(map_gobj);

        gGroundStruct.yoster.clouds[i].status = nGRYosterCloudStatusSolid;
        gGroundStruct.yoster.clouds[i].anim_id = nGRYosterCloudStatusSolid;
        gGroundStruct.yoster.clouds[i].pressure_timer = -1;
        gGroundStruct.yoster.clouds[i].is_cloud_line_active = FALSE;
        gGroundStruct.yoster.clouds[i].pressure = 0.0F;

        mpCollision_SetYakumonoOnID(dGRYosterCloudLineIDs[i]);

    }
    gGroundStruct.yoster.particle_bank_id = efAllocGetAddParticleBankID(&lGRYosterParticleBankHeaderLo, &lGRYosterParticleBankHeaderHi, &lGRYosterParticleBankTextureLo, &lGRYosterParticleBankTextureHi);
}

// 0x80108C80
GObj* grYosterMakeGround(void)
{
    GObj *ground_gobj = omMakeGObjSPAfter(GObj_Kind_Ground, NULL, GObj_LinkID_Ground, GOBJ_LINKORDER_DEFAULT);

    grYosterInitAll();
    omAddGObjCommonProc(ground_gobj, grYosterProcUpdate, GObjProcess_Kind_Proc, 4);

    return ground_gobj;
}
