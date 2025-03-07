#include <ft/fighter.h>
#include <sc/scene.h>

extern alSoundEffect* func_800269C0_275C0(u16);

// // // // // // // // // // // //
//                               //
//   GLOBAL / STATIC VARIABLES   //
//                               //
// // // // // // // // // // // //

// 0x8018CF90
s32 sFTPublicityCommonFramesSince;              // Frames passed since last audience reaction

// 0x8018CF94
u32 sFTPublicityCommonPlayerNum;                // Can go beyond actual max player num? Also, either this...

// 0x8018CF98
f32 sFTPublicityCommonKnockback;                // Last knockback value that prompted audience reaction?

// 0x8018CF9C
alSoundEffect *sFTPublicityCommonALSound;       // Current common reaction sound struct

// 0x8018CFA0
u16 sFTPublicityCommonOrder;                    // Current common reaction's sound effect number

// 0x8018CFA4
sb32 sFTPublicityChantIsInterrupt;              // If TRUE, stop player's crowd chant

// 0x8018CFA8
s32 sFTPublicityChantWait;                      // Wait this much before new audience cheer can occur?

// 0x8018CFAC
s32 sFTPublicityChantPlayerNum;                 // ...or this is u32 and the other s32, not entirely sure which

// 0x8018CFB0
alSoundEffect *sFTPublicityChantALSound;        // Fighter's chant sound struct

// 0x8018CFB4
u16 sFTPublicityChantOrder;                     // Current chant's sound effect number

// 0x8018CFB8
s32 sFTPublicityChantCount;                     // Number of times fighter's name has been chanted

// 0x8018CFBC
u32 sFTPublicityChantID;                        // Sound effect ID of audience chant for fighter

// 0x8018CFC0
s32 sFTPublicityPlayersDown;                    // Number of players too close to the bottom blast zone

// 0x8018CFC4
// s32 D_ovl3_8018CFC4;                         // Might be required padding? Not sure

// 0x8018CFC8                       
u16 sFTPublicityDefeatedVoiceIDs[10];           // Array of announcer voices to play for when a player is defeated  

// 0x8018CFDC
u32 sFTPublicityDefeatedQueueCurrent;           // Current array index to play from queued "<player> defeated" announcement voice IDs

// 0x8018CFE0
u32 sFTPublicityDefeatedQueueEnd;               // Last array index of queued "<player> defeated" announcement voice IDs

// 0x8018CFE4
alSoundEffect *sFTPublicityDefeatedALSound;     // "<player> defeated" announcement voice sound struct

// 0x8018CFE8
u16 sFTPublicityDefeatedCurrentOrder;           // Current "<player> defeated" announcement's sound effect number

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80164AB0
sb32 ftPublicityTryStartChant(GObj *gobj, f32 knockback, s32 player_number)
{
    FTStruct *fp;
    GObj *fighter_gobj = ftParamGetPlayerNumGObj(player_number);
    u16 sfx_id;

    if (fighter_gobj == NULL)
    {
        return FALSE;
    }
    else if ((ftGetStruct(fighter_gobj)->percent_damage < 100) || (sFTPublicityChantWait < 1200))
    {
        return FALSE;
    }
    else if (player_number == sFTPublicityChantPlayerNum)
    {
        return FALSE;
    }
    else sFTPublicityChantID = dFTCommonDataPublicityFighterChantFGMs[ftGetStruct(fighter_gobj)->fkind];

    if (sFTPublicityChantID == nSYAudioFGMVoiceEnd)
    {
        return FALSE;
    }
    if (sFTPublicityChantALSound != NULL)
    {
        sfx_id = sFTPublicityChantALSound->sfx_id;

        if ((sfx_id != 0) && (sfx_id == sFTPublicityChantOrder))
        {
            func_80026738_27338(sFTPublicityChantALSound);
        }
    }
    sFTPublicityChantALSound = func_800269C0_275C0((knockback >= 160.0F) ? nSYAudioVoicePublicityCheer : nSYAudioVoicePublicityAmazed);

    if (sFTPublicityChantALSound != NULL)
    {
        sFTPublicityChantOrder = sFTPublicityChantALSound->sfx_id;
        sFTPublicityChantPlayerNum = player_number;
        sFTPublicityChantCount = 0;

        return TRUE;
    }
    return FALSE;
}

// 0x80164C18
void ftPublicityTryInterruptChant(void)
{
    if ((sFTPublicityChantCount < 9) && (sFTPublicityChantCount >= 3))
    {
        sFTPublicityChantIsInterrupt = TRUE;
    }
}

// 0x80164C44
void ftPublicityPlayCommon(u16 new_sfx)
{
    if (sFTPublicityCommonALSound != NULL)
    {
        u16 current_sfx = sFTPublicityCommonALSound->sfx_id;

        if ((current_sfx != 0) && (current_sfx == sFTPublicityCommonOrder))
        {
            func_80026738_27338(sFTPublicityCommonALSound);
        }
    }
    sFTPublicityCommonALSound = func_800269C0_275C0(new_sfx);

    if (sFTPublicityCommonALSound != NULL)
    {
        sFTPublicityCommonOrder = sFTPublicityCommonALSound->sfx_id;
    }
}

