#pragma once

#include <d3dx9.h>
#include <windows.h>

#define SCREEN_WIDTH (1024.0f)
#define SCREEN_HEIGHT (768.0f)
#define ReleaseCOM(x) if(x) { x->Release(); x = NULL; }

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif
#ifndef SAFE_DESTROY
#define SAFE_DESTROY(p)		 { if (p) { (p)->Destroy(); (p)=NULL; } }
#endif 

#define BETWEEN(min,x,max) (min<=x&&x<=max)


#pragma comment ( lib, "./Library/d3d9.lib" )
#pragma comment ( lib, "./Library/d3dx9.lib" )
#pragma comment ( lib, "./Library/dxguid.lib" )
#pragma comment ( lib, "./Library/dinput8.lib" )
#pragma comment ( lib, "./Library/Box2D.lib" )
#pragma comment ( lib, "winmm.lib" )