#include <ft/fighter.h>
#include <sc/scene.h>
#include <sys/develop.h>
#include <lb/library.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern FTFileSize gSCManagerFighterFileSizes[nFTKindEnumCount];

extern intptr_t D_NF_000000A3;
extern intptr_t D_NF_000000C9;

// // // // // // // // // // // //
//                               //
//   GLOBAL / STATIC VARIABLES   //
//                               //
// // // // // // // // // // // //

// 0x80130D80
FTStruct *sFTManagerStructsAllocFree;

// 0x80130D84
FTStruct *sFTManagerStructsAllocBuf;

// 0x80130D88
FTParts *sFTManagerPartsAllocFree;

// 0x80130D8C
FTParts *sFTManagerPartsAllocBuf;

// 0x80130D90
u32 gFTManagerPlayersNum;

// 0x80130D94
u16 gFTManagerMotionCount;

// 0x80130D96
u16 gFTManagerStatUpdateCount;

// 0x80130D98
void *gFTManagerCommonFile;

// 0x80130D9C
size_t gFTManagerFigatreeHeapSize;

// 0x80130DA0
LBFileNode sFTManagerForceStatusBuffer[7];

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

// 0x80116E10
extern FTData *dFTManagerDataFiles[nFTKindEnumCount];

/*
FTData *dFTManagerDataFiles[] =
{
    D_ovl2_80117810,
    D_ovl2_801196F4,
    D_ovl2_8011AC8C,
    D_ovl2_8011CC78,
    D_ovl2_8011E0A0,
    D_ovl2_8011F520,
    D_ovl2_801209D0,
    D_ovl2_80121E98,
    D_ovl2_80123680,
    D_ovl2_80124CE4,
    D_ovl2_8012617C,
    D_ovl2_801276A0,
    D_ovl2_80128C7C,
    D_ovl2_80118220,
    D_ovl2_80118C30,
    D_ovl2_8011A1B4,
    D_ovl2_8011B76C,
    D_ovl2_8011D698,
    D_ovl2_8011EAB0,
    D_ovl2_8011FF90,
    D_ovl2_80121410,
    D_ovl2_80122918,
    D_ovl2_8012427C,
    D_ovl2_8012572C,
    D_ovl2_80126BCC,
    D_ovl2_80128170,
    D_ovl2_8011C24C
};

*/

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x800D6FE0
void ftManagerSetupFileSize(void)
{
    s32 i, j;
    size_t largest_size;
    size_t current_anim_size;
    FTData *data;
    FTFileSize *file_size;
    LBRelocSetup rl_setup;
    FTMotionDesc *motion_desc;

    rl_setup.table_addr = (uintptr_t)&lLBRelocTableAddr;
    rl_setup.table_files_num = (uintptr_t)&lLBRelocTableFilesNum;
    rl_setup.file_heap = NULL;
    rl_setup.file_heap_size = 0;
    rl_setup.status_buffer = NULL;
    rl_setup.status_buffer_size = 0;
    rl_setup.force_status_buffer = sFTManagerForceStatusBuffer;
    rl_setup.force_status_buffer_size = ARRAY_COUNT(sFTManagerForceStatusBuffer);

    lbRelocInitSetup(&rl_setup);

    for (i = 0; i < ARRAY_COUNT(dFTManagerDataFiles); i++)
    {
        file_size = &gSCManagerFighterFileSizes[i];
        data = dFTManagerDataFiles[i];

        largest_size = 0;

        file_size->main = lbRelocGetFileSize(data->file_main_id);

        for (j = 0; j < data->mainmotion_array_count; j++)
        {
            motion_desc = &data->mainmotion->motion_desc[j];

            current_anim_size = data->mainmotion->motion_desc[j].anim_file_id;

            if (motion_desc->anim_file_id != 0)
            {
                if (!(motion_desc->anim_desc.flags.is_use_shieldpose))
                {
                    current_anim_size = lbRelocGetFileSize(motion_desc->anim_file_id);

                    if (largest_size < current_anim_size)
                    {
                        largest_size = current_anim_size;
                    }
                }
            }
        }
        file_size->mainmotion_largest_anim = largest_size;

        for (j = 0; j < *data->submotion_array_count; j++)
        {
            motion_desc = &data->submotion->motion_desc[j];

            current_anim_size = data->submotion->motion_desc[j].anim_file_id;

            if (motion_desc->anim_file_id != 0)
            {
                if (!(motion_desc->anim_desc.flags.is_use_shieldpose))
                {
                    current_anim_size = lbRelocGetFileSize(motion_desc->anim_file_id);

                    if (largest_size < current_anim_size)
                    {
                        largest_size = current_anim_size;
                    }
                }
            }
        }
        file_size->submotion_largest_anim = largest_size;
    }
}

