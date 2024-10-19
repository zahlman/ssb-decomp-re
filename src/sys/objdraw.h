#ifndef _OBJDRAW_H_
#define _OBJDRAW_H_

#include <sys/objtypes.h>

extern Gfx *gSYTaskmanDLHeads[4];

#define syMatrixStoreGbi(mtx_store, mtx_heap) \
(mtx_store.gbi = mtx_heap.ptr, mtx_heap.ptr = (Mtx*)mtx_heap.ptr + 1) \

// should be a concrete pointer type
typedef struct syMtxProcess
{
    sb32 (*proc_diff)();    // If GObj's last frame drawn is not the same as... something?
    sb32 (*proc_same)();    // If it's the same ^

} syMtxProcess;

// gbi Mtx * ? pointer to some sort of matrix
extern Mtx *sODMatrixProjectL;
extern f32 gODScaleX;
extern Mtx44f gODMatrixPerspF;
extern syMtxProcess *sODMatrixProcess;

extern void gcSetCameraScissor(s32 top, s32 bottom, s32 left, s32 right);
extern void gcSetMatrixProcess(syMtxProcess *proc_mtx);
extern void unref_80010740(void);
extern void func_80010748(Mtx *mtx_l, DObj *dobj, sb32 is_translate);
extern void func_80010918(Mtx *mtx_l, DObj *dobj, sb32 is_translate);
extern void func_80010AE8(Mtx *mtx_l, DObj *dobj, sb32 is_translate);
extern void func_80010C2C(Mtx *mtx_l, DObj *dobj, sb32 is_translate);
extern s32 gcPrepDObjMatrix(Gfx **dl, DObj *dobj);
extern void gcDrawMObjForDObj(DObj *dobj, Gfx **dl_head);
extern void gcDrawDObjForGObj(GObj *gobj, Gfx **dl_head);
extern void gcDrawDObjDLHead0(GObj *gobj);
extern void gcDrawDObjDLHead1(GObj *gobj);
extern void gcDrawDObjDLHead2(GObj *gobj);
extern void gcDrawDObjDLHead3(GObj *gobj);
extern void gcDrawDObjTree(DObj *this_dobj);
extern void gcDrawDObjTreeForGObj(GObj *gobj);
extern void gcDrawDObjDLLinks(DObj *dobj, DObjDLLink *dl_link);
extern void gcDrawDObjDLLinksForGObj(GObj *gobj);
extern void func_80014430(void);
extern void gcDrawDObjTreeDLLinks(DObj *dobj);
extern void gcDrawDObjTreeDLLinksForGObj(GObj *gobj);
extern f32 gcGetDObjDistFromEye(DObj *dobj);
extern void gcDrawDObjTreeMultiList(DObj *dobj);
extern void unref_800147E0(GObj *gobj);
extern void unref_80014A84(GObj *gobj);
extern void unref_80014C38(GObj *gobj);
extern void func_80014CD0(DObj *dobj);
extern void unref_80014FFC(GObj *gobj);
extern void gcDrawDObjTreeDLArray(DObj *dobj);
extern void unref_800154F0(GObj *gobj);
extern void gcDrawDObjTreeMultiList(DObj *dobj);
extern void unref_80015860(GObj *gobj);
extern void gcDrawDObjTreeDLDoubleArray(DObj *dobj);
extern void unref_80015A58(GObj *gobj);
extern void func_80015C0C(DObj *dobj);
extern void unref_80015F6C(GObj *gobj);
extern void unref_800162C8(GObj *gobj);
extern void func_80016338(Gfx **dls, Camera *cam, s32 buffer_id);
extern void func_8001663C(Gfx **dls, Camera *cam, s32 buffer_id);
extern void unref_80016AE4(Gfx **dls, Camera *cam, s32 arg2, void *image, s32 max_lrx, s32 max_lry, void *depth);
extern void gcPrepCameraMatrix(Gfx **dls, Camera *cam);
extern void gcSetCameraMatrixMode(s32 val);
extern void gcRunFuncCamera(Camera *cam, s32 arg);
extern void func_80017868(GObj *this_gobj, s32 link_id, s32 arg2);
extern void func_80017978(GObj *gobj, s32 index, s32 arg2);
extern void func_80017AAC(s32 index);
extern void func_80017B80(GObj *gobj, s32 arg1);
extern void func_80017CC8(Camera *cam);
extern void func_80017D3C(GObj *gobj, Gfx **dls, s32 index);
extern void func_80017DBC(GObj *gobj);
extern void unref_80017DE4(GObj *gobj);
extern void unref_80017E0C(GObj *gobj);
extern void unref_80017E34(GObj *gobj);
extern void unref_80017E5C(void);
extern void func_80017EC0(GObj *gobj);
extern void unref_8001810C(void);
extern void func_80018300(GObj *gobj);

#endif
