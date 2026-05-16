sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/data
include $(dir)/Rules.mk

MAIN_$(d) := $(d)/main.event

MAIN_$(d): $(d)/data/ch1TalkSethFranz.dmp
MAIN_$(d): $(d)/data/ch1TalkEirikaFranz.dmp
MAIN_$(d): $(d)/data/ch2TalkEirikaRoss.dmp
MAIN_$(d): $(d)/data/ch2TalkRossGarcia.dmp
MAIN_$(d): $(d)/data/ch3TalkNeimiColm.dmp
MAIN_$(d): $(d)/data/ch5TalkNatashaJoshua.dmp
MAIN_$(d): $(d)/data/ch8TalkSethKyle.dmp
MAIN_$(d): $(d)/data/ch8TalkFranzForde.dmp
MAIN_$(d): $(d)/data/ch9aEirTalkEirikaAmelia.dmp
MAIN_$(d): $(d)/data/ch9aEirTalkFranzAmelia.dmp
MAIN_$(d): $(d)/data/ch10aEirTalkEirikaInnes.dmp
MAIN_$(d): $(d)/data/ch10aEirTalkTanaInnes.dmp
MAIN_$(d): $(d)/data/ch10aEirTalkInnesGerik.dmp
MAIN_$(d): $(d)/data/ch10aEirTalkTethysGerik.dmp
MAIN_$(d): $(d)/data/ch10aEirTalkInnesTethys.dmp
MAIN_$(d): $(d)/data/ch10aEirTalkGerikTethys.dmp
MAIN_$(d): $(d)/data/ch10aEirTalkGerikMarisa.dmp
MAIN_$(d): $(d)/data/ch11aEirTalkEirikaLArachel.dmp
MAIN_$(d): $(d)/data/ch11aEirTalkLArachelDozla.dmp
MAIN_$(d): $(d)/data/ch13aEirTalkEirikaAmelia.dmp
MAIN_$(d): $(d)/data/ch13aEirTalkFranzAmelia.dmp
MAIN_$(d): $(d)/data/ch13aEirTalkEirikaCormag.dmp
MAIN_$(d): $(d)/data/ch14aEirTalkLArachelRennac.dmp
MAIN_$(d): $(d)/data/ch14aEirTalkEirikaRennac.dmp
MAIN_$(d): $(d)/data/ch17aEirTalkInnesSyrene.dmp
MAIN_$(d): $(d)/data/ch17aEirTalkTanaSyrene.dmp
MAIN_$(d): $(d)/data/ch17aEirTalkVanessaSyrene.dmp
MAIN_$(d): $(d)/data/ch9bEphTalkEphAmelia.dmp
MAIN_$(d): $(d)/data/ch9bEphTalkFranzAmelia.dmp
MAIN_$(d): $(d)/data/ch9bEphTalkEphTana.dmp
MAIN_$(d): $(d)/data/ch10bEphTalkEphDuessel.dmp
MAIN_$(d): $(d)/data/ch10bEphTalkDuesselCormag.dmp
MAIN_$(d): $(d)/data/ch10bEphTalkTanaCormag.dmp
MAIN_$(d): $(d)/data/ch11bEphTalkEphLArachel.dmp
MAIN_$(d): $(d)/data/ch11bEphTalkLArachelDozla.dmp
MAIN_$(d): $(d)/data/ch12bEphTalkEwanMarisa.dmp
MAIN_$(d): $(d)/data/ch13bEphTalkEphGerik.dmp
MAIN_$(d): $(d)/data/ch13bEphTalkGerikMarisa.dmp
MAIN_$(d): $(d)/data/ch13bEphTalkTethysEwan.dmp
MAIN_$(d): $(d)/data/ch14bEphTalkLArachelRennac.dmp
MAIN_$(d): $(d)/data/ch14bEphTalkEphRennac.dmp
MAIN_$(d): $(d)/data/ch17bEphTalkInnesSyrene.dmp
MAIN_$(d): $(d)/data/ch17bEphTalkTanaSyrene.dmp
MAIN_$(d): $(d)/data/ch17bEphTalkVanessaSyrene.dmp
MAIN_$(d): $(d)/data/prologueBeginScene.dmp
MAIN_$(d): $(d)/data/ch2BeginScene.dmp
MAIN_$(d): $(d)/data/ch3BeginScene.dmp
MAIN_$(d): $(d)/data/ch4BeginScene.dmp
MAIN_$(d): $(d)/data/ch8BeginScene.dmp
MAIN_$(d): $(d)/data/ch11aBeginScene.dmp
MAIN_$(d): $(d)/data/ch12bBeginScene.dmp
MAIN_$(d): $(d)/data/ch14aBeginScene.dmp
MAIN_$(d): $(d)/data/ch15aBeginScene.dmp
MAIN_$(d): $(d)/data/ch16aBeginScene.dmp
MAIN_$(d): $(d)/data/ch16bBeginScene.dmp

EVENTS_$(d) := MAIN_$(d) \
	$(d)/markRecruits.lyn.event \
	$(d)/deployPermits.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/markRecruits.lyn.event $(d)/markRecruits.o \
	$(d)/deployPermits.lyn.event $(d)/deployPermits.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
