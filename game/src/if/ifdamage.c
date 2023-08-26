#include "interface.h"

#include <ft/fighter.h>
#include <gr/ground.h>
#include <gm/battle.h>

extern intptr_t D_NF_00000148;

// 0x8012EBF0 - Width of each digit?
s32 ifPlayer_Damage_DigitWidths[/* */] =
{
    14,  9, 15, 14,
    15, 13, 15, 14,
    15, 15, 17, 20
};

// 0x8012EC20 -> 0x8012EC38 - Player HUD colors
u8 ifPlayer_Damage_DigitColorsR[/* */] = { 0xFF, 0xF0, 0xF0, 0xFF, 0xFF }; // Hope the padding works here
u8 ifPlayer_Damage_DigitColorsG[/* */] = { 0xF0, 0xFF, 0xF0, 0xFF, 0xFF };
u8 ifPlayer_Damage_DigitColorsB[/* */] = { 0xF0, 0xF0, 0xFF, 0xFF, 0xFF };

// 0x8012EC38 - Player HUD position X offsets
s32 ifPlayer_Damage_PositionOffsetsX[/* */] = { 55, 125, 195, 265 };

// 0x8012EC58
s32 ifPlayer_Damage_EmblemOffsetsX[/* */] = { 3, 3, 3, 3 };

// 0x8012EC68
s32 ifPlayer_Damage_EmblemOffsetsY[/* */] = { -3, -3, -3, -3 };

// 0x8012EC78
f32 ifPlayer_Damage_EmblemScales[/* */] = { 1.0F, 1.0F, 1.0F, 1.0F };

// 0x8012EE64 - Offset of twelve digits: numbers 0 through 9, % sign and H.P. text
intptr_t ifPlayer_Damage_DigitSpriteOffsets[/* */] =
{
    0x0148, 0x02D8, 0x0500, 0x0698,
    0x08C0, 0x0A58, 0x0C80, 0x0E18,
    0x1040, 0x1270, 0x1458, 0x15D8
};

extern void *D_ovl2_80130D40[];

s32 D_ovl2_80131590;
s32 D_ovl2_80131594;

ifPlayerDamage gPlayerDamageInterface[GMMATCH_PLAYERS_MAX];

// 0x8010E690
void ifPlayer_Damage_InitInterface(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerDamageInterface); i++)
    {
        if (gPlayerDamageInterface[i].interface_gobj != NULL)
        {
            gPlayerDamageInterface[i].is_display_interface = TRUE;
        }
    }
}

// 0x8010E700 - Gets position of special character (% or H.P.) in damage display character array?
s32 ifPlayer_Damage_GetSpecialArrayID(s32 damage, s8 *digits)
{
    s8 *digits_start = digits;
    s32 digit_update = 1;

    if (damage >= 10)
    {
        do
        {
            digit_update *= 10;
        } 
        while ((damage / digit_update) >= 10);
    }
    do
    {
        *digits++ = damage / digit_update;

        damage %= digit_update;

        digit_update /= 10;

    } 
    while (digit_update != 0);

    return digits - digits_start;
}

// 0x8010E7D4
s32 ifPlayer_Damage_GetPercentArrayID(s32 damage, s8 *digits)
{
    s32 id = ifPlayer_Damage_GetSpecialArrayID(damage, digits);

    digits[id] = 0xA;

    return id + 1;
}

// 0x8010E808
s32 ifPlayer_Damage_GetHitPointsArrayID(s32 damage, s8 *digits)
{
    s32 id = ifPlayer_Damage_GetSpecialArrayID(damage, digits);

    digits[id] = 0xB;

    return id + 1;
}

// 0x8010E83C
s32 func_ovl2_8010E83C(s32 digit_count, u8 *arg1)
{
    s32 i, j = 0;

    for (i = 0; i < digit_count; i++)
    {
        j += ifPlayer_Damage_DigitWidths[arg1[i]];
    }
    return j;
}

