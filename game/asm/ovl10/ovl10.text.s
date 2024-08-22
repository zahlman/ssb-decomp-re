.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section .text

.align 4

# Text Sections
#  0x80131B00 -> 0x801341E0

glabel mnTitleGetUnlockedCharsCountForMask
  /* 117180 80131B00 AFA40000 */        sw $a0, ($sp)
  /* 117184 80131B04 3084FFFF */      andi $a0, $a0, 0xffff
  /* 117188 80131B08 00001025 */        or $v0, $zero, $zero
  /* 11718C 80131B0C 00001825 */        or $v1, $zero, $zero
  /* 117190 80131B10 24060010 */     addiu $a2, $zero, 0x10
  .L80131B14:
  /* 117194 80131B14 308E0001 */      andi $t6, $a0, 1
  /* 117198 80131B18 11C00002 */      beqz $t6, .L80131B24
  /* 11719C 80131B1C 00802825 */        or $a1, $a0, $zero
  /* 1171A0 80131B20 24630001 */     addiu $v1, $v1, 1
  .L80131B24:
  /* 1171A4 80131B24 00052043 */       sra $a0, $a1, 1
  /* 1171A8 80131B28 3085FFFF */      andi $a1, $a0, 0xffff
  /* 1171AC 80131B2C 30AF0001 */      andi $t7, $a1, 1
  /* 1171B0 80131B30 11E00002 */      beqz $t7, .L80131B3C
  /* 1171B4 80131B34 00052043 */       sra $a0, $a1, 1
  /* 1171B8 80131B38 24630001 */     addiu $v1, $v1, 1
  .L80131B3C:
  /* 1171BC 80131B3C 3085FFFF */      andi $a1, $a0, 0xffff
  /* 1171C0 80131B40 30B80001 */      andi $t8, $a1, 1
  /* 1171C4 80131B44 13000002 */      beqz $t8, .L80131B50
  /* 1171C8 80131B48 00052043 */       sra $a0, $a1, 1
  /* 1171CC 80131B4C 24630001 */     addiu $v1, $v1, 1
  .L80131B50:
  /* 1171D0 80131B50 3085FFFF */      andi $a1, $a0, 0xffff
  /* 1171D4 80131B54 30B90001 */      andi $t9, $a1, 1
  /* 1171D8 80131B58 13200002 */      beqz $t9, .L80131B64
  /* 1171DC 80131B5C 24420004 */     addiu $v0, $v0, 4
  /* 1171E0 80131B60 24630001 */     addiu $v1, $v1, 1
  .L80131B64:
  /* 1171E4 80131B64 00052043 */       sra $a0, $a1, 1
  /* 1171E8 80131B68 1446FFEA */       bne $v0, $a2, .L80131B14
  /* 1171EC 80131B6C 3084FFFF */      andi $a0, $a0, 0xffff
  /* 1171F0 80131B70 03E00008 */        jr $ra
  /* 1171F4 80131B74 00601025 */        or $v0, $v1, $zero

glabel mnTitleGetMissingFtKind
  /* 1171F8 80131B78 AFA50004 */        sw $a1, 4($sp)
  /* 1171FC 80131B7C 30A5FFFF */      andi $a1, $a1, 0xffff
  /* 117200 80131B80 AFA40000 */        sw $a0, ($sp)
  /* 117204 80131B84 3082FFFF */      andi $v0, $a0, 0xffff
  /* 117208 80131B88 2403FFFF */     addiu $v1, $zero, -1
  /* 11720C 80131B8C 24C60001 */     addiu $a2, $a2, 1
  /* 117210 80131B90 24630001 */     addiu $v1, $v1, 1
  .L80131B94:
  /* 117214 80131B94 240E0001 */     addiu $t6, $zero, 1
  /* 117218 80131B98 006E2004 */      sllv $a0, $t6, $v1
  /* 11721C 80131B9C 00447824 */       and $t7, $v0, $a0
  /* 117220 80131BA0 11E00004 */      beqz $t7, .L80131BB4
  /* 117224 80131BA4 00A4C024 */       and $t8, $a1, $a0
  /* 117228 80131BA8 17000002 */      bnez $t8, .L80131BB4
  /* 11722C 80131BAC 00000000 */       nop
  /* 117230 80131BB0 24C6FFFF */     addiu $a2, $a2, -1
  .L80131BB4:
  /* 117234 80131BB4 54C0FFF7 */      bnel $a2, $zero, .L80131B94
  /* 117238 80131BB8 24630001 */     addiu $v1, $v1, 1
  /* 11723C 80131BBC 03E00008 */        jr $ra
  /* 117240 80131BC0 00601025 */        or $v0, $v1, $zero

glabel mnTitleSetDemoFtKinds
  /* 117244 80131BC4 27BDFFD8 */     addiu $sp, $sp, -0x28
  /* 117248 80131BC8 AFB20020 */        sw $s2, 0x20($sp)
  /* 11724C 80131BCC 3C12800A */       lui $s2, %hi((gSaveData + 0x458))
  /* 117250 80131BD0 96524938 */       lhu $s2, %lo((gSaveData + 0x458))($s2)
  /* 117254 80131BD4 AFB00018 */        sw $s0, 0x18($sp)
  /* 117258 80131BD8 3C10800A */       lui $s0, %hi(gSceneData)
  /* 11725C 80131BDC 26104AD0 */     addiu $s0, $s0, %lo(gSceneData)
  /* 117260 80131BE0 960F000A */       lhu $t7, 0xa($s0) # gSceneData + 10
  /* 117264 80131BE4 3652036F */       ori $s2, $s2, 0x36f
  /* 117268 80131BE8 3252FFFF */      andi $s2, $s2, 0xffff
  /* 11726C 80131BEC 02407027 */       not $t6, $s2
  /* 117270 80131BF0 01CFC024 */       and $t8, $t6, $t7
  /* 117274 80131BF4 AFBF0024 */        sw $ra, 0x24($sp)
  /* 117278 80131BF8 13000002 */      beqz $t8, .L80131C04
  /* 11727C 80131BFC AFB1001C */        sw $s1, 0x1c($sp)
  /* 117280 80131C00 A600000A */        sh $zero, 0xa($s0) # gSceneData + 10
  .L80131C04:
  /* 117284 80131C04 0C04C6C0 */       jal mnTitleGetUnlockedCharsCountForMask
  /* 117288 80131C08 3244FFFF */      andi $a0, $s2, 0xffff
  /* 11728C 80131C0C 00408825 */        or $s1, $v0, $zero
  /* 117290 80131C10 0C04C6C0 */       jal mnTitleGetUnlockedCharsCountForMask
  /* 117294 80131C14 9604000A */       lhu $a0, 0xa($s0) # gSceneData + 10
  /* 117298 80131C18 0051082A */       slt $at, $v0, $s1
  /* 11729C 80131C1C 14200002 */      bnez $at, .L80131C28
  /* 1172A0 80131C20 00000000 */       nop
  /* 1172A4 80131C24 A600000A */        sh $zero, 0xa($s0) # gSceneData + 10
  .L80131C28:
  /* 1172A8 80131C28 0C04C6C0 */       jal mnTitleGetUnlockedCharsCountForMask
  /* 1172AC 80131C2C 3244FFFF */      andi $a0, $s2, 0xffff
  /* 1172B0 80131C30 00408825 */        or $s1, $v0, $zero
  /* 1172B4 80131C34 0C04C6C0 */       jal mnTitleGetUnlockedCharsCountForMask
  /* 1172B8 80131C38 9604000A */       lhu $a0, 0xa($s0) # gSceneData + 10
  /* 1172BC 80131C3C 0C006265 */       jal lbRandom_GetIntRange
  /* 1172C0 80131C40 02222023 */      subu $a0, $s1, $v0
  /* 1172C4 80131C44 3244FFFF */      andi $a0, $s2, 0xffff
  /* 1172C8 80131C48 9605000A */       lhu $a1, 0xa($s0) # gSceneData + 10
  /* 1172CC 80131C4C 0C04C6DE */       jal mnTitleGetMissingFtKind
  /* 1172D0 80131C50 00403025 */        or $a2, $v0, $zero
  /* 1172D4 80131C54 9603000A */       lhu $v1, 0xa($s0) # gSceneData + 10
  /* 1172D8 80131C58 A202000D */        sb $v0, 0xd($s0) # gSceneData + 13
  /* 1172DC 80131C5C 54600003 */      bnel $v1, $zero, .L80131C6C
  /* 1172E0 80131C60 9208000D */       lbu $t0, 0xd($s0) # gSceneData + 13
  /* 1172E4 80131C64 A202000C */        sb $v0, 0xc($s0) # gSceneData + 12
  /* 1172E8 80131C68 9208000D */       lbu $t0, 0xd($s0) # gSceneData + 13
  .L80131C6C:
  /* 1172EC 80131C6C 24090001 */     addiu $t1, $zero, 1
  /* 1172F0 80131C70 3244FFFF */      andi $a0, $s2, 0xffff
  /* 1172F4 80131C74 01095004 */      sllv $t2, $t1, $t0
  /* 1172F8 80131C78 006A5825 */        or $t3, $v1, $t2
  /* 1172FC 80131C7C 0C04C6C0 */       jal mnTitleGetUnlockedCharsCountForMask
  /* 117300 80131C80 A60B000A */        sh $t3, 0xa($s0) # gSceneData + 10
  /* 117304 80131C84 00408825 */        or $s1, $v0, $zero
  /* 117308 80131C88 0C04C6C0 */       jal mnTitleGetUnlockedCharsCountForMask
  /* 11730C 80131C8C 9604000A */       lhu $a0, 0xa($s0) # gSceneData + 10
  /* 117310 80131C90 02222023 */      subu $a0, $s1, $v0
  /* 117314 80131C94 14800004 */      bnez $a0, .L80131CA8
  /* 117318 80131C98 00000000 */       nop
  /* 11731C 80131C9C 920C000C */       lbu $t4, 0xc($s0) # gSceneData + 12
  /* 117320 80131CA0 1000000E */         b .L80131CDC
  /* 117324 80131CA4 A20C000E */        sb $t4, 0xe($s0) # gSceneData + 14
  .L80131CA8:
  /* 117328 80131CA8 0C006265 */       jal lbRandom_GetIntRange
  /* 11732C 80131CAC 00000000 */       nop
  /* 117330 80131CB0 3244FFFF */      andi $a0, $s2, 0xffff
  /* 117334 80131CB4 9605000A */       lhu $a1, 0xa($s0) # gSceneData + 10
  /* 117338 80131CB8 0C04C6DE */       jal mnTitleGetMissingFtKind
  /* 11733C 80131CBC 00403025 */        or $a2, $v0, $zero
  /* 117340 80131CC0 960D000A */       lhu $t5, 0xa($s0) # gSceneData + 10
  /* 117344 80131CC4 304E00FF */      andi $t6, $v0, 0xff
  /* 117348 80131CC8 240F0001 */     addiu $t7, $zero, 1
  /* 11734C 80131CCC 01CFC004 */      sllv $t8, $t7, $t6
  /* 117350 80131CD0 01B8C825 */        or $t9, $t5, $t8
  /* 117354 80131CD4 A202000E */        sb $v0, 0xe($s0) # gSceneData + 14
  /* 117358 80131CD8 A619000A */        sh $t9, 0xa($s0) # gSceneData + 10
  .L80131CDC:
  /* 11735C 80131CDC 8FBF0024 */        lw $ra, 0x24($sp)
  /* 117360 80131CE0 8FB00018 */        lw $s0, 0x18($sp)
  /* 117364 80131CE4 8FB1001C */        lw $s1, 0x1c($sp)
  /* 117368 80131CE8 8FB20020 */        lw $s2, 0x20($sp)
  /* 11736C 80131CEC 03E00008 */        jr $ra
  /* 117370 80131CF0 27BD0028 */     addiu $sp, $sp, 0x28

glabel mnTitleInitVars
  /* 117374 80131CF4 3C0E800A */       lui $t6, %hi((gSceneData + 0x1))
  /* 117378 80131CF8 91CE4AD1 */       lbu $t6, %lo((gSceneData + 0x1))($t6)
  /* 11737C 80131CFC 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 117380 80131D00 2401002E */     addiu $at, $zero, 0x2e
  /* 117384 80131D04 15C10011 */       bne $t6, $at, .L80131D4C
  /* 117388 80131D08 AFBF0014 */        sw $ra, 0x14($sp)
  /* 11738C 80131D0C 3C018013 */       lui $at, %hi(gMNTitleLayout)
  /* 117390 80131D10 44800000 */      mtc1 $zero, $f0
  /* 117394 80131D14 AC204450 */        sw $zero, %lo(gMNTitleLayout)($at)
  /* 117398 80131D18 3C038013 */       lui $v1, %hi(gMNTitleFireBGOverlayBlue)
  /* 11739C 80131D1C 3C018013 */       lui $at, %hi(gMNTitleTransitionFramesElapsed)
  /* 1173A0 80131D20 24634484 */     addiu $v1, $v1, %lo(gMNTitleFireBGOverlayBlue)
  /* 1173A4 80131D24 AC20445C */        sw $zero, %lo(gMNTitleTransitionFramesElapsed)($at)
  /* 1173A8 80131D28 E4600000 */      swc1 $f0, ($v1) # gMNTitleFireBGOverlayBlue + 0
  /* 1173AC 80131D2C C4640000 */      lwc1 $f4, ($v1) # gMNTitleFireBGOverlayBlue + 0
  /* 1173B0 80131D30 3C048013 */       lui $a0, %hi(gMNTitleFireBGOverlayGreen)
  /* 1173B4 80131D34 24844480 */     addiu $a0, $a0, %lo(gMNTitleFireBGOverlayGreen)
  /* 1173B8 80131D38 E4840000 */      swc1 $f4, ($a0) # gMNTitleFireBGOverlayGreen + 0
  /* 1173BC 80131D3C C4860000 */      lwc1 $f6, ($a0) # gMNTitleFireBGOverlayGreen + 0
  /* 1173C0 80131D40 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayRed)
  /* 1173C4 80131D44 10000036 */         b .L80131E20
  /* 1173C8 80131D48 E426447C */      swc1 $f6, %lo(gMNTitleFireBGOverlayRed)($at)
  .L80131D4C:
  /* 1173CC 80131D4C 0C00829D */       jal func_80020A74
  /* 1173D0 80131D50 00000000 */       nop
  /* 1173D4 80131D54 0C0099A8 */       jal func_800266A0
  /* 1173D8 80131D58 00000000 */       nop
  /* 1173DC 80131D5C 240F0001 */     addiu $t7, $zero, 1
  /* 1173E0 80131D60 3C018013 */       lui $at, %hi(gMNTitleLayout)
  /* 1173E4 80131D64 AC2F4450 */        sw $t7, %lo(gMNTitleLayout)($at)
  /* 1173E8 80131D68 3C018013 */       lui $at, %hi(gMNTitleTransitionFramesElapsed)
  /* 1173EC 80131D6C 241800A9 */     addiu $t8, $zero, 0xa9
  /* 1173F0 80131D70 AC38445C */        sw $t8, %lo(gMNTitleTransitionFramesElapsed)($at)
  /* 1173F4 80131D74 0C00628C */       jal lbRandom_GetTimeByteRange
  /* 1173F8 80131D78 24040007 */     addiu $a0, $zero, 7
  /* 1173FC 80131D7C 3C198013 */       lui $t9, %hi(dMNTitleFireBGOverlayColorArrayRed)
  /* 117400 80131D80 0322C821 */      addu $t9, $t9, $v0
  /* 117404 80131D84 93394318 */       lbu $t9, %lo(dMNTitleFireBGOverlayColorArrayRed)($t9)
  /* 117408 80131D88 3C038013 */       lui $v1, %hi(gMNTitleFireBGOverlayBlue)
  /* 11740C 80131D8C 3C048013 */       lui $a0, %hi(gMNTitleFireBGOverlayGreen)
  /* 117410 80131D90 44994000 */      mtc1 $t9, $f8
  /* 117414 80131D94 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayIndex)
  /* 117418 80131D98 24844480 */     addiu $a0, $a0, %lo(gMNTitleFireBGOverlayGreen)
  /* 11741C 80131D9C 24634484 */     addiu $v1, $v1, %lo(gMNTitleFireBGOverlayBlue)
  /* 117420 80131DA0 AC224494 */        sw $v0, %lo(gMNTitleFireBGOverlayIndex)($at)
  /* 117424 80131DA4 07210005 */      bgez $t9, .L80131DBC
  /* 117428 80131DA8 468042A0 */   cvt.s.w $f10, $f8
  /* 11742C 80131DAC 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 117430 80131DB0 44818000 */      mtc1 $at, $f16 # 4294967300.0 to cop1
  /* 117434 80131DB4 00000000 */       nop
  /* 117438 80131DB8 46105280 */     add.s $f10, $f10, $f16
  .L80131DBC:
  /* 11743C 80131DBC 3C088013 */       lui $t0, %hi(dMNTitleFireBGOverlayColorArrayGreen)
  /* 117440 80131DC0 01024021 */      addu $t0, $t0, $v0
  /* 117444 80131DC4 91084320 */       lbu $t0, %lo(dMNTitleFireBGOverlayColorArrayGreen)($t0)
  /* 117448 80131DC8 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayRed)
  /* 11744C 80131DCC E42A447C */      swc1 $f10, %lo(gMNTitleFireBGOverlayRed)($at)
  /* 117450 80131DD0 44889000 */      mtc1 $t0, $f18
  /* 117454 80131DD4 3C098013 */       lui $t1, %hi(dMNTitleFireBGOverlayColorArrayBlue)
  /* 117458 80131DD8 05010005 */      bgez $t0, .L80131DF0
  /* 11745C 80131DDC 46809120 */   cvt.s.w $f4, $f18
  /* 117460 80131DE0 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 117464 80131DE4 44813000 */      mtc1 $at, $f6 # 4294967300.0 to cop1
  /* 117468 80131DE8 00000000 */       nop
  /* 11746C 80131DEC 46062100 */     add.s $f4, $f4, $f6
  .L80131DF0:
  /* 117470 80131DF0 E4840000 */      swc1 $f4, ($a0) # gMNTitleFireBGOverlayGreen + 0
  /* 117474 80131DF4 01224821 */      addu $t1, $t1, $v0
  /* 117478 80131DF8 91294328 */       lbu $t1, %lo(dMNTitleFireBGOverlayColorArrayBlue)($t1)
  /* 11747C 80131DFC 44800000 */      mtc1 $zero, $f0
  /* 117480 80131E00 44894000 */      mtc1 $t1, $f8
  /* 117484 80131E04 05210005 */      bgez $t1, .L80131E1C
  /* 117488 80131E08 46804420 */   cvt.s.w $f16, $f8
  /* 11748C 80131E0C 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 117490 80131E10 44815000 */      mtc1 $at, $f10 # 4294967300.0 to cop1
  /* 117494 80131E14 00000000 */       nop
  /* 117498 80131E18 460A8400 */     add.s $f16, $f16, $f10
  .L80131E1C:
  /* 11749C 80131E1C E4700000 */      swc1 $f16, ($v1) # gMNTitleFireBGOverlayBlue + 0
  .L80131E20:
  /* 1174A0 80131E20 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayTimer)
  /* 1174A4 80131E24 AC204478 */        sw $zero, %lo(gMNTitleFireBGOverlayTimer)($at)
  /* 1174A8 80131E28 3C018013 */       lui $at, %hi(gMNTitleChangeSceneInterrupt)
  /* 1174AC 80131E2C AC204470 */        sw $zero, %lo(gMNTitleChangeSceneInterrupt)($at)
  /* 1174B0 80131E30 3C018013 */       lui $at, %hi(gMNTitleChangeSceneTimer)
  /* 1174B4 80131E34 240A0003 */     addiu $t2, $zero, 3
  /* 1174B8 80131E38 AC2A4474 */        sw $t2, %lo(gMNTitleChangeSceneTimer)($at)
  /* 1174BC 80131E3C 3C018013 */       lui $at, %hi(gMNTitleEnableMain)
  /* 1174C0 80131E40 AC204460 */        sw $zero, %lo(gMNTitleEnableMain)($at)
  /* 1174C4 80131E44 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaRed)
  /* 1174C8 80131E48 E4204488 */      swc1 $f0, %lo(gMNTitleFireBGOverlayDeltaRed)($at)
  /* 1174CC 80131E4C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 1174D0 80131E50 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaGreen)
  /* 1174D4 80131E54 E420448C */      swc1 $f0, %lo(gMNTitleFireBGOverlayDeltaGreen)($at)
  /* 1174D8 80131E58 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaBlue)
  /* 1174DC 80131E5C E4204490 */      swc1 $f0, %lo(gMNTitleFireBGOverlayDeltaBlue)($at)
  /* 1174E0 80131E60 03E00008 */        jr $ra
  /* 1174E4 80131E64 27BD0018 */     addiu $sp, $sp, 0x18

glabel mnTitleSetFinalLogoPosition
  /* 1174E8 80131E68 3C0E800A */       lui $t6, %hi((gSceneData + 0x1))
  /* 1174EC 80131E6C 91CE4AD1 */       lbu $t6, %lo((gSceneData + 0x1))($t6)
  /* 1174F0 80131E70 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 1174F4 80131E74 3C078004 */       lui $a3, %hi(gOMObjCommonLinks + (0x0A * 4))
  /* 1174F8 80131E78 2401002E */     addiu $at, $zero, 0x2e
  /* 1174FC 80131E7C AFBF0014 */        sw $ra, 0x14($sp)
  /* 117500 80131E80 15C10005 */       bne $t6, $at, .L80131E98
  /* 117504 80131E84 8CE76718 */        lw $a3, %lo(gOMObjCommonLinks + (0x0A * 4))($a3)
  /* 117508 80131E88 00E02025 */        or $a0, $a3, $zero
  /* 11750C 80131E8C 0C002CE7 */       jal func_8000B39C
  /* 117510 80131E90 AFA7001C */        sw $a3, 0x1c($sp)
  /* 117514 80131E94 8FA7001C */        lw $a3, 0x1c($sp)
  .L80131E98:
  /* 117518 80131E98 8CE50074 */        lw $a1, 0x74($a3)
  /* 11751C 80131E9C 00002025 */        or $a0, $zero, $zero
  /* 117520 80131EA0 24060008 */     addiu $a2, $zero, 8
  /* 117524 80131EA4 0C04C9D9 */       jal mnTitleSetPosition
  /* 117528 80131EA8 AFA50018 */        sw $a1, 0x18($sp)
  /* 11752C 80131EAC 8FA50018 */        lw $a1, 0x18($sp)
  /* 117530 80131EB0 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 117534 80131EB4 44810000 */      mtc1 $at, $f0 # 1.0 to cop1
  /* 117538 80131EB8 240F00FF */     addiu $t7, $zero, 0xff
  /* 11753C 80131EBC 3C018013 */       lui $at, %hi(gMNTitleLogoAlpha)
  /* 117540 80131EC0 2418004C */     addiu $t8, $zero, 0x4c
  /* 117544 80131EC4 ACAF0054 */        sw $t7, 0x54($a1)
  /* 117548 80131EC8 AC38446C */        sw $t8, %lo(gMNTitleLogoAlpha)($at)
  /* 11754C 80131ECC E4A00018 */      swc1 $f0, 0x18($a1)
  /* 117550 80131ED0 E4A0001C */      swc1 $f0, 0x1c($a1)
  /* 117554 80131ED4 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117558 80131ED8 27BD0020 */     addiu $sp, $sp, 0x20
  /* 11755C 80131EDC 03E00008 */        jr $ra
  /* 117560 80131EE0 00000000 */       nop

glabel mnTitleSetFinalLayout
  /* 117564 80131EE4 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 117568 80131EE8 AFB0001C */        sw $s0, 0x1c($sp)
  /* 11756C 80131EEC 3C108004 */       lui $s0, %hi(gOMObjCommonLinks + (0x06 * 4))
  /* 117570 80131EF0 8E106708 */        lw $s0, %lo(gOMObjCommonLinks + (0x06 * 4))($s0)
  /* 117574 80131EF4 AFBF0024 */        sw $ra, 0x24($sp)
  /* 117578 80131EF8 AFB10020 */        sw $s1, 0x20($sp)
  /* 11757C 80131EFC 1200000A */      beqz $s0, .L80131F28
  /* 117580 80131F00 F7B40010 */      sdc1 $f20, 0x10($sp)
  /* 117584 80131F04 24110005 */     addiu $s1, $zero, 5
  /* 117588 80131F08 8E0E0000 */        lw $t6, ($s0)
  .L80131F0C:
  /* 11758C 80131F0C 562E0004 */      bnel $s1, $t6, .L80131F20
  /* 117590 80131F10 8E100004 */        lw $s0, 4($s0)
  /* 117594 80131F14 0C04CA96 */       jal mnTitleShowFire
  /* 117598 80131F18 02002025 */        or $a0, $s0, $zero
  /* 11759C 80131F1C 8E100004 */        lw $s0, 4($s0)
  .L80131F20:
  /* 1175A0 80131F20 5600FFFA */      bnel $s0, $zero, .L80131F0C
  /* 1175A4 80131F24 8E0E0000 */        lw $t6, ($s0)
  .L80131F28:
  /* 1175A8 80131F28 3C108004 */       lui $s0, %hi(gOMObjCommonLinks + (0x08 * 4))
  /* 1175AC 80131F2C 8E106710 */        lw $s0, %lo(gOMObjCommonLinks + (0x08 * 4))($s0)
  /* 1175B0 80131F30 24020008 */     addiu $v0, $zero, 8
  /* 1175B4 80131F34 12000008 */      beqz $s0, .L80131F58
  /* 1175B8 80131F38 00000000 */       nop
  /* 1175BC 80131F3C 8E0F0000 */        lw $t7, ($s0)
  .L80131F40:
  /* 1175C0 80131F40 544F0003 */      bnel $v0, $t7, .L80131F50
  /* 1175C4 80131F44 8E100004 */        lw $s0, 4($s0)
  /* 1175C8 80131F48 AFB00028 */        sw $s0, 0x28($sp)
  /* 1175CC 80131F4C 8E100004 */        lw $s0, 4($s0)
  .L80131F50:
  /* 1175D0 80131F50 5600FFFB */      bnel $s0, $zero, .L80131F40
  /* 1175D4 80131F54 8E0F0000 */        lw $t7, ($s0)
  .L80131F58:
  /* 1175D8 80131F58 0C002CE7 */       jal func_8000B39C
  /* 1175DC 80131F5C 8FA40028 */        lw $a0, 0x28($sp)
  /* 1175E0 80131F60 8FA20028 */        lw $v0, 0x28($sp)
  /* 1175E4 80131F64 00008825 */        or $s1, $zero, $zero
  /* 1175E8 80131F68 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 1175EC 80131F6C 8C500074 */        lw $s0, 0x74($v0)
  /* 1175F0 80131F70 AC40007C */        sw $zero, 0x7c($v0)
  /* 1175F4 80131F74 52000011 */      beql $s0, $zero, .L80131FBC
  /* 1175F8 80131F78 8FBF0024 */        lw $ra, 0x24($sp)
  /* 1175FC 80131F7C 4481A000 */      mtc1 $at, $f20 # 1.0 to cop1
  /* 117600 80131F80 00000000 */       nop
  /* 117604 80131F84 00002025 */        or $a0, $zero, $zero
  .L80131F88:
  /* 117608 80131F88 02002825 */        or $a1, $s0, $zero
  /* 11760C 80131F8C 0C04C9D9 */       jal mnTitleSetPosition
  /* 117610 80131F90 02203025 */        or $a2, $s1, $zero
  /* 117614 80131F94 02002025 */        or $a0, $s0, $zero
  /* 117618 80131F98 0C04CA0B */       jal mnTitleSetColors
  /* 11761C 80131F9C 02202825 */        or $a1, $s1, $zero
  /* 117620 80131FA0 E614001C */      swc1 $f20, 0x1c($s0)
  /* 117624 80131FA4 E6140018 */      swc1 $f20, 0x18($s0)
  /* 117628 80131FA8 8E100008 */        lw $s0, 8($s0)
  /* 11762C 80131FAC 26310001 */     addiu $s1, $s1, 1
  /* 117630 80131FB0 5600FFF5 */      bnel $s0, $zero, .L80131F88
  /* 117634 80131FB4 00002025 */        or $a0, $zero, $zero
  /* 117638 80131FB8 8FBF0024 */        lw $ra, 0x24($sp)
  .L80131FBC:
  /* 11763C 80131FBC D7B40010 */      ldc1 $f20, 0x10($sp)
  /* 117640 80131FC0 8FB0001C */        lw $s0, 0x1c($sp)
  /* 117644 80131FC4 8FB10020 */        lw $s1, 0x20($sp)
  /* 117648 80131FC8 03E00008 */        jr $ra
  /* 11764C 80131FCC 27BD0030 */     addiu $sp, $sp, 0x30

