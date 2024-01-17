#include "global.h"

#include "variables.h"
#include "bmcontainer.h"

#include "ram_structures.h"

#define NEW_CONVOY_ITEM_COUNT 200

// CR-someday cam: This file copy-pastes huge swaths of `bmcontainer.c` just to
// change a few constants. It would be nice to be a bit less heavy-handed about
// everything.

u16 *GetConvoyItemArray() {
    return newConvoyArray;
}

void ClearSupplyItems() {
    CpuFill16(0, newConvoyArray, NEW_CONVOY_ITEM_COUNT * sizeof(u16));
}

void ShrinkConvoyItemList() {
    u16 i;
    u16 * buffer = (void*) gGenericBuffer;
    u16 * bufferIt = buffer;
    u16 * convoy = GetConvoyItemArray();

    for (i = 0; i < CONVOY_ITEM_COUNT; ++i)
    {
        if (*convoy != 0)
        {
            *bufferIt = *convoy;
            bufferIt++;
        }
        convoy++;
    }

    *bufferIt = 0;
    ClearSupplyItems();
    CpuCopy16(buffer, GetConvoyItemArray(), i * sizeof(u16));
    return;
}

int GetConvoyItemCount() {
    int i;
    int count = 0;
    u16 * convoy = newConvoyArray;
    for (i = 0; i < NEW_CONVOY_ITEM_COUNT; i++) {
        if (convoy[i] != 0) {
            count++;
          }
    }

    return count;
}

int AddItemToConvoy(int item) {
    int i;
    u16 * convoy;
    gBmSt.itemUnk2E = 0;
    convoy = newConvoyArray;
    for (i = 0; i < NEW_CONVOY_ITEM_COUNT; ++i) {
        if (convoy[i] == 0)
        {
            convoy[i] = item;
            return i;
        }
    }
    gBmSt.itemUnk2E = item;
    return -1;
}

void RemoveItemFromConvoy(int index)
{
    newConvoyArray[index] = 0;
    ShrinkConvoyItemList();
    return;
}
