#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// include loaders

#define PROGRAM_MENU_NEW 1
#define PROGRAM_MENU_OPEN 2
#define PROGRAM_MENU_EXIT 3
#define CHANGE_TITLE 4

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu;
HWND hEdit;

int WINAPI WinMain(HINSTANCE hInst , HINSTANCE hPrevInst, LPSTR args,int ncmdshow) // Initialization

{
    MessageBox(NULL,"Running executable...","C++ Window",MB_YESNOCANCEL);

    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;


    if(!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass",L"C++ Executable",WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,500,500,
                  NULL,NULL,NULL,NULL);

    MSG msg = {0};

    while( GetMessage(&msg,NULL,NULL,NULL) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;

}


LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
     switch ( msg)
     {
     case WM_COMMAND:

        switch(wp)
        {
        case PROGRAM_MENU_EXIT:
            DestroyWindow(hWnd);
            break;

        case PROGRAM_MENU_NEW:
            MessageBeep(MB_ICONINFORMATION);
            break;

        case CHANGE_TITLE:
            wchar_t text[100];
            GetWindowTextW(hEdit,text,100);
            SetWindowTextW(hWnd,text);
            break;
        }

        break;
     case WM_CREATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
     case WM_DESTROY:
        PostQuitMessage(0);
        break;
     default:
        return DefWindowProcW(hWnd,msg,wp,lp);
     }
}


void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hProgramMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu,MF_STRING,CHANGE_TITLE,"Change Title");

    AppendMenu(hProgramMenu,MF_STRING,PROGRAM_MENU_NEW,"New");
    AppendMenu(hProgramMenu,MF_POPUP,(UINT_PTR)hSubMenu,"Open SubMenu");
    AppendMenu(hProgramMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hProgramMenu,MF_STRING,PROGRAM_MENU_EXIT,"Exit");

    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hProgramMenu,"Program");
    AppendMenu(hMenu,MF_STRING,NULL,"Help");

    SetMenu(hWnd,hMenu);
}

void AddControls(HWND hWnd)
{
     CreateWindowW(L"static",L"Enter Text Here :",WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER ,200,100,100,50,hWnd,
                   NULL,NULL,NULL);

     hEdit = CreateWindowW(L"Edit",L"...",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL ,200,152,100,50,hWnd,
                   NULL,NULL,NULL);

     CreateWindowW(L"Button",L"Change Title",WS_VISIBLE | WS_CHILD ,200,204,100,50,hWnd,(HMENU)CHANGE_TITLE,NULL,NULL);

     CreateWindowW(L"Button",L"Credits : https://github.com/0xVienna",WS_VISIBLE | WS_CHILD ,80,300,300,50,hWnd,NULL,NULL,NULL);
}


