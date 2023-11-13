#pragma once
#include"Pch.h"
#include"WinApp.h"
#include"LogManager.h"

class Input
{
public:


	static Input * GetInstance();

	static void Initialize();

	static void BeginFlame();

	bool PushKey(uint8_t keyNum);

	bool PushKeyPressed(uint32_t keyNum);

	static void NoneJoyState(XINPUT_STATE& state);

	bool GetJoystickState(XINPUT_STATE& state);

private:

	static void CreateKeybordDevice();

	ComPtr<IDirectInput8> directInput = nullptr;
	ComPtr<IDirectInputDevice8> keyboard = nullptr;

	BYTE keys[256] = {};
	BYTE preKeys[256] = {};
	XINPUT_STATE state_{};

	bool isInitialize=false;



	//0x80=�����Ă�����
	//0x00=�����ĂȂ����
	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;
};

