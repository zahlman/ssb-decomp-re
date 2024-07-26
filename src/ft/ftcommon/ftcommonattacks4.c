#include <ft/fighter.h>
#include <it/item.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t lFTNessAttackS4Reflector;                 // 0x00001114

extern void ftCommon_ProcResumeGFX(GObj*);
extern void ftCommon_ProcPauseGFX(GObj*);
extern f32 ftCommon_GetStickAngleRadians(ftStruct*);

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8014FE40
void ftCommonAttackS4ProcUpdate(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    Vec3f offset;

    switch (fp->ft_kind)
    {
    case nFTKindPikachu:
    case nFTKindPolyPikachu:
        if ((fp->command_vars.flags.flag1 != 0) || (fp->command_vars.flags.flag2 != 0))
        {
            fp->status_vars.common.attack4.gfx_id += mtTrigGetRandomIntRange((FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_ID_MAX - 1)) + 1;

            if (fp->status_vars.common.attack4.gfx_id >= FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_ID_MAX)
            {
                fp->status_vars.common.attack4.gfx_id -= FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_ID_MAX;
            }
            if (fp->command_vars.flags.flag1 != 0)
            {
                fp->command_vars.flags.flag1 = 0;

                offset.x = -FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_X;
                offset.z = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_Z;
                offset.y = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_Y;
            }
            if (fp->command_vars.flags.flag2 != 0)
            {
                fp->command_vars.flags.flag2 = 0;

                offset.x = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_X;
                offset.z = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_Z;
                offset.y = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_Y;

            }
            ftParts_GetDObjWorldPosition(fp->joint[11], &offset);
            func_ovl2_800EE018(fp->joint[ftParts_Joint_TopN], &offset);

            if (efManagerPikachuThunderShockMakeEffect(fighter_gobj, &offset, fp->status_vars.common.attack4.gfx_id) != NULL)
            {
                fp->is_attach_effect = TRUE;
            }
        }
        // Fallthrough, should break here for efficiency
    case nFTKindNess:
    case nFTKindPolyNess:
        if ((fp->command_vars.flags.flag1 != 0) && !(fp->is_reflect))
        {
            fp->is_reflect = TRUE;
        }
        if ((fp->command_vars.flags.flag1 == 0) && (fp->is_reflect))
        {
            fp->is_reflect = FALSE;
        }
        break;
    }
    ftStatusWaitOnAnimEnd(fighter_gobj);
}

// 0x8014FFE0
void ftCommonAttackS4SetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    f32 stick_angle;
    s32 status_id;

    if (fp->ft_data->battlemotion->script_info[nFTCommonMotionAttackS4HiS].anim_id != 0)
    {
        stick_angle = ftCommon_GetStickAngleRadians(fp);

        status_id = (stick_angle > FTCOMMON_ATTACKS4_5ANGLE_HI_MIN)  ? nFTCommonStatusAttackS4Hi  :
                    (stick_angle > FTCOMMON_ATTACKS4_5ANGLE_HIS_MIN) ? nFTCommonStatusAttackS4HiS :
                    (stick_angle < FTCOMMON_ATTACKS4_5ANGLE_LW_MIN)  ? nFTCommonStatusAttackS4Lw  :
                    (stick_angle < FTCOMMON_ATTACKS4_5ANGLE_LWS_MIN) ? nFTCommonStatusAttackS4LwS :
                                                                       nFTCommonStatusAttackS4;
    }
    else if (fp->ft_data->battlemotion->script_info[nFTCommonMotionAttackS4Hi].anim_id != 0)
    {
        stick_angle = ftCommon_GetStickAngleRadians(fp);

        status_id = (stick_angle > FTCOMMON_ATTACKS4_3ANGLE_HI_MIN)  ? nFTCommonStatusAttackS4Hi  :
                    (stick_angle < FTCOMMON_ATTACKS4_3ANGLE_LW_MIN)  ? nFTCommonStatusAttackS4Lw  :
                                                                       nFTCommonStatusAttackS4;
    }
    else status_id = nFTCommonStatusAttackS4;

    switch (fp->ft_kind)
    {
    case nFTKindPikachu:
    case nFTKindPolyPikachu:
        fp->command_vars.flags.flag2 = 0;
        fp->command_vars.flags.flag1 = 0;
        break;

    case nFTKindNess:
    case nFTKindPolyNess:
        fp->command_vars.flags.flag1 = 0;
        break;
    }
    ftMainSetFighterStatus(fighter_gobj, status_id, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftMainUpdateAnimCheckInterrupt(fighter_gobj);

    switch (fp->ft_kind)
    {
    case nFTKindPikachu:
    case nFTKindPolyPikachu:
        fp->status_vars.common.attack4.gfx_id = 0;

        fp->proc_lagstart = ftCommon_ProcPauseGFX;
        fp->proc_lagend = ftCommon_ProcResumeGFX;
        break;

    case nFTKindNess:
    case nFTKindPolyNess:
        fp->special_hit = (ftSpecialHit*) ((uintptr_t)gFTDataNessBattleMotion + (intptr_t)&lFTNessAttackS4Reflector); // Linker thing
        break;
    }
}

