#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern intptr_t lFTKirbyAttack100Effect;            // 0x00001220

// // // // // // // // // // // //
//                               //
//             MACROS            //
//                               //
// // // // // // // // // // // //

#define ftCommonAttack100CheckFighterKind(fp) \
(                                             \
    ((fp)->ft_kind == nFTKindFox)        ||  \
    ((fp)->ft_kind == nFTKindPolyFox)    ||  \
    ((fp)->ft_kind == nFTKindLink)       ||  \
    ((fp)->ft_kind == nFTKindPolyLink)   ||  \
    ((fp)->ft_kind == nFTKindKirby)      ||  \
    ((fp)->ft_kind == nFTKindPolyKirby)  ||  \
    ((fp)->ft_kind == nFTKindPurin)      ||  \
    ((fp)->ft_kind == nFTKindPolyPurin)  ||  \
    ((fp)->ft_kind == nFTKindCaptain)    ||  \
    ((fp)->ft_kind == nFTKindPolyCaptain)    \
)

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8014F0D0
void ftCommonAttack100StartProcUpdate(GObj *fighter_gobj)
{
    ftStatusSetOnAnimEnd(fighter_gobj, ftCommonAttack100LoopSetStatus);
}

// 0x8014F0F4
void ftCommonAttack100StartSetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    s32 status_id;

    if (ftCommonGetCheckInterruptCommon(fighter_gobj) == FALSE)
    {
        switch (fp->ft_kind)
        {
        case nFTKindFox:
        case nFTKindPolyFox:
            status_id = nFTFoxStatusAttack100Start;
            break;

        case nFTKindLink:
        case nFTKindPolyLink:
            status_id = nFTLinkStatusAttack100Start;
            break;

        case nFTKindKirby:
        case nFTKindPolyKirby:
            status_id = nFTKirbyStatusAttack100Start;
            break;

        case nFTKindPurin:
        case nFTKindPolyPurin:
            status_id = nFTPurinStatusAttack100Start;
            break;

        case nFTKindCaptain:
        case nFTKindPolyCaptain:
            status_id = nFTCaptainStatusAttack100Start;
            break;
        }
        ftMainSetFighterStatus(fighter_gobj, status_id, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
        ftMainUpdateAnimCheckInterrupt(fighter_gobj);

        fp->status_vars.common.attack100.is_anim_end = FALSE;
        fp->status_vars.common.attack100.is_goto_loop = FALSE;

        fp->command_vars.flags.flag1 = 0;
        fp->command_vars.flags.flag2 = 0;
    }
}

// 0x8014F1BC
void ftCommonAttack100LoopKirbyUpdateEffect(ftStruct *fp)
{
    Vec3f pos;

    if (fp->ft_kind == nFTKindKirby)
    {
        if (fp->command_vars.flags.flag2 != 0)
        {
            ftKirbyAttack100Effect *effect = (ftKirbyAttack100Effect*) ((uintptr_t)gFTDataKirbyBattleMotion + (intptr_t)&lFTKirbyAttack100Effect); // Linker thing

            pos.x = effect[fp->command_vars.flags.flag2 - 1].offset.x;
            pos.y = effect[fp->command_vars.flags.flag2 - 1].offset.y;
            pos.z = effect[fp->command_vars.flags.flag2 - 1].offset.z;

            ftParts_GetDObjWorldPosition(fp->joint[ftParts_Joint_TopN], &pos);

            efManagerKirbyVulcanJabMakeEffect(&pos, fp->lr, effect[fp->command_vars.flags.flag2 - 1].rotate, effect[fp->command_vars.flags.flag2 - 1].vel, effect[fp->command_vars.flags.flag2 - 1].add);

            fp->command_vars.flags.flag2 = 0;
        }
    }
}

// 0x8014F2A8
void ftCommonAttack100LoopProcUpdate(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if ((fighter_gobj->anim_frame >= 0.0F) && (fighter_gobj->anim_frame < DObjGetStruct(fighter_gobj)->dobj_f1))
    {
        fp->status_vars.common.attack100.is_anim_end = TRUE;

        ftCommon_MotionCountIncSetAttackID(fp, nFTMotionAttackIDAttack100);
        ftCommon_StatUpdateCountIncSetFlags(fp, fp->stat_flags.halfword);
        ftCommon_Update1PGameAttackStats(fp, 0);
    }
    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->command_vars.flags.flag1 = 0;

        if ((fp->status_vars.common.attack100.is_anim_end != FALSE) && (fp->status_vars.common.attack100.is_goto_loop == FALSE))
        {
            ftCommonAttack100EndSetStatus(fighter_gobj);

            return;
        }
        else if (ftCommonGetCheckInterruptCommon(fighter_gobj) == FALSE)
        {
            fp->status_vars.common.attack100.is_goto_loop = FALSE;
        }
        else return;
    }
    ftCommonAttack100LoopKirbyUpdateEffect(fp);
}

