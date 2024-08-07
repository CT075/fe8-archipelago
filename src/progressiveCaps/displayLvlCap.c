#include "global.h"

#include "statscreen.h"
#include "fontgrp.h"
#include "scene.h"
#include "helpbox.h"

#include "constants.h"
#include "archipelago.h"
#include "progressiveCaps.h"
#include "ram_structures.h"

#define LEVEL_HELP_TEXT 0x0542

// CR cam: this is hardcoded into [alltext.txt]
#define LEVEL_CAP_ID_BASE 0x00DE

int selectLevelCapTextId() {
  return LEVEL_CAP_ID_BASE + progressiveCaps->lvlCapStage;
}

void StartHelpBoxExt(const struct HelpBoxInfo* info, int unk) {
  struct HelpBoxProc *proc;
  int wContent, hContent;

  proc = (void *)Proc_Find(gProcScr_HelpBox);

  if (!proc) {
    proc = (void *)Proc_Start(gProcScr_HelpBox, PROC_TREE_3);

    proc->unk52 = unk;

    SetHelpBoxInitPosition(proc, info->xDisplay, info->yDisplay);
    ResetHelpBoxInitSize(proc);
  }
  else {
    proc->xBoxInit = proc->xBox;
    proc->yBoxInit = proc->yBox;

    proc->wBoxInit = proc->wBox;
    proc->hBoxInit = proc->hBox;
  }

  proc->info = info;

  proc->timer    = 0;
  proc->timerMax = 12;

  proc->item = 0;
  proc->mid = info->mid;

  // CR cam: it feels bad to hardcode this but it's easier than the alternatives
  if (proc->mid == LEVEL_HELP_TEXT) {
    proc->mid = selectLevelCapTextId();
  }

  if (proc->info->populate) {
    proc->info->populate(proc);
  }

  SetTextFontGlyphs(1);
  GetStringTextBox(GetStringFromIndex(proc->mid), &wContent, &hContent);
  SetTextFontGlyphs(0);

  ApplyHelpBoxContentSize(proc, wContent, hContent);
  ApplyHelpBoxPosition(proc, info->xDisplay, info->yDisplay);

  ClearHelpBoxText();
  StartHelpBoxTextInit(proc->item, proc->mid);

  sLastHbi = info;
}
