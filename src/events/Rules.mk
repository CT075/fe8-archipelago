sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/data
include $(dir)/Rules.mk

MAIN_$(d) := $(d)/main.event

MAIN_$(d): data/ch10eirEndScene.dmp
MAIN_$(d): data/ch10ephEndScene.dmp
MAIN_$(d): data/ch11eirEndScene.dmp
MAIN_$(d): data/ch11ephEndScene.dmp
MAIN_$(d): data/ch12eirEndScene.dmp
MAIN_$(d): data/ch12ephEndScene.dmp
MAIN_$(d): data/ch13eirEndScene.dmp
MAIN_$(d): data/ch13ephEndScene.dmp
MAIN_$(d): data/ch14eirEndScene.dmp
MAIN_$(d): data/ch14ephEndScene.dmp
MAIN_$(d): data/ch15eirEndScene.dmp
MAIN_$(d): data/ch15ephEndScene.dmp
MAIN_$(d): data/ch16eirEndScene.dmp
MAIN_$(d): data/ch16ephEndScene.dmp
MAIN_$(d): data/ch17eirEndScene.dmp
MAIN_$(d): data/ch17ephEndScene.dmp
MAIN_$(d): data/ch18eirEndScene.dmp
MAIN_$(d): data/ch18ephEndScene.dmp
MAIN_$(d): data/ch19eirEndScene.dmp
MAIN_$(d): data/ch19ephEndScene.dmp
MAIN_$(d): data/ch1EndScene.dmp
MAIN_$(d): data/ch20eirEndScene.dmp
MAIN_$(d): data/ch20ephEndScene.dmp
MAIN_$(d): data/ch2EndScene.dmp
MAIN_$(d): data/ch3EndScene.dmp
MAIN_$(d): data/ch4EndScene.dmp
MAIN_$(d): data/ch5EndScene.dmp
MAIN_$(d): data/ch5xEndScene.dmp
MAIN_$(d): data/ch6EndScene.dmp
MAIN_$(d): data/ch7EndScene.dmp
MAIN_$(d): data/ch8EndScene.dmp
MAIN_$(d): data/ch9eirEndScene.dmp
MAIN_$(d): data/ch9ephEndScene.dmp
MAIN_$(d): data/final1eirEndScene.dmp
MAIN_$(d): data/final1ephEndScene.dmp
MAIN_$(d): data/final2eirEndScene.dmp
MAIN_$(d): data/final2ephEndScene.dmp
MAIN_$(d): data/prologueEndScene.dmp

EVENTS_$(d) := MAIN_$(d)

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
