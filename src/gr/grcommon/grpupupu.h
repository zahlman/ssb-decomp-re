#ifndef _GRPUPUPU_H_
#define _GRPUPUPU_H_

#include <ssb_types.h>
#include <sys/objdef.h>
#include <gr/grdef.h>
#include <ef/efdef.h>

extern s32 grPupupuWhispyGetLR(GObj *ground_gobj);
extern void grPupupuWhispySetWindPush(void);
extern void grPupupuWhispyUpdateSleep(void);
extern void grPupupuWhispyLeavesMakeEffect(void);
extern void grPupupuWhispyUpdateWait(void);
extern void grPupupuWhispyUpdateTurn(void);
extern void grPupupuWhispyUpdateOpen(void);
extern void grPupupuWhispyUpdateWindRumble(void);
extern void grPupupuWhispyUpdateBlow(void);
extern void grPupupuWhispyUpdateStop(void);
extern void grPupupuWhispyUpdateBlink(void);
extern void grPupupuUpdateWhispyStatus(void);
extern void grPupupuFlowersBackWindStart(void);
extern void grPupupuFlowersBackLoopStart(void);
extern void grPupupuFlowersBackLoopEnd(void);
extern void grPupupuFlowersBackUpdateAll(void);
extern void grPupupuFlowersFrontWindStart(void);
extern void grPupupuWhispyDustMakeEffect(void);
extern void grPupupuFlowersFrontLoopStart(void);
extern void grPupupuFlowersFrontLoopEnd(void);
extern void grPupupuFlowersFrontUpdateAll(void);
extern void grPupupuUpdateGObjAnims(void);
extern void grPupupuProcUpdate(GObj *ground_gobj);
extern GObj* grPupupuMakeMapGObj(intptr_t tk, intptr_t offset2, void (*proc_render)(GObj*), u8 dl_link);
extern void grPupupuInitAll(void);
extern GObj* grPupupuMakeGround(void);

#endif
