#ifndef _FTTYPES_H_
#define _FTTYPES_H_

#include <ssb_types.h>
#include <macros.h>
// #include <sys/objdraw.h> // Probably shouldn't be included
// #include <PR/ultratypes.h>
#include <sys/obj.h>
#include <sys/thread6.h>
#include <mp/map.h>
#include <ef/effect.h>
#include <cm/camera.h>
#include <gm/generic.h>
#include <gm/gmsound.h>

#include <ft/ftdef.h>

#include <ft/ftcommon.h>
#include <ft/ftchar.h>

// Structs
struct FTSpecialColl
{
    s32 kind;
    s32 joint_id;
    Vec3f offset;
    Vec3f size;
    s32 damage_resist;
};

struct FTItemPickup
{
    Vec2f pickup_offset_light;
    Vec2f pickup_range_light;
    Vec2f pickup_offset_heavy;
    Vec2f pickup_range_heavy;
};

struct FTThrownStatus
{
    s32 status1, status2;
};

struct FTThrownStatusArray
{
    FTThrownStatus ft_thrown[2];
};

union FTAnimDesc
{
    u32 word;

    struct
    {
        u32 is_use_xrotn_joint : 1;         // 0x80000000
        u32 is_use_transn_joint : 1;        // 0x40000000
        u32 is_use_yrotn_joint : 1;         // 0x20000000
        u32 x198_flag_b3 : 1;
        u32 x198_flag_b4 : 1;
        u32 x198_flag_b5 : 1;
        u32 x198_flag_b6 : 1;
        u32 x198_flag_b7 : 1;
        u32 x199_flag_b0 : 1;
        u32 x199_flag_b1 : 1;
        u32 x199_flag_b2 : 1;
        u32 x199_flag_b3 : 1;
        u32 x199_flag_b4 : 1;
        u32 x199_flag_b5 : 1;
        u32 x199_flag_b6 : 1;
        u32 x199_flag_b7 : 1;
        u32 x19A_flag_b0 : 1;
        u32 x19A_flag_b1 : 1;
        u32 x19A_flag_b2 : 1;
        u32 x19A_flag_b3 : 1;
        u32 x19A_flag_b4 : 1;
        u32 x19A_flag_b5 : 1;
        u32 x19A_flag_b6 : 1;
        u32 x19A_flag_b7 : 1;
        u32 x19B_flag_b0 : 1;
        u32 x19B_flag_b1 : 1;
        u32 x19B_flag_b2 : 1;
        ub32 is_use_submotion_script : 1;   // 0x00000010
        ub32 is_anim_joint : 1;             // 0x00000008 - whether current animation is type Figatree (0) or AnimJoint (1)
        ub32 is_have_translate_scale : 1;   // 0x00000004
        ub32 is_use_shieldpose : 1;         // 0x00000002
        ub32 is_use_animlocks : 1;          // 0x00000001

    } flags;
};

struct FTMotionDesc
{
    u32 anim_file_id;       // Animation file ID
    intptr_t offset;        // Offset?
    FTAnimDesc anim_desc;   // Animation flags
};

struct FTMotionDescArray
{
    FTMotionDesc script_info[1]; // Array size = last animation ID?
};

struct FTFileSize
{
    size_t main;
    size_t mainmotion_largest_anim;
    size_t submotion_largest_anim;
};

struct FTData
{
    u32 file_main_id; // File size in bytes?
    u32 file_mainmotion_id;
    u32 file_submotion_id;
    u32 file_model_id;
    u32 file_shieldpose_id;
    u32 file_special1_id;
    u32 file_special2_id;
    u32 file_special3_id;
    u32 file_special4_id;
    size_t file_main_size;
    void **p_file_main; // Pointer to character's file?
    void **p_file_mainmotion;
    void **p_file_submotion;
    void **p_file_model;
    void **p_file_shieldpose;
    void **p_file_special1;
    void **p_file_special2;
    void **p_file_special3;
    void **p_file_special4;
    s32 *p_particle;
    uintptr_t particles_script_lo;
    uintptr_t particles_script_hi;
    uintptr_t particles_texture_lo;
    uintptr_t particles_texture_hi;
    intptr_t o_attributes; // Offset to fighter's attributes
    FTMotionDescArray *mainmotion;
    FTMotionDescArray *submotion;
    s32 mainmotion_array_count;
    s32 *submotion_array_count;
    size_t file_anim_size;
};

struct FTModelPart
{
    void *display_list;
    MObjSub **mobjsubs;
    AObjEvent32 **costume_matanim_joints;
    AObjEvent32 **main_matanim_joints;
    u8 flags;
};

struct FTCommonPart
{
    DObjDesc *dobjdesc;
    MObjSub ***p_mobjsubs;
    AObjEvent32 ***p_costume_matanim_joints;
    u8 flags;
};

struct FTCommonPartContainer
{
    FTCommonPart commonparts[2];
};

struct FTModelPartDesc
{
    FTModelPart modelparts[1][2];
};

struct FTModelPartContainer
{
    FTModelPartDesc *modelparts_desc[FTPARTS_JOINT_NUM_MAX - nFTPartsJointCommonStart];
};

struct FTModelPartStatus
{
    s8 modelpart_id_default, modelpart_id_current;
};

struct FTTexturePart
{
    u8 joint_id;
    u8 detail[2];
};

struct FTTexturePartContainer
{
    FTTexturePart textureparts[2];
};

struct FTTexturePartStatus
{
    s8 texture_id_default, texture_id_current;
};

struct FTMotionFlags
{
    s16 motion_id : 10;
    u16 motion_attack_id : 6;
};

