#include <sys/develop.h>
#include <ft/fighter.h>
#include <gm/gmsound.h>
#include <gr/ground.h>
#include <sc/scene.h>
#include <lb/library.h>
#include <sys/video.h>

#include "debug.h"

// Externs
extern intptr_t D_NF_800A5240;      // 0x800A5240
extern intptr_t lOverlay14ArenaLo;  // 0x80133130
extern intptr_t lOverlay14ArenaHi;  // 0x80369240

extern void gcDefaultFuncRun(UNUSED GObj* arg0);
extern FTCreateDesc dFTManagerDefaultFighterDesc;
extern sb32 gMNDebugMenuIsMenuOpen; // isMenuShown
extern void dbMenuCreateMenu(s32, s32, s32, void*, s32);
extern dbMenuDestroyMenu();

// Forward declarations
void dbBattleStartBattle();

// Data

// 0x80132690
s32 gMNDebugBattleExitInterrupt = 0;

// 0x80132694
s8 gMNDebugBattleMenuValueScene = 0; // scene

// 0x80132698
s32 gMNDebugBattleCurrentAnimation = 0x0002000A;

// 0x8013269C
char* dMNDebugBattleFighterKindStrings[27] = {
	" Mario",
	" Fox",
	" Donkey",
	" Samus",
	" Luigi",
	" Link",
	" Yoshi",
	" Captain",
	" Kirby",
	" Pikacyu",
	" Purin",
	" Nes",
	" Boss",
	" Metal",
	" NMario",
	" NFox",
	" NDonkey",
	" NSamus",
	" NLuigi",
	" NLink",
	" NYoshi",
	" NCaptain",
	" NKirby",
	" NPikacyu",
	" NPurin",
	" NNes",
	" GDonkey"
};

// 0x80132708
char* dMNDebugBattlePlayerKindStrings[6] = {
	"Man",
	"Com",
	"Not",
	"Demo",
	"Key",
	"GameKey"
};

// 0x80132720
char* dMNDebugBattleSceneStrings[6] = {
	"VS mode",
	"1P mode",
	"Staffroll",
	"Explain",
	"AutoDemo",
	"Congra"
};

// 0x80132738
char* dMNDebugBattleStageStrings[18] = {
	"S:Link",
	"S:Yoshi",
	"S:Fox",
	"S:Bonus1",
	"S:MarioBros",
	"S:Pikacyu",
	"S:GDonkey",
	"S:Bonus2",
	"S:Kirby",
	"S:Samus",
	"S:Metal",
	"S:Bonus3",
	"S:Zako",
	"S:Boss",
	"S:Luigi",
	"S:Nes",
	"S:Purin",
	"S:Captain"
};

