#include <it/item.h>
#include <wp/weapon.h>
#include <ft/fighter.h>
#include <gr/ground.h>
#include <gm/battle.h>
#include <ovl0/reloc_data_mgr.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t D_NF_000000FB;
extern intptr_t D_NF_00B1BCA0;
extern intptr_t D_NF_00B1BDE0;
extern intptr_t D_NF_00B1BDE0_other;
extern intptr_t D_NF_00B1E640;

extern void func_8000F364_FF64(DObj*, u8, void*, void*, void*);
extern void func_8000DF34_EB34(GObj*);
extern void func_8000BED8_CAD8(GObj*, void*, void*, f32);

// // // // // // // // // // // //
//                               //
//   GLOBAL / STATIC VARIABLES   //
//                               //
// // // // // // // // // // // //

// 0x8018D040
void *gITManagerFileData;

// 0x8018D044
s32 gITManagerParticleBankID;

// 0x8018D048
itRandomWeights gITManagerRandomWeights;

// 0x8018D060
itMonsterInfo gITManagerMonsterData;

// 0x8018D090
s32 gITManagerDisplayMode;

// 0x8018D094 - points to next available item struct
itStruct *gITManagerStructsAllocFree;

// 0x8018D098
itSpawnActor gITManagerSpawnActor;

// // // // // // // // // // // //
//                               //
//        INITIALIZED DATA       //
//                               //
// // // // // // // // // // // //

// 0x80189450 - Not uninitialized, so it's hardcoded upon building the ROM? 0 => random, beyond 0 => index of Pokémon to spawn; when in doubt, change to s32
s32 dITManagerMonsterSpawnID = 0;

// 0x80189454
u16 dITManagerAppearanceRatesMin[/* */] = 
{
    I_SEC_TO_FRAMES(0), 
    I_SEC_TO_FRAMES(30),
    I_SEC_TO_FRAMES(25),
    I_SEC_TO_FRAMES(20),
    I_SEC_TO_FRAMES(15),
    I_SEC_TO_FRAMES(10)
};

// 0x80189460
u16 dITManagerAppearanceRatesMax[/* */] =
{
    I_SEC_TO_FRAMES(0),
    I_SEC_TO_FRAMES(30) + 90,
    I_SEC_TO_FRAMES(25) + 75,
    I_SEC_TO_FRAMES(20) + 60,
    I_SEC_TO_FRAMES(15) + 45,
    I_SEC_TO_FRAMES(10) + 30
};