glabel mnTitleGoToNextDemo
  /* 117650 80131FD0 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 117654 80131FD4 AFB00020 */        sw $s0, 0x20($sp)
  /* 117658 80131FD8 3C10800A */       lui $s0, %hi(gSceneData)
  /* 11765C 80131FDC 26104AD0 */     addiu $s0, $s0, %lo(gSceneData)
  /* 117660 80131FE0 920E0001 */       lbu $t6, 1($s0) # gSceneData + 1
  /* 117664 80131FE4 AFBF0024 */        sw $ra, 0x24($sp)
  /* 117668 80131FE8 240F00FF */     addiu $t7, $zero, 0xff
  /* 11766C 80131FEC AFAF0010 */        sw $t7, 0x10($sp)
  /* 117670 80131FF0 24040002 */     addiu $a0, $zero, 2
  /* 117674 80131FF4 3C058000 */       lui $a1, 0x8000
  /* 117678 80131FF8 00003025 */        or $a2, $zero, $zero
  /* 11767C 80131FFC 24070002 */     addiu $a3, $zero, 2
  /* 117680 80132000 0C002E7F */       jal func_8000B9FC
  /* 117684 80132004 A3AE002F */        sb $t6, 0x2f($sp)
  /* 117688 80132008 0C04C6F1 */       jal mnTitleSetDemoFtKinds
  /* 11768C 8013200C 00000000 */       nop
  /* 117690 80132010 0C0099A8 */       jal func_800266A0
  /* 117694 80132014 00000000 */       nop
  /* 117698 80132018 93A2002F */       lbu $v0, 0x2f($sp)
  /* 11769C 8013201C 92180000 */       lbu $t8, ($s0) # gSceneData + 0
  /* 1176A0 80132020 24010007 */     addiu $at, $zero, 7
  /* 1176A4 80132024 1041000F */       beq $v0, $at, .L80132064
  /* 1176A8 80132028 A2180001 */        sb $t8, 1($s0) # gSceneData + 1
  /* 1176AC 8013202C 2401003C */     addiu $at, $zero, 0x3c
  /* 1176B0 80132030 10410006 */       beq $v0, $at, .L8013204C
  /* 1176B4 80132034 2408001A */     addiu $t0, $zero, 0x1a
  /* 1176B8 80132038 2401003D */     addiu $at, $zero, 0x3d
  /* 1176BC 8013203C 10410009 */       beq $v0, $at, .L80132064
  /* 1176C0 80132040 2419003C */     addiu $t9, $zero, 0x3c
  /* 1176C4 80132044 10000009 */         b .L8013206C
  /* 1176C8 80132048 A2190000 */        sb $t9, ($s0) # gSceneData + 0
  .L8013204C:
  /* 1176CC 8013204C A2080000 */        sb $t0, ($s0) # gSceneData + 0
  /* 1176D0 80132050 00002025 */        or $a0, $zero, $zero
  /* 1176D4 80132054 0C0082AD */       jal func_80020AB4
  /* 1176D8 80132058 24050022 */     addiu $a1, $zero, 0x22
  /* 1176DC 8013205C 10000004 */         b .L80132070
  /* 1176E0 80132060 8FBF0024 */        lw $ra, 0x24($sp)
  .L80132064:
  /* 1176E4 80132064 2409001B */     addiu $t1, $zero, 0x1b
  /* 1176E8 80132068 A2090000 */        sb $t1, ($s0) # gSceneData + 0
  .L8013206C:
  /* 1176EC 8013206C 8FBF0024 */        lw $ra, 0x24($sp)
  .L80132070:
  /* 1176F0 80132070 240A0001 */     addiu $t2, $zero, 1
  /* 1176F4 80132074 A20A003F */        sb $t2, 0x3f($s0) # gSceneData + 63
  /* 1176F8 80132078 240B0001 */     addiu $t3, $zero, 1
  /* 1176FC 8013207C 3C018013 */       lui $at, %hi(gMNTitleChangeSceneInterrupt)
  /* 117700 80132080 8FB00020 */        lw $s0, 0x20($sp)
  /* 117704 80132084 AC2B4470 */        sw $t3, %lo(gMNTitleChangeSceneInterrupt)($at)
  /* 117708 80132088 03E00008 */        jr $ra
  /* 11770C 8013208C 27BD0030 */     addiu $sp, $sp, 0x30

glabel mnTitleGoToMainMenu
  /* 117710 80132090 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 117714 80132094 AFBF001C */        sw $ra, 0x1c($sp)
  /* 117718 80132098 240E00FF */     addiu $t6, $zero, 0xff
  /* 11771C 8013209C AFAE0010 */        sw $t6, 0x10($sp)
  /* 117720 801320A0 24040002 */     addiu $a0, $zero, 2
  /* 117724 801320A4 3C058000 */       lui $a1, 0x8000
  /* 117728 801320A8 00003025 */        or $a2, $zero, $zero
  /* 11772C 801320AC 0C002E7F */       jal func_8000B9FC
  /* 117730 801320B0 24070002 */     addiu $a3, $zero, 2
  /* 117734 801320B4 3C02800A */       lui $v0, %hi(gSceneData)
  /* 117738 801320B8 24424AD0 */     addiu $v0, $v0, %lo(gSceneData)
  /* 11773C 801320BC 904F0000 */       lbu $t7, ($v0) # gSceneData + 0
  /* 117740 801320C0 24180007 */     addiu $t8, $zero, 7
  /* 117744 801320C4 A0580000 */        sb $t8, ($v0) # gSceneData + 0
  /* 117748 801320C8 0C0099A8 */       jal func_800266A0
  /* 11774C 801320CC A04F0001 */        sb $t7, 1($v0) # gSceneData + 1
  /* 117750 801320D0 0C009A70 */       jal func_800269C0
  /* 117754 801320D4 2404009D */     addiu $a0, $zero, 0x9d
  /* 117758 801320D8 8FBF001C */        lw $ra, 0x1c($sp)
  /* 11775C 801320DC 24190001 */     addiu $t9, $zero, 1
  /* 117760 801320E0 3C018013 */       lui $at, %hi(gMNTitleChangeSceneInterrupt)
  /* 117764 801320E4 AC394470 */        sw $t9, %lo(gMNTitleChangeSceneInterrupt)($at)
  /* 117768 801320E8 03E00008 */        jr $ra
  /* 11776C 801320EC 27BD0020 */     addiu $sp, $sp, 0x20

glabel mnTitleMain
  /* 117770 801320F0 3C038013 */       lui $v1, %hi(gMNTitleEnableMain)
  /* 117774 801320F4 24634460 */     addiu $v1, $v1, %lo(gMNTitleEnableMain)
  /* 117778 801320F8 8C620000 */        lw $v0, ($v1) # gMNTitleEnableMain + 0
  /* 11777C 801320FC 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 117780 80132100 AFBF0014 */        sw $ra, 0x14($sp)
  /* 117784 80132104 14400004 */      bnez $v0, .L80132118
  /* 117788 80132108 AFA40018 */        sw $a0, 0x18($sp)
  /* 11778C 8013210C 244E0001 */     addiu $t6, $v0, 1
  /* 117790 80132110 1000003B */         b .L80132200
  /* 117794 80132114 AC6E0000 */        sw $t6, ($v1) # gMNTitleEnableMain + 0
  .L80132118:
  /* 117798 80132118 3C0F8013 */       lui $t7, %hi(gMNTitleChangeSceneInterrupt)
  /* 11779C 8013211C 8DEF4470 */        lw $t7, %lo(gMNTitleChangeSceneInterrupt)($t7)
  /* 1177A0 80132120 11E0000A */      beqz $t7, .L8013214C
  /* 1177A4 80132124 3C028013 */       lui $v0, %hi(gMNTitleChangeSceneTimer)
  /* 1177A8 80132128 24424474 */     addiu $v0, $v0, %lo(gMNTitleChangeSceneTimer)
  /* 1177AC 8013212C 8C580000 */        lw $t8, ($v0) # gMNTitleChangeSceneTimer + 0
  /* 1177B0 80132130 2719FFFF */     addiu $t9, $t8, -1
  /* 1177B4 80132134 17200032 */      bnez $t9, .L80132200
  /* 1177B8 80132138 AC590000 */        sw $t9, ($v0) # gMNTitleChangeSceneTimer + 0
  /* 1177BC 8013213C 0C00171D */       jal func_80005C74
  /* 1177C0 80132140 00000000 */       nop
  /* 1177C4 80132144 1000002F */         b .L80132204
  /* 1177C8 80132148 8FBF0014 */        lw $ra, 0x14($sp)
  .L8013214C:
  /* 1177CC 8013214C 3C038004 */       lui $v1, %hi(gPlayerControllers)
  /* 1177D0 80132150 3C088004 */       lui $t0, %hi(gUpdateContData)
  /* 1177D4 80132154 3C078000 */       lui $a3, %hi(D_NF_8000030C)
  /* 1177D8 80132158 3C06800A */       lui $a2, %hi(gSceneData)
  /* 1177DC 8013215C 3C058013 */       lui $a1, %hi(gMNTitleLayout)
  /* 1177E0 80132160 24A54450 */     addiu $a1, $a1, %lo(gMNTitleLayout)
  /* 1177E4 80132164 24C64AD0 */     addiu $a2, $a2, %lo(gSceneData)
  /* 1177E8 80132168 24E7030C */     addiu $a3, $a3, %lo(D_NF_8000030C)
  /* 1177EC 8013216C 25085250 */     addiu $t0, $t0, %lo(gUpdateContData)
  /* 1177F0 80132170 24635228 */     addiu $v1, $v1, %lo(gPlayerControllers)
  /* 1177F4 80132174 94640002 */       lhu $a0, 2($v1) # gPlayerControllers + 2
  .L80132178:
  /* 1177F8 80132178 2463000A */     addiu $v1, $v1, 0xa
  /* 1177FC 8013217C 308AD000 */      andi $t2, $a0, 0xd000
  /* 117800 80132180 1140001D */      beqz $t2, .L801321F8
  /* 117804 80132184 00000000 */       nop
  /* 117808 80132188 8CAB0000 */        lw $t3, ($a1) # gMNTitleLayout + 0
  /* 11780C 8013218C 308E4000 */      andi $t6, $a0, 0x4000
  /* 117810 80132190 5160000E */      beql $t3, $zero, .L801321CC
  /* 117814 80132194 240F00A9 */     addiu $t7, $zero, 0xa9
  /* 117818 80132198 90CC0044 */       lbu $t4, 0x44($a2) # gSceneData + 68
  /* 11781C 8013219C 15800004 */      bnez $t4, .L801321B0
  /* 117820 801321A0 00000000 */       nop
  /* 117824 801321A4 8CED0000 */        lw $t5, ($a3) # D_NF_8000030C + 0
  /* 117828 801321A8 11A00013 */      beqz $t5, .L801321F8
  /* 11782C 801321AC 00000000 */       nop
  .L801321B0:
  /* 117830 801321B0 15C00011 */      bnez $t6, .L801321F8
  /* 117834 801321B4 00000000 */       nop
  /* 117838 801321B8 0C04C824 */       jal mnTitleGoToMainMenu
  /* 11783C 801321BC 00000000 */       nop
  /* 117840 801321C0 10000010 */         b .L80132204
  /* 117844 801321C4 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117848 801321C8 240F00A9 */     addiu $t7, $zero, 0xa9
  .L801321CC:
  /* 11784C 801321CC 3C018013 */       lui $at, %hi(gMNTitleTransitionFramesElapsed)
  /* 117850 801321D0 AC2F445C */        sw $t7, %lo(gMNTitleTransitionFramesElapsed)($at)
  /* 117854 801321D4 24180001 */     addiu $t8, $zero, 1
  /* 117858 801321D8 0C04C8C8 */       jal mnTitleTransitionFromFireLogo
  /* 11785C 801321DC ACB80000 */        sw $t8, ($a1)
  /* 117860 801321E0 0C00829D */       jal func_80020A74
  /* 117864 801321E4 00000000 */       nop
  /* 117868 801321E8 0C0099A8 */       jal func_800266A0
  /* 11786C 801321EC 00000000 */       nop
  /* 117870 801321F0 10000004 */         b .L80132204
  /* 117874 801321F4 8FBF0014 */        lw $ra, 0x14($sp)
  .L801321F8:
  /* 117878 801321F8 5468FFDF */      bnel $v1, $t0, .L80132178
  /* 11787C 801321FC 94640002 */       lhu $a0, 2($v1)
  .L80132200:
  /* 117880 80132200 8FBF0014 */        lw $ra, 0x14($sp)
  .L80132204:
  /* 117884 80132204 27BD0018 */     addiu $sp, $sp, 0x18
  /* 117888 80132208 03E00008 */        jr $ra
  /* 11788C 8013220C 00000000 */       nop

glabel mnTitleUpdateFireBGOverlayVars
  /* 117890 80132210 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 117894 80132214 AFBF0014 */        sw $ra, 0x14($sp)
  /* 117898 80132218 0C00628C */       jal lbRandom_GetTimeByteRange
  /* 11789C 8013221C 24040007 */     addiu $a0, $zero, 7
  /* 1178A0 80132220 3C0142A0 */       lui $at, (0x42A00000 >> 16) # 80.0
  /* 1178A4 80132224 44802000 */      mtc1 $zero, $f4
  /* 1178A8 80132228 44816000 */      mtc1 $at, $f12 # 80.0 to cop1
  /* 1178AC 8013222C 3C038013 */       lui $v1, %hi(gMNTitleFireBGOverlayBlue)
  /* 1178B0 80132230 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayIndex)
  /* 1178B4 80132234 24634484 */     addiu $v1, $v1, %lo(gMNTitleFireBGOverlayBlue)
  /* 1178B8 80132238 AC224494 */        sw $v0, %lo(gMNTitleFireBGOverlayIndex)($at)
  /* 1178BC 8013223C E4640000 */      swc1 $f4, ($v1) # gMNTitleFireBGOverlayBlue + 0
  /* 1178C0 80132240 C4600000 */      lwc1 $f0, ($v1) # gMNTitleFireBGOverlayBlue + 0
  /* 1178C4 80132244 3C048013 */       lui $a0, %hi(gMNTitleFireBGOverlayGreen)
  /* 1178C8 80132248 24844480 */     addiu $a0, $a0, %lo(gMNTitleFireBGOverlayGreen)
  /* 1178CC 8013224C E4800000 */      swc1 $f0, ($a0) # gMNTitleFireBGOverlayGreen + 0
  /* 1178D0 80132250 C4820000 */      lwc1 $f2, ($a0) # gMNTitleFireBGOverlayGreen + 0
  /* 1178D4 80132254 3C058013 */       lui $a1, %hi(gMNTitleFireBGOverlayRed)
  /* 1178D8 80132258 24A5447C */     addiu $a1, $a1, %lo(gMNTitleFireBGOverlayRed)
  /* 1178DC 8013225C 3C0E8013 */       lui $t6, %hi(dMNTitleFireBGOverlayColorArrayRed)
  /* 1178E0 80132260 01C27021 */      addu $t6, $t6, $v0
  /* 1178E4 80132264 E4A20000 */      swc1 $f2, ($a1) # gMNTitleFireBGOverlayRed + 0
  /* 1178E8 80132268 91CE4318 */       lbu $t6, %lo(dMNTitleFireBGOverlayColorArrayRed)($t6)
  /* 1178EC 8013226C 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 1178F0 80132270 448E3000 */      mtc1 $t6, $f6
  /* 1178F4 80132274 05C10004 */      bgez $t6, .L80132288
  /* 1178F8 80132278 46803220 */   cvt.s.w $f8, $f6
  /* 1178FC 8013227C 44815000 */      mtc1 $at, $f10 # 4294967300.0 to cop1
  /* 117900 80132280 00000000 */       nop
  /* 117904 80132284 460A4200 */     add.s $f8, $f8, $f10
  .L80132288:
  /* 117908 80132288 C4B00000 */      lwc1 $f16, ($a1) # gMNTitleFireBGOverlayRed + 0
  /* 11790C 8013228C 3C0F8013 */       lui $t7, %hi(dMNTitleFireBGOverlayColorArrayGreen)
  /* 117910 80132290 01E27821 */      addu $t7, $t7, $v0
  /* 117914 80132294 46104481 */     sub.s $f18, $f8, $f16
  /* 117918 80132298 91EF4320 */       lbu $t7, %lo(dMNTitleFireBGOverlayColorArrayGreen)($t7)
  /* 11791C 8013229C 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaRed)
  /* 117920 801322A0 460C9103 */     div.s $f4, $f18, $f12
  /* 117924 801322A4 448F3000 */      mtc1 $t7, $f6
  /* 117928 801322A8 00000000 */       nop
  /* 11792C 801322AC 468032A0 */   cvt.s.w $f10, $f6
  /* 117930 801322B0 05E10005 */      bgez $t7, .L801322C8
  /* 117934 801322B4 E4244488 */      swc1 $f4, %lo(gMNTitleFireBGOverlayDeltaRed)($at)
  /* 117938 801322B8 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 11793C 801322BC 44814000 */      mtc1 $at, $f8 # 4294967300.0 to cop1
  /* 117940 801322C0 00000000 */       nop
  /* 117944 801322C4 46085280 */     add.s $f10, $f10, $f8
  .L801322C8:
  /* 117948 801322C8 46025401 */     sub.s $f16, $f10, $f2
  /* 11794C 801322CC 3C188013 */       lui $t8, %hi(dMNTitleFireBGOverlayColorArrayBlue)
  /* 117950 801322D0 0302C021 */      addu $t8, $t8, $v0
  /* 117954 801322D4 93184328 */       lbu $t8, %lo(dMNTitleFireBGOverlayColorArrayBlue)($t8)
  /* 117958 801322D8 460C8483 */     div.s $f18, $f16, $f12
  /* 11795C 801322DC 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaGreen)
  /* 117960 801322E0 44982000 */      mtc1 $t8, $f4
  /* 117964 801322E4 00000000 */       nop
  /* 117968 801322E8 468021A0 */   cvt.s.w $f6, $f4
  /* 11796C 801322EC 07010005 */      bgez $t8, .L80132304
  /* 117970 801322F0 E432448C */      swc1 $f18, %lo(gMNTitleFireBGOverlayDeltaGreen)($at)
  /* 117974 801322F4 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 117978 801322F8 44814000 */      mtc1 $at, $f8 # 4294967300.0 to cop1
  /* 11797C 801322FC 00000000 */       nop
  /* 117980 80132300 46083180 */     add.s $f6, $f6, $f8
  .L80132304:
  /* 117984 80132304 46003281 */     sub.s $f10, $f6, $f0
  /* 117988 80132308 8FBF0014 */        lw $ra, 0x14($sp)
  /* 11798C 8013230C 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaBlue)
  /* 117990 80132310 27BD0018 */     addiu $sp, $sp, 0x18
  /* 117994 80132314 460C5403 */     div.s $f16, $f10, $f12
  /* 117998 80132318 03E00008 */        jr $ra
  /* 11799C 8013231C E4304490 */      swc1 $f16, %lo(gMNTitleFireBGOverlayDeltaBlue)($at)

glabel mnTitleTransitionFromFireLogo
  /* 1179A0 80132320 3C068004 */       lui $a2, %hi(gOMObjCommonLinks)
  /* 1179A4 80132324 24C666F0 */     addiu $a2, $a2, %lo(gOMObjCommonLinks)
  /* 1179A8 80132328 8CC2001C */        lw $v0, 0x1c($a2) # gOMObjCommonLinks + 28
  /* 1179AC 8013232C 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 1179B0 80132330 AFBF0014 */        sw $ra, 0x14($sp)
  /* 1179B4 80132334 10400009 */      beqz $v0, .L8013235C
  /* 1179B8 80132338 24050001 */     addiu $a1, $zero, 1
  /* 1179BC 8013233C 24040006 */     addiu $a0, $zero, 6
  .L80132340:
  /* 1179C0 80132340 8C4E0000 */        lw $t6, ($v0)
  /* 1179C4 80132344 8C430004 */        lw $v1, 4($v0)
  /* 1179C8 80132348 148E0002 */       bne $a0, $t6, .L80132354
  /* 1179CC 8013234C 00000000 */       nop
  /* 1179D0 80132350 AC45007C */        sw $a1, 0x7c($v0)
  .L80132354:
  /* 1179D4 80132354 1460FFFA */      bnez $v1, .L80132340
  /* 1179D8 80132358 00601025 */        or $v0, $v1, $zero
  .L8013235C:
  /* 1179DC 8013235C 8CC40010 */        lw $a0, 0x10($a2) # gOMObjCommonLinks + 16
  /* 1179E0 80132360 50800006 */      beql $a0, $zero, .L8013237C
  /* 1179E4 80132364 8CC40038 */        lw $a0, 0x38($a2) # gOMObjCommonLinks + 56
  /* 1179E8 80132368 0C0026A1 */       jal omEjectGObj
  /* 1179EC 8013236C 00000000 */       nop
  /* 1179F0 80132370 3C068004 */       lui $a2, %hi(gOMObjCommonLinks)
  /* 1179F4 80132374 24C666F0 */     addiu $a2, $a2, %lo(gOMObjCommonLinks)
  /* 1179F8 80132378 8CC40038 */        lw $a0, 0x38($a2) # gOMObjCommonLinks + 56
  .L8013237C:
  /* 1179FC 8013237C 10800003 */      beqz $a0, .L8013238C
  /* 117A00 80132380 00000000 */       nop
  /* 117A04 80132384 0C0026A1 */       jal omEjectGObj
  /* 117A08 80132388 00000000 */       nop
  .L8013238C:
  /* 117A0C 8013238C 0C04C8EB */       jal mnTitleEnableAllInGroup
  /* 117A10 80132390 24040006 */     addiu $a0, $zero, 6
  /* 117A14 80132394 0C04C884 */       jal mnTitleUpdateFireBGOverlayVars
  /* 117A18 80132398 00000000 */       nop
  /* 117A1C 8013239C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117A20 801323A0 27BD0018 */     addiu $sp, $sp, 0x18
  /* 117A24 801323A4 03E00008 */        jr $ra
  /* 117A28 801323A8 00000000 */       nop

glabel mnTitleEnableAllInGroup
  /* 117A2C 801323AC 00047080 */       sll $t6, $a0, 2
  /* 117A30 801323B0 3C028004 */       lui $v0, %hi(gOMObjCommonLinks)
  /* 117A34 801323B4 004E1021 */      addu $v0, $v0, $t6
  /* 117A38 801323B8 8C4266F0 */        lw $v0, %lo(gOMObjCommonLinks)($v0)
  /* 117A3C 801323BC 10400005 */      beqz $v0, .L801323D4
  /* 117A40 801323C0 00000000 */       nop
  /* 117A44 801323C4 AC40007C */        sw $zero, 0x7c($v0)
  .L801323C8:
  /* 117A48 801323C8 8C420004 */        lw $v0, 4($v0)
  /* 117A4C 801323CC 5440FFFE */      bnel $v0, $zero, .L801323C8
  /* 117A50 801323D0 AC40007C */        sw $zero, 0x7c($v0)
  .L801323D4:
  /* 117A54 801323D4 03E00008 */        jr $ra
  /* 117A58 801323D8 00000000 */       nop

glabel mnTitleNextLayout
  /* 117A5C 801323DC 3C038013 */       lui $v1, %hi(gMNTitleLayout)
  /* 117A60 801323E0 24634450 */     addiu $v1, $v1, %lo(gMNTitleLayout)
  /* 117A64 801323E4 8C620000 */        lw $v0, ($v1) # gMNTitleLayout + 0
  /* 117A68 801323E8 3C04800A */       lui $a0, %hi(gSceneData)
  /* 117A6C 801323EC 24844AD0 */     addiu $a0, $a0, %lo(gSceneData)
  /* 117A70 801323F0 14400006 */      bnez $v0, .L8013240C
  /* 117A74 801323F4 244F0001 */     addiu $t7, $v0, 1
  /* 117A78 801323F8 908E0001 */       lbu $t6, 1($a0) # gSceneData + 1
  /* 117A7C 801323FC 2401002E */     addiu $at, $zero, 0x2e
  /* 117A80 80132400 15C10002 */       bne $t6, $at, .L8013240C
  /* 117A84 80132404 00000000 */       nop
  /* 117A88 80132408 A080003F */        sb $zero, 0x3f($a0) # gSceneData + 63
  .L8013240C:
  /* 117A8C 8013240C 03E00008 */        jr $ra
  /* 117A90 80132410 AC6F0000 */        sw $t7, ($v1) # gMNTitleLayout + 0

glabel mnTitleSetMainMenuFramesToWait
  /* 117A94 80132414 3C0E8013 */       lui $t6, %hi(gMNTitleLayout)
  /* 117A98 80132418 8DCE4450 */        lw $t6, %lo(gMNTitleLayout)($t6)
  /* 117A9C 8013241C 24010002 */     addiu $at, $zero, 2
  /* 117AA0 80132420 240F0118 */     addiu $t7, $zero, 0x118
  /* 117AA4 80132424 15C10004 */       bne $t6, $at, .L80132438
  /* 117AA8 80132428 2418016C */     addiu $t8, $zero, 0x16c
  /* 117AAC 8013242C 3C018013 */       lui $at, %hi(gMNTitleMainMenuFramesToWait)
  /* 117AB0 80132430 03E00008 */        jr $ra
  /* 117AB4 80132434 AC2F4498 */        sw $t7, %lo(gMNTitleMainMenuFramesToWait)($at)

  .L80132438:
  /* 117AB8 80132438 3C018013 */       lui $at, %hi(gMNTitleMainMenuFramesToWait)
  /* 117ABC 8013243C AC384498 */        sw $t8, %lo(gMNTitleMainMenuFramesToWait)($at)
  /* 117AC0 80132440 03E00008 */        jr $ra
  /* 117AC4 80132444 00000000 */       nop

