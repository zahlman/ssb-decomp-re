#include <ft/fighter.h>
#include <wp/weapon.h>
#include <it/item.h>
#include <gr/ground.h>
#include <gm/battle.h>
#include <sys/thread6.h>

extern ub8 gGM1PGameBonusStarCount;
extern ub8 gGM1PGameBonusGiantImpact;

extern alSoundEffect* func_800269C0_275C0(u16);
extern void gcSetDObjAnimPlaybackRate(GObj*, f32);
extern void func_ovl0_800C8CB8(void*, void*, void*, void*, f32);
extern void func_ovl0_800C8654(u16, f32);
extern void func_ovl0_800C87F4(void*, void*, f32);
extern void func_ovl0_800C9A38();

// // // // // // // // // // // //
//                               //
//   GLOBAL / STATIC VARIABLES   //
//                               //
// // // // // // // // // // // //

/* MARIO FTDATA */

// 0x80130E30
void *gFTDataMarioMain;

// 0x80130E34
void *gFTDataMarioBattleMotion;

// 0x80130E38
void *gFTDataMarioModel;

// 0x80130E3C
void *gFTDataMarioSpecial1;

// 0x80130E40
void *gFTDataMarioSpecial2;

// 0x80130E44
void *gFTDataMarioSpecial3;

// 0x80130E48
u32 gFTDataMarioParticleBankID;

// 0x80130E4C
u32 gFTDataMarioPadding[1];

/* METALMARIO FTDATA */

// 0x80130E50
void *gFTDataMetalMarioMain;

// 0x80130E54
void *gFTDataMetalMarioBattleMotion;

// 0x80130E58
void *gFTDataMetalMarioSubMotion;

// 0x80130E5C
void *gFTDataMetalMarioModel;

// 0x80130E60
void *gFTDataMetalMarioSpecial1;

// 0x80130E64
void *gFTDataMetalMarioSpecial2;

// 0x80130E68
void *gFTDataMetalMarioSpecial3;

// 0x80130E6C
u32 gFTDataMetalMarioParticleBankID;

/* POLYMARIO FTDATA */

// 0x80130E70
void *gFTDataPolyMarioMain;

// 0x80130E74
void *gFTDataPolyMarioSubMotion;

// 0x80130E78
void *gFTDataPolyMarioModel;

// 0x80130E7C
u32 gFTDataPolyMarioParticleBankID;

// 0x80130E80
u32 gFTDataPolyMarioPadding[4];

/* FOX FTDATA */

// 0x80130E90
void *gFTDataFoxMain;

// 0x80130E94
void *gFTDataFoxBattleMotion;

// 0x80130E98
void *gFTDataFoxModel;

// 0x80130E9C
void *gFTDataFoxSpecial1;

// 0x80130EA0
void *gFTDataFoxSpecial2;

// 0x80130EA4
void *gFTDataFoxSpecial3;

// 0x80130EA8
void *gFTDataFoxSpecial4;

// 0x80130EAC
u32 gFTDataFoxParticleBankID;

/* POLYFOX FDATA */

// 0x80130EB0
void *gFTDataPolyFoxMain;

// 0x80130EB4
void *gFTDataPolyFoxSubMotion;

// 0x80130EB8
void *gFTDataPolyFoxModel;

// 0x80130EBC
u32 gFTDataPolyFoxParticleBankID;

// 0x80130EC0
u32 gFTDataPolyFoxPadding[4];

/* DONKEY FTDATA */

// 0x80130ED0
void *gFTDataDonkeyMain;

// 0x80130ED4
void *gFTDataDonkeyBattleMotion;

// 0x80130ED8
void *gFTDataDonkeyModel;

// 0x80130EDC
void *gFTDataDonkeySpecial2;

// 0x80130EE0
u32 gFTDataDonkeyParticleBankID;

// 0x80130EE4
u32 gFTDataDonkeyPadding[3];

/* POLYDONKEY FTDATA */

// 0x80130EF0
void *gFTDataPolyDonkeyMain;

// 0x80130EF4
void *gFTDataPolyDonkeySubMotion;

// 0x80130EF8
void *gFTDataPolyDonkeyModel;

// 0x80130EFC
u32 gFTDataPolyDonkeyParticleBankID;

// 0x80130F00
u32 gFTDataPolyDonkeyPadding[4];

/* GIANTDONKEY FTDATA */

// 0x80130F10
void *gFTDataGiantDonkeyMain;

// 0x80130F14
void *gFTDataGiantDonkeySubMotion;

// 0x80130F18
void *gFTDataGiantDonkeyModel;

// 0x80130F1C
void *gFTDataGiantDonkeySpecial2;

// 0x80130F20
u32 gFTDataGiantDonkeyParticleBankID;

// 0x80130F24
u32 gFTDataGiantDonkeyPadding[3];

/* SAMUS FTDATA */

// 0x80130F30
void *gFTDataSamusMain;

// 0x80130F34
void *gFTDataSamusBattleMotion;

// 0x80130F38
void *gFTDataSamusModel;

// 0x80130F3C
void *gFTDataSamusSpecial1;

// 0x80130F40
void *gFTDataSamusSpecial2;

// 0x80130F44
void *gFTDataSamusSpecial3;

// 0x80130F48
u32 gFTDataSamusParticleBankID;

// 0x80130F4C
u32 gFTDataSamusPadding[1];

/* POLYSAMUS FTDATA */

// 0x80130F50
void *gFTDataPolySamusMain;

// 0x80130F54
void *gFTDataPolySamusSubMotion;

// 0x80130F58
void *gFTDataPolySamusModel;

// 0x80130F5C
u32 gFTDataPolySamusParticleBankID;

// 0x80130F60
u32 gFTDataPolySamusPadding[4];

/* LUIGI FTDATA */

// 0x80130F70
void *gFTDataLuigiMain;

// 0x80130F74
void *gFTDataLuigiBattleMotion;

// 0x80130F78
void *gFTDataLuigiModel;

// 0x80130F7C
void *gFTDataLuigiSpecial1;

// 0x80130F80
void *gFTDataLuigiSpecial2;

// 0x80130F84
void *gFTDataLuigiSpecial3;

// 0x80130F88
u32 gFTDataLuigiParticleBankID;

// 0x80130F8C
u32 gFTDataLuigiPadding[1];

/* POLYLUIGI FTDATA */

// 0x80130F90
void *gFTDataPolyLuigiMain;

// 0x80130F94
void *gFTDataPolyLuigiSubMotion;

// 0x80130F98
void *gFTDataPolyLuigiModel;

// 0x80130F9C
u32 gFTDataPolyLuigiParticleBankID;

// 0x80130FA0
u32 gFTDataPolyLuigiPadding[4];

/* LINK FTDATA */

// 0x80130FB0
void *gFTDataLinkMain;

// 0x80130FB4
void *gFTDataLinkBattleMotion;

// 0x80130FB8
void *gFTDataLinkModel;

// 0x80130FBC
void *gFTDataLinkSpecial1;

// 0x80130FC0
void *gFTDataLinkSpecial2;

// 0x80130FC4
void *gFTDataLinkSpecial3;

// 0x80130FC8
u32 gFTDataLinkParticleBankID;

// 0x80130FCC
u32 gFTDataLinkPadding[1];

/* POLYLINK FTDATA */

// 0x80130FD0
void *gFTDataPolyLinkMain;

// 0x80130FD4
void *gFTDataPolyLinkSubMotion;

// 0x80130FD8
void *gFTDataPolyLinkModel;

// 0x80130FDC
u32 gFTDataPolyLinkParticleBankID;

// 0x80130FE0
u32 gFTDataPolyLinkPadding[4];

/* YOSHI FTDATA */

// 0x80130FF0
void *gFTDataYoshiMain;

// 0x80130FF4
void *gFTDataYoshiBattleMotion;

// 0x80130FF8
void *gFTDataYoshiModel;

// 0x80130FFC
void *gFTDataYoshiSpecial2;

// 0x80131000
void *gFTDataYoshiSpecial3;

// 0x80131004
u32 gFTDataYoshiParticleBankID;

// 0x80131008
u32 gFTDataYoshiPadding[2];

/* POLYYOSHI FTDATA */

// 0x80131010
void *gFTDataPolyYoshiMain;

// 0x80131014
void *gFTDataPolyYoshiSubMotion;

// 0x80131018
void *gFTDataPolyYoshiModel;

// 0x8013101C
u32 gFTDataPolyYoshiParticleBankID;

// 0x80131020
u32 gFTDataPolyYoshiPadding[4];

/* CAPTAIN FTDATA */

// 0x80131030
void *gFTDataCaptainMain;

// 0x80131034
void *gFTDataCaptainBattleMotion;

// 0x80131038
void *gFTDataCaptainModel;

// 0x8013103C
void *gFTDataCaptainSpecial2;

// 0x80131040
void *gFTDataCaptainSpecial3;

// 0x80131044
u32 gFTDataCaptainParticleBankID;

// 0x80131048
u32 gFTDataCaptainPadding[2];

/* POLYCAPTAIN FTDATA */

// 0x80131050
void *gFTDataPolyCaptainMain;

// 0x80131054
void *gFTDataPolyCaptainSubMotion;

// 0x80131058
void *gFTDataPolyCaptainModel;

// 0x8013105C
u32 gFTDataPolyCaptainParticleBankID;

// 0x80131060
u32 gFTDataPolyCaptainPadding[4];

/* KIRBY FTDATA */

// 0x80131070
void *gFTDataKirbyMain;

// 0x80131074
void *gFTDataKirbyBattleMotion;

// 0x80131078
void *gFTDataKirbyModel;

// 0x8013107C
void *gFTDataKirbySpecial2;

// 0x80131080
u32 gFTDataKirbyParticleBankID;

// 0x80131084
u32 gFTDataKirbyPadding[3];

/* POLYKIRBY FTDATA */

// 0x80131090
void *gFTDataPolyKirbyMain;

// 0x80131094
void *gFTDataPolyKirbySubMotion;

// 0x80131098
void *gFTDataPolyKirbyModel;

// 0x8013109C
u32 gFTDataPolyKirbyParticleBankID;

// 0x801310A0
u32 gFTDataPolyKirbyPadding[3];

/* PIKACHU FTDATA */

// 0x801310B0
void *gFTDataPikachuMain;

// 0x801310B4
void *gFTDataPikachuBattleMotion;

// 0x801310B8
void *gFTDataPikachuModel;

// 0x801310BC
void *gFTDataPikachuSpecial1;

// 0x801310C0
void *gFTDataPikachuSpecial2;

// 0x801310C4
void *gFTDataPikachuSpecial3;

// 0x801310C8
u32 gFTDataPikachuParticleBankID;

// 0x801310CC
u32 gFTDataPikachuPadding[1];

/* POLYPIKACHU FTDATA */

// 0x801310D0
void *gFTDataPolyPikachuMain;

// 0x801310D4
void *gFTDataPolyPikachuSubMotion;

// 0x801310D8
void *gFTDataPolyPikachuModel;

// 0x801310DC
u32 gFTDataPolyPikachuParticleBankID;

// 0x801310E0
u32 gFTDataPolyPikachuPadding[4];

/* PURIN FTDATA */

// 0x801310F0
void *gFTDataPurinMain;

// 0x801310F4
void *gFTDataPurinBattleMotion;

// 0x801310F8
void *gFTDataPurinModel;

// 0x801310FC
void *gFTDataPurinSpecial2;

// 0x80131100
u32 gFTDataPurinParticleBankID;

// 0x80131104
u32 gFTDataPurinPadding[3];

/* POLYPURIN FTDATA */

// 0x80131110
void *gFTDataPolyPurinMain;

// 0x80131114
void *gFTDataPolyPurinSubMotion;

// 0x80131118
void *gFTDataPolyPurinModel;

// 0x8013111C
u32 gFTDataPolyPurinParticleBankID;

// 0x80131120
u32 gFTDataPolyPurinPadding[4];

/* NESS FTDATA */

// 0x80131130
void *gFTDataNessMain;

// 0x80131134
void *gFTDataNessBattleMotion;

// 0x80131138
void *gFTDataNessModel;

// 0x8013113C
void *gFTDataNessSpecial1;

// 0x80131140
void *gFTDataNessSpecial2;

// 0x80131144
void *gFTDataNessSpecial3;

// 0x80131148
u32 gFTDataNessParticleBankID;

// 0x8013114C
u32 gFTDataNessPadding[1];

/* POLYNESS FTDATA */

// 0x80131150
void *gFTDataPolyNessMain;

// 0x80131154
void *gFTDataPolyNessSubMotion;

// 0x80131158
void *gFTDataPolyNessModel;

// 0x8013115C
u32 gFTDataPolyNessParticleBankID;

// 0x80131160
u32 gFTDataPolyNessPadding[4];

/* BOSS FTDATA */

// 0x80131170
void *gFTDataBossMain;

// 0x80131174
void *gFTDataBossBattleMotion;

// 0x80131178
void *gFTDataBossModel;

// 0x8013117C
u32 gFTDataBossParticleBankID;

/* MISC. VARIABLES */

// 0x80131180 - stage moving hazards
grObstacle sFTMainGroundObstacles[2];

// 0x80131190 - stage environmental obstacles
grHazard sFTMainGroundHazards[1];

// 0x80131198
s32 sFTMainGroundObstaclesNum;

// 0x8013119C
s32 sFTMainGroundHazardsNum;

// 0x801311A0
sb32 gFTMainIsHurtDetect[GMBATTLE_PLAYERS_MAX];

// 0x801311B0
sb32 gFTMainIsHitDetect[GMBATTLE_PLAYERS_MAX];

// 0x801311C0
s32 sFTMainHitlogID;

// 0x801311C4
s32 sFTPad801311C4;

// 0x801311C8 - 0x10 bytes of padding after this, for mpcoll .bss
ftHitlog sFTMainHitlogs[10];

// // // // // // // // // // // //
//                               //
//        INITALIZED DATA        //
//                               //
// // // // // // // // // // // //

// Hitbox sound effects
// Rows = SFX type
// Columns = SFX level

// 0x80128D00
u16 dFTMainHitCollisionFGMs[/* */][nGMHitLevelEnumMax] =
{
    { nGMSoundFGMPunchS,             nGMSoundFGMPunchM,             nGMSoundFGMPunchL             },    // Punch
    { nGMSoundFGMKickS,              nGMSoundFGMKickM,              nGMSoundFGMKickL              },    // Kick
    { nGMSoundFGMMarioSpecialHiCoin, nGMSoundFGMMarioSpecialHiCoin, nGMSoundFGMMarioSpecialHiCoin },    // Coin
    { nGMSoundFGMBurnS,              nGMSoundFGMBurnM,              nGMSoundFGMBurnL              },    // Burn
    { nGMSoundFGMShockS,             nGMSoundFGMShockM,             nGMSoundFGMShockL             },    // Shock
    { nGMSoundFGMSlashS,             nGMSoundFGMSlashM,             nGMSoundFGMSlashL             },    // Slash
    { nGMSoundFGMHarisenHit,         nGMSoundFGMHarisenHit,         nGMSoundFGMHarisenHit         },    // Fan / Slap
    { nGMSoundFGMPunchM,             nGMSoundFGMPunchL,             nGMSoundFGMBatHit             }     // Bat
};

// 0x80128D30
grHitbox dFTMainGroundHitCollisionAttributes[/* */] =
{
    {  4,  1, 361, 100, 100, 0, nGMHitElementFire  },
    {  5, 10,  90, 100, 200, 0, nGMHitElementFire  },
    {  6, 10,  90, 100, 100, 0, nGMHitElementFire  },
    {  7, 10, 361, 100,  80, 0, nGMHitElementSlash },
    {  8,  1,  90, 100, 100, 0, nGMHitElementFire  },
    {  9,  1,  90, 100, 100, 0, nGMHitElementFire  }
};

/*
    Fighter status files order:
    1. Mario: 0x80129F08
    2. Donkey Kong: 0x80129FBC
    3. Fox: 0x8012A214
    4. Samus: 0x8012A41C
    5. Luigi: 0x8015A4F8
    6. Link: 0x8012A5AC
    7. Kirby: 0x8012A700
    9. Captain Falcon: 0x8012AD7C
    8. Yoshi: 0x8012AEF8
    10. Pikachu: 0x8012B010
    11. Jigglypuff: 0x8012B178
    12. Ness: 0x8012B2B8
    13. Master Hand: 0x8012B4AC
*/

#include <ft/ftcommon/ftcommonstatus.h>
#include <ft/ftchar/ftmario/ftmariostatus.h>
#include <ft/ftchar/ftdonkey/ftdonkeystatus.h>
#include <ft/ftchar/ftfox/ftfoxstatus.h>
#include <ft/ftchar/ftsamus/ftsamusstatus.h>
#include <ft/ftchar/ftluigi/ftluigistatus.h>
#include <ft/ftchar/ftlink/ftlinkstatus.h>
#include <ft/ftchar/ftkirby/ftkirbystatus.h>
#include <ft/ftchar/ftcaptain/ftcaptainstatus.h>
#include <ft/ftchar/ftyoshi/ftyoshistatus.h>
#include <ft/ftchar/ftpikachu/ftpikachustatus.h>
#include <ft/ftchar/ftpurin/ftpurinstatus.h>
#include <ft/ftchar/ftness/ftnessstatus.h>
#include <ft/ftchar/ftboss/ftbossstatus.h>

