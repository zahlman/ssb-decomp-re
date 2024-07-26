#include <ft/fighter.h>
#include <it/item.h>

// // // // // // // // // // // //
//                               //
//             MACROS            //
//                               //
// // // // // // // // // // // //

#define ftCommonAttack13CheckFighterKind(fp)  \
(                                             \
    ((fp)->ft_kind == nFTKindMario)      ||  \
    ((fp)->ft_kind == nFTKindMetalMario) ||  \
    ((fp)->ft_kind == nFTKindPolyMario)  ||  \
    ((fp)->ft_kind == nFTKindLuigi)      ||  \
    ((fp)->ft_kind == nFTKindPolyLuigi)  ||  \
    ((fp)->ft_kind == nFTKindCaptain)    ||  \
    ((fp)->ft_kind == nFTKindPolyCaptain)||  \
    ((fp)->ft_kind == nFTKindLink)       ||  \
    ((fp)->ft_kind == nFTKindPolyLink)   ||  \
    ((fp)->ft_kind == nFTKindNess)       ||  \
    ((fp)->ft_kind == nFTKindPolyNess)       \
)

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8014E7B0
void ftCommonAttack11ProcUpdate(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (fp->status_vars.common.attack1.is_goto_followup != FALSE))
    {
        if ((fp->ft_kind == nFTKindPikachu) || (fp->ft_kind == nFTKindPolyPikachu))
        {
            ftCommonAttack11SetStatus(fighter_gobj);
        }
        else ftCommonAttack12SetStatus(fighter_gobj);
    }
    else ftStatusWaitOnAnimEnd(fighter_gobj);
}

// 0x8014E824
void ftCommonAttack12ProcUpdate(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if ((fp->ft_kind != nFTKindCaptain) && (fp->ft_kind != nFTKindPolyCaptain) && (fp->command_vars.flags.flag1 != 0) && (fp->is_goto_attack100))
    {
        ftCommonAttack100StartSetStatus(fighter_gobj);
    }
    else if ((fp->command_vars.flags.flag1 != 0) && (fp->status_vars.common.attack1.is_goto_followup != FALSE))
    {
        ftCommonAttack13SetStatus(fighter_gobj);
    }
    else ftStatusWaitOnAnimEnd(fighter_gobj);
}

// 0x8014E8B4
void ftCommonAttack13ProcUpdate(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (((fp->ft_kind == nFTKindCaptain) || (fp->ft_kind == nFTKindPolyCaptain)) && (fp->command_vars.flags.flag1 != 0) && (fp->is_goto_attack100))
    {
        ftCommonAttack100StartSetStatus(fighter_gobj);
    }
    else ftStatusWaitOnAnimEnd(fighter_gobj);
}

// 0x8014E91C
void ftCommonAttack11ProcInterrupt(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (fp->status_vars.common.attack1.interrupt_catch_timer < 2)
    {
        fp->status_vars.common.attack1.interrupt_catch_timer++;

        if (ftCommonCatchCheckInterruptAttack11(fighter_gobj) != FALSE)
        {
            return;
        }
    }
    if (ftCommonAttack100StartCheckInterruptCommon(fighter_gobj) == FALSE)
    {
        if ((fp->ft_kind == nFTKindPikachu) || (fp->ft_kind == nFTKindPolyPikachu))
        {
            if (ftCommonAttack11CheckGoto(fighter_gobj) != FALSE)
            {
                return;
            }
        }
        else ftCommonAttack12CheckGoto(fighter_gobj);
    }
}

// 0x8014E9B4
void ftCommonAttack12ProcInterrupt(GObj *fighter_gobj)
{
    if (ftCommonAttack13CheckGoto(fighter_gobj) == FALSE)
    {
        ftCommonAttack100StartCheckInterruptCommon(fighter_gobj);
    }
}

// 0x8014E9E4
void ftCommonAttack13ProcInterrupt(GObj *fighter_gobj)
{
    ftCommonAttack100StartCheckInterruptCommon(fighter_gobj);
}

// 0x8014EA04
void ftCommonAttack11ProcStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftCommon_MotionCountIncSetAttackID(fp, nFTMotionAttackIDAttack11);
    ftCommon_StatUpdateCountIncSetFlags(fp, fp->stat_flags.halfword);
    ftCommon_Update1PGameAttackStats(fp, 0);
}

// 0x8014EA44
void ftCommonAttack11SetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftAttributes *attributes = fp->attributes;

    if (ftCommonGetCheckInterruptCommon(fighter_gobj) == FALSE)
    {
        fp->proc_status = ftCommonAttack11ProcStatus;

        ftMainSetFighterStatus(fighter_gobj, nFTCommonStatusAttack11, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
        ftMainUpdateAnimCheckInterrupt(fighter_gobj);

        fp->command_vars.flags.flag1 = 0;

        fp->status_vars.common.attack1.is_goto_followup = FALSE;
        fp->status_vars.common.attack1.interrupt_catch_timer = 0;

        fp->attack1_input_count = 0;
        fp->attack1_status_id = fp->status_info.status_id;
        fp->is_goto_attack100 = FALSE;
        fp->attack1_followup_frames = attributes->attack1_followup_frames;
    }
}

// 0x8014EAD8
void ftCommonAttack12SetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (ftCommonGetCheckInterruptCommon(fighter_gobj) == FALSE)
    {
        ftMainSetFighterStatus(fighter_gobj, nFTCommonStatusAttack12, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
        ftMainUpdateAnimCheckInterrupt(fighter_gobj);

        fp->command_vars.flags.flag1 = 0;

        fp->status_vars.common.attack1.is_goto_followup = FALSE;

        fp->attack1_status_id = fp->status_info.status_id;

        switch (fp->ft_kind)
        {
        case nFTKindMario:
        case nFTKindMetalMario:
        case nFTKindPolyMario:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;

        case nFTKindLuigi:
        case nFTKindPolyLuigi:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;

        case nFTKindCaptain:
        case nFTKindPolyCaptain:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;

        case nFTKindLink:
        case nFTKindPolyLink:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;

        case nFTKindNess:
        case nFTKindPolyNess:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;
        }
    }
}