// 0x8010E8F4
void ifPlayer_Damage_UpdateDigits(GObj *interface_gobj)
{
    s32 player;
    ifCharacter *ifchar;
    SObj *sobj;
    s32 damage_scale;
    s32 start_damage;
    s32 char_count;
    s32 hitpoints;
    s32 digit_id;
    s32 color_id; // I don't know
    s32 pos_adjust_wait;
    s32 flash_reset_wait;
    s32 unused[2];
    f32 scale;
    s8 digits[4];
    s32 sprite_id;
    f32 offset;
    s32 damage;
    f32 pos_x;

    player = ifGetPlayer(interface_gobj);
    damage = start_damage = gBattleState->player_block[player].stock_damage_all;

    if (damage > 999)
    {
        damage = 999;
    }
    scale = gPlayerDamageInterface[player].scale;
    damage_scale = start_damage - gPlayerDamageInterface[player].damage;

    if (damage_scale == 0)
    {
        if (scale == 1.0F)
        {
            return;
        }
    }
    else if (damage_scale < 0)
    {
        scale = 1.0F;
    }
    else
    {
        gPlayerDamageInterface[player].pos_adjust_wait = 4;
        gPlayerDamageInterface[player].flash_reset_wait = 1;

        scale = (damage_scale / 300.0F) + 1.0F;
    }
    pos_adjust_wait = gPlayerDamageInterface[player].pos_adjust_wait;
    flash_reset_wait = gPlayerDamageInterface[player].flash_reset_wait;

    if (flash_reset_wait != 0)
    {
        color_id = GMMATCH_PLAYERS_MAX;
    }
    else color_id = player;

    if (gBattleState->player_block[player].character_kind == Ft_Kind_MasterHand)
    {
        hitpoints = 300 - damage;

        if (hitpoints < 0)
        {
            hitpoints = 0;
        }
        gPlayerDamageInterface[player].char_display_count = char_count = ifPlayer_Damage_GetHitPointsArrayID(hitpoints, digits);
    }
    else gPlayerDamageInterface[player].char_display_count = char_count = ifPlayer_Damage_GetPercentArrayID(damage, digits);

    pos_x = (func_ovl2_8010E83C(char_count, digits) * scale * 0.5F);

    pos_x = D_ovl2_80131580.ifdamage_pos_x[player] + pos_x;

    if ((scale > 1.0F) && (pos_adjust_wait == 0))
    {
        scale -= 0.05F;

        if (scale < 1.0F)
        {
            scale = 1.0F;
        }
    }
    digit_id = char_count - 1;

    sobj = SObjGetStruct(interface_gobj)->unk_sobj_0x8;

    while (sobj != NULL)
    {
        if (digit_id < 0)
        {
            sobj->sprite.attr |= SP_HIDDEN;
        }
        else
        {
            sprite_id = digits[digit_id];
            ifchar = sobj->sobj_user_data;

            ifchar->image_id = sprite_id;

            offset = ifPlayer_Damage_DigitWidths[sprite_id] * scale;

            ifchar->pos.x = (pos_x - (offset * 0.5F));
            ifchar->pos.y = D_ovl2_80131580.ifdamage_pos_y;

            pos_x -= offset;

            sobj->sprite.attr &= ~SP_HIDDEN;
        }
        sobj = sobj->unk_sobj_0x8;

        digit_id--;
    }
    if (pos_adjust_wait > 0)
    {
        pos_adjust_wait--;
    }
    if (flash_reset_wait > 0)
    {
        flash_reset_wait--;
    }
    gPlayerDamageInterface[player].damage = start_damage;
    gPlayerDamageInterface[player].scale = scale;
    gPlayerDamageInterface[player].color_id = color_id;

    gPlayerDamageInterface[player].pos_adjust_wait = pos_adjust_wait;
    gPlayerDamageInterface[player].flash_reset_wait = flash_reset_wait;
}

