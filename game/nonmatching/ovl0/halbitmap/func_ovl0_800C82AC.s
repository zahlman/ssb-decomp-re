.section .late_rodata

glabel D_ovl0_800D5E78
  /* E638 051858 800D5E78 */
  .word 0x4422f983 # .float 651.8986

.section .text
glabel func_ovl0_800C82AC
  /* 043C8C 800C82AC 3C01800D */       lui $at, %hi(D_ovl0_800D5E78)
  /* 043C90 800C82B0 C4205E78 */      lwc1 $f0, %lo(D_ovl0_800D5E78)($at)
  /* 043C94 800C82B4 44856000 */      mtc1 $a1, $f12
  /* 043C98 800C82B8 44867000 */      mtc1 $a2, $f14
  /* 043C9C 800C82BC 27BDFFB8 */     addiu $sp, $sp, -0x48
  /* 043CA0 800C82C0 46006102 */     mul.s $f4, $f12, $f0
  /* 043CA4 800C82C4 AFA70054 */        sw $a3, 0x54($sp)
  /* 043CA8 800C82C8 C7B00054 */      lwc1 $f16, 0x54($sp)
  /* 043CAC 800C82CC 46007202 */     mul.s $f8, $f14, $f0
  /* 043CB0 800C82D0 3C014380 */       lui $at, (0x43800000 >> 16) # 256.0
  /* 043CB4 800C82D4 3C0C8004 */       lui $t4, %hi(gSinTable)
  /* 043CB8 800C82D8 46008482 */     mul.s $f18, $f16, $f0
  /* 043CBC 800C82DC 44810000 */      mtc1 $at, $f0 # 256.0 to cop1
  /* 043CC0 800C82E0 258CB950 */     addiu $t4, $t4, %lo(gSinTable)
  /* 043CC4 800C82E4 4600218D */ trunc.w.s $f6, $f4
  /* 043CC8 800C82E8 4600428D */ trunc.w.s $f10, $f8
  /* 043CCC 800C82EC 44033000 */      mfc1 $v1, $f6
  /* 043CD0 800C82F0 C7A6005C */      lwc1 $f6, 0x5c($sp)
  /* 043CD4 800C82F4 4600910D */ trunc.w.s $f4, $f18
  /* 043CD8 800C82F8 30630FFF */      andi $v1, $v1, 0xfff
  /* 043CDC 800C82FC 46003202 */     mul.s $f8, $f6, $f0
  /* 043CE0 800C8300 3065FFFF */      andi $a1, $v1, 0xffff
  /* 043CE4 800C8304 30AF07FF */      andi $t7, $a1, 0x7ff
  /* 043CE8 800C8308 000FC040 */       sll $t8, $t7, 1
  /* 043CEC 800C830C 0198C821 */      addu $t9, $t4, $t8
  /* 043CF0 800C8310 30AE0800 */      andi $t6, $a1, 0x800
  /* 043CF4 800C8314 44035000 */      mfc1 $v1, $f10
  /* 043CF8 800C8318 972A0000 */       lhu $t2, ($t9)
  /* 043CFC 800C831C 11C00002 */      beqz $t6, .L800C8328
  /* 043D00 800C8320 4600428D */ trunc.w.s $f10, $f8
  /* 043D04 800C8324 000A5023 */      negu $t2, $t2
  .L800C8328:
  /* 043D08 800C8328 24A20400 */     addiu $v0, $a1, 0x400
  /* 043D0C 800C832C 304F07FF */      andi $t7, $v0, 0x7ff
  /* 043D10 800C8330 000FC040 */       sll $t8, $t7, 1
  /* 043D14 800C8334 0198C821 */      addu $t9, $t4, $t8
  /* 043D18 800C8338 304E0800 */      andi $t6, $v0, 0x800
  /* 043D1C 800C833C 11C00002 */      beqz $t6, .L800C8348
  /* 043D20 800C8340 97280000 */       lhu $t0, ($t9)
  /* 043D24 800C8344 00084023 */      negu $t0, $t0
  .L800C8348:
  /* 043D28 800C8348 30630FFF */      andi $v1, $v1, 0xfff
  /* 043D2C 800C834C 3065FFFF */      andi $a1, $v1, 0xffff
  /* 043D30 800C8350 30B807FF */      andi $t8, $a1, 0x7ff
  /* 043D34 800C8354 0018C840 */       sll $t9, $t8, 1
  /* 043D38 800C8358 01997021 */      addu $t6, $t4, $t9
  /* 043D3C 800C835C 30AF0800 */      andi $t7, $a1, 0x800
  /* 043D40 800C8360 11E00002 */      beqz $t7, .L800C836C
  /* 043D44 800C8364 95C90000 */       lhu $t1, ($t6)
  /* 043D48 800C8368 00094823 */      negu $t1, $t1
  .L800C836C:
  /* 043D4C 800C836C 24A20400 */     addiu $v0, $a1, 0x400
  /* 043D50 800C8370 305807FF */      andi $t8, $v0, 0x7ff
  /* 043D54 800C8374 0018C840 */       sll $t9, $t8, 1
  /* 043D58 800C8378 01997021 */      addu $t6, $t4, $t9
  /* 043D5C 800C837C 304F0800 */      andi $t7, $v0, 0x800
  /* 043D60 800C8380 11E00002 */      beqz $t7, .L800C838C
  /* 043D64 800C8384 95C60000 */       lhu $a2, ($t6)
  /* 043D68 800C8388 00063023 */      negu $a2, $a2
  .L800C838C:
  /* 043D6C 800C838C 44022000 */      mfc1 $v0, $f4
  /* 043D70 800C8390 00000000 */       nop 
  /* 043D74 800C8394 30420FFF */      andi $v0, $v0, 0xfff
  /* 043D78 800C8398 3047FFFF */      andi $a3, $v0, 0xffff
  /* 043D7C 800C839C 30F907FF */      andi $t9, $a3, 0x7ff
  /* 043D80 800C83A0 00197040 */       sll $t6, $t9, 1
  /* 043D84 800C83A4 018E7821 */      addu $t7, $t4, $t6
  /* 043D88 800C83A8 30F80800 */      andi $t8, $a3, 0x800
  /* 043D8C 800C83AC 13000002 */      beqz $t8, .L800C83B8
  /* 043D90 800C83B0 95E30000 */       lhu $v1, ($t7)
  /* 043D94 800C83B4 00031823 */      negu $v1, $v1
  .L800C83B8:
  /* 043D98 800C83B8 24E50400 */     addiu $a1, $a3, 0x400
  /* 043D9C 800C83BC 30B907FF */      andi $t9, $a1, 0x7ff
  /* 043DA0 800C83C0 00197040 */       sll $t6, $t9, 1
  /* 043DA4 800C83C4 018E7821 */      addu $t7, $t4, $t6
  /* 043DA8 800C83C8 30B80800 */      andi $t8, $a1, 0x800
  /* 043DAC 800C83CC 13000002 */      beqz $t8, .L800C83D8
  /* 043DB0 800C83D0 95E20000 */       lhu $v0, ($t7)
  /* 043DB4 800C83D4 00021023 */      negu $v0, $v0
  .L800C83D8:
  /* 043DB8 800C83D8 C7B00060 */      lwc1 $f16, 0x60($sp)
  /* 043DBC 800C83DC C7A60058 */      lwc1 $f6, 0x58($sp)
  /* 043DC0 800C83E0 00C20019 */     multu $a2, $v0
  /* 043DC4 800C83E4 46008482 */     mul.s $f18, $f16, $f0
  /* 043DC8 800C83E8 440D5000 */      mfc1 $t5, $f10
  /* 043DCC 800C83EC 3C05FFFF */       lui $a1, 0xffff
  /* 043DD0 800C83F0 46003202 */     mul.s $f8, $f6, $f0
  /* 043DD4 800C83F4 0000C012 */      mflo $t8
  /* 043DD8 800C83F8 4600428D */ trunc.w.s $f10, $f8
  /* 043DDC 800C83FC 0018CB83 */       sra $t9, $t8, 0xe
  /* 043DE0 800C8400 4600910D */ trunc.w.s $f4, $f18
  /* 043DE4 800C8404 440B5000 */      mfc1 $t3, $f10
  /* 043DE8 800C8408 00000000 */       nop 
  /* 043DEC 800C840C 032B0019 */     multu $t9, $t3
  /* 043DF0 800C8410 44072000 */      mfc1 $a3, $f4
  /* 043DF4 800C8414 00007012 */      mflo $t6
  /* 043DF8 800C8418 000E7A03 */       sra $t7, $t6, 8
  /* 043DFC 800C841C AFAF0008 */        sw $t7, 8($sp)
  /* 043E00 800C8420 00C30019 */     multu $a2, $v1
  /* 043E04 800C8424 0000C012 */      mflo $t8
  /* 043E08 800C8428 0018CB83 */       sra $t9, $t8, 0xe
  /* 043E0C 800C842C 00000000 */       nop 
  /* 043E10 800C8430 032B0019 */     multu $t9, $t3
  /* 043E14 800C8434 01E5C824 */       and $t9, $t7, $a1
  /* 043E18 800C8438 00007012 */      mflo $t6
  /* 043E1C 800C843C 000EC203 */       sra $t8, $t6, 8
  /* 043E20 800C8440 00187402 */       srl $t6, $t8, 0x10
  /* 043E24 800C8444 032E7825 */        or $t7, $t9, $t6
  /* 043E28 800C8448 AFB80004 */        sw $t8, 4($sp)
  /* 043E2C 800C844C AC8F0000 */        sw $t7, ($a0)
  /* 043E30 800C8450 8FAE0004 */        lw $t6, 4($sp)
  /* 043E34 800C8454 8FB80008 */        lw $t8, 8($sp)
  /* 043E38 800C8458 31CFFFFF */      andi $t7, $t6, 0xffff
  /* 043E3C 800C845C 00097023 */      negu $t6, $t1
  /* 043E40 800C8460 01CB0019 */     multu $t6, $t3
  /* 043E44 800C8464 0018CC00 */       sll $t9, $t8, 0x10
  /* 043E48 800C8468 032FC025 */        or $t8, $t9, $t7
  /* 043E4C 800C846C AC980020 */        sw $t8, 0x20($a0)
  /* 043E50 800C8470 0000C812 */      mflo $t9
  /* 043E54 800C8474 001979C3 */       sra $t7, $t9, 7
  /* 043E58 800C8478 AFAF000C */        sw $t7, 0xc($sp)
  /* 043E5C 800C847C 01490019 */     multu $t2, $t1
  /* 043E60 800C8480 01E5C024 */       and $t8, $t7, $a1
  /* 043E64 800C8484 AC980004 */        sw $t8, 4($a0)
  /* 043E68 800C8488 8FAE000C */        lw $t6, 0xc($sp)
  /* 043E6C 800C848C 000ECC00 */       sll $t9, $t6, 0x10
  /* 043E70 800C8490 AC990024 */        sw $t9, 0x24($a0)
  /* 043E74 800C8494 00005812 */      mflo $t3
  /* 043E78 800C8498 000B5BC3 */       sra $t3, $t3, 0xf
  /* 043E7C 800C849C 00000000 */       nop 
  /* 043E80 800C84A0 01620019 */     multu $t3, $v0
  /* 043E84 800C84A4 00007812 */      mflo $t7
  /* 043E88 800C84A8 000FC383 */       sra $t8, $t7, 0xe
  /* 043E8C 800C84AC 00000000 */       nop 
  /* 043E90 800C84B0 01030019 */     multu $t0, $v1
  /* 043E94 800C84B4 00007012 */      mflo $t6
  /* 043E98 800C84B8 000ECB83 */       sra $t9, $t6, 0xe
  /* 043E9C 800C84BC 03197823 */      subu $t7, $t8, $t9
  /* 043EA0 800C84C0 01ED0019 */     multu $t7, $t5
  /* 043EA4 800C84C4 00007012 */      mflo $t6
  /* 043EA8 800C84C8 000EC203 */       sra $t8, $t6, 8
  /* 043EAC 800C84CC AFB80008 */        sw $t8, 8($sp)
  /* 043EB0 800C84D0 01630019 */     multu $t3, $v1
  /* 043EB4 800C84D4 0000C812 */      mflo $t9
  /* 043EB8 800C84D8 00197B83 */       sra $t7, $t9, 0xe
  /* 043EBC 800C84DC 00000000 */       nop 
  /* 043EC0 800C84E0 01020019 */     multu $t0, $v0
  /* 043EC4 800C84E4 00007012 */      mflo $t6
  /* 043EC8 800C84E8 000ECB83 */       sra $t9, $t6, 0xe
  /* 043ECC 800C84EC 01F97021 */      addu $t6, $t7, $t9
  /* 043ED0 800C84F0 01CD0019 */     multu $t6, $t5
  /* 043ED4 800C84F4 03057024 */       and $t6, $t8, $a1
  /* 043ED8 800C84F8 00007812 */      mflo $t7
  /* 043EDC 800C84FC 000FCA03 */       sra $t9, $t7, 8
  /* 043EE0 800C8500 00197C02 */       srl $t7, $t9, 0x10
  /* 043EE4 800C8504 01460019 */     multu $t2, $a2
  /* 043EE8 800C8508 01CFC025 */        or $t8, $t6, $t7
  /* 043EEC 800C850C AFB9000C */        sw $t9, 0xc($sp)
  /* 043EF0 800C8510 AC980008 */        sw $t8, 8($a0)
  /* 043EF4 800C8514 8FAF000C */        lw $t7, 0xc($sp)
  /* 043EF8 800C8518 8FB90008 */        lw $t9, 8($sp)
  /* 043EFC 800C851C 31F8FFFF */      andi $t8, $t7, 0xffff
  /* 043F00 800C8520 00197400 */       sll $t6, $t9, 0x10
  /* 043F04 800C8524 01D8C825 */        or $t9, $t6, $t8
  /* 043F08 800C8528 00007812 */      mflo $t7
  /* 043F0C 800C852C 000F7383 */       sra $t6, $t7, 0xe
  /* 043F10 800C8530 AC990028 */        sw $t9, 0x28($a0)
  /* 043F14 800C8534 01CD0019 */     multu $t6, $t5
  /* 043F18 800C8538 0000C012 */      mflo $t8
  /* 043F1C 800C853C 0018CA03 */       sra $t9, $t8, 8
  /* 043F20 800C8540 AFB9000C */        sw $t9, 0xc($sp)
  /* 043F24 800C8544 01090019 */     multu $t0, $t1
  /* 043F28 800C8548 03257824 */       and $t7, $t9, $a1
  /* 043F2C 800C854C AC8F000C */        sw $t7, 0xc($a0)
  /* 043F30 800C8550 8FAE000C */        lw $t6, 0xc($sp)
  /* 043F34 800C8554 000EC400 */       sll $t8, $t6, 0x10
  /* 043F38 800C8558 AC98002C */        sw $t8, 0x2c($a0)
  /* 043F3C 800C855C 00005812 */      mflo $t3
  /* 043F40 800C8560 000B5BC3 */       sra $t3, $t3, 0xf
  /* 043F44 800C8564 00000000 */       nop 
  /* 043F48 800C8568 01620019 */     multu $t3, $v0
  /* 043F4C 800C856C 0000C812 */      mflo $t9
  /* 043F50 800C8570 00197B83 */       sra $t7, $t9, 0xe
  /* 043F54 800C8574 00000000 */       nop 
  /* 043F58 800C8578 01430019 */     multu $t2, $v1
  /* 043F5C 800C857C 00007012 */      mflo $t6
  /* 043F60 800C8580 000EC383 */       sra $t8, $t6, 0xe
  /* 043F64 800C8584 01F8C821 */      addu $t9, $t7, $t8
  /* 043F68 800C8588 03270019 */     multu $t9, $a3
  /* 043F6C 800C858C 00006012 */      mflo $t4
  /* 043F70 800C8590 000C6203 */       sra $t4, $t4, 8
  /* 043F74 800C8594 00000000 */       nop 
  /* 043F78 800C8598 01630019 */     multu $t3, $v1
  /* 043F7C 800C859C 00007012 */      mflo $t6
  /* 043F80 800C85A0 000E7B83 */       sra $t7, $t6, 0xe
  /* 043F84 800C85A4 00000000 */       nop 
  /* 043F88 800C85A8 01420019 */     multu $t2, $v0
  /* 043F8C 800C85AC 0000C012 */      mflo $t8
  /* 043F90 800C85B0 0018CB83 */       sra $t9, $t8, 0xe
  /* 043F94 800C85B4 01F97023 */      subu $t6, $t7, $t9
  /* 043F98 800C85B8 01C70019 */     multu $t6, $a3
  /* 043F9C 800C85BC 0185C024 */       and $t8, $t4, $a1
  /* 043FA0 800C85C0 000C7400 */       sll $t6, $t4, 0x10
  /* 043FA4 800C85C4 00006812 */      mflo $t5
  /* 043FA8 800C85C8 000D6A03 */       sra $t5, $t5, 8
  /* 043FAC 800C85CC 000D7C02 */       srl $t7, $t5, 0x10
  /* 043FB0 800C85D0 01060019 */     multu $t0, $a2
  /* 043FB4 800C85D4 030FC825 */        or $t9, $t8, $t7
  /* 043FB8 800C85D8 AC990010 */        sw $t9, 0x10($a0)
  /* 043FBC 800C85DC 31B8FFFF */      andi $t8, $t5, 0xffff
  /* 043FC0 800C85E0 01D87825 */        or $t7, $t6, $t8
  /* 043FC4 800C85E4 AC8F0030 */        sw $t7, 0x30($a0)
  /* 043FC8 800C85E8 0000C812 */      mflo $t9
  /* 043FCC 800C85EC 00197383 */       sra $t6, $t9, 0xe
  /* 043FD0 800C85F0 00000000 */       nop 
  /* 043FD4 800C85F4 01C70019 */     multu $t6, $a3
  /* 043FD8 800C85F8 0000C012 */      mflo $t8
  /* 043FDC 800C85FC 00187A03 */       sra $t7, $t8, 8
  /* 043FE0 800C8600 AFAF0010 */        sw $t7, 0x10($sp)
  /* 043FE4 800C8604 01E5C824 */       and $t9, $t7, $a1
  /* 043FE8 800C8608 AC990014 */        sw $t9, 0x14($a0)
  /* 043FEC 800C860C 8FAE0010 */        lw $t6, 0x10($sp)
  /* 043FF0 800C8610 240F0001 */     addiu $t7, $zero, 1
  /* 043FF4 800C8614 AC800018 */        sw $zero, 0x18($a0)
  /* 043FF8 800C8618 000EC400 */       sll $t8, $t6, 0x10
  /* 043FFC 800C861C AC980034 */        sw $t8, 0x34($a0)
  /* 044000 800C8620 AC800038 */        sw $zero, 0x38($a0)
  /* 044004 800C8624 AC8F001C */        sw $t7, 0x1c($a0)
  /* 044008 800C8628 AC80003C */        sw $zero, 0x3c($a0)
  /* 04400C 800C862C 03E00008 */        jr $ra
  /* 044010 800C8630 27BD0048 */     addiu $sp, $sp, 0x48

  /* 044014 800C8634 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 044018 800C8638 AFBF0014 */        sw $ra, 0x14($sp)
  /* 04401C 800C863C 0C002979 */       jal func_8000A5E4
  /* 044020 800C8640 00000000 */       nop 
  /* 044024 800C8644 8FBF0014 */        lw $ra, 0x14($sp)
  /* 044028 800C8648 27BD0018 */     addiu $sp, $sp, 0x18
  /* 04402C 800C864C 03E00008 */        jr $ra
  /* 044030 800C8650 00000000 */       nop 