// 0x800D7194
void ftManagerAllocFighter(u32 data_flags, s32 allocs_num)
{
    size_t largest_size;
    s32 i;
    size_t current_size;
    FTData *data;
    FTFileSize *file_size;
    size_t heap_size;

    heap_size = 0;

    sFTManagerStructsAllocBuf = sFTManagerStructsAllocFree = syTaskmanMalloc(sizeof(FTStruct) * allocs_num, 0x8);

    bzero(sFTManagerStructsAllocBuf, sizeof(FTStruct) * allocs_num);

    for (i = 0; i < (allocs_num - 1); i++)
    {
        sFTManagerStructsAllocBuf[i].alloc_next = &sFTManagerStructsAllocBuf[i + 1];
    }
    sFTManagerStructsAllocBuf[i].alloc_next = NULL;

    sFTManagerPartsAllocFree = sFTManagerPartsAllocBuf = syTaskmanMalloc(sizeof(FTParts) * allocs_num * FTPARTS_JOINT_NUM_MAX, 0x8);

    for (i = 0; i < ((allocs_num * FTPARTS_JOINT_NUM_MAX) - 1); i++)
    {
        sFTManagerPartsAllocBuf[i].alloc_next = &sFTManagerPartsAllocBuf[i + 1];
    }
    sFTManagerPartsAllocBuf[i].alloc_next = NULL;

    gFTManagerPlayersNum = 1;
    gFTManagerMotionCount = 1;
    gFTManagerStatUpdateCount = 1;

    gFTManagerCommonFile = lbRelocGetFileExternHeap((u32)&D_NF_000000A3, syTaskmanMalloc(lbRelocGetFileSize((u32)&D_NF_000000A3), 0x10));

    lbRelocGetFileExternHeap((u32)&D_NF_000000C9, syTaskmanMalloc(lbRelocGetFileSize((u32)&D_NF_000000C9), 0x10));

    for (i = 0; i < (ARRAY_COUNT(dFTManagerDataFiles) + ARRAY_COUNT(gSCManagerFighterFileSizes)) / 2; i++)
    {
        data = dFTManagerDataFiles[i];
        file_size = &gSCManagerFighterFileSizes[i];

        largest_size = 0;

        *data->p_file_main = NULL;

        data->file_main_size = file_size->main;

        if (data_flags & FTDATA_FLAG_MAINMOTION)
        {
            current_size = file_size->mainmotion_largest_anim;

            if (current_size != 0)
            {
                largest_size = current_size;
            }
        }
        if (data_flags & FTDATA_FLAG_SUBMOTION)
        {
            current_size = file_size->submotion_largest_anim;

            if (largest_size < current_size)
            {
                largest_size = current_size;
            }
        }
        data->file_anim_size = largest_size;

        if (heap_size < data->file_anim_size)
        {
            heap_size = data->file_anim_size;
        }
    }
    gFTManagerFigatreeHeapSize = heap_size;

    if (data_flags & FTDATA_FLAG_SUBMOTION)
    {
        scSubsysFighterSetLightParams(45.0F, 45.0F, 0xFF, 0xFF, 0xFF, 0xFF);
    }
}

// 0x800D7594
FTStruct* ftManagerGetNextStructAlloc(void)
{
    FTStruct *current_fighter;
    FTStruct *new_fighter = sFTManagerStructsAllocFree;

    if (new_fighter == NULL)
    {
        while (TRUE)
        {
            syErrorPrintf("couldn\'t get Fighter struct.\n");
            scManagerRunPrintGObjStatus();
        }
    }
    else current_fighter = new_fighter;

    sFTManagerStructsAllocFree = new_fighter->alloc_next;

    return current_fighter;
}