struct FTMotionScript
{
	f32 frame_timer;
	u32* p_script;
	s32 script_id;
	void* p_goto[1];
	s32 loop_count[4];
};

struct FTMotionEventDefault // Event with no arguments
{
	u32 opcode : 6;
    u32 value : 26;
};

struct FTMotionEventDouble // Event with no arguments
{
	u32 opcode : 6;
	u32 pad1 : 26;
	u32 pad2 : 32;
};

struct FTMotionEventMakeHit1
{
	u32 opcode : 6;
	u32 atk_id: 3;
	u32 group_id : 3;
	s32 joint_id : 7;
	u32 damage : 8;
	ub32 can_rebound : 1;
	u32 element : 4;
};

struct FTMotionEventMakeHit2
{
	u32 size : 16;
	s32 off_x : 16;
};

struct FTMotionEventMakeHit3
{
	s32 off_y : 16;
	s32 off_z : 16;
};

struct FTMotionEventMakeHit4
{
	s32 angle : 10;
	u32 knockback_scale : 10;
	u32 knockback_weight : 10;
	u32 is_hit_ground_air : 2;  // This should really be two separate bits, but it doesn't match that way
};

struct FTMotionEventMakeHit5
{
	s32 shield_damage : 8;
	u32 fgm_level : 3;
	u32 fgm_kind : 4;
	u32 knockback_base : 10;
};

struct FTMotionEventMakeHit
{
	FTMotionEventMakeHit1 s1;
	FTMotionEventMakeHit2 s2;
	FTMotionEventMakeHit3 s3;
	FTMotionEventMakeHit4 s4;
	FTMotionEventMakeHit5 s5;
};

struct FTMotionEventSetHitOffset1
{
	u32 opcode : 6;
	u32 atk_id: 3;
	s32 off_x : 16;
};

struct FTMotionEventSetHitOffset2
{
	s32 off_y : 16;
	s32 off_z : 16;
};

struct FTMotionEventSetHitOffset
{
	FTMotionEventSetHitOffset1 s1;
	FTMotionEventSetHitOffset2 s2;
};

struct FTMotionEventSetHitDamage
{
	u32 opcode : 6;
	u32 atk_id: 3;
	u32 damage : 8;
};

struct FTMotionEventSetHitSize
{
	u32 opcode : 6;
	u32 atk_id: 3;
	u32 size : 16;
};

struct FTMotionEventSetHitSound
{
	u32 opcode : 6;
	u32 atk_id: 3;
	u32 fgm_level : 3;
};

struct FTMotionEventSetThrow1
{
	u32 opcode : 6;
};

struct FTMotionEventSetThrow2
{
	FTThrowHitDesc* fighter_throw;
};

struct FTMotionEventSetThrow
{
	FTMotionEventSetThrow1 s1;
	FTMotionEventSetThrow2 s2;
};

struct FTMotionEventMakeEffect1
{
	u32 opcode : 6;
	s32 joint_id : 7;
	u32 effect_id : 9;
	u32 flag : 10;
};

struct FTMotionEventMakeEffect2
{
	s32 off_x : 16;
	s32 off_y : 16;
};

struct FTMotionEventMakeEffect3
{
	s32 off_z : 16;
	s32 rng_x : 16;
};

struct FTMotionEventMakeEffect4
{
	s32 rng_y : 16;
	s32 rng_z : 16;
};

struct FTMotionEventMakeEffect
{
	FTMotionEventMakeEffect1 s1;
	FTMotionEventMakeEffect2 s2;
	FTMotionEventMakeEffect3 s3;
	FTMotionEventMakeEffect4 s4;
};

struct FTMotionEventSetHitStatusPartID
{
	u32 opcode : 6;
	s32 joint_id : 7;
	u32 hitstatus : 19;
};

struct FTMotionEventModifyHurtPartID1
{
	u32 opcode : 6;
	s32 joint_id : 7;
};

struct FTMotionEventModifyHurtPartID2
{
	s32 off_x : 16;
	s32 off_y : 16;
};

struct FTMotionEventModifyHurtPartID3
{
	s32 off_z : 16;
	s32 size_x : 16;
};

struct FTMotionEventModifyHurtPartID4
{
	s32 size_y : 16;
	s32 size_z : 16;
};

struct FTMotionEventModifyHurtPartID
{
	FTMotionEventModifyHurtPartID1 s1;
	FTMotionEventModifyHurtPartID2 s2;
	FTMotionEventModifyHurtPartID3 s3;
	FTMotionEventModifyHurtPartID4 s4;
};

struct FTMotionEventSubroutine1
{
	u32 opcode : 6;
};

struct FTMotionEventSubroutine2
{
	void* p_goto;
};

struct FTMotionEventSubroutine
{
	FTMotionEventSubroutine1 s1;
	FTMotionEventSubroutine2 s2;
};

struct FTMotionEventSetDamageThrown1
{
	u32 opcode : 6;
};

struct FTMotionEventSetDamageThrown2
{
	void* p_subroutine;
};

struct FTMotionDamageScript
{
	void* p_script[2][nFTKindEnumMax];
};

struct FTMotionEventSetDamageThrown
{
	FTMotionEventSetDamageThrown1 s1;
	FTMotionEventSetDamageThrown2 s2;
};

struct FTMotionEventGoto1
{
	u32 opcode : 6;
};

struct FTMotionEventGoto2
{
	void* p_goto;
};

struct FTMotionEventGoto
{
	FTMotionEventGoto1 s1;
	FTMotionEventGoto2 s2;
};

