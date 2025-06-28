#pragma once
#include "GameObject.h"
#include <Windows.h>
class Player : public GameObject
{
public:
	// �÷��̾� Ŭ������ GameObject�� ��ӹ޾� ���� ������Ʈ�� ����� Ȯ���մϴ�.
	int x; // �÷��̾��� x ��ǥ
	int y; // �÷��̾��� y ��ǥ
	int width; // �÷��̾��� �ʺ�
	int height; // �÷��̾��� ����

	Player() = default; // �⺻ ������
	~Player() override = default; // �Ҹ���
	void Update() override {
		// �÷��̾� ������Ʈ ���� ����
		x+=1; // ���÷� x ��ǥ�� ������Ű�� ����
	}
	void Render(HDC hdc) override {
		// �÷��̾� ������ ���� ����
		Rectangle(hdc, x, y, x + width, y + height); // �÷��̾ �簢������ �׸��ϴ�.
	}
};

