#pragma once
#include <Windows.h>
#include <vector>
class GameObject
{
public:
	virtual void Update() = 0; // 게임 오브젝트 업데이트 함수	
	virtual void Render(HDC hdc) = 0; // 게임 오브젝트 렌더링 함수
	virtual ~GameObject() = default; // 가상 소멸자
};

// 게임 오브젝트의 기본 인터페이스를 정의합니다.
// Update() 함수는 게임 오브젝트의 상태를 업데이트하는 데 사용되며,
// Render() 함수는 게임 오브젝트를 화면에 렌더링하는 데 사용됩니다.
// 가상 소멸자를 사용하여 파생 클래스에서 안전하게 소멸할 수 있도록 합니다.

class GameObjectManager
{
private:
	std::vector<GameObject*> gameObjects; // 게임 오브젝트를 저장하는 벡터
public:
	void AddGameObject(GameObject* obj) {
		gameObjects.push_back(obj); // 게임 오브젝트를 추가합니다.
	}
	void UpdateAll() {
		for (GameObject* obj : gameObjects) {
			obj->Update(); // 모든 게임 오브젝트를 업데이트합니다.
		}
	}
	void RenderAll(HDC hdc) {
		for (GameObject* obj : gameObjects) {
			obj->Render(hdc); // 모든 게임 오브젝트를 렌더링합니다.
		}
	}
	void Clear() {
		for (GameObject* obj : gameObjects) {
			delete obj; // 게임 오브젝트 메모리 해제
		}
		gameObjects.clear(); // 벡터 초기화
	}
};