struct FTMotionEventParallel1
{
	u32 opcode : 6;
};

struct FTMotionEventParallel2
{
	void* p_goto;
};

struct FTMotionEventParallel
{
	FTMotionEventParallel1 s1;
	FTMotionEventParallel2 s2;
};

struct FTMotionEventSetModelPartID
{
	u32 opcode : 6;
	s32 joint_id : 7;
	s32 modelpart_id : 19;
};

struct FTMotionEventSetTexturePartID
{
	u32 opcode : 6;
	u32 texturepart_id : 6;
	u32 frame : 20;
};

struct FTMotionEventSetColAnimID
{
	u32 opcode : 6;
	u32 colanim_id : 8;
	u32 length : 18;
};

struct FTMotionEventSetSlopeContour
{
	u32 opcode : 6;
	u32 pad : 23;
	u32 flags : 3;
};

struct FTMotionEventSetAfterImage
{
	u32 opcode : 6;
	u32 is_itemswing : 8;
	s32 drawstatus : 18;
};

struct FTMotionEventMakeRumble
{
	u32 opcode : 6;
	u32 length : 13;
	u32 rumble_id : 13;
};

struct FTMotionEventStopRumble
{
	u32 opcode : 6;
	u32 rumble_id : 26;
};

struct FTStatusDesc
{
    FTMotionFlags mflags;
    GMStatFlags sflags;

    void (*proc_update)(GObj*);
    void (*proc_interrupt)(GObj*);
    void (*proc_physics)(GObj*);
    void (*proc_map)(GObj*);
};

struct FTOpeningDesc
{
    s32 motion_id;
    void (*proc_update)(GObj*);
};

struct FTThrowHitDesc
{
    s32 status_id;
    s32 damage;
    s32 angle;
    s32 knockback_scale;
    s32 knockback_weight;
    s32 knockback_base;
    s32 element;
};

struct FTThrowReleaseDesc
{
    s32 angle;
    s32 knockback_scale;
    s32 knockback_weight;
    s32 knockback_base;
};

struct FTCreateDesc
{
    s32 fkind;
    Vec3f pos;
    s32 lr_spawn;
    u8 team;
    u8 player;
    u8 detail;
    u8 costume;
    u8 shade;
    u8 handicap;
    u8 cp_level;
    u8 stock_count;
    u8 unk_rebirth_0x1C;
    u8 unk_rebirth_0x1D;
    u8 team_order;                  // Order number of fighter if member of "VS *character* Team" 
    ub32 is_skip_entry : 1;         // If TRUE, fighter gets spawned in Wait or Fall state, otherwise use entry state
    ub32 is_skip_shadow_setup : 1;  // If TRUE, fighter's shadow is not initialized
    ub32 is_skip_magnify : 1;       // If TRUE, fighter's magnifying glass is not rendered?
    s32 copy_kind;                  // Kirby's copy ID on spawn
    s32 damage;
    s32 pkind;
    gsController *controller;       // Pointer to player's controller input struct
    u16 button_mask_a;
    u16 button_mask_b;
    u16 button_mask_z;
    u16 button_mask_l;
    void *figatree_heap;                // Pointer to animation bank?
    void *func_display;
};

struct FTAttackMatrix
{
    sb32 unk_fthitmtx_0x0;
    Mtx44f mtx;
    f32 unk_fthitmtx_0x44;
};

struct FTAttackColl
{
    s32 atk_state;
    u32 group_id;
    s32 joint_id;
    s32 damage;
    s32 element;
    DObj *joint;
    Vec3f offset;
    f32 size;
    s32 angle;
    s32 knockback_scale;
    s32 knockback_weight;
    s32 knockback_base;
    s32 shield_damage;
    u32 fgm_level : 3;
    u32 fgm_kind : 4;
    ub32 is_hit_air : 1;
    ub32 is_hit_ground : 1;
    ub32 can_rebound : 1;
    ub32 is_scale_pos : 1;
    u32 attack_id : 6;
    u16 motion_count;
    u16 stat_count;
    Vec3f pos_curr;
    Vec3f pos_prev;
    GMAttackRecord atk_records[GMATKRECORD_NUM_MAX];
    FTAttackMatrix hit_matrix;
};

struct FTDamageCollDesc
{
    s32 joint_id;
    s32 placement;
    sb32 is_grabbable;
    Vec3f offset;
    Vec3f size;
};

struct FTDamageColl
{
    s32 hitstatus;
    s32 joint_id;
    DObj *joint;
    s32 placement;              // 0 = low, 1 = middle, 2 = high
    sb32 is_grabbable;
    Vec3f offset;
    Vec3f size;
};

struct FTHitlog // Might have to return once structs are cleaned up (alas once forward declarations are implemented to replace void* with struct*)
{
    s32 attacker_object_class;
    void *attacker_hit;
    s32 atk_id;
    GObj *attacker_gobj;
    FTDamageColl *victim_hurt; // Victim fighter's hurtbox
    u8 attacker_player;
    s32 attacker_player_number;
};

struct FTItemThrow
{
    sb32 is_smash_throw : 1;
    s32 velocity : 10;
    s32 angle : 11;
    u32 damage : 10;
};

struct FTItemSwing
{
    u32 anim_speed : 10;
};

// PObj / Polygon object?
struct FTParts
{
    s32 transform_update_mode;              // Update mode of DObj's transformations?
    // 0 = free transformation updates
    // 1 = lock transformation updates
    // 2 = ???
    // 3 = ???
    union
    {
        struct
        {
            u8 unk_dobjtrans_0x4;
            u8 unk_dobjtrans_0x5;
            u8 unk_dobjtrans_0x6;
            u8 unk_dobjtrans_0x7;
        };
        s32 unk_dobjtrans_word;
    };

