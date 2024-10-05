#include <sys/develop.h>
#include <gr/ground.h>
#include <sc/scene.h>
#include <lb/library.h>
#include <sys/system_00.h>

// Externs
extern s32 gMNNoControllerFiles[];
extern u32 D_ovl11_800D67D8[];
extern lbFileNode D_ovl11_800D6AF8;

// Data
u32 D_ovl11_800D67B0[1] = { 0x00A9 };

// 0x800D6660
void mnNoControllerLoadFiles()
{
	lbRelocSetup rldmSetup;

	rldmSetup.table_addr = (uintptr_t)&lLBRelocTableAddr;
	rldmSetup.table_files_num = (uintptr_t)&lLBRelocTableFilesNum;
	rldmSetup.file_heap = NULL;
	rldmSetup.file_heap_size = 0;
	rldmSetup.status_buffer = (lbFileNode*) &D_ovl11_800D67D8;
	rldmSetup.status_buffer_size = 0x64;
	rldmSetup.force_status_buffer = (lbFileNode*) &D_ovl11_800D6AF8;
	rldmSetup.force_status_buffer_size = 7;
	lbRelocInitSetup(&rldmSetup);
	lbRelocLoadFilesExtern(D_ovl11_800D67B0, ARRAY_COUNT(D_ovl11_800D67B0), gMNNoControllerFiles, syTasklogMalloc(lbRelocGetAllocSize(D_ovl11_800D67B0, ARRAY_COUNT(D_ovl11_800D67B0)), 0x10U));
}