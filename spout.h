#ifndef SPOUT_H_
#define SPOUT_H_

#define FRAMERATE 50

void pceAppInit(void);

void pceAppProc(int);

void spout(int t, int x, int y);
void sweep(unsigned char c1, unsigned char c2);

#endif /* SPOUT_H_ */