    FTParts *alloc_next;
    u8 flags;
    u8 joint_id;
    ub8 is_have_anim;
    u8 unk_dobjtrans_0xF;
    Mtx44f unk_dobjtrans_0x10;
    Mtx44f mtx_translate;
    Vec3f vec_scale; // ???
    Mtx44f unk_dobjtrans_0x9C;
    GObj *gobj;
};

struct FTWithheldPart
{
    s32 root_joint_id;
    s32 parent_joint_id;
    s32 partindex_0x8;
    s32 joint_kind;
};

// Skeleton joints for electric shock effects?
struct FTSkeleton
{
    union
    {
        Gfx *display_list;
        Gfx **dl_array;
    };
    u8 flags;
};

struct FTShadow
{
    Vtx shadow_vertex1[8];
    Vtx shadow_vertex2[8];
    s32 player;
    s32 unk_0x104;
};

struct FTCostume
{
    u8 royal[4];
    u8 team[3];
    u8 develop;
};

struct FTDemoDesc
{
    s32 fkind;
    s32 costume;
    s32 shade;
};

struct FTAfterImage
{
    s16 translate_x;
    s16 translate_y;
    s16 translate_z;
    Vec3f vec;
};

struct FTCamera
{
    FTStruct *target_fp;
    Vec3f target_pos;
    f32 unk_ftcobj_0x10;
};

struct FTSprites
{
    Sprite *stock_sprite;
    int **stock_luts;
    Sprite *emblem;
};

struct FTComputer
{
    u8 objective;                           // CPU player's current objective
    u8 objective_default;                   // CPU player's default objective
    u8 input_kind;                          // Stick + Button combination CPU player is set to execute
    u8 behavior;                            // CPU player's general behavior
    u8 unk_ftcom_0x4;                       // Unused?
    u8 trait;                               // CPU player will determine behavior based on this
    u8 unk_ftcom_0x6;                       // Unused?
    u8 input_wait;                          // "Controller command wait timer"
    u8 *p_command;                          // Controller input commands
    sb32 (*proc_com)(GObj*);                // "Main behavior routine"
    u16 jump_wait;                          // CPU player will wait this many frames before jumping on "jump" behavior?
    u16 item_track_wait;                    // CPU player will wait this many frames before targeting an item?
    u16 behavior_change_wait;               // CPU player will wait this many frames before changing behavior?
    u16 unk_ftcom_0x16;                     // Unused?
    u16 walk_stop_wait;                     // CPU player will wait this many frames before stopping after walking for 2.5 seconds?
    u16 fighter_follow_since;               // CPU player has followed its opponent for this many frames?
    u16 fighter_follow_wait;                // CPU player will wait this many frames before following target?
    u16 fighter_follow_end;                 // CPU player will stop following target after this many frames?
    u16 unk_ftcom_0x20;                     // ???
    u16 target_find_wait;
    u16 wiggle_wait;                        // CPU player will wait this many frames before finding a new target?
    u16 target_damage_percent;              // ???
    u16 attack_atk_count;                   // Number of times CPU player successfully dealt damage?
    u16 appeal_attempt_frames;              // CPU player will attempt to taunt while this is not 0
    u16 stand_stop_wait;                    // CPU player will wait this many frames before breaking out of idle behavior
    GObj *target_gobj;                      // CPU player's target's GObj
    u8 item_throw_wait;                     // CPU player will wait this many frames before throwing held item?
    u8 unk_ftcom_0x35;
    u8 unk_ftcom_0x36;                      // Unused?
    u8 input_repeat_count;                  // Number of times CPU player has repeated the same input combination?
    u8 unk_ftcom_0x38;
    u8 stickn_button_a_count;               // Jab
    u8 sticktilts_button_a_count;           // Forward Tilt
    u8 sticksmashs_button_a_count;          // Forward Smash
    u8 sticktilthi_button_a_count;          // Up Tilt
    u8 sticksmashhi_button_a_count;         // Up Tilt / Up Aerial / Down Tilt / Down Aerial?
    u8 sticktiltlw_button_a_count;          // Down Tilt
    u8 sticksmashlw_button_a_count;         // Down Smash / Down Aerial
    u8 sticksmashs_button_b_count;          // Neutral Special
    u8 sticksmashhi_button_b_count;         // Up Special
    u8 sticksmashlw_button_b_count;         // Down Special
    u8 stickn_button_z_button_a_count;      // Grab
    ub32 unk_ftcom_0x44;                    // Unused?
    ub32 ftcom_flags_0x48_b0 : 1;           // Unused?
    ub32 ftcom_flags_0x48_b1 : 1;           // Unused?
    ub32 ftcom_flags_0x48_b2 : 1;           // Unused?
    ub32 ftcom_flags_0x48_b3 : 1;           // Unused?
    ub32 ftcom_flags_0x48_b4 : 1;           // Unused?
    ub32 ftcom_flags_0x48_b5 : 1;           // Unused?
    ub32 ftcom_flags_0x48_b6 : 1;           // Unused?
    ub32 ftcom_flags_0x48_b7 : 1;           // Unused?
    ub32 is_within_vertical_bounds : 1;     // ???
    ub32 ftcom_flags_0x49_b1 : 1;
    ub32 ftcom_flags_0x49_b2 : 1;           // Never set but compared against to check if CPU player should act appropriately VS fighters with reflector/absorb moves?
    ub32 ftcom_flags_0x49_b3 : 1;
    ub32 is_counterattack : 1;              // Whether CPU player will act just before landing from DamageFall?
    ub32 is_shield_item_weapon : 1;         // CPU player will attempt to shield if it detects an incoming weapon or item
    ub32 is_opponent_ra : 1;                // Whether CPU player's opponent can reflect or absorb?
    ub32 is_attempt_specialhi_recovery : 1; // Whether CPU will attempt to recover with Up Speciial
    ub32 ftcom_flags_0x4A_b0 : 1;
    ub32 ftcom_flags_0x4A_b1 : 1;
    ub32 is_stop_stand : 1;                 // Whether CPU player should leave standing / idle state
    Vec2f cliff_left_pos;                   // Nearest left ledge?
    Vec2f cliff_right_pos;                  // Nearest right ledge?
    s32 target_line_id;                     // CPU's target's line ID
    Vec2f target_pos;                       // CPU's target's position
    f32 target_dist;                        // FLOAT_MAX when offstage
    void *target_user;                      // FTStruct* most of the time, but can be ITStruct* too when looking for nearest item
    Vec2f origin_pos;                       // CPU player's TopN position at creation?
    Vec2f edge_pos;                         // CPU player's patrol range? (ends at edges of ground_line_id?)
    Vec2f stand_pos;                        // ??? Is this where the CPU player is supposed to stand when idling?
    s32 ground_line_id;                     // Some kind of collision line ID
    f32 dash_predict;                       // CPU player uses this to predict when it's appropriate to dash / run?
    f32 jump_predict;                       // CPU player uses this to predict what jump height to go for?
};

