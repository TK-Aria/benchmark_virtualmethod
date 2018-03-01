//=============================================================================
//
// 入力処理 [input.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _INPUTDEVICE_H_
#define _INPUTDEVICE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX		(256)	// キー最大数

//*********************************************************
// 入力クラス
//*********************************************************
class CInputDevice
{
public:

	CInputDevice( );
	virtual ~CInputDevice( );

	virtual HRESULT Init( HINSTANCE hInst, HWND hWnd );
	virtual void Uninit( void );
	virtual void Update( void ) = 0;		// ---> 純粋仮想関数化


protected:
	static LPDIRECTINPUT8 m_pDInput;		// DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8  m_pDIDevice;		// Deviceオブジェクト(入力に必要)
};

using namespace std;

#endif