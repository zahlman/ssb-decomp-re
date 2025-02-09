#include <gm/generic.h>
#include <lb/library.h>

// 0x8018E480
LBFileNode sSCVSBattleStatusBuffer[100];

// 0x8018E7A0
LBFileNode sSCVSBattleForceStatusBuffer[7];

// 0x8018E330
void scVSBattleSetupFiles(void)
{
	LBRelocSetup rl_setup;

	rl_setup.table_addr = (uintptr_t)&lLBRelocTableAddr;
	rl_setup.table_files_num = (uintptr_t)&lLBRelocTableFilesNum;
	rl_setup.file_heap = NULL;
	rl_setup.file_heap_size = 0;
	rl_setup.status_buffer = sSCVSBattleStatusBuffer;
	rl_setup.status_buffer_size = ARRAY_COUNT(sSCVSBattleStatusBuffer);
	rl_setup.force_status_buffer = sSCVSBattleForceStatusBuffer;
	rl_setup.force_status_buffer_size = ARRAY_COUNT(sSCVSBattleForceStatusBuffer);

	lbRelocInitSetup(&rl_setup);
	lbRelocLoadFilesExtern
	(
		dGMCommonFileIDs,
		ARRAY_COUNT(dGMCommonFileIDs),
		gGMCommonFiles,
		syTaskmanMalloc
		(
			lbRelocGetAllocSize
			(
				dGMCommonFileIDs,
				ARRAY_COUNT(dGMCommonFileIDs)
			),
			0x10
		)
	);
}
