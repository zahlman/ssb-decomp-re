#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//             MACROS            //
//                               //
// // // // // // // // // // // //

#define ftCheckInterruptLanding(fighter_gobj)                           \
(                                                                       \
    (ftCommonSpecialNCheckInterruptCommon(fighter_gobj) != FALSE)   ||  \
    (ftCommonSpecialHiCheckInterruptCommon(fighter_gobj) != FALSE)  ||  \
    (ftCommonSpecialLwCheckInterruptCommon(fighter_gobj) != FALSE)  ||  \
    (ftCommonCatchCheckInterruptCommon(fighter_gobj) != FALSE)      ||  \
    (ftCommonAttackS4CheckInterruptCommon(fighter_gobj) != FALSE)   ||  \
    (ftCommonAttackHi4CheckInterruptCommon(fighter_gobj) != FALSE)  ||  \
    (ftCommonAttackLw4CheckInterruptCommon(fighter_gobj) != FALSE)  ||  \
    (ftCommonAttackS3CheckInterruptCommon(fighter_gobj) != FALSE)   ||  \
    (ftCommonAttackHi3CheckInterruptCommon(fighter_gobj) != FALSE)  ||  \
    (ftCommonAttackLw3CheckInterruptCommon(fighter_gobj) != FALSE)  ||  \
    (ftCommonAttack1CheckInterruptCommon(fighter_gobj) != FALSE)    ||  \
    (ftCommonGuardOnCheckInterruptCommon(fighter_gobj) != FALSE)    ||  \
    (ftCommonAppealCheckInterruptCommon(fighter_gobj) != FALSE)     ||  \
    (ftCommon_KneeBend_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (ftCommon_Dash_CheckInterruptCommon(fighter_gobj) != FALSE) ||      \
    (ftCommon_Pass_CheckInterruptCommon(fighter_gobj) != FALSE) ||      \
    (ftCommon_DokanStart_CheckInterruptCommon(fighter_gobj) != FALSE)   \
)

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80142B70
void ftCommonLandingProcInterrupt(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame < FTCOMMON_LANDING_INTERRUPT_BEGIN)
    {
        return;
    }
    else if ((fp->status_vars.common.landing.is_allow_interrupt != FALSE) && !(ftCheckInterruptLanding(fighter_gobj)))
    {
        if ((fighter_gobj->anim_frame >= FTCOMMON_LANDING_INTERRUPT_BEGIN) && (fighter_gobj->anim_frame < (FTCOMMON_LANDING_INTERRUPT_BEGIN + DObjGetStruct(fighter_gobj)->dobj_f1)))
        {
            if (ftCommonSquatWaitCheckInterruptLanding(fighter_gobj) != FALSE) return;
        }
        else if (ftCommonSquatCheckInterruptCommon(fighter_gobj) != FALSE) return;

        if (ftCommon_Turn_CheckInterruptCommon(fighter_gobj) == FALSE)
        {
            ftCommon_Walk_CheckInterruptCommon(fighter_gobj);
        }
    }
}

// 0x80142D44
void ftCommonLandingSetStatusParam(GObj *fighter_gobj, s32 status_id, sb32 is_allow_interrupt, f32 anim_speed)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftMap_SetGround(fp);
    ftMainSetFighterStatus(fighter_gobj, status_id, 0.0F, anim_speed, FTSTATUPDATE_NONE_PRESERVE);

    fp->status_vars.common.landing.is_allow_interrupt = is_allow_interrupt;
}

// 0x80142D9C
void ftCommonLandingSetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if ((fp->is_fast_fall) && (fp->phys_info.vel_air.y <= -fp->attributes->fast_fall_speed))
    {
        ftCommonLandingSetStatusParam(fighter_gobj, ftStatus_Common_LandingHeavy, TRUE, FTCOMMON_LANDING_HEAVY_ANIM_SPEED);
    }
    else ftCommonLandingSetStatusParam(fighter_gobj, ftStatus_Common_LandingLight, TRUE, FTCOMMON_LANDING_LIGHT_ANIM_SPEED);
}

// 0x80142E10
void ftCommonLandingAirNullSetStatus(GObj *fighter_gobj, f32 anim_speed)
{
    ftCommonLandingSetStatusParam(fighter_gobj, ftStatus_Common_LandingAirNull, FALSE, anim_speed);
}

// 0x80142E3C
void ftCommonLandingFallSpecialSetStatus(GObj *fighter_gobj, sb32 is_allow_interrupt, f32 anim_speed)
{
    ftCommonLandingSetStatusParam(fighter_gobj, ftStatus_Common_LandingFallSpecial, is_allow_interrupt, anim_speed);
}
