#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8014E6A0
void ftCommonAppealProcInterrupt(GObj *fighter_gobj)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);

    if ((fp->motion_vars.flags.flag1 != 0) && (ftCommonCatchCheckInterruptCommon(fighter_gobj) == FALSE))
    {
        ftCommonGuardOnCheckInterruptCommon(fighter_gobj);
    }
}

// 0x8014E6E0
void ftCommonAppealSetStatus(GObj *fighter_gobj)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);

    if ((fp->fkind == nFTKindKirby) || (fp->fkind == nFTKindNKirby))
    {
        if ((fp->fighter_vars.kirby.copy_id != nFTKindKirby) && (fp->fighter_vars.kirby.is_ignore_losecopy == FALSE))
        {
            ftKirbySpecialNLoseCopy(fighter_gobj);
        }
    }
    ftMainSetFighterStatus(fighter_gobj, nFTCommonStatusAppeal, 0.0F, 1.0F, FTSTATUS_PRESERVE_NONE);

    fp->motion_vars.flags.flag1 = 0;
}

// 0x8014E764
sb32 ftCommonAppealCheckInterruptCommon(GObj *fighter_gobj)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);

    if (fp->input.pl.button_tap & fp->input.button_mask_l)
    {
        ftCommonAppealSetStatus(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}
