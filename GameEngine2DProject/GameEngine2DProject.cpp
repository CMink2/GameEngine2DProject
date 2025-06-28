// GameEngine2DProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
// 깃허브 테스트

#include "framework.h"
#include "GameEngine2DProject.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;                                    // 현재 윈도우 핸들을 저장하는 전역 변수입니다.

wchar_t g_windowTitle[100];                          // 윈도우 제목을 저장하는 전역 변수입니다.

//프레임 타이머 관련 변수
double deltaTime = 0.0;                         // 프레임 간 시간 차이를 저장하는 변수입니다.
LARGE_INTEGER startTime;                        // 프레임 시작 시각을 저장하는 변수입니다.
LARGE_INTEGER endTime;                          // 프레임 종료 시각을 저장하는 변수입니다.
LARGE_INTEGER freq;                             // 타이머의 해상도를 저장하는 변수입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//디버깅 관련 함수들
void CreateConsole(); // 콘솔을 생성하는 함수

//게임 로직 관련 함수들
void Start();
void Update();
void Render();

// 프레임 시작과 끝을 알리는 함수들
void StartFrame();
void EndFrame();

void ShowFPS(); // FPS를 출력하는 함수

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEENGINE2DPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	Start(); // 게임 시작 함수 호출

	CreateConsole(); // 콘솔 생성 함수 호출

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEENGINE2DPROJECT));

    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break; // ⬅️ 종료
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		// 메시지가 없을 때 게임 루프를 실행합니다.
        else
        {
			StartFrame(); // 프레임 시작
			EndFrame(); // 프레임 종료   
        }

    }

    
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEENGINE2DPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAMEENGINE2DPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd) return FALSE;

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// 콘솔을 생성하는 함수
void CreateConsole()
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr); // 표준 출력과 오류 출력을 콘솔로 리다이렉트합니다.
}
// 게임 로직 관련 함수들 구현
void StartFrame()
{
    QueryPerformanceCounter(&startTime); // 프레임 시작 시 타이머 시작
    // 프레임의 시작 작업을 여기에 작성합니다.
    // 예: 물리 충돌, 업데이트 로직 등.
}

void EndFrame()
{
    QueryPerformanceCounter(&endTime); // 프레임 종료 시 타이머 종료
    // 프레임 간 시간 차이를 계산합니다.
    deltaTime = static_cast<double>(endTime.QuadPart - startTime.QuadPart) / static_cast<double>(freq.QuadPart); // 밀리초 단위로 변환
    // 프레임 종료 후 작업을 여기에 작성합니다.

    Update(); // 게임 업데이트 함수 호출
	ShowFPS(); // FPS를 출력하는 함수 호출
	Render(); // 렌더링 함수 호출
     
    // 예: 화면 업데이트, 렌더링 완료 등
}
void Start()
{
    QueryPerformanceFrequency(&freq);   // 해상도 받아오는 함수. 정밀 시간 연산에 사용.
	// 게임 시작 로직을 여기에 작성합니다.
}
void Update()
{
	// 게임 업데이트 로직을 여기에 작성합니다.
}
void Render()
{
	HDC hdc = GetDC(g_hWnd); // 현재 윈도우의 DC를 가져옵니다.
	RECT rect;
	GetClientRect(g_hWnd, &rect); // 윈도우의 클라이언트 영역을 가져옵니다.
	int width = rect.right - rect.left; // 클라이언트 영역의 너비
	int height = rect.bottom - rect.top; // 클라이언트 영역의 높이

	HDC memDC = CreateCompatibleDC(hdc); // 메모리 DC 생성
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height); // 메모리 DC에 사용할 비트맵 생성
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hBitmap); // 메모리 DC에 비트맵 선택
	// 메모리 DC에 그리기 작업을 수행합니다.
    //배경 색상
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); // 흰색 브러시 생성
	FillRect(memDC, &rect, hBrush); // 메모리 DC에 배경 색상 채우기
	// 브러시 해제
	DeleteObject(hBrush);

    //오브젝트 랜더링
    
    //실제 화면 랜더링
	BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY); // 메모리 DC의 내용을 화면에 복사


    //사용한 메모리 해제 작업.
	SelectObject(memDC, hOldBitmap); // 메모리 DC에서 이전 비트맵을 선택
	DeleteObject(hBitmap); // 비트맵 삭제
	DeleteDC(memDC); // 메모리 DC 삭제
	ReleaseDC(g_hWnd, hdc); // 윈도우 DC 해제
}
void ShowFPS()
{
    static double timeAccumulator = 0.0;
    timeAccumulator += deltaTime;

    double fps = 1.0 / deltaTime;

    // 디버그 출력
    wchar_t buffer[100];
    swprintf_s(buffer, 100, L"FPS : %.2f\n", fps);
    OutputDebugStringW(buffer);
    timeAccumulator = 0.0;

    // 창 제목에 FPS 표시
    swprintf_s(buffer, 100, L"GameEngine2DProject - FPS : %.2f", fps);
    SetWindowTextW(g_hWnd, buffer);
}