// 0x8018946C
GObj* (*dITManagerMakeProcList[/* */])(GObj*, Vec3f*, Vec3f*, u32) = 
{
    // Containers
    itBoxMakeItem,          // Box
    itTaruMakeItem,         // Barrel
    itCapsuleMakeItem,      // Capsule
    itEggMakeItem,          // Egg

    // Usable items
    itTomatoMakeItem,       // Maxim Tomato
    itHeartMakeItem,        // Heart Container
    itStarMakeItem,         // Star Man
    itSwordMakeItem,        // Beam Sword
    itBatMakeItem,          // Home Run Bat
    itHarisenMakeItem,      // Fan
    itStarRodMakeItem,      // Star Rod
    itLGunMakeItem,         // Ray Gun
    itFFlowerMakeItem,      // Fire Flower
    itHammerMakeItem,       // Hammer
    itMSBombMakeItem,       // Motion-sensor Bomb
    itBombHeiMakeItem,      // Bob-omb
    itNBumperMakeItem,      // Normal Bumper
    itGShellMakeItem,       // Green Shell
    itRShellMakeItem,       // Red Shell
    itMBallMakeItem,        // Poké Ball

    // Fighter items
    NULL,                   // Ness' PK Fire
    NULL,                   // Link's Bomb

    // Stage items
    itPowerBlockMakeItem,   // Mushroom Kingdom POW Block
    itGBumperMakeItem,      // Common Stage Bumper
    itPakkunMakeItem,       // Mushroom Kingdom Piranha Plant
    itTargetMakeItem,       // Bonus Stage Target
    itRBombMakeItem,        // Race to the Finish Bomb
    itGLuckyMakeItem,       // Saffron City Chansey
    itMarumineMakeItem,     // Saffron City Electrode
    itHitokageMakeItem,     // Saffron City Charmander
    itFushigibanaMakeItem,  // Saffron City Venusaur
    itPorygonMakeItem,      // Saffron City Porygon

    // Pokémon items
    itIwarkMakeItem,        // Poké Ball Onix
    itKabigonMakeItem,      // Poké Ball Snorlax
    itTosakintoMakeItem,    // Poké Ball Goldeen
    itNyarsMakeItem,        // Poké Ball Meowth
    itLizardonMakeItem,     // Poké Ball Charizard
    itSpearMakeItem,        // Poké Ball Beedrill
    itKamexMakeItem,        // Poké Ball Blastoise
    itMLuckyMakeItem,       // Poké Ball Chansey
    itStarmieMakeItem,      // Poké Ball Starmie
    itSawamuraMakeItem,     // Poké Ball Hitmonlee
    itDogasMakeItem,        // Poké Ball Koffing
    itPippiMakeItem,        // Poké Ball Clefairy
    itMewMakeItem           // Poké Ball Mew
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8016DEA0
void itManagerInitItems(void) // Many linker things here
{
    itStruct *ip;
    s32 i;

    gITManagerStructsAllocFree = ip = gsMemoryAlloc(sizeof(itStruct) * ITEM_ALLOC_MAX, 0x8);

    for (i = 0; i < (ITEM_ALLOC_MAX - 1); i++)
    {
        ip[i].alloc_next = &ip[i + 1];
    }
    if (ip != NULL)
    {
        ip[i].alloc_next = NULL;
    }
    gITManagerFileData = (void*)rdManagerGetFileWithExternHeap(&D_NF_000000FB, gsMemoryAlloc(rdManagerGetFileSize(&D_NF_000000FB), 0x10));

    gITManagerParticleBankID = efAllocGetAddParticleBankID(&D_NF_00B1BCA0, &D_NF_00B1BDE0, &D_NF_00B1BDE0_other, &D_NF_00B1E640);

    itManagerSetupContainerDrops();
    itManagerInitMonsterVars();
    ifCommonItemArrowSetAttr();

    gITManagerDisplayMode = dbObject_DisplayMode_Master;
}

// 0x8016DFAC
itStruct* itManagerGetItemSetNextAlloc(void) // Set global Item user_data link pointer to next member
{
    itStruct *new_item = gITManagerStructsAllocFree;
    itStruct *get_item;

    if (new_item == NULL)
    {
        return NULL;
    }
    get_item = new_item;

    gITManagerStructsAllocFree = new_item->alloc_next;

    return get_item;
}

// 0x8016DFDC
void itManagerSetPrevAlloc(itStruct *ip) // Set global Item user_data link pointer to previous member
{
    ip->alloc_next = gITManagerStructsAllocFree;

    gITManagerStructsAllocFree = ip;
}

// 0x8016DFF4
void itManagerDObjSetup(GObj *gobj, DObjDesc *dobj_desc, DObj **p_dobj, u8 transform_kind)
{
    s32 i, index;
    DObj *joint, *dobj_array[18];

    for (i = 0; i < ARRAY_COUNT(dobj_array); i++)
    {
        dobj_array[i] = NULL;
    }
    for (i = 0; dobj_desc->index != ARRAY_COUNT(dobj_array); i++, dobj_desc++)
    {
        index = dobj_desc->index & 0xFFF;

        if (index != 0)
        {
            joint = dobj_array[index] = omAddChildForDObj(dobj_array[index - 1], dobj_desc->display_list);
        }
        else joint = dobj_array[0] = omAddDObjForGObj(gobj, dobj_desc->display_list);
        
        if (i == 1)
        {
            func_8000F364_FF64(joint, transform_kind, NULL, NULL, NULL);
        }
        else if (transform_kind != OMMtx_Transform_Null)
        {
            omAddOMMtxForDObjFixed(joint, transform_kind, NULL);
        }
        joint->translate.vec.f = dobj_desc->translate;
        joint->rotate.vec.f = dobj_desc->rotate;
        joint->scale.vec.f = dobj_desc->scale;

        if (p_dobj != NULL) // I have yet to find a case where this point is actually reached
        {
            p_dobj[i] = joint;
        }
    }
}

// 0x8016E174
GObj* itManagerMakeItem(GObj *spawn_gobj, itCreateDesc *item_desc, Vec3f *pos, Vec3f *vel, u32 flags)
{
    itStruct *ip = itManagerGetItemSetNextAlloc();
    GObj *item_gobj;
    itAttributes *attributes;
    void (*proc_render)(GObj*);
    s32 unused[4];

    if (ip == NULL)
    {
        return NULL;
    }
    item_gobj = omMakeGObjSPAfter(nOMObjKindItem, NULL, GObj_LinkID_Item, GOBJ_LINKORDER_DEFAULT);

    if (item_gobj == NULL)
    {
        itManagerSetPrevAlloc(ip);

        return NULL;
    }
    attributes = (itAttributes*) ((uintptr_t)*item_desc->p_file + (intptr_t)item_desc->o_attributes);

    if (attributes->is_render_colanim)
    {
        proc_render = (attributes->is_render_transparency) ? itRenderProcRenderColAnimXLU : itRenderProcRenderColAnimOPA;
    }
    else proc_render = (attributes->is_render_transparency) ? itRenderProcRenderXLU : itRenderProcRenderOPA;

    omAddGObjRenderProc(item_gobj, proc_render, 11, GOBJ_DLLINKORDER_DEFAULT, -1);

    item_gobj->user_data.p = ip;

    ip->item_gobj = item_gobj;
    ip->owner_gobj = NULL;

    ip->it_kind = item_desc->it_kind;
    ip->type = attributes->type;

    ip->phys_info.vel_air = *vel;
    ip->phys_info.vel_ground = 0.0F;

    ip->attributes = attributes;

    itMainVelSetRotateStepLR(item_gobj);
    itMainResetPlayerVars(item_gobj);

    ip->is_allow_pickup     = FALSE;
    ip->is_hold             = FALSE;
    ip->is_allow_knockback  = FALSE;
    ip->is_unused_item_bool = FALSE;
    ip->is_static_damage    = FALSE;

    ip->pickup_wait         = ITEM_PICKUP_WAIT_DEFAULT;

    ip->percent_damage      = 0;
    ip->hitlag_timer        = 0;
    ip->damage_highest      = 0;
    ip->damage_knockback    = 0.0F;
    ip->damage_queue        = 0;
    ip->damage_lag          = 0;

    ip->times_landed        = 0;
    ip->times_thrown        = 0;

    ip->weight              = attributes->weight;
    ip->is_hitlag_victim    = attributes->is_give_hitlag;
    ip->drop_sfx            = attributes->drop_sfx;
    ip->throw_sfx           = attributes->throw_sfx;
    ip->smash_sfx           = attributes->smash_sfx;

    ip->vel_scale           = F_PCT_TO_DEC(attributes->vel_scale);

    ip->is_damage_all       = FALSE;
    ip->is_thrown           = FALSE; // Applies magnitude and stale multiplier if TRUE and hitbox is active?
    ip->is_attach_surface   = FALSE;

    ip->rotate_step         = 0.0F;

    ip->indicator_gobj      = NULL;
    ip->indicator_timer     = 0;

    ip->item_hit.update_state       = item_desc->update_state;
    ip->item_hit.damage             = attributes->damage;
    ip->item_hit.throw_mul          = 1.0F;
    ip->item_hit.stale              = 1.0F;
    ip->item_hit.element            = attributes->element;
    ip->item_hit.offset[0].x        = attributes->hit_offset1_x;
    ip->item_hit.offset[0].y        = attributes->hit_offset1_y;
    ip->item_hit.offset[0].z        = attributes->hit_offset1_z;
    ip->item_hit.offset[1].x        = attributes->hit_offset2_x;
    ip->item_hit.offset[1].y        = attributes->hit_offset2_y;
    ip->item_hit.offset[1].z        = attributes->hit_offset2_z;
    ip->item_hit.size               = attributes->size * 0.5F;
    ip->item_hit.angle              = attributes->angle;
    ip->item_hit.knockback_scale    = attributes->knockback_scale;
    ip->item_hit.knockback_weight   = attributes->knockback_weight;
    ip->item_hit.knockback_base     = attributes->knockback_base;
    ip->item_hit.can_setoff         = attributes->can_setoff;
    ip->item_hit.shield_damage      = attributes->shield_damage;
    ip->item_hit.hit_sfx            = attributes->hit_sfx;
    ip->item_hit.priority           = attributes->priority;
    ip->item_hit.can_rehit_item     = attributes->can_rehit_item;
    ip->item_hit.can_rehit_fighter  = attributes->can_rehit_fighter;
    ip->item_hit.can_rehit_shield   = FALSE;
    ip->item_hit.can_hop            = attributes->can_hop;
    ip->item_hit.can_reflect        = attributes->can_reflect;
    ip->item_hit.can_shield         = attributes->can_shield;
    ip->item_hit.hitbox_count       = attributes->hitbox_count;
    ip->item_hit.interact_mask      = GMHITCOLLISION_MASK_ALL;

    ip->item_hit.attack_id                  = nFTMotionAttackIDNone;
    ip->item_hit.motion_count               = gmCommon_GetMotionCountInc();
    ip->item_hit.stat_flags.stat_attack_id  = nFTStatusAttackIDNull;
    ip->item_hit.stat_flags.is_smash_attack = ip->item_hit.stat_flags.is_ground_or_air = ip->item_hit.stat_flags.is_projectile = 0;
    ip->item_hit.stat_count                 = gmCommon_GetStatUpdateCountInc();

    itMainClearHitRecord(ip);

    ip->item_hurt.hitstatus     = attributes->hitstatus;
    ip->item_hurt.offset.x      = attributes->hurt_offset.x;
    ip->item_hurt.offset.y      = attributes->hurt_offset.y;
    ip->item_hurt.offset.z      = attributes->hurt_offset.z;
    ip->item_hurt.size.x        = attributes->hurt_size.x * 0.5F;
    ip->item_hurt.size.y        = attributes->hurt_size.y * 0.5F;
    ip->item_hurt.size.z        = attributes->hurt_size.z * 0.5F;
    ip->item_hurt.interact_mask = GMHITCOLLISION_MASK_ALL;

    ip->shield_collide_angle = 0.0F;
    ip->shield_collide_vec.x = 0.0F;
    ip->shield_collide_vec.y = 0.0F;
    ip->shield_collide_vec.z = 0.0F;

    ip->hit_normal_damage  = 0;
    ip->hit_refresh_damage = 0;
    ip->hit_attack_damage  = 0;
    ip->hit_shield_damage  = 0;

    ip->reflect_gobj = NULL;

    if (attributes->model_desc != NULL)
    {
        if (!(attributes->unk_0x10_b1))
        {
            func_8000F720(item_gobj, attributes->model_desc, attributes->mobjsub, NULL, item_desc->transform_types.tk1, item_desc->transform_types.tk2, item_desc->transform_types.unk_dobjtransform_0x2);
        }
        else
        {
            itManagerDObjSetup(item_gobj, attributes->model_desc, NULL, item_desc->transform_types.tk1);

            if (attributes->mobjsub != NULL)
            {
                func_8000F8F4(item_gobj, attributes->mobjsub);
            }
        }
        if ((attributes->anim_joint != NULL) || (attributes->matanim_joint != NULL)) // Runs if item has joint or texture animation on spawn?
        {
            func_8000BED8_CAD8(item_gobj, attributes->anim_joint, attributes->matanim_joint, 0.0F);
            func_8000DF34_EB34(item_gobj);
        }
        func_ovl0_800C9424(DObjGetStruct(item_gobj));
    }
    else omAddDObjForGObj(item_gobj, NULL);
    
    ip->coll_data.p_translate           = &DObjGetStruct(item_gobj)->translate.vec.f;
    ip->coll_data.p_lr                  = &ip->lr;
    ip->coll_data.object_coll.top       = attributes->objectcoll_top;
    ip->coll_data.object_coll.center    = attributes->objectcoll_center;
    ip->coll_data.object_coll.bottom    = attributes->objectcoll_bottom;
    ip->coll_data.object_coll.width     = attributes->objectcoll_width;
    ip->coll_data.p_object_coll         = &ip->coll_data.object_coll;
    ip->coll_data.ignore_line_id        = -1;
    ip->coll_data.coll_update_frame     = gMPCollUpdateFrame;
    ip->coll_data.coll_mask_curr        = 0;
    ip->coll_data.vel_push.x            = 0.0F;
    ip->coll_data.vel_push.y            = 0.0F;
    ip->coll_data.vel_push.z            = 0.0F;

    omAddGObjCommonProc(item_gobj, itProcessProcItemMain, nOMObjProcessKindProc, 3);
    omAddGObjCommonProc(item_gobj, itProcessProcSearchHitAll, nOMObjProcessKindProc, 1);
    omAddGObjCommonProc(item_gobj, itProcessProcHitCollisions, nOMObjProcessKindProc, 0);

    ip->proc_update     = item_desc->proc_update;
    ip->proc_map        = item_desc->proc_map;
    ip->proc_hit        = item_desc->proc_hit;
    ip->proc_shield     = item_desc->proc_shield;
    ip->proc_hop        = item_desc->proc_hop;
    ip->proc_setoff     = item_desc->proc_setoff;
    ip->proc_reflector  = item_desc->proc_reflector;
    ip->proc_damage     = item_desc->proc_damage;
    ip->proc_dead       = NULL;

    ip->coll_data.pos_curr = DObjGetStruct(item_gobj)->translate.vec.f = *pos;

    if (flags & ITEM_FLAG_PROJECT)
    {
        switch (flags & ITEM_MASK_SPAWN_ALL)
        {
        case ITEM_MASK_SPAWN_GROUND:
        case ITEM_MASK_SPAWN_DEFAULT: // Default?
            break;

        case ITEM_MASK_SPAWN_FIGHTER:
            itMapRunCollisionDefault(item_gobj, ftGetStruct(spawn_gobj)->coll_data.p_translate, &ftGetStruct(spawn_gobj)->coll_data);
            break;

        case ITEM_MASK_SPAWN_WEAPON:
            itMapRunCollisionDefault(item_gobj, wpGetStruct(spawn_gobj)->coll_data.p_translate, &wpGetStruct(spawn_gobj)->coll_data);
            break;

        case ITEM_MASK_SPAWN_ITEM:
            itMapRunCollisionDefault(item_gobj, itGetStruct(spawn_gobj)->coll_data.p_translate, &itGetStruct(spawn_gobj)->coll_data);
            break;

        default:
            break;
        }
    }
    ip->ground_or_air = nMPKineticsAir;

    itProcessUpdateHitPositions(item_gobj);
    itMainClearColAnim(item_gobj);

    return item_gobj;
}

// 0x8016EA78
GObj* itManagerMakeItemSetupCommon(GObj *spawn_gobj, s32 index, Vec3f *pos, Vec3f *vel, u32 spawn_flags)
{
    GObj *item_gobj = dITManagerMakeProcList[index](spawn_gobj, pos, vel, spawn_flags);

    if (item_gobj != NULL)
    {
        if (index <= nITKindCommonEnd)
        {
            efManagerItemSpawnSwirlMakeEffect(pos);
            func_ovl3_80172394(item_gobj, FALSE);
        }
    }
    return item_gobj;
}

// 0x8016EB00
itStruct* itManagerGetAllocFree(void)
{
    return gITManagerStructsAllocFree;
}

// 0x8016EB0C
void itManagerSetItemSpawnWait(void)
{
    gITManagerSpawnActor.item_spawn_wait = 
    dITManagerAppearanceRatesMin[gBattleState->item_switch] + 
    mtTrigGetRandomIntRange(dITManagerAppearanceRatesMax[gBattleState->item_switch] - dITManagerAppearanceRatesMin[gBattleState->item_switch]);
}

// 0x8016EB78
void itManagerMakeRandomItem(GObj *item_gobj)
{
    s32 unused;
    s32 index;
    Vec3f pos;
    Vec3f vel;

    if (gBattleState->game_status != gmMatch_GameStatus_Wait)
    {
        if (gITManagerSpawnActor.item_spawn_wait > 0)
        {
            gITManagerSpawnActor.item_spawn_wait--;

            return;
        }
        if (itManagerGetAllocFree() != NULL)
        {
            index = itMainGetWeightedItemID(&gITManagerSpawnActor.weights);

            mpCollisionGetMapObjPositionID(gITManagerSpawnActor.item_mapobjs[mtTrigGetRandomIntRange(gITManagerSpawnActor.item_mapobj_count)], &pos);

            vel.x = vel.y = vel.z = 0.0F;

            func_800269C0_275C0(alSound_SFX_ItemSpawn1);

            itManagerMakeItemSetupCommon(NULL, index, &pos, &vel, ITEM_MASK_SPAWN_DEFAULT);
        }
        itManagerSetItemSpawnWait();
    }
}

// 0x8016EC40 - create item spawner GObj?
GObj* itManagerMakeItemSpawnActor(void)
{
    GObj *gobj;
    s32 i;
    s32 item_count;
    mpItemWeights *item_count_qty;
    s32 item_weights;
    s32 item_mapobj_count;
    s32 item_mpoint_ids[30];
    u32 item_count_toggles;
    s32 j;
    u32 item_id_toggles;
    mpItemWeights *item_weight_qty;
    u32 item_num_toggles;

    if (gBattleState->item_switch != gmMatch_ItemSwitch_None)
    {
        if (gBattleState->item_toggles != 0)
        {
            if (gMPGroundData->item_weights != NULL)
            {
                item_count_qty = gMPGroundData->item_weights;

                item_num_toggles = gBattleState->item_toggles;

                item_count = 0;

                for (i = 0; i <= nITKindCommonEnd; i++, item_num_toggles >>= 1)
                {
                    if (item_num_toggles & 1)
                    {
                        item_count += item_count_qty->item_quantities[i];
                    }
                }
                if (item_count == 0)
                {
                    return NULL;
                }
                gITManagerSpawnActor.weights.item_num = item_count;

                item_mapobj_count = mpCollisionGetMapObjCountKind(nMPMapObjKindItemSpawn);

                if (item_mapobj_count == 0)
                {
                    return NULL;
                }
                if (item_mapobj_count > ARRAY_COUNT(item_mpoint_ids))
                {
                    while (TRUE)
                    {
                        gsFatalPrintF("Item positions are over %d!\n", ARRAY_COUNT(item_mpoint_ids));
                        smRunPrintGObjStatus();
                    }
                }
                gITManagerSpawnActor.item_mapobj_count = item_mapobj_count;
                gITManagerSpawnActor.item_mapobjs = (u8*)gsMemoryAlloc(item_mapobj_count * sizeof(*gITManagerSpawnActor.item_mapobjs), 0);

                mpCollisionGetMapObjIDsKind(nMPMapObjKindItemSpawn, item_mpoint_ids);

                for (i = 0; i < item_mapobj_count; i++)
                {
                    gITManagerSpawnActor.item_mapobjs[i] = item_mpoint_ids[i];
                }
                gobj = omMakeGObjSPAfter(nOMObjKindItem, NULL, 2, GOBJ_LINKORDER_DEFAULT);

                omAddGObjCommonProc(gobj, itManagerMakeRandomItem, nOMObjProcessKindProc, 3);

                item_count_toggles = gBattleState->item_toggles;

                item_weight_qty = gMPGroundData->item_weights;

                for (i = 0, j = 0; i <= nITKindCommonEnd; i++, item_count_toggles >>= 1)
                {
                    if ((item_count_toggles & 1) && (item_weight_qty->item_quantities[i] != 0))
                    {
                        j++;
                    }
                }
                gITManagerSpawnActor.weights.item_count = j;
                gITManagerSpawnActor.weights.item_ids = (u8*)gsMemoryAlloc(j * sizeof(*gITManagerSpawnActor.weights.item_ids), 0x0);
                gITManagerSpawnActor.weights.item_totals = (u16*)gsMemoryAlloc(j * sizeof(*gITManagerSpawnActor.weights.item_totals), 0x2);

                item_id_toggles = gBattleState->item_toggles;

                item_weights = 0;

                for (i = 0, j = 0; i <= nITKindCommonEnd; i++, item_id_toggles >>= 1)
                {
                    if ((item_id_toggles & 1) && (item_weight_qty->item_quantities[i] != 0))
                    {
                        gITManagerSpawnActor.weights.item_ids[j] = i;
                        gITManagerSpawnActor.weights.item_totals[j] = item_weights;
                        item_weights += item_weight_qty->item_quantities[i];

                        j++;
                    }
                }
                itManagerSetItemSpawnWait();

                return gobj;
            }
        }
    }
    return NULL;
}

// 0x8016EF40
void itManagerSetupContainerDrops(void)
{
    s32 item_tenth_floor;
    s32 item_count;
    u32 item_num_toggles;
    u32 item_id_toggles;
    s32 i;
    s32 j;
    s32 item_weights;
    mpItemWeights *item_count_qty;
    mpItemWeights *item_weight_qty;
    s32 item_tenth_round;

    if ((gBattleState->item_switch != gmMatch_ItemSwitch_None) && (gBattleState->item_toggles != 0) && (gMPGroundData->item_weights != NULL))
    {
        item_num_toggles = gBattleState->item_toggles >> nITKindUtilityStart;
        item_count_qty = gMPGroundData->item_weights;

        item_count = 0;

        for (i = nITKindUtilityStart; i <= nITKindUtilityEnd; i++, item_num_toggles >>= 1)
        {
            if (item_num_toggles & 1)
            {
                item_count += item_count_qty->item_quantities[i];
            }
        }
        gITManagerRandomWeights.item_num = item_count;

        if (item_count != 0)
        {
            item_id_toggles = gBattleState->item_toggles >> nITKindUtilityStart;
            item_weight_qty = gMPGroundData->item_weights;

            for (j = 0, i = nITKindUtilityStart; i <= nITKindUtilityEnd; i++, item_id_toggles >>= 1)
            {
                if ((item_id_toggles & 1) && (item_weight_qty->item_quantities[i] != 0))
                {
                    j++;
                }
            }
            j++;

            gITManagerRandomWeights.item_count = j;
            gITManagerRandomWeights.item_ids = (u8*)gsMemoryAlloc(j * sizeof(*gITManagerRandomWeights.item_ids), 0x0);
            gITManagerRandomWeights.item_totals = (u16*)gsMemoryAlloc(j * sizeof(*gITManagerRandomWeights.item_totals), 0x2);

            item_id_toggles = gBattleState->item_toggles >> nITKindUtilityStart;

            item_weights = 0;

            for (j = 0, i = nITKindUtilityStart; i <= nITKindUtilityEnd; i++, item_id_toggles >>= 1)
            {
                if ((item_id_toggles & 1) && (item_weight_qty->item_quantities[i] != 0))
                {
                    gITManagerRandomWeights.item_ids[j] = i;
                    gITManagerRandomWeights.item_totals[j] = item_weights;
                    item_weights += item_weight_qty->item_quantities[i];
                    j++;
                }
            }
            gITManagerRandomWeights.item_ids[j] = nITKindMbMonsterStart;
            gITManagerRandomWeights.item_totals[j] = item_weights;

            item_tenth_round = (gITManagerRandomWeights.item_num * 0.1F);

            if (item_tenth_round != 0)
            {
                item_tenth_floor = item_tenth_round;
            }
            else item_tenth_floor = 1;

            gITManagerRandomWeights.item_num += item_tenth_floor;
        }
    }
    else gITManagerRandomWeights.item_num = 0;
}

// 0x8016F218
void itManagerInitMonsterVars(void)
{
    gITManagerMonsterData.monster_curr = gITManagerMonsterData.monster_prev = U8_MAX;
    gITManagerMonsterData.monster_count = (nITKindMbMonsterEnd - nITKindMbMonsterStart);
}

// 0x8016F238
GObj* itManagerMakeItemID(GObj *spawn_gobj, s32 index, Vec3f *pos, Vec3f *vel, u32 flags)
{
    return dITManagerMakeProcList[index](spawn_gobj, pos, vel, flags);
}