glabel mnTitleHandleTransitions
  /* 117AC8 80132448 3C028013 */       lui $v0, %hi(gMNTitleTransitionFramesElapsed)
  /* 117ACC 8013244C 2442445C */     addiu $v0, $v0, %lo(gMNTitleTransitionFramesElapsed)
  /* 117AD0 80132450 8C4E0000 */        lw $t6, ($v0) # gMNTitleTransitionFramesElapsed + 0
  /* 117AD4 80132454 3C188013 */       lui $t8, %hi(gMNTitleMainMenuFramesToWait)
  /* 117AD8 80132458 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 117ADC 8013245C 25C30001 */     addiu $v1, $t6, 1
  /* 117AE0 80132460 AC430000 */        sw $v1, ($v0) # gMNTitleTransitionFramesElapsed + 0
  /* 117AE4 80132464 8F184498 */        lw $t8, %lo(gMNTitleMainMenuFramesToWait)($t8)
  /* 117AE8 80132468 AFBF0014 */        sw $ra, 0x14($sp)
  /* 117AEC 8013246C AFA40018 */        sw $a0, 0x18($sp)
  /* 117AF0 80132470 17030005 */       bne $t8, $v1, .L80132488
  /* 117AF4 80132474 00601025 */        or $v0, $v1, $zero
  /* 117AF8 80132478 3C04800A */       lui $a0, %hi(gSceneData)
  /* 117AFC 8013247C 24844AD0 */     addiu $a0, $a0, %lo(gSceneData)
  /* 117B00 80132480 24190001 */     addiu $t9, $zero, 1
  /* 117B04 80132484 A0990044 */        sb $t9, 0x44($a0) # gSceneData + 68
  .L80132488:
  /* 117B08 80132488 3C04800A */       lui $a0, %hi(gSceneData)
  /* 117B0C 8013248C 286100D7 */      slti $at, $v1, 0xd7
  /* 117B10 80132490 1420000E */      bnez $at, .L801324CC
  /* 117B14 80132494 24844AD0 */     addiu $a0, $a0, %lo(gSceneData)
  /* 117B18 80132498 240100DC */     addiu $at, $zero, 0xdc
  /* 117B1C 8013249C 10610029 */       beq $v1, $at, .L80132544
  /* 117B20 801324A0 240100F0 */     addiu $at, $zero, 0xf0
  /* 117B24 801324A4 10610047 */       beq $v1, $at, .L801325C4
  /* 117B28 801324A8 24010118 */     addiu $at, $zero, 0x118
  /* 117B2C 801324AC 10610029 */       beq $v1, $at, .L80132554
  /* 117B30 801324B0 2401028A */     addiu $at, $zero, 0x28a
  /* 117B34 801324B4 10610037 */       beq $v1, $at, .L80132594
  /* 117B38 801324B8 240104A6 */     addiu $at, $zero, 0x4a6
  /* 117B3C 801324BC 5061003D */      beql $v1, $at, .L801325B4
  /* 117B40 801324C0 908A003F */       lbu $t2, 0x3f($a0) # gSceneData + 63
  /* 117B44 801324C4 10000040 */         b .L801325C8
  /* 117B48 801324C8 8FBF0014 */        lw $ra, 0x14($sp)
  .L801324CC:
  /* 117B4C 801324CC 24010023 */     addiu $at, $zero, 0x23
  /* 117B50 801324D0 10410024 */       beq $v0, $at, .L80132564
  /* 117B54 801324D4 24010041 */     addiu $at, $zero, 0x41
  /* 117B58 801324D8 10410022 */       beq $v0, $at, .L80132564
  /* 117B5C 801324DC 2401006F */     addiu $at, $zero, 0x6f
  /* 117B60 801324E0 1041000A */       beq $v0, $at, .L8013250C
  /* 117B64 801324E4 240100AA */     addiu $at, $zero, 0xaa
  /* 117B68 801324E8 1041000C */       beq $v0, $at, .L8013251C
  /* 117B6C 801324EC 240100C8 */     addiu $at, $zero, 0xc8
  /* 117B70 801324F0 10410020 */       beq $v0, $at, .L80132574
  /* 117B74 801324F4 3C088013 */       lui $t0, 0x8013
  /* 117B78 801324F8 240100D6 */     addiu $at, $zero, 0xd6
  /* 117B7C 801324FC 50410032 */      beql $v0, $at, .L801325C8
  /* 117B80 80132500 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117B84 80132504 10000030 */         b .L801325C8
  /* 117B88 80132508 8FBF0014 */        lw $ra, 0x14($sp)
  .L8013250C:
  /* 117B8C 8013250C 0C04C8C8 */       jal mnTitleTransitionFromFireLogo
  /* 117B90 80132510 00000000 */       nop
  /* 117B94 80132514 1000002C */         b .L801325C8
  /* 117B98 80132518 8FBF0014 */        lw $ra, 0x14($sp)
  .L8013251C:
  /* 117B9C 8013251C 0C04C79A */       jal mnTitleSetFinalLogoPosition
  /* 117BA0 80132520 00000000 */       nop
  /* 117BA4 80132524 0C04C8EB */       jal mnTitleEnableAllInGroup
  /* 117BA8 80132528 24040008 */     addiu $a0, $zero, 8
  /* 117BAC 8013252C 0C04C8F7 */       jal mnTitleNextLayout
  /* 117BB0 80132530 00000000 */       nop
  /* 117BB4 80132534 0C04C905 */       jal mnTitleSetMainMenuFramesToWait
  /* 117BB8 80132538 00000000 */       nop
  /* 117BBC 8013253C 10000022 */         b .L801325C8
  /* 117BC0 80132540 8FBF0014 */        lw $ra, 0x14($sp)
  .L80132544:
  /* 117BC4 80132544 0C04C7B9 */       jal mnTitleSetFinalLayout
  /* 117BC8 80132548 00000000 */       nop
  /* 117BCC 8013254C 1000001E */         b .L801325C8
  /* 117BD0 80132550 8FBF0014 */        lw $ra, 0x14($sp)
  .L80132554:
  /* 117BD4 80132554 0C04C8EB */       jal mnTitleEnableAllInGroup
  /* 117BD8 80132558 24040009 */     addiu $a0, $zero, 9
  /* 117BDC 8013255C 1000001A */         b .L801325C8
  /* 117BE0 80132560 8FBF0014 */        lw $ra, 0x14($sp)
  .L80132564:
  /* 117BE4 80132564 0C009A70 */       jal func_800269C0
  /* 117BE8 80132568 24040098 */     addiu $a0, $zero, 0x98
  /* 117BEC 8013256C 10000016 */         b .L801325C8
  /* 117BF0 80132570 8FBF0014 */        lw $ra, 0x14($sp)
  .L80132574:
  /* 117BF4 80132574 8D084450 */        lw $t0, 0x4450($t0)
  /* 117BF8 80132578 24010001 */     addiu $at, $zero, 1
  /* 117BFC 8013257C 55010012 */      bnel $t0, $at, .L801325C8
  /* 117C00 80132580 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117C04 80132584 0C009A70 */       jal func_800269C0
  /* 117C08 80132588 24040096 */     addiu $a0, $zero, 0x96
  /* 117C0C 8013258C 1000000E */         b .L801325C8
  /* 117C10 80132590 8FBF0014 */        lw $ra, 0x14($sp)
  .L80132594:
  /* 117C14 80132594 9089003F */       lbu $t1, 0x3f($a0)
  /* 117C18 80132598 5520000B */      bnel $t1, $zero, .L801325C8
  /* 117C1C 8013259C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117C20 801325A0 0C04C7F4 */       jal mnTitleGoToNextDemo
  /* 117C24 801325A4 00000000 */       nop
  /* 117C28 801325A8 10000007 */         b .L801325C8
  /* 117C2C 801325AC 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117C30 801325B0 908A003F */       lbu $t2, 0x3f($a0)
  .L801325B4:
  /* 117C34 801325B4 51400004 */      beql $t2, $zero, .L801325C8
  /* 117C38 801325B8 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117C3C 801325BC 0C04C7F4 */       jal mnTitleGoToNextDemo
  /* 117C40 801325C0 00000000 */       nop
  .L801325C4:
  /* 117C44 801325C4 8FBF0014 */        lw $ra, 0x14($sp)
  .L801325C8:
  /* 117C48 801325C8 27BD0018 */     addiu $sp, $sp, 0x18
  /* 117C4C 801325CC 03E00008 */        jr $ra
  /* 117C50 801325D0 00000000 */       nop

glabel mnTitleAnimateGObj
  /* 117C54 801325D4 27BDFFD8 */     addiu $sp, $sp, -0x28
  /* 117C58 801325D8 AFBF0014 */        sw $ra, 0x14($sp)
  /* 117C5C 801325DC 00802825 */        or $a1, $a0, $zero
  /* 117C60 801325E0 8C840084 */        lw $a0, 0x84($a0)
  /* 117C64 801325E4 8CA20074 */        lw $v0, 0x74($a1)
  /* 117C68 801325E8 8C830074 */        lw $v1, 0x74($a0)
  /* 117C6C 801325EC AFA20020 */        sw $v0, 0x20($sp)
  /* 117C70 801325F0 0C0037CD */       jal func_8000DF34
  /* 117C74 801325F4 AFA3001C */        sw $v1, 0x1c($sp)
  /* 117C78 801325F8 8FA20020 */        lw $v0, 0x20($sp)
  /* 117C7C 801325FC 8FA3001C */        lw $v1, 0x1c($sp)
  /* 117C80 80132600 3C0142F0 */       lui $at, (0x42F00000 >> 16) # 120.0
  /* 117C84 80132604 10400023 */      beqz $v0, .L80132694
  /* 117C88 80132608 8C630010 */        lw $v1, 0x10($v1)
  /* 117C8C 8013260C 44816000 */      mtc1 $at, $f12 # 120.0 to cop1
  /* 117C90 80132610 3C014320 */       lui $at, (0x43200000 >> 16) # 160.0
  /* 117C94 80132614 44811000 */      mtc1 $at, $f2 # 160.0 to cop1
  /* 117C98 80132618 3C013F00 */       lui $at, (0x3F000000 >> 16) # 0.5
  /* 117C9C 8013261C 44810000 */      mtc1 $at, $f0 # 0.5 to cop1
  /* 117CA0 80132620 00000000 */       nop
  /* 117CA4 80132624 844E0014 */        lh $t6, 0x14($v0)
  .L80132628:
  /* 117CA8 80132628 C4640040 */      lwc1 $f4, 0x40($v1)
  /* 117CAC 8013262C 844F0016 */        lh $t7, 0x16($v0)
  /* 117CB0 80132630 448E4000 */      mtc1 $t6, $f8
  /* 117CB4 80132634 E4440018 */      swc1 $f4, 0x18($v0)
  /* 117CB8 80132638 C4500018 */      lwc1 $f16, 0x18($v0)
  /* 117CBC 8013263C 468042A0 */   cvt.s.w $f10, $f8
  /* 117CC0 80132640 C4660044 */      lwc1 $f6, 0x44($v1)
  /* 117CC4 80132644 E446001C */      swc1 $f6, 0x1c($v0)
  /* 117CC8 80132648 C466001C */      lwc1 $f6, 0x1c($v1)
  /* 117CCC 8013264C 46105482 */     mul.s $f18, $f10, $f16
  /* 117CD0 80132650 448F8000 */      mtc1 $t7, $f16
  /* 117CD4 80132654 46023200 */     add.s $f8, $f6, $f2
  /* 117CD8 80132658 C446001C */      lwc1 $f6, 0x1c($v0)
  /* 117CDC 8013265C 46009102 */     mul.s $f4, $f18, $f0
  /* 117CE0 80132660 468084A0 */   cvt.s.w $f18, $f16
  /* 117CE4 80132664 46044281 */     sub.s $f10, $f8, $f4
  /* 117CE8 80132668 46069202 */     mul.s $f8, $f18, $f6
  /* 117CEC 8013266C E44A0058 */      swc1 $f10, 0x58($v0)
  /* 117CF0 80132670 C46A0020 */      lwc1 $f10, 0x20($v1)
  /* 117CF4 80132674 46004102 */     mul.s $f4, $f8, $f0
  /* 117CF8 80132678 460A6401 */     sub.s $f16, $f12, $f10
  /* 117CFC 8013267C 46048481 */     sub.s $f18, $f16, $f4
  /* 117D00 80132680 E452005C */      swc1 $f18, 0x5c($v0)
  /* 117D04 80132684 8C420008 */        lw $v0, 8($v0)
  /* 117D08 80132688 8C630008 */        lw $v1, 8($v1)
  /* 117D0C 8013268C 5440FFE6 */      bnel $v0, $zero, .L80132628
  /* 117D10 80132690 844E0014 */        lh $t6, 0x14($v0)
  .L80132694:
  /* 117D14 80132694 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117D18 80132698 27BD0028 */     addiu $sp, $sp, 0x28
  /* 117D1C 8013269C 03E00008 */        jr $ra
  /* 117D20 801326A0 00000000 */       nop

glabel mnTitleAnimatePressStart
  /* 117D24 801326A4 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 117D28 801326A8 AFBF0014 */        sw $ra, 0x14($sp)
  /* 117D2C 801326AC 8C8E007C */        lw $t6, 0x7c($a0)
  /* 117D30 801326B0 24010001 */     addiu $at, $zero, 1
  /* 117D34 801326B4 51C10004 */      beql $t6, $at, .L801326C8
  /* 117D38 801326B8 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117D3C 801326BC 0C04C975 */       jal mnTitleAnimateGObj
  /* 117D40 801326C0 00000000 */       nop
  /* 117D44 801326C4 8FBF0014 */        lw $ra, 0x14($sp)
  .L801326C8:
  /* 117D48 801326C8 27BD0018 */     addiu $sp, $sp, 0x18
  /* 117D4C 801326CC 03E00008 */        jr $ra
  /* 117D50 801326D0 00000000 */       nop

glabel mnTitleAnimateTitle
  /* 117D54 801326D4 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 117D58 801326D8 AFBF0014 */        sw $ra, 0x14($sp)
  /* 117D5C 801326DC 8C8E007C */        lw $t6, 0x7c($a0)
  /* 117D60 801326E0 24010001 */     addiu $at, $zero, 1
  /* 117D64 801326E4 51C10004 */      beql $t6, $at, .L801326F8
  /* 117D68 801326E8 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117D6C 801326EC 0C04C975 */       jal mnTitleAnimateGObj
  /* 117D70 801326F0 00000000 */       nop
  /* 117D74 801326F4 8FBF0014 */        lw $ra, 0x14($sp)
  .L801326F8:
  /* 117D78 801326F8 27BD0018 */     addiu $sp, $sp, 0x18
  /* 117D7C 801326FC 03E00008 */        jr $ra
  /* 117D80 80132700 00000000 */       nop

glabel mnTitleUpdateHeaderAndFooterPosition
  /* 117D84 80132704 3C0E8013 */       lui $t6, %hi(gMNTitleLayout)
  /* 117D88 80132708 8DCE4450 */        lw $t6, %lo(gMNTitleLayout)($t6)
  /* 117D8C 8013270C 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 117D90 80132710 AFBF0014 */        sw $ra, 0x14($sp)
  /* 117D94 80132714 15C00005 */      bnez $t6, .L8013272C
  /* 117D98 80132718 8C870074 */        lw $a3, 0x74($a0)
  /* 117D9C 8013271C 3C0F800A */       lui $t7, %hi((gSceneData + 0x1))
  /* 117DA0 80132720 91EF4AD1 */       lbu $t7, %lo((gSceneData + 0x1))($t7)
  /* 117DA4 80132724 2401002E */     addiu $at, $zero, 0x2e
  /* 117DA8 80132728 11E1000A */       beq $t7, $at, .L80132754
  .L8013272C:
  /* 117DAC 8013272C 00002025 */        or $a0, $zero, $zero
  /* 117DB0 80132730 00E02825 */        or $a1, $a3, $zero
  /* 117DB4 80132734 24060005 */     addiu $a2, $zero, 5
  /* 117DB8 80132738 0C04C9D9 */       jal mnTitleSetPosition
  /* 117DBC 8013273C AFA7001C */        sw $a3, 0x1c($sp)
  /* 117DC0 80132740 8FA7001C */        lw $a3, 0x1c($sp)
  /* 117DC4 80132744 00002025 */        or $a0, $zero, $zero
  /* 117DC8 80132748 24060006 */     addiu $a2, $zero, 6
  /* 117DCC 8013274C 0C04C9D9 */       jal mnTitleSetPosition
  /* 117DD0 80132750 8CE50008 */        lw $a1, 8($a3)
  .L80132754:
  /* 117DD4 80132754 8FBF0014 */        lw $ra, 0x14($sp)
  /* 117DD8 80132758 27BD0020 */     addiu $sp, $sp, 0x20
  /* 117DDC 8013275C 03E00008 */        jr $ra
  /* 117DE0 80132760 00000000 */       nop

glabel mnTitleSetPosition
  /* 117DE4 80132764 10800017 */      beqz $a0, .L801327C4
  /* 117DE8 80132768 00064080 */       sll $t0, $a2, 2
  /* 117DEC 8013276C 00067080 */       sll $t6, $a2, 2
  /* 117DF0 80132770 01C67023 */      subu $t6, $t6, $a2
  /* 117DF4 80132774 3C0F8013 */       lui $t7, %hi(dMNTitleTextureConfigs)
  /* 117DF8 80132778 25EF4268 */     addiu $t7, $t7, %lo(dMNTitleTextureConfigs)
  /* 117DFC 8013277C 000E7080 */       sll $t6, $t6, 2
  /* 117E00 80132780 01CF1021 */      addu $v0, $t6, $t7
  /* 117E04 80132784 8C580000 */        lw $t8, ($v0)
  /* 117E08 80132788 3C014320 */       lui $at, (0x43200000 >> 16) # 160.0
  /* 117E0C 8013278C 44814000 */      mtc1 $at, $f8 # 160.0 to cop1
  /* 117E10 80132790 44982000 */      mtc1 $t8, $f4
  /* 117E14 80132794 3C0142F0 */       lui $at, (0x42F00000 >> 16) # 120.0
  /* 117E18 80132798 468021A0 */   cvt.s.w $f6, $f4
  /* 117E1C 8013279C 44812000 */      mtc1 $at, $f4 # 120.0 to cop1
  /* 117E20 801327A0 46083281 */     sub.s $f10, $f6, $f8
  /* 117E24 801327A4 E48A001C */      swc1 $f10, 0x1c($a0)
  /* 117E28 801327A8 8C590004 */        lw $t9, 4($v0)
  /* 117E2C 801327AC 44998000 */      mtc1 $t9, $f16
  /* 117E30 801327B0 00000000 */       nop
  /* 117E34 801327B4 468084A0 */   cvt.s.w $f18, $f16
  /* 117E38 801327B8 46049181 */     sub.s $f6, $f18, $f4
  /* 117E3C 801327BC 46003207 */     neg.s $f8, $f6
  /* 117E40 801327C0 E4880020 */      swc1 $f8, 0x20($a0)
  .L801327C4:
  /* 117E44 801327C4 84AB0014 */        lh $t3, 0x14($a1)
  /* 117E48 801327C8 01064023 */      subu $t0, $t0, $a2
  /* 117E4C 801327CC 3C098013 */       lui $t1, %hi(dMNTitleTextureConfigs)
  /* 117E50 801327D0 448B9000 */      mtc1 $t3, $f18
  /* 117E54 801327D4 25294268 */     addiu $t1, $t1, %lo(dMNTitleTextureConfigs)
  /* 117E58 801327D8 00084080 */       sll $t0, $t0, 2
  /* 117E5C 801327DC 46809120 */   cvt.s.w $f4, $f18
  /* 117E60 801327E0 01091021 */      addu $v0, $t0, $t1
  /* 117E64 801327E4 8C4A0000 */        lw $t2, ($v0)
  /* 117E68 801327E8 3C013F00 */       lui $at, (0x3F000000 >> 16) # 0.5
  /* 117E6C 801327EC 44810000 */      mtc1 $at, $f0 # 0.5 to cop1
  /* 117E70 801327F0 448A5000 */      mtc1 $t2, $f10
  /* 117E74 801327F4 84AD0016 */        lh $t5, 0x16($a1)
  /* 117E78 801327F8 46002182 */     mul.s $f6, $f4, $f0
  /* 117E7C 801327FC 448D2000 */      mtc1 $t5, $f4
  /* 117E80 80132800 46805420 */   cvt.s.w $f16, $f10
  /* 117E84 80132804 46068201 */     sub.s $f8, $f16, $f6
  /* 117E88 80132808 46802420 */   cvt.s.w $f16, $f4
  /* 117E8C 8013280C E4A80058 */      swc1 $f8, 0x58($a1)
  /* 117E90 80132810 8C4C0004 */        lw $t4, 4($v0)
  /* 117E94 80132814 448C5000 */      mtc1 $t4, $f10
  /* 117E98 80132818 46008182 */     mul.s $f6, $f16, $f0
  /* 117E9C 8013281C 468054A0 */   cvt.s.w $f18, $f10
  /* 117EA0 80132820 46069201 */     sub.s $f8, $f18, $f6
  /* 117EA4 80132824 03E00008 */        jr $ra
  /* 117EA8 80132828 E4A8005C */      swc1 $f8, 0x5c($a1)

glabel mnTitleSetColors
  /* 117EAC 8013282C 28A10005 */      slti $at, $a1, 5
  /* 117EB0 80132830 50200013 */      beql $at, $zero, .L80132880
  /* 117EB4 80132834 24010005 */     addiu $at, $zero, 5
  /* 117EB8 80132838 10A00003 */      beqz $a1, .L80132848
  /* 117EBC 8013283C 24010004 */     addiu $at, $zero, 4
  /* 117EC0 80132840 14A10005 */       bne $a1, $at, .L80132858
  /* 117EC4 80132844 240200FF */     addiu $v0, $zero, 0xff
  .L80132848:
  /* 117EC8 80132848 A0800028 */        sb $zero, 0x28($a0)
  /* 117ECC 8013284C A0800029 */        sb $zero, 0x29($a0)
  /* 117ED0 80132850 03E00008 */        jr $ra
  /* 117ED4 80132854 A080002A */        sb $zero, 0x2a($a0)

  .L80132858:
  /* 117ED8 80132858 240E00FE */     addiu $t6, $zero, 0xfe
  /* 117EDC 8013285C 240F002A */     addiu $t7, $zero, 0x2a
  /* 117EE0 80132860 A0820028 */        sb $v0, 0x28($a0)
  /* 117EE4 80132864 A08E0029 */        sb $t6, 0x29($a0)
  /* 117EE8 80132868 A08F002A */        sb $t7, 0x2a($a0)
  /* 117EEC 8013286C A0800060 */        sb $zero, 0x60($a0)
  /* 117EF0 80132870 A0800061 */        sb $zero, 0x61($a0)
  /* 117EF4 80132874 03E00008 */        jr $ra
  /* 117EF8 80132878 A0800062 */        sb $zero, 0x62($a0)

  /* 117EFC 8013287C 24010005 */     addiu $at, $zero, 5
  .L80132880:
  /* 117F00 80132880 10A1000C */       beq $a1, $at, .L801328B4
  /* 117F04 80132884 241800B7 */     addiu $t8, $zero, 0xb7
  /* 117F08 80132888 24010006 */     addiu $at, $zero, 6
  /* 117F0C 8013288C 10A10015 */       beq $a1, $at, .L801328E4
  /* 117F10 80132890 240C0014 */     addiu $t4, $zero, 0x14
  /* 117F14 80132894 24010007 */     addiu $at, $zero, 7
  /* 117F18 80132898 10A10018 */       beq $a1, $at, .L801328FC
  /* 117F1C 8013289C 240200FF */     addiu $v0, $zero, 0xff
  /* 117F20 801328A0 24010009 */     addiu $at, $zero, 9
  /* 117F24 801328A4 10A1001F */       beq $a1, $at, .L80132924
  /* 117F28 801328A8 24080015 */     addiu $t0, $zero, 0x15
  /* 117F2C 801328AC 03E00008 */        jr $ra
  /* 117F30 801328B0 00000000 */       nop

  .L801328B4:
  /* 117F34 801328B4 241900AE */     addiu $t9, $zero, 0xae
  /* 117F38 801328B8 2408007C */     addiu $t0, $zero, 0x7c
  /* 117F3C 801328BC 24090014 */     addiu $t1, $zero, 0x14
  /* 117F40 801328C0 240A0012 */     addiu $t2, $zero, 0x12
  /* 117F44 801328C4 240B0006 */     addiu $t3, $zero, 6
  /* 117F48 801328C8 A0980028 */        sb $t8, 0x28($a0)
  /* 117F4C 801328CC A0990029 */        sb $t9, 0x29($a0)
  /* 117F50 801328D0 A088002A */        sb $t0, 0x2a($a0)
  /* 117F54 801328D4 A0890060 */        sb $t1, 0x60($a0)
  /* 117F58 801328D8 A08A0061 */        sb $t2, 0x61($a0)
  /* 117F5C 801328DC 03E00008 */        jr $ra
  /* 117F60 801328E0 A08B0062 */        sb $t3, 0x62($a0)

  .L801328E4:
  /* 117F64 801328E4 240D0012 */     addiu $t5, $zero, 0x12
  /* 117F68 801328E8 240E0006 */     addiu $t6, $zero, 6
  /* 117F6C 801328EC A08C0028 */        sb $t4, 0x28($a0)
  /* 117F70 801328F0 A08D0029 */        sb $t5, 0x29($a0)
  /* 117F74 801328F4 03E00008 */        jr $ra
  /* 117F78 801328F8 A08E002A */        sb $t6, 0x2a($a0)

  .L801328FC:
  /* 117F7C 801328FC 240F0017 */     addiu $t7, $zero, 0x17
  /* 117F80 80132900 24180010 */     addiu $t8, $zero, 0x10
  /* 117F84 80132904 241900A4 */     addiu $t9, $zero, 0xa4
  /* 117F88 80132908 A0820028 */        sb $v0, 0x28($a0)
  /* 117F8C 8013290C A0820029 */        sb $v0, 0x29($a0)
  /* 117F90 80132910 A082002A */        sb $v0, 0x2a($a0)
  /* 117F94 80132914 A08F0060 */        sb $t7, 0x60($a0)
  /* 117F98 80132918 A0980061 */        sb $t8, 0x61($a0)
  /* 117F9C 8013291C 03E00008 */        jr $ra
  /* 117FA0 80132920 A0990062 */        sb $t9, 0x62($a0)

  .L80132924:
  /* 117FA4 80132924 24090013 */     addiu $t1, $zero, 0x13
  /* 117FA8 80132928 240A0006 */     addiu $t2, $zero, 6
  /* 117FAC 8013292C A0880028 */        sb $t0, 0x28($a0)
  /* 117FB0 80132930 A0890029 */        sb $t1, 0x29($a0)
  /* 117FB4 80132934 A08A002A */        sb $t2, 0x2a($a0)
  /* 117FB8 80132938 03E00008 */        jr $ra
  /* 117FBC 8013293C 00000000 */       nop