// 0x8012B740
ftStatusDesc *dFTMainSpecialStatusDescs[/* */] =
{
    dFTMarioSpecialStatusDesc,
    dFTFoxSpecialStatusDesc,
    dFTDonkeySpecialStatusDesc,
    dFTSamusSpecialStatusDesc,
    dFTLuigiSpecialStatusDesc,
    dFTLinkSpecialStatusDesc,
    dFTYoshiSpecialStatusDesc,
    dFTCaptainSpecialStatusDesc,
    dFTKirbySpecialStatusDesc,
    dFTPikachuSpecialStatusDesc,
    dFTPurinSpecialStatusDesc,
    dFTNessSpecialStatusDesc,
    dFTBossSpecialStatusDesc,
    dFTMarioSpecialStatusDesc,
    dFTMarioSpecialStatusDesc,
    dFTFoxSpecialStatusDesc,
    dFTDonkeySpecialStatusDesc,
    dFTSamusSpecialStatusDesc,
    dFTLuigiSpecialStatusDesc,
    dFTLinkSpecialStatusDesc,
    dFTYoshiSpecialStatusDesc,
    dFTCaptainSpecialStatusDesc,
    dFTKirbySpecialStatusDesc,
    dFTPikachuSpecialStatusDesc,
    dFTPurinSpecialStatusDesc,
    dFTNessSpecialStatusDesc,
    dFTDonkeySpecialStatusDesc
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x800DF0F0
void ftMainParseMotionEvent(GObj *fighter_gobj, ftStruct *fp, ftMotionEvent *p_event, u32 ev_kind)
{
    ftScriptPointer *p_goto;
    s32 effect_id;
    s32 i, j;
    sb32 unused;
    ftHitbox *ft_hit;
    s32 hit_id;
    s32 group_id;
    u32 sfx_id;
    s32 joint_id;
    Vec3f effect_offset;
    Vec3f effect_scatter;
    u32 flag;
    Vec3f hurt_offset;
    Vec3f hurt_size;
    ftAttributes *attributes;
    ftMotionEventDamage *p_damage;
    s32 ft_kind;
    s32 script_index;
    s32 slope_contour;
    sb32 unused2;

    switch (ev_kind)
    {
    case nFTMotionEventKindEnd:
        p_event->p_script = NULL;
        break;

    case nFTMotionEventKindSyncWait:
        p_event->frame_timer += ftMotionEventCast(p_event, ftMotionEventWait)->frames;

        ftMotionEventAdvance(p_event, ftMotionEventWait);
        break;

    case nFTMotionEventKindAsyncWait:
        p_event->frame_timer = ftMotionEventCast(p_event, ftMotionEventWait)->frames - fighter_gobj->anim_frame;

        ftMotionEventAdvance(p_event, ftMotionEventWait);
        break;

    case nFTMotionEventKindMakeHit:
    case nFTMotionEventKindMakeHitScaleOffset:
        if (fp->status_info.pl_kind != nFTPlayerKindDemo)
        {
            hit_id = ftMotionEventCast(p_event, ftMotionEventMakeHit1)->hit_id;
            ft_hit = &fp->fighter_hit[hit_id];

            if ((ft_hit->update_state == nGMHitUpdateDisable) || (ft_hit->group_id != ftMotionEventCast(p_event, ftMotionEventMakeHit1)->group_id))
            {
                ft_hit->group_id = ftMotionEventCast(p_event, ftMotionEventMakeHit1)->group_id;
                ft_hit->update_state = nGMHitUpdateNew;
                fp->is_hitbox_active = TRUE;

                for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
                {
                    if ((i != hit_id) && (fp->fighter_hit[i].update_state != nGMHitUpdateDisable) && (ft_hit->group_id == fp->fighter_hit[i].group_id))
                    {
                        for (j = 0; j < ARRAY_COUNT(ft_hit->hit_targets); j++)
                        {
                            ft_hit->hit_targets[j] = fp->fighter_hit[i].hit_targets[j];
                        }
                        break;
                    }
                }
                if (i == ARRAY_COUNT(fp->fighter_hit))
                {
                    ftParamClearHitRecordID(fp, hit_id);
                }
            }
            ft_hit->joint_id = ftParamGetJointID(fp, ftMotionEventCast(p_event, ftMotionEventMakeHit1)->joint_id);
            ft_hit->joint = fp->joint[ft_hit->joint_id];
            ft_hit->damage = ftMotionEventCast(p_event, ftMotionEventMakeHit1)->damage;
            ft_hit->can_rebound = ftMotionEventCast(p_event, ftMotionEventMakeHit1)->can_rebound;
            ft_hit->element = ftMotionEventCast(p_event, ftMotionEventMakeHit1)->element;

            ftMotionEventAdvance(p_event, ftMotionEventMakeHit1);

            ft_hit->size = ftMotionEventCast(p_event, ftMotionEventMakeHit2)->size * 0.5F;
            ft_hit->offset.x = ftMotionEventCast(p_event, ftMotionEventMakeHit2)->off_x;

            ftMotionEventAdvance(p_event, ftMotionEventMakeHit2);

            ft_hit->offset.y = ftMotionEventCast(p_event, ftMotionEventMakeHit3)->off_y;
            ft_hit->offset.z = ftMotionEventCast(p_event, ftMotionEventMakeHit3)->off_z;

            ftMotionEventAdvance(p_event, ftMotionEventMakeHit3);

            ft_hit->angle = ftMotionEventCast(p_event, ftMotionEventMakeHit4)->angle;
            ft_hit->knockback_scale = ftMotionEventCast(p_event, ftMotionEventMakeHit4)->knockback_scale;
            ft_hit->knockback_weight = ftMotionEventCast(p_event, ftMotionEventMakeHit4)->knockback_weight;

            ft_hit->is_hit_air = ftMotionEventCast(p_event, ftMotionEventMakeHit4)->is_hit_ground_air & 1;           // Why?
            ft_hit->is_hit_ground = (ftMotionEventCast(p_event, ftMotionEventMakeHit4)->is_hit_ground_air & 2) >> 1; // ???

            ftMotionEventAdvance(p_event, ftMotionEventMakeHit4);

            ft_hit->shield_damage = ftMotionEventCast(p_event, ftMotionEventMakeHit5)->shield_damage;

            ft_hit->sfx_level = ftMotionEventCast(p_event, ftMotionEventMakeHit5)->sfx_level;
            ft_hit->sfx_kind = ftMotionEventCast(p_event, ftMotionEventMakeHit5)->sfx_kind;

            ft_hit->knockback_base = ftMotionEventCast(p_event, ftMotionEventMakeHit5)->knockback_base;

            ftMotionEventAdvance(p_event, ftMotionEventMakeHit5);

            ft_hit->is_scale_pos = (ev_kind == nFTMotionEventKindMakeHitScaleOffset) ? TRUE : FALSE;

            ft_hit->attack_id = fp->attack_id;

            ft_hit->motion_count = fp->motion_count;

            ft_hit->damage = ftParamGetStaledDamage(fp->player, ft_hit->damage, ft_hit->attack_id, ft_hit->motion_count);
        }
        else ftMotionEventAdvance(p_event, ftMotionEventMakeHit);
        break;

    case nFTMotionEventKindSetHitOffset:
        hit_id = ftMotionEventCast(p_event, ftMotionEventSetHitOffset1)->hit_id;

        ft_hit = &fp->fighter_hit[hit_id];

        ft_hit->offset.x = ftMotionEventCast(p_event, ftMotionEventSetHitOffset1)->off_x;

        ftMotionEventAdvance(p_event, ftMotionEventSetHitOffset1);

        ft_hit->offset.y = ftMotionEventCast(p_event, ftMotionEventSetHitOffset2)->off_y;
        ft_hit->offset.z = ftMotionEventCast(p_event, ftMotionEventSetHitOffset2)->off_z;

        ftMotionEventAdvance(p_event, ftMotionEventSetHitOffset2);
        break;

    case nFTMotionEventKindSetHitDamage:
        if (fp->status_info.pl_kind != nFTPlayerKindDemo)
        {
            hit_id = ftMotionEventCast(p_event, ftMotionEventSetHitDamage)->hit_id;

            fp->fighter_hit[hit_id].damage = ftMotionEventCast(p_event, ftMotionEventSetHitDamage)->damage;

            ftMotionEventAdvance(p_event, ftMotionEventSetHitDamage);

            fp->fighter_hit[hit_id].damage = ftParamGetStaledDamage(fp->player, fp->fighter_hit[hit_id].damage, fp->fighter_hit[hit_id].attack_id, fp->fighter_hit[hit_id].motion_count);
        }
        else ftMotionEventAdvance(p_event, ftMotionEventSetHitDamage);
        break;

    case nFTMotionEventKindSetHitSize:
        hit_id = ftMotionEventCast(p_event, ftMotionEventSetHitSize)->hit_id;

        fp->fighter_hit[hit_id].size = ftMotionEventCast(p_event, ftMotionEventSetHitSize)->size * 0.5F;

        ftMotionEventAdvance(p_event, ftMotionEventSetHitSize);
        break;

    case nFTMotionEventKindSetHitSoundLevel:
        hit_id = ftMotionEventCast(p_event, ftMotionEventSetHitSound)->hit_id;

        fp->fighter_hit[hit_id].sfx_level = ftMotionEventCast(p_event, ftMotionEventSetHitSound)->sfx_level;

        ftMotionEventAdvance(p_event, ftMotionEventSetHitSound);
        break;

    case nFTMotionEventKindRefrershHitID:
        hit_id = ftMotionEventCast(p_event, ftMotionEventRefrershHitID)->hit_id;

        ftMotionEventAdvance(p_event, ftMotionEventRefrershHitID);

        ftParamRefreshHitID(fighter_gobj, hit_id);
        break;

    case nFTMotionEventKindClearHitID:
        hit_id = ftMotionEventCast(p_event, ftMotionEventClearHitID)->hit_id;

        ftMotionEventAdvance(p_event, ftMotionEventClearHitID);

        fp->fighter_hit[hit_id].update_state = nGMHitUpdateDisable;
        break;

    case nFTMotionEventKindClearHitAll:
        ftParamClearHitAll(fighter_gobj);

        ftMotionEventAdvance(p_event, ftMotionEventClearHitAll);
        break;

    case nFTMotionEventKindSetFighterThrow:
        ftMotionEventAdvance(p_event, ftMotionEventSetFighterThrow1);

        fp->fighter_throw = ftMotionEventCast(p_event, ftMotionEventSetFighterThrow2)->fighter_throw;

        ftMotionEventAdvance(p_event, ftMotionEventSetFighterThrow2);
        break;

    case nFTMotionEventKindPlaySFXStoreInfo:
        if (!(fp->is_playing_sfx))
        {
            fp->p_sfx = func_800269C0_275C0(ftMotionEventCastAdvance(p_event, ftMotionEventPlaySFX)->sfx_id);

            fp->sfx_id = (fp->p_sfx != NULL) ? fp->p_sfx->sfx_id : 0;
        }
        else ftMotionEventAdvance(p_event, ftMotionEventPlaySFX);
        break;

    case nFTMotionEventKindPlaySFX:
        if (!(fp->is_playing_sfx))
        {
            func_800269C0_275C0(ftMotionEventCastAdvance(p_event, ftMotionEventPlaySFX)->sfx_id);
        }
        else ftMotionEventAdvance(p_event, ftMotionEventPlaySFX);
        break;

    case nFTMotionEventKindPlayLoopSFXStoreInfo:
        if (!(fp->is_playing_sfx))
        {
            ftParamPlayLoopSFX(fp, ftMotionEventCastAdvance(p_event, ftMotionEventPlaySFX)->sfx_id);
        }
        else ftMotionEventAdvance(p_event, ftMotionEventPlaySFX);
        break;

    case nFTMotionEventKindStopLoopSFX:
        ftParamStopLoopSFX(fp), ftMotionEventAdvance(p_event, ftMotionEventPlaySFX);
        break;

    case nFTMotionEventKindPlayVoiceStoreInfo:
        if (!(fp->is_playing_sfx) && (fp->attributes->is_have_voice))
        {
            ftParamPlayVoice(fp, ftMotionEventCastAdvance(p_event, ftMotionEventPlaySFX)->sfx_id);
        }
        else ftMotionEventAdvance(p_event, ftMotionEventPlaySFX);
        break;

    case nFTMotionEventKindPlayLoopVoiceStoreInfo:
        if (!(fp->is_playing_sfx) && (fp->attributes->is_have_voice))
        {
            ftParamPlayLoopSFX(fp, ftMotionEventCastAdvance(p_event, ftMotionEventPlaySFX)->sfx_id);
        }
        else ftMotionEventAdvance(p_event, ftMotionEventPlaySFX);
        break;

    case nFTMotionEventKindPlaySmashVoice:
        if (!(fp->is_playing_sfx))
        {
            ftParamPlayVoice(fp, fp->attributes->smash_sfx[mtTrigGetRandomIntRange(ARRAY_COUNT(fp->attributes->smash_sfx))]);

            ftMotionEventAdvance(p_event, ftMotionEventPlaySFX);
        }
        else ftMotionEventAdvance(p_event, ftMotionEventPlaySFX);
        break;

    case nFTMotionEventKindSetAirJumpAdd:
        fp->ga = nMPKineticsAir;

        fp->phys_info.vel_air.z = DObjGetStruct(fighter_gobj)->translate.vec.f.z = 0.0F;

        fp->jumps_used++;

        ftMotionEventAdvance(p_event, ftMotionEventDefault);
        break;

    case nFTMotionEventKindSetAirJumpMax:
        attributes = fp->attributes;

        fp->ga = nMPKineticsAir;

        fp->phys_info.vel_air.z = DObjGetStruct(fighter_gobj)->translate.vec.f.z = 0.0F;

        fp->jumps_used = attributes->jumps_max;

        ftMotionEventAdvance(p_event, ftMotionEventDefault);
        break;

    case nFTMotionEventKindEffect:
    case nFTMotionEventKindEffectScaleOffset:
        if (!(fp->is_playing_effect))
        {
            joint_id = ftParamGetJointID(fp, ftMotionEventCast(p_event, ftMotionEventMakeEffect1)->joint_id);
            effect_id = ftMotionEventCast(p_event, ftMotionEventMakeEffect1)->effect_id;
            flag = ftMotionEventCast(p_event, ftMotionEventMakeEffect1)->flag;

            ftMotionEventAdvance(p_event, ftMotionEventMakeEffect1);

            effect_offset.x = ftMotionEventCast(p_event, ftMotionEventMakeEffect2)->off_x;
            effect_offset.y = ftMotionEventCast(p_event, ftMotionEventMakeEffect2)->off_y;

            ftMotionEventAdvance(p_event, ftMotionEventMakeEffect2);

            effect_offset.z = ftMotionEventCast(p_event, ftMotionEventMakeEffect3)->off_z;
            effect_scatter.x = ftMotionEventCast(p_event, ftMotionEventMakeEffect3)->rng_x;

            ftMotionEventAdvance(p_event, ftMotionEventMakeEffect3);

            effect_scatter.y = ftMotionEventCast(p_event, ftMotionEventMakeEffect4)->rng_y;
            effect_scatter.z = ftMotionEventCast(p_event, ftMotionEventMakeEffect4)->rng_z;

            ftMotionEventAdvance(p_event, ftMotionEventMakeEffect4);

            ftParamMakeEffect(fighter_gobj, effect_id, joint_id, &effect_offset, &effect_scatter, fp->lr, (ev_kind == nFTMotionEventKindEffectScaleOffset) ? TRUE : FALSE, flag);
        }
        else ftMotionEventAdvance(p_event, ftMotionEventMakeEffect);
        break;

    case nFTMotionEventKindSetHitStatusPartAll:
        ftParamSetHitStatusPartAll(fighter_gobj, ftMotionEventCast(p_event, ftMotionEventSetHitStatusAll)->hitstatus);

        ftMotionEventAdvance(p_event, ftMotionEventSetHitStatusAll);
        break;

    case nFTMotionEventKindSetHitStatusPartID:
        ftParamSetHitStatusPartID(fighter_gobj, ftParamGetJointID(fp, ftMotionEventCast(p_event, ftMotionEventSetHitStatusPart)->joint_id), ftMotionEventCast(p_event, ftMotionEventSetHitStatusPart)->hitstatus);

        ftMotionEventAdvance(p_event, ftMotionEventSetHitStatusPart);
        break;

    case nFTMotionEventKindSetHitStatusAll:
        ftParamSetHitStatusAll(fighter_gobj, ftMotionEventCast(p_event, ftMotionEventSetHitStatusAll)->hitstatus);

        ftMotionEventAdvance(p_event, ftMotionEventSetHitStatusAll);
        break;

    case nFTMotionEventKindResetHurtPartAll:
        ftParamResetFighterHurtPartAll(fighter_gobj);

        ftMotionEventAdvance(p_event, ftMotionEventDefault);
        break;

    case nFTMotionEventKindSetHurtPartID:
        joint_id = ftParamGetJointID(fp, ftMotionEventCast(p_event, ftMotionEventSetHurtPart1)->joint_id);

        ftMotionEventAdvance(p_event, ftMotionEventSetHurtPart1);

        hurt_offset.x = ftMotionEventCast(p_event, ftMotionEventSetHurtPart2)->off_x;
        hurt_offset.y = ftMotionEventCast(p_event, ftMotionEventSetHurtPart2)->off_y;

        ftMotionEventAdvance(p_event, ftMotionEventSetHurtPart2);

        hurt_offset.z = ftMotionEventCast(p_event, ftMotionEventSetHurtPart3)->off_z;
        hurt_size.x = ftMotionEventCast(p_event, ftMotionEventSetHurtPart3)->size_x;

        ftMotionEventAdvance(p_event, ftMotionEventSetHurtPart3);

        hurt_size.y = ftMotionEventCast(p_event, ftMotionEventSetHurtPart4)->size_y;
        hurt_size.z = ftMotionEventCast(p_event, ftMotionEventSetHurtPart4)->size_z;

        ftMotionEventAdvance(p_event, ftMotionEventSetHurtPart4);

        ftParamModifyFighterHurtPartID(fighter_gobj, joint_id, &hurt_offset, &hurt_size);
        break;

    case nFTMotionEventKindLoopBegin:
        p_event->p_goto[p_event->script_index] = (void*) ((uintptr_t)p_event->p_script + sizeof(ftMotionEventLoopBegin));

        p_event->script_index++;

        p_event->loop_count[p_event->script_index++ - 1] = ftMotionEventCast(p_event, ftMotionEventLoopBegin)->loop_count, ftMotionEventAdvance(p_event, ftMotionEventLoopBegin);
        break;

    case nFTMotionEventKindLoopEnd:
        if (--p_event->loop_count[p_event->script_index - 2] != 0)
        {
            p_event->p_script = p_event->p_goto[p_event->script_index - 2];
        }
        else ftMotionEventAdvance(p_event, ftMotionEventDefault), p_event->script_index -= 2; // Seems fake, but also impossible to match otherwise???
        break;

    case nFTMotionEventKindSubroutine:
        ftMotionEventAdvance(p_event, ftMotionEventSubroutine1);

        p_event->p_goto[p_event->script_index] = (void*) ((uintptr_t)p_event->p_script + sizeof(ftMotionEventSubroutine2));

        p_event->script_index++;

        p_event->p_script = ftMotionEventCast(p_event, ftMotionEventSubroutine2)->p_goto;
        break;

    case nFTMotionEventKindSubroutineThrown:
        if (fp->throw_gobj != NULL)
        {
            ft_kind = fp->throw_ft_kind;

            ftMotionEventAdvance(p_event, ftMotionEventSubroutineThrown1);

            p_damage = ftMotionEventCast(p_event, ftMotionEventSubroutineThrown2)->p_subroutine;

            if (p_damage->p_script[fp->status_vars.common.damage.script_index][ft_kind] != NULL)
            {
                p_event->p_goto[p_event->script_index] = (void*) ((uintptr_t)p_event->p_script + sizeof(ftMotionEventSubroutineThrown2));

                p_event->script_index++;

                p_event->p_script = p_damage->p_script[fp->status_vars.common.damage.script_index][ft_kind];
            }
            else ftMotionEventAdvance(p_event, ftMotionEventSubroutineThrown2);
        }
        else ftMotionEventAdvance(p_event, ftMotionEventSubroutineThrown);
        break;

    case nFTMotionEventKindReturn:
        p_event->p_script = p_event->p_goto[--p_event->script_index];
        break;

    case nFTMotionEventKindGoto:
        ftMotionEventAdvance(p_event, ftMotionEventGoto1);

        p_event->p_script = ftMotionEventCast(p_event, ftMotionEventGoto2)->p_goto;
        break;

    case nFTMotionEventKindSetParallelScript:
        ftMotionEventAdvance(p_event, ftMotionEventParallel1);

        if (fp->motion_event[0][1].p_script == NULL)
        {
            fp->motion_event[0][1].p_script = fp->motion_event[1][1].p_script = ftMotionEventCast(p_event, ftMotionEventParallel2)->p_goto;

            fp->motion_event[0][1].frame_timer = fp->motion_event[1][1].frame_timer = DObjGetStruct(fighter_gobj)->anim_rate - fighter_gobj->anim_frame;

            fp->motion_event[0][1].script_index = fp->motion_event[1][1].script_index = 0;
        }
        ftMotionEventAdvance(p_event, ftMotionEventParallel2);
        break;

    case nFTMotionEventKindScriptPause:
        ftMotionEventAdvance(p_event, ftMotionEventDefault);

        p_event->frame_timer = F32_MAX;
        break;

    case nFTMotionEventKindSetModelPart:
        ftParamSetModelPartID(fighter_gobj, ftParamGetJointID(fp, ftMotionEventCast(p_event, ftMotionEventSetModelPart)->joint_id), ftMotionEventCast(p_event, ftMotionEventSetModelPart)->mode);

        ftMotionEventAdvance(p_event, ftMotionEventSetModelPart);
        break;

    case nFTMotionEventKindResetModelPartAll:
        ftParamResetModelPartAll(fighter_gobj);

        ftMotionEventAdvance(p_event, ftMotionEventDefault);
        break;

    case nFTMotionEventKindHideModelPartAll:
        ftParamHideModelPartAll(fighter_gobj);

        ftMotionEventAdvance(p_event, ftMotionEventDefault);
        break;

    case nFTMotionEventKindSetTexturePart:
        ftParamSetTexturePartID(fighter_gobj, ftMotionEventCast(p_event, ftMotionEventSetTexturePart)->texture_part_id, ftMotionEventCast(p_event, ftMotionEventSetTexturePart)->frame);

        ftMotionEventAdvance(p_event, ftMotionEventSetTexturePart);
        break;

    case nFTMotionEventKindSetColAnim:
        ftParamCheckSetFighterColAnimID(fighter_gobj, ftMotionEventCast(p_event, ftMotionEventSetColAnim)->colanim_id, ftMotionEventCast(p_event, ftMotionEventSetColAnim)->duration);

        ftMotionEventAdvance(p_event, ftMotionEventSetColAnim);
        break;

    case nFTMotionEventKindResetColAnim:
        ftParamResetStatUpdateColAnim(fighter_gobj);

        ftMotionEventAdvance(p_event, ftMotionEventDefault);
        break;

    case nFTMotionEventKindSetFlag0:
        fp->command_vars.flags.flag0 = ftMotionEventCast(p_event, ftMotionEventSetFlag)->flag;

        ftMotionEventAdvance(p_event, ftMotionEventSetFlag);
        break;

    case nFTMotionEventKindSetFlag1:
        fp->command_vars.flags.flag1 = ftMotionEventCast(p_event, ftMotionEventSetFlag)->flag;

        ftMotionEventAdvance(p_event, ftMotionEventSetFlag);
        break;

    case nFTMotionEventKindSetFlag2:
        fp->command_vars.flags.flag2 = ftMotionEventCast(p_event, ftMotionEventSetFlag)->flag;

        ftMotionEventAdvance(p_event, ftMotionEventSetFlag);
        break;

    case nFTMotionEventKindSetFlag3:
        fp->command_vars.flags.flag3 = ftMotionEventCast(p_event, ftMotionEventSetFlag)->flag;

        ftMotionEventAdvance(p_event, ftMotionEventSetFlag);
        break;

    case nFTMotionEventKindSlopeContour:
        slope_contour = fp->slope_contour;

        fp->slope_contour = ftMotionEventCastAdvance(p_event, ftMotionEventSlopeContour)->mode;

        if (!(slope_contour & fp->slope_contour & 4))
        {
            DObjGetStruct(fighter_gobj)->rotate.vec.f.x = F_CLC_DTOR32(0.0F);
        }
        break;

    case nFTMotionEventKindHideItem:
        fp->is_show_item = ftMotionEventCast(p_event, ftMotionEventShowItem)->flag;

        ftMotionEventAdvance(p_event, ftMotionEventDefault);
        break;

    case nFTMotionEventKindAfterImage:
        fp->afterimage.is_itemswing = ftMotionEventCast(p_event, ftMotionEventAfterImage)->is_itemswing;
        fp->afterimage.drawstatus = ftMotionEventCast(p_event, ftMotionEventAfterImage)->drawstatus;

        ftMotionEventAdvance(p_event, ftMotionEventAfterImage);
        break;

    case nFTMotionEventKindMakeRumble:
        if (fp->status_info.pl_kind != nFTPlayerKindDemo)
        {
            ftParamMakeRumble(fp, ftMotionEventCast(p_event, ftMotionEventMakeRumble)->rumble_id, ftMotionEventCast(p_event, ftMotionEventMakeRumble)->duration);
        }
        ftMotionEventAdvance(p_event, ftMotionEventMakeRumble);
        break;

    case nFTMotionEventKindStopRumble:
        if (fp->status_info.pl_kind != nFTPlayerKindDemo)
        {
            gmRumbleSetRumbleID(fp->player, ftMotionEventCast(p_event, ftMotionEventStopRumble)->rumble_id);
        }
        ftMotionEventAdvance(p_event, ftMotionEventStopRumble);
        break;
    }
}

// 0x800E02A8
void ftMainUpdateMotionEventsNoEffect(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftMotionEvent *p_event;
    u32 ev_kind;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->motion_event); i++)
    {
        p_event = &fp->motion_event[0][i];

        if (p_event->p_script != NULL)
        {
            if (p_event->frame_timer != F32_MAX)
            {
                p_event->frame_timer -= DObjGetStruct(fighter_gobj)->anim_rate;
            }
        loop:
            if (p_event->p_script != NULL)
            {
                if (p_event->frame_timer == F32_MAX)
                {
                    if ((DObjGetStruct(fighter_gobj)->anim_rate <= fighter_gobj->anim_frame)) 
                    {
                        continue;
                    }
                    else p_event->frame_timer = -fighter_gobj->anim_frame;
                }
                else if (p_event->frame_timer > 0.0F) 
                {
                    continue;
                }
                ev_kind = ftMotionEventCast(p_event, ftMotionEventMakeEffect1)->opcode;

                if (((ev_kind == nFTMotionEventKindEffect) || (ev_kind == nFTMotionEventKindEffectScaleOffset)) && (fp->is_effect_interrupt))
                {
                    ftMotionEventAdvance(p_event, ftMotionEventMakeEffect);
                }
                else ftMainParseMotionEvent(fighter_gobj, fp, p_event, ev_kind);

                goto loop;
            }
        }
    }
    if (!(fp->is_effect_interrupt))
    {
        for (i = 0; i < ARRAY_COUNT(fp->motion_event); i++)
        {
            fp->motion_event[1][i] = fp->motion_event[0][i];
        }
    }
}

// 0x800E0478 - Fast forward all fighter-specific events, update only core events (sync timer, async timer, goto, subroutine, etc.)
void ftMainUpdateMotionEventsDefault(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftMotionEvent *p_event;
    u32 ev_kind;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->motion_event); i++)
    {
        p_event = &fp->motion_event[0][i];

        if (p_event->p_script != NULL)
        {
            if (p_event->frame_timer != F32_MAX)
            {
                p_event->frame_timer -= DObjGetStruct(fighter_gobj)->anim_rate;
            }
        loop:
            if (p_event->p_script != NULL)
            {
                if (p_event->frame_timer == F32_MAX)
                {
                    if ((DObjGetStruct(fighter_gobj)->anim_rate <= fighter_gobj->anim_frame)) continue;

                    else p_event->frame_timer = -fighter_gobj->anim_frame;
                }
                else if (p_event->frame_timer > 0.0F) continue;

                ev_kind = ftMotionEventCast(p_event, ftMotionEventDefault)->opcode;

                switch (ev_kind)
                {
                case nFTMotionEventKindClearHitID:
                case nFTMotionEventKindClearHitAll:
                case nFTMotionEventKindSetHitDamage:
                case nFTMotionEventKindSetHitSize:
                case nFTMotionEventKindSetHitSoundLevel:
                case nFTMotionEventKindRefrershHitID:
                case nFTMotionEventKindPlaySFX:
                case nFTMotionEventKindPlayLoopSFXStoreInfo:
                case nFTMotionEventKindStopLoopSFX:
                case nFTMotionEventKindPlayVoiceStoreInfo:
                case nFTMotionEventKindPlayLoopVoiceStoreInfo:
                case nFTMotionEventKindPlaySFXStoreInfo:
                case nFTMotionEventKindPlaySmashVoice:
                case nFTMotionEventKindSetFlag0:
                case nFTMotionEventKindSetFlag1:
                case nFTMotionEventKindSetFlag2:
                case nFTMotionEventKindSetAirJumpAdd:
                case nFTMotionEventKindSetAirJumpMax:
                case nFTMotionEventKindSetColAnim:
                case nFTMotionEventKindResetColAnim:
                case nFTMotionEventKindMakeRumble:
                case nFTMotionEventKindStopRumble:
                case nFTMotionEventKindAfterImage:
                    ftMotionEventAdvance(p_event, ftMotionEventDefault);
                    break;

                case nFTMotionEventKindEffect:
                case nFTMotionEventKindEffectScaleOffset:
                    ftMotionEventAdvance(p_event, ftMotionEventMakeEffect);
                    break;

                case nFTMotionEventKindMakeHit:
                case nFTMotionEventKindMakeHitScaleOffset:
                    ftMotionEventAdvance(p_event, ftMotionEventMakeHit);
                    break;

                case nFTMotionEventKindSetHitOffset:
                    ftMotionEventAdvance(p_event, ftMotionEventSetHitOffset);
                    break;

                default:
                    ftMainParseMotionEvent(fighter_gobj, fp, p_event, ev_kind);
                    break;
                }
                goto loop;
            }
        }
    }
    for (i = 0; i < ARRAY_COUNT(fp->motion_event); i++)
    {
        fp->motion_event[1][i] = fp->motion_event[0][i];
    }
}