// 0x8010EC50
void ifPlayer_Damage_UpdateAnim(GObj *interface_gobj)
{
    s32 player;
    s32 char_id;
    s32 random;
    s32 modulo;
    s32 i, j;
    ifCharacter *ifchar;
    SObj *sobj;

    player = ifGetPlayer(interface_gobj);

    if (gPlayerDamageInterface[player].break_anim_frame < 0x13)
    {
        modulo = gPlayerDamageInterface[player].break_anim_frame / 6;

        if (!(gPlayerDamageInterface[player].break_anim_frame - modulo * 6))
        {
            char_id = gPlayerDamageInterface[player].char_display_count - modulo;

            if (char_id > 0)
            {
                random = lbRandom_GetIntRange(char_id);

                for (i = j = 0; i < gPlayerDamageInterface[player].char_display_count; i++)
                {
                    if (gPlayerDamageInterface[player].chars[i].is_lock_movement == FALSE)
                    {
                        if (j == random)
                        {
                            break;
                        }
                        else j++;
                    }
                }
                gPlayerDamageInterface[player].chars[i].is_lock_movement = TRUE;
            }
        }
        gPlayerDamageInterface[player].break_anim_frame++;
    }
    sobj = SObjGetStruct(interface_gobj)->unk_sobj_0x8;

    while (sobj != NULL)
    {
        if (!(sobj->sprite.attr & SP_HIDDEN))
        {
            ifchar = sobj->sobj_user_data;

            if (ifchar->is_lock_movement != FALSE)
            {
                ifchar->vel.y++;

                ifchar->pos.x += ifchar->vel.x;
                ifchar->pos.y += ifchar->vel.y;
            }
        }
        sobj = sobj->unk_sobj_0x8;
    }
}

// 0x8010EE18
void func_ovl2_8010EE18(GObj *interface_gobj)
{
    s32 player = ifGetPlayer(interface_gobj);

    if (gBattleState->player_block[player].stock_count == -1)
    {
        if (gPlayerDamageInterface[player].dead_stopupdate_wait != 0)
        {
            if (gPlayerDamageInterface[player].is_update_anim != FALSE)
            {
                ifPlayer_Damage_UpdateAnim(interface_gobj);
            }
            gPlayerDamageInterface[player].dead_stopupdate_wait--;
        }
    }
    else if (gPlayerDamageInterface[player].is_update_anim != FALSE)
    {
        ifPlayer_Damage_UpdateAnim(interface_gobj);
    }
    else ifPlayer_Damage_UpdateDigits(interface_gobj);
}

