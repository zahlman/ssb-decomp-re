#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8015A0C0
void ftBossDrillProcUpdate(GObj *fighter_gobj)
{
    ftStatusSetOnAnimEnd(fighter_gobj, ftBossWaitSetStatus);
}

// 0x8015A0E4
void ftBossDrillProcPhysics(GObj *fighter_gobj)
{
    ftStruct *fp;

    ftPhysics_ApplyAirVelTransNYZ(fighter_gobj);

    fp = ftGetStruct(fighter_gobj);

    fp->status_vars.boss.drill.follow_timer--;

    if (fp->status_vars.boss.drill.follow_timer == 0) // Wait until timer reaches 0 to switch physics?
    {
        fp->proc_physics = ftBossDrillProcPhysicsFollow;
        fp->status_vars.boss.drill.follow_timer = 39;
    }
}

// 0x8015A138
void ftBossDrillProcPhysicsFollow(GObj *fighter_gobj)
{
    ftStruct *fp;
    f32 dist_x;

    ftPhysics_ApplyAirVelTransNYZ(fighter_gobj);

    fp = ftGetStruct(fighter_gobj);

    dist_x = DObjGetStruct(fp->fighter_vars.boss.p->target_gobj)->translate.vec.f.x - DObjGetStruct(fighter_gobj)->translate.vec.f.x;

    if (ABSF(dist_x) > 30.0F)
    {
        fp->phys_info.vel_air.x = (dist_x > 0.0F) ? 30.0F : -30.0F;
    }
    else fp->phys_info.vel_air.x = dist_x;
    
    fp->status_vars.boss.drill.follow_timer--;

    if (fp->status_vars.boss.drill.follow_timer == 0)
    {
        fp->phys_info.vel_air.x = 0.0F;
        fp->proc_physics = ftPhysics_ApplyAirVelTransNYZ;
    }
}

// 0x8015A204
void ftBossDrillProcMap(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    Vec3f *translate = &DObjGetStruct(fighter_gobj)->translate.vec.f;

    if (translate->x > fp->status_vars.boss.drill.edgeright_pos_x)
    {
        translate->x = fp->status_vars.boss.drill.edgeright_pos_x;
    }
    else if (translate->x < fp->status_vars.boss.drill.edgeleft_pos_x)
    {
        translate->x = fp->status_vars.boss.drill.edgeleft_pos_x;
    }
    mpCommonUpdateFighterProjectGround(fighter_gobj);
}

// 0x8015A268
void ftBossDrillSetStatus(GObj *fighter_gobj)
{
    ftStruct *fp;
    Vec3f pos;

    ftMainSetFighterStatus(fighter_gobj, nFTBossStatusDrill, 0.0F, 1.0F, FTSTATUS_PRESERVE_NONE);
    ftBossCommonCheckEdgeInvertLR(fighter_gobj);

    fp = ftGetStruct(fighter_gobj);

    mpCollisionGetLREdgeLeft(fp->coll_data.ground_line_id, &pos);

    fp->status_vars.boss.drill.edgeleft_pos_x = pos.x;

    mpCollisionGetLREdgeRight(fp->coll_data.ground_line_id, &pos);

    fp->status_vars.boss.drill.edgeright_pos_x = pos.x;

    fp->status_vars.boss.drill.follow_timer = 61;
}
