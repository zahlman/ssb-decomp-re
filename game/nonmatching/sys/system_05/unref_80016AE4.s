.section .text
glabel unref_80016AE4
  /* 0176E4 80016AE4 27BDFF70 */     addiu $sp, $sp, -0x90
  /* 0176E8 80016AE8 AFBF001C */        sw $ra, 0x1c($sp)
  /* 0176EC 80016AEC AFB10018 */        sw $s1, 0x18($sp)
  /* 0176F0 80016AF0 AFB00014 */        sw $s0, 0x14($sp)
  /* 0176F4 80016AF4 AFA40090 */        sw $a0, 0x90($sp)
  /* 0176F8 80016AF8 AFA60098 */        sw $a2, 0x98($sp)
  /* 0176FC 80016AFC AFA7009C */        sw $a3, 0x9c($sp)
  /* 017700 80016B00 8C830000 */        lw $v1, ($a0)
  /* 017704 80016B04 3C0FDC08 */       lui $t7, (0xDC080008 >> 16) # 3691511816
  /* 017708 80016B08 35EF0008 */       ori $t7, $t7, (0xDC080008 & 0xFFFF) # 3691511816
  /* 01770C 80016B0C 00601025 */        or $v0, $v1, $zero
  /* 017710 80016B10 24B80008 */     addiu $t8, $a1, 8
  /* 017714 80016B14 AC580004 */        sw $t8, 4($v0)
  /* 017718 80016B18 AC4F0000 */        sw $t7, ($v0)
  /* 01771C 80016B1C 84A80010 */        lh $t0, 0x10($a1)
  /* 017720 80016B20 00A08025 */        or $s0, $a1, $zero
  /* 017724 80016B24 86090008 */        lh $t1, 8($s0)
  /* 017728 80016B28 860A0012 */        lh $t2, 0x12($s0)
  /* 01772C 80016B2C 860B000A */        lh $t3, 0xa($s0)
  /* 017730 80016B30 00807025 */        or $t6, $a0, $zero
  /* 017734 80016B34 24630008 */     addiu $v1, $v1, 8
  /* 017738 80016B38 05010002 */      bgez $t0, .L80016B44
  /* 01773C 80016B3C 01000821 */      addu $at, $t0, $zero
  /* 017740 80016B40 25010003 */     addiu $at, $t0, 3
  .L80016B44:
  /* 017744 80016B44 00014083 */       sra $t0, $at, 2
  /* 017748 80016B48 05210002 */      bgez $t1, .L80016B54
  /* 01774C 80016B4C 01200821 */      addu $at, $t1, $zero
  /* 017750 80016B50 25210003 */     addiu $at, $t1, 3
  .L80016B54:
  /* 017754 80016B54 00014883 */       sra $t1, $at, 2
  /* 017758 80016B58 0109F823 */      subu $ra, $t0, $t1
  /* 01775C 80016B5C 05410002 */      bgez $t2, .L80016B68
  /* 017760 80016B60 01400821 */      addu $at, $t2, $zero
  /* 017764 80016B64 25410003 */     addiu $at, $t2, 3
  .L80016B68:
  /* 017768 80016B68 00015083 */       sra $t2, $at, 2
  /* 01776C 80016B6C 05610002 */      bgez $t3, .L80016B78
  /* 017770 80016B70 01600821 */      addu $at, $t3, $zero
  /* 017774 80016B74 25610003 */     addiu $at, $t3, 3
  .L80016B78:
  /* 017778 80016B78 00015883 */       sra $t3, $at, 2
  /* 01777C 80016B7C 014B8823 */      subu $s1, $t2, $t3
  /* 017780 80016B80 01286021 */      addu $t4, $t1, $t0
  /* 017784 80016B84 07E10002 */      bgez $ra, .L80016B90
  /* 017788 80016B88 016A6821 */      addu $t5, $t3, $t2
  /* 01778C 80016B8C 0000F825 */        or $ra, $zero, $zero
  .L80016B90:
  /* 017790 80016B90 06210002 */      bgez $s1, .L80016B9C
  /* 017794 80016B94 8FA800A0 */        lw $t0, 0xa0($sp)
  /* 017798 80016B98 00008825 */        or $s1, $zero, $zero
  .L80016B9C:
  /* 01779C 80016B9C 010C082A */       slt $at, $t0, $t4
  /* 0177A0 80016BA0 10200002 */      beqz $at, .L80016BAC
  /* 0177A4 80016BA4 8FA200A4 */        lw $v0, 0xa4($sp)
  /* 0177A8 80016BA8 01006025 */        or $t4, $t0, $zero
  .L80016BAC:
  /* 0177AC 80016BAC 449F2000 */      mtc1 $ra, $f4
  /* 0177B0 80016BB0 004D082A */       slt $at, $v0, $t5
  /* 0177B4 80016BB4 10200002 */      beqz $at, .L80016BC0
  /* 0177B8 80016BB8 468021A0 */   cvt.s.w $f6, $f4
  /* 0177BC 80016BBC 00406825 */        or $t5, $v0, $zero
  .L80016BC0:
  /* 0177C0 80016BC0 44918000 */      mtc1 $s1, $f16
  /* 0177C4 80016BC4 3C014080 */       lui $at, (0x40800000 >> 16) # 4.0
  /* 0177C8 80016BC8 44810000 */      mtc1 $at, $f0 # 4.0 to cop1
  /* 0177CC 80016BCC 468084A0 */   cvt.s.w $f18, $f16
  /* 0177D0 80016BD0 3C01ED00 */       lui $at, 0xed00
  /* 0177D4 80016BD4 46003202 */     mul.s $f8, $f6, $f0
  /* 0177D8 80016BD8 00601025 */        or $v0, $v1, $zero
  /* 0177DC 80016BDC 24630008 */     addiu $v1, $v1, 8
  /* 0177E0 80016BE0 46009102 */     mul.s $f4, $f18, $f0
  /* 0177E4 80016BE4 4600428D */ trunc.w.s $f10, $f8
  /* 0177E8 80016BE8 448C4000 */      mtc1 $t4, $f8
  /* 0177EC 80016BEC 258CFFFF */     addiu $t4, $t4, -1
  /* 0177F0 80016BF0 4600218D */ trunc.w.s $f6, $f4
  /* 0177F4 80016BF4 440E5000 */      mfc1 $t6, $f10
  /* 0177F8 80016BF8 448D2000 */      mtc1 $t5, $f4
  /* 0177FC 80016BFC 468042A0 */   cvt.s.w $f10, $f8
  /* 017800 80016C00 31CF0FFF */      andi $t7, $t6, 0xfff
  /* 017804 80016C04 000FC300 */       sll $t8, $t7, 0xc
  /* 017808 80016C08 440F3000 */      mfc1 $t7, $f6
  /* 01780C 80016C0C 0301C825 */        or $t9, $t8, $at
  /* 017810 80016C10 468021A0 */   cvt.s.w $f6, $f4
  /* 017814 80016C14 46005402 */     mul.s $f16, $f10, $f0
  /* 017818 80016C18 31F80FFF */      andi $t8, $t7, 0xfff
  /* 01781C 80016C1C 03387025 */        or $t6, $t9, $t8
  /* 017820 80016C20 AC4E0000 */        sw $t6, ($v0)
  /* 017824 80016C24 25ADFFFF */     addiu $t5, $t5, -1
  /* 017828 80016C28 46003202 */     mul.s $f8, $f6, $f0
  /* 01782C 80016C2C 3C01FF10 */       lui $at, 0xff10
  /* 017830 80016C30 4600848D */ trunc.w.s $f18, $f16
  /* 017834 80016C34 4600428D */ trunc.w.s $f10, $f8
  /* 017838 80016C38 44199000 */      mfc1 $t9, $f18
  /* 01783C 80016C3C 00000000 */       nop 
  /* 017840 80016C40 33380FFF */      andi $t8, $t9, 0xfff
  /* 017844 80016C44 44195000 */      mfc1 $t9, $f10
  /* 017848 80016C48 00187300 */       sll $t6, $t8, 0xc
  /* 01784C 80016C4C 33380FFF */      andi $t8, $t9, 0xfff
  /* 017850 80016C50 01D87825 */        or $t7, $t6, $t8
  /* 017854 80016C54 AC4F0004 */        sw $t7, 4($v0)
  /* 017858 80016C58 8E190080 */        lw $t9, 0x80($s0)
  /* 01785C 80016C5C 00601025 */        or $v0, $v1, $zero
  /* 017860 80016C60 3C18E700 */       lui $t8, 0xe700
  /* 017864 80016C64 332E0001 */      andi $t6, $t9, 1
  /* 017868 80016C68 11C0002F */      beqz $t6, .L80016D28
  /* 01786C 80016C6C 3C0FE300 */       lui $t7, (0xE3000A01 >> 16) # 3808430593
  /* 017870 80016C70 24630008 */     addiu $v1, $v1, 8
  /* 017874 80016C74 00602025 */        or $a0, $v1, $zero
  /* 017878 80016C78 AC580000 */        sw $t8, ($v0)
  /* 01787C 80016C7C AC400004 */        sw $zero, 4($v0)
  /* 017880 80016C80 24630008 */     addiu $v1, $v1, 8
  /* 017884 80016C84 35EF0A01 */       ori $t7, $t7, (0xE3000A01 & 0xFFFF) # 3808430593
  /* 017888 80016C88 3C190030 */       lui $t9, 0x30
  /* 01788C 80016C8C AC990004 */        sw $t9, 4($a0)
  /* 017890 80016C90 AC8F0000 */        sw $t7, ($a0)
  /* 017894 80016C94 00602825 */        or $a1, $v1, $zero
  /* 017898 80016C98 3C0EE200 */       lui $t6, (0xE200001C >> 16) # 3791650844
  /* 01789C 80016C9C 2518FFFF */     addiu $t8, $t0, -1
  /* 0178A0 80016CA0 35CE001C */       ori $t6, $t6, (0xE200001C & 0xFFFF) # 3791650844
  /* 0178A4 80016CA4 24630008 */     addiu $v1, $v1, 8
  /* 0178A8 80016CA8 330F0FFF */      andi $t7, $t8, 0xfff
  /* 0178AC 80016CAC ACAE0000 */        sw $t6, ($a1)
  /* 0178B0 80016CB0 ACA00004 */        sw $zero, 4($a1)
  /* 0178B4 80016CB4 01E1C825 */        or $t9, $t7, $at
  /* 0178B8 80016CB8 00603025 */        or $a2, $v1, $zero
  /* 0178BC 80016CBC ACD90000 */        sw $t9, ($a2)
  /* 0178C0 80016CC0 8FAE00A8 */        lw $t6, 0xa8($sp)
  /* 0178C4 80016CC4 24630008 */     addiu $v1, $v1, 8
  /* 0178C8 80016CC8 3C0FFFFC */       lui $t7, (0xFFFCFFFC >> 16) # 4294770684
  /* 0178CC 80016CCC ACCE0004 */        sw $t6, 4($a2)
  /* 0178D0 80016CD0 35EFFFFC */       ori $t7, $t7, (0xFFFCFFFC & 0xFFFF) # 4294770684
  /* 0178D4 80016CD4 00603825 */        or $a3, $v1, $zero
  /* 0178D8 80016CD8 319903FF */      andi $t9, $t4, 0x3ff
  /* 0178DC 80016CDC ACEF0004 */        sw $t7, 4($a3)
  /* 0178E0 80016CE0 3C18F700 */       lui $t8, 0xf700
  /* 0178E4 80016CE4 00197380 */       sll $t6, $t9, 0xe
  /* 0178E8 80016CE8 ACF80000 */        sw $t8, ($a3)
  /* 0178EC 80016CEC 31AF03FF */      andi $t7, $t5, 0x3ff
  /* 0178F0 80016CF0 3C01F600 */       lui $at, 0xf600
  /* 0178F4 80016CF4 01C1C025 */        or $t8, $t6, $at
  /* 0178F8 80016CF8 000FC880 */       sll $t9, $t7, 2
  /* 0178FC 80016CFC 03197025 */        or $t6, $t8, $t9
  /* 017900 80016D00 24630008 */     addiu $v1, $v1, 8
  /* 017904 80016D04 00601025 */        or $v0, $v1, $zero
  /* 017908 80016D08 AC4E0000 */        sw $t6, ($v0)
  /* 01790C 80016D0C 323903FF */      andi $t9, $s1, 0x3ff
  /* 017910 80016D10 33EF03FF */      andi $t7, $ra, 0x3ff
  /* 017914 80016D14 000FC380 */       sll $t8, $t7, 0xe
  /* 017918 80016D18 00197080 */       sll $t6, $t9, 2
  /* 01791C 80016D1C 030E7825 */        or $t7, $t8, $t6
  /* 017920 80016D20 AC4F0004 */        sw $t7, 4($v0)
  /* 017924 80016D24 24630008 */     addiu $v1, $v1, 8
  .L80016D28:
  /* 017928 80016D28 00601025 */        or $v0, $v1, $zero
  /* 01792C 80016D2C 3C19E700 */       lui $t9, 0xe700
  /* 017930 80016D30 AC590000 */        sw $t9, ($v0)
  /* 017934 80016D34 AC400004 */        sw $zero, 4($v0)
  /* 017938 80016D38 3C188004 */       lui $t8, %hi(gPixelComponentSize)
  /* 01793C 80016D3C 8F186674 */        lw $t8, %lo(gPixelComponentSize)($t8)
  /* 017940 80016D40 3C01FF00 */       lui $at, 0xff00
  /* 017944 80016D44 24630008 */     addiu $v1, $v1, 8
  /* 017948 80016D48 330E0003 */      andi $t6, $t8, 3
  /* 01794C 80016D4C 000E7CC0 */       sll $t7, $t6, 0x13
  /* 017950 80016D50 2518FFFF */     addiu $t8, $t0, -1
  /* 017954 80016D54 330E0FFF */      andi $t6, $t8, 0xfff
  /* 017958 80016D58 01E1C825 */        or $t9, $t7, $at
  /* 01795C 80016D5C 032E7825 */        or $t7, $t9, $t6
  /* 017960 80016D60 00602025 */        or $a0, $v1, $zero
  /* 017964 80016D64 AC8F0000 */        sw $t7, ($a0)
  /* 017968 80016D68 8FB8009C */        lw $t8, 0x9c($sp)
  /* 01796C 80016D6C 24630008 */     addiu $v1, $v1, 8
  /* 017970 80016D70 00602825 */        or $a1, $v1, $zero
  /* 017974 80016D74 3C19FE00 */       lui $t9, 0xfe00
  /* 017978 80016D78 AC980004 */        sw $t8, 4($a0)
  /* 01797C 80016D7C ACB90000 */        sw $t9, ($a1)
  /* 017980 80016D80 8FAE00A8 */        lw $t6, 0xa8($sp)
  /* 017984 80016D84 24630008 */     addiu $v1, $v1, 8
  /* 017988 80016D88 3C19E300 */       lui $t9, (0xE3000A01 >> 16) # 3808430593
  /* 01798C 80016D8C ACAE0004 */        sw $t6, 4($a1)
  /* 017990 80016D90 8E0F0080 */        lw $t7, 0x80($s0)
  /* 017994 80016D94 24650008 */     addiu $a1, $v1, 8
  /* 017998 80016D98 37390A01 */       ori $t9, $t9, (0xE3000A01 & 0xFFFF) # 3808430593
  /* 01799C 80016D9C 31F80002 */      andi $t8, $t7, 2
  /* 0179A0 80016DA0 13000027 */      beqz $t8, .L80016E40
  /* 0179A4 80016DA4 00601025 */        or $v0, $v1, $zero
  /* 0179A8 80016DA8 3C0E0030 */       lui $t6, 0x30
  /* 0179AC 80016DAC AC4E0004 */        sw $t6, 4($v0)
  /* 0179B0 80016DB0 AC590000 */        sw $t9, ($v0)
  /* 0179B4 80016DB4 3C0FE200 */       lui $t7, (0xE200001C >> 16) # 3791650844
  /* 0179B8 80016DB8 35EF001C */       ori $t7, $t7, (0xE200001C & 0xFFFF) # 3791650844
  /* 0179BC 80016DBC ACAF0000 */        sw $t7, ($a1)
  /* 0179C0 80016DC0 ACA00004 */        sw $zero, 4($a1)
  /* 0179C4 80016DC4 24A60008 */     addiu $a2, $a1, 8
  /* 0179C8 80016DC8 319903FF */      andi $t9, $t4, 0x3ff
  /* 0179CC 80016DCC 3C18F700 */       lui $t8, 0xf700
  /* 0179D0 80016DD0 ACD80000 */        sw $t8, ($a2)
  /* 0179D4 80016DD4 00197380 */       sll $t6, $t9, 0xe
  /* 0179D8 80016DD8 31B803FF */      andi $t8, $t5, 0x3ff
  /* 0179DC 80016DDC 3C01F600 */       lui $at, 0xf600
  /* 0179E0 80016DE0 01C17825 */        or $t7, $t6, $at
  /* 0179E4 80016DE4 0018C880 */       sll $t9, $t8, 2
  /* 0179E8 80016DE8 01F97025 */        or $t6, $t7, $t9
  /* 0179EC 80016DEC 8E040084 */        lw $a0, 0x84($s0)
  /* 0179F0 80016DF0 AFAE0028 */        sw $t6, 0x28($sp)
  /* 0179F4 80016DF4 323903FF */      andi $t9, $s1, 0x3ff
  /* 0179F8 80016DF8 33F803FF */      andi $t8, $ra, 0x3ff
  /* 0179FC 80016DFC 00187B80 */       sll $t7, $t8, 0xe
  /* 017A00 80016E00 00197080 */       sll $t6, $t9, 2
  /* 017A04 80016E04 01EEC025 */        or $t8, $t7, $t6
  /* 017A08 80016E08 24C30008 */     addiu $v1, $a2, 8
  /* 017A0C 80016E0C AFA3008C */        sw $v1, 0x8c($sp)
  /* 017A10 80016E10 AFB80024 */        sw $t8, 0x24($sp)
  /* 017A14 80016E14 0C001B5C */       jal gsGetFillColor
  /* 017A18 80016E18 AFA60040 */        sw $a2, 0x40($sp)
  /* 017A1C 80016E1C 8FA60040 */        lw $a2, 0x40($sp)
  /* 017A20 80016E20 8FA3008C */        lw $v1, 0x8c($sp)
  /* 017A24 80016E24 ACC20004 */        sw $v0, 4($a2)
  /* 017A28 80016E28 8FB90028 */        lw $t9, 0x28($sp)
  /* 017A2C 80016E2C 00602025 */        or $a0, $v1, $zero
  /* 017A30 80016E30 24630008 */     addiu $v1, $v1, 8
  /* 017A34 80016E34 AC990000 */        sw $t9, ($a0)
  /* 017A38 80016E38 8FAF0024 */        lw $t7, 0x24($sp)
  /* 017A3C 80016E3C AC8F0004 */        sw $t7, 4($a0)
  .L80016E40:
  /* 017A40 80016E40 00601025 */        or $v0, $v1, $zero
  /* 017A44 80016E44 24630008 */     addiu $v1, $v1, 8
  /* 017A48 80016E48 3C0EE700 */       lui $t6, 0xe700
  /* 017A4C 80016E4C AC4E0000 */        sw $t6, ($v0)
  /* 017A50 80016E50 AC400004 */        sw $zero, 4($v0)
  /* 017A54 80016E54 00602025 */        or $a0, $v1, $zero
  /* 017A58 80016E58 3C18E300 */       lui $t8, (0xE3000A01 >> 16) # 3808430593
  /* 017A5C 80016E5C 37180A01 */       ori $t8, $t8, (0xE3000A01 & 0xFFFF) # 3808430593
  /* 017A60 80016E60 AC980000 */        sw $t8, ($a0)
  /* 017A64 80016E64 AC800004 */        sw $zero, 4($a0)
  /* 017A68 80016E68 8FB90098 */        lw $t9, 0x98($sp)
  /* 017A6C 80016E6C 24630008 */     addiu $v1, $v1, 8
  /* 017A70 80016E70 24010002 */     addiu $at, $zero, 2
  /* 017A74 80016E74 13200003 */      beqz $t9, .L80016E84
  /* 017A78 80016E78 00601025 */        or $v0, $v1, $zero
  /* 017A7C 80016E7C 17210009 */       bne $t9, $at, .L80016EA4
  /* 017A80 80016E80 3C18E200 */       lui $t8, (0xE200001C >> 16) # 3791650844
  .L80016E84:
  /* 017A84 80016E84 3C0FE200 */       lui $t7, (0xE200001C >> 16) # 3791650844
  /* 017A88 80016E88 3C0E0055 */       lui $t6, (0x552078 >> 16) # 5578872
  /* 017A8C 80016E8C 35CE2078 */       ori $t6, $t6, (0x552078 & 0xFFFF) # 5578872
  /* 017A90 80016E90 35EF001C */       ori $t7, $t7, (0xE200001C & 0xFFFF) # 3791650844
  /* 017A94 80016E94 AC4F0000 */        sw $t7, ($v0)
  /* 017A98 80016E98 AC4E0004 */        sw $t6, 4($v0)
  /* 017A9C 80016E9C 10000008 */         b .L80016EC0
  /* 017AA0 80016EA0 24630008 */     addiu $v1, $v1, 8
  .L80016EA4:
  /* 017AA4 80016EA4 00601025 */        or $v0, $v1, $zero
  /* 017AA8 80016EA8 3C190050 */       lui $t9, (0x5049D8 >> 16) # 5261784
  /* 017AAC 80016EAC 373949D8 */       ori $t9, $t9, (0x5049D8 & 0xFFFF) # 5261784
  /* 017AB0 80016EB0 3718001C */       ori $t8, $t8, (0xE200001C & 0xFFFF) # 3791650844
  /* 017AB4 80016EB4 AC580000 */        sw $t8, ($v0)
  /* 017AB8 80016EB8 AC590004 */        sw $t9, 4($v0)
  /* 017ABC 80016EBC 24630008 */     addiu $v1, $v1, 8
  .L80016EC0:
  /* 017AC0 80016EC0 8FAF0090 */        lw $t7, 0x90($sp)
  /* 017AC4 80016EC4 ADE30000 */        sw $v1, ($t7)
  /* 017AC8 80016EC8 8FBF001C */        lw $ra, 0x1c($sp)
  /* 017ACC 80016ECC 8FB10018 */        lw $s1, 0x18($sp)
  /* 017AD0 80016ED0 8FB00014 */        lw $s0, 0x14($sp)
  /* 017AD4 80016ED4 03E00008 */        jr $ra
  /* 017AD8 80016ED8 27BD0090 */     addiu $sp, $sp, 0x90

