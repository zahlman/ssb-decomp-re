#include <sys/develop.h>
#include <ft/fighter.h>
#include <gr/ground.h>
#include <sc/scene.h>
#include <lb/library.h>
#include <sys/video.h>

// Externs
extern intptr_t D_NF_800A5240;      // 0x800A5240
extern intptr_t lOverlay35ArenaLo;  // 0x80132BC0
extern intptr_t lOverlay35ArenaHi;  // 0x803903E0
extern intptr_t FILE_035_PORTRAIT_OVERLAY_IMAGE_OFFSET; // file 0x035 image offset for portrait overlay
extern void ftDisplayLightsDrawReflect(Gfx**, f32, f32);
extern f32 scSubsysFighterGetLightAngleX();
extern f32 scSubsysFighterGetLightAngleY();


extern void syRdpSetViewport(void*, f32, f32, f32, f32);



// Data
// 0x801328A0
u32 D_ovl35_801328A0[2] = {

	0x35, 0x36
};

// 0x801328A8
s32 D_ovl35_801328A8[] = {

	0x20202000,
	0x20202000,
	0xFFFFFF00,
	0xFFFFFF00,
	0x14141400,
	0x00000000,
	0x20202000,
	0x20202000,
	0xFFFFFF00,
	0xFFFFFF00,
	0x00140000,
	0x00000000
};


// BSS
// 0x801329E0
s32 D_ovl35_801329E0[2];

// 0x801329E8
s32 gIntroPotraitsFramesElapsed;

// 0x801329EC
s32 gIntroPotraitsCurrentRow;

// 0x801329F0
GObj* gIntroPortraitsPortraitGObj;

// 0x801329F4
s32 gIntroPortraitsUnusedCounter;

// 0x801329F8
u32 D_ovl35_801329F8[96];

// 0x80132B78
LBFileNode D_ovl35_80132B78;

// 0x80132B80
u32 D_ovl35_80132B80[12];

// 0x80132BB0
s32 gIntroPortraitsFiles[2];


// 0x80131B00
void mvPortraitsFuncLights(Gfx **display_list)
{
	gSPSetGeometryMode(display_list[0]++, G_LIGHTING);
	ftDisplayLightsDrawReflect(display_list, scSubsysFighterGetLightAngleX(), scSubsysFighterGetLightAngleY());
}

// 0x80131B58
void mvPortraitsCreatePortraitsSet1()
{
	GObj* portraits_gobj;
	SObj* portrait_sobj;
	s32 i;
	intptr_t offsets[4] = {

		0x09960,
		0x13310,
		0x1CCC0,
		0x26670
	};
	Vec2f positions[4] = {

		{ 10.0, 10.0  },
		{ 10.0, 65.0  },
		{ 10.0, 120.0 },
		{ 10.0, 175.0 }
	};

	gIntroPortraitsPortraitGObj = portraits_gobj = gcMakeGObjSPAfter(0, 0, 0x11, GOBJ_PRIORITY_DEFAULT);
	gcAddGObjDisplay(portraits_gobj, lbCommonDrawSObjAttr, 0x1B, GOBJ_PRIORITY_DEFAULT, ~0);

	for (i = 0; i < ARRAY_COUNT(offsets); i++)
	{
		portrait_sobj = lbCommonMakeSObjForGObj(portraits_gobj, GetAddressFromOffset(gIntroPortraitsFiles[0], offsets[i]));
		portrait_sobj->sprite.attr &= ~SP_FASTCOPY;
		portrait_sobj->pos.x = positions[i].x;
		portrait_sobj->pos.y = positions[i].y;
	}
}

// 0x80131CAC
void mvPortraitsCreatePortraitsSet2()
{
	GObj* portraits_gobj;
	SObj* portrait_sobj;
	s32 i;
	intptr_t offsets[4] = {

		0x09960,
		0x13310,
		0x1CCC0,
		0x26670
	};
	Vec2f positions[4] = {

		{ 10.0, 10.0  },
		{ 10.0, 65.0  },
		{ 10.0, 120.0 },
		{ 10.0, 175.0 }
	};

	gIntroPortraitsPortraitGObj = portraits_gobj = gcMakeGObjSPAfter(0, 0, 0x11, GOBJ_PRIORITY_DEFAULT);
	gcAddGObjDisplay(portraits_gobj, lbCommonDrawSObjAttr, 0x1B, GOBJ_PRIORITY_DEFAULT, ~0);

	for (i = 0; i < ARRAY_COUNT(offsets); i++)
	{
		portrait_sobj = lbCommonMakeSObjForGObj(portraits_gobj, GetAddressFromOffset(gIntroPortraitsFiles[1], offsets[i]));
		portrait_sobj->sprite.attr &= ~SP_FASTCOPY;
		portrait_sobj->pos.x = positions[i].x;
		portrait_sobj->pos.y = positions[i].y;
	}
}

