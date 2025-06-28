#pragma once
#include <Windows.h>
#include <vector>
class GameObject
{
public:
	virtual void Update() = 0; // ���� ������Ʈ ������Ʈ �Լ�	
	virtual void Render(HDC hdc) = 0; // ���� ������Ʈ ������ �Լ�
	virtual ~GameObject() = default; // ���� �Ҹ���
};

// ���� ������Ʈ�� �⺻ �������̽��� �����մϴ�.
// Update() �Լ��� ���� ������Ʈ�� ���¸� ������Ʈ�ϴ� �� ���Ǹ�,
// Render() �Լ��� ���� ������Ʈ�� ȭ�鿡 �������ϴ� �� ���˴ϴ�.
// ���� �Ҹ��ڸ� ����Ͽ� �Ļ� Ŭ�������� �����ϰ� �Ҹ��� �� �ֵ��� �մϴ�.

class GameObjectManager
{
private:
	std::vector<GameObject*> gameObjects; // ���� ������Ʈ�� �����ϴ� ����
public:
	void AddGameObject(GameObject* obj) {
		gameObjects.push_back(obj); // ���� ������Ʈ�� �߰��մϴ�.
	}
	void UpdateAll() {
		for (GameObject* obj : gameObjects) {
			obj->Update(); // ��� ���� ������Ʈ�� ������Ʈ�մϴ�.
		}
	}
	void RenderAll(HDC hdc) {
		for (GameObject* obj : gameObjects) {
			obj->Render(hdc); // ��� ���� ������Ʈ�� �������մϴ�.
		}
	}
	void Clear() {
		for (GameObject* obj : gameObjects) {
			delete obj; // ���� ������Ʈ �޸� ����
		}
		gameObjects.clear(); // ���� �ʱ�ȭ
	}
};