#include <ft/fighter.h>
#include <gm/battle.h>

extern f32 gmCommonObject_DamageCalcKnockback(s32 percent_damage, s32 recent_damage, s32 hit_damage, s32 knockback_weight, s32 knockback_scale, s32 knockback_base, f32 weight, s32 attack_handicap, s32 defend_handicap);
extern s32 gmCommon_DamageApplyStale(s32 player, s32 damage, s32 attack_id, u16 flags);

// // // // // // // // // // // //
//                               //
//   GLOBAL / STATIC VARIABLES   //
//                               //
// // // // // // // // // // // //

// 0x8018CF80
s32 sFTCommonThrownScriptID;

// // // // // // // // // // // //
//                               //
//        INITIALIZED DATA       //
//                               //
// // // // // // // // // // // //

// 0x801886E0
ftThrowHitDesc dFTCommonThrownNoDamageKnockback = { -1, 0, 361, 0, 0, 20, 0 };

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8014ADB0
void ftCommonThrownReleaseFighterLoseGrip(GObj *fighter_gobj)
{
    ftStruct *this_fp = ftGetStruct(fighter_gobj);
    GObj *interact_gobj;
    ftStruct *interact_fp;
    Vec3f pos;

    if (this_fp->x192_flag_b3)
    {
        interact_gobj = this_fp->catch_gobj;
    }
    else interact_gobj = this_fp->capture_gobj;

    interact_fp = ftGetStruct(interact_gobj);

    if ((this_fp->status_info.status_id >= nFTCommonStatusThrownStart) && (this_fp->status_info.status_id <= nFTCommonStatusThrownEnd))
    {
        pos.x = pos.y = pos.z = 0.0F;

        ftParts_GetDObjWorldPosition(this_fp->joint[4], &pos);

        pos.y -= 300.0F;

        DObjGetStruct(fighter_gobj)->translate.vec.f = pos;
    }
    ftMap_RunCollisionDefault(fighter_gobj, &DObjGetStruct(interact_gobj)->translate.vec.f, &interact_fp->coll_data);

    if ((this_fp->ground_or_air == nMPKineticsGround) && ((this_fp->coll_data.ground_line_id == -1) || (this_fp->coll_data.ground_dist != 0.0F)))
    {
        ftMap_SetAir(this_fp);
    }
}

// 0x8014AECC
void ftCommonThrownDecideFighterLoseGrip(GObj *fighter_gobj, GObj *interact_gobj)
{
    ftStruct *this_fp = ftGetStruct(fighter_gobj);
    ftStruct *interact_fp = ftGetStruct(interact_gobj);

    if (this_fp->x192_flag_b3)
    {
        ftCommonThrownReleaseFighterLoseGrip(fighter_gobj);
    }
    else ftCommonThrownReleaseFighterLoseGrip(interact_gobj);

    interact_fp->capture_gobj = NULL;
    this_fp->catch_gobj = NULL;
}

// 0x8014AF2C
void ftCommonThrownDecideDeadResult(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    GObj *interact_gobj = fp->catch_gobj;

    if (interact_gobj != NULL)
    {
        ftCommonThrownDecideFighterLoseGrip(fighter_gobj, interact_gobj);

        goto next;
    }
    else interact_gobj = fp->capture_gobj;

    if (interact_gobj != NULL)
    {
        ftCommonThrownDecideFighterLoseGrip(interact_gobj, fighter_gobj);

    next:
        ftMap_SetStatusWaitOrFall(fighter_gobj);
        ftMap_SetStatusWaitOrFall(interact_gobj);
    }
}

// 0x8014AF98
void ftCommonThrownProcStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftCommon_ThrownUpdateEnemyInfo(fp, fp->capture_gobj);

    fp->status_vars.common.damage.script_index = sFTCommonThrownScriptID;
}