glabel mnTitleRenderFire
  /* 117FC0 80132940 27BDFFC8 */     addiu $sp, $sp, -0x38
  /* 117FC4 80132944 AFB70030 */        sw $s7, 0x30($sp)
  /* 117FC8 80132948 AFB6002C */        sw $s6, 0x2c($sp)
  /* 117FCC 8013294C AFB50028 */        sw $s5, 0x28($sp)
  /* 117FD0 80132950 AFB40024 */        sw $s4, 0x24($sp)
  /* 117FD4 80132954 AFB30020 */        sw $s3, 0x20($sp)
  /* 117FD8 80132958 AFB2001C */        sw $s2, 0x1c($sp)
  /* 117FDC 8013295C AFB00014 */        sw $s0, 0x14($sp)
  /* 117FE0 80132960 AFBF0034 */        sw $ra, 0x34($sp)
  /* 117FE4 80132964 AFB10018 */        sw $s1, 0x18($sp)
  /* 117FE8 80132968 3C108004 */       lui $s0, %hi(gDisplayListHead)
  /* 117FEC 8013296C 3C148013 */       lui $s4, %hi(gMNTitleFireAlpha)
  /* 117FF0 80132970 3C15FCFF */       lui $s5, (0xFCFF97FF >> 16) # 4244609023
  /* 117FF4 80132974 3C16FF2C */       lui $s6, (0xFF2CFE7F >> 16) # 4281138815
  /* 117FF8 80132978 8C910074 */        lw $s1, 0x74($a0)
  /* 117FFC 8013297C 36D6FE7F */       ori $s6, $s6, (0xFF2CFE7F & 0xFFFF) # 4281138815
  /* 118000 80132980 36B597FF */       ori $s5, $s5, (0xFCFF97FF & 0xFFFF) # 4244609023
  /* 118004 80132984 26944464 */     addiu $s4, $s4, %lo(gMNTitleFireAlpha)
  /* 118008 80132988 261065B0 */     addiu $s0, $s0, %lo(gDisplayListHead)
  /* 11800C 8013298C 00009025 */        or $s2, $zero, $zero
  /* 118010 80132990 3C13FA00 */       lui $s3, 0xfa00
  /* 118014 80132994 24170002 */     addiu $s7, $zero, 2
  .L80132998:
  /* 118018 80132998 02002025 */        or $a0, $s0, $zero
  /* 11801C 8013299C 0C033046 */       jal func_ovl0_800CC118
  /* 118020 801329A0 02202825 */        or $a1, $s1, $zero
  /* 118024 801329A4 8E020000 */        lw $v0, ($s0) # gDisplayListHead + 0
  /* 118028 801329A8 02002025 */        or $a0, $s0, $zero
  /* 11802C 801329AC 02202825 */        or $a1, $s1, $zero
  /* 118030 801329B0 244E0008 */     addiu $t6, $v0, 8
  /* 118034 801329B4 AE0E0000 */        sw $t6, ($s0) # gDisplayListHead + 0
  /* 118038 801329B8 AC530000 */        sw $s3, ($v0)
  /* 11803C 801329BC 8E8F0000 */        lw $t7, ($s4) # gMNTitleFireAlpha + 0
  /* 118040 801329C0 31F800FF */      andi $t8, $t7, 0xff
  /* 118044 801329C4 AC580004 */        sw $t8, 4($v0)
  /* 118048 801329C8 8E020000 */        lw $v0, ($s0) # gDisplayListHead + 0
  /* 11804C 801329CC 24590008 */     addiu $t9, $v0, 8
  /* 118050 801329D0 AE190000 */        sw $t9, ($s0) # gDisplayListHead + 0
  /* 118054 801329D4 AC560004 */        sw $s6, 4($v0)
  /* 118058 801329D8 0C033206 */       jal func_ovl0_800CC818
  /* 11805C 801329DC AC550000 */        sw $s5, ($v0)
  /* 118060 801329E0 0C0333AB */       jal func_ovl0_800CCEAC
  /* 118064 801329E4 00000000 */       nop
  /* 118068 801329E8 26520001 */     addiu $s2, $s2, 1
  /* 11806C 801329EC 1657FFEA */       bne $s2, $s7, .L80132998
  /* 118070 801329F0 8E310008 */        lw $s1, 8($s1)
  /* 118074 801329F4 8FBF0034 */        lw $ra, 0x34($sp)
  /* 118078 801329F8 8FB00014 */        lw $s0, 0x14($sp)
  /* 11807C 801329FC 8FB10018 */        lw $s1, 0x18($sp)
  /* 118080 80132A00 8FB2001C */        lw $s2, 0x1c($sp)
  /* 118084 80132A04 8FB30020 */        lw $s3, 0x20($sp)
  /* 118088 80132A08 8FB40024 */        lw $s4, 0x24($sp)
  /* 11808C 80132A0C 8FB50028 */        lw $s5, 0x28($sp)
  /* 118090 80132A10 8FB6002C */        lw $s6, 0x2c($sp)
  /* 118094 80132A14 8FB70030 */        lw $s7, 0x30($sp)
  /* 118098 80132A18 03E00008 */        jr $ra
  /* 11809C 80132A1C 27BD0038 */     addiu $sp, $sp, 0x38

glabel mnTitleFadeInFire
  /* 1180A0 80132A20 8C8E007C */        lw $t6, 0x7c($a0)
  /* 1180A4 80132A24 24010001 */     addiu $at, $zero, 1
  /* 1180A8 80132A28 3C028013 */       lui $v0, %hi(gMNTitleFireAlpha)
  /* 1180AC 80132A2C 11C10008 */       beq $t6, $at, .L80132A50
  /* 1180B0 80132A30 24424464 */     addiu $v0, $v0, %lo(gMNTitleFireAlpha)
  /* 1180B4 80132A34 8C4F0000 */        lw $t7, ($v0) # gMNTitleFireAlpha + 0
  /* 1180B8 80132A38 240800FF */     addiu $t0, $zero, 0xff
  /* 1180BC 80132A3C 25F8000D */     addiu $t8, $t7, 0xd
  /* 1180C0 80132A40 2B010100 */      slti $at, $t8, 0x100
  /* 1180C4 80132A44 14200002 */      bnez $at, .L80132A50
  /* 1180C8 80132A48 AC580000 */        sw $t8, ($v0) # gMNTitleFireAlpha + 0
  /* 1180CC 80132A4C AC480000 */        sw $t0, ($v0) # gMNTitleFireAlpha + 0
  .L80132A50:
  /* 1180D0 80132A50 03E00008 */        jr $ra
  /* 1180D4 80132A54 00000000 */       nop

glabel mnTitleShowFire
  /* 1180D8 80132A58 240E00FF */     addiu $t6, $zero, 0xff
  /* 1180DC 80132A5C 3C018013 */       lui $at, %hi(gMNTitleFireAlpha)
  /* 1180E0 80132A60 AC2E4464 */        sw $t6, %lo(gMNTitleFireAlpha)($at)
  /* 1180E4 80132A64 03E00008 */        jr $ra
  /* 1180E8 80132A68 AC80007C */        sw $zero, 0x7c($a0)

glabel mnTitleChangeFireTexture
  /* 1180EC 80132A6C 8C8E0054 */        lw $t6, 0x54($a0)
  /* 1180F0 80132A70 3C188013 */       lui $t8, %hi(dMNTitleFireTextureOffsets)
  /* 1180F4 80132A74 3C198013 */       lui $t9, %hi(D_ovl10_801345A4)
  /* 1180F8 80132A78 000E7880 */       sll $t7, $t6, 2
  /* 1180FC 80132A7C 030FC021 */      addu $t8, $t8, $t7
  /* 118100 80132A80 8F1841F0 */        lw $t8, %lo(dMNTitleFireTextureOffsets)($t8)
  /* 118104 80132A84 8F3945A4 */        lw $t9, %lo(D_ovl10_801345A4)($t9)
  /* 118108 80132A88 00805825 */        or $t3, $a0, $zero
  /* 11810C 80132A8C 3C014140 */       lui $at, 0x4140
  /* 118110 80132A90 03195021 */      addu $t2, $t8, $t9
  /* 118114 80132A94 254C003C */     addiu $t4, $t2, 0x3c
  .L80132A98:
  /* 118118 80132A98 8D490000 */        lw $t1, ($t2)
  /* 11811C 80132A9C 254A000C */     addiu $t2, $t2, 0xc
  /* 118120 80132AA0 256B000C */     addiu $t3, $t3, 0xc
  /* 118124 80132AA4 AD690004 */        sw $t1, 4($t3)
  /* 118128 80132AA8 8D48FFF8 */        lw $t0, -8($t2)
  /* 11812C 80132AAC AD680008 */        sw $t0, 8($t3)
  /* 118130 80132AB0 8D49FFFC */        lw $t1, -4($t2)
  /* 118134 80132AB4 154CFFF8 */       bne $t2, $t4, .L80132A98
  /* 118138 80132AB8 AD69000C */        sw $t1, 0xc($t3)
  /* 11813C 80132ABC 8D490000 */        lw $t1, ($t2)
  /* 118140 80132AC0 240D0001 */     addiu $t5, $zero, 1
  /* 118144 80132AC4 AD690010 */        sw $t1, 0x10($t3)
  /* 118148 80132AC8 8D480004 */        lw $t0, 4($t2)
  /* 11814C 80132ACC AD680014 */        sw $t0, 0x14($t3)
  /* 118150 80132AD0 10A00005 */      beqz $a1, .L80132AE8
  /* 118154 80132AD4 A48D0024 */        sh $t5, 0x24($a0)
  /* 118158 80132AD8 3C014118 */       lui $at, (0x41180000 >> 16) # 9.5
  /* 11815C 80132ADC 44812000 */      mtc1 $at, $f4 # 9.5 to cop1
  /* 118160 80132AE0 10000004 */         b .L80132AF4
  /* 118164 80132AE4 E4840018 */      swc1 $f4, 0x18($a0)
  .L80132AE8:
  /* 118168 80132AE8 44813000 */      mtc1 $at, $f6 # 9.5 to cop1
  /* 11816C 80132AEC 00000000 */       nop
  /* 118170 80132AF0 E4860018 */      swc1 $f6, 0x18($a0)
  .L80132AF4:
  /* 118174 80132AF4 10A00005 */      beqz $a1, .L80132B0C
  /* 118178 80132AF8 3C014108 */       lui $at, 0x4108
  /* 11817C 80132AFC 3C0140E0 */       lui $at, (0x40E00000 >> 16) # 7.0
  /* 118180 80132B00 44814000 */      mtc1 $at, $f8 # 7.0 to cop1
  /* 118184 80132B04 10000004 */         b .L80132B18
  /* 118188 80132B08 E488001C */      swc1 $f8, 0x1c($a0)
  .L80132B0C:
  /* 11818C 80132B0C 44815000 */      mtc1 $at, $f10 # 7.0 to cop1
  /* 118190 80132B10 00000000 */       nop
  /* 118194 80132B14 E48A001C */      swc1 $f10, 0x1c($a0)
  .L80132B18:
  /* 118198 80132B18 8C8E0054 */        lw $t6, 0x54($a0)
  /* 11819C 80132B1C 25CF0001 */     addiu $t7, $t6, 1
  /* 1181A0 80132B20 29E1001E */      slti $at, $t7, 0x1e
  /* 1181A4 80132B24 14200002 */      bnez $at, .L80132B30
  /* 1181A8 80132B28 AC8F0054 */        sw $t7, 0x54($a0)
  /* 1181AC 80132B2C AC800054 */        sw $zero, 0x54($a0)
  .L80132B30:
  /* 1181B0 80132B30 03E00008 */        jr $ra
  /* 1181B4 80132B34 00000000 */       nop

glabel mnTitleAnimateFire
  /* 1181B8 80132B38 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 1181BC 80132B3C AFBF0014 */        sw $ra, 0x14($sp)
  /* 1181C0 80132B40 8C840074 */        lw $a0, 0x74($a0)
  /* 1181C4 80132B44 00002825 */        or $a1, $zero, $zero
  /* 1181C8 80132B48 8C8E0008 */        lw $t6, 8($a0)
  /* 1181CC 80132B4C 0C04CA9B */       jal mnTitleChangeFireTexture
  /* 1181D0 80132B50 AFAE0018 */        sw $t6, 0x18($sp)
  /* 1181D4 80132B54 8FA40018 */        lw $a0, 0x18($sp)
  /* 1181D8 80132B58 0C04CA9B */       jal mnTitleChangeFireTexture
  /* 1181DC 80132B5C 24050001 */     addiu $a1, $zero, 1
  /* 1181E0 80132B60 8FBF0014 */        lw $ra, 0x14($sp)
  /* 1181E4 80132B64 27BD0020 */     addiu $sp, $sp, 0x20
  /* 1181E8 80132B68 03E00008 */        jr $ra
  /* 1181EC 80132B6C 00000000 */       nop

glabel mnTitleCreateFire
  /* 1181F0 80132B70 27BDFF90 */     addiu $sp, $sp, -0x70
  /* 1181F4 80132B74 AFB00050 */        sw $s0, 0x50($sp)
  /* 1181F8 80132B78 3C108000 */       lui $s0, %hi(D_NF_80000001)
  /* 1181FC 80132B7C AFBF006C */        sw $ra, 0x6c($sp)
  /* 118200 80132B80 3C058013 */       lui $a1, %hi(mnTitleFadeInFire)
  /* 118204 80132B84 AFB60068 */        sw $s6, 0x68($sp)
  /* 118208 80132B88 AFB50064 */        sw $s5, 0x64($sp)
  /* 11820C 80132B8C AFB40060 */        sw $s4, 0x60($sp)
  /* 118210 80132B90 AFB3005C */        sw $s3, 0x5c($sp)
  /* 118214 80132B94 AFB20058 */        sw $s2, 0x58($sp)
  /* 118218 80132B98 AFB10054 */        sw $s1, 0x54($sp)
  /* 11821C 80132B9C F7BE0048 */      sdc1 $f30, 0x48($sp)
  /* 118220 80132BA0 F7BC0040 */      sdc1 $f28, 0x40($sp)
  /* 118224 80132BA4 F7BA0038 */      sdc1 $f26, 0x38($sp)
  /* 118228 80132BA8 F7B80030 */      sdc1 $f24, 0x30($sp)
  /* 11822C 80132BAC F7B60028 */      sdc1 $f22, 0x28($sp)
  /* 118230 80132BB0 F7B40020 */      sdc1 $f20, 0x20($sp)
  /* 118234 80132BB4 24A52A20 */     addiu $a1, $a1, %lo(mnTitleFadeInFire)
  /* 118238 80132BB8 02003825 */        or $a3, $s0, $zero
  /* 11823C 80132BBC 24040005 */     addiu $a0, $zero, 5
  /* 118240 80132BC0 0C00265A */       jal omMakeGObjSPAfter
  /* 118244 80132BC4 24060006 */     addiu $a2, $zero, 6
  /* 118248 80132BC8 10400054 */      beqz $v0, .L80132D1C
  /* 11824C 80132BCC 00409025 */        or $s2, $v0, $zero
  /* 118250 80132BD0 3C058013 */       lui $a1, %hi(mnTitleRenderFire)
  /* 118254 80132BD4 240EFFFF */     addiu $t6, $zero, -1
  /* 118258 80132BD8 AFAE0010 */        sw $t6, 0x10($sp)
  /* 11825C 80132BDC 24A52940 */     addiu $a1, $a1, %lo(mnTitleRenderFire)
  /* 118260 80132BE0 00402025 */        or $a0, $v0, $zero
  /* 118264 80132BE4 00003025 */        or $a2, $zero, $zero
  /* 118268 80132BE8 0C00277D */       jal omAddGObjRenderProc
  /* 11826C 80132BEC 02003825 */        or $a3, $s0, $zero
  /* 118270 80132BF0 3C058013 */       lui $a1, %hi(mnTitleAnimateFire)
  /* 118274 80132BF4 24A52B38 */     addiu $a1, $a1, %lo(mnTitleAnimateFire)
  /* 118278 80132BF8 02402025 */        or $a0, $s2, $zero
  /* 11827C 80132BFC 24060001 */     addiu $a2, $zero, 1
  /* 118280 80132C00 0C002062 */       jal omAddGObjCommonProc
  /* 118284 80132C04 24070001 */     addiu $a3, $zero, 1
  /* 118288 80132C08 3C01C180 */       lui $at, (0xC1800000 >> 16) # -16.0
  /* 11828C 80132C0C 4481F000 */      mtc1 $at, $f30 # -16.0 to cop1
  /* 118290 80132C10 3C014140 */       lui $at, (0x41400000 >> 16) # 12.0
  /* 118294 80132C14 4481E000 */      mtc1 $at, $f28 # 12.0 to cop1
  /* 118298 80132C18 3C014108 */       lui $at, (0x41080000 >> 16) # 8.5
  /* 11829C 80132C1C 4481D000 */      mtc1 $at, $f26 # 8.5 to cop1
  /* 1182A0 80132C20 3C0140E0 */       lui $at, (0x40E00000 >> 16) # 7.0
  /* 1182A4 80132C24 4481C000 */      mtc1 $at, $f24 # 7.0 to cop1
  /* 1182A8 80132C28 3C014118 */       lui $at, (0x41180000 >> 16) # 9.5
  /* 1182AC 80132C2C 4481B000 */      mtc1 $at, $f22 # 9.5 to cop1
  /* 1182B0 80132C30 3C014100 */       lui $at, (0x41000000 >> 16) # 8.0
  /* 1182B4 80132C34 3C148013 */       lui $s4, %hi(D_ovl10_801345A0)
  /* 1182B8 80132C38 3C138013 */       lui $s3, %hi(dMNTitleFireTextureOffsets)
  /* 1182BC 80132C3C 4481A000 */      mtc1 $at, $f20 # 8.0 to cop1
  /* 1182C0 80132C40 267341F0 */     addiu $s3, $s3, %lo(dMNTitleFireTextureOffsets)
  /* 1182C4 80132C44 269445A0 */     addiu $s4, $s4, %lo(D_ovl10_801345A0)
  /* 1182C8 80132C48 00008025 */        or $s0, $zero, $zero
  /* 1182CC 80132C4C 24160001 */     addiu $s6, $zero, 1
  /* 1182D0 80132C50 24150002 */     addiu $s5, $zero, 2
  .L80132C54:
  /* 1182D4 80132C54 12000003 */      beqz $s0, .L80132C64
  /* 1182D8 80132C58 2411000C */     addiu $s1, $zero, 0xc
  /* 1182DC 80132C5C 10000001 */         b .L80132C64
  /* 1182E0 80132C60 00008825 */        or $s1, $zero, $zero
  .L80132C64:
  /* 1182E4 80132C64 00117880 */       sll $t7, $s1, 2
  /* 1182E8 80132C68 026FC021 */      addu $t8, $s3, $t7
  /* 1182EC 80132C6C 8F190000 */        lw $t9, ($t8)
  /* 1182F0 80132C70 8E880004 */        lw $t0, 4($s4) # D_ovl10_801345A0 + 4
  /* 1182F4 80132C74 02402025 */        or $a0, $s2, $zero
  /* 1182F8 80132C78 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 1182FC 80132C7C 03282821 */      addu $a1, $t9, $t0
  /* 118300 80132C80 12000003 */      beqz $s0, .L80132C90
  /* 118304 80132C84 A4560024 */        sh $s6, 0x24($v0)
  /* 118308 80132C88 10000005 */         b .L80132CA0
  /* 11830C 80132C8C E4540058 */      swc1 $f20, 0x58($v0)
  .L80132C90:
  /* 118310 80132C90 3C01C200 */       lui $at, (0xC2000000 >> 16) # -32.0
  /* 118314 80132C94 44812000 */      mtc1 $at, $f4 # -32.0 to cop1
  /* 118318 80132C98 00000000 */       nop
  /* 11831C 80132C9C E4440058 */      swc1 $f4, 0x58($v0)
  .L80132CA0:
  /* 118320 80132CA0 52000004 */      beql $s0, $zero, .L80132CB4
  /* 118324 80132CA4 E45E005C */      swc1 $f30, 0x5c($v0)
  /* 118328 80132CA8 10000002 */         b .L80132CB4
  /* 11832C 80132CAC E454005C */      swc1 $f20, 0x5c($v0)
  /* 118330 80132CB0 E45E005C */      swc1 $f30, 0x5c($v0)
  .L80132CB4:
  /* 118334 80132CB4 52000004 */      beql $s0, $zero, .L80132CC8
  /* 118338 80132CB8 E45C0018 */      swc1 $f28, 0x18($v0)
  /* 11833C 80132CBC 10000002 */         b .L80132CC8
  /* 118340 80132CC0 E4560018 */      swc1 $f22, 0x18($v0)
  /* 118344 80132CC4 E45C0018 */      swc1 $f28, 0x18($v0)
  .L80132CC8:
  /* 118348 80132CC8 52000004 */      beql $s0, $zero, .L80132CDC
  /* 11834C 80132CCC E45A001C */      swc1 $f26, 0x1c($v0)
  /* 118350 80132CD0 10000002 */         b .L80132CDC
  /* 118354 80132CD4 E458001C */      swc1 $f24, 0x1c($v0)
  /* 118358 80132CD8 E45A001C */      swc1 $f26, 0x1c($v0)
  .L80132CDC:
  /* 11835C 80132CDC 26100001 */     addiu $s0, $s0, %lo(D_NF_80000001)
  /* 118360 80132CE0 1615FFDC */       bne $s0, $s5, .L80132C54
  /* 118364 80132CE4 AC510054 */        sw $s1, 0x54($v0)
  /* 118368 80132CE8 3C028013 */       lui $v0, %hi(gMNTitleFireAlphaUnused)
  /* 11836C 80132CEC 24424468 */     addiu $v0, $v0, %lo(gMNTitleFireAlphaUnused)
  /* 118370 80132CF0 AC400000 */        sw $zero, ($v0) # gMNTitleFireAlphaUnused + 0
  /* 118374 80132CF4 3C018013 */       lui $at, %hi(gMNTitleFireAlpha)
  /* 118378 80132CF8 AC204464 */        sw $zero, %lo(gMNTitleFireAlpha)($at)
  /* 11837C 80132CFC AE56007C */        sw $s6, 0x7c($s2)
  /* 118380 80132D00 3C0A800A */       lui $t2, %hi((gSceneData + 0x1))
  /* 118384 80132D04 914A4AD1 */       lbu $t2, %lo((gSceneData + 0x1))($t2)
  /* 118388 80132D08 2401002E */     addiu $at, $zero, 0x2e
  /* 11838C 80132D0C 51410004 */      beql $t2, $at, .L80132D20
  /* 118390 80132D10 8FBF006C */        lw $ra, 0x6c($sp)
  /* 118394 80132D14 0C04CA96 */       jal mnTitleShowFire
  /* 118398 80132D18 02402025 */        or $a0, $s2, $zero
  .L80132D1C:
  /* 11839C 80132D1C 8FBF006C */        lw $ra, 0x6c($sp)
  .L80132D20:
  /* 1183A0 80132D20 D7B40020 */      ldc1 $f20, 0x20($sp)
  /* 1183A4 80132D24 D7B60028 */      ldc1 $f22, 0x28($sp)
  /* 1183A8 80132D28 D7B80030 */      ldc1 $f24, 0x30($sp)
  /* 1183AC 80132D2C D7BA0038 */      ldc1 $f26, 0x38($sp)
  /* 1183B0 80132D30 D7BC0040 */      ldc1 $f28, 0x40($sp)
  /* 1183B4 80132D34 D7BE0048 */      ldc1 $f30, 0x48($sp)
  /* 1183B8 80132D38 8FB00050 */        lw $s0, 0x50($sp)
  /* 1183BC 80132D3C 8FB10054 */        lw $s1, 0x54($sp)
  /* 1183C0 80132D40 8FB20058 */        lw $s2, 0x58($sp)
  /* 1183C4 80132D44 8FB3005C */        lw $s3, 0x5c($sp)
  /* 1183C8 80132D48 8FB40060 */        lw $s4, 0x60($sp)
  /* 1183CC 80132D4C 8FB50064 */        lw $s5, 0x64($sp)
  /* 1183D0 80132D50 8FB60068 */        lw $s6, 0x68($sp)
  /* 1183D4 80132D54 03E00008 */        jr $ra
  /* 1183D8 80132D58 27BD0070 */     addiu $sp, $sp, 0x70

glabel mnTitleAnimateLogo
  /* 1183DC 80132D5C 8C820084 */        lw $v0, 0x84($a0)
  /* 1183E0 80132D60 8C830074 */        lw $v1, 0x74($a0)
  /* 1183E4 80132D64 3C013F00 */       lui $at, (0x3F000000 >> 16) # 0.5
  /* 1183E8 80132D68 8C4E0074 */        lw $t6, 0x74($v0)
  /* 1183EC 80132D6C 84680014 */        lh $t0, 0x14($v1)
  /* 1183F0 80132D70 44810000 */      mtc1 $at, $f0 # 0.5 to cop1
  /* 1183F4 80132D74 8DCF0010 */        lw $t7, 0x10($t6)
  /* 1183F8 80132D78 44889000 */      mtc1 $t0, $f18
  /* 1183FC 80132D7C 3C014320 */       lui $at, (0x43200000 >> 16) # 160.0
  /* 118400 80132D80 8DF80008 */        lw $t8, 8($t7)
  /* 118404 80132D84 44815000 */      mtc1 $at, $f10 # 160.0 to cop1
  /* 118408 80132D88 84690016 */        lh $t1, 0x16($v1)
  /* 11840C 80132D8C 8F190008 */        lw $t9, 8($t8)
  /* 118410 80132D90 3C0142F0 */       lui $at, (0x42F00000 >> 16) # 120.0
  /* 118414 80132D94 8F250008 */        lw $a1, 8($t9)
  /* 118418 80132D98 C4A40040 */      lwc1 $f4, 0x40($a1)
  /* 11841C 80132D9C E4640018 */      swc1 $f4, 0x18($v1)
  /* 118420 80132DA0 C4A60044 */      lwc1 $f6, 0x44($a1)
  /* 118424 80132DA4 46809120 */   cvt.s.w $f4, $f18
  /* 118428 80132DA8 E466001C */      swc1 $f6, 0x1c($v1)
  /* 11842C 80132DAC C4A8001C */      lwc1 $f8, 0x1c($a1)
  /* 118430 80132DB0 C4660018 */      lwc1 $f6, 0x18($v1)
  /* 118434 80132DB4 460A4400 */     add.s $f16, $f8, $f10
  /* 118438 80132DB8 46062202 */     mul.s $f8, $f4, $f6
  /* 11843C 80132DBC 44812000 */      mtc1 $at, $f4 # 120.0 to cop1
  /* 118440 80132DC0 46004282 */     mul.s $f10, $f8, $f0
  /* 118444 80132DC4 460A8481 */     sub.s $f18, $f16, $f10
  /* 118448 80132DC8 44898000 */      mtc1 $t1, $f16
  /* 11844C 80132DCC 00000000 */       nop
  /* 118450 80132DD0 468082A0 */   cvt.s.w $f10, $f16
  /* 118454 80132DD4 E4720058 */      swc1 $f18, 0x58($v1)
  /* 118458 80132DD8 C4A60020 */      lwc1 $f6, 0x20($a1)
  /* 11845C 80132DDC C472001C */      lwc1 $f18, 0x1c($v1)
  /* 118460 80132DE0 46062201 */     sub.s $f8, $f4, $f6
  /* 118464 80132DE4 46125102 */     mul.s $f4, $f10, $f18
  /* 118468 80132DE8 00000000 */       nop
  /* 11846C 80132DEC 46002182 */     mul.s $f6, $f4, $f0
  /* 118470 80132DF0 46064401 */     sub.s $f16, $f8, $f6
  /* 118474 80132DF4 03E00008 */        jr $ra
  /* 118478 80132DF8 E470005C */      swc1 $f16, 0x5c($v1)

glabel mnTitleRenderLogoNoIntro
  /* 11847C 80132DFC 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 118480 80132E00 AFBF0014 */        sw $ra, 0x14($sp)
  /* 118484 80132E04 AFA40020 */        sw $a0, 0x20($sp)
  /* 118488 80132E08 8C850074 */        lw $a1, 0x74($a0)
  /* 11848C 80132E0C 3C018013 */       lui $at, %hi(D_ovl10_80134438)
  /* 118490 80132E10 C4204438 */      lwc1 $f0, %lo(D_ovl10_80134438)($at)
  /* 118494 80132E14 C4A40018 */      lwc1 $f4, 0x18($a1)
  /* 118498 80132E18 4600203C */    c.lt.s $f4, $f0
  /* 11849C 80132E1C 00000000 */       nop
  /* 1184A0 80132E20 4503002B */     bc1tl .L80132ED0
  /* 1184A4 80132E24 8FBF0014 */        lw $ra, 0x14($sp)
  /* 1184A8 80132E28 C4A6001C */      lwc1 $f6, 0x1c($a1)
  /* 1184AC 80132E2C 3C078004 */       lui $a3, 0x8004
  /* 1184B0 80132E30 24E465B0 */     addiu $a0, $a3, 0x65b0
  /* 1184B4 80132E34 4600303C */    c.lt.s $f6, $f0
  /* 1184B8 80132E38 00000000 */       nop
  /* 1184BC 80132E3C 45030024 */     bc1tl .L80132ED0
  /* 1184C0 80132E40 8FBF0014 */        lw $ra, 0x14($sp)
  /* 1184C4 80132E44 0C033046 */       jal func_ovl0_800CC118
  /* 1184C8 80132E48 AFA5001C */        sw $a1, 0x1c($sp)
  /* 1184CC 80132E4C 3C078004 */       lui $a3, %hi(gDisplayListHead)
  /* 1184D0 80132E50 24E765B0 */     addiu $a3, $a3, %lo(gDisplayListHead)
  /* 1184D4 80132E54 8CE20000 */        lw $v0, ($a3) # gDisplayListHead + 0
  /* 1184D8 80132E58 8FA5001C */        lw $a1, 0x1c($sp)
  /* 1184DC 80132E5C 3C18FA00 */       lui $t8, 0xfa00
  /* 1184E0 80132E60 244F0008 */     addiu $t7, $v0, 8
  /* 1184E4 80132E64 ACEF0000 */        sw $t7, ($a3) # gDisplayListHead + 0
  /* 1184E8 80132E68 AC580000 */        sw $t8, ($v0)
  /* 1184EC 80132E6C 90A80028 */       lbu $t0, 0x28($a1)
  /* 1184F0 80132E70 90AB0029 */       lbu $t3, 0x29($a1)
  /* 1184F4 80132E74 90AF002A */       lbu $t7, 0x2a($a1)
  /* 1184F8 80132E78 00084E00 */       sll $t1, $t0, 0x18
  /* 1184FC 80132E7C 3C088013 */       lui $t0, %hi(gMNTitleLogoAlpha)
  /* 118500 80132E80 8D08446C */        lw $t0, %lo(gMNTitleLogoAlpha)($t0)
  /* 118504 80132E84 000B6400 */       sll $t4, $t3, 0x10
  /* 118508 80132E88 012C6825 */        or $t5, $t1, $t4
  /* 11850C 80132E8C 000FC200 */       sll $t8, $t7, 8
  /* 118510 80132E90 01B8C825 */        or $t9, $t5, $t8
  /* 118514 80132E94 310A00FF */      andi $t2, $t0, 0xff
  /* 118518 80132E98 032A5825 */        or $t3, $t9, $t2
  /* 11851C 80132E9C AC4B0004 */        sw $t3, 4($v0)
  /* 118520 80132EA0 8CE20000 */        lw $v0, ($a3) # gDisplayListHead + 0
  /* 118524 80132EA4 3C0CFCFF */       lui $t4, (0xFCFF97FF >> 16) # 4244609023
  /* 118528 80132EA8 3C0EFF2D */       lui $t6, (0xFF2DFEFF >> 16) # 4281204479
  /* 11852C 80132EAC 24490008 */     addiu $t1, $v0, 8
  /* 118530 80132EB0 ACE90000 */        sw $t1, ($a3) # gDisplayListHead + 0
  /* 118534 80132EB4 35CEFEFF */       ori $t6, $t6, (0xFF2DFEFF & 0xFFFF) # 4281204479
  /* 118538 80132EB8 358C97FF */       ori $t4, $t4, (0xFCFF97FF & 0xFFFF) # 4244609023
  /* 11853C 80132EBC AC4C0000 */        sw $t4, ($v0)
  /* 118540 80132EC0 AC4E0004 */        sw $t6, 4($v0)
  /* 118544 80132EC4 0C0333DD */       jal func_ovl0_800CCF74
  /* 118548 80132EC8 8FA40020 */        lw $a0, 0x20($sp)
  /* 11854C 80132ECC 8FBF0014 */        lw $ra, 0x14($sp)
  .L80132ED0:
  /* 118550 80132ED0 27BD0020 */     addiu $sp, $sp, 0x20
  /* 118554 80132ED4 03E00008 */        jr $ra
  /* 118558 80132ED8 00000000 */       nop