// 0x8010EEFC
void func_ovl2_8010EEFC(GObj *interface_gobj)
{
    f32 pos_x;
    f32 scale;
    f32 pos_y;
    f32 damage_scale;
    s32 player;
    s32 color_id;
    u8 color_r;
    u8 color_g;
    u8 color_b;
    SObj *sobj, *sub_sobj;
    ifCharacter *ifchar;

    sobj = SObjGetStruct(interface_gobj);

    func_ovl0_800CC118(gDisplayListHead, sobj);
    func_ovl0_800CC818(gDisplayListHead, sobj);

    func_ovl0_800CCED8(&sobj->sprite);

    player = ifGetPlayer(interface_gobj);

    if ((gPlayerDamageInterface[player].is_display_interface != FALSE) && ((gBattleState->player_block[player].stock_count >= 0) || (gPlayerDamageInterface[player].dead_stopupdate_wait != 0)))
    {
        color_id = gPlayerDamageInterface[player].color_id;
        scale = gPlayerDamageInterface[player].scale;

        if (color_id == GMMATCH_PLAYERS_MAX)
        {
            color_r = ifPlayer_Damage_DigitColorsR[color_id];
            color_g = ifPlayer_Damage_DigitColorsG[color_id];
            color_b = ifPlayer_Damage_DigitColorsB[color_id];
        }
        else
        {
            damage_scale = 1.0F - (gPlayerDamageInterface[player].damage / 300.0F);

            if (damage_scale < 0.0F)
            {
                damage_scale = 0.0F;
            }
            color_r = (s32)((ifPlayer_Damage_DigitColorsR[color_id] - 0x64) * damage_scale) + 0x64;
            color_g = (s32)((ifPlayer_Damage_DigitColorsG[color_id] - 0x14) * damage_scale) + 0x14;
            color_b = (s32)((ifPlayer_Damage_DigitColorsB[color_id] - 0x14) * damage_scale) + 0x14;
        }
        sobj = sobj->unk_sobj_0x8;
        ifchar = sobj->sobj_user_data;

        sobj->sprite = *(Sprite*) ((uintptr_t)D_ovl2_80130D40[2] + (intptr_t)ifPlayer_Damage_DigitSpriteOffsets[ifchar->image_id]);

        sobj->pos.x = (ifchar->pos.x - (sobj->sprite.width * 0.5F * scale));
        sobj->pos.y = (ifchar->pos.y - (sobj->sprite.height * 0.5F * scale));

        sobj->sprite.scalex = scale;
        sobj->sprite.scaley = scale;

        sobj->sprite.red = color_r;
        sobj->sprite.green = color_g;
        sobj->sprite.blue = color_b;

        func_ovl0_800CC118(gDisplayListHead, sobj);

        if (color_id == GMMATCH_PLAYERS_MAX)
        {
            gDPSetCombineLERP(gDisplayListHead[0]++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
        }
        func_ovl0_800CC818(gDisplayListHead, sobj);

        sobj = sobj->unk_sobj_0x8;

        while (sobj != NULL)
        {
            if (!(sobj->sprite.attr & SP_HIDDEN))
            {
                ifchar = sobj->sobj_user_data;

                sobj->sprite = *(Sprite*) ((uintptr_t)D_ovl2_80130D40[2] + (intptr_t)ifPlayer_Damage_DigitSpriteOffsets[ifchar->image_id]);

                pos_x = ifchar->pos.x - (sobj->sprite.width * 0.5F * scale);
                pos_y = ifchar->pos.y - (sobj->sprite.height * 0.5F * scale);

                if ((scale == 1.0F) && (gPlayerDamageInterface[player].is_update_anim == FALSE))
                {
                    sobj->pos.x = (s32)pos_x;
                    sobj->pos.y = (s32)pos_y;
                }
                else
                {
                    sobj->pos.x = pos_x;
                    sobj->pos.y = pos_y;
                }
                sobj->sprite.scalex = sobj->sprite.scaley = scale;

                func_ovl0_800CC818(gDisplayListHead, sobj);
            }
            sobj = sobj->unk_sobj_0x8;
        }
        func_ovl0_800CCEAC();
    }
}

// 0x8010F334
void func_ovl2_8010F334(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(ifPlayer_Damage_DigitSpriteOffsets); i++)
    {
        ((Sprite*) ((uintptr_t)D_ovl2_80130D40[2] + (intptr_t)ifPlayer_Damage_DigitSpriteOffsets[i]))->attr = SP_TEXSHUF | SP_TRANSPARENT;
    }
}

// 0x8010F3A0
void func_ovl2_8010F3A0(void)
{
    D_ovl2_80131580.ifdamage_pos_x = ifPlayer_Damage_PositionOffsetsX;
    D_ovl2_80131580.ifdamage_pos_y = 0xD2;
}

