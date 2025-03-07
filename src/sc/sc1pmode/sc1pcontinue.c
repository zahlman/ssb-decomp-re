#include <ft/fighter.h>
#include <if/interface.h>
#include <mn/menu.h>
#include <sc/scene.h>
#include <sys/video.h>

extern void scManagerFuncDraw();
extern void syRdpSetViewport(Vp *vp, f32 arg1, f32 arg2, f32 arg3, f32 arg4);

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern f32 dSCSubsysFighterScales[/* */];

extern uintptr_t D_NF_0000004F;                         // 0x0000004F
extern uintptr_t D_NF_00000050;							// 0x00000050
extern uintptr_t D_NF_00000051;							// 0x00000051
extern uintptr_t D_NF_000000A4;							// 0x000000A4
extern uintptr_t D_NF_00000025;							// 0x00000025

// // // // // // // // // // // //
//                               //
//             MACROS            //
//                               //
// // // // // // // // // // // //

#define sc1PContinueCheckGetOptionButtonInput(is_button, mask) \
mnCommonCheckGetOptionButtonInput(sSC1PContinueOptionChangeWait, is_button, mask)

#define sc1PContinueCheckGetOptionStickInputUD(stick_range, min, b) \
mnCommonCheckGetOptionStickInputUD(sSC1PContinueOptionChangeWait, stick_range, min, b)

#define sc1PContinueCheckGetOptionStickInputLR(stick_range, min, b) \
mnCommonCheckGetOptionStickInputLR(sSC1PContinueOptionChangeWait, stick_range, min, b)

#define sc1PContinueSetOptionChangeWaitP(stick_range) \
(sSC1PContinueOptionChangeWait = (160 - (stick_range)) / 5)

#define sc1PContinueSetOptionChangeWaitN(stick_range) \
(sSC1PContinueOptionChangeWait = ((stick_range) + 160) / 5)

// // // // // // // // // // // //
//                               //
//   GLOBAL / STATIC VARIABLES   //
//                               //
// // // // // // // // // // // //

// 0x801342F0
s32 sSC1PContinuePad0x801342F0[2];

// 0x801342F8
void *sSC1PContinueFigatreeHeap;

// 0x801342FC
s32 sSC1PContinueTotalTimeTics;

// 0x80134300
GObj *sSC1PContinueFighterGObj;

// 0x80134304
GObj *sSC1PContinueContinueGObj;

// 0x80134308
GObj *sSC1PContinueShadowGObj;

// 0x8013430C
GObj *sSC1PContinueSpotlightGObj;

// 0x80134310
GObj *sSC1PContinueCursorGObj;

// 0x80134314
GObj *sSC1PContinueOptionGObj;

// 0x80134318
GObj *sSC1PContinueRoomGObj;

// 0x8013431C
s32 sSC1PContinueRoomFadeInAlpha;

// 0x80134320
GObj *sSC1PContinueRoomFadeInGObj;

// 0x80134324
s32 sSC1PContinueSpotlightFadeAlpha;

// 0x80134328
GObj *sSC1PContinueSpotlightFadeGObj;

// 0x8013432C
s32 sSC1PContinueRoomFadeOutAlpha;

// 0x80134330
GObj *sSC1PContinueRoomFadeOutGObj;

// 0x80134334
GObj *sSC1PContinueGameOverGObj;

// 0x80134338
s32 sSC1PContinueOptionSelect;

// 0x8013433C
s32 sSC1PContinueStatus;

// 0x80134340
f32 sSC1PContinueGameOverFadeOutScale;

// 0x80134344
f32 sSC1PContinueGameOverColorStep;

// 0x80134348
FTDemoDesc sSC1PContinueFighterDemoDesc;

// 0x80134354 - ??? set but never used?
s32 D_ovl55_80134354;

// 0x80134358
s32 sSC1PContinueOptionNoGameOverInputWait;

// 0x8013435C
s32 sSC1PContinueOptionYesRetryTic;

// 0x80134360
s32 sSC1PContinueIsSelectContinue;

// 0x80134364
s32 sSC1PContinueOptionNoGameOverAutoWait;

// 0x80134368
GObj *sSC1PContinueScoreGObj;

// 0x8013436C
s32 sSC1PContinueOptionChangeWait;

// 0x80134370
LBFileNode sSC1PContinueStatusBuffer[48];

// 0x801344F0
LBFileNode sSC1PContinueForceStatusBuffer[7];

// 0x80134528
void *sSC1PContinueFiles[5];

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

// 0x80134160
u32 dSC1PContinueFileIDs[/* */] =
{
    &D_NF_0000004F,
    &D_NF_00000051,
    &D_NF_00000025,
    &D_NF_000000A4,
    &D_NF_00000050
};

// 0x80134178
Lights1 dSC1PContinueLights11 = gdSPDefLights1(0x20, 0x20, 0x20, 0xFF, 0xFF, 0xFF, 0x14, 0x14, 0x14);

// 0x80134190
Lights1 dSC1PContinueLights12 = gdSPDefLights1(0x20, 0x20, 0x20, 0xFF, 0xFF, 0xFF, 0x00, 0x14, 0x00);

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80131B00
void sc1PContinueFuncLights(Gfx **dls)
{
    gSPSetGeometryMode(dls[0]++, G_LIGHTING);

    ftDisplayLightsDrawReflect(dls, scSubsysFighterGetLightAngleX(), scSubsysFighterGetLightAngleY());
}

// 0x80131B58
s32 sc1PContinueGetPowerOf(s32 base, s32 exp)
{
	s32 raised = base;
	s32 i;

	if (exp == 0)
	{
		return 1;
	}
	i = exp;

	while (i > 1)
	{
		i--;
		raised *= base;
	}
	return raised;
}

// 0x80131BF8
void sc1PContinueScoreDigitInitSprite(SObj *sobj)
{
    sobj->sprite.attr &= ~SP_FASTCOPY;
    sobj->sprite.attr |= SP_TRANSPARENT;

    sobj->envcolor.r = 0x00;
    sobj->envcolor.g = 0x00;
    sobj->envcolor.b = 0x00;

    sobj->sprite.red = 0xFF;
    sobj->sprite.green = 0xEC;
    sobj->sprite.blue = 0x00;
}