struct FTComputerAttack
{
    s32 input_kind;
    s32 hit_start_frame;
    s32 hit_end_frame;
    f32 detect_near_x;
    f32 detect_far_x;
    f32 detect_near_y;
    f32 detect_far_y;
};

struct FTPlayerInput
{
    u16 button_hold;
    u16 button_tap;
    u16 button_tap_prev;
    Vec2b stick_range;
    Vec2b stick_prev; // Previous stick range?
};

struct FTComputerInput
{
    u16 button_inputs;
    Vec2b stick_range; // CPU stick input?
};

union FTKeyCommand
{
    u16 halfword;

    struct
    {
        u16 opcode : 4;
        u16 param : 12;
    } 
    command;

    Vec2b stick_range;
};

struct FTKey
{
    s32 input_wait;
    FTKeyCommand *input_seq;
};

struct FTAttributes
{
    f32 size_mul;
    f32 walkslow_anim_length;
    f32 walkmiddle_anim_length;
    f32 walkfast_anim_length;
    f32 throw_walkslow_anim_length;
    f32 throw_walkmiddle_anim_length;
    f32 throw_walkfast_anim_length; // Cargo Throw
    f32 rebound_anim_length;
    f32 walk_speed_mul;
    f32 traction;
    f32 dash_speed;
    f32 dash_decelerate;
    f32 run_speed;
    f32 kneebend_anim_length; // Jump squat frames
    f32 jump_vel_x;
    f32 jump_height_mul;
    f32 jump_height_base;
    f32 aerial_jump_vel_x;
    f32 aerial_jump_height;
    f32 aerial_acceleration;
    f32 aerial_speed_max_x;
    f32 aerial_friction;
    f32 gravity;
    f32 tvel_default;
    f32 tvel_fast;
    s32 jumps_max; // Number of jumps
    f32 weight;
    f32 attack1_followup_frames; // Jab combo connection frames
    f32 dash_to_run; // Frames before dash transitions to run?
    f32 shield_size;
    f32 shield_break_vel_y;
    f32 shadow_size;
    f32 jostle_width; // ???
    f32 jostle_x;
    sb32 is_metallic; // So far only seen this used to determine whether the character makes blue sparks or gray metal dust particles when hit; used by Metal Mario and Samus
    f32 cam_offset_y;
    f32 closeup_camera_zoom;
    f32 camera_zoom;
    f32 camera_zoom_default;
    MPObjectColl obj_coll;
    Vec2f cliffcatch_coll; // Ledge grab box
    u16 dead_sfx[2]; // KO voices
    u16 deadup_sfx;  // Star-KO voice
    u16 damage_sfx;
    u16 smash_sfx[3]; // Random Smash SFX
    FTItemPickup item_pickup;
    u16 item_throw_vel;
    u16 item_throw_mul;
    u16 heavyget_sfx;
    f32 halo_size; // Respawn platform size?
    syColorRGBA shade_color[3];
    syColorRGBA fog_color;
    ub32 is_have_attack11    : 1;
    ub32 is_have_attack12    : 1;
    ub32 is_have_attackdash  : 1;
    ub32 is_have_attacks3    : 1;
    ub32 is_have_attackhi3   : 1;
    ub32 is_have_attacklw3   : 1;
    ub32 is_have_attacks4    : 1;
    ub32 is_have_attackhi4   : 1;
    ub32 is_have_attacklw4   : 1;
    ub32 is_have_attackairn  : 1;
    ub32 is_have_attackairf  : 1;
    ub32 is_have_attackairb  : 1;
    ub32 is_have_attackairhi : 1;
    ub32 is_have_attackairlw : 1;
    ub32 is_have_specialn    : 1;
    ub32 is_have_specialairn : 1;
    ub32 is_have_specialhi   : 1;
    ub32 is_have_specialairhi: 1;
    ub32 is_have_speciallw   : 1;
    ub32 is_have_specialairlw: 1;
    ub32 is_have_catch       : 1;   // Whether fighter has a grab
    ub32 is_have_voice       : 1;
    FTDamageCollDesc dmg_colls_desc[FTPARTS_HURT_NUM_MAX];
    Vec3f hit_detect_range;         // This is a radius around the fighter within which hitbox detection can occur
    u32 *setup_parts;               // Pointer to two sets of flags marking joints that should be initialized on fighter creation
    u32 *animlock;                  // Pointer to two sets of flags marking joints that should not be animated;
                                    // Ignores special joints, so count starts from 4
    s32 effect_joint_ids[5];        // The game will cycle through these joints when applying certain particles such as electricity and flames
    sb32 cliff_status_ga[5];        // Bool for whether fighter is grounded or airborne during each cliff state
    u8 filler_0x2CC[0x2D0 - 0x2CC];
    FTWithheldPart *withheld_parts;
    FTCommonPartContainer *commonparts_container;
    DObjDesc *dobj_lookup; // WARNING: Not actually DObjDesc* but I don't know what this struct is or what its bounds are; bunch of consecutive floats
    AObjEvent32 **shield_anim_joints[8];  // One for each ordinal direction
    s32 joint_rfoot_id; // What does this do?
    f32 joint_rfoot_rotate;
    s32 joint_lfoot_id;
    f32 joint_lfoot_rotate;
    u8 filler_0x304[0x31C - 0x30C];
    f32 unk_0x31C;
    f32 unk_0x320;
    Vec3f *translate_scales; // Scales the translation vector of a given joint?
    FTModelPartContainer *modelparts_container;
    FTMesh *mesh;
    FTTexturePartContainer *textureparts_container;
    s32 joint_itemheavy_id;
    FTThrownStatusArray *thrown_status;
    s32 joint_itemlight_id;
    FTSprites *sprites;
    FTSkeleton **skeleton;
};