// 0x80131E00
void mvPortraitsBlockRow1()
{
	gDPFillRectangle(gSYTaskmanDLHeads[0]++, 10, 10, 310, 65);
}

// 0x80131E30
void mvPortraitsBlockRow2()
{
	gDPFillRectangle(gSYTaskmanDLHeads[0]++, 10, 65, 310, 120);
}

// 0x80131E60
void mvPortraitsBlockRow3()
{
	gDPFillRectangle(gSYTaskmanDLHeads[0]++, 10, 120, 310, 175);
}

// 0x80131E90
void mvPortraitsBlockRow4()
{
	gDPFillRectangle(gSYTaskmanDLHeads[0]++, 10, 175, 310, 230);
}

// 0x80131EC0
void mvPortraitsPartiallyBlockRow(s32 row, s32 x_offset)
{
	s32 uly = 10 + row * 55;
	s32 lry = 65 + row * 55;

	if (x_offset > 0)
		gDPFillRectangle(gSYTaskmanDLHeads[0]++, 0, uly, x_offset, lry);

	if (x_offset + 656 < 0)
		gDPFillRectangle(gSYTaskmanDLHeads[0]++, 0, uly, 320, lry);

	if (x_offset + 656 < 320)
		gDPFillRectangle(gSYTaskmanDLHeads[0]++, x_offset + 656, uly, 320, lry);
}