glabel mnTitleFadeOutLogo
  /* 11855C 80132EDC 8C820074 */        lw $v0, 0x74($a0)
  /* 118560 80132EE0 3C018013 */       lui $at, %hi(D_ovl10_8013443C)
  /* 118564 80132EE4 C420443C */      lwc1 $f0, %lo(D_ovl10_8013443C)($at)
  /* 118568 80132EE8 C4440018 */      lwc1 $f4, 0x18($v0)
  /* 11856C 80132EEC 4600203C */    c.lt.s $f4, $f0
  /* 118570 80132EF0 00000000 */       nop
  /* 118574 80132EF4 4501000F */      bc1t .L80132F34
  /* 118578 80132EF8 00000000 */       nop
  /* 11857C 80132EFC C446001C */      lwc1 $f6, 0x1c($v0)
  /* 118580 80132F00 3C028013 */       lui $v0, %hi(gMNTitleLogoAlpha)
  /* 118584 80132F04 2442446C */     addiu $v0, $v0, %lo(gMNTitleLogoAlpha)
  /* 118588 80132F08 4600303C */    c.lt.s $f6, $f0
  /* 11858C 80132F0C 00000000 */       nop
  /* 118590 80132F10 45010008 */      bc1t .L80132F34
  /* 118594 80132F14 00000000 */       nop
  /* 118598 80132F18 8C4E0000 */        lw $t6, ($v0) # gMNTitleLogoAlpha + 0
  /* 11859C 80132F1C 2419004C */     addiu $t9, $zero, 0x4c
  /* 1185A0 80132F20 25CFFFFC */     addiu $t7, $t6, -4
  /* 1185A4 80132F24 29E1004D */      slti $at, $t7, 0x4d
  /* 1185A8 80132F28 10200002 */      beqz $at, .L80132F34
  /* 1185AC 80132F2C AC4F0000 */        sw $t7, ($v0) # gMNTitleLogoAlpha + 0
  /* 1185B0 80132F30 AC590000 */        sw $t9, ($v0) # gMNTitleLogoAlpha + 0
  .L80132F34:
  /* 1185B4 80132F34 03E00008 */        jr $ra
  /* 1185B8 80132F38 00000000 */       nop

glabel mnTitleCreateLogoNoIntro
  /* 1185BC 80132F3C 27BDFFC8 */     addiu $sp, $sp, -0x38
  /* 1185C0 80132F40 3C188013 */       lui $t8, %hi(D_ovl10_801342D0)
  /* 1185C4 80132F44 3C198013 */       lui $t9, %hi(D_ovl10_801345A0)
  /* 1185C8 80132F48 8F3945A0 */        lw $t9, %lo(D_ovl10_801345A0)($t9)
  /* 1185CC 80132F4C 8F1842D0 */        lw $t8, %lo(D_ovl10_801342D0)($t8)
  /* 1185D0 80132F50 3C0E8013 */       lui $t6, %hi(mnTitleRenderLogoNoIntro)
  /* 1185D4 80132F54 AFBF0034 */        sw $ra, 0x34($sp)
  /* 1185D8 80132F58 3C078000 */       lui $a3, 0x8000
  /* 1185DC 80132F5C 25CE2DFC */     addiu $t6, $t6, %lo(mnTitleRenderLogoNoIntro)
  /* 1185E0 80132F60 240FFFFF */     addiu $t7, $zero, -1
  /* 1185E4 80132F64 24090001 */     addiu $t1, $zero, 1
  /* 1185E8 80132F68 240A0001 */     addiu $t2, $zero, 1
  /* 1185EC 80132F6C 03194021 */      addu $t0, $t8, $t9
  /* 1185F0 80132F70 AFA80020 */        sw $t0, 0x20($sp)
  /* 1185F4 80132F74 AFAA002C */        sw $t2, 0x2c($sp)
  /* 1185F8 80132F78 AFA90024 */        sw $t1, 0x24($sp)
  /* 1185FC 80132F7C AFAF001C */        sw $t7, 0x1c($sp)
  /* 118600 80132F80 AFAE0010 */        sw $t6, 0x10($sp)
  /* 118604 80132F84 AFA70018 */        sw $a3, 0x18($sp)
  /* 118608 80132F88 AFA00014 */        sw $zero, 0x14($sp)
  /* 11860C 80132F8C AFA00028 */        sw $zero, 0x28($sp)
  /* 118610 80132F90 2404000B */     addiu $a0, $zero, 0xb
  /* 118614 80132F94 00002825 */        or $a1, $zero, $zero
  /* 118618 80132F98 0C033414 */       jal func_ovl0_800CD050
  /* 11861C 80132F9C 2406000A */     addiu $a2, $zero, 0xa
  /* 118620 80132FA0 8C450074 */        lw $a1, 0x74($v0)
  /* 118624 80132FA4 240B0001 */     addiu $t3, $zero, 1
  /* 118628 80132FA8 240C00FF */     addiu $t4, $zero, 0xff
  /* 11862C 80132FAC 00002025 */        or $a0, $zero, $zero
  /* 118630 80132FB0 24060008 */     addiu $a2, $zero, 8
  /* 118634 80132FB4 A4AB0024 */        sh $t3, 0x24($a1)
  /* 118638 80132FB8 A0AC0028 */        sb $t4, 0x28($a1)
  /* 11863C 80132FBC A0A00029 */        sb $zero, 0x29($a1)
  /* 118640 80132FC0 0C04C9D9 */       jal mnTitleSetPosition
  /* 118644 80132FC4 A0A0002A */        sb $zero, 0x2a($a1)
  /* 118648 80132FC8 8FBF0034 */        lw $ra, 0x34($sp)
  /* 11864C 80132FCC 27BD0038 */     addiu $sp, $sp, 0x38
  /* 118650 80132FD0 03E00008 */        jr $ra
  /* 118654 80132FD4 00000000 */       nop

glabel mnTitleCreateLogo
  /* 118658 80132FD8 27BDFF98 */     addiu $sp, $sp, -0x68
  /* 11865C 80132FDC 3C0E800A */       lui $t6, %hi((gSceneData + 0x1))
  /* 118660 80132FE0 91CE4AD1 */       lbu $t6, %lo((gSceneData + 0x1))($t6)
  /* 118664 80132FE4 2401002E */     addiu $at, $zero, 0x2e
  /* 118668 80132FE8 AFBF0064 */        sw $ra, 0x64($sp)
  /* 11866C 80132FEC AFB60060 */        sw $s6, 0x60($sp)
  /* 118670 80132FF0 AFB5005C */        sw $s5, 0x5c($sp)
  /* 118674 80132FF4 AFB40058 */        sw $s4, 0x58($sp)
  /* 118678 80132FF8 AFB30054 */        sw $s3, 0x54($sp)
  /* 11867C 80132FFC AFB20050 */        sw $s2, 0x50($sp)
  /* 118680 80133000 AFB1004C */        sw $s1, 0x4c($sp)
  /* 118684 80133004 AFB00048 */        sw $s0, 0x48($sp)
  /* 118688 80133008 F7B60040 */      sdc1 $f22, 0x40($sp)
  /* 11868C 8013300C 11C10005 */       beq $t6, $at, .L80133024
  /* 118690 80133010 F7B40038 */      sdc1 $f20, 0x38($sp)
  /* 118694 80133014 0C04CBCF */       jal mnTitleCreateLogoNoIntro
  /* 118698 80133018 00000000 */       nop
  /* 11869C 8013301C 1000006C */         b .L801331D0
  /* 1186A0 80133020 8FBF0064 */        lw $ra, 0x64($sp)
  .L80133024:
  /* 1186A4 80133024 24040007 */     addiu $a0, $zero, 7
  /* 1186A8 80133028 00002825 */        or $a1, $zero, $zero
  /* 1186AC 8013302C 24060007 */     addiu $a2, $zero, 7
  /* 1186B0 80133030 0C00265A */       jal omMakeGObjSPAfter
  /* 1186B4 80133034 3C078000 */       lui $a3, 0x8000
  /* 1186B8 80133038 3C158013 */       lui $s5, %hi(D_ovl10_801345A0)
  /* 1186BC 8013303C 26B545A0 */     addiu $s5, $s5, %lo(D_ovl10_801345A0)
  /* 1186C0 80133040 8EAF0000 */        lw $t7, ($s5) # D_ovl10_801345A0 + 0
  /* 1186C4 80133044 3C180002 */       lui $t8, %hi(D_NF_00026020)
  /* 1186C8 80133048 27186020 */     addiu $t8, $t8, %lo(D_NF_00026020)
  /* 1186CC 8013304C 0040B025 */        or $s6, $v0, $zero
  /* 1186D0 80133050 00402025 */        or $a0, $v0, $zero
  /* 1186D4 80133054 00003025 */        or $a2, $zero, $zero
  /* 1186D8 80133058 0C003C48 */       jal func_8000F120
  /* 1186DC 8013305C 01F82821 */      addu $a1, $t7, $t8
  /* 1186E0 80133060 4480B000 */      mtc1 $zero, $f22
  /* 1186E4 80133064 8EB90000 */        lw $t9, ($s5) # D_ovl10_801345A0 + 0
  /* 1186E8 80133068 3C080002 */       lui $t0, %hi(D_NF_000251D0)
  /* 1186EC 8013306C 250851D0 */     addiu $t0, $t0, %lo(D_NF_000251D0)
  /* 1186F0 80133070 4406B000 */      mfc1 $a2, $f22
  /* 1186F4 80133074 02C02025 */        or $a0, $s6, $zero
  /* 1186F8 80133078 0C002F63 */       jal func_8000BD8C
  /* 1186FC 8013307C 03282821 */      addu $a1, $t9, $t0
  /* 118700 80133080 0C0037CD */       jal func_8000DF34
  /* 118704 80133084 02C02025 */        or $a0, $s6, $zero
  /* 118708 80133088 24040006 */     addiu $a0, $zero, 6
  /* 11870C 8013308C 00002825 */        or $a1, $zero, $zero
  /* 118710 80133090 24060007 */     addiu $a2, $zero, 7
  /* 118714 80133094 0C00265A */       jal omMakeGObjSPAfter
  /* 118718 80133098 3C078000 */       lui $a3, 0x8000
  /* 11871C 8013309C 3C05800D */       lui $a1, %hi(func_ovl0_800CCF00)
  /* 118720 801330A0 2409FFFF */     addiu $t1, $zero, -1
  /* 118724 801330A4 00409025 */        or $s2, $v0, $zero
  /* 118728 801330A8 AFA90010 */        sw $t1, 0x10($sp)
  /* 11872C 801330AC 24A5CF00 */     addiu $a1, $a1, %lo(func_ovl0_800CCF00)
  /* 118730 801330B0 00402025 */        or $a0, $v0, $zero
  /* 118734 801330B4 00003025 */        or $a2, $zero, $zero
  /* 118738 801330B8 0C00277D */       jal omAddGObjRenderProc
  /* 11873C 801330BC 3C078000 */       lui $a3, 0x8000
  /* 118740 801330C0 3C058013 */       lui $a1, %hi(mnTitleAnimateGObj)
  /* 118744 801330C4 24A525D4 */     addiu $a1, $a1, %lo(mnTitleAnimateGObj)
  /* 118748 801330C8 02402025 */        or $a0, $s2, $zero
  /* 11874C 801330CC 24060001 */     addiu $a2, $zero, 1
  /* 118750 801330D0 0C002062 */       jal omAddGObjCommonProc
  /* 118754 801330D4 24070001 */     addiu $a3, $zero, 1
  /* 118758 801330D8 AE560084 */        sw $s6, 0x84($s2)
  /* 11875C 801330DC 8ECA0074 */        lw $t2, 0x74($s6)
  /* 118760 801330E0 3C108013 */       lui $s0, %hi(dMNTitleAnimatedLogoOffsets)
  /* 118764 801330E4 3C148013 */       lui $s4, %hi(dMNTitleLogoOffset)
  /* 118768 801330E8 4480A000 */      mtc1 $zero, $f20
  /* 11876C 801330EC 269441EC */     addiu $s4, $s4, %lo(dMNTitleLogoOffset)
  /* 118770 801330F0 261041E0 */     addiu $s0, $s0, %lo(dMNTitleAnimatedLogoOffsets)
  /* 118774 801330F4 24130001 */     addiu $s3, $zero, 1
  /* 118778 801330F8 8D510010 */        lw $s1, 0x10($t2)
  .L801330FC:
  /* 11877C 801330FC 8E0B0000 */        lw $t3, ($s0) # dMNTitleAnimatedLogoOffsets + 0
  /* 118780 80133100 8EAC0000 */        lw $t4, ($s5) # D_ovl10_801345A0 + 0
  /* 118784 80133104 02402025 */        or $a0, $s2, $zero
  /* 118788 80133108 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 11878C 8013310C 016C2821 */      addu $a1, $t3, $t4
  /* 118790 80133110 A4530024 */        sh $s3, 0x24($v0)
  /* 118794 80133114 E4540058 */      swc1 $f20, 0x58($v0)
  /* 118798 80133118 E454005C */      swc1 $f20, 0x5c($v0)
  /* 11879C 8013311C A0400028 */        sb $zero, 0x28($v0)
  /* 1187A0 80133120 A0400029 */        sb $zero, 0x29($v0)
  /* 1187A4 80133124 A040002A */        sb $zero, 0x2a($v0)
  /* 1187A8 80133128 26100004 */     addiu $s0, $s0, 4
  /* 1187AC 8013312C E636001C */      swc1 $f22, 0x1c($s1)
  /* 1187B0 80133130 E6360020 */      swc1 $f22, 0x20($s1)
  /* 1187B4 80133134 1614FFF1 */       bne $s0, $s4, .L801330FC
  /* 1187B8 80133138 8E310008 */        lw $s1, 8($s1)
  /* 1187BC 8013313C 3C188013 */       lui $t8, %hi(dMNTitleLogoOffset)
  /* 1187C0 80133140 8F1841EC */        lw $t8, %lo(dMNTitleLogoOffset)($t8)
  /* 1187C4 80133144 8EB90000 */        lw $t9, ($s5) # D_ovl10_801345A0 + 0
  /* 1187C8 80133148 3C0D8013 */       lui $t5, %hi(mnTitleRenderLogoNoIntro)
  /* 1187CC 8013314C 3C098013 */       lui $t1, %hi(mnTitleAnimateLogo)
  /* 1187D0 80133150 25292D5C */     addiu $t1, $t1, %lo(mnTitleAnimateLogo)
  /* 1187D4 80133154 25AD2DFC */     addiu $t5, $t5, %lo(mnTitleRenderLogoNoIntro)
  /* 1187D8 80133158 3C058013 */       lui $a1, %hi(mnTitleFadeOutLogo)
  /* 1187DC 8013315C 3C0E8000 */       lui $t6, 0x8000
  /* 1187E0 80133160 240FFFFF */     addiu $t7, $zero, -1
  /* 1187E4 80133164 03194021 */      addu $t0, $t8, $t9
  /* 1187E8 80133168 AFA80020 */        sw $t0, 0x20($sp)
  /* 1187EC 8013316C AFAF001C */        sw $t7, 0x1c($sp)
  /* 1187F0 80133170 AFAE0018 */        sw $t6, 0x18($sp)
  /* 1187F4 80133174 24A52EDC */     addiu $a1, $a1, %lo(mnTitleFadeOutLogo)
  /* 1187F8 80133178 AFAD0010 */        sw $t5, 0x10($sp)
  /* 1187FC 8013317C AFA90028 */        sw $t1, 0x28($sp)
  /* 118800 80133180 2404000B */     addiu $a0, $zero, 0xb
  /* 118804 80133184 2406000A */     addiu $a2, $zero, 0xa
  /* 118808 80133188 3C078000 */       lui $a3, 0x8000
  /* 11880C 8013318C AFA00014 */        sw $zero, 0x14($sp)
  /* 118810 80133190 AFB30024 */        sw $s3, 0x24($sp)
  /* 118814 80133194 0C033414 */       jal func_ovl0_800CD050
  /* 118818 80133198 AFB3002C */        sw $s3, 0x2c($sp)
  /* 11881C 8013319C 8C430074 */        lw $v1, 0x74($v0)
  /* 118820 801331A0 240A00FF */     addiu $t2, $zero, 0xff
  /* 118824 801331A4 240B00FF */     addiu $t3, $zero, 0xff
  /* 118828 801331A8 A4730024 */        sh $s3, 0x24($v1)
  /* 11882C 801331AC A06A0028 */        sb $t2, 0x28($v1)
  /* 118830 801331B0 A0600029 */        sb $zero, 0x29($v1)
  /* 118834 801331B4 A060002A */        sb $zero, 0x2a($v1)
  /* 118838 801331B8 E636001C */      swc1 $f22, 0x1c($s1)
  /* 11883C 801331BC E6360020 */      swc1 $f22, 0x20($s1)
  /* 118840 801331C0 AC560084 */        sw $s6, 0x84($v0)
  /* 118844 801331C4 3C018013 */       lui $at, %hi(gMNTitleLogoAlpha)
  /* 118848 801331C8 AC2B446C */        sw $t3, %lo(gMNTitleLogoAlpha)($at)
  /* 11884C 801331CC 8FBF0064 */        lw $ra, 0x64($sp)
  .L801331D0:
  /* 118850 801331D0 D7B40038 */      ldc1 $f20, 0x38($sp)
  /* 118854 801331D4 D7B60040 */      ldc1 $f22, 0x40($sp)
  /* 118858 801331D8 8FB00048 */        lw $s0, 0x48($sp)
  /* 11885C 801331DC 8FB1004C */        lw $s1, 0x4c($sp)
  /* 118860 801331E0 8FB20050 */        lw $s2, 0x50($sp)
  /* 118864 801331E4 8FB30054 */        lw $s3, 0x54($sp)
  /* 118868 801331E8 8FB40058 */        lw $s4, 0x58($sp)
  /* 11886C 801331EC 8FB5005C */        lw $s5, 0x5c($sp)
  /* 118870 801331F0 8FB60060 */        lw $s6, 0x60($sp)
  /* 118874 801331F4 03E00008 */        jr $ra
  /* 118878 801331F8 27BD0068 */     addiu $sp, $sp, 0x68

glabel mnTitleCreateTextures
  /* 11887C 801331FC 27BDFFC0 */     addiu $sp, $sp, -0x40
  /* 118880 80133200 AFB00020 */        sw $s0, 0x20($sp)
  /* 118884 80133204 3C108000 */       lui $s0, %hi(D_NF_80000001)
  /* 118888 80133208 AFBF003C */        sw $ra, 0x3c($sp)
  /* 11888C 8013320C AFB60038 */        sw $s6, 0x38($sp)
  /* 118890 80133210 AFB50034 */        sw $s5, 0x34($sp)
  /* 118894 80133214 AFB40030 */        sw $s4, 0x30($sp)
  /* 118898 80133218 AFB3002C */        sw $s3, 0x2c($sp)
  /* 11889C 8013321C AFB20028 */        sw $s2, 0x28($sp)
  /* 1188A0 80133220 AFB10024 */        sw $s1, 0x24($sp)
  /* 1188A4 80133224 02003825 */        or $a3, $s0, $zero
  /* 1188A8 80133228 24040008 */     addiu $a0, $zero, 8
  /* 1188AC 8013322C 00002825 */        or $a1, $zero, $zero
  /* 1188B0 80133230 0C00265A */       jal omMakeGObjSPAfter
  /* 1188B4 80133234 24060008 */     addiu $a2, $zero, 8
  /* 1188B8 80133238 3C05800D */       lui $a1, %hi(func_ovl0_800CCF00)
  /* 1188BC 8013323C 240EFFFF */     addiu $t6, $zero, -1
  /* 1188C0 80133240 0040B025 */        or $s6, $v0, $zero
  /* 1188C4 80133244 AFAE0010 */        sw $t6, 0x10($sp)
  /* 1188C8 80133248 24A5CF00 */     addiu $a1, $a1, %lo(func_ovl0_800CCF00)
  /* 1188CC 8013324C 00402025 */        or $a0, $v0, $zero
  /* 1188D0 80133250 24060001 */     addiu $a2, $zero, 1
  /* 1188D4 80133254 0C00277D */       jal omAddGObjRenderProc
  /* 1188D8 80133258 02003825 */        or $a3, $s0, $zero
  /* 1188DC 8013325C 3C118013 */       lui $s1, %hi(dMNTitleTextureConfigs)
  /* 1188E0 80133260 3C138013 */       lui $s3, %hi(D_ovl10_801345A0)
  /* 1188E4 80133264 267345A0 */     addiu $s3, $s3, %lo(D_ovl10_801345A0)
  /* 1188E8 80133268 26314268 */     addiu $s1, $s1, %lo(dMNTitleTextureConfigs)
  /* 1188EC 8013326C 00008025 */        or $s0, $zero, $zero
  /* 1188F0 80133270 24150007 */     addiu $s5, $zero, 7
  /* 1188F4 80133274 24140001 */     addiu $s4, $zero, 1
  .L80133278:
  /* 1188F8 80133278 8E2F0008 */        lw $t7, 8($s1) # dMNTitleTextureConfigs + 8
  /* 1188FC 8013327C 8E780000 */        lw $t8, ($s3) # D_ovl10_801345A0 + 0
  /* 118900 80133280 02C02025 */        or $a0, $s6, $zero
  /* 118904 80133284 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 118908 80133288 01F82821 */      addu $a1, $t7, $t8
  /* 11890C 8013328C 00409025 */        or $s2, $v0, $zero
  /* 118910 80133290 A4540024 */        sh $s4, 0x24($v0)
  /* 118914 80133294 00002025 */        or $a0, $zero, $zero
  /* 118918 80133298 00402825 */        or $a1, $v0, $zero
  /* 11891C 8013329C 0C04C9D9 */       jal mnTitleSetPosition
  /* 118920 801332A0 02003025 */        or $a2, $s0, $zero
  /* 118924 801332A4 02402025 */        or $a0, $s2, $zero
  /* 118928 801332A8 0C04CA0B */       jal mnTitleSetColors
  /* 11892C 801332AC 02002825 */        or $a1, $s0, $zero
  /* 118930 801332B0 26100001 */     addiu $s0, $s0, %lo(D_NF_80000001)
  /* 118934 801332B4 1615FFF0 */       bne $s0, $s5, .L80133278
  /* 118938 801332B8 2631000C */     addiu $s1, $s1, 0xc
  /* 11893C 801332BC 8FBF003C */        lw $ra, 0x3c($sp)
  /* 118940 801332C0 8FB00020 */        lw $s0, 0x20($sp)
  /* 118944 801332C4 8FB10024 */        lw $s1, 0x24($sp)
  /* 118948 801332C8 8FB20028 */        lw $s2, 0x28($sp)
  /* 11894C 801332CC 8FB3002C */        lw $s3, 0x2c($sp)
  /* 118950 801332D0 8FB40030 */        lw $s4, 0x30($sp)
  /* 118954 801332D4 8FB50034 */        lw $s5, 0x34($sp)
  /* 118958 801332D8 8FB60038 */        lw $s6, 0x38($sp)
  /* 11895C 801332DC 03E00008 */        jr $ra
  /* 118960 801332E0 27BD0040 */     addiu $sp, $sp, 0x40

