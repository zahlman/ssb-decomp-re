#include <mn/menu.h>
#include <sc/scene.h> // includes sys/obj.h
#include <sys/thread6.h>
#include <sys/video.h>

extern void syRdpSetViewport(void*, f32, f32, f32, f32);

// // // // // // // // // // // //
//                               //
//       EXTERNAL VARIABLES      //
//                               //
// // // // // // // // // // // //

extern uintptr_t D_NF_000000C2;

// // // // // // // // // // // //
//                               //
//   GLOBAL / STATIC VARIABLES   //
//                               //
// // // // // // // // // // // //

// 0x80132040
s32 sMNN64Pad0x80132040[2];

// 0x80132048
LBFileNode sMNN64StatusBuffer[5];

// 0x80132070 - Delay frames before N64 logo can be skipped
s32 sMNN64SkipAllowWait;

// 0x80132074 - if TRUE, proceed to the opening movie
sb32 sMNN64IsProceedOpening;

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

// 0x80131F50
SYColorRGBA dMNN64EndFadeColor = { 0x00, 0x00, 0x00, 0xFF };

// 0x80131F54
SYColorRGBA dMNN64StartFadeColor = { 0x00, 0x00, 0x00, 0x00 };

// 0x80131F58
Lights1 dMNN64Lights1 = gdSPDefLights1(0x20, 0x20, 0x20, 0xFF, 0xFF, 0xFF, 0x0A, 0x32, 0x32);

// 0x80131F70
Gfx dMNN64DisplayList[/* */] =
{
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPSetLights1(dMNN64Lights1),
	gsSPEndDisplayList()
};

// 0x80131F98
SYVideoSetup dMNN64VideoSetup = SYVIDEO_DEFINE_DEFAULT();

