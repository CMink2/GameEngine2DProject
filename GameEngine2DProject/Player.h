#pragma once
#include "GameObject.h"
#include <Windows.h>
class Player : public GameObject
{
public:
	// 플레이어 클래스는 GameObject를 상속받아 게임 오브젝트의 기능을 확장합니다.
	int x; // 플레이어의 x 좌표
	int y; // 플레이어의 y 좌표
	int width; // 플레이어의 너비
	int height; // 플레이어의 높이

	Player() = default; // 기본 생성자
	~Player() override = default; // 소멸자
	void Update() override {
		// 플레이어 업데이트 로직 구현
		x+=1; // 예시로 x 좌표를 증가시키는 로직
	}
	void Render(HDC hdc) override {
		// 플레이어 렌더링 로직 구현
		Rectangle(hdc, x, y, x + width, y + height); // 플레이어를 사각형으로 그립니다.
	}
};

