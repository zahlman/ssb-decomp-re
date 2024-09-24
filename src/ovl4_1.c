#include <lb/library.h>

extern void *gGMCommonFiles[];
extern u32 dGMCommonFileIDs[8];

lbFileNode D_ovl4_8018E480[100];
lbFileNode D_ovl4_8018E7A0[7];

// 8018E330
void func_ovl4_8018E330(void)
{
	lbRelocSetup rldm_setup;

	rldm_setup.table_addr = (s32)&lLBRelocTableAddr;
	rldm_setup.table_files_num = (u32)&lLBRelocTableFilesNum;
	rldm_setup.file_heap = NULL;
	rldm_setup.file_heap_size = 0;
	rldm_setup.status_buf = D_ovl4_8018E480;
	rldm_setup.status_buf_size = ARRAY_COUNT(D_ovl4_8018E480);
	rldm_setup.force_buf = D_ovl4_8018E7A0;
	rldm_setup.force_buf_size = ARRAY_COUNT(D_ovl4_8018E7A0);

	lbRelocInitSetup(&rldm_setup);
	lbRelocLoadFilesExtern(dGMCommonFileIDs, ARRAY_COUNT(dGMCommonFileIDs), gGMCommonFiles, gsMemoryAlloc(lbRelocGetAllocSize(dGMCommonFileIDs, ARRAY_COUNT(dGMCommonFileIDs)), 0x10));
}