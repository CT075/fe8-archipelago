	.cpu arm7tdmi
	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
	.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
	.eabi_attribute 26, 1	@ Tag_ABI_enum_size
	.eabi_attribute 30, 4	@ Tag_ABI_optimization_goals
	.eabi_attribute 34, 0	@ Tag_CPU_unaligned_access
	.eabi_attribute 18, 4	@ Tag_ABI_PCS_wchar_t
	.file	"levelCapSave.c"
@ GNU C17 (devkitARM release 61) version 13.1.0 (arm-none-eabi)
@	compiled by GNU C version 8.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.18-GMP

@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed: -mcpu=arm7tdmi -mthumb -mthumb-interwork -mtune=arm7tdmi -mlong-calls -march=armv4t -Os -ffreestanding
	.text
	.align	1
	.global	packProgCaps
	.syntax unified
	.code	16
	.thumb_func
	.type	packProgCaps, %function
packProgCaps:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
@ src/levelcap/levelCapSave.c:14:     result |= progCaps->swordLvlStage << 3;
	ldr	r3, .L2	@ tmp148,
@ src/levelcap/levelCapSave.c:23: }
	@ sp needed	@
@ src/levelcap/levelCapSave.c:14:     result |= progCaps->swordLvlStage << 3;
	ldr	r2, [r3, #4]	@ MEM[(struct ProgressiveCaps *)33812416B].swordLvlStage, MEM[(struct ProgressiveCaps *)33812416B].swordLvlStage
@ src/levelcap/levelCapSave.c:15:     result |= progCaps->lanceLvlStage << (3+2*1);
	ldr	r1, [r3, #8]	@ MEM[(struct ProgressiveCaps *)33812416B].lanceLvlStage, MEM[(struct ProgressiveCaps *)33812416B].lanceLvlStage
@ src/levelcap/levelCapSave.c:14:     result |= progCaps->swordLvlStage << 3;
	lsls	r2, r2, #3	@ tmp149, MEM[(struct ProgressiveCaps *)33812416B].swordLvlStage,
@ src/levelcap/levelCapSave.c:15:     result |= progCaps->lanceLvlStage << (3+2*1);
	lsls	r1, r1, #5	@ tmp152, MEM[(struct ProgressiveCaps *)33812416B].lanceLvlStage,
@ src/levelcap/levelCapSave.c:15:     result |= progCaps->lanceLvlStage << (3+2*1);
	orrs	r2, r1	@ tmp154, tmp152
	ldr	r1, [r3]	@ MEM[(struct ProgressiveCaps *)33812416B].lvlCapStage, MEM[(struct ProgressiveCaps *)33812416B].lvlCapStage
	orrs	r2, r1	@ result, MEM[(struct ProgressiveCaps *)33812416B].lvlCapStage
@ src/levelcap/levelCapSave.c:16:     result |= progCaps->axeLvlStage << (3+2*2);
	ldr	r1, [r3, #12]	@ MEM[(struct ProgressiveCaps *)33812416B].axeLvlStage, MEM[(struct ProgressiveCaps *)33812416B].axeLvlStage
	lsls	r1, r1, #7	@ tmp158, MEM[(struct ProgressiveCaps *)33812416B].axeLvlStage,
@ src/levelcap/levelCapSave.c:16:     result |= progCaps->axeLvlStage << (3+2*2);
	orrs	r2, r1	@ result, tmp158
@ src/levelcap/levelCapSave.c:17:     result |= progCaps->bowLvlStage << (3+2*3);
	ldr	r1, [r3, #16]	@ MEM[(struct ProgressiveCaps *)33812416B].bowLvlStage, MEM[(struct ProgressiveCaps *)33812416B].bowLvlStage
	lsls	r1, r1, #9	@ tmp161, MEM[(struct ProgressiveCaps *)33812416B].bowLvlStage,
@ src/levelcap/levelCapSave.c:17:     result |= progCaps->bowLvlStage << (3+2*3);
	orrs	r1, r2	@ result, result
@ src/levelcap/levelCapSave.c:18:     result |= progCaps->animaLvlStage << (3+2*4);
	ldr	r2, [r3, #20]	@ MEM[(struct ProgressiveCaps *)33812416B].animaLvlStage, MEM[(struct ProgressiveCaps *)33812416B].animaLvlStage
	lsls	r2, r2, #11	@ tmp164, MEM[(struct ProgressiveCaps *)33812416B].animaLvlStage,
@ src/levelcap/levelCapSave.c:18:     result |= progCaps->animaLvlStage << (3+2*4);
	orrs	r2, r1	@ result, result
@ src/levelcap/levelCapSave.c:19:     result |= progCaps->lightLvlStage << (3+2*5);
	ldr	r1, [r3, #24]	@ MEM[(struct ProgressiveCaps *)33812416B].lightLvlStage, MEM[(struct ProgressiveCaps *)33812416B].lightLvlStage
	lsls	r1, r1, #13	@ tmp167, MEM[(struct ProgressiveCaps *)33812416B].lightLvlStage,
@ src/levelcap/levelCapSave.c:19:     result |= progCaps->lightLvlStage << (3+2*5);
	orrs	r1, r2	@ result, result
@ src/levelcap/levelCapSave.c:20:     result |= progCaps->darkLvlStage << (3+2*6);
	ldr	r2, [r3, #28]	@ MEM[(struct ProgressiveCaps *)33812416B].darkLvlStage, MEM[(struct ProgressiveCaps *)33812416B].darkLvlStage
@ src/levelcap/levelCapSave.c:21:     result |= progCaps->staffLvlStage << (3+2*7);
	ldr	r0, [r3, #32]	@ MEM[(struct ProgressiveCaps *)33812416B].staffLvlStage, MEM[(struct ProgressiveCaps *)33812416B].staffLvlStage
@ src/levelcap/levelCapSave.c:20:     result |= progCaps->darkLvlStage << (3+2*6);
	lsls	r2, r2, #15	@ tmp170, MEM[(struct ProgressiveCaps *)33812416B].darkLvlStage,
@ src/levelcap/levelCapSave.c:20:     result |= progCaps->darkLvlStage << (3+2*6);
	orrs	r2, r1	@ result, result
@ src/levelcap/levelCapSave.c:21:     result |= progCaps->staffLvlStage << (3+2*7);
	lsls	r0, r0, #17	@ tmp174, MEM[(struct ProgressiveCaps *)33812416B].staffLvlStage,
@ src/levelcap/levelCapSave.c:21:     result |= progCaps->staffLvlStage << (3+2*7);
	orrs	r0, r2	@ result, result
@ src/levelcap/levelCapSave.c:23: }
	bx	lr
.L3:
	.align	2
.L2:
	.word	33812416
	.size	packProgCaps, .-packProgCaps
	.align	1
	.global	unpackProgCaps
	.syntax unified
	.code	16
	.thumb_func
	.type	unpackProgCaps, %function
unpackProgCaps:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
@ src/levelcap/levelCapSave.c:26:     progCaps->lvlCapStage = bonusFlags & 3;
	movs	r2, #3	@ tmp143,
@ src/levelcap/levelCapSave.c:35: }
	@ sp needed	@
@ src/levelcap/levelCapSave.c:26:     progCaps->lvlCapStage = bonusFlags & 3;
	ldr	r3, .L5	@ tmp141,
@ src/levelcap/levelCapSave.c:26:     progCaps->lvlCapStage = bonusFlags & 3;
	ands	r2, r0	@ tmp142, bonusFlags
@ src/levelcap/levelCapSave.c:26:     progCaps->lvlCapStage = bonusFlags & 3;
	str	r2, [r3]	@ tmp142, MEM[(struct ProgressiveCaps *)33812416B].lvlCapStage
@ src/levelcap/levelCapSave.c:27:     progCaps->swordLvlStage = (bonusFlags >> 3) & 2;
	movs	r2, #2	@ tmp147,
@ src/levelcap/levelCapSave.c:27:     progCaps->swordLvlStage = (bonusFlags >> 3) & 2;
	lsrs	r1, r0, #3	@ tmp145, bonusFlags,
@ src/levelcap/levelCapSave.c:27:     progCaps->swordLvlStage = (bonusFlags >> 3) & 2;
	ands	r1, r2	@ tmp146, tmp147
@ src/levelcap/levelCapSave.c:27:     progCaps->swordLvlStage = (bonusFlags >> 3) & 2;
	str	r1, [r3, #4]	@ tmp146, MEM[(struct ProgressiveCaps *)33812416B].swordLvlStage
@ src/levelcap/levelCapSave.c:28:     progCaps->lanceLvlStage = (bonusFlags >> (3+2*1)) & 2;
	lsrs	r1, r0, #5	@ tmp149, bonusFlags,
@ src/levelcap/levelCapSave.c:28:     progCaps->lanceLvlStage = (bonusFlags >> (3+2*1)) & 2;
	ands	r1, r2	@ tmp150, tmp147
@ src/levelcap/levelCapSave.c:28:     progCaps->lanceLvlStage = (bonusFlags >> (3+2*1)) & 2;
	str	r1, [r3, #8]	@ tmp150, MEM[(struct ProgressiveCaps *)33812416B].lanceLvlStage
@ src/levelcap/levelCapSave.c:29:     progCaps->axeLvlStage = (bonusFlags >> (3+2*2)) & 2;
	lsrs	r1, r0, #7	@ tmp153, bonusFlags,
@ src/levelcap/levelCapSave.c:29:     progCaps->axeLvlStage = (bonusFlags >> (3+2*2)) & 2;
	ands	r1, r2	@ tmp154, tmp147
@ src/levelcap/levelCapSave.c:29:     progCaps->axeLvlStage = (bonusFlags >> (3+2*2)) & 2;
	str	r1, [r3, #12]	@ tmp154, MEM[(struct ProgressiveCaps *)33812416B].axeLvlStage
@ src/levelcap/levelCapSave.c:30:     progCaps->bowLvlStage = (bonusFlags >> (3+2*3)) & 2;
	lsrs	r1, r0, #9	@ tmp157, bonusFlags,
@ src/levelcap/levelCapSave.c:30:     progCaps->bowLvlStage = (bonusFlags >> (3+2*3)) & 2;
	ands	r1, r2	@ tmp158, tmp147
@ src/levelcap/levelCapSave.c:30:     progCaps->bowLvlStage = (bonusFlags >> (3+2*3)) & 2;
	str	r1, [r3, #16]	@ tmp158, MEM[(struct ProgressiveCaps *)33812416B].bowLvlStage
@ src/levelcap/levelCapSave.c:31:     progCaps->animaLvlStage = (bonusFlags >> (3+2*4)) & 2;
	lsrs	r1, r0, #11	@ tmp161, bonusFlags,
@ src/levelcap/levelCapSave.c:31:     progCaps->animaLvlStage = (bonusFlags >> (3+2*4)) & 2;
	ands	r1, r2	@ tmp162, tmp147
@ src/levelcap/levelCapSave.c:31:     progCaps->animaLvlStage = (bonusFlags >> (3+2*4)) & 2;
	str	r1, [r3, #20]	@ tmp162, MEM[(struct ProgressiveCaps *)33812416B].animaLvlStage
@ src/levelcap/levelCapSave.c:32:     progCaps->lightLvlStage = (bonusFlags >> (3+2*5)) & 2;
	lsrs	r1, r0, #13	@ tmp165, bonusFlags,
@ src/levelcap/levelCapSave.c:32:     progCaps->lightLvlStage = (bonusFlags >> (3+2*5)) & 2;
	ands	r1, r2	@ tmp166, tmp147
@ src/levelcap/levelCapSave.c:32:     progCaps->lightLvlStage = (bonusFlags >> (3+2*5)) & 2;
	str	r1, [r3, #24]	@ tmp166, MEM[(struct ProgressiveCaps *)33812416B].lightLvlStage
@ src/levelcap/levelCapSave.c:33:     progCaps->darkLvlStage = (bonusFlags >> (3+2*6)) & 2;
	lsrs	r1, r0, #15	@ tmp169, bonusFlags,
@ src/levelcap/levelCapSave.c:34:     progCaps->staffLvlStage = (bonusFlags >> (3+2*7)) & 2;
	lsrs	r0, r0, #17	@ tmp173, bonusFlags,
@ src/levelcap/levelCapSave.c:33:     progCaps->darkLvlStage = (bonusFlags >> (3+2*6)) & 2;
	ands	r1, r2	@ tmp170, tmp147
@ src/levelcap/levelCapSave.c:34:     progCaps->staffLvlStage = (bonusFlags >> (3+2*7)) & 2;
	ands	r0, r2	@ tmp174, tmp147
@ src/levelcap/levelCapSave.c:33:     progCaps->darkLvlStage = (bonusFlags >> (3+2*6)) & 2;
	str	r1, [r3, #28]	@ tmp170, MEM[(struct ProgressiveCaps *)33812416B].darkLvlStage
@ src/levelcap/levelCapSave.c:34:     progCaps->staffLvlStage = (bonusFlags >> (3+2*7)) & 2;
	str	r0, [r3, #32]	@ tmp174, MEM[(struct ProgressiveCaps *)33812416B].staffLvlStage
@ src/levelcap/levelCapSave.c:35: }
	bx	lr
.L6:
	.align	2
.L5:
	.word	33812416
	.size	unpackProgCaps, .-unpackProgCaps
	.align	1
	.global	WriteGameSave
	.syntax unified
	.code	16
	.thumb_func
	.type	WriteGameSave, %function
WriteGameSave:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 160
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}	@
@ src/levelcap/levelCapSave.c:44:     struct GameSaveBlock *dest = GetSaveWriteAddr(slot);
	ldr	r3, .L12	@ tmp140,
@ src/levelcap/levelCapSave.c:38: {
	sub	sp, sp, #164	@,,
@ src/levelcap/levelCapSave.c:38: {
	movs	r5, r0	@ slot, tmp192
@ src/levelcap/levelCapSave.c:44:     struct GameSaveBlock *dest = GetSaveWriteAddr(slot);
	bl	.L14		@
@ src/levelcap/levelCapSave.c:45:     InvalidateSuspendSave(SAVE_ID_SUSPEND);
	ldr	r3, .L12+4	@ tmp141,
@ src/levelcap/levelCapSave.c:44:     struct GameSaveBlock *dest = GetSaveWriteAddr(slot);
	movs	r4, r0	@ dest, tmp193
@ src/levelcap/levelCapSave.c:45:     InvalidateSuspendSave(SAVE_ID_SUSPEND);
	movs	r0, #3	@,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:46:     gPlaySt.gameSaveSlot = slot;
	ldr	r6, .L12+8	@ tmp142,
@ src/levelcap/levelCapSave.c:47:     gPlaySt.time_saved = GetGameClock();
	ldr	r3, .L12+12	@ tmp144,
@ src/levelcap/levelCapSave.c:46:     gPlaySt.gameSaveSlot = slot;
	strb	r5, [r6, #12]	@ slot, gPlaySt.gameSaveSlot
@ src/levelcap/levelCapSave.c:47:     gPlaySt.time_saved = GetGameClock();
	bl	.L14		@
@ src/levelcap/levelCapSave.c:48:     WriteAndVerifySramFast(&gPlaySt, &dest->playSt, sizeof(gPlaySt));
	ldr	r3, .L12+16	@ tmp147,
@ src/levelcap/levelCapSave.c:47:     gPlaySt.time_saved = GetGameClock();
	str	r0, [r6]	@ tmp194, gPlaySt.time_saved
@ src/levelcap/levelCapSave.c:48:     WriteAndVerifySramFast(&gPlaySt, &dest->playSt, sizeof(gPlaySt));
	movs	r2, #76	@,
	movs	r0, r6	@, tmp142
	movs	r1, r4	@, dest
	str	r3, [sp, #4]	@ tmp147, %sfp
	bl	.L14		@
	movs	r3, #239	@ tmp202,
	movs	r6, r4	@ ivtmp.31, dest
	lsls	r3, r3, #3	@ tmp202, tmp202,
	adds	r3, r4, r3	@ _73, dest, tmp202
	ldr	r7, .L12+20	@ ivtmp.30,
	str	r3, [sp]	@ _73, %sfp
	adds	r6, r6, #76	@ ivtmp.31,
.L8:
@ src/levelcap/levelCapSave.c:51:         WriteGameSavePackedUnit(&gUnitArrayBlue[i], &dest->units[i]);
	movs	r1, r6	@, ivtmp.31
	movs	r0, r7	@, ivtmp.30
	ldr	r3, .L12+24	@ tmp148,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:50:     for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
	ldr	r3, [sp]	@ _73, %sfp
	adds	r6, r6, #36	@ ivtmp.31,
	adds	r7, r7, #72	@ ivtmp.30,
	cmp	r6, r3	@ ivtmp.31, _73
	bne	.L8		@,
@ src/levelcap/levelCapSave.c:53:     ReadGlobalSaveInfo(&info);
	ldr	r3, .L12+28	@ tmp150,
	add	r0, sp, #60	@,,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:55:     for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
	movs	r6, #0	@ i,
@ src/levelcap/levelCapSave.c:56:         SGM_SetCharacterKnown(UNIT_CHAR_ID(&gUnitArrayBlue[i]), &info);
	movs	r7, #72	@ tmp152,
.L9:
	movs	r3, r7	@ tmp153, tmp152
	muls	r3, r6	@ tmp153, i
	ldr	r2, .L12+20	@ tmp204,
	ldr	r3, [r2, r3]	@ MEM[(const struct CharacterData * *)&gUnitArrayBlue + _17 * 1], MEM[(const struct CharacterData * *)&gUnitArrayBlue + _17 * 1]
@ src/levelcap/levelCapSave.c:56:         SGM_SetCharacterKnown(UNIT_CHAR_ID(&gUnitArrayBlue[i]), &info);
	add	r1, sp, #60	@ tmp205,,
	ldrb	r0, [r3, #4]	@ tmp157,
@ src/levelcap/levelCapSave.c:55:     for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
	adds	r6, r6, #1	@ i,
@ src/levelcap/levelCapSave.c:56:         SGM_SetCharacterKnown(UNIT_CHAR_ID(&gUnitArrayBlue[i]), &info);
	ldr	r3, .L12+32	@ tmp158,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:55:     for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
	cmp	r6, #51	@ i,
	bne	.L9		@,
@ src/levelcap/levelCapSave.c:58:     WriteGlobalSaveInfo(&info);
	add	r0, sp, #60	@ tmp206,,
	ldr	r3, .L12+36	@ tmp160,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:59:     WriteGMMonsterRnState(&dest->gmUnit);
	ldr	r0, [sp]	@, %sfp
	ldr	r3, .L12+40	@ tmp162,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:60:     WriteSupplyItems(dest->supplyItems);
	ldr	r3, .L12+44	@ tmp207,
	adds	r0, r4, r3	@ tmp163, dest, tmp207
@ src/levelcap/levelCapSave.c:60:     WriteSupplyItems(dest->supplyItems);
	ldr	r3, .L12+48	@ tmp164,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:61:     WritePidStats(dest->pidStats);
	ldr	r3, .L12+52	@ tmp208,
	adds	r0, r4, r3	@ tmp165, dest, tmp208
@ src/levelcap/levelCapSave.c:61:     WritePidStats(dest->pidStats);
	ldr	r3, .L12+56	@ tmp166,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:62:     WriteChapterStats(dest->chapterStats);
	ldr	r3, .L12+60	@ tmp209,
	adds	r0, r4, r3	@ tmp167, dest, tmp209
@ src/levelcap/levelCapSave.c:62:     WriteChapterStats(dest->chapterStats);
	ldr	r3, .L12+64	@ tmp168,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:63:     dest->bonusClaimFlags = packProgCaps();
	bl	packProgCaps		@
@ src/levelcap/levelCapSave.c:63:     dest->bonusClaimFlags = packProgCaps();
	ldr	r3, .L12+68	@ tmp169,
	str	r0, [r4, r3]	@ tmp195, dest_24->bonusClaimFlags
@ src/levelcap/levelCapSave.c:64:     WriteBonusContentClaimFlags(dest);
	movs	r0, r4	@, dest
	ldr	r3, .L12+72	@ tmp170,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:65:     WritePermanentFlags(dest->permanentFlags);
	ldr	r3, .L12+76	@ tmp210,
	adds	r0, r4, r3	@ tmp171, dest, tmp210
@ src/levelcap/levelCapSave.c:65:     WritePermanentFlags(dest->permanentFlags);
	ldr	r3, .L12+80	@ tmp172,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:66:     WriteWorldMapStuff(&dest->wmStuff, &gGMData);
	ldr	r3, .L12+84	@ tmp211,
@ src/levelcap/levelCapSave.c:66:     WriteWorldMapStuff(&dest->wmStuff, &gGMData);
	ldr	r1, .L12+88	@ tmp173,
@ src/levelcap/levelCapSave.c:66:     WriteWorldMapStuff(&dest->wmStuff, &gGMData);
	adds	r0, r4, r3	@ tmp174, dest, tmp211
@ src/levelcap/levelCapSave.c:66:     WriteWorldMapStuff(&dest->wmStuff, &gGMData);
	ldr	r3, .L12+92	@ tmp175,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:67:     SaveDungeonRecords(dungeon);
	add	r0, sp, #28	@ tmp212,,
	ldr	r3, .L12+96	@ tmp177,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:68:     WriteAndVerifySramFast(dungeon, dest->dungeons, sizeof(dungeon));
	movs	r3, #219	@ tmp213,
	lsls	r3, r3, #4	@ tmp213, tmp213,
@ src/levelcap/levelCapSave.c:68:     WriteAndVerifySramFast(dungeon, dest->dungeons, sizeof(dungeon));
	movs	r2, #32	@,
@ src/levelcap/levelCapSave.c:68:     WriteAndVerifySramFast(dungeon, dest->dungeons, sizeof(dungeon));
	adds	r1, r4, r3	@ tmp178, dest, tmp213
@ src/levelcap/levelCapSave.c:68:     WriteAndVerifySramFast(dungeon, dest->dungeons, sizeof(dungeon));
	add	r0, sp, #28	@ tmp214,,
	ldr	r3, [sp, #4]	@ tmp147, %sfp
	bl	.L14		@
@ src/levelcap/levelCapSave.c:70:     chunk.magic32 = SAVEMAGIC32;
	ldr	r3, .L12+100	@ tmp182,
	str	r3, [sp, #12]	@ tmp182, chunk.magic32
@ src/levelcap/levelCapSave.c:71:     chunk.kind = SAVEBLOCK_KIND_GAME;
	movs	r3, #0	@ tmp184,
@ src/levelcap/levelCapSave.c:70:     chunk.magic32 = SAVEMAGIC32;
	add	r0, sp, #12	@ tmp181,,
@ src/levelcap/levelCapSave.c:72:     WriteSaveBlockInfo(&chunk, slot);
	movs	r1, r5	@, slot
@ src/levelcap/levelCapSave.c:71:     chunk.kind = SAVEBLOCK_KIND_GAME;
	strb	r3, [r0, #6]	@ tmp184, chunk.kind
@ src/levelcap/levelCapSave.c:72:     WriteSaveBlockInfo(&chunk, slot);
	ldr	r3, .L12+104	@ tmp187,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:73:     WriteLastGameSaveId(slot);
	movs	r0, r5	@, slot
	ldr	r3, .L12+108	@ tmp188,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:74: }
	add	sp, sp, #164	@,,
	@ sp needed	@
	pop	{r4, r5, r6, r7}
	pop	{r0}
	bx	r0
.L13:
	.align	2
.L12:
	.word	GetSaveWriteAddr
	.word	InvalidateSuspendSave
	.word	gPlaySt
	.word	GetGameClock
	.word	WriteAndVerifySramFast
	.word	gUnitArrayBlue
	.word	WriteGameSavePackedUnit
	.word	ReadGlobalSaveInfo
	.word	SGM_SetCharacterKnown
	.word	WriteGlobalSaveInfo
	.word	WriteGMMonsterRnState
	.word	1948
	.word	WriteSupplyItems
	.word	2124
	.word	WritePidStats
	.word	3244
	.word	WriteChapterStats
	.word	3464
	.word	WriteBonusContentClaimFlags
	.word	3436
	.word	WritePermanentFlags
	.word	3468
	.word	gGMData
	.word	WriteWorldMapStuff
	.word	SaveDungeonRecords
	.word	263716
	.word	WriteSaveBlockInfo
	.word	WriteLastGameSaveId
	.size	WriteGameSave, .-WriteGameSave
	.align	1
	.global	ReadGameSave
	.syntax unified
	.code	16
	.thumb_func
	.type	ReadGameSave, %function
ReadGameSave:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}	@
@ src/levelcap/levelCapSave.c:80:     struct GameSaveBlock *src = GetSaveReadAddr(slot);
	ldr	r3, .L20	@ tmp138,
@ src/levelcap/levelCapSave.c:77: {
	sub	sp, sp, #44	@,,
@ src/levelcap/levelCapSave.c:77: {
	str	r0, [sp]	@ tmp181, %sfp
@ src/levelcap/levelCapSave.c:80:     struct GameSaveBlock *src = GetSaveReadAddr(slot);
	bl	.L14		@
@ src/levelcap/levelCapSave.c:82:     if (!(PLAY_FLAG_HARD & gBmSt.gameStateBits))
	ldr	r3, .L20+4	@ tmp139,
@ src/levelcap/levelCapSave.c:82:     if (!(PLAY_FLAG_HARD & gBmSt.gameStateBits))
	ldrb	r3, [r3, #4]	@ tmp141,
@ src/levelcap/levelCapSave.c:80:     struct GameSaveBlock *src = GetSaveReadAddr(slot);
	movs	r4, r0	@ src, tmp182
@ src/levelcap/levelCapSave.c:82:     if (!(PLAY_FLAG_HARD & gBmSt.gameStateBits))
	lsls	r3, r3, #25	@ tmp183, tmp141,
	bmi	.L16		@,
@ src/levelcap/levelCapSave.c:83:         InvalidateSuspendSave(SAVE_ID_SUSPEND);
	movs	r0, #3	@,
	ldr	r3, .L20+8	@ tmp147,
	bl	.L14		@
.L16:
@ src/levelcap/levelCapSave.c:85:     ReadSramFast(src, &gPlaySt, sizeof(gPlaySt));
	ldr	r5, .L20+12	@ tmp148,
	ldr	r7, .L20+16	@ tmp149,
	movs	r1, r5	@, tmp148
	movs	r2, #76	@,
	movs	r0, r4	@, src
	ldr	r3, [r7]	@ ReadSramFast, ReadSramFast
	bl	.L14		@
@ src/levelcap/levelCapSave.c:86:     SetGameTime(gPlaySt.time_saved);
	ldr	r0, [r5]	@, gPlaySt.time_saved
	ldr	r3, .L20+20	@ tmp152,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:87:     gPlaySt.gameSaveSlot = slot;
	ldr	r3, [sp]	@ slot, %sfp
	strb	r3, [r5, #12]	@ slot, gPlaySt.gameSaveSlot
@ src/levelcap/levelCapSave.c:89:     InitUnits();
	ldr	r3, .L20+24	@ tmp155,
	bl	.L14		@
	movs	r3, #239	@ tmp190,
	movs	r5, r4	@ ivtmp.43, src
	lsls	r3, r3, #3	@ tmp190, tmp190,
	adds	r3, r4, r3	@ _59, src, tmp190
	ldr	r6, .L20+28	@ ivtmp.45,
	str	r3, [sp, #4]	@ _59, %sfp
	adds	r5, r5, #76	@ ivtmp.43,
.L17:
@ src/levelcap/levelCapSave.c:92:         LoadSavedUnit(src->units + i, &gUnitArrayBlue[i]);
	movs	r1, r6	@, ivtmp.45
	movs	r0, r5	@, ivtmp.43
	ldr	r3, .L20+32	@ tmp156,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:91:     for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
	ldr	r3, [sp, #4]	@ _59, %sfp
	adds	r5, r5, #36	@ ivtmp.43,
	adds	r6, r6, #72	@ ivtmp.45,
	cmp	r5, r3	@ ivtmp.43, _59
	bne	.L17		@,
@ src/levelcap/levelCapSave.c:94:     ReadGMMonsterRnState(&src->gmUnit);
	movs	r0, r5	@, ivtmp.43
	ldr	r3, .L20+36	@ tmp158,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:95:     ReadSupplyItems(src->supplyItems);
	ldr	r3, .L20+40	@ tmp192,
	adds	r0, r4, r3	@ tmp159, src, tmp192
@ src/levelcap/levelCapSave.c:95:     ReadSupplyItems(src->supplyItems);
	ldr	r3, .L20+44	@ tmp160,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:96:     ReadPermanentFlags(src->permanentFlags);
	ldr	r3, .L20+48	@ tmp193,
	adds	r0, r4, r3	@ tmp161, src, tmp193
@ src/levelcap/levelCapSave.c:96:     ReadPermanentFlags(src->permanentFlags);
	ldr	r3, .L20+52	@ tmp162,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:97:     ReadPidStats(src->pidStats);
	ldr	r3, .L20+56	@ tmp194,
	adds	r0, r4, r3	@ tmp163, src, tmp194
@ src/levelcap/levelCapSave.c:97:     ReadPidStats(src->pidStats);
	ldr	r3, .L20+60	@ tmp164,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:98:     ReadChapterStats(src->chapterStats);
	ldr	r3, .L20+64	@ tmp195,
	adds	r0, r4, r3	@ tmp165, src, tmp195
@ src/levelcap/levelCapSave.c:98:     ReadChapterStats(src->chapterStats);
	ldr	r3, .L20+68	@ tmp166,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:99:     ReadBonusContentClaimFlags(src);
	movs	r0, r4	@, src
	ldr	r3, .L20+72	@ tmp167,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:100:     unpackProgCaps(src->bonusClaimFlags);
	ldr	r3, .L20+76	@ tmp168,
	ldr	r0, [r4, r3]	@, src_27->bonusClaimFlags
	bl	unpackProgCaps		@
@ src/levelcap/levelCapSave.c:101:     ReadWorldMapStuff(&src->wmStuff, &gGMData);
	ldr	r3, .L20+80	@ tmp196,
@ src/levelcap/levelCapSave.c:101:     ReadWorldMapStuff(&src->wmStuff, &gGMData);
	ldr	r1, .L20+84	@ tmp169,
@ src/levelcap/levelCapSave.c:101:     ReadWorldMapStuff(&src->wmStuff, &gGMData);
	adds	r0, r4, r3	@ tmp170, src, tmp196
@ src/levelcap/levelCapSave.c:101:     ReadWorldMapStuff(&src->wmStuff, &gGMData);
	ldr	r3, .L20+88	@ tmp171,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:102:     ReadSramFast(src->dungeons, dungeon, sizeof(dungeon));
	movs	r3, #219	@ tmp197,
	lsls	r3, r3, #4	@ tmp197, tmp197,
@ src/levelcap/levelCapSave.c:102:     ReadSramFast(src->dungeons, dungeon, sizeof(dungeon));
	movs	r2, #32	@,
@ src/levelcap/levelCapSave.c:102:     ReadSramFast(src->dungeons, dungeon, sizeof(dungeon));
	adds	r0, r4, r3	@ tmp173, src, tmp197
@ src/levelcap/levelCapSave.c:102:     ReadSramFast(src->dungeons, dungeon, sizeof(dungeon));
	add	r1, sp, #8	@,,
	ldr	r3, [r7]	@ ReadSramFast, ReadSramFast
	bl	.L14		@
@ src/levelcap/levelCapSave.c:103:     LoadDungeonRecords(dungeon);
	add	r0, sp, #8	@,,
	ldr	r3, .L20+92	@ tmp177,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:104:     WriteLastGameSaveId(slot);
	ldr	r0, [sp]	@, %sfp
	ldr	r3, .L20+96	@ tmp178,
	bl	.L14		@
@ src/levelcap/levelCapSave.c:105: }
	add	sp, sp, #44	@,,
	@ sp needed	@
	pop	{r4, r5, r6, r7}
	pop	{r0}
	bx	r0
.L21:
	.align	2
.L20:
	.word	GetSaveReadAddr
	.word	gBmSt
	.word	InvalidateSuspendSave
	.word	gPlaySt
	.word	.LANCHOR0
	.word	SetGameTime
	.word	InitUnits
	.word	gUnitArrayBlue
	.word	LoadSavedUnit
	.word	ReadGMMonsterRnState
	.word	1948
	.word	ReadSupplyItems
	.word	3436
	.word	ReadPermanentFlags
	.word	2124
	.word	ReadPidStats
	.word	3244
	.word	ReadChapterStats
	.word	ReadBonusContentClaimFlags
	.word	3464
	.word	3468
	.word	gGMData
	.word	ReadWorldMapStuff
	.word	LoadDungeonRecords
	.word	WriteLastGameSaveId
	.size	ReadGameSave, .-ReadGameSave
	.global	ReadSramFast
	.bss
	.align	2
	.set	.LANCHOR0,. + 0
	.type	ReadSramFast, %object
	.size	ReadSramFast, 4
ReadSramFast:
	.space	4
	.ident	"GCC: (devkitARM release 61) 13.1.0"
	.text
	.code 16
	.align	1
.L14:
	bx	r3