// 0x800E0654 - Update only standard events and GFX spawn
void ftMainUpdateMotionEventsDefaultEffect(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftMotionEvent *p_event;
    u32 ev_kind;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->motion_event); i++)
    {
        p_event = &fp->motion_event[1][i];

        if (p_event->p_script != NULL)
        {
            if (p_event->frame_timer != F32_MAX)
            {
                p_event->frame_timer -= DObjGetStruct(fighter_gobj)->anim_rate;
            }
        loop:
            if (p_event->p_script != NULL)
            {
                if (p_event->frame_timer == F32_MAX)
                {
                    if ((DObjGetStruct(fighter_gobj)->anim_rate <= fighter_gobj->anim_frame)) continue;

                    else p_event->frame_timer = -fighter_gobj->anim_frame;
                }
                else if (p_event->frame_timer > 0.0F) continue;

                ev_kind = ftMotionEventCast(p_event, ftMotionEventDefault)->opcode;

                switch (ev_kind)
                {
                case nFTMotionEventKindEnd:
                case nFTMotionEventKindSyncWait:
                case nFTMotionEventKindAsyncWait:
                case nFTMotionEventKindSubroutineThrown:
                case nFTMotionEventKindLoopBegin:
                case nFTMotionEventKindLoopEnd:
                case nFTMotionEventKindSubroutine:
                case nFTMotionEventKindReturn:
                case nFTMotionEventKindGoto:
                case nFTMotionEventKindScriptPause:
                case nFTMotionEventKindEffect:
                case nFTMotionEventKindEffectScaleOffset:
                    ftMainParseMotionEvent(fighter_gobj, fp, p_event, ev_kind);
                    break;

                case nFTMotionEventKindMakeHit:
                case nFTMotionEventKindMakeHitScaleOffset:
                    ftMotionEventAdvance(p_event, ftMotionEventMakeHit);
                    break;

                case nFTMotionEventKindSetHitOffset:
                case nFTMotionEventKindSetFighterThrow:
                case nFTMotionEventKindSetParallelScript:
                    ftMotionEventAdvance(p_event, ftMotionEventDouble);
                    break;

                case nFTMotionEventKindSetHurtPartID:
                    ftMotionEventAdvance(p_event, ftMotionEventSetHurtPart);
                    break;

                default:
                    ftMotionEventAdvance(p_event, ftMotionEventDefault);
                    break;
                }
                goto loop;
            }
        }
    }
}

// 0x800E07D4
void ftMainPlayAnim(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (fp->anim_flags.flags.is_use_transn_joint)
    {
        fp->anim_vel = fp->joint[nFTPartsJointTransN]->translate.vec.f;
    }
    ftParamUpdateAnimKeys(fighter_gobj);
    func_ovl2_800EB648(fp->joint[nFTPartsJointTopN]);
}

// 0x800E0830
void ftMainPlayAnimNoEffect(GObj *fighter_gobj)
{
    ftMainPlayAnim(fighter_gobj);
    ftMainUpdateMotionEventsNoEffect(fighter_gobj);
}

// 0x800E0858
void ftMainPlayAnimDefault(GObj *fighter_gobj)
{
    ftMainPlayAnim(fighter_gobj);
    ftMainUpdateMotionEventsDefault(fighter_gobj);
}

// 0x800E0880
sb32 ftMainUpdateColAnim(gmColAnim *colanim, GObj *fighter_gobj, sb32 is_playing_sfx, sb32 is_playing_effect)
{
    s32 i, j;
    ftStruct *fp;
    gmColScript *cs;
    void *p_script;
    s32 effect_id;
    s32 joint_id;
    u32 flag;
    gmColEventDefault *def;
    Vec3f effect_offset;
    Vec3f effect_scatter;
    u32 ev_kind;
    s32 blend_frames;

    for (i = 0; i < ARRAY_COUNT(colanim->cs); i++)
    {
        cs = &colanim->cs[i]; // What's the point bruh

        if ((colanim->cs[i].p_script != NULL) && (colanim->cs[i].color_event_timer != 0))
        {
            colanim->cs[i].color_event_timer--;
        }
        while ((colanim->cs[i].p_script != NULL) && (cs->color_event_timer == 0))
        {
            ev_kind = gmColEventCast(colanim->cs[i].p_script, gmColEventDefault)->opcode;

            switch (ev_kind)
            {
            case nGMColEventKindEnd:
                for (j = 0; j < ARRAY_COUNT(colanim->cs); j++)
                {
                    if ((j != i) && (colanim->cs[j].p_script != NULL)) break;
                }

                if (j == ARRAY_COUNT(colanim->cs))
                {
                    return TRUE;
                }
                else colanim->cs[i].p_script = NULL;
                break;

            case nGMColEventKindWait:
                colanim->cs[i].color_event_timer = gmColEventCast(colanim->cs[i].p_script, gmColEventDefault)->value1, gmColEventAdvance(colanim->cs[i].p_script, gmColEventDefault);
                break;

            case nGMColEventKindGoto:
                gmColEventAdvance(colanim->cs[i].p_script, gmColEventGoto1);

                colanim->cs[i].p_script = gmColEventCast(colanim->cs[i].p_script, gmColEventGoto2)->p_goto;
                break;

            case nGMColEventKindLoopBegin:
                colanim->cs[i].p_subroutine[colanim->cs[i].script_index++] = (void*) ((uintptr_t)colanim->cs[i].p_script + sizeof(gmColEventLoopBegin));
                colanim->cs[i].p_subroutine[colanim->cs[i].script_index++] = gmColEventCast(colanim->cs[i].p_script, gmColEventLoopBegin)->loop_count, gmColEventAdvance(colanim->cs[i].p_script, gmColEventLoopBegin);
                break;

            case nGMColEventKindLoopEnd:
                if (--colanim->cs[i].loop_count[colanim->cs[i].script_index - 2] != 0)
                {
                    colanim->cs[i].p_script = colanim->cs[i].p_subroutine[colanim->cs[i].script_index - 2];
                }
                else gmColEventAdvance(colanim->cs[i].p_script, gmColEventDefault), colanim->cs[i].script_index -= 2;
                break;

            case nGMColEventKindSubroutine:
                gmColEventAdvance(colanim->cs[i].p_script, gmColEventSubroutine1);

                colanim->cs[i].p_subroutine[colanim->cs[i].script_index++] = (void*) ((uintptr_t)colanim->cs[i].p_script + sizeof(gmColEventSubroutine1));

                colanim->cs[i].p_script = gmColEventCast(colanim->cs[i].p_script, gmColEventSubroutine2)->p_subroutine;
                break;

            case nGMColEventKindReturn:
                colanim->cs[i].p_script = colanim->cs[i].p_subroutine[--colanim->cs[i].script_index];
                break;

            case nGMColEventKindSetParallelScript:
                gmColEventAdvance(colanim->cs[i].p_script, gmColEventParallel1);

                if (colanim->cs[1].p_script == NULL)
                {
                    colanim->cs[1].p_script = gmColEventCast(colanim->cs[i].p_script, gmColEventParallel2)->p_script;
                    colanim->cs[1].color_event_timer = 0;
                    colanim->cs[1].script_index = 0;
                }
                gmColEventAdvance(colanim->cs[i].p_script, gmColEventParallel2);
                break;

            case nGMColEventKindToggleColorOff:
                colanim->is_use_maincolor = colanim->is_use_blendcolor = colanim->skeleton_id = 0;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventDefault);
                break;

            case nGMColEventKindSetColor1:
                colanim->is_use_maincolor = TRUE;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventSetRGBA1);

                colanim->maincolor.r = gmColEventCast(colanim->cs[i].p_script, gmColEventSetRGBA2)->r;
                colanim->maincolor.g = gmColEventCast(colanim->cs[i].p_script, gmColEventSetRGBA2)->g;
                colanim->maincolor.b = gmColEventCast(colanim->cs[i].p_script, gmColEventSetRGBA2)->b;
                colanim->maincolor.a = gmColEventCast(colanim->cs[i].p_script, gmColEventSetRGBA2)->a;

                colanim->maincolor.ir = colanim->maincolor.ig = colanim->maincolor.ib = colanim->maincolor.ia = 0;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventSetRGBA2);
                break;

            case nGMColEventKindSetColor2:
                colanim->is_use_blendcolor = TRUE;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventSetRGBA1);

                colanim->blendcolor.r = gmColEventCast(colanim->cs[i].p_script, gmColEventSetRGBA2)->r;
                colanim->blendcolor.g = gmColEventCast(colanim->cs[i].p_script, gmColEventSetRGBA2)->g;
                colanim->blendcolor.b = gmColEventCast(colanim->cs[i].p_script, gmColEventSetRGBA2)->b;
                colanim->blendcolor.a = gmColEventCast(colanim->cs[i].p_script, gmColEventSetRGBA2)->a;

                colanim->blendcolor.ir = colanim->blendcolor.ig = colanim->blendcolor.ib = colanim->blendcolor.ia = 0;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventSetRGBA2);
                break;

            case nGMColEventKindBlendColor1:
                blend_frames = gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA1)->blend_frames;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventBlendRGBA1);

                colanim->maincolor.ir = (s32)(gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA2)->r - colanim->maincolor.r) / blend_frames;
                colanim->maincolor.ig = (s32)(gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA2)->g - colanim->maincolor.g) / blend_frames;
                colanim->maincolor.ib = (s32)(gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA2)->b - colanim->maincolor.b) / blend_frames;
                colanim->maincolor.ia = (s32)(gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA2)->a - colanim->maincolor.a) / blend_frames;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventBlendRGBA2);
                break;

            case nGMColEventKindBlendColor2:
                blend_frames = gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA1)->blend_frames;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventBlendRGBA1);

                colanim->blendcolor.ir = (s32)(gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA2)->r - colanim->blendcolor.r) / blend_frames;
                colanim->blendcolor.ig = (s32)(gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA2)->g - colanim->blendcolor.g) / blend_frames;
                colanim->blendcolor.ib = (s32)(gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA2)->b - colanim->blendcolor.b) / blend_frames;
                colanim->blendcolor.ia = (s32)(gmColEventCast(colanim->cs[i].p_script, gmColEventBlendRGBA2)->a - colanim->blendcolor.a) / blend_frames;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventBlendRGBA2);
                break;

            case nGMColEventKindEffect:
            case nGMColEventKindEffectScaleOffset:
                if (is_playing_effect == FALSE)
                {
                    fp = ftGetStruct(fighter_gobj);

                    joint_id = ftParamGetJointID(fp, gmColEventCast(colanim->cs[i].p_script, gmColEventMakeEffect1)->joint_id);
                    effect_id = gmColEventCast(colanim->cs[i].p_script, gmColEventMakeEffect1)->effect_id;
                    flag = gmColEventCast(colanim->cs[i].p_script, gmColEventMakeEffect1)->flag;

                    gmColEventAdvance(colanim->cs[i].p_script, gmColEventMakeEffect1);

                    effect_offset.x = gmColEventCast(colanim->cs[i].p_script, gmColEventMakeEffect2)->off_x;
                    effect_offset.y = gmColEventCast(colanim->cs[i].p_script, gmColEventMakeEffect2)->off_y;

                    gmColEventAdvance(colanim->cs[i].p_script, gmColEventMakeEffect2);

                    effect_offset.z = gmColEventCast(colanim->cs[i].p_script, gmColEventMakeEffect3)->off_z;
                    effect_scatter.x = gmColEventCast(colanim->cs[i].p_script, gmColEventMakeEffect3)->rng_x;

                    gmColEventAdvance(colanim->cs[i].p_script, gmColEventMakeEffect3);

                    effect_scatter.y = gmColEventCast(colanim->cs[i].p_script, gmColEventMakeEffect4)->rng_y;
                    effect_scatter.z = gmColEventCast(colanim->cs[i].p_script, gmColEventMakeEffect4)->rng_z;

                    gmColEventAdvance(colanim->cs[i].p_script, gmColEventMakeEffect4);

                    ftParamMakeEffect(fighter_gobj, effect_id, joint_id, &effect_offset, &effect_scatter, fp->lr, (ev_kind == nGMColEventKindEffectScaleOffset) ? TRUE : FALSE, flag);
                }
                else gmColEventAdvance(colanim->cs[i].p_script, gmColEventMakeEffect);
                break;

            case nGMColEventKindSetLight:
                colanim->is_use_light = TRUE;

                colanim->light_angle1 = gmColEventCast(colanim->cs[i].p_script, gmColEventSetLight)->light1;
                colanim->light_angle2 = gmColEventCast(colanim->cs[i].p_script, gmColEventSetLight)->light2;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventSetLight);
                break;

            case nGMColEventKindToggleLightOff:
                colanim->is_use_light = FALSE;

                gmColEventAdvance(colanim->cs[i].p_script, gmColEventDefault);
                break;

            case nGMColEventKindPlaySFX:
                if (is_playing_sfx == FALSE)
                {
                    func_800269C0_275C0(gmColEventCastAdvance(colanim->cs[i].p_script, gmColEventPlaySFX)->sfx_id);
                }
                else gmColEventAdvance(colanim->cs[i].p_script, gmColEventDefault);
                break;

            case nGMColEventKindSetSkeletonID:
                colanim->skeleton_id = gmColEventCastAdvance(colanim->cs[i].p_script, gmColEventDefault)->value1;
                break;

            default:
                break;
            }
        }
    }
    if (colanim->is_use_maincolor)
    {
        colanim->maincolor.r += colanim->maincolor.ir;
        colanim->maincolor.g += colanim->maincolor.ig;
        colanim->maincolor.b += colanim->maincolor.ib;
        colanim->maincolor.a += colanim->maincolor.ia;
    }
    if (colanim->is_use_blendcolor)
    {
        colanim->blendcolor.r += colanim->blendcolor.ir;
        colanim->blendcolor.g += colanim->blendcolor.ig;
        colanim->blendcolor.b += colanim->blendcolor.ib;
        colanim->blendcolor.a += colanim->blendcolor.ia;
    }
    if (colanim->duration != 0)
    {
        colanim->duration--;

        if (colanim->duration == 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}

// 0x800E11C8
void ftMainRunUpdateColAnim(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    while (ftMainUpdateColAnim(&fp->colanim, fighter_gobj, fp->is_playing_sfx, fp->is_playing_effect) != FALSE)
    {
        ftParamResetStatUpdateColAnim(fighter_gobj);
    }
}

// 0x800E1260
void ftMainProcInterruptMain(GObj *fighter_gobj)
{
    ftStruct *this_fp = ftGetStruct(fighter_gobj);
    ftStruct *other_fp;
    ftAttributes *this_attributes;
    ftAttributes *other_attributes;
    ftPlayerInput *pl;
    ftComputerInput *cp;
    gsController *controller;
    GObj *other_gobj;
    f32 jostle_dist_x;
    f32 dist_z;
    sb32 is_check_self;
    sb32 is_jostle;
    u16 button_tap_mask;
    u16 button_press;
    u16 button_press_com;
    f32 this_jostle;

    if (!(this_fp->is_disable_control))
    {
        this_fp->status_info.status_time_spent++;
    }
    if (!(this_fp->is_disable_control))
    {
        this_fp->input.pl.stick_prev.x = this_fp->input.pl.stick_range.x;
        this_fp->input.pl.stick_prev.y = this_fp->input.pl.stick_range.y;

        switch (this_fp->status_info.pl_kind)
        {
        default:
            pl = &this_fp->input.pl;
            break;

        case nFTPlayerKindMan:
            controller = this_fp->input.controller;
            pl = &this_fp->input.pl;

            button_press = controller->button_press;

            if (button_press & R_TRIG)
            {
                button_press |= (A_BUTTON | Z_TRIG);
            }

            pl->stick_range.x = controller->stick_range.x;
            pl->stick_range.y = controller->stick_range.y;

            button_tap_mask = (button_press ^ pl->button_hold) & button_press;

            pl->button_tap = (this_fp->hitlag_timer != 0) ? pl->button_tap | button_tap_mask : button_tap_mask;

            button_tap_mask = (button_press ^ pl->button_hold) & pl->button_hold;

            pl->button_tap_prev = (this_fp->hitlag_timer != 0) ? pl->button_tap_prev | button_tap_mask : button_tap_mask;

            pl->button_hold = button_press;

            break;

        case nFTPlayerKindCom:
            ftComputerProcessAll(fighter_gobj);
            goto next;

        case nFTPlayerKindKey:
        case nFTPlayerKindGameKey:
            ftExplainProcessInputSequence(fighter_gobj);

        next:
            cp = &this_fp->input.cp;
            pl = &this_fp->input.pl;

            button_press_com = this_fp->input.cp.button_inputs;

            if (button_press_com & R_TRIG)
            {
                button_press_com |= (A_BUTTON | Z_TRIG);
            }

            pl->stick_range.x = cp->stick_range.x;
            pl->stick_range.y = cp->stick_range.y;

            button_tap_mask = (button_press_com ^ pl->button_hold) & button_press_com;

            pl->button_tap = (this_fp->hitlag_timer != 0) ? pl->button_tap | button_tap_mask : button_tap_mask;

            button_tap_mask = (button_press_com ^ pl->button_hold) & pl->button_hold;

            pl->button_tap_prev = (this_fp->hitlag_timer != 0) ? pl->button_tap_prev | button_tap_mask : button_tap_mask;

            pl->button_hold = button_press_com;

            break;
        }
        if (pl->stick_range.x > I_CONTROLLER_RANGE_MAX)
        {
            pl->stick_range.x = I_CONTROLLER_RANGE_MAX;
        }
        if (pl->stick_range.x < -I_CONTROLLER_RANGE_MAX)
        {
            pl->stick_range.x = -I_CONTROLLER_RANGE_MAX;
        }
        if (pl->stick_range.y > I_CONTROLLER_RANGE_MAX)
        {
            pl->stick_range.y = I_CONTROLLER_RANGE_MAX;
        }
        if (pl->stick_range.y < -I_CONTROLLER_RANGE_MAX)
        {
            pl->stick_range.y = -I_CONTROLLER_RANGE_MAX;
        }
        if (gSaveData.error_flags & GMBACKUP_ERROR_HALFSTICKRANGE)
        {
            pl->stick_range.x *= 0.5F;
            pl->stick_range.y *= 0.5F;
        }
        if (pl->stick_range.x >= 20)
        {
            if (pl->stick_prev.x >= 20)
            {
                this_fp->tap_stick_x++, this_fp->hold_stick_x++;
            }
            else this_fp->tap_stick_x = this_fp->hold_stick_x = 1;
        }
        else if (pl->stick_range.x <= -20)
        {
            if (pl->stick_prev.x <= -20)
            {
                this_fp->tap_stick_x++, this_fp->hold_stick_x++;
            }
            else this_fp->tap_stick_x = this_fp->hold_stick_x = 1;
        }
        else this_fp->tap_stick_x = this_fp->hold_stick_x = FTINPUT_STICKBUFFER_FRAMES_MAX;

        if (this_fp->tap_stick_x > FTINPUT_STICKBUFFER_FRAMES_MAX)
        {
            this_fp->tap_stick_x = FTINPUT_STICKBUFFER_FRAMES_MAX;
        }
        if (this_fp->hold_stick_x > FTINPUT_STICKBUFFER_FRAMES_MAX)
        {
            this_fp->hold_stick_x = FTINPUT_STICKBUFFER_FRAMES_MAX;
        }
        if (pl->stick_range.y >= 20)
        {
            if (pl->stick_prev.y >= 20)
            {
                this_fp->tap_stick_y++, this_fp->hold_stick_y++;
            }
            else this_fp->tap_stick_y = this_fp->hold_stick_y = 1;
        }
        else if (pl->stick_range.y <= -20)
        {
            if (pl->stick_prev.y <= -20)
            {
                this_fp->tap_stick_y++, this_fp->hold_stick_y++;
            }
            else this_fp->tap_stick_y = this_fp->hold_stick_y = 1;
        }
        else this_fp->tap_stick_y = this_fp->hold_stick_y = FTINPUT_STICKBUFFER_FRAMES_MAX;

        if (this_fp->tap_stick_y > FTINPUT_STICKBUFFER_FRAMES_MAX)
        {
            this_fp->tap_stick_y = FTINPUT_STICKBUFFER_FRAMES_MAX;
        }
        if (this_fp->hold_stick_y > FTINPUT_STICKBUFFER_FRAMES_MAX)
        {
            this_fp->hold_stick_y = FTINPUT_STICKBUFFER_FRAMES_MAX;
        }
    }
    if (this_fp->time_since_last_z < FTINPUT_ZTRIGLAST_FRAMES_MAX)
    {
        this_fp->time_since_last_z++;
    }
    if (this_fp->input.pl.button_tap & this_fp->input.button_mask_z)
    {
        this_fp->time_since_last_z = 0;
    }
    if (this_fp->hitlag_timer != 0)
    {
        this_fp->hitlag_timer--;

        if (this_fp->hitlag_timer == 0)
        {
            this_fp->x192_flag_b6 = FALSE;

            if (this_fp->proc_lagend != NULL)
            {
                this_fp->proc_lagend(fighter_gobj);
            }
        }
    }
    this_fp->is_effect_interrupt = TRUE;

    if (this_fp->hitlag_timer == 0)
    {
        ftMainPlayAnimNoEffect(fighter_gobj);
    }
    ftMainRunUpdateColAnim(fighter_gobj);

    if (this_fp->intangible_timer != 0)
    {
        this_fp->intangible_timer--;

        if (this_fp->intangible_timer == 0)
        {
            this_fp->special_hitstatus = (this_fp->invincible_timer != FALSE) ? nGMHitStatusInvincible : nGMHitStatusNormal;

            if (this_fp->colanim.colanim_id == 0xA)
            {
                ftParamResetStatUpdateColAnim(fighter_gobj);
            }
        }
    }
    if (this_fp->invincible_timer != 0)
    {
        this_fp->invincible_timer--;

        if ((this_fp->invincible_timer == 0) && (this_fp->intangible_timer == 0))
        {
            this_fp->special_hitstatus = nGMHitStatusNormal;

            if (this_fp->colanim.colanim_id == 0xA)
            {
                ftParamResetStatUpdateColAnim(fighter_gobj);
            }
        }
    }
    if (this_fp->star_invincible_timer != 0)
    {
        this_fp->star_invincible_timer--;

        if (this_fp->star_invincible_timer == 0)
        {
            this_fp->star_hitstatus = nGMHitStatusNormal;

            if (this_fp->colanim.colanim_id == 0x4A)
            {
                ftParamResetStatUpdateColAnim(fighter_gobj);
            }
        }
        else if (this_fp->star_invincible_timer == ITSTAR_WARN_BEGIN_FRAME)
        {
            ftParamTryUpdateItemMusic();
        }
    }
    if (this_fp->damage_heal != 0)
    {
        this_fp->damage_heal--;

        if (this_fp->percent_damage != 0)
        {
            this_fp->percent_damage--;

            func_800269C0_275C0(nGMSoundFGMPlayerHeal);

            gBattleState->players[this_fp->player].stock_damage_all = this_fp->percent_damage;
        }
        if (this_fp->percent_damage == 0)
        {
            this_fp->damage_heal = 0;
        }
        if ((this_fp->damage_heal == 0) && (this_fp->colanim.colanim_id == 0x9))
        {
            ftParamResetStatUpdateColAnim(fighter_gobj);
        }
    }
    if ((this_fp->item_hold != NULL) && (this_fp->status_info.status_id != nFTCommonStatusLightGet) && (itGetStruct(this_fp->item_hold)->it_kind == nITKindHammer))
    {
        ftHammerUpdateStats(fighter_gobj);
    }
    if (this_fp->shuffle_timer != 0)
    {
        this_fp->shuffle_timer--;

        this_fp->shuffle_frame_index++;

        if (this_fp->shuffle_frame_index == this_fp->shuffle_index_max)
        {
            this_fp->shuffle_frame_index = 0;
        }
    }
    if (this_fp->proc_effect != NULL)
    {
        this_fp->proc_effect(fighter_gobj);
    }
    if (this_fp->hitlag_timer == 0)
    {
        if ((this_fp->playertag_wait > 1) && !(this_fp->is_disable_control))
        {
            this_fp->playertag_wait--;
        }
        if (this_fp->proc_update != NULL)
        {
            this_fp->proc_update(fighter_gobj);
        }
        if (this_fp->proc_interrupt != NULL)
        {
            this_fp->proc_interrupt(fighter_gobj);
        }
        if (!(this_fp->is_hitstun))
        {
            gBattleState->players[this_fp->player].combo_damage_foe = 0;
            gBattleState->players[this_fp->player].combo_count_foe = 0;
        }
        is_jostle = FALSE;

        this_fp->phys_info.vel_jostle_x = this_fp->phys_info.vel_jostle_z = 0.0F;

        if ((this_fp->ga == nMPKineticsGround) && !(this_fp->is_ignore_jostle))
        {
            other_gobj = gOMObjCommonLinks[nOMObjCommonLinkIDFighter];

            is_check_self = FALSE;

            while (other_gobj != NULL)
            {
                other_fp = ftGetStruct(other_gobj);

                if ((fighter_gobj != other_gobj) && (other_fp->capture_gobj == NULL))
                {
                    if ((other_fp->ga == nMPKineticsGround) && (this_fp->coll_data.ground_line_id == other_fp->coll_data.ground_line_id))
                    {
                        this_attributes = this_fp->attributes;
                        other_attributes = other_fp->attributes;

                        this_jostle = this_fp->attributes->jostle_width;

                        jostle_dist_x = (DObjGetStruct(fighter_gobj)->translate.vec.f.x + (this_attributes->jostle_x * this_fp->lr)) - (DObjGetStruct(other_gobj)->translate.vec.f.x + (other_attributes->jostle_x * other_fp->lr));

                        if (ABS(jostle_dist_x) < (this_jostle + other_attributes->jostle_width))
                        {
                            is_jostle = TRUE;

                            if (jostle_dist_x == 0.0F)
                            {
                                this_fp->phys_info.vel_jostle_x += (6.75F * ((is_check_self != FALSE) ? -1 : 1));
                            }
                            else this_fp->phys_info.vel_jostle_x += (6.75F * ((jostle_dist_x < 0.0F) ? -1 : 1));

                            dist_z = DObjGetStruct(fighter_gobj)->translate.vec.f.z - DObjGetStruct(other_gobj)->translate.vec.f.z;

                            if (dist_z == 0.0F)
                            {
                                if (jostle_dist_x == 0.0F)
                                {
                                    this_fp->phys_info.vel_jostle_z += (3.0F * ((is_check_self != FALSE) ? -1 : 1));
                                }
                                else this_fp->phys_info.vel_jostle_z += (3.0F * ((jostle_dist_x < 0.0F) ? 1 : -1));
                            }
                            else this_fp->phys_info.vel_jostle_z += (3.0F * ((dist_z < 0.0F) ? -1 : 1));
                        }
                    }
                }
                else is_check_self = TRUE;

                other_gobj = other_gobj->link_next;
            }
            if ((is_jostle == FALSE) && (DObjGetStruct(fighter_gobj)->translate.vec.f.z != 0.0F))
            {
                this_fp->phys_info.vel_jostle_z = ((DObjGetStruct(fighter_gobj)->translate.vec.f.z < 0.0F) ? nGMDirectionR : nGMDirectionL) * 3.0F;
            }
        }
    }
    this_fp->coll_data.vel_push.x = this_fp->coll_data.vel_push.y = this_fp->coll_data.vel_push.z = 0.0F;
}

// 0x800E1CF0
void ftMainClearGroundElementsAll(void)
{
    s32 i;

    sFTMainGroundObstaclesNum = sFTMainGroundHazardsNum = 0;

    for (i = 0; i < ARRAY_COUNT(sFTMainGroundObstacles); i++)
    {
        sFTMainGroundObstacles[i].gobj = NULL;
    }
    for (i = 0; i < ARRAY_COUNT(sFTMainGroundHazards); i++)
    {
        sFTMainGroundHazards[i].gobj = NULL;
    }
}

// 0x800E1D48
sb32 ftMainCheckAddGroundObstacle(GObj *gobj, sb32(*proc_update)(GObj*, GObj*, s32*))
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sFTMainGroundObstacles); i++)
    {
        if (sFTMainGroundObstacles[i].gobj == NULL)
        {
            sFTMainGroundObstacles[i].gobj = gobj;
            sFTMainGroundObstacles[i].proc_update = proc_update;
            sFTMainGroundObstaclesNum++;

            return TRUE;
        }
    }
    return FALSE;
}