glabel mnTitleCreateTitleHeaderAndFooter
  /* 118964 801332E4 27BDFFA8 */     addiu $sp, $sp, -0x58
  /* 118968 801332E8 AFBF003C */        sw $ra, 0x3c($sp)
  /* 11896C 801332EC AFB70038 */        sw $s7, 0x38($sp)
  /* 118970 801332F0 AFB60034 */        sw $s6, 0x34($sp)
  /* 118974 801332F4 AFB50030 */        sw $s5, 0x30($sp)
  /* 118978 801332F8 AFB4002C */        sw $s4, 0x2c($sp)
  /* 11897C 801332FC AFB30028 */        sw $s3, 0x28($sp)
  /* 118980 80133300 AFB20024 */        sw $s2, 0x24($sp)
  /* 118984 80133304 AFB10020 */        sw $s1, 0x20($sp)
  /* 118988 80133308 AFB0001C */        sw $s0, 0x1c($sp)
  /* 11898C 8013330C 2404000A */     addiu $a0, $zero, 0xa
  /* 118990 80133310 00002825 */        or $a1, $zero, $zero
  /* 118994 80133314 24060008 */     addiu $a2, $zero, 8
  /* 118998 80133318 0C00265A */       jal omMakeGObjSPAfter
  /* 11899C 8013331C 3C078000 */       lui $a3, 0x8000
  /* 1189A0 80133320 3C178013 */       lui $s7, %hi(D_ovl10_801345A0)
  /* 1189A4 80133324 26F745A0 */     addiu $s7, $s7, %lo(D_ovl10_801345A0)
  /* 1189A8 80133328 8EEE0000 */        lw $t6, ($s7) # D_ovl10_801345A0 + 0
  /* 1189AC 8013332C 3C0F0002 */       lui $t7, %hi(D_NF_00026130)
  /* 1189B0 80133330 25EF6130 */     addiu $t7, $t7, %lo(D_NF_00026130)
  /* 1189B4 80133334 0040A025 */        or $s4, $v0, $zero
  /* 1189B8 80133338 00402025 */        or $a0, $v0, $zero
  /* 1189BC 8013333C 00003025 */        or $a2, $zero, $zero
  /* 1189C0 80133340 0C003C48 */       jal func_8000F120
  /* 1189C4 80133344 01CF2821 */      addu $a1, $t6, $t7
  /* 1189C8 80133348 8EF80000 */        lw $t8, ($s7) # D_ovl10_801345A0 + 0
  /* 1189CC 8013334C 3C190002 */       lui $t9, %hi(D_NF_00025350)
  /* 1189D0 80133350 27395350 */     addiu $t9, $t9, %lo(D_NF_00025350)
  /* 1189D4 80133354 02802025 */        or $a0, $s4, $zero
  /* 1189D8 80133358 24060000 */     addiu $a2, $zero, 0
  /* 1189DC 8013335C 0C002F63 */       jal func_8000BD8C
  /* 1189E0 80133360 03192821 */      addu $a1, $t8, $t9
  /* 1189E4 80133364 0C0037CD */       jal func_8000DF34
  /* 1189E8 80133368 02802025 */        or $a0, $s4, $zero
  /* 1189EC 8013336C 24040008 */     addiu $a0, $zero, 8
  /* 1189F0 80133370 00002825 */        or $a1, $zero, $zero
  /* 1189F4 80133374 24060008 */     addiu $a2, $zero, 8
  /* 1189F8 80133378 0C00265A */       jal omMakeGObjSPAfter
  /* 1189FC 8013337C 3C078000 */       lui $a3, 0x8000
  /* 118A00 80133380 3C05800D */       lui $a1, %hi(func_ovl0_800CCF00)
  /* 118A04 80133384 24A5CF00 */     addiu $a1, $a1, %lo(func_ovl0_800CCF00)
  /* 118A08 80133388 2408FFFF */     addiu $t0, $zero, -1
  /* 118A0C 8013338C 0040A825 */        or $s5, $v0, $zero
  /* 118A10 80133390 AFA80010 */        sw $t0, 0x10($sp)
  /* 118A14 80133394 AFA50040 */        sw $a1, 0x40($sp)
  /* 118A18 80133398 00402025 */        or $a0, $v0, $zero
  /* 118A1C 8013339C 24060001 */     addiu $a2, $zero, 1
  /* 118A20 801333A0 0C00277D */       jal omAddGObjRenderProc
  /* 118A24 801333A4 3C078000 */       lui $a3, 0x8000
  /* 118A28 801333A8 3C058013 */       lui $a1, %hi(mnTitleAnimateTitle)
  /* 118A2C 801333AC 24A526D4 */     addiu $a1, $a1, %lo(mnTitleAnimateTitle)
  /* 118A30 801333B0 02A02025 */        or $a0, $s5, $zero
  /* 118A34 801333B4 24060001 */     addiu $a2, $zero, 1
  /* 118A38 801333B8 0C002062 */       jal omAddGObjCommonProc
  /* 118A3C 801333BC 24070001 */     addiu $a3, $zero, 1
  /* 118A40 801333C0 AEB40084 */        sw $s4, 0x84($s5)
  /* 118A44 801333C4 8E890074 */        lw $t1, 0x74($s4)
  /* 118A48 801333C8 3C128013 */       lui $s2, %hi(dMNTitleTextureConfigs)
  /* 118A4C 801333CC 26524268 */     addiu $s2, $s2, %lo(dMNTitleTextureConfigs)
  /* 118A50 801333D0 00008025 */        or $s0, $zero, $zero
  /* 118A54 801333D4 24160001 */     addiu $s6, $zero, 1
  /* 118A58 801333D8 8D330010 */        lw $s3, 0x10($t1)
  .L801333DC:
  /* 118A5C 801333DC 8E4A0008 */        lw $t2, 8($s2) # dMNTitleTextureConfigs + 8
  /* 118A60 801333E0 8EEB0000 */        lw $t3, ($s7) # D_ovl10_801345A0 + 0
  /* 118A64 801333E4 02A02025 */        or $a0, $s5, $zero
  /* 118A68 801333E8 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 118A6C 801333EC 014B2821 */      addu $a1, $t2, $t3
  /* 118A70 801333F0 00408825 */        or $s1, $v0, $zero
  /* 118A74 801333F4 A4560024 */        sh $s6, 0x24($v0)
  /* 118A78 801333F8 02602025 */        or $a0, $s3, $zero
  /* 118A7C 801333FC 00402825 */        or $a1, $v0, $zero
  /* 118A80 80133400 0C04C9D9 */       jal mnTitleSetPosition
  /* 118A84 80133404 02003025 */        or $a2, $s0, $zero
  /* 118A88 80133408 02202025 */        or $a0, $s1, $zero
  /* 118A8C 8013340C 0C04CA0B */       jal mnTitleSetColors
  /* 118A90 80133410 02002825 */        or $a1, $s0, $zero
  /* 118A94 80133414 26100001 */     addiu $s0, $s0, 1
  /* 118A98 80133418 2A010005 */      slti $at, $s0, 5
  /* 118A9C 8013341C 2652000C */     addiu $s2, $s2, 0xc
  /* 118AA0 80133420 1420FFEE */      bnez $at, .L801333DC
  /* 118AA4 80133424 8E730008 */        lw $s3, 8($s3)
  /* 118AA8 80133428 AEB6007C */        sw $s6, 0x7c($s5)
  /* 118AAC 8013342C 24040009 */     addiu $a0, $zero, 9
  /* 118AB0 80133430 00002825 */        or $a1, $zero, $zero
  /* 118AB4 80133434 24060008 */     addiu $a2, $zero, 8
  /* 118AB8 80133438 0C00265A */       jal omMakeGObjSPAfter
  /* 118ABC 8013343C 3C078000 */       lui $a3, 0x8000
  /* 118AC0 80133440 240CFFFF */     addiu $t4, $zero, -1
  /* 118AC4 80133444 0040A825 */        or $s5, $v0, $zero
  /* 118AC8 80133448 AFAC0010 */        sw $t4, 0x10($sp)
  /* 118ACC 8013344C 00402025 */        or $a0, $v0, $zero
  /* 118AD0 80133450 8FA50040 */        lw $a1, 0x40($sp)
  /* 118AD4 80133454 32C600FF */      andi $a2, $s6, 0xff
  /* 118AD8 80133458 0C00277D */       jal omAddGObjRenderProc
  /* 118ADC 8013345C 3C078000 */       lui $a3, 0x8000
  /* 118AE0 80133460 3C058013 */       lui $a1, %hi(mnTitleUpdateHeaderAndFooterPosition)
  /* 118AE4 80133464 24A52704 */     addiu $a1, $a1, %lo(mnTitleUpdateHeaderAndFooterPosition)
  /* 118AE8 80133468 02A02025 */        or $a0, $s5, $zero
  /* 118AEC 8013346C 32C600FF */      andi $a2, $s6, 0xff
  /* 118AF0 80133470 0C002062 */       jal omAddGObjCommonProc
  /* 118AF4 80133474 02C03825 */        or $a3, $s6, $zero
  /* 118AF8 80133478 AEB40084 */        sw $s4, 0x84($s5)
  /* 118AFC 8013347C 3C128013 */       lui $s2, %hi(D_ovl10_801342A4)
  /* 118B00 80133480 265242A4 */     addiu $s2, $s2, %lo(D_ovl10_801342A4)
  /* 118B04 80133484 24140007 */     addiu $s4, $zero, 7
  /* 118B08 80133488 24100005 */     addiu $s0, $zero, 5
  .L8013348C:
  /* 118B0C 8013348C 8E4D0008 */        lw $t5, 8($s2) # D_ovl10_801342A4 + 8
  /* 118B10 80133490 8EEE0000 */        lw $t6, ($s7) # D_ovl10_801345A0 + 0
  /* 118B14 80133494 02A02025 */        or $a0, $s5, $zero
  /* 118B18 80133498 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 118B1C 8013349C 01AE2821 */      addu $a1, $t5, $t6
  /* 118B20 801334A0 00408825 */        or $s1, $v0, $zero
  /* 118B24 801334A4 A4560024 */        sh $s6, 0x24($v0)
  /* 118B28 801334A8 02602025 */        or $a0, $s3, $zero
  /* 118B2C 801334AC 00402825 */        or $a1, $v0, $zero
  /* 118B30 801334B0 0C04C9D9 */       jal mnTitleSetPosition
  /* 118B34 801334B4 02003025 */        or $a2, $s0, $zero
  /* 118B38 801334B8 02202025 */        or $a0, $s1, $zero
  /* 118B3C 801334BC 0C04CA0B */       jal mnTitleSetColors
  /* 118B40 801334C0 02002825 */        or $a1, $s0, $zero
  /* 118B44 801334C4 26100001 */     addiu $s0, $s0, 1
  /* 118B48 801334C8 2652000C */     addiu $s2, $s2, 0xc
  /* 118B4C 801334CC 1614FFEF */       bne $s0, $s4, .L8013348C
  /* 118B50 801334D0 8E730008 */        lw $s3, 8($s3)
  /* 118B54 801334D4 AEB6007C */        sw $s6, 0x7c($s5)
  /* 118B58 801334D8 8FBF003C */        lw $ra, 0x3c($sp)
  /* 118B5C 801334DC 8FB70038 */        lw $s7, 0x38($sp)
  /* 118B60 801334E0 8FB60034 */        lw $s6, 0x34($sp)
  /* 118B64 801334E4 8FB50030 */        lw $s5, 0x30($sp)
  /* 118B68 801334E8 8FB4002C */        lw $s4, 0x2c($sp)
  /* 118B6C 801334EC 8FB30028 */        lw $s3, 0x28($sp)
  /* 118B70 801334F0 8FB20024 */        lw $s2, 0x24($sp)
  /* 118B74 801334F4 8FB10020 */        lw $s1, 0x20($sp)
  /* 118B78 801334F8 8FB0001C */        lw $s0, 0x1c($sp)
  /* 118B7C 801334FC 03E00008 */        jr $ra
  /* 118B80 80133500 27BD0058 */     addiu $sp, $sp, 0x58

glabel mnTitleCreatePressStart
  /* 118B84 80133504 27BDFFC8 */     addiu $sp, $sp, -0x38
  /* 118B88 80133508 AFBF0024 */        sw $ra, 0x24($sp)
  /* 118B8C 8013350C AFB10020 */        sw $s1, 0x20($sp)
  /* 118B90 80133510 AFB0001C */        sw $s0, 0x1c($sp)
  /* 118B94 80133514 2404000A */     addiu $a0, $zero, 0xa
  /* 118B98 80133518 00002825 */        or $a1, $zero, $zero
  /* 118B9C 8013351C 24060008 */     addiu $a2, $zero, 8
  /* 118BA0 80133520 0C00265A */       jal omMakeGObjSPAfter
  /* 118BA4 80133524 3C078000 */       lui $a3, 0x8000
  /* 118BA8 80133528 3C0E8013 */       lui $t6, %hi(D_ovl10_801345A0)
  /* 118BAC 8013352C 8DCE45A0 */        lw $t6, %lo(D_ovl10_801345A0)($t6)
  /* 118BB0 80133530 3C0F0002 */       lui $t7, %hi(D_NF_000262C0)
  /* 118BB4 80133534 25EF62C0 */     addiu $t7, $t7, %lo(D_NF_000262C0)
  /* 118BB8 80133538 00408025 */        or $s0, $v0, $zero
  /* 118BBC 8013353C 00402025 */        or $a0, $v0, $zero
  /* 118BC0 80133540 00003025 */        or $a2, $zero, $zero
  /* 118BC4 80133544 0C003C48 */       jal func_8000F120
  /* 118BC8 80133548 01CF2821 */      addu $a1, $t6, $t7
  /* 118BCC 8013354C 3C188013 */       lui $t8, %hi(D_ovl10_801345A0)
  /* 118BD0 80133550 8F1845A0 */        lw $t8, %lo(D_ovl10_801345A0)($t8)
  /* 118BD4 80133554 3C190002 */       lui $t9, %hi(D_NF_000258D0)
  /* 118BD8 80133558 273958D0 */     addiu $t9, $t9, %lo(D_NF_000258D0)
  /* 118BDC 8013355C 02002025 */        or $a0, $s0, $zero
  /* 118BE0 80133560 24060000 */     addiu $a2, $zero, 0
  /* 118BE4 80133564 0C002F63 */       jal func_8000BD8C
  /* 118BE8 80133568 03192821 */      addu $a1, $t8, $t9
  /* 118BEC 8013356C 0C0037CD */       jal func_8000DF34
  /* 118BF0 80133570 02002025 */        or $a0, $s0, $zero
  /* 118BF4 80133574 8E080074 */        lw $t0, 0x74($s0)
  /* 118BF8 80133578 24040008 */     addiu $a0, $zero, 8
  /* 118BFC 8013357C 00002825 */        or $a1, $zero, $zero
  /* 118C00 80133580 8D090010 */        lw $t1, 0x10($t0)
  /* 118C04 80133584 24060009 */     addiu $a2, $zero, 9
  /* 118C08 80133588 3C078000 */       lui $a3, 0x8000
  /* 118C0C 8013358C 0C00265A */       jal omMakeGObjSPAfter
  /* 118C10 80133590 AFA9002C */        sw $t1, 0x2c($sp)
  /* 118C14 80133594 3C05800D */       lui $a1, %hi(func_ovl0_800CCF00)
  /* 118C18 80133598 240AFFFF */     addiu $t2, $zero, -1
  /* 118C1C 8013359C 00408825 */        or $s1, $v0, $zero
  /* 118C20 801335A0 AFAA0010 */        sw $t2, 0x10($sp)
  /* 118C24 801335A4 24A5CF00 */     addiu $a1, $a1, %lo(func_ovl0_800CCF00)
  /* 118C28 801335A8 00402025 */        or $a0, $v0, $zero
  /* 118C2C 801335AC 24060001 */     addiu $a2, $zero, 1
  /* 118C30 801335B0 0C00277D */       jal omAddGObjRenderProc
  /* 118C34 801335B4 3C078000 */       lui $a3, 0x8000
  /* 118C38 801335B8 3C058013 */       lui $a1, %hi(mnTitleAnimatePressStart)
  /* 118C3C 801335BC 24A526A4 */     addiu $a1, $a1, %lo(mnTitleAnimatePressStart)
  /* 118C40 801335C0 02202025 */        or $a0, $s1, $zero
  /* 118C44 801335C4 24060001 */     addiu $a2, $zero, 1
  /* 118C48 801335C8 0C002062 */       jal omAddGObjCommonProc
  /* 118C4C 801335CC 24070001 */     addiu $a3, $zero, 1
  /* 118C50 801335D0 AE300084 */        sw $s0, 0x84($s1)
  /* 118C54 801335D4 3C0B8013 */       lui $t3, %hi(D_ovl10_801342C4)
  /* 118C58 801335D8 3C0C8013 */       lui $t4, %hi(D_ovl10_801345A0)
  /* 118C5C 801335DC 8D8C45A0 */        lw $t4, %lo(D_ovl10_801345A0)($t4)
  /* 118C60 801335E0 8D6B42C4 */        lw $t3, %lo(D_ovl10_801342C4)($t3)
  /* 118C64 801335E4 02202025 */        or $a0, $s1, $zero
  /* 118C68 801335E8 0C0333F7 */       jal gcAppendSObjWithSprite
  /* 118C6C 801335EC 016C2821 */      addu $a1, $t3, $t4
  /* 118C70 801335F0 240D0001 */     addiu $t5, $zero, 1
  /* 118C74 801335F4 A44D0024 */        sh $t5, 0x24($v0)
  /* 118C78 801335F8 00408025 */        or $s0, $v0, $zero
  /* 118C7C 801335FC 8FA4002C */        lw $a0, 0x2c($sp)
  /* 118C80 80133600 00402825 */        or $a1, $v0, $zero
  /* 118C84 80133604 0C04C9D9 */       jal mnTitleSetPosition
  /* 118C88 80133608 24060007 */     addiu $a2, $zero, 7
  /* 118C8C 8013360C 02002025 */        or $a0, $s0, $zero
  /* 118C90 80133610 0C04CA0B */       jal mnTitleSetColors
  /* 118C94 80133614 24050007 */     addiu $a1, $zero, 7
  /* 118C98 80133618 240E0001 */     addiu $t6, $zero, 1
  /* 118C9C 8013361C AE2E007C */        sw $t6, 0x7c($s1)
  /* 118CA0 80133620 8FBF0024 */        lw $ra, 0x24($sp)
  /* 118CA4 80133624 8FB10020 */        lw $s1, 0x20($sp)
  /* 118CA8 80133628 8FB0001C */        lw $s0, 0x1c($sp)
  /* 118CAC 8013362C 03E00008 */        jr $ra
  /* 118CB0 80133630 27BD0038 */     addiu $sp, $sp, 0x38

glabel func_ovl10_80133634
  /* 118CB4 80133634 03E00008 */        jr $ra
  /* 118CB8 80133638 00000000 */       nop

glabel mnTitleAnimateSlashEffectGFX
  /* 118CBC 8013363C 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 118CC0 80133640 AFBF0014 */        sw $ra, 0x14($sp)
  /* 118CC4 80133644 8C8E007C */        lw $t6, 0x7c($a0)
  /* 118CC8 80133648 24010001 */     addiu $at, $zero, 1
  /* 118CCC 8013364C 51C10004 */      beql $t6, $at, .L80133660
  /* 118CD0 80133650 8FBF0014 */        lw $ra, 0x14($sp)
  /* 118CD4 80133654 0C0037CD */       jal func_8000DF34
  /* 118CD8 80133658 00000000 */       nop
  /* 118CDC 8013365C 8FBF0014 */        lw $ra, 0x14($sp)
  .L80133660:
  /* 118CE0 80133660 27BD0018 */     addiu $sp, $sp, 0x18
  /* 118CE4 80133664 03E00008 */        jr $ra
  /* 118CE8 80133668 00000000 */       nop

glabel mnTitleCreateSlashEffectGFX
  /* 118CEC 8013366C 3C0E800A */       lui $t6, %hi((gSceneData + 0x1))
  /* 118CF0 80133670 91CE4AD1 */       lbu $t6, %lo((gSceneData + 0x1))($t6)
  /* 118CF4 80133674 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 118CF8 80133678 2401002E */     addiu $at, $zero, 0x2e
  /* 118CFC 8013367C AFBF002C */        sw $ra, 0x2c($sp)
  /* 118D00 80133680 15C10036 */       bne $t6, $at, .L8013375C
  /* 118D04 80133684 AFB00028 */        sw $s0, 0x28($sp)
  /* 118D08 80133688 2404000C */     addiu $a0, $zero, 0xc
  /* 118D0C 8013368C 00002825 */        or $a1, $zero, $zero
  /* 118D10 80133690 2406000E */     addiu $a2, $zero, 0xe
  /* 118D14 80133694 0C00265A */       jal omMakeGObjSPAfter
  /* 118D18 80133698 3C078000 */       lui $a3, 0x8000
  /* 118D1C 8013369C 3C058001 */       lui $a1, %hi(odRenderDObjTreeDLLinksForGObj)
  /* 118D20 801336A0 240FFFFF */     addiu $t7, $zero, -1
  /* 118D24 801336A4 00408025 */        or $s0, $v0, $zero
  /* 118D28 801336A8 AFAF0010 */        sw $t7, 0x10($sp)
  /* 118D2C 801336AC 24A54768 */     addiu $a1, $a1, %lo(odRenderDObjTreeDLLinksForGObj)
  /* 118D30 801336B0 00402025 */        or $a0, $v0, $zero
  /* 118D34 801336B4 24060002 */     addiu $a2, $zero, 2
  /* 118D38 801336B8 0C00277D */       jal omAddGObjRenderProc
  /* 118D3C 801336BC 3C078000 */       lui $a3, 0x8000
  /* 118D40 801336C0 3C028013 */       lui $v0, %hi(D_ovl10_801345A0)
  /* 118D44 801336C4 8C4245A0 */        lw $v0, %lo(D_ovl10_801345A0)($v0)
  /* 118D48 801336C8 3C180003 */       lui $t8, %hi(D_NF_00028DA8)
  /* 118D4C 801336CC 3C190003 */       lui $t9, %hi(D_NF_000287D8)
  /* 118D50 801336D0 273987D8 */     addiu $t9, $t9, %lo(D_NF_000287D8)
  /* 118D54 801336D4 27188DA8 */     addiu $t8, $t8, %lo(D_NF_00028DA8)
  /* 118D58 801336D8 2408001C */     addiu $t0, $zero, 0x1c
  /* 118D5C 801336DC AFA80010 */        sw $t0, 0x10($sp)
  /* 118D60 801336E0 02002025 */        or $a0, $s0, $zero
  /* 118D64 801336E4 00003825 */        or $a3, $zero, $zero
  /* 118D68 801336E8 AFA00014 */        sw $zero, 0x14($sp)
  /* 118D6C 801336EC AFA00018 */        sw $zero, 0x18($sp)
  /* 118D70 801336F0 00582821 */      addu $a1, $v0, $t8
  /* 118D74 801336F4 0C003DC8 */       jal func_8000F720
  /* 118D78 801336F8 00593021 */      addu $a2, $v0, $t9
  /* 118D7C 801336FC 3C098013 */       lui $t1, %hi(D_ovl10_801345A0)
  /* 118D80 80133700 8D2945A0 */        lw $t1, %lo(D_ovl10_801345A0)($t1)
  /* 118D84 80133704 3C0A0002 */       lui $t2, %hi(D_NF_00025E70)
  /* 118D88 80133708 254A5E70 */     addiu $t2, $t2, %lo(D_NF_00025E70)
  /* 118D8C 8013370C 02002025 */        or $a0, $s0, $zero
  /* 118D90 80133710 24060000 */     addiu $a2, $zero, 0
  /* 118D94 80133714 0C002F63 */       jal func_8000BD8C
  /* 118D98 80133718 012A2821 */      addu $a1, $t1, $t2
  /* 118D9C 8013371C 3C0B8013 */       lui $t3, %hi(D_ovl10_801345A0)
  /* 118DA0 80133720 8D6B45A0 */        lw $t3, %lo(D_ovl10_801345A0)($t3)
  /* 118DA4 80133724 3C0C0002 */       lui $t4, %hi(D_NF_00025F60)
  /* 118DA8 80133728 258C5F60 */     addiu $t4, $t4, %lo(D_NF_00025F60)
  /* 118DAC 8013372C 02002025 */        or $a0, $s0, $zero
  /* 118DB0 80133730 24060000 */     addiu $a2, $zero, 0
  /* 118DB4 80133734 0C002F8A */       jal func_8000BE28
  /* 118DB8 80133738 016C2821 */      addu $a1, $t3, $t4
  /* 118DBC 8013373C 0C0037CD */       jal func_8000DF34
  /* 118DC0 80133740 02002025 */        or $a0, $s0, $zero
  /* 118DC4 80133744 3C058001 */       lui $a1, %hi(func_8000DF34)
  /* 118DC8 80133748 24A5DF34 */     addiu $a1, $a1, %lo(func_8000DF34)
  /* 118DCC 8013374C 02002025 */        or $a0, $s0, $zero
  /* 118DD0 80133750 24060001 */     addiu $a2, $zero, 1
  /* 118DD4 80133754 0C002062 */       jal omAddGObjCommonProc
  /* 118DD8 80133758 24070001 */     addiu $a3, $zero, 1
  .L8013375C:
  /* 118DDC 8013375C 8FBF002C */        lw $ra, 0x2c($sp)
  /* 118DE0 80133760 8FB00028 */        lw $s0, 0x28($sp)
  /* 118DE4 80133764 27BD0030 */     addiu $sp, $sp, 0x30
  /* 118DE8 80133768 03E00008 */        jr $ra
  /* 118DEC 8013376C 00000000 */       nop