// 0x8014F388
void ftCommonAttack100LoopProcInterrupt(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if ((fp->input.pl.button_tap & fp->input.button_mask_a) || (fp->input.pl.button_tap_prev & fp->input.button_mask_a))
    {
        fp->status_vars.common.attack100.is_goto_loop = TRUE;
    }
}

// 0x8014F3C0
void ftCommonAttack100LoopSetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    s32 status_id;

    switch (fp->ft_kind)
    {
    case nFTKindFox:
    case nFTKindPolyFox:
        status_id = nFTFoxStatusAttack100Loop;
        break;

    case nFTKindLink:
    case nFTKindPolyLink:
        status_id = nFTLinkStatusAttack100Loop;
        break;

    case nFTKindKirby:
    case nFTKindPolyKirby:
        status_id = nFTKirbyStatusAttack100Loop;
        break;

    case nFTKindPurin:
    case nFTKindPolyPurin:
        status_id = nFTPurinStatusAttack100Loop;
        break;

    case nFTKindCaptain:
    case nFTKindPolyCaptain:
        status_id = nFTCaptainStatusAttack100Loop;
        break;
    }
    ftMainSetFighterStatus(fighter_gobj, status_id, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftCommonAttack100LoopKirbyUpdateEffect(fp);
}

// 0x8014F45C
void ftCommonAttack100EndSetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    s32 status_id;

    switch (fp->ft_kind)
    {
    case nFTKindFox:
    case nFTKindPolyFox:
        status_id = nFTFoxStatusAttack100End;
        break;

    case nFTKindLink:
    case nFTKindPolyLink:
        status_id = nFTLinkStatusAttack100End;
        break;

    case nFTKindKirby:
    case nFTKindPolyKirby:
        status_id = nFTKirbyStatusAttack100End;
        break;

    case nFTKindPurin:
    case nFTKindPolyPurin:
        status_id = nFTPurinStatusAttack100End;
        break;

    case nFTKindCaptain:
    case nFTKindPolyCaptain:
        status_id = nFTCaptainStatusAttack100End;
        break;
    }
    ftMainSetFighterStatus(fighter_gobj, status_id, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
}

// 0x8014F4EC
sb32 ftCommonAttack100StartCheckInterruptCommon(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    s32 status_id;
    s32 inputs_req;

    if(!(ftCommonAttack100CheckFighterKind(fp)))
    {
        return FALSE;
    }
    if ((fp->input.pl.button_tap & fp->input.button_mask_a) || (fp->input.pl.button_tap_prev & fp->input.button_mask_a))
    {
        fp->attack1_input_count++;

        switch (fp->ft_kind)
        {
        case nFTKindFox:
        case nFTKindPolyFox:
            inputs_req = 4;
            status_id = nFTCommonStatusAttack12;
            break;

        case nFTKindLink:
        case nFTKindPolyLink:
            inputs_req = 5;
            status_id = nFTCommonStatusAttack12;
            break;

        case nFTKindKirby:
        case nFTKindPolyKirby:
            inputs_req = 4;
            status_id = nFTCommonStatusAttack12;
            break;

        case nFTKindPurin:
        case nFTKindPolyPurin:
            inputs_req = 4;
            status_id = nFTCommonStatusAttack12;
            break;

        case nFTKindCaptain:
        case nFTKindPolyCaptain:
            inputs_req = 6;
            status_id = nFTCaptainStatusAttack13;
            break;
        }
        if (fp->attack1_input_count >= inputs_req)
        {
            if ((status_id == fp->status_info.status_id) && (fp->command_vars.flags.flag1 != 0))
            {
                ftCommonAttack100StartSetStatus(fighter_gobj);

                return TRUE;
            }
            else fp->is_goto_attack100 = TRUE;
        }
    }
    return FALSE;
}
