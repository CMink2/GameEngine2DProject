#pragma once
#include "GameObject.h"
#include "BitMapManager.h"
#include <Windows.h>

#define BITMAP_PLAYER_PATH L"BitMap\\Player\\player.bmp"

class Player : public GameObject
{
public:
	int x, y, width, height;
	HBITMAP hBitmap;

	Player() :
		x(100), y(100), width(50), height(50), hBitmap(nullptr)
	{
		std::wstring bmpPath = BitMapManager::GetFullPathFromExe(BITMAP_PLAYER_PATH);

		// 디버깅 경로 출력
		wchar_t debugMsg[512];
		swprintf_s(debugMsg, 512, L"[DEBUG] Full Path: %s\n", bmpPath.c_str());
		OutputDebugStringW(debugMsg);

		if (!BitMapManager::GetInstance().HasBitmap("player"))
		{
			BitMapManager::GetInstance().LoadBitmap("player", bmpPath);
		}

		hBitmap = BitMapManager::GetInstance().GetBitmap("player");
		if (!hBitmap) {
			DWORD err = GetLastError();
			swprintf_s(debugMsg, 512, L"Failed to load bitmap. Error code: %lu\n", err);
			OutputDebugStringW(debugMsg);
			assert(false && "Failed to load bitmap!");
		}
	}

	~Player() override = default;

	void Update() override {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) x -= 1;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) x += 1;
		if (GetAsyncKeyState(VK_UP) & 0x8000) y -= 1;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) y += 1;
	}

	void Render(HDC hdc) override {
		if (hBitmap) {
			HDC bmpDC = CreateCompatibleDC(hdc);
			HBITMAP oldBmp = (HBITMAP)SelectObject(bmpDC, hBitmap);

			BitBlt(hdc, x, y, width, height, bmpDC, 0, 0, SRCCOPY);

			SelectObject(bmpDC, oldBmp);
			DeleteDC(bmpDC);
		}
		else {
			Rectangle(hdc, x, y, x + width, y + height);
		}
	}
};