// 0x80132780
dbMenuItem dMNDebugBattleMenuItems[15] = {
	{ dbMenuItemKindStringByte,  dbBattleStartBattle, (char*) dMNDebugBattleSceneStrings,       (void*) &gMNDebugBattleMenuValueScene,            0.0F, 5.0F,  0 },
	{ dbMenuItemKindNumericByte, 0,                        (char*) "BattleTime %3d",                 (void*) &gSCManagerTransferBattleState.time_limit,         1.0F, 60.0F, 0 },
	{ dbMenuItemKindStringByte,  0,                        (char*) dMNDebugBattleStageStrings,       (void*) &gSCManagerSceneData.spgame_stage,                 0.0F, 17.0F, 0 },
	{ dbMenuItemKindStringByte,  0,                        (char*) dMNDebugBattlePlayerKindStrings,  (void*) &gSCManagerTransferBattleState.players[0].pkind, 0.0F, 5.0F,  0 },
	{ dbMenuItemKindStringByte,  0,                        (char*) dMNDebugBattleFighterKindStrings, (void*) &gSCManagerTransferBattleState.players[0].fkind, 0.0F, 26.0F, 0 },
	{ dbMenuItemKindNumericByte, 0,                        (char*) "  %1d",                          (void*) &gSCManagerTransferBattleState.players[0].costume, 0.0F, 10.0F, 0 },
	{ dbMenuItemKindStringByte,  0,                        (char*) dMNDebugBattlePlayerKindStrings,  (void*) &gSCManagerTransferBattleState.players[1].pkind, 0.0F, 5.0F,  0 },
	{ dbMenuItemKindStringByte,  0,                        (char*) dMNDebugBattleFighterKindStrings, (void*) &gSCManagerTransferBattleState.players[1].fkind, 0.0F, 26.0F, 0 },
	{ dbMenuItemKindNumericByte, 0,                        (char*) "  %1d",                          (void*) &gSCManagerTransferBattleState.players[1].costume, 0.0F, 10.0F, 0 },
	{ dbMenuItemKindStringByte,  0,                        (char*) dMNDebugBattlePlayerKindStrings,  (void*) &gSCManagerTransferBattleState.players[2].pkind, 0.0F, 5.0F,  0 },
	{ dbMenuItemKindStringByte,  0,                        (char*) dMNDebugBattleFighterKindStrings, (void*) &gSCManagerTransferBattleState.players[2].fkind, 0.0F, 26.0F, 0 },
	{ dbMenuItemKindNumericByte, 0,                        (char*) "  %1d",                          (void*) &gSCManagerTransferBattleState.players[2].costume, 0.0F, 10.0F, 0 },
	{ dbMenuItemKindStringByte,  0,                        (char*) dMNDebugBattlePlayerKindStrings,  (void*) &gSCManagerTransferBattleState.players[3].pkind, 0.0F, 5.0F,  0 },
	{ dbMenuItemKindStringByte,  0,                        (char*) dMNDebugBattleFighterKindStrings, (void*) &gSCManagerTransferBattleState.players[3].fkind, 0.0F, 26.0F, 0 },
	{ dbMenuItemKindNumericByte, 0,                        (char*) "  %1d",                          (void*) &gSCManagerTransferBattleState.players[3].costume, 0.0F, 10.0F, 0 }
};

// 0x80132924
s32 dMNDebugBattleInitialFtKinds[4] = { nFTKindMario, nFTKindDonkey, nFTKindSamus, nFTKindFox };

// 0x80132934
SYVideoSetup D_ovl14_80132934 = { 0x80392a00, 0x803b6900, 0x803da800, 0x00000000, 0x00000140, 0x000000f0, 0x00016a99 };

// 0x80132950
scRuntimeInfo D_ovl14_80132950 = {

	0x00000000, 0x8000a5e4, 0x8000a340, 0x80133130,
	0x00000000, 0x00000001, 0x00000002, 0x00004000,
	0x00002000, 0x00000000, 0x00000000, 0x00008000,
	0x00020000, 0x0000c000, 0x80131b00, 0x80004310,
	0x00000008, 0x00000600, 0x00000008, 0x00000000,
	0x00000020, 0x00000020, 0x00000088, 0x00000100,
	0x800d5cac, 0x00000000, 0x00000400, 0x000000a0,
	0x00000100, 0x00000088, 0x00000007, 0x0000006c,
	0x00000008, 0x00000090, 0x8013239c
};

// BSS

// 0x80132C20
u32 D_ovl14_80132C20[2];

// 0x80132C28
u32 D_ovl14_80132C28[150];

// 0x80132E80
u32 D_ovl14_80132E80[150];

// 0x801330D8
u32 D_ovl14_801330D8[7];

// 0x801330F8
u32 D_ovl14_801330F8[6];

// 0x80133110
dbFighter gMNDebugBattleFighters[4];

// 0x80131B00
void dbBattleSetupDisplaylist(Gfx **display_list)
{
	gSPSetGeometryMode(display_list[0]++, G_LIGHTING);
	ftDisplayLightsDrawReflect(display_list, scSubsysFighterGetLightAngleX(), scSubsysFighterGetLightAngleY());
}

// 0x80131B58
void dbBattleStartBattle()
{
	s32 i;

	gMNDebugBattleExitInterrupt = 1;
	gSCManagerTransferBattleState.pl_count = gSCManagerTransferBattleState.cp_count = 0;

	for (i = 0; i < 4; i++)
	{
		switch (gSCManagerTransferBattleState.players[i].pkind)
		{
			case nFTPlayerKindMan:
				gSCManagerTransferBattleState.pl_count++;
				break;
			case nFTPlayerKindCom:
				gSCManagerTransferBattleState.cp_count++;
				break;
		}

		gSCManagerTransferBattleState.players[i].team = i;
		gSCManagerTransferBattleState.players[i].color = i;
		gSCManagerTransferBattleState.players[i].tag = i;
	}

	gSCManagerTransferBattleState.is_team_battle = FALSE;
}

