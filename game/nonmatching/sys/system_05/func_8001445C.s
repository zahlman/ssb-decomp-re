.section .text
glabel odRenderDObjTreeDLLinks
  /* 01505C 8001445C 27BDFFB0 */     addiu $sp, $sp, -0x50
  /* 015060 80014460 AFBF002C */        sw $ra, 0x2c($sp)
  /* 015064 80014464 AFB40028 */        sw $s4, 0x28($sp)
  /* 015068 80014468 AFB30024 */        sw $s3, 0x24($sp)
  /* 01506C 8001446C AFB20020 */        sw $s2, 0x20($sp)
  /* 015070 80014470 AFB1001C */        sw $s1, 0x1c($sp)
  /* 015074 80014474 AFB00018 */        sw $s0, 0x18($sp)
  /* 015078 80014478 908E0054 */       lbu $t6, 0x54($a0)
  /* 01507C 8001447C 00809825 */        or $s3, $a0, $zero
  /* 015080 80014480 0000A025 */        or $s4, $zero, $zero
  /* 015084 80014484 31CF0002 */      andi $t7, $t6, 2
  /* 015088 80014488 15E000A4 */      bnez $t7, .L8001471C
  /* 01508C 8001448C 3C128004 */       lui $s2, %hi(D_800470B0)
  /* 015090 80014490 3C018004 */       lui $at, %hi(D_80046FA4)
  /* 015094 80014494 C4246FA4 */      lwc1 $f4, %lo(D_80046FA4)($at)
  /* 015098 80014498 265270B0 */     addiu $s2, $s2, %lo(D_800470B0)
  /* 01509C 8001449C 8E580000 */        lw $t8, ($s2) # D_800470B0 + 0
  /* 0150A0 800144A0 E7A40034 */      swc1 $f4, 0x34($sp)
  /* 0150A4 800144A4 8C860050 */        lw $a2, 0x50($a0)
  /* 0150A8 800144A8 02402025 */        or $a0, $s2, $zero
  /* 0150AC 800144AC 02602825 */        or $a1, $s3, $zero
  /* 0150B0 800144B0 AFB80040 */        sw $t8, 0x40($sp)
  /* 0150B4 800144B4 0C00435C */       jal odRenderDObjMain
  /* 0150B8 800144B8 AFA60044 */        sw $a2, 0x44($sp)
  /* 0150BC 800144BC 8FA60044 */        lw $a2, 0x44($sp)
  /* 0150C0 800144C0 00405825 */        or $t3, $v0, $zero
  /* 0150C4 800144C4 50C00057 */      beql $a2, $zero, .L80014624
  /* 0150C8 800144C8 8E640010 */        lw $a0, 0x10($s3)
  /* 0150CC 800144CC 92790054 */       lbu $t9, 0x54($s3)
  /* 0150D0 800144D0 332D0001 */      andi $t5, $t9, 1
  /* 0150D4 800144D4 55A00053 */      bnel $t5, $zero, .L80014624
  /* 0150D8 800144D8 8E640010 */        lw $a0, 0x10($s3)
  /* 0150DC 800144DC 8CC20000 */        lw $v0, ($a2)
  /* 0150E0 800144E0 24010004 */     addiu $at, $zero, 4
  /* 0150E4 800144E4 3C118004 */       lui $s1, %hi(gDisplayListHead)
  /* 0150E8 800144E8 1041004D */       beq $v0, $at, .L80014620
  /* 0150EC 800144EC 263165B0 */     addiu $s1, $s1, %lo(gDisplayListHead)
  /* 0150F0 800144F0 3C078004 */       lui $a3, %hi(D_800470B8)
  /* 0150F4 800144F4 24E770B8 */     addiu $a3, $a3, %lo(D_800470B8)
  /* 0150F8 800144F8 8CCE0004 */        lw $t6, 4($a2)
  .L800144FC:
  /* 0150FC 800144FC 00028080 */       sll $s0, $v0, 2
  /* 015100 80014500 00F07821 */      addu $t7, $a3, $s0
  /* 015104 80014504 51C00042 */      beql $t6, $zero, .L80014610
  /* 015108 80014508 8CC20008 */        lw $v0, 8($a2)
  /* 01510C 8001450C 8DE40000 */        lw $a0, ($t7)
  /* 015110 80014510 8E580000 */        lw $t8, ($s2) # D_800470B0 + 0
  /* 015114 80014514 13040019 */       beq $t8, $a0, .L8001457C
  /* 015118 80014518 0230C821 */      addu $t9, $s1, $s0
  .L8001451C:
  # *(Gfx *) = *(Gfx *)
  /* 01511C 8001451C 8F2D0000 */        lw $t5, ($t9)
  /* 015120 80014520 8C8F0000 */        lw $t7, ($a0)
  /* 015124 80014524 ADAF0000 */        sw $t7, ($t5)
  /* 015128 80014528 8C8E0004 */        lw $t6, 4($a0)
  /* 01512C 8001452C ADAE0004 */        sw $t6, 4($t5)

  /* 015130 80014530 8CD80000 */        lw $t8, ($a2)
  /* 015134 80014534 0018C880 */       sll $t9, $t8, 2
  /* 015138 80014538 02391821 */      addu $v1, $s1, $t9
  /* 01513C 8001453C 8C6D0000 */        lw $t5, ($v1)
  /* 015140 80014540 25AE0008 */     addiu $t6, $t5, 8
  /* 015144 80014544 AC6E0000 */        sw $t6, ($v1)
  
  /* 015148 80014548 8CCF0000 */        lw $t7, ($a2)
  /* 01514C 8001454C 000FC080 */       sll $t8, $t7, 2
  /* 015150 80014550 00F81021 */      addu $v0, $a3, $t8
  /* 015154 80014554 8C590000 */        lw $t9, ($v0)
  /* 015158 80014558 8E4F0000 */        lw $t7, ($s2) # D_800470B0 + 0
  /* 01515C 8001455C 272D0008 */     addiu $t5, $t9, 8
  /* 015160 80014560 AC4D0000 */        sw $t5, ($v0)
  /* 015164 80014564 8CD00000 */        lw $s0, ($a2)
  /* 015168 80014568 00108080 */       sll $s0, $s0, 2
  /* 01516C 8001456C 00F07021 */      addu $t6, $a3, $s0
  /* 015170 80014570 8DC40000 */        lw $a0, ($t6)
  /* 015174 80014574 55E4FFE9 */      bnel $t7, $a0, .L8001451C
  /* 015178 80014578 0230C821 */      addu $t9, $s1, $s0
  .L8001457C:
  /* 01517C 8001457C 8E780080 */        lw $t8, 0x80($s3)
  /* 015180 80014580 5300001B */      beql $t8, $zero, .L800145F0
  /* 015184 80014584 02301821 */      addu $v1, $s1, $s0
  /* 015188 80014588 1680000F */      bnez $s4, .L800145C8
  /* 01518C 8001458C 02301821 */      addu $v1, $s1, $s0
  /* 015190 80014590 3C148004 */       lui $s4, %hi(gGraphicsHeap + 12)
  /* 015194 80014594 8E9465E4 */        lw $s4, %lo(gGraphicsHeap + 12)($s4)
  /* 015198 80014598 02602025 */        or $a0, $s3, $zero
  /* 01519C 8001459C 02302821 */      addu $a1, $s1, $s0
  /* 0151A0 800145A0 AFA60044 */        sw $a2, 0x44($sp)
  /* 0151A4 800145A4 0C004B64 */       jal odRenderMObjForDObj
  /* 0151A8 800145A8 AFAB0048 */        sw $t3, 0x48($sp)
  /* 0151AC 800145AC 8FA60044 */        lw $a2, 0x44($sp)
  /* 0151B0 800145B0 3C078004 */       lui $a3, %hi(D_800470B8)
  /* 0151B4 800145B4 24E770B8 */     addiu $a3, $a3, %lo(D_800470B8)
  /* 0151B8 800145B8 8CD00000 */        lw $s0, ($a2)
  /* 0151BC 800145BC 8FAB0048 */        lw $t3, 0x48($sp)
  /* 0151C0 800145C0 1000000A */         b .L800145EC
  /* 0151C4 800145C4 00108080 */       sll $s0, $s0, 2
  .L800145C8:
  /* 0151C8 800145C8 8C620000 */        lw $v0, ($v1)
  /* 0151CC 800145CC 3C0DDB06 */       lui $t5, (0xDB060038 >> 16) # 3674603576
  /* 0151D0 800145D0 35AD0038 */       ori $t5, $t5, (0xDB060038 & 0xFFFF) # 3674603576
  /* 0151D4 800145D4 24590008 */     addiu $t9, $v0, 8
  /* 0151D8 800145D8 AC790000 */        sw $t9, ($v1)
  /* 0151DC 800145DC AC540004 */        sw $s4, 4($v0)
  /* 0151E0 800145E0 AC4D0000 */        sw $t5, ($v0)
  /* 0151E4 800145E4 8CD00000 */        lw $s0, ($a2)
  /* 0151E8 800145E8 00108080 */       sll $s0, $s0, 2
  .L800145EC:
  /* 0151EC 800145EC 02301821 */      addu $v1, $s1, $s0
  .L800145F0:
  /* 0151F0 800145F0 8C620000 */        lw $v0, ($v1)
  /* 0151F4 800145F4 3C0FDE00 */       lui $t7, 0xde00
  /* 0151F8 800145F8 244E0008 */     addiu $t6, $v0, 8
  /* 0151FC 800145FC AC6E0000 */        sw $t6, ($v1)
  /* 015200 80014600 AC4F0000 */        sw $t7, ($v0)
  /* 015204 80014604 8CD80004 */        lw $t8, 4($a2)
  /* 015208 80014608 AC580004 */        sw $t8, 4($v0)
  /* 01520C 8001460C 8CC20008 */        lw $v0, 8($a2)
  .L80014610:
  /* 015210 80014610 24010004 */     addiu $at, $zero, 4
  /* 015214 80014614 24C60008 */     addiu $a2, $a2, 8
  /* 015218 80014618 5441FFB8 */      bnel $v0, $at, .L800144FC
  /* 01521C 8001461C 8CCE0004 */        lw $t6, 4($a2)
  .L80014620:
  /* 015220 80014620 8E640010 */        lw $a0, 0x10($s3)
  .L80014624:
  /* 015224 80014624 3C118004 */       lui $s1, %hi(gDisplayListHead)
  /* 015228 80014628 263165B0 */     addiu $s1, $s1, %lo(gDisplayListHead)
  /* 01522C 8001462C 50800005 */      beql $a0, $zero, .L80014644
  /* 015230 80014630 8FB90040 */        lw $t9, 0x40($sp)
  /* 015234 80014634 0C005117 */       jal odRenderDObjTreeDLLinks
  /* 015238 80014638 AFAB0048 */        sw $t3, 0x48($sp)
  /* 01523C 8001463C 8FAB0048 */        lw $t3, 0x48($sp)
  /* 015240 80014640 8FB90040 */        lw $t9, 0x40($sp)
  .L80014644:
  /* 015244 80014644 3C068004 */       lui $a2, %hi(D_800470B8)
  /* 015248 80014648 3C0C8004 */       lui $t4, %hi(D_800470C8)
  /* 01524C 8001464C 3C09D838 */       lui $t1, (0xD8380002 >> 16) # 3627548674
  /* 015250 80014650 35290002 */       ori $t1, $t1, (0xD8380002 & 0xFFFF) # 3627548674
  /* 015254 80014654 258C70C8 */     addiu $t4, $t4, %lo(D_800470C8)
  /* 015258 80014658 24C670B8 */     addiu $a2, $a2, %lo(D_800470B8)
  /* 01525C 8001465C 00003825 */        or $a3, $zero, $zero
  /* 015260 80014660 240A0040 */     addiu $t2, $zero, 0x40
  /* 015264 80014664 24080001 */     addiu $t0, $zero, 1
  /* 015268 80014668 AE590000 */        sw $t9, ($s2) # D_800470B0 + 0
  .L8001466C:
  /* 01526C 8001466C 8E450000 */        lw $a1, ($s2) # D_800470B0 + 0
  /* 015270 80014670 8CCD0000 */        lw $t5, ($a2) # D_800470B8 + 0
  /* 015274 80014674 00AD082B */      sltu $at, $a1, $t5
  /* 015278 80014678 50200011 */      beql $at, $zero, .L800146C0
  /* 01527C 8001467C 8CD90004 */        lw $t9, 4($a2) # D_800470B8 + 4
  /* 015280 80014680 1160000E */      beqz $t3, .L800146BC
  /* 015284 80014684 ACC50000 */        sw $a1, ($a2) # D_800470B8 + 0
  /* 015288 80014688 8E6E0014 */        lw $t6, 0x14($s3)
  /* 01528C 8001468C 02271821 */      addu $v1, $s1, $a3
  /* 015290 80014690 510E0005 */      beql $t0, $t6, .L800146A8
  /* 015294 80014694 8C640000 */        lw $a0, ($v1)
  /* 015298 80014698 8E6F0008 */        lw $t7, 8($s3)
  /* 01529C 8001469C 51E00008 */      beql $t7, $zero, .L800146C0
  /* 0152A0 800146A0 8CD90004 */        lw $t9, 4($a2) # D_800470B8 + 4
  /* 0152A4 800146A4 8C640000 */        lw $a0, ($v1)
  .L800146A8:
  /* 0152A8 800146A8 24980008 */     addiu $t8, $a0, 8
  /* 0152AC 800146AC AC780000 */        sw $t8, ($v1)
  /* 0152B0 800146B0 AC8A0004 */        sw $t2, 4($a0)
  /* 0152B4 800146B4 AC890000 */        sw $t1, ($a0)
  /* 0152B8 800146B8 8E450000 */        lw $a1, ($s2) # D_800470B0 + 0
  .L800146BC:
  /* 0152BC 800146BC 8CD90004 */        lw $t9, 4($a2) # D_800470B8 + 4
  .L800146C0:
  /* 0152C0 800146C0 00B9082B */      sltu $at, $a1, $t9
  /* 0152C4 800146C4 50200010 */      beql $at, $zero, .L80014708
  /* 0152C8 800146C8 24C60008 */     addiu $a2, $a2, 8
  /* 0152CC 800146CC 1160000D */      beqz $t3, .L80014704
  /* 0152D0 800146D0 ACC50004 */        sw $a1, 4($a2) # D_800470B8 + 4
  /* 0152D4 800146D4 8E6D0014 */        lw $t5, 0x14($s3)
  /* 0152D8 800146D8 02271821 */      addu $v1, $s1, $a3
  /* 0152DC 800146DC 510D0005 */      beql $t0, $t5, .L800146F4
  /* 0152E0 800146E0 8C640004 */        lw $a0, 4($v1)
  /* 0152E4 800146E4 8E6E0008 */        lw $t6, 8($s3)
  /* 0152E8 800146E8 51C00007 */      beql $t6, $zero, .L80014708
  /* 0152EC 800146EC 24C60008 */     addiu $a2, $a2, 8
  /* 0152F0 800146F0 8C640004 */        lw $a0, 4($v1)
  .L800146F4:
  /* 0152F4 800146F4 248F0008 */     addiu $t7, $a0, 8
  /* 0152F8 800146F8 AC6F0004 */        sw $t7, 4($v1)
  /* 0152FC 800146FC AC8A0004 */        sw $t2, 4($a0)
  /* 015300 80014700 AC890000 */        sw $t1, ($a0)
  .L80014704:
  /* 015304 80014704 24C60008 */     addiu $a2, $a2, 8
  .L80014708:
  /* 015308 80014708 14CCFFD8 */       bne $a2, $t4, .L8001466C
  /* 01530C 8001470C 24E70008 */     addiu $a3, $a3, 8
  /* 015310 80014710 C7A60034 */      lwc1 $f6, 0x34($sp)
  /* 015314 80014714 3C018004 */       lui $at, %hi(D_80046FA4)
  /* 015318 80014718 E4266FA4 */      swc1 $f6, %lo(D_80046FA4)($at)
  .L8001471C:
  /* 01531C 8001471C 8E78000C */        lw $t8, 0xc($s3)
  /* 015320 80014720 5700000A */      bnel $t8, $zero, .L8001474C
  /* 015324 80014724 8FBF002C */        lw $ra, 0x2c($sp)
  /* 015328 80014728 8E700008 */        lw $s0, 8($s3)
  /* 01532C 8001472C 52000007 */      beql $s0, $zero, .L8001474C
  /* 015330 80014730 8FBF002C */        lw $ra, 0x2c($sp)
  .L80014734:
  /* 015334 80014734 0C005117 */       jal odRenderDObjTreeDLLinks
  /* 015338 80014738 02002025 */        or $a0, $s0, $zero
  /* 01533C 8001473C 8E100008 */        lw $s0, 8($s0)
  /* 015340 80014740 1600FFFC */      bnez $s0, .L80014734
  /* 015344 80014744 00000000 */       nop 
  /* 015348 80014748 8FBF002C */        lw $ra, 0x2c($sp)
  .L8001474C:
  /* 01534C 8001474C 8FB00018 */        lw $s0, 0x18($sp)
  /* 015350 80014750 8FB1001C */        lw $s1, 0x1c($sp)
  /* 015354 80014754 8FB20020 */        lw $s2, 0x20($sp)
  /* 015358 80014758 8FB30024 */        lw $s3, 0x24($sp)
  /* 01535C 8001475C 8FB40028 */        lw $s4, 0x28($sp)
  /* 015360 80014760 03E00008 */        jr $ra
  /* 015364 80014764 27BD0050 */     addiu $sp, $sp, 0x50

