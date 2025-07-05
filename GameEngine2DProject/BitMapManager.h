#pragma once
#include <map>
#include <Windows.h>
#include <string>
#include <assert.h>
#include <fstream>

class BitMapManager
{
private:
	std::map<std::string, HBITMAP> bitmaps_map;
	BitMapManager() = default;
	~BitMapManager()
	{
		for (auto& pair : bitmaps_map)
			DeleteObject(pair.second);
		bitmaps_map.clear();
	}

public:
	static BitMapManager& GetInstance()
	{
		static BitMapManager instance;
		return instance;
	}

	void LoadBitmap(const std::string& key, const std::wstring& filePath)
	{
		// 디버깅 경로 출력
		OutputDebugStringW(L"[DEBUG] LoadBitmap 호출\n");
		OutputDebugStringW(filePath.c_str());
		OutputDebugStringW(L"\n");

		CheckBitmapFile(filePath);

		HBITMAP bitmap = (HBITMAP)LoadImageW(NULL, filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (!bitmap) {
			DWORD err = GetLastError();
			wchar_t msg[256];
			swprintf_s(msg, 256, L"Failed to load bitmap. Error code: %lu\n", err);
			OutputDebugStringW(msg);
			MessageBoxW(nullptr, msg, L"Bitmap Load Error", MB_OK);
			assert(false && "Failed to load bitmap!");
		}
		else {
			AddBitmap(key, bitmap);
		}
	}

	void AddBitmap(const std::string& key, HBITMAP bitmap)
	{
		if (HasBitmap(key)) {
			DeleteObject(bitmaps_map[key]);
		}
		bitmaps_map[key] = bitmap;
	}

	HBITMAP GetBitmap(const std::string& key)
	{
		auto it = bitmaps_map.find(key);
		return (it != bitmaps_map.end()) ? it->second : nullptr;
	}

	bool HasBitmap(const std::string& key)
	{
		return bitmaps_map.find(key) != bitmaps_map.end();
	}

	static std::wstring GetFullPathFromExe(const std::wstring& relativePath)
	{
		wchar_t exePath[MAX_PATH] = { 0 };
		GetModuleFileNameW(NULL, exePath, MAX_PATH);

		wchar_t* lastSlash = wcsrchr(exePath, L'\\');
		if (lastSlash) *(lastSlash + 1) = L'\0';

		std::wstring fullPath = exePath;
		fullPath += relativePath;

		return fullPath;
	}

	void CheckBitmapFile(const std::wstring& filePath)
	{
		std::ifstream ifs(filePath);
		if (!ifs) {
			OutputDebugStringW(L"[DEBUG] 파일 존재하지 않음!\n");
			MessageBoxW(nullptr, filePath.c_str(), L"파일 없음!", MB_OK);
		}
		else {
			OutputDebugStringW(L"[DEBUG] 파일 존재 확인 완료!\n");
		}
		ifs.close();
	}
};
