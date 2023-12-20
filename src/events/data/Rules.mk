sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

$(d)/ch10eirEndScene.dmp \
$(d)/ch10ephEndScene.dmp \
$(d)/ch11eirEndScene.dmp \
$(d)/ch11ephEndScene.dmp \
$(d)/ch12eirEndScene.dmp \
$(d)/ch12ephEndScene.dmp \
$(d)/ch13eirEndScene.dmp \
$(d)/ch13ephEndScene.dmp \
$(d)/ch14eirEndScene.dmp \
$(d)/ch14ephEndScene.dmp \
$(d)/ch15eirEndScene.dmp \
$(d)/ch15ephEndScene.dmp \
$(d)/ch16eirEndScene.dmp \
$(d)/ch16ephEndScene.dmp \
$(d)/ch17eirEndScene.dmp \
$(d)/ch17ephEndScene.dmp \
$(d)/ch18eirEndScene.dmp \
$(d)/ch18ephEndScene.dmp \
$(d)/ch19eirEndScene.dmp \
$(d)/ch19ephEndScene.dmp \
$(d)/ch1EndScene.dmp \
$(d)/ch20eirEndScene.dmp \
$(d)/ch20ephEndScene.dmp \
$(d)/ch2EndScene.dmp \
$(d)/ch3EndScene.dmp \
$(d)/ch4EndScene.dmp \
$(d)/ch5EndScene.dmp \
$(d)/ch5xEndScene.dmp \
$(d)/ch6EndScene.dmp \
$(d)/ch7EndScene.dmp \
$(d)/ch8EndScene.dmp \
$(d)/ch9eirEndScene.dmp \
$(d)/ch9ephEndScene.dmp \
$(d)/final1eirEndScene.dmp \
$(d)/final1ephEndScene.dmp \
$(d)/final2eirEndScene.dmp \
$(d)/final2ephEndScene.dmp \
$(d)/prologueEndScene.dmp \
$(d)/tower1EndScene.dmp \
$(d)/tower2EndScene.dmp \
$(d)/tower3EndScene.dmp \
$(d)/tower4EndScene.dmp \
$(d)/tower5EndScene.dmp \
$(d)/tower6EndScene.dmp \
$(d)/tower7EndScene.dmp \
$(d)/tower8EndScene.dmp \
$(d)/ruins1EndScene.dmp \
$(d)/ruins2EndScene.dmp \
$(d)/ruins3EndScene.dmp \
$(d)/ruins4EndScene.dmp \
$(d)/ruins5EndScene.dmp \
$(d)/ruins6EndScene.dmp \
$(d)/ruins7EndScene.dmp \
$(d)/ruins8EndScene.dmp \
$(d)/ruins9EndScene.dmp \
$(d)/ruins10EndScene.dmp : HERE := $(d)

$(d)/ch10eirEndScene.dmp \
$(d)/ch10ephEndScene.dmp \
$(d)/ch11eirEndScene.dmp \
$(d)/ch11ephEndScene.dmp \
$(d)/ch12eirEndScene.dmp \
$(d)/ch12ephEndScene.dmp \
$(d)/ch13eirEndScene.dmp \
$(d)/ch13ephEndScene.dmp \
$(d)/ch14eirEndScene.dmp \
$(d)/ch14ephEndScene.dmp \
$(d)/ch15eirEndScene.dmp \
$(d)/ch15ephEndScene.dmp \
$(d)/ch16eirEndScene.dmp \
$(d)/ch16ephEndScene.dmp \
$(d)/ch17eirEndScene.dmp \
$(d)/ch17ephEndScene.dmp \
$(d)/ch18eirEndScene.dmp \
$(d)/ch18ephEndScene.dmp \
$(d)/ch19eirEndScene.dmp \
$(d)/ch19ephEndScene.dmp \
$(d)/ch1EndScene.dmp \
$(d)/ch20eirEndScene.dmp \
$(d)/ch20ephEndScene.dmp \
$(d)/ch2EndScene.dmp \
$(d)/ch3EndScene.dmp \
$(d)/ch4EndScene.dmp \
$(d)/ch5EndScene.dmp \
$(d)/ch5xEndScene.dmp \
$(d)/ch6EndScene.dmp \
$(d)/ch7EndScene.dmp \
$(d)/ch8EndScene.dmp \
$(d)/ch9eirEndScene.dmp \
$(d)/ch9ephEndScene.dmp \
$(d)/final1eirEndScene.dmp \
$(d)/final1ephEndScene.dmp \
$(d)/final2eirEndScene.dmp \
$(d)/final2ephEndScene.dmp \
$(d)/prologueEndScene.dmp \
$(d)/tower1EndScene.dmp \
$(d)/tower2EndScene.dmp \
$(d)/tower3EndScene.dmp \
$(d)/tower4EndScene.dmp \
$(d)/tower5EndScene.dmp \
$(d)/tower6EndScene.dmp \
$(d)/tower7EndScene.dmp \
$(d)/tower8EndScene.dmp \
$(d)/ruins1EndScene.dmp \
$(d)/ruins2EndScene.dmp \
$(d)/ruins3EndScene.dmp \
$(d)/ruins4EndScene.dmp \
$(d)/ruins5EndScene.dmp \
$(d)/ruins6EndScene.dmp \
$(d)/ruins7EndScene.dmp \
$(d)/ruins8EndScene.dmp \
$(d)/ruins9EndScene.dmp \
$(d)/ruins10EndScene.dmp &:
	python $(HERE)/rip_chunks.py $(BASEROM) $(HERE)

CLEAN := $(CLEAN) $(d)/*.dmp

d := $(dirstack_$(sp))
sp := $(basename $(sp))