// 0x80131FC4
void mvPortraitsRenderPortraitOverlay(GObj* portrait_overlay_gobj)
{
	gDPPipeSync(gSYTaskmanDLHeads[0]++);
	gDPSetCycleType(gSYTaskmanDLHeads[0]++, G_CYC_1CYCLE);
	gDPSetPrimColor(gSYTaskmanDLHeads[0]++, 0, 0, 0, 0, 0, 255);
	gDPSetCombineLERP(gSYTaskmanDLHeads[0]++, 0, 0, 0, PRIMITIVE,  0, 0, 0, PRIMITIVE,  0, 0, 0, PRIMITIVE,  0, 0, 0, PRIMITIVE);
	gDPSetRenderMode(gSYTaskmanDLHeads[0]++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

	switch (gIntroPotraitsCurrentRow)
	{
		case 0:
			mvPortraitsBlockRow2();
			mvPortraitsBlockRow3();
			mvPortraitsBlockRow4();
			mvPortraitsPartiallyBlockRow(0, SObjGetStruct(portrait_overlay_gobj)->pos.x);
			break;
		case 1:
			mvPortraitsBlockRow1();
			mvPortraitsBlockRow3();
			mvPortraitsBlockRow4();
			mvPortraitsPartiallyBlockRow(1, SObjGetStruct(portrait_overlay_gobj)->pos.x);
			break;
		case 2:
			mvPortraitsBlockRow1();
			mvPortraitsBlockRow2();
			mvPortraitsBlockRow4();
			mvPortraitsPartiallyBlockRow(2, SObjGetStruct(portrait_overlay_gobj)->pos.x);
			break;
		case 3:
			mvPortraitsBlockRow1();
			mvPortraitsBlockRow2();
			mvPortraitsBlockRow3();
			mvPortraitsPartiallyBlockRow(3, SObjGetStruct(portrait_overlay_gobj)->pos.x);
			break;
	}

	gDPPipeSync(gSYTaskmanDLHeads[0]++);
	gDPSetRenderMode(gSYTaskmanDLHeads[0]++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

	lbCommonClearExternSpriteParams();
	lbCommonDrawSObjAttr(portrait_overlay_gobj);
}

// 0x801321FC
void mvPortraitsAnimatePortraitOverlay(GObj* portrait_overlay_gobj)
{
	SObj* portrait_overlay_sobj = SObjGetStruct(portrait_overlay_gobj);

	if (gIntroPotraitsFramesElapsed == 75)
		portrait_overlay_sobj->pos.x = -656.0F;

	if (gIntroPotraitsFramesElapsed < 75)
	{
		if (portrait_overlay_sobj->pos.x < 656.0F)
		{
			portrait_overlay_sobj->pos.x += 93.0F;

			if (portrait_overlay_sobj->pos.x > 656.0F)
				portrait_overlay_sobj->pos.x = 656.0F;
		}
	}
	else
	{
		if (portrait_overlay_sobj->pos.x > -656.0F)
		{
			portrait_overlay_sobj->pos.x -= 93.0F;

			if (portrait_overlay_sobj->pos.x < -656.0F)
				portrait_overlay_sobj->pos.x = -656.0F;
		}
	}

	switch (gIntroPotraitsFramesElapsed)
	{
		case 15:
			portrait_overlay_sobj->pos.x = -656.0F;
			portrait_overlay_sobj->pos.y = 10.0F;
			gIntroPotraitsCurrentRow = 0;
			break;
		case 45:
			portrait_overlay_sobj->pos.x = -656.0F;
			portrait_overlay_sobj->pos.y = 65.0F;
			gIntroPotraitsCurrentRow = 1;
			break;
		case 30:
			portrait_overlay_sobj->pos.x = -656.0F;
			portrait_overlay_sobj->pos.y = 120.0F;
			gIntroPotraitsCurrentRow = 2;
			break;
		case 60:
			portrait_overlay_sobj->pos.x = -656.0F;
			portrait_overlay_sobj->pos.y = 175.0F;
			gIntroPotraitsCurrentRow = 3;
			break;
		case 105:
			portrait_overlay_sobj->pos.x = 656.0F;
			portrait_overlay_sobj->pos.y = 10.0F;
			gIntroPotraitsCurrentRow = 0;
			break;
		case 135:
			portrait_overlay_sobj->pos.x = 656.0F;
			portrait_overlay_sobj->pos.y = 65.0F;
			gIntroPotraitsCurrentRow = 1;
			break;
		case 90:
			portrait_overlay_sobj->pos.x = 656.0F;
			portrait_overlay_sobj->pos.y = 120.0F;
			gIntroPotraitsCurrentRow = 2;
			break;
		case 120:
			portrait_overlay_sobj->pos.x = 656.0F;
			portrait_overlay_sobj->pos.y = 175.0F;
			gIntroPotraitsCurrentRow = 3;
			break;
	}
}

// 0x80132414
void mvPortraitsCreatePortraitOverlay()
{
	GObj* portrait_overlay_gobj;
	SObj* portrait_overlay_sobj;

	portrait_overlay_gobj = gcMakeGObjSPAfter(0, 0, 0x12, 0x80000000);
	gcAddGObjDisplay(portrait_overlay_gobj, &mvPortraitsRenderPortraitOverlay, 0x1C, GOBJ_PRIORITY_DEFAULT, ~0);

	portrait_overlay_sobj = lbCommonMakeSObjForGObj(portrait_overlay_gobj, GetAddressFromOffset(gIntroPortraitsFiles[0], &FILE_035_PORTRAIT_OVERLAY_IMAGE_OFFSET));
	portrait_overlay_sobj->sprite.attr &= ~SP_FASTCOPY;
	portrait_overlay_sobj->sprite.attr |= SP_TRANSPARENT;
	portrait_overlay_sobj->sprite.red = 0;
	portrait_overlay_sobj->sprite.green = 0;
	portrait_overlay_sobj->sprite.blue = 0;
	portrait_overlay_sobj->pos.x = 656.0F;
	portrait_overlay_sobj->pos.y = 10.0F;
	gcAddGObjProcess(portrait_overlay_gobj, mvPortraitsAnimatePortraitOverlay, 1, 1);
}

// 0x801324D0
void mvPortraitsCreatePortraitViewport()
{
	GObj *camera_gobj = gcMakeCameraGObj(0x401, NULL, 0x10, 0x80000000U, lbCommonDrawSprite, 0x50, 0x8000000, -1, 0, 1, 0, 1, 0);
	CObj *cobj = CObjGetStruct(camera_gobj);
	syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);
}

// 0x80132570
void mvPortraitsCreatePortraitOverlayViewport()
{
	GObj *camera_gobj = gcMakeCameraGObj(0x401, NULL, 0x10, 0x80000000U, lbCommonDrawSprite, 0x3C, 0x10000000, -1, 0, 1, 0, 1, 0);
	CObj *cobj = CObjGetStruct(camera_gobj);
	syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);
}

// 0x80132610
void mvPortraitsInitVariables()
{
	gIntroPotraitsFramesElapsed = 0;
	gIntroPotraitsCurrentRow = 0;
}

