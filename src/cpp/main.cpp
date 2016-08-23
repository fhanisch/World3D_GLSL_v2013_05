#include "main.h"
#include "Renderer.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int init_fullscreen(HINSTANCE hInstance, LPCTSTR wnd_name);
int enable_opengl();
int init_opengl();
int build_font();

HWND	hWnd;
HDC		hDC;
GLuint  base;
bool	key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	bool quit=false;
	MSG		msg;
	Renderer *renderer;
	CAMERA cam;
	ORIENTATION ori;
	const double dAngle=0.02;
	const double ds=0.2;

	init_fullscreen(hInstance, TEXT("GLSL_Demo"));
	enable_opengl();
	init_opengl();
	build_font();

	memset(&ori,0,sizeof(ORIENTATION));

	GLenum err = glewInit();
	renderer = new Renderer(&cam, &ori, base);

	const GLubyte *vendor		= glGetString(GL_VENDOR);
	const GLubyte *bezeichnung	= glGetString(GL_RENDERER);
	const GLubyte *oglVersion	= glGetString(GL_VERSION);
	const GLubyte *glslVersion	= glGetString(GL_SHADING_LANGUAGE_VERSION);

	int maxVerts;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxVerts);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while(!quit)
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if( msg.message == WM_QUIT)
				quit = TRUE;
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}

		if (key[VK_ESCAPE]==true) quit=true;
		if (key[VK_LEFT]==true) cam.yAngle=dAngle;
		else if (key[VK_RIGHT]==true) cam.yAngle=-dAngle;
			else cam.yAngle=0.0;
		if (key[VK_UP]==true) cam.xAngle=dAngle;
		else if (key[VK_DOWN]==true) cam.xAngle=-dAngle;
			else cam.xAngle=0.0;
		if (key[87]==true) cam.xPos=ds;
			else if (key[83]==true) cam.xPos=-ds;
			else cam.xPos=0.0;
		if (key[68]==true) cam.yPos=-ds;
			else if (key[65]==true) cam.yPos=ds;
			else cam.yPos=0.0;
		if (key[0x58]==true) cam.zPos=-ds;
			else if (key[0x59]==true) cam.zPos=ds;
			else cam.zPos=0.0;

		if (key[VK_NUMPAD2]) ori.xAngle+=0.01;
		if (key[VK_NUMPAD8]) ori.xAngle-=0.01;
		if (key[VK_NUMPAD4]) ori.yAngle-=0.01;
		if (key[VK_NUMPAD6]) ori.yAngle+=0.01;

        if (key[0x31]) ori.viewIndex=0;
        if (key[0x32]) ori.viewIndex=1;

		renderer->render();
		SwapBuffers(hDC);
	}

	return 0;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_KEYDOWN:
			key[wParam] = TRUE;
			break;
		case WM_KEYUP:
			key[wParam] = FALSE;
			break;
	}
	return( DefWindowProc( hWnd, uMsg, wParam, lParam ));
}

int init_fullscreen(HINSTANCE hInstance, LPCTSTR wnd_name)
{
	WNDCLASS		wc;
	DEVMODE			old_screen_settings;
	DEVMODE			new_screen_settings;
	memset( &old_screen_settings, 0, sizeof( old_screen_settings ));
	memset( &new_screen_settings, 0, sizeof( new_screen_settings ));

	if( EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &old_screen_settings ) != TRUE ) return 1;

	wc.lpszClassName = TEXT("GenericApplicationClass");
	wc.lpszMenuName = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.lpfnWndProc = MainWndProc;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.style = CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	RegisterClass(&wc);
	hWnd = CreateWindowEx(
						WS_EX_TOPMOST,
						wc.lpszClassName,
						wnd_name,
						WS_POPUP |WS_VISIBLE,
						0,
						0,
						WND_WIDTH,
						WND_HEIGHT,
						NULL,
						NULL,
						hInstance,
						NULL);

	new_screen_settings.dmSize = sizeof( new_screen_settings );
	new_screen_settings.dmPelsWidth = WND_WIDTH;
	new_screen_settings.dmPelsHeight = WND_HEIGHT;
	new_screen_settings.dmBitsPerPel = BIT_DEPTH;
	new_screen_settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if( ChangeDisplaySettings( &new_screen_settings, 0 ) != DISP_CHANGE_SUCCESSFUL ) return 1;
	ShowCursor( 0 );
	return 0;
}

int enable_opengl()
{
	HGLRC					hRC;
	PIXELFORMATDESCRIPTOR	pfd;
	int						pixelFormat;

	hDC = GetDC(hWnd);
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.cAlphaBits = 8;
	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);
	hRC = wglCreateContext( hDC );
	wglMakeCurrent(hDC,hRC);

	return 0;
}

int init_opengl()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return 0;
}

int build_font()
{
    HFONT font;

    base = glGenLists(96);
    font = CreateFont( -11, 			                    // Height Of Font ( NEW )
                        0, 									// Width Of Font
                        0, 									// Angle Of Escapement
                        0, 									// Orientation Angle
                        FW_NORMAL, 							// Font Weight
                        FALSE, 								// Italic
                        FALSE, 								// Underline
                        FALSE, 								// Strikeout
                        ANSI_CHARSET, 						// Character Set Identifier
                        OUT_TT_PRECIS, 						// Output Precision
                        CLIP_DEFAULT_PRECIS, 				// Clipping Precision
                        ANTIALIASED_QUALITY, 				// Output Quality
                        FF_DONTCARE|DEFAULT_PITCH, 			// Family And Pitch
                        "Courier New");		 				// Font Name

    SelectObject(hDC,font);
    wglUseFontBitmaps(hDC, 32, 96, base); // Builds 96 Characters Starting At Character 32
	DeleteObject(font);

    return 0;
}
