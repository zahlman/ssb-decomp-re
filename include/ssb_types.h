#ifndef SSB64_TYPES_H
#define SSB64_TYPES_H

#include <PR/ultratypes.h>

// When building with IDO, define some stdint types
#ifdef __sgi
typedef u32 uintptr_t;
typedef s32 intptr_t;
#else
#include <stdint.h>
#endif /* __sgi */

// until there's a better place to put the math types...
typedef f32 Mtx4f[4][4];
typedef f32 Mtx44f[4][4]; // Same thing as above but I'm terrible at matrices and I need it to be extra specific

typedef struct Vec3h
{
    s16 x, y, z;

} Vec3h;

typedef struct Vec3i
{
    s32 x, y, z;

} Vec3i;

typedef struct Vec3f
{
    f32 x, y, z;

} Vec3f;

typedef struct Vec2b
{
    s8 x, y;

} Vec2b;

typedef struct Vec2f
{
    f32 x, y;

} Vec2f;

typedef struct Vec2h
{
    s16 x, y;

} Vec2h;

typedef struct Vec2i
{
    s32 x, y;

} Vec2i;

// boolean quick types

typedef  s8  sb8; // Signed  8-bit boolean
typedef s16 sb16; // Signed 16-bit boolean
typedef s32 sb32; // Signed 32-bit boolean

typedef u8   ub8; // Unsigned  8-bit boolean
typedef u16 ub16; // Unsigned 16-bit boolean
typedef u32 ub32; // Unsigned 32-bit boolean

// Gfx color types

enum syColorRGBIndex
{
    syColorRGBIndexR,
    syColorRGBIndexG,
    syColorRGBIndexB,
    syColorRGBIndexA
};

typedef struct syColorRGB
{
    u8 r, g, b;

} syColorRGB;

typedef struct syColorRGBPair
{
    syColorRGB prim, env;

} syColorRGBPair;

typedef union syColorRGBA
{
    struct
    {
        u8 r, g, b, a;
    };
    u32 pack;

} syColorRGBA;

typedef struct syRectangle
{
    s32 ulx, uly;
    s32 lrx, lry;

} syRectangle;

typedef struct syPixelPair
{
    u32 chunk0;
    u32 chunk1;

} syPixelPair;

typedef struct CameraVec7
{
    Vec3f eye;
    Vec3f at;
    f32 upx;

} CameraVec7;

#endif /* SSB64_TYPES_H */