struct FTMesh
{
    s32 joint_id;
    Gfx *dl;
    MObjSub **mobjsubs;
    AObjEvent32 **costume_matanim_joints;
};

// Main fighter struct
struct FTStruct
{
    FTStruct *alloc_next;
    GObj *fighter_gobj;
    s32 fkind;
    u8 team;
    u8 player;
    u8 detail_current;          // Hi-Poly = 1, Low-Poly = 2
    u8 detail_default;          // Hi-Poly = 1, Low-Poly = 2
    u8 costume;
    u8 shade;                   // i.e. When multiple instances of the same character costume are in-game
    u8 handicap;
    u8 cp_level;
    s8 stock_count;
    u8 team_order;              // Order number if this fighter is a "VS *character* Team" member; used to check for bonuses such as Yoshi Rainbow
    u8 dl_link;
    s32 player_number;          // Player's number? (Note: NOT player port, e.g. if players 2 and 4 are in a match,
                                // player 2 will be number 1 and player 4 will be number 2; used to match fighters and items?)

    u32 status_total_tics;      // Frames spent in this action state

    s32 pkind;                  // Control type: 0 = HMN, 1 = COM, 2 = N/A

    s32 status_id;
    s32 motion_id;              // Index of moveset command script to use

    s32 percent_damage;
    s32 damage_resist;          // Resits a specific amount of % damage before breaking, effectively damage-based armor
    s32 shield_health;
    f32 unk_ft_0x38;
    s32 unk_ft_0x3C;
    u32 hitlag_tics;
    s32 lr;                     // Facing direction; -1 = -1, 1 = +1

    struct FTPhysics
    {
        Vec3f vel_air; // Aerial self-induced velocity
        Vec3f vel_damage_air; // Aerial knockback velocity
        Vec3f vel_ground; // Grounded self-induced velocity
        f32 vel_damage_ground;
        f32 vel_jostle_x;
        f32 vel_jostle_z;

    } physics;

    MPCollData coll_data;

    u8 jumps_used;
    u8 unk_ft_0x149;
    sb32 ga;

    f32 attack1_followup_frames;
    s32 attack1_status_id;
    s32 attack1_input_count;
    s32 cliffcatch_wait;
    s32 tics_since_last_z;              // Frames since last Z-press, resets to 65536 on action state change
    s32 acid_wait;                      // Wait this many frames before fighter can be hurt by Planet Zebes acid again
    s32 twister_wait;                   // Wait this many frames before fighter can be picked up by the Hyrule Tornado again
    s32 tarucann_wait;                  // Wait this many frames before fighter can enter Barrel Cannon again
    s32 damagefloor_wait;               // Wait this many frames before fighter can be hurt by damaging floors again (e.g. Mario's Board the Platforms stage)
    s32 playertag_wait;                 // Wait this many frames before fighter's player indicator is shown again; tag is shown when this reaches 1 or is overridden by position on stage

    s32 card_anim_frame_id;             // Index of fighter's role on 1P Stage Card scene? (e.g. player character, opponent, ally etc.)

    union FTCommandVars
    {
        struct FTCommandFlags
        {
            u32 flag0;
            u32 flag1;
            u32 flag2;
            u32 flag3;

        } flags;

        struct FTItemThrowFlags
        {
            sb32 is_throw_item;
            u8 unk1;
            u32 damage : 24;
            u8 unk2;
            u32 vel : 12;
            s32 angle : 12;

        } item_throw;

    } motion_vars;