// 0x80131CD8
s32 dbBattleSetShade(s32 port_id)
{
	s32 i, shade;

	for (i = shade = 0; i != ARRAY_COUNT(gSCManagerTransferBattleState.players); i++)
	{
	loop:
		if (i == port_id)
			continue;

		if
		(
			(gSCManagerTransferBattleState.players[i].fkind == gSCManagerTransferBattleState.players[port_id].fkind) &&
			(gSCManagerTransferBattleState.players[i].costume == gSCManagerTransferBattleState.players[port_id].costume) &&
			(gSCManagerTransferBattleState.players[i].shade == shade)
		)
		{
			shade++, i = 0;
			goto loop;
		}
	}
	gSCManagerTransferBattleState.players[port_id].shade = shade;
	return shade;
}

// 0x80131D74
s32 dbBattleGetUnlockedCharsCountForMask(u16 mask)
{
	s32 i;
	s32 unlocked_chars;

	for (i = 0, unlocked_chars = 0; i < 16; i++, mask = mask >> 1)
	{
		if (mask & 1)
			unlocked_chars++;
	}

	return unlocked_chars;
}

// 0x80131DEC
s32 dbBattleGetMissingFtKind(u16 mask_1, u16 mask_2, s32 missing_index)
{
	s32 fkind = -1;
	missing_index = missing_index + 1;

	do
	{
		fkind += 1;

		if ((mask_1 & gmSaveChrMask(fkind)) && !(mask_2 & gmSaveChrMask(fkind)))
			missing_index -= 1;
	}
	while (missing_index != 0);

	return fkind;
}

// 0x80131E38
void dbBattleSetDemoFtKinds()
{
	s32 non_recently_demoed_count;
	u16 unlocked_mask = (gSCManagerBackupData.fighter_mask | LBBACKUP_CHARACTER_MASK_STARTER);

	if (unlocked_mask == gSCManagerSceneData.demo_mask_prev)
		gSCManagerSceneData.demo_mask_prev = 0;

	non_recently_demoed_count = dbBattleGetUnlockedCharsCountForMask(unlocked_mask) - dbBattleGetUnlockedCharsCountForMask(gSCManagerSceneData.demo_mask_prev);

	gSCManagerSceneData.demo_fkind[0] = dbBattleGetMissingFtKind(unlocked_mask, gSCManagerSceneData.demo_mask_prev, mtTrigGetRandomIntRange(non_recently_demoed_count));

	if (gSCManagerSceneData.demo_mask_prev == 0)
		gSCManagerSceneData.demo_first_fkind = gSCManagerSceneData.demo_fkind[0];

	gSCManagerSceneData.demo_mask_prev |= gmSaveChrMask(gSCManagerSceneData.demo_fkind[0]);

	non_recently_demoed_count = dbBattleGetUnlockedCharsCountForMask(unlocked_mask) - dbBattleGetUnlockedCharsCountForMask(gSCManagerSceneData.demo_mask_prev);

	if (non_recently_demoed_count == 0)
		gSCManagerSceneData.demo_fkind[1] = gSCManagerSceneData.demo_first_fkind;
	else
	{
		gSCManagerSceneData.demo_fkind[1] = dbBattleGetMissingFtKind(unlocked_mask, gSCManagerSceneData.demo_mask_prev, mtTrigGetRandomIntRange(non_recently_demoed_count));
		gSCManagerSceneData.demo_mask_prev |= gmSaveChrMask(gSCManagerSceneData.demo_fkind[1]);
	}
}

