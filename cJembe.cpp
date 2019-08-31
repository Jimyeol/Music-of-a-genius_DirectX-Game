#include "cJembe.h"
cJembe::cJembe()
{
	m_pSound				= NULL;
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
	m_vPos					= D3DXVECTOR3(0,0,0);
	m_Node					= NULL;
	m_pDialog				= NULL;
	m_pCursor				= NULL;
	m_pDialog1				= NULL;
	m_pDialog2				= NULL;

}
cJembe::~cJembe()
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_Node);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pDialog1);
	SAFE_DELETE(m_pDialog2);
	
}
void cJembe::OnDestroyDevice(void* pUserContext)
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	//JembeSound->drop();
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_Node);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog1);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pCursor);
}


HRESULT cJembe::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	if(m_pSprite == NULL) 
	{
		m_pSprite		= new KGSprite(pd3dDevice);

		m_pSprite->Entry(L"res/te/node.Te");
		m_pSprite->Entry(L"res/te/jembe_miss_effect.te");
		m_pSprite->Entry(L"res/te/jembe_effect_red.te");
		m_pSprite->Entry(L"res/te/jembe_effect_blue.te");
		m_pSprite->Entry(L"res/te/CGEffect.te");
		m_pSprite->Entry(L"res/te/MPEffect.te");
		m_pSprite->Entry(L"res/te/mouse_effect.te"); 
		m_pSprite->Entry(L"res/te/mouse_effect2.te");
		m_pSprite->Entry(L"res/te/jembe_back.te");
		m_pSprite->Entry(L"res/te/jembe_colorback.te");
		m_pSprite->Entry(L"res/te/Combo.te");
		m_pSprite->Entry(L"res/te/help_game.te");
		m_pSprite->Entry(L"res/te/Dialog_number.te");
		m_pSprite->Entry(L"res/te/RankInterface.te");
		m_pSprite->Entry(L"res/te/jembe.te");
		m_pSprite->Entry(L"res/te/number.te");
		m_pSprite->Entry(L"res/te/score.te");
		m_pSprite->Entry(L"res/te/example.te");
		m_pSprite->Entry(L"res/te/love.te");
		m_pSprite->Entry(L"res/te/pause.te");
		m_pSprite->Entry(L"res/te/to_mode.te");
		m_pSprite->Entry(L"res/te/return.te");
		m_pSprite->Entry(L"res/te/log.te");
		m_pSprite->Entry(L"res/te/logg.te");
		m_pSprite->Entry(L"res/te/Dialog_number.Te");
		

	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate		= new KGAnimate(m_pSprite);

		m_pAnimate->Entry(L"res/ta/jembe_effect_red.ta");
		m_pAnimate->Entry(L"res/ta/jembe_effect_blue.ta");
		m_pAnimate->Entry(L"res/ta/jembe_miss_effect.ta");
		m_pAnimate->Entry(L"res/ta/mouse_effect.ta");
		m_pAnimate->Entry(L"res/ta/Effect.ta");
		m_pAnimate->Entry(L"res/ta/Combo.ta");
	}
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());

	}
	if(m_pDialog == NULL)
	{
		m_pDialog		= new KGDialog(m_pSprite, NULL, NULL);
		m_pDialog->AddNumber(1, L"jembe_", D3DXVECTOR3(1030, 740, 0),-10,DT_RIGHT);
		m_pDialog->AddNumber(2, L"Dnum_", D3DXVECTOR3(640, 630, 0),-25,DT_RIGHT);
		m_pDialog->AddNumber(3, L"Dnum_", D3DXVECTOR3(640, 700, 0),-25,DT_RIGHT);
	

	}
	if(m_pDialog1 == NULL)
	{
		m_pDialog1 = new KGDialog(m_pSprite, NULL, this);
		m_pDialog1->AddButton(10,L"to_mode",L"to_mode_click",L"to_mode_over",L"to_mode",D3DXVECTOR3(300,470,0),true);
		m_pDialog1->AddButton(11,L"return",L"return_click",L"return_over",L"return",D3DXVECTOR3(300,240,0),true);
		m_pDialog1->SetVisible(false);
	}
	if(m_pDialog2 == NULL)
	{
		m_pDialog2 = new KGDialog(m_pSprite, NULL, this);
		m_pDialog2->SetSprite(L"pause",D3DXVECTOR3(225,50,0),D3DXCOLOR(1,1,1,1));
		m_pDialog2->SetVisible(false);
	}
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768),L"cursor_jembe", L"cursor_jembe1",L"cursor_jembe1");
	}
	if(m_Node ==NULL)
	{
		m_Node = new cJembeNode(m_pAnimate,m_pSound,m_pDialog);
	}
	SCORE					= 0;  // 전역변수 인데 이 두개는 모든것에서도 써야함
	MAXPERFECT				= 0;
	MAXGOOD					= 0;
	MAXMISS					= 0;
	MAXCOMBO				= 0;
	NOWNODE					= 0;
	MAXNODE					= 0;
	AIPHABAR				= 1;
	m_bPause				= false;

	//m_Node->OnCreateDevice(pd3dDevice,pBackBufferSurfaceDesc, pUserContext);
	return S_OK;
}
HRESULT cJembe::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pDialog1);
	return S_OK;
}
void cJembe::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	SAFE_ONLOSTDEVICE(m_pDialog1);

}

void cJembe::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	if(m_bPause == false)
	{
		SAFE_ONFRAMEMOVE(m_Node);
	}
	SAFE_ONFRAMEMOVE(m_pDialog);
	SAFE_ONFRAMEMOVE(m_pDialog1);
	

}

void cJembe::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;
	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0));
	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		SAFE_ONFRAMERENDER(m_Node);
		if(AIPHABAR > 0)
		{		
			SAFE_ONFRAMERENDER(m_pDialog);
			SAFE_ONFRAMERENDER(m_pDialog2);
			SAFE_ONFRAMERENDER(m_pDialog1);

		}
		SAFE_ONFRAMERENDER(m_pCursor);

		V(pd3dDevice->EndScene());
	}

}

void cJembe::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	SAFE_ONKEYBOARD(m_pDialog);
	SAFE_ONKEYBOARD(m_pDialog1);
	SAFE_ONKEYBOARD(m_Node);
	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case VK_ESCAPE: // esc키로
		{
			if(!m_bPause)
			{
				cMain()->JembeSound->setIsPaused(true);
				m_bPause = true;
				m_pDialog2->SetVisible(true);
				m_pDialog1->SetVisible(true);
			}
			break;
		}
	}

}


void cJembe::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					 bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	SAFE_ONMOUSE(m_pDialog);
	SAFE_ONMOUSE(m_pDialog1);
	if(m_bPause == false)
	{
		SAFE_ONMOUSE(m_Node);
	}
	SAFE_ONMOUSE(m_pCursor);
}


LRESULT cJembe::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	SAFE_ONMSGPROC(m_pDialog);
	SAFE_ONMSGPROC(m_pDialog1);
	return uMsg;
}
void cJembe::OnEvent(UINT id, int xPos, int yPos)
{
	switch(id)
	{
	case 10:
		cMain()->JembeSound->stop();
		cMain()->Trans(L"mode");
		break;
	case 11:
		m_bPause = false;
		cMain()->JembeSound->setIsPaused(false);
		m_pDialog2->SetVisible(false);
		m_pDialog1->SetVisible(false);
		break;
	}
}