glabel mnTitleUpdateFireBGOverlayColor
  /* 118DF0 80133770 3C028013 */       lui $v0, %hi(gMNTitleTransitionFramesElapsed)
  /* 118DF4 80133774 8C42445C */        lw $v0, %lo(gMNTitleTransitionFramesElapsed)($v0)
  /* 118DF8 80133778 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 118DFC 8013377C 3C0E8013 */       lui $t6, %hi(gMNTitleFireBGOverlayCameraGObj)
  /* 118E00 80133780 8DCE4448 */        lw $t6, %lo(gMNTitleFireBGOverlayCameraGObj)($t6)
  /* 118E04 80133784 AFBF0014 */        sw $ra, 0x14($sp)
  /* 118E08 80133788 AFA40020 */        sw $a0, 0x20($sp)
  /* 118E0C 8013378C 28410028 */      slti $at, $v0, 0x28
  /* 118E10 80133790 142000BC */      bnez $at, .L80133A84
  /* 118E14 80133794 8DC60074 */        lw $a2, 0x74($t6)
  /* 118E18 80133798 2841006F */      slti $at, $v0, 0x6f
  /* 118E1C 8013379C 10200019 */      beqz $at, .L80133804
  /* 118E20 801337A0 3C048013 */       lui $a0, %hi(gMNTitleFireBGOverlayRed)
  /* 118E24 801337A4 3C01437F */       lui $at, (0x437F0000 >> 16) # 255.0
  /* 118E28 801337A8 44811000 */      mtc1 $at, $f2 # 255.0 to cop1
  /* 118E2C 801337AC 2484447C */     addiu $a0, $a0, %lo(gMNTitleFireBGOverlayRed)
  /* 118E30 801337B0 3C014080 */       lui $at, (0x40800000 >> 16) # 4.0
  /* 118E34 801337B4 44813000 */      mtc1 $at, $f6 # 4.0 to cop1
  /* 118E38 801337B8 C4840000 */      lwc1 $f4, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 118E3C 801337BC 3C088013 */       lui $t0, %hi(gMNTitleFireBGOverlayBlue)
  /* 118E40 801337C0 3C078013 */       lui $a3, %hi(gMNTitleFireBGOverlayGreen)
  /* 118E44 801337C4 46062200 */     add.s $f8, $f4, $f6
  /* 118E48 801337C8 24E74480 */     addiu $a3, $a3, %lo(gMNTitleFireBGOverlayGreen)
  /* 118E4C 801337CC 25084484 */     addiu $t0, $t0, %lo(gMNTitleFireBGOverlayBlue)
  /* 118E50 801337D0 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayGreen)
  /* 118E54 801337D4 E4880000 */      swc1 $f8, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 118E58 801337D8 C4800000 */      lwc1 $f0, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 118E5C 801337DC 4600103C */    c.lt.s $f2, $f0
  /* 118E60 801337E0 00000000 */       nop
  /* 118E64 801337E4 45000003 */      bc1f .L801337F4
  /* 118E68 801337E8 00000000 */       nop
  /* 118E6C 801337EC E4820000 */      swc1 $f2, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 118E70 801337F0 C4800000 */      lwc1 $f0, ($a0) # gMNTitleFireBGOverlayRed + 0
  .L801337F4:
  /* 118E74 801337F4 C4224480 */      lwc1 $f2, %lo(gMNTitleFireBGOverlayGreen)($at)
  /* 118E78 801337F8 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayBlue)
  /* 118E7C 801337FC 1000006D */         b .L801339B4
  /* 118E80 80133800 C42C4484 */      lwc1 $f12, %lo(gMNTitleFireBGOverlayBlue)($at)
  .L80133804:
  /* 118E84 80133804 3C038013 */       lui $v1, %hi(gMNTitleFireBGOverlayTimer)
  /* 118E88 80133808 24634478 */     addiu $v1, $v1, %lo(gMNTitleFireBGOverlayTimer)
  /* 118E8C 8013380C 8C620000 */        lw $v0, ($v1) # gMNTitleFireBGOverlayTimer + 0
  /* 118E90 80133810 1440004C */      bnez $v0, .L80133944
  /* 118E94 80133814 240F0104 */     addiu $t7, $zero, 0x104
  /* 118E98 80133818 AC6F0000 */        sw $t7, ($v1) # gMNTitleFireBGOverlayTimer + 0
  /* 118E9C 8013381C 24040007 */     addiu $a0, $zero, 7
  /* 118EA0 80133820 0C00628C */       jal lbRandom_GetTimeByteRange
  /* 118EA4 80133824 AFA6001C */        sw $a2, 0x1c($sp)
  /* 118EA8 80133828 3C058013 */       lui $a1, %hi(gMNTitleFireBGOverlayIndex)
  /* 118EAC 8013382C 24A54494 */     addiu $a1, $a1, %lo(gMNTitleFireBGOverlayIndex)
  /* 118EB0 80133830 8CB80000 */        lw $t8, ($a1) # gMNTitleFireBGOverlayIndex + 0
  /* 118EB4 80133834 8FA6001C */        lw $a2, 0x1c($sp)
  /* 118EB8 80133838 00401825 */        or $v1, $v0, $zero
  /* 118EBC 8013383C 14580006 */       bne $v0, $t8, .L80133858
  /* 118EC0 80133840 3C048013 */       lui $a0, %hi(gMNTitleFireBGOverlayRed)
  /* 118EC4 80133844 24430001 */     addiu $v1, $v0, 1
  /* 118EC8 80133848 28610007 */      slti $at, $v1, 7
  /* 118ECC 8013384C 14200002 */      bnez $at, .L80133858
  /* 118ED0 80133850 00000000 */       nop
  /* 118ED4 80133854 00001825 */        or $v1, $zero, $zero
  .L80133858:
  /* 118ED8 80133858 3C198013 */       lui $t9, %hi(dMNTitleFireBGOverlayColorArrayRed)
  /* 118EDC 8013385C ACA30000 */        sw $v1, ($a1) # gMNTitleFireBGOverlayIndex + 0
  /* 118EE0 80133860 0323C821 */      addu $t9, $t9, $v1
  /* 118EE4 80133864 93394318 */       lbu $t9, %lo(dMNTitleFireBGOverlayColorArrayRed)($t9)
  /* 118EE8 80133868 3C0142A0 */       lui $at, (0x42A00000 >> 16) # 80.0
  /* 118EEC 8013386C 44810000 */      mtc1 $at, $f0 # 80.0 to cop1
  /* 118EF0 80133870 44995000 */      mtc1 $t9, $f10
  /* 118EF4 80133874 3C078013 */       lui $a3, %hi(gMNTitleFireBGOverlayGreen)
  /* 118EF8 80133878 3C088013 */       lui $t0, %hi(gMNTitleFireBGOverlayBlue)
  /* 118EFC 8013387C 25084484 */     addiu $t0, $t0, %lo(gMNTitleFireBGOverlayBlue)
  /* 118F00 80133880 24E74480 */     addiu $a3, $a3, %lo(gMNTitleFireBGOverlayGreen)
  /* 118F04 80133884 2484447C */     addiu $a0, $a0, %lo(gMNTitleFireBGOverlayRed)
  /* 118F08 80133888 07210005 */      bgez $t9, .L801338A0
  /* 118F0C 8013388C 46805420 */   cvt.s.w $f16, $f10
  /* 118F10 80133890 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 118F14 80133894 44819000 */      mtc1 $at, $f18 # 4294967300.0 to cop1
  /* 118F18 80133898 00000000 */       nop
  /* 118F1C 8013389C 46128400 */     add.s $f16, $f16, $f18
  .L801338A0:
  /* 118F20 801338A0 C4840000 */      lwc1 $f4, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 118F24 801338A4 3C098013 */       lui $t1, %hi(dMNTitleFireBGOverlayColorArrayGreen)
  /* 118F28 801338A8 01234821 */      addu $t1, $t1, $v1
  /* 118F2C 801338AC 46048181 */     sub.s $f6, $f16, $f4
  /* 118F30 801338B0 91294320 */       lbu $t1, %lo(dMNTitleFireBGOverlayColorArrayGreen)($t1)
  /* 118F34 801338B4 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaRed)
  /* 118F38 801338B8 46003203 */     div.s $f8, $f6, $f0
  /* 118F3C 801338BC 44895000 */      mtc1 $t1, $f10
  /* 118F40 801338C0 00000000 */       nop
  /* 118F44 801338C4 468054A0 */   cvt.s.w $f18, $f10
  /* 118F48 801338C8 05210005 */      bgez $t1, .L801338E0
  /* 118F4C 801338CC E4284488 */      swc1 $f8, %lo(gMNTitleFireBGOverlayDeltaRed)($at)
  /* 118F50 801338D0 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 118F54 801338D4 44818000 */      mtc1 $at, $f16 # 4294967300.0 to cop1
  /* 118F58 801338D8 00000000 */       nop
  /* 118F5C 801338DC 46109480 */     add.s $f18, $f18, $f16
  .L801338E0:
  /* 118F60 801338E0 C4E40000 */      lwc1 $f4, ($a3) # gMNTitleFireBGOverlayGreen + 0
  /* 118F64 801338E4 3C0A8013 */       lui $t2, %hi(dMNTitleFireBGOverlayColorArrayBlue)
  /* 118F68 801338E8 01435021 */      addu $t2, $t2, $v1
  /* 118F6C 801338EC 46049181 */     sub.s $f6, $f18, $f4
  /* 118F70 801338F0 914A4328 */       lbu $t2, %lo(dMNTitleFireBGOverlayColorArrayBlue)($t2)
  /* 118F74 801338F4 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaGreen)
  /* 118F78 801338F8 46003203 */     div.s $f8, $f6, $f0
  /* 118F7C 801338FC 448A5000 */      mtc1 $t2, $f10
  /* 118F80 80133900 00000000 */       nop
  /* 118F84 80133904 46805420 */   cvt.s.w $f16, $f10
  /* 118F88 80133908 05410005 */      bgez $t2, .L80133920
  /* 118F8C 8013390C E428448C */      swc1 $f8, %lo(gMNTitleFireBGOverlayDeltaGreen)($at)
  /* 118F90 80133910 3C014F80 */       lui $at, (0x4F800000 >> 16) # 4294967300.0
  /* 118F94 80133914 44819000 */      mtc1 $at, $f18 # 4294967300.0 to cop1
  /* 118F98 80133918 00000000 */       nop
  /* 118F9C 8013391C 46128400 */     add.s $f16, $f16, $f18
  .L80133920:
  /* 118FA0 80133920 C5040000 */      lwc1 $f4, ($t0) # gMNTitleFireBGOverlayBlue + 0
  /* 118FA4 80133924 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaBlue)
  /* 118FA8 80133928 3C028013 */       lui $v0, %hi(gMNTitleFireBGOverlayTimer)
  /* 118FAC 8013392C 46048181 */     sub.s $f6, $f16, $f4
  /* 118FB0 80133930 3C038013 */       lui $v1, %hi(gMNTitleFireBGOverlayTimer)
  /* 118FB4 80133934 24634478 */     addiu $v1, $v1, %lo(gMNTitleFireBGOverlayTimer)
  /* 118FB8 80133938 8C424478 */        lw $v0, %lo(gMNTitleFireBGOverlayTimer)($v0)
  /* 118FBC 8013393C 46003203 */     div.s $f8, $f6, $f0
  /* 118FC0 80133940 E4284490 */      swc1 $f8, %lo(gMNTitleFireBGOverlayDeltaBlue)($at)
  .L80133944:
  /* 118FC4 80133944 3C048013 */       lui $a0, %hi(gMNTitleFireBGOverlayRed)
  /* 118FC8 80133948 3C078013 */       lui $a3, %hi(gMNTitleFireBGOverlayGreen)
  /* 118FCC 8013394C 3C088013 */       lui $t0, %hi(gMNTitleFireBGOverlayBlue)
  /* 118FD0 80133950 25084484 */     addiu $t0, $t0, %lo(gMNTitleFireBGOverlayBlue)
  /* 118FD4 80133954 24E74480 */     addiu $a3, $a3, %lo(gMNTitleFireBGOverlayGreen)
  /* 118FD8 80133958 2484447C */     addiu $a0, $a0, %lo(gMNTitleFireBGOverlayRed)
  /* 118FDC 8013395C 28410050 */      slti $at, $v0, 0x50
  /* 118FE0 80133960 C4800000 */      lwc1 $f0, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 118FE4 80133964 C4E20000 */      lwc1 $f2, ($a3) # gMNTitleFireBGOverlayGreen + 0
  /* 118FE8 80133968 14200010 */      bnez $at, .L801339AC
  /* 118FEC 8013396C C50C0000 */      lwc1 $f12, ($t0) # gMNTitleFireBGOverlayBlue + 0
  /* 118FF0 80133970 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaRed)
  /* 118FF4 80133974 C42A4488 */      lwc1 $f10, %lo(gMNTitleFireBGOverlayDeltaRed)($at)
  /* 118FF8 80133978 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaGreen)
  /* 118FFC 8013397C 460A0480 */     add.s $f18, $f0, $f10
  /* 119000 80133980 E4920000 */      swc1 $f18, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 119004 80133984 C430448C */      lwc1 $f16, %lo(gMNTitleFireBGOverlayDeltaGreen)($at)
  /* 119008 80133988 3C018013 */       lui $at, %hi(gMNTitleFireBGOverlayDeltaBlue)
  /* 11900C 8013398C C4800000 */      lwc1 $f0, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 119010 80133990 46101100 */     add.s $f4, $f2, $f16
  /* 119014 80133994 E4E40000 */      swc1 $f4, ($a3) # gMNTitleFireBGOverlayGreen + 0
  /* 119018 80133998 C4264490 */      lwc1 $f6, %lo(gMNTitleFireBGOverlayDeltaBlue)($at)
  /* 11901C 8013399C C4E20000 */      lwc1 $f2, ($a3) # gMNTitleFireBGOverlayGreen + 0
  /* 119020 801339A0 46066200 */     add.s $f8, $f12, $f6
  /* 119024 801339A4 E5080000 */      swc1 $f8, ($t0) # gMNTitleFireBGOverlayBlue + 0
  /* 119028 801339A8 C50C0000 */      lwc1 $f12, ($t0) # gMNTitleFireBGOverlayBlue + 0
  .L801339AC:
  /* 11902C 801339AC 244BFFFF */     addiu $t3, $v0, -1
  /* 119030 801339B0 AC6B0000 */        sw $t3, ($v1) # gMNTitleFireBGOverlayTimer + 0
  .L801339B4:
  /* 119034 801339B4 3C01437F */       lui $at, (0x437F0000 >> 16) # 255.0
  /* 119038 801339B8 44817000 */      mtc1 $at, $f14 # 255.0 to cop1
  /* 11903C 801339BC 00000000 */       nop
  /* 119040 801339C0 4600703C */    c.lt.s $f14, $f0
  /* 119044 801339C4 00000000 */       nop
  /* 119048 801339C8 45020004 */     bc1fl .L801339DC
  /* 11904C 801339CC 4602703C */    c.lt.s $f14, $f2
  /* 119050 801339D0 E48E0000 */      swc1 $f14, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 119054 801339D4 C4800000 */      lwc1 $f0, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 119058 801339D8 4602703C */    c.lt.s $f14, $f2
  .L801339DC:
  /* 11905C 801339DC 00000000 */       nop
  /* 119060 801339E0 45020004 */     bc1fl .L801339F4
  /* 119064 801339E4 460C703C */    c.lt.s $f14, $f12
  /* 119068 801339E8 E4EE0000 */      swc1 $f14, ($a3) # gMNTitleFireBGOverlayGreen + 0
  /* 11906C 801339EC C4E20000 */      lwc1 $f2, ($a3) # gMNTitleFireBGOverlayGreen + 0
  /* 119070 801339F0 460C703C */    c.lt.s $f14, $f12
  .L801339F4:
  /* 119074 801339F4 00000000 */       nop
  /* 119078 801339F8 45020004 */     bc1fl .L80133A0C
  /* 11907C 801339FC 44807000 */      mtc1 $zero, $f14
  /* 119080 80133A00 E50E0000 */      swc1 $f14, ($t0) # gMNTitleFireBGOverlayBlue + 0
  /* 119084 80133A04 C50C0000 */      lwc1 $f12, ($t0) # gMNTitleFireBGOverlayBlue + 0
  /* 119088 80133A08 44807000 */      mtc1 $zero, $f14
  .L80133A0C:
  /* 11908C 80133A0C 00000000 */       nop
  /* 119090 80133A10 460E003C */    c.lt.s $f0, $f14
  /* 119094 80133A14 00000000 */       nop
  /* 119098 80133A18 45020004 */     bc1fl .L80133A2C
  /* 11909C 80133A1C 460E103C */    c.lt.s $f2, $f14
  /* 1190A0 80133A20 E48E0000 */      swc1 $f14, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 1190A4 80133A24 C4800000 */      lwc1 $f0, ($a0) # gMNTitleFireBGOverlayRed + 0
  /* 1190A8 80133A28 460E103C */    c.lt.s $f2, $f14
  .L80133A2C:
  /* 1190AC 80133A2C 4600028D */ trunc.w.s $f10, $f0
  /* 1190B0 80133A30 45020004 */     bc1fl .L80133A44
  /* 1190B4 80133A34 460E603C */    c.lt.s $f12, $f14
  /* 1190B8 80133A38 E4EE0000 */      swc1 $f14, ($a3) # gMNTitleFireBGOverlayGreen + 0
  /* 1190BC 80133A3C C4E20000 */      lwc1 $f2, ($a3) # gMNTitleFireBGOverlayGreen + 0
  /* 1190C0 80133A40 460E603C */    c.lt.s $f12, $f14
  .L80133A44:
  /* 1190C4 80133A44 4600148D */ trunc.w.s $f18, $f2
  /* 1190C8 80133A48 45020004 */     bc1fl .L80133A5C
  /* 1190CC 80133A4C 4600640D */ trunc.w.s $f16, $f12
  /* 1190D0 80133A50 E50E0000 */      swc1 $f14, ($t0) # gMNTitleFireBGOverlayBlue + 0
  /* 1190D4 80133A54 C50C0000 */      lwc1 $f12, ($t0) # gMNTitleFireBGOverlayBlue + 0
  /* 1190D8 80133A58 4600640D */ trunc.w.s $f16, $f12
  .L80133A5C:
  /* 1190DC 80133A5C 440D5000 */      mfc1 $t5, $f10
  /* 1190E0 80133A60 44189000 */      mfc1 $t8, $f18
  /* 1190E4 80133A64 440B8000 */      mfc1 $t3, $f16
  /* 1190E8 80133A68 000D7600 */       sll $t6, $t5, 0x18
  /* 1190EC 80133A6C 0018CC00 */       sll $t9, $t8, 0x10
  /* 1190F0 80133A70 01D94825 */        or $t1, $t6, $t9
  /* 1190F4 80133A74 000B6200 */       sll $t4, $t3, 8
  /* 1190F8 80133A78 012C6825 */        or $t5, $t1, $t4
  /* 1190FC 80133A7C 35AF00FF */       ori $t7, $t5, 0xff
  /* 119100 80133A80 ACCF0084 */        sw $t7, 0x84($a2)
  .L80133A84:
  /* 119104 80133A84 8FBF0014 */        lw $ra, 0x14($sp)
  /* 119108 80133A88 27BD0020 */     addiu $sp, $sp, 0x20
  /* 11910C 80133A8C 03E00008 */        jr $ra
  /* 119110 80133A90 00000000 */       nop

glabel mnTitleCreateViewports
  /* 119114 80133A94 27BDFF98 */     addiu $sp, $sp, -0x68
  /* 119118 80133A98 AFBF004C */        sw $ra, 0x4c($sp)
  /* 11911C 80133A9C 240E00FF */     addiu $t6, $zero, 0xff
  /* 119120 80133AA0 AFB00048 */        sw $s0, 0x48($sp)
  /* 119124 80133AA4 F7B40040 */      sdc1 $f20, 0x40($sp)
  /* 119128 80133AA8 AFAE0010 */        sw $t6, 0x10($sp)
  /* 11912C 80133AAC 24040002 */     addiu $a0, $zero, 2
  /* 119130 80133AB0 3C058000 */       lui $a1, 0x8000
  /* 119134 80133AB4 24060064 */     addiu $a2, $zero, 0x64
  /* 119138 80133AB8 0C002E7F */       jal func_8000B9FC
  /* 11913C 80133ABC 24070003 */     addiu $a3, $zero, 3
  /* 119140 80133AC0 3C038013 */       lui $v1, %hi(gMNTitleFireBGOverlayCameraGObj)
  /* 119144 80133AC4 24634448 */     addiu $v1, $v1, %lo(gMNTitleFireBGOverlayCameraGObj)
  /* 119148 80133AC8 3C058013 */       lui $a1, %hi(mnTitleUpdateFireBGOverlayColor)
  /* 11914C 80133ACC AC620000 */        sw $v0, ($v1) # gMNTitleFireBGOverlayCameraGObj + 0
  /* 119150 80133AD0 24A53770 */     addiu $a1, $a1, %lo(mnTitleUpdateFireBGOverlayColor)
  /* 119154 80133AD4 00402025 */        or $a0, $v0, $zero
  /* 119158 80133AD8 24060001 */     addiu $a2, $zero, 1
  /* 11915C 80133ADC 0C002062 */       jal omAddGObjCommonProc
  /* 119160 80133AE0 24070001 */     addiu $a3, $zero, 1
  /* 119164 80133AE4 3C0F800D */       lui $t7, %hi(func_ovl0_800CD2CC)
  /* 119168 80133AE8 25EFD2CC */     addiu $t7, $t7, %lo(func_ovl0_800CD2CC)
  /* 11916C 80133AEC 2418003C */     addiu $t8, $zero, 0x3c
  /* 119170 80133AF0 24080000 */     addiu $t0, $zero, 0
  /* 119174 80133AF4 24090003 */     addiu $t1, $zero, 3
  /* 119178 80133AF8 2419FFFF */     addiu $t9, $zero, -1
  /* 11917C 80133AFC 240A0001 */     addiu $t2, $zero, 1
  /* 119180 80133B00 240B0001 */     addiu $t3, $zero, 1
  /* 119184 80133B04 AFAB0030 */        sw $t3, 0x30($sp)
  /* 119188 80133B08 AFAA0028 */        sw $t2, 0x28($sp)
  /* 11918C 80133B0C AFB90020 */        sw $t9, 0x20($sp)
  /* 119190 80133B10 AFA9001C */        sw $t1, 0x1c($sp)
  /* 119194 80133B14 AFA80018 */        sw $t0, 0x18($sp)
  /* 119198 80133B18 AFB80014 */        sw $t8, 0x14($sp)
  /* 11919C 80133B1C AFAF0010 */        sw $t7, 0x10($sp)
  /* 1191A0 80133B20 24040002 */     addiu $a0, $zero, 2
  /* 1191A4 80133B24 00002825 */        or $a1, $zero, $zero
  /* 1191A8 80133B28 24060003 */     addiu $a2, $zero, 3
  /* 1191AC 80133B2C 3C078000 */       lui $a3, 0x8000
  /* 1191B0 80133B30 AFA00024 */        sw $zero, 0x24($sp)
  /* 1191B4 80133B34 AFA0002C */        sw $zero, 0x2c($sp)
  /* 1191B8 80133B38 0C002E4F */       jal func_8000B93C
  /* 1191BC 80133B3C AFA00034 */        sw $zero, 0x34($sp)
  /* 1191C0 80133B40 3C014120 */       lui $at, (0x41200000 >> 16) # 10.0
  /* 1191C4 80133B44 4481A000 */      mtc1 $at, $f20 # 10.0 to cop1
  /* 1191C8 80133B48 3C014366 */       lui $at, (0x43660000 >> 16) # 230.0
  /* 1191CC 80133B4C 8C500074 */        lw $s0, 0x74($v0)
  /* 1191D0 80133B50 44812000 */      mtc1 $at, $f4 # 230.0 to cop1
  /* 1191D4 80133B54 4405A000 */      mfc1 $a1, $f20
  /* 1191D8 80133B58 4406A000 */      mfc1 $a2, $f20
  /* 1191DC 80133B5C 3C07439B */       lui $a3, 0x439b
  /* 1191E0 80133B60 26040008 */     addiu $a0, $s0, 8
  /* 1191E4 80133B64 0C001C20 */       jal func_80007080
  /* 1191E8 80133B68 E7A40010 */      swc1 $f4, 0x10($sp)
  /* 1191EC 80133B6C 3C028001 */       lui $v0, %hi(func_80017EC0)
  /* 1191F0 80133B70 24427EC0 */     addiu $v0, $v0, %lo(func_80017EC0)
  /* 1191F4 80133B74 240C0028 */     addiu $t4, $zero, 0x28
  /* 1191F8 80133B78 240E0000 */     addiu $t6, $zero, 0
  /* 1191FC 80133B7C 240F0004 */     addiu $t7, $zero, 4
  /* 119200 80133B80 240DFFFF */     addiu $t5, $zero, -1
  /* 119204 80133B84 24180001 */     addiu $t8, $zero, 1
  /* 119208 80133B88 24080001 */     addiu $t0, $zero, 1
  /* 11920C 80133B8C AFA80030 */        sw $t0, 0x30($sp)
  /* 119210 80133B90 AFB80028 */        sw $t8, 0x28($sp)
  /* 119214 80133B94 AFAD0020 */        sw $t5, 0x20($sp)
  /* 119218 80133B98 AFAF001C */        sw $t7, 0x1c($sp)
  /* 11921C 80133B9C AFAE0018 */        sw $t6, 0x18($sp)
  /* 119220 80133BA0 AFAC0014 */        sw $t4, 0x14($sp)
  /* 119224 80133BA4 AFA20010 */        sw $v0, 0x10($sp)
  /* 119228 80133BA8 AFA20054 */        sw $v0, 0x54($sp)
  /* 11922C 80133BAC 24040003 */     addiu $a0, $zero, 3
  /* 119230 80133BB0 00002825 */        or $a1, $zero, $zero
  /* 119234 80133BB4 24060003 */     addiu $a2, $zero, 3
  /* 119238 80133BB8 3C078000 */       lui $a3, 0x8000
  /* 11923C 80133BBC AFA00024 */        sw $zero, 0x24($sp)
  /* 119240 80133BC0 AFA0002C */        sw $zero, 0x2c($sp)
  /* 119244 80133BC4 0C002E4F */       jal func_8000B93C
  /* 119248 80133BC8 AFA00034 */        sw $zero, 0x34($sp)
  /* 11924C 80133BCC 8C500074 */        lw $s0, 0x74($v0)
  /* 119250 80133BD0 24050005 */     addiu $a1, $zero, 5
  /* 119254 80133BD4 00003025 */        or $a2, $zero, $zero
  /* 119258 80133BD8 0C00233C */       jal omAddOMMtxForCamera
  /* 11925C 80133BDC 02002025 */        or $a0, $s0, $zero
  /* 119260 80133BE0 02002025 */        or $a0, $s0, $zero
  /* 119264 80133BE4 24050006 */     addiu $a1, $zero, 6
  /* 119268 80133BE8 0C00233C */       jal omAddOMMtxForCamera
  /* 11926C 80133BEC 00003025 */        or $a2, $zero, $zero
  /* 119270 80133BF0 3C014366 */       lui $at, (0x43660000 >> 16) # 230.0
  /* 119274 80133BF4 44813000 */      mtc1 $at, $f6 # 230.0 to cop1
  /* 119278 80133BF8 4405A000 */      mfc1 $a1, $f20
  /* 11927C 80133BFC 4406A000 */      mfc1 $a2, $f20
  /* 119280 80133C00 26040008 */     addiu $a0, $s0, 8
  /* 119284 80133C04 3C07439B */       lui $a3, 0x439b
  /* 119288 80133C08 0C001C20 */       jal func_80007080
  /* 11928C 80133C0C E7A60010 */      swc1 $f6, 0x10($sp)
  /* 119290 80133C10 44800000 */      mtc1 $zero, $f0
  /* 119294 80133C14 3C0144FA */       lui $at, (0x44FA0000 >> 16) # 2000.0
  /* 119298 80133C18 44814000 */      mtc1 $at, $f8 # 2000.0 to cop1
  /* 11929C 80133C1C E6000050 */      swc1 $f0, 0x50($s0)
  /* 1192A0 80133C20 E600004C */      swc1 $f0, 0x4c($s0)
  /* 1192A4 80133C24 E6000048 */      swc1 $f0, 0x48($s0)
  /* 1192A8 80133C28 E6000040 */      swc1 $f0, 0x40($s0)
  /* 1192AC 80133C2C E600003C */      swc1 $f0, 0x3c($s0)
  /* 1192B0 80133C30 E6080044 */      swc1 $f8, 0x44($s0)
  /* 1192B4 80133C34 8FA90054 */        lw $t1, 0x54($sp)
  /* 1192B8 80133C38 24190050 */     addiu $t9, $zero, 0x50
  /* 1192BC 80133C3C 240A0000 */     addiu $t2, $zero, 0
  /* 1192C0 80133C40 240B0008 */     addiu $t3, $zero, 8
  /* 1192C4 80133C44 240CFFFF */     addiu $t4, $zero, -1
  /* 1192C8 80133C48 240E0001 */     addiu $t6, $zero, 1
  /* 1192CC 80133C4C 240F0001 */     addiu $t7, $zero, 1
  /* 1192D0 80133C50 240D0001 */     addiu $t5, $zero, 1
  /* 1192D4 80133C54 AFAD0030 */        sw $t5, 0x30($sp)
  /* 1192D8 80133C58 AFAF0028 */        sw $t7, 0x28($sp)
  /* 1192DC 80133C5C AFAE0024 */        sw $t6, 0x24($sp)
  /* 1192E0 80133C60 AFAC0020 */        sw $t4, 0x20($sp)
  /* 1192E4 80133C64 AFAB001C */        sw $t3, 0x1c($sp)
  /* 1192E8 80133C68 AFAA0018 */        sw $t2, 0x18($sp)
  /* 1192EC 80133C6C AFB90014 */        sw $t9, 0x14($sp)
  /* 1192F0 80133C70 AFA00034 */        sw $zero, 0x34($sp)
  /* 1192F4 80133C74 AFA0002C */        sw $zero, 0x2c($sp)
  /* 1192F8 80133C78 24040003 */     addiu $a0, $zero, 3
  /* 1192FC 80133C7C 00002825 */        or $a1, $zero, $zero
  /* 119300 80133C80 24060003 */     addiu $a2, $zero, 3
  /* 119304 80133C84 3C078000 */       lui $a3, 0x8000
  /* 119308 80133C88 0C002E4F */       jal func_8000B93C
  /* 11930C 80133C8C AFA90010 */        sw $t1, 0x10($sp)
  /* 119310 80133C90 3C014366 */       lui $at, (0x43660000 >> 16) # 230.0
  /* 119314 80133C94 8C500074 */        lw $s0, 0x74($v0)
  /* 119318 80133C98 44815000 */      mtc1 $at, $f10 # 230.0 to cop1
  /* 11931C 80133C9C 4405A000 */      mfc1 $a1, $f20
  /* 119320 80133CA0 4406A000 */      mfc1 $a2, $f20
  /* 119324 80133CA4 3C07439B */       lui $a3, 0x439b
  /* 119328 80133CA8 26040008 */     addiu $a0, $s0, 8
  /* 11932C 80133CAC 0C001C20 */       jal func_80007080
  /* 119330 80133CB0 E7AA0010 */      swc1 $f10, 0x10($sp)
  /* 119334 80133CB4 44800000 */      mtc1 $zero, $f0
  /* 119338 80133CB8 3C01447A */       lui $at, (0x447A0000 >> 16) # 1000.0
  /* 11933C 80133CBC 44818000 */      mtc1 $at, $f16 # 1000.0 to cop1
  /* 119340 80133CC0 3C0141F0 */       lui $at, (0x41F00000 >> 16) # 30.0
  /* 119344 80133CC4 44819000 */      mtc1 $at, $f18 # 30.0 to cop1
  /* 119348 80133CC8 E6000050 */      swc1 $f0, 0x50($s0)
  /* 11934C 80133CCC E600004C */      swc1 $f0, 0x4c($s0)
  /* 119350 80133CD0 E6000048 */      swc1 $f0, 0x48($s0)
  /* 119354 80133CD4 E6000040 */      swc1 $f0, 0x40($s0)
  /* 119358 80133CD8 E600003C */      swc1 $f0, 0x3c($s0)
  /* 11935C 80133CDC E6100044 */      swc1 $f16, 0x44($s0)
  /* 119360 80133CE0 E6120020 */      swc1 $f18, 0x20($s0)
  /* 119364 80133CE4 8FBF004C */        lw $ra, 0x4c($sp)
  /* 119368 80133CE8 8FB00048 */        lw $s0, 0x48($sp)
  /* 11936C 80133CEC D7B40040 */      ldc1 $f20, 0x40($sp)
  /* 119370 80133CF0 8FA20060 */        lw $v0, 0x60($sp)
  /* 119374 80133CF4 03E00008 */        jr $ra
  /* 119378 80133CF8 27BD0068 */     addiu $sp, $sp, 0x68