// 0x801501E0
sb32 ftCommonAttackS4CheckInterruptDash(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftAttributes *attributes = fp->attributes;

    if (((fp->input.pl.stick_range.x * fp->lr) >= FTCOMMON_ATTACKS4_STICK_RANGE_MIN) && (fp->input.pl.button_tap & fp->input.button_mask_a))
    {
        GObj *item_gobj = fp->item_hold;

        if (item_gobj != NULL)
        {
            itStruct *ip = itGetStruct(item_gobj);

            if ((fp->input.pl.button_hold & fp->input.button_mask_z) || ((ip->type == nITTypeThrow) || (ip->type == nITTypeShoot) && (itMainCheckShootNoAmmo(item_gobj) != FALSE)))
            {
                ftCommonItemThrowSetStatus(fighter_gobj, nFTCommonStatusLightThrowF4);

                return TRUE;
            }
            switch (ip->type)
            {
            case nITTypeSwing:
                ftCommonItemSwingSetStatus(fighter_gobj, ftItemSwing_Type_Attack4);
                return TRUE;

            case nITTypeShoot:
                ftCommonItemShootSetStatus(fighter_gobj);
                return TRUE;
            }
        }
        if (attributes->is_have_attacks4)
        {
            ftCommonAttackS4SetStatus(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}

// 0x8015030C
sb32 ftCommonAttackS4CheckInterruptTurn(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftAttributes *attributes = fp->attributes;

    if (((fp->input.pl.stick_range.x * fp->status_vars.common.attack4.lr) >= FTCOMMON_ATTACKS4_STICK_RANGE_MIN) && (fp->input.pl.button_tap & fp->input.button_mask_a))
    {
        GObj *item_gobj = fp->item_hold;

        if (item_gobj != NULL)
        {
            itStruct *ip = itGetStruct(item_gobj);

            if ((fp->input.pl.button_hold & fp->input.button_mask_z) || ((ip->type == nITTypeThrow) || (ip->type == nITTypeShoot) && (itMainCheckShootNoAmmo(item_gobj) != FALSE)))
            {
                ftCommonItemThrowSetStatus(fighter_gobj, ((fp->input.pl.stick_range.x * fp->lr) >= 0) ? nFTCommonStatusLightThrowF4 : nFTCommonStatusLightThrowB4);

                return TRUE;
            }
            switch (ip->type)
            {
            case nITTypeSwing:
                ftCommon_StickInputSetLR(fp);
                ftCommonItemSwingSetStatus(fighter_gobj, ftItemSwing_Type_Attack4);
                return TRUE;

            case nITTypeShoot:
                ftCommon_StickInputSetLR(fp);
                ftCommonItemShootSetStatus(fighter_gobj);
                return TRUE;
            }
        }
        if (attributes->is_have_attacks4)
        {
            ftCommon_StickInputSetLR(fp);
            ftCommonAttackS4SetStatus(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}

// 0x80150470
sb32 ftCommonAttackS4CheckInterruptCommon(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftAttributes *attributes = fp->attributes;

    if ((ABS(fp->input.pl.stick_range.x) >= FTCOMMON_ATTACKS4_STICK_RANGE_MIN) && (fp->tap_stick_x < FTCOMMON_ATTACKS4_BUFFER_FRAMES_MAX) && (fp->input.pl.button_tap & fp->input.button_mask_a))
    {
        GObj *item_gobj = fp->item_hold;

        if (item_gobj != NULL)
        {
            itStruct *ip = itGetStruct(item_gobj);

            if ((fp->input.pl.button_hold & fp->input.button_mask_z) || ((ip->type == nITTypeThrow) || (ip->type == nITTypeShoot) && (itMainCheckShootNoAmmo(item_gobj) != FALSE)))
            {
                ftCommonItemThrowSetStatus(fighter_gobj, ((fp->input.pl.stick_range.x * fp->lr) >= 0) ? nFTCommonStatusLightThrowF4 : nFTCommonStatusLightThrowB4);

                return TRUE;
            }
            switch (ip->type)
            {
            case nITTypeSwing:
                ftCommon_StickInputSetLR(fp);
                ftCommonItemSwingSetStatus(fighter_gobj, ftItemSwing_Type_Attack4);
                return TRUE;

            case nITTypeShoot:
                ftCommon_StickInputSetLR(fp);
                ftCommonItemShootSetStatus(fighter_gobj);
                return TRUE;
            }
        }
        if (attributes->is_have_attacks4)
        {
            ftCommon_StickInputSetLR(fp);
            ftCommonAttackS4SetStatus(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}
