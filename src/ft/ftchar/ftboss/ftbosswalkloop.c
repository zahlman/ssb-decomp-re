#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x801598C0
sb32 ftBossWalkLoopCheckPlayerInRange(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    Vec3f *translate_m = &DObjGetStruct(fighter_gobj)->translate.vec.f;
    Vec3f *translate_t = &DObjGetStruct(fp->fighter_vars.boss.p->target_gobj)->translate.vec.f;

    if 
    (
        ((translate_t->y - translate_m->y) > -300.0F)           &&
        ((translate_t->y - translate_m->y) < 500.0F)            &&
        ((translate_t->x - translate_m->x) * fp->lr < 1200.0F)
    )                                                           // Check if target is in range, return TRUE if Master Hand should flick his pointer finger
    {
        return TRUE;
    }
    else return FALSE;
}

// 0x80159964
void ftBossWalkLoopProcPhysics(GObj *fighter_gobj)
{
    if (ftBossWalkLoopCheckPlayerInRange(fighter_gobj) != FALSE)
    {
        ftBossWalkShootSetStatus(fighter_gobj);
    }
}

// 0x80159994
void ftBossWalkLoopProcMap(GObj *fighter_gobj)
{
    if (ftMap_CheckGroundStanding(fighter_gobj) == FALSE)
    {
        ftBossWalkWaitSetStatus(fighter_gobj);
    }
}

// 0x801599C4
void ftBossWalkLoopSetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    fp->phys_info.vel_air.y = 0;

    ftMainSetFighterStatus(fighter_gobj, nFTBossStatusWalkLoop, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);

    fp->phys_info.vel_air.x = fp->lr * 35.0F;
}
