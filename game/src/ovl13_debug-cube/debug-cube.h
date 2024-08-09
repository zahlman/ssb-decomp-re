#ifndef _RESULTS_H_
#define _RESULTS_H_

#include <ssb_types.h>
#include <sys/obj_renderer.h>
#include <sys/thread6.h>

// EXTERN
extern intptr_t D_NF_800A5240;      // 0x800A5240
extern intptr_t lOverlay13ArenaLo;  // 0x80133170
extern intptr_t lOverlay13ArenaHi;  // 0x80369240

// DATA
// TODO!

// Stuff - where does it go?!?
typedef enum dbMenuItemKind
{
    dbMenuItemKindExitLabel,        // Label which exits menu when selected
    dbMenuItemKindNumeric,          // Number
    dbMenuItemKindString = 3,       // String
    dbMenuItemKindLabel,            // Label
    dbMenuItemKindNumericNoSelect   // Number with no A press?

} dbMenuItemKind;

typedef struct dbMenuItem
{
    s32 type_maybe;
    void (*proc_a)();
    void* label;
    s32 *value;
    f32 min;
    f32 max;
    s32 unknown18;
} dbMenuItem;

#define GetAddressFromOffset(file_ptr, offset) \
((int*)((intptr_t)(file_ptr) + (intptr_t)(offset))) \

#endif