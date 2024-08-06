#ifndef _OBJFUNCTIONS_H_
#define _OBJFUNCTIONS_H_

#include <sys/objmanager.h>
#include <sys/objdraw.h>

// Orphan functions (no header yet / header not cleaned up yet)

// Add animation script to specific DObj
extern void gcAddDObjAnimJoint(DObj*, AObjAnimJoint*, f32);

// Add material animation script to specific MObj
extern void gcAddMObjMatAnimJoint(MObj*, AObjAnimJoint*, f32);

// Add animation script to all DObjs on a GObj
extern void gcAddAnimJointAll(GObj *gobj, AObjAnimJoint **anim_joints, f32 anim_frame);

// Add material aninmation script to all MObjs on a GObj
extern void gcAddMatAnimJointAll(GObj *gobj, AObjAnimJoint ***p_matanim_joints, f32 anim_frame);

// Add animation and material animation scripts to all DObjs and MObjs on a GObj
extern void gcAddAnimAll(GObj *gobj, AObjAnimJoint **anim_joints, AObjAnimJoint ***p_matanim_joints, f32 anim_frame);

// Parse AnimJoint on specific DObj
extern void gcParseDObjAnimJoint(DObj *dobj);

// Interpolation?
extern f32 func_8000CA28_D628(f32 length_invert, f32 length, f32 value_base, f32 value_target, f32 step_base, f32 step_target);

// Other kind of interpolation?
extern f32 func_8000CADC_D6DC(f32 length_invert, f32 length, f32 value_base, f32 value_target, f32 step_base, f32 step_target);

// ???
extern f32 func_8000CB94_D794(AObj *aobj);

// ???
extern f32 func_8000CC40_D840(AObj *aobj);

// Apply AnimJoint values on current frame of animation to specific DObj
extern void gcPlayDObjAnim(DObj *dobj);

// Apply MatAnimJoint values on current frame of animation to specific MObj
extern void gcPlayMObjMatAnim(MObj *mobj);

// Play all DObj and MObj animations on a GObj
extern void gcPlayAnimAll(GObj *gobj);

// Get AObj with matching track ID
extern AObj* gcGetTrackAObj(AObj *aobj, u8 track);

// Set DObj animation length?
extern void gcSetDObjAnimLength(DObj *dobj, f32 length);

// Get DObj vector value of corresponding track ID
extern f32 gcGetDObjValueTrack(DObj *dobj, s32 track);

#endif