// 0x80132624
void mvPortraitsMain(GObj* arg0)
{
	gIntroPotraitsFramesElapsed++;

	if (gIntroPotraitsFramesElapsed >= 10)
	{
		// gIntroPortraitsUnusedCounter gets set to 0 if any diagonal stick press occurs...
		// This scene must have been interactive at some point
		if (gIntroPortraitsUnusedCounter != 0)
			gIntroPortraitsUnusedCounter -= 1;

		if ((scSubsysControllerGetPlayerStickInRangeLR(-0xF, 0xF) != 0) && (scSubsysControllerGetPlayerStickInRangeUD(-0xF, 0xF) != 0))
			gIntroPortraitsUnusedCounter = 0;

		if (scSubsysControllerGetPlayerTapButtons(A_BUTTON | B_BUTTON | START_BUTTON))
		{
			gSCManagerSceneData.scene_prev = gSCManagerSceneData.scene_curr;
			gSCManagerSceneData.scene_curr = nSCKindTitle;
			syTaskmanSetLoadScene();
		}

		if (gIntroPotraitsFramesElapsed == 75)
		{
			gcEjectGObj(gIntroPortraitsPortraitGObj);
			mvPortraitsCreatePortraitsSet2();
		}

		if (gIntroPotraitsFramesElapsed == 150)
		{
			gSCManagerSceneData.scene_prev = gSCManagerSceneData.scene_curr;
			gSCManagerSceneData.scene_curr = 0x1E;
			syTaskmanSetLoadScene();
		}
	}
}

// 0x80132718
void mvPortraitsInit()
{
	s32 foo;
	LBRelocSetup rl_setup;

	rl_setup.table_addr = (uintptr_t)&lLBRelocTableAddr;
	rl_setup.table_files_num = (uintptr_t)&lLBRelocTableFilesNum;
	rl_setup.file_heap = NULL;
	rl_setup.file_heap_size = 0;
	rl_setup.status_buffer = (LBFileNode*) &D_ovl35_801329F8;
	rl_setup.status_buffer_size = 0x30;
	rl_setup.force_status_buffer = (LBFileNode*) &D_ovl35_80132B78;
	rl_setup.force_status_buffer_size = 7;
	lbRelocInitSetup(&rl_setup);
	lbRelocLoadFilesExtern(D_ovl35_801328A0, ARRAY_COUNT(D_ovl35_801328A0), gIntroPortraitsFiles, syTaskmanMalloc(lbRelocGetAllocSize(D_ovl35_801328A0, ARRAY_COUNT(D_ovl35_801328A0)), 0x10));

	gcMakeGObjSPAfter(0, mvPortraitsMain, 0, GOBJ_PRIORITY_DEFAULT);
	gcMakeDefaultCameraGObj(0, GOBJ_PRIORITY_DEFAULT, 100, COBJ_FLAG_FILLCOLOR | COBJ_FLAG_ZBUFFER, GPACK_RGBA8888(0x00, 0x00, 0x00, 0xFF));
	mvPortraitsInitVariables();
	mvPortraitsCreatePortraitViewport();
	mvPortraitsCreatePortraitOverlayViewport();
	mvPortraitsCreatePortraitsSet1();
	mvPortraitsCreatePortraitOverlay();

	while (func_8000092C() < 1335U)
		continue;
}

// 0x80132938
SYVideoSetup D_ovl35_80132938 = {

	gSCSubsysFramebuffer0,
	gSCSubsysFramebuffer1,
	gSCSubsysFramebuffer2,
	0x00000000,
	0x00000140,
	0x000000F0,
	0x00016A99
};

// 0x80132954
scRuntimeInfo D_ovl35_80132954 = {

	0x00000000, 0x8000A5E4,
	gcDrawAll, &lOverlay35ArenaLo,
	0x00000000, 0x00000001, 0x00000002, 0x00009C40, 0x00001000,
	0x00000000, 0x00000000, 0x00008000, 0x00020000, 0x0000C000,
	mvPortraitsFuncLights, update_contdata,
	0x00000008, 0x00000600, 0x00000008, 0x00000000,
	0x00000080, 0x00000080, 0x00000088, 0x00000100,
	0x800D5CAC, 0x00000000, 0x00000200, 0x000000A0,
	0x00000100, 0x00000088, 0x00000080, 0x0000006C,
	0x00000010, 0x00000090,
	mvPortraitsInit
};

// 0x8013283C
void mvPortraitsStartScene()
{
	D_ovl35_80132938.zbuffer = syVideoGetZBuffer(6400);
	syVideoInit(&D_ovl35_80132938);
	D_ovl35_80132954.arena_size = (u32) ((uintptr_t)&lOverlay35ArenaHi - (uintptr_t)&lOverlay35ArenaLo);
	syTaskmanRun(&D_ovl35_80132954);
}