// 0x8014AFD0
void ftCommonThrownReleaseThrownUpdateStats(GObj *fighter_gobj, s32 lr, s32 script_index, sb32 is_proc_status)
{
    ftStruct *this_fp = ftGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    ftStruct *capture_fp = ftGetStruct(capture_gobj);
    ftThrowHitDesc *ft_throw;
    f32 knockback_final;
    s32 damage;
    f32 knockback_resist;
    f32 knockback_calc;

    knockback_resist = (this_fp->knockback_resist_status < this_fp->knockback_resist_passive) ? this_fp->knockback_resist_passive : this_fp->knockback_resist_status;

    sFTCommonThrownScriptID = script_index;

    if (this_fp->hitstatus != gmHitCollision_HitStatus_Normal)
    {
        ftCollision_SetHitStatusAll(fighter_gobj, gmHitCollision_HitStatus_Normal);
    }
    if (!(this_fp->x192_flag_b3))
    {
        ftCommonThrownReleaseFighterLoseGrip(fighter_gobj);
    }
    ftMap_SetAir(this_fp);

    ft_throw = capture_fp->fighter_throw;

    knockback_calc = gmCommonObject_DamageCalcKnockback(this_fp->percent_damage, ft_throw->damage, ft_throw->damage, ft_throw->knockback_weight, ft_throw->knockback_scale, ft_throw->knockback_base, this_fp->attributes->weight, capture_fp->handicap, this_fp->handicap);

    knockback_final = knockback_calc - knockback_resist;

    if (knockback_calc <= knockback_resist)
    {
        knockback_final = 0.0F;
    }
    damage = gmCommon_DamageApplyStale(capture_fp->player, ft_throw->damage, capture_fp->attack_id, capture_fp->motion_count);

    if (capture_fp->is_shield_catch)
    {
        damage = ((damage * 0.5F) + 0.999F);
    }
    if (ftCommon_GetBestHitStatusAll(fighter_gobj) != gmHitCollision_HitStatus_Normal)
    {
        damage = 0;
    }
    if (is_proc_status != FALSE)
    {
        this_fp->proc_status = ftCommonThrownProcStatus;
    }
    ftCommonDamageInitDamageVars(fighter_gobj, ft_throw->status_id, damage, knockback_final, ft_throw->angle, lr, 1, ft_throw->element, capture_fp->player_number, TRUE, TRUE, TRUE);
    ftCommon_Update1PGameDamageStats(this_fp, capture_fp->player, ftHitlog_ObjectClass_Fighter, capture_fp->ft_kind, capture_fp->stat_flags.halfword, capture_fp->stat_count);

    if (damage != 0)
    {
        ftDamageUpdateCheckDropItem(this_fp, damage);
        ftAttackUpdateMatchStats(capture_fp->player, this_fp->player, damage);
        ftAttackAddStaleQueue(capture_fp->player, this_fp->player, capture_fp->attack_id, capture_fp->motion_count);

        if ((s32) ((damage * 0.75F) + 4.0F) > 0)
        {
            ftMainMakeRumble(this_fp, 0, (s32) ((damage * 0.75F) + 4.0F));
        }
        if ((s32) ((damage * 0.5F) + 2.0F) > 0)
        {
            ftMainMakeRumble(capture_fp, 5, (s32) ((damage * 0.5F) + 2.0F));
        }
    }
    this_fp->capture_gobj = NULL;
}

// 0x8014B2AC
void ftCommonThrownUpdateDamageStats(ftStruct *this_fp)
{
    GObj *capture_gobj = this_fp->capture_gobj;
    ftStruct *capture_fp = ftGetStruct(capture_gobj);
    ftThrowHitDesc *ft_throw = &capture_fp->fighter_throw[1];
    s32 damage = gmCommon_DamageApplyStale(capture_fp->player, ft_throw->damage, capture_fp->attack_id, capture_fp->motion_count);

    ftDamageUpdateCheckDropItem(this_fp, damage);
    ftAttackUpdateMatchStats(capture_fp->player, this_fp->player, damage);
    ftAttackAddStaleQueue(capture_fp->player, this_fp->player, capture_fp->attack_id, capture_fp->motion_count);
}