    ub32 is_atk_active : 1;
    ub32 is_hitstatus_nodamage : 1;
    ub32 is_hurtbox_modify : 1;
    ub32 is_modelpart_modify : 1;
    ub32 is_texturepart_modify : 1;
    ub32 is_reflect : 1;                // Fighter's reflect box is active
    s32 reflect_lr : 2;
    ub32 is_absorb : 1;                 // Fighter's absorb box is active
    s32 absorb_lr : 2;
    ub32 is_goto_attack100 : 1;
    ub32 is_fast_fall : 1;
    ub32 is_show_magnify : 1;
    ub32 is_limit_map_bounds : 1;       // When Master Hand is defeated, this is set to TRUE so the player cannot die if they are offstage;
                                        // Effectively keeps the player at the blast zone and ignores the dead action state
    ub32 is_invisible : 1;
    ub32 is_hide_shadow : 1;
    ub32 is_rebirth : 1;
    ub32 is_skip_magnify : 1;           // Skip rendering magnifying glass if TRUE?
    ub32 is_playertag_hide : 1;         // Skip rendering player indicator if TRUE
    ub32 is_playertag_bossend : 1;      // Also skips rendering player indicator? Used only in "Master Hand defeated" cinematic from what I can tell so far
    ub32 is_playing_effect : 1;
    u32 effect_joint_array_id : 4;      // Goes up to 5 by default; index of the array from effect_joint_ids from FTAttributes which houses the actual joint ID
    ub32 is_shield : 1;                 // Fighter's shield bubble is active
    ub32 is_attach_effect : 1;          // Destroy GFX on action state change if TRUE, not sure why this and is_playing_effect are different
    ub32 is_ignore_jostle : 1;
    ub32 is_have_translate_scale : 1;
    ub32 is_disable_control : 1;        // Fighter cannot be controlled if TRUE; enabled when training mode menu is up
    ub32 is_hitstun : 1;
    u32 slope_contour : 3;
    ub32 is_use_animlocks : 1;
    ub32 is_playing_sfx : 1;
    ub32 unk_ft_0x190_b5 : 1;           // Never seen this used
    ub32 is_show_item : 1;
    ub32 is_cliff_hold : 1;             // Whether fighter is holding onto a ledge
    ub32 is_effect_interrupt : 1;       // Is this flag's sole purpose to fast-forward GFX in the moveset event parser?
    ub32 is_nullstatus : 1;             // Dead / Entry / Appear / Rebirth, ignore hit collisions + map_bounds?
    ub32 is_damage_resist : 1;
    ub32 is_ignore_training_menu : 1;   // Can't bring up training menu if TRUE? Might be used for some other things
    u32 camera_mode : 4;
    ub32 is_special_interrupt : 1;      // Whether move can be interrupted by Link's boomerang? Have not seen this used anywhere else
    ub32 is_ignore_dead : 1;            // Ignore dead action states altogether
    ub32 is_catchstatus : 1;
    ub32 unk_ft_0x192_b3 : 1;           // My brain stops working every time I try to understand what this does
    ub32 is_use_fogcolor : 1;
    ub32 is_shield_catch : 1;           // Set to TRUE when fighter grabs after getting shield poked; there is a check for this flag that halves throw damage if TRUE
    ub32 is_knockback_paused : 1;       // Whether fighter's knockback is paused until hitlag is over?

    u8 capture_immune_mask;             // Fighter is immune to these grab types
    u8 catch_mask;                      // Fighter's current grab type

    FTAnimDesc anim_desc;
    Vec3f anim_vel;

    Vec2f magnify_pos;

    struct FTInputStruct
    {
        void *controller;               // Controller inputs?
        u16 button_mask_a;
        u16 button_mask_b;
        u16 button_mask_z;
        u16 button_mask_l;
        FTPlayerInput pl;
        FTComputerInput cp;

    } input;

    FTComputer computer;

    Vec2f dmg_coll_size;             // Width and height of fighter's hurtbox; calculated from distance of TopN position to farthest hurtbox multiplied by 0.55

    u8 tap_stick_x;                     // Frames control stick has been tapped
    u8 tap_stick_y;                     // Frames control stick has been tapped
    u8 hold_stick_x;                    // Frames control stick has been tapped or held
    u8 hold_stick_y;                    // Frames control stick has been tapped or held

    s32 breakout_wait;                  // Frames until fighter breaks out of shield break / sleep / Cargo Throw
    s8 breakout_lr;                     // Whether victim is mashing left or right
    s8 breakout_ud;                     // Whether victim is mashing up or down

    u8 shuffle_frame_index;             // Ranges from 0-3; position of fighter's model vibration is adjusted based on this index when receiving hitlag
    u8 shuffle_index_max;               // How many iterations the frame index increments before looping back to 0;
    ub8 is_shuffle_electric;            // Fighter vibrates horizontally rather than vertically if hit by an electric attack
    u16 shuffle_tics;                   // Model shift timer

    GObj *throw_gobj;                   // GObj of opponent that threw this fighter
    FTKind throw_fkind;               // Kind of opponent that threw this fighter
    u8 throw_team;                      // Team of opponent that threw this fighter
    u8 throw_player;                    // Port of opponent that threw this fighter
    s32 throw_player_number;            // Player number of opponent that threw this fighter

    u32 attack_id;                      // Also used in staling queue
    u16 motion_count;                   // This is used to tell the game not to stale multihit attacks
    GMStatFlags stat_flags;
    u16 stat_count;

    FTAttackColl atk_colls[4];

    s32 invincible_tics;
    s32 intangible_tics;
    s32 special_hitstatus;
    s32 star_invincible_tics;
    s32 star_hitstatus;                 // Enemy CPUs avoid player depending on this?
    s32 hitstatus;

