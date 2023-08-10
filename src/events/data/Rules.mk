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
$(d)/prologueEndScene.dmp : HERE := $(d)

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
$(d)/prologueEndScene.dmp &:
	python $(HERE)/rip_chunks.py $(BASEROM) $(HERE)

d := $(dirstack_$(sp))
sp := $(basename $(sp))
