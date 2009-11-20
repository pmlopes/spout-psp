#include <pspkernel.h>
#include <pspdebug.h>
#include <psprtc.h>

#include "graphics.h"
#include "spout.h"

#define printf pspDebugScreenPrintf

/* Define the module info section */
PSP_MODULE_INFO("spout", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

static int running = 1;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
	running = 0;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0,
			PSP_THREAD_ATTR_USER, 0);
	if (thid >= 0) {
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

int main(int argc, char *argv[])
{
	unsigned long long curTick, nextTick = 0;
	unsigned int wait;
	unsigned int cnt = 0;
	unsigned int interval = 1000 / FRAMERATE;

	SetupCallbacks();

	initGraphics();
	pceAppInit();

	sceRtcGetCurrentTick(&nextTick);
	nextTick += interval;
	while(running) {
		sceRtcGetCurrentTick(&curTick);
		wait = nextTick - curTick;
		if(wait > 0) {
			sceKernelDelayThread(wait);
		}

		pceAppProc(cnt);

		nextTick += interval;
		cnt++;
	}

	sceKernelExitGame();
	return 0;
}
