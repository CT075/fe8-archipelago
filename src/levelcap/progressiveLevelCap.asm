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
	.file	"progressiveLevelCap.c"
@ GNU C17 (devkitARM release 61) version 13.1.0 (arm-none-eabi)
@	compiled by GNU C version 8.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.18-GMP

@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
@ options passed: -mcpu=arm7tdmi -mthumb -mthumb-interwork -mtune=arm7tdmi -mlong-calls -march=armv4t -Os -ffreestanding
	.text
	.align	1
	.global	bumpLevelCap
	.syntax unified
	.code	16
	.thumb_func
	.type	bumpLevelCap, %function
bumpLevelCap:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
@ src/levelcap/progressiveLevelCap.c:16:     progCaps->lvlCapStage += 1;
	ldr	r2, .L5	@ tmp121,
	ldr	r3, [r2]	@ MEM[(struct ProgressiveCaps *)33812416B].lvlCapStage, MEM[(struct ProgressiveCaps *)33812416B].lvlCapStage
	adds	r3, r3, #1	@ tmp123,
	str	r3, [r2]	@ tmp123, MEM[(struct ProgressiveCaps *)33812416B].lvlCapStage
@ src/levelcap/progressiveLevelCap.c:18:     for (int i = 0 ; i < BLUE_UNIT_MAX ; i += 1) {
	movs	r2, #0	@ i,
@ src/levelcap/progressiveLevelCap.c:21:             unit->exp = 0;
	movs	r1, r2	@ tmp132, i
	ldr	r3, .L5+4	@ ivtmp.15,
.L3:
@ src/levelcap/progressiveLevelCap.c:20:         if (unit->exp == UNIT_EXP_DISABLED && unit->level < TRUE_LEVEL_CAP) {
	ldrb	r0, [r3, #9]	@ MEM <u8> [(struct Unit *)_19 + 9B], MEM <u8> [(struct Unit *)_19 + 9B]
	cmp	r0, #255	@ MEM <u8> [(struct Unit *)_19 + 9B],
	bne	.L2		@,
@ src/levelcap/progressiveLevelCap.c:20:         if (unit->exp == UNIT_EXP_DISABLED && unit->level < TRUE_LEVEL_CAP) {
	movs	r0, #8	@ MEM <s8> [(struct Unit *)_19 + 8B],
	ldrsb	r0, [r3, r0]	@ MEM <s8> [(struct Unit *)_19 + 8B],* MEM <s8> [(struct Unit *)_19 + 8B]
	cmp	r0, #19	@ MEM <s8> [(struct Unit *)_19 + 8B],
	bgt	.L2		@,
@ src/levelcap/progressiveLevelCap.c:21:             unit->exp = 0;
	strb	r1, [r3, #9]	@ tmp132, MEM <u8> [(struct Unit *)_19 + 9B]
.L2:
@ src/levelcap/progressiveLevelCap.c:18:     for (int i = 0 ; i < BLUE_UNIT_MAX ; i += 1) {
	adds	r2, r2, #1	@ i,
@ src/levelcap/progressiveLevelCap.c:18:     for (int i = 0 ; i < BLUE_UNIT_MAX ; i += 1) {
	adds	r3, r3, #72	@ ivtmp.15,
	cmp	r2, #62	@ i,
	bne	.L3		@,
@ src/levelcap/progressiveLevelCap.c:24: }
	@ sp needed	@
	bx	lr
.L6:
	.align	2
.L5:
	.word	33812416
	.word	gUnitArrayBlue
	.size	bumpLevelCap, .-bumpLevelCap
	.align	1
	.global	CanBattleUnitGainLevels
	.syntax unified
	.code	16
	.thumb_func
	.type	CanBattleUnitGainLevels, %function
CanBattleUnitGainLevels:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}	@
@ src/levelcap/progressiveLevelCap.c:27:     if (gBmSt.gameStateBits & 0x40)
	ldr	r3, .L16	@ tmp127,
@ src/levelcap/progressiveLevelCap.c:27:     if (gBmSt.gameStateBits & 0x40)
	ldrb	r3, [r3, #4]	@ tmp129,
@ src/levelcap/progressiveLevelCap.c:26: s8 CanBattleUnitGainLevels(struct BattleUnit *bu) {
	movs	r4, r0	@ bu, tmp149
@ src/levelcap/progressiveLevelCap.c:28:         return TRUE;
	movs	r0, #1	@ <retval>,
@ src/levelcap/progressiveLevelCap.c:27:     if (gBmSt.gameStateBits & 0x40)
	lsls	r3, r3, #25	@ tmp152, tmp129,
	bmi	.L8		@,
@ src/levelcap/progressiveLevelCap.c:30:     if (bu->unit.level >= TRUE_LEVEL_CAP)
	movs	r3, #8	@ tmp137,
	ldrsb	r3, [r4, r3]	@ tmp137,
	cmp	r3, #19	@ tmp137,
	ble	.L9		@,
.L10:
@ src/levelcap/progressiveLevelCap.c:31:         return FALSE;
	movs	r0, #0	@ <retval>,
.L8:
@ src/levelcap/progressiveLevelCap.c:43: }
	@ sp needed	@
	pop	{r4, r5, r6}
	pop	{r1}
	bx	r1
.L9:
@ src/levelcap/progressiveLevelCap.c:33:     if (GetUnitExpLevel(&bu->unit) >= GetLevelCap())
	ldr	r3, .L16+4	@ tmp138,
	movs	r0, r4	@, bu
	bl	.L18		@
@ src/levelcap/progressiveLevelCap.c:33:     if (GetUnitExpLevel(&bu->unit) >= GetLevelCap())
	ldr	r3, .L16+8	@ tmp139,
@ src/levelcap/progressiveLevelCap.c:33:     if (GetUnitExpLevel(&bu->unit) >= GetLevelCap())
	movs	r5, r0	@ _6, tmp150
@ src/levelcap/progressiveLevelCap.c:33:     if (GetUnitExpLevel(&bu->unit) >= GetLevelCap())
	bl	.L18		@
@ src/levelcap/progressiveLevelCap.c:33:     if (GetUnitExpLevel(&bu->unit) >= GetLevelCap())
	cmp	r5, r0	@ _6, tmp151
	bge	.L10		@,
@ src/levelcap/progressiveLevelCap.c:36:     if (bu->unit.exp == UNIT_EXP_DISABLED)
	ldrb	r3, [r4, #9]	@ tmp140,
	cmp	r3, #255	@ tmp140,
	beq	.L10		@,
@ src/levelcap/progressiveLevelCap.c:39:     if (UNIT_FACTION(&bu->unit) != FACTION_BLUE)
	movs	r0, #11	@ tmp141,
	movs	r3, #192	@ tmp143,
	ldrsb	r0, [r4, r0]	@ tmp141,
	ands	r0, r3	@ tmp142, tmp143
@ src/levelcap/progressiveLevelCap.c:39:     if (UNIT_FACTION(&bu->unit) != FACTION_BLUE)
	rsbs	r3, r0, #0	@ tmp146, tmp142
	adcs	r0, r0, r3	@ <retval>, tmp142, tmp146
	b	.L8		@
.L17:
	.align	2
.L16:
	.word	gBmSt
	.word	GetUnitExpLevel
	.word	GetLevelCap
	.size	CanBattleUnitGainLevels, .-CanBattleUnitGainLevels
	.align	1
	.global	EnforceLevelCap
	.syntax unified
	.code	16
	.thumb_func
	.type	EnforceLevelCap, %function
EnforceLevelCap:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
@ src/levelcap/progressiveLevelCap.c:46:     if (UNIT_CATTRIBUTES(&bu->unit) & CA_MAXLEVEL10) {
	ldr	r3, [r0]	@ bu_14(D)->unit.pCharacterData, bu_14(D)->unit.pCharacterData
	ldr	r2, [r0, #4]	@ bu_14(D)->unit.pClassData, bu_14(D)->unit.pClassData
	ldr	r3, [r3, #40]	@ _1->attributes, _1->attributes
	ldr	r2, [r2, #40]	@ _3->attributes, _3->attributes
	orrs	r3, r2	@ tmp137, _3->attributes
@ src/levelcap/progressiveLevelCap.c:45: void EnforceLevelCap(struct BattleUnit *bu) {
	push	{r4, r5, r6, lr}	@
@ src/levelcap/progressiveLevelCap.c:45: void EnforceLevelCap(struct BattleUnit *bu) {
	movs	r4, r0	@ bu, tmp173
@ src/levelcap/progressiveLevelCap.c:46:     if (UNIT_CATTRIBUTES(&bu->unit) & CA_MAXLEVEL10) {
	lsls	r3, r3, #12	@ tmp176, tmp137,
	bpl	.L20		@,
@ src/levelcap/progressiveLevelCap.c:47:         if (bu->unit.level == 10) {
	movs	r3, #8	@ tmp142,
	ldrsb	r3, [r0, r3]	@ tmp142,
	cmp	r3, #10	@ tmp142,
	bne	.L19		@,
.L24:
@ src/levelcap/progressiveLevelCap.c:52:         bu->expGain -= bu->unit.exp;
	movs	r2, r4	@ tmp161, bu
	adds	r2, r2, #110	@ tmp161,
@ src/levelcap/progressiveLevelCap.c:52:         bu->expGain -= bu->unit.exp;
	ldrb	r3, [r2]	@ tmp163,
	ldrb	r1, [r4, #9]	@ tmp165,
	subs	r3, r3, r1	@ tmp166, tmp163, tmp165
	strb	r3, [r2]	@ tmp166, bu_14(D)->expGain
@ src/levelcap/progressiveLevelCap.c:53:         bu->unit.exp = UNIT_EXP_DISABLED;
	movs	r3, #255	@ tmp171,
	strb	r3, [r4, #9]	@ tmp171, bu_14(D)->unit.exp
@ src/levelcap/progressiveLevelCap.c:55: }
	b	.L19		@
.L20:
@ src/levelcap/progressiveLevelCap.c:51:     } else if (GetUnitExpLevel(&bu->unit) >= GetLevelCap()) {
	ldr	r3, .L25	@ tmp157,
	bl	.L18		@
@ src/levelcap/progressiveLevelCap.c:51:     } else if (GetUnitExpLevel(&bu->unit) >= GetLevelCap()) {
	ldr	r3, .L25+4	@ tmp158,
@ src/levelcap/progressiveLevelCap.c:51:     } else if (GetUnitExpLevel(&bu->unit) >= GetLevelCap()) {
	movs	r5, r0	@ _20, tmp174
@ src/levelcap/progressiveLevelCap.c:51:     } else if (GetUnitExpLevel(&bu->unit) >= GetLevelCap()) {
	bl	.L18		@
@ src/levelcap/progressiveLevelCap.c:51:     } else if (GetUnitExpLevel(&bu->unit) >= GetLevelCap()) {
	cmp	r5, r0	@ _20, tmp175
	bge	.L24		@,
.L19:
@ src/levelcap/progressiveLevelCap.c:55: }
	@ sp needed	@
	pop	{r4, r5, r6}
	pop	{r0}
	bx	r0
.L26:
	.align	2
.L25:
	.word	GetUnitExpLevel
	.word	GetLevelCap
	.size	EnforceLevelCap, .-EnforceLevelCap
	.align	1
	.global	CheckBattleUnitLevelUp
	.syntax unified
	.code	16
	.thumb_func
	.type	CheckBattleUnitLevelUp, %function
CheckBattleUnitLevelUp:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}	@
	sub	sp, sp, #20	@,,
@ src/levelcap/progressiveLevelCap.c:57: void CheckBattleUnitLevelUp(struct BattleUnit *bu) {
	movs	r4, r0	@ bu, tmp375
@ src/levelcap/progressiveLevelCap.c:58:     if (CanBattleUnitGainLevels(bu) && bu->unit.exp >= 100) {
	bl	CanBattleUnitGainLevels		@
@ src/levelcap/progressiveLevelCap.c:58:     if (CanBattleUnitGainLevels(bu) && bu->unit.exp >= 100) {
	cmp	r0, #0	@ tmp376,
	beq	.L27		@,
@ src/levelcap/progressiveLevelCap.c:58:     if (CanBattleUnitGainLevels(bu) && bu->unit.exp >= 100) {
	ldrb	r3, [r4, #9]	@ _2,
@ src/levelcap/progressiveLevelCap.c:58:     if (CanBattleUnitGainLevels(bu) && bu->unit.exp >= 100) {
	cmp	r3, #99	@ _2,
	bls	.L27		@,
@ src/levelcap/progressiveLevelCap.c:61:         bu->unit.exp -= 100;
	subs	r3, r3, #100	@ tmp224,
	strb	r3, [r4, #9]	@ tmp224, bu_103(D)->unit.exp
@ src/levelcap/progressiveLevelCap.c:62:         bu->unit.level++;
	ldrb	r3, [r4, #8]	@ tmp227,
	adds	r3, r3, #1	@ tmp228,
	strb	r3, [r4, #8]	@ tmp228, bu_103(D)->unit.level
@ src/levelcap/progressiveLevelCap.c:64:         EnforceLevelCap(bu);
	movs	r0, r4	@, bu
	bl	EnforceLevelCap		@
@ src/levelcap/progressiveLevelCap.c:66:         growthBonus = (bu->unit.state & US_GROWTH_BOOST) ? 5: 0;
	ldr	r3, [r4, #12]	@ bu_103(D)->unit.state, bu_103(D)->unit.state
@ src/levelcap/progressiveLevelCap.c:66:         growthBonus = (bu->unit.state & US_GROWTH_BOOST) ? 5: 0;
	movs	r6, #0	@ iftmp.0_98,
@ src/levelcap/progressiveLevelCap.c:66:         growthBonus = (bu->unit.state & US_GROWTH_BOOST) ? 5: 0;
	lsls	r3, r3, #18	@ tmp392, bu_103(D)->unit.state,
	bpl	.L29		@,
@ src/levelcap/progressiveLevelCap.c:66:         growthBonus = (bu->unit.state & US_GROWTH_BOOST) ? 5: 0;
	adds	r6, r6, #5	@ iftmp.0_98,
.L29:
@ src/levelcap/progressiveLevelCap.c:69:         bu->changeHP  = GetStatIncrease(bu->unit.pCharacterData->growthHP + growthBonus);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	ldrb	r0, [r3, #28]	@ tmp234,
@ src/levelcap/progressiveLevelCap.c:69:         bu->changeHP  = GetStatIncrease(bu->unit.pCharacterData->growthHP + growthBonus);
	ldr	r5, .L39	@ tmp236,
	adds	r0, r0, r6	@ tmp235, tmp234, iftmp.0_98
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:69:         bu->changeHP  = GetStatIncrease(bu->unit.pCharacterData->growthHP + growthBonus);
	movs	r3, r4	@ tmp240, bu
	lsls	r7, r0, #24	@ tmp237, tmp377,
	asrs	r7, r7, #24	@ _15, tmp237,
	adds	r3, r3, #115	@ tmp240,
	strb	r7, [r3]	@ _15, bu_103(D)->changeHP
	str	r3, [sp, #4]	@ tmp240, %sfp
@ src/levelcap/progressiveLevelCap.c:72:         bu->changePow = GetStatIncrease(bu->unit.pCharacterData->growthPow + growthBonus);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	ldrb	r0, [r3, #29]	@ tmp243,
@ src/levelcap/progressiveLevelCap.c:72:         bu->changePow = GetStatIncrease(bu->unit.pCharacterData->growthPow + growthBonus);
	adds	r0, r0, r6	@ tmp244, tmp243, iftmp.0_98
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:72:         bu->changePow = GetStatIncrease(bu->unit.pCharacterData->growthPow + growthBonus);
	movs	r3, r4	@ tmp249, bu
	lsls	r0, r0, #24	@ tmp246, tmp378,
	asrs	r0, r0, #24	@ _22, tmp246,
	adds	r3, r3, #116	@ tmp249,
	strb	r0, [r3]	@ _22, bu_103(D)->changePow
	str	r3, [sp, #8]	@ tmp249, %sfp
@ src/levelcap/progressiveLevelCap.c:73:         statGainTotal += bu->changePow;
	adds	r3, r7, r0	@ statGainTotal, _15, _22
	str	r3, [sp, #12]	@ statGainTotal, %sfp
@ src/levelcap/progressiveLevelCap.c:75:         bu->changeSkl = GetStatIncrease(bu->unit.pCharacterData->growthSkl + growthBonus);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	ldrb	r0, [r3, #30]	@ tmp252,
@ src/levelcap/progressiveLevelCap.c:75:         bu->changeSkl = GetStatIncrease(bu->unit.pCharacterData->growthSkl + growthBonus);
	adds	r0, r0, r6	@ tmp253, tmp252, iftmp.0_98
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:75:         bu->changeSkl = GetStatIncrease(bu->unit.pCharacterData->growthSkl + growthBonus);
	movs	r7, r4	@ tmp258, bu
	lsls	r0, r0, #24	@ tmp255, tmp379,
@ src/levelcap/progressiveLevelCap.c:76:         statGainTotal += bu->changeSkl;
	ldr	r3, [sp, #12]	@ statGainTotal, %sfp
@ src/levelcap/progressiveLevelCap.c:75:         bu->changeSkl = GetStatIncrease(bu->unit.pCharacterData->growthSkl + growthBonus);
	asrs	r0, r0, #24	@ _29, tmp255,
	adds	r7, r7, #117	@ tmp258,
	strb	r0, [r7]	@ _29, bu_103(D)->changeSkl
@ src/levelcap/progressiveLevelCap.c:76:         statGainTotal += bu->changeSkl;
	adds	r3, r0, r3	@ statGainTotal, _29, statGainTotal
	str	r3, [sp, #12]	@ statGainTotal, %sfp
@ src/levelcap/progressiveLevelCap.c:78:         bu->changeSpd = GetStatIncrease(bu->unit.pCharacterData->growthSpd + growthBonus);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	ldrb	r0, [r3, #31]	@ tmp261,
@ src/levelcap/progressiveLevelCap.c:78:         bu->changeSpd = GetStatIncrease(bu->unit.pCharacterData->growthSpd + growthBonus);
	adds	r0, r0, r6	@ tmp262, tmp261, iftmp.0_98
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:78:         bu->changeSpd = GetStatIncrease(bu->unit.pCharacterData->growthSpd + growthBonus);
	movs	r3, r4	@ tmp267, bu
	lsls	r0, r0, #24	@ tmp264, tmp380,
	asrs	r0, r0, #24	@ _36, tmp264,
	adds	r3, r3, #118	@ tmp267,
	strb	r0, [r3]	@ _36, bu_103(D)->changeSpd
@ src/levelcap/progressiveLevelCap.c:79:         statGainTotal += bu->changeSpd;
	ldr	r3, [sp, #12]	@ statGainTotal, %sfp
	adds	r3, r0, r3	@ statGainTotal, _36, statGainTotal
	str	r3, [sp, #12]	@ statGainTotal, %sfp
@ src/levelcap/progressiveLevelCap.c:81:         bu->changeDef = GetStatIncrease(bu->unit.pCharacterData->growthDef + growthBonus);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	adds	r3, r3, #1	@ tmp270,
	ldrb	r0, [r3, #31]	@ tmp271,
@ src/levelcap/progressiveLevelCap.c:81:         bu->changeDef = GetStatIncrease(bu->unit.pCharacterData->growthDef + growthBonus);
	adds	r0, r0, r6	@ tmp272, tmp271, iftmp.0_98
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:81:         bu->changeDef = GetStatIncrease(bu->unit.pCharacterData->growthDef + growthBonus);
	movs	r3, r4	@ tmp277, bu
	lsls	r0, r0, #24	@ tmp274, tmp381,
	asrs	r0, r0, #24	@ _43, tmp274,
	adds	r3, r3, #119	@ tmp277,
	strb	r0, [r3]	@ _43, bu_103(D)->changeDef
@ src/levelcap/progressiveLevelCap.c:82:         statGainTotal += bu->changeDef;
	ldr	r3, [sp, #12]	@ statGainTotal, %sfp
	adds	r3, r0, r3	@ statGainTotal, _43, statGainTotal
	str	r3, [sp, #12]	@ statGainTotal, %sfp
@ src/levelcap/progressiveLevelCap.c:84:         bu->changeRes = GetStatIncrease(bu->unit.pCharacterData->growthRes + growthBonus);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	adds	r3, r3, #2	@ tmp280,
	ldrb	r0, [r3, #31]	@ tmp281,
@ src/levelcap/progressiveLevelCap.c:84:         bu->changeRes = GetStatIncrease(bu->unit.pCharacterData->growthRes + growthBonus);
	adds	r0, r0, r6	@ tmp282, tmp281, iftmp.0_98
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:84:         bu->changeRes = GetStatIncrease(bu->unit.pCharacterData->growthRes + growthBonus);
	movs	r3, r4	@ tmp287, bu
	lsls	r0, r0, #24	@ tmp284, tmp382,
	asrs	r0, r0, #24	@ _50, tmp284,
	adds	r3, r3, #120	@ tmp287,
	strb	r0, [r3]	@ _50, bu_103(D)->changeRes
@ src/levelcap/progressiveLevelCap.c:85:         statGainTotal += bu->changeRes;
	ldr	r3, [sp, #12]	@ statGainTotal, %sfp
	adds	r3, r0, r3	@ statGainTotal, _50, statGainTotal
	str	r3, [sp, #12]	@ statGainTotal, %sfp
@ src/levelcap/progressiveLevelCap.c:87:         bu->changeLck = GetStatIncrease(bu->unit.pCharacterData->growthLck + growthBonus);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	adds	r3, r3, #3	@ tmp290,
	ldrb	r0, [r3, #31]	@ tmp291,
@ src/levelcap/progressiveLevelCap.c:87:         bu->changeLck = GetStatIncrease(bu->unit.pCharacterData->growthLck + growthBonus);
	adds	r0, r0, r6	@ tmp292, tmp291, iftmp.0_98
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:87:         bu->changeLck = GetStatIncrease(bu->unit.pCharacterData->growthLck + growthBonus);
	movs	r3, r4	@ tmp297, bu
	lsls	r0, r0, #24	@ tmp294, tmp383,
	asrs	r0, r0, #24	@ _57, tmp294,
	adds	r3, r3, #121	@ tmp297,
	strb	r0, [r3]	@ _57, bu_103(D)->changeLck
@ src/levelcap/progressiveLevelCap.c:88:         statGainTotal += bu->changeLck;
	ldr	r3, [sp, #12]	@ statGainTotal, %sfp
	adds	r0, r0, r3	@ statGainTotal, _57, statGainTotal
	movs	r6, #2	@ ivtmp_100,
@ src/levelcap/progressiveLevelCap.c:90:         if (statGainTotal == 0) {
	cmp	r0, #0	@ statGainTotal,
	beq	.L31		@,
.L30:
@ src/levelcap/progressiveLevelCap.c:129:         CheckBattleUnitStatCaps(GetUnit(bu->unit.index), bu);
	movs	r0, #11	@ tmp359,
	ldr	r3, .L39+4	@ tmp360,
	ldrsb	r0, [r4, r0]	@ tmp359,
	bl	.L18		@
@ src/levelcap/progressiveLevelCap.c:129:         CheckBattleUnitStatCaps(GetUnit(bu->unit.index), bu);
	movs	r1, r4	@, bu
	ldr	r3, .L39+8	@ tmp361,
	bl	.L18		@
.L27:
@ src/levelcap/progressiveLevelCap.c:131: }
	add	sp, sp, #20	@,,
	@ sp needed	@
	pop	{r4, r5, r6, r7}
	pop	{r0}
	bx	r0
.L33:
	movs	r6, #1	@ ivtmp_100,
.L31:
@ src/levelcap/progressiveLevelCap.c:92:                 bu->changeHP = GetStatIncrease(bu->unit.pCharacterData->growthHP);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
@ src/levelcap/progressiveLevelCap.c:92:                 bu->changeHP = GetStatIncrease(bu->unit.pCharacterData->growthHP);
	ldrb	r0, [r3, #28]	@ tmp301,
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:92:                 bu->changeHP = GetStatIncrease(bu->unit.pCharacterData->growthHP);
	ldr	r3, [sp, #4]	@ tmp240, %sfp
	lsls	r0, r0, #24	@ tmp303, tmp384,
	asrs	r0, r0, #24	@ _63, tmp303,
	strb	r0, [r3]	@ _63, bu_103(D)->changeHP
@ src/levelcap/progressiveLevelCap.c:94:                 if (bu->changeHP)
	bne	.L30		@,
@ src/levelcap/progressiveLevelCap.c:97:                 bu->changePow = GetStatIncrease(bu->unit.pCharacterData->growthPow);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
@ src/levelcap/progressiveLevelCap.c:97:                 bu->changePow = GetStatIncrease(bu->unit.pCharacterData->growthPow);
	ldrb	r0, [r3, #29]	@ tmp309,
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:97:                 bu->changePow = GetStatIncrease(bu->unit.pCharacterData->growthPow);
	ldr	r3, [sp, #8]	@ tmp249, %sfp
	lsls	r0, r0, #24	@ tmp311, tmp385,
	asrs	r0, r0, #24	@ _68, tmp311,
	strb	r0, [r3]	@ _68, bu_103(D)->changePow
@ src/levelcap/progressiveLevelCap.c:99:                 if (bu->changePow)
	bne	.L30		@,
@ src/levelcap/progressiveLevelCap.c:102:                 bu->changeSkl = GetStatIncrease(bu->unit.pCharacterData->growthSkl);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
@ src/levelcap/progressiveLevelCap.c:102:                 bu->changeSkl = GetStatIncrease(bu->unit.pCharacterData->growthSkl);
	ldrb	r0, [r3, #30]	@ tmp317,
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:102:                 bu->changeSkl = GetStatIncrease(bu->unit.pCharacterData->growthSkl);
	lsls	r0, r0, #24	@ tmp319, tmp386,
	asrs	r0, r0, #24	@ _73, tmp319,
	strb	r0, [r7]	@ _73, bu_103(D)->changeSkl
@ src/levelcap/progressiveLevelCap.c:104:                 if (bu->changeSkl)
	bne	.L30		@,
@ src/levelcap/progressiveLevelCap.c:107:                 bu->changeSpd = GetStatIncrease(bu->unit.pCharacterData->growthSpd);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
@ src/levelcap/progressiveLevelCap.c:107:                 bu->changeSpd = GetStatIncrease(bu->unit.pCharacterData->growthSpd);
	ldrb	r0, [r3, #31]	@ tmp325,
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:107:                 bu->changeSpd = GetStatIncrease(bu->unit.pCharacterData->growthSpd);
	movs	r3, r4	@ tmp330, bu
	lsls	r0, r0, #24	@ tmp327, tmp387,
	asrs	r0, r0, #24	@ _78, tmp327,
	adds	r3, r3, #118	@ tmp330,
	strb	r0, [r3]	@ _78, bu_103(D)->changeSpd
@ src/levelcap/progressiveLevelCap.c:109:                 if (bu->changeSpd)
	cmp	r0, #0	@ _78,
	bne	.L30		@,
@ src/levelcap/progressiveLevelCap.c:112:                 bu->changeDef = GetStatIncrease(bu->unit.pCharacterData->growthDef);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	adds	r3, r3, #1	@ tmp333,
@ src/levelcap/progressiveLevelCap.c:112:                 bu->changeDef = GetStatIncrease(bu->unit.pCharacterData->growthDef);
	ldrb	r0, [r3, #31]	@ tmp334,
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:112:                 bu->changeDef = GetStatIncrease(bu->unit.pCharacterData->growthDef);
	movs	r3, r4	@ tmp339, bu
	lsls	r0, r0, #24	@ tmp336, tmp388,
	asrs	r0, r0, #24	@ _83, tmp336,
	adds	r3, r3, #119	@ tmp339,
	strb	r0, [r3]	@ _83, bu_103(D)->changeDef
@ src/levelcap/progressiveLevelCap.c:114:                 if (bu->changeDef)
	cmp	r0, #0	@ _83,
	bne	.L30		@,
@ src/levelcap/progressiveLevelCap.c:117:                 bu->changeRes = GetStatIncrease(bu->unit.pCharacterData->growthRes);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	adds	r3, r3, #2	@ tmp342,
@ src/levelcap/progressiveLevelCap.c:117:                 bu->changeRes = GetStatIncrease(bu->unit.pCharacterData->growthRes);
	ldrb	r0, [r3, #31]	@ tmp343,
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:117:                 bu->changeRes = GetStatIncrease(bu->unit.pCharacterData->growthRes);
	movs	r3, r4	@ tmp348, bu
	lsls	r0, r0, #24	@ tmp345, tmp389,
	asrs	r0, r0, #24	@ _88, tmp345,
	adds	r3, r3, #120	@ tmp348,
	strb	r0, [r3]	@ _88, bu_103(D)->changeRes
@ src/levelcap/progressiveLevelCap.c:119:                 if (bu->changeRes)
	cmp	r0, #0	@ _88,
	bne	.L30		@,
@ src/levelcap/progressiveLevelCap.c:122:                 bu->changeLck = GetStatIncrease(bu->unit.pCharacterData->growthLck);
	ldr	r3, [r4]	@ bu_103(D)->unit.pCharacterData, bu_103(D)->unit.pCharacterData
	adds	r3, r3, #3	@ tmp351,
@ src/levelcap/progressiveLevelCap.c:122:                 bu->changeLck = GetStatIncrease(bu->unit.pCharacterData->growthLck);
	ldrb	r0, [r3, #31]	@ tmp352,
	bl	.L41		@
@ src/levelcap/progressiveLevelCap.c:122:                 bu->changeLck = GetStatIncrease(bu->unit.pCharacterData->growthLck);
	movs	r3, r4	@ tmp357, bu
	lsls	r0, r0, #24	@ tmp354, tmp390,
	asrs	r0, r0, #24	@ _93, tmp354,
	adds	r3, r3, #121	@ tmp357,
	strb	r0, [r3]	@ _93, bu_103(D)->changeLck
@ src/levelcap/progressiveLevelCap.c:124:                 if (bu->changeLck)
	cmp	r0, #0	@ _93,
	bne	.L30		@,
@ src/levelcap/progressiveLevelCap.c:91:             for (statGainTotal = 0; statGainTotal < 2; ++statGainTotal) {
	cmp	r6, #1	@ ivtmp_100,
	bne	.L33		@,
	b	.L30		@
.L40:
	.align	2
.L39:
	.word	GetStatIncrease
	.word	GetUnit
	.word	CheckBattleUnitStatCaps
	.size	CheckBattleUnitLevelUp, .-CheckBattleUnitLevelUp
	.ident	"GCC: (devkitARM release 61) 13.1.0"
	.code 16
	.align	1
.L18:
	bx	r3
.L41:
	bx	r5