glabel mnTitleRenderLogoFireEffect
  /* 11937C 80133CFC 3C038004 */       lui $v1, %hi(gDisplayListHead)
  /* 119380 80133D00 246365B0 */     addiu $v1, $v1, %lo(gDisplayListHead)
  /* 119384 80133D04 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 119388 80133D08 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 11938C 80133D0C AFBF0014 */        sw $ra, 0x14($sp)
  /* 119390 80133D10 244E0008 */     addiu $t6, $v0, 8
  /* 119394 80133D14 AC6E0000 */        sw $t6, ($v1) # gDisplayListHead + 0
  /* 119398 80133D18 3C0FE700 */       lui $t7, 0xe700
  /* 11939C 80133D1C AC4F0000 */        sw $t7, ($v0)
  /* 1193A0 80133D20 AC400004 */        sw $zero, 4($v0)
  /* 1193A4 80133D24 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 1193A8 80133D28 3C19E200 */       lui $t9, (0xE200001C >> 16) # 3791650844
  /* 1193AC 80133D2C 3C080050 */       lui $t0, (0x5049D8 >> 16) # 5261784
  /* 1193B0 80133D30 24580008 */     addiu $t8, $v0, 8
  /* 1193B4 80133D34 AC780000 */        sw $t8, ($v1) # gDisplayListHead + 0
  /* 1193B8 80133D38 350849D8 */       ori $t0, $t0, (0x5049D8 & 0xFFFF) # 5261784
  /* 1193BC 80133D3C 3739001C */       ori $t9, $t9, (0xE200001C & 0xFFFF) # 3791650844
  /* 1193C0 80133D40 AC590000 */        sw $t9, ($v0)
  /* 1193C4 80133D44 0C03434D */       jal func_ovl0_800D0D34
  /* 1193C8 80133D48 AC480004 */        sw $t0, 4($v0)
  /* 1193CC 80133D4C 3C038004 */       lui $v1, %hi(gDisplayListHead)
  /* 1193D0 80133D50 246365B0 */     addiu $v1, $v1, %lo(gDisplayListHead)
  /* 1193D4 80133D54 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 1193D8 80133D58 3C0AE300 */       lui $t2, (0xE3000C00 >> 16) # 3808431104
  /* 1193DC 80133D5C 354A0C00 */       ori $t2, $t2, (0xE3000C00 & 0xFFFF) # 3808431104
  /* 1193E0 80133D60 24490008 */     addiu $t1, $v0, 8
  /* 1193E4 80133D64 AC690000 */        sw $t1, ($v1) # gDisplayListHead + 0
  /* 1193E8 80133D68 3C0B0008 */       lui $t3, 8
  /* 1193EC 80133D6C AC4B0004 */        sw $t3, 4($v0)
  /* 1193F0 80133D70 AC4A0000 */        sw $t2, ($v0)
  /* 1193F4 80133D74 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 1193F8 80133D78 3C0DE200 */       lui $t5, (0xE2001D00 >> 16) # 3791658240
  /* 1193FC 80133D7C 35AD1D00 */       ori $t5, $t5, (0xE2001D00 & 0xFFFF) # 3791658240
  /* 119400 80133D80 244C0008 */     addiu $t4, $v0, 8
  /* 119404 80133D84 AC6C0000 */        sw $t4, ($v1) # gDisplayListHead + 0
  /* 119408 80133D88 AC400004 */        sw $zero, 4($v0)
  /* 11940C 80133D8C AC4D0000 */        sw $t5, ($v0)
  /* 119410 80133D90 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 119414 80133D94 3C0FE700 */       lui $t7, 0xe700
  /* 119418 80133D98 3C19E200 */       lui $t9, (0xE200001C >> 16) # 3791650844
  /* 11941C 80133D9C 244E0008 */     addiu $t6, $v0, 8
  /* 119420 80133DA0 AC6E0000 */        sw $t6, ($v1) # gDisplayListHead + 0
  /* 119424 80133DA4 AC400004 */        sw $zero, 4($v0)
  /* 119428 80133DA8 AC4F0000 */        sw $t7, ($v0)
  /* 11942C 80133DAC 8C620000 */        lw $v0, ($v1) # gDisplayListHead + 0
  /* 119430 80133DB0 3C080055 */       lui $t0, (0x552078 >> 16) # 5578872
  /* 119434 80133DB4 35082078 */       ori $t0, $t0, (0x552078 & 0xFFFF) # 5578872
  /* 119438 80133DB8 24580008 */     addiu $t8, $v0, 8
  /* 11943C 80133DBC AC780000 */        sw $t8, ($v1) # gDisplayListHead + 0
  /* 119440 80133DC0 3739001C */       ori $t9, $t9, (0xE200001C & 0xFFFF) # 3791650844
  /* 119444 80133DC4 AC590000 */        sw $t9, ($v0)
  /* 119448 80133DC8 AC480004 */        sw $t0, 4($v0)
  /* 11944C 80133DCC 8FBF0014 */        lw $ra, 0x14($sp)
  /* 119450 80133DD0 27BD0018 */     addiu $sp, $sp, 0x18
  /* 119454 80133DD4 03E00008 */        jr $ra
  /* 119458 80133DD8 00000000 */       nop

glabel mnTitleCreateLogoFire
  /* 11945C 80133DDC 27BDFFD8 */     addiu $sp, $sp, -0x28
  /* 119460 80133DE0 AFBF001C */        sw $ra, 0x1c($sp)
  /* 119464 80133DE4 2404000F */     addiu $a0, $zero, 0xf
  /* 119468 80133DE8 00002825 */        or $a1, $zero, $zero
  /* 11946C 80133DEC 24060004 */     addiu $a2, $zero, 4
  /* 119470 80133DF0 0C00265A */       jal omMakeGObjSPAfter
  /* 119474 80133DF4 3C078000 */       lui $a3, 0x8000
  /* 119478 80133DF8 3C058013 */       lui $a1, %hi(mnTitleRenderLogoFireEffect)
  /* 11947C 80133DFC 240EFFFF */     addiu $t6, $zero, -1
  /* 119480 80133E00 AFA20024 */        sw $v0, 0x24($sp)
  /* 119484 80133E04 AFAE0010 */        sw $t6, 0x10($sp)
  /* 119488 80133E08 24A53CFC */     addiu $a1, $a1, %lo(mnTitleRenderLogoFireEffect)
  /* 11948C 80133E0C 00402025 */        or $a0, $v0, $zero
  /* 119490 80133E10 24060003 */     addiu $a2, $zero, 3
  /* 119494 80133E14 0C00277D */       jal omAddGObjRenderProc
  /* 119498 80133E18 3C078000 */       lui $a3, 0x8000
  /* 11949C 80133E1C 8FAF0024 */        lw $t7, 0x24($sp)
  /* 1194A0 80133E20 24180000 */     addiu $t8, $zero, 0
  /* 1194A4 80133E24 24190001 */     addiu $t9, $zero, 1
  /* 1194A8 80133E28 3C0400B2 */       lui $a0, %hi(D_NF_00B22C30)
  /* 1194AC 80133E2C 3C0500B2 */       lui $a1, %hi(D_NF_00B22D40)
  /* 1194B0 80133E30 3C0600B2 */       lui $a2, %hi(D_NF_00B22D40)
  /* 1194B4 80133E34 3C0700B2 */       lui $a3, %hi(D_NF_00B277B0)
  /* 1194B8 80133E38 24E777B0 */     addiu $a3, $a3, %lo(D_NF_00B277B0)
  /* 1194BC 80133E3C 24C62D40 */     addiu $a2, $a2, %lo(D_NF_00B22D40)
  /* 1194C0 80133E40 24A52D40 */     addiu $a1, $a1, %lo(D_NF_00B22D40)
  /* 1194C4 80133E44 24842C30 */     addiu $a0, $a0, %lo(D_NF_00B22C30)
  /* 1194C8 80133E48 ADF90034 */        sw $t9, 0x34($t7)
  /* 1194CC 80133E4C 0C04567E */       jal efAlloc_SetParticleBank
  /* 1194D0 80133E50 ADF80030 */        sw $t8, 0x30($t7)
  /* 1194D4 80133E54 8FBF001C */        lw $ra, 0x1c($sp)
  /* 1194D8 80133E58 3C018013 */       lui $at, %hi(gMNTitleParticleBankId)
  /* 1194DC 80133E5C AC22444C */        sw $v0, %lo(gMNTitleParticleBankId)($at)
  /* 1194E0 80133E60 03E00008 */        jr $ra
  /* 1194E4 80133E64 27BD0028 */     addiu $sp, $sp, 0x28

glabel mnTitleLogoFireMakeEffect
  /* 1194E8 80133E68 3C0E800A */       lui $t6, %hi((gSceneData + 0x1))
  /* 1194EC 80133E6C 91CE4AD1 */       lbu $t6, %lo((gSceneData + 0x1))($t6)
  /* 1194F0 80133E70 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 1194F4 80133E74 2401002E */     addiu $at, $zero, 0x2e
  /* 1194F8 80133E78 AFBF001C */        sw $ra, 0x1c($sp)
  /* 1194FC 80133E7C 15C1002A */       bne $t6, $at, .L80133F28
  /* 119500 80133E80 AFB00018 */        sw $s0, 0x18($sp)
  /* 119504 80133E84 2404000E */     addiu $a0, $zero, 0xe
  /* 119508 80133E88 00002825 */        or $a1, $zero, $zero
  /* 11950C 80133E8C 24060005 */     addiu $a2, $zero, 5
  /* 119510 80133E90 0C00265A */       jal omMakeGObjSPAfter
  /* 119514 80133E94 3C078000 */       lui $a3, 0x8000
  /* 119518 80133E98 3C0F8013 */       lui $t7, %hi(D_ovl10_801345A0)
  /* 11951C 80133E9C 8DEF45A0 */        lw $t7, %lo(D_ovl10_801345A0)($t7)
  /* 119520 80133EA0 3C180003 */       lui $t8, %hi(D_NF_00028EB0)
  /* 119524 80133EA4 27188EB0 */     addiu $t8, $t8, %lo(D_NF_00028EB0)
  /* 119528 80133EA8 00408025 */        or $s0, $v0, $zero
  /* 11952C 80133EAC 00402025 */        or $a0, $v0, $zero
  /* 119530 80133EB0 00003025 */        or $a2, $zero, $zero
  /* 119534 80133EB4 0C003C48 */       jal func_8000F120
  /* 119538 80133EB8 01F82821 */      addu $a1, $t7, $t8
  /* 11953C 80133EBC 3C198013 */       lui $t9, %hi(D_ovl10_801345A0)
  /* 119540 80133EC0 8F3945A0 */        lw $t9, %lo(D_ovl10_801345A0)($t9)
  /* 119544 80133EC4 3C080003 */       lui $t0, %hi(D_NF_00029010)
  /* 119548 80133EC8 25089010 */     addiu $t0, $t0, %lo(D_NF_00029010)
  /* 11954C 80133ECC 02002025 */        or $a0, $s0, $zero
  /* 119550 80133ED0 24060000 */     addiu $a2, $zero, 0
  /* 119554 80133ED4 0C002F63 */       jal func_8000BD8C
  /* 119558 80133ED8 03282821 */      addu $a1, $t9, $t0
  /* 11955C 80133EDC 0C0037CD */       jal func_8000DF34
  /* 119560 80133EE0 02002025 */        or $a0, $s0, $zero
  /* 119564 80133EE4 3C058001 */       lui $a1, %hi(func_8000DF34)
  /* 119568 80133EE8 24A5DF34 */     addiu $a1, $a1, %lo(func_8000DF34)
  /* 11956C 80133EEC 02002025 */        or $a0, $s0, $zero
  /* 119570 80133EF0 24060001 */     addiu $a2, $zero, 1
  /* 119574 80133EF4 0C002062 */       jal omAddGObjCommonProc
  /* 119578 80133EF8 24070001 */     addiu $a3, $zero, 1
  /* 11957C 80133EFC 3C048013 */       lui $a0, %hi(gMNTitleParticleBankId)
  /* 119580 80133F00 8C84444C */        lw $a0, %lo(gMNTitleParticleBankId)($a0)
  /* 119584 80133F04 0C034D77 */       jal func_ovl0_800D35DC
  /* 119588 80133F08 00002825 */        or $a1, $zero, $zero
  /* 11958C 80133F0C 50400007 */      beql $v0, $zero, .L80133F2C
  /* 119590 80133F10 8FBF001C */        lw $ra, 0x1c($sp)
  /* 119594 80133F14 8E090074 */        lw $t1, 0x74($s0)
  /* 119598 80133F18 8D2A0010 */        lw $t2, 0x10($t1)
  /* 11959C 80133F1C 8D4B0008 */        lw $t3, 8($t2)
  /* 1195A0 80133F20 8D6C0010 */        lw $t4, 0x10($t3)
  /* 1195A4 80133F24 AC4C0048 */        sw $t4, 0x48($v0)
  .L80133F28:
  /* 1195A8 80133F28 8FBF001C */        lw $ra, 0x1c($sp)
  .L80133F2C:
  /* 1195AC 80133F2C 8FB00018 */        lw $s0, 0x18($sp)
  /* 1195B0 80133F30 27BD0020 */     addiu $sp, $sp, 0x20
  /* 1195B4 80133F34 03E00008 */        jr $ra
  /* 1195B8 80133F38 00000000 */       nop

glabel mnTitleCreateMainRoutines
  /* 1195BC 80133F3C 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 1195C0 80133F40 AFBF0014 */        sw $ra, 0x14($sp)
  /* 1195C4 80133F44 3C058013 */       lui $a1, %hi(mnTitleMain)
  /* 1195C8 80133F48 24A520F0 */     addiu $a1, $a1, %lo(mnTitleMain)
  /* 1195CC 80133F4C 00002025 */        or $a0, $zero, $zero
  /* 1195D0 80133F50 24060001 */     addiu $a2, $zero, 1
  /* 1195D4 80133F54 0C00265A */       jal omMakeGObjSPAfter
  /* 1195D8 80133F58 3C078000 */       lui $a3, 0x8000
  /* 1195DC 80133F5C 3C018013 */       lui $at, %hi(gMNTitleMainGObj)
  /* 1195E0 80133F60 3C058013 */       lui $a1, %hi(mnTitleHandleTransitions)
  /* 1195E4 80133F64 AC224458 */        sw $v0, %lo(gMNTitleMainGObj)($at)
  /* 1195E8 80133F68 24A52448 */     addiu $a1, $a1, %lo(mnTitleHandleTransitions)
  /* 1195EC 80133F6C 00002025 */        or $a0, $zero, $zero
  /* 1195F0 80133F70 2406000F */     addiu $a2, $zero, 0xf
  /* 1195F4 80133F74 0C00265A */       jal omMakeGObjSPAfter
  /* 1195F8 80133F78 3C078000 */       lui $a3, 0x8000
  /* 1195FC 80133F7C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 119600 80133F80 3C018013 */       lui $at, %hi(gMNTitleTransitionsGObj)
  /* 119604 80133F84 AC224454 */        sw $v0, %lo(gMNTitleTransitionsGObj)($at)
  /* 119608 80133F88 03E00008 */        jr $ra
  /* 11960C 80133F8C 27BD0018 */     addiu $sp, $sp, 0x18

glabel mnTitleInit
  /* 119610 80133F90 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 119614 80133F94 AFB10018 */        sw $s1, 0x18($sp)
  /* 119618 80133F98 AFB00014 */        sw $s0, 0x14($sp)
  /* 11961C 80133F9C AFBF001C */        sw $ra, 0x1c($sp)
  /* 119620 80133FA0 00008025 */        or $s0, $zero, $zero
  /* 119624 80133FA4 24110004 */     addiu $s1, $zero, 4
  .L80133FA8:
  /* 119628 80133FA8 0C001125 */       jal func_80004494
  /* 11962C 80133FAC 02002025 */        or $a0, $s0, $zero
  /* 119630 80133FB0 26100001 */     addiu $s0, $s0, 1
  /* 119634 80133FB4 1611FFFC */       bne $s0, $s1, .L80133FA8
  /* 119638 80133FB8 00000000 */       nop
  /* 11963C 80133FBC 0C04D050 */       jal mnTitleLoadFiles
  /* 119640 80133FC0 00000000 */       nop
  /* 119644 80133FC4 0C04CFCF */       jal mnTitleCreateMainRoutines
  /* 119648 80133FC8 00000000 */       nop
  /* 11964C 80133FCC 0C045624 */       jal func_ovl2_80115890
  /* 119650 80133FD0 00000000 */       nop
  /* 119654 80133FD4 0C04CF77 */       jal mnTitleCreateLogoFire
  /* 119658 80133FD8 00000000 */       nop
  /* 11965C 80133FDC 0C04CEA5 */       jal mnTitleCreateViewports
  /* 119660 80133FE0 00000000 */       nop
  /* 119664 80133FE4 0C04C73D */       jal mnTitleInitVars
  /* 119668 80133FE8 00000000 */       nop
  /* 11966C 80133FEC 0C04CADC */       jal mnTitleCreateFire
  /* 119670 80133FF0 00000000 */       nop
  /* 119674 80133FF4 0C04CBF6 */       jal mnTitleCreateLogo
  /* 119678 80133FF8 00000000 */       nop
  /* 11967C 80133FFC 0C04CCB9 */       jal mnTitleCreateTitleHeaderAndFooter
  /* 119680 80134000 00000000 */       nop
  /* 119684 80134004 0C04CD8D */       jal func_ovl10_80133634
  /* 119688 80134008 00000000 */       nop
  /* 11968C 8013400C 0C04CD41 */       jal mnTitleCreatePressStart
  /* 119690 80134010 00000000 */       nop
  /* 119694 80134014 0C04CD9B */       jal mnTitleCreateSlashEffectGFX
  /* 119698 80134018 00000000 */       nop
  /* 11969C 8013401C 0C04CF9A */       jal mnTitleLogoFireMakeEffect
  /* 1196A0 80134020 00000000 */       nop
  /* 1196A4 80134024 3C0E800A */       lui $t6, %hi((gSceneData + 0x1))
  /* 1196A8 80134028 91CE4AD1 */       lbu $t6, %lo((gSceneData + 0x1))($t6)
  /* 1196AC 8013402C 2401002E */     addiu $at, $zero, 0x2e
  /* 1196B0 80134030 55C1000C */      bnel $t6, $at, .L80134064
  /* 1196B4 80134034 8FBF001C */        lw $ra, 0x1c($sp)
  /* 1196B8 80134038 0C00024B */       jal func_8000092C
  /* 1196BC 8013403C 00000000 */       nop
  /* 1196C0 80134040 2C411077 */     sltiu $at, $v0, 0x1077
  /* 1196C4 80134044 50200007 */      beql $at, $zero, .L80134064
  /* 1196C8 80134048 8FBF001C */        lw $ra, 0x1c($sp)
  .L8013404C:
  /* 1196CC 8013404C 0C00024B */       jal func_8000092C
  /* 1196D0 80134050 00000000 */       nop
  /* 1196D4 80134054 2C411077 */     sltiu $at, $v0, 0x1077
  /* 1196D8 80134058 1420FFFC */      bnez $at, .L8013404C
  /* 1196DC 8013405C 00000000 */       nop
  /* 1196E0 80134060 8FBF001C */        lw $ra, 0x1c($sp)
  .L80134064:
  /* 1196E4 80134064 8FB00014 */        lw $s0, 0x14($sp)
  /* 1196E8 80134068 8FB10018 */        lw $s1, 0x18($sp)
  /* 1196EC 8013406C 03E00008 */        jr $ra
  /* 1196F0 80134070 27BD0020 */     addiu $sp, $sp, 0x20

glabel mnTitleSetupDisplayList
  /* 1196F4 80134074 8C830000 */        lw $v1, ($a0)
  /* 1196F8 80134078 3C188013 */       lui $t8, %hi(dMNTitleDisplayList)
  /* 1196FC 8013407C 27184348 */     addiu $t8, $t8, %lo(dMNTitleDisplayList)
  /* 119700 80134080 246E0008 */     addiu $t6, $v1, 8
  /* 119704 80134084 AC8E0000 */        sw $t6, ($a0)
  /* 119708 80134088 3C0FDE00 */       lui $t7, 0xde00
  /* 11970C 8013408C AC6F0000 */        sw $t7, ($v1)
  /* 119710 80134090 03E00008 */        jr $ra
  /* 119714 80134094 AC780004 */        sw $t8, 4($v1)

glabel mnTitleAdvanceFrame
  /* 119718 80134098 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 11971C 8013409C AFBF0014 */        sw $ra, 0x14($sp)
  /* 119720 801340A0 0C002979 */       jal func_8000A5E4
  /* 119724 801340A4 00000000 */       nop
  /* 119728 801340A8 8FBF0014 */        lw $ra, 0x14($sp)
  /* 11972C 801340AC 27BD0018 */     addiu $sp, $sp, 0x18
  /* 119730 801340B0 03E00008 */        jr $ra
  /* 119734 801340B4 00000000 */       nop

glabel mnTitleStartScene
  /* 119738 801340B8 3C0E800A */       lui $t6, %hi(D_NF_800A5240)
  /* 11973C 801340BC 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 119740 801340C0 3C048013 */       lui $a0, %hi(D_ovl10_80134370)
  /* 119744 801340C4 25CE5240 */     addiu $t6, $t6, %lo(D_NF_800A5240)
  /* 119748 801340C8 24844370 */     addiu $a0, $a0, %lo(D_ovl10_80134370)
  /* 11974C 801340CC AFBF0014 */        sw $ra, 0x14($sp)
  /* 119750 801340D0 25CFE700 */     addiu $t7, $t6, -0x1900
  /* 119754 801340D4 0C001C09 */       jal func_80007024
  /* 119758 801340D8 AC8F000C */        sw $t7, 0xc($a0) # D_ovl10_80134370 + 12
  /* 11975C 801340DC 3C18800A */       lui $t8, %hi((gSceneData + 0x44))
  /* 119760 801340E0 93184B14 */       lbu $t8, %lo((gSceneData + 0x44))($t8)
  /* 119764 801340E4 3C03800A */       lui $v1, %hi(gSaveData)
  /* 119768 801340E8 246344E0 */     addiu $v1, $v1, %lo(gSaveData)
  /* 11976C 801340EC 17000007 */      bnez $t8, .L8013410C
  /* 119770 801340F0 00000000 */       nop
  /* 119774 801340F4 906205E3 */       lbu $v0, 0x5e3($v1) # gSaveData + 1507
  /* 119778 801340F8 28410100 */      slti $at, $v0, 0x100
  /* 11977C 801340FC 10200003 */      beqz $at, .L8013410C
  /* 119780 80134100 24590001 */     addiu $t9, $v0, 1
  /* 119784 80134104 0C03517D */       jal lbMemory_SaveData_WriteSRAM
  /* 119788 80134108 A07905E3 */        sb $t9, 0x5e3($v1) # gSaveData + 1507
  .L8013410C:
  /* 11978C 8013410C 3C088037 */       lui $t0, %hi(mnDebugMenuUpdateMenuInputs)
  /* 119790 80134110 3C098013 */       lui $t1, %hi(D_NF_801345B0)
  /* 119794 80134114 3C048013 */       lui $a0, %hi(D_ovl10_8013438C)
  /* 119798 80134118 252945B0 */     addiu $t1, $t1, %lo(D_NF_801345B0)
  /* 11979C 8013411C 25089240 */     addiu $t0, $t0, %lo(mnDebugMenuUpdateMenuInputs)
  /* 1197A0 80134120 2484438C */     addiu $a0, $a0, %lo(D_ovl10_8013438C)
  /* 1197A4 80134124 01095023 */      subu $t2, $t0, $t1
  /* 1197A8 80134128 0C001A0F */       jal gsGTLSceneInit
  /* 1197AC 8013412C AC8A0010 */        sw $t2, 0x10($a0) # D_ovl10_8013438C + 16
  /* 1197B0 80134130 8FBF0014 */        lw $ra, 0x14($sp)
  /* 1197B4 80134134 27BD0018 */     addiu $sp, $sp, 0x18
  /* 1197B8 80134138 03E00008 */        jr $ra
  /* 1197BC 8013413C 00000000 */       nop

glabel mnTitleLoadFiles
  /* 1197C0 80134140 27BDFFC0 */     addiu $sp, $sp, -0x40
  /* 1197C4 80134144 3C0E001B */       lui $t6, %hi(D_NF_001AC870)
  /* 1197C8 80134148 3C0F0000 */       lui $t7, %hi(D_NF_00000854)
  /* 1197CC 8013414C 3C188013 */       lui $t8, %hi(D_ovl10_801344A0)
  /* 1197D0 80134150 AFBF0014 */        sw $ra, 0x14($sp)
  /* 1197D4 80134154 25CEC870 */     addiu $t6, $t6, %lo(D_NF_001AC870)
  /* 1197D8 80134158 25EF0854 */     addiu $t7, $t7, %lo(D_NF_00000854)
  /* 1197DC 8013415C 271844A0 */     addiu $t8, $t8, %lo(D_ovl10_801344A0)
  /* 1197E0 80134160 24190020 */     addiu $t9, $zero, 0x20
  /* 1197E4 80134164 AFAE0020 */        sw $t6, 0x20($sp)
  /* 1197E8 80134168 AFAF0024 */        sw $t7, 0x24($sp)
  /* 1197EC 8013416C AFA00028 */        sw $zero, 0x28($sp)
  /* 1197F0 80134170 AFA0002C */        sw $zero, 0x2c($sp)
  /* 1197F4 80134174 AFB80030 */        sw $t8, 0x30($sp)
  /* 1197F8 80134178 AFB90034 */        sw $t9, 0x34($sp)
  /* 1197FC 8013417C AFA00038 */        sw $zero, 0x38($sp)
  /* 119800 80134180 AFA0003C */        sw $zero, 0x3c($sp)
  /* 119804 80134184 0C0337DE */       jal rdManagerInitSetup
  /* 119808 80134188 27A40020 */     addiu $a0, $sp, 0x20
  /* 11980C 8013418C 3C048013 */       lui $a0, %hi(D_ovl10_80134420)
  /* 119810 80134190 24844420 */     addiu $a0, $a0, %lo(D_ovl10_80134420)
  /* 119814 80134194 0C0337BB */       jal rdManagerGetAllocSize
  /* 119818 80134198 24050002 */     addiu $a1, $zero, 2
  /* 11981C 8013419C 00402025 */        or $a0, $v0, $zero
  /* 119820 801341A0 0C001260 */       jal gsMemoryAlloc
  /* 119824 801341A4 24050010 */     addiu $a1, $zero, 0x10
  /* 119828 801341A8 3C048013 */       lui $a0, %hi(D_ovl10_80134420)
  /* 11982C 801341AC 3C068013 */       lui $a2, %hi(D_ovl10_801345A0)
  /* 119830 801341B0 24C645A0 */     addiu $a2, $a2, %lo(D_ovl10_801345A0)
  /* 119834 801341B4 24844420 */     addiu $a0, $a0, %lo(D_ovl10_80134420)
  /* 119838 801341B8 24050002 */     addiu $a1, $zero, 2
  /* 11983C 801341BC 0C033781 */       jal rdManagerLoadFiles
  /* 119840 801341C0 00403825 */        or $a3, $v0, $zero
  /* 119844 801341C4 8FBF0014 */        lw $ra, 0x14($sp)
  /* 119848 801341C8 27BD0040 */     addiu $sp, $sp, 0x40
  /* 11984C 801341CC 03E00008 */        jr $ra
  /* 119850 801341D0 00000000 */       nop

  /* 119854 801341D4 00000000 */       nop
  /* 119858 801341D8 00000000 */       nop
  /* 11985C 801341DC 00000000 */       nop