// 0x80131F3C
void dbBattleMain(GObj* arg0)
{
	void **figatree_heap;
	s32 i;
	GObj* fighter_gobj;
	FTStruct *fp;

	if (gSysController.button_tap & START_BUTTON)
	{
		if (gMNDebugMenuIsMenuOpen != FALSE)
			dbBattleStartBattle();
		else
			dbMenuCreateMenu(0x1E, 0x14, 0x55, &dMNDebugBattleMenuItems, 0xF);
	}

	for (i = 0; i < 4; i++)
	{
		if (gSCManagerTransferBattleState.players[i].fkind != gMNDebugBattleFighters[i].fkind)
		{
			FTCreateDesc spawn_info = dFTManagerDefaultFighterDesc;
			fighter_gobj = gMNDebugBattleFighters[i].fighter_gobj;
			fp = ftGetStruct(fighter_gobj);

			figatree_heap = fp->figatree_heap;

			ftManagerDestroyFighter(fighter_gobj);

			spawn_info.fkind = gSCManagerTransferBattleState.players[i].fkind;
			spawn_info.pos.x = (i * 400.0f) - 600.0f;

			if (ftParamGetCostumeDevelop(spawn_info.fkind) < gSCManagerTransferBattleState.players[i].costume)
				gSCManagerTransferBattleState.players[i].costume = ftParamGetCostumeDevelop(gSCManagerTransferBattleState.players[i].fkind);

			spawn_info.costume = gSCManagerTransferBattleState.players[i].costume;
			spawn_info.shade = dbBattleSetShade(i);
			spawn_info.figatree_heap = figatree_heap;
			gMNDebugBattleFighters[i].fighter_gobj = ftManagerMakeFighter(&spawn_info);

			gMNDebugBattleFighters[i].fkind = gSCManagerTransferBattleState.players[i].fkind;
			gMNDebugBattleFighters[i].costume_index = gSCManagerTransferBattleState.players[i].costume;
		}

		if (gSCManagerTransferBattleState.players[i].costume != gMNDebugBattleFighters[i].costume_index)
		{
			dbBattleSetShade(i);
			ftParamInitModelTexturePartsAll(gMNDebugBattleFighters[i].fighter_gobj, gSCManagerTransferBattleState.players[i].costume, gSCManagerTransferBattleState.players[i].shade);
			gMNDebugBattleFighters[i].costume_index = gSCManagerTransferBattleState.players[i].costume;
		}
	}

	if (gSysController.button_tap & U_CBUTTONS)
		scSubsysFighterSetStatus(gMNDebugBattleFighters[1].fighter_gobj, gMNDebugBattleCurrentAnimation++);

	if (gSysController.button_tap & D_CBUTTONS)
		scSubsysFighterSetStatus(gMNDebugBattleFighters[1].fighter_gobj, gMNDebugBattleCurrentAnimation--);

	if (gMNDebugBattleExitInterrupt != 0)
	{
		dbMenuDestroyMenu();

		gSCManagerSceneData.scene_prev = gSCManagerSceneData.scene_curr;

		switch (gMNDebugBattleMenuValueScene)
		{
			case dbBattleSceneVsMode:
				gSCManagerSceneData.scene_curr = nSCKindDebugMaps;
				break;
			case dbBattleScene1PMode:
				gSCManagerSceneData.scene_curr = nSCKind1PGame;
				gSCManagerSceneData.player = 0;
				gSCManagerSceneData.fkind = gSCManagerTransferBattleState.players[0].fkind;
				gSCManagerSceneData.costume = gSCManagerTransferBattleState.players[0].costume;
				break;
			case dbBattleSceneStaffroll:
				gSCManagerSceneData.scene_curr = nSCKindStaffroll;
				break;
			case dbBattleSceneExplain:
				gSCManagerSceneData.scene_curr = nSCKindExplain;
				gSCManagerTransferBattleState.is_team_battle = FALSE;
				break;
			case dbBattleSceneAutoDemo:
				dbBattleSetDemoFtKinds();
				gSCManagerSceneData.scene_curr = nSCKindAutoDemo;
				gSCManagerTransferBattleState.is_team_battle = FALSE;
				break;
			case dbBattleSceneCongra:
				gSCManagerSceneData.scene_curr = nSCKindCongra;
				break;
		}

		syTaskmanSetLoadScene();
	}
}

// 0x80132238
void dbBattleSyncCostumes(s32 arg0)
{
	s32 i;
	u8 temp_v0;

	for (i = 0; i < 4; i++)
	{
		if (gSCManagerTransferBattleState.players[i].costume != gMNDebugBattleFighters[i].costume_index)
		{
			if (gSCManagerTransferBattleState.players[i].costume == 10)
				gSCManagerTransferBattleState.players[i].costume = ftParamGetCostumeDevelop(gSCManagerTransferBattleState.players[i].fkind);

			else if (ftParamGetCostumeDevelop(gSCManagerTransferBattleState.players[i].fkind) < gSCManagerTransferBattleState.players[i].costume)
				gSCManagerTransferBattleState.players[i].costume = 0;
		}
	}
}

