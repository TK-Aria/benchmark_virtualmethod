//=============================================================================
//
// 入力処理 [input.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "inputdevice.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	COUNT_WAIT_REPEAT	(20)	// リピート待ち時間

//*****************************************************************************
// 静的変数
//*****************************************************************************
LPDIRECTINPUT8	CInputDevice::m_pDInput = NULL;	// DirectInputオブジェクト

//=============================================================================
// CInputDeviceコンストラスタ
//=============================================================================
CInputDevice::CInputDevice()
{
	m_pDIDevice = NULL;
}

//=============================================================================
// CInputDeviceデストラスタ
//=============================================================================
CInputDevice::~CInputDevice()
{

}

//=============================================================================
// 入力処理の初期化処理
//=============================================================================
HRESULT CInputDevice::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr = S_FALSE;

	// DirectInputオブジェクトの作成
	if(!m_pDInput)
	{
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&m_pDInput, NULL);
	}

	return hr;
}

// INPUT_DEVICEの初期化処理
HRESULT CInputDevice::InitSingleDevice( HINSTANCE hInstance, HWND hWnd )
{

	HRESULT hr = S_FALSE;

	// DirectInputオブジェクトの作成
	if(!m_pDInput)
	{
		hr = DirectInput8Create( hInstance, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&m_pDInput, NULL);
	}

	return hr;

}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
#if 0	// ---> 純粋仮想関数化
HRESULT CInputDevice::Update(void)
{
	return S_OK;
}
#endif

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void CInputDevice::Uninit(void)
{
	if(m_pDIDevice)
	{// デバイスオブジェクトの開放
		m_pDIDevice->Unacquire();

		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}

	if(m_pDInput)
	{// DirectInputオブジェクトの開放
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

// 入力処理の終了処理
void CInputDevice::UninitSingleDevice( void )
{
	
	if(m_pDInput)
	{// DirectInputオブジェクトの開放
		m_pDInput->Release();
		m_pDInput = NULL;
	}

}

// INPUT_DEVICEの取得
LPDIRECTINPUT8 CInputDevice::GetInputDevice( void )
{

	return m_pDInput;

}
