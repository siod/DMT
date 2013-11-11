//Si*
#pragma comment(lib, "SiConf.lib")
#pragma comment(lib, "SiLog.lib")

//Graphics
#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d11.lib" )
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment( lib, "d3dx11d.lib" )
#else
#pragma comment( lib, "d3dx11.lib" )
#endif

//Input
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"xinput.lib")
