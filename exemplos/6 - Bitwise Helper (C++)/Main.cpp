#include <iostream>
#include <windows.h>
#include "Exception.cpp"
#include "Vector2.cpp"
#include "Rect.cpp"
#include "BaseConverter.h";
#include <sstream>

using namespace std;

// == DEFINING
#define LAYOUT_DEFAULT_SPACING 16
#define LABEL_DEFAULT_HEIGHT 24 
#define TEXTBOX_DEFAULT_HEIGHT 24

typedef struct
{
	UINT8 v1;
	wchar_t* binaryRepresentation1;
	UINT8 v2;
	wchar_t* binaryRepresentation2;
	UINT8 andValue;
	wchar_t* andValueBinaryRepresentation;
	UINT8 orValue;
	wchar_t* orValueBinaryRepresentation;
	UINT8 xorValue;
	wchar_t* xorValueBinaryRepresentation;
	UINT8 shiftLeftV1;
	wchar_t* slV1BinaryRepresentation;
	UINT8 shiftRightV1;
	wchar_t* srV1BinaryRepresentation;
	UINT8 shiftLeftV2;
	wchar_t* slV2BinaryRepresentation;
	UINT8 shiftRightV2;
	wchar_t* srV2BinaryRepresentation;

} BitwiseResult;

// == CONSTANT SECTION

const wchar_t className[] = L"BITWISE_MAIN";

// == VARIABLE SECTION

IRect clientPadding;
IRect clientSizePadding;
IVector2 clientSize; 
BitwiseResult result;

// CONTROLS
struct ComponentList
{
	struct Head
	{
		HWND txtInput1;
		HWND lblInput1Binary;
		HWND txtInput2;
		HWND lblInput2Binary;
		HWND lblInput;
		HWND btnProcess;
		HWND separator;
	} head;
	struct Body
	{
		HWND lblInputR1;
		HWND txtInputR1;
		HWND lblInputR2;
		HWND txtInputR2;
		HWND lblInputR3;
		HWND txtInputR3;
		HWND lblInputSlV1;
		HWND txtInputSlV1;
		HWND lblInputSlV2;
		HWND txtInputSlV2;
		HWND lblInputSrV1;
		HWND txtInputSrV1;
		HWND lblInputSrV2;
		HWND txtInputSrV2;

	} body;

} children;

// == EVENTS
// ========================================================================

void onButtonGOPressed()
{
	// APPLY BITWISE OPERATIONS

	result.andValue = result.v1 & result.v2;
	result.andValueBinaryRepresentation = convertByteToBinaryNotation(result.andValue);
	result.orValue = result.v1 | result.v2;
	result.orValueBinaryRepresentation = convertByteToBinaryNotation(result.orValue);
	result.xorValue = result.v1 ^ result.v2;
	result.xorValueBinaryRepresentation = convertByteToBinaryNotation(result.xorValue);

	result.shiftLeftV1 = result.v1 << 1;
	result.slV1BinaryRepresentation = convertByteToBinaryNotation(result.shiftLeftV1);

	result.shiftRightV1 = result.v1 >> 1;
	result.srV1BinaryRepresentation = convertByteToBinaryNotation(result.shiftRightV1);

	result.shiftLeftV2 = result.v2 << 1;
	result.slV2BinaryRepresentation = convertByteToBinaryNotation(result.shiftLeftV2);

	result.shiftRightV2 = result.v2 >> 1;
	result.srV2BinaryRepresentation = convertByteToBinaryNotation(result.shiftRightV2);

	SetWindowText(children.body.txtInputR1, result.andValueBinaryRepresentation);
	SetWindowText(children.body.txtInputR2, result.orValueBinaryRepresentation);
	SetWindowText(children.body.txtInputR3, result.xorValueBinaryRepresentation);
	SetWindowText(children.body.txtInputSlV1, result.slV1BinaryRepresentation);
	SetWindowText(children.body.txtInputSrV1, result.srV1BinaryRepresentation);
	SetWindowText(children.body.txtInputSlV2, result.slV2BinaryRepresentation);
	SetWindowText(children.body.txtInputSrV2, result.srV2BinaryRepresentation);
}