// 0x800E1D9C
void ftMainClearGroundObstacle(GObj *gobj)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sFTMainGroundObstacles); i++)
    {
        if (sFTMainGroundObstacles[i].gobj == gobj)
        {
            sFTMainGroundObstacles[i].gobj = NULL;
            sFTMainGroundObstaclesNum--;

            break;
        }
    }
}

// 0x800E1DE8
sb32 ftMainCheckAddGroundHazard(GObj *gobj, sb32(*proc_update)(GObj*, GObj*, grHitbox**, s32*))
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sFTMainGroundHazards); i++)
    {
        if (sFTMainGroundHazards[i].gobj == NULL)
        {
            sFTMainGroundHazards[i].gobj = gobj;
            sFTMainGroundHazards[i].proc_update = proc_update;

            sFTMainGroundHazardsNum++;

            return TRUE;
        }
    }
    return FALSE;
}

// 0x800E1E3C - Remove map environment object by GObj pointer match
void ftMainClearHazard(GObj *gobj)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sFTMainGroundHazards); i++)
    {
        if (sFTMainGroundHazards[i].gobj == gobj)
        {
            sFTMainGroundHazards[i].gobj = NULL;
            sFTMainGroundHazardsNum--;

            break;
        }
    }
}

// 0x800E1E88
void ftMainSetHitHazard(GObj *gobj, GObj *fighter_gobj, ftStruct *fp, s32 kind)
{
    switch (kind)
    {
    case nGMHitEnvironmentTwister:
        ftCommonTwisterSetStatus(fighter_gobj, gobj);
        break;

    case nGMHitEnvironmentTaruCann:
        ftCommonTaruCannSetStatus(fighter_gobj, gobj);
        break;
    }
}

// 0x800E1EE8
void ftMainSearchHitHazard(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    grObstacle *gh = &sFTMainGroundObstacles[0];

    if (!fp->is_nullstatus)
    {
        s32 i;

        if (!fp->hitlag_timer)
        {
            if (fp->twister_wait)
            {
                fp->twister_wait--;
            }
            if (fp->tarucann_wait)
            {
                fp->tarucann_wait--;
            }
        }
        for (i = 0; i < sFTMainGroundObstaclesNum; i++, gh++)
        {
            if (gh->gobj != NULL)
            {
                s32 kind;

                if (gh->proc_update(gh->gobj, fighter_gobj, &kind) != FALSE)
                {
                    ftMainSetHitHazard(gh->gobj, fighter_gobj, fp, kind);
                }
            }
        }
    }
}

// 0x800E1FE0
void ftMainUpdateVelDamageGround(ftStruct *fp, f32 move)
{
    if (fp->phys_info.vel_damage_ground < 0.0F)
    {
        fp->phys_info.vel_damage_ground += move;

        if (fp->phys_info.vel_damage_ground > 0.0F)
        {
            fp->phys_info.vel_damage_ground = 0.0F;
        }
    }
    else
    {
        fp->phys_info.vel_damage_ground -= move;

        if (fp->phys_info.vel_damage_ground < 0.0F)
        {
            fp->phys_info.vel_damage_ground = 0.0F;
        }
    }
}

// 0x800E2048
void ftMainProcPhysicsMap(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    Vec3f *topn_translate = &fp->joint[nFTPartsJointTopN]->translate.vec.f;
    Vec3f *coll_translate = &fp->coll_data.pos_curr;
    Vec3f *ground_angle = &fp->coll_data.ground_angle;
    Vec3f *vel_damage_air;
    s32 unused[2];
    f32 size_mul;
    f32 tan;
    f32 damage_angle;
    Vec2f vel_damage_new;
    s32 i;

    *coll_translate = *topn_translate;

    if (fp->hitlag_timer == 0)
    {
        if (fp->cliffcatch_wait != 0)
        {
            fp->cliffcatch_wait--;
        }
        if (fp->proc_physics != NULL)
        {
            fp->proc_physics(fighter_gobj);
        }
        vel_damage_air = &fp->phys_info.vel_damage_air;

        if ((fp->phys_info.vel_damage_air.x != 0.0F) || (vel_damage_air->y != 0.0F))
        {
            if (fp->ga == nMPKineticsAir)
            {
                damage_angle = atan2f(vel_damage_air->y, vel_damage_air->x);
                vel_damage_new.y = vel_damage_air->x;
                vel_damage_new.x = vel_damage_air->y;

                vel_damage_air->x -= (1.7F * __cosf(damage_angle));
                vel_damage_air->y -= (1.7F * __sinf(damage_angle));

                if (((vel_damage_air->x * vel_damage_new.y) < 0.0F) || ((vel_damage_air->y * vel_damage_new.x) < 0.0F))
                {
                    vel_damage_air->x = vel_damage_air->y = 0.0F;
                }
                fp->phys_info.vel_damage_ground = 0.0F;
            }
            else
            {
                if (fp->phys_info.vel_damage_ground == 0.0F)
                {
                    fp->phys_info.vel_damage_ground = fp->phys_info.vel_damage_air.x;
                }
                ftMainUpdateVelDamageGround(fp, dMPCollisionMaterialFrictions[fp->coll_data.ground_flags & MPCOLL_VERTEX_MAT_MASK] * fp->attributes->traction * 0.25F);

                vel_damage_air->x = (ground_angle->y * fp->phys_info.vel_damage_ground);
                vel_damage_air->y = (-ground_angle->x * fp->phys_info.vel_damage_ground);
            }
        }
        lbVector_Vec3fAddTo(topn_translate, &fp->phys_info.vel_air);

        topn_translate->x += vel_damage_air->x;
        topn_translate->y += vel_damage_air->y;
    }
    if (fp->proc_lagupdate != NULL)
    {
        fp->proc_lagupdate(fighter_gobj);
    }
    lbVector_Vec3fSubtract(&fp->coll_data.pos_correct, topn_translate, coll_translate);

    if ((fp->ga == nMPKineticsGround) && (fp->coll_data.ground_line_id != -1) && (fp->coll_data.ground_line_id != -2) && (mpCollisionCheckExistLineID(fp->coll_data.ground_line_id) != FALSE))
    {
        mpCollisionGetSpeedLineID(fp->coll_data.ground_line_id, &fp->coll_data.pos_speed);
        lbVector_Vec3fAddTo(topn_translate, &fp->coll_data.pos_speed);
    }
    else fp->coll_data.pos_speed.x = fp->coll_data.pos_speed.y = fp->coll_data.pos_speed.z = 0.0F;

    ftCommonDeadCheckInterruptCommon(fighter_gobj);

    if ((fp->coll_data.pos_curr.y >= gMPCollisionGroundData->altitude_warning) && (topn_translate->y < gMPCollisionGroundData->altitude_warning) && (fp->ft_kind != nFTKindBoss))
    {
        func_800269C0_275C0(nGMSoundFGMDeadPortalLw);
    }
    if (fp->publicity_knockback != 0)
    {
        if ((fp->joint[nFTPartsJointTopN]->translate.vec.f.x > (gMPCollisionEdgeBounds.d2.left + 450.0F)) && (fp->joint[nFTPartsJointTopN]->translate.vec.f.x < (gMPCollisionEdgeBounds.d2.right - 450.0F)))
        {
            fp->publicity_knockback = 0.0F;
        }
    }
    if (fp->proc_map != NULL)
    {
        fp->coll_data.coll_mask_prev = fp->coll_data.coll_mask_curr;
        fp->coll_data.coll_mask_curr = 0;
        fp->coll_data.is_coll_end = FALSE;
        fp->coll_data.coll_mask_stat = 0;
        fp->coll_data.coll_mask_unk = 0;

        fp->proc_map(fighter_gobj);

        if (fp->ft_kind == nFTKindKirby)
        {
            ftParamKirbyTryMakeMapStarEffect(fighter_gobj);
        }
    }
    if (fp->proc_slope != NULL)
    {
        fp->proc_slope(fighter_gobj);
    }
    func_ovl2_800EB528(fp->joint[nFTPartsJointTopN]);

    if (fp->hitlag_timer == 0)
    {
        ftMainUpdateMotionEventsDefaultEffect(fighter_gobj);
    }
    if (fp->hitlag_timer == 0)
    {
        if (fp->proc_accessory != NULL)
        {
            fp->proc_accessory(fighter_gobj);
        }
    }
    fp->is_effect_interrupt = FALSE;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
    {
        ftHitbox *ft_hit = &fp->fighter_hit[i];

        switch (ft_hit->update_state)
        {
        case nGMHitUpdateDisable:
            break;

        case nGMHitUpdateNew:
            ft_hit->pos = ft_hit->offset;

            if (ft_hit->is_scale_pos)
            {
                size_mul = 1.0F / fp->attributes->size_mul;

                ft_hit->pos.x *= size_mul;
                ft_hit->pos.y *= size_mul;
                ft_hit->pos.z *= size_mul;
            }
            gmCollisionGetFighterPartsWorldPosition(ft_hit->joint, &ft_hit->pos);

            ft_hit->update_state = nGMHitUpdateTransfer;

            ft_hit->hit_matrix.unk_fthitmtx_0x0 = FALSE;
            ft_hit->hit_matrix.unk_fthitmtx_0x44 = 0.0F;
            break;

        case nGMHitUpdateTransfer:
            ft_hit->update_state = nGMHitUpdateInterpolate;

            /* fallthrough */

        case nGMHitUpdateInterpolate:
            ft_hit->pos_prev = ft_hit->pos;
            ft_hit->pos = ft_hit->offset;

            if (ft_hit->is_scale_pos)
            {
                size_mul = 1.0F / fp->attributes->size_mul;

                ft_hit->pos.x *= size_mul;
                ft_hit->pos.y *= size_mul;
                ft_hit->pos.z *= size_mul;
            }
            gmCollisionGetFighterPartsWorldPosition(ft_hit->joint, &ft_hit->pos);

            ft_hit->hit_matrix.unk_fthitmtx_0x0 = FALSE;
            ft_hit->hit_matrix.unk_fthitmtx_0x44 = 0.0F;

            break;
        }
    }
}

// 0x800E2604
void ftMainProcPhysicsMapDefault(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (((fp->capture_gobj == NULL) || (fp->x192_flag_b3)) && ((fp->catch_gobj == NULL) || !(fp->x192_flag_b3)))
    {
        ftMainProcPhysicsMap(fighter_gobj);
    }
}

// 0x800E2660
void ftMainProcPhysicsMapCapture(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (((fp->capture_gobj != NULL) && !(fp->x192_flag_b3)) || ((fp->catch_gobj != NULL) && (fp->x192_flag_b3)))
    {
        ftMainProcPhysicsMap(fighter_gobj);
    }
}

// 0x800E26BC
void ftMainSetHitInteractStats(ftStruct *fp, u32 attack_group_id, GObj *victim_gobj, s32 hitbox_type, u32 victim_group_id, sb32 ignore_hurt_or_hit)
{
    s32 i, j;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
    {
        if (i == ARRAY_COUNT(fp->fighter_hit)); // WAT

        if ((fp->fighter_hit[i].update_state != nGMHitUpdateDisable) && (attack_group_id == fp->fighter_hit[i].group_id))
        {
            for (j = 0; j < ARRAY_COUNT(fp->fighter_hit[i].hit_targets); j++)
            {
                if (victim_gobj == fp->fighter_hit[i].hit_targets[j].victim_gobj)
                {
                    switch (hitbox_type)
                    {
                    case nGMHitTypeHurt:
                        fp->fighter_hit[i].hit_targets[j].victim_flags.is_interact_hurt = TRUE;
                        break;

                    case nGMHitTypeShield:
                        fp->fighter_hit[i].hit_targets[j].victim_flags.is_interact_shield = TRUE;
                        break;

                    case nGMHitTypeHit:
                        fp->fighter_hit[i].hit_targets[j].victim_flags.group_id = victim_group_id;
                        break;

                    default:
                        break;
                    }
                    break;
                }
            }
            if (j == ARRAY_COUNT(fp->fighter_hit[i].hit_targets))
            {
                for (j = 0; j < ARRAY_COUNT(fp->fighter_hit[i].hit_targets); j++)
                {
                    if (fp->fighter_hit[i].hit_targets[j].victim_gobj == NULL) break;
                }
                if (j == ARRAY_COUNT(fp->fighter_hit[i].hit_targets)) j = 0;

                fp->fighter_hit[i].hit_targets[j].victim_gobj = victim_gobj;

                switch (hitbox_type)
                {
                case nGMHitTypeHurt:
                    fp->fighter_hit[i].hit_targets[j].victim_flags.is_interact_hurt = TRUE;
                    break;

                case nGMHitTypeShield:
                    fp->fighter_hit[i].hit_targets[j].victim_flags.is_interact_shield = TRUE;
                    break;

                case nGMHitTypeHit:
                    fp->fighter_hit[i].hit_targets[j].victim_flags.group_id = victim_group_id;
                    break;

                default:
                    break;
                }
            }
            if (ignore_hurt_or_hit == 0)
            {
                gFTMainIsHurtDetect[i] = FALSE;
            }
            else gFTMainIsHitDetect[i] = FALSE;
        }
    }
}

