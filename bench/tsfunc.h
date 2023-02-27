#ifndef _H_TS_
#define _H_TS_

extern blm_t			m;
extern pmc_t			pm;

extern void sim_TlmDrop();
extern void sim_Run(double dT);

int ts_wait_for_IDLE();
int ts_wait_for_SPINUP(float ref);
int ts_wait_for_MOTION(float ref);

void ts_BASE();
void ts_SPEED();
void ts_HFI();
void ts_HALL();
void ts_WEAK();
void ts_START_all();

#endif /* _H_TS_ */

