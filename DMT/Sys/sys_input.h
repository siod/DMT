


struct input_vibration;
bool Sys_InputInit();
void Sys_InputPoll();
void Sys_InputSetCaptureMouse(bool);
void Sys_InputCaptureMouse();
void Sys_InputFrame();
void Sys_InputLost();
void Sys_InputGained();
void Sys_InputSetRumble(unsigned int which,input_vibration* data);
