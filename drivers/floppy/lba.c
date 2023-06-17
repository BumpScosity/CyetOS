#include "internal.h"
#include "floppy.h"

void lba_2_chs_f(int sectors_per_track, uint32_t lba, uint16_t* cyl, uint16_t* head, uint16_t* sector)
{
    *cyl    = lba / (2 * sectors_per_track);
    *head   = ((lba % (2 * sectors_per_track)) / 18);
    *sector = ((lba % (2 * sectors_per_track)) % sectors_per_track + 1);

}

void lba_2_chs(uint32_t lba, uint16_t* cyl, uint16_t* head, uint16_t* sector)
{
    lba_2_chs_f(18, lba, cyl, head, sector);
}