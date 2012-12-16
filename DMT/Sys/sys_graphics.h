

typedef struct {
	int width;
	int height;
	int numSamples;
	unsigned int deviceFlags;
	bool fullscreen;
} driver_params_t;

void Sys_InitWindow();
void Sys_InitGraphics(driver_params_t);
void Sys_ShutdownGraphics();
void Sys_SwapBuffers();