// 0x800D75EC
void ftManagerSetPrevStructAlloc(FTStruct *fp)
{
    fp->alloc_next = sFTManagerStructsAllocFree;
    sFTManagerStructsAllocFree = fp;
}

// 0x800D7604
FTParts* ftManagerGetNextPartsAlloc(void)
{
    FTParts *current_part;
    FTParts *new_part;

    new_part = sFTManagerPartsAllocFree;

    if (new_part == NULL)
    {
        while (TRUE)
        {
            syErrorPrintf("couldn\'t get FighterParts struct.\n");
            scManagerRunPrintGObjStatus();
        }
    }
    current_part = new_part;

    sFTManagerPartsAllocFree = new_part->alloc_next;

    new_part->transform_update_mode =
    new_part->unk_dobjtrans_0x5 =
    new_part->unk_dobjtrans_0x7 = 0;
    new_part->unk_dobjtrans_0x6 = 0;

    new_part->gobj = NULL;
    new_part->is_have_anim = FALSE;

    return current_part;
}

// 0x800D767C
void ftManagerSetPrevPartsAlloc(FTParts *parts)
{
    parts->alloc_next = sFTManagerPartsAllocFree;
    sFTManagerPartsAllocFree = parts;
}

// 0x800D7694
void ftManagerSetupFilesMainKind(s32 fkind)
{
    FTData *data = dFTManagerDataFiles[fkind];

    *data->p_file_main = lbRelocGetFileExternHeap(data->file_main_id, syTaskmanMalloc(lbRelocGetFileSize(data->file_main_id), 0x10));

    if (data->particles_script_lo != 0)
    {
        *data->p_particle = efParticleGetLoadBankID
        (
            data->particles_script_lo, 
            data->particles_script_hi, 
            data->particles_texture_lo, 
            data->particles_texture_hi
        );
    }
}

// 0x800D7710
void ftManagerSetupFilesKind(s32 fkind)
{
    FTData *data = dFTManagerDataFiles[fkind];

    if (data->file_mainmotion_id != 0)
    {
        *data->p_file_mainmotion = lbRelocGetFileStatusBuffer(data->file_mainmotion_id);
    }
    if (data->file_submotion_id != 0)
    {
        *data->p_file_submotion = lbRelocGetFileStatusBuffer(data->file_submotion_id);
    }
    *data->p_file_model = lbRelocGetFileStatusBuffer(data->file_model_id);

    if (data->file_shieldpose_id != 0)
    {
        data->p_file_shieldpose = lbRelocGetFileStatusBuffer(data->file_shieldpose_id);
    }
    if (data->file_special1_id != 0)
    {
        *data->p_file_special1 = lbRelocGetFileStatusBuffer(data->file_special1_id);
    }
    if (data->file_special2_id != 0)
    {
        *data->p_file_special2 = lbRelocGetFileStatusBuffer(data->file_special2_id);
    }
    if (data->file_special3_id != 0)
    {
        *data->p_file_special3 = lbRelocGetFileStatusBuffer(data->file_special3_id);
    }
    if (data->file_special4_id != 0)
    {
        *data->p_file_special4 = lbRelocGetFileStatusBuffer(data->file_special4_id);
    }
    if (data->particles_script_lo != 0)
    {
        *data->p_particle = efParticleGetBankID(data->particles_script_lo);
    }
}

// 0x800D782C
void ftManagerSetupFilesPlayablesAll(void)
{
    s32 i;

    for (i = 0; i <= nFTKindPlayableEnd; i++)
    {
        ftManagerSetupFilesKind(i);
    }
}

// 0x800D786C
void ftManagerSetupFilesAllKind(s32 fkind)
{
    FTData *data = dFTManagerDataFiles[fkind];

    if (*data->p_file_main == NULL)
    {
        ftManagerSetupFilesMainKind(fkind);
        ftManagerSetupFilesKind(fkind);
    }
}

// 0x800D78B4
void* ftManagerAllocFigatreeHeapKind(s32 fkind)
{
    FTData *data = dFTManagerDataFiles[fkind];

    return syTaskmanMalloc(data->file_anim_size, 0x10);
}