// 0x80131C30
s32 sc1PContinueGetScoreDigitCount(s32 points, s32 digit_count_max)
{
    s32 digit_count_curr = digit_count_max;

    while (digit_count_curr > 0)
    {
        s32 digit = (sc1PContinueGetPowerOf(10, digit_count_curr - 1) != 0) ? points / sc1PContinueGetPowerOf(10, digit_count_curr - 1) : 0;

        if (digit != 0)
        {
            return digit_count_curr;
        }
        else digit_count_curr--;
    }
    return 0;
}

// 0x80131CDC
Sprite* sc1PContinueScoreDigitGetSprite(s32 digit)
{
    // 0x80134534
    intptr_t offsets[/* */] =
    {
        &lSC1PStageClearScoreDigit0,
        &lSC1PStageClearScoreDigit1,
        &lSC1PStageClearScoreDigit2,
        &lSC1PStageClearScoreDigit3,
        &lSC1PStageClearScoreDigit4,
        &lSC1PStageClearScoreDigit5,
        &lSC1PStageClearScoreDigit6,
        &lSC1PStageClearScoreDigit7,
        &lSC1PStageClearScoreDigit8,
        &lSC1PStageClearScoreDigit9
    };
    return lbRelocGetFileData(Sprite*, sSC1PContinueFiles[3], offsets[digit]);
}

// 0x80131D40
void sc1PContinueMakeScoreDigits
(
    GObj *gobj,
    s32 points,
    f32 x,
    f32 y,
    f32 offset_x,
    s32 sub,
    s32 digit_count,
    sb32 is_fixed_digit_count
)
{
    SObj *sobj;
    f32 calc_x;
    s32 digit;
    s32 i;

    if (points < 0)
    {
        points = 0;
    }
    sobj = lbCommonMakeSObjForGObj(gobj, sc1PContinueScoreDigitGetSprite(points % 10));
    sc1PContinueScoreDigitInitSprite(sobj);

    calc_x = (sub != 0) ? x - sub : x - (sobj->sprite.width + offset_x);

    sobj->pos.x = calc_x;
    sobj->pos.y = y;

    for (i = 1; i < ((is_fixed_digit_count != FALSE) ? digit_count : sc1PContinueGetScoreDigitCount(points, digit_count)); i++)
    {
        digit = (sc1PContinueGetPowerOf(10, i) != 0) ? points / sc1PContinueGetPowerOf(10, i) : 0;

        sobj = lbCommonMakeSObjForGObj(gobj, sc1PContinueScoreDigitGetSprite(digit % 10));
        sc1PContinueScoreDigitInitSprite(sobj);

        calc_x = (sub != 0) ? calc_x - sub : calc_x - (sobj->sprite.width + offset_x);

        sobj->pos.x = calc_x;
        sobj->pos.y = y;
    }
}

// 0x80131F98
void sc1PContinueMakeScoreDisplay(s32 points)
{
    GObj *gobj;
    SObj *sobj;

    sSC1PContinueScoreGObj = gobj = gcMakeGObjSPAfter(0, NULL, 20, GOBJ_PRIORITY_DEFAULT);
    gcAddGObjDisplay(gobj, lbCommonDrawSObjAttr, 28, GOBJ_PRIORITY_DEFAULT, ~0);

    sobj = lbCommonMakeSObjForGObj(gobj, lbRelocGetFileData(Sprite*, sSC1PContinueFiles[1], &lSC1PContinueTextScore));

    sobj->sprite.attr &= ~SP_FASTCOPY;
    sobj->sprite.attr |= SP_TRANSPARENT;

    sobj->envcolor.r = 0xFF;
    sobj->envcolor.g = 0x00;
    sobj->envcolor.b = 0x00;

    sobj->sprite.red = 0xFF;
    sobj->sprite.green = 0xC8;
    sobj->sprite.blue = 0x00;

    sobj->pos.x = 90.0F;
    sobj->pos.y = 200.0F;

    sc1PContinueMakeScoreDigits(gobj, points, 295.0F, 197.0F, 0.0F, 16, 8, TRUE);
}

// 0x80132094 - Unused?
void func_ovl55_80132094(void)
{
    return;
}

// 0x8013209C
void sc1PContinueSetFighterScale(GObj *gobj, s32 fkind)
{
    DObjGetStruct(gobj)->scale.vec.f.x = dSCSubsysFighterScales[fkind];
    DObjGetStruct(gobj)->scale.vec.f.y = dSCSubsysFighterScales[fkind];
    DObjGetStruct(gobj)->scale.vec.f.z = dSCSubsysFighterScales[fkind];
}

// 0x801320D4
void sc1PContinueMakeFighter(s32 fkind)
{
    GObj *fighter_gobj;
    FTCreateDesc ft_desc;

    ft_desc = dFTManagerDefaultFighterDesc;

    ft_desc.fkind = fkind;

    ft_desc.pos.x = 90.0F;

    ft_desc.costume = sSC1PContinueFighterDemoDesc.costume;
    ft_desc.shade = sSC1PContinueFighterDemoDesc.shade;
    ft_desc.figatree_heap = sSC1PContinueFigatreeHeap;

    ft_desc.pos.y = 2070.0F;
    ft_desc.pos.z = 0.0F;

    sSC1PContinueFighterGObj = fighter_gobj = ftManagerMakeFighter(&ft_desc);

    scSubsysFighterSetStatus(fighter_gobj, 0x10009);
    sc1PContinueSetFighterScale(fighter_gobj, sSC1PContinueFighterDemoDesc.fkind);
}

