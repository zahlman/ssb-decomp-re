.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section .text

.align 4

# Text Sections
#  0x80131B00 -> 0x80135260

glabel gmCreditsCheckUnpause
  /* 17F200 80131B00 3C0E8014 */       lui $t6, %hi(gCreditsPlayer)
  /* 17F204 80131B04 91CEA904 */       lbu $t6, %lo(gCreditsPlayer)($t6)
  /* 17F208 80131B08 3C028004 */       lui $v0, %hi(gPlayerControllers + 2)
  /* 17F20C 80131B0C 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 17F210 80131B10 000E7880 */       sll $t7, $t6, 2
  /* 17F214 80131B14 01EE7821 */      addu $t7, $t7, $t6
  /* 17F218 80131B18 000F7840 */       sll $t7, $t7, 1
  /* 17F21C 80131B1C 004F1021 */      addu $v0, $v0, $t7
  /* 17F220 80131B20 9442522A */       lhu $v0, %lo(gPlayerControllers + 2)($v0)
  /* 17F224 80131B24 AFBF001C */        sw $ra, 0x1c($sp)
  /* 17F228 80131B28 AFB00018 */        sw $s0, 0x18($sp)
  /* 17F22C 80131B2C 3058F000 */      andi $t8, $v0, 0xf000
  /* 17F230 80131B30 1300001A */      beqz $t8, .L80131B9C
  /* 17F234 80131B34 24030001 */     addiu $v1, $zero, 1
  /* 17F238 80131B38 3C048014 */       lui $a0, %hi(gCreditsStaffRollGObj)
  /* 17F23C 80131B3C 8C84A8C8 */        lw $a0, %lo(gCreditsStaffRollGObj)($a0)
  /* 17F240 80131B40 10800003 */      beqz $a0, .L80131B50
  /* 17F244 80131B44 00000000 */       nop 
  /* 17F248 80131B48 0C002CAE */       jal func_8000B2B8
  /* 17F24C 80131B4C 00000000 */       nop 
  .L80131B50:
  /* 17F250 80131B50 3C108004 */       lui $s0, %hi(gOMObjCommonLinks + (0x03 * 4))
  /* 17F254 80131B54 8E1066FC */        lw $s0, %lo(gOMObjCommonLinks + (0x03 * 4))($s0)
  /* 17F258 80131B58 12000006 */      beqz $s0, .L80131B74
  /* 17F25C 80131B5C 00000000 */       nop 
  .L80131B60:
  /* 17F260 80131B60 0C002CAE */       jal func_8000B2B8
  /* 17F264 80131B64 02002025 */        or $a0, $s0, $zero
  /* 17F268 80131B68 8E100004 */        lw $s0, 4($s0)
  /* 17F26C 80131B6C 1600FFFC */      bnez $s0, .L80131B60
  /* 17F270 80131B70 00000000 */       nop 
  .L80131B74:
  /* 17F274 80131B74 3C108004 */       lui $s0, %hi(gOMObjCommonLinks + (0x04 * 4))
  /* 17F278 80131B78 8E106700 */        lw $s0, %lo(gOMObjCommonLinks + (0x04 * 4))($s0)
  /* 17F27C 80131B7C 52000007 */      beql $s0, $zero, .L80131B9C
  /* 17F280 80131B80 00001825 */        or $v1, $zero, $zero
  .L80131B84:
  /* 17F284 80131B84 0C002CAE */       jal func_8000B2B8
  /* 17F288 80131B88 02002025 */        or $a0, $s0, $zero
  /* 17F28C 80131B8C 8E100004 */        lw $s0, 4($s0)
  /* 17F290 80131B90 1600FFFC */      bnez $s0, .L80131B84
  /* 17F294 80131B94 00000000 */       nop 
  /* 17F298 80131B98 00001825 */        or $v1, $zero, $zero
  .L80131B9C:
  /* 17F29C 80131B9C 8FBF001C */        lw $ra, 0x1c($sp)
  /* 17F2A0 80131BA0 8FB00018 */        lw $s0, 0x18($sp)
  /* 17F2A4 80131BA4 27BD0020 */     addiu $sp, $sp, 0x20
  /* 17F2A8 80131BA8 03E00008 */        jr $ra
  /* 17F2AC 80131BAC 00601025 */        or $v0, $v1, $zero

glabel func_ovl59_80131BB0
  /* 17F2B0 80131BB0 C4A00000 */      lwc1 $f0, ($a1)
  /* 17F2B4 80131BB4 C4840000 */      lwc1 $f4, ($a0)
  /* 17F2B8 80131BB8 C4A20004 */      lwc1 $f2, 4($a1)
  /* 17F2BC 80131BBC C4880010 */      lwc1 $f8, 0x10($a0)
  /* 17F2C0 80131BC0 46002182 */     mul.s $f6, $f4, $f0
  /* 17F2C4 80131BC4 C4AC0008 */      lwc1 $f12, 8($a1)
  /* 17F2C8 80131BC8 3C013F00 */       lui $at, (0x3F000000 >> 16) # 0.5
  /* 17F2CC 80131BCC 46024282 */     mul.s $f10, $f8, $f2
  /* 17F2D0 80131BD0 C4880020 */      lwc1 $f8, 0x20($a0)
  /* 17F2D4 80131BD4 460A3100 */     add.s $f4, $f6, $f10
  /* 17F2D8 80131BD8 460C4182 */     mul.s $f6, $f8, $f12
  /* 17F2DC 80131BDC C4880030 */      lwc1 $f8, 0x30($a0)
  /* 17F2E0 80131BE0 46062280 */     add.s $f10, $f4, $f6
  /* 17F2E4 80131BE4 C4840004 */      lwc1 $f4, 4($a0)
  /* 17F2E8 80131BE8 460A4380 */     add.s $f14, $f8, $f10
  /* 17F2EC 80131BEC 46002182 */     mul.s $f6, $f4, $f0
  /* 17F2F0 80131BF0 C4880014 */      lwc1 $f8, 0x14($a0)
  /* 17F2F4 80131BF4 46024282 */     mul.s $f10, $f8, $f2
  /* 17F2F8 80131BF8 C4880024 */      lwc1 $f8, 0x24($a0)
  /* 17F2FC 80131BFC 460A3100 */     add.s $f4, $f6, $f10
  /* 17F300 80131C00 460C4182 */     mul.s $f6, $f8, $f12
  /* 17F304 80131C04 C4880034 */      lwc1 $f8, 0x34($a0)
  /* 17F308 80131C08 46062280 */     add.s $f10, $f4, $f6
  /* 17F30C 80131C0C C484000C */      lwc1 $f4, 0xc($a0)
  /* 17F310 80131C10 460A4400 */     add.s $f16, $f8, $f10
  /* 17F314 80131C14 46002182 */     mul.s $f6, $f4, $f0
  /* 17F318 80131C18 C488001C */      lwc1 $f8, 0x1c($a0)
  /* 17F31C 80131C1C 44810000 */      mtc1 $at, $f0 # 0.5 to cop1
  /* 17F320 80131C20 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 17F324 80131C24 46024282 */     mul.s $f10, $f8, $f2
  /* 17F328 80131C28 C488002C */      lwc1 $f8, 0x2c($a0)
  /* 17F32C 80131C2C 460A3100 */     add.s $f4, $f6, $f10
  /* 17F330 80131C30 460C4182 */     mul.s $f6, $f8, $f12
  /* 17F334 80131C34 C488003C */      lwc1 $f8, 0x3c($a0)
  /* 17F338 80131C38 46062280 */     add.s $f10, $f4, $f6
  /* 17F33C 80131C3C 44812000 */      mtc1 $at, $f4 # 1.0 to cop1
  /* 17F340 80131C40 3C014420 */       lui $at, (0x44200000 >> 16) # 640.0
  /* 17F344 80131C44 460A4480 */     add.s $f18, $f8, $f10
  /* 17F348 80131C48 44814000 */      mtc1 $at, $f8 # 640.0 to cop1
  /* 17F34C 80131C4C 3C0143F0 */       lui $at, (0x43F00000 >> 16) # 480.0
  /* 17F350 80131C50 46122483 */     div.s $f18, $f4, $f18
  /* 17F354 80131C54 46127182 */     mul.s $f6, $f14, $f18
  /* 17F358 80131C58 00000000 */       nop 
  /* 17F35C 80131C5C 46083282 */     mul.s $f10, $f6, $f8
  /* 17F360 80131C60 44814000 */      mtc1 $at, $f8 # 480.0 to cop1
  /* 17F364 80131C64 46005102 */     mul.s $f4, $f10, $f0
  /* 17F368 80131C68 00000000 */       nop 
  /* 17F36C 80131C6C 46128182 */     mul.s $f6, $f16, $f18
  /* 17F370 80131C70 E4C40000 */      swc1 $f4, ($a2)
  /* 17F374 80131C74 46083282 */     mul.s $f10, $f6, $f8
  /* 17F378 80131C78 00000000 */       nop 
  /* 17F37C 80131C7C 46005102 */     mul.s $f4, $f10, $f0
  /* 17F380 80131C80 03E00008 */        jr $ra
  /* 17F384 80131C84 E4E40000 */      swc1 $f4, ($a3)

glabel func_ovl59_80131C88
  /* 17F388 80131C88 27BDFF48 */     addiu $sp, $sp, -0xb8
  /* 17F38C 80131C8C AFB00030 */        sw $s0, 0x30($sp)
  /* 17F390 80131C90 00808025 */        or $s0, $a0, $zero
  /* 17F394 80131C94 AFBF0034 */        sw $ra, 0x34($sp)
  /* 17F398 80131C98 C6040028 */      lwc1 $f4, 0x28($s0)
  /* 17F39C 80131C9C 8E070024 */        lw $a3, 0x24($s0)
  /* 17F3A0 80131CA0 8E060020 */        lw $a2, 0x20($s0)
  /* 17F3A4 80131CA4 E7A40010 */      swc1 $f4, 0x10($sp)
  /* 17F3A8 80131CA8 C606002C */      lwc1 $f6, 0x2c($s0)
  /* 17F3AC 80131CAC 2605001C */     addiu $a1, $s0, 0x1c
  /* 17F3B0 80131CB0 27A40038 */     addiu $a0, $sp, 0x38
  /* 17F3B4 80131CB4 E7A60014 */      swc1 $f6, 0x14($sp)
  /* 17F3B8 80131CB8 C6080030 */      lwc1 $f8, 0x30($s0)
  /* 17F3BC 80131CBC 0C006C92 */       jal hal_perspective_fast_f
  /* 17F3C0 80131CC0 E7A80018 */      swc1 $f8, 0x18($sp)
  /* 17F3C4 80131CC4 C60A0048 */      lwc1 $f10, 0x48($s0)
  /* 17F3C8 80131CC8 8E05003C */        lw $a1, 0x3c($s0)
  /* 17F3CC 80131CCC 8E060040 */        lw $a2, 0x40($s0)
  /* 17F3D0 80131CD0 8E070044 */        lw $a3, 0x44($s0)
  /* 17F3D4 80131CD4 E7AA0010 */      swc1 $f10, 0x10($sp)
  /* 17F3D8 80131CD8 C610004C */      lwc1 $f16, 0x4c($s0)
  /* 17F3DC 80131CDC 27A40078 */     addiu $a0, $sp, 0x78
  /* 17F3E0 80131CE0 E7B00014 */      swc1 $f16, 0x14($sp)
  /* 17F3E4 80131CE4 C6120050 */      lwc1 $f18, 0x50($s0)
  /* 17F3E8 80131CE8 E7B20018 */      swc1 $f18, 0x18($sp)
  /* 17F3EC 80131CEC C6040054 */      lwc1 $f4, 0x54($s0)
  /* 17F3F0 80131CF0 E7A4001C */      swc1 $f4, 0x1c($sp)
  /* 17F3F4 80131CF4 C6060058 */      lwc1 $f6, 0x58($s0)
  /* 17F3F8 80131CF8 E7A60020 */      swc1 $f6, 0x20($sp)
  /* 17F3FC 80131CFC C608005C */      lwc1 $f8, 0x5c($s0)
  /* 17F400 80131D00 0C00683C */       jal hal_look_at_f
  /* 17F404 80131D04 E7A80024 */      swc1 $f8, 0x24($sp)
  /* 17F408 80131D08 3C068014 */       lui $a2, %hi(gCreditsMatrix)
  /* 17F40C 80131D0C 24C6AA18 */     addiu $a2, $a2, %lo(gCreditsMatrix)
  /* 17F410 80131D10 27A40078 */     addiu $a0, $sp, 0x78
  /* 17F414 80131D14 0C00D260 */       jal guMtxCatF
  /* 17F418 80131D18 27A50038 */     addiu $a1, $sp, 0x38
  /* 17F41C 80131D1C 8FBF0034 */        lw $ra, 0x34($sp)
  /* 17F420 80131D20 8FB00030 */        lw $s0, 0x30($sp)
  /* 17F424 80131D24 27BD00B8 */     addiu $sp, $sp, 0xb8
  /* 17F428 80131D28 03E00008 */        jr $ra
  /* 17F42C 80131D2C 00000000 */       nop 

glabel func_ovl59_80131D30
  /* 17F430 80131D30 27BDFF48 */     addiu $sp, $sp, -0xb8
  /* 17F434 80131D34 AFB00030 */        sw $s0, 0x30($sp)
  /* 17F438 80131D38 00808025 */        or $s0, $a0, $zero
  /* 17F43C 80131D3C AFBF0034 */        sw $ra, 0x34($sp)
  /* 17F440 80131D40 AFA500BC */        sw $a1, 0xbc($sp)
  /* 17F444 80131D44 AFA600C0 */        sw $a2, 0xc0($sp)
  /* 17F448 80131D48 AFA700C4 */        sw $a3, 0xc4($sp)
  /* 17F44C 80131D4C C6040030 */      lwc1 $f4, 0x30($s0)
  /* 17F450 80131D50 8E070024 */        lw $a3, 0x24($s0)
  /* 17F454 80131D54 8E060020 */        lw $a2, 0x20($s0)
  /* 17F458 80131D58 8E05001C */        lw $a1, 0x1c($s0)
  /* 17F45C 80131D5C E7A40010 */      swc1 $f4, 0x10($sp)
  /* 17F460 80131D60 C6060034 */      lwc1 $f6, 0x34($s0)
  /* 17F464 80131D64 27A40078 */     addiu $a0, $sp, 0x78
  /* 17F468 80131D68 E7A60014 */      swc1 $f6, 0x14($sp)
  /* 17F46C 80131D6C C6080038 */      lwc1 $f8, 0x38($s0)
  /* 17F470 80131D70 E7A80018 */      swc1 $f8, 0x18($sp)
  /* 17F474 80131D74 C60A0040 */      lwc1 $f10, 0x40($s0)
  /* 17F478 80131D78 E7AA001C */      swc1 $f10, 0x1c($sp)
  /* 17F47C 80131D7C C6100044 */      lwc1 $f16, 0x44($s0)
  /* 17F480 80131D80 E7B00020 */      swc1 $f16, 0x20($sp)
  /* 17F484 80131D84 C6120048 */      lwc1 $f18, 0x48($s0)
  /* 17F488 80131D88 0C007149 */       jal hal_rotate_rpy_translate_scale_f
  /* 17F48C 80131D8C E7B20024 */      swc1 $f18, 0x24($sp)
  /* 17F490 80131D90 27B00038 */     addiu $s0, $sp, 0x38
  /* 17F494 80131D94 3C058014 */       lui $a1, %hi(gCreditsMatrix)
  /* 17F498 80131D98 24A5AA18 */     addiu $a1, $a1, %lo(gCreditsMatrix)
  /* 17F49C 80131D9C 02003025 */        or $a2, $s0, $zero
  /* 17F4A0 80131DA0 0C00D260 */       jal guMtxCatF
  /* 17F4A4 80131DA4 27A40078 */     addiu $a0, $sp, 0x78
  /* 17F4A8 80131DA8 02002025 */        or $a0, $s0, $zero
  /* 17F4AC 80131DAC 8FA500BC */        lw $a1, 0xbc($sp)
  /* 17F4B0 80131DB0 8FA600C0 */        lw $a2, 0xc0($sp)
  /* 17F4B4 80131DB4 0C04C6EC */       jal func_ovl59_80131BB0
  /* 17F4B8 80131DB8 8FA700C4 */        lw $a3, 0xc4($sp)
  /* 17F4BC 80131DBC 8FBF0034 */        lw $ra, 0x34($sp)
  /* 17F4C0 80131DC0 8FB00030 */        lw $s0, 0x30($sp)
  /* 17F4C4 80131DC4 27BD00B8 */     addiu $sp, $sp, 0xb8
  /* 17F4C8 80131DC8 03E00008 */        jr $ra
  /* 17F4CC 80131DCC 00000000 */       nop 

glabel func_ovl59_80131DD0
  /* 17F4D0 80131DD0 8C820084 */        lw $v0, 0x84($a0)
  /* 17F4D4 80131DD4 44806000 */      mtc1 $zero, $f12
  /* 17F4D8 80131DD8 3C0141E0 */       lui $at, (0x41E00000 >> 16) # 28.0
  /* 17F4DC 80131DDC 44817000 */      mtc1 $at, $f14 # 28.0 to cop1
  /* 17F4E0 80131DE0 3C01C1B0 */       lui $at, (0xC1B00000 >> 16) # -22.0
  /* 17F4E4 80131DE4 44818000 */      mtc1 $at, $f16 # -22.0 to cop1
  /* 17F4E8 80131DE8 3C014080 */       lui $at, (0x40800000 >> 16) # 4.0
  /* 17F4EC 80131DEC E4AC002C */      swc1 $f12, 0x2c($a1)
  /* 17F4F0 80131DF0 E4AC0020 */      swc1 $f12, 0x20($a1)
  /* 17F4F4 80131DF4 E4AC0014 */      swc1 $f12, 0x14($a1)
  /* 17F4F8 80131DF8 E4AC0008 */      swc1 $f12, 8($a1)
  /* 17F4FC 80131DFC E4AE001C */      swc1 $f14, 0x1c($a1)
  /* 17F500 80131E00 E4AE0004 */      swc1 $f14, 4($a1)
  /* 17F504 80131E04 44813000 */      mtc1 $at, $f6 # 4.0 to cop1
  /* 17F508 80131E08 C4440010 */      lwc1 $f4, 0x10($v0)
  /* 17F50C 80131E0C E4B00000 */      swc1 $f16, ($a1)
  /* 17F510 80131E10 E4B0000C */      swc1 $f16, 0xc($a1)
  /* 17F514 80131E14 46062000 */     add.s $f0, $f4, $f6
  /* 17F518 80131E18 44804000 */      mtc1 $zero, $f8
  /* 17F51C 80131E1C 3C014000 */       lui $at, (0x40000000 >> 16) # 2.0
  /* 17F520 80131E20 44815000 */      mtc1 $at, $f10 # 2.0 to cop1
  /* 17F524 80131E24 46000007 */     neg.s $f0, $f0
  /* 17F528 80131E28 E4A00028 */      swc1 $f0, 0x28($a1)
  /* 17F52C 80131E2C E4A00010 */      swc1 $f0, 0x10($a1)
  /* 17F530 80131E30 C442000C */      lwc1 $f2, 0xc($v0)
  /* 17F534 80131E34 4608103C */    c.lt.s $f2, $f8
  /* 17F538 80131E38 00000000 */       nop 
  /* 17F53C 80131E3C 45020004 */     bc1fl .L80131E50
  /* 17F540 80131E40 46001006 */     mov.s $f0, $f2
  /* 17F544 80131E44 10000002 */         b .L80131E50
  /* 17F548 80131E48 46001007 */     neg.s $f0, $f2
  /* 17F54C 80131E4C 46001006 */     mov.s $f0, $f2
  .L80131E50:
  /* 17F550 80131E50 460A0482 */     mul.s $f18, $f0, $f10
  /* 17F554 80131E54 3C014190 */       lui $at, (0x41900000 >> 16) # 18.0
  /* 17F558 80131E58 44812000 */      mtc1 $at, $f4 # 18.0 to cop1
  /* 17F55C 80131E5C 00000000 */       nop 
  /* 17F560 80131E60 46049080 */     add.s $f2, $f18, $f4
  /* 17F564 80131E64 E4A20024 */      swc1 $f2, 0x24($a1)
  /* 17F568 80131E68 03E00008 */        jr $ra
  /* 17F56C 80131E6C E4A20018 */      swc1 $f2, 0x18($a1)

glabel func_ovl59_80131E70
  /* 17F570 80131E70 44866000 */      mtc1 $a2, $f12
  /* 17F574 80131E74 C7AE0010 */      lwc1 $f14, 0x10($sp)
  /* 17F578 80131E78 AFA50004 */        sw $a1, 4($sp)
  /* 17F57C 80131E7C AFA7000C */        sw $a3, 0xc($sp)
  /* 17F580 80131E80 460E6101 */     sub.s $f4, $f12, $f14
  /* 17F584 80131E84 E4840000 */      swc1 $f4, ($a0)
  /* 17F588 80131E88 C7A6000C */      lwc1 $f6, 0xc($sp)
  /* 17F58C 80131E8C C7A80004 */      lwc1 $f8, 4($sp)
  /* 17F590 80131E90 46083281 */     sub.s $f10, $f6, $f8
  /* 17F594 80131E94 E48A0004 */      swc1 $f10, 4($a0)
  /* 17F598 80131E98 C7B00004 */      lwc1 $f16, 4($sp)
  /* 17F59C 80131E9C C7A4000C */      lwc1 $f4, 0xc($sp)
  /* 17F5A0 80131EA0 460E8482 */     mul.s $f18, $f16, $f14
  /* 17F5A4 80131EA4 00000000 */       nop 
  /* 17F5A8 80131EA8 460C2182 */     mul.s $f6, $f4, $f12
  /* 17F5AC 80131EAC 46069201 */     sub.s $f8, $f18, $f6
  /* 17F5B0 80131EB0 03E00008 */        jr $ra
  /* 17F5B4 80131EB4 E4880008 */      swc1 $f8, 8($a0)

glabel gmCreditsCheckCursorNameOverlap
  /* 17F5B8 80131EB8 3C0E8014 */       lui $t6, %hi(gCreditsCrosshairGObj)
  /* 17F5BC 80131EBC 8DCEA8CC */        lw $t6, %lo(gCreditsCrosshairGObj)($t6)
  /* 17F5C0 80131EC0 3C0141E8 */       lui $at, (0x41E80000 >> 16) # 29.0
  /* 17F5C4 80131EC4 44817000 */      mtc1 $at, $f14 # 29.0 to cop1
  /* 17F5C8 80131EC8 8DC20074 */        lw $v0, 0x74($t6)
  /* 17F5CC 80131ECC 3C0143A0 */       lui $at, (0x43A00000 >> 16) # 320.0
  /* 17F5D0 80131ED0 44814000 */      mtc1 $at, $f8 # 320.0 to cop1
  /* 17F5D4 80131ED4 C4440058 */      lwc1 $f4, 0x58($v0)
  /* 17F5D8 80131ED8 C450005C */      lwc1 $f16, 0x5c($v0)
  /* 17F5DC 80131EDC 3C014370 */       lui $at, (0x43700000 >> 16) # 240.0
  /* 17F5E0 80131EE0 460E2180 */     add.s $f6, $f4, $f14
  /* 17F5E4 80131EE4 44815000 */      mtc1 $at, $f10 # 240.0 to cop1
  /* 17F5E8 80131EE8 C4840000 */      lwc1 $f4, ($a0)
  /* 17F5EC 80131EEC 460E8480 */     add.s $f18, $f16, $f14
  /* 17F5F0 80131EF0 24030001 */     addiu $v1, $zero, 1
  /* 17F5F4 80131EF4 46083001 */     sub.s $f0, $f6, $f8
  /* 17F5F8 80131EF8 C4880004 */      lwc1 $f8, 4($a0)
  /* 17F5FC 80131EFC 46125081 */     sub.s $f2, $f10, $f18
  /* 17F600 80131F00 46002182 */     mul.s $f6, $f4, $f0
  /* 17F604 80131F04 C4920008 */      lwc1 $f18, 8($a0)
  /* 17F608 80131F08 44802000 */      mtc1 $zero, $f4
  /* 17F60C 80131F0C 46024402 */     mul.s $f16, $f8, $f2
  /* 17F610 80131F10 46103280 */     add.s $f10, $f6, $f16
  /* 17F614 80131F14 46125300 */     add.s $f12, $f10, $f18
  /* 17F618 80131F18 4604603C */    c.lt.s $f12, $f4
  /* 17F61C 80131F1C 00000000 */       nop 
  /* 17F620 80131F20 45000002 */      bc1f .L80131F2C
  /* 17F624 80131F24 00000000 */       nop 
  /* 17F628 80131F28 00001825 */        or $v1, $zero, $zero
  .L80131F2C:
  /* 17F62C 80131F2C 03E00008 */        jr $ra
  /* 17F630 80131F30 00601025 */        or $v0, $v1, $zero

glabel func_ovl59_80131F34
  /* 17F634 80131F34 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 17F638 80131F38 AFBF0014 */        sw $ra, 0x14($sp)
  /* 17F63C 80131F3C 8C830084 */        lw $v1, 0x84($a0)
  /* 17F640 80131F40 3C018014 */       lui $at, %hi(gCreditsRollSpeed)
  /* 17F644 80131F44 C426A8BC */      lwc1 $f6, %lo(gCreditsRollSpeed)($at)
  /* 17F648 80131F48 8C650084 */        lw $a1, 0x84($v1)
  /* 17F64C 80131F4C 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 17F650 80131F50 44815000 */      mtc1 $at, $f10 # 1.0 to cop1
  /* 17F654 80131F54 C4A40014 */      lwc1 $f4, 0x14($a1)
  /* 17F658 80131F58 3C014000 */       lui $at, 0x4000
  /* 17F65C 80131F5C 46062200 */     add.s $f8, $f4, $f6
  /* 17F660 80131F60 4608503E */    c.le.s $f10, $f8
  /* 17F664 80131F64 00000000 */       nop 
  /* 17F668 80131F68 4502000C */     bc1fl .L80131F9C
  /* 17F66C 80131F6C 8C6E0074 */        lw $t6, 0x74($v1)
  /* 17F670 80131F70 0C0026A1 */       jal omEjectGObjCommon
  /* 17F674 80131F74 00002025 */        or $a0, $zero, $zero
  /* 17F678 80131F78 3C048014 */       lui $a0, %hi(gCreditsStaffRoleTextGObj)
  /* 17F67C 80131F7C 0C0026A1 */       jal omEjectGObjCommon
  /* 17F680 80131F80 8C84A8F8 */        lw $a0, %lo(gCreditsStaffRoleTextGObj)($a0)
  /* 17F684 80131F84 3C048014 */       lui $a0, %hi(gCreditsCompanyTextGObj)
  /* 17F688 80131F88 0C0026A1 */       jal omEjectGObjCommon
  /* 17F68C 80131F8C 8C84A8FC */        lw $a0, %lo(gCreditsCompanyTextGObj)($a0)
  /* 17F690 80131F90 10000023 */         b .L80132020
  /* 17F694 80131F94 8FBF0014 */        lw $ra, 0x14($sp)
  /* 17F698 80131F98 8C6E0074 */        lw $t6, 0x74($v1)
  .L80131F9C:
  /* 17F69C 80131F9C 8C820074 */        lw $v0, 0x74($a0)
  /* 17F6A0 80131FA0 44808000 */      mtc1 $zero, $f16
  /* 17F6A4 80131FA4 8DD8001C */        lw $t8, 0x1c($t6)
  /* 17F6A8 80131FA8 8C460010 */        lw $a2, 0x10($v0)
  /* 17F6AC 80131FAC 44819000 */      mtc1 $at, $f18
  /* 17F6B0 80131FB0 AC58001C */        sw $t8, 0x1c($v0)
  /* 17F6B4 80131FB4 8DCF0020 */        lw $t7, 0x20($t6)
  /* 17F6B8 80131FB8 AC4F0020 */        sw $t7, 0x20($v0)
  /* 17F6BC 80131FBC 8DD80024 */        lw $t8, 0x24($t6)
  /* 17F6C0 80131FC0 AC580024 */        sw $t8, 0x24($v0)
  /* 17F6C4 80131FC4 8C680074 */        lw $t0, 0x74($v1)
  /* 17F6C8 80131FC8 8C990074 */        lw $t9, 0x74($a0)
  /* 17F6CC 80131FCC 8D0A0030 */        lw $t2, 0x30($t0)
  /* 17F6D0 80131FD0 AF2A0030 */        sw $t2, 0x30($t9)
  /* 17F6D4 80131FD4 8D090034 */        lw $t1, 0x34($t0)
  /* 17F6D8 80131FD8 AF290034 */        sw $t1, 0x34($t9)
  /* 17F6DC 80131FDC 8D0A0038 */        lw $t2, 0x38($t0)
  /* 17F6E0 80131FE0 AF2A0038 */        sw $t2, 0x38($t9)
  /* 17F6E4 80131FE4 C4A0000C */      lwc1 $f0, 0xc($a1)
  /* 17F6E8 80131FE8 4610003C */    c.lt.s $f0, $f16
  /* 17F6EC 80131FEC 00000000 */       nop 
  /* 17F6F0 80131FF0 45020004 */     bc1fl .L80132004
  /* 17F6F4 80131FF4 46000086 */     mov.s $f2, $f0
  /* 17F6F8 80131FF8 10000002 */         b .L80132004
  /* 17F6FC 80131FFC 46000087 */     neg.s $f2, $f0
  /* 17F700 80132000 46000086 */     mov.s $f2, $f0
  .L80132004:
  /* 17F704 80132004 46121102 */     mul.s $f4, $f2, $f18
  /* 17F708 80132008 3C014190 */       lui $at, (0x41900000 >> 16) # 18.0
  /* 17F70C 8013200C 44813000 */      mtc1 $at, $f6 # 18.0 to cop1
  /* 17F710 80132010 00000000 */       nop 
  /* 17F714 80132014 46062200 */     add.s $f8, $f4, $f6
  /* 17F718 80132018 E4C8001C */      swc1 $f8, 0x1c($a2)
  /* 17F71C 8013201C 8FBF0014 */        lw $ra, 0x14($sp)
  .L80132020:
  /* 17F720 80132020 27BD0018 */     addiu $sp, $sp, 0x18
  /* 17F724 80132024 03E00008 */        jr $ra
  /* 17F728 80132028 00000000 */       nop 

glabel func_ovl59_8013202C
  /* 17F72C 8013202C 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 17F730 80132030 AFB00020 */        sw $s0, 0x20($sp)
  /* 17F734 80132034 3C108004 */       lui $s0, %hi(gOMObjCommonLinks + (0x02 * 4))
  /* 17F738 80132038 8E1066F8 */        lw $s0, %lo(gOMObjCommonLinks + (0x02 * 4))($s0)
  /* 17F73C 8013203C AFBF0024 */        sw $ra, 0x24($sp)
  /* 17F740 80132040 AFA40030 */        sw $a0, 0x30($sp)
  /* 17F744 80132044 16000023 */      bnez $s0, .L801320D4
  /* 17F748 80132048 8C820084 */        lw $v0, 0x84($a0)
  /* 17F74C 8013204C 24040008 */     addiu $a0, $zero, 8
  /* 17F750 80132050 00002825 */        or $a1, $zero, $zero
  /* 17F754 80132054 24060002 */     addiu $a2, $zero, 2
  /* 17F758 80132058 3C078000 */       lui $a3, 0x8000
  /* 17F75C 8013205C 0C00265A */       jal omMakeGObjCommon
  /* 17F760 80132060 AFA20028 */        sw $v0, 0x28($sp)
  /* 17F764 80132064 3C058001 */       lui $a1, %hi(func_80014038)
  /* 17F768 80132068 240FFFFF */     addiu $t7, $zero, -1
  /* 17F76C 8013206C 00408025 */        or $s0, $v0, $zero
  /* 17F770 80132070 AFAF0010 */        sw $t7, 0x10($sp)
  /* 17F774 80132074 24A54038 */     addiu $a1, $a1, %lo(func_80014038)
  /* 17F778 80132078 00402025 */        or $a0, $v0, $zero
  /* 17F77C 8013207C 24060003 */     addiu $a2, $zero, 3
  /* 17F780 80132080 0C00277D */       jal omAddGObjRenderProc
  /* 17F784 80132084 3C078000 */       lui $a3, 0x8000
  /* 17F788 80132088 3C058014 */       lui $a1, %hi(D_ovl59_8013A8E8)
  /* 17F78C 8013208C 8CA5A8E8 */        lw $a1, %lo(D_ovl59_8013A8E8)($a1)
  /* 17F790 80132090 02002025 */        or $a0, $s0, $zero
  /* 17F794 80132094 00003025 */        or $a2, $zero, $zero
  /* 17F798 80132098 2407001C */     addiu $a3, $zero, 0x1c
  /* 17F79C 8013209C AFA00010 */        sw $zero, 0x10($sp)
  /* 17F7A0 801320A0 0C003D64 */       jal func_8000F590
  /* 17F7A4 801320A4 AFA00014 */        sw $zero, 0x14($sp)
  /* 17F7A8 801320A8 3C058013 */       lui $a1, %hi(func_ovl59_80131F34)
  /* 17F7AC 801320AC 24A51F34 */     addiu $a1, $a1, %lo(func_ovl59_80131F34)
  /* 17F7B0 801320B0 02002025 */        or $a0, $s0, $zero
  /* 17F7B4 801320B4 24060001 */     addiu $a2, $zero, 1
  /* 17F7B8 801320B8 0C002062 */       jal omAddGObjCommonProc
  /* 17F7BC 801320BC 24070001 */     addiu $a3, $zero, 1
  /* 17F7C0 801320C0 8FB80030 */        lw $t8, 0x30($sp)
  /* 17F7C4 801320C4 AE180084 */        sw $t8, 0x84($s0)
  /* 17F7C8 801320C8 8FB90028 */        lw $t9, 0x28($sp)
  /* 17F7CC 801320CC 10000004 */         b .L801320E0
  /* 17F7D0 801320D0 AF30001C */        sw $s0, 0x1c($t9)
  .L801320D4:
  /* 17F7D4 801320D4 8FA80030 */        lw $t0, 0x30($sp)
  /* 17F7D8 801320D8 AE080084 */        sw $t0, 0x84($s0)
  /* 17F7DC 801320DC AC50001C */        sw $s0, 0x1c($v0)
  .L801320E0:
  /* 17F7E0 801320E0 8FBF0024 */        lw $ra, 0x24($sp)
  /* 17F7E4 801320E4 8FB00020 */        lw $s0, 0x20($sp)
  /* 17F7E8 801320E8 27BD0030 */     addiu $sp, $sp, 0x30
  /* 17F7EC 801320EC 03E00008 */        jr $ra
  /* 17F7F0 801320F0 00000000 */       nop 

glabel gmCreditsGetLockOnPosX
  /* 17F7F4 801320F4 28810014 */      slti $at, $a0, 0x14
  /* 17F7F8 801320F8 10200002 */      beqz $at, .L80132104
  /* 17F7FC 801320FC 00801825 */        or $v1, $a0, $zero
  /* 17F800 80132100 24030014 */     addiu $v1, $zero, 0x14
  .L80132104:
  /* 17F804 80132104 2881026D */      slti $at, $a0, 0x26d
  /* 17F808 80132108 14200002 */      bnez $at, .L80132114
  /* 17F80C 8013210C 00000000 */       nop 
  /* 17F810 80132110 2403026C */     addiu $v1, $zero, 0x26c
  .L80132114:
  /* 17F814 80132114 03E00008 */        jr $ra
  /* 17F818 80132118 00601025 */        or $v0, $v1, $zero

glabel gmCreditsGetLockOnPosY
  /* 17F81C 8013211C 28810014 */      slti $at, $a0, 0x14
  /* 17F820 80132120 10200002 */      beqz $at, .L8013212C
  /* 17F824 80132124 00801825 */        or $v1, $a0, $zero
  /* 17F828 80132128 24030014 */     addiu $v1, $zero, 0x14
  .L8013212C:
  /* 17F82C 8013212C 288101CD */      slti $at, $a0, 0x1cd
  /* 17F830 80132130 14200002 */      bnez $at, .L8013213C
  /* 17F834 80132134 00000000 */       nop 
  /* 17F838 80132138 240301CC */     addiu $v1, $zero, 0x1cc
  .L8013213C:
  /* 17F83C 8013213C 03E00008 */        jr $ra
  /* 17F840 80132140 00601025 */        or $v0, $v1, $zero

glabel gmCreditsHighlightProcRender
  /* 17F844 80132144 27BDFFA8 */     addiu $sp, $sp, -0x58
  /* 17F848 80132148 AFB00018 */        sw $s0, 0x18($sp)
  /* 17F84C 8013214C 3C108004 */       lui $s0, %hi(gDisplayListHead)
  /* 17F850 80132150 261065B0 */     addiu $s0, $s0, %lo(gDisplayListHead)
  /* 17F854 80132154 8E030000 */        lw $v1, ($s0) # gDisplayListHead + 0
  /* 17F858 80132158 AFBF002C */        sw $ra, 0x2c($sp)
  /* 17F85C 8013215C AFB40028 */        sw $s4, 0x28($sp)
  /* 17F860 80132160 246E0008 */     addiu $t6, $v1, 8
  /* 17F864 80132164 AFB30024 */        sw $s3, 0x24($sp)
  /* 17F868 80132168 AFB20020 */        sw $s2, 0x20($sp)
  /* 17F86C 8013216C AFB1001C */        sw $s1, 0x1c($sp)
  /* 17F870 80132170 AFA40058 */        sw $a0, 0x58($sp)
  /* 17F874 80132174 AE0E0000 */        sw $t6, ($s0) # gDisplayListHead + 0
  /* 17F878 80132178 3C0FE700 */       lui $t7, 0xe700
  /* 17F87C 8013217C AC6F0000 */        sw $t7, ($v1)
  /* 17F880 80132180 AC600004 */        sw $zero, 4($v1)
  /* 17F884 80132184 8E030000 */        lw $v1, ($s0) # gDisplayListHead + 0
  /* 17F888 80132188 3C19E300 */       lui $t9, (0xE3000A01 >> 16) # 3808430593
  /* 17F88C 8013218C 37390A01 */       ori $t9, $t9, (0xE3000A01 & 0xFFFF) # 3808430593
  /* 17F890 80132190 24780008 */     addiu $t8, $v1, 8
  /* 17F894 80132194 AE180000 */        sw $t8, ($s0) # gDisplayListHead + 0
  /* 17F898 80132198 3C080030 */       lui $t0, 0x30
  /* 17F89C 8013219C AC680004 */        sw $t0, 4($v1)
  /* 17F8A0 801321A0 AC790000 */        sw $t9, ($v1)
  /* 17F8A4 801321A4 8E030000 */        lw $v1, ($s0) # gDisplayListHead + 0
  /* 17F8A8 801321A8 3C0AE200 */       lui $t2, (0xE200001C >> 16) # 3791650844
  /* 17F8AC 801321AC 354A001C */       ori $t2, $t2, (0xE200001C & 0xFFFF) # 3791650844
  /* 17F8B0 801321B0 24690008 */     addiu $t1, $v1, 8
  /* 17F8B4 801321B4 AE090000 */        sw $t1, ($s0) # gDisplayListHead + 0
  /* 17F8B8 801321B8 AC600004 */        sw $zero, 4($v1)
  /* 17F8BC 801321BC AC6A0000 */        sw $t2, ($v1)
  /* 17F8C0 801321C0 8E030000 */        lw $v1, ($s0) # gDisplayListHead + 0
  /* 17F8C4 801321C4 3C0D8001 */       lui $t5, (0x80018001 >> 16) # 2147581953
  /* 17F8C8 801321C8 3C128014 */       lui $s2, %hi(gCreditsHighlightSize)
  /* 17F8CC 801321CC 246B0008 */     addiu $t3, $v1, 8
  /* 17F8D0 801321D0 AE0B0000 */        sw $t3, ($s0) # gDisplayListHead + 0
  /* 17F8D4 801321D4 35AD8001 */       ori $t5, $t5, (0x80018001 & 0xFFFF) # 2147581953
  /* 17F8D8 801321D8 3C0CF700 */       lui $t4, 0xf700
  /* 17F8DC 801321DC 2652A8EC */     addiu $s2, $s2, %lo(gCreditsHighlightSize)
  /* 17F8E0 801321E0 AC6C0000 */        sw $t4, ($v1)
  /* 17F8E4 801321E4 AC6D0004 */        sw $t5, 4($v1)
  /* 17F8E8 801321E8 8E4F0000 */        lw $t7, ($s2) # gCreditsHighlightSize + 0
  /* 17F8EC 801321EC 3C138014 */       lui $s3, %hi(gCreditsHighlightPositionX)
  /* 17F8F0 801321F0 2673A8F0 */     addiu $s3, $s3, %lo(gCreditsHighlightPositionX)
  /* 17F8F4 801321F4 000F0823 */      negu $at, $t7
  /* 17F8F8 801321F8 0001C100 */       sll $t8, $at, 4
  /* 17F8FC 801321FC 0301C023 */      subu $t8, $t8, $at
  /* 17F900 80132200 0018C040 */       sll $t8, $t8, 1
  /* 17F904 80132204 27190002 */     addiu $t9, $t8, 2
  /* 17F908 80132208 44992000 */      mtc1 $t9, $f4 # -2.361904e21 to cop1
  /* 17F90C 8013220C C6680000 */      lwc1 $f8, ($s3) # gCreditsHighlightPositionX + 0
  /* 17F910 80132210 8E030000 */        lw $v1, ($s0) # gDisplayListHead + 0
  /* 17F914 80132214 468021A0 */   cvt.s.w $f6, $f4
  /* 17F918 80132218 246E0008 */     addiu $t6, $v1, 8
  /* 17F91C 8013221C AE0E0000 */        sw $t6, ($s0) # gDisplayListHead + 0
  /* 17F920 80132220 AFA30040 */        sw $v1, 0x40($sp)
  /* 17F924 80132224 46083280 */     add.s $f10, $f6, $f8
  /* 17F928 80132228 4600540D */ trunc.w.s $f16, $f10
  /* 17F92C 8013222C 44048000 */      mfc1 $a0, $f16
  /* 17F930 80132230 0C04C83D */       jal gmCreditsGetLockOnPosX
  /* 17F934 80132234 00000000 */       nop 
  /* 17F938 80132238 8E490000 */        lw $t1, ($s2) # gCreditsHighlightSize + 0
  /* 17F93C 8013223C 3C148014 */       lui $s4, %hi(gCreditsHighlightPositionY)
  /* 17F940 80132240 2694A8F4 */     addiu $s4, $s4, %lo(gCreditsHighlightPositionY)
  /* 17F944 80132244 00095080 */       sll $t2, $t1, 2
  /* 17F948 80132248 01495023 */      subu $t2, $t2, $t1
  /* 17F94C 8013224C 000A5080 */       sll $t2, $t2, 2
  /* 17F950 80132250 01495023 */      subu $t2, $t2, $t1
  /* 17F954 80132254 000A5080 */       sll $t2, $t2, 2
  /* 17F958 80132258 01495021 */      addu $t2, $t2, $t1
  /* 17F95C 8013225C 254B0002 */     addiu $t3, $t2, 2
  /* 17F960 80132260 448B9000 */      mtc1 $t3, $f18
  /* 17F964 80132264 C6860000 */      lwc1 $f6, ($s4) # gCreditsHighlightPositionY + 0
  /* 17F968 80132268 00408825 */        or $s1, $v0, $zero
  /* 17F96C 8013226C 46809120 */   cvt.s.w $f4, $f18
  /* 17F970 80132270 46062200 */     add.s $f8, $f4, $f6
  /* 17F974 80132274 4600428D */ trunc.w.s $f10, $f8
  /* 17F978 80132278 44045000 */      mfc1 $a0, $f10
  /* 17F97C 8013227C 0C04C847 */       jal gmCreditsGetLockOnPosY
  /* 17F980 80132280 00000000 */       nop 
  /* 17F984 80132284 304D03FF */      andi $t5, $v0, 0x3ff
  /* 17F988 80132288 8FA90040 */        lw $t1, 0x40($sp)
  /* 17F98C 8013228C 000D7080 */       sll $t6, $t5, 2
  /* 17F990 80132290 3C01F600 */       lui $at, 0xf600
  /* 17F994 80132294 323803FF */      andi $t8, $s1, 0x3ff
  /* 17F998 80132298 0018CB80 */       sll $t9, $t8, 0xe
  /* 17F99C 8013229C 01C17825 */        or $t7, $t6, $at
  /* 17F9A0 801322A0 01F94025 */        or $t0, $t7, $t9
  /* 17F9A4 801322A4 AD280000 */        sw $t0, ($t1)
  /* 17F9A8 801322A8 8E4A0000 */        lw $t2, ($s2) # gCreditsHighlightSize + 0
  /* 17F9AC 801322AC C6640000 */      lwc1 $f4, ($s3) # gCreditsHighlightPositionX + 0
  /* 17F9B0 801322B0 000A0823 */      negu $at, $t2
  /* 17F9B4 801322B4 00015900 */       sll $t3, $at, 4
  /* 17F9B8 801322B8 01615823 */      subu $t3, $t3, $at
  /* 17F9BC 801322BC 000B5840 */       sll $t3, $t3, 1
  /* 17F9C0 801322C0 448B8000 */      mtc1 $t3, $f16
  /* 17F9C4 801322C4 00000000 */       nop 
  /* 17F9C8 801322C8 468084A0 */   cvt.s.w $f18, $f16
  /* 17F9CC 801322CC 46049180 */     add.s $f6, $f18, $f4
  /* 17F9D0 801322D0 4600320D */ trunc.w.s $f8, $f6
  /* 17F9D4 801322D4 44044000 */      mfc1 $a0, $f8
  /* 17F9D8 801322D8 0C04C83D */       jal gmCreditsGetLockOnPosX
  /* 17F9DC 801322DC 00000000 */       nop 
  /* 17F9E0 801322E0 8E4D0000 */        lw $t5, ($s2) # gCreditsHighlightSize + 0
  /* 17F9E4 801322E4 C6920000 */      lwc1 $f18, ($s4) # gCreditsHighlightPositionY + 0
  /* 17F9E8 801322E8 00408825 */        or $s1, $v0, $zero
  /* 17F9EC 801322EC 000D0823 */      negu $at, $t5
  /* 17F9F0 801322F0 00017080 */       sll $t6, $at, 2
  /* 17F9F4 801322F4 01C17023 */      subu $t6, $t6, $at
  /* 17F9F8 801322F8 000E70C0 */       sll $t6, $t6, 3
  /* 17F9FC 801322FC 01C17021 */      addu $t6, $t6, $at
  /* 17FA00 80132300 448E5000 */      mtc1 $t6, $f10
  /* 17FA04 80132304 00000000 */       nop 
  /* 17FA08 80132308 46805420 */   cvt.s.w $f16, $f10
  /* 17FA0C 8013230C 46128100 */     add.s $f4, $f16, $f18
  /* 17FA10 80132310 4600218D */ trunc.w.s $f6, $f4
  /* 17FA14 80132314 44043000 */      mfc1 $a0, $f6
  /* 17FA18 80132318 0C04C847 */       jal gmCreditsGetLockOnPosY
  /* 17FA1C 8013231C 00000000 */       nop 
  /* 17FA20 80132320 8FAB0040 */        lw $t3, 0x40($sp)
  /* 17FA24 80132324 304F03FF */      andi $t7, $v0, 0x3ff
  /* 17FA28 80132328 322803FF */      andi $t0, $s1, 0x3ff
  /* 17FA2C 8013232C 00084B80 */       sll $t1, $t0, 0xe
  /* 17FA30 80132330 000FC880 */       sll $t9, $t7, 2
  /* 17FA34 80132334 03295025 */        or $t2, $t9, $t1
  /* 17FA38 80132338 AD6A0004 */        sw $t2, 4($t3)
  /* 17FA3C 8013233C 8E4D0000 */        lw $t5, ($s2) # gCreditsHighlightSize + 0
  /* 17FA40 80132340 C6700000 */      lwc1 $f16, ($s3) # gCreditsHighlightPositionX + 0
  /* 17FA44 80132344 8E030000 */        lw $v1, ($s0) # gDisplayListHead + 0
  /* 17FA48 80132348 000D7180 */       sll $t6, $t5, 6
  /* 17FA4C 8013234C 01CD7021 */      addu $t6, $t6, $t5
  /* 17FA50 80132350 25D80002 */     addiu $t8, $t6, 2
  /* 17FA54 80132354 44984000 */      mtc1 $t8, $f8
  /* 17FA58 80132358 246C0008 */     addiu $t4, $v1, 8
  /* 17FA5C 8013235C AE0C0000 */        sw $t4, ($s0) # gDisplayListHead + 0
  /* 17FA60 80132360 468042A0 */   cvt.s.w $f10, $f8
  /* 17FA64 80132364 AFA3003C */        sw $v1, 0x3c($sp)
  /* 17FA68 80132368 46105480 */     add.s $f18, $f10, $f16
  /* 17FA6C 8013236C 4600910D */ trunc.w.s $f4, $f18
  /* 17FA70 80132370 44042000 */      mfc1 $a0, $f4
  /* 17FA74 80132374 0C04C83D */       jal gmCreditsGetLockOnPosX
  /* 17FA78 80132378 00000000 */       nop 
  /* 17FA7C 8013237C 8E480000 */        lw $t0, ($s2) # gCreditsHighlightSize + 0
  /* 17FA80 80132380 C68A0000 */      lwc1 $f10, ($s4) # gCreditsHighlightPositionY + 0
  /* 17FA84 80132384 00408825 */        or $s1, $v0, $zero
  /* 17FA88 80132388 00080823 */      negu $at, $t0
  /* 17FA8C 8013238C 0001C880 */       sll $t9, $at, 2
  /* 17FA90 80132390 0321C823 */      subu $t9, $t9, $at
  /* 17FA94 80132394 0019C8C0 */       sll $t9, $t9, 3
  /* 17FA98 80132398 0321C821 */      addu $t9, $t9, $at
  /* 17FA9C 8013239C 27290002 */     addiu $t1, $t9, 2
  /* 17FAA0 801323A0 44893000 */      mtc1 $t1, $f6
  /* 17FAA4 801323A4 00000000 */       nop 
  /* 17FAA8 801323A8 46803220 */   cvt.s.w $f8, $f6
  /* 17FAAC 801323AC 460A4400 */     add.s $f16, $f8, $f10
  /* 17FAB0 801323B0 4600848D */ trunc.w.s $f18, $f16
  /* 17FAB4 801323B4 44049000 */      mfc1 $a0, $f18
  /* 17FAB8 801323B8 0C04C847 */       jal gmCreditsGetLockOnPosY
  /* 17FABC 801323BC 00000000 */       nop 
  /* 17FAC0 801323C0 304B03FF */      andi $t3, $v0, 0x3ff
  /* 17FAC4 801323C4 8FA8003C */        lw $t0, 0x3c($sp)
  /* 17FAC8 801323C8 000B6080 */       sll $t4, $t3, 2
  /* 17FACC 801323CC 3C01F600 */       lui $at, 0xf600
  /* 17FAD0 801323D0 322E03FF */      andi $t6, $s1, 0x3ff
  /* 17FAD4 801323D4 000EC380 */       sll $t8, $t6, 0xe
  /* 17FAD8 801323D8 01816825 */        or $t5, $t4, $at
  /* 17FADC 801323DC 01B87825 */        or $t7, $t5, $t8
  /* 17FAE0 801323E0 AD0F0000 */        sw $t7, ($t0)
  /* 17FAE4 801323E4 8E590000 */        lw $t9, ($s2) # gCreditsHighlightSize + 0
  /* 17FAE8 801323E8 C6680000 */      lwc1 $f8, ($s3) # gCreditsHighlightPositionX + 0
  /* 17FAEC 801323EC 00190823 */      negu $at, $t9
  /* 17FAF0 801323F0 00014900 */       sll $t1, $at, 4
  /* 17FAF4 801323F4 01214823 */      subu $t1, $t1, $at
  /* 17FAF8 801323F8 00094840 */       sll $t1, $t1, 1
  /* 17FAFC 801323FC 44892000 */      mtc1 $t1, $f4
  /* 17FB00 80132400 00000000 */       nop 
  /* 17FB04 80132404 468021A0 */   cvt.s.w $f6, $f4
  /* 17FB08 80132408 46083280 */     add.s $f10, $f6, $f8
  /* 17FB0C 8013240C 4600540D */ trunc.w.s $f16, $f10
  /* 17FB10 80132410 44048000 */      mfc1 $a0, $f16
  /* 17FB14 80132414 0C04C83D */       jal gmCreditsGetLockOnPosX
  /* 17FB18 80132418 00000000 */       nop 
  /* 17FB1C 8013241C 8E4B0000 */        lw $t3, ($s2) # gCreditsHighlightSize + 0
  /* 17FB20 80132420 C6860000 */      lwc1 $f6, ($s4) # gCreditsHighlightPositionY + 0
  /* 17FB24 80132424 00408825 */        or $s1, $v0, $zero
  /* 17FB28 80132428 000B0823 */      negu $at, $t3
  /* 17FB2C 8013242C 00016080 */       sll $t4, $at, 2
  /* 17FB30 80132430 01816023 */      subu $t4, $t4, $at
  /* 17FB34 80132434 000C60C0 */       sll $t4, $t4, 3
  /* 17FB38 80132438 01816021 */      addu $t4, $t4, $at
  /* 17FB3C 8013243C 448C9000 */      mtc1 $t4, $f18
  /* 17FB40 80132440 00000000 */       nop 
  /* 17FB44 80132444 46809120 */   cvt.s.w $f4, $f18
  /* 17FB48 80132448 46062200 */     add.s $f8, $f4, $f6
  /* 17FB4C 8013244C 4600428D */ trunc.w.s $f10, $f8
  /* 17FB50 80132450 44045000 */      mfc1 $a0, $f10
  /* 17FB54 80132454 0C04C847 */       jal gmCreditsGetLockOnPosY
  /* 17FB58 80132458 00000000 */       nop 
  /* 17FB5C 8013245C 8FA9003C */        lw $t1, 0x3c($sp)
  /* 17FB60 80132460 304D03FF */      andi $t5, $v0, 0x3ff
  /* 17FB64 80132464 322F03FF */      andi $t7, $s1, 0x3ff
  /* 17FB68 80132468 000F4380 */       sll $t0, $t7, 0xe
  /* 17FB6C 8013246C 000DC080 */       sll $t8, $t5, 2
  /* 17FB70 80132470 0308C825 */        or $t9, $t8, $t0
  /* 17FB74 80132474 AD390004 */        sw $t9, 4($t1)
  /* 17FB78 80132478 8E4B0000 */        lw $t3, ($s2) # gCreditsHighlightSize + 0
  /* 17FB7C 8013247C C6640000 */      lwc1 $f4, ($s3) # gCreditsHighlightPositionX + 0
  /* 17FB80 80132480 8E030000 */        lw $v1, ($s0) # gDisplayListHead + 0
  /* 17FB84 80132484 000B6180 */       sll $t4, $t3, 6
  /* 17FB88 80132488 018B6021 */      addu $t4, $t4, $t3
  /* 17FB8C 8013248C 258E0002 */     addiu $t6, $t4, 2
  /* 17FB90 80132490 448E8000 */      mtc1 $t6, $f16
  /* 17FB94 80132494 246A0008 */     addiu $t2, $v1, 8
  /* 17FB98 80132498 AE0A0000 */        sw $t2, ($s0) # gDisplayListHead + 0
  /* 17FB9C 8013249C 468084A0 */   cvt.s.w $f18, $f16
  /* 17FBA0 801324A0 AFA30038 */        sw $v1, 0x38($sp)
  /* 17FBA4 801324A4 46049180 */     add.s $f6, $f18, $f4
  /* 17FBA8 801324A8 4600320D */ trunc.w.s $f8, $f6
  /* 17FBAC 801324AC 44044000 */      mfc1 $a0, $f8
  /* 17FBB0 801324B0 0C04C83D */       jal gmCreditsGetLockOnPosX
  /* 17FBB4 801324B4 00000000 */       nop 
  /* 17FBB8 801324B8 8E4F0000 */        lw $t7, ($s2) # gCreditsHighlightSize + 0
  /* 17FBBC 801324BC C6920000 */      lwc1 $f18, ($s4) # gCreditsHighlightPositionY + 0
  /* 17FBC0 801324C0 00408825 */        or $s1, $v0, $zero
  /* 17FBC4 801324C4 000FC080 */       sll $t8, $t7, 2
  /* 17FBC8 801324C8 030FC023 */      subu $t8, $t8, $t7
  /* 17FBCC 801324CC 0018C080 */       sll $t8, $t8, 2
  /* 17FBD0 801324D0 030FC023 */      subu $t8, $t8, $t7
  /* 17FBD4 801324D4 0018C080 */       sll $t8, $t8, 2
  /* 17FBD8 801324D8 030FC021 */      addu $t8, $t8, $t7
  /* 17FBDC 801324DC 27080002 */     addiu $t0, $t8, 2
  /* 17FBE0 801324E0 44885000 */      mtc1 $t0, $f10
  /* 17FBE4 801324E4 00000000 */       nop 
  /* 17FBE8 801324E8 46805420 */   cvt.s.w $f16, $f10
  /* 17FBEC 801324EC 46128100 */     add.s $f4, $f16, $f18
  /* 17FBF0 801324F0 4600218D */ trunc.w.s $f6, $f4
  /* 17FBF4 801324F4 44043000 */      mfc1 $a0, $f6
  /* 17FBF8 801324F8 0C04C847 */       jal gmCreditsGetLockOnPosY
  /* 17FBFC 801324FC 00000000 */       nop 
  /* 17FC00 80132500 304903FF */      andi $t1, $v0, 0x3ff
  /* 17FC04 80132504 8FAF0038 */        lw $t7, 0x38($sp)
  /* 17FC08 80132508 00095080 */       sll $t2, $t1, 2
  /* 17FC0C 8013250C 3C01F600 */       lui $at, 0xf600
  /* 17FC10 80132510 322C03FF */      andi $t4, $s1, 0x3ff
  /* 17FC14 80132514 000C7380 */       sll $t6, $t4, 0xe
  /* 17FC18 80132518 01415825 */        or $t3, $t2, $at
  /* 17FC1C 8013251C 016E6825 */        or $t5, $t3, $t6
  /* 17FC20 80132520 ADED0000 */        sw $t5, ($t7)
  /* 17FC24 80132524 8E580000 */        lw $t8, ($s2) # gCreditsHighlightSize + 0
  /* 17FC28 80132528 C6700000 */      lwc1 $f16, ($s3) # gCreditsHighlightPositionX + 0
  /* 17FC2C 8013252C 00180823 */      negu $at, $t8
  /* 17FC30 80132530 00014100 */       sll $t0, $at, 4
  /* 17FC34 80132534 01014023 */      subu $t0, $t0, $at
  /* 17FC38 80132538 00084040 */       sll $t0, $t0, 1
  /* 17FC3C 8013253C 44884000 */      mtc1 $t0, $f8
  /* 17FC40 80132540 00000000 */       nop 
  /* 17FC44 80132544 468042A0 */   cvt.s.w $f10, $f8
  /* 17FC48 80132548 46105480 */     add.s $f18, $f10, $f16
  /* 17FC4C 8013254C 4600910D */ trunc.w.s $f4, $f18
  /* 17FC50 80132550 44042000 */      mfc1 $a0, $f4
  /* 17FC54 80132554 0C04C83D */       jal gmCreditsGetLockOnPosX
  /* 17FC58 80132558 00000000 */       nop 
  /* 17FC5C 8013255C 8E490000 */        lw $t1, ($s2) # gCreditsHighlightSize + 0
  /* 17FC60 80132560 C68A0000 */      lwc1 $f10, ($s4) # gCreditsHighlightPositionY + 0
  /* 17FC64 80132564 00408825 */        or $s1, $v0, $zero
  /* 17FC68 80132568 00095080 */       sll $t2, $t1, 2
  /* 17FC6C 8013256C 01495023 */      subu $t2, $t2, $t1
  /* 17FC70 80132570 000A5080 */       sll $t2, $t2, 2
  /* 17FC74 80132574 01495023 */      subu $t2, $t2, $t1
  /* 17FC78 80132578 000A5080 */       sll $t2, $t2, 2
  /* 17FC7C 8013257C 01495021 */      addu $t2, $t2, $t1
  /* 17FC80 80132580 448A3000 */      mtc1 $t2, $f6
  /* 17FC84 80132584 00000000 */       nop 
  /* 17FC88 80132588 46803220 */   cvt.s.w $f8, $f6
  /* 17FC8C 8013258C 460A4400 */     add.s $f16, $f8, $f10
  /* 17FC90 80132590 4600848D */ trunc.w.s $f18, $f16
  /* 17FC94 80132594 44049000 */      mfc1 $a0, $f18
  /* 17FC98 80132598 0C04C847 */       jal gmCreditsGetLockOnPosY
  /* 17FC9C 8013259C 00000000 */       nop 
  /* 17FCA0 801325A0 8FA80038 */        lw $t0, 0x38($sp)
  /* 17FCA4 801325A4 304B03FF */      andi $t3, $v0, 0x3ff
  /* 17FCA8 801325A8 322D03FF */      andi $t5, $s1, 0x3ff
  /* 17FCAC 801325AC 000D7B80 */       sll $t7, $t5, 0xe
  /* 17FCB0 801325B0 000B7080 */       sll $t6, $t3, 2
  /* 17FCB4 801325B4 01CFC025 */        or $t8, $t6, $t7
  /* 17FCB8 801325B8 AD180004 */        sw $t8, 4($t0)
  /* 17FCBC 801325BC 8E490000 */        lw $t1, ($s2) # gCreditsHighlightSize + 0
  /* 17FCC0 801325C0 C6680000 */      lwc1 $f8, ($s3) # gCreditsHighlightPositionX + 0
  /* 17FCC4 801325C4 8E030000 */        lw $v1, ($s0) # gDisplayListHead + 0
  /* 17FCC8 801325C8 00095180 */       sll $t2, $t1, 6
  /* 17FCCC 801325CC 01495021 */      addu $t2, $t2, $t1
  /* 17FCD0 801325D0 254C0002 */     addiu $t4, $t2, 2
  /* 17FCD4 801325D4 448C2000 */      mtc1 $t4, $f4
  /* 17FCD8 801325D8 24790008 */     addiu $t9, $v1, 8
  /* 17FCDC 801325DC AE190000 */        sw $t9, ($s0) # gDisplayListHead + 0
  /* 17FCE0 801325E0 468021A0 */   cvt.s.w $f6, $f4
  /* 17FCE4 801325E4 AFA30034 */        sw $v1, 0x34($sp)
  /* 17FCE8 801325E8 46083280 */     add.s $f10, $f6, $f8
  /* 17FCEC 801325EC 4600540D */ trunc.w.s $f16, $f10
  /* 17FCF0 801325F0 44048000 */      mfc1 $a0, $f16
  /* 17FCF4 801325F4 0C04C83D */       jal gmCreditsGetLockOnPosX
  /* 17FCF8 801325F8 00000000 */       nop 
  /* 17FCFC 801325FC 8E4D0000 */        lw $t5, ($s2) # gCreditsHighlightSize + 0
  /* 17FD00 80132600 C6860000 */      lwc1 $f6, ($s4) # gCreditsHighlightPositionY + 0
  /* 17FD04 80132604 8FB00034 */        lw $s0, 0x34($sp)
  /* 17FD08 80132608 000D7080 */       sll $t6, $t5, 2
  /* 17FD0C 8013260C 01CD7023 */      subu $t6, $t6, $t5
  /* 17FD10 80132610 000E7080 */       sll $t6, $t6, 2
  /* 17FD14 80132614 01CD7023 */      subu $t6, $t6, $t5
  /* 17FD18 80132618 000E7080 */       sll $t6, $t6, 2
  /* 17FD1C 8013261C 01CD7021 */      addu $t6, $t6, $t5
  /* 17FD20 80132620 25CF0002 */     addiu $t7, $t6, 2
  /* 17FD24 80132624 448F9000 */      mtc1 $t7, $f18
  /* 17FD28 80132628 00408825 */        or $s1, $v0, $zero
  /* 17FD2C 8013262C 46809120 */   cvt.s.w $f4, $f18
  /* 17FD30 80132630 46062200 */     add.s $f8, $f4, $f6
  /* 17FD34 80132634 4600428D */ trunc.w.s $f10, $f8
  /* 17FD38 80132638 44045000 */      mfc1 $a0, $f10
  /* 17FD3C 8013263C 0C04C847 */       jal gmCreditsGetLockOnPosY
  /* 17FD40 80132640 00000000 */       nop 
  /* 17FD44 80132644 304803FF */      andi $t0, $v0, 0x3ff
  /* 17FD48 80132648 0008C880 */       sll $t9, $t0, 2
  /* 17FD4C 8013264C 3C01F600 */       lui $at, 0xf600
  /* 17FD50 80132650 322A03FF */      andi $t2, $s1, 0x3ff
  /* 17FD54 80132654 000A6380 */       sll $t4, $t2, 0xe
  /* 17FD58 80132658 03214825 */        or $t1, $t9, $at
  /* 17FD5C 8013265C 012C5825 */        or $t3, $t1, $t4
  /* 17FD60 80132660 AE0B0000 */        sw $t3, ($s0)
  /* 17FD64 80132664 8E4D0000 */        lw $t5, ($s2) # gCreditsHighlightSize + 0
  /* 17FD68 80132668 C6640000 */      lwc1 $f4, ($s3) # gCreditsHighlightPositionX + 0
  /* 17FD6C 8013266C 000D7180 */       sll $t6, $t5, 6
  /* 17FD70 80132670 01CD7021 */      addu $t6, $t6, $t5
  /* 17FD74 80132674 448E8000 */      mtc1 $t6, $f16
  /* 17FD78 80132678 00000000 */       nop 
  /* 17FD7C 8013267C 468084A0 */   cvt.s.w $f18, $f16
  /* 17FD80 80132680 46049180 */     add.s $f6, $f18, $f4
  /* 17FD84 80132684 4600320D */ trunc.w.s $f8, $f6
  /* 17FD88 80132688 44044000 */      mfc1 $a0, $f8
  /* 17FD8C 8013268C 0C04C83D */       jal gmCreditsGetLockOnPosX
  /* 17FD90 80132690 00000000 */       nop 
  /* 17FD94 80132694 8E580000 */        lw $t8, ($s2) # gCreditsHighlightSize + 0
  /* 17FD98 80132698 C6920000 */      lwc1 $f18, ($s4) # gCreditsHighlightPositionY + 0
  /* 17FD9C 8013269C 00408825 */        or $s1, $v0, $zero
  /* 17FDA0 801326A0 00180823 */      negu $at, $t8
  /* 17FDA4 801326A4 00014080 */       sll $t0, $at, 2
  /* 17FDA8 801326A8 01014023 */      subu $t0, $t0, $at
  /* 17FDAC 801326AC 000840C0 */       sll $t0, $t0, 3
  /* 17FDB0 801326B0 01014021 */      addu $t0, $t0, $at
  /* 17FDB4 801326B4 44885000 */      mtc1 $t0, $f10
  /* 17FDB8 801326B8 00000000 */       nop 
  /* 17FDBC 801326BC 46805420 */   cvt.s.w $f16, $f10
  /* 17FDC0 801326C0 46128100 */     add.s $f4, $f16, $f18
  /* 17FDC4 801326C4 4600218D */ trunc.w.s $f6, $f4
  /* 17FDC8 801326C8 44043000 */      mfc1 $a0, $f6
  /* 17FDCC 801326CC 0C04C847 */       jal gmCreditsGetLockOnPosY
  /* 17FDD0 801326D0 00000000 */       nop 
  /* 17FDD4 801326D4 304A03FF */      andi $t2, $v0, 0x3ff
  /* 17FDD8 801326D8 322C03FF */      andi $t4, $s1, 0x3ff
  /* 17FDDC 801326DC 000C5B80 */       sll $t3, $t4, 0xe
  /* 17FDE0 801326E0 000A4880 */       sll $t1, $t2, 2
  /* 17FDE4 801326E4 012B6825 */        or $t5, $t1, $t3
  /* 17FDE8 801326E8 AE0D0004 */        sw $t5, 4($s0)
  /* 17FDEC 801326EC 8FBF002C */        lw $ra, 0x2c($sp)
  /* 17FDF0 801326F0 8FB40028 */        lw $s4, 0x28($sp)
  /* 17FDF4 801326F4 8FB30024 */        lw $s3, 0x24($sp)
  /* 17FDF8 801326F8 8FB20020 */        lw $s2, 0x20($sp)
  /* 17FDFC 801326FC 8FB1001C */        lw $s1, 0x1c($sp)
  /* 17FE00 80132700 8FB00018 */        lw $s0, 0x18($sp)
  /* 17FE04 80132704 03E00008 */        jr $ra
  /* 17FE08 80132708 27BD0058 */     addiu $sp, $sp, 0x58

glabel gmCreditsHighlightProcUpdate
  /* 17FE0C 8013270C 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 17FE10 80132710 AFB1001C */        sw $s1, 0x1c($sp)
  /* 17FE14 80132714 AFB40028 */        sw $s4, 0x28($sp)
  /* 17FE18 80132718 AFB30024 */        sw $s3, 0x24($sp)
  /* 17FE1C 8013271C AFB20020 */        sw $s2, 0x20($sp)
  /* 17FE20 80132720 3C118014 */       lui $s1, %hi(gCreditsHighlightSize)
  /* 17FE24 80132724 AFBF002C */        sw $ra, 0x2c($sp)
  /* 17FE28 80132728 AFB00018 */        sw $s0, 0x18($sp)
  /* 17FE2C 8013272C AFA40030 */        sw $a0, 0x30($sp)
  /* 17FE30 80132730 2631A8EC */     addiu $s1, $s1, %lo(gCreditsHighlightSize)
  /* 17FE34 80132734 00009025 */        or $s2, $zero, $zero
  /* 17FE38 80132738 24130006 */     addiu $s3, $zero, 6
  /* 17FE3C 8013273C 24140003 */     addiu $s4, $zero, 3
  /* 17FE40 80132740 AE330000 */        sw $s3, ($s1) # gCreditsHighlightSize + 0
  .L80132744:
  /* 17FE44 80132744 12600008 */      beqz $s3, .L80132768
  /* 17FE48 80132748 02608025 */        or $s0, $s3, $zero
  /* 17FE4C 8013274C 260EFFFF */     addiu $t6, $s0, -1
  .L80132750:
  /* 17FE50 80132750 AE2E0000 */        sw $t6, ($s1) # gCreditsHighlightSize + 0
  /* 17FE54 80132754 0C002C7A */       jal stop_current_process
  /* 17FE58 80132758 24040001 */     addiu $a0, $zero, 1
  /* 17FE5C 8013275C 8E300000 */        lw $s0, ($s1) # gCreditsHighlightSize + 0
  /* 17FE60 80132760 5600FFFB */      bnel $s0, $zero, .L80132750
  /* 17FE64 80132764 260EFFFF */     addiu $t6, $s0, -1
  .L80132768:
  /* 17FE68 80132768 26520001 */     addiu $s2, $s2, 1
  /* 17FE6C 8013276C 5654FFF5 */      bnel $s2, $s4, .L80132744
  /* 17FE70 80132770 AE330000 */        sw $s3, ($s1) # gCreditsHighlightSize + 0
  /* 17FE74 80132774 0C0026A1 */       jal omEjectGObjCommon
  /* 17FE78 80132778 00002025 */        or $a0, $zero, $zero
  /* 17FE7C 8013277C 0C002C7A */       jal stop_current_process
  /* 17FE80 80132780 24040001 */     addiu $a0, $zero, 1
  /* 17FE84 80132784 8FBF002C */        lw $ra, 0x2c($sp)
  /* 17FE88 80132788 8FB00018 */        lw $s0, 0x18($sp)
  /* 17FE8C 8013278C 8FB1001C */        lw $s1, 0x1c($sp)
  /* 17FE90 80132790 8FB20020 */        lw $s2, 0x20($sp)
  /* 17FE94 80132794 8FB30024 */        lw $s3, 0x24($sp)
  /* 17FE98 80132798 8FB40028 */        lw $s4, 0x28($sp)
  /* 17FE9C 8013279C 03E00008 */        jr $ra
  /* 17FEA0 801327A0 27BD0030 */     addiu $sp, $sp, 0x30

glabel gmCreditsMakeHighlightGObj
  /* 17FEA4 801327A4 3C0E8014 */       lui $t6, %hi(gCreditsCrosshairGObj)
  /* 17FEA8 801327A8 8DCEA8CC */        lw $t6, %lo(gCreditsCrosshairGObj)($t6)
  /* 17FEAC 801327AC 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 17FEB0 801327B0 3C028004 */       lui $v0, %hi(gOMObjCommonLinks + (0x09 * 4))
  /* 17FEB4 801327B4 8C426714 */        lw $v0, %lo(gOMObjCommonLinks + (0x09 * 4))($v0)
  /* 17FEB8 801327B8 AFBF001C */        sw $ra, 0x1c($sp)
  /* 17FEBC 801327BC AFA40030 */        sw $a0, 0x30($sp)
  /* 17FEC0 801327C0 8DCF0074 */        lw $t7, 0x74($t6)
  /* 17FEC4 801327C4 24040009 */     addiu $a0, $zero, 9
  /* 17FEC8 801327C8 14400021 */      bnez $v0, .L80132850
  /* 17FECC 801327CC AFAF0024 */        sw $t7, 0x24($sp)
  /* 17FED0 801327D0 00002825 */        or $a1, $zero, $zero
  /* 17FED4 801327D4 24060009 */     addiu $a2, $zero, 9
  /* 17FED8 801327D8 0C00265A */       jal omMakeGObjCommon
  /* 17FEDC 801327DC 3C078000 */       lui $a3, 0x8000
  /* 17FEE0 801327E0 3C058013 */       lui $a1, %hi(gmCreditsHighlightProcRender)
  /* 17FEE4 801327E4 2418FFFF */     addiu $t8, $zero, -1
  /* 17FEE8 801327E8 AFA2002C */        sw $v0, 0x2c($sp)
  /* 17FEEC 801327EC AFB80010 */        sw $t8, 0x10($sp)
  /* 17FEF0 801327F0 24A52144 */     addiu $a1, $a1, %lo(gmCreditsHighlightProcRender)
  /* 17FEF4 801327F4 00402025 */        or $a0, $v0, $zero
  /* 17FEF8 801327F8 24060008 */     addiu $a2, $zero, 8
  /* 17FEFC 801327FC 0C00277D */       jal omAddGObjRenderProc
  /* 17FF00 80132800 3C078000 */       lui $a3, 0x8000
  /* 17FF04 80132804 3C058013 */       lui $a1, %hi(gmCreditsHighlightProcUpdate)
  /* 17FF08 80132808 24A5270C */     addiu $a1, $a1, %lo(gmCreditsHighlightProcUpdate)
  /* 17FF0C 8013280C 8FA4002C */        lw $a0, 0x2c($sp)
  /* 17FF10 80132810 00003025 */        or $a2, $zero, $zero
  /* 17FF14 80132814 0C002062 */       jal omAddGObjCommonProc
  /* 17FF18 80132818 24070001 */     addiu $a3, $zero, 1
  /* 17FF1C 8013281C 8FA30024 */        lw $v1, 0x24($sp)
  /* 17FF20 80132820 3C014100 */       lui $at, (0x41000000 >> 16) # 8.0
  /* 17FF24 80132824 44813000 */      mtc1 $at, $f6 # 8.0 to cop1
  /* 17FF28 80132828 C4640058 */      lwc1 $f4, 0x58($v1)
  /* 17FF2C 8013282C 3C018014 */       lui $at, %hi(gCreditsHighlightPositionX)
  /* 17FF30 80132830 46062200 */     add.s $f8, $f4, $f6
  /* 17FF34 80132834 E428A8F0 */      swc1 $f8, %lo(gCreditsHighlightPositionX)($at)
  /* 17FF38 80132838 3C0141A0 */       lui $at, (0x41A00000 >> 16) # 20.0
  /* 17FF3C 8013283C 44818000 */      mtc1 $at, $f16 # 20.0 to cop1
  /* 17FF40 80132840 C46A005C */      lwc1 $f10, 0x5c($v1)
  /* 17FF44 80132844 3C018014 */       lui $at, %hi(gCreditsHighlightPositionY)
  /* 17FF48 80132848 46105480 */     add.s $f18, $f10, $f16
  /* 17FF4C 8013284C E432A8F4 */      swc1 $f18, %lo(gCreditsHighlightPositionY)($at)
  .L80132850:
  /* 17FF50 80132850 8FBF001C */        lw $ra, 0x1c($sp)
  /* 17FF54 80132854 27BD0030 */     addiu $sp, $sp, 0x30
  /* 17FF58 80132858 03E00008 */        jr $ra
  /* 17FF5C 8013285C 00000000 */       nop 

glabel gmCreditsSetTextQMarks
  /* 17FF60 80132860 27BDFFF0 */     addiu $sp, $sp, -0x10
  /* 17FF64 80132864 AFB1000C */        sw $s1, 0xc($sp)
  /* 17FF68 80132868 AFB00008 */        sw $s0, 8($sp)
  /* 17FF6C 8013286C 3C028013 */       lui $v0, %hi(dCreditsStaffRoleCharacters)
  /* 17FF70 80132870 3C068014 */       lui $a2, %hi(dCreditsStaffRoleTextInfo)
  /* 17FF74 80132874 3C0A8014 */       lui $t2, %hi(D_ovl59_80139E00)
  /* 17FF78 80132878 00808025 */        or $s0, $a0, $zero
  /* 17FF7C 8013287C 00A08825 */        or $s1, $a1, $zero
  /* 17FF80 80132880 24426BA0 */     addiu $v0, $v0, %lo(dCreditsStaffRoleCharacters)
  /* 17FF84 80132884 254A9E00 */     addiu $t2, $t2, %lo(D_ovl59_80139E00)
  /* 17FF88 80132888 24C69B68 */     addiu $a2, $a2, %lo(dCreditsStaffRoleTextInfo)
  /* 17FF8C 8013288C 24090046 */     addiu $t1, $zero, 0x46
  /* 17FF90 80132890 8CC70004 */        lw $a3, 4($a2) # dCreditsStaffRoleTextInfo + 4
  .L80132894:
  /* 17FF94 80132894 00401825 */        or $v1, $v0, $zero
  /* 17FF98 80132898 00002025 */        or $a0, $zero, $zero
  /* 17FF9C 8013289C 18E00027 */      blez $a3, .L8013293C
  /* 17FFA0 801328A0 00002825 */        or $a1, $zero, $zero
  .L801328A4:
  /* 17FFA4 801328A4 00057880 */       sll $t7, $a1, 2
  /* 17FFA8 801328A8 020FC021 */      addu $t8, $s0, $t7
  /* 17FFAC 801328AC 8F190000 */        lw $t9, ($t8)
  /* 17FFB0 801328B0 8C4E0000 */        lw $t6, ($v0) # dCreditsStaffRoleCharacters + 0
  /* 17FFB4 801328B4 24840001 */     addiu $a0, $a0, 1
  /* 17FFB8 801328B8 55D90007 */      bnel $t6, $t9, .L801328D8
  /* 17FFBC 801328BC 00002825 */        or $a1, $zero, $zero
  /* 17FFC0 801328C0 14A00002 */      bnez $a1, .L801328CC
  /* 17FFC4 801328C4 00000000 */       nop 
  /* 17FFC8 801328C8 00401825 */        or $v1, $v0, $zero
  .L801328CC:
  /* 17FFCC 801328CC 10000002 */         b .L801328D8
  /* 17FFD0 801328D0 24A50001 */     addiu $a1, $a1, 1
  /* 17FFD4 801328D4 00002825 */        or $a1, $zero, $zero
  .L801328D8:
  /* 17FFD8 801328D8 54B10016 */      bnel $a1, $s1, .L80132934
  /* 17FFDC 801328DC 0087082A */       slt $at, $a0, $a3
  /* 17FFE0 801328E0 10A00011 */      beqz $a1, .L80132928
  /* 17FFE4 801328E4 30A80003 */      andi $t0, $a1, 3
  /* 17FFE8 801328E8 00084023 */      negu $t0, $t0
  /* 17FFEC 801328EC 11000006 */      beqz $t0, .L80132908
  /* 17FFF0 801328F0 01053821 */      addu $a3, $t0, $a1
  .L801328F4:
  /* 17FFF4 801328F4 24A5FFFF */     addiu $a1, $a1, -1
  /* 17FFF8 801328F8 AC690000 */        sw $t1, ($v1)
  /* 17FFFC 801328FC 14E5FFFD */       bne $a3, $a1, .L801328F4
  /* 180000 80132900 24630004 */     addiu $v1, $v1, 4
  /* 180004 80132904 10A00007 */      beqz $a1, .L80132924
  .L80132908:
  /* 180008 80132908 24A5FFFC */     addiu $a1, $a1, -4
  /* 18000C 8013290C AC690000 */        sw $t1, ($v1)
  /* 180010 80132910 AC690004 */        sw $t1, 4($v1)
  /* 180014 80132914 AC690008 */        sw $t1, 8($v1)
  /* 180018 80132918 AC69000C */        sw $t1, 0xc($v1)
  /* 18001C 8013291C 14A0FFFA */      bnez $a1, .L80132908
  /* 180020 80132920 24630010 */     addiu $v1, $v1, 0x10
  .L80132924:
  /* 180024 80132924 8CC70004 */        lw $a3, 4($a2) # dCreditsStaffRoleTextInfo + 4
  .L80132928:
  /* 180028 80132928 00401825 */        or $v1, $v0, $zero
  /* 18002C 8013292C 00002825 */        or $a1, $zero, $zero
  /* 180030 80132930 0087082A */       slt $at, $a0, $a3
  .L80132934:
  /* 180034 80132934 1420FFDB */      bnez $at, .L801328A4
  /* 180038 80132938 24420004 */     addiu $v0, $v0, 4
  .L8013293C:
  /* 18003C 8013293C 24C60008 */     addiu $a2, $a2, 8
  /* 180040 80132940 54CAFFD4 */      bnel $a2, $t2, .L80132894
  /* 180044 80132944 8CC70004 */        lw $a3, 4($a2) # dCreditsStaffRoleTextInfo + 4
  /* 180048 80132948 8FB00008 */        lw $s0, 8($sp)
  /* 18004C 8013294C 8FB1000C */        lw $s1, 0xc($sp)
  /* 180050 80132950 03E00008 */        jr $ra
  /* 180054 80132954 27BD0010 */     addiu $sp, $sp, 0x10

glabel func_ovl59_80132958
  /* 180058 80132958 27BDFEE8 */     addiu $sp, $sp, -0x118
  /* 18005C 8013295C 3C0E8014 */       lui $t6, %hi(dCreditsTextLuigi)
  /* 180060 80132960 AFBF0014 */        sw $ra, 0x14($sp)
  /* 180064 80132964 25CEA5E0 */     addiu $t6, $t6, %lo(dCreditsTextLuigi)
  /* 180068 80132968 8DD80000 */        lw $t8, ($t6) # dCreditsTextLuigi + 0
  /* 18006C 8013296C 27A400F0 */     addiu $a0, $sp, 0xf0
  /* 180070 80132970 3C088014 */       lui $t0, %hi(dCreditsTextJigglypuff)
  /* 180074 80132974 AC980000 */        sw $t8, ($a0)
  /* 180078 80132978 8DCF0004 */        lw $t7, 4($t6) # dCreditsTextLuigi + 4
  /* 18007C 8013297C 2508A5F4 */     addiu $t0, $t0, %lo(dCreditsTextJigglypuff)
  /* 180080 80132980 250B0024 */     addiu $t3, $t0, 0x24
  /* 180084 80132984 AC8F0004 */        sw $t7, 4($a0)
  /* 180088 80132988 8DD80008 */        lw $t8, 8($t6) # dCreditsTextLuigi + 8
  /* 18008C 8013298C 27B900C8 */     addiu $t9, $sp, 0xc8
  /* 180090 80132990 27AC00A8 */     addiu $t4, $sp, 0xa8
  /* 180094 80132994 AC980008 */        sw $t8, 8($a0)
  /* 180098 80132998 8DCF000C */        lw $t7, 0xc($t6) # dCreditsTextLuigi + 12
  /* 18009C 8013299C 3C0D8014 */       lui $t5, %hi(dCreditsTextCFalcon)
  /* 1800A0 801329A0 3C02800A */       lui $v0, %hi((gSaveData + 0x457))
  /* 1800A4 801329A4 AC8F000C */        sw $t7, 0xc($a0)
  /* 1800A8 801329A8 8DD80010 */        lw $t8, 0x10($t6) # dCreditsTextLuigi + 16
  /* 1800AC 801329AC AC980010 */        sw $t8, 0x10($a0)
  .L801329B0:
  /* 1800B0 801329B0 8D0A0000 */        lw $t2, ($t0) # dCreditsTextJigglypuff + 0
  /* 1800B4 801329B4 2508000C */     addiu $t0, $t0, 0xc
  /* 1800B8 801329B8 2739000C */     addiu $t9, $t9, 0xc
  /* 1800BC 801329BC AF2AFFF4 */        sw $t2, -0xc($t9)
  /* 1800C0 801329C0 8D09FFF8 */        lw $t1, -8($t0) # dCreditsTextJigglypuff + -8
  /* 1800C4 801329C4 AF29FFF8 */        sw $t1, -8($t9)
  /* 1800C8 801329C8 8D0AFFFC */        lw $t2, -4($t0) # dCreditsTextJigglypuff + -4
  /* 1800CC 801329CC 150BFFF8 */       bne $t0, $t3, .L801329B0
  /* 1800D0 801329D0 AF2AFFFC */        sw $t2, -4($t9)
  /* 1800D4 801329D4 8D0A0000 */        lw $t2, ($t0) # dCreditsTextJigglypuff + 0
  /* 1800D8 801329D8 25ADA61C */     addiu $t5, $t5, %lo(dCreditsTextCFalcon)
  /* 1800DC 801329DC 3C0B8014 */       lui $t3, %hi(dCreditsTextNess)
  /* 1800E0 801329E0 AF2A0000 */        sw $t2, ($t9)
  /* 1800E4 801329E4 8DAE0004 */        lw $t6, 4($t5) # dCreditsTextCFalcon + 4
  /* 1800E8 801329E8 8DAF0000 */        lw $t7, ($t5) # dCreditsTextCFalcon + 0
  /* 1800EC 801329EC 256BA63C */     addiu $t3, $t3, %lo(dCreditsTextNess)
  /* 1800F0 801329F0 AD8E0004 */        sw $t6, 4($t4)
  /* 1800F4 801329F4 AD8F0000 */        sw $t7, ($t4)
  /* 1800F8 801329F8 8DAF0008 */        lw $t7, 8($t5) # dCreditsTextCFalcon + 8
  /* 1800FC 801329FC 8DAE000C */        lw $t6, 0xc($t5) # dCreditsTextCFalcon + 12
  /* 180100 80132A00 27B80098 */     addiu $t8, $sp, 0x98
  /* 180104 80132A04 AD8F0008 */        sw $t7, 8($t4)
  /* 180108 80132A08 AD8E000C */        sw $t6, 0xc($t4)
  /* 18010C 80132A0C 8DAE0014 */        lw $t6, 0x14($t5) # dCreditsTextCFalcon + 20
  /* 180110 80132A10 8DAF0010 */        lw $t7, 0x10($t5) # dCreditsTextCFalcon + 16
  /* 180114 80132A14 3C0A8014 */       lui $t2, %hi(dCreditsTextEarthBound)
  /* 180118 80132A18 AD8E0014 */        sw $t6, 0x14($t4)
  /* 18011C 80132A1C AD8F0010 */        sw $t7, 0x10($t4)
  /* 180120 80132A20 8DAF0018 */        lw $t7, 0x18($t5) # dCreditsTextCFalcon + 24
  /* 180124 80132A24 8DAE001C */        lw $t6, 0x1c($t5) # dCreditsTextCFalcon + 28
  /* 180128 80132A28 254AA64C */     addiu $t2, $t2, %lo(dCreditsTextEarthBound)
  /* 18012C 80132A2C AD8F0018 */        sw $t7, 0x18($t4)
  /* 180130 80132A30 AD8E001C */        sw $t6, 0x1c($t4)
  /* 180134 80132A34 8D680004 */        lw $t0, 4($t3) # dCreditsTextNess + 4
  /* 180138 80132A38 8D790000 */        lw $t9, ($t3) # dCreditsTextNess + 0
  /* 18013C 80132A3C 254E0024 */     addiu $t6, $t2, 0x24
  /* 180140 80132A40 AF080004 */        sw $t0, 4($t8)
  /* 180144 80132A44 AF190000 */        sw $t9, ($t8)
  /* 180148 80132A48 8D790008 */        lw $t9, 8($t3) # dCreditsTextNess + 8
  /* 18014C 80132A4C 8D68000C */        lw $t0, 0xc($t3) # dCreditsTextNess + 12
  /* 180150 80132A50 27A90070 */     addiu $t1, $sp, 0x70
  /* 180154 80132A54 AF190008 */        sw $t9, 8($t8)
  /* 180158 80132A58 AF08000C */        sw $t0, 0xc($t8)
  .L80132A5C:
  /* 18015C 80132A5C 8D4D0000 */        lw $t5, ($t2) # dCreditsTextEarthBound + 0
  /* 180160 80132A60 254A000C */     addiu $t2, $t2, 0xc
  /* 180164 80132A64 2529000C */     addiu $t1, $t1, 0xc
  /* 180168 80132A68 AD2DFFF4 */        sw $t5, -0xc($t1)
  /* 18016C 80132A6C 8D4CFFF8 */        lw $t4, -8($t2) # dCreditsTextEarthBound + -8
  /* 180170 80132A70 AD2CFFF8 */        sw $t4, -8($t1)
  /* 180174 80132A74 8D4DFFFC */        lw $t5, -4($t2) # dCreditsTextEarthBound + -4
  /* 180178 80132A78 154EFFF8 */       bne $t2, $t6, .L80132A5C
  /* 18017C 80132A7C AD2DFFFC */        sw $t5, -4($t1)
  /* 180180 80132A80 8D4D0000 */        lw $t5, ($t2) # dCreditsTextEarthBound + 0
  /* 180184 80132A84 3C188014 */       lui $t8, %hi(dCreditsTextFZero)
  /* 180188 80132A88 2718A674 */     addiu $t8, $t8, %lo(dCreditsTextFZero)
  /* 18018C 80132A8C AD2D0000 */        sw $t5, ($t1)
  /* 180190 80132A90 8F0B0004 */        lw $t3, 4($t8) # dCreditsTextFZero + 4
  /* 180194 80132A94 8F080000 */        lw $t0, ($t8) # dCreditsTextFZero + 0
  /* 180198 80132A98 27AF0050 */     addiu $t7, $sp, 0x50
  /* 18019C 80132A9C ADEB0004 */        sw $t3, 4($t7)
  /* 1801A0 80132AA0 ADE80000 */        sw $t0, ($t7)
  /* 1801A4 80132AA4 8F080008 */        lw $t0, 8($t8) # dCreditsTextFZero + 8
  /* 1801A8 80132AA8 8F0B000C */        lw $t3, 0xc($t8) # dCreditsTextFZero + 12
  /* 1801AC 80132AAC 3C0E8014 */       lui $t6, %hi(dCreditsTextClassicMario)
  /* 1801B0 80132AB0 ADE80008 */        sw $t0, 8($t7)
  /* 1801B4 80132AB4 ADEB000C */        sw $t3, 0xc($t7)
  /* 1801B8 80132AB8 8F0B0014 */        lw $t3, 0x14($t8) # dCreditsTextFZero + 20
  /* 1801BC 80132ABC 8F080010 */        lw $t0, 0x10($t8) # dCreditsTextFZero + 16
  /* 1801C0 80132AC0 25CEA694 */     addiu $t6, $t6, %lo(dCreditsTextClassicMario)
  /* 1801C4 80132AC4 ADEB0014 */        sw $t3, 0x14($t7)
  /* 1801C8 80132AC8 ADE80010 */        sw $t0, 0x10($t7)
  /* 1801CC 80132ACC 8F080018 */        lw $t0, 0x18($t8) # dCreditsTextFZero + 24
  /* 1801D0 80132AD0 8F0B001C */        lw $t3, 0x1c($t8) # dCreditsTextFZero + 28
  /* 1801D4 80132AD4 25CC0030 */     addiu $t4, $t6, 0x30
  /* 1801D8 80132AD8 27B90020 */     addiu $t9, $sp, 0x20
  /* 1801DC 80132ADC ADE80018 */        sw $t0, 0x18($t7)
  /* 1801E0 80132AE0 ADEB001C */        sw $t3, 0x1c($t7)
  .L80132AE4:
  /* 1801E4 80132AE4 8DC90000 */        lw $t1, ($t6) # dCreditsTextClassicMario + 0
  /* 1801E8 80132AE8 25CE000C */     addiu $t6, $t6, 0xc
  /* 1801EC 80132AEC 2739000C */     addiu $t9, $t9, 0xc
  /* 1801F0 80132AF0 AF29FFF4 */        sw $t1, -0xc($t9)
  /* 1801F4 80132AF4 8DCAFFF8 */        lw $t2, -8($t6) # dCreditsTextClassicMario + -8
  /* 1801F8 80132AF8 AF2AFFF8 */        sw $t2, -8($t9)
  /* 1801FC 80132AFC 8DC9FFFC */        lw $t1, -4($t6) # dCreditsTextClassicMario + -4
  /* 180200 80132B00 15CCFFF8 */       bne $t6, $t4, .L80132AE4
  /* 180204 80132B04 AF29FFFC */        sw $t1, -4($t9)
  /* 180208 80132B08 90424937 */       lbu $v0, %lo((gSaveData + 0x457))($v0)
  /* 18020C 80132B0C 304D0001 */      andi $t5, $v0, 1
  /* 180210 80132B10 55A00006 */      bnel $t5, $zero, .L80132B2C
  /* 180214 80132B14 304F0008 */      andi $t7, $v0, 8
  /* 180218 80132B18 0C04CA18 */       jal gmCreditsSetTextQMarks
  /* 18021C 80132B1C 24050005 */     addiu $a1, $zero, 5
  /* 180220 80132B20 3C02800A */       lui $v0, %hi((gSaveData + 0x457))
  /* 180224 80132B24 90424937 */       lbu $v0, %lo((gSaveData + 0x457))($v0)
  /* 180228 80132B28 304F0008 */      andi $t7, $v0, 8
  .L80132B2C:
  /* 18022C 80132B2C 15E00005 */      bnez $t7, .L80132B44
  /* 180230 80132B30 27A400C8 */     addiu $a0, $sp, 0xc8
  /* 180234 80132B34 0C04CA18 */       jal gmCreditsSetTextQMarks
  /* 180238 80132B38 2405000A */     addiu $a1, $zero, 0xa
  /* 18023C 80132B3C 3C02800A */       lui $v0, %hi((gSaveData + 0x457))
  /* 180240 80132B40 90424937 */       lbu $v0, %lo((gSaveData + 0x457))($v0)
  .L80132B44:
  /* 180244 80132B44 30580004 */      andi $t8, $v0, 4
  /* 180248 80132B48 17000008 */      bnez $t8, .L80132B6C
  /* 18024C 80132B4C 27A400A8 */     addiu $a0, $sp, 0xa8
  /* 180250 80132B50 0C04CA18 */       jal gmCreditsSetTextQMarks
  /* 180254 80132B54 24050008 */     addiu $a1, $zero, 8
  /* 180258 80132B58 27A40050 */     addiu $a0, $sp, 0x50
  /* 18025C 80132B5C 0C04CA18 */       jal gmCreditsSetTextQMarks
  /* 180260 80132B60 24050008 */     addiu $a1, $zero, 8
  /* 180264 80132B64 3C02800A */       lui $v0, %hi((gSaveData + 0x457))
  /* 180268 80132B68 90424937 */       lbu $v0, %lo((gSaveData + 0x457))($v0)
  .L80132B6C:
  /* 18026C 80132B6C 304B0002 */      andi $t3, $v0, 2
  /* 180270 80132B70 15600008 */      bnez $t3, .L80132B94
  /* 180274 80132B74 27A40098 */     addiu $a0, $sp, 0x98
  /* 180278 80132B78 0C04CA18 */       jal gmCreditsSetTextQMarks
  /* 18027C 80132B7C 24050004 */     addiu $a1, $zero, 4
  /* 180280 80132B80 27A40070 */     addiu $a0, $sp, 0x70
  /* 180284 80132B84 0C04CA18 */       jal gmCreditsSetTextQMarks
  /* 180288 80132B88 2405000A */     addiu $a1, $zero, 0xa
  /* 18028C 80132B8C 3C02800A */       lui $v0, %hi((gSaveData + 0x457))
  /* 180290 80132B90 90424937 */       lbu $v0, %lo((gSaveData + 0x457))($v0)
  .L80132B94:
  /* 180294 80132B94 30480010 */      andi $t0, $v0, 0x10
  /* 180298 80132B98 15000003 */      bnez $t0, .L80132BA8
  /* 18029C 80132B9C 27A40020 */     addiu $a0, $sp, 0x20
  /* 1802A0 80132BA0 0C04CA18 */       jal gmCreditsSetTextQMarks
  /* 1802A4 80132BA4 2405000C */     addiu $a1, $zero, 0xc
  .L80132BA8:
  /* 1802A8 80132BA8 8FBF0014 */        lw $ra, 0x14($sp)
  /* 1802AC 80132BAC 27BD0118 */     addiu $sp, $sp, 0x118
  /* 1802B0 80132BB0 03E00008 */        jr $ra
  /* 1802B4 80132BB4 00000000 */       nop 

glabel gmCreditsMakeStaffRoleTextSObjs
  /* 1802B8 80132BB8 27BDFFB0 */     addiu $sp, $sp, -0x50
  /* 1802BC 80132BBC AFBF0024 */        sw $ra, 0x24($sp)
  /* 1802C0 80132BC0 AFB10020 */        sw $s1, 0x20($sp)
  /* 1802C4 80132BC4 AFB0001C */        sw $s0, 0x1c($sp)
  /* 1802C8 80132BC8 F7B40010 */      sdc1 $f20, 0x10($sp)
  /* 1802CC 80132BCC AFA40050 */        sw $a0, 0x50($sp)
  /* 1802D0 80132BD0 8CA30084 */        lw $v1, 0x84($a1)
  /* 1802D4 80132BD4 3C188014 */       lui $t8, %hi(dCreditsStaffRoleTextInfo)
  /* 1802D8 80132BD8 27189B68 */     addiu $t8, $t8, %lo(dCreditsStaffRoleTextInfo)
  /* 1802DC 80132BDC 8C6E0004 */        lw $t6, 4($v1)
  /* 1802E0 80132BE0 3C0143AF */       lui $at, (0x43AF0000 >> 16) # 350.0
  /* 1802E4 80132BE4 44810000 */      mtc1 $at, $f0 # 350.0 to cop1
  /* 1802E8 80132BE8 000E78C0 */       sll $t7, $t6, 3
  /* 1802EC 80132BEC 01F81021 */      addu $v0, $t7, $t8
  /* 1802F0 80132BF0 8C480004 */        lw $t0, 4($v0)
  /* 1802F4 80132BF4 3C014220 */       lui $at, (0x42200000 >> 16) # 40.0
  /* 1802F8 80132BF8 44811000 */      mtc1 $at, $f2 # 40.0 to cop1
  /* 1802FC 80132BFC 8C470000 */        lw $a3, ($v0)
  /* 180300 80132C00 19000096 */      blez $t0, .L80132E5C
  /* 180304 80132C04 00003025 */        or $a2, $zero, $zero
  /* 180308 80132C08 0007C880 */       sll $t9, $a3, 2
  /* 18030C 80132C0C 3C098013 */       lui $t1, %hi(dCreditsStaffRoleCharacters)
  /* 180310 80132C10 3C014040 */       lui $at, (0x40400000 >> 16) # 3.0
  /* 180314 80132C14 25296BA0 */     addiu $t1, $t1, %lo(dCreditsStaffRoleCharacters)
  /* 180318 80132C18 3C118014 */       lui $s1, %hi(dCreditsTextBoxSpriteInfo)
  /* 18031C 80132C1C 44817000 */      mtc1 $at, $f14 # 3.0 to cop1
  /* 180320 80132C20 2631A348 */     addiu $s1, $s1, %lo(dCreditsTextBoxSpriteInfo)
  /* 180324 80132C24 03291821 */      addu $v1, $t9, $t1
  /* 180328 80132C28 2407FFDF */     addiu $a3, $zero, -0x21
  .L80132C2C:
  /* 18032C 80132C2C 8C700000 */        lw $s0, ($v1)
  /* 180330 80132C30 2401FFC9 */     addiu $at, $zero, -0x37
  /* 180334 80132C34 10F0007D */       beq $a3, $s0, .L80132E2C
  /* 180338 80132C38 00000000 */       nop 
  /* 18033C 80132C3C 1201007B */       beq $s0, $at, .L80132E2C
  /* 180340 80132C40 8FA40050 */        lw $a0, 0x50($sp)
  /* 180344 80132C44 001050C0 */       sll $t2, $s0, 3
  /* 180348 80132C48 022A5821 */      addu $t3, $s1, $t2
  /* 18034C 80132C4C 8D6C0004 */        lw $t4, 4($t3)
  /* 180350 80132C50 3C0D8014 */       lui $t5, %hi(gCreditsSpriteFile)
  /* 180354 80132C54 8DADAA10 */        lw $t5, %lo(gCreditsSpriteFile)($t5)
  /* 180358 80132C58 4480A000 */      mtc1 $zero, $f20
  /* 18035C 80132C5C E7A20034 */      swc1 $f2, 0x34($sp)
  /* 180360 80132C60 E7A00038 */      swc1 $f0, 0x38($sp)
  /* 180364 80132C64 AFA8003C */        sw $t0, 0x3c($sp)
  /* 180368 80132C68 AFA60044 */        sw $a2, 0x44($sp)
  /* 18036C 80132C6C AFA3002C */        sw $v1, 0x2c($sp)
  /* 180370 80132C70 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 180374 80132C74 018D2821 */      addu $a1, $t4, $t5
  /* 180378 80132C78 8FA3002C */        lw $v1, 0x2c($sp)
  /* 18037C 80132C7C C7A00038 */      lwc1 $f0, 0x38($sp)
  /* 180380 80132C80 8FA60044 */        lw $a2, 0x44($sp)
  /* 180384 80132C84 8FA8003C */        lw $t0, 0x3c($sp)
  /* 180388 80132C88 C7A20034 */      lwc1 $f2, 0x34($sp)
  /* 18038C 80132C8C 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 180390 80132C90 44816000 */      mtc1 $at, $f12 # 1.0 to cop1
  /* 180394 80132C94 240E0001 */     addiu $t6, $zero, 1
  /* 180398 80132C98 240F00B7 */     addiu $t7, $zero, 0xb7
  /* 18039C 80132C9C 241800BC */     addiu $t8, $zero, 0xbc
  /* 1803A0 80132CA0 241900EC */     addiu $t9, $zero, 0xec
  /* 1803A4 80132CA4 A44E0024 */        sh $t6, 0x24($v0)
  /* 1803A8 80132CA8 A04F0028 */        sb $t7, 0x28($v0)
  /* 1803AC 80132CAC A0580029 */        sb $t8, 0x29($v0)
  /* 1803B0 80132CB0 A059002A */        sb $t9, 0x2a($v0)
  /* 1803B4 80132CB4 E4400058 */      swc1 $f0, 0x58($v0)
  /* 1803B8 80132CB8 E44C001C */      swc1 $f12, 0x1c($v0)
  /* 1803BC 80132CBC E44C0018 */      swc1 $f12, 0x18($v0)
  /* 1803C0 80132CC0 8C700000 */        lw $s0, ($v1)
  /* 1803C4 80132CC4 3C014040 */       lui $at, (0x40400000 >> 16) # 3.0
  /* 1803C8 80132CC8 44817000 */      mtc1 $at, $f14 # 3.0 to cop1
  /* 1803CC 80132CCC 2A01001A */      slti $at, $s0, 0x1a
  /* 1803D0 80132CD0 14200035 */      bnez $at, .L80132DA8
  /* 1803D4 80132CD4 2407FFDF */     addiu $a3, $zero, -0x21
  /* 1803D8 80132CD8 2401001B */     addiu $at, $zero, 0x1b
  /* 1803DC 80132CDC 1201002F */       beq $s0, $at, .L80132D9C
  /* 1803E0 80132CE0 46007506 */     mov.s $f20, $f14
  /* 1803E4 80132CE4 2401001D */     addiu $at, $zero, 0x1d
  /* 1803E8 80132CE8 1201002C */       beq $s0, $at, .L80132D9C
  /* 1803EC 80132CEC 2401001F */     addiu $at, $zero, 0x1f
  /* 1803F0 80132CF0 1201002A */       beq $s0, $at, .L80132D9C
  /* 1803F4 80132CF4 24010021 */     addiu $at, $zero, 0x21
  /* 1803F8 80132CF8 12010028 */       beq $s0, $at, .L80132D9C
  /* 1803FC 80132CFC 24010022 */     addiu $at, $zero, 0x22
  /* 180400 80132D00 12010026 */       beq $s0, $at, .L80132D9C
  /* 180404 80132D04 24010023 */     addiu $at, $zero, 0x23
  /* 180408 80132D08 12010024 */       beq $s0, $at, .L80132D9C
  /* 18040C 80132D0C 24010024 */     addiu $at, $zero, 0x24
  /* 180410 80132D10 12010022 */       beq $s0, $at, .L80132D9C
  /* 180414 80132D14 24010025 */     addiu $at, $zero, 0x25
  /* 180418 80132D18 12010020 */       beq $s0, $at, .L80132D9C
  /* 18041C 80132D1C 2401002D */     addiu $at, $zero, 0x2d
  /* 180420 80132D20 1201001E */       beq $s0, $at, .L80132D9C
  /* 180424 80132D24 24010034 */     addiu $at, $zero, 0x34
  /* 180428 80132D28 1201001C */       beq $s0, $at, .L80132D9C
  /* 18042C 80132D2C 24010035 */     addiu $at, $zero, 0x35
  /* 180430 80132D30 1201001A */       beq $s0, $at, .L80132D9C
  /* 180434 80132D34 24010036 */     addiu $at, $zero, 0x36
  /* 180438 80132D38 12010018 */       beq $s0, $at, .L80132D9C
  /* 18043C 80132D3C 24010037 */     addiu $at, $zero, 0x37
  /* 180440 80132D40 12010016 */       beq $s0, $at, .L80132D9C
  /* 180444 80132D44 24010038 */     addiu $at, $zero, 0x38
  /* 180448 80132D48 12010014 */       beq $s0, $at, .L80132D9C
  /* 18044C 80132D4C 24010039 */     addiu $at, $zero, 0x39
  /* 180450 80132D50 12010012 */       beq $s0, $at, .L80132D9C
  /* 180454 80132D54 2401003A */     addiu $at, $zero, 0x3a
  /* 180458 80132D58 12010010 */       beq $s0, $at, .L80132D9C
  /* 18045C 80132D5C 2401003B */     addiu $at, $zero, 0x3b
  /* 180460 80132D60 1201000E */       beq $s0, $at, .L80132D9C
  /* 180464 80132D64 2401003C */     addiu $at, $zero, 0x3c
  /* 180468 80132D68 1201000C */       beq $s0, $at, .L80132D9C
  /* 18046C 80132D6C 2401003D */     addiu $at, $zero, 0x3d
  /* 180470 80132D70 1201000A */       beq $s0, $at, .L80132D9C
  /* 180474 80132D74 2401003E */     addiu $at, $zero, 0x3e
  /* 180478 80132D78 12010008 */       beq $s0, $at, .L80132D9C
  /* 18047C 80132D7C 24010042 */     addiu $at, $zero, 0x42
  /* 180480 80132D80 12010006 */       beq $s0, $at, .L80132D9C
  /* 180484 80132D84 24010046 */     addiu $at, $zero, 0x46
  /* 180488 80132D88 12010004 */       beq $s0, $at, .L80132D9C
  /* 18048C 80132D8C 24010049 */     addiu $at, $zero, 0x49
  /* 180490 80132D90 12010002 */       beq $s0, $at, .L80132D9C
  /* 180494 80132D94 24010043 */     addiu $at, $zero, 0x43
  /* 180498 80132D98 16010003 */       bne $s0, $at, .L80132DA8
  .L80132D9C:
  /* 18049C 80132D9C 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 1804A0 80132DA0 4481A000 */      mtc1 $at, $f20 # 1.0 to cop1
  /* 1804A4 80132DA4 00000000 */       nop 
  .L80132DA8:
  /* 1804A8 80132DA8 2401003F */     addiu $at, $zero, 0x3f
  /* 1804AC 80132DAC 16010004 */       bne $s0, $at, .L80132DC0
  /* 1804B0 80132DB0 3C0140C0 */       lui $at, (0x40C00000 >> 16) # 6.0
  /* 1804B4 80132DB4 44812000 */      mtc1 $at, $f4 # 6.0 to cop1
  /* 1804B8 80132DB8 00000000 */       nop 
  /* 1804BC 80132DBC 4604A500 */     add.s $f20, $f20, $f4
  .L80132DC0:
  /* 1804C0 80132DC0 24010040 */     addiu $at, $zero, 0x40
  /* 1804C4 80132DC4 16010004 */       bne $s0, $at, .L80132DD8
  /* 1804C8 80132DC8 3C014000 */       lui $at, (0x40000000 >> 16) # 2.0
  /* 1804CC 80132DCC 44813000 */      mtc1 $at, $f6 # 2.0 to cop1
  /* 1804D0 80132DD0 00000000 */       nop 
  /* 1804D4 80132DD4 4606A500 */     add.s $f20, $f20, $f6
  .L80132DD8:
  /* 1804D8 80132DD8 24010041 */     addiu $at, $zero, 0x41
  /* 1804DC 80132DDC 16010004 */       bne $s0, $at, .L80132DF0
  /* 1804E0 80132DE0 3C0140E0 */       lui $at, (0x40E00000 >> 16) # 7.0
  /* 1804E4 80132DE4 44814000 */      mtc1 $at, $f8 # 7.0 to cop1
  /* 1804E8 80132DE8 00000000 */       nop 
  /* 1804EC 80132DEC 4608A500 */     add.s $f20, $f20, $f8
  .L80132DF0:
  /* 1804F0 80132DF0 46141280 */     add.s $f10, $f2, $f20
  /* 1804F4 80132DF4 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 1804F8 80132DF8 E44A005C */      swc1 $f10, 0x5c($v0)
  /* 1804FC 80132DFC 8C690000 */        lw $t1, ($v1)
  /* 180500 80132E00 000950C0 */       sll $t2, $t1, 3
  /* 180504 80132E04 022A5821 */      addu $t3, $s1, $t2
  /* 180508 80132E08 916C0000 */       lbu $t4, ($t3)
  /* 18050C 80132E0C 448C8000 */      mtc1 $t4, $f16
  /* 180510 80132E10 05810004 */      bgez $t4, .L80132E24
  /* 180514 80132E14 468084A0 */   cvt.s.w $f18, $f16
  /* 180518 80132E18 44812000 */      mtc1 $at, $f4 # 4294967300.0 to cop1
  /* 18051C 80132E1C 00000000 */       nop 
  /* 180520 80132E20 46049480 */     add.s $f18, $f18, $f4
  .L80132E24:
  /* 180524 80132E24 1000000A */         b .L80132E50
  /* 180528 80132E28 46120000 */     add.s $f0, $f0, $f18
  .L80132E2C:
  /* 18052C 80132E2C 14F00003 */       bne $a3, $s0, .L80132E3C
  /* 180530 80132E30 3C0143AF */       lui $at, (0x43AF0000 >> 16) # 350.0
  /* 180534 80132E34 10000006 */         b .L80132E50
  /* 180538 80132E38 460E0000 */     add.s $f0, $f0, $f14
  .L80132E3C:
  /* 18053C 80132E3C 44810000 */      mtc1 $at, $f0 # 350.0 to cop1
  /* 180540 80132E40 3C0141A0 */       lui $at, (0x41A00000 >> 16) # 20.0
  /* 180544 80132E44 44813000 */      mtc1 $at, $f6 # 20.0 to cop1
  /* 180548 80132E48 00000000 */       nop 
  /* 18054C 80132E4C 46061080 */     add.s $f2, $f2, $f6
  .L80132E50:
  /* 180550 80132E50 24C60001 */     addiu $a2, $a2, 1
  /* 180554 80132E54 14C8FF75 */       bne $a2, $t0, .L80132C2C
  /* 180558 80132E58 24630004 */     addiu $v1, $v1, 4
  .L80132E5C:
  /* 18055C 80132E5C 8FBF0024 */        lw $ra, 0x24($sp)
  /* 180560 80132E60 D7B40010 */      ldc1 $f20, 0x10($sp)
  /* 180564 80132E64 8FB0001C */        lw $s0, 0x1c($sp)
  /* 180568 80132E68 8FB10020 */        lw $s1, 0x20($sp)
  /* 18056C 80132E6C 03E00008 */        jr $ra
  /* 180570 80132E70 27BD0050 */     addiu $sp, $sp, 0x50

glabel gmCreditsMakeStaffRoleTextGObj
  /* 180574 80132E74 3C058004 */       lui $a1, %hi(gOMObjCommonLinks + (0x0A * 4))
  /* 180578 80132E78 8CA56718 */        lw $a1, %lo(gOMObjCommonLinks + (0x0A * 4))($a1)
  /* 18057C 80132E7C 27BDFFD8 */     addiu $sp, $sp, -0x28
  /* 180580 80132E80 AFBF001C */        sw $ra, 0x1c($sp)
  /* 180584 80132E84 10A00003 */      beqz $a1, .L80132E94
  /* 180588 80132E88 AFA40028 */        sw $a0, 0x28($sp)
  /* 18058C 80132E8C 0C0026A1 */       jal omEjectGObjCommon
  /* 180590 80132E90 00A02025 */        or $a0, $a1, $zero
  .L80132E94:
  /* 180594 80132E94 24040006 */     addiu $a0, $zero, 6
  /* 180598 80132E98 00002825 */        or $a1, $zero, $zero
  /* 18059C 80132E9C 2406000A */     addiu $a2, $zero, 0xa
  /* 1805A0 80132EA0 0C00265A */       jal omMakeGObjCommon
  /* 1805A4 80132EA4 3C078000 */       lui $a3, 0x8000
  /* 1805A8 80132EA8 3C05800D */       lui $a1, %hi(func_ovl0_800CCF00)
  /* 1805AC 80132EAC 240EFFFF */     addiu $t6, $zero, -1
  /* 1805B0 80132EB0 AFA20024 */        sw $v0, 0x24($sp)
  /* 1805B4 80132EB4 AFAE0010 */        sw $t6, 0x10($sp)
  /* 1805B8 80132EB8 24A5CF00 */     addiu $a1, $a1, %lo(func_ovl0_800CCF00)
  /* 1805BC 80132EBC 00402025 */        or $a0, $v0, $zero
  /* 1805C0 80132EC0 24060005 */     addiu $a2, $zero, 5
  /* 1805C4 80132EC4 0C00277D */       jal omAddGObjRenderProc
  /* 1805C8 80132EC8 3C078000 */       lui $a3, 0x8000
  /* 1805CC 80132ECC 8FA40024 */        lw $a0, 0x24($sp)
  /* 1805D0 80132ED0 3C018014 */       lui $at, %hi(gCreditsStaffRoleTextGObj)
  /* 1805D4 80132ED4 8FA50028 */        lw $a1, 0x28($sp)
  /* 1805D8 80132ED8 0C04CAEE */       jal gmCreditsMakeStaffRoleTextSObjs
  /* 1805DC 80132EDC AC24A8F8 */        sw $a0, %lo(gCreditsStaffRoleTextGObj)($at)
  /* 1805E0 80132EE0 8FBF001C */        lw $ra, 0x1c($sp)
  /* 1805E4 80132EE4 27BD0028 */     addiu $sp, $sp, 0x28
  /* 1805E8 80132EE8 03E00008 */        jr $ra
  /* 1805EC 80132EEC 00000000 */       nop 

glabel gmCreditsMakeCompanyTextSObjs
  /* 1805F0 80132EF0 27BDFF90 */     addiu $sp, $sp, -0x70
  /* 1805F4 80132EF4 AFBF006C */        sw $ra, 0x6c($sp)
  /* 1805F8 80132EF8 AFBE0068 */        sw $fp, 0x68($sp)
  /* 1805FC 80132EFC AFB70064 */        sw $s7, 0x64($sp)
  /* 180600 80132F00 AFB60060 */        sw $s6, 0x60($sp)
  /* 180604 80132F04 AFB5005C */        sw $s5, 0x5c($sp)
  /* 180608 80132F08 AFB40058 */        sw $s4, 0x58($sp)
  /* 18060C 80132F0C AFB30054 */        sw $s3, 0x54($sp)
  /* 180610 80132F10 AFB20050 */        sw $s2, 0x50($sp)
  /* 180614 80132F14 AFB1004C */        sw $s1, 0x4c($sp)
  /* 180618 80132F18 AFB00048 */        sw $s0, 0x48($sp)
  /* 18061C 80132F1C F7BE0040 */      sdc1 $f30, 0x40($sp)
  /* 180620 80132F20 F7BC0038 */      sdc1 $f28, 0x38($sp)
  /* 180624 80132F24 F7BA0030 */      sdc1 $f26, 0x30($sp)
  /* 180628 80132F28 F7B80028 */      sdc1 $f24, 0x28($sp)
  /* 18062C 80132F2C F7B60020 */      sdc1 $f22, 0x20($sp)
  /* 180630 80132F30 F7B40018 */      sdc1 $f20, 0x18($sp)
  /* 180634 80132F34 AFA40070 */        sw $a0, 0x70($sp)
  /* 180638 80132F38 8CA20084 */        lw $v0, 0x84($a1)
  /* 18063C 80132F3C 3C038014 */       lui $v1, %hi(dCreditsCompanyIDs)
  /* 180640 80132F40 2401FFFF */     addiu $at, $zero, -1
  /* 180644 80132F44 8C4E0004 */        lw $t6, 4($v0)
  /* 180648 80132F48 3C198014 */       lui $t9, %hi(dCreditsCompanyTextInfo)
  /* 18064C 80132F4C 27399FD4 */     addiu $t9, $t9, %lo(dCreditsCompanyTextInfo)
  /* 180650 80132F50 000E7880 */       sll $t7, $t6, 2
  /* 180654 80132F54 006F1821 */      addu $v1, $v1, $t7
  /* 180658 80132F58 8C63A034 */        lw $v1, %lo(dCreditsCompanyIDs)($v1)
  /* 18065C 80132F5C 00009025 */        or $s2, $zero, $zero
  /* 180660 80132F60 10610076 */       beq $v1, $at, .L8013313C
  /* 180664 80132F64 0003C0C0 */       sll $t8, $v1, 3
  /* 180668 80132F68 03191021 */      addu $v0, $t8, $t9
  /* 18066C 80132F6C 8C550004 */        lw $s5, 4($v0)
  /* 180670 80132F70 3C0143AF */       lui $at, (0x43AF0000 >> 16) # 350.0
  /* 180674 80132F74 4481B000 */      mtc1 $at, $f22 # 350.0 to cop1
  /* 180678 80132F78 1AA00070 */      blez $s5, .L8013313C
  /* 18067C 80132F7C 8C440000 */        lw $a0, ($v0)
  /* 180680 80132F80 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 180684 80132F84 4481E000 */      mtc1 $at, $f28 # 1.0 to cop1
  /* 180688 80132F88 3C014040 */       lui $at, (0x40400000 >> 16) # 3.0
  /* 18068C 80132F8C 4481D000 */      mtc1 $at, $f26 # 3.0 to cop1
  /* 180690 80132F90 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 180694 80132F94 3C098014 */       lui $t1, %hi(dCreditsCompanyCharacters)
  /* 180698 80132F98 25299E08 */     addiu $t1, $t1, %lo(dCreditsCompanyCharacters)
  /* 18069C 80132F9C 00044080 */       sll $t0, $a0, 2
  /* 1806A0 80132FA0 3C178014 */       lui $s7, %hi(gCreditsSpriteFile)
  /* 1806A4 80132FA4 3C138014 */       lui $s3, %hi(dCreditsTextBoxSpriteInfo)
  /* 1806A8 80132FA8 4481C000 */      mtc1 $at, $f24 # 1.0 to cop1
  /* 1806AC 80132FAC 4480F000 */      mtc1 $zero, $f30
  /* 1806B0 80132FB0 2673A348 */     addiu $s3, $s3, %lo(dCreditsTextBoxSpriteInfo)
  /* 1806B4 80132FB4 26F7AA10 */     addiu $s7, $s7, %lo(gCreditsSpriteFile)
  /* 1806B8 80132FB8 01098821 */      addu $s1, $t0, $t1
  /* 1806BC 80132FBC 241E0001 */     addiu $fp, $zero, 1
  /* 1806C0 80132FC0 2416FFDF */     addiu $s6, $zero, -0x21
  /* 1806C4 80132FC4 24140080 */     addiu $s4, $zero, 0x80
  .L80132FC8:
  /* 1806C8 80132FC8 8E300000 */        lw $s0, ($s1)
  /* 1806CC 80132FCC 8FA40070 */        lw $a0, 0x70($sp)
  /* 1806D0 80132FD0 12D00056 */       beq $s6, $s0, .L8013312C
  /* 1806D4 80132FD4 001050C0 */       sll $t2, $s0, 3
  /* 1806D8 80132FD8 026A5821 */      addu $t3, $s3, $t2
  /* 1806DC 80132FDC 8D6C0004 */        lw $t4, 4($t3)
  /* 1806E0 80132FE0 8EED0000 */        lw $t5, ($s7) # gCreditsSpriteFile + 0
  /* 1806E4 80132FE4 4600F506 */     mov.s $f20, $f30
  /* 1806E8 80132FE8 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 1806EC 80132FEC 018D2821 */      addu $a1, $t4, $t5
  /* 1806F0 80132FF0 240E0040 */     addiu $t6, $zero, 0x40
  /* 1806F4 80132FF4 A45E0024 */        sh $fp, 0x24($v0)
  /* 1806F8 80132FF8 E458001C */      swc1 $f24, 0x1c($v0)
  /* 1806FC 80132FFC E4580018 */      swc1 $f24, 0x18($v0)
  /* 180700 80133000 A0540028 */        sb $s4, 0x28($v0)
  /* 180704 80133004 A04E0029 */        sb $t6, 0x29($v0)
  /* 180708 80133008 A054002A */        sb $s4, 0x2a($v0)
  /* 18070C 8013300C E4560058 */      swc1 $f22, 0x58($v0)
  /* 180710 80133010 8E300000 */        lw $s0, ($s1)
  /* 180714 80133014 2A01001A */      slti $at, $s0, 0x1a
  /* 180718 80133018 1420001B */      bnez $at, .L80133088
  /* 18071C 8013301C 2401001B */     addiu $at, $zero, 0x1b
  /* 180720 80133020 12010018 */       beq $s0, $at, .L80133084
  /* 180724 80133024 4600D506 */     mov.s $f20, $f26
  /* 180728 80133028 2401001D */     addiu $at, $zero, 0x1d
  /* 18072C 8013302C 12010015 */       beq $s0, $at, .L80133084
  /* 180730 80133030 2401001F */     addiu $at, $zero, 0x1f
  /* 180734 80133034 12010013 */       beq $s0, $at, .L80133084
  /* 180738 80133038 24010021 */     addiu $at, $zero, 0x21
  /* 18073C 8013303C 12010011 */       beq $s0, $at, .L80133084
  /* 180740 80133040 24010022 */     addiu $at, $zero, 0x22
  /* 180744 80133044 1201000F */       beq $s0, $at, .L80133084
  /* 180748 80133048 24010023 */     addiu $at, $zero, 0x23
  /* 18074C 8013304C 1201000D */       beq $s0, $at, .L80133084
  /* 180750 80133050 24010024 */     addiu $at, $zero, 0x24
  /* 180754 80133054 1201000B */       beq $s0, $at, .L80133084
  /* 180758 80133058 24010025 */     addiu $at, $zero, 0x25
  /* 18075C 8013305C 12010009 */       beq $s0, $at, .L80133084
  /* 180760 80133060 2401002D */     addiu $at, $zero, 0x2d
  /* 180764 80133064 12010007 */       beq $s0, $at, .L80133084
  /* 180768 80133068 24010034 */     addiu $at, $zero, 0x34
  /* 18076C 8013306C 12010005 */       beq $s0, $at, .L80133084
  /* 180770 80133070 24010042 */     addiu $at, $zero, 0x42
  /* 180774 80133074 12010003 */       beq $s0, $at, .L80133084
  /* 180778 80133078 24010043 */     addiu $at, $zero, 0x43
  /* 18077C 8013307C 56010003 */      bnel $s0, $at, .L8013308C
  /* 180780 80133080 24010047 */     addiu $at, $zero, 0x47
  .L80133084:
  /* 180784 80133084 4600E506 */     mov.s $f20, $f28
  .L80133088:
  /* 180788 80133088 24010047 */     addiu $at, $zero, 0x47
  .L8013308C:
  /* 18078C 8013308C 12010003 */       beq $s0, $at, .L8013309C
  /* 180790 80133090 24010048 */     addiu $at, $zero, 0x48
  /* 180794 80133094 56010003 */      bnel $s0, $at, .L801330A4
  /* 180798 80133098 2401003F */     addiu $at, $zero, 0x3f
  .L8013309C:
  /* 18079C 8013309C 4600F506 */     mov.s $f20, $f30
  /* 1807A0 801330A0 2401003F */     addiu $at, $zero, 0x3f
  .L801330A4:
  /* 1807A4 801330A4 16010004 */       bne $s0, $at, .L801330B8
  /* 1807A8 801330A8 3C0140C0 */       lui $at, (0x40C00000 >> 16) # 6.0
  /* 1807AC 801330AC 44812000 */      mtc1 $at, $f4 # 6.0 to cop1
  /* 1807B0 801330B0 00000000 */       nop 
  /* 1807B4 801330B4 4604A500 */     add.s $f20, $f20, $f4
  .L801330B8:
  /* 1807B8 801330B8 24010040 */     addiu $at, $zero, 0x40
  /* 1807BC 801330BC 16010004 */       bne $s0, $at, .L801330D0
  /* 1807C0 801330C0 3C014000 */       lui $at, (0x40000000 >> 16) # 2.0
  /* 1807C4 801330C4 44813000 */      mtc1 $at, $f6 # 2.0 to cop1
  /* 1807C8 801330C8 00000000 */       nop 
  /* 1807CC 801330CC 4606A500 */     add.s $f20, $f20, $f6
  .L801330D0:
  /* 1807D0 801330D0 24010041 */     addiu $at, $zero, 0x41
  /* 1807D4 801330D4 16010004 */       bne $s0, $at, .L801330E8
  /* 1807D8 801330D8 3C0140E0 */       lui $at, (0x40E00000 >> 16) # 7.0
  /* 1807DC 801330DC 44814000 */      mtc1 $at, $f8 # 7.0 to cop1
  /* 1807E0 801330E0 00000000 */       nop 
  /* 1807E4 801330E4 4608A500 */     add.s $f20, $f20, $f8
  .L801330E8:
  /* 1807E8 801330E8 3C01430C */       lui $at, (0x430C0000 >> 16) # 140.0
  /* 1807EC 801330EC 44815000 */      mtc1 $at, $f10 # 140.0 to cop1
  /* 1807F0 801330F0 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 1807F4 801330F4 46145400 */     add.s $f16, $f10, $f20
  /* 1807F8 801330F8 E450005C */      swc1 $f16, 0x5c($v0)
  /* 1807FC 801330FC 8E2F0000 */        lw $t7, ($s1)
  /* 180800 80133100 000FC0C0 */       sll $t8, $t7, 3
  /* 180804 80133104 0278C821 */      addu $t9, $s3, $t8
  /* 180808 80133108 93280000 */       lbu $t0, ($t9)
  /* 18080C 8013310C 44889000 */      mtc1 $t0, $f18
  /* 180810 80133110 05010004 */      bgez $t0, .L80133124
  /* 180814 80133114 46809120 */   cvt.s.w $f4, $f18
  /* 180818 80133118 44813000 */      mtc1 $at, $f6 # 4294967300.0 to cop1
  /* 18081C 8013311C 00000000 */       nop 
  /* 180820 80133120 46062100 */     add.s $f4, $f4, $f6
  .L80133124:
  /* 180824 80133124 10000002 */         b .L80133130
  /* 180828 80133128 4604B580 */     add.s $f22, $f22, $f4
  .L8013312C:
  /* 18082C 8013312C 461AB580 */     add.s $f22, $f22, $f26
  .L80133130:
  /* 180830 80133130 26520001 */     addiu $s2, $s2, 1
  /* 180834 80133134 1655FFA4 */       bne $s2, $s5, .L80132FC8
  /* 180838 80133138 26310004 */     addiu $s1, $s1, 4
  .L8013313C:
  /* 18083C 8013313C 8FBF006C */        lw $ra, 0x6c($sp)
  /* 180840 80133140 D7B40018 */      ldc1 $f20, 0x18($sp)
  /* 180844 80133144 D7B60020 */      ldc1 $f22, 0x20($sp)
  /* 180848 80133148 D7B80028 */      ldc1 $f24, 0x28($sp)
  /* 18084C 8013314C D7BA0030 */      ldc1 $f26, 0x30($sp)
  /* 180850 80133150 D7BC0038 */      ldc1 $f28, 0x38($sp)
  /* 180854 80133154 D7BE0040 */      ldc1 $f30, 0x40($sp)
  /* 180858 80133158 8FB00048 */        lw $s0, 0x48($sp)
  /* 18085C 8013315C 8FB1004C */        lw $s1, 0x4c($sp)
  /* 180860 80133160 8FB20050 */        lw $s2, 0x50($sp)
  /* 180864 80133164 8FB30054 */        lw $s3, 0x54($sp)
  /* 180868 80133168 8FB40058 */        lw $s4, 0x58($sp)
  /* 18086C 8013316C 8FB5005C */        lw $s5, 0x5c($sp)
  /* 180870 80133170 8FB60060 */        lw $s6, 0x60($sp)
  /* 180874 80133174 8FB70064 */        lw $s7, 0x64($sp)
  /* 180878 80133178 8FBE0068 */        lw $fp, 0x68($sp)
  /* 18087C 8013317C 03E00008 */        jr $ra
  /* 180880 80133180 27BD0070 */     addiu $sp, $sp, 0x70

glabel gmCreditsMakeCompanyTextGObj
  /* 180884 80133184 3C058004 */       lui $a1, %hi(gOMObjCommonLinks + (0x0B * 4))
  /* 180888 80133188 8CA5671C */        lw $a1, %lo(gOMObjCommonLinks + (0x0B * 4))($a1)
  /* 18088C 8013318C 27BDFFD8 */     addiu $sp, $sp, -0x28
  /* 180890 80133190 AFBF001C */        sw $ra, 0x1c($sp)
  /* 180894 80133194 10A00003 */      beqz $a1, .L801331A4
  /* 180898 80133198 AFA40028 */        sw $a0, 0x28($sp)
  /* 18089C 8013319C 0C0026A1 */       jal omEjectGObjCommon
  /* 1808A0 801331A0 00A02025 */        or $a0, $a1, $zero
  .L801331A4:
  /* 1808A4 801331A4 24040007 */     addiu $a0, $zero, 7
  /* 1808A8 801331A8 00002825 */        or $a1, $zero, $zero
  /* 1808AC 801331AC 2406000B */     addiu $a2, $zero, 0xb
  /* 1808B0 801331B0 0C00265A */       jal omMakeGObjCommon
  /* 1808B4 801331B4 3C078000 */       lui $a3, 0x8000
  /* 1808B8 801331B8 3C05800D */       lui $a1, %hi(func_ovl0_800CCF00)
  /* 1808BC 801331BC 240EFFFF */     addiu $t6, $zero, -1
  /* 1808C0 801331C0 AFA20024 */        sw $v0, 0x24($sp)
  /* 1808C4 801331C4 AFAE0010 */        sw $t6, 0x10($sp)
  /* 1808C8 801331C8 24A5CF00 */     addiu $a1, $a1, %lo(func_ovl0_800CCF00)
  /* 1808CC 801331CC 00402025 */        or $a0, $v0, $zero
  /* 1808D0 801331D0 24060006 */     addiu $a2, $zero, 6
  /* 1808D4 801331D4 0C00277D */       jal omAddGObjRenderProc
  /* 1808D8 801331D8 3C078000 */       lui $a3, 0x8000
  /* 1808DC 801331DC 8FA40024 */        lw $a0, 0x24($sp)
  /* 1808E0 801331E0 3C018014 */       lui $at, %hi(gCreditsCompanyTextGObj)
  /* 1808E4 801331E4 8FA50028 */        lw $a1, 0x28($sp)
  /* 1808E8 801331E8 0C04CBBC */       jal gmCreditsMakeCompanyTextSObjs
  /* 1808EC 801331EC AC24A8FC */        sw $a0, %lo(gCreditsCompanyTextGObj)($at)
  /* 1808F0 801331F0 8FBF001C */        lw $ra, 0x1c($sp)
  /* 1808F4 801331F4 27BD0028 */     addiu $sp, $sp, 0x28
  /* 1808F8 801331F8 03E00008 */        jr $ra
  /* 1808FC 801331FC 00000000 */       nop 

glabel gmCreditsCheckCursorHighlightPrompt
  /* 180900 80133200 27BDFFA0 */     addiu $sp, $sp, -0x60
  /* 180904 80133204 AFB00020 */        sw $s0, 0x20($sp)
  /* 180908 80133208 240E0001 */     addiu $t6, $zero, 1
  /* 18090C 8013320C 00A08025 */        or $s0, $a1, $zero
  /* 180910 80133210 AFBF0024 */        sw $ra, 0x24($sp)
  /* 180914 80133214 AFA40060 */        sw $a0, 0x60($sp)
  /* 180918 80133218 AFAE005C */        sw $t6, 0x5c($sp)
  /* 18091C 8013321C C6040044 */      lwc1 $f4, 0x44($s0)
  /* 180920 80133220 8E070040 */        lw $a3, 0x40($s0)
  /* 180924 80133224 8E060034 */        lw $a2, 0x34($s0)
  /* 180928 80133228 8CA50030 */        lw $a1, 0x30($a1)
  /* 18092C 8013322C 27A4004C */     addiu $a0, $sp, 0x4c
  /* 180930 80133230 0C04C79C */       jal func_ovl59_80131E70
  /* 180934 80133234 E7A40010 */      swc1 $f4, 0x10($sp)
  /* 180938 80133238 C606004C */      lwc1 $f6, 0x4c($s0)
  /* 18093C 8013323C 8E050038 */        lw $a1, 0x38($s0)
  /* 180940 80133240 8E06003C */        lw $a2, 0x3c($s0)
  /* 180944 80133244 8E070048 */        lw $a3, 0x48($s0)
  /* 180948 80133248 27A40040 */     addiu $a0, $sp, 0x40
  /* 18094C 8013324C 0C04C79C */       jal func_ovl59_80131E70
  /* 180950 80133250 E7A60010 */      swc1 $f6, 0x10($sp)
  /* 180954 80133254 C608003C */      lwc1 $f8, 0x3c($s0)
  /* 180958 80133258 8E050030 */        lw $a1, 0x30($s0)
  /* 18095C 8013325C 8E060034 */        lw $a2, 0x34($s0)
  /* 180960 80133260 8E070038 */        lw $a3, 0x38($s0)
  /* 180964 80133264 27A40034 */     addiu $a0, $sp, 0x34
  /* 180968 80133268 0C04C79C */       jal func_ovl59_80131E70
  /* 18096C 8013326C E7A80010 */      swc1 $f8, 0x10($sp)
  /* 180970 80133270 C60A004C */      lwc1 $f10, 0x4c($s0)
  /* 180974 80133274 8E050040 */        lw $a1, 0x40($s0)
  /* 180978 80133278 8E060044 */        lw $a2, 0x44($s0)
  /* 18097C 8013327C 8E070048 */        lw $a3, 0x48($s0)
  /* 180980 80133280 27A40028 */     addiu $a0, $sp, 0x28
  /* 180984 80133284 0C04C79C */       jal func_ovl59_80131E70
  /* 180988 80133288 E7AA0010 */      swc1 $f10, 0x10($sp)
  /* 18098C 8013328C 0C04C7AE */       jal gmCreditsCheckCursorNameOverlap
  /* 180990 80133290 27A4004C */     addiu $a0, $sp, 0x4c
  /* 180994 80133294 54400019 */      bnel $v0, $zero, .L801332FC
  /* 180998 80133298 8FBF0024 */        lw $ra, 0x24($sp)
  /* 18099C 8013329C 0C04C7AE */       jal gmCreditsCheckCursorNameOverlap
  /* 1809A0 801332A0 27A40040 */     addiu $a0, $sp, 0x40
  /* 1809A4 801332A4 50400015 */      beql $v0, $zero, .L801332FC
  /* 1809A8 801332A8 8FBF0024 */        lw $ra, 0x24($sp)
  /* 1809AC 801332AC 0C04C7AE */       jal gmCreditsCheckCursorNameOverlap
  /* 1809B0 801332B0 27A40034 */     addiu $a0, $sp, 0x34
  /* 1809B4 801332B4 50400011 */      beql $v0, $zero, .L801332FC
  /* 1809B8 801332B8 8FBF0024 */        lw $ra, 0x24($sp)
  /* 1809BC 801332BC 0C04C7AE */       jal gmCreditsCheckCursorNameOverlap
  /* 1809C0 801332C0 27A40028 */     addiu $a0, $sp, 0x28
  /* 1809C4 801332C4 5440000D */      bnel $v0, $zero, .L801332FC
  /* 1809C8 801332C8 8FBF0024 */        lw $ra, 0x24($sp)
  /* 1809CC 801332CC 0C009A70 */       jal func_800269C0
  /* 1809D0 801332D0 24040015 */     addiu $a0, $zero, 0x15
  /* 1809D4 801332D4 AFA0005C */        sw $zero, 0x5c($sp)
  /* 1809D8 801332D8 0C04C80B */       jal func_ovl59_8013202C
  /* 1809DC 801332DC 8FA40060 */        lw $a0, 0x60($sp)
  /* 1809E0 801332E0 0C04C9E9 */       jal gmCreditsMakeHighlightGObj
  /* 1809E4 801332E4 8FA40060 */        lw $a0, 0x60($sp)
  /* 1809E8 801332E8 0C04CB9D */       jal gmCreditsMakeStaffRoleTextGObj
  /* 1809EC 801332EC 8FA40060 */        lw $a0, 0x60($sp)
  /* 1809F0 801332F0 0C04CC61 */       jal gmCreditsMakeCompanyTextGObj
  /* 1809F4 801332F4 8FA40060 */        lw $a0, 0x60($sp)
  /* 1809F8 801332F8 8FBF0024 */        lw $ra, 0x24($sp)
  .L801332FC:
  /* 1809FC 801332FC 8FA2005C */        lw $v0, 0x5c($sp)
  /* 180A00 80133300 8FB00020 */        lw $s0, 0x20($sp)
  /* 180A04 80133304 03E00008 */        jr $ra
  /* 180A08 80133308 27BD0060 */     addiu $sp, $sp, 0x60

glabel func_ovl59_8013330C
  /* 180A0C 8013330C 27BDFF60 */     addiu $sp, $sp, -0xa0
  /* 180A10 80133310 AFBF003C */        sw $ra, 0x3c($sp)
  /* 180A14 80133314 3C048014 */       lui $a0, %hi(gCreditsPerspective)
  /* 180A18 80133318 AFBE0038 */        sw $fp, 0x38($sp)
  /* 180A1C 8013331C AFB70034 */        sw $s7, 0x34($sp)
  /* 180A20 80133320 AFB60030 */        sw $s6, 0x30($sp)
  /* 180A24 80133324 AFB5002C */        sw $s5, 0x2c($sp)
  /* 180A28 80133328 AFB40028 */        sw $s4, 0x28($sp)
  /* 180A2C 8013332C AFB30024 */        sw $s3, 0x24($sp)
  /* 180A30 80133330 AFB20020 */        sw $s2, 0x20($sp)
  /* 180A34 80133334 AFB1001C */        sw $s1, 0x1c($sp)
  /* 180A38 80133338 AFB00018 */        sw $s0, 0x18($sp)
  /* 180A3C 8013333C 0C04C722 */       jal func_ovl59_80131C88
  /* 180A40 80133340 8C84A8E4 */        lw $a0, %lo(gCreditsPerspective)($a0)
  /* 180A44 80133344 3C118004 */       lui $s1, %hi(gOMObjCommonLinks + (0x03 * 4))
  /* 180A48 80133348 8E3166FC */        lw $s1, %lo(gOMObjCommonLinks + (0x03 * 4))($s1)
  /* 180A4C 8013334C 27BE0060 */     addiu $fp, $sp, 0x60
  /* 180A50 80133350 27B70084 */     addiu $s7, $sp, 0x84
  /* 180A54 80133354 12200025 */      beqz $s1, .L801333EC
  /* 180A58 80133358 27B60080 */     addiu $s6, $sp, 0x80
  /* 180A5C 8013335C 27B50054 */     addiu $s5, $sp, 0x54
  /* 180A60 80133360 27B4007C */     addiu $s4, $sp, 0x7c
  /* 180A64 80133364 27B30078 */     addiu $s3, $sp, 0x78
  /* 180A68 80133368 27B20048 */     addiu $s2, $sp, 0x48
  /* 180A6C 8013336C 8E300074 */        lw $s0, 0x74($s1)
  .L80133370:
  /* 180A70 80133370 02202025 */        or $a0, $s1, $zero
  /* 180A74 80133374 0C04C774 */       jal func_ovl59_80131DD0
  /* 180A78 80133378 02402825 */        or $a1, $s2, $zero
  /* 180A7C 8013337C 02002025 */        or $a0, $s0, $zero
  /* 180A80 80133380 02402825 */        or $a1, $s2, $zero
  /* 180A84 80133384 02603025 */        or $a2, $s3, $zero
  /* 180A88 80133388 0C04C74C */       jal func_ovl59_80131D30
  /* 180A8C 8013338C 02803825 */        or $a3, $s4, $zero
  /* 180A90 80133390 02002025 */        or $a0, $s0, $zero
  /* 180A94 80133394 02A02825 */        or $a1, $s5, $zero
  /* 180A98 80133398 02C03025 */        or $a2, $s6, $zero
  /* 180A9C 8013339C 0C04C74C */       jal func_ovl59_80131D30
  /* 180AA0 801333A0 02E03825 */        or $a3, $s7, $zero
  /* 180AA4 801333A4 02002025 */        or $a0, $s0, $zero
  /* 180AA8 801333A8 03C02825 */        or $a1, $fp, $zero
  /* 180AAC 801333AC 27A60088 */     addiu $a2, $sp, 0x88
  /* 180AB0 801333B0 0C04C74C */       jal func_ovl59_80131D30
  /* 180AB4 801333B4 27A7008C */     addiu $a3, $sp, 0x8c
  /* 180AB8 801333B8 02002025 */        or $a0, $s0, $zero
  /* 180ABC 801333BC 27A5006C */     addiu $a1, $sp, 0x6c
  /* 180AC0 801333C0 27A60090 */     addiu $a2, $sp, 0x90
  /* 180AC4 801333C4 0C04C74C */       jal func_ovl59_80131D30
  /* 180AC8 801333C8 27A70094 */     addiu $a3, $sp, 0x94
  /* 180ACC 801333CC 02202025 */        or $a0, $s1, $zero
  /* 180AD0 801333D0 0C04CC80 */       jal gmCreditsCheckCursorHighlightPrompt
  /* 180AD4 801333D4 02402825 */        or $a1, $s2, $zero
  /* 180AD8 801333D8 8E310004 */        lw $s1, 4($s1)
  /* 180ADC 801333DC 52200004 */      beql $s1, $zero, .L801333F0
  /* 180AE0 801333E0 8FBF003C */        lw $ra, 0x3c($sp)
  /* 180AE4 801333E4 5440FFE2 */      bnel $v0, $zero, .L80133370
  /* 180AE8 801333E8 8E300074 */        lw $s0, 0x74($s1)
  .L801333EC:
  /* 180AEC 801333EC 8FBF003C */        lw $ra, 0x3c($sp)
  .L801333F0:
  /* 180AF0 801333F0 8FB00018 */        lw $s0, 0x18($sp)
  /* 180AF4 801333F4 8FB1001C */        lw $s1, 0x1c($sp)
  /* 180AF8 801333F8 8FB20020 */        lw $s2, 0x20($sp)
  /* 180AFC 801333FC 8FB30024 */        lw $s3, 0x24($sp)
  /* 180B00 80133400 8FB40028 */        lw $s4, 0x28($sp)
  /* 180B04 80133404 8FB5002C */        lw $s5, 0x2c($sp)
  /* 180B08 80133408 8FB60030 */        lw $s6, 0x30($sp)
  /* 180B0C 8013340C 8FB70034 */        lw $s7, 0x34($sp)
  /* 180B10 80133410 8FBE0038 */        lw $fp, 0x38($sp)
  /* 180B14 80133414 03E00008 */        jr $ra
  /* 180B18 80133418 27BD00A0 */     addiu $sp, $sp, 0xa0

glabel gmCreditsCheckPause
  /* 180B1C 8013341C 3C0E8014 */       lui $t6, %hi(gCreditsPlayer)
  /* 180B20 80133420 91CEA904 */       lbu $t6, %lo(gCreditsPlayer)($t6)
  /* 180B24 80133424 3C028004 */       lui $v0, %hi(gPlayerControllers + 2)
  /* 180B28 80133428 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 180B2C 8013342C 000E7880 */       sll $t7, $t6, 2
  /* 180B30 80133430 01EE7821 */      addu $t7, $t7, $t6
  /* 180B34 80133434 000F7840 */       sll $t7, $t7, 1
  /* 180B38 80133438 004F1021 */      addu $v0, $v0, $t7
  /* 180B3C 8013343C 9442522A */       lhu $v0, %lo(gPlayerControllers + 2)($v0)
  /* 180B40 80133440 AFB00018 */        sw $s0, 0x18($sp)
  /* 180B44 80133444 AFBF001C */        sw $ra, 0x1c($sp)
  /* 180B48 80133448 3058C000 */      andi $t8, $v0, 0xc000
  /* 180B4C 8013344C 13000020 */      beqz $t8, .L801334D0
  /* 180B50 80133450 00008025 */        or $s0, $zero, $zero
  /* 180B54 80133454 0C04CCC3 */       jal func_ovl59_8013330C
  /* 180B58 80133458 AFA20020 */        sw $v0, 0x20($sp)
  /* 180B5C 8013345C 8FA30020 */        lw $v1, 0x20($sp)
  /* 180B60 80133460 3C048014 */       lui $a0, %hi(gCreditsStaffRollGObj)
  /* 180B64 80133464 30794000 */      andi $t9, $v1, 0x4000
  /* 180B68 80133468 5320001A */      beql $t9, $zero, .L801334D4
  /* 180B6C 8013346C 8FBF001C */        lw $ra, 0x1c($sp)
  /* 180B70 80133470 8C84A8C8 */        lw $a0, %lo(gCreditsStaffRollGObj)($a0)
  /* 180B74 80133474 10800003 */      beqz $a0, .L80133484
  /* 180B78 80133478 00000000 */       nop 
  /* 180B7C 8013347C 0C002CA1 */       jal func_8000B284
  /* 180B80 80133480 00000000 */       nop 
  .L80133484:
  /* 180B84 80133484 3C108004 */       lui $s0, %hi(gOMObjCommonLinks + (0x03 * 4))
  /* 180B88 80133488 8E1066FC */        lw $s0, %lo(gOMObjCommonLinks + (0x03 * 4))($s0)
  /* 180B8C 8013348C 12000006 */      beqz $s0, .L801334A8
  /* 180B90 80133490 00000000 */       nop 
  .L80133494:
  /* 180B94 80133494 0C002CA1 */       jal func_8000B284
  /* 180B98 80133498 02002025 */        or $a0, $s0, $zero
  /* 180B9C 8013349C 8E100004 */        lw $s0, 4($s0)
  /* 180BA0 801334A0 1600FFFC */      bnez $s0, .L80133494
  /* 180BA4 801334A4 00000000 */       nop 
  .L801334A8:
  /* 180BA8 801334A8 3C108004 */       lui $s0, %hi(gOMObjCommonLinks + (0x04 * 4))
  /* 180BAC 801334AC 8E106700 */        lw $s0, %lo(gOMObjCommonLinks + (0x04 * 4))($s0)
  /* 180BB0 801334B0 52000007 */      beql $s0, $zero, .L801334D0
  /* 180BB4 801334B4 24100001 */     addiu $s0, $zero, 1
  .L801334B8:
  /* 180BB8 801334B8 0C002CA1 */       jal func_8000B284
  /* 180BBC 801334BC 02002025 */        or $a0, $s0, $zero
  /* 180BC0 801334C0 8E100004 */        lw $s0, 4($s0)
  /* 180BC4 801334C4 1600FFFC */      bnez $s0, .L801334B8
  /* 180BC8 801334C8 00000000 */       nop 
  /* 180BCC 801334CC 24100001 */     addiu $s0, $zero, 1
  .L801334D0:
  /* 180BD0 801334D0 8FBF001C */        lw $ra, 0x1c($sp)
  .L801334D4:
  /* 180BD4 801334D4 02001025 */        or $v0, $s0, $zero
  /* 180BD8 801334D8 8FB00018 */        lw $s0, 0x18($sp)
  /* 180BDC 801334DC 03E00008 */        jr $ra
  /* 180BE0 801334E0 27BD0030 */     addiu $sp, $sp, 0x30

glabel func_ovl59_801334E4
  /* 180BE4 801334E4 3C0E8014 */       lui $t6, %hi(gCreditsRollEndWait)
  /* 180BE8 801334E8 8DCEA908 */        lw $t6, %lo(gCreditsRollEndWait)($t6)
  /* 180BEC 801334EC 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 180BF0 801334F0 AFBF0014 */        sw $ra, 0x14($sp)
  /* 180BF4 801334F4 11C00007 */      beqz $t6, .L80133514
  /* 180BF8 801334F8 AFA40020 */        sw $a0, 0x20($sp)
  /* 180BFC 801334FC 3C028014 */       lui $v0, %hi(gCreditsStatus)
  /* 180C00 80133500 8C42A8C0 */        lw $v0, %lo(gCreditsStatus)($v0)
  /* 180C04 80133504 2401FFFF */     addiu $at, $zero, -1
  /* 180C08 80133508 1041003F */       beq $v0, $at, .L80133608
  /* 180C0C 8013350C 2401FFFE */     addiu $at, $zero, -2
  /* 180C10 80133510 1041003D */       beq $v0, $at, .L80133608
  .L80133514:
  /* 180C14 80133514 3C0F8014 */       lui $t7, %hi(gCreditsPlayer)
  /* 180C18 80133518 91EFA904 */       lbu $t7, %lo(gCreditsPlayer)($t7)
  /* 180C1C 8013351C 3C198004 */       lui $t9, %hi(gPlayerControllers + 2)
  /* 180C20 80133520 3C088014 */       lui $t0, %hi(gCreditsStatus)
  /* 180C24 80133524 000FC080 */       sll $t8, $t7, 2
  /* 180C28 80133528 030FC021 */      addu $t8, $t8, $t7
  /* 180C2C 8013352C 0018C040 */       sll $t8, $t8, 1
  /* 180C30 80133530 8D08A8C0 */        lw $t0, %lo(gCreditsStatus)($t0)
  /* 180C34 80133534 0338C821 */      addu $t9, $t9, $t8
  /* 180C38 80133538 9739522A */       lhu $t9, %lo(gPlayerControllers + 2)($t9)
  /* 180C3C 8013353C 24010001 */     addiu $at, $zero, 1
  /* 180C40 80133540 1501000F */       bne $t0, $at, .L80133580
  /* 180C44 80133544 A7B9001A */        sh $t9, 0x1a($sp)
  /* 180C48 80133548 3C038014 */       lui $v1, %hi(gCreditsRollBeginWait)
  /* 180C4C 8013354C 2463A900 */     addiu $v1, $v1, %lo(gCreditsRollBeginWait)
  /* 180C50 80133550 8C620000 */        lw $v0, ($v1) # gCreditsRollBeginWait + 0
  /* 180C54 80133554 28410078 */      slti $at, $v0, 0x78
  /* 180C58 80133558 10200003 */      beqz $at, .L80133568
  /* 180C5C 8013355C 24490001 */     addiu $t1, $v0, 1
  /* 180C60 80133560 10000007 */         b .L80133580
  /* 180C64 80133564 AC690000 */        sw $t1, ($v1) # gCreditsRollBeginWait + 0
  .L80133568:
  /* 180C68 80133568 0C04D1AD */       jal gmCreditsMakeTextBoxBracketSObjs
  /* 180C6C 8013356C 00000000 */       nop 
  /* 180C70 80133570 0C04D1FD */       jal gmCreditsMakeTextBoxGObj
  /* 180C74 80133574 00000000 */       nop 
  /* 180C78 80133578 3C018014 */       lui $at, %hi(gCreditsStatus)
  /* 180C7C 8013357C AC20A8C0 */        sw $zero, %lo(gCreditsStatus)($at)
  .L80133580:
  /* 180C80 80133580 3C038014 */       lui $v1, %hi(gCreditsIsPaused)
  /* 180C84 80133584 8C63A8D0 */        lw $v1, %lo(gCreditsIsPaused)($v1)
  /* 180C88 80133588 14600006 */      bnez $v1, .L801335A4
  /* 180C8C 8013358C 00602025 */        or $a0, $v1, $zero
  /* 180C90 80133590 0C04CD07 */       jal gmCreditsCheckPause
  /* 180C94 80133594 00000000 */       nop 
  /* 180C98 80133598 3C038014 */       lui $v1, %hi(gCreditsIsPaused)
  /* 180C9C 8013359C 8C63A8D0 */        lw $v1, %lo(gCreditsIsPaused)($v1)
  /* 180CA0 801335A0 00402025 */        or $a0, $v0, $zero
  .L801335A4:
  /* 180CA4 801335A4 24010001 */     addiu $at, $zero, 1
  /* 180CA8 801335A8 54610005 */      bnel $v1, $at, .L801335C0
  /* 180CAC 801335AC 97AA001A */       lhu $t2, 0x1a($sp)
  /* 180CB0 801335B0 0C04C6C0 */       jal gmCreditsCheckUnpause
  /* 180CB4 801335B4 00000000 */       nop 
  /* 180CB8 801335B8 00402025 */        or $a0, $v0, $zero
  /* 180CBC 801335BC 97AA001A */       lhu $t2, 0x1a($sp)
  .L801335C0:
  /* 180CC0 801335C0 3C018014 */       lui $at, %hi(gCreditsIsPaused)
  /* 180CC4 801335C4 AC24A8D0 */        sw $a0, %lo(gCreditsIsPaused)($at)
  /* 180CC8 801335C8 314B1000 */      andi $t3, $t2, 0x1000
  /* 180CCC 801335CC 1160000E */      beqz $t3, .L80133608
  /* 180CD0 801335D0 3C028014 */       lui $v0, %hi(gCreditsRollSpeed)
  /* 180CD4 801335D4 2442A8BC */     addiu $v0, $v0, %lo(gCreditsRollSpeed)
  /* 180CD8 801335D8 3C018014 */       lui $at, %hi(D_ovl59_8013A7B0)
  /* 180CDC 801335DC C420A7B0 */      lwc1 $f0, %lo(D_ovl59_8013A7B0)($at)
  /* 180CE0 801335E0 C4440000 */      lwc1 $f4, ($v0) # gCreditsRollSpeed + 0
  /* 180CE4 801335E4 3C018014 */       lui $at, %hi(D_ovl59_8013A7B4)
  /* 180CE8 801335E8 46040032 */    c.eq.s $f0, $f4
  /* 180CEC 801335EC 00000000 */       nop 
  /* 180CF0 801335F0 45020005 */     bc1fl .L80133608
  /* 180CF4 801335F4 E4400000 */      swc1 $f0, ($v0) # gCreditsRollSpeed + 0
  /* 180CF8 801335F8 C426A7B4 */      lwc1 $f6, %lo(D_ovl59_8013A7B4)($at)
  /* 180CFC 801335FC 10000002 */         b .L80133608
  /* 180D00 80133600 E4460000 */      swc1 $f6, ($v0) # gCreditsRollSpeed + 0
  /* 180D04 80133604 E4400000 */      swc1 $f0, ($v0) # gCreditsRollSpeed + 0
  .L80133608:
  /* 180D08 80133608 8FBF0014 */        lw $ra, 0x14($sp)
  /* 180D0C 8013360C 27BD0020 */     addiu $sp, $sp, 0x20
  /* 180D10 80133610 03E00008 */        jr $ra
  /* 180D14 80133614 00000000 */       nop 

glabel gmCreditsNameUpdateAlloc
  /* 180D18 80133618 3C058014 */       lui $a1, %hi(gCreditsNameAllocFree)
  /* 180D1C 8013361C 24A5A8C4 */     addiu $a1, $a1, %lo(gCreditsNameAllocFree)
  /* 180D20 80133620 8CA20000 */        lw $v0, ($a1) # gCreditsNameAllocFree + 0
  /* 180D24 80133624 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 180D28 80133628 AFBF0014 */        sw $ra, 0x14($sp)
  /* 180D2C 8013362C 14400006 */      bnez $v0, .L80133648
  /* 180D30 80133630 AFA40018 */        sw $a0, 0x18($sp)
  /* 180D34 80133634 24040020 */     addiu $a0, $zero, 0x20
  /* 180D38 80133638 0C001260 */       jal hal_alloc
  /* 180D3C 8013363C 24050004 */     addiu $a1, $zero, 4
  /* 180D40 80133640 10000004 */         b .L80133654
  /* 180D44 80133644 00401825 */        or $v1, $v0, $zero
  .L80133648:
  /* 180D48 80133648 8C4E0000 */        lw $t6, ($v0)
  /* 180D4C 8013364C 00401825 */        or $v1, $v0, $zero
  /* 180D50 80133650 ACAE0000 */        sw $t6, ($a1)
  .L80133654:
  /* 180D54 80133654 44800000 */      mtc1 $zero, $f0
  /* 180D58 80133658 AC600018 */        sw $zero, 0x18($v1)
  /* 180D5C 8013365C 00601025 */        or $v0, $v1, $zero
  /* 180D60 80133660 E4600014 */      swc1 $f0, 0x14($v1)
  /* 180D64 80133664 E4600010 */      swc1 $f0, 0x10($v1)
  /* 180D68 80133668 E460000C */      swc1 $f0, 0xc($v1)
  /* 180D6C 8013366C 8FAF0018 */        lw $t7, 0x18($sp)
  /* 180D70 80133670 ADE30084 */        sw $v1, 0x84($t7)
  /* 180D74 80133674 8FBF0014 */        lw $ra, 0x14($sp)
  /* 180D78 80133678 27BD0018 */     addiu $sp, $sp, 0x18
  /* 180D7C 8013367C 03E00008 */        jr $ra
  /* 180D80 80133680 00000000 */       nop 

glabel gmCreditsNameSetPrevAlloc
  /* 180D84 80133684 3C028014 */       lui $v0, %hi(gCreditsNameAllocFree)
  /* 180D88 80133688 2442A8C4 */     addiu $v0, $v0, %lo(gCreditsNameAllocFree)
  /* 180D8C 8013368C 8C4E0000 */        lw $t6, ($v0) # gCreditsNameAllocFree + 0
  /* 180D90 80133690 AC8E0000 */        sw $t6, ($a0)
  /* 180D94 80133694 03E00008 */        jr $ra
  /* 180D98 80133698 AC440000 */        sw $a0, ($v0) # gCreditsNameAllocFree + 0

glabel gmCreditsJobAndNameProcUpdate
  /* 180D9C 8013369C 27BDFF88 */     addiu $sp, $sp, -0x78
  /* 180DA0 801336A0 AFBF004C */        sw $ra, 0x4c($sp)
  /* 180DA4 801336A4 AFB70048 */        sw $s7, 0x48($sp)
  /* 180DA8 801336A8 AFB60044 */        sw $s6, 0x44($sp)
  /* 180DAC 801336AC AFB50040 */        sw $s5, 0x40($sp)
  /* 180DB0 801336B0 AFB4003C */        sw $s4, 0x3c($sp)
  /* 180DB4 801336B4 AFB30038 */        sw $s3, 0x38($sp)
  /* 180DB8 801336B8 AFB20034 */        sw $s2, 0x34($sp)
  /* 180DBC 801336BC AFB10030 */        sw $s1, 0x30($sp)
  /* 180DC0 801336C0 AFB0002C */        sw $s0, 0x2c($sp)
  /* 180DC4 801336C4 F7B80020 */      sdc1 $f24, 0x20($sp)
  /* 180DC8 801336C8 F7B60018 */      sdc1 $f22, 0x18($sp)
  /* 180DCC 801336CC F7B40010 */      sdc1 $f20, 0x10($sp)
  /* 180DD0 801336D0 8C900084 */        lw $s0, 0x84($a0)
  /* 180DD4 801336D4 44802000 */      mtc1 $zero, $f4
  /* 180DD8 801336D8 8C910074 */        lw $s1, 0x74($a0)
  /* 180DDC 801336DC 3C178014 */       lui $s7, %hi(gCreditsStatus)
  /* 180DE0 801336E0 240E0001 */     addiu $t6, $zero, 1
  /* 180DE4 801336E4 E6040014 */      swc1 $f4, 0x14($s0)
  /* 180DE8 801336E8 26F7A8C0 */     addiu $s7, $s7, %lo(gCreditsStatus)
  /* 180DEC 801336EC AC8E007C */        sw $t6, 0x7c($a0)
  /* 180DF0 801336F0 8EEF0000 */        lw $t7, ($s7) # gCreditsStatus + 0
  /* 180DF4 801336F4 0080B025 */        or $s6, $a0, $zero
  /* 180DF8 801336F8 51E00007 */      beql $t7, $zero, .L80133718
  /* 180DFC 801336FC 3C013F80 */       lui $at, 0x3f80
  .L80133700:
  /* 180E00 80133700 0C002C7A */       jal stop_current_process
  /* 180E04 80133704 24040001 */     addiu $a0, $zero, 1
  /* 180E08 80133708 8EF80000 */        lw $t8, ($s7) # gCreditsStatus + 0
  /* 180E0C 8013370C 1700FFFC */      bnez $t8, .L80133700
  /* 180E10 80133710 00000000 */       nop 
  /* 180E14 80133714 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  .L80133718:
  /* 180E18 80133718 AEC0007C */        sw $zero, 0x7c($s6)
  /* 180E1C 8013371C 4481A000 */      mtc1 $at, $f20 # 1.0 to cop1
  /* 180E20 80133720 C6000014 */      lwc1 $f0, 0x14($s0)
  /* 180E24 80133724 3C158014 */       lui $s5, %hi(gCreditsRollSpeed)
  /* 180E28 80133728 3C148014 */       lui $s4, %hi(gCreditsNameInterpolation)
  /* 180E2C 8013372C 4600A032 */    c.eq.s $f20, $f0
  /* 180E30 80133730 2694A8E0 */     addiu $s4, $s4, %lo(gCreditsNameInterpolation)
  /* 180E34 80133734 26B5A8BC */     addiu $s5, $s5, %lo(gCreditsRollSpeed)
  /* 180E38 80133738 3C014140 */       lui $at, (0x41400000 >> 16) # 12.0
  /* 180E3C 8013373C 4501002C */      bc1t .L801337F0
  /* 180E40 80133740 27B30068 */     addiu $s3, $sp, 0x68
  /* 180E44 80133744 4481C000 */      mtc1 $at, $f24 # 12.0 to cop1
  /* 180E48 80133748 3C0142C6 */       lui $at, (0x42C60000 >> 16) # 99.0
  /* 180E4C 8013374C 3C128014 */       lui $s2, %hi(gCreditsNameATrack)
  /* 180E50 80133750 4481B000 */      mtc1 $at, $f22 # 99.0 to cop1
  /* 180E54 80133754 2652A8DC */     addiu $s2, $s2, %lo(gCreditsNameATrack)
  .L80133758:
  /* 180E58 80133758 46160182 */     mul.s $f6, $f0, $f22
  /* 180E5C 8013375C 02202025 */        or $a0, $s1, $zero
  /* 180E60 80133760 8E450000 */        lw $a1, ($s2) # gCreditsNameATrack + 0
  /* 180E64 80133764 44063000 */      mfc1 $a2, $f6
  /* 180E68 80133768 0C002F47 */       jal omAddDObjAnimAll
  /* 180E6C 8013376C 00000000 */       nop 
  /* 180E70 80133770 02602025 */        or $a0, $s3, $zero
  /* 180E74 80133774 8E850000 */        lw $a1, ($s4) # gCreditsNameInterpolation + 0
  /* 180E78 80133778 0C00794C */       jal hal_interpolation_cubic
  /* 180E7C 8013377C 8E060014 */        lw $a2, 0x14($s0)
  /* 180E80 80133780 C608000C */      lwc1 $f8, 0xc($s0)
  /* 180E84 80133784 C7AA0068 */      lwc1 $f10, 0x68($sp)
  /* 180E88 80133788 460A4400 */     add.s $f16, $f8, $f10
  /* 180E8C 8013378C E630001C */      swc1 $f16, 0x1c($s1)
  /* 180E90 80133790 C7B2006C */      lwc1 $f18, 0x6c($sp)
  /* 180E94 80133794 46189100 */     add.s $f4, $f18, $f24
  /* 180E98 80133798 E6240020 */      swc1 $f4, 0x20($s1)
  /* 180E9C 8013379C C7A60070 */      lwc1 $f6, 0x70($sp)
  /* 180EA0 801337A0 E6260024 */      swc1 $f6, 0x24($s1)
  /* 180EA4 801337A4 C6080014 */      lwc1 $f8, 0x14($s0)
  /* 180EA8 801337A8 C6AA0000 */      lwc1 $f10, ($s5) # gCreditsRollSpeed + 0
  /* 180EAC 801337AC 460A4400 */     add.s $f16, $f8, $f10
  /* 180EB0 801337B0 E6100014 */      swc1 $f16, 0x14($s0)
  /* 180EB4 801337B4 C6120014 */      lwc1 $f18, 0x14($s0)
  /* 180EB8 801337B8 4612A03C */    c.lt.s $f20, $f18
  /* 180EBC 801337BC 00000000 */       nop 
  /* 180EC0 801337C0 45000002 */      bc1f .L801337CC
  /* 180EC4 801337C4 00000000 */       nop 
  /* 180EC8 801337C8 E6140014 */      swc1 $f20, 0x14($s0)
  .L801337CC:
  /* 180ECC 801337CC 0C0037CD */       jal func_8000DF34
  /* 180ED0 801337D0 02C02025 */        or $a0, $s6, $zero
  /* 180ED4 801337D4 0C002C7A */       jal stop_current_process
  /* 180ED8 801337D8 24040001 */     addiu $a0, $zero, 1
  /* 180EDC 801337DC C6000014 */      lwc1 $f0, 0x14($s0)
  /* 180EE0 801337E0 4600A032 */    c.eq.s $f20, $f0
  /* 180EE4 801337E4 00000000 */       nop 
  /* 180EE8 801337E8 4500FFDB */      bc1f .L80133758
  /* 180EEC 801337EC 00000000 */       nop 
  .L801337F0:
  /* 180EF0 801337F0 8E190018 */        lw $t9, 0x18($s0)
  /* 180EF4 801337F4 2402FFFF */     addiu $v0, $zero, -1
  /* 180EF8 801337F8 14590002 */       bne $v0, $t9, .L80133804
  /* 180EFC 801337FC 00000000 */       nop 
  /* 180F00 80133800 AEE20000 */        sw $v0, ($s7) # gCreditsStatus + 0
  .L80133804:
  /* 180F04 80133804 0C04CDA1 */       jal gmCreditsNameSetPrevAlloc
  /* 180F08 80133808 02002025 */        or $a0, $s0, $zero
  /* 180F0C 8013380C 0C0026A1 */       jal omEjectGObjCommon
  /* 180F10 80133810 00002025 */        or $a0, $zero, $zero
  /* 180F14 80133814 0C002C7A */       jal stop_current_process
  /* 180F18 80133818 24040001 */     addiu $a0, $zero, 1
  /* 180F1C 8013381C 8FBF004C */        lw $ra, 0x4c($sp)
  /* 180F20 80133820 D7B40010 */      ldc1 $f20, 0x10($sp)
  /* 180F24 80133824 D7B60018 */      ldc1 $f22, 0x18($sp)
  /* 180F28 80133828 D7B80020 */      ldc1 $f24, 0x20($sp)
  /* 180F2C 8013382C 8FB0002C */        lw $s0, 0x2c($sp)
  /* 180F30 80133830 8FB10030 */        lw $s1, 0x30($sp)
  /* 180F34 80133834 8FB20034 */        lw $s2, 0x34($sp)
  /* 180F38 80133838 8FB30038 */        lw $s3, 0x38($sp)
  /* 180F3C 8013383C 8FB4003C */        lw $s4, 0x3c($sp)
  /* 180F40 80133840 8FB50040 */        lw $s5, 0x40($sp)
  /* 180F44 80133844 8FB60044 */        lw $s6, 0x44($sp)
  /* 180F48 80133848 8FB70048 */        lw $s7, 0x48($sp)
  /* 180F4C 8013384C 03E00008 */        jr $ra
  /* 180F50 80133850 27BD0078 */     addiu $sp, $sp, 0x78

glabel gmCreditsJobProcRender
  /* 180F54 80133854 3C0F8004 */       lui $t7, %hi(gOMObjCommonLinks + (0x04 * 4))
  /* 180F58 80133858 8DEF6700 */        lw $t7, %lo(gOMObjCommonLinks + (0x04 * 4))($t7)
  /* 180F5C 8013385C 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 180F60 80133860 AFBF0014 */        sw $ra, 0x14($sp)
  /* 180F64 80133864 148F002C */       bne $a0, $t7, .L80133918
  /* 180F68 80133868 AFA40018 */        sw $a0, 0x18($sp)
  /* 180F6C 8013386C 3C038004 */       lui $v1, %hi(gDisplayListHead)
  /* 180F70 80133870 246365B0 */     addiu $v1, $v1, %lo(gDisplayListHead)
  /* 180F74 80133874 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 180F78 80133878 3C19D700 */       lui $t9, (0xD7000002 >> 16) # 3607101442
  /* 180F7C 8013387C 37390002 */       ori $t9, $t9, (0xD7000002 & 0xFFFF) # 3607101442
  /* 180F80 80133880 24580008 */     addiu $t8, $v0, 8
  /* 180F84 80133884 AC780000 */        sw $t8, ($v1) # gDisplayListHead + 0
  /* 180F88 80133888 2409FFFF */     addiu $t1, $zero, -1
  /* 180F8C 8013388C AC490004 */        sw $t1, 4($v0)
  /* 180F90 80133890 AC590000 */        sw $t9, ($v0)
  /* 180F94 80133894 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 180F98 80133898 3C0BE200 */       lui $t3, (0xE200001C >> 16) # 3791650844
  /* 180F9C 8013389C 3C0C0050 */       lui $t4, (0x504240 >> 16) # 5259840
  /* 180FA0 801338A0 244A0008 */     addiu $t2, $v0, 8
  /* 180FA4 801338A4 AC6A0000 */        sw $t2, ($v1) # gDisplayListHead + 0
  /* 180FA8 801338A8 358C4240 */       ori $t4, $t4, (0x504240 & 0xFFFF) # 5259840
  /* 180FAC 801338AC 356B001C */       ori $t3, $t3, (0xE200001C & 0xFFFF) # 3791650844
  /* 180FB0 801338B0 AC4B0000 */        sw $t3, ($v0)
  /* 180FB4 801338B4 AC4C0004 */        sw $t4, 4($v0)
  /* 180FB8 801338B8 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 180FBC 801338BC 3C0ED9FF */       lui $t6, (0xD9FFFFFE >> 16) # 3657433086
  /* 180FC0 801338C0 35CEFFFE */       ori $t6, $t6, (0xD9FFFFFE & 0xFFFF) # 3657433086
  /* 180FC4 801338C4 244D0008 */     addiu $t5, $v0, 8
  /* 180FC8 801338C8 AC6D0000 */        sw $t5, ($v1) # gDisplayListHead + 0
  /* 180FCC 801338CC AC400004 */        sw $zero, 4($v0)
  /* 180FD0 801338D0 AC4E0000 */        sw $t6, ($v0)
  /* 180FD4 801338D4 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 180FD8 801338D8 3C197F7F */       lui $t9, (0x7F7F89FF >> 16) # 2139064831
  /* 180FDC 801338DC 373989FF */       ori $t9, $t9, (0x7F7F89FF & 0xFFFF) # 2139064831
  /* 180FE0 801338E0 244F0008 */     addiu $t7, $v0, 8
  /* 180FE4 801338E4 AC6F0000 */        sw $t7, ($v1) # gDisplayListHead + 0
  /* 180FE8 801338E8 3C18FA00 */       lui $t8, 0xfa00
  /* 180FEC 801338EC AC580000 */        sw $t8, ($v0)
  /* 180FF0 801338F0 AC590004 */        sw $t9, 4($v0)
  /* 180FF4 801338F4 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 180FF8 801338F8 3C0BFFFD */       lui $t3, (0xFFFDF2F9 >> 16) # 4294832889
  /* 180FFC 801338FC 3C0AFCFF */       lui $t2, (0xFCFFFFFF >> 16) # 4244635647
  /* 181000 80133900 24490008 */     addiu $t1, $v0, 8
  /* 181004 80133904 AC690000 */        sw $t1, ($v1) # gDisplayListHead + 0
  /* 181008 80133908 354AFFFF */       ori $t2, $t2, (0xFCFFFFFF & 0xFFFF) # 4244635647
  /* 18100C 8013390C 356BF2F9 */       ori $t3, $t3, (0xFFFDF2F9 & 0xFFFF) # 4294832889
  /* 181010 80133910 AC4B0004 */        sw $t3, 4($v0)
  /* 181014 80133914 AC4A0000 */        sw $t2, ($v0)
  .L80133918:
  /* 181018 80133918 0C00500E */       jal func_80014038
  /* 18101C 8013391C 8FA40018 */        lw $a0, 0x18($sp)
  /* 181020 80133920 8FBF0014 */        lw $ra, 0x14($sp)
  /* 181024 80133924 27BD0018 */     addiu $sp, $sp, 0x18
  /* 181028 80133928 03E00008 */        jr $ra
  /* 18102C 8013392C 00000000 */       nop 

glabel gmCreditsNameProcRender
  /* 181030 80133930 3C0F8004 */       lui $t7, %hi(gOMObjCommonLinks + (0x03 * 4))
  /* 181034 80133934 8DEF66FC */        lw $t7, %lo(gOMObjCommonLinks + (0x03 * 4))($t7)
  /* 181038 80133938 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 18103C 8013393C AFBF0014 */        sw $ra, 0x14($sp)
  /* 181040 80133940 148F002C */       bne $a0, $t7, .L801339F4
  /* 181044 80133944 AFA40018 */        sw $a0, 0x18($sp)
  /* 181048 80133948 3C038004 */       lui $v1, %hi(gDisplayListHead)
  /* 18104C 8013394C 246365B0 */     addiu $v1, $v1, %lo(gDisplayListHead)
  /* 181050 80133950 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 181054 80133954 3C19D700 */       lui $t9, (0xD7000002 >> 16) # 3607101442
  /* 181058 80133958 37390002 */       ori $t9, $t9, (0xD7000002 & 0xFFFF) # 3607101442
  /* 18105C 8013395C 24580008 */     addiu $t8, $v0, 8
  /* 181060 80133960 AC780000 */        sw $t8, ($v1) # gDisplayListHead + 0
  /* 181064 80133964 2409FFFF */     addiu $t1, $zero, -1
  /* 181068 80133968 AC490004 */        sw $t1, 4($v0)
  /* 18106C 8013396C AC590000 */        sw $t9, ($v0)
  /* 181070 80133970 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 181074 80133974 3C0BE200 */       lui $t3, (0xE200001C >> 16) # 3791650844
  /* 181078 80133978 3C0C0050 */       lui $t4, (0x504240 >> 16) # 5259840
  /* 18107C 8013397C 244A0008 */     addiu $t2, $v0, 8
  /* 181080 80133980 AC6A0000 */        sw $t2, ($v1) # gDisplayListHead + 0
  /* 181084 80133984 358C4240 */       ori $t4, $t4, (0x504240 & 0xFFFF) # 5259840
  /* 181088 80133988 356B001C */       ori $t3, $t3, (0xE200001C & 0xFFFF) # 3791650844
  /* 18108C 8013398C AC4B0000 */        sw $t3, ($v0)
  /* 181090 80133990 AC4C0004 */        sw $t4, 4($v0)
  /* 181094 80133994 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 181098 80133998 3C0ED9FF */       lui $t6, (0xD9FFFFFE >> 16) # 3657433086
  /* 18109C 8013399C 35CEFFFE */       ori $t6, $t6, (0xD9FFFFFE & 0xFFFF) # 3657433086
  /* 1810A0 801339A0 244D0008 */     addiu $t5, $v0, 8
  /* 1810A4 801339A4 AC6D0000 */        sw $t5, ($v1) # gDisplayListHead + 0
  /* 1810A8 801339A8 AC400004 */        sw $zero, 4($v0)
  /* 1810AC 801339AC AC4E0000 */        sw $t6, ($v0)
  /* 1810B0 801339B0 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 1810B4 801339B4 3C198893 */       lui $t9, (0x8893FFFF >> 16) # 2291400703
  /* 1810B8 801339B8 3739FFFF */       ori $t9, $t9, (0x8893FFFF & 0xFFFF) # 2291400703
  /* 1810BC 801339BC 244F0008 */     addiu $t7, $v0, 8
  /* 1810C0 801339C0 AC6F0000 */        sw $t7, ($v1) # gDisplayListHead + 0
  /* 1810C4 801339C4 3C18FA00 */       lui $t8, 0xfa00
  /* 1810C8 801339C8 AC580000 */        sw $t8, ($v0)
  /* 1810CC 801339CC AC590004 */        sw $t9, 4($v0)
  /* 1810D0 801339D0 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 1810D4 801339D4 3C0BFFFD */       lui $t3, (0xFFFDF2F9 >> 16) # 4294832889
  /* 1810D8 801339D8 3C0AFCFF */       lui $t2, (0xFCFFFFFF >> 16) # 4244635647
  /* 1810DC 801339DC 24490008 */     addiu $t1, $v0, 8
  /* 1810E0 801339E0 AC690000 */        sw $t1, ($v1) # gDisplayListHead + 0
  /* 1810E4 801339E4 354AFFFF */       ori $t2, $t2, (0xFCFFFFFF & 0xFFFF) # 4244635647
  /* 1810E8 801339E8 356BF2F9 */       ori $t3, $t3, (0xFFFDF2F9 & 0xFFFF) # 4294832889
  /* 1810EC 801339EC AC4B0004 */        sw $t3, 4($v0)
  /* 1810F0 801339F0 AC4A0000 */        sw $t2, ($v0)
  .L801339F4:
  /* 1810F4 801339F4 0C00500E */       jal func_80014038
  /* 1810F8 801339F8 8FA40018 */        lw $a0, 0x18($sp)
  /* 1810FC 801339FC 8FBF0014 */        lw $ra, 0x14($sp)
  /* 181100 80133A00 27BD0018 */     addiu $sp, $sp, 0x18
  /* 181104 80133A04 03E00008 */        jr $ra
  /* 181108 80133A08 00000000 */       nop 

glabel gmCreditsJobAndNameInitStruct
  /* 18110C 80133A0C 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 181110 80133A10 AFBF0014 */        sw $ra, 0x14($sp)
  /* 181114 80133A14 AFA5001C */        sw $a1, 0x1c($sp)
  /* 181118 80133A18 AFA60020 */        sw $a2, 0x20($sp)
  /* 18111C 80133A1C 0C04CD86 */       jal gmCreditsNameUpdateAlloc
  /* 181120 80133A20 AFA70024 */        sw $a3, 0x24($sp)
  /* 181124 80133A24 8FAE001C */        lw $t6, 0x1c($sp)
  /* 181128 80133A28 8FAF0020 */        lw $t7, 0x20($sp)
  /* 18112C 80133A2C 3C013F00 */       lui $at, (0x3F000000 >> 16) # 0.5
  /* 181130 80133A30 C5C4001C */      lwc1 $f4, 0x1c($t6)
  /* 181134 80133A34 C5E6001C */      lwc1 $f6, 0x1c($t7)
  /* 181138 80133A38 44815000 */      mtc1 $at, $f10 # 0.5 to cop1
  /* 18113C 80133A3C 3C0141D0 */       lui $at, (0x41D00000 >> 16) # 26.0
  /* 181140 80133A40 46062201 */     sub.s $f8, $f4, $f6
  /* 181144 80133A44 44819000 */      mtc1 $at, $f18 # 26.0 to cop1
  /* 181148 80133A48 3C188014 */       lui $t8, %hi(gCreditsNameID)
  /* 18114C 80133A4C 460A4402 */     mul.s $f16, $f8, $f10
  /* 181150 80133A50 E4520010 */      swc1 $f18, 0x10($v0)
  /* 181154 80133A54 E450000C */      swc1 $f16, 0xc($v0)
  /* 181158 80133A58 8F18A8B8 */        lw $t8, %lo(gCreditsNameID)($t8)
  /* 18115C 80133A5C AC580004 */        sw $t8, 4($v0)
  /* 181160 80133A60 8FB90024 */        lw $t9, 0x24($sp)
  /* 181164 80133A64 AC590008 */        sw $t9, 8($v0)
  /* 181168 80133A68 8FBF0014 */        lw $ra, 0x14($sp)
  /* 18116C 80133A6C 27BD0018 */     addiu $sp, $sp, 0x18
  /* 181170 80133A70 03E00008 */        jr $ra
  /* 181174 80133A74 00000000 */       nop 

glabel gmCreditsMakeJobDObjs
  /* 181178 80133A78 27BDFF50 */     addiu $sp, $sp, -0xb0
  /* 18117C 80133A7C 3C0F8013 */       lui $t7, %hi(dCreditsJobTextInfo)
  /* 181180 80133A80 25EF6B10 */     addiu $t7, $t7, %lo(dCreditsJobTextInfo)
  /* 181184 80133A84 000670C0 */       sll $t6, $a2, 3
  /* 181188 80133A88 01CF1021 */      addu $v0, $t6, $t7
  /* 18118C 80133A8C 8C430004 */        lw $v1, 4($v0)
  /* 181190 80133A90 F7B40018 */      sdc1 $f20, 0x18($sp)
  /* 181194 80133A94 4487A000 */      mtc1 $a3, $f20
  /* 181198 80133A98 AFB40058 */        sw $s4, 0x58($sp)
  /* 18119C 80133A9C AFB30054 */        sw $s3, 0x54($sp)
  /* 1811A0 80133AA0 AFB00048 */        sw $s0, 0x48($sp)
  /* 1811A4 80133AA4 AFBF006C */        sw $ra, 0x6c($sp)
  /* 1811A8 80133AA8 AFBE0068 */        sw $fp, 0x68($sp)
  /* 1811AC 80133AAC AFB70064 */        sw $s7, 0x64($sp)
  /* 1811B0 80133AB0 AFB60060 */        sw $s6, 0x60($sp)
  /* 1811B4 80133AB4 AFB5005C */        sw $s5, 0x5c($sp)
  /* 1811B8 80133AB8 AFB20050 */        sw $s2, 0x50($sp)
  /* 1811BC 80133ABC AFB1004C */        sw $s1, 0x4c($sp)
  /* 1811C0 80133AC0 F7BE0040 */      sdc1 $f30, 0x40($sp)
  /* 1811C4 80133AC4 F7BC0038 */      sdc1 $f28, 0x38($sp)
  /* 1811C8 80133AC8 F7BA0030 */      sdc1 $f26, 0x30($sp)
  /* 1811CC 80133ACC F7B80028 */      sdc1 $f24, 0x28($sp)
  /* 1811D0 80133AD0 F7B60020 */      sdc1 $f22, 0x20($sp)
  /* 1811D4 80133AD4 AFA400B0 */        sw $a0, 0xb0($sp)
  /* 1811D8 80133AD8 AFA500B4 */        sw $a1, 0xb4($sp)
  /* 1811DC 80133ADC 2410FFFF */     addiu $s0, $zero, -1
  /* 1811E0 80133AE0 8C530000 */        lw $s3, ($v0)
  /* 1811E4 80133AE4 186000BE */      blez $v1, .L80133DE0
  /* 1811E8 80133AE8 0000A025 */        or $s4, $zero, $zero
  /* 1811EC 80133AEC 3C014080 */       lui $at, (0x40800000 >> 16) # 4.0
  /* 1811F0 80133AF0 4481F000 */      mtc1 $at, $f30 # 4.0 to cop1
  /* 1811F4 80133AF4 3C0140C0 */       lui $at, (0x40C00000 >> 16) # 6.0
  /* 1811F8 80133AF8 4481E000 */      mtc1 $at, $f28 # 6.0 to cop1
  /* 1811FC 80133AFC 3C0141B0 */       lui $at, (0x41B00000 >> 16) # 22.0
  /* 181200 80133B00 3C198013 */       lui $t9, %hi(dCreditsJobCharacters)
  /* 181204 80133B04 2739685C */     addiu $t9, $t9, %lo(dCreditsJobCharacters)
  /* 181208 80133B08 0013C080 */       sll $t8, $s3, 2
  /* 18120C 80133B0C 4481D000 */      mtc1 $at, $f26 # 22.0 to cop1
  /* 181210 80133B10 03198821 */      addu $s1, $t8, $t9
  /* 181214 80133B14 AFA2007C */        sw $v0, 0x7c($sp)
  /* 181218 80133B18 241E001E */     addiu $fp, $zero, 0x1e
  /* 18121C 80133B1C 2417001A */     addiu $s7, $zero, 0x1a
  /* 181220 80133B20 24160032 */     addiu $s6, $zero, 0x32
  /* 181224 80133B24 24150028 */     addiu $s5, $zero, 0x28
  /* 181228 80133B28 8FB20098 */        lw $s2, 0x98($sp)
  .L80133B2C:
  /* 18122C 80133B2C 8E220000 */        lw $v0, ($s1)
  /* 181230 80133B30 2401FFDF */     addiu $at, $zero, -0x21
  /* 181234 80133B34 3C0A8014 */       lui $t2, %hi(dCreditsNameAndJobSpriteInfo)
  /* 181238 80133B38 14410005 */       bne $v0, $at, .L80133B50
  /* 18123C 80133B3C 00024080 */       sll $t0, $v0, 2
  /* 181240 80133B40 3C014180 */       lui $at, (0x41800000 >> 16) # 16.0
  /* 181244 80133B44 44812000 */      mtc1 $at, $f4 # 16.0 to cop1
  /* 181248 80133B48 1000009E */         b .L80133DC4
  /* 18124C 80133B4C 4604A500 */     add.s $f20, $f20, $f4
  .L80133B50:
  /* 181250 80133B50 000248C0 */       sll $t1, $v0, 3
  /* 181254 80133B54 254AA188 */     addiu $t2, $t2, %lo(dCreditsNameAndJobSpriteInfo)
  /* 181258 80133B58 012A1821 */      addu $v1, $t1, $t2
  /* 18125C 80133B5C 906B0000 */       lbu $t3, ($v1)
  /* 181260 80133B60 3C058014 */       lui $a1, %hi(gCreditsNameAndJobDisplayLists)
  /* 181264 80133B64 00A82821 */      addu $a1, $a1, $t0
  /* 181268 80133B68 448B3000 */      mtc1 $t3, $f6
  /* 18126C 80133B6C 8CA5A7D8 */        lw $a1, %lo(gCreditsNameAndJobDisplayLists)($a1)
  /* 181270 80133B70 05610005 */      bgez $t3, .L80133B88
  /* 181274 80133B74 468035A0 */   cvt.s.w $f22, $f6
  /* 181278 80133B78 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 18127C 80133B7C 44814000 */      mtc1 $at, $f8 # 4294967300.0 to cop1
  /* 181280 80133B80 00000000 */       nop 
  /* 181284 80133B84 4608B580 */     add.s $f22, $f22, $f8
  .L80133B88:
  /* 181288 80133B88 906C0001 */       lbu $t4, 1($v1)
  /* 18128C 80133B8C 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 181290 80133B90 448C5000 */      mtc1 $t4, $f10
  /* 181294 80133B94 05810004 */      bgez $t4, .L80133BA8
  /* 181298 80133B98 46805620 */   cvt.s.w $f24, $f10
  /* 18129C 80133B9C 44818000 */      mtc1 $at, $f16 # 4294967300.0 to cop1
  /* 1812A0 80133BA0 00000000 */       nop 
  /* 1812A4 80133BA4 4610C600 */     add.s $f24, $f24, $f16
  .L80133BA8:
  /* 1812A8 80133BA8 0C0024FD */       jal func_800093F4
  /* 1812AC 80133BAC 8FA400B4 */        lw $a0, 0xb4($sp)
  /* 1812B0 80133BB0 00409025 */        or $s2, $v0, $zero
  /* 1812B4 80133BB4 00402025 */        or $a0, $v0, $zero
  /* 1812B8 80133BB8 24050012 */     addiu $a1, $zero, 0x12
  /* 1812BC 80133BBC 0C002330 */       jal func_80008CC0
  /* 1812C0 80133BC0 24060001 */     addiu $a2, $zero, 1
  /* 1812C4 80133BC4 2401FFFF */     addiu $at, $zero, -1
  /* 1812C8 80133BC8 12010056 */       beq $s0, $at, .L80133D24
  /* 1812CC 80133BCC 461AC481 */     sub.s $f18, $f24, $f26
  /* 1812D0 80133BD0 00106880 */       sll $t5, $s0, 2
  /* 1812D4 80133BD4 3C038013 */       lui $v1, %hi(dCreditsJobCharacters)
  /* 1812D8 80133BD8 006D1821 */      addu $v1, $v1, $t5
  /* 1812DC 80133BDC 8C63685C */        lw $v1, %lo(dCreditsJobCharacters)($v1)
  /* 1812E0 80133BE0 2401000A */     addiu $at, $zero, 0xa
  /* 1812E4 80133BE4 10610009 */       beq $v1, $at, .L80133C0C
  /* 1812E8 80133BE8 24010013 */     addiu $at, $zero, 0x13
  /* 1812EC 80133BEC 10610007 */       beq $v1, $at, .L80133C0C
  /* 1812F0 80133BF0 24010015 */     addiu $at, $zero, 0x15
  /* 1812F4 80133BF4 10610005 */       beq $v1, $at, .L80133C0C
  /* 1812F8 80133BF8 24010016 */     addiu $at, $zero, 0x16
  /* 1812FC 80133BFC 10610003 */       beq $v1, $at, .L80133C0C
  /* 181300 80133C00 24010018 */     addiu $at, $zero, 0x18
  /* 181304 80133C04 54610028 */      bnel $v1, $at, .L80133CA8
  /* 181308 80133C08 24010024 */     addiu $at, $zero, 0x24
  .L80133C0C:
  /* 18130C 80133C0C 8E220000 */        lw $v0, ($s1)
  /* 181310 80133C10 2401001C */     addiu $at, $zero, 0x1c
  /* 181314 80133C14 12E20021 */       beq $s7, $v0, .L80133C9C
  /* 181318 80133C18 00000000 */       nop 
  /* 18131C 80133C1C 1041001F */       beq $v0, $at, .L80133C9C
  /* 181320 80133C20 00000000 */       nop 
  /* 181324 80133C24 13C2001D */       beq $fp, $v0, .L80133C9C
  /* 181328 80133C28 24010020 */     addiu $at, $zero, 0x20
  /* 18132C 80133C2C 1041001B */       beq $v0, $at, .L80133C9C
  /* 181330 80133C30 24010026 */     addiu $at, $zero, 0x26
  /* 181334 80133C34 10410019 */       beq $v0, $at, .L80133C9C
  /* 181338 80133C38 24010027 */     addiu $at, $zero, 0x27
  /* 18133C 80133C3C 10410017 */       beq $v0, $at, .L80133C9C
  /* 181340 80133C40 00000000 */       nop 
  /* 181344 80133C44 12A20015 */       beq $s5, $v0, .L80133C9C
  /* 181348 80133C48 24010029 */     addiu $at, $zero, 0x29
  /* 18134C 80133C4C 10410013 */       beq $v0, $at, .L80133C9C
  /* 181350 80133C50 2401002A */     addiu $at, $zero, 0x2a
  /* 181354 80133C54 10410011 */       beq $v0, $at, .L80133C9C
  /* 181358 80133C58 2401002B */     addiu $at, $zero, 0x2b
  /* 18135C 80133C5C 1041000F */       beq $v0, $at, .L80133C9C
  /* 181360 80133C60 2401002C */     addiu $at, $zero, 0x2c
  /* 181364 80133C64 1041000D */       beq $v0, $at, .L80133C9C
  /* 181368 80133C68 2401002E */     addiu $at, $zero, 0x2e
  /* 18136C 80133C6C 1041000B */       beq $v0, $at, .L80133C9C
  /* 181370 80133C70 2401002F */     addiu $at, $zero, 0x2f
  /* 181374 80133C74 10410009 */       beq $v0, $at, .L80133C9C
  /* 181378 80133C78 24010030 */     addiu $at, $zero, 0x30
  /* 18137C 80133C7C 10410007 */       beq $v0, $at, .L80133C9C
  /* 181380 80133C80 24010031 */     addiu $at, $zero, 0x31
  /* 181384 80133C84 10410005 */       beq $v0, $at, .L80133C9C
  /* 181388 80133C88 00000000 */       nop 
  /* 18138C 80133C8C 12C20003 */       beq $s6, $v0, .L80133C9C
  /* 181390 80133C90 24010033 */     addiu $at, $zero, 0x33
  /* 181394 80133C94 54410004 */      bnel $v0, $at, .L80133CA8
  /* 181398 80133C98 24010024 */     addiu $at, $zero, 0x24
  .L80133C9C:
  /* 18139C 80133C9C 10000021 */         b .L80133D24
  /* 1813A0 80133CA0 461CA501 */     sub.s $f20, $f20, $f28
  /* 1813A4 80133CA4 24010024 */     addiu $at, $zero, 0x24
  .L80133CA8:
  /* 1813A8 80133CA8 10610005 */       beq $v1, $at, .L80133CC0
  /* 1813AC 80133CAC 2401002B */     addiu $at, $zero, 0x2b
  /* 1813B0 80133CB0 50610004 */      beql $v1, $at, .L80133CC4
  /* 1813B4 80133CB4 8E220000 */        lw $v0, ($s1)
  /* 1813B8 80133CB8 16C3000A */       bne $s6, $v1, .L80133CE4
  /* 1813BC 80133CBC 00000000 */       nop 
  .L80133CC0:
  /* 1813C0 80133CC0 8E220000 */        lw $v0, ($s1)
  .L80133CC4:
  /* 1813C4 80133CC4 12E20005 */       beq $s7, $v0, .L80133CDC
  /* 1813C8 80133CC8 00000000 */       nop 
  /* 1813CC 80133CCC 13C20003 */       beq $fp, $v0, .L80133CDC
  /* 1813D0 80133CD0 00000000 */       nop 
  /* 1813D4 80133CD4 16A20003 */       bne $s5, $v0, .L80133CE4
  /* 1813D8 80133CD8 00000000 */       nop 
  .L80133CDC:
  /* 1813DC 80133CDC 10000011 */         b .L80133D24
  /* 1813E0 80133CE0 461CA501 */     sub.s $f20, $f20, $f28
  .L80133CE4:
  /* 1813E4 80133CE4 56A30008 */      bnel $s5, $v1, .L80133D08
  /* 1813E8 80133CE8 24010012 */     addiu $at, $zero, 0x12
  /* 1813EC 80133CEC 8E2E0000 */        lw $t6, ($s1)
  /* 1813F0 80133CF0 2401002C */     addiu $at, $zero, 0x2c
  /* 1813F4 80133CF4 55C10004 */      bnel $t6, $at, .L80133D08
  /* 1813F8 80133CF8 24010012 */     addiu $at, $zero, 0x12
  /* 1813FC 80133CFC 10000009 */         b .L80133D24
  /* 181400 80133D00 461EA501 */     sub.s $f20, $f20, $f30
  /* 181404 80133D04 24010012 */     addiu $at, $zero, 0x12
  .L80133D08:
  /* 181408 80133D08 54610007 */      bnel $v1, $at, .L80133D28
  /* 18140C 80133D0C 4616A000 */     add.s $f0, $f20, $f22
  /* 181410 80133D10 8E2F0000 */        lw $t7, ($s1)
  /* 181414 80133D14 2401002E */     addiu $at, $zero, 0x2e
  /* 181418 80133D18 55E10003 */      bnel $t7, $at, .L80133D28
  /* 18141C 80133D1C 4616A000 */     add.s $f0, $f20, $f22
  /* 181420 80133D20 461EA501 */     sub.s $f20, $f20, $f30
  .L80133D24:
  /* 181424 80133D24 4616A000 */     add.s $f0, $f20, $f22
  .L80133D28:
  /* 181428 80133D28 E6520020 */      swc1 $f18, 0x20($s2)
  /* 18142C 80133D2C 24010033 */     addiu $at, $zero, 0x33
  /* 181430 80133D30 E640001C */      swc1 $f0, 0x1c($s2)
  /* 181434 80133D34 8E220000 */        lw $v0, ($s1)
  /* 181438 80133D38 46160500 */     add.s $f20, $f0, $f22
  /* 18143C 80133D3C 14410006 */       bne $v0, $at, .L80133D58
  /* 181440 80133D40 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 181444 80133D44 44813000 */      mtc1 $at, $f6 # 1.0 to cop1
  /* 181448 80133D48 C6440020 */      lwc1 $f4, 0x20($s2)
  /* 18144C 80133D4C 46062200 */     add.s $f8, $f4, $f6
  /* 181450 80133D50 E6480020 */      swc1 $f8, 0x20($s2)
  /* 181454 80133D54 8E220000 */        lw $v0, ($s1)
  .L80133D58:
  /* 181458 80133D58 24010023 */     addiu $at, $zero, 0x23
  /* 18145C 80133D5C 54410005 */      bnel $v0, $at, .L80133D74
  /* 181460 80133D60 24010036 */     addiu $at, $zero, 0x36
  /* 181464 80133D64 4618D281 */     sub.s $f10, $f26, $f24
  /* 181468 80133D68 E64A0020 */      swc1 $f10, 0x20($s2)
  /* 18146C 80133D6C 8E220000 */        lw $v0, ($s1)
  /* 181470 80133D70 24010036 */     addiu $at, $zero, 0x36
  .L80133D74:
  /* 181474 80133D74 54410006 */      bnel $v0, $at, .L80133D90
  /* 181478 80133D78 24010020 */     addiu $at, $zero, 0x20
  /* 18147C 80133D7C C6500020 */      lwc1 $f16, 0x20($s2)
  /* 181480 80133D80 461A8480 */     add.s $f18, $f16, $f26
  /* 181484 80133D84 E6520020 */      swc1 $f18, 0x20($s2)
  /* 181488 80133D88 8E220000 */        lw $v0, ($s1)
  /* 18148C 80133D8C 24010020 */     addiu $at, $zero, 0x20
  .L80133D90:
  /* 181490 80133D90 10410006 */       beq $v0, $at, .L80133DAC
  /* 181494 80133D94 24010029 */     addiu $at, $zero, 0x29
  /* 181498 80133D98 10410004 */       beq $v0, $at, .L80133DAC
  /* 18149C 80133D9C 2401002A */     addiu $at, $zero, 0x2a
  /* 1814A0 80133DA0 50410003 */      beql $v0, $at, .L80133DB0
  /* 1814A4 80133DA4 3C01C100 */       lui $at, 0xc100
  /* 1814A8 80133DA8 16C20004 */       bne $s6, $v0, .L80133DBC
  .L80133DAC:
  /* 1814AC 80133DAC 3C01C100 */       lui $at, (0xC1000000 >> 16) # -8.0
  .L80133DB0:
  /* 1814B0 80133DB0 44812000 */      mtc1 $at, $f4 # -8.0 to cop1
  /* 1814B4 80133DB4 00000000 */       nop 
  /* 1814B8 80133DB8 E6440020 */      swc1 $f4, 0x20($s2)
  .L80133DBC:
  /* 1814BC 80133DBC 8FB8007C */        lw $t8, 0x7c($sp)
  /* 1814C0 80133DC0 8F030004 */        lw $v1, 4($t8)
  .L80133DC4:
  /* 1814C4 80133DC4 26940001 */     addiu $s4, $s4, 1
  /* 1814C8 80133DC8 0283082A */       slt $at, $s4, $v1
  /* 1814CC 80133DCC 02608025 */        or $s0, $s3, $zero
  /* 1814D0 80133DD0 26730001 */     addiu $s3, $s3, 1
  /* 1814D4 80133DD4 1420FF55 */      bnez $at, .L80133B2C
  /* 1814D8 80133DD8 26310004 */     addiu $s1, $s1, 4
  /* 1814DC 80133DDC AFB20098 */        sw $s2, 0x98($sp)
  .L80133DE0:
  /* 1814E0 80133DE0 8FB20098 */        lw $s2, 0x98($sp)
  /* 1814E4 80133DE4 E7B400A4 */      swc1 $f20, 0xa4($sp)
  /* 1814E8 80133DE8 27A8009C */     addiu $t0, $sp, 0x9c
  /* 1814EC 80133DEC AFB200A0 */        sw $s2, 0xa0($sp)
  /* 1814F0 80133DF0 8D0A0000 */        lw $t2, ($t0)
  /* 1814F4 80133DF4 8FB900B0 */        lw $t9, 0xb0($sp)
  /* 1814F8 80133DF8 AF2A0000 */        sw $t2, ($t9)
  /* 1814FC 80133DFC 8D090004 */        lw $t1, 4($t0)
  /* 181500 80133E00 AF290004 */        sw $t1, 4($t9)
  /* 181504 80133E04 8D0A0008 */        lw $t2, 8($t0)
  /* 181508 80133E08 AF2A0008 */        sw $t2, 8($t9)
  /* 18150C 80133E0C 8D09000C */        lw $t1, 0xc($t0)
  /* 181510 80133E10 AF29000C */        sw $t1, 0xc($t9)
  /* 181514 80133E14 8D0A0010 */        lw $t2, 0x10($t0)
  /* 181518 80133E18 AF2A0010 */        sw $t2, 0x10($t9)
  /* 18151C 80133E1C 8FBF006C */        lw $ra, 0x6c($sp)
  /* 181520 80133E20 8FBE0068 */        lw $fp, 0x68($sp)
  /* 181524 80133E24 8FB70064 */        lw $s7, 0x64($sp)
  /* 181528 80133E28 8FB60060 */        lw $s6, 0x60($sp)
  /* 18152C 80133E2C 8FB5005C */        lw $s5, 0x5c($sp)
  /* 181530 80133E30 8FB40058 */        lw $s4, 0x58($sp)
  /* 181534 80133E34 8FB30054 */        lw $s3, 0x54($sp)
  /* 181538 80133E38 8FB20050 */        lw $s2, 0x50($sp)
  /* 18153C 80133E3C 8FB1004C */        lw $s1, 0x4c($sp)
  /* 181540 80133E40 8FB00048 */        lw $s0, 0x48($sp)
  /* 181544 80133E44 D7BE0040 */      ldc1 $f30, 0x40($sp)
  /* 181548 80133E48 D7BC0038 */      ldc1 $f28, 0x38($sp)
  /* 18154C 80133E4C D7BA0030 */      ldc1 $f26, 0x30($sp)
  /* 181550 80133E50 D7B80028 */      ldc1 $f24, 0x28($sp)
  /* 181554 80133E54 D7B60020 */      ldc1 $f22, 0x20($sp)
  /* 181558 80133E58 D7B40018 */      ldc1 $f20, 0x18($sp)
  /* 18155C 80133E5C 8FA200B0 */        lw $v0, 0xb0($sp)
  /* 181560 80133E60 03E00008 */        jr $ra
  /* 181564 80133E64 27BD00B0 */     addiu $sp, $sp, 0xb0

glabel gmCreditsMakeJobGObj
  /* 181568 80133E68 27BDFFB0 */     addiu $sp, $sp, -0x50
  /* 18156C 80133E6C 44802000 */      mtc1 $zero, $f4
  /* 181570 80133E70 AFBF0024 */        sw $ra, 0x24($sp)
  /* 181574 80133E74 AFA40050 */        sw $a0, 0x50($sp)
  /* 181578 80133E78 AFB00020 */        sw $s0, 0x20($sp)
  /* 18157C 80133E7C 24040001 */     addiu $a0, $zero, 1
  /* 181580 80133E80 00002825 */        or $a1, $zero, $zero
  /* 181584 80133E84 24060004 */     addiu $a2, $zero, 4
  /* 181588 80133E88 3C078000 */       lui $a3, 0x8000
  /* 18158C 80133E8C 0C00265A */       jal omMakeGObjCommon
  /* 181590 80133E90 E7A4002C */      swc1 $f4, 0x2c($sp)
  /* 181594 80133E94 3C058013 */       lui $a1, %hi(gmCreditsJobProcRender)
  /* 181598 80133E98 240EFFFF */     addiu $t6, $zero, -1
  /* 18159C 80133E9C 00408025 */        or $s0, $v0, $zero
  /* 1815A0 80133EA0 AFAE0010 */        sw $t6, 0x10($sp)
  /* 1815A4 80133EA4 24A53854 */     addiu $a1, $a1, %lo(gmCreditsJobProcRender)
  /* 1815A8 80133EA8 00402025 */        or $a0, $v0, $zero
  /* 1815AC 80133EAC 24060002 */     addiu $a2, $zero, 2
  /* 1815B0 80133EB0 0C00277D */       jal omAddGObjRenderProc
  /* 1815B4 80133EB4 3C078000 */       lui $a3, 0x8000
  /* 1815B8 80133EB8 02002025 */        or $a0, $s0, $zero
  /* 1815BC 80133EBC 0C0024B4 */       jal func_800092D0
  /* 1815C0 80133EC0 00002825 */        or $a1, $zero, $zero
  /* 1815C4 80133EC4 AFA20030 */        sw $v0, 0x30($sp)
  /* 1815C8 80133EC8 00402025 */        or $a0, $v0, $zero
  /* 1815CC 80133ECC 2405001C */     addiu $a1, $zero, 0x1c
  /* 1815D0 80133ED0 0C002330 */       jal func_80008CC0
  /* 1815D4 80133ED4 00003025 */        or $a2, $zero, $zero
  /* 1815D8 80133ED8 8FAF0050 */        lw $t7, 0x50($sp)
  /* 1815DC 80133EDC 2401FFFF */     addiu $at, $zero, -1
  /* 1815E0 80133EE0 27A4003C */     addiu $a0, $sp, 0x3c
  /* 1815E4 80133EE4 8DE60000 */        lw $a2, ($t7)
  /* 1815E8 80133EE8 8FA50030 */        lw $a1, 0x30($sp)
  /* 1815EC 80133EEC 50C10009 */      beql $a2, $at, .L80133F14
  /* 1815F0 80133EF0 8FB80050 */        lw $t8, 0x50($sp)
  /* 1815F4 80133EF4 0C04CE9E */       jal gmCreditsMakeJobDObjs
  /* 1815F8 80133EF8 24070000 */     addiu $a3, $zero, 0
  /* 1815FC 80133EFC 3C014180 */       lui $at, (0x41800000 >> 16) # 16.0
  /* 181600 80133F00 44813000 */      mtc1 $at, $f6 # 16.0 to cop1
  /* 181604 80133F04 C7A80044 */      lwc1 $f8, 0x44($sp)
  /* 181608 80133F08 46083280 */     add.s $f10, $f6, $f8
  /* 18160C 80133F0C E7AA002C */      swc1 $f10, 0x2c($sp)
  /* 181610 80133F10 8FB80050 */        lw $t8, 0x50($sp)
  .L80133F14:
  /* 181614 80133F14 27A4003C */     addiu $a0, $sp, 0x3c
  /* 181618 80133F18 8FA50030 */        lw $a1, 0x30($sp)
  /* 18161C 80133F1C 8FA7002C */        lw $a3, 0x2c($sp)
  /* 181620 80133F20 0C04CE9E */       jal gmCreditsMakeJobDObjs
  /* 181624 80133F24 8F060004 */        lw $a2, 4($t8)
  /* 181628 80133F28 02002025 */        or $a0, $s0, $zero
  /* 18162C 80133F2C 8FA50030 */        lw $a1, 0x30($sp)
  /* 181630 80133F30 8FA60040 */        lw $a2, 0x40($sp)
  /* 181634 80133F34 0C04CE83 */       jal gmCreditsJobAndNameInitStruct
  /* 181638 80133F38 00003825 */        or $a3, $zero, $zero
  /* 18163C 80133F3C 3C058013 */       lui $a1, %hi(gmCreditsJobAndNameProcUpdate)
  /* 181640 80133F40 24A5369C */     addiu $a1, $a1, %lo(gmCreditsJobAndNameProcUpdate)
  /* 181644 80133F44 02002025 */        or $a0, $s0, $zero
  /* 181648 80133F48 00003025 */        or $a2, $zero, $zero
  /* 18164C 80133F4C 0C002062 */       jal omAddGObjCommonProc
  /* 181650 80133F50 24070001 */     addiu $a3, $zero, 1
  /* 181654 80133F54 8FBF0024 */        lw $ra, 0x24($sp)
  /* 181658 80133F58 02001025 */        or $v0, $s0, $zero
  /* 18165C 80133F5C 8FB00020 */        lw $s0, 0x20($sp)
  /* 181660 80133F60 03E00008 */        jr $ra
  /* 181664 80133F64 27BD0050 */     addiu $sp, $sp, 0x50

glabel gmCreditsMakeNameGObjAndDObjs
  /* 181668 80133F68 27BDFF78 */     addiu $sp, $sp, -0x88
  /* 18166C 80133F6C AFB10054 */        sw $s1, 0x54($sp)
  /* 181670 80133F70 3C118000 */       lui $s1, %hi(D_NF_80000004)
  /* 181674 80133F74 AFBF0074 */        sw $ra, 0x74($sp)
  /* 181678 80133F78 AFB00050 */        sw $s0, 0x50($sp)
  /* 18167C 80133F7C AFBE0070 */        sw $fp, 0x70($sp)
  /* 181680 80133F80 AFB7006C */        sw $s7, 0x6c($sp)
  /* 181684 80133F84 AFB60068 */        sw $s6, 0x68($sp)
  /* 181688 80133F88 AFB50064 */        sw $s5, 0x64($sp)
  /* 18168C 80133F8C AFB40060 */        sw $s4, 0x60($sp)
  /* 181690 80133F90 AFB3005C */        sw $s3, 0x5c($sp)
  /* 181694 80133F94 AFB20058 */        sw $s2, 0x58($sp)
  /* 181698 80133F98 F7BE0048 */      sdc1 $f30, 0x48($sp)
  /* 18169C 80133F9C F7BC0040 */      sdc1 $f28, 0x40($sp)
  /* 1816A0 80133FA0 F7BA0038 */      sdc1 $f26, 0x38($sp)
  /* 1816A4 80133FA4 F7B80030 */      sdc1 $f24, 0x30($sp)
  /* 1816A8 80133FA8 F7B60028 */      sdc1 $f22, 0x28($sp)
  /* 1816AC 80133FAC F7B40020 */      sdc1 $f20, 0x20($sp)
  /* 1816B0 80133FB0 2410FFFF */     addiu $s0, $zero, -1
  /* 1816B4 80133FB4 02203825 */        or $a3, $s1, $zero
  /* 1816B8 80133FB8 24040001 */     addiu $a0, $zero, 1
  /* 1816BC 80133FBC 00002825 */        or $a1, $zero, $zero
  /* 1816C0 80133FC0 0C00265A */       jal omMakeGObjCommon
  /* 1816C4 80133FC4 24060003 */     addiu $a2, $zero, 3
  /* 1816C8 80133FC8 3C058013 */       lui $a1, %hi(gmCreditsNameProcRender)
  /* 1816CC 80133FCC 240EFFFF */     addiu $t6, $zero, -1
  /* 1816D0 80133FD0 AFA20080 */        sw $v0, 0x80($sp)
  /* 1816D4 80133FD4 AFAE0010 */        sw $t6, 0x10($sp)
  /* 1816D8 80133FD8 24A53930 */     addiu $a1, $a1, %lo(gmCreditsNameProcRender)
  /* 1816DC 80133FDC 00402025 */        or $a0, $v0, $zero
  /* 1816E0 80133FE0 24060001 */     addiu $a2, $zero, 1
  /* 1816E4 80133FE4 0C00277D */       jal omAddGObjRenderProc
  /* 1816E8 80133FE8 02203825 */        or $a3, $s1, $zero
  /* 1816EC 80133FEC 8FA40080 */        lw $a0, 0x80($sp)
  /* 1816F0 80133FF0 0C0024B4 */       jal func_800092D0
  /* 1816F4 80133FF4 00002825 */        or $a1, $zero, $zero
  /* 1816F8 80133FF8 AFA20078 */        sw $v0, 0x78($sp)
  /* 1816FC 80133FFC 00409025 */        or $s2, $v0, $zero
  /* 181700 80134000 00402025 */        or $a0, $v0, $zero
  /* 181704 80134004 2405001C */     addiu $a1, $zero, 0x1c
  /* 181708 80134008 0C002330 */       jal func_80008CC0
  /* 18170C 8013400C 00003025 */        or $a2, $zero, $zero
  /* 181710 80134010 3C0F8014 */       lui $t7, %hi(gCreditsNameID)
  /* 181714 80134014 8DEFA8B8 */        lw $t7, %lo(gCreditsNameID)($t7)
  /* 181718 80134018 3C198013 */       lui $t9, %hi(dCreditsNameTextInfo)
  /* 18171C 8013401C 273964F4 */     addiu $t9, $t9, %lo(dCreditsNameTextInfo)
  /* 181720 80134020 000FC0C0 */       sll $t8, $t7, 3
  /* 181724 80134024 03192021 */      addu $a0, $t8, $t9
  /* 181728 80134028 8C830004 */        lw $v1, 4($a0)
  /* 18172C 8013402C 4480A000 */      mtc1 $zero, $f20
  /* 181730 80134030 8C930000 */        lw $s3, ($a0)
  /* 181734 80134034 186000BF */      blez $v1, .L80134334
  /* 181738 80134038 0000A025 */        or $s4, $zero, $zero
  /* 18173C 8013403C 3C0141B0 */       lui $at, (0x41B00000 >> 16) # 22.0
  /* 181740 80134040 4481F000 */      mtc1 $at, $f30 # 22.0 to cop1
  /* 181744 80134044 3C0140C0 */       lui $at, (0x40C00000 >> 16) # 6.0
  /* 181748 80134048 4481E000 */      mtc1 $at, $f28 # 6.0 to cop1
  /* 18174C 8013404C 3C014080 */       lui $at, (0x40800000 >> 16) # 4.0
  /* 181750 80134050 3C098013 */       lui $t1, %hi(dCreditsNameCharacters)
  /* 181754 80134054 25295260 */     addiu $t1, $t1, %lo(dCreditsNameCharacters)
  /* 181758 80134058 00134080 */       sll $t0, $s3, 2
  /* 18175C 8013405C 4481D000 */      mtc1 $at, $f26 # 4.0 to cop1
  /* 181760 80134060 01098821 */      addu $s1, $t0, $t1
  /* 181764 80134064 241E001E */     addiu $fp, $zero, 0x1e
  /* 181768 80134068 2417001A */     addiu $s7, $zero, 0x1a
  /* 18176C 8013406C 24160032 */     addiu $s6, $zero, 0x32
  /* 181770 80134070 24150028 */     addiu $s5, $zero, 0x28
  .L80134074:
  /* 181774 80134074 8E220000 */        lw $v0, %lo(D_NF_80000000)($s1)
  /* 181778 80134078 2401FFDF */     addiu $at, $zero, -0x21
  /* 18177C 8013407C 3C0C8014 */       lui $t4, %hi(dCreditsNameAndJobSpriteInfo)
  /* 181780 80134080 14410005 */       bne $v0, $at, .L80134098
  /* 181784 80134084 00025080 */       sll $t2, $v0, 2
  /* 181788 80134088 3C014180 */       lui $at, (0x41800000 >> 16) # 16.0
  /* 18178C 8013408C 44812000 */      mtc1 $at, $f4 # 16.0 to cop1
  /* 181790 80134090 100000A2 */         b .L8013431C
  /* 181794 80134094 4604A500 */     add.s $f20, $f20, $f4
  .L80134098:
  /* 181798 80134098 000258C0 */       sll $t3, $v0, 3
  /* 18179C 8013409C 258CA188 */     addiu $t4, $t4, %lo(dCreditsNameAndJobSpriteInfo)
  /* 1817A0 801340A0 016C1821 */      addu $v1, $t3, $t4
  /* 1817A4 801340A4 906D0000 */       lbu $t5, ($v1)
  /* 1817A8 801340A8 3C058014 */       lui $a1, %hi(gCreditsNameAndJobDisplayLists)
  /* 1817AC 801340AC 00AA2821 */      addu $a1, $a1, $t2
  /* 1817B0 801340B0 448D3000 */      mtc1 $t5, $f6
  /* 1817B4 801340B4 8CA5A7D8 */        lw $a1, %lo(gCreditsNameAndJobDisplayLists)($a1)
  /* 1817B8 801340B8 05A10005 */      bgez $t5, .L801340D0
  /* 1817BC 801340BC 468035A0 */   cvt.s.w $f22, $f6
  /* 1817C0 801340C0 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 1817C4 801340C4 44814000 */      mtc1 $at, $f8 # 4294967300.0 to cop1
  /* 1817C8 801340C8 00000000 */       nop 
  /* 1817CC 801340CC 4608B580 */     add.s $f22, $f22, $f8
  .L801340D0:
  /* 1817D0 801340D0 906E0001 */       lbu $t6, 1($v1)
  /* 1817D4 801340D4 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 1817D8 801340D8 448E5000 */      mtc1 $t6, $f10
  /* 1817DC 801340DC 05C10004 */      bgez $t6, .L801340F0
  /* 1817E0 801340E0 46805620 */   cvt.s.w $f24, $f10
  /* 1817E4 801340E4 44818000 */      mtc1 $at, $f16 # 4294967300.0 to cop1
  /* 1817E8 801340E8 00000000 */       nop 
  /* 1817EC 801340EC 4610C600 */     add.s $f24, $f24, $f16
  .L801340F0:
  /* 1817F0 801340F0 0C0024FD */       jal func_800093F4
  /* 1817F4 801340F4 8FA40078 */        lw $a0, 0x78($sp)
  /* 1817F8 801340F8 00409025 */        or $s2, $v0, $zero
  /* 1817FC 801340FC 00402025 */        or $a0, $v0, $zero
  /* 181800 80134100 24050012 */     addiu $a1, $zero, 0x12
  /* 181804 80134104 0C002330 */       jal func_80008CC0
  /* 181808 80134108 24060001 */     addiu $a2, $zero, 1
  /* 18180C 8013410C 2401FFFF */     addiu $at, $zero, -1
  /* 181810 80134110 12010056 */       beq $s0, $at, .L8013426C
  /* 181814 80134114 461EC481 */     sub.s $f18, $f24, $f30
  /* 181818 80134118 00107880 */       sll $t7, $s0, 2
  /* 18181C 8013411C 3C038013 */       lui $v1, %hi(dCreditsNameCharacters)
  /* 181820 80134120 006F1821 */      addu $v1, $v1, $t7
  /* 181824 80134124 8C635260 */        lw $v1, %lo(dCreditsNameCharacters)($v1)
  /* 181828 80134128 2401000A */     addiu $at, $zero, 0xa
  /* 18182C 8013412C 10610009 */       beq $v1, $at, .L80134154
  /* 181830 80134130 24010013 */     addiu $at, $zero, 0x13
  /* 181834 80134134 10610007 */       beq $v1, $at, .L80134154
  /* 181838 80134138 24010015 */     addiu $at, $zero, 0x15
  /* 18183C 8013413C 10610005 */       beq $v1, $at, .L80134154
  /* 181840 80134140 24010016 */     addiu $at, $zero, 0x16
  /* 181844 80134144 10610003 */       beq $v1, $at, .L80134154
  /* 181848 80134148 24010018 */     addiu $at, $zero, 0x18
  /* 18184C 8013414C 54610028 */      bnel $v1, $at, .L801341F0
  /* 181850 80134150 24010024 */     addiu $at, $zero, 0x24
  .L80134154:
  /* 181854 80134154 8E220000 */        lw $v0, %lo(D_NF_80000000)($s1)
  /* 181858 80134158 2401001C */     addiu $at, $zero, 0x1c
  /* 18185C 8013415C 12E20021 */       beq $s7, $v0, .L801341E4
  /* 181860 80134160 00000000 */       nop 
  /* 181864 80134164 1041001F */       beq $v0, $at, .L801341E4
  /* 181868 80134168 00000000 */       nop 
  /* 18186C 8013416C 13C2001D */       beq $fp, $v0, .L801341E4
  /* 181870 80134170 24010020 */     addiu $at, $zero, 0x20
  /* 181874 80134174 1041001B */       beq $v0, $at, .L801341E4
  /* 181878 80134178 24010026 */     addiu $at, $zero, 0x26
  /* 18187C 8013417C 10410019 */       beq $v0, $at, .L801341E4
  /* 181880 80134180 24010027 */     addiu $at, $zero, 0x27
  /* 181884 80134184 10410017 */       beq $v0, $at, .L801341E4
  /* 181888 80134188 00000000 */       nop 
  /* 18188C 8013418C 12A20015 */       beq $s5, $v0, .L801341E4
  /* 181890 80134190 24010029 */     addiu $at, $zero, 0x29
  /* 181894 80134194 10410013 */       beq $v0, $at, .L801341E4
  /* 181898 80134198 2401002A */     addiu $at, $zero, 0x2a
  /* 18189C 8013419C 10410011 */       beq $v0, $at, .L801341E4
  /* 1818A0 801341A0 2401002B */     addiu $at, $zero, 0x2b
  /* 1818A4 801341A4 1041000F */       beq $v0, $at, .L801341E4
  /* 1818A8 801341A8 2401002C */     addiu $at, $zero, 0x2c
  /* 1818AC 801341AC 1041000D */       beq $v0, $at, .L801341E4
  /* 1818B0 801341B0 2401002E */     addiu $at, $zero, 0x2e
  /* 1818B4 801341B4 1041000B */       beq $v0, $at, .L801341E4
  /* 1818B8 801341B8 2401002F */     addiu $at, $zero, 0x2f
  /* 1818BC 801341BC 10410009 */       beq $v0, $at, .L801341E4
  /* 1818C0 801341C0 24010030 */     addiu $at, $zero, 0x30
  /* 1818C4 801341C4 10410007 */       beq $v0, $at, .L801341E4
  /* 1818C8 801341C8 24010031 */     addiu $at, $zero, 0x31
  /* 1818CC 801341CC 10410005 */       beq $v0, $at, .L801341E4
  /* 1818D0 801341D0 00000000 */       nop 
  /* 1818D4 801341D4 12C20003 */       beq $s6, $v0, .L801341E4
  /* 1818D8 801341D8 24010033 */     addiu $at, $zero, 0x33
  /* 1818DC 801341DC 54410004 */      bnel $v0, $at, .L801341F0
  /* 1818E0 801341E0 24010024 */     addiu $at, $zero, 0x24
  .L801341E4:
  /* 1818E4 801341E4 10000021 */         b .L8013426C
  /* 1818E8 801341E8 461CA501 */     sub.s $f20, $f20, $f28
  /* 1818EC 801341EC 24010024 */     addiu $at, $zero, 0x24
  .L801341F0:
  /* 1818F0 801341F0 10610005 */       beq $v1, $at, .L80134208
  /* 1818F4 801341F4 2401002B */     addiu $at, $zero, 0x2b
  /* 1818F8 801341F8 50610004 */      beql $v1, $at, .L8013420C
  /* 1818FC 801341FC 8E220000 */        lw $v0, %lo(D_NF_80000000)($s1)
  /* 181900 80134200 16C3000A */       bne $s6, $v1, .L8013422C
  /* 181904 80134204 00000000 */       nop 
  .L80134208:
  /* 181908 80134208 8E220000 */        lw $v0, %lo(D_NF_80000000)($s1)
  .L8013420C:
  /* 18190C 8013420C 12E20005 */       beq $s7, $v0, .L80134224
  /* 181910 80134210 00000000 */       nop 
  /* 181914 80134214 13C20003 */       beq $fp, $v0, .L80134224
  /* 181918 80134218 00000000 */       nop 
  /* 18191C 8013421C 16A20003 */       bne $s5, $v0, .L8013422C
  /* 181920 80134220 00000000 */       nop 
  .L80134224:
  /* 181924 80134224 10000011 */         b .L8013426C
  /* 181928 80134228 461CA501 */     sub.s $f20, $f20, $f28
  .L8013422C:
  /* 18192C 8013422C 56A30008 */      bnel $s5, $v1, .L80134250
  /* 181930 80134230 24010012 */     addiu $at, $zero, 0x12
  /* 181934 80134234 8E380000 */        lw $t8, %lo(D_NF_80000000)($s1)
  /* 181938 80134238 2401002C */     addiu $at, $zero, 0x2c
  /* 18193C 8013423C 57010004 */      bnel $t8, $at, .L80134250
  /* 181940 80134240 24010012 */     addiu $at, $zero, 0x12
  /* 181944 80134244 10000009 */         b .L8013426C
  /* 181948 80134248 461AA501 */     sub.s $f20, $f20, $f26
  /* 18194C 8013424C 24010012 */     addiu $at, $zero, 0x12
  .L80134250:
  /* 181950 80134250 54610007 */      bnel $v1, $at, .L80134270
  /* 181954 80134254 4616A000 */     add.s $f0, $f20, $f22
  /* 181958 80134258 8E390000 */        lw $t9, %lo(D_NF_80000000)($s1)
  /* 18195C 8013425C 2401002E */     addiu $at, $zero, 0x2e
  /* 181960 80134260 57210003 */      bnel $t9, $at, .L80134270
  /* 181964 80134264 4616A000 */     add.s $f0, $f20, $f22
  /* 181968 80134268 461AA501 */     sub.s $f20, $f20, $f26
  .L8013426C:
  /* 18196C 8013426C 4616A000 */     add.s $f0, $f20, $f22
  .L80134270:
  /* 181970 80134270 E6520020 */      swc1 $f18, 0x20($s2)
  /* 181974 80134274 24010033 */     addiu $at, $zero, 0x33
  /* 181978 80134278 3C088014 */       lui $t0, %hi(gCreditsNameID)
  /* 18197C 8013427C E640001C */      swc1 $f0, 0x1c($s2)
  /* 181980 80134280 8E220000 */        lw $v0, %lo(D_NF_80000000)($s1)
  /* 181984 80134284 46160500 */     add.s $f20, $f0, $f22
  /* 181988 80134288 14410006 */       bne $v0, $at, .L801342A4
  /* 18198C 8013428C 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 181990 80134290 44813000 */      mtc1 $at, $f6 # 1.0 to cop1
  /* 181994 80134294 C6440020 */      lwc1 $f4, 0x20($s2)
  /* 181998 80134298 46062200 */     add.s $f8, $f4, $f6
  /* 18199C 8013429C E6480020 */      swc1 $f8, 0x20($s2)
  /* 1819A0 801342A0 8E220000 */        lw $v0, %lo(D_NF_80000000)($s1)
  .L801342A4:
  /* 1819A4 801342A4 24010023 */     addiu $at, $zero, 0x23
  /* 1819A8 801342A8 54410005 */      bnel $v0, $at, .L801342C0
  /* 1819AC 801342AC 24010020 */     addiu $at, $zero, 0x20
  /* 1819B0 801342B0 4618F281 */     sub.s $f10, $f30, $f24
  /* 1819B4 801342B4 E64A0020 */      swc1 $f10, 0x20($s2)
  /* 1819B8 801342B8 8E220000 */        lw $v0, %lo(D_NF_80000000)($s1)
  /* 1819BC 801342BC 24010020 */     addiu $at, $zero, 0x20
  .L801342C0:
  /* 1819C0 801342C0 10410006 */       beq $v0, $at, .L801342DC
  /* 1819C4 801342C4 24010029 */     addiu $at, $zero, 0x29
  /* 1819C8 801342C8 10410004 */       beq $v0, $at, .L801342DC
  /* 1819CC 801342CC 2401002A */     addiu $at, $zero, 0x2a
  /* 1819D0 801342D0 50410003 */      beql $v0, $at, .L801342E0
  /* 1819D4 801342D4 3C01C100 */       lui $at, 0xc100
  /* 1819D8 801342D8 16C20005 */       bne $s6, $v0, .L801342F0
  .L801342DC:
  /* 1819DC 801342DC 3C01C100 */       lui $at, (0xC1000000 >> 16) # -8.0
  .L801342E0:
  /* 1819E0 801342E0 44818000 */      mtc1 $at, $f16 # -8.0 to cop1
  /* 1819E4 801342E4 00000000 */       nop 
  /* 1819E8 801342E8 E6500020 */      swc1 $f16, 0x20($s2)
  /* 1819EC 801342EC 8E220000 */        lw $v0, %lo(D_NF_80000000)($s1)
  .L801342F0:
  /* 1819F0 801342F0 24010035 */     addiu $at, $zero, 0x35
  /* 1819F4 801342F4 14410004 */       bne $v0, $at, .L80134308
  /* 1819F8 801342F8 00000000 */       nop 
  /* 1819FC 801342FC C6520020 */      lwc1 $f18, 0x20($s2)
  /* 181A00 80134300 461A9101 */     sub.s $f4, $f18, $f26
  /* 181A04 80134304 E6440020 */      swc1 $f4, 0x20($s2)
  .L80134308:
  /* 181A08 80134308 8D08A8B8 */        lw $t0, %lo(gCreditsNameID)($t0)
  /* 181A0C 8013430C 3C038013 */       lui $v1, %hi(D_ovl59_801364F8)
  /* 181A10 80134310 000848C0 */       sll $t1, $t0, 3
  /* 181A14 80134314 00691821 */      addu $v1, $v1, $t1
  /* 181A18 80134318 8C6364F8 */        lw $v1, %lo(D_ovl59_801364F8)($v1)
  .L8013431C:
  /* 181A1C 8013431C 26940001 */     addiu $s4, $s4, 1
  /* 181A20 80134320 0283082A */       slt $at, $s4, $v1
  /* 181A24 80134324 02608025 */        or $s0, $s3, $zero
  /* 181A28 80134328 26730001 */     addiu $s3, $s3, 1
  /* 181A2C 8013432C 1420FF51 */      bnez $at, .L80134074
  /* 181A30 80134330 26310004 */     addiu $s1, $s1, %lo(D_NF_80000004)
  .L80134334:
  /* 181A34 80134334 8FA40080 */        lw $a0, 0x80($sp)
  /* 181A38 80134338 8FA50078 */        lw $a1, 0x78($sp)
  /* 181A3C 8013433C 02403025 */        or $a2, $s2, $zero
  /* 181A40 80134340 0C04CE83 */       jal gmCreditsJobAndNameInitStruct
  /* 181A44 80134344 24070001 */     addiu $a3, $zero, 1
  /* 181A48 80134348 3C058013 */       lui $a1, %hi(gmCreditsJobAndNameProcUpdate)
  /* 181A4C 8013434C 24A5369C */     addiu $a1, $a1, %lo(gmCreditsJobAndNameProcUpdate)
  /* 181A50 80134350 8FA40080 */        lw $a0, 0x80($sp)
  /* 181A54 80134354 00003025 */        or $a2, $zero, $zero
  /* 181A58 80134358 0C002062 */       jal omAddGObjCommonProc
  /* 181A5C 8013435C 24070001 */     addiu $a3, $zero, 1
  /* 181A60 80134360 8FBF0074 */        lw $ra, 0x74($sp)
  /* 181A64 80134364 8FA20080 */        lw $v0, 0x80($sp)
  /* 181A68 80134368 D7B40020 */      ldc1 $f20, 0x20($sp)
  /* 181A6C 8013436C D7B60028 */      ldc1 $f22, 0x28($sp)
  /* 181A70 80134370 D7B80030 */      ldc1 $f24, 0x30($sp)
  /* 181A74 80134374 D7BA0038 */      ldc1 $f26, 0x38($sp)
  /* 181A78 80134378 D7BC0040 */      ldc1 $f28, 0x40($sp)
  /* 181A7C 8013437C D7BE0048 */      ldc1 $f30, 0x48($sp)
  /* 181A80 80134380 8FB00050 */        lw $s0, 0x50($sp)
  /* 181A84 80134384 8FB10054 */        lw $s1, 0x54($sp)
  /* 181A88 80134388 8FB20058 */        lw $s2, 0x58($sp)
  /* 181A8C 8013438C 8FB3005C */        lw $s3, 0x5c($sp)
  /* 181A90 80134390 8FB40060 */        lw $s4, 0x60($sp)
  /* 181A94 80134394 8FB50064 */        lw $s5, 0x64($sp)
  /* 181A98 80134398 8FB60068 */        lw $s6, 0x68($sp)
  /* 181A9C 8013439C 8FB7006C */        lw $s7, 0x6c($sp)
  /* 181AA0 801343A0 8FBE0070 */        lw $fp, 0x70($sp)
  /* 181AA4 801343A4 03E00008 */        jr $ra
  /* 181AA8 801343A8 27BD0088 */     addiu $sp, $sp, 0x88

glabel gmCreditsCrosshairProcUpdate
  /* 181AAC 801343AC 27BDFFA0 */     addiu $sp, $sp, -0x60
  /* 181AB0 801343B0 AFBF005C */        sw $ra, 0x5c($sp)
  /* 181AB4 801343B4 AFB50058 */        sw $s5, 0x58($sp)
  /* 181AB8 801343B8 AFB40054 */        sw $s4, 0x54($sp)
  /* 181ABC 801343BC AFB30050 */        sw $s3, 0x50($sp)
  /* 181AC0 801343C0 AFB2004C */        sw $s2, 0x4c($sp)
  /* 181AC4 801343C4 AFB10048 */        sw $s1, 0x48($sp)
  /* 181AC8 801343C8 AFB00044 */        sw $s0, 0x44($sp)
  /* 181ACC 801343CC F7BE0038 */      sdc1 $f30, 0x38($sp)
  /* 181AD0 801343D0 F7BC0030 */      sdc1 $f28, 0x30($sp)
  /* 181AD4 801343D4 F7BA0028 */      sdc1 $f26, 0x28($sp)
  /* 181AD8 801343D8 F7B80020 */      sdc1 $f24, 0x20($sp)
  /* 181ADC 801343DC F7B60018 */      sdc1 $f22, 0x18($sp)
  /* 181AE0 801343E0 F7B40010 */      sdc1 $f20, 0x10($sp)
  /* 181AE4 801343E4 3C018014 */       lui $at, %hi(D_ovl59_8013A7B8)
  /* 181AE8 801343E8 8C900074 */        lw $s0, 0x74($a0)
  /* 181AEC 801343EC C424A7B8 */      lwc1 $f4, %lo(D_ovl59_8013A7B8)($at)
  /* 181AF0 801343F0 4480F000 */      mtc1 $zero, $f30
  /* 181AF4 801343F4 3C014128 */       lui $at, (0x41280000 >> 16) # 10.5
  /* 181AF8 801343F8 4481A000 */      mtc1 $at, $f20 # 10.5 to cop1
  /* 181AFC 801343FC 24110013 */     addiu $s1, $zero, 0x13
  /* 181B00 80134400 E6040058 */      swc1 $f4, 0x58($s0)
  /* 181B04 80134404 E61E005C */      swc1 $f30, 0x5c($s0)
  .L80134408:
  /* 181B08 80134408 C606005C */      lwc1 $f6, 0x5c($s0)
  /* 181B0C 8013440C 24040001 */     addiu $a0, $zero, 1
  /* 181B10 80134410 46143200 */     add.s $f8, $f6, $f20
  /* 181B14 80134414 0C002C7A */       jal stop_current_process
  /* 181B18 80134418 E608005C */      swc1 $f8, 0x5c($s0)
  /* 181B1C 8013441C 02201025 */        or $v0, $s1, $zero
  /* 181B20 80134420 1620FFF9 */      bnez $s1, .L80134408
  /* 181B24 80134424 2631FFFF */     addiu $s1, $s1, -1
  /* 181B28 80134428 240E0001 */     addiu $t6, $zero, 1
  /* 181B2C 8013442C 3C018014 */       lui $at, %hi(gCreditsStatus)
  /* 181B30 80134430 AC2EA8C0 */        sw $t6, %lo(gCreditsStatus)($at)
  /* 181B34 80134434 3C014407 */       lui $at, (0x44070000 >> 16) # 540.0
  /* 181B38 80134438 4481E000 */      mtc1 $at, $f28 # 540.0 to cop1
  /* 181B3C 8013443C 3C0143C8 */       lui $at, (0x43C80000 >> 16) # 400.0
  /* 181B40 80134440 4481D000 */      mtc1 $at, $f26 # 400.0 to cop1
  /* 181B44 80134444 3C014210 */       lui $at, (0x42100000 >> 16) # 36.0
  /* 181B48 80134448 4481C000 */      mtc1 $at, $f24 # 36.0 to cop1
  /* 181B4C 8013444C 3C014200 */       lui $at, (0x42000000 >> 16) # 32.0
  /* 181B50 80134450 4481B000 */      mtc1 $at, $f22 # 32.0 to cop1
  /* 181B54 80134454 3C013E00 */       lui $at, (0x3E000000 >> 16) # 0.125
  /* 181B58 80134458 3C158014 */       lui $s5, %hi(gCreditsCrosshairPositionY)
  /* 181B5C 8013445C 3C148014 */       lui $s4, %hi(gCreditsCrosshairPositionX)
  /* 181B60 80134460 3C128014 */       lui $s2, %hi(gCreditsPlayer)
  /* 181B64 80134464 3C118004 */       lui $s1, %hi(gPlayerControllers)
  /* 181B68 80134468 4481A000 */      mtc1 $at, $f20 # 0.125 to cop1
  /* 181B6C 8013446C 26315228 */     addiu $s1, $s1, %lo(gPlayerControllers)
  /* 181B70 80134470 2652A904 */     addiu $s2, $s2, %lo(gCreditsPlayer)
  /* 181B74 80134474 2694A8D4 */     addiu $s4, $s4, %lo(gCreditsCrosshairPositionX)
  /* 181B78 80134478 26B5A8D8 */     addiu $s5, $s5, %lo(gCreditsCrosshairPositionY)
  /* 181B7C 8013447C 2413000A */     addiu $s3, $zero, 0xa
  /* 181B80 80134480 924F0000 */       lbu $t7, ($s2) # gCreditsPlayer + 0
  .L80134484:
  /* 181B84 80134484 C6020058 */      lwc1 $f2, 0x58($s0)
  /* 181B88 80134488 C60E005C */      lwc1 $f14, 0x5c($s0)
  /* 181B8C 8013448C 01F30019 */     multu $t7, $s3
  /* 181B90 80134490 46001306 */     mov.s $f12, $f2
  /* 181B94 80134494 0000C012 */      mflo $t8
  /* 181B98 80134498 02381021 */      addu $v0, $s1, $t8
  /* 181B9C 8013449C 80430008 */        lb $v1, 8($v0)
  /* 181BA0 801344A0 80440009 */        lb $a0, 9($v0)
  /* 181BA4 801344A4 04610003 */      bgez $v1, .L801344B4
  /* 181BA8 801344A8 00601025 */        or $v0, $v1, $zero
  /* 181BAC 801344AC 10000001 */         b .L801344B4
  /* 181BB0 801344B0 00031023 */      negu $v0, $v1
  .L801344B4:
  /* 181BB4 801344B4 28410011 */      slti $at, $v0, 0x11
  /* 181BB8 801344B8 14200007 */      bnez $at, .L801344D8
  /* 181BBC 801344BC 00801025 */        or $v0, $a0, $zero
  /* 181BC0 801344C0 44835000 */      mtc1 $v1, $f10
  /* 181BC4 801344C4 00000000 */       nop 
  /* 181BC8 801344C8 46805420 */   cvt.s.w $f16, $f10
  /* 181BCC 801344CC 46148002 */     mul.s $f0, $f16, $f20
  /* 181BD0 801344D0 10000003 */         b .L801344E0
  /* 181BD4 801344D4 46001480 */     add.s $f18, $f2, $f0
  .L801344D8:
  /* 181BD8 801344D8 4600F006 */     mov.s $f0, $f30
  /* 181BDC 801344DC 46001480 */     add.s $f18, $f2, $f0
  .L801344E0:
  /* 181BE0 801344E0 04810003 */      bgez $a0, .L801344F0
  /* 181BE4 801344E4 E6120058 */      swc1 $f18, 0x58($s0)
  /* 181BE8 801344E8 10000001 */         b .L801344F0
  /* 181BEC 801344EC 00041023 */      negu $v0, $a0
  .L801344F0:
  /* 181BF0 801344F0 28410011 */      slti $at, $v0, 0x11
  /* 181BF4 801344F4 54200008 */      bnel $at, $zero, .L80134518
  /* 181BF8 801344F8 4600F006 */     mov.s $f0, $f30
  /* 181BFC 801344FC 44842000 */      mtc1 $a0, $f4
  /* 181C00 80134500 00000000 */       nop 
  /* 181C04 80134504 468021A0 */   cvt.s.w $f6, $f4
  /* 181C08 80134508 46143002 */     mul.s $f0, $f6, $f20
  /* 181C0C 8013450C 10000003 */         b .L8013451C
  /* 181C10 80134510 C6020058 */      lwc1 $f2, 0x58($s0)
  /* 181C14 80134514 4600F006 */     mov.s $f0, $f30
  .L80134518:
  /* 181C18 80134518 C6020058 */      lwc1 $f2, 0x58($s0)
  .L8013451C:
  /* 181C1C 8013451C C608005C */      lwc1 $f8, 0x5c($s0)
  /* 181C20 80134520 4616103C */    c.lt.s $f2, $f22
  /* 181C24 80134524 46004281 */     sub.s $f10, $f8, $f0
  /* 181C28 80134528 45000003 */      bc1f .L80134538
  /* 181C2C 8013452C E60A005C */      swc1 $f10, 0x5c($s0)
  /* 181C30 80134530 10000009 */         b .L80134558
  /* 181C34 80134534 E6160058 */      swc1 $f22, 0x58($s0)
  .L80134538:
  /* 181C38 80134538 4602E03C */    c.lt.s $f28, $f2
  /* 181C3C 8013453C 00000000 */       nop 
  /* 181C40 80134540 45020004 */     bc1fl .L80134554
  /* 181C44 80134544 46001006 */     mov.s $f0, $f2
  /* 181C48 80134548 10000002 */         b .L80134554
  /* 181C4C 8013454C 4600E006 */     mov.s $f0, $f28
  /* 181C50 80134550 46001006 */     mov.s $f0, $f2
  .L80134554:
  /* 181C54 80134554 E6000058 */      swc1 $f0, 0x58($s0)
  .L80134558:
  /* 181C58 80134558 C602005C */      lwc1 $f2, 0x5c($s0)
  /* 181C5C 8013455C 4618103C */    c.lt.s $f2, $f24
  /* 181C60 80134560 00000000 */       nop 
  /* 181C64 80134564 45020004 */     bc1fl .L80134578
  /* 181C68 80134568 4602D03C */    c.lt.s $f26, $f2
  /* 181C6C 8013456C 10000009 */         b .L80134594
  /* 181C70 80134570 E618005C */      swc1 $f24, 0x5c($s0)
  /* 181C74 80134574 4602D03C */    c.lt.s $f26, $f2
  .L80134578:
  /* 181C78 80134578 00000000 */       nop 
  /* 181C7C 8013457C 45020004 */     bc1fl .L80134590
  /* 181C80 80134580 46001006 */     mov.s $f0, $f2
  /* 181C84 80134584 10000002 */         b .L80134590
  /* 181C88 80134588 4600D006 */     mov.s $f0, $f26
  /* 181C8C 8013458C 46001006 */     mov.s $f0, $f2
  .L80134590:
  /* 181C90 80134590 E600005C */      swc1 $f0, 0x5c($s0)
  .L80134594:
  /* 181C94 80134594 C6100058 */      lwc1 $f16, 0x58($s0)
  /* 181C98 80134598 24040001 */     addiu $a0, $zero, 1
  /* 181C9C 8013459C 460C8481 */     sub.s $f18, $f16, $f12
  /* 181CA0 801345A0 E6920000 */      swc1 $f18, ($s4) # gCreditsCrosshairPositionX + 0
  /* 181CA4 801345A4 C604005C */      lwc1 $f4, 0x5c($s0)
  /* 181CA8 801345A8 460E2181 */     sub.s $f6, $f4, $f14
  /* 181CAC 801345AC 0C002C7A */       jal stop_current_process
  /* 181CB0 801345B0 E6A60000 */      swc1 $f6, ($s5) # gCreditsCrosshairPositionY + 0
  /* 181CB4 801345B4 1000FFB3 */         b .L80134484
  /* 181CB8 801345B8 924F0000 */       lbu $t7, ($s2) # gCreditsPlayer + 0
  /* 181CBC 801345BC 00000000 */       nop 
  /* 181CC0 801345C0 8FBF005C */        lw $ra, 0x5c($sp)
  /* 181CC4 801345C4 D7B40010 */      ldc1 $f20, 0x10($sp)
  /* 181CC8 801345C8 D7B60018 */      ldc1 $f22, 0x18($sp)
  /* 181CCC 801345CC D7B80020 */      ldc1 $f24, 0x20($sp)
  /* 181CD0 801345D0 D7BA0028 */      ldc1 $f26, 0x28($sp)
  /* 181CD4 801345D4 D7BC0030 */      ldc1 $f28, 0x30($sp)
  /* 181CD8 801345D8 D7BE0038 */      ldc1 $f30, 0x38($sp)
  /* 181CDC 801345DC 8FB00044 */        lw $s0, 0x44($sp)
  /* 181CE0 801345E0 8FB10048 */        lw $s1, 0x48($sp)
  /* 181CE4 801345E4 8FB2004C */        lw $s2, 0x4c($sp)
  /* 181CE8 801345E8 8FB30050 */        lw $s3, 0x50($sp)
  /* 181CEC 801345EC 8FB40054 */        lw $s4, 0x54($sp)
  /* 181CF0 801345F0 8FB50058 */        lw $s5, 0x58($sp)
  /* 181CF4 801345F4 03E00008 */        jr $ra
  /* 181CF8 801345F8 27BD0060 */     addiu $sp, $sp, 0x60

glabel gmCreditsMakeCrosshairGObj
  /* 181CFC 801345FC 27BDFFD8 */     addiu $sp, $sp, -0x28
  /* 181D00 80134600 AFBF001C */        sw $ra, 0x1c($sp)
  /* 181D04 80134604 24040003 */     addiu $a0, $zero, 3
  /* 181D08 80134608 00002825 */        or $a1, $zero, $zero
  /* 181D0C 8013460C 24060006 */     addiu $a2, $zero, 6
  /* 181D10 80134610 0C00265A */       jal omMakeGObjCommon
  /* 181D14 80134614 3C078000 */       lui $a3, 0x8000
  /* 181D18 80134618 3C05800D */       lui $a1, %hi(func_ovl0_800CCF00)
  /* 181D1C 8013461C 240EFFFF */     addiu $t6, $zero, -1
  /* 181D20 80134620 AFA20024 */        sw $v0, 0x24($sp)
  /* 181D24 80134624 AFAE0010 */        sw $t6, 0x10($sp)
  /* 181D28 80134628 24A5CF00 */     addiu $a1, $a1, %lo(func_ovl0_800CCF00)
  /* 181D2C 8013462C 00402025 */        or $a0, $v0, $zero
  /* 181D30 80134630 24060004 */     addiu $a2, $zero, 4
  /* 181D34 80134634 0C00277D */       jal omAddGObjRenderProc
  /* 181D38 80134638 3C078000 */       lui $a3, 0x8000
  /* 181D3C 8013463C 3C058013 */       lui $a1, %hi(gmCreditsCrosshairProcUpdate)
  /* 181D40 80134640 24A543AC */     addiu $a1, $a1, %lo(gmCreditsCrosshairProcUpdate)
  /* 181D44 80134644 8FA40024 */        lw $a0, 0x24($sp)
  /* 181D48 80134648 00003025 */        or $a2, $zero, $zero
  /* 181D4C 8013464C 0C002062 */       jal omAddGObjCommonProc
  /* 181D50 80134650 24070001 */     addiu $a3, $zero, 1
  /* 181D54 80134654 3C0F8014 */       lui $t7, %hi(gCreditsSpriteFile)
  /* 181D58 80134658 8DEFAA10 */        lw $t7, %lo(gCreditsSpriteFile)($t7)
  /* 181D5C 8013465C 3C180000 */       lui $t8, %hi(D_NF_00006D58)
  /* 181D60 80134660 27186D58 */     addiu $t8, $t8, %lo(D_NF_00006D58)
  /* 181D64 80134664 8FA40024 */        lw $a0, 0x24($sp)
  /* 181D68 80134668 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 181D6C 8013466C 01F82821 */      addu $a1, $t7, $t8
  /* 181D70 80134670 8FB90024 */        lw $t9, 0x24($sp)
  /* 181D74 80134674 3C014000 */       lui $at, (0x40000000 >> 16) # 2.0
  /* 181D78 80134678 44810000 */      mtc1 $at, $f0 # 2.0 to cop1
  /* 181D7C 8013467C 3C018014 */       lui $at, %hi(gCreditsCrosshairGObj)
  /* 181D80 80134680 AC39A8CC */        sw $t9, %lo(gCreditsCrosshairGObj)($at)
  /* 181D84 80134684 24080001 */     addiu $t0, $zero, 1
  /* 181D88 80134688 240900FF */     addiu $t1, $zero, 0xff
  /* 181D8C 8013468C A4480024 */        sh $t0, 0x24($v0)
  /* 181D90 80134690 A0490028 */        sb $t1, 0x28($v0)
  /* 181D94 80134694 A0400029 */        sb $zero, 0x29($v0)
  /* 181D98 80134698 A040002A */        sb $zero, 0x2a($v0)
  /* 181D9C 8013469C E4400018 */      swc1 $f0, 0x18($v0)
  /* 181DA0 801346A0 E440001C */      swc1 $f0, 0x1c($v0)
  /* 181DA4 801346A4 8FBF001C */        lw $ra, 0x1c($sp)
  /* 181DA8 801346A8 27BD0028 */     addiu $sp, $sp, 0x28
  /* 181DAC 801346AC 03E00008 */        jr $ra
  /* 181DB0 801346B0 00000000 */       nop 

glabel gmCreditsMakeTextBoxBracketSObjs
  /* 181DB4 801346B4 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 181DB8 801346B8 AFBF001C */        sw $ra, 0x1c($sp)
  /* 181DBC 801346BC 24040003 */     addiu $a0, $zero, 3
  /* 181DC0 801346C0 00002825 */        or $a1, $zero, $zero
  /* 181DC4 801346C4 24060008 */     addiu $a2, $zero, 8
  /* 181DC8 801346C8 0C00265A */       jal omMakeGObjCommon
  /* 181DCC 801346CC 3C078000 */       lui $a3, 0x8000
  /* 181DD0 801346D0 3C05800D */       lui $a1, %hi(func_ovl0_800CCF00)
  /* 181DD4 801346D4 24A5CF00 */     addiu $a1, $a1, %lo(func_ovl0_800CCF00)
  /* 181DD8 801346D8 240EFFFF */     addiu $t6, $zero, -1
  /* 181DDC 801346DC AFA2002C */        sw $v0, 0x2c($sp)
  /* 181DE0 801346E0 AFAE0010 */        sw $t6, 0x10($sp)
  /* 181DE4 801346E4 AFA50020 */        sw $a1, 0x20($sp)
  /* 181DE8 801346E8 00402025 */        or $a0, $v0, $zero
  /* 181DEC 801346EC 24060007 */     addiu $a2, $zero, 7
  /* 181DF0 801346F0 0C00277D */       jal omAddGObjRenderProc
  /* 181DF4 801346F4 3C078000 */       lui $a3, 0x8000
  /* 181DF8 801346F8 3C0F8014 */       lui $t7, %hi(gCreditsSpriteFile)
  /* 181DFC 801346FC 8DEFAA10 */        lw $t7, %lo(gCreditsSpriteFile)($t7)
  /* 181E00 80134700 3C180000 */       lui $t8, %hi(D_NF_00006F98)
  /* 181E04 80134704 27186F98 */     addiu $t8, $t8, %lo(D_NF_00006F98)
  /* 181E08 80134708 8FA4002C */        lw $a0, 0x2c($sp)
  /* 181E0C 8013470C 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 181E10 80134710 01F82821 */      addu $a1, $t7, $t8
  /* 181E14 80134714 24040003 */     addiu $a0, $zero, 3
  /* 181E18 80134718 00002825 */        or $a1, $zero, $zero
  /* 181E1C 8013471C 24060008 */     addiu $a2, $zero, 8
  /* 181E20 80134720 3C078000 */       lui $a3, 0x8000
  /* 181E24 80134724 0C00265A */       jal omMakeGObjCommon
  /* 181E28 80134728 AFA20028 */        sw $v0, 0x28($sp)
  /* 181E2C 8013472C 2419FFFF */     addiu $t9, $zero, -1
  /* 181E30 80134730 AFA2002C */        sw $v0, 0x2c($sp)
  /* 181E34 80134734 AFB90010 */        sw $t9, 0x10($sp)
  /* 181E38 80134738 00402025 */        or $a0, $v0, $zero
  /* 181E3C 8013473C 8FA50020 */        lw $a1, 0x20($sp)
  /* 181E40 80134740 24060007 */     addiu $a2, $zero, 7
  /* 181E44 80134744 0C00277D */       jal omAddGObjRenderProc
  /* 181E48 80134748 3C078000 */       lui $a3, 0x8000
  /* 181E4C 8013474C 3C088014 */       lui $t0, %hi(gCreditsSpriteFile)
  /* 181E50 80134750 8D08AA10 */        lw $t0, %lo(gCreditsSpriteFile)($t0)
  /* 181E54 80134754 3C090000 */       lui $t1, %hi(D_NF_000071D8)
  /* 181E58 80134758 252971D8 */     addiu $t1, $t1, %lo(D_NF_000071D8)
  /* 181E5C 8013475C 8FA4002C */        lw $a0, 0x2c($sp)
  /* 181E60 80134760 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 181E64 80134764 01092821 */      addu $a1, $t0, $t1
  /* 181E68 80134768 3C014000 */       lui $at, (0x40000000 >> 16) # 2.0
  /* 181E6C 8013476C 44810000 */      mtc1 $at, $f0 # 2.0 to cop1
  /* 181E70 80134770 3C018014 */       lui $at, %hi(D_ovl59_8013A7BC)
  /* 181E74 80134774 C422A7BC */      lwc1 $f2, %lo(D_ovl59_8013A7BC)($at)
  /* 181E78 80134778 8FA30028 */        lw $v1, 0x28($sp)
  /* 181E7C 8013477C 240B0001 */     addiu $t3, $zero, 1
  /* 181E80 80134780 A44B0024 */        sh $t3, 0x24($v0)
  /* 181E84 80134784 A46B0024 */        sh $t3, 0x24($v1)
  /* 181E88 80134788 E4400018 */      swc1 $f0, 0x18($v0)
  /* 181E8C 8013478C E4600018 */      swc1 $f0, 0x18($v1)
  /* 181E90 80134790 E442001C */      swc1 $f2, 0x1c($v0)
  /* 181E94 80134794 240D0078 */     addiu $t5, $zero, 0x78
  /* 181E98 80134798 E462001C */      swc1 $f2, 0x1c($v1)
  /* 181E9C 8013479C A04D0028 */        sb $t5, 0x28($v0)
  /* 181EA0 801347A0 3C0141F0 */       lui $at, (0x41F00000 >> 16) # 30.0
  /* 181EA4 801347A4 240F006E */     addiu $t7, $zero, 0x6e
  /* 181EA8 801347A8 A06D0028 */        sb $t5, 0x28($v1)
  /* 181EAC 801347AC 44816000 */      mtc1 $at, $f12 # 30.0 to cop1
  /* 181EB0 801347B0 A04F0029 */        sb $t7, 0x29($v0)
  /* 181EB4 801347B4 24190040 */     addiu $t9, $zero, 0x40
  /* 181EB8 801347B8 3C0143A4 */       lui $at, (0x43A40000 >> 16) # 328.0
  /* 181EBC 801347BC A06F0029 */        sb $t7, 0x29($v1)
  /* 181EC0 801347C0 44812000 */      mtc1 $at, $f4 # 328.0 to cop1
  /* 181EC4 801347C4 A059002A */        sb $t9, 0x2a($v0)
  /* 181EC8 801347C8 3C014413 */       lui $at, (0x44130000 >> 16) # 588.0
  /* 181ECC 801347CC A079002A */        sb $t9, 0x2a($v1)
  /* 181ED0 801347D0 44813000 */      mtc1 $at, $f6 # 588.0 to cop1
  /* 181ED4 801347D4 E44C005C */      swc1 $f12, 0x5c($v0)
  /* 181ED8 801347D8 E46C005C */      swc1 $f12, 0x5c($v1)
  /* 181EDC 801347DC E4640058 */      swc1 $f4, 0x58($v1)
  /* 181EE0 801347E0 E4460058 */      swc1 $f6, 0x58($v0)
  /* 181EE4 801347E4 8FBF001C */        lw $ra, 0x1c($sp)
  /* 181EE8 801347E8 27BD0030 */     addiu $sp, $sp, 0x30
  /* 181EEC 801347EC 03E00008 */        jr $ra
  /* 181EF0 801347F0 00000000 */       nop 

glabel gmCreditsMakeTextBoxGObj
  /* 181EF4 801347F4 27BDFFD8 */     addiu $sp, $sp, -0x28
  /* 181EF8 801347F8 AFBF001C */        sw $ra, 0x1c($sp)
  /* 181EFC 801347FC 24040004 */     addiu $a0, $zero, 4
  /* 181F00 80134800 00002825 */        or $a1, $zero, $zero
  /* 181F04 80134804 24060007 */     addiu $a2, $zero, 7
  /* 181F08 80134808 0C00265A */       jal omMakeGObjCommon
  /* 181F0C 8013480C 3C078000 */       lui $a3, 0x8000
  /* 181F10 80134810 3C058001 */       lui $a1, %hi(func_80014038)
  /* 181F14 80134814 240EFFFF */     addiu $t6, $zero, -1
  /* 181F18 80134818 AFA20024 */        sw $v0, 0x24($sp)
  /* 181F1C 8013481C AFAE0010 */        sw $t6, 0x10($sp)
  /* 181F20 80134820 24A54038 */     addiu $a1, $a1, %lo(func_80014038)
  /* 181F24 80134824 00402025 */        or $a0, $v0, $zero
  /* 181F28 80134828 24060009 */     addiu $a2, $zero, 9
  /* 181F2C 8013482C 0C00277D */       jal omAddGObjRenderProc
  /* 181F30 80134830 3C078000 */       lui $a3, 0x8000
  /* 181F34 80134834 3C058014 */       lui $a1, %hi(dCreditsTextBoxDisplayList)
  /* 181F38 80134838 24A5A598 */     addiu $a1, $a1, %lo(dCreditsTextBoxDisplayList)
  /* 181F3C 8013483C 0C0024B4 */       jal func_800092D0
  /* 181F40 80134840 8FA40024 */        lw $a0, 0x24($sp)
  /* 181F44 80134844 8FBF001C */        lw $ra, 0x1c($sp)
  /* 181F48 80134848 27BD0028 */     addiu $sp, $sp, 0x28
  /* 181F4C 8013484C 03E00008 */        jr $ra
  /* 181F50 80134850 00000000 */       nop 

glabel gmCreditsStaffRollProcUpdate
  /* 181F54 80134854 27BDFFC0 */     addiu $sp, $sp, -0x40
  /* 181F58 80134858 AFA40040 */        sw $a0, 0x40($sp)
  /* 181F5C 8013485C 3C048013 */       lui $a0, %hi(dCreditsJobDescriptions)
  /* 181F60 80134860 2484679C */     addiu $a0, $a0, %lo(dCreditsJobDescriptions)
  /* 181F64 80134864 AFBF0034 */        sw $ra, 0x34($sp)
  /* 181F68 80134868 AFB2002C */        sw $s2, 0x2c($sp)
  /* 181F6C 8013486C AFB10028 */        sw $s1, 0x28($sp)
  /* 181F70 80134870 AFB30030 */        sw $s3, 0x30($sp)
  /* 181F74 80134874 AFB00024 */        sw $s0, 0x24($sp)
  /* 181F78 80134878 F7B60018 */      sdc1 $f22, 0x18($sp)
  /* 181F7C 8013487C F7B40010 */      sdc1 $f20, 0x10($sp)
  /* 181F80 80134880 24110001 */     addiu $s1, $zero, 1
  /* 181F84 80134884 0C04CF9A */       jal gmCreditsMakeJobGObj
  /* 181F88 80134888 00809025 */        or $s2, $a0, $zero
  /* 181F8C 8013488C 3C138014 */       lui $s3, %hi(gCreditsNameID)
  /* 181F90 80134890 2673A8B8 */     addiu $s3, $s3, %lo(gCreditsNameID)
  /* 181F94 80134894 8E6E0000 */        lw $t6, ($s3) # gCreditsNameID + 0
  /* 181F98 80134898 8C500084 */        lw $s0, 0x84($v0)
  /* 181F9C 8013489C 29C10054 */      slti $at, $t6, 0x54
  /* 181FA0 801348A0 10200027 */      beqz $at, .L80134940
  /* 181FA4 801348A4 3C018014 */       lui $at, %hi(D_ovl59_8013A7C0)
  /* 181FA8 801348A8 C436A7C0 */      lwc1 $f22, %lo(D_ovl59_8013A7C0)($at)
  /* 181FAC 801348AC 3C018014 */       lui $at, %hi(D_ovl59_8013A7C4)
  /* 181FB0 801348B0 C434A7C4 */      lwc1 $f20, %lo(D_ovl59_8013A7C4)($at)
  .L801348B4:
  /* 181FB4 801348B4 52200004 */      beql $s1, $zero, .L801348C8
  /* 181FB8 801348B8 4600B006 */     mov.s $f0, $f22
  /* 181FBC 801348BC 10000002 */         b .L801348C8
  /* 181FC0 801348C0 4600A006 */     mov.s $f0, $f20
  /* 181FC4 801348C4 4600B006 */     mov.s $f0, $f22
  .L801348C8:
  /* 181FC8 801348C8 C6040014 */      lwc1 $f4, 0x14($s0)
  /* 181FCC 801348CC 4604003C */    c.lt.s $f0, $f4
  /* 181FD0 801348D0 00000000 */       nop 
  /* 181FD4 801348D4 45000014 */      bc1f .L80134928
  /* 181FD8 801348D8 00000000 */       nop 
  /* 181FDC 801348DC 5220000E */      beql $s1, $zero, .L80134918
  /* 181FE0 801348E0 2652000C */     addiu $s2, $s2, 0xc
  /* 181FE4 801348E4 0C04CFDA */       jal gmCreditsMakeNameGObjAndDObjs
  /* 181FE8 801348E8 00000000 */       nop 
  /* 181FEC 801348EC 8E6F0000 */        lw $t7, ($s3) # gCreditsNameID + 0
  /* 181FF0 801348F0 AFA2003C */        sw $v0, 0x3c($sp)
  /* 181FF4 801348F4 8C500084 */        lw $s0, 0x84($v0)
  /* 181FF8 801348F8 25F80001 */     addiu $t8, $t7, 1
  /* 181FFC 801348FC AE780000 */        sw $t8, ($s3) # gCreditsNameID + 0
  /* 182000 80134900 8E590008 */        lw $t9, 8($s2)
  /* 182004 80134904 17380008 */       bne $t9, $t8, .L80134928
  /* 182008 80134908 00000000 */       nop 
  /* 18200C 8013490C 10000006 */         b .L80134928
  /* 182010 80134910 00008825 */        or $s1, $zero, $zero
  /* 182014 80134914 2652000C */     addiu $s2, $s2, 0xc
  .L80134918:
  /* 182018 80134918 02402025 */        or $a0, $s2, $zero
  /* 18201C 8013491C 0C04CF9A */       jal gmCreditsMakeJobGObj
  /* 182020 80134920 24110001 */     addiu $s1, $zero, 1
  /* 182024 80134924 8C500084 */        lw $s0, 0x84($v0)
  .L80134928:
  /* 182028 80134928 0C002C7A */       jal stop_current_process
  /* 18202C 8013492C 24040001 */     addiu $a0, $zero, 1
  /* 182030 80134930 8E690000 */        lw $t1, ($s3) # gCreditsNameID + 0
  /* 182034 80134934 29210054 */      slti $at, $t1, 0x54
  /* 182038 80134938 1420FFDE */      bnez $at, .L801348B4
  /* 18203C 8013493C 00000000 */       nop 
  .L80134940:
  /* 182040 80134940 8FAA003C */        lw $t2, 0x3c($sp)
  /* 182044 80134944 240BFFFF */     addiu $t3, $zero, -1
  /* 182048 80134948 3C018014 */       lui $at, %hi(gCreditsStaffRollGObj)
  /* 18204C 8013494C 8D500084 */        lw $s0, 0x84($t2)
  /* 182050 80134950 00002025 */        or $a0, $zero, $zero
  /* 182054 80134954 AE0B0018 */        sw $t3, 0x18($s0)
  /* 182058 80134958 0C0026A1 */       jal omEjectGObjCommon
  /* 18205C 8013495C AC20A8C8 */        sw $zero, %lo(gCreditsStaffRollGObj)($at)
  /* 182060 80134960 0C002C7A */       jal stop_current_process
  /* 182064 80134964 24040001 */     addiu $a0, $zero, 1
  /* 182068 80134968 8FBF0034 */        lw $ra, 0x34($sp)
  /* 18206C 8013496C D7B40010 */      ldc1 $f20, 0x10($sp)
  /* 182070 80134970 D7B60018 */      ldc1 $f22, 0x18($sp)
  /* 182074 80134974 8FB00024 */        lw $s0, 0x24($sp)
  /* 182078 80134978 8FB10028 */        lw $s1, 0x28($sp)
  /* 18207C 8013497C 8FB2002C */        lw $s2, 0x2c($sp)
  /* 182080 80134980 8FB30030 */        lw $s3, 0x30($sp)
  /* 182084 80134984 03E00008 */        jr $ra
  /* 182088 80134988 27BD0040 */     addiu $sp, $sp, 0x40

glabel gmCreditsMakeStaffRollGObj
  /* 18208C 8013498C 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 182090 80134990 AFBF0014 */        sw $ra, 0x14($sp)
  /* 182094 80134994 00002025 */        or $a0, $zero, $zero
  /* 182098 80134998 00002825 */        or $a1, $zero, $zero
  /* 18209C 8013499C 24060001 */     addiu $a2, $zero, 1
  /* 1820A0 801349A0 0C00265A */       jal omMakeGObjCommon
  /* 1820A4 801349A4 3C078000 */       lui $a3, 0x8000
  /* 1820A8 801349A8 3C058013 */       lui $a1, %hi(gmCreditsStaffRollProcUpdate)
  /* 1820AC 801349AC AFA2001C */        sw $v0, 0x1c($sp)
  /* 1820B0 801349B0 24A54854 */     addiu $a1, $a1, %lo(gmCreditsStaffRollProcUpdate)
  /* 1820B4 801349B4 00402025 */        or $a0, $v0, $zero
  /* 1820B8 801349B8 00003025 */        or $a2, $zero, $zero
  /* 1820BC 801349BC 0C002062 */       jal omAddGObjCommonProc
  /* 1820C0 801349C0 24070001 */     addiu $a3, $zero, 1
  /* 1820C4 801349C4 8FBF0014 */        lw $ra, 0x14($sp)
  /* 1820C8 801349C8 8FAE001C */        lw $t6, 0x1c($sp)
  /* 1820CC 801349CC 3C018014 */       lui $at, %hi(gCreditsStaffRollGObj)
  /* 1820D0 801349D0 27BD0020 */     addiu $sp, $sp, 0x20
  /* 1820D4 801349D4 03E00008 */        jr $ra
  /* 1820D8 801349D8 AC2EA8C8 */        sw $t6, %lo(gCreditsStaffRollGObj)($at)

glabel func_ovl59_801349DC
  /* 1820DC 801349DC 27BDFFC0 */     addiu $sp, $sp, -0x40
  /* 1820E0 801349E0 3C0E001B */       lui $t6, %hi(D_NF_001AC870)
  /* 1820E4 801349E4 3C0F0000 */       lui $t7, %hi(D_NF_00000854)
  /* 1820E8 801349E8 3C188014 */       lui $t8, %hi(D_ovl59_8013A910)
  /* 1820EC 801349EC AFBF0014 */        sw $ra, 0x14($sp)
  /* 1820F0 801349F0 25CEC870 */     addiu $t6, $t6, %lo(D_NF_001AC870)
  /* 1820F4 801349F4 25EF0854 */     addiu $t7, $t7, %lo(D_NF_00000854)
  /* 1820F8 801349F8 2718A910 */     addiu $t8, $t8, %lo(D_ovl59_8013A910)
  /* 1820FC 801349FC 24190020 */     addiu $t9, $zero, 0x20
  /* 182100 80134A00 AFAE0020 */        sw $t6, 0x20($sp)
  /* 182104 80134A04 AFAF0024 */        sw $t7, 0x24($sp)
  /* 182108 80134A08 AFA00028 */        sw $zero, 0x28($sp)
  /* 18210C 80134A0C AFA0002C */        sw $zero, 0x2c($sp)
  /* 182110 80134A10 AFB80030 */        sw $t8, 0x30($sp)
  /* 182114 80134A14 AFB90034 */        sw $t9, 0x34($sp)
  /* 182118 80134A18 AFA00038 */        sw $zero, 0x38($sp)
  /* 18211C 80134A1C AFA0003C */        sw $zero, 0x3c($sp)
  /* 182120 80134A20 0C0337DE */       jal rldm_initialize
  /* 182124 80134A24 27A40020 */     addiu $a0, $sp, 0x20
  /* 182128 80134A28 3C048014 */       lui $a0, %hi(D_ovl59_8013A184)
  /* 18212C 80134A2C 2484A184 */     addiu $a0, $a0, %lo(D_ovl59_8013A184)
  /* 182130 80134A30 0C0337BB */       jal rldm_bytes_need_to_load
  /* 182134 80134A34 24050001 */     addiu $a1, $zero, 1
  /* 182138 80134A38 00402025 */        or $a0, $v0, $zero
  /* 18213C 80134A3C 0C001260 */       jal hal_alloc
  /* 182140 80134A40 24050010 */     addiu $a1, $zero, 0x10
  /* 182144 80134A44 3C048014 */       lui $a0, %hi(D_ovl59_8013A184)
  /* 182148 80134A48 3C068014 */       lui $a2, %hi(gCreditsSpriteFile)
  /* 18214C 80134A4C 24C6AA10 */     addiu $a2, $a2, %lo(gCreditsSpriteFile)
  /* 182150 80134A50 2484A184 */     addiu $a0, $a0, %lo(D_ovl59_8013A184)
  /* 182154 80134A54 24050001 */     addiu $a1, $zero, 1
  /* 182158 80134A58 0C033781 */       jal rldm_load_files_into
  /* 18215C 80134A5C 00403825 */        or $a3, $v0, $zero
  /* 182160 80134A60 8FBF0014 */        lw $ra, 0x14($sp)
  /* 182164 80134A64 27BD0040 */     addiu $sp, $sp, 0x40
  /* 182168 80134A68 03E00008 */        jr $ra
  /* 18216C 80134A6C 00000000 */       nop 

glabel func_ovl59_80134A70
  /* 182170 80134A70 27BDFFC0 */     addiu $sp, $sp, -0x40
  /* 182174 80134A74 AFB70034 */        sw $s7, 0x34($sp)
  /* 182178 80134A78 AFB30024 */        sw $s3, 0x24($sp)
  /* 18217C 80134A7C AFB00018 */        sw $s0, 0x18($sp)
  /* 182180 80134A80 AFBE0038 */        sw $fp, 0x38($sp)
  /* 182184 80134A84 AFB60030 */        sw $s6, 0x30($sp)
  /* 182188 80134A88 AFB40028 */        sw $s4, 0x28($sp)
  /* 18218C 80134A8C AFB20020 */        sw $s2, 0x20($sp)
  /* 182190 80134A90 AFB1001C */        sw $s1, 0x1c($sp)
  /* 182194 80134A94 3C108014 */       lui $s0, %hi(dCreditsNameAndJobSpriteInfo)
  /* 182198 80134A98 3C138014 */       lui $s3, %hi(gCreditsNameAndJobDisplayLists)
  /* 18219C 80134A9C 3C178014 */       lui $s7, %hi(gCreditsSpriteFile)
  /* 1821A0 80134AA0 AFBF003C */        sw $ra, 0x3c($sp)
  /* 1821A4 80134AA4 AFB5002C */        sw $s5, 0x2c($sp)
  /* 1821A8 80134AA8 26F7AA10 */     addiu $s7, $s7, %lo(gCreditsSpriteFile)
  /* 1821AC 80134AAC 2673A7D8 */     addiu $s3, $s3, %lo(gCreditsNameAndJobDisplayLists)
  /* 1821B0 80134AB0 2610A188 */     addiu $s0, $s0, %lo(dCreditsNameAndJobSpriteInfo)
  /* 1821B4 80134AB4 2411007F */     addiu $s1, $zero, 0x7f
  /* 1821B8 80134AB8 24120004 */     addiu $s2, $zero, 4
  /* 1821BC 80134ABC 3C14E700 */       lui $s4, 0xe700
  /* 1821C0 80134AC0 3C16FD90 */       lui $s6, 0xfd90
  /* 1821C4 80134AC4 3C1EF590 */       lui $fp, 0xf590
  .L80134AC8:
  /* 1821C8 80134AC8 24040040 */     addiu $a0, $zero, 0x40
  /* 1821CC 80134ACC 0C001260 */       jal hal_alloc
  /* 1821D0 80134AD0 24050008 */     addiu $a1, $zero, 8
  /* 1821D4 80134AD4 00401825 */        or $v1, $v0, $zero
  /* 1821D8 80134AD8 0040A825 */        or $s5, $v0, $zero
  /* 1821DC 80134ADC 00002825 */        or $a1, $zero, $zero
  .L80134AE0:
  /* 1821E0 80134AE0 30A20002 */      andi $v0, $a1, 2
  /* 1821E4 80134AE4 10400005 */      beqz $v0, .L80134AFC
  /* 1821E8 80134AE8 28A10003 */      slti $at, $a1, 3
  /* 1821EC 80134AEC 920E0000 */       lbu $t6, ($s0) # dCreditsNameAndJobSpriteInfo + 0
  /* 1821F0 80134AF0 000E7823 */      negu $t7, $t6
  /* 1821F4 80134AF4 10000003 */         b .L80134B04
  /* 1821F8 80134AF8 A46F0000 */        sh $t7, ($v1)
  .L80134AFC:
  /* 1821FC 80134AFC 92180000 */       lbu $t8, ($s0) # dCreditsNameAndJobSpriteInfo + 0
  /* 182200 80134B00 A4780000 */        sh $t8, ($v1)
  .L80134B04:
  /* 182204 80134B04 14A00004 */      bnez $a1, .L80134B18
  /* 182208 80134B08 00000000 */       nop 
  /* 18220C 80134B0C 92190001 */       lbu $t9, 1($s0) # dCreditsNameAndJobSpriteInfo + 1
  /* 182210 80134B10 10000008 */         b .L80134B34
  /* 182214 80134B14 A4790002 */        sh $t9, 2($v1)
  .L80134B18:
  /* 182218 80134B18 50200005 */      beql $at, $zero, .L80134B30
  /* 18221C 80134B1C 92040001 */       lbu $a0, 1($s0) # dCreditsNameAndJobSpriteInfo + 1
  /* 182220 80134B20 92040001 */       lbu $a0, 1($s0) # dCreditsNameAndJobSpriteInfo + 1
  /* 182224 80134B24 10000002 */         b .L80134B30
  /* 182228 80134B28 00042023 */      negu $a0, $a0
  /* 18222C 80134B2C 92040001 */       lbu $a0, 1($s0) # dCreditsNameAndJobSpriteInfo + 1
  .L80134B30:
  /* 182230 80134B30 A4640002 */        sh $a0, 2($v1)
  .L80134B34:
  /* 182234 80134B34 A4600004 */        sh $zero, 4($v1)
  /* 182238 80134B38 10400003 */      beqz $v0, .L80134B48
  /* 18223C 80134B3C A4600006 */        sh $zero, 6($v1)
  /* 182240 80134B40 10000004 */         b .L80134B54
  /* 182244 80134B44 A4600008 */        sh $zero, 8($v1)
  .L80134B48:
  /* 182248 80134B48 920C0000 */       lbu $t4, ($s0) # dCreditsNameAndJobSpriteInfo + 0
  /* 18224C 80134B4C 000C6940 */       sll $t5, $t4, 5
  /* 182250 80134B50 A46D0008 */        sh $t5, 8($v1)
  .L80134B54:
  /* 182254 80134B54 14A00003 */      bnez $a1, .L80134B64
  /* 182258 80134B58 28A10003 */      slti $at, $a1, 3
  /* 18225C 80134B5C 10000007 */         b .L80134B7C
  /* 182260 80134B60 A460000A */        sh $zero, 0xa($v1)
  .L80134B64:
  /* 182264 80134B64 10200004 */      beqz $at, .L80134B78
  /* 182268 80134B68 00002025 */        or $a0, $zero, $zero
  /* 18226C 80134B6C 92040001 */       lbu $a0, 1($s0) # dCreditsNameAndJobSpriteInfo + 1
  /* 182270 80134B70 10000001 */         b .L80134B78
  /* 182274 80134B74 00042140 */       sll $a0, $a0, 5
  .L80134B78:
  /* 182278 80134B78 A464000A */        sh $a0, 0xa($v1)
  .L80134B7C:
  /* 18227C 80134B7C 24A50001 */     addiu $a1, $a1, 1
  /* 182280 80134B80 24630010 */     addiu $v1, $v1, 0x10
  /* 182284 80134B84 A060FFFC */        sb $zero, -4($v1)
  /* 182288 80134B88 A060FFFD */        sb $zero, -3($v1)
  /* 18228C 80134B8C A071FFFE */        sb $s1, -2($v1)
  /* 182290 80134B90 14B2FFD3 */       bne $a1, $s2, .L80134AE0
  /* 182294 80134B94 A060FFFF */        sb $zero, -1($v1)
  /* 182298 80134B98 24040060 */     addiu $a0, $zero, 0x60
  /* 18229C 80134B9C 0C001260 */       jal hal_alloc
  /* 1822A0 80134BA0 24050008 */     addiu $a1, $zero, 8
  /* 1822A4 80134BA4 AE620000 */        sw $v0, ($s3) # gCreditsNameAndJobDisplayLists + 0
  /* 1822A8 80134BA8 AC400004 */        sw $zero, 4($v0)
  /* 1822AC 80134BAC AC540000 */        sw $s4, ($v0)
  /* 1822B0 80134BB0 AC560008 */        sw $s6, 8($v0)
  /* 1822B4 80134BB4 8EEF0000 */        lw $t7, ($s7) # gCreditsSpriteFile + 0
  /* 1822B8 80134BB8 8E0E0004 */        lw $t6, 4($s0) # dCreditsNameAndJobSpriteInfo + 4
  /* 1822BC 80134BBC 3C190709 */       lui $t9, (0x7094250 >> 16) # 118047312
  /* 1822C0 80134BC0 37394250 */       ori $t9, $t9, (0x7094250 & 0xFFFF) # 118047312
  /* 1822C4 80134BC4 3C0CE600 */       lui $t4, 0xe600
  /* 1822C8 80134BC8 3C0DF300 */       lui $t5, 0xf300
  /* 1822CC 80134BCC 01CFC021 */      addu $t8, $t6, $t7
  /* 1822D0 80134BD0 AC58000C */        sw $t8, 0xc($v0)
  /* 1822D4 80134BD4 AC4D0020 */        sw $t5, 0x20($v0)
  /* 1822D8 80134BD8 AC4C0018 */        sw $t4, 0x18($v0)
  /* 1822DC 80134BDC AC590014 */        sw $t9, 0x14($v0)
  /* 1822E0 80134BE0 AC40001C */        sw $zero, 0x1c($v0)
  /* 1822E4 80134BE4 AC5E0010 */        sw $fp, 0x10($v0)
  /* 1822E8 80134BE8 92040000 */       lbu $a0, ($s0) # dCreditsNameAndJobSpriteInfo + 0
  /* 1822EC 80134BEC 920E0001 */       lbu $t6, 1($s0) # dCreditsNameAndJobSpriteInfo + 1
  /* 1822F0 80134BF0 24490028 */     addiu $t1, $v0, 0x28
  /* 1822F4 80134BF4 2484000F */     addiu $a0, $a0, 0xf
  /* 1822F8 80134BF8 01201825 */        or $v1, $t1, $zero
  /* 1822FC 80134BFC 04810002 */      bgez $a0, .L80134C08
  /* 182300 80134C00 00800821 */      addu $at, $a0, $zero
  /* 182304 80134C04 2481000F */     addiu $at, $a0, 0xf
  .L80134C08:
  /* 182308 80134C08 00012103 */       sra $a0, $at, 4
  /* 18230C 80134C0C 01C40019 */     multu $t6, $a0
  /* 182310 80134C10 26730004 */     addiu $s3, $s3, 4
  /* 182314 80134C14 00041900 */       sll $v1, $a0, 4
  /* 182318 80134C18 240A07FF */     addiu $t2, $zero, 0x7ff
  /* 18231C 80134C1C 00002812 */      mflo $a1
  /* 182320 80134C20 00052900 */       sll $a1, $a1, 4
  /* 182324 80134C24 24A50003 */     addiu $a1, $a1, 3
  /* 182328 80134C28 00052883 */       sra $a1, $a1, 2
  /* 18232C 80134C2C 24A5FFFF */     addiu $a1, $a1, -1
  /* 182330 80134C30 28A107FF */      slti $at, $a1, 0x7ff
  /* 182334 80134C34 10200003 */      beqz $at, .L80134C44
  /* 182338 80134C38 00000000 */       nop 
  /* 18233C 80134C3C 10000001 */         b .L80134C44
  /* 182340 80134C40 00A05025 */        or $t2, $a1, $zero
  .L80134C44:
  /* 182344 80134C44 04610002 */      bgez $v1, .L80134C50
  /* 182348 80134C48 00600821 */      addu $at, $v1, $zero
  /* 18234C 80134C4C 2461000F */     addiu $at, $v1, 0xf
  .L80134C50:
  /* 182350 80134C50 00011903 */       sra $v1, $at, 4
  /* 182354 80134C54 1C600003 */      bgtz $v1, .L80134C64
  /* 182358 80134C58 314D0FFF */      andi $t5, $t2, 0xfff
  /* 18235C 80134C5C 10000002 */         b .L80134C68
  /* 182360 80134C60 240B0001 */     addiu $t3, $zero, 1
  .L80134C64:
  /* 182364 80134C64 00605825 */        or $t3, $v1, $zero
  .L80134C68:
  /* 182368 80134C68 1C600003 */      bgtz $v1, .L80134C78
  /* 18236C 80134C6C 256F07FF */     addiu $t7, $t3, 0x7ff
  /* 182370 80134C70 10000002 */         b .L80134C7C
  /* 182374 80134C74 24040001 */     addiu $a0, $zero, 1
  .L80134C78:
  /* 182378 80134C78 00602025 */        or $a0, $v1, $zero
  .L80134C7C:
  /* 18237C 80134C7C 01E4001A */       div $zero, $t7, $a0
  /* 182380 80134C80 14800002 */      bnez $a0, .L80134C8C
  /* 182384 80134C84 00000000 */       nop 
  /* 182388 80134C88 0007000D */     break 7
  .L80134C8C:
  /* 18238C 80134C8C 2401FFFF */     addiu $at, $zero, -1
  /* 182390 80134C90 14810004 */       bne $a0, $at, .L80134CA4
  /* 182394 80134C94 3C018000 */       lui $at, 0x8000
  /* 182398 80134C98 15E10002 */       bne $t7, $at, .L80134CA4
  /* 18239C 80134C9C 00000000 */       nop 
  /* 1823A0 80134CA0 0006000D */     break 6
  .L80134CA4:
  /* 1823A4 80134CA4 0000C012 */      mflo $t8
  /* 1823A8 80134CA8 33190FFF */      andi $t9, $t8, 0xfff
  /* 1823AC 80134CAC 3C010700 */       lui $at, 0x700
  /* 1823B0 80134CB0 03216025 */        or $t4, $t9, $at
  /* 1823B4 80134CB4 000D7300 */       sll $t6, $t5, 0xc
  /* 1823B8 80134CB8 018E7825 */        or $t7, $t4, $t6
  /* 1823BC 80134CBC AC4F0024 */        sw $t7, 0x24($v0)
  /* 1823C0 80134CC0 AD200004 */        sw $zero, 4($t1)
  /* 1823C4 80134CC4 AD340000 */        sw $s4, ($t1)
  /* 1823C8 80134CC8 92180000 */       lbu $t8, ($s0) # dCreditsNameAndJobSpriteInfo + 0
  /* 1823CC 80134CCC 25230008 */     addiu $v1, $t1, 8
  /* 1823D0 80134CD0 00603025 */        or $a2, $v1, $zero
  /* 1823D4 80134CD4 2719000F */     addiu $t9, $t8, 0xf
  /* 1823D8 80134CD8 24630008 */     addiu $v1, $v1, 8
  /* 1823DC 80134CDC 00603825 */        or $a3, $v1, $zero
  /* 1823E0 80134CE0 24630008 */     addiu $v1, $v1, 8
  /* 1823E4 80134CE4 00604025 */        or $t0, $v1, $zero
  /* 1823E8 80134CE8 24630008 */     addiu $v1, $v1, 8
  /* 1823EC 80134CEC 00601025 */        or $v0, $v1, $zero
  /* 1823F0 80134CF0 24630008 */     addiu $v1, $v1, 8
  /* 1823F4 80134CF4 00602025 */        or $a0, $v1, $zero
  /* 1823F8 80134CF8 01202825 */        or $a1, $t1, $zero
  /* 1823FC 80134CFC 07210003 */      bgez $t9, .L80134D0C
  /* 182400 80134D00 00196903 */       sra $t5, $t9, 4
  /* 182404 80134D04 2721000F */     addiu $at, $t9, 0xf
  /* 182408 80134D08 00016903 */       sra $t5, $at, 4
  .L80134D0C:
  /* 18240C 80134D0C 000D6100 */       sll $t4, $t5, 4
  /* 182410 80134D10 000C7043 */       sra $t6, $t4, 1
  /* 182414 80134D14 25CF0007 */     addiu $t7, $t6, 7
  /* 182418 80134D18 000FC0C3 */       sra $t8, $t7, 3
  /* 18241C 80134D1C 331901FF */      andi $t9, $t8, 0x1ff
  /* 182420 80134D20 00196A40 */       sll $t5, $t9, 9
  /* 182424 80134D24 3C0E0009 */       lui $t6, (0x94250 >> 16) # 606800
  /* 182428 80134D28 3C01F580 */       lui $at, 0xf580
  /* 18242C 80134D2C 01A16025 */        or $t4, $t5, $at
  /* 182430 80134D30 35CE4250 */       ori $t6, $t6, (0x94250 & 0xFFFF) # 606800
  /* 182434 80134D34 ACCE0004 */        sw $t6, 4($a2)
  /* 182438 80134D38 ACCC0000 */        sw $t4, ($a2)
  /* 18243C 80134D3C 3C0FF200 */       lui $t7, 0xf200
  /* 182440 80134D40 ACEF0000 */        sw $t7, ($a3)
  /* 182444 80134D44 92180001 */       lbu $t8, 1($s0) # dCreditsNameAndJobSpriteInfo + 1
  /* 182448 80134D48 920E0000 */       lbu $t6, ($s0) # dCreditsNameAndJobSpriteInfo + 0
  /* 18244C 80134D4C 24630008 */     addiu $v1, $v1, 8
  /* 182450 80134D50 2719FFFF */     addiu $t9, $t8, -1
  /* 182454 80134D54 25CF000F */     addiu $t7, $t6, 0xf
  /* 182458 80134D58 00196880 */       sll $t5, $t9, 2
  /* 18245C 80134D5C 31AC0FFF */      andi $t4, $t5, 0xfff
  /* 182460 80134D60 05E10003 */      bgez $t7, .L80134D70
  /* 182464 80134D64 000FC103 */       sra $t8, $t7, 4
  /* 182468 80134D68 25E1000F */     addiu $at, $t7, 0xf
  /* 18246C 80134D6C 0001C103 */       sra $t8, $at, 4
  .L80134D70:
  /* 182470 80134D70 0018C900 */       sll $t9, $t8, 4
  /* 182474 80134D74 272DFFFF */     addiu $t5, $t9, -1
  /* 182478 80134D78 000D7080 */       sll $t6, $t5, 2
  /* 18247C 80134D7C 31CF0FFF */      andi $t7, $t6, 0xfff
  /* 182480 80134D80 000FC300 */       sll $t8, $t7, 0xc
  /* 182484 80134D84 0198C825 */        or $t9, $t4, $t8
  /* 182488 80134D88 ACF90004 */        sw $t9, 4($a3)
  /* 18248C 80134D8C AD000004 */        sw $zero, 4($t0)
  /* 182490 80134D90 AD140000 */        sw $s4, ($t0)
  /* 182494 80134D94 3C0D0100 */       lui $t5, (0x1004008 >> 16) # 16793608
  /* 182498 80134D98 35AD4008 */       ori $t5, $t5, (0x1004008 & 0xFFFF) # 16793608
  /* 18249C 80134D9C AC4D0000 */        sw $t5, ($v0)
  /* 1824A0 80134DA0 AC550004 */        sw $s5, 4($v0)
  /* 1824A4 80134DA4 3C0E0606 */       lui $t6, (0x6060402 >> 16) # 101057538
  /* 1824A8 80134DA8 3C188014 */       lui $t8, %hi(gCreditsNameID)
  /* 1824AC 80134DAC 35CE0402 */       ori $t6, $t6, (0x6060402 & 0xFFFF) # 101057538
  /* 1824B0 80134DB0 240F0602 */     addiu $t7, $zero, 0x602
  /* 1824B4 80134DB4 2718A8B8 */     addiu $t8, $t8, %lo(gCreditsNameID)
  /* 1824B8 80134DB8 AC8F0004 */        sw $t7, 4($a0)
  /* 1824BC 80134DBC AC8E0000 */        sw $t6, ($a0)
  /* 1824C0 80134DC0 3C0CDF00 */       lui $t4, 0xdf00
  /* 1824C4 80134DC4 26100008 */     addiu $s0, $s0, 8
  /* 1824C8 80134DC8 AC6C0000 */        sw $t4, ($v1)
  /* 1824CC 80134DCC AC600004 */        sw $zero, 4($v1)
  /* 1824D0 80134DD0 1678FF3D */       bne $s3, $t8, .L80134AC8
  /* 1824D4 80134DD4 00602825 */        or $a1, $v1, $zero
  /* 1824D8 80134DD8 8FBF003C */        lw $ra, 0x3c($sp)
  /* 1824DC 80134DDC 8FB00018 */        lw $s0, 0x18($sp)
  /* 1824E0 80134DE0 8FB1001C */        lw $s1, 0x1c($sp)
  /* 1824E4 80134DE4 8FB20020 */        lw $s2, 0x20($sp)
  /* 1824E8 80134DE8 8FB30024 */        lw $s3, 0x24($sp)
  /* 1824EC 80134DEC 8FB40028 */        lw $s4, 0x28($sp)
  /* 1824F0 80134DF0 8FB5002C */        lw $s5, 0x2c($sp)
  /* 1824F4 80134DF4 8FB60030 */        lw $s6, 0x30($sp)
  /* 1824F8 80134DF8 8FB70034 */        lw $s7, 0x34($sp)
  /* 1824FC 80134DFC 8FBE0038 */        lw $fp, 0x38($sp)
  /* 182500 80134E00 03E00008 */        jr $ra
  /* 182504 80134E04 27BD0040 */     addiu $sp, $sp, 0x40

glabel func_ovl59_80134E08
  /* 182508 80134E08 240E0002 */     addiu $t6, $zero, 2
  /* 18250C 80134E0C 3C018014 */       lui $at, %hi(gCreditsStatus)
  /* 182510 80134E10 AC2EA8C0 */        sw $t6, %lo(gCreditsStatus)($at)
  /* 182514 80134E14 3C018014 */       lui $at, %hi(gCreditsNameID)
  /* 182518 80134E18 AC20A8B8 */        sw $zero, %lo(gCreditsNameID)($at)
  /* 18251C 80134E1C 3C018014 */       lui $at, %hi(D_ovl59_8013A7C8)
  /* 182520 80134E20 C424A7C8 */      lwc1 $f4, %lo(D_ovl59_8013A7C8)($at)
  /* 182524 80134E24 3C018014 */       lui $at, %hi(gCreditsRollSpeed)
  /* 182528 80134E28 3C028014 */       lui $v0, %hi(gCreditsSpriteFile)
  /* 18252C 80134E2C E424A8BC */      swc1 $f4, %lo(gCreditsRollSpeed)($at)
  /* 182530 80134E30 3C018014 */       lui $at, %hi(gCreditsNameAllocFree)
  /* 182534 80134E34 8C42AA10 */        lw $v0, %lo(gCreditsSpriteFile)($v0)
  /* 182538 80134E38 AC20A8C4 */        sw $zero, %lo(gCreditsNameAllocFree)($at)
  /* 18253C 80134E3C 3C018014 */       lui $at, %hi(gCreditsIsPaused)
  /* 182540 80134E40 3C0F0000 */       lui $t7, %hi(D_NF_00007304)
  /* 182544 80134E44 AC20A8D0 */        sw $zero, %lo(gCreditsIsPaused)($at)
  /* 182548 80134E48 25EF7304 */     addiu $t7, $t7, %lo(D_NF_00007304)
  /* 18254C 80134E4C 3C018014 */       lui $at, %hi(gCreditsNameInterpolation)
  /* 182550 80134E50 3C190000 */       lui $t9, %hi(D_NF_00007338)
  /* 182554 80134E54 004FC021 */      addu $t8, $v0, $t7
  /* 182558 80134E58 AC38A8E0 */        sw $t8, %lo(gCreditsNameInterpolation)($at)
  /* 18255C 80134E5C 27397338 */     addiu $t9, $t9, %lo(D_NF_00007338)
  /* 182560 80134E60 3C018014 */       lui $at, %hi(gCreditsNameATrack)
  /* 182564 80134E64 3C090000 */       lui $t1, %hi(D_NF_000078C0)
  /* 182568 80134E68 00594021 */      addu $t0, $v0, $t9
  /* 18256C 80134E6C AC28A8DC */        sw $t0, %lo(gCreditsNameATrack)($at)
  /* 182570 80134E70 252978C0 */     addiu $t1, $t1, %lo(D_NF_000078C0)
  /* 182574 80134E74 3C018014 */       lui $at, %hi(D_ovl59_8013A8E8)
  /* 182578 80134E78 00495021 */      addu $t2, $v0, $t1
  /* 18257C 80134E7C AC2AA8E8 */        sw $t2, %lo(D_ovl59_8013A8E8)($at)
  /* 182580 80134E80 3C0B800A */       lui $t3, %hi((gSceneData + 0x13))
  /* 182584 80134E84 916B4AE3 */       lbu $t3, %lo((gSceneData + 0x13))($t3)
  /* 182588 80134E88 3C018014 */       lui $at, %hi(gCreditsRollBeginWait)
  /* 18258C 80134E8C AC20A900 */        sw $zero, %lo(gCreditsRollBeginWait)($at)
  /* 182590 80134E90 3C018014 */       lui $at, %hi(gCreditsPlayer)
  /* 182594 80134E94 A02BA904 */        sb $t3, %lo(gCreditsPlayer)($at)
  /* 182598 80134E98 3C018014 */       lui $at, %hi(gCreditsRollEndWait)
  /* 18259C 80134E9C 240C003C */     addiu $t4, $zero, 0x3c
  /* 1825A0 80134EA0 03E00008 */        jr $ra
  /* 1825A4 80134EA4 AC2CA908 */        sw $t4, %lo(gCreditsRollEndWait)($at)

glabel func_ovl59_80134EA8
  /* 1825A8 80134EA8 3C013E80 */       lui $at, (0x3E800000 >> 16) # 0.25
  /* 1825AC 80134EAC 44810000 */      mtc1 $at, $f0 # 0.25 to cop1
  /* 1825B0 80134EB0 3C018014 */       lui $at, %hi(gCreditsCrosshairPositionX)
  /* 1825B4 80134EB4 C426A8D4 */      lwc1 $f6, %lo(gCreditsCrosshairPositionX)($at)
  /* 1825B8 80134EB8 8C820074 */        lw $v0, 0x74($a0)
  /* 1825BC 80134EBC 3C018014 */       lui $at, %hi(gCreditsCrosshairPositionY)
  /* 1825C0 80134EC0 46003202 */     mul.s $f8, $f6, $f0
  /* 1825C4 80134EC4 C4440048 */      lwc1 $f4, 0x48($v0)
  /* 1825C8 80134EC8 C450004C */      lwc1 $f16, 0x4c($v0)
  /* 1825CC 80134ECC 46082280 */     add.s $f10, $f4, $f8
  /* 1825D0 80134ED0 E44A0048 */      swc1 $f10, 0x48($v0)
  /* 1825D4 80134ED4 C432A8D8 */      lwc1 $f18, %lo(gCreditsCrosshairPositionY)($at)
  /* 1825D8 80134ED8 46009182 */     mul.s $f6, $f18, $f0
  /* 1825DC 80134EDC 46068101 */     sub.s $f4, $f16, $f6
  /* 1825E0 80134EE0 03E00008 */        jr $ra
  /* 1825E4 80134EE4 E444004C */      swc1 $f4, 0x4c($v0)

glabel func_ovl59_80134EE8
  /* 1825E8 80134EE8 27BDFFB8 */     addiu $sp, $sp, -0x48
  /* 1825EC 80134EEC 3C0E800D */       lui $t6, %hi(func_ovl0_800CD2CC)
  /* 1825F0 80134EF0 AFBF003C */        sw $ra, 0x3c($sp)
  /* 1825F4 80134EF4 25CED2CC */     addiu $t6, $t6, %lo(func_ovl0_800CD2CC)
  /* 1825F8 80134EF8 240F001E */     addiu $t7, $zero, 0x1e
  /* 1825FC 80134EFC 24180000 */     addiu $t8, $zero, 0
  /* 182600 80134F00 241900F0 */     addiu $t9, $zero, 0xf0
  /* 182604 80134F04 2408FFFF */     addiu $t0, $zero, -1
  /* 182608 80134F08 24090001 */     addiu $t1, $zero, 1
  /* 18260C 80134F0C 240A0001 */     addiu $t2, $zero, 1
  /* 182610 80134F10 AFAA0030 */        sw $t2, 0x30($sp)
  /* 182614 80134F14 AFA90028 */        sw $t1, 0x28($sp)
  /* 182618 80134F18 AFA80020 */        sw $t0, 0x20($sp)
  /* 18261C 80134F1C AFB9001C */        sw $t9, 0x1c($sp)
  /* 182620 80134F20 AFB80018 */        sw $t8, 0x18($sp)
  /* 182624 80134F24 AFAF0014 */        sw $t7, 0x14($sp)
  /* 182628 80134F28 AFAE0010 */        sw $t6, 0x10($sp)
  /* 18262C 80134F2C AFA00024 */        sw $zero, 0x24($sp)
  /* 182630 80134F30 AFA0002C */        sw $zero, 0x2c($sp)
  /* 182634 80134F34 AFA00034 */        sw $zero, 0x34($sp)
  /* 182638 80134F38 24040005 */     addiu $a0, $zero, 5
  /* 18263C 80134F3C 00002825 */        or $a1, $zero, $zero
  /* 182640 80134F40 2406000C */     addiu $a2, $zero, 0xc
  /* 182644 80134F44 0C002E4F */       jal func_8000B93C
  /* 182648 80134F48 3C078000 */       lui $a3, 0x8000
  /* 18264C 80134F4C 3C0141A0 */       lui $at, (0x41A00000 >> 16) # 20.0
  /* 182650 80134F50 44810000 */      mtc1 $at, $f0 # 20.0 to cop1
  /* 182654 80134F54 3C0143E6 */       lui $at, (0x43E60000 >> 16) # 460.0
  /* 182658 80134F58 8C430074 */        lw $v1, 0x74($v0)
  /* 18265C 80134F5C 44812000 */      mtc1 $at, $f4 # 460.0 to cop1
  /* 182660 80134F60 44050000 */      mfc1 $a1, $f0
  /* 182664 80134F64 44060000 */      mfc1 $a2, $f0
  /* 182668 80134F68 3C07441B */       lui $a3, 0x441b
  /* 18266C 80134F6C 24640008 */     addiu $a0, $v1, 8
  /* 182670 80134F70 0C001C20 */       jal func_80007080
  /* 182674 80134F74 E7A40010 */      swc1 $f4, 0x10($sp)
  /* 182678 80134F78 3C0B8001 */       lui $t3, %hi(func_80017EC0)
  /* 18267C 80134F7C 3C088013 */       lui $t0, %hi(func_ovl59_80134EA8)
  /* 182680 80134F80 25084EA8 */     addiu $t0, $t0, %lo(func_ovl59_80134EA8)
  /* 182684 80134F84 256B7EC0 */     addiu $t3, $t3, %lo(func_80017EC0)
  /* 182688 80134F88 240C0032 */     addiu $t4, $zero, 0x32
  /* 18268C 80134F8C 240E0000 */     addiu $t6, $zero, 0
  /* 182690 80134F90 240F030E */     addiu $t7, $zero, 0x30e
  /* 182694 80134F94 240DFFFF */     addiu $t5, $zero, -1
  /* 182698 80134F98 24180001 */     addiu $t8, $zero, 1
  /* 18269C 80134F9C 24190001 */     addiu $t9, $zero, 1
  /* 1826A0 80134FA0 24090001 */     addiu $t1, $zero, 1
  /* 1826A4 80134FA4 AFA90030 */        sw $t1, 0x30($sp)
  /* 1826A8 80134FA8 AFB90028 */        sw $t9, 0x28($sp)
  /* 1826AC 80134FAC AFB80024 */        sw $t8, 0x24($sp)
  /* 1826B0 80134FB0 AFAD0020 */        sw $t5, 0x20($sp)
  /* 1826B4 80134FB4 AFAF001C */        sw $t7, 0x1c($sp)
  /* 1826B8 80134FB8 AFAE0018 */        sw $t6, 0x18($sp)
  /* 1826BC 80134FBC AFAC0014 */        sw $t4, 0x14($sp)
  /* 1826C0 80134FC0 AFAB0010 */        sw $t3, 0x10($sp)
  /* 1826C4 80134FC4 AFA8002C */        sw $t0, 0x2c($sp)
  /* 1826C8 80134FC8 24040005 */     addiu $a0, $zero, 5
  /* 1826CC 80134FCC 00002825 */        or $a1, $zero, $zero
  /* 1826D0 80134FD0 2406000C */     addiu $a2, $zero, 0xc
  /* 1826D4 80134FD4 3C078000 */       lui $a3, 0x8000
  /* 1826D8 80134FD8 0C002E4F */       jal func_8000B93C
  /* 1826DC 80134FDC AFA00034 */        sw $zero, 0x34($sp)
  /* 1826E0 80134FE0 8C430074 */        lw $v1, 0x74($v0)
  /* 1826E4 80134FE4 3C0141A0 */       lui $at, (0x41A00000 >> 16) # 20.0
  /* 1826E8 80134FE8 44810000 */      mtc1 $at, $f0 # 20.0 to cop1
  /* 1826EC 80134FEC 3C018014 */       lui $at, %hi(gCreditsPerspective)
  /* 1826F0 80134FF0 AC23A8E4 */        sw $v1, %lo(gCreditsPerspective)($at)
  /* 1826F4 80134FF4 3C0143E6 */       lui $at, (0x43E60000 >> 16) # 460.0
  /* 1826F8 80134FF8 44813000 */      mtc1 $at, $f6 # 460.0 to cop1
  /* 1826FC 80134FFC 44050000 */      mfc1 $a1, $f0
  /* 182700 80135000 44060000 */      mfc1 $a2, $f0
  /* 182704 80135004 3C07441B */       lui $a3, 0x441b
  /* 182708 80135008 24640008 */     addiu $a0, $v1, 8
  /* 18270C 8013500C AFA30044 */        sw $v1, 0x44($sp)
  /* 182710 80135010 0C001C20 */       jal func_80007080
  /* 182714 80135014 E7A60010 */      swc1 $f6, 0x10($sp)
  /* 182718 80135018 8FA30044 */        lw $v1, 0x44($sp)
  /* 18271C 8013501C 44800000 */      mtc1 $zero, $f0
  /* 182720 80135020 3C014411 */       lui $at, (0x44110000 >> 16) # 580.0
  /* 182724 80135024 44814000 */      mtc1 $at, $f8 # 580.0 to cop1
  /* 182728 80135028 3C014248 */       lui $at, (0x42480000 >> 16) # 50.0
  /* 18272C 8013502C 44815000 */      mtc1 $at, $f10 # 50.0 to cop1
  /* 182730 80135030 E4600050 */      swc1 $f0, 0x50($v1)
  /* 182734 80135034 E460004C */      swc1 $f0, 0x4c($v1)
  /* 182738 80135038 E4600048 */      swc1 $f0, 0x48($v1)
  /* 18273C 8013503C E4600040 */      swc1 $f0, 0x40($v1)
  /* 182740 80135040 E460003C */      swc1 $f0, 0x3c($v1)
  /* 182744 80135044 E4680044 */      swc1 $f8, 0x44($v1)
  /* 182748 80135048 E46A0020 */      swc1 $f10, 0x20($v1)
  /* 18274C 8013504C 8FBF003C */        lw $ra, 0x3c($sp)
  /* 182750 80135050 27BD0048 */     addiu $sp, $sp, 0x48
  /* 182754 80135054 03E00008 */        jr $ra
  /* 182758 80135058 00000000 */       nop 

glabel func_ovl59_8013505C
  /* 18275C 8013505C 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 182760 80135060 AFBF001C */        sw $ra, 0x1c($sp)
  /* 182764 80135064 3C058013 */       lui $a1, %hi(func_ovl59_801334E4)
  /* 182768 80135068 24A534E4 */     addiu $a1, $a1, %lo(func_ovl59_801334E4)
  /* 18276C 8013506C 00002025 */        or $a0, $zero, $zero
  /* 182770 80135070 24060001 */     addiu $a2, $zero, 1
  /* 182774 80135074 0C00265A */       jal omMakeGObjCommon
  /* 182778 80135078 3C078000 */       lui $a3, 0x8000
  /* 18277C 8013507C 240E00FF */     addiu $t6, $zero, 0xff
  /* 182780 80135080 AFAE0010 */        sw $t6, 0x10($sp)
  /* 182784 80135084 2404000C */     addiu $a0, $zero, 0xc
  /* 182788 80135088 3C058000 */       lui $a1, 0x8000
  /* 18278C 8013508C 24060064 */     addiu $a2, $zero, 0x64
  /* 182790 80135090 0C002E7F */       jal func_8000B9FC
  /* 182794 80135094 24070002 */     addiu $a3, $zero, 2
  /* 182798 80135098 0C04D277 */       jal func_ovl59_801349DC
  /* 18279C 8013509C 00000000 */       nop 
  /* 1827A0 801350A0 0C04D29C */       jal func_ovl59_80134A70
  /* 1827A4 801350A4 00000000 */       nop 
  /* 1827A8 801350A8 0C04CA56 */       jal func_ovl59_80132958
  /* 1827AC 801350AC 00000000 */       nop 
  /* 1827B0 801350B0 0C04D382 */       jal func_ovl59_80134E08
  /* 1827B4 801350B4 00000000 */       nop 
  /* 1827B8 801350B8 0C04D17F */       jal gmCreditsMakeCrosshairGObj
  /* 1827BC 801350BC 00000000 */       nop 
  /* 1827C0 801350C0 0C04D263 */       jal gmCreditsMakeStaffRollGObj
  /* 1827C4 801350C4 00000000 */       nop 
  /* 1827C8 801350C8 0C04D3BA */       jal func_ovl59_80134EE8
  /* 1827CC 801350CC 00000000 */       nop 
  /* 1827D0 801350D0 0C00829D */       jal func_80020A74
  /* 1827D4 801350D4 00000000 */       nop 
  /* 1827D8 801350D8 00002025 */        or $a0, $zero, $zero
  /* 1827DC 801350DC 0C0082AD */       jal func_80020AB4
  /* 1827E0 801350E0 24050027 */     addiu $a1, $zero, 0x27
  /* 1827E4 801350E4 8FBF001C */        lw $ra, 0x1c($sp)
  /* 1827E8 801350E8 27BD0020 */     addiu $sp, $sp, 0x20
  /* 1827EC 801350EC 03E00008 */        jr $ra
  /* 1827F0 801350F0 00000000 */       nop 

glabel func_ovl59_801350F4
  /* 1827F4 801350F4 8C830000 */        lw $v1, ($a0)
  /* 1827F8 801350F8 3C188014 */       lui $t8, %hi(D_ovl59_8013A6E0)
  /* 1827FC 801350FC 2718A6E0 */     addiu $t8, $t8, %lo(D_ovl59_8013A6E0)
  /* 182800 80135100 246E0008 */     addiu $t6, $v1, 8
  /* 182804 80135104 AC8E0000 */        sw $t6, ($a0)
  /* 182808 80135108 3C0FDE00 */       lui $t7, 0xde00
  /* 18280C 8013510C AC6F0000 */        sw $t7, ($v1)
  /* 182810 80135110 03E00008 */        jr $ra
  /* 182814 80135114 AC780004 */        sw $t8, 4($v1)

glabel func_ovl59_80135118
  /* 182818 80135118 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 18281C 8013511C AFBF0014 */        sw $ra, 0x14($sp)
  /* 182820 80135120 0C0028D0 */       jal func_8000A340
  /* 182824 80135124 00000000 */       nop 
  /* 182828 80135128 3C048014 */       lui $a0, %hi(gCreditsRollEndWait)
  /* 18282C 8013512C 2484A908 */     addiu $a0, $a0, %lo(gCreditsRollEndWait)
  /* 182830 80135130 8C820000 */        lw $v0, ($a0) # gCreditsRollEndWait + 0
  /* 182834 80135134 3C038014 */       lui $v1, %hi(gCreditsStatus)
  /* 182838 80135138 1040000A */      beqz $v0, .L80135164
  /* 18283C 8013513C 00000000 */       nop 
  /* 182840 80135140 8C63A8C0 */        lw $v1, %lo(gCreditsStatus)($v1)
  /* 182844 80135144 2401FFFF */     addiu $at, $zero, -1
  /* 182848 80135148 244EFFFF */     addiu $t6, $v0, -1
  /* 18284C 8013514C 10610003 */       beq $v1, $at, .L8013515C
  /* 182850 80135150 2401FFFE */     addiu $at, $zero, -2
  /* 182854 80135154 14610003 */       bne $v1, $at, .L80135164
  /* 182858 80135158 00000000 */       nop 
  .L8013515C:
  /* 18285C 8013515C AC8E0000 */        sw $t6, ($a0) # gCreditsRollEndWait + 0
  /* 182860 80135160 01C01025 */        or $v0, $t6, $zero
  .L80135164:
  /* 182864 80135164 14400003 */      bnez $v0, .L80135174
  /* 182868 80135168 00000000 */       nop 
  /* 18286C 8013516C 0C00171D */       jal func_80005C74
  /* 182870 80135170 00000000 */       nop 
  .L80135174:
  /* 182874 80135174 3C0F8014 */       lui $t7, %hi(gCreditsStatus)
  /* 182878 80135178 8DEFA8C0 */        lw $t7, %lo(gCreditsStatus)($t7)
  /* 18287C 8013517C 2401FFFF */     addiu $at, $zero, -1
  /* 182880 80135180 2418001B */     addiu $t8, $zero, 0x1b
  /* 182884 80135184 15E10008 */       bne $t7, $at, .L801351A8
  /* 182888 80135188 3C01800A */       lui $at, %hi(gSceneData)
  /* 18288C 8013518C 0C00829D */       jal func_80020A74
  /* 182890 80135190 A0384AD0 */        sb $t8, %lo(gSceneData)($at)
  /* 182894 80135194 0C001B86 */       jal func_80006E18
  /* 182898 80135198 24040100 */     addiu $a0, $zero, 0x100
  /* 18289C 8013519C 2419FFFE */     addiu $t9, $zero, -2
  /* 1828A0 801351A0 3C018014 */       lui $at, %hi(gCreditsStatus)
  /* 1828A4 801351A4 AC39A8C0 */        sw $t9, %lo(gCreditsStatus)($at)
  .L801351A8:
  /* 1828A8 801351A8 8FBF0014 */        lw $ra, 0x14($sp)
  /* 1828AC 801351AC 27BD0018 */     addiu $sp, $sp, 0x18
  /* 1828B0 801351B0 03E00008 */        jr $ra
  /* 1828B4 801351B4 00000000 */       nop 

glabel overlay_set56_entry
  /* 1828B8 801351B8 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 1828BC 801351BC 3C028023 */       lui $v0, (0x8023E000 >> 16) # 2149834752
  /* 1828C0 801351C0 AFBF0014 */        sw $ra, 0x14($sp)
  /* 1828C4 801351C4 3442E000 */       ori $v0, $v0, (0x8023E000 & 0xFFFF) # 2149834752
  /* 1828C8 801351C8 3C058040 */       lui $a1, 0x8040
  .L801351CC:
  /* 1828CC 801351CC 24420010 */     addiu $v0, $v0, 0x10
  /* 1828D0 801351D0 AC40FFF0 */        sw $zero, -0x10($v0) # D_NF_8023E000 + -16
  /* 1828D4 801351D4 AC40FFF4 */        sw $zero, -0xc($v0) # D_NF_8023E000 + -12
  /* 1828D8 801351D8 AC40FFF8 */        sw $zero, -8($v0) # D_NF_8023E000 + -8
  /* 1828DC 801351DC 1445FFFB */       bne $v0, $a1, .L801351CC
  /* 1828E0 801351E0 AC40FFFC */        sw $zero, -4($v0) # D_NF_8023E000 + -4
  /* 1828E4 801351E4 3C0E800A */       lui $t6, %hi(D_NF_800A5240)
  /* 1828E8 801351E8 3C048014 */       lui $a0, %hi(D_ovl59_8013A708)
  /* 1828EC 801351EC 25CE5240 */     addiu $t6, $t6, %lo(D_NF_800A5240)
  /* 1828F0 801351F0 2484A708 */     addiu $a0, $a0, %lo(D_ovl59_8013A708)
  /* 1828F4 801351F4 25CFCE00 */     addiu $t7, $t6, -0x3200
  /* 1828F8 801351F8 0C001C09 */       jal func_80007024
  /* 1828FC 801351FC AC8F000C */        sw $t7, 0xc($a0) # D_ovl59_8013A708 + 12
  /* 182900 80135200 3C188023 */       lui $t8, (0x8023E000 >> 16) # 2149834752
  /* 182904 80135204 3C198014 */       lui $t9, %hi(D_NF_8013AA60)
  /* 182908 80135208 3C048014 */       lui $a0, %hi(D_ovl59_8013A724)
  /* 18290C 8013520C 2739AA60 */     addiu $t9, $t9, %lo(D_NF_8013AA60)
  /* 182910 80135210 3718E000 */       ori $t8, $t8, (0x8023E000 & 0xFFFF) # 2149834752
  /* 182914 80135214 2484A724 */     addiu $a0, $a0, %lo(D_ovl59_8013A724)
  /* 182918 80135218 03194023 */      subu $t0, $t8, $t9
  /* 18291C 8013521C 0C001A0F */       jal func_8000683C
  /* 182920 80135220 AC880010 */        sw $t0, 0x10($a0) # D_ovl59_8013A724 + 16
  /* 182924 80135224 3C038039 */       lui $v1, 0x8039
  /* 182928 80135228 24622A00 */     addiu $v0, $v1, 0x2a00
  /* 18292C 8013522C 3C058040 */       lui $a1, 0x8040
  /* 182930 80135230 0045082B */      sltu $at, $v0, $a1
  /* 182934 80135234 10200005 */      beqz $at, .L8013524C
  /* 182938 80135238 24030001 */     addiu $v1, $zero, 1
  .L8013523C:
  /* 18293C 8013523C 24420002 */     addiu $v0, $v0, 2
  /* 182940 80135240 0045082B */      sltu $at, $v0, $a1
  /* 182944 80135244 1420FFFD */      bnez $at, .L8013523C
  /* 182948 80135248 A443FFFE */        sh $v1, -2($v0)
  .L8013524C:
  /* 18294C 8013524C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 182950 80135250 27BD0018 */     addiu $sp, $sp, 0x18
  /* 182954 80135254 03E00008 */        jr $ra
  /* 182958 80135258 00000000 */       nop 

  /* 18295C 8013525C 00000000 */       nop 

# Likely start of new file
#glabel dCreditsNameCharacters   # Routine parsed as data
#  /* 182960 80135260 0000000C */   syscall 
#  /* 182964 80135264 0000001A */       div $zero, $zero, $zero
#  /* 182968 80135268 0000002C */      dadd $zero, $zero, $zero
#  /* 18296C 8013526C 0000001A */       div $zero, $zero, $zero
#  /* 182970 80135270 00000021 */      addu $zero, $zero, $zero
#  /* 182974 80135274 00000022 */       neg $zero, $zero
#  /* 182978 80135278 0000002B */      sltu $zero, $zero, $zero
