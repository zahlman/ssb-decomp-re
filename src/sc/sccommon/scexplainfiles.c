

#include <gm/generic.h>
#include <lb/library.h>

// // // // // // // // // // // //
//                               //
//   GLOBAL / STATIC VARIABLES   //
//                               //
// // // // // // // // // // // //

// 0x8018EA30
LBFileNode sSCExplainStatusBuffer[50];

// 0x8018EBC0
LBFileNode sSCExplainForceStatusBuffer[7];

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x8018E640
void scExplainSetupFiles(void)
{
    LBRelocSetup rl_setup;

    rl_setup.table_addr = (uintptr_t)&lLBRelocTableAddr;
    rl_setup.table_files_num = (uintptr_t)&lLBRelocTableFilesNum;
    rl_setup.file_heap = NULL;
    rl_setup.file_heap_size = 0;
    rl_setup.status_buffer = sSCExplainStatusBuffer;
    rl_setup.status_buffer_size = ARRAY_COUNT(sSCExplainStatusBuffer);
    rl_setup.force_status_buffer = sSCExplainForceStatusBuffer;
    rl_setup.force_status_buffer_size = ARRAY_COUNT(sSCExplainForceStatusBuffer);

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