// 0x800D78E8
void ftManagerDestroyFighter(GObj *fighter_gobj)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);
    s32 i;

    if (fp->is_attach_effect)
    {
        ftParamProcStopEffect(fighter_gobj);
    }
    for (i = 0; i < ARRAY_COUNT(fp->joints); i++)
    {
        if (fp->joints[i] != NULL)
        {
            FTParts *parts = fp->joints[i]->user_data.p;

            if (parts->gobj != NULL)
            {
                gcEjectGObj(parts->gobj);
            }
            ftManagerSetPrevPartsAlloc(parts);
        }
    }
    ftManagerSetPrevStructAlloc(fp);
    gcEjectGObj(fighter_gobj);
}

// 0x800D7994
void ftManagerDestroyFighterWeapons(GObj *fighter_gobj)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);

    switch (fp->fkind)
    {
    case nFTKindKirby:
    case nFTKindNKirby:
        ftKirbyCopyLinkSpecialNDestroyBoomerang(fighter_gobj);
        break;

    case nFTKindLink:
    case nFTKindNLink:
        ftLinkSpecialNDestroyBoomerang(fighter_gobj);
        break;
    }
}

// 0x800D79F0
void ftManagerInitFighter(GObj *fighter_gobj, FTCreateDesc *ft_desc)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);
    FTAttributes *attr = fp->attr;
    f32 scale;

    fp->lr = ft_desc->lr;
    fp->percent_damage = ft_desc->damage;

    if (fp->pkind != nFTPlayerKindDemo)
    {
        gSCManagerBattleState->players[fp->player].stock_damage_all = fp->percent_damage;
    }
    fp->shield_health = (fp->fkind == nFTKindYoshi) ? 55 : 55;

#ifdef BUGFIX_CRASH_SELFDESTRUCT
    /*
     * shield_player is never explicitly initialized during creation, so its value is 0.
     * This can result in a crash if a player other than P1 self-destructs
     * without getting their shield hit, as shield_player is moved to damage_player,
     * which is then used to award points the player who caused the shield break.
     * This results in an invalid GObj* being accessed without a NULL check, crashing the game.
     */
    fp->shield_player = -1;