void onInputValueChanged()
{
	stringstream ss;
	int txtLength1 = GetWindowTextLength(children.head.txtInput1);
	int txtLength2 = GetWindowTextLength(children.head.txtInput2);

	if (txtLength1 && txtLength2 > 0)
	{
		EnableWindow(children.head.btnProcess, TRUE);
	}
	else
	{
		EnableWindow(children.head.btnProcess, FALSE);
	}

	// GET VALUES

	// VALUE 1

	int length1 = GetWindowTextLength(children.head.txtInput1);

	wchar_t value1[4];
	GetWindowTextW(children.head.txtInput1, value1, sizeof(value1) );


	int valueConverted1 = _wtoi(value1);

	if (valueConverted1 < 256)
	{
		result.v1 = valueConverted1;
	}
	else
	{
		result.v1 = 255;
	}

	result.binaryRepresentation1 = convertByteToBinaryNotation(result.v1);
	SetWindowText(children.head.lblInput1Binary, result.binaryRepresentation1);
	
	// VALUE 2

	int length2 = GetWindowTextLength(children.head.txtInput2);

	wchar_t value2[4];
	GetWindowTextW(children.head.txtInput2, value2, sizeof(value2) );

	int valueConverted2 = _wtoi(value2);

	if (valueConverted2 < 256)
	{
		result.v2 = valueConverted2;
	}
	else
	{
		result.v2 = 255;
	}

	result.binaryRepresentation2 = convertByteToBinaryNotation(result.v2);
	SetWindowText(children.head.lblInput2Binary, result.binaryRepresentation2);
}

// == FUNCTIONS
// ========================================================================

void createAndPopulateStructures(HWND hWndParent)
{
	// WINDOW SIZE

	RECT clientRect;
	if (GetClientRect(hWndParent, &clientRect) == false)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot obtain the 'hWndParent' rect.";

		throw e;
	}

	clientSize.x = clientRect.right - clientRect.left;
	clientSize.y = clientRect.bottom - clientRect.top;

	// WINDOW PADDING

	clientPadding.x = LAYOUT_DEFAULT_SPACING;
	clientPadding.y = LAYOUT_DEFAULT_SPACING;
	clientPadding.w = LAYOUT_DEFAULT_SPACING;
	clientPadding.h = LAYOUT_DEFAULT_SPACING;

	// WINDOW SIZE PADDING
	clientSizePadding.x = clientPadding.x;
	clientSizePadding.y = clientPadding.y;
	clientSizePadding.w = clientSize.x - ( clientPadding.w * 2 );
	clientSizePadding.h = clientSize.y - ( clientPadding.h * 2 );
}

