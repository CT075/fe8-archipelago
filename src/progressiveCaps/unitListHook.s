ldr r4, =getPlayerUnitWeaponRank
mov lr, r4
.short 0xf800 @ bl lr
ldr r4, =GetWeaponLevelFromExp
mov lr, r4
.short 0xf800 @ bl lr
ldr r4, =UnitListHookRet+1
bx r4
