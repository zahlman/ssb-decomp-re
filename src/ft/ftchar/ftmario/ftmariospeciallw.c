#include <ft/fighter.h>
#include <ef/effect.h>

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x801564F0
void ftMarioSpecialLwProcUpdate(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag3 != 0)
    {
        fp->status_vars.mario.speciallw.dust_effect_int--;

        if (fp->status_vars.mario.speciallw.dust_effect_int == 4)
        {
            ftParamMakeEffect(fighter_gobj, nEFKindDustLight, nFTPartsJointTopN, NULL, NULL, -fp->lr, FALSE, FALSE); // Spawn GFX
        }
        else if (fp->status_vars.mario.speciallw.dust_effect_int == 0)
        {
            ftParamMakeEffect(fighter_gobj, nEFKindDustLight, nFTPartsJointTopN, NULL, NULL, fp->lr, FALSE, FALSE); // Spawn GFX 

            fp->status_vars.mario.speciallw.dust_effect_int = 8;
        }
    }
    ftStatusWaitOnAnimEnd(fighter_gobj);
}

// 0x801565A8
void ftMarioSpecialAirLwProcUpdate(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag2 != 0)
    {
        fp->command_vars.flags.flag2 = 0;
        fp->fighter_vars.mario.is_expend_tornado = TRUE;
    }
    ftStatusFallOnAnimEnd(fighter_gobj);
}

// 0x801565E4
f32 ftMarioSpecialLwUpdateFriction(ftStruct *fp, f32 vel)
{
    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->status_vars.mario.speciallw.friction -= 2.0F;

        vel += fp->status_vars.mario.speciallw.friction;

        if (vel < 0.0F)
        {
            vel = 0.0F;
        }
    }
    return vel;
}

// 0x80156630
void ftMarioSpecialLwProcPhysics(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftPhysics_ApplyClampGroundVelStickRange(fp, 0, FTMARIO_TORNADO_VEL_X_GROUND, ftMarioSpecialLwUpdateFriction(fp, FTMARIO_TORNADO_VEL_X_CLAMP));
    ftPhysics_SetGroundVelTransferAir(fighter_gobj);

    if ((fp->command_vars.flags.flag3 != 0) && (fp->input.pl.button_tap & fp->input.button_mask_b))
    {
        fp->phys_info.vel_air.y += FTMARIO_TORNADO_VEL_Y_TAP;

        ftMarioSpecialLwSwitchStatusAir(fighter_gobj);
    }
}

// 0x801566C4
void ftMarioSpecialAirLwProcPhysics(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    ftAttributes *attributes = fp->attributes;

    if ((fp->fighter_vars.mario.is_expend_tornado == FALSE) && (fp->command_vars.flags.flag3 != 0) && (fp->input.pl.button_tap & fp->input.button_mask_b))
    {
        ftPhysics_AddClampAirVelY(fp, FTMARIO_TORNADO_VEL_Y_TAP, FTMARIO_TORNADO_VEL_Y_CLAMP);
    }
    ftPhysics_ApplyGravityDefault(fp, attributes);
    ftPhysics_ClampAirVelXStickRange(fp, 0, FTMARIO_TORNADO_VEL_X_AIR, ftMarioSpecialLwUpdateFriction(fp, FTMARIO_TORNADO_VEL_X_CLAMP));
}

// 0x8015675C
void ftMarioSpecialLwProcMap(GObj *fighter_gobj)
{
    mpCommonProcFighterOnGround(fighter_gobj, ftMarioSpecialLwSwitchStatusAir);
}

// 0x80156780
void ftMarioSpecialAirLwProcMap(GObj *fighter_gobj)
{
    mpCommonProcFighterLanding(fighter_gobj, ftMarioSpecialAirLwSwitchStatusGround);
}

// 0x801567A4
void ftMarioSpecialAirLwSetDisableRise(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    fp->command_vars.flags.flag3 = 0;
}

// 0x801567B0
void ftMarioSpecialAirLwSwitchStatusGround(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftMarioSpecialAirLwSetDisableRise(fighter_gobj);
    mpCommonSetFighterGround(fp);
    ftMainSetFighterStatus(fighter_gobj, nFTMarioStatusSpecialLw, fighter_gobj->anim_frame, 1.0F, FTSTATUS_PRESERVE_RUMBLE);
    ftPhysics_ClampGroundVel(fp, FTMARIO_TORNADO_VEL_X_CLAMP);
}

// 0x80156808
void ftMarioSpecialLwSwitchStatusAir(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftMarioSpecialAirLwSetDisableRise(fighter_gobj);
    mpCommonSetFighterAir(fp);
    ftMainSetFighterStatus(fighter_gobj, nFTMarioStatusSpecialAirLw, fighter_gobj->anim_frame, 1.0F, FTSTATUS_PRESERVE_RUMBLE);
    ftPhysics_ClampAirVelY(fp, FTMARIO_TORNADO_VEL_Y_CLAMP);
    ftPhysics_ClampAirVelX(fp, FTMARIO_TORNADO_VEL_X_CLAMP);
}

// 0x8015686C
void ftMarioSpecialLwInitStatusVars(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    fp->command_vars.flags.flag1 = 0;
    fp->command_vars.flags.flag2 = 0;

    fp->status_vars.mario.speciallw.dust_effect_int = 5;
    fp->status_vars.mario.speciallw.friction = 0.0F;
}

// 0x8015688C
void ftMarioSpecialLwSetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftMarioSpecialAirLwSetDisableRise(fighter_gobj);
    mpCommonSetFighterAir(fp);
    ftMainSetFighterStatus(fighter_gobj, nFTMarioStatusSpecialAirLw, 0.0F, 1.0F, FTSTATUS_PRESERVE_NONE);
    ftMainPlayAnimNoEffect(fighter_gobj);

    fp->phys_info.vel_air.y = -7.0F;

    ftPhysics_ClampAirVelX(fp, FTMARIO_TORNADO_VEL_X_CLAMP);
    ftMarioSpecialLwInitStatusVars(fighter_gobj);

    fp->stat_flags.ga = nMPKineticsGround;
}

// 0x80156910
void ftMarioSpecialAirLwSetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    f32 tornado_vel_y;

    ftMarioSpecialAirLwSetDisableRise(fighter_gobj);
    ftMainSetFighterStatus(fighter_gobj, nFTMarioStatusSpecialAirLw, 0.0F, 1.0F, FTSTATUS_PRESERVE_NONE);
    ftMainPlayAnimNoEffect(fighter_gobj);

    tornado_vel_y = (fp->fighter_vars.mario.is_expend_tornado != FALSE) ? 0.0F : FTMARIO_TORNADO_VEL_Y_TAP;

    fp->phys_info.vel_air.y = (FTMARIO_TORNADO_VEL_Y_BASE - tornado_vel_y);

    ftPhysics_ClampAirVelX(fp, FTMARIO_TORNADO_VEL_X_CLAMP);
    ftMarioSpecialLwInitStatusVars(fighter_gobj);
}