void createControls(HWND hWndParent)
{
	// == HEAD SECTION 
	// ===================================================================
	
	// LABEL

	children.head.lblInput = CreateWindowEx
	(
		NULL,
		L"STATIC",
		L" VALUE: ",
		WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
		clientSizePadding.x, // X
		clientSizePadding.y, // Y
		50, // WIDTH
		LABEL_DEFAULT_HEIGHT, // HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.head.lblInput == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInput'.";

		throw e;
	}

	// BUTTON

	children.head.btnProcess = CreateWindowEx
	(
		NULL,
		L"BUTTON",
		L"GO",
		WS_CHILD | WS_VISIBLE | WS_DISABLED,
		clientSizePadding.w - LAYOUT_DEFAULT_SPACING, //X
		clientSizePadding.y, // Y
		50 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.head.btnProcess == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'btnProcess'.";

		throw e;
	}

	// INPUT 1

	children.head.txtInput1 = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		L"0",
		WS_CHILD | WS_VISIBLE | ES_NUMBER,
		clientSizePadding.x + (50 + LAYOUT_DEFAULT_SPACING), //X
		clientSizePadding.y, // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.head.txtInput1 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'txtInput'.";

		throw e;
	}

	SendMessage(children.head.txtInput1, EM_SETLIMITTEXT, 3, 0);

	// BINARY LABEL 1

	children.head.lblInput1Binary = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"????????",
		WS_CHILD | WS_VISIBLE | ES_CENTER | SS_CENTERIMAGE,
		clientSizePadding.x + (50 + LAYOUT_DEFAULT_SPACING), //X
		clientSizePadding.y + TEXTBOX_DEFAULT_HEIGHT + (clientSizePadding.y / 2), // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.head.lblInput1Binary == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInput1Binary'.";

		throw e;
	}

	// INPUT 2

	children.head.txtInput2 = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		L"0",
		WS_CHILD | WS_VISIBLE | ES_NUMBER,
		clientSizePadding.x + (150 + LAYOUT_DEFAULT_SPACING), //X
		clientSizePadding.y, // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.head.txtInput2 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'txtInput'.";

		throw e;
	}

	SendMessage(children.head.txtInput2, EM_SETLIMITTEXT, 3, 0);

	// BINARY LABEL 2

	children.head.lblInput2Binary = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"????????",
		WS_CHILD | WS_VISIBLE | ES_CENTER | SS_CENTERIMAGE,
		clientSizePadding.x + (150 + LAYOUT_DEFAULT_SPACING), //X
		clientSizePadding.y + TEXTBOX_DEFAULT_HEIGHT + (clientSizePadding.y / 2), // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.head.lblInput2Binary == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInput2Binary'.";

		throw e;
	}
	
	// SEPARATOR

	children.head.separator = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"",
		WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ,
		LAYOUT_DEFAULT_SPACING, //X
		LAYOUT_DEFAULT_SPACING + TEXTBOX_DEFAULT_HEIGHT + (LAYOUT_DEFAULT_SPACING * 3), // Y
		clientSizePadding.w, // WIDTH
		2, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.head.separator == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'separator'.";

		throw e;
	}

	// == BODY 
	// ===================================================================

	// LEFT SIDE

	RECT rect;
	GetWindowRect(children.head.separator, &rect);
	MapWindowPoints(HWND_DESKTOP, GetParent(children.head.separator), (LPPOINT)&rect, 2);

	// LBL INPUT R1

	children.body.lblInputR1 = CreateWindowEx
	(
		NULL,
		L"STATIC",
		L"| OR: ",
		WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE,
		clientSizePadding.x, // X
		rect.bottom + clientSizePadding.y, // Y
		50, // WIDTH
		LABEL_DEFAULT_HEIGHT, // HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.lblInputR1 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInputR1'.";

		throw e;
	}

	// TXT INPUT R1

	children.body.txtInputR1 = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"????????",
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		clientSizePadding.x + (50 + LAYOUT_DEFAULT_SPACING), //X
		rect.bottom + clientSizePadding.y, // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.txtInputR1 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'txtInput'.";

		throw e;
	}

	// LBL INPUT R2

	children.body.lblInputR2 = CreateWindowEx
	(
		NULL,
		L"STATIC",
		L"&& AND: ",
		WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE,
		clientSizePadding.x, // X
		rect.bottom + (clientSizePadding.y * 4), // Y
		50, // WIDTH
		LABEL_DEFAULT_HEIGHT, // HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.lblInputR2 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInputR2'.";

		throw e;
	}

	//TXT INPUT 3

	children.body.txtInputR2 = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"????????",
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		clientSizePadding.x + (50 + LAYOUT_DEFAULT_SPACING), //X
		rect.bottom + (clientSizePadding.y * 4), // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.txtInputR2 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'txtInput'.";

		throw e;
	}

	// LBL INPUT R3

	children.body.lblInputR3 = CreateWindowEx
	(
		NULL,
		L"STATIC",
		L"^ XOR: ",
		WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE,
		clientSizePadding.x, // X
		rect.bottom + (clientSizePadding.y * 7), // Y
		50, // WIDTH
		LABEL_DEFAULT_HEIGHT, // HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.lblInputR3 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInputR2'.";

		throw e;
	}

	//TXT INPUT 3

	children.body.txtInputR3 = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"????????",
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		clientSizePadding.x + (50 + LAYOUT_DEFAULT_SPACING), //X
		rect.bottom + (clientSizePadding.y * 7), // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.txtInputR3 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'txtInputR3'.";

		throw e;
	}

		children.head.btnProcess = CreateWindowEx
	(
		NULL,
		L"BUTTON",
		L"GO",
		WS_CHILD | WS_VISIBLE | WS_DISABLED,
		clientSizePadding.w - LAYOUT_DEFAULT_SPACING, //X
		clientSizePadding.y, // Y
		50 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);


	// == RIGHT SIDE

	// INPUT SHIFT LEFT V1

	children.body.txtInputSlV1 = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"????????",
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		clientSizePadding.x + (150 + LAYOUT_DEFAULT_SPACING), //X
		rect.bottom + clientSizePadding.y, // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.txtInputSlV1 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'txtInputSlV1'.";

		throw e;
	}

	// LABEL SHIFT LEFT V1

	children.body.lblInputSlV1 = CreateWindowEx
	(
		NULL,
		L"STATIC",
		L"V1<<",
		WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE,
		clientSizePadding.w - LAYOUT_DEFAULT_SPACING, //X
		rect.bottom + clientSizePadding.y, // Y
		50 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.lblInputSlV1 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInputSlV1'.";

		throw e;
	}

	// INPUT SHIFT LEFT V2

	children.body.txtInputSlV2 = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"????????",
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		clientSizePadding.x + (150 + LAYOUT_DEFAULT_SPACING), //X
		rect.bottom + (clientSizePadding.y * 3), // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.txtInputSlV2 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'txtInputSlV2'.";

		throw e;
	}

	// LABEL SHIFT LEFT V2

	children.body.lblInputSlV2 = CreateWindowEx
	(
		NULL,
		L"STATIC",
		L"V2<<",
		WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE,
		clientSizePadding.w - LAYOUT_DEFAULT_SPACING, //X
		rect.bottom + (clientSizePadding.y * 3), // Y
		50 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.lblInputSlV2 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInputSlV2'.";

		throw e;
	}

	// INPUT SHIFT RIGHT V1

	children.body.txtInputSrV1 = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"????????",
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		clientSizePadding.x + (150 + LAYOUT_DEFAULT_SPACING), //X
		rect.bottom + (clientSizePadding.y * 5), // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.txtInputSlV2 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'txtInputSlV1'.";

		throw e;
	}

	// LABEL SHIFT RIGHT V1

	children.body.lblInputSlV2 = CreateWindowEx
	(
		NULL,
		L"STATIC",
		L"V1>>",
		WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE,
		clientSizePadding.w - LAYOUT_DEFAULT_SPACING, //X
		rect.bottom + (clientSizePadding.y * 5), // Y
		50 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.lblInputSlV2 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInputSlV2'.";

		throw e;
	}

	// INPUT SHIFT RIGHT V2

	children.body.txtInputSrV2 = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		L"STATIC",
		L"????????",
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		clientSizePadding.x + (150 + LAYOUT_DEFAULT_SPACING), //X
		rect.bottom + (clientSizePadding.y * 7), // Y
		100 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.txtInputSrV2 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'txtInputSrV2'.";

		throw e;
	}

	// LABEL SHIFT RIGHT V2

	children.body.lblInputSlV2 = CreateWindowEx
	(
		NULL,
		L"STATIC",
		L"V2>>",
		WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE,
		clientSizePadding.w - LAYOUT_DEFAULT_SPACING, //X
		rect.bottom + (clientSizePadding.y * 7), // Y
		50 - LAYOUT_DEFAULT_SPACING, // WIDTH
		TEXTBOX_DEFAULT_HEIGHT, //HEIGHT
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (children.body.lblInputSlV2 == NULL)
	{
		Exception e;
		e.title = L"ERROR!";
		e.message = L"Cannot create the component 'lblInputSlV2'.";

		throw e;
	}
}

