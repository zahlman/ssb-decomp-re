#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80159380
void ftBossHippatakuProcUpdate(GObj *fighter_gobj)
{
    ftStatusSetOnAnimEnd(fighter_gobj, ftBossWaitSetStatus);
}

// 0x801593A4
void ftBossHippatakuSetStatus(GObj *fighter_gobj)
{
    ftMainSetFighterStatus(fighter_gobj, ftStatus_Boss_Hippataku, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftBossCommonCheckEdgeInvertLR(fighter_gobj);
}