// 0x8010F3C0
void func_ovl2_8010F3C0(void)
{
    ftStruct *fp;
    ftSprites *ft_sprites;
    GObj *interface_gobj;
    SObj *sobj;
    s32 player;
    s32 emblem;

    func_ovl2_8010F334();

    for (player = 0; player < ARRAY_COUNT(gPlayerDamageInterface); player++)
    {
        if (gBattleState->player_block[player].player_kind == 2)
        {
            gPlayerDamageInterface[player].interface_gobj = NULL;
        }
        else
        {
            interface_gobj = omMakeGObjCommon(omGObj_Kind_Interface, NULL, 0xB, 0x80000000U);

            gPlayerDamageInterface[player].interface_gobj = interface_gobj;

            func_80009DF4(interface_gobj, func_ovl2_8010EEFC, 0x17, 0x80000000U, -1);

            fp = ftGetStruct(gBattleState->player_block[player].fighter_gobj);

            ft_sprites = fp->attributes->sprites;

            if ((ft_sprites != NULL) && (ft_sprites->emblem != NULL))
            {
                sobj = func_ovl0_800CCFDC(interface_gobj, ft_sprites->emblem);

                sobj->pos.x = (s32)(((f32)D_ovl2_80131580.ifdamage_pos_x[player] - ((f32)sobj->sprite.width  * ifPlayer_Damage_EmblemScales[player] * 0.5F)) + (f32)ifPlayer_Damage_EmblemOffsetsX[player]);
                sobj->pos.y = (s32)(((f32)D_ovl2_80131580.ifdamage_pos_y         - ((f32)sobj->sprite.height * ifPlayer_Damage_EmblemScales[player] * 0.5F)) + (f32)ifPlayer_Damage_EmblemOffsetsY[player]);

                sobj->sprite.scalex = sobj->sprite.scaley = ifPlayer_Damage_EmblemScales[player];

                emblem = gBattleState->player_block[player].emblem_color_index;

                sobj->sprite.red = gGroundInfo->emblem_colors[emblem].r;
                sobj->sprite.green = gGroundInfo->emblem_colors[emblem].g;
                sobj->sprite.blue = gGroundInfo->emblem_colors[emblem].b;

                sobj->sprite.attr = SP_TEXSHUF | SP_TRANSPARENT;
            }
            else
            {
                func_80009614(interface_gobj, NULL)->sprite.attr = SP_HIDDEN;
            }
            func_ovl0_800CCFDC(interface_gobj, (uintptr_t)D_ovl2_80130D40[2] + (intptr_t)&D_NF_00000148)->sobj_user_data = &gPlayerDamageInterface[player].chars[0];
            func_ovl0_800CCFDC(interface_gobj, (uintptr_t)D_ovl2_80130D40[2] + (intptr_t)&D_NF_00000148)->sobj_user_data = &gPlayerDamageInterface[player].chars[1];
            func_ovl0_800CCFDC(interface_gobj, (uintptr_t)D_ovl2_80130D40[2] + (intptr_t)&D_NF_00000148)->sobj_user_data = &gPlayerDamageInterface[player].chars[2];
            func_ovl0_800CCFDC(interface_gobj, (uintptr_t)D_ovl2_80130D40[2] + (intptr_t)&D_NF_00000148)->sobj_user_data = &gPlayerDamageInterface[player].chars[3];

            // The above functions should all return SObj*

            gPlayerDamageInterface[player].damage = gBattleState->player_block[player].stock_damage_all;
            gPlayerDamageInterface[player].pos_adjust_wait = 0;
            gPlayerDamageInterface[player].flash_reset_wait = 0;
            gPlayerDamageInterface[player].scale = 1.04F;
            gPlayerDamageInterface[player].is_update_anim = FALSE;
            gPlayerDamageInterface[player].dead_stopupdate_wait = 180;
            gPlayerDamageInterface[player].is_display_interface = FALSE;

            interface_gobj->user_data = (void*)player; // Cast is probably redundant but I don't want any compilers screaming at me

            func_ovl2_8010EE18(interface_gobj);
            omAddGObjCommonProc(interface_gobj, func_ovl2_8010EE18, 1, 0);
        }
    }
}

// 0x8010F76C
void ifPlayer_Damage_StartBreakAnim(ftStruct *fp)
{
    s32 player = fp->player;
    s32 i;

    for (i = 0; i < gPlayerDamageInterface[player].char_display_count; i++)
    {
        gPlayerDamageInterface[player].chars[i].vel.x = (lbRandom_GetFloat() * 2) + (-1.0F);
        gPlayerDamageInterface[player].chars[i].vel.y = -10.0F;

        gPlayerDamageInterface[player].chars[i].is_lock_movement = FALSE;
    }
    gPlayerDamageInterface[player].break_anim_frame = 0;
    gPlayerDamageInterface[player].is_update_anim = TRUE;
}

// 0x8010F840
void ifPlayer_Damage_StopBreakAnim(ftStruct *fp)
{
    s32 player = fp->player;

    gPlayerDamageInterface[player].is_update_anim = FALSE;
    gPlayerDamageInterface[player].scale = 1.04F;
}
