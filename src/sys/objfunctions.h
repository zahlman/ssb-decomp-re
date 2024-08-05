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

#endif