// 0x80164CBC
void ftPublicityCommonStop(void)
{
    if (sFTPublicityCommonALSound != NULL)
    {
        u16 sfx_id = sFTPublicityCommonALSound->sfx_id;

        if ((sfx_id != 0) && (sfx_id == sFTPublicityCommonOrder))
        {
            func_80026738_27338(sFTPublicityCommonALSound);
        }
    }
}

// 0x80164D08
void ftPublicityDecideChant(GObj *gobj, s32 player_num, f32 knockback)
{
    if (knockback >= 130.0F)
    {
        if (ftPublicityTryStartChant(gobj, knockback, player_num) != FALSE)
        {
            ftPublicityCommonStop();
            return;
        }
        else if (knockback >= 160.0F)
        {
            ftPublicityTryInterruptChant();
            ftPublicityPlayCommon(nSYAudioVoicePublicityCheer);
            return;
        }
        else if (player_num == sFTPublicityChantPlayerNum)
        {
            ftPublicityTryInterruptChant();
        }
        ftPublicityPlayCommon(nSYAudioVoicePublicityAmazed);
    }
    else if (knockback >= 100.0F)
    {
        ftPublicityPlayCommon(nSYAudioVoicePublicityGaspClap);
    }
}

// 0x80164DED4
void ftPublicityDecideCommon(GObj *fighter_gobj, s32 player_number, f32 knockback, sb32 is_force_curr_knockback)
{
    if (is_force_curr_knockback != FALSE)
    {
        ftPublicityDecideChant(fighter_gobj, player_number, knockback);
    }
    else if ((player_number == sFTPublicityCommonPlayerNum) && (sFTPublicityCommonFramesSince < 60))
    {
        ftPublicityDecideChant(fighter_gobj, player_number, (knockback > sFTPublicityCommonKnockback) ? knockback : sFTPublicityCommonKnockback);
    }
    else if (knockback >= 160.0F)
    {
        ftPublicityTryInterruptChant();
        ftPublicityPlayCommon(nSYAudioVoicePublicityDamageL);
    }
    else if (knockback >= 130.0F)
    {
        if (player_number == sFTPublicityChantPlayerNum)
        {
            ftPublicityTryInterruptChant();
        }
        ftPublicityPlayCommon(nSYAudioVoicePublicityDamageM);
    }
    else if (knockback >= 100.0F)
    {
        ftPublicityPlayCommon(nSYAudioVoicePublicityDamageS);
    }
    sFTPublicityCommonFramesSince = 0;
    sFTPublicityCommonPlayerNum = player_number;
    sFTPublicityCommonKnockback = knockback;
}

// 0x80164F2C
void ftPublicityCommonCheck(GObj *fighter_gobj, f32 knockback, sb32 is_force_curr_knockback)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);

    if (knockback >= 100.0F) // Check if knockback is over 100 units
    {
        ftPublicityDecideCommon(fighter_gobj, fp->damage_player_number, knockback, is_force_curr_knockback); // Play crowd SFX
    }
}

// 0x80164F70 - Play audience gasp when fighter successfully recovers
void ftPublicityPlayCliffReact(GObj *fighter_gobj, f32 knockback)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);

    if (sFTPublicityChantPlayerNum == fp->player_number)
    {
        ftPublicityTryInterruptChant();
    }
    if (knockback >= 160.0F)
    {
        ftPublicityPlayCommon(nSYAudioVoicePublicityGaspL);
    }
    else if (knockback >= 130.0F)
    {
        ftPublicityPlayCommon(nSYAudioVoicePublicityGaspM);
    }
    else if (knockback >= 100.0F)
    {
        ftPublicityPlayCommon(nSYAudioVoicePublicityGaspS);
    }
}

// 0x80165024
void ftPublicityTryPlayFallSpecialReact(GObj *fighter_gobj)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);
    f32 pos_y = fp->joints[nFTPartsJointTopN]->translate.vec.f.y;

    if ((pos_y >= gMPCollisionEdgeBounds.d2.bottom) || (pos_y < -2400.0F))
    {
        return;
    }
    else if (pos_y >= -300.0F)
    {
        ftPublicityPlayCommon(nSYAudioVoicePublicityGaspL);
    }
    else if (pos_y >= -900.0F)
    {
        ftPublicityPlayCommon(nSYAudioVoicePublicityGaspM);
    }
    else ftPublicityPlayCommon(nSYAudioVoicePublicityGaspS);

    if (sFTPublicityChantPlayerNum == fp->player_number)
    {
        ftPublicityTryInterruptChant();
    }
}

// 0x801650F8
void ftPublicityDefeatedAddID(u16 sfx_id)
{
    sFTPublicityDefeatedVoiceIDs[sFTPublicityDefeatedQueueEnd] = sfx_id;

    sFTPublicityDefeatedQueueEnd++;

    if (sFTPublicityDefeatedQueueEnd == ARRAY_COUNT(sFTPublicityDefeatedVoiceIDs))
    {
        sFTPublicityDefeatedQueueEnd = 0;
    }
}

