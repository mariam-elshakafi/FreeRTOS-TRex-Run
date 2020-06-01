#ifndef SWITCH_H
#define SWITCH_H

/* Switch states */
#define SWITCH_NOT_PRESSED        (1)
#define SWITCH_PRESSED            (0)


extern void SWITCH_init(void);
extern u8 SWITCH_GetSwitchValue(void);

#endif