// 0x80131FB4
SYTaskmanSetup dMNN64TaskmanSetup =
{
    // Task Manager Buffer Setup
    {
        0,                          // ???
        gcRunAll,              		// Update function
        gcDrawAll,                  // Frame draw function
        &ovl58_BSS_END,             // Allocatable memory pool start
        0,                          // Allocatable memory pool size
        1,                          // ???
        2,                          // Number of contexts?
        sizeof(Gfx) * 1280,         // Display List Buffer 0 Size
        sizeof(Gfx) * 1280,         // Display List Buffer 1 Size
        0,                          // Display List Buffer 2 Size
        0,                          // Display List Buffer 3 Size
        0x2800,                     // Graphics Heap Size
        2,                          // ???
        0xC000,                     // RDP Output Buffer Size
        mnN64FuncLights,         	// Pre-render function
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
    NULL,                           // Matrix function list
    NULL,                           // Function for ejecting DObjVec?
    0,                              // Number of AObjs
    0,                              // Number of MObjs
    0,                              // Number of DObjs
    sizeof(DObj),                   // DObj size
    0,                              // Number of SObjs
    sizeof(SObj),                   // SObj size
    0,                              // Number of Cameras
    sizeof(CObj),                 	// CObj size
    
    mnN64FuncStart               	// Task start function
};

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80131B00
void mnN64LogoThreadUpdate(GObj *gobj)
{
	f32 step;
	s32 i;
	SObj *sobj;
	SYColorRGBA color;

	sobj = SObjGetStruct(gobj);

	i = 0;

	while (i < 16)
	{
		step = 16 - i;
		sobj->pos.y = 65.0F - ((-(38.75F / 64.0F) * step) * step);

		gcStopCurrentGObjThread(1);
		
		i++;
	}
	sobj->pos.y = 65.0F;

	i = 0;

	while (i < 24)
	{
		gcStopCurrentGObjThread(1);
		i++;
	}
	color = dMNN64EndFadeColor;

	lbFadeMakeActor(nGCCommonKindTransition, nGCCommonLinkIDTransition, 10, &color, 10, FALSE, NULL);

	i = 0;

	while (i < 13)
	{
		gcStopCurrentGObjThread(1);
		i++;
	}
	sMNN64IsProceedOpening = TRUE;

	while (TRUE)
	{
		gcStopCurrentGObjThread(1);
	}
}

// 0x80131C20
void mnN64ActorFuncRun(GObj *gobj)
{
	if (sMNN64SkipAllowWait != 0)
	{
		sMNN64SkipAllowWait--;
	}
	if ((sMNN64SkipAllowWait == 0) && (scSubsysControllerGetPlayerTapButtons(A_BUTTON | B_BUTTON | START_BUTTON) != FALSE))
	{
		gSCManagerSceneData.scene_prev = gSCManagerSceneData.scene_curr;
		gSCManagerSceneData.scene_curr = nSCKindTitle;
		syTaskmanSetLoadScene();
	}
	else if (sMNN64IsProceedOpening != FALSE)
	{
		gSCManagerSceneData.scene_prev = gSCManagerSceneData.scene_curr;
		gSCManagerSceneData.scene_curr = nSCKindOpeningRoom;
		syTaskmanSetLoadScene();
	}
}

// 0x80131CB8
void mnN64FuncStart(void)
{
	LBRelocSetup rl_setup;
	CObj *cobj;
	GObj *gobj;
	SObj *sobj;
	Sprite *sprite;
	SYColorRGBA color;

	sMNN64SkipAllowWait = 8;
	sMNN64IsProceedOpening = FALSE;

	rl_setup.table_addr = (uintptr_t)&lLBRelocTableAddr;
	rl_setup.table_files_num = (uintptr_t)&lLBRelocTableFilesNum;
	rl_setup.file_heap = NULL;
	rl_setup.file_heap_size = 0;
	rl_setup.status_buffer = sMNN64StatusBuffer;
	rl_setup.status_buffer_size = ARRAY_COUNT(sMNN64StatusBuffer);
	rl_setup.force_status_buffer = NULL;
	rl_setup.force_status_buffer_size = 0;

	lbRelocInitSetup(&rl_setup);

	gcMakeGObjSPAfter(0, mnN64ActorFuncRun, 0, GOBJ_PRIORITY_DEFAULT);
	gcMakeDefaultCameraGObj(0, GOBJ_PRIORITY_DEFAULT, 100, COBJ_FLAG_FILLCOLOR, GPACK_RGBA8888(0x00, 0x00, 0x00, 0xFF));

	cobj = CObjGetStruct
	(
		gcMakeCameraGObj
		(
			nGCCommonKindWallpaperCamera,
			NULL,
			nGCCommonLinkIDCamera,
			GOBJ_PRIORITY_DEFAULT,
			lbCommonDrawSprite,
			80,
			COBJ_MASK_DLLINK(0),
			-1,
			FALSE,
			nGCProcessKindFunc,
			NULL,
			1,
			FALSE
		)
	);
	syRdpSetViewport(&cobj->viewport, 10.0F, 10.0F, 310.0F, 230.0F);

	gobj = gcMakeGObjSPAfter(nGCCommonKindWallpaper, NULL, nGCCommonLinkIDWallpaper, GOBJ_PRIORITY_DEFAULT);

	gcAddGObjProcess(gobj, mnN64LogoThreadUpdate, nGCProcessKindThread, 1);
	gcAddGObjDisplay(gobj, lbCommonDrawSObjAttr, 0, GOBJ_PRIORITY_DEFAULT, ~0);

	sprite = lbRelocGetFileData
	(
		Sprite*,
		lbRelocGetFileExternHeap
		(
			&D_NF_000000C2,
			syTaskmanMalloc
			(
				lbRelocGetFileSize
				(
					&D_NF_000000C2
				),
				0x10
			)
		),
		&lMNN64LogoSprite
	);
	sobj = lbCommonMakeSObjForGObj(gobj, sprite);

	sobj->sprite.attr &= ~SP_FASTCOPY;

	sobj->pos.x = 96.0F;
	sobj->pos.y = 220.0F;

	color = dMNN64StartFadeColor;

	lbFadeMakeActor(nGCCommonKindTransition, nGCCommonLinkIDTransition, 10, &color, 16, TRUE, NULL);
}

// 0x80131ECC
void mnN64FuncLights(Gfx **dls)
{
	gSPDisplayList(dls[0]++, dMNN64DisplayList);
}

// 0x80131EF0
void mnN64StartScene(void)
{
	auStopBGM();
	
	dMNN64VideoSetup.zbuffer = syVideoGetZBuffer(6400);
	syVideoInit(&dMNN64VideoSetup);

	dMNN64TaskmanSetup.buffer_setup.arena_size = (size_t) ((uintptr_t)&ovl1_VRAM - (uintptr_t)&ovl58_BSS_END);
	syTaskmanRun(&dMNN64TaskmanSetup);
}
