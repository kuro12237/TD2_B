#pragma once

#include<format>
#include<string>
#include<wrl.h>
#include<cassert>
#include<list>
#include<vector>
#include<numbers>
#include<fstream>
#include<sstream>
#include<chrono>
#include<random>
#include<map>

#include<Windows.h>
#pragma comment(lib,"winmm.lib")

#include"imgui.h"
#include"imgui_impl_dx12.h"
#include"imgui_impl_win32.h"

#pragma region DirectX

#include <dxgidebug.h>
#include <dxcapi.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>


#define DIRECTINPUT_VERSION 0x0800//DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"dinput8.lib")

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")
#include"DirectXTex/DirectXTex.h"

#pragma endregion

#pragma region XAudio
#include<xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

#pragma endregion

using Microsoft::WRL::ComPtr;
using namespace std;
using namespace std::chrono;

#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"

#include"Matrix2x2.h"
#include"Matrix3x3.h"
#include"Matrix4x4.h"