// == EXCEPTION HANDLER
void DealWithException(Exception e)
{
	MessageBoxEx(0, e.message, e.title, MB_ICONERROR | MB_OK, 0);
	ExitProcess(1);
}

// == WINDOW PROCESS HANDLER

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	try
	{
		switch (msg)
		{

			case WM_CREATE:
				createAndPopulateStructures(hWnd);
				createControls(hWnd);
				break;

			case WM_CLOSE:
				DestroyWindow(hWnd);
				break;

			case WM_COMMAND:

				if ( (HWND) lParam == children.head.btnProcess)
				{
					// BUTTON "GO"
					onButtonGOPressed();
				}
				else if ( (HWND) lParam == children.head.txtInput1 )
				{
					// INPUT TEXT

					if (HIWORD(wParam) == EN_CHANGE)
					{
						onInputValueChanged();
					}
				}
				else if ((HWND)lParam == children.head.txtInput2)
				{
					// INPUT TEXT

					if (HIWORD(wParam) == EN_CHANGE)
					{
						onInputValueChanged();
					}
				}

				break;

			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

		return 0;
	}
	catch (Exception e)
	{
		DealWithException(e);
	}
}

// == ENTRY POINT

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		WNDCLASSEX wc;
		HWND hWnd;
		MSG msg;

		// CREATE WINDOW CLASS

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = wndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = className;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			Exception e;
			e.title = L"ERROR!";
			e.message = L"Error at register window class.";

			throw e;
		}

		// CREATE WINDOW

		hWnd = CreateWindowEx
		(
			WS_EX_WINDOWEDGE,
			className,
			L"BITWISE HELPER",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			350,
			300,
			NULL,
			NULL,
			hInstance,
			NULL
		);

		if (hWnd == NULL)
		{
			Exception e;
			e.title = L"ERROR!";
			e.message = L"Error at create window.";

			throw e;
		}

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		// MESSAGE LOOP

		while ( GetMessage(&msg, NULL, 0, 0) > 0 )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		return 0;

	}
	catch (Exception e)
	{
		DealWithException(e);
	}
}