.section .text
glabel func_8001663C
  /* 01723C 8001663C 27BDFF78 */     addiu $sp, $sp, -0x88
  /* 017240 80016640 AFBF0014 */        sw $ra, 0x14($sp)
  /* 017244 80016644 AFA40088 */        sw $a0, 0x88($sp)
  /* 017248 80016648 AFA5008C */        sw $a1, 0x8c($sp)
  /* 01724C 8001664C AFA60090 */        sw $a2, 0x90($sp)
  /* 017250 80016650 10C00004 */      beqz $a2, .L80016664
  /* 017254 80016654 8C830000 */        lw $v1, ($a0)
  /* 017258 80016658 24010001 */     addiu $at, $zero, 1
  /* 01725C 8001665C 54C10010 */      bnel $a2, $at, .L800166A0
  /* 017260 80016660 3C19DC08 */       lui $t9, 0xdc08
  .L80016664:
  /* 017264 80016664 8FB8008C */        lw $t8, 0x8c($sp)
  /* 017268 80016668 8FA40088 */        lw $a0, 0x88($sp)
  /* 01726C 8001666C 3C058004 */       lui $a1, %hi(D_80046626)
  /* 017270 80016670 8F190080 */        lw $t9, 0x80($t8)
  /* 017274 80016674 332E0020 */      andi $t6, $t9, 0x20
  /* 017278 80016678 51C00009 */      beql $t6, $zero, .L800166A0
  /* 01727C 8001667C 3C19DC08 */       lui $t9, 0xdc08
  /* 017280 80016680 0C0014D1 */       jal gsAppendGfxUCodeLoad
  /* 017284 80016684 94A56626 */       lhu $a1, %lo(D_80046626)($a1)
  /* 017288 80016688 8FB80088 */        lw $t8, 0x88($sp)
  /* 01728C 8001668C 240F0001 */     addiu $t7, $zero, 1
  /* 017290 80016690 3C018004 */       lui $at, %hi(D_80046628)
  /* 017294 80016694 A42F6628 */        sh $t7, %lo(D_80046628)($at)
  /* 017298 80016698 8F030000 */        lw $v1, ($t8)
  /* 01729C 8001669C 3C19DC08 */       lui $t9, (0xDC080008 >> 16) # 3691511816
  .L800166A0:
  /* 0172A0 800166A0 37390008 */       ori $t9, $t9, (0xDC080008 & 0xFFFF) # 3691511816
  /* 0172A4 800166A4 00602025 */        or $a0, $v1, $zero
  /* 0172A8 800166A8 AC990000 */        sw $t9, ($a0)
  /* 0172AC 800166AC 8FA2008C */        lw $v0, 0x8c($sp)
  /* 0172B0 800166B0 3C0D8004 */       lui $t5, %hi(gCurrScreenWidth)
  /* 0172B4 800166B4 3C0E8004 */       lui $t6, %hi(D_8003B938)
  /* 0172B8 800166B8 24420008 */     addiu $v0, $v0, 8
  /* 0172BC 800166BC AC820004 */        sw $v0, 4($a0)
  /* 0172C0 800166C0 84450008 */        lh $a1, 8($v0)
  /* 0172C4 800166C4 84460000 */        lh $a2, ($v0)
  /* 0172C8 800166C8 8447000A */        lh $a3, 0xa($v0)
  /* 0172CC 800166CC 84480002 */        lh $t0, 2($v0)
  /* 0172D0 800166D0 8DAD6678 */        lw $t5, %lo(gCurrScreenWidth)($t5)
  /* 0172D4 800166D4 8DCEB938 */        lw $t6, %lo(D_8003B938)($t6)
  /* 0172D8 800166D8 24630008 */     addiu $v1, $v1, 8
  /* 0172DC 800166DC 04A10002 */      bgez $a1, .L800166E8
  /* 0172E0 800166E0 00A00821 */      addu $at, $a1, $zero
  /* 0172E4 800166E4 24A10003 */     addiu $at, $a1, 3
  .L800166E8:
  /* 0172E8 800166E8 00012883 */       sra $a1, $at, 2
  /* 0172EC 800166EC 04C10002 */      bgez $a2, .L800166F8
  /* 0172F0 800166F0 00C00821 */      addu $at, $a2, $zero
  /* 0172F4 800166F4 24C10003 */     addiu $at, $a2, 3
  .L800166F8:
  /* 0172F8 800166F8 00013083 */       sra $a2, $at, 2
  /* 0172FC 800166FC 00A65823 */      subu $t3, $a1, $a2
  /* 017300 80016700 04E10002 */      bgez $a3, .L8001670C
  /* 017304 80016704 00E00821 */      addu $at, $a3, $zero
  /* 017308 80016708 24E10003 */     addiu $at, $a3, 3
  .L8001670C:
  /* 01730C 8001670C 00013883 */       sra $a3, $at, 2
  /* 017310 80016710 05010002 */      bgez $t0, .L8001671C
  /* 017314 80016714 01000821 */      addu $at, $t0, $zero
  /* 017318 80016718 25010003 */     addiu $at, $t0, 3
  .L8001671C:
  /* 01731C 8001671C 00014083 */       sra $t0, $at, 2
  /* 017320 80016720 24010140 */     addiu $at, $zero, 0x140
  /* 017324 80016724 01A1001A */       div $zero, $t5, $at
  /* 017328 80016728 0000F812 */      mflo $ra
  /* 01732C 8001672C 00E86023 */      subu $t4, $a3, $t0
  /* 017330 80016730 00C54821 */      addu $t1, $a2, $a1
  /* 017334 80016734 03EE0019 */     multu $ra, $t6
  /* 017338 80016738 01075021 */      addu $t2, $t0, $a3
  /* 01733C 8001673C 3C028004 */       lui $v0, %hi(gCurrScreenHeight)
  /* 017340 80016740 3C198004 */       lui $t9, %hi(D_8003B930)
  /* 017344 80016744 3C0E8004 */       lui $t6, %hi(D_8003B93C)
  /* 017348 80016748 3C188004 */       lui $t8, %hi(D_8003B934)
  /* 01734C 8001674C 00007812 */      mflo $t7
  /* 017350 80016750 016F082A */       slt $at, $t3, $t7
  /* 017354 80016754 10200002 */      beqz $at, .L80016760
  /* 017358 80016758 AFAF001C */        sw $t7, 0x1c($sp)
  /* 01735C 8001675C 01E05825 */        or $t3, $t7, $zero
  .L80016760:
  /* 017360 80016760 8C42667C */        lw $v0, %lo(gCurrScreenHeight)($v0)
  /* 017364 80016764 240100F0 */     addiu $at, $zero, 0xf0
  /* 017368 80016768 8F39B930 */        lw $t9, %lo(D_8003B930)($t9)
  /* 01736C 8001676C 0041001A */       div $zero, $v0, $at
  /* 017370 80016770 00002012 */      mflo $a0
  /* 017374 80016774 448B2000 */      mtc1 $t3, $f4
  /* 017378 80016778 3C08E200 */       lui $t0, (0xE200001C >> 16) # 3791650844
  /* 01737C 8001677C 00990019 */     multu $a0, $t9
  /* 017380 80016780 3508001C */       ori $t0, $t0, (0xE200001C & 0xFFFF) # 3791650844
  /* 017384 80016784 468021A0 */   cvt.s.w $f6, $f4
  /* 017388 80016788 00002812 */      mflo $a1
  /* 01738C 8001678C 0185082A */       slt $at, $t4, $a1
  /* 017390 80016790 10200002 */      beqz $at, .L8001679C
  /* 017394 80016794 00000000 */       nop 
  /* 017398 80016798 00A06025 */        or $t4, $a1, $zero
  .L8001679C:
  /* 01739C 8001679C 8DCEB93C */        lw $t6, %lo(D_8003B93C)($t6)
  /* 0173A0 800167A0 448C8000 */      mtc1 $t4, $f16
  /* 0173A4 800167A4 03EE0019 */     multu $ra, $t6
  /* 0173A8 800167A8 468084A0 */   cvt.s.w $f18, $f16
  /* 0173AC 800167AC 00007812 */      mflo $t7
  /* 0173B0 800167B0 01AF2823 */      subu $a1, $t5, $t7
  /* 0173B4 800167B4 00A9082A */       slt $at, $a1, $t1
  /* 0173B8 800167B8 10200002 */      beqz $at, .L800167C4
  /* 0173BC 800167BC 00000000 */       nop 
  /* 0173C0 800167C0 00A04825 */        or $t1, $a1, $zero
  .L800167C4:
  /* 0173C4 800167C4 8F18B934 */        lw $t8, %lo(D_8003B934)($t8)
  /* 0173C8 800167C8 3C0D8004 */       lui $t5, %hi(gCurrScreenWidth)
  /* 0173CC 800167CC 25AD6678 */     addiu $t5, $t5, %lo(gCurrScreenWidth)
  /* 0173D0 800167D0 00980019 */     multu $a0, $t8
  /* 0173D4 800167D4 0000C812 */      mflo $t9
  /* 0173D8 800167D8 00592823 */      subu $a1, $v0, $t9
  /* 0173DC 800167DC 00AA082A */       slt $at, $a1, $t2
  /* 0173E0 800167E0 50200003 */      beql $at, $zero, .L800167F0
  /* 0173E4 800167E4 3C014080 */       lui $at, 0x4080
  /* 0173E8 800167E8 00A05025 */        or $t2, $a1, $zero
  /* 0173EC 800167EC 3C014080 */       lui $at, (0x40800000 >> 16) # 4.0
  .L800167F0:
  /* 0173F0 800167F0 44810000 */      mtc1 $at, $f0 # 4.0 to cop1
  /* 0173F4 800167F4 3C01ED00 */       lui $at, 0xed00
  /* 0173F8 800167F8 8FBF008C */        lw $ra, 0x8c($sp)
  /* 0173FC 800167FC 46003202 */     mul.s $f8, $f6, $f0
  /* 017400 80016800 00601025 */        or $v0, $v1, $zero
  /* 017404 80016804 24630008 */     addiu $v1, $v1, 8
  /* 017408 80016808 46009102 */     mul.s $f4, $f18, $f0
  /* 01740C 8001680C 4600428D */ trunc.w.s $f10, $f8
  /* 017410 80016810 44894000 */      mtc1 $t1, $f8
  /* 017414 80016814 2529FFFF */     addiu $t1, $t1, -1
  /* 017418 80016818 4600218D */ trunc.w.s $f6, $f4
  /* 01741C 8001681C 440F5000 */      mfc1 $t7, $f10
  /* 017420 80016820 448A2000 */      mtc1 $t2, $f4
  /* 017424 80016824 468042A0 */   cvt.s.w $f10, $f8
  /* 017428 80016828 31F80FFF */      andi $t8, $t7, 0xfff
  /* 01742C 8001682C 0018CB00 */       sll $t9, $t8, 0xc
  /* 017430 80016830 44183000 */      mfc1 $t8, $f6
  /* 017434 80016834 03217025 */        or $t6, $t9, $at
  /* 017438 80016838 468021A0 */   cvt.s.w $f6, $f4
  /* 01743C 8001683C 46005402 */     mul.s $f16, $f10, $f0
  /* 017440 80016840 33190FFF */      andi $t9, $t8, 0xfff
  /* 017444 80016844 01D97825 */        or $t7, $t6, $t9
  /* 017448 80016848 AC4F0000 */        sw $t7, ($v0)
  /* 01744C 8001684C 254AFFFF */     addiu $t2, $t2, -1
  /* 017450 80016850 46003202 */     mul.s $f8, $f6, $f0
  /* 017454 80016854 3C01FF10 */       lui $at, 0xff10
  /* 017458 80016858 4600848D */ trunc.w.s $f18, $f16
  /* 01745C 8001685C 4600428D */ trunc.w.s $f10, $f8
  /* 017460 80016860 440E9000 */      mfc1 $t6, $f18
  /* 017464 80016864 00000000 */       nop 
  /* 017468 80016868 31D90FFF */      andi $t9, $t6, 0xfff
  /* 01746C 8001686C 440E5000 */      mfc1 $t6, $f10
  /* 017470 80016870 00197B00 */       sll $t7, $t9, 0xc
  /* 017474 80016874 31D90FFF */      andi $t9, $t6, 0xfff
  /* 017478 80016878 01F9C025 */        or $t8, $t7, $t9
  /* 01747C 8001687C AC580004 */        sw $t8, 4($v0)
  /* 017480 80016880 8FEE0080 */        lw $t6, 0x80($ra)
  /* 017484 80016884 00601025 */        or $v0, $v1, $zero
  /* 017488 80016888 3C19E700 */       lui $t9, 0xe700
  /* 01748C 8001688C 31CF0001 */      andi $t7, $t6, 1
  /* 017490 80016890 11E0002F */      beqz $t7, .L80016950
  /* 017494 80016894 3C18E300 */       lui $t8, (0xE3000A01 >> 16) # 3808430593
  /* 017498 80016898 24630008 */     addiu $v1, $v1, 8
  /* 01749C 8001689C 00602025 */        or $a0, $v1, $zero
  /* 0174A0 800168A0 AC590000 */        sw $t9, ($v0)
  /* 0174A4 800168A4 AC400004 */        sw $zero, 4($v0)
  /* 0174A8 800168A8 24630008 */     addiu $v1, $v1, 8
  /* 0174AC 800168AC 37180A01 */       ori $t8, $t8, (0xE3000A01 & 0xFFFF) # 3808430593
  /* 0174B0 800168B0 3C0E0030 */       lui $t6, 0x30
  /* 0174B4 800168B4 AC8E0004 */        sw $t6, 4($a0)
  /* 0174B8 800168B8 AC980000 */        sw $t8, ($a0)
  /* 0174BC 800168BC 00602825 */        or $a1, $v1, $zero
  /* 0174C0 800168C0 ACA80000 */        sw $t0, ($a1)
  /* 0174C4 800168C4 ACA00004 */        sw $zero, 4($a1)
  /* 0174C8 800168C8 8DAF0000 */        lw $t7, ($t5) # gCurrScreenWidth + 0
  /* 0174CC 800168CC 24630008 */     addiu $v1, $v1, 8
  /* 0174D0 800168D0 00603025 */        or $a2, $v1, $zero
  /* 0174D4 800168D4 25F9FFFF */     addiu $t9, $t7, -1
  /* 0174D8 800168D8 33380FFF */      andi $t8, $t9, 0xfff
  /* 0174DC 800168DC 03017025 */        or $t6, $t8, $at
  /* 0174E0 800168E0 ACCE0000 */        sw $t6, ($a2)
  /* 0174E4 800168E4 3C0F8004 */       lui $t7, %hi(gZBuffer)
  /* 0174E8 800168E8 8DEF6670 */        lw $t7, %lo(gZBuffer)($t7)
  /* 0174EC 800168EC 24630008 */     addiu $v1, $v1, 8
  /* 0174F0 800168F0 3C18FFFC */       lui $t8, (0xFFFCFFFC >> 16) # 4294770684
  /* 0174F4 800168F4 ACCF0004 */        sw $t7, 4($a2)
  /* 0174F8 800168F8 3718FFFC */       ori $t8, $t8, (0xFFFCFFFC & 0xFFFF) # 4294770684
  /* 0174FC 800168FC 00603825 */        or $a3, $v1, $zero
  /* 017500 80016900 312E03FF */      andi $t6, $t1, 0x3ff
  /* 017504 80016904 ACF80004 */        sw $t8, 4($a3)
  /* 017508 80016908 3C19F700 */       lui $t9, 0xf700
  /* 01750C 8001690C 000E7B80 */       sll $t7, $t6, 0xe
  /* 017510 80016910 ACF90000 */        sw $t9, ($a3)
  /* 017514 80016914 315803FF */      andi $t8, $t2, 0x3ff
  /* 017518 80016918 3C01F600 */       lui $at, 0xf600
  /* 01751C 8001691C 01E1C825 */        or $t9, $t7, $at
  /* 017520 80016920 00187080 */       sll $t6, $t8, 2
  /* 017524 80016924 032E7825 */        or $t7, $t9, $t6
  /* 017528 80016928 24630008 */     addiu $v1, $v1, 8
  /* 01752C 8001692C 00601025 */        or $v0, $v1, $zero
  /* 017530 80016930 AC4F0000 */        sw $t7, ($v0)
  /* 017534 80016934 318E03FF */      andi $t6, $t4, 0x3ff
  /* 017538 80016938 317803FF */      andi $t8, $t3, 0x3ff
  /* 01753C 8001693C 0018CB80 */       sll $t9, $t8, 0xe
  /* 017540 80016940 000E7880 */       sll $t7, $t6, 2
  /* 017544 80016944 032FC025 */        or $t8, $t9, $t7
  /* 017548 80016948 AC580004 */        sw $t8, 4($v0)
  /* 01754C 8001694C 24630008 */     addiu $v1, $v1, 8
  .L80016950:
  /* 017550 80016950 00601025 */        or $v0, $v1, $zero
  /* 017554 80016954 3C0EE700 */       lui $t6, 0xe700
  /* 017558 80016958 AC4E0000 */        sw $t6, ($v0)
  /* 01755C 8001695C AC400004 */        sw $zero, 4($v0)
  /* 017560 80016960 3C198004 */       lui $t9, %hi(gPixelComponentSize)
  /* 017564 80016964 8F396674 */        lw $t9, %lo(gPixelComponentSize)($t9)
  /* 017568 80016968 3C01FF00 */       lui $at, 0xff00
  /* 01756C 8001696C 24630008 */     addiu $v1, $v1, 8
  /* 017570 80016970 332F0003 */      andi $t7, $t9, 3
  /* 017574 80016974 8DB90000 */        lw $t9, ($t5) # gCurrScreenWidth + 0
  /* 017578 80016978 000FC4C0 */       sll $t8, $t7, 0x13
  /* 01757C 8001697C 03017025 */        or $t6, $t8, $at
  /* 017580 80016980 272FFFFF */     addiu $t7, $t9, -1
  /* 017584 80016984 31F80FFF */      andi $t8, $t7, 0xfff
  /* 017588 80016988 00602025 */        or $a0, $v1, $zero
  /* 01758C 8001698C 01D8C825 */        or $t9, $t6, $t8
  /* 017590 80016990 3C0F0F00 */       lui $t7, 0xf00
  /* 017594 80016994 AC8F0004 */        sw $t7, 4($a0)
  /* 017598 80016998 AC990000 */        sw $t9, ($a0)
  /* 01759C 8001699C 8FEE0080 */        lw $t6, 0x80($ra)
  /* 0175A0 800169A0 3C08E200 */       lui $t0, (0xE200001C >> 16) # 3791650844
  /* 0175A4 800169A4 3508001C */       ori $t0, $t0, (0xE200001C & 0xFFFF) # 3791650844
  /* 0175A8 800169A8 31D80002 */      andi $t8, $t6, 2
  /* 0175AC 800169AC 1300002B */      beqz $t8, .L80016A5C
  /* 0175B0 800169B0 24630008 */     addiu $v1, $v1, 8
  /* 0175B4 800169B4 3C19E300 */       lui $t9, (0xE3000A01 >> 16) # 3808430593
  /* 0175B8 800169B8 37390A01 */       ori $t9, $t9, (0xE3000A01 & 0xFFFF) # 3808430593
  /* 0175BC 800169BC 00601025 */        or $v0, $v1, $zero
  /* 0175C0 800169C0 AC590000 */        sw $t9, ($v0)
  /* 0175C4 800169C4 24650008 */     addiu $a1, $v1, 8
  /* 0175C8 800169C8 3C0F0030 */       lui $t7, 0x30
  /* 0175CC 800169CC AC4F0004 */        sw $t7, 4($v0)
  /* 0175D0 800169D0 ACA00004 */        sw $zero, 4($a1)
  /* 0175D4 800169D4 ACA80000 */        sw $t0, ($a1)
  /* 0175D8 800169D8 24A60008 */     addiu $a2, $a1, 8
  /* 0175DC 800169DC 3C0EF700 */       lui $t6, 0xf700
  /* 0175E0 800169E0 313803FF */      andi $t8, $t1, 0x3ff
  /* 0175E4 800169E4 0018CB80 */       sll $t9, $t8, 0xe
  /* 0175E8 800169E8 ACCE0000 */        sw $t6, ($a2)
  /* 0175EC 800169EC 314E03FF */      andi $t6, $t2, 0x3ff
  /* 0175F0 800169F0 3C01F600 */       lui $at, 0xf600
  /* 0175F4 800169F4 03217825 */        or $t7, $t9, $at
  /* 0175F8 800169F8 000EC080 */       sll $t8, $t6, 2
  /* 0175FC 800169FC 01F8C825 */        or $t9, $t7, $t8
  /* 017600 80016A00 8FE40084 */        lw $a0, 0x84($ra)
  /* 017604 80016A04 AFB90024 */        sw $t9, 0x24($sp)
  /* 017608 80016A08 319803FF */      andi $t8, $t4, 0x3ff
  /* 01760C 80016A0C 316E03FF */      andi $t6, $t3, 0x3ff
  /* 017610 80016A10 000E7B80 */       sll $t7, $t6, 0xe
  /* 017614 80016A14 0018C880 */       sll $t9, $t8, 2
  /* 017618 80016A18 01F97025 */        or $t6, $t7, $t9
  /* 01761C 80016A1C 24C30008 */     addiu $v1, $a2, 8
  /* 017620 80016A20 AFA30084 */        sw $v1, 0x84($sp)
  /* 017624 80016A24 AFAE0020 */        sw $t6, 0x20($sp)
  /* 017628 80016A28 0C001B5C */       jal gsGetFillColor
  /* 01762C 80016A2C AFA6003C */        sw $a2, 0x3c($sp)
  /* 017630 80016A30 8FA6003C */        lw $a2, 0x3c($sp)
  /* 017634 80016A34 8FA30084 */        lw $v1, 0x84($sp)
  /* 017638 80016A38 3C08E200 */       lui $t0, (0xE200001C >> 16) # 3791650844
  /* 01763C 80016A3C ACC20004 */        sw $v0, 4($a2)
  /* 017640 80016A40 8FB80024 */        lw $t8, 0x24($sp)
  /* 017644 80016A44 00602025 */        or $a0, $v1, $zero
  /* 017648 80016A48 3508001C */       ori $t0, $t0, (0xE200001C & 0xFFFF) # 3791650844
  /* 01764C 80016A4C AC980000 */        sw $t8, ($a0)
  /* 017650 80016A50 8FAF0020 */        lw $t7, 0x20($sp)
  /* 017654 80016A54 24630008 */     addiu $v1, $v1, 8
  /* 017658 80016A58 AC8F0004 */        sw $t7, 4($a0)
  .L80016A5C:
  /* 01765C 80016A5C 00601025 */        or $v0, $v1, $zero
  /* 017660 80016A60 24630008 */     addiu $v1, $v1, 8
  /* 017664 80016A64 3C19E700 */       lui $t9, 0xe700
  /* 017668 80016A68 AC590000 */        sw $t9, ($v0)
  /* 01766C 80016A6C AC400004 */        sw $zero, 4($v0)
  /* 017670 80016A70 00602025 */        or $a0, $v1, $zero
  /* 017674 80016A74 3C0EE300 */       lui $t6, (0xE3000A01 >> 16) # 3808430593
  /* 017678 80016A78 35CE0A01 */       ori $t6, $t6, (0xE3000A01 & 0xFFFF) # 3808430593
  /* 01767C 80016A7C AC8E0000 */        sw $t6, ($a0)
  /* 017680 80016A80 AC800004 */        sw $zero, 4($a0)
  /* 017684 80016A84 8FB80090 */        lw $t8, 0x90($sp)
  /* 017688 80016A88 24630008 */     addiu $v1, $v1, 8
  /* 01768C 80016A8C 24010002 */     addiu $at, $zero, 2
  /* 017690 80016A90 13000003 */      beqz $t8, .L80016AA0
  /* 017694 80016A94 00601025 */        or $v0, $v1, $zero
  /* 017698 80016A98 17010007 */       bne $t8, $at, .L80016AB8
  /* 01769C 80016A9C 3C190050 */       lui $t9, (0x5049D8 >> 16) # 5261784
  .L80016AA0:
  /* 0176A0 80016AA0 3C0F0055 */       lui $t7, (0x552078 >> 16) # 5578872
  /* 0176A4 80016AA4 35EF2078 */       ori $t7, $t7, (0x552078 & 0xFFFF) # 5578872
  /* 0176A8 80016AA8 AC4F0004 */        sw $t7, 4($v0)
  /* 0176AC 80016AAC 24630008 */     addiu $v1, $v1, 8
  /* 0176B0 80016AB0 10000006 */         b .L80016ACC
  /* 0176B4 80016AB4 AC480000 */        sw $t0, ($v0)
  .L80016AB8:
  /* 0176B8 80016AB8 00601025 */        or $v0, $v1, $zero
  /* 0176BC 80016ABC 373949D8 */       ori $t9, $t9, (0x5049D8 & 0xFFFF) # 5261784
  /* 0176C0 80016AC0 AC590004 */        sw $t9, 4($v0)
  /* 0176C4 80016AC4 AC480000 */        sw $t0, ($v0)
  /* 0176C8 80016AC8 24630008 */     addiu $v1, $v1, 8
  .L80016ACC:
  /* 0176CC 80016ACC 8FAE0088 */        lw $t6, 0x88($sp)
  /* 0176D0 80016AD0 ADC30000 */        sw $v1, ($t6)
  /* 0176D4 80016AD4 8FBF0014 */        lw $ra, 0x14($sp)
  /* 0176D8 80016AD8 27BD0088 */     addiu $sp, $sp, 0x88
  /* 0176DC 80016ADC 03E00008 */        jr $ra
  /* 0176E0 80016AE0 00000000 */       nop 

