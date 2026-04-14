#ifndef _SCREEN_H_
#define _SCREEN_H_
#define INCREASE_VALUE 30
#define START_SPEED 500
#define MINIMUM_SPEED 100
static unsigned int speed=START_SPEED;

void init_screen();
void done_screen();
void gotoyx(int y, int x);
int ngetch();
void getscreensize(int& y, int& x);

#endif /* _SCREEN_H_ */