// 0x80165134
void ftPublicityProcUpdate(GObj *public_gobj)
{
    s32 players_down_bak;
    s32 unused[2];
    GObj *down_gobj;
    GObj *fighter_gobj;

    if (sFTPublicityCommonFramesSince < (U16_MAX + 1))
    {
        sFTPublicityCommonFramesSince++;
    }
    players_down_bak = sFTPublicityPlayersDown;
    sFTPublicityPlayersDown = 0;
    fighter_gobj = gGCCommonLinks[nGCCommonLinkIDFighter];

    down_gobj = NULL;

    while (fighter_gobj != NULL)
    {
        FTStruct *fp = ftGetStruct(fighter_gobj);

        if (!(gSCManagerBattleState->game_rules & SCBATTLE_GAMERULE_STOCK) || (fp->stock_count != -1))
        {
            if (DObjGetStruct(fighter_gobj)->translate.vec.f.y < (gMPCollisionEdgeBounds.d2.bottom - 100.0F)) // 0x80131308 = stage data?
            {
                sFTPublicityPlayersDown++;
            }
            else down_gobj = fighter_gobj;
        }
        fighter_gobj = fighter_gobj->link_next;
    }
    if ((players_down_bak < 3) && (sFTPublicityPlayersDown >= 3))
    {
        ftPublicityPlayCommon(nSYAudioVoicePublicityGaspL);

        if ((down_gobj != NULL) && (sFTPublicityChantPlayerNum == ftGetStruct(down_gobj)->player_number))
        {
            ftPublicityTryInterruptChant();
        }
    }
    if (sFTPublicityChantCount < 9)
    {
        if ((sFTPublicityChantALSound == NULL) || (sFTPublicityChantALSound->sfx_id == 0) || (sFTPublicityChantALSound->sfx_id != sFTPublicityChantOrder))
        {
            sFTPublicityChantCount++;

            if (sFTPublicityChantCount < 9)
            {
                if (sFTPublicityChantIsInterrupt != FALSE)
                {
                    sFTPublicityChantIsInterrupt = FALSE;
                    sFTPublicityChantWait = 0;
                    sFTPublicityChantCount = 9;
                }
                else
                {
                    sFTPublicityChantALSound = func_800269C0_275C0(sFTPublicityChantID);

                    if (sFTPublicityChantALSound != NULL)
                    {
                        sFTPublicityChantOrder = sFTPublicityChantALSound->sfx_id;
                    }
                }
            }
            else
            {
                sFTPublicityChantWait = 0;

                ftPublicityPlayCommon(nSYAudioVoicePublicityCheer);
            }
        }
    }
    else if (sFTPublicityChantWait < 1200)
    {
        sFTPublicityChantWait++;
    }
    if (sFTPublicityDefeatedQueueCurrent != sFTPublicityDefeatedQueueEnd)
    {
        if ((sFTPublicityDefeatedALSound == NULL) || (sFTPublicityDefeatedCurrentOrder == 0) || (sFTPublicityDefeatedALSound->sfx_id != sFTPublicityDefeatedCurrentOrder))
        {
            sFTPublicityDefeatedALSound = func_800269C0_275C0(sFTPublicityDefeatedVoiceIDs[sFTPublicityDefeatedQueueCurrent]);

            if (sFTPublicityDefeatedALSound != NULL)
            {
                sFTPublicityDefeatedCurrentOrder = sFTPublicityDefeatedALSound->sfx_id;
            }
            else sFTPublicityDefeatedCurrentOrder = 0;

            sFTPublicityDefeatedQueueCurrent++;

            if (sFTPublicityDefeatedQueueCurrent == ARRAY_COUNT(sFTPublicityDefeatedVoiceIDs))
            {
                sFTPublicityDefeatedQueueCurrent = 0;
            }
        }
    }
}

// 0x801653E0
void ftPublicityMakeActor(void)
{
    gcAddGObjProcess
    (
        gcMakeGObjSPAfter(nGCCommonKindPublicity, NULL, 0xD, GOBJ_PRIORITY_DEFAULT), 
        ftPublicityProcUpdate, 
        nGCProcessKindFunc, 
        0
    );
    sFTPublicityCommonFramesSince = U16_MAX + 1;
    sFTPublicityCommonPlayerNum = -1;
    sFTPublicityCommonKnockback = 0.0F;
    sFTPublicityCommonALSound = NULL;
    sFTPublicityCommonOrder = 0;
    sFTPublicityChantIsInterrupt = 0;
    sFTPublicityChantWait = 1200;
    sFTPublicityChantPlayerNum = -1;
    sFTPublicityChantCount = 9;
    sFTPublicityPlayersDown = 0;
    sFTPublicityDefeatedALSound = NULL;
    sFTPublicityDefeatedCurrentOrder = 0;
    sFTPublicityDefeatedQueueCurrent = sFTPublicityDefeatedQueueEnd = 0;
}