// 0x801322DC
GObj* dbBattleCreateViewport(void (*proc)(GObj*))
{
	GObj *camera_gobj = gcMakeCameraGObj(0x400, gcDefaultFuncRun, 0xF, 0x80000000U, func_80017DBC, 0x32, 0x00048600, -1, 1, 0, proc, 1, 0);
	CObj *cobj;

	if (camera_gobj == NULL)
		return NULL;

	cobj = CObjGetStruct(camera_gobj);
	cobj->flags = 5;
	cobj->vec.at.y = 600.0f;
	cobj->vec.eye.z = 3000.0f;
	cobj->vec.eye.y = 600.0f;

	return camera_gobj;
}

// 0x8013239C
void dbBattleInit()
{
	s32 i;
	LBRelocSetup rl_setup;
	GObj *main_gobj;

	rl_setup.table_addr = (uintptr_t)&lLBRelocTableAddr;
	rl_setup.table_files_num = (uintptr_t)&lLBRelocTableFilesNum;
	rl_setup.file_heap = NULL;
	rl_setup.file_heap_size = 0;
	rl_setup.status_buffer = (LBFileNode*) &D_ovl14_80132C28;
	rl_setup.status_buffer_size = 0x96;
	rl_setup.force_status_buffer = (LBFileNode*) &D_ovl14_801330D8;
	rl_setup.force_status_buffer_size = 7;
	lbRelocInitSetup(&rl_setup);

	main_gobj = gcMakeGObjSPAfter(0, dbBattleMain, 0xF, 0x80000000);
	gcAddGObjProcess(main_gobj, dbBattleSyncCostumes, 1, 0);

	gcMakeDefaultCameraGObj(0xF, 0x80000000, 0x64, 2, 0xFF);
	efParticleInitAll();
	dbBattleCreateViewport(0);
	efManagerInitEffects();
	ftManagerAllocFighter(3, 4);

	for (i = nFTKindMario; i <= nFTKindGDonkey; i++)
		ftManagerSetupFilesAllKind(i);

	for (i = 0; i < ARRAY_COUNT(gSCManagerTransferBattleState.players); i++)
	{
		gSCManagerTransferBattleState.players[i].team = i;
		gSCManagerTransferBattleState.players[i].pkind = 0;
		gSCManagerTransferBattleState.players[i].shade = 0;
		gSCManagerTransferBattleState.players[i].fkind = dMNDebugBattleInitialFtKinds[i];
	}

	for (i = 0; i < ARRAY_COUNT(gSCManagerTransferBattleState.players); i++)
	{
		FTCreateDesc spawn_info = dFTManagerDefaultFighterDesc;
		spawn_info.fkind = gSCManagerTransferBattleState.players[i].fkind;
		spawn_info.costume = gSCManagerTransferBattleState.players[i].costume;
		spawn_info.pos.x = (i * 400.0f) - 600.0f;
		spawn_info.figatree_heap = syTaskmanMalloc(gFTManagerFigatreeHeapSize, 0x10);
		gMNDebugBattleFighters[i].fighter_gobj = ftManagerMakeFighter(&spawn_info);

		gMNDebugBattleFighters[i].fkind = gSCManagerTransferBattleState.players[i].fkind;
		gMNDebugBattleFighters[i].costume_index = gSCManagerTransferBattleState.players[i].costume;
	}

	dbMenuInitMenu();
	dbMenuCreateMenu(0x1E, 0x14, 0x55, &dMNDebugBattleMenuItems, 0xF);
	scSubsysFighterSetLightParams(45.0F, 45.0F, 0xFF, 0xFF, 0xFF, 0xFF);
}

// 0x80132638
void dbBattleStartScene()
{
	D_ovl14_80132934.zbuffer = syVideoGetZBuffer(6400);
	syVideoInit(&D_ovl14_80132934);
	D_ovl14_80132950.arena_size = (u32) ((uintptr_t)&lOverlay14ArenaHi - (uintptr_t)&lOverlay14ArenaLo);
	syTaskmanRun(&D_ovl14_80132950);
}