// 0x801321A8
void sc1PContinueRoomFadeOutFuncDisplay(GObj *gobj)
{
    if (sSC1PContinueRoomFadeOutAlpha < 0xFF)
    {
        sSC1PContinueRoomFadeOutAlpha += 5;

        if (sSC1PContinueRoomFadeOutAlpha > 0xFF)
        {
            sSC1PContinueRoomFadeOutAlpha = 0xFF;
        }
    }
    gDPPipeSync(gSYTaskmanDLHeads[0]++);
    gDPSetCycleType(gSYTaskmanDLHeads[0]++, G_CYC_1CYCLE);
    gDPSetPrimColor(gSYTaskmanDLHeads[0]++, 0, 0, 0x00, 0x00, 0x00, sSC1PContinueRoomFadeOutAlpha);
    gDPSetCombineMode(gSYTaskmanDLHeads[0]++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode(gSYTaskmanDLHeads[0]++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPFillRectangle(gSYTaskmanDLHeads[0]++, 10, 10, 310, 230);
    gDPPipeSync(gSYTaskmanDLHeads[0]++);
    gDPSetRenderMode(gSYTaskmanDLHeads[0]++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

// 0x801322DC
void sc1PContinueMakeRoomFadeOut(void)
{
    GObj *gobj;

    sSC1PContinueRoomFadeOutAlpha = 0x00;
    sSC1PContinueRoomFadeOutGObj = gobj = gcMakeGObjSPAfter(0, NULL, 23, GOBJ_PRIORITY_DEFAULT);
    gcAddGObjDisplay(gobj, sc1PContinueRoomFadeOutFuncDisplay, 32, GOBJ_PRIORITY_DEFAULT, ~0);
}

// 0x80132338
void sc1PContinueRoomFadeInFuncDisplay(GObj *gobj)
{
    if (sSC1PContinueRoomFadeInAlpha > 0x00)
    {
        sSC1PContinueRoomFadeInAlpha -= 0x05;

        if (sSC1PContinueRoomFadeInAlpha < 0x00)
        {
            sSC1PContinueRoomFadeInAlpha = 0x00;
        }
    }
    gDPPipeSync(gSYTaskmanDLHeads[0]++);
    gDPSetCycleType(gSYTaskmanDLHeads[0]++, G_CYC_1CYCLE);
    gDPSetPrimColor(gSYTaskmanDLHeads[0]++, 0, 0, 0x00, 0x00, 0x00, sSC1PContinueRoomFadeInAlpha);
    gDPSetCombineMode(gSYTaskmanDLHeads[0]++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode(gSYTaskmanDLHeads[0]++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPFillRectangle(gSYTaskmanDLHeads[0]++, 10, 10, 310, 230);
    gDPPipeSync(gSYTaskmanDLHeads[0]++);
    gDPSetRenderMode(gSYTaskmanDLHeads[0]++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

// 0x80132460
void sc1PContinueMakeRoomFadeIn(void)
{
    GObj *gobj;

    sSC1PContinueRoomFadeInAlpha = 0xFF;
    sSC1PContinueRoomFadeInGObj = gobj = gcMakeGObjSPAfter(0, NULL, 17, GOBJ_PRIORITY_DEFAULT);
    gcAddGObjDisplay(gobj, sc1PContinueRoomFadeInFuncDisplay, 26, GOBJ_PRIORITY_DEFAULT, ~0);
}

// 0x801324C0
void sc1PContinueSpotlightFadeFuncDisplay(GObj *gobj)
{
    if (sSC1PContinueSpotlightFadeAlpha > 0x00)
    {
        sSC1PContinueSpotlightFadeAlpha -= 0x05;

        if (sSC1PContinueSpotlightFadeAlpha < 0x00)
        {
            sSC1PContinueSpotlightFadeAlpha = 0x00;
        }
    }
    gDPPipeSync(gSYTaskmanDLHeads[0]++);
    gDPSetCycleType(gSYTaskmanDLHeads[0]++, G_CYC_1CYCLE);
    gDPSetPrimColor(gSYTaskmanDLHeads[0]++, 0, 0, 0x00, 0x00, 0x00, sSC1PContinueSpotlightFadeAlpha);
    gDPSetCombineMode(gSYTaskmanDLHeads[0]++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode(gSYTaskmanDLHeads[0]++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPFillRectangle(gSYTaskmanDLHeads[0]++, 10, 10, 310, 230);
    gDPPipeSync(gSYTaskmanDLHeads[0]++);
    gDPSetRenderMode(gSYTaskmanDLHeads[0]++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

// 0x801325E8
void sc1PContinueMakeSpotlightFade(void)
{
    GObj *gobj;

    sSC1PContinueSpotlightFadeAlpha = 0xFF;
    sSC1PContinueSpotlightFadeGObj = gobj = gcMakeGObjSPAfter(0, NULL, 22, GOBJ_PRIORITY_DEFAULT);
    gcAddGObjDisplay(gobj, sc1PContinueSpotlightFadeFuncDisplay, 31, GOBJ_PRIORITY_DEFAULT, ~0);
}

// 0x80132648
void sc1PContinueMakeRoom(void)
{
    GObj *gobj;
    SObj *sobj;

    sSC1PContinueRoomGObj = gobj = gcMakeGObjSPAfter(0, NULL, 19, GOBJ_PRIORITY_DEFAULT);

    gcAddGObjDisplay(gobj, lbCommonDrawSObjAttr, 29, GOBJ_PRIORITY_DEFAULT, ~0);
    sobj = lbCommonMakeSObjForGObj(gobj, lbRelocGetFileData(Sprite*, sSC1PContinueFiles[0], &lSC1PContinueRoom));

    sobj->pos.x = 30.0F;
    sobj->pos.y = 28.0F;
}

// 0x801326D4
void sc1PContinueMakeSpotlight(void)
{
    GObj *gobj;
    SObj *sobj;

    sSC1PContinueShadowGObj = gobj = gcMakeGObjSPAfter(0, NULL, 21, GOBJ_PRIORITY_DEFAULT);
    gcAddGObjDisplay(gobj, lbCommonDrawSObjAttr, 30, GOBJ_PRIORITY_DEFAULT, ~0);
    sobj = lbCommonMakeSObjForGObj(gobj, lbRelocGetFileData(Sprite*, sSC1PContinueFiles[0], &lSC1PContinueShadow));

    sobj->sprite.attr &= ~SP_FASTCOPY;
    sobj->sprite.attr |= SP_TRANSPARENT;

    sobj->sprite.red = 0xBE;
    sobj->sprite.green = 0xBE;
    sobj->sprite.blue = 0xFF;

    sobj->pos.x = 80.0F;
    sobj->pos.y = 156.0F;

    sSC1PContinueSpotlightGObj = gobj = gcMakeGObjSPAfter(0, NULL, 21, GOBJ_PRIORITY_DEFAULT);
    gcAddGObjDisplay(gobj, lbCommonDrawSObjAttr, 30, GOBJ_PRIORITY_DEFAULT, ~0);
    sobj = lbCommonMakeSObjForGObj(gobj, lbRelocGetFileData(Sprite*, sSC1PContinueFiles[0], &lSC1PContinueSpotlight));

    sobj->sprite.attr &= ~SP_FASTCOPY;
    sobj->sprite.attr |= SP_TRANSPARENT;

    sobj->sprite.red = 0xBE;
    sobj->sprite.green = 0xBE;
    sobj->sprite.blue = 0xFF;

    sobj->pos.x = 80.0F;
    sobj->pos.y = 28.0F;
}

// 0x80132824
void sc1PContinueMakeContinue(void)
{
    GObj *gobj;
    SObj *sobj;

    sSC1PContinueContinueGObj = gobj = gcMakeGObjSPAfter(0, NULL, 20, GOBJ_PRIORITY_DEFAULT);
    gcAddGObjDisplay(gobj, lbCommonDrawSObjAttr, 28, GOBJ_PRIORITY_DEFAULT, ~0);
    sobj = lbCommonMakeSObjForGObj(gobj, lbRelocGetFileData(Sprite*, sSC1PContinueFiles[0], &lSC1PContinueTextContinue));

    sobj->sprite.attr &= ~SP_FASTCOPY;
    sobj->sprite.attr |= SP_TRANSPARENT;

    sobj->envcolor.r = 0x00;
    sobj->envcolor.g = 0x00;
    sobj->envcolor.b = 0x00;

    sobj->sprite.red = 0xFF;
    sobj->sprite.green = 0xFF;
    sobj->sprite.blue = 0xFF;

    sobj->pos.x = 64.0F;
    sobj->pos.y = 64.0F;
}

// 0x801328D8
void SC1PContinueOptionSetHighlightColors(GObj *gobj, s32 option)
{
    SObj *sobj;

    // 0x801341D0
    SYColorRGBPair not = { { 0x00, 0x00, 0x00 }, { 0xFF, 0x00, 0x00 } };

    // 0x801341D8
    SYColorRGBPair highlight = { { 0x00, 0x00, 0x00 }, { 0x4C, 0x47, 0x5F } };

    SYColorRGBPair *color;

    sobj = SObjGetStruct(gobj);

    color = (option == nSC1PContinueOptionYes) ? &not : &highlight;

    sobj->envcolor.r = color->prim.r;
    sobj->envcolor.g = color->prim.g;
    sobj->envcolor.b = color->prim.b;

    sobj->sprite.red = color->env.r;
    sobj->sprite.green = color->env.g;
    sobj->sprite.blue = color->env.b;

    sobj = SObjGetStruct(gobj)->next;

    color = (option == nSC1PContinueOptionNo) ? &not : &highlight;

    sobj->envcolor.r = color->prim.r;
    sobj->envcolor.g = color->prim.g;
    sobj->envcolor.b = color->prim.b;

    sobj->sprite.red = color->env.r;
    sobj->sprite.green = color->env.g;
    sobj->sprite.blue = color->env.b;
}

// 0x801329AC
void SC1PContinueOptionProcUpdate(GObj *gobj)
{
    SC1PContinueOptionSetHighlightColors(gobj, sSC1PContinueOptionSelect);
}

// 0x801329D0
void sc1PContinueMakeOptions(void)
{
    GObj *gobj;
    SObj *sobj;

    sSC1PContinueOptionGObj = gobj = gcMakeGObjSPAfter(0, NULL, 20, GOBJ_PRIORITY_DEFAULT);
    gcAddGObjDisplay(gobj, lbCommonDrawSObjAttr, 28, GOBJ_PRIORITY_DEFAULT, ~0);
    gcAddGObjProcess(gobj, SC1PContinueOptionProcUpdate, nGCProcessKindFunc, 1);

    sobj = lbCommonMakeSObjForGObj(gobj, lbRelocGetFileData(Sprite*, sSC1PContinueFiles[0], &lSC1PContinueTextYes));

    sobj->sprite.attr &= ~SP_FASTCOPY;
    sobj->sprite.attr |= SP_TRANSPARENT;

    sobj->pos.x = 84.0F;
    sobj->pos.y = 129.0F;

    sobj = lbCommonMakeSObjForGObj(gobj, lbRelocGetFileData(Sprite*, sSC1PContinueFiles[0], &lSC1PContinueTextNo));

    sobj->sprite.attr &= ~SP_FASTCOPY;
    sobj->sprite.attr |= SP_TRANSPARENT;

    sobj->pos.x = 189.0F;
    sobj->pos.y = 129.0F;

    SC1PContinueOptionSetHighlightColors(gobj, sSC1PContinueOptionSelect);
}

// 0x80132AE8
void sc1PContinueCursorSetPosition(GObj *gobj, s32 option)
{
    SObj *sobj = SObjGetStruct(gobj);

    if (option == nSC1PContinueOptionYes)
    {
        sobj->pos.x = 76.0F;
        sobj->pos.y = 120.0F;
    }
    else
    {
        sobj->pos.x = 177.0F;
        sobj->pos.y = 120.0F;
    }
}

// 0x80132B2C
void sc1PContinueCursorProcUpdate(GObj *gobj)
{
    sc1PContinueCursorSetPosition(gobj, sSC1PContinueOptionSelect);
}

// 0x80132B50
void sc1PContinueMakeCursor(void)
{
    GObj *gobj;
    SObj *sobj;

    sSC1PContinueCursorGObj = gobj = gcMakeGObjSPAfter(0, NULL, 20, GOBJ_PRIORITY_DEFAULT);

    gcAddGObjDisplay(gobj, lbCommonDrawSObjAttr, 28, GOBJ_PRIORITY_DEFAULT, ~0);
    gcAddGObjProcess(gobj, sc1PContinueCursorProcUpdate, nGCProcessKindFunc, 1);
    sobj = lbCommonMakeSObjForGObj(gobj, lbRelocGetFileData(Sprite*, sSC1PContinueFiles[0], &lSC1PContinueCursor));

    sobj->sprite.attr &= ~SP_FASTCOPY;
    sobj->sprite.attr |= SP_TRANSPARENT;

    sobj->envcolor.r = 0x00;
    sobj->envcolor.g = 0x00;
    sobj->envcolor.b = 0x00;

    sobj->sprite.red = 0xFF;
    sobj->sprite.green = 0x00;
    sobj->sprite.blue = 0x00;

    sc1PContinueCursorSetPosition(gobj, sSC1PContinueOptionSelect);
}

// 0x80132C1C
void sc1PContinueGameOverInitSprites(SObj *sobj)
{
    sobj->sprite.attr &= ~SP_FASTCOPY;
    sobj->sprite.attr |= SP_TRANSPARENT;

    sobj->envcolor.r = 0x1A;
    sobj->envcolor.g = 0x00;
    sobj->envcolor.b = 0xE6;

    sobj->sprite.red = 0xFF;
    sobj->sprite.green = 0xFF;
    sobj->sprite.blue = 0xFF;
}

// 0x80132C58
void sc1PContinueGameOverTextStepColors(GObj *gobj)
{
    SObj *sobj = SObjGetStruct(gobj);

    // 0x801341E0
    f32 values[/* */] = { 26.0F, 0.0F, 230.0F, 255.0F, 255.0F, 255.0F };

    if (sSC1PContinueGameOverColorStep < 1.0F)
    {
        sSC1PContinueGameOverColorStep += F_PCT_TO_DEC(1.0F);

        if (sSC1PContinueGameOverColorStep > 1.0F)
        {
            sSC1PContinueGameOverColorStep = 1.0F;
        }
        while (sobj != NULL)
        {
            sobj->envcolor.r = values[0] * sSC1PContinueGameOverColorStep;
            sobj->envcolor.g = values[1] * sSC1PContinueGameOverColorStep;
            sobj->envcolor.b = values[2] * sSC1PContinueGameOverColorStep;

            sobj->sprite.red = values[3] * sSC1PContinueGameOverColorStep;
            sobj->sprite.green = values[4] * sSC1PContinueGameOverColorStep;
            sobj->sprite.blue = values[5] * sSC1PContinueGameOverColorStep;

            sobj = sobj->next;
        }
    }
}

// 0x8013307C
void sc1PContinueMakeGameOverText(void)
{
    GObj *gobj;
    SObj *sobj;

    // 0x801341F8
    intptr_t letters[/* */] =
    { 
        &lIFCommonAnnounceCommonLetterG,
        &lIFCommonAnnounceCommonLetterA,
        &lIFCommonAnnounceCommonLetterM,
        &lIFCommonAnnounceCommonLetterE,
        &lIFCommonAnnounceCommonLetterO,
        &lIFCommonAnnounceCommonLetterV,
        &lIFCommonAnnounceCommonLetterE,
        &lIFCommonAnnounceCommonLetterR
    };

    // 0x80134218
    f32 positions_x[/* */] = { 30.0F, 60.0F, 95.0F, 133.0F, 166.0F, 200.0F, 230.0F, 254.0F };

    s32 i;

    sSC1PContinueGameOverColorStep = 0.0F;

    sSC1PContinueGameOverGObj = gobj = gcMakeGObjSPAfter(0, NULL, 20, GOBJ_PRIORITY_DEFAULT);
    gcAddGObjDisplay(gobj, lbCommonDrawSObjAttr, 28, GOBJ_PRIORITY_DEFAULT, ~0);
    gcAddGObjProcess(gobj, sc1PContinueGameOverTextStepColors, nGCProcessKindFunc, 1);

    for (i = 0; i < (ARRAY_COUNT(letters) + ARRAY_COUNT(positions_x)) / 2; i++)
    {
        sobj = lbCommonMakeSObjForGObj(gobj, lbRelocGetFileData(Sprite*, sSC1PContinueFiles[2], letters[i]));

        sobj->pos.x = positions_x[i];
        sobj->pos.y = 50.0F;

        sc1PContinueGameOverInitSprites(sobj);
    }
}

// 0x80133210
void sc1PContinueGameOverProcUpdate(GObj *gobj)
{
    SObj *sobj = SObjGetStruct(sSC1PContinueRoomGObj);

    if (sSC1PContinueGameOverFadeOutScale > F_PCT_TO_DEC(1.0F))
    {
        sSC1PContinueGameOverFadeOutScale -= F_PCT_TO_DEC(1.0F);

        if (sSC1PContinueGameOverFadeOutScale < F_PCT_TO_DEC(1.0F))
        {
            sSC1PContinueGameOverFadeOutScale = F_PCT_TO_DEC(1.0F);
        }
        sobj->sprite.scalex = sSC1PContinueGameOverFadeOutScale;
        sobj->sprite.scaley = sSC1PContinueGameOverFadeOutScale;

        sobj->pos.x = 160.0F - ((260.0F * sSC1PContinueGameOverFadeOutScale) / 2);
        sobj->pos.y = 120.0F - ((184.0F * sSC1PContinueGameOverFadeOutScale) / 2);

        DObjGetStruct(sSC1PContinueFighterGObj)->translate.vec.f.y += 3.0F;

        DObjGetStruct(sSC1PContinueFighterGObj)->scale.vec.f.x = dSCSubsysFighterScales[sSC1PContinueFighterDemoDesc.fkind] * sSC1PContinueGameOverFadeOutScale;
        DObjGetStruct(sSC1PContinueFighterGObj)->scale.vec.f.y = dSCSubsysFighterScales[sSC1PContinueFighterDemoDesc.fkind] * sSC1PContinueGameOverFadeOutScale;
        DObjGetStruct(sSC1PContinueFighterGObj)->scale.vec.f.z = dSCSubsysFighterScales[sSC1PContinueFighterDemoDesc.fkind] * sSC1PContinueGameOverFadeOutScale;
    }
}

// 0x80133368
void sc1PContinueMakeGameOver(void)
{
    GObj *gobj;

    sSC1PContinueGameOverFadeOutScale = 1.0F;
    sSC1PContinueGameOverGObj = gobj = gcMakeGObjSPAfter(0, NULL, 20, GOBJ_PRIORITY_DEFAULT);

    gcAddGObjProcess(gobj, sc1PContinueGameOverProcUpdate, nGCProcessKindFunc, 1);
}

// 0x801333C4
void sc1PContinueMakeRoomFadeInCamera(void)
{
    CObj *cobj = CObjGetStruct
    (
        gcMakeCameraGObj
        (
            nGCCommonKindSceneCamera,
            NULL,
            16,
            GOBJ_PRIORITY_DEFAULT,
            lbCommonDrawSprite,
            80,
            COBJ_MASK_DLLINK(26),
			-1,
			FALSE,
			nGCProcessKindFunc,
			NULL,
			1,
			FALSE
        )
    );
    syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);

    cobj->flags = 4;
}

// 0x80133474
void sc1PContinueMakeSpotlightFadeCamera(void)
{
    CObj *cobj = CObjGetStruct
    (
        gcMakeCameraGObj
        (
            nGCCommonKindSceneCamera,
            NULL,
            16,
            GOBJ_PRIORITY_DEFAULT,
            lbCommonDrawSprite,
            60,
            COBJ_MASK_DLLINK(31),
			-1,
			FALSE,
			nGCProcessKindFunc,
			NULL,
			1,
			FALSE
        )
    );
    syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);

    cobj->flags = 4;
}

// 0x80133524
void sc1PContinueMakeRoomFadeOutCamera(void)
{
    CObj *cobj = CObjGetStruct
    (
        gcMakeCameraGObj
        (
            nGCCommonKindSceneCamera,
            NULL,
            16,
            GOBJ_PRIORITY_DEFAULT,
            lbCommonDrawSprite,
            40,
            COBJ_MASK_DLLINK(32),
            -1,
            FALSE,
            nGCProcessKindFunc,
            NULL,
            1,
            FALSE
        )
    );
    syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);

    cobj->flags = 4;
}

// 0x801335D4
void sc1PContinueSetupCamera(CObj *cobj)
{
    syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);

    cobj->vec.eye.y = 1000.0F;
    cobj->vec.eye.z = 2000.0F;
    cobj->vec.at.y = 400.0F;

    cobj->vec.eye.x = 0.0F;
    cobj->vec.at.x = 0.0F;
    cobj->vec.at.z = 0.0F;
    cobj->vec.up.x = 0.0F;
    cobj->vec.up.z = 0.0F;

    cobj->vec.up.y = 1.0F;

    cobj->projection.persp.fovy = 30.0F;
    cobj->projection.persp.near = 100.0F;
    cobj->projection.persp.far = 15000.0F;

    cobj->flags = 4;
}

// 0x80133694
void sc1PContinueMakeMainCamera(void)
{
    // 0x08048600
    CObj *cobj = CObjGetStruct
    (
        gcMakeCameraGObj
        (
            nGCCommonKindSceneCamera,
            NULL,
            16,
            GOBJ_PRIORITY_DEFAULT,
            func_80017EC0,
            50,
            COBJ_MASK_DLLINK(27) | COBJ_MASK_DLLINK(18) | 
            COBJ_MASK_DLLINK(15) | COBJ_MASK_DLLINK(10) | 
            COBJ_MASK_DLLINK(9),
            -1,
            TRUE,
            nGCProcessKindFunc,
            NULL,
            1,
            FALSE
        )
    );
    sc1PContinueSetupCamera(cobj);
}

// 0x80133718
void sc1PContinueMakeRoomCamera(void)
{
    CObj *cobj = CObjGetStruct
    (
        gcMakeCameraGObj
        (
            nGCCommonKindSceneCamera,
            NULL,
            16,
            GOBJ_PRIORITY_DEFAULT,
            lbCommonDrawSprite,
            90,
            COBJ_MASK_DLLINK(29),
            -1,
            FALSE,
            nGCProcessKindFunc,
            NULL,
            1,
            FALSE
        )
    );
    syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);
}

// 0x801337B8
void sc1PContinueMakeSpotlightCamera(void)
{
    CObj *cobj = CObjGetStruct
    (
        gcMakeCameraGObj
        (
            nGCCommonKindSceneCamera,
            NULL,
            16,
            GOBJ_PRIORITY_DEFAULT,
            lbCommonDrawSprite,
            70,
            COBJ_MASK_DLLINK(30),
			-1,
			FALSE,
			nGCProcessKindFunc,
			NULL,
			1,
			FALSE
        )
    );
    syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);

    cobj->flags = 4;
}

// 0x80133868
void sc1PContinueMakeTextCamera(void)
{
    CObj *cobj = CObjGetStruct
    (
        gcMakeCameraGObj
        (
            nGCCommonKindSceneCamera,
            NULL,
            16,
            GOBJ_PRIORITY_DEFAULT,
            lbCommonDrawSprite,
            30,
            COBJ_MASK_DLLINK(28),
			-1,
			FALSE,
			nGCProcessKindFunc,
			NULL,
			1,
			FALSE
        )
    );
    syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);

    cobj->flags = 4;
}

// 0x80133918
void sc1PContinueInitVars(void)
{
    sSC1PContinueTotalTimeTics = 0;

    sSC1PContinueFighterDemoDesc.fkind = gSCManager1PGameBattleState.players[gSCManagerSceneData.player].fkind;
    sSC1PContinueFighterDemoDesc.costume = gSCManager1PGameBattleState.players[gSCManagerSceneData.player].costume;
    sSC1PContinueFighterDemoDesc.shade   = gSCManager1PGameBattleState.players[gSCManagerSceneData.player].shade;

    sSC1PContinueOptionSelect = 0;
    sSC1PContinueStatus = 0;
    D_ovl55_80134354 = 0;
    sSC1PContinueOptionNoGameOverAutoWait = -1;
}

// 0x80133990 - real
void sc1PContinueUnused0x80133990(void)
{
    return;
}

// 0x80133998
void sc1PContinueFuncRun(GObj *gobj)
{
    s32 unused;
    s32 stick_range;

    sSC1PContinueTotalTimeTics++;

    if (sSC1PContinueTotalTimeTics >= 10)
    {
        if (sSC1PContinueTotalTimeTics == sSC1PContinueOptionYesRetryTic)
        {
            // Why though?
            gSCManagerSceneData.scene_prev = gSCManagerSceneData.scene_curr;
            gSCManagerSceneData.scene_curr = nSCKindTitle;

            sSC1PContinueIsSelectContinue = TRUE;

            syTaskmanSetLoadScene();
        }
        if (D_ovl55_80134354 != 0)
        {
            D_ovl55_80134354--;
        }
        if (sSC1PContinueOptionChangeWait != 0)
        {
            sSC1PContinueOptionChangeWait--;
        }
		if
        (
            (scSubsysControllerGetPlayerStickInRangeLR(-15, 15) != FALSE) &&
            (scSubsysControllerGetPlayerStickInRangeUD(-15, 15) != FALSE)
        )
		{
            sSC1PContinueOptionChangeWait = 0;
        }
        if ((sSC1PContinueTotalTimeTics == I_SEC_TO_TICS(40)) && (sSC1PContinueStatus == 0))
        {
            gcEjectGObj(sSC1PContinueShadowGObj);
            gcEjectGObj(sSC1PContinueSpotlightGObj);
            gcEjectGObj(sSC1PContinueContinueGObj);
            gcEjectGObj(sSC1PContinueOptionGObj);
            gcEjectGObj(sSC1PContinueCursorGObj);

            sc1PContinueMakeRoomFadeOut();
            sc1PContinueMakeGameOverText();
            sc1PContinueMakeGameOver();

            sSC1PContinueStatus = 2;
            sSC1PContinueOptionNoGameOverInputWait = sSC1PContinueTotalTimeTics + I_SEC_TO_TICS(1.5);
            sSC1PContinueOptionNoGameOverAutoWait = sSC1PContinueTotalTimeTics + I_SEC_TO_TICS(30);

			auPlaySong(0, nSYAudioBGM1PGameOver);
			func_800269C0_275C0(nSYAudioVoiceAnnounceGameOver);
		}
        if (sSC1PContinueStatus == 0)
        {
            if
            (
                (sSC1PContinueTotalTimeTics > I_SEC_TO_TICS(2.5)) && 
                (scSubsysControllerGetPlayerTapButtons(A_BUTTON | START_BUTTON) != FALSE)
            )
            {
                switch (sSC1PContinueOptionSelect)
                {
                case nSC1PContinueOptionYes:
                    gcEjectGObj(sSC1PContinueShadowGObj);
                    gcEjectGObj(sSC1PContinueSpotlightGObj);
                    gcEjectGObj(sSC1PContinueContinueGObj);
                    gcEjectGObj(sSC1PContinueOptionGObj);
                    gcEjectGObj(sSC1PContinueCursorGObj);

                    gSCManagerSceneData.spgame_score *= 0.5F;

                    gcEjectGObj(sSC1PContinueScoreGObj);
                    sc1PContinueMakeScoreDisplay(gSCManagerSceneData.spgame_score);
					scSubsysFighterSetStatus(sSC1PContinueFighterGObj, 0x1000A);

					sSC1PContinueStatus = 1;
                    sSC1PContinueOptionYesRetryTic = sSC1PContinueTotalTimeTics + I_SEC_TO_TICS(4);

					func_800269C0_275C0(nSYAudioFGM1PGameContinue);
					break;

                case nSC1PContinueOptionNo:
                    gcEjectGObj(sSC1PContinueShadowGObj);
                    gcEjectGObj(sSC1PContinueSpotlightGObj);
                    gcEjectGObj(sSC1PContinueContinueGObj);
                    gcEjectGObj(sSC1PContinueOptionGObj);
                    gcEjectGObj(sSC1PContinueCursorGObj);

                    sc1PContinueMakeRoomFadeOut();
                    sc1PContinueMakeGameOverText();
                    sc1PContinueMakeGameOver();

                    sSC1PContinueStatus = 2;
                    sSC1PContinueOptionNoGameOverInputWait = sSC1PContinueTotalTimeTics + I_SEC_TO_TICS(1.5);
                    sSC1PContinueOptionNoGameOverAutoWait = sSC1PContinueTotalTimeTics + I_SEC_TO_TICS(30);

                    auPlaySong(0, nSYAudioBGM1PGameOver);
                    func_800269C0_275C0(nSYAudioVoiceAnnounceGameOver);
                    break;
                }
            }
            if (sSC1PContinueTotalTimeTics > 120)
            {
                if
                (
                    (
                        (scSubsysControllerGetPlayerTapButtons(L_TRIG | L_JPAD | L_CBUTTONS) != FALSE) || 
                        sc1PContinueCheckGetOptionStickInputLR(stick_range, -15, FALSE)
                    ) 
                    &&
                    (sSC1PContinueOptionSelect == nSC1PContinueOptionNo)
                )
                {
                    func_800269C0_275C0(nSYAudioFGMMenuScroll1);
                    sSC1PContinueOptionSelect = nSC1PContinueOptionYes;
                    sc1PContinueSetOptionChangeWaitN(stick_range);
                }
                if
                (
                    (
                        (scSubsysControllerGetPlayerTapButtons(R_TRIG | R_JPAD | R_CBUTTONS) != FALSE) || 
                        sc1PContinueCheckGetOptionStickInputLR(stick_range, 15, TRUE)
                    )
                    &&
                    (sSC1PContinueOptionSelect == nSC1PContinueOptionYes)
                )
                {
                    func_800269C0_275C0(nSYAudioFGMMenuScroll1);
                    sSC1PContinueOptionSelect = nSC1PContinueOptionNo;
                    sc1PContinueSetOptionChangeWaitP(stick_range);
                }
            }
        }
        if
        (
            (sSC1PContinueStatus == 2)                                              && 
            (sSC1PContinueOptionNoGameOverInputWait < sSC1PContinueTotalTimeTics)   && 
            (scSubsysControllerGetPlayerTapButtons(A_BUTTON | START_BUTTON) != FALSE)
        )
        {
            gSCManagerSceneData.scene_prev = gSCManagerSceneData.scene_curr;
            gSCManagerSceneData.scene_curr = nSCKindTitle;

        #if !defined(DAIRANTOU_OPT0)
            sc1PContinueUnused0x80133990();
        #endif
            sSC1PContinueIsSelectContinue = FALSE;
            syTaskmanSetLoadScene();
        }
        if (sSC1PContinueTotalTimeTics == sSC1PContinueOptionNoGameOverAutoWait)
        {
            gSCManagerSceneData.scene_prev = gSCManagerSceneData.scene_curr;
            gSCManagerSceneData.scene_curr = nSCKindTitle;

        #if !defined(DAIRANTOU_OPT0)
            sc1PContinueUnused0x80133990();
        #endif
            sSC1PContinueIsSelectContinue = FALSE;
            syTaskmanSetLoadScene();
        }
        if (sSC1PContinueTotalTimeTics == 40)
        {
            sc1PContinueMakeSpotlight();
            sc1PContinueMakeSpotlightFade();
        }
        if (sSC1PContinueTotalTimeTics == 60)
        {
            sc1PContinueMakeRoomFadeIn();
            sc1PContinueMakeRoom();
            sc1PContinueMakeContinue();
            func_800269C0_275C0(nSYAudioVoiceAnnounceContinue);
        }
        if (sSC1PContinueTotalTimeTics == 120)
        {
            sc1PContinueMakeOptions();
            sc1PContinueMakeCursor();
        }
    }
}

// 0x80133F58
void sc1PContinueFuncStart(void)
{
    s32 unused;
    LBRelocSetup rl_setup;

    rl_setup.table_addr = (uintptr_t)&lLBRelocTableAddr;
    rl_setup.table_files_num = (uintptr_t)&lLBRelocTableFilesNum;
    rl_setup.file_heap = NULL;
    rl_setup.file_heap_size = 0;
    rl_setup.status_buffer = sSC1PContinueStatusBuffer;
    rl_setup.status_buffer_size = ARRAY_COUNT(sSC1PContinueStatusBuffer);
    rl_setup.force_status_buffer = sSC1PContinueForceStatusBuffer;
    rl_setup.force_status_buffer_size = ARRAY_COUNT(sSC1PContinueForceStatusBuffer);

    lbRelocInitSetup(&rl_setup);
    lbRelocLoadFilesExtern
    (
        dSC1PContinueFileIDs,
        ARRAY_COUNT(dSC1PContinueFileIDs),
        sSC1PContinueFiles,
        syTaskmanMalloc
        (
            lbRelocGetAllocSize
            (
                dSC1PContinueFileIDs,
                ARRAY_COUNT(dSC1PContinueFileIDs)
            ),
            0x10
        )
    );
    gcMakeGObjSPAfter(0, sc1PContinueFuncRun, 0, GOBJ_PRIORITY_DEFAULT);
    gcMakeDefaultCameraGObj(0, GOBJ_PRIORITY_DEFAULT, 100, COBJ_FLAG_FILLCOLOR | COBJ_FLAG_ZBUFFER, GPACK_RGBA8888(0x00, 0x00, 0x00, 0xFF));
    efParticleInitAll();
    sc1PContinueInitVars();
    efManagerInitEffects();
    ftManagerAllocFighter(FTDATA_FLAG_SUBMOTION, 1);
    ftManagerSetupFilesAllKind(sSC1PContinueFighterDemoDesc.fkind);
    
    sSC1PContinueFigatreeHeap = syTaskmanMalloc(gFTManagerFigatreeHeapSize, 0x10);

    sc1PContinueMakeMainCamera();
    sc1PContinueMakeRoomFadeInCamera();
    sc1PContinueMakeSpotlightFadeCamera();
    sc1PContinueMakeRoomFadeOutCamera();
    sc1PContinueMakeRoomCamera();
    sc1PContinueMakeSpotlightCamera();
    sc1PContinueMakeTextCamera();
    sc1PContinueMakeFighter(sSC1PContinueFighterDemoDesc.fkind);
    sc1PContinueMakeScoreDisplay(gSCManagerSceneData.spgame_score);

    scSubsysFighterSetLightParams(45.0F, 45.0F, 0xFF, 0xFF, 0xFF, 0xFF);

    auStopBGM();
    auPlaySong(0, nSYAudioBGM1PGameEndChoice);
}

// 0x80134238
SYVideoSetup dSC1PContinueVideoSetup = SYVIDEO_DEFINE_DEFAULT();

// 0x80134254
SYTaskmanSetup dSC1PContinueTaskmanSetup =
{
    // Task Manager Buffer Setup
    {
        0,                          // ???
        gcRunAll,              		// Update function
        scManagerFuncDraw,              // Frame draw function
        &ovl55_BSS_END,             // Allocatable memory pool start
        0,                          // Allocatable memory pool size
        1,                          // ???
        2,                          // Number of contexts?
        sizeof(Gfx) * 2500,         // Display List Buffer 0 Size
        sizeof(Gfx) * 512,          // Display List Buffer 1 Size
        0,                          // Display List Buffer 2 Size
        0,                          // Display List Buffer 3 Size
        0x8000,                     // Graphics Heap Size
        2,                          // ???
        0xC000,                     // RDP Output Buffer Size
        sc1PContinueFuncLights,     // Pre-render function
        update_contdata,            // Controller I/O function
    },

    0,                              // Number of GObjThreads
    sizeof(u64) * 192,              // Thread stack size
    0,                              // Number of thread stacks
    0,                              // ???
    0,                              // Number of GObjProcesses
    0,                              // Number of GObjs
    sizeof(GObj),                   // GObj size
    0,                              // Number of Object Manager Matrices
    dLBCommonFuncMatrixList,        // Matrix function list
    NULL,                           // Function for ejecting DObjVec?
    0,                              // Number of AObjs
    0,                              // Number of MObjs
    0,                              // Number of DObjs
    sizeof(DObj),                   // DObj size
    0,                              // Number of SObjs
    sizeof(SObj),                   // SObj size
    0,                              // Number of Cameras
    sizeof(CObj),                 	// CObj size
    
    sc1PContinueFuncStart           // Task start function
};

// 0x801340FC
void sc1PContinueStartScene(void)
{
    dSC1PContinueVideoSetup.zbuffer = syVideoGetZBuffer(6400);

    syVideoInit(&dSC1PContinueVideoSetup);

    dSC1PContinueTaskmanSetup.buffer_setup.arena_size = (size_t) ((uintptr_t)&ovl1_VRAM - (uintptr_t)&ovl55_BSS_END);

    scManagerFuncUpdate(&dSC1PContinueTaskmanSetup);

    gSCManagerSceneData.is_continue = sSC1PContinueIsSelectContinue;
}