// 0x800E287C
void ftMainSetHitRebound(GObj *attacker_gobj, ftStruct *fp, ftHitbox *ft_hit, GObj *victim_gobj)
{
    if (fp->attack_shield_push < ft_hit->damage)
    {
        fp->attack_shield_push = ft_hit->damage;

        if ((ft_hit->can_rebound) && (fp->ga == nMPKineticsGround))
        {
            fp->attack_rebound = (fp->attack_shield_push * 1.62F) + 4.0F;

            fp->lr_attack = (DObjGetStruct(attacker_gobj)->translate.vec.f.x < DObjGetStruct(victim_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;
        }
    }
}

// 0x800E2910
void ftMainUpdateAttackStatFighter(ftStruct *other_fp, ftHitbox *other_hit, ftStruct *this_fp, ftHitbox *this_hit, GObj *other_gobj, GObj *this_gobj)
{
    Vec3f impact_pos;

    gmCollisionGetFighterHitFighterHitPosition(&impact_pos, this_hit, other_hit);

    if ((this_hit->damage - 10) < other_hit->damage)
    {
        ftMainSetHitInteractStats(this_fp, this_hit->group_id, other_gobj, nGMHitTypeHit, other_hit->group_id, 1);
        ftMainSetHitRebound(this_gobj, this_fp, this_hit, other_gobj);
        efManagerSetOffMakeEffect(&impact_pos, this_hit->damage);

        if ((gBattleState->game_type == nGMBattleGameType1PGame) && (this_hit->damage >= 20) && (other_fp->player == gSceneData.spgame_player))
        {
            gGM1PGameBonusGiantImpact = TRUE;
        }
    }
    if ((other_hit->damage - 10) < this_hit->damage)
    {
        ftMainSetHitInteractStats(other_fp, other_hit->group_id, this_gobj, nGMHitTypeHit, this_hit->group_id, 0);
        ftMainSetHitRebound(other_gobj, other_fp, other_hit, this_gobj);
        efManagerSetOffMakeEffect(&impact_pos, other_hit->damage);

        if ((gBattleState->game_type == nGMBattleGameType1PGame) && (other_hit->damage >= 20) && (this_fp->player == gSceneData.spgame_player))
        {
            gGM1PGameBonusGiantImpact = TRUE;
        }
    }
}

// 0x800E2A90
void ftMainUpdateShieldStatFighter(ftStruct *attacker_fp, ftHitbox *attacker_hit, ftStruct *victim_fp, GObj *attacker_gobj, GObj *victim_gobj)
{
    Vec3f impact_pos;

    ftMainSetHitInteractStats(attacker_fp, attacker_hit->group_id, victim_gobj, nGMHitTypeShield, 0, 0);

    if (attacker_fp->attack_shield_push < attacker_hit->damage)
    {
        attacker_fp->attack_shield_push = attacker_hit->damage;
    }
    victim_fp->shield_damage_total += (attacker_hit->damage + attacker_hit->shield_damage);

    if (victim_fp->shield_damage < attacker_hit->damage)
    {
        victim_fp->shield_damage = attacker_hit->damage;

        victim_fp->lr_shield = (DObjGetStruct(victim_gobj)->translate.vec.f.x < DObjGetStruct(attacker_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;

        victim_fp->shield_player = attacker_fp->player;
    }
    gmCollisionGetFighterHitShieldPosition(&impact_pos, attacker_hit, victim_gobj, victim_fp->joint[nFTPartsJointYRotN]);
    efManagerSetOffMakeEffect(&impact_pos, attacker_hit->damage);
}

// 0x800E2B88
void ftMainUpdateCatchStatFighter(ftStruct *attacker_fp, ftHitbox *attacker_hit, ftStruct *victim_fp, GObj *attacker_gobj, GObj *victim_gobj)
{
    f32 dist;

    ftMainSetHitInteractStats(attacker_fp, attacker_hit->group_id, victim_gobj, nGMHitTypeHurt, 0, 1);

    if (DObjGetStruct(victim_gobj)->translate.vec.f.x < DObjGetStruct(attacker_gobj)->translate.vec.f.x)
    {
        dist = -(DObjGetStruct(victim_gobj)->translate.vec.f.x - DObjGetStruct(attacker_gobj)->translate.vec.f.x);
    }
    else dist = DObjGetStruct(victim_gobj)->translate.vec.f.x - DObjGetStruct(attacker_gobj)->translate.vec.f.x;

    if (dist < attacker_fp->search_gobj_dist)
    {
        attacker_fp->search_gobj_dist = dist;
        attacker_fp->search_gobj = victim_gobj;
    }
}

// 0x800E2C24
void ftMainPlayHitSFX(ftStruct *fp, ftHitbox *ft_hit)
{
    if ((fp->p_sfx != NULL) && (fp->p_sfx->sfx_id != 0) && (fp->p_sfx->sfx_id == fp->sfx_id))
    {
        func_80026738_27338(fp->p_sfx);
    }
    fp->p_sfx = NULL, fp->sfx_id = 0;

    func_ovl0_800C8654(dFTMainHitCollisionFGMs[ft_hit->sfx_kind][ft_hit->sfx_level], fp->joint[nFTPartsJointTopN]->translate.vec.f.x);
}

// 0x800E2CC0
sb32 ftMainCheckGetUpdateDamage(ftStruct *fp, s32 *damage)
{
    if (fp->is_damage_resist)
    {
        fp->damage_resist -= *damage;

        if (fp->damage_resist <= 0)
        {
            fp->is_damage_resist = FALSE;

            *damage = -fp->damage_resist;
        }
    }
    if (!(fp->is_damage_resist))
    {
        fp->damage_queue += *damage;

        if (fp->damage_lag < *damage)
        {
            fp->damage_lag = *damage;
        }
        return TRUE;
    }
    else return FALSE;
}

// 0x800E2D44
void ftMainUpdateDamageStatFighter(ftStruct *attacker_fp, ftHitbox *attacker_hit, ftStruct *victim_fp, ftHurtbox *victim_hurt, GObj *attacker_gobj, GObj *victim_gobj)
{
    s32 damage;
    s32 attacker_player;
    s32 attacker_player_number;
    s32 unused;
    Vec3f impact_pos;

    ftMainSetHitInteractStats(attacker_fp, attacker_hit->group_id, victim_gobj, nGMHitTypeHurt, 0, FALSE);

    damage = ftParamGetCapturedDamage(victim_fp, attacker_hit->damage);

    if (attacker_fp->attack_damage < damage)
    {
        attacker_fp->attack_damage = damage;
    }
    if
    (
        (victim_fp->special_hitstatus == nGMHitStatusNormal) &&
        (victim_fp->star_hitstatus == nGMHitStatusNormal)    &&
        (victim_fp->hitstatus == nGMHitStatusNormal)         &&
        (victim_hurt->hitstatus == nGMHitStatusNormal)
    )
    {
        if (ftMainCheckGetUpdateDamage(victim_fp, &damage) != FALSE)
        {
            if (attacker_fp->throw_gobj != NULL)
            {
                attacker_player = attacker_fp->throw_player;
                attacker_player_number = attacker_fp->throw_player_number;
            }
            else
            {
                attacker_player = attacker_fp->player;
                attacker_player_number = attacker_fp->player_number;
            }
            if (sFTMainHitlogID < ARRAY_COUNT(sFTMainHitlogs))
            {
                ftHitlog *hitlog = &sFTMainHitlogs[sFTMainHitlogID];

                hitlog->attacker_object_class = nFTHitlogObjectFighter;
                hitlog->attacker_hit = attacker_hit;
                hitlog->attacker_gobj = attacker_gobj;
                hitlog->victim_hurt = victim_hurt;
                hitlog->attacker_player = attacker_player;
                hitlog->attacker_player_number = attacker_player_number;

                sFTMainHitlogID++;
            }
            ftParamUpdateBattleStats(attacker_player, victim_fp->player, damage);
            ftParamUpdateStaleQueue(attacker_player, victim_fp->player, attacker_hit->attack_id, attacker_hit->motion_count);
        }
        else
        {
            gmCollisionGetFighterHitFighterHurtPosition(&impact_pos, attacker_hit, victim_hurt);
            efManagerSetOffMakeEffect(&impact_pos, damage);
        }
    }
    else
    {
        gmCollisionGetFighterHitFighterHurtPosition(&impact_pos, attacker_hit, victim_hurt);
        efManagerSetOffMakeEffect(&impact_pos, damage);
    }
    ftMainPlayHitSFX(attacker_fp, attacker_hit);
}

// 0x800E2F04
void ftMainUpdateAttackStatWeapon(wpStruct *ip, wpHitbox *wp_hit, s32 index, ftStruct *fp, ftHitbox *ft_hit, GObj *weapon_gobj, GObj *fighter_gobj)
{
    s32 damage = wpMainGetStaledDamage(ip);
    Vec3f impact_pos;

    gmCollisionGetWeaponHitFighterHitPosition(&impact_pos, wp_hit, index, ft_hit);

    if ((ft_hit->damage - 10) < damage)
    {
        ftMainSetHitInteractStats(fp, ft_hit->group_id, weapon_gobj, nGMHitTypeHit, 0, TRUE);
        ftMainSetHitRebound(fighter_gobj, fp, ft_hit, weapon_gobj);
        efManagerSetOffMakeEffect(&impact_pos, ft_hit->damage);
    }

    if ((damage - 10) < ft_hit->damage)
    {
        wpProcessUpdateHitInteractStatsGroupID(ip, wp_hit, fighter_gobj, nGMHitTypeHit, ft_hit->group_id);

        if (ip->hit_attack_damage < damage)
        {
            ip->hit_attack_damage = damage;
        }
        efManagerSetOffMakeEffect(&impact_pos, damage);

        if ((gBattleState->game_type == nGMBattleGameType1PGame) && ((damage - 10) >= 10) && (fp->player == gSceneData.spgame_player))
        {
            gGM1PGameBonusGiantImpact = TRUE;
        }
    }
}

// 0x800E3048
void ftMainUpdateShieldStatWeapon(wpStruct *wp, wpHitbox *wp_hit, s32 hitbox_id, ftStruct *fp, GObj *weapon_gobj, GObj *fighter_gobj, f32 angle, Vec3f *vec)
{
    s32 damage = wpMainGetStaledDamage(wp);
    Vec3f impact_pos;

    wpProcessUpdateHitInteractStatsGroupID(wp, wp_hit, fighter_gobj, (wp_hit->can_rehit_shield) ? nGMHitTypeShieldRehit : nGMHitTypeShield, 0);

    if (wp->hit_shield_damage < damage)
    {
        wp->hit_shield_damage = damage;

        wp->shield_collide_angle = angle;

        wp->shield_collide_vec.x = 0.0F;
        wp->shield_collide_vec.y = 0.0F;

        wp->shield_collide_vec.z = (fp->lr == nGMDirectionR) ? -vec->x : vec->x;

        lbVector_Vec3fNormalize(&wp->shield_collide_vec);
    }
    fp->shield_damage_total += damage + wp_hit->shield_damage;

    if (fp->shield_damage < damage)
    {
        fp->shield_damage = damage;

        fp->lr_shield = (wp->phys_info.vel_air.x < 0.0F) ? nGMDirectionR : nGMDirectionL;

        fp->shield_player = wp->player;
    }
    gmCollisionGetWeaponHitShieldPosition(&impact_pos, wp_hit, hitbox_id, fighter_gobj, fp->joint[nFTPartsJointYRotN]);
    efManagerSetOffMakeEffect(&impact_pos, wp_hit->shield_damage + damage);
}

// 0x800E31B4
void ftMainUpdateReflectorStatWeapon(wpStruct *wp, wpHitbox *wp_hit, ftStruct *fp, GObj *fighter_gobj)
{
    s32 damage = wpMainGetStaledDamage(wp);

    wpProcessUpdateHitInteractStatsGroupID(wp, wp_hit, fighter_gobj, nGMHitTypeReflect, 0);

    if (fp->special_hit->damage_resist < damage)
    {
        if (wp_hit->can_rehit_fighter)
        {
            if (wp->hit_refresh_damage < damage)
            {
                wp->hit_refresh_damage = damage;
            }
        }
        else if (wp->hit_normal_damage < damage)
        {
            wp->hit_normal_damage = damage;
        }
        fp->reflect_damage = damage;

        fp->lr_reflect = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(wp->weapon_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;
    }
    else
    {
        wp->reflect_gobj = fighter_gobj;

        wp->reflect_stat_flags = fp->stat_flags;
        wp->reflect_stat_count = fp->stat_count;

        fp->lr_reflect = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(wp->weapon_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;
    }
}

// 0x800E3308
void ftMainUpdateAbsorbStatWeapon(wpStruct *ip, wpHitbox *wp_hit, ftStruct *fp, GObj *fighter_gobj)
{
    s32 damage = wpMainGetStaledDamage(ip);

    wpProcessUpdateHitInteractStatsGroupID(ip, wp_hit, fighter_gobj, nGMHitTypeAbsorb, 0);

    ip->absorb_gobj = fighter_gobj;

    fp->lr_absorb = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(ip->weapon_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;

    if (!(wp_hit->can_not_heal))
    {
        fp->percent_damage -= (s32)(damage * 2.0F);

        if (fp->percent_damage < 0)
        {
            fp->percent_damage = 0;
        }
        gBattleState->players[fp->player].stock_damage_all = fp->percent_damage;
    }
}

// 0x800E3418
void ftMainUpdateDamageStatWeapon(wpStruct *wp, wpHitbox *wp_hit, s32 hitbox_id, ftStruct *fp, ftHurtbox *ft_hurt, GObj *weapon_gobj, GObj *fighter_gobj)
{
    s32 temp_damage = wpMainGetStaledDamage(wp);
    s32 damage;

    wpProcessUpdateHitInteractStatsGroupID(wp, wp_hit, fighter_gobj, (wp_hit->can_rehit_fighter) ? nGMHitTypeHurtRehit : nGMHitTypeHurt, 0);

    damage = ftParamGetCapturedDamage(fp, temp_damage);

    if (wp_hit->can_rehit_fighter)
    {
        if (wp->hit_refresh_damage < damage)
        {
            wp->hit_refresh_damage = damage;
        }
    }
    else if (wp->hit_normal_damage < damage)
    {
        wp->hit_normal_damage = damage;
    }
    if
    (
        (fp->special_hitstatus == nGMHitStatusNormal) &&
        (fp->star_hitstatus == nGMHitStatusNormal)    &&
        (fp->hitstatus == nGMHitStatusNormal)         &&
        (ft_hurt->hitstatus == nGMHitStatusNormal)    &&
        (ftMainCheckGetUpdateDamage(fp, &damage) != FALSE)
    )
    {
        if (sFTMainHitlogID < ARRAY_COUNT(sFTMainHitlogs))
        {
            ftHitlog *hitlog = &sFTMainHitlogs[sFTMainHitlogID];

            hitlog->attacker_object_class = nFTHitlogObjectWeapon;
            hitlog->attacker_hit = wp_hit;
            hitlog->hitbox_id = hitbox_id;
            hitlog->attacker_gobj = weapon_gobj;
            hitlog->victim_hurt = ft_hurt;
            hitlog->attacker_player = wp->player;
            hitlog->attacker_player_number = wp->player_number;

            sFTMainHitlogID++;
        }
        ftParamUpdateBattleStats(wp->player, fp->player, damage);
        ftParamUpdateStaleQueue(wp->player, fp->player, wp_hit->attack_id, wp_hit->motion_count);
    }
    func_800269C0_275C0(wp_hit->hit_sfx);
}

// 0x800E35BC
void ftMainUpdateAttackStatItem(itStruct *ip, itHitbox *it_hit, s32 hitbox_id, ftStruct *fp, ftHitbox *ft_hit, GObj *item_gobj, GObj *fighter_gobj)
{
    s32 damage = itMainGetDamageOutput(ip);
    Vec3f impact_pos;

    gmCollisionGetItemHitFighterHitPosition(&impact_pos, it_hit, hitbox_id, ft_hit);

    if ((ft_hit->damage - 10) < damage)
    {
        ftMainSetHitInteractStats(fp, ft_hit->group_id, item_gobj, nGMHitTypeHit, 0, 1);
        ftMainSetHitRebound(fighter_gobj, fp, ft_hit, item_gobj);
        efManagerSetOffMakeEffect(&impact_pos, ft_hit->damage);
    }
    if ((damage - 10) < ft_hit->damage)
    {
        itProcessSetHitInteractStats(it_hit, fighter_gobj, nGMHitTypeHit, ft_hit->group_id);

        if (ip->hit_attack_damage < damage)
        {
            ip->hit_attack_damage = damage;
        }
        efManagerSetOffMakeEffect(&impact_pos, damage);

        if ((gBattleState->game_type == nGMBattleGameType1PGame) && ((damage - 10) >= 10) && (fp->player == gSceneData.spgame_player))
        {
            gGM1PGameBonusGiantImpact = TRUE;
        }
    }
}

// 0x800E36F8
void ftMainUpdateShieldStatItem(itStruct *ip, itHitbox *it_hit, s32 hitbox_id, ftStruct *fp, GObj *item_gobj, GObj *fighter_gobj, f32 angle, Vec3f *vec)
{
    s32 damage = itMainGetDamageOutput(ip);
    Vec3f impact_pos;

    itProcessSetHitInteractStats(it_hit, fighter_gobj, (it_hit->can_rehit_shield) ? nGMHitTypeShieldRehit : nGMHitTypeShield, 0);

    if (ip->hit_shield_damage < damage)
    {
        ip->hit_shield_damage = damage;

        ip->shield_collide_angle = angle;

        ip->shield_collide_vec.x = 0.0F;
        ip->shield_collide_vec.y = 0.0F;

        ip->shield_collide_vec.z = (fp->lr == nGMDirectionR) ? -vec->x : vec->x;

        lbVector_Vec3fNormalize(&ip->shield_collide_vec);
    }
    fp->shield_damage_total += damage + it_hit->shield_damage;

    if (fp->shield_damage < damage)
    {
        fp->shield_damage = damage;

        fp->lr_shield = (ip->phys_info.vel_air.x < 0.0F) ? nGMDirectionR : nGMDirectionL;

        fp->shield_player = ip->player;
    }
    gmCollisionGetItemHitShieldPosition(&impact_pos, it_hit, hitbox_id, fighter_gobj, fp->joint[nFTPartsJointYRotN]);
    efManagerSetOffMakeEffect(&impact_pos, it_hit->shield_damage + damage);
}

// 0x800E3860
void ftMainUpdateReflectorStatItem(itStruct *ip, itHitbox *it_hit, ftStruct *fp, GObj *fighter_gobj)
{
    s32 damage = itMainGetDamageOutput(ip);

    itProcessSetHitInteractStats(it_hit, fighter_gobj, nGMHitTypeReflect, 0);

    if (fp->special_hit->damage_resist < damage)
    {
        if (it_hit->can_rehit_fighter)
        {
            if (ip->hit_refresh_damage < damage)
            {
                ip->hit_refresh_damage = damage;
            }
        }
        else if (ip->hit_normal_damage < damage)
        {
            ip->hit_normal_damage = damage;
        }
        fp->reflect_damage = damage;

        fp->lr_reflect = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(ip->item_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;
    }
    else
    {
        ip->reflect_gobj = fighter_gobj;

        ip->reflect_stat_flags = fp->stat_flags;
        ip->reflect_stat_count = fp->stat_count;

        fp->lr_reflect = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(ip->item_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;
    }
}

// 0x800E39B0
void ftMainUpdateDamageStatItem(itStruct *ip, itHitbox *it_hit, s32 hitbox_id, ftStruct *fp, ftHurtbox *ft_hurt, GObj *item_gobj, GObj *fighter_gobj)
{
    s32 damage_temp = itMainGetDamageOutput(ip);
    s32 damage;
    s32 lr_attack;

    itProcessSetHitInteractStats(it_hit, fighter_gobj, (it_hit->can_rehit_fighter) ? nGMHitTypeHurtRehit : nGMHitTypeHurt, 0);

    if (ip->type == nITTypeTouch)
    {
        switch (ip->it_kind)
        {
        case nITKindStar:
            it_hit->update_state = nGMHitUpdateDisable;
            ip->hit_normal_damage = 1;

            ftParamSetStarHitStatusInvincible(fp, ITSTAR_INVINCIBLE_TIME);
            ftParamTryPlayItemMusic(nGMSoundBGMStarman);
            func_800269C0_275C0(nGMSoundFGMStarCollect);

            if ((gBattleState->game_type == nGMBattleGameType1PGame) && (fp->player == gSceneData.spgame_player) && (gGM1PGameBonusStarCount < U8_MAX))
            {
                gGM1PGameBonusStarCount++;
            }
            break;

        case nITKindGLucky:
            ftParamHealDamage(fp, it_hit->damage);
            break;
        }
    }
    else
    {
        damage = ftParamGetCapturedDamage(fp, damage_temp);

        if (it_hit->can_rehit_fighter)
        {
            if (ip->hit_refresh_damage < damage)
            {
                ip->hit_refresh_damage = damage;
            }
        }
        else if (ip->hit_normal_damage < damage)
        {
            ip->hit_normal_damage = damage;
        }
        if (ABSF(ip->phys_info.vel_air.x) < 5.0F)
        {
            ip->lr_attack = lr_attack = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(item_gobj)->translate.vec.f.x) ? nGMDirectionL : nGMDirectionR;
        }
        else
        {
            lr_attack = (ip->phys_info.vel_air.x < 0) ? nGMDirectionL : nGMDirectionR;

            ip->lr_attack = lr_attack;
        }
        if 
        (
            (fp->special_hitstatus == nGMHitStatusNormal) &&
            (fp->star_hitstatus == nGMHitStatusNormal)    &&
            (fp->hitstatus == nGMHitStatusNormal)         &&
            (ft_hurt->hitstatus == nGMHitStatusNormal)    &&
            (ftMainCheckGetUpdateDamage(fp, &damage) != FALSE)
        )
        {
            if (sFTMainHitlogID < ARRAY_COUNT(sFTMainHitlogs))
            {
                ftHitlog *hitlog = &sFTMainHitlogs[sFTMainHitlogID];

                hitlog->attacker_object_class = nFTHitlogObjectItem;
                hitlog->attacker_hit = it_hit;
                hitlog->hitbox_id = hitbox_id;
                hitlog->attacker_gobj = item_gobj;
                hitlog->victim_hurt = ft_hurt;
                hitlog->attacker_player = ip->player;
                hitlog->attacker_player_number = ip->player_number;

                sFTMainHitlogID++;
            }
            ftParamUpdateBattleStats(ip->player, fp->player, damage);
            ftParamUpdateStaleQueue(ip->player, fp->player, it_hit->attack_id, it_hit->motion_count);
        }
        func_800269C0_275C0(it_hit->hit_sfx);
    }
}

// 0x800E3CAC
void ftMainUpdateDamageStatGround(GObj *special_gobj, GObj *fighter_gobj, ftStruct *fp, grHitbox *gr_hit, s32 target_kind)
{
    s32 damage = ftParamGetCapturedDamage(fp, gr_hit->damage);
    sb32 is_take_damage = ftMainCheckGetUpdateDamage(fp, &damage);

    if ((is_take_damage != FALSE) && (sFTMainHitlogID < ARRAY_COUNT(sFTMainHitlogs)))
    {
        ftHitlog *hitlog = &sFTMainHitlogs[sFTMainHitlogID];

        hitlog->attacker_object_class = nFTHitlogObjectGround;
        hitlog->attacker_hit = gr_hit;
        hitlog->attacker_gobj = special_gobj;

        sFTMainHitlogID++;
    }
    switch (target_kind)
    {
    case nGMHitEnvironmentAcid:
        fp->acid_wait = 30;

        func_800269C0_275C0(nGMSoundFGMFloorDamageBurn);
        break;

    case nGMHitEnvironmentPowerBlock:
        if (is_take_damage != FALSE)
        {
            ftParamUpdateBattleStats(itGetStruct(special_gobj)->damage_port, fp->player, damage);
        }
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        fp->damagefloor_wait = 16;

        if (target_kind == 7)
        {
            func_800269C0_275C0(nGMSoundFGMShockML);
        }
        else func_800269C0_275C0(nGMSoundFGMFloorDamageBurn);
        break;

    default:
        break;
    }
}

// 0x800E3DD0
void ftMainGetBumperDamageAngle(GObj *fighter_gobj, GObj *attacker_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (fp->damage_angle == 362)
    {
        f32 dist_x = DObjGetStruct(fighter_gobj)->translate.vec.f.x - DObjGetStruct(attacker_gobj)->translate.vec.f.x;
        f32 dist_y;

        fp->lr_damage = (dist_x < 0) ? nGMDirectionR : nGMDirectionL;

        if (dist_x < 0.0F)
        {
            dist_x = -dist_x;
        }
        dist_y = (DObjGetStruct(fighter_gobj)->translate.vec.f.y + fp->coll_data.object_coll.center) - DObjGetStruct(attacker_gobj)->translate.vec.f.y;

        fp->damage_angle = (dist_x == 0) ? 0 : F_CLC_RTOD32(atanf(dist_y / dist_x));
    }
}

// 0x800E3EBC
void ftMainProcessHitCollisionStatsMain(GObj *fighter_gobj)
{
    ftStruct *this_fp = ftGetStruct(fighter_gobj);
    ftStruct *attacker_fp;
    wpStruct *wp;
    itStruct *ip;
    ftAttributes *attributes = this_fp->attributes;
    ftHitlog *hitlog;
    s32 i, j;
    f32 knockback_temp;
    f32 knockback;
    ftHitbox *ft_hit;
    wpHitbox *wp_hit;
    itHitbox *it_hit;
    grHitbox *gr_hit;
    Vec3f pos;
    s32 damage;
    u8 gr_handicap;
    GObj *attacker_gobj;
    s32 lr_damage;

    knockback = -1.0F;

    for (i = 0; i < sFTMainHitlogID; i++)
    {
        hitlog = &sFTMainHitlogs[i];

        switch (hitlog->attacker_object_class)
        {
        case nFTHitlogObjectFighter:
            ft_hit = hitlog->attacker_hit;
            attacker_fp = ftGetStruct(hitlog->attacker_gobj);

            knockback_temp = ftParamGetCommonKnockback
            (
                this_fp->percent_damage, 
                this_fp->damage_queue, ft_hit->damage, 
                ft_hit->knockback_weight, 
                ft_hit->knockback_scale, 
                ft_hit->knockback_base, 
                attributes->weight, 
                attacker_fp->handicap, 
                this_fp->handicap
            );

            gmCollisionGetFighterHitFighterHurtPosition(&pos, ft_hit, hitlog->victim_hurt);

            switch (ft_hit->element)
            {
            case nGMHitElementFire:
                efManagerDamageFireMakeEffect(&pos, ft_hit->damage);
                break;

            case nGMHitElementElectric:
                efManagerDamageElectricMakeEffect(&pos, ft_hit->damage);
                break;

            case nGMHitElementCoin:
                efManagerDamageCoinMakeEffect(&pos);
                break;

            case nGMHitElementSlash:
                efManagerDamageSlashMakeEffect(&pos, ft_hit->damage, gmCollisionGetDamageSlashRotation(attacker_fp, ft_hit));
                break;

            default:
                if (knockback_temp < 180.0F)
                {
                    efManagerDamageNormalLightMakeEffect(&pos, hitlog->attacker_player, ft_hit->damage, 0);
                }
                else efManagerDamageNormalHeavyMakeEffect(&pos, hitlog->attacker_player, ft_hit->damage);

                if (ft_hit->sfx_level > 0) // Changed this to > 0 for now, makes a bit more sense to me since it only does this on moves with hit SFX levels greater than weak (0)
                {
                    efManagerDamageSpawnOrbsRandomMakeEffect(&pos);

                    switch (this_fp->attributes->is_metallic)
                    {
                    case FALSE:
                        efManagerDamageSpawnSparksRandomMakeEffect(&pos, this_fp->lr);
                        break;

                    case TRUE:
                        efManagerDamageSpawnMDustRandomMakeEffect(&pos, this_fp->lr);
                        break;

                    /* default: break; // This might not be necessary */
                    }
                }
                break;
            }
            break;

        case nFTHitlogObjectWeapon:
            wp_hit = hitlog->attacker_hit;
            wp = wpGetStruct(hitlog->attacker_gobj);
            damage = wpMainGetStaledDamage(wp);

            knockback_temp = ftParamGetCommonKnockback(this_fp->percent_damage, this_fp->damage_queue, damage, wp_hit->knockback_weight, wp_hit->knockback_scale, wp_hit->knockback_base, attributes->weight, wp->handicap, this_fp->handicap);

            if (wp->is_hitlag_victim)
            {
                gmCollisionGetWeaponHitFighterHurtPosition(&pos, wp_hit, hitlog->hitbox_id, hitlog->victim_hurt);

                switch (wp_hit->element)
                {
                case nGMHitElementFire:
                    efManagerDamageFireMakeEffect(&pos, damage);
                    break;

                case nGMHitElementElectric:
                    efManagerDamageElectricMakeEffect(&pos, damage);
                    break;

                case nGMHitElementCoin:
                    efManagerDamageCoinMakeEffect(&pos);
                    break;

                default:
                    if (knockback_temp < 180.0F)
                    {
                        efManagerDamageNormalLightMakeEffect(&pos, hitlog->attacker_player, damage, NULL);
                    }
                    else efManagerDamageNormalHeavyMakeEffect(&pos, hitlog->attacker_player, damage);
                    break;
                }
            }
            break;

        case nFTHitlogObjectItem:
            it_hit = hitlog->attacker_hit;
            ip = itGetStruct(hitlog->attacker_gobj);

            damage = itMainGetDamageOutput(ip);

            knockback_temp = ftParamGetCommonKnockback(this_fp->percent_damage, this_fp->damage_queue, damage, it_hit->knockback_weight, it_hit->knockback_scale, it_hit->knockback_base, attributes->weight, ip->handicap, this_fp->handicap);

            if (ip->is_hitlag_victim)
            {
                gmCollisionGetItemHitFighterHurtPosition(&pos, it_hit, hitlog->hitbox_id, hitlog->victim_hurt);

                switch (it_hit->element)
                {
                case nGMHitElementFire:
                    efManagerDamageFireMakeEffect(&pos, damage);
                    break;

                case nGMHitElementElectric:
                    efManagerDamageElectricMakeEffect(&pos, damage);
                    break;

                case nGMHitElementCoin:
                    efManagerDamageCoinMakeEffect(&pos);
                    break;

                default:
                    if (knockback_temp < 180.0F)
                    {
                        efManagerDamageNormalLightMakeEffect(&pos, hitlog->attacker_player, damage, NULL);
                    }
                    else efManagerDamageNormalHeavyMakeEffect(&pos, hitlog->attacker_player, damage);
                    break;
                }
            }
            break;

        case nFTHitlogObjectGround:
            gr_hit = hitlog->attacker_hit;

            if (gr_hit->kind == nGMHitEnvironmentPowerBlock) // POW Block?
            {
                gr_handicap = itGetStruct(hitlog->attacker_gobj)->damage_handicap;
            }
            else gr_handicap = 9;

            knockback_temp = ftParamGetCommonKnockback(this_fp->percent_damage, this_fp->damage_queue, gr_hit->damage, gr_hit->knockback_weight, gr_hit->knockback_scale, gr_hit->knockback_base, attributes->weight, gr_handicap, this_fp->handicap);
            break;

        default:
            break;
        }
        if (knockback < knockback_temp)
        {
            knockback = knockback_temp;

            j = i;
        }
    }
    hitlog = &sFTMainHitlogs[j];
    attacker_gobj = hitlog->attacker_gobj;

    switch (hitlog->attacker_object_class)
    {
    case nFTHitlogObjectFighter:
        ft_hit = hitlog->attacker_hit;
        attacker_fp = ftGetStruct(attacker_gobj);
        this_fp->damage_angle = ft_hit->angle;
        this_fp->damage_element = ft_hit->element;

        this_fp->lr_damage = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(attacker_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;

        this_fp->damage_player_number = hitlog->attacker_player_number;

        ftParamUpdate1PGameDamageStats(this_fp, hitlog->attacker_player, hitlog->attacker_object_class, attacker_fp->ft_kind, attacker_fp->stat_flags.halfword & ~0x400, attacker_fp->stat_count);

        this_fp->damage_joint_id = hitlog->victim_hurt->joint_id;
        this_fp->damage_index = hitlog->victim_hurt->placement;

        if (this_fp->damage_element == nGMHitElementElectric)
        {
            attacker_fp->hitlag_mul = 1.5F;
        }
        break;

    case nFTHitlogObjectWeapon:
        wp_hit = hitlog->attacker_hit;
        wp = wpGetStruct(attacker_gobj);
        this_fp->damage_angle = wp_hit->angle;
        this_fp->damage_element = wp_hit->element;

        if (ABSF(wp->phys_info.vel_air.x) < 5.0F)
        {
            this_fp->lr_damage = lr_damage = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(attacker_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;
        }
        else
        {
            lr_damage = (wp->phys_info.vel_air.x < 0) ? nGMDirectionR : nGMDirectionL;

            this_fp->lr_damage = lr_damage;
        }
        if (this_fp->player == hitlog->attacker_player)
        {
            this_fp->damage_player_number = 0;

            ftParamUpdate1PGameDamageStats(this_fp, GMBATTLE_PLAYERS_MAX, hitlog->attacker_object_class, wp->wp_kind, 0, 0);
        }
        else
        {
            this_fp->damage_player_number = hitlog->attacker_player_number;

            ftParamUpdate1PGameDamageStats(this_fp, hitlog->attacker_player, hitlog->attacker_object_class, wp->wp_kind, wp_hit->stat_flags.halfword, wp_hit->stat_count);
        }
        this_fp->damage_joint_id = hitlog->victim_hurt->joint_id;
        this_fp->damage_index = hitlog->victim_hurt->placement;

        ftMainGetBumperDamageAngle(fighter_gobj, attacker_gobj);
        break;

    case nFTHitlogObjectItem:
        it_hit = hitlog->attacker_hit;
        ip = itGetStruct(attacker_gobj);

        this_fp->damage_angle = it_hit->angle;
        this_fp->damage_element = it_hit->element;

        if (ABSF(ip->phys_info.vel_air.x) < 5.0F)
        {
            this_fp->lr_damage = lr_damage = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(attacker_gobj)->translate.vec.f.x) ? nGMDirectionR : nGMDirectionL;
        }
        else
        {
            lr_damage = (ip->phys_info.vel_air.x < 0) ? nGMDirectionR : nGMDirectionL;

            this_fp->lr_damage = lr_damage;
        }

        if (this_fp->player == hitlog->attacker_player)
        {
            this_fp->damage_player_number = 0;

            ftParamUpdate1PGameDamageStats(this_fp, GMBATTLE_PLAYERS_MAX, hitlog->attacker_object_class, ip->it_kind, 0, 0);
        }
        else
        {
            this_fp->damage_player_number = hitlog->attacker_player_number;
            ftParamUpdate1PGameDamageStats(this_fp, hitlog->attacker_player, hitlog->attacker_object_class, ip->it_kind, it_hit->stat_flags.halfword, it_hit->stat_count);
        }
        this_fp->damage_joint_id = hitlog->victim_hurt->joint_id;
        this_fp->damage_index = hitlog->victim_hurt->placement;

        ftMainGetBumperDamageAngle(fighter_gobj, attacker_gobj);
        break;

    case nFTHitlogObjectGround:
        gr_hit = hitlog->attacker_hit;

        this_fp->damage_angle = gr_hit->angle;
        this_fp->damage_element = gr_hit->element;

        this_fp->lr_damage = this_fp->lr;

        switch (gr_hit->kind)
        {
        case nGMHitEnvironmentAcid:
            this_fp->damage_player_number = 0;

            if (this_fp->damage_player == -1)
            {
                this_fp->damage_player = GMBATTLE_PLAYERS_MAX;
            }
            ftParamUpdate1PGameDamageStats(this_fp, this_fp->damage_player, hitlog->attacker_object_class, gr_hit->kind, 0, 0);
            break;

        case nGMHitEnvironmentPowerBlock:
            ip = itGetStruct(attacker_gobj);

            this_fp->damage_player_number = ip->damage_player_number;

            ftParamUpdate1PGameDamageStats(this_fp, ip->damage_port, hitlog->attacker_object_class, gr_hit->kind, 0, 0);

            break;

        default:
            this_fp->damage_player_number = 0;

            ftParamUpdate1PGameDamageStats(this_fp, GMBATTLE_PLAYERS_MAX, hitlog->attacker_object_class, gr_hit->kind, 0, 0);
            break;
        }
        this_fp->damage_joint_id = 0;
        this_fp->damage_index = 0;

        break;

    default:
        break;
    }
    this_fp->damage_knockback = knockback;

    if (this_fp->damage_element == nGMHitElementElectric)
    {
        this_fp->hitlag_mul = 1.5F;
    }
}

// 0x800E4870 - My brain hurts
void ftMainSearchFighterHit(GObj *this_gobj)
{
    GObj *other_gobj;
    ftStruct *this_fp;
    ftStruct *other_fp;
    s32 i, j, k, l, m, n;
    gmHitCollisionFlags those_flags;
    gmHitCollisionFlags these_flags;
    ftHitbox *this_ft_hit;
    f32 angle;
    ftHitbox *other_ft_hit;
    ftHurtbox *ft_hurt;
    sb32 is_check_self;

    this_fp = ftGetStruct(this_gobj);
    other_gobj = gOMObjCommonLinks[nOMObjCommonLinkIDFighter];
    is_check_self = FALSE;

    while (other_gobj != NULL)
    {
        if (other_gobj == this_gobj)
        {
            is_check_self = TRUE;

            goto next_gobj;
        }
        else if (other_gobj == this_fp->capture_gobj) goto next_gobj;

        other_fp = ftGetStruct(other_gobj);

        if (((gBattleState->is_team_battle == TRUE) && (gBattleState->is_team_attack == FALSE)) && (((other_fp->throw_gobj != NULL) ? other_fp->throw_team : other_fp->team) == this_fp->team))
        {
            goto next_gobj;
        }
        if (!(other_fp->is_catchstatus))
        {
            if ((other_fp->throw_gobj != NULL) && (this_gobj == other_fp->throw_gobj))
            {
                goto next_gobj;
            }
            else
            {
                k = 0;

                for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++)
                {
                    other_ft_hit = &other_fp->fighter_hit[i];

                    if (other_ft_hit->update_state != nGMHitUpdateDisable)
                    {
                        if ((this_fp->ga == nMPKineticsAir) && (other_ft_hit->is_hit_air) || (this_fp->ga == nMPKineticsGround) && (other_ft_hit->is_hit_ground))
                        {
                            these_flags.is_interact_hurt = these_flags.is_interact_shield = FALSE;

                            these_flags.group_id = 7;

                            for (m = 0; m < ARRAY_COUNT(other_ft_hit->hit_targets); m++)
                            {
                                if (this_gobj == other_ft_hit->hit_targets[m].victim_gobj)
                                {
                                    these_flags = other_ft_hit->hit_targets[m].victim_flags;

                                    break;
                                }
                            }
                            if ((!(these_flags.is_interact_hurt)) && (!(these_flags.is_interact_shield)) && (these_flags.group_id == 7))
                            {
                                gFTMainIsHurtDetect[i] = TRUE;

                                k++;

                                continue;
                            }
                        }
                    }
                    gFTMainIsHurtDetect[i] = FALSE;
                }
                if (k == 0) goto next_gobj;

                else
                {
                    k = 0;

                    if ((is_check_self != FALSE) && (this_gobj != other_fp->capture_gobj) && (other_fp->ga == nMPKineticsGround) && (this_fp->ga == nMPKineticsGround) && !(this_fp->is_catchstatus))
                    {
                        if ((this_fp->throw_gobj == NULL) || (other_gobj != this_fp->throw_gobj) && (((gBattleState->is_team_battle != TRUE) || (gBattleState->is_team_attack != FALSE)) || (((other_fp->throw_gobj != NULL) ? other_fp->throw_team : other_fp->team) != this_fp->throw_team)))
                        {
                            l = 0;

                            for (i = 0; i < ARRAY_COUNT(this_fp->fighter_hit); i++)
                            {
                                this_ft_hit = &this_fp->fighter_hit[i];

                                if (this_ft_hit->update_state != nGMHitUpdateDisable)
                                {
                                    if ((other_fp->ga == nMPKineticsAir) && (this_ft_hit->is_hit_air) || (other_fp->ga == nMPKineticsGround) && (this_ft_hit->is_hit_ground))
                                    {
                                        those_flags.is_interact_hurt = those_flags.is_interact_shield = FALSE;

                                        those_flags.group_id = 7;

                                        for (n = 0; n < ARRAY_COUNT(this_ft_hit->hit_targets); n++)
                                        {
                                            if (other_gobj == this_ft_hit->hit_targets[n].victim_gobj)
                                            {
                                                those_flags = this_ft_hit->hit_targets[n].victim_flags;

                                                break;
                                            }
                                        }
                                        if ((!(those_flags.is_interact_hurt)) && (!(those_flags.is_interact_shield)) && (those_flags.group_id == 7))
                                        {
                                            gFTMainIsHitDetect[i] = TRUE;

                                            l++;

                                            continue;
                                        }
                                    }
                                }
                                gFTMainIsHitDetect[i] = FALSE;
                            }
                            if (l != 0)
                            {
                                for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++)
                                {
                                    other_ft_hit = &other_fp->fighter_hit[i];

                                    if (gFTMainIsHurtDetect[i] == FALSE) 
                                    {
                                        continue;
                                    }
                                    else for (j = 0; j < ARRAY_COUNT(this_fp->fighter_hit); j++)
                                    {
                                        this_ft_hit = &this_fp->fighter_hit[j];

                                        if (gFTMainIsHitDetect[j] == FALSE) 
                                        {
                                            continue;
                                        }
                                        else if (gmCollisionCheckFighterHitFighterHitCollide(other_ft_hit, this_ft_hit) != FALSE)
                                        {
                                            ftMainUpdateAttackStatFighter(other_fp, other_ft_hit, this_fp, this_ft_hit, other_gobj, this_gobj);

                                            if (gFTMainIsHurtDetect[i] == FALSE)
                                            {
                                                break;
                                            }
                                            else continue;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++)
                    {
                        other_ft_hit = &other_fp->fighter_hit[i];

                        if (gFTMainIsHurtDetect[i] == FALSE) 
                        {
                            continue;
                        }
                        gFTMainIsHurtDetect[i] = gmCollisionCheckFighterInFighterRange(other_ft_hit, this_gobj);

                        if (gFTMainIsHurtDetect[i] != FALSE) 
                        {
                            k++;
                        }
                    }
                    if (k != 0)
                    {
                        if (this_fp->is_shield)
                        {
                            for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++)
                            {
                                other_ft_hit = &other_fp->fighter_hit[i];

                                if (gFTMainIsHurtDetect[i] == FALSE) 
                                {
                                    continue;
                                }
                                else if (gmCollisionCheckFighterHitShieldCollide(other_ft_hit, this_gobj, this_fp->joint[nFTPartsJointYRotN], &angle) != FALSE)
                                {
                                    ftMainUpdateShieldStatFighter(other_fp, other_ft_hit, this_fp, other_gobj, this_gobj);
                                }
                            }
                        }
                        if ((this_fp->special_hitstatus != nGMHitStatusIntangible) && (this_fp->star_hitstatus != nGMHitStatusIntangible) && (this_fp->hitstatus != nGMHitStatusIntangible))
                        {
                            for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++)
                            {
                                other_ft_hit = &other_fp->fighter_hit[i];

                                if (gFTMainIsHurtDetect[i] == FALSE) 
                                {
                                    continue;
                                }
                                else for (j = 0; j < ARRAY_COUNT(this_fp->fighter_hurt); j++)
                                {
                                    ft_hurt = &this_fp->fighter_hurt[j];

                                    if (ft_hurt->hitstatus == nGMHitStatusNone) 
                                    {
                                        break;
                                    }
                                    if (ft_hurt->hitstatus != nGMHitStatusIntangible)
                                    {
                                        if (gmCollisionCheckFighterHitFighterHurtCollide(other_ft_hit, ft_hurt) != FALSE)
                                        {
                                            ftMainUpdateDamageStatFighter(other_fp, other_ft_hit, this_fp, ft_hurt, other_gobj, this_gobj);

                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    next_gobj:
        other_gobj = other_gobj->link_next;
    }
}

// 0x800E4ED4
void ftMainSearchWeaponHit(GObj *fighter_gobj)
{
    GObj *weapon_gobj;
    s32 i, j, k, l, m, n;
    gmHitCollisionFlags fighter_flags;
    gmHitCollisionFlags item_flags;
    ftStruct *fp;
    wpStruct *wp;
    wpHitbox *wp_hit;
    f32 angle;
    Vec3f vec;
    ftHurtbox *ft_hurt;
    ftHitbox *ft_hit;
    s32 unused1;

    fp = ftGetStruct(fighter_gobj);
    weapon_gobj = gOMObjCommonLinks[nOMObjCommonLinkIDWeapon];

    while (weapon_gobj != NULL)
    {
        wp = wpGetStruct(weapon_gobj);
        wp_hit = &wp->weapon_hit;

        if ((fighter_gobj != wp->owner_gobj) && ((gBattleState->is_team_battle != TRUE) || (gBattleState->is_team_attack != FALSE) || (fp->team != wp->team)) && (wp_hit->update_state != nGMHitUpdateDisable))
        {
            if (wp_hit->interact_mask & GMHITCOLLISION_MASK_FIGHTER)
            {
                item_flags.is_interact_hurt = item_flags.is_interact_shield = item_flags.is_interact_reflect = item_flags.is_interact_absorb = FALSE;

                item_flags.group_id = 7;

                for (m = 0; m < ARRAY_COUNT(wp_hit->hit_targets); m++)
                {
                    if (fighter_gobj == wp_hit->hit_targets[m].victim_gobj)
                    {
                        item_flags = wp_hit->hit_targets[m].victim_flags;

                        break;
                    }
                }
                if (!(item_flags.is_interact_hurt) && !(item_flags.is_interact_shield) && !(item_flags.is_interact_reflect) && !(item_flags.is_interact_absorb) && (item_flags.group_id == 7))
                {
                    if ((wp_hit->can_setoff) && !(fp->is_catchstatus) && ((fp->throw_gobj == NULL) || (fp->throw_gobj != wp->owner_gobj) && ((gBattleState->is_team_battle != TRUE) || (gBattleState->is_team_attack != FALSE) || (fp->throw_team != wp->team))))
                    {

                        if (!(fp->is_reflect) || !(wp_hit->can_reflect))
                        {
                            k = 0;

                            for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
                            {
                                ft_hit = &fp->fighter_hit[i];

                                if ((ft_hit->update_state != nGMHitUpdateDisable) && ((wp->ga == nMPKineticsAir) && (ft_hit->is_hit_air) || (wp->ga == nMPKineticsGround) && (ft_hit->is_hit_ground)))
                                {
                                    fighter_flags.group_id = 7;

                                    for (n = 0; n < ARRAY_COUNT(ft_hit->hit_targets); n++)
                                    {
                                        if (weapon_gobj == ft_hit->hit_targets[n].victim_gobj)
                                        {
                                            fighter_flags = ft_hit->hit_targets[n].victim_flags;

                                            break;
                                        }
                                    }
                                    if (fighter_flags.group_id == 7)
                                    {
                                        gFTMainIsHitDetect[i] = TRUE;

                                        k++;

                                        continue;
                                    }
                                }
                                gFTMainIsHitDetect[i] = FALSE;
                            }
                            if (k != 0)
                            {
                                for (i = 0; i < wp_hit->hitbox_count; i++)
                                {
                                    for (j = 0; j < ARRAY_COUNT(fp->fighter_hit); j++)
                                    {
                                        ft_hit = &fp->fighter_hit[j];

                                        if (gFTMainIsHitDetect[j] == FALSE) 
                                        {
                                            continue;
                                        }
                                        else if (gmCollisionCheckWeaponHitFighterHitCollide(wp_hit, i, ft_hit) != FALSE)
                                        {
                                            ftMainUpdateAttackStatWeapon(wp, wp_hit, i, fp, ft_hit, weapon_gobj, fighter_gobj);

                                            if (wp->hit_attack_damage != 0) 
                                            {
                                                goto next_gobj;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                    }
                    for (i = 0, l = 0; i < wp_hit->hitbox_count; i++)
                    {
                        gFTMainIsHurtDetect[i] = gmCollisionCheckWeaponInFighterRange(wp_hit, i, fighter_gobj);

                        if (gFTMainIsHurtDetect[i] != FALSE)
                        {
                            l++;
                        }
                    }
                    if (l != 0)
                    {
                        if ((fp->is_reflect) && (wp_hit->can_reflect))
                        {
                            for (i = 0; i < wp_hit->hitbox_count; i++)
                            {
                                if (gFTMainIsHurtDetect[i] == FALSE) continue;

                                else if (gmCollisionCheckWeaponHitSpecialCollide(wp_hit, i, fp, fp->special_hit) != FALSE)
                                {
                                    ftMainUpdateReflectorStatWeapon(wp, wp_hit, fp, fighter_gobj);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->is_absorb) && (wp_hit->can_absorb))
                        {
                            for (i = 0; i < wp_hit->hitbox_count; i++)
                            {
                                if (gFTMainIsHurtDetect[i] == FALSE) 
                                {
                                    continue;
                                }
                                else if (gmCollisionCheckWeaponHitSpecialCollide(wp_hit, i, fp, fp->special_hit) != FALSE)
                                {
                                    ftMainUpdateAbsorbStatWeapon(wp, wp_hit, fp, fighter_gobj);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->is_shield) && (wp_hit->can_shield))
                        {
                            for (i = 0; i < wp_hit->hitbox_count; i++)
                            {
                                if (gFTMainIsHurtDetect[i] == FALSE) 
                                {
                                    continue;
                                }
                                else if (gmCollisionCheckWeaponHitShieldCollide(wp_hit, i, fighter_gobj, fp->joint[nFTPartsJointYRotN], &angle, &vec) != FALSE)
                                {
                                    ftMainUpdateShieldStatWeapon(wp, wp_hit, i, fp, weapon_gobj, fighter_gobj, angle, &vec);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->special_hitstatus != nGMHitStatusIntangible) && (fp->star_hitstatus != nGMHitStatusIntangible) && (fp->hitstatus != nGMHitStatusIntangible))
                        {
                            for (i = 0; i < wp_hit->hitbox_count; i++)
                            {
                                if (gFTMainIsHurtDetect[i] == FALSE) 
                                {
                                    continue;
                                }
                                else for (j = 0; j < ARRAY_COUNT(fp->fighter_hurt); j++)
                                {
                                    ft_hurt = &fp->fighter_hurt[j];

                                    if (ft_hurt->hitstatus == nGMHitStatusNone) break;

                                    if (ft_hurt->hitstatus != nGMHitStatusIntangible)
                                    {
                                        if (gmCollisionCheckWeaponHitFighterHurtCollide(wp_hit, i, ft_hurt) != FALSE)
                                        {
                                            ftMainUpdateDamageStatWeapon(wp, wp_hit, i, fp, ft_hurt, weapon_gobj, fighter_gobj);

                                            goto next_gobj;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    next_gobj:
        weapon_gobj = weapon_gobj->link_next;
    }
}

// 0x800E55DC
void ftMainSearchItemHit(GObj *fighter_gobj)
{
    GObj *item_gobj;
    s32 i, j, k, l, m, n;
    gmHitCollisionFlags fighter_flags;
    gmHitCollisionFlags article_flags;
    ftStruct *fp;
    itStruct *ip;
    itHitbox *it_hit;
    f32 angle;
    Vec3f vec;
    ftHurtbox *ft_hurt;
    ftHitbox *ft_hit;
    s32 unused1;

    fp = ftGetStruct(fighter_gobj);
    item_gobj = gOMObjCommonLinks[nOMObjCommonLinkIDItem];

    while (item_gobj != NULL)
    {
        ip = itGetStruct(item_gobj);
        it_hit = &ip->item_hit;

        if ((fighter_gobj != ip->owner_gobj) && ((gBattleState->is_team_battle != TRUE) || (gBattleState->is_team_attack != FALSE) || (fp->team != ip->team)) && (it_hit->update_state != nGMHitUpdateDisable))
        {
            if (it_hit->interact_mask & GMHITCOLLISION_MASK_FIGHTER)
            {
                article_flags.is_interact_hurt = article_flags.is_interact_shield = article_flags.is_interact_reflect = FALSE;

                article_flags.group_id = 7;

                for (m = 0; m < ARRAY_COUNT(it_hit->hit_targets); m++)
                {
                    if (fighter_gobj == it_hit->hit_targets[m].victim_gobj)
                    {
                        article_flags = it_hit->hit_targets[m].victim_flags;

                        break;
                    }
                }
                if (!(article_flags.is_interact_hurt) && !(article_flags.is_interact_shield) && !(article_flags.is_interact_reflect) && (article_flags.group_id == 7))
                {
                    if ((it_hit->can_setoff) && !(fp->is_catchstatus) && ((fp->throw_gobj == NULL) || (fp->throw_gobj != ip->owner_gobj) && ((gBattleState->is_team_battle != TRUE) || (gBattleState->is_team_attack != FALSE) || (fp->throw_team != ip->team))))
                    {
                        if (!(fp->is_reflect) || !(it_hit->can_reflect))
                        {
                            k = 0;

                            for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
                            {
                                ft_hit = &fp->fighter_hit[i];

                                if ((ft_hit->update_state != nGMHitUpdateDisable) && ((ip->ga == nMPKineticsAir) && (ft_hit->is_hit_air) || (ip->ga == nMPKineticsGround) && (ft_hit->is_hit_ground)))
                                {
                                    fighter_flags.group_id = 7;

                                    for (n = 0; n < ARRAY_COUNT(ft_hit->hit_targets); n++)
                                    {
                                        if (item_gobj == ft_hit->hit_targets[n].victim_gobj)
                                        {
                                            fighter_flags = ft_hit->hit_targets[n].victim_flags;

                                            break;
                                        }
                                    }
                                    if (fighter_flags.group_id == 7)
                                    {
                                        gFTMainIsHitDetect[i] = TRUE;

                                        k++;

                                        continue;
                                    }
                                }
                                gFTMainIsHitDetect[i] = FALSE;
                            }
                            if (k != 0)
                            {
                                for (i = 0; i < it_hit->hitbox_count; i++)
                                {
                                    for (j = 0; j < ARRAY_COUNT(fp->fighter_hit); j++)
                                    {
                                        ft_hit = &fp->fighter_hit[j];

                                        if (gFTMainIsHitDetect[j] == FALSE) 
                                        {
                                            continue;
                                        }
                                        else if (gmCollisionCheckItemHitFighterHitCollide(it_hit, i, ft_hit) != FALSE)
                                        {
                                            ftMainUpdateAttackStatItem(ip, it_hit, i, fp, ft_hit, item_gobj, fighter_gobj);

                                            if (ip->hit_attack_damage != 0) goto next_gobj;
                                        }
                                    }
                                }
                            }
                        }

                    }
                    for (i = 0, l = 0; i < it_hit->hitbox_count; i++)
                    {
                        gFTMainIsHurtDetect[i] = gmCollisionCheckItemInFighterRange(it_hit, i, fighter_gobj);

                        if (gFTMainIsHurtDetect[i] != FALSE)
                        {
                            l++;
                        }
                    }
                    if (l != 0)
                    {
                        if ((fp->is_reflect) && (it_hit->can_reflect))
                        {
                            for (i = 0; i < it_hit->hitbox_count; i++)
                            {
                                if (gFTMainIsHurtDetect[i] == FALSE) 
                                {
                                    continue;
                                }
                                else if (gmCollisionCheckItemHitSpecialCollide(it_hit, i, fp, fp->special_hit) != FALSE)
                                {
                                    ftMainUpdateReflectorStatItem(ip, it_hit, fp, fighter_gobj);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->is_shield) && (it_hit->can_shield))
                        {
                            for (i = 0; i < it_hit->hitbox_count; i++)
                            {
                                if (gFTMainIsHurtDetect[i] == FALSE) continue;

                                else if (gmCollisionCheckItemHitShieldCollide(it_hit, i, fighter_gobj, fp->joint[nFTPartsJointYRotN], &angle, &vec) != FALSE)
                                {
                                    ftMainUpdateShieldStatItem(ip, it_hit, i, fp, item_gobj, fighter_gobj, angle, &vec);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->special_hitstatus != nGMHitStatusIntangible) && (fp->star_hitstatus != nGMHitStatusIntangible) && (fp->hitstatus != nGMHitStatusIntangible))
                        {
                            for (i = 0; i < it_hit->hitbox_count; i++)
                            {
                                if (gFTMainIsHurtDetect[i] == FALSE) 
                                {
                                    continue;
                                }
                                else for (j = 0; j < ARRAY_COUNT(fp->fighter_hurt); j++)
                                {
                                    ft_hurt = &fp->fighter_hurt[j];

                                    if (ft_hurt->hitstatus == nGMHitStatusNone) 
                                    {
                                        break;
                                    }
                                    if (ft_hurt->hitstatus != nGMHitStatusIntangible)
                                    {
                                        if (gmCollisionCheckItemHitFighterHurtCollide(it_hit, i, ft_hurt) != FALSE)
                                        {
                                            ftMainUpdateDamageStatItem(ip, it_hit, i, fp, ft_hurt, item_gobj, fighter_gobj);

                                            goto next_gobj;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    next_gobj:
        item_gobj = item_gobj->link_next;
    }
}

// 0x800E5C30
sb32 ftMainGetGroundHitObstacle(ftStruct *fp, grHitbox **p_gr_hit)
{
    if ((fp->damagefloor_wait == 0) && (fp->ga == nMPKineticsGround) && (fp->coll_data.ground_line_id != -1) && (fp->coll_data.ground_line_id != -2))
    {
        switch (fp->coll_data.ground_flags & MPCOLL_VERTEX_MAT_MASK)
        {
        case nMPMaterialFireWeakHz1:
            *p_gr_hit = &dFTMainGroundHitCollisionAttributes[0];
            return TRUE;

        case nMPMaterialFireStrongVt1:
            *p_gr_hit = &dFTMainGroundHitCollisionAttributes[1];
            return TRUE;

        case nMPMaterialFireWeakVt1:
            *p_gr_hit = &dFTMainGroundHitCollisionAttributes[2];
            return TRUE;

        case nMPMaterialSpikeStrongHz1:
            *p_gr_hit = &dFTMainGroundHitCollisionAttributes[3];
            return TRUE;

        case nMPMaterialFireWeakVt2:
            *p_gr_hit = &dFTMainGroundHitCollisionAttributes[4];
            return TRUE;

        case nMPMaterialFireWeakVt3:
            *p_gr_hit = &dFTMainGroundHitCollisionAttributes[5];
            return TRUE;

        default:
            return FALSE;
        }
    }
    else return FALSE;
}

// 0x800E5D20
void ftMainSearchGroundHit(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    grHazard *ge = &sFTMainGroundHazards[0];
    s32 i;
    grHitbox *gr_hit;
    s32 kind;

    if (fp->hitlag_timer == 0)
    {
        if (fp->acid_wait != 0)
        {
            fp->acid_wait--;
        }
        if (fp->damagefloor_wait != 0)
        {
            fp->damagefloor_wait--;
        }
    }
    if (ftParamGetBestHitStatusAll(fighter_gobj) == nGMHitStatusNormal)
    {
        for (i = 0; i < sFTMainGroundHazardsNum; i++, ge++)
        {
            if ((ge->gobj != NULL) && (ge->proc_update(ge->gobj, fighter_gobj, &gr_hit, &kind) != FALSE))
            {
                ftMainUpdateDamageStatGround(ge->gobj, fighter_gobj, fp, gr_hit, kind);
            }
        }
        if (ftMainGetGroundHitObstacle(fp, &gr_hit) != FALSE)
        {
            ftMainUpdateDamageStatGround(NULL, fighter_gobj, fp, gr_hit, gr_hit->kind);
        }
    }
}

// 0x800E5E58 - Meth
void ftMainSearchFighterCatch(GObj *this_gobj)
{
    GObj *other_gobj;
    ftStruct *this_fp;
    ftStruct *other_fp;
    s32 i, j, m;
    ftHurtbox *ft_hurt;
    gmHitCollisionFlags catch_mask;
    ftHitbox *ft_hit;

    this_fp = ftGetStruct(this_gobj);

    this_fp->search_gobj = NULL;
    this_fp->search_gobj_dist = F32_MAX;

    other_gobj = gOMObjCommonLinks[nOMObjCommonLinkIDFighter];

    while (other_gobj != NULL)
    {
        if (other_gobj == this_gobj) 
        {
            goto next_gobj;
        }
        other_fp = ftGetStruct(other_gobj);

        if (other_fp->is_nullstatus) 
        {
            goto next_gobj;
        }
        if (other_fp->ft_kind == nFTKindBoss)
        {
            goto next_gobj;
        }
        if ((gBattleState->is_team_battle == TRUE) && (gBattleState->is_team_attack == FALSE) && (this_fp->team == other_fp->team)) 
        {
            goto next_gobj;
        }
        if (other_fp->capture_immune_mask & this_fp->catch_mask)
        {
            goto next_gobj;
        }
        if ((other_fp->special_hitstatus != nGMHitStatusNormal) || (other_fp->star_hitstatus != nGMHitStatusNormal) || (other_fp->hitstatus != nGMHitStatusNormal)) 
        {
            goto next_gobj;
        }
        for (i = 0; i < ARRAY_COUNT(this_fp->fighter_hit) ^ 0; i++) // XOR 0 ???
        {
            ft_hit = &this_fp->fighter_hit[i];

            if (ft_hit->update_state == nGMHitUpdateDisable) 
            {
                continue;
            }
            if ((other_fp->ga == nMPKineticsAir) && !(ft_hit->is_hit_air) || (other_fp->ga == nMPKineticsGround) && !(ft_hit->is_hit_ground)) 
            {
                continue;
            }
            catch_mask.is_interact_hurt = catch_mask.is_interact_shield = FALSE;

            catch_mask.group_id = 7;

            for (m = 0; m < ARRAY_COUNT(ft_hit->hit_targets); m++)
            {
                if (other_gobj == ft_hit->hit_targets[m].victim_gobj)
                {
                    catch_mask = ft_hit->hit_targets[m].victim_flags;

                    break;
                }
            }
            if ((catch_mask.is_interact_hurt) || (catch_mask.is_interact_shield) || (catch_mask.group_id != 7)) continue;

            for (j = 0; j < ARRAY_COUNT(other_fp->fighter_hurt); j++)
            {
                ft_hurt = &other_fp->fighter_hurt[j];

                if (ft_hurt->hitstatus == nGMHitStatusNone) 
                {
                    break;
                }
                if ((ft_hurt->hitstatus != nGMHitStatusIntangible) && (ft_hurt->hitstatus != nGMHitStatusInvincible))
                {
                    if ((ft_hurt->is_grabbable != FALSE) && (gmCollisionCheckFighterHitFighterHurtCollide(ft_hit, ft_hurt) != FALSE))
                    {
                        ftMainUpdateCatchStatFighter(this_fp, ft_hit, other_fp, this_gobj, other_gobj);

                        goto next_gobj;
                    }
                }
            }        
        }
    next_gobj:
        other_gobj = other_gobj->link_next;
    }
}

// 0x800E6100
void ftMainProcSearchAllCatch(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftMainSearchHitHazard(fighter_gobj);

    if (fp->is_catchstatus)
    {
        ftMainSearchFighterCatch(fighter_gobj);

        if (fp->search_gobj != NULL)
        {
            fp->proc_catch(fighter_gobj);
            fp->proc_capture(fp->search_gobj, fighter_gobj);
        }
    }
}

// 0x800E6178
void ftMainProcSearchAllHit(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (!(fp->is_nullstatus))
    {
        sFTMainHitlogID = 0;

        ftMainSearchFighterHit(fighter_gobj);
        ftMainSearchItemHit(fighter_gobj);
        ftMainSearchWeaponHit(fighter_gobj);
        ftMainSearchGroundHit(fighter_gobj);

        if (sFTMainHitlogID != 0)
        {
            ftMainProcessHitCollisionStatsMain(fighter_gobj);
        }
    }
}

// 0x800E61EC
void ftMainProcUpdateMain(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    s32 damage;
    s32 status_id;
    f32 knockback_resist;
    sb32 is_shieldbreak;
    u32 hitlag_timer;
    s32 sp84;
    s32 element;

    damage = 0;
    is_shieldbreak = FALSE;
    status_id = fp->status_info.status_id;
    hitlag_timer = fp->hitlag_timer;
    sp84 = 0;

    if (fp->unk_ft_0x7AC != 0)
    {
        fp->x3C_unk += fp->unk_ft_0x7AC;
    }
    if (!(fp->is_shield) && (fp->shield_health < 55))
    {
        fp->shield_lifeup_wait--;

        if (fp->shield_lifeup_wait == 0.0F)
        {
            fp->shield_health++;

            fp->shield_lifeup_wait = 10.0F;
        }
    }
    fp->shield_health -= fp->shield_damage_total;

    if (fp->shield_health <= 0)
    {
        fp->shield_health = (fp->ft_kind == nFTKindYoshi) ? 30 : 30;

        is_shieldbreak = TRUE;
    }
    if (fp->damage_knockback != 0.0F)
    {
        if ((fp->status_info.status_id == nFTCommonStatusSquat) || (fp->status_info.status_id == nFTCommonStatusSquatWait))
        {
            fp->damage_knockback *= (2.0F / 3.0F);
        }
        if (fp->status_info.status_id == nFTCommonStatusTwister)
        {
            fp->damage_kind = 2;
        }
        if (fp->knockback_resist_status < fp->knockback_resist_passive)
        {
            knockback_resist = fp->knockback_resist_passive;
        }
        else knockback_resist = fp->knockback_resist_status;

        fp->damage_knockback -= knockback_resist;

        if (fp->damage_knockback <= 0)
        {
            fp->damage_knockback = 0;
        }
        ftParamUpdateDamage(fp, fp->damage_queue);

        if (fp->proc_trap != NULL)
        {
            fp->proc_trap(fighter_gobj);
        }
        if (fp->ft_kind != nFTKindBoss)
        {
            switch (fp->damage_kind)
            {
            case 4:
                break;

            case nGMHitEnvironmentPowerBlock:
                ftParamStopVoiceRunProcDamage(fighter_gobj);
                ftCommonDamageGotoDamageStatus(fighter_gobj);
                break;

            case nGMHitEnvironmentTwister:
                ftCommonDamageSetDamageColAnim(fighter_gobj);
                break;

            case nGMHitEnvironmentTaruCann:
                ftParamStopVoiceRunProcDamage(fighter_gobj);
                ftCommonDamageUpdateCatchResist(fighter_gobj);
                break;

            default:
                ftCommonDamageUpdateMain(fighter_gobj);
                break;
            }
        }
        else
        {
            ftCommonDamageSetDamageColAnim(fighter_gobj);
            ftBossCommonUpdateDamageStats(fighter_gobj);
        }
        damage = fp->damage_lag;
        sp84 = 1;

        ftParamSetDamageShuffle(fp, (fp->damage_element == nGMHitElementElectric) ? TRUE : FALSE, damage, status_id, fp->hitlag_mul);

        if ((s32)((fp->damage_queue * 0.75F) + 4.0F) > 0)
        {
            ftParamMakeRumble(fp, 0, (s32)((fp->damage_queue * 0.75F) + 4.0F));
        }
    }
    else if (fp->shield_damage != 0)
    {
        if (is_shieldbreak != FALSE)
        {
            ftCommonShieldBreakFlyCommonSetStatus(fighter_gobj);
        }
        else ftCommonGuardSetOffSetStatus(fighter_gobj);

        damage = fp->shield_damage;
    }
    else if (fp->attack_shield_push != 0)
    {
        if (fp->proc_shield != NULL)
        {
            fp->proc_shield(fighter_gobj);
        }
        if ((fp->attack_rebound != 0) && (fp->catch_gobj == NULL) && (fp->capture_gobj == NULL))
        {
            ftParamStopVoiceRunProcDamage(fighter_gobj);
            ftCommonReboundWaitSetStatus(fighter_gobj);
        }
        damage = fp->attack_shield_push;
    }
    else if (fp->attack_damage != 0)
    {
        if (fp->proc_hit != NULL)
        {
            fp->proc_hit(fighter_gobj);
        }
        damage = fp->attack_damage;

        if (fp->stat_flags.stat_attack_id == nFTStatusAttackIDBatSwing4)
        {
            ftParamMakeRumble(fp, 10, 0);
        }
        else if ((s32) ((fp->attack_damage * 0.5F) + 2.0F) > 0)
        {
            ftParamMakeRumble(fp, 5, (s32)((fp->attack_damage * 0.5F) + 2.0F));
        }
    }
    else if (fp->reflect_damage != 0)
    {
        ftCommonShieldBreakFlyReflectorSetStatus(fighter_gobj);
    }
    else if (fp->lr_reflect != nGMDirectionC)
    {
        switch (fp->special_hit->hit_type)
        {
        case nFTSpecialHitKindFoxReflector:
            ftFoxSpecialLwHitSetStatus(fighter_gobj);
            break;

        case nFTSpecialHitKindNessReflector:
            func_800269C0_275C0(nGMSoundFGMBatHit);
            break;
        }
    }
    else if (fp->lr_absorb != nGMDirectionC)
    {
        ftNessSpecialLwProcAbsorb(fighter_gobj);
    }
    if (damage != 0)
    {
        fp->hitlag_timer = ftParamGetHitLag(damage, status_id, fp->hitlag_mul);

        if ((fp->hitlag_timer != 0) && (sp84 != 0))
        {
            fp->x192_flag_b6 = TRUE;
        }
        fp->input.pl.button_tap = fp->input.pl.button_tap_prev = 0;

        if (fp->proc_lagstart != NULL)
        {
            fp->proc_lagstart(fighter_gobj);
        }
    }
    fp->unk_ft_0x7AC = 0;
    fp->attack_damage = 0;
    fp->attack_shield_push = 0;
    fp->shield_damage = 0;
    fp->shield_damage_total = 0;
    fp->damage_lag = 0;
    fp->damage_queue = 0;
    fp->damage_kind = 0;

    fp->lr_reflect = nGMDirectionC;
    fp->reflect_damage = 0;
    fp->lr_absorb = nGMDirectionC;

    fp->unk_ft_0x7A0 = 0;
    fp->attack_rebound = 0;
    fp->damage_knockback = 0;
    fp->hitlag_mul = 1.0F;

    if ((hitlag_timer == 0) && (fp->afterimage.drawstatus != -1))
    {
        switch (fp->afterimage.is_itemswing)
        {
        case FALSE:
            if ((fp->ft_kind == nFTKindLink) && (fp->joint_drawstatus[11 - nFTPartsJointEnumMax].drawstatus_current == 0))
            {
                ftParts *ft_parts = fp->joint[11]->user_data.p;

                func_ovl2_800EDBA4(fp->joint[11]);

                fp->afterimage.desc[fp->afterimage.desc_index].translate_x = ft_parts->mtx_translate[3][0];
                fp->afterimage.desc[fp->afterimage.desc_index].translate_y = ft_parts->mtx_translate[3][1];
                fp->afterimage.desc[fp->afterimage.desc_index].translate_z = ft_parts->mtx_translate[3][2];
                fp->afterimage.desc[fp->afterimage.desc_index].vec.x = ft_parts->mtx_translate[2][0];
                fp->afterimage.desc[fp->afterimage.desc_index].vec.y = ft_parts->mtx_translate[2][1];
                fp->afterimage.desc[fp->afterimage.desc_index].vec.z = ft_parts->mtx_translate[2][2];

                if (fp->afterimage.desc_index == 2)
                {
                    fp->afterimage.desc_index = 0;
                }
                else fp->afterimage.desc_index++;

                if (fp->afterimage.drawstatus <= 2)
                {
                    fp->afterimage.drawstatus++;
                }
            }
            break;

        case TRUE:
            if ((fp->item_hold != NULL) && (fp->is_show_item) && (itGetStruct(fp->item_hold)->it_kind == nITKindSword))
            {
                s32 unused;
                Mtx44f mtx;

                func_ovl0_800C9A38(mtx, fp->joint[fp->attributes->joint_itemlight_id]);

                fp->afterimage.desc[fp->afterimage.desc_index].translate_x = mtx[3][0];
                fp->afterimage.desc[fp->afterimage.desc_index].translate_y = mtx[3][1];
                fp->afterimage.desc[fp->afterimage.desc_index].translate_z = mtx[3][2];
                fp->afterimage.desc[fp->afterimage.desc_index].vec.x = mtx[1][0];
                fp->afterimage.desc[fp->afterimage.desc_index].vec.y = mtx[1][1];
                fp->afterimage.desc[fp->afterimage.desc_index].vec.z = mtx[1][2];

                lbVector_Vec3fNormalize(&fp->afterimage.desc[fp->afterimage.desc_index].vec);

                if (fp->afterimage.desc_index == 2)
                {
                    fp->afterimage.desc_index = 0;
                }
                else fp->afterimage.desc_index++;

                if (fp->afterimage.drawstatus <= 2)
                {
                    fp->afterimage.drawstatus++;
                }
            }
            break;
        }
    }
}

// 0x800E69C4
void ftMainUpdateWithheldPartID(ftStruct *fp, s32 withheld_part_id)
{
    ftWithheldPart *withheld_part;
    void *dl;
    DObj *root_joint;
    DObj *child_joint;
    DObj *sibling_joint;
    ftAttributes *attributes;
    ftCommonPart *common_part;
    DObj *parent_joint;
    ftParts *ft_parts;

    attributes = fp->attributes;
    withheld_part = &attributes->withheld_parts[withheld_part_id];

    if (withheld_part->root_joint_id >= nFTPartsJointEnumMax)
    {
        if (fp->detail_current == nFTPartsDetailHigh)
        {
            common_part = &fp->attributes->common_parts_container->common_parts[0];
        }
        else if (attributes->common_parts_container->common_parts[1].dobj_desc[withheld_part->root_joint_id - nFTPartsJointEnumMax].display_list != NULL)
        {
            common_part = &attributes->common_parts_container->common_parts[1];
        }
        else common_part = &attributes->common_parts_container->common_parts[0];
    }
    else common_part = NULL;

    dl = (common_part != NULL) ? common_part->dobj_desc[withheld_part->root_joint_id - nFTPartsJointEnumMax].display_list : NULL;

    root_joint = omAddDObjForGObj(fp->fighter_gobj, dl);
    root_joint->sib_prev->sib_next = NULL;
    root_joint->sib_prev = NULL;

    if (dl != NULL)
    {
        func_ovl0_800C8CB8(root_joint, common_part->mobjsub[withheld_part->root_joint_id - nFTPartsJointEnumMax], common_part->costume_matanim_joint[withheld_part->root_joint_id - nFTPartsJointEnumMax], NULL, fp->costume);
    }
    if (common_part != NULL)
    {
        fp->joint_drawstatus[withheld_part->root_joint_id - nFTPartsJointEnumMax].drawstatus_default = fp->joint_drawstatus[withheld_part->root_joint_id - nFTPartsJointEnumMax].drawstatus_current = (dl != NULL) ? 0 : -1;
    }
    parent_joint = fp->joint[withheld_part->parent_joint_id];

    switch (withheld_part->joint_kind)
    {
    case 0:
        if (parent_joint->child != NULL)
        {
            sibling_joint = parent_joint->child->sib_next;
            child_joint = parent_joint->child;

            while (sibling_joint != NULL)
            {
                child_joint = sibling_joint;
                sibling_joint = sibling_joint->sib_next;
            }
            child_joint->sib_next = root_joint;
            root_joint->sib_prev = child_joint;
        }
        else parent_joint->child = root_joint;
        root_joint->parent = parent_joint;
        break;

    case 1:
        if (parent_joint->child != NULL)
        {
            child_joint = parent_joint->child;
            child_joint->sib_prev = root_joint;
            root_joint->sib_next = child_joint;
        }
        parent_joint->child = root_joint;
        root_joint->parent = parent_joint;
        break;

    case 2:
        child_joint = parent_joint->child->sib_next;
        child_joint->sib_prev = root_joint;
        root_joint->sib_next = child_joint;
        child_joint = parent_joint->child;
        child_joint->sib_next = root_joint;
        root_joint->parent = parent_joint;
        root_joint->sib_prev = child_joint;
        break;

    case 3:
        if (parent_joint->child != NULL)
        {
            child_joint = parent_joint->child;
            root_joint->child = child_joint;

            do
            {
                child_joint->parent = root_joint;
                child_joint = child_joint->sib_next;
            }
            while (child_joint != NULL);
        }
        parent_joint->child = root_joint;

        root_joint->parent = parent_joint;
        break;
    }
    fp->joint[withheld_part->root_joint_id] = root_joint;

    root_joint->user_data.p = ft_parts = ftManagerGetFighterPartsSetNextAlloc();

    ft_parts->flags = attributes->common_parts_container->common_parts[fp->detail_current - 1].flags;
    ft_parts->joint_id = withheld_part->root_joint_id;

    if (withheld_part->partindex_0x8 != 0)
    {
        func_ovl0_800C8A58(root_joint, 0x4B, 0, 0, fp->unk_ft_0x149);
    }
}

// 0x800E6CE0
void ftMainAddWithheldPartID(ftStruct *fp, s32 withheld_part_id)
{
    DObj *new_parent_joint;
    DObj *sibling_joint;
    ftWithheldPart *withheld_part;
    DObj *root_joint;
    DObj *child_joint;  // var_a2
    DObj *new_child_joint; // var_a3
    DObj *parent_joint; // new_var

    withheld_part = &fp->attributes->withheld_parts[withheld_part_id];
    root_joint = fp->joint[withheld_part->root_joint_id];

    if (withheld_part->root_joint_id == nFTPartsJointTransN)
    {
        parent_joint = root_joint->parent;
        child_joint = root_joint->child;
        new_parent_joint = parent_joint;
        new_child_joint = child_joint;

        if (new_child_joint != NULL)
        {
            sibling_joint = root_joint->sib_prev;

            new_child_joint = child_joint;
            child_joint = sibling_joint;

            if (sibling_joint == NULL)
            {
                new_parent_joint->child = new_child_joint;
            }
            else
            {
                child_joint->sib_next = new_child_joint;
                new_child_joint->sib_prev = root_joint->sib_prev;
            }
            child_joint = new_child_joint->sib_next;
            new_child_joint->parent = new_parent_joint;

            while (child_joint != NULL)
            {
                new_child_joint = child_joint;
                child_joint->parent = new_parent_joint;
                child_joint = child_joint->sib_next;
            }

            new_child_joint->sib_next = root_joint->sib_next;
            new_parent_joint = root_joint->sib_next;

            if (new_parent_joint != NULL)
            {
                new_parent_joint->sib_prev = new_child_joint;
            }
        }
        else
        {
            sibling_joint = root_joint->sib_prev;

            if (sibling_joint == NULL)
            {
                new_parent_joint->child = root_joint->sib_next;
            }
            else sibling_joint->sib_next = root_joint->sib_next;

            new_parent_joint = root_joint->sib_next;

            if (new_parent_joint != NULL)
            {
                new_parent_joint->sib_prev = root_joint->sib_prev;
            }
        }
        root_joint->child = NULL;
        root_joint->sib_prev = NULL;
        root_joint->sib_next = NULL;
        root_joint->parent = NULL;

        new_parent_joint = fp->joint[withheld_part->parent_joint_id];

        if (new_parent_joint->child != NULL)
        {
            new_child_joint = new_parent_joint->child;
            root_joint->child = new_parent_joint->child;

            do
            {
                new_child_joint->parent = root_joint;
                new_child_joint = new_child_joint->sib_next;
            } 
            while (new_child_joint != NULL);
        }
        new_parent_joint->child = root_joint;
        root_joint->parent = new_parent_joint;
    }
}

// 0x800E6E00
void ftMainEjectWithheldPartID(ftStruct *fp, s32 withheld_part_id)
{
    ftWithheldPart *withheld_part = &fp->attributes->withheld_parts[withheld_part_id];
    DObj *root_joint = fp->joint[withheld_part->root_joint_id];
    DObj *parent_joint;
    DObj *child_joint;
    DObj *sibling_joint;
    DObj *new_sibling_joint;

    ftManagerSetFighterPartsPrevAlloc(root_joint->user_data.p);

    child_joint = root_joint->child;
    parent_joint = root_joint->parent;

    if (child_joint != NULL)
    {
        sibling_joint = child_joint;

        if (root_joint->sib_prev == NULL)
        {
            parent_joint->child = child_joint;
        }
        else
        {
            root_joint->sib_prev->sib_next = sibling_joint;
            sibling_joint->sib_prev = (child_joint = root_joint)->sib_prev;
        }
        new_sibling_joint = sibling_joint->sib_next;
        sibling_joint->parent = parent_joint;

        while (new_sibling_joint != NULL)
        {
            sibling_joint = new_sibling_joint;
            new_sibling_joint->parent = parent_joint;
            new_sibling_joint = new_sibling_joint->sib_next;
        }
        sibling_joint->sib_next = root_joint->sib_next;
        new_sibling_joint = root_joint->sib_next;

        if (new_sibling_joint != NULL)
        {
            new_sibling_joint->sib_prev = sibling_joint;
        }
    }
    else
    {
        if (root_joint->sib_prev == NULL)
        {
            parent_joint->child = root_joint->sib_next;
        }
        else root_joint->sib_prev->sib_next = root_joint->sib_next;
        
        if (root_joint->sib_next != NULL)
        {
            root_joint->sib_next->sib_prev = root_joint->sib_prev;
        }
    }
    fp->joint[withheld_part->root_joint_id] = NULL;
    root_joint->sib_next = NULL;
    root_joint->sib_prev = NULL;
    root_joint->child = NULL;

    omEjectDObj(root_joint);
}

// 0x800E6F24
void ftMainSetFighterStatus(GObj *fighter_gobj, s32 status_id, f32 frame_begin, f32 anim_rate, u32 flags)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    intptr_t event_file_head;
    ftAttributes *attributes = fp->attributes;
    ftStatusDesc *status_struct;
    ftOpeningDesc *opening_struct;
    f32 anim_frame;
    s32 status_struct_id;
    s32 anim_flags_update;
    s32 anim_flags_bak;
    s32 unused1;
    gmStatFlags status_flags;
    gmStatFlags attack_flags;
    s32 unused2;
    s32 motion_id;
    void *event_script_ptr;
    DObjDesc *dobj_desc;
    s32 unused3;
    ftStatusDesc *status_desc;
    ftScriptInfoArray *script_array;
    ftScriptInfo *script_info;
    DObj *joint;
    DObj *transn_parent;                // Parent of TrasnN_Joint
    DObj *transn_child;                 // Child of TransN_Joint
    s32 i;

    status_struct = NULL;
    opening_struct = NULL;

    status_flags = fp->stat_flags;

    if (fp->is_effect_interrupt)
    {
        ftMainUpdateMotionEventsDefaultEffect(fighter_gobj);

        if (fp->proc_accessory != NULL)
        {
            fp->proc_accessory(fighter_gobj);
        }
    }
    fp->status_info.status_id = status_id;

    if (fp->detail_current != fp->detail_default)
    {
        ftParamSetModelPartDetailAll(fighter_gobj, fp->detail_default);
        
        fp->detail_current = fp->detail_default;
    }
    if (!(flags & FTSTATUS_PRESERVE_HIT) && (fp->is_hitbox_active))
    {
        ftParamClearHitAll(fighter_gobj);
    }
    if (!(flags & FTSTATUS_PRESERVE_THROWPOINTER))
    {
        fp->throw_gobj = NULL;
    }
    if (!(flags & FTSTATUS_PRESERVE_HITSTATUS))
    {
        if (fp->is_hitstatus_nodamage)
        {
            ftParamSetHitStatusPartAll(fighter_gobj, nGMHitStatusNormal);
        }
        if (fp->hitstatus != nGMHitStatusNormal)
        {
            ftParamSetHitStatusAll(fighter_gobj, nGMHitStatusNormal);
        }
    }
    if (fp->is_hurtbox_modify)
    {
        ftParamResetFighterHurtPartAll(fighter_gobj);
    }
    if (!(flags & FTSTATUS_PRESERVE_MODELPART) && (fp->is_modelpart_modify))
    {
        ftParamResetModelPartAll(fighter_gobj);
    }
    if (!(flags & FTSTATUS_PRESERVE_TEXTUREPART) && (fp->is_texturepart_modify))
    {
        ftParamResetTexturePartAll(fighter_gobj);
    }
    if (!(flags & FTSTATUS_PRESERVE_COLANIM) && (dFTCommonDataColAnimDescs[fp->colanim.colanim_id].is_unlocked != FALSE))
    {
        ftParamResetStatUpdateColAnim(fighter_gobj);
    }
    if (!(flags & FTSTATUS_PRESERVE_EFFECT) && (fp->is_attach_effect))
    {
        ftParamProcStopEffect(fighter_gobj);
    }
    fp->is_reflect = FALSE;
    fp->is_absorb = FALSE;
    fp->is_shield = FALSE;

    if (!(flags & FTSTATUS_PRESERVE_FASTFALL))
    {
        fp->is_fast_fall = FALSE;
    }

    fp->is_invisible = FALSE;
    fp->x18E_flag_b0 = FALSE;
    fp->x18E_flag_b1 = FALSE;
    fp->is_playertag_hide = FALSE;
    fp->is_playing_effect = FALSE; // Not sure exactly what this is, but it prevents certain ColAnim events from running if true?

    if (fp->status_info.pl_kind != nFTPlayerKindDemo)
    {
        gmRumbleSetRumbleID(fp->player, 2);
        gmRumbleSetRumbleID(fp->player, 3);

        if (!(flags & FTSTATUS_PRESERVE_RUMBLE))
        {
            gmRumbleSetRumbleID(fp->player, 7);
        }
        fp->joint[nFTPartsJointTopN]->rotate.vec.f.y = fp->lr * F_CLC_DTOR32(90.0F); // HALF_PI32

        DObjGetStruct(fighter_gobj)->rotate.vec.f.z = 0.0F;

        fp->joint[nFTPartsJointTopN]->rotate.vec.f.x = DObjGetStruct(fighter_gobj)->rotate.vec.f.z;

        fp->phys_info.vel_air.z = 0.0F;
        fp->phys_info.vel_ground.z = 0.0F;
    }

    fp->is_ignore_jostle = FALSE;
    fp->is_hitstun = FALSE;

    fp->damage_mul = 1.0F;

    if ((fp->ga == nMPKineticsGround) && !(flags & FTSTATUS_PRESERVE_DAMAGEPLAYER))
    {
        fp->damage_player = -1;
    }
    if (!(flags & FTSTATUS_PRESERVE_SLOPECONTOUR))
    {
        fp->slope_contour = 0;
    }
    fp->coll_data.ignore_line_id = -1;

    fp->is_show_item = TRUE;
    fp->is_cliff_hold = FALSE;

    ftParamSetCaptureImmuneMask(fp, FTCATCHKIND_MASK_NONE);

    fp->is_nullstatus = FALSE;
    fp->is_damage_resist = FALSE;
    fp->is_ignore_training_menu = FALSE;

    if (fp->camera_mode != 3)
    {
        fp->camera_mode = 0;
    }
    fp->camera_zoom_range = 1.0F;

    if (!(flags & FTSTATUS_PRESERVE_PLAYERTAG))
    {
        fp->playertag_wait = 0;
    }
    fp->is_special_interrupt = FALSE;
    fp->is_catchstatus = FALSE;
    fp->x192_flag_b1 = FALSE;

    if (!(flags & FTSTATUS_PRESERVE_SHUFFLETIME))
    {
        fp->shuffle_timer = 0;
    }
    if (!(flags & FTSTATUS_PRESERVE_LOOPSFX))
    {
        ftParamStopLoopSFX(fp);
    }
    fp->knockback_resist_status = 0.0F;
    fp->damage_stack = 0.0F;

    if (!(flags & FTSTATUS_PRESERVE_AFTERIMAGE))
    {
        fp->afterimage.drawstatus = -1;
    }
    if ((status_id != nFTCommonStatusWait) && (status_id != nFTCommonStatusWalkSlow) && (status_id != nFTCommonStatusWalkMiddle) && (status_id != nFTCommonStatusWalkFast))
    {
        fp->attack1_followup_frames = 0.0F;
    }
    if ((fp->status_info.pl_kind != nFTPlayerKindDemo) && (fp->dl_link != 9))
    {
        ftParamMoveDLLink(fighter_gobj, 9);
    }
    fp->status_info.status_time_spent = 0;

    if (status_id >= FTSTAT_CHARDATA_START) // Check if Character Data status ID
    {
        status_id -= FTSTAT_CHARDATA_START;
    }
    if (status_id >= FTSTAT_OPENING1_START) // Check if Opening status ID 1
    {
        opening_struct = D_ovl1_80390D20[fp->ft_kind];
        status_struct_id = status_id - FTSTAT_OPENING1_START;
    }
    else if (status_id >= FTSTAT_OPENING2_START) // Check if Opening status ID 2
    {
        opening_struct = &D_ovl1_80390BE8;
        status_struct_id = status_id - FTSTAT_OPENING2_START;
    }
    else if (status_id >= nFTCommonStatusSpecialStart)
    {
        status_struct = dFTMainSpecialStatusDescs[fp->ft_kind];
        status_struct_id = status_id - nFTCommonStatusSpecialStart;
    }
    else if (status_id >= nFTCommonStatusActionStart)
    {
        status_struct = dFTCommonActionStatusDesc;
        status_struct_id = status_id - nFTCommonStatusActionStart;
    }
    else
    {
        status_struct = dFTCommonNullStatusDesc;
        status_struct_id = status_id;
    }
    status_desc = &status_struct[status_struct_id];

    if (fp->status_info.pl_kind != nFTPlayerKindDemo)
    {
        if ((status_struct[status_struct_id].mflags.motion_attack_id == nFTMotionAttackIDNone) || (status_struct[status_struct_id].mflags.motion_attack_id != fp->attack_id))
        {
            ftParamSetMotionID(fp, status_struct[status_struct_id].mflags.motion_attack_id);
        }
        attack_flags = status_desc->sflags;

        if ((attack_flags.stat_attack_id == nFTStatusAttackIDNone) || (attack_flags.stat_attack_id != fp->stat_flags.stat_attack_id))
        {
            ftParamSetStatUpdate(fp, status_struct[status_struct_id].sflags.halfword);
        }
    }
    if (fp->proc_status != NULL)
    {
        fp->proc_status(fighter_gobj);
        fp->proc_status = NULL;
    }
    ftParamUpdate1PGameAttackStats(fp, status_flags.halfword);

    if (status_struct != NULL)
    {
        motion_id = status_struct[status_struct_id].mflags.motion_id;
        fp->status_info.motion_id = motion_id;
        script_array = fp->ft_data->battlemotion;
    }
    else
    {
        motion_id = opening_struct[status_struct_id].motion_id - 0x10000;
        fp->status_info.motion_id = motion_id;
        script_array = fp->ft_data->submotion;
    }
    if ((motion_id != -1) && (motion_id != -2))
    {
        script_info = &script_array->script_info[motion_id];

        if (script_info->anim_flags.flags.is_use_shieldpose)
        {
            fp->anim_bank = (void*)((intptr_t)script_info->anim_file_id + (uintptr_t)fp->ft_data->p_file_shieldpose);
        }
        else if (script_info->anim_file_id != 0)
        {
            rldm_get_file_external_force_heap(script_info->anim_file_id, fp->anim_load);
            fp->anim_bank = fp->anim_load;
        }
        else fp->anim_bank = NULL;
        
        if (fp->anim_bank != NULL)
        {
            anim_flags_bak = fp->anim_flags.word & 0xFFFFFFE0;
            fp->anim_flags.word = script_info->anim_flags.word;
            anim_flags_update = fp->anim_flags.word & 0xFFFFFFE0;

            for (i = 0; ((anim_flags_bak != 0) || (anim_flags_update != 0)); i++, anim_flags_update <<= 1, anim_flags_bak <<= 1)
            {
                if (!(anim_flags_bak & (1 << 31)))
                {
                    if (anim_flags_update & (1 << 31))
                    {
                        ftMainUpdateWithheldPartID(fp, i);
                    }
                }
                else if (anim_flags_update & (1 << 31))
                {
                    ftMainAddWithheldPartID(fp, i);
                }
                else ftMainEjectWithheldPartID(fp, i);
            }

            dobj_desc = attributes->common_parts_container->common_parts[fp->detail_current - 1].dobj_desc;

            for (i = nFTPartsJointEnumMax; dobj_desc->index != DOBJ_ARRAY_MAX; i++, dobj_desc++)
            {
                joint = fp->joint[i];

                if (joint != NULL)
                {
                    joint->translate.vec.f = dobj_desc->translate;

                    joint->rotate.vec.f = dobj_desc->rotate;

                    joint->scale.vec.f = dobj_desc->scale;

                    joint->flags = DOBJ_FLAG_NONE;
                }
            }
            if (fp->anim_flags.flags.is_use_transn_joint)
            {
                joint = fp->joint[nFTPartsJointTransN];
                
                joint->translate.vec.f.x = joint->translate.vec.f.y = joint->translate.vec.f.z = 0.0F;

                joint->rotate.vec.f.z = 0.0F;

                joint->flags = DOBJ_FLAG_NONE;
            }
            if (fp->anim_flags.flags.is_use_xrotn_joint)
            {
                joint = fp->joint[nFTPartsJointXRotN];

                joint->translate.vec.f.x = joint->translate.vec.f.y = joint->translate.vec.f.z = 0.0F;
                
                joint->rotate.vec.f.x = joint->rotate.vec.f.y = joint->rotate.vec.f.z = 0.0F; 
                
                joint->scale.vec.f.x = joint->scale.vec.f.y = joint->scale.vec.f.z = 1.0F;

                joint->flags = DOBJ_FLAG_NONE;
            }
            if (fp->anim_flags.flags.is_use_yrotn_joint)
            {
                joint = fp->joint[nFTPartsJointYRotN];

                joint->translate.vec.f.x = joint->translate.vec.f.y = joint->translate.vec.f.z = 0.0F;

                joint->rotate.vec.f.x = joint->rotate.vec.f.y = joint->rotate.vec.f.z = 0.0F;

                joint->scale.vec.f.x = joint->scale.vec.f.y = joint->scale.vec.f.z = 1.0F;

                joint->flags = DOBJ_FLAG_NONE;
            }
            func_ovl0_800C87F4(fp->joint[nFTPartsJointTopN]->child, fp->anim_bank, frame_begin);

            if (anim_rate != DObjGetStruct(fighter_gobj)->anim_rate)
            {
                gcSetDObjAnimPlaybackRate(fighter_gobj, anim_rate);
            }
            if (fp->anim_flags.flags.is_use_transn_joint)
            {
                joint = fp->joint[nFTPartsJointTransN];

                transn_parent = joint->parent;
                transn_child = joint->child;
                transn_parent->child = transn_child;
                transn_child->parent = transn_parent;
                transn_child->sib_next = joint;
                joint->sib_prev = transn_child;
                joint->parent = transn_child->parent;
                joint->child = NULL;
            }

            if (fp->is_use_anim_locks)
            {
                if (!(fp->anim_flags.flags.is_use_anim_locks))
                {
                    ftParamSetAnimLocks(fp);
                }
            }
            else if (fp->anim_flags.flags.is_use_anim_locks)
            {
                ftParamClearAnimLocks(fp);
            }
            fp->is_use_anim_locks = fp->anim_flags.flags.is_use_anim_locks;

            if (attributes->translate_scales != NULL)
            {
                if (fp->anim_flags.flags.is_have_translate_scale)
                {
                    fp->is_have_translate_scale = FALSE;
                }
                else fp->is_have_translate_scale = TRUE;
            }
        }
        if (status_struct != NULL)
        {
            if (script_info->offset != 0x80000000)
            {
                // Actually subaction scripts?
                if (fp->anim_flags.flags.is_use_submotion_script)
                {
                    event_file_head = *fp->ft_data->p_file_submotion;

                    event_script_ptr = (void*)((intptr_t)script_info->offset + (intptr_t)event_file_head);
                }
                else
                {
                    event_file_head = *fp->ft_data->p_file_battlemotion;

                    event_script_ptr = (void*)((intptr_t)script_info->offset + (intptr_t)event_file_head);
                }
            }
            else event_script_ptr = NULL;

            fp->motion_event[0][0].p_script = fp->motion_event[1][0].p_script = event_script_ptr;
        }
        else
        {
            if (script_info->offset != 0x80000000)
            {
                event_script_ptr = (void*)script_info->offset;
            }
            else event_script_ptr = NULL;

            fp->motion_event[0][0].p_script = fp->motion_event[1][0].p_script = event_script_ptr;
        }
        anim_frame = DObjGetStruct(fighter_gobj)->anim_rate - frame_begin;

        fp->motion_event[0][0].frame_timer = fp->motion_event[1][0].frame_timer = anim_frame;

        fp->motion_event[0][0].script_index = fp->motion_event[1][0].script_index = 0;

        for (i = 1; i < ARRAY_COUNT(fp->motion_event); i++)
        {
            fp->motion_event[0][i].p_script = fp->motion_event[1][i].p_script = NULL;
        }

        if (frame_begin != 0.0F)
        {
            ftMainPlayAnimDefault(fighter_gobj);
        }
        else
        {
            ftMainPlayAnimNoEffect(fighter_gobj);
            ftMainRunUpdateColAnim(fighter_gobj);
        }
    }
    else for (i = 0; i < ARRAY_COUNT(fp->motion_event); i++)
    {
        fp->motion_event[0][i].p_script = fp->motion_event[1][i].p_script = NULL;
    }
    if (fp->status_info.pl_kind != nFTPlayerKindDemo)
    {
        fp->proc_update = status_struct[status_struct_id].proc_update;
        fp->proc_interrupt = status_struct[status_struct_id].proc_interrupt;
        fp->proc_physics = status_struct[status_struct_id].proc_physics;
        fp->proc_map = status_struct[status_struct_id].proc_map;
        fp->proc_slope = mpCommonUpdateFighterSlopeContour;
        fp->proc_accessory = NULL;
        fp->proc_damage = NULL;
        fp->proc_trap = NULL;
        fp->proc_hit = NULL;
        fp->proc_shield = NULL;
        fp->proc_effect = NULL;
        fp->proc_lagupdate = NULL;
        fp->proc_lagstart = NULL;
        fp->proc_lagend = NULL;
    }
    else if (opening_struct != NULL)
    {
        fp->proc_update = opening_struct[status_struct_id].proc_update;
    }
    else fp->proc_update = NULL;
}
