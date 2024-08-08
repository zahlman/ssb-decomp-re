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
extern f32 gcGetInterpValueCubic(f32 length_invert, f32 length, f32 value_base, f32 value_target, f32 rate_base, f32 rate_target);

// Other kind of interpolation?
extern f32 gcGetInterpRateCubic(f32 length_invert, f32 length, f32 value_base, f32 value_target, f32 rate_base, f32 rate_target);

// ???
extern f32 gcGetAObjValue(AObj *aobj);

// ???
extern f32 gcGetAObjRate(AObj *aobj);

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

// Get DObj axis value of corresponding track ID
extern f32 gcGetDObjAxisTrack(DObj *dobj, s32 track);

// Get DObjDesc axis value of corresponding track ID
extern f32 gcGetDObjDescAxisTrack(DObjDesc *dobj_desc, s32 track);

// Check if DObj or DObjDesc axis value of corresponding track ID has been retreived
extern sb32 gcCheckGetDObjNoAxisTrack
(
    sb32 is_desc_or_dobj,
    DObj *dobj,
    f32 *axis_value,
    f32 *rate,
    AObj *seek_aobj,
    DObjDesc *dobj_desc,
    s32 track,
    sb32 rate_kind,
    Vec3f *translate,
    sb32 *is_axis_ready
);

// ???
extern void gcGetAObjTrackAnimTimeMax(s32 track, f32 translate, f32 rotate, f32 scale, f32 *anim_time_max, AObj *aobj);

// ???
extern f32 gcGetDObjTempAnimTimeMax
(
    DObj *dobj,
    AObjAnimJoint **anim_joints,
    f32 anim_frame,
    DObjDesc *dobj_desc,
    s32 rate_kind,
    f32 length,
    f32 translate,
    f32 rotate,
    f32 scale
);

// Set up common DObj node tree for GObj
extern void gcSetupCommonDObjs(GObj *gobj, DObjDesc *dobj_desc, DObj **dobjs, u8 tk1, u8 tk2, u8 arg5);

#endif
