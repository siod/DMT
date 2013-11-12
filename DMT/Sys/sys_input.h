


struct input_vibration;
bool Sys_InputInit();
//Poll methods
unsigned int Sys_InputPollKeyboard();
unsigned int Sys_InputPollMouse();
bool Sys_InputPollController(const unsigned int which,void* blah);

void Sys_InputGetKeyboardData();
void Sys_InputGetMouseData();
void Sys_InputGetControllerData();

void Sys_InputSetCaptureMouse(bool);
void Sys_InputCaptureMouse();
void Sys_InputFrame();
void Sys_InputLost();
void Sys_InputGained();
void Sys_InputSetRumble(unsigned int which,input_vibration* data);