#endif

    fp->unk_ft_0x38 = 0.0F;
    fp->hitlag_tics = 0;
    fp->is_knockback_paused = FALSE;

    ftPhysicsStopVelAll(fighter_gobj);

    fp->jumps_used = 0;
    fp->is_reflect = FALSE;
    fp->is_absorb = FALSE;
    fp->is_shield = FALSE;
    fp->is_attach_effect = FALSE;
    fp->is_ignore_jostle = FALSE;

    fp->cliffcatch_wait = 0;
    fp->tics_since_last_z = 0;

    fp->acid_wait = fp->twister_wait = fp->tarucann_wait = fp->damagefloor_wait = 0;

    fp->unk_ft_0x7AC = 0;
    fp->attack_damage = 0;
    fp->attack_attack_count = 0;
    fp->attack_shield_push = 0;
    fp->shield_damage = 0;
    fp->damage_lag = 0;
    fp->damage_queue = 0;
    fp->damage_player = -1;
    fp->damage_object_class = 0;
    fp->damage_object_kind = 0;
    fp->damage_count = 0;
    fp->damage_kind = nFTDamageKindDefault;
    fp->damage_heal = 0;
    fp->damage_joint_id = 0;
    fp->invincible_tics = 0;
    fp->intangible_tics = 0;
    fp->star_invincible_tics = 0;

    fp->hitstatus = nGMHitStatusNormal;
    fp->star_hitstatus = nGMHitStatusNormal;
    fp->special_hitstatus = nGMHitStatusNormal;

    fp->throw_gobj = NULL;
    fp->catch_gobj = NULL;
    fp->capture_gobj = NULL;
    fp->unk_ft_0x192_b3 = FALSE;

    fp->item_gobj = NULL;

    fp->reflect_lr = 0;
    fp->absorb_lr = 0;

    fp->reflect_damage = 0;

    fp->spc_coll = NULL;

    fp->attack1_followup_frames = 0.0F;
    fp->unk_ft_0x7A0 = 0.0F;
    fp->attack_knockback = 0.0F;
    fp->attack_rebound = 0.0F;
    fp->damage_stack = 0.0F;
    fp->knockback_resist_status = 0.0F;
    fp->knockback_resist_passive = 0.0F;
    fp->damage_knockback = 0.0F;
    fp->hitlag_mul = 1.0F;
    fp->shield_lifeup_wait = 10.0F;

    fp->is_fast_fall = FALSE;

    fp->player_number = gFTManagerPlayersNum++;

    fp->publicity_knockback = 0.0F;

    fp->is_hitstun = FALSE;
    fp->is_use_animlocks = FALSE;

    fp->shuffle_frame_index = fp->shuffle_index_max = 0;

    fp->is_use_fogcolor = FALSE;

    fp->is_shuffle_electric = FALSE;
    fp->shuffle_tics = 0;

    fp->attack_id = nFTMotionAttackIDNone;
    fp->motion_count = 0;
    fp->stat_flags.stat_attack_id = nFTStatusAttackIDNone;
    fp->stat_flags.is_smash_attack = fp->stat_flags.ga = fp->stat_flags.is_projectile = 0;

    fp->stat_count = fp->damage_stat_count = 0;
    fp->damage_stat_flags = fp->stat_flags;

    fp->afterimage.desc_index = 0;

    DObjGetStruct(fighter_gobj)->translate.vec.f = ft_desc->pos;
    DObjGetStruct(fighter_gobj)->scale.vec.f.x = DObjGetStruct(fighter_gobj)->scale.vec.f.y = DObjGetStruct(fighter_gobj)->scale.vec.f.z = attr->size_mul;

    if (fp->pkind != nFTPlayerKindDemo)
    {
        sb32 is_collide_ground = func_ovl2_800F9348(&DObjGetStruct(fighter_gobj)->translate.vec.f, &fp->coll_data.ground_line_id, &fp->coll_data.ground_dist, &fp->coll_data.ground_flags, &fp->coll_data.ground_angle);

        if (is_collide_ground == FALSE)
        {
            fp->coll_data.ground_line_id = -1;
        }
        if ((is_collide_ground != FALSE) && (fp->coll_data.ground_dist > -300.0F) && (fp->fkind != nFTKindBoss))
        {
            fp->ga = nMPKineticsGround;

            DObjGetStruct(fighter_gobj)->translate.vec.f.y += fp->coll_data.ground_dist;

            fp->coll_data.ground_dist = 0;
        }
        else
        {
            fp->ga = nMPKineticsAir;
            fp->jumps_used = 1;
        }
    }
    else
    {
        fp->ga = nMPKineticsAir;
        fp->jumps_used = 1;
    }
    fp->coll_data.pos_curr = DObjGetStruct(fighter_gobj)->translate.vec.f;

    switch (fp->fkind)
    {
    case nFTKindMMario:
        fp->knockback_resist_passive = 30.0F;

    case nFTKindMario:
    case nFTKindNMario:
        fp->fighter_vars.mario.is_expend_tornado = FALSE;
        break;

    case nFTKindGDonkey:
        fp->knockback_resist_passive = 48.0F;

    case nFTKindDonkey:
    case nFTKindNDonkey:
        fp->fighter_vars.donkey.charge_level = 0;
        break;

    case nFTKindSamus:
    case nFTKindNSamus:
        fp->fighter_vars.samus.charge_level = 0;
        fp->fighter_vars.samus.charge_recoil = 0;
        break;

    case nFTKindLuigi:
    case nFTKindNLuigi:
        fp->fighter_vars.mario.is_expend_tornado = FALSE;
        break;

    case nFTKindCaptain:
    case nFTKindNCaptain:
        fp->fighter_vars.captain.falcon_punch_unk = 0;
        break;

    case nFTKindKirby:
    case nFTKindNKirby:
        fp->fighter_vars.kirby.copy_id = ft_desc->copy_kind;

        fp->fighter_vars.kirby.copysamus_charge_level = 0;
        fp->fighter_vars.kirby.copysamus_charge_recoil = 0;
        fp->fighter_vars.kirby.copydonkey_charge_level = 0;
        fp->fighter_vars.kirby.copycaptain_falcon_punch_unk = 0;
        fp->fighter_vars.kirby.copypurin_unk = 0;
        fp->fighter_vars.kirby.copylink_boomerang_gobj = NULL;

        if (ft_desc->copy_kind == nFTKindKirby)
        {
            fp->fighter_vars.kirby.is_ignore_losecopy = FALSE;
        }
        else fp->fighter_vars.kirby.is_ignore_losecopy = TRUE;

        if (fp->fkind == nFTKindKirby)
        {
            ftKirbyCopy *copy_data = (ftKirbyCopy*) ((uintptr_t)gFTDataKirbyMainMotion + (intptr_t)&lFTKirbySpecialNCopyData);

            ftParamSetModelPartDefaultID(fighter_gobj, FTKIRBY_COPY_MODELPARTS_JOINT, copy_data[fp->fighter_vars.kirby.copy_id].copy_modelpart_id);
        }
        break;

    case nFTKindLink:
    case nFTKindNLink:
        fp->fighter_vars.link.boomerang_gobj = NULL;

        ftParamSetModelPartDefaultID(fighter_gobj, 0x15, -1);
        ftParamSetModelPartDefaultID(fighter_gobj, 0x13, 0);
        break;

    case nFTKindPurin:
    case nFTKindNPurin:
        fp->fighter_vars.purin.unk_0x0 = 0;
        break;

    case nFTKindBoss:
        fp->fighter_vars.boss.p = &fp->fighter_vars.boss.s;
        fp->fighter_vars.boss.p->wait_div = 1.0F;
        fp->fighter_vars.boss.p->status_id = -1;
        fp->fighter_vars.boss.p->status_id_random = -1;
        fp->fighter_vars.boss.p->status_id_guard = 0;

        if (fp->pkind != nFTPlayerKindDemo)
        {
            ftBossCommonSetNextAttackWait(fighter_gobj);
            ftBossCommonSetDefaultLineID(fighter_gobj);
        }
        break;
    }
    ftParamClearAttackCollAll(fighter_gobj);
    ftParamSetHitStatusPartAll(fighter_gobj, nGMHitStatusNormal);
    ftParamResetFighterColAnim(fighter_gobj);
}