// 0x8014B330
void ftCommonThrownSetStatusDamageRelease(GObj *fighter_gobj)
{
    ftStruct *this_fp = ftGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    ftStruct *capture_fp = ftGetStruct(capture_gobj);
    ftThrowHitDesc *ft_throw;
    f32 knockback_final;
    s32 lr;
    s32 damage;
    f32 knockback_resist;
    f32 knockback_calc;

    knockback_resist = (this_fp->knockback_resist_status < this_fp->knockback_resist_passive) ? this_fp->knockback_resist_passive : this_fp->knockback_resist_status;

    if (this_fp->hitstatus != gmHitCollision_HitStatus_Normal)
    {
        ftCollision_SetHitStatusAll(fighter_gobj, gmHitCollision_HitStatus_Normal);
    }
    if (!(this_fp->x192_flag_b3))
    {
        ftCommonThrownReleaseFighterLoseGrip(fighter_gobj);
    }
    if (this_fp->ground_or_air == nMPKineticsAir)
    {
        ftMap_SetAir(this_fp);
    }
    ft_throw = &capture_fp->fighter_throw[1];

    knockback_calc = gmCommonObject_DamageCalcKnockback(this_fp->percent_damage, ft_throw->damage, ft_throw->damage, ft_throw->knockback_weight, ft_throw->knockback_scale, ft_throw->knockback_base, this_fp->attributes->weight, capture_fp->handicap, this_fp->handicap);

    knockback_final = knockback_calc - knockback_resist;

    if (knockback_calc <= knockback_resist)
    {
        knockback_final = 0.0F;
    }
    lr = (DObjGetStruct(fighter_gobj)->translate.vec.f.x < DObjGetStruct(capture_gobj)->translate.vec.f.x) ? LR_Right : LR_Left;

    damage = gmCommon_DamageApplyStale(capture_fp->player, ft_throw->damage, capture_fp->attack_id, capture_fp->motion_count);;

    if (capture_fp->is_shield_catch)
    {
        damage = ((damage * 0.5F) + 0.999F);
    }

    if (ftCommon_GetBestHitStatusAll(fighter_gobj) != gmHitCollision_HitStatus_Normal)
    {
        damage = 0;
    }
    ftCommonDamageInitDamageVars(fighter_gobj, ft_throw->status_id, damage, knockback_final, ft_throw->angle, lr, 1, gmHitCollision_Element_Normal, capture_fp->player_number, FALSE, FALSE, TRUE);
    ftCommon_Update1PGameDamageStats(this_fp, capture_fp->player, ftHitlog_ObjectClass_Fighter, capture_fp->ft_kind, capture_fp->stat_flags.halfword, capture_fp->stat_count);

    if (damage != 0)
    {
        ftDamageUpdateCheckDropItem(this_fp, damage);
        ftAttackUpdateMatchStats(capture_fp->player, this_fp->player, damage);
        ftAttackAddStaleQueue(capture_fp->player, this_fp->player, capture_fp->attack_id, capture_fp->motion_count);
    }
    this_fp->capture_gobj = NULL;
}

// 0x8014B5B4
void ftCommonThrownSetStatusNoDamageRelease(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftThrowHitDesc *ft_throw = &dFTCommonThrownNoDamageKnockback;
    f32 knockback_calc;
    f32 knockback_resist;
    f32 knockback_final;

    if (fp->knockback_resist_status < fp->knockback_resist_passive)
    {
        knockback_resist = fp->knockback_resist_passive;
    }
    else knockback_resist = fp->knockback_resist_status;

    DObjGetStruct(fighter_gobj)->translate.vec.f.z = 0.0F;

    knockback_calc = gmCommonObject_DamageCalcKnockback(fp->percent_damage, ft_throw->damage, ft_throw->damage, ft_throw->knockback_weight, ft_throw->knockback_scale, ft_throw->knockback_base, fp->attributes->weight, 9, fp->handicap);

    knockback_final = knockback_calc - knockback_resist;

    if (knockback_calc <= knockback_resist)
    {
        knockback_final = 0.0F;
    }
    ftCommonDamageInitDamageVars(fighter_gobj, ft_throw->status_id, 0, knockback_final, ft_throw->angle, fp->lr, 1, ft_throw->element, 0, TRUE, TRUE, FALSE);
    ftCommon_Update1PGameDamageStats(fp, GMMATCH_PLAYERS_MAX, ftHitlog_ObjectClass_None, 0, 0, 0);
}