    FTDamageColl dmg_colls[FTPARTS_HURT_NUM_MAX];

    f32 unk_ft_0x7A0;                   // Unused?
    f32 hitlag_mul;
    f32 shield_lifeup_wait;
    s32 unk_ft_0x7AC;                   // Unused?

    s32 attack_damage;
    f32 attack_knockback;
    u16 attack_atk_count;               // Number of times this fighter successfully dealt damage 
    s32 attack_shield_push;             // Used to calculate shield/rebound pushback
    f32 attack_rebound;                 // Actually 2x staled damage?
    s32 attack_lr;
    s32 shield_damage;
    s32 shield_damage_total;            // shield_damage + hitbox damage + hitbox shield damage, does not persist?
    s32 shield_lr;
    s32 shield_player;                  // Port of player hitting this fighter's shield
    s32 reflect_damage;
    s32 damage_lag;                     // Used to calculate hitlag?
    f32 damage_knockback;
    f32 knockback_resist_passive;       // Passive armor, always active (?)
    f32 knockback_resist_status;        // Resist this many units of knockback, effectively knockback-based armor
    f32 damage_stack;                   // Knockback stacking?
    s32 damage_queue;                   // Used to calculate knockback?
    s32 damage_angle;
    s32 damage_element;
    s32 damage_lr;
    s32 damage_index;
    s32 damage_joint_id;
    s32 damage_player_number;
    s32 damage_player;                  // Port index of damaging fighter
    u16 damage_count;
    s32 damage_kind;
    s32 damage_heal;                    // Percent damage to heal
    f32 damage_mul;
    s32 damage_object_class;            // Fighter, Weapon, Item or Ground
    s32 damage_object_kind;             // FTKind, WPKind, ITKind, envKind
    GMStatFlags damage_stat_flags;
    u16 damage_stat_count;

    f32 publicity_knockback;            // Knockback value used for crowd reactions

    GObj *search_gobj;                  // GObj this fighter found when searching for grabbable fighters?
    f32 search_gobj_dist;
    void (*proc_catch)(GObj*);          // Run this callback on grabbing attacker
    void (*proc_capture)(GObj*, GObj*); // Run this callback on grabbed victim
    GObj *catch_gobj;                   // GObj this fighter has caught
    GObj *capture_gobj;                 // GObj this fighter is captured by

    FTThrowHitDesc *fighter_throw;      // Pointer to throw description

    GObj *item_gobj;

    FTSpecialColl *spc_coll;

    Vec3f entry_pos;

    f32 camera_zoom_frame;              // Maximum size of fighter's camera range?
    f32 camera_zoom_range;              // Multiplier of fighter's camera range?

    FTMotionScript motion_script[2][2];

    DObj *joints[FTPARTS_JOINT_NUM_MAX];

    FTModelPartStatus modelpart_status[FTPARTS_JOINT_NUM_MAX - nFTPartsJointCommonStart]; // -1 = hidden, 0 and up = draw model part ID
    FTTexturePartStatus texturepart_status[2];

    FTData *data;
    FTAttributes *attr;

    void **figatree;                // Main animation bank?
    void **figatree_heap;           // Load animations into this?

    void (*proc_update)(GObj*);
    void (*proc_accessory)(GObj*);
    void (*proc_interrupt)(GObj*);
    void (*proc_physics)(GObj*);
    void (*proc_map)(GObj*);
    void (*proc_slope)(GObj*);   // Slope Contour update
    void (*proc_damage)(GObj*);
    void (*proc_trap)(GObj*);    // Used only by Yoshi Egg?
    void (*proc_shield)(GObj*);
    void (*proc_hit)(GObj*);
    void (*proc_effect)(GObj*);
    void (*proc_lagupdate)(GObj*);
    void (*proc_lagstart)(GObj*);
    void (*proc_lagend)(GObj*);
    void (*proc_status)(GObj*);

    alSoundEffect *p_sfx;
    u16 sfx_id;
    alSoundEffect *p_voice;
    u16 voice_id;
    alSoundEffect *p_loop_sfx;
    u16 loop_sfx_id;

    GMColAnim colanim;

    syColorRGBA fog_color;      // Used only by Master Hand, when in the background on the -Z plane?
    syColorRGBA shade_color;    // Shade colors of character costume

    FTKey key;                  // Automatic input sequence struct

    struct FTAfterImageInfo
    {
        ub8 is_itemswing;
        s8 drawstatus;
        u8 desc_index;
        FTAfterImage desc[3];

    } afterimage;

    union FTFighterVars
    {
        FTMarioFighterVars      mario;
        FTDonkeyFighterVars     donkey;
        FTSamusFighterVars      samus;
        FTLinkFighterVars       link;
        FTCaptainFighterVars    captain;
        FTKirbyFighterVars      kirby;
        FTPikachuFighterVars    pikachu;
        FTPurinFighterVars      purin;
        FTNessFighterVars       ness;
        FTBossFighterVars       boss;

    } fighter_vars;

    s32 hammer_tics;

    union FTStatusVars
    {
        FTCommonStatusVars      common;
        FTMarioStatusVars       mario;
        FTFoxStatusVars         fox;
        FTDonkeyStatusVars      donkey;
        FTSamusStatusVars       samus;
        FTLinkStatusVars        link;
        FTYoshiStatusVars       yoshi;
        FTCaptainStatusVars     captain;
        FTKirbyStatusVars       kirby;
        FTPikachuStatusVars     pikachu;
        FTNessStatusVars        ness;
        FTBossStatusVars        boss;

    } status_vars;

    s32 display_mode;
};

#endif