// 0x800D7F3C
GObj* ftManagerMakeFighter(FTCreateDesc *ft_desc) // Create fighter
{
    FTStruct *fp;
    GObj *fighter_gobj;
    s32 i;
    FTParts *parts;
    FTAttributes *attr;
    s32 unused;
    DObj *topn_joint;
    FTMesh *ft_mesh;

    fighter_gobj = gcMakeGObjSPAfter(nGCCommonKindFighter, NULL, nGCCommonLinkIDFighter, GOBJ_PRIORITY_DEFAULT);

    gcAddGObjDisplay(fighter_gobj, ft_desc->func_display, FTRENDER_DLLINK_DEFAULT, GOBJ_PRIORITY_DEFAULT, ~0);

    fp = ftManagerGetNextStructAlloc();

    fighter_gobj->user_data.p = fp;

    fp->pkind = ft_desc->pkind;
    fp->fighter_gobj = fighter_gobj;
    fp->fkind = ft_desc->fkind;
    fp->data = dFTManagerDataFiles[fp->fkind];
    attr = fp->attr = (FTAttributes*) ((uintptr_t)*fp->data->p_file_main + (intptr_t)fp->data->o_attributes);
    fp->figatree_heap = ft_desc->figatree_heap;
    fp->team = ft_desc->team;
    fp->player = ft_desc->player;
    fp->stock_count = ft_desc->stock_count;

    if (fp->pkind != nFTPlayerKindDemo)
    {
        gSCManagerBattleState->players[fp->player].stock_count = ft_desc->stock_count;
    }
    fp->detail_curr = fp->detail_base = ft_desc->detail;

    fp->costume = ft_desc->costume;
    fp->shade = ft_desc->shade;

    fp->shade_color.r = (attr->shade_color[fp->shade - 1].r * attr->shade_color[fp->shade - 1].a) / 0xFF;
    fp->shade_color.g = (attr->shade_color[fp->shade - 1].g * attr->shade_color[fp->shade - 1].a) / 0xFF;
    fp->shade_color.b = (attr->shade_color[fp->shade - 1].b * attr->shade_color[fp->shade - 1].a) / 0xFF;

    fp->handicap = ft_desc->handicap;
    fp->level = ft_desc->level;

    fp->card_anim_frame_id = 0;
    fp->unk_ft_0x3C = 0;
    fp->anim_desc.word = 0;

    fp->p_sfx = NULL;
    fp->sfx_id = 0;
    fp->p_voice = NULL;
    fp->voice_id = 0;
    fp->p_loop_sfx = NULL;
    fp->loop_sfx_id = 0;

    fp->effect_joint_array_id = 0;

    fp->is_invisible = FALSE;
    fp->is_hide_shadow = FALSE;

    fp->display_mode = nDBDisplayModeMaster;

    fp->is_playing_sfx = FALSE;
    fp->is_effect_interrupt = FALSE;

    fp->proc_status = NULL;

    fp->unk_ft_0x149 = ft_desc->unk_rebirth_0x1C;
    fp->team_order = ft_desc->team_order;
    fp->dl_link = FTRENDER_DLLINK_DEFAULT;

    fp->is_skip_magnify = ft_desc->is_skip_magnify;

    fp->status_total_tics = 0;

    fp->camera_zoom_frame = attr->camera_zoom;
    fp->camera_zoom_range = 1.0F;

    fp->is_playertag_bossend = FALSE;
    fp->is_limit_map_bounds = FALSE;

    fp->is_have_translate_scale = (attr->translate_scales != NULL) ? TRUE : FALSE;

    for (i = 0; i < ARRAY_COUNT(fp->joints); i++)
    {
        fp->joints[i] = NULL;
    }
    topn_joint = gcAddDObjForGObj(fighter_gobj, NULL);
    fp->joints[nFTPartsJointTopN] = topn_joint;

    lbCommonInitDObjTriTransform(topn_joint, 0x4B, nGCMatrixKindNull, nGCMatrixKindNull);

    fp->joints[nFTPartsJointTopN]->xobjs[0]->unk05 = ft_desc->unk_rebirth_0x1D;

    lbCommonSetupFighterPartsDObjs(DObjGetStruct(fighter_gobj), attr->commonparts_container, fp->detail_curr, &fp->joints[nFTPartsJointCommonStart], attr->setup_parts, 0x4B, 0, 0, fp->costume, fp->unk_ft_0x149);

    for (i = 0; i < ARRAY_COUNT(fp->joints); i++)
    {
        if (fp->joints[i] != NULL)
        {
            fp->joints[i]->user_data.p = ftManagerGetNextPartsAlloc();

            parts = fp->joints[i]->user_data.p;
            parts->flags = attr->commonparts_container->commonparts[fp->detail_curr - nFTPartsDetailStart].flags;
            parts->joint_id = i;

            if (fp->costume != 0)
            {
                if ((attr->mesh != NULL) && (i == attr->mesh->joint_id))
                {
                    ft_mesh = attr->mesh;

                    parts->gobj = gcMakeGObjSPAfter(nGCCommonKindFighterParts, NULL, nGCCommonLinkIDFighterParts, GOBJ_PRIORITY_DEFAULT);

                    gcAddDObjForGObj(parts->gobj, ft_mesh->dl);
                    lbCommonAddMObjForFighterPartsDObj(DObjGetStruct(parts->gobj), ft_mesh->mobjsubs, ft_mesh->costume_matanim_joints, NULL, fp->costume);
                }
            }
        }
    }
    for (i = nFTPartsJointCommonStart; i < ARRAY_COUNT(fp->joints); i++)
    {
        if (fp->joints[i] != NULL)
        {
            fp->modelpart_status[i - nFTPartsJointCommonStart].modelpart_id_base = 
            fp->modelpart_status[i - nFTPartsJointCommonStart].modelpart_id_curr = (fp->joints[i]->display_ptr != NULL) ? 0 : -1;
        }
    }
    for (i = 0; i < ARRAY_COUNT(fp->texturepart_status); i++)
    {
        fp->texturepart_status[i].texture_id_base = fp->texturepart_status[i].texture_id_curr = 0;
    }
    ftParamSetAnimLocks(fp);

    fp->input.pl.stick_range.x = fp->input.pl.stick_range.y = fp->input.pl.stick_prev.x = fp->input.pl.stick_prev.y = fp->input.cp.stick_range.x = fp->input.cp.stick_range.y = 0;
    fp->input.pl.button_hold = fp->input.pl.button_tap = fp->input.cp.button_inputs = 0;

    fp->input.controller = ft_desc->controller;

    fp->input.button_mask_a = ft_desc->button_mask_a;
    fp->input.button_mask_b = ft_desc->button_mask_b;
    fp->input.button_mask_z = ft_desc->button_mask_z;
    fp->input.button_mask_l = ft_desc->button_mask_l;

    fp->tap_stick_x = fp->tap_stick_y = fp->hold_stick_x = fp->hold_stick_y = FTINPUT_STICKBUFFER_FRAMES_MAX;

    for (i = 0; i < ARRAY_COUNT(fp->damage_colls); i++)
    {
        if (attr->damage_colls_desc[i].joint_id != -1)
        {
            fp->damage_colls[i].hitstatus = nGMHitStatusNormal;
            fp->damage_colls[i].joint_id = attr->damage_colls_desc[i].joint_id;
            fp->damage_colls[i].joint = fp->joints[fp->damage_colls[i].joint_id];
            fp->damage_colls[i].placement = attr->damage_colls_desc[i].placement;
            fp->damage_colls[i].is_grabbable = attr->damage_colls_desc[i].is_grabbable;
            fp->damage_colls[i].offset = attr->damage_colls_desc[i].offset;
            fp->damage_colls[i].size = attr->damage_colls_desc[i].size;

            fp->damage_colls[i].size.x *= 0.5F;
            fp->damage_colls[i].size.y *= 0.5F;
            fp->damage_colls[i].size.z *= 0.5F;
        }
        else fp->damage_colls[i].hitstatus = nGMHitStatusNone;
    }
    fp->coll_data.p_translate = &DObjGetStruct(fighter_gobj)->translate.vec.f;
    fp->coll_data.p_lr = &fp->lr;
    fp->coll_data.map_coll = attr->map_coll;
    fp->coll_data.p_map_coll = &fp->coll_data.map_coll;
    fp->coll_data.cliffcatch_coll = attr->cliffcatch_coll;
    fp->coll_data.ignore_line_id = -1;
    fp->coll_data.coll_update_frame = gMPCollisionUpdateFrame;
    fp->coll_data.coll_mask_curr = 0;

    if (fp->pkind != nFTPlayerKindDemo)
    {
        gcAddGObjProcess(fighter_gobj, ftMainProcInterruptMain, nGCProcessKindFunc, 5);
        gcAddGObjProcess(fighter_gobj, ftMainProcPhysicsMapDefault, nGCProcessKindFunc, 4);
        gcAddGObjProcess(fighter_gobj, ftMainProcPhysicsMapCapture, nGCProcessKindFunc, 3);
        gcAddGObjProcess(fighter_gobj, ftMainProcSearchAllCatch, nGCProcessKindFunc, 2);
        gcAddGObjProcess(fighter_gobj, ftMainProcSearchAllHit, nGCProcessKindFunc, 1);
        gcAddGObjProcess(fighter_gobj, ftMainProcUpdateMain, nGCProcessKindFunc, 0);
    }
    else gcAddGObjProcess(fighter_gobj, scSubsysFighterProcUpdate, nGCProcessKindFunc, 5);

    ftManagerInitFighter(fighter_gobj, ft_desc);

    if (fp->pkind == nFTPlayerKindCom)
    {
        ftComputerSetupAll(fighter_gobj);
    }
    if ((fp->pkind == nFTPlayerKindKey) || (fp->pkind == nFTPlayerKindGameKey))
    {
        fp->key.input_seq = NULL;
        fp->key.input_wait = 0;
    }
    switch (fp->pkind)
    {
    case nFTPlayerKindDemo:
        scSubsysFighterSetStatus(fighter_gobj, 0x10000);
        break;

    case nFTPlayerKindKey:
        mpCommonSetFighterWaitOrFall(fighter_gobj);
        break;

    default:
        if (ft_desc->is_skip_entry)
        {
            mpCommonSetFighterWaitOrFall(fighter_gobj);
            ftParamLockPlayerControl(fighter_gobj);
        }
        else
        {
            ftCommonEntrySetStatus(fighter_gobj);
            ftParamLockPlayerControl(fighter_gobj);
        }
        break;
    }
    if ((fp->pkind == nFTPlayerKindMan) || (fp->pkind == nFTPlayerKindCom))
    {
        ftComputerSetFighterDamageDetectSize(fighter_gobj);
    }
    if ((fp->pkind != nFTPlayerKindDemo) && !(ft_desc->is_skip_shadow_setup))
    {
        FTShadowMakeShadow(fighter_gobj);
    }
    return fighter_gobj;
}