// 0x8014EBB4
void ftCommonAttack13SetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    s32 status_id;

    if (ftCommonGetCheckInterruptCommon(fighter_gobj) == FALSE)
    {
        switch (fp->ft_kind)
        {
        case nFTKindMario:
        case nFTKindMetalMario:
        case nFTKindPolyMario:
            status_id = nFTMarioStatusAttack13;
            break;

        case nFTKindLuigi:
        case nFTKindPolyLuigi:
            status_id = nFTMarioStatusAttack13;
            break;

        case nFTKindCaptain:
        case nFTKindPolyCaptain:
            status_id = nFTCaptainStatusAttack13;
            break;

        case nFTKindLink:
        case nFTKindPolyLink:
            status_id = nFTLinkStatusAttack13;
            break;

        case nFTKindNess:
        case nFTKindPolyNess:
            status_id = nFTNessStatusAttack13;
            break;
        }
        ftMainSetFighterStatus(fighter_gobj, status_id, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
        ftMainUpdateAnimCheckInterrupt(fighter_gobj);

        fp->command_vars.flags.flag1 = 0;

        fp->status_vars.common.attack1.is_goto_followup = FALSE;

        fp->attack1_status_id = fp->status_info.status_id;
    }
}

// 0x8014EC78
sb32 ftCommonAttack1CheckInterruptCommon(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftAttributes *attributes = fp->attributes;

    if (fp->input.pl.button_tap & fp->input.button_mask_a)
    {
        if (fp->item_hold != NULL)
        {
            if (itGetStruct(fp->item_hold)->type == nITTypeThrow)
            {
                ftCommonItemThrowSetStatus(fighter_gobj, nFTCommonStatusLightThrowF);

                return TRUE;
            }
            if (fp->input.pl.button_hold & fp->input.button_mask_z)
            {
                ftCommonItemThrowSetStatus(fighter_gobj, nFTCommonStatusLightThrowDrop);

                return TRUE;
            }
            switch (itGetStruct(fp->item_hold)->type)
            {
            case nITTypeSwing:
                ftCommonItemSwingSetStatus(fighter_gobj, ftItemSwing_Type_Attack1);
                return TRUE;

            case nITTypeShoot:
                ftCommonItemShootSetStatus(fighter_gobj);
                return TRUE;
            }
        }
        if (fp->attack1_followup_frames != 0.0F)
        {
            switch (fp->attack1_status_id)
            {
            case nFTCommonStatusAttack11:
                if ((fp->ft_kind == nFTKindPikachu) || (fp->ft_kind == nFTKindPolyPikachu))
                {
                    if (attributes->is_have_attack11)
                    {
                        ftCommonAttack11SetStatus(fighter_gobj);

                        fp->attack1_input_count++;

                        return TRUE;
                    }
                    break;
                }
                else if (attributes->is_have_attack12)
                {
                    ftCommonAttack12SetStatus(fighter_gobj);

                    fp->attack1_input_count++;

                    return TRUE;
                }
                break;

            case nFTCommonStatusAttack12:
                if(ftCommonAttack13CheckFighterKind(fp))
                {
                    ftCommonAttack13SetStatus(fighter_gobj);

                    return TRUE;
                }
                break;
            }
        }
        else if (attributes->is_have_attack11)
        {
            ftCommonAttack11SetStatus(fighter_gobj);

            return TRUE;
        }
    }
    if (fp->attack1_followup_frames != 0.0F)
    {
        fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->dobj_f1;
    }
    return FALSE;
}

// 0x8014EEC0
sb32 ftCommonAttack11CheckGoto(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftAttributes *attributes = fp->attributes;

    if (fp->attack1_followup_frames != 0.0F)
    {
        fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->dobj_f1;

        if ((fp->input.pl.button_tap & fp->input.button_mask_a) && (attributes->is_have_attack11))
        {
            if (fp->command_vars.flags.flag1 != 0)
            {
                ftCommonAttack11SetStatus(fighter_gobj);

                return TRUE;
            }
            fp->status_vars.common.attack1.is_goto_followup = TRUE;
        }
    }
    return FALSE;
}

// 0x8014EF50
sb32 ftCommonAttack12CheckGoto(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftAttributes *attributes = fp->attributes;

    if (fp->attack1_followup_frames != 0.0F)
    {
        fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->dobj_f1;

        if ((fp->input.pl.button_tap & fp->input.button_mask_a) && (attributes->is_have_attack12))
        {
            if (fp->command_vars.flags.flag1 != 0)
            {
                ftCommonAttack12SetStatus(fighter_gobj);

                return TRUE;
            }
            fp->status_vars.common.attack1.is_goto_followup = TRUE;
        }
    }
    return FALSE;
}

// 0x8014EFE0
sb32 ftCommonAttack13CheckGoto(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if(!(ftCommonAttack13CheckFighterKind(fp)))
    {
        return FALSE;
    }
    else
    {
        if (fp->attack1_followup_frames != 0.0F)
        {
            fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->dobj_f1;

            if (fp->input.pl.button_tap & fp->input.button_mask_a)
            {
                if (fp->command_vars.flags.flag1 != 0)
                {
                    ftCommonAttack13SetStatus(fighter_gobj);

                    return TRUE;
                }
                fp->status_vars.common.attack1.is_goto_followup = TRUE;
            }
        }
    }
    return FALSE;
}
