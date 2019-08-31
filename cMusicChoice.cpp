#include "cMusicChoice.h"
cMusicChoice::cMusicChoice()
{
	m_pSprite				= NULL;
	m_pSound				= NULL;
	m_vPos					= D3DXVECTOR3(550, 330, 0);
	m_pCursor				= NULL;
	m_pDialog				= NULL;
	m_pAnimate				= NULL;
	m_pMulti				= NULL;
	m_pDialog1				= NULL;
	m_pRank					= NULL;
}

cMusicChoice::~cMusicChoice()
{
	SAFE_DELETE(m_pSprite);
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pMulti);
	SAFE_DELETE(m_pDialog1);
	SAFE_DELETE(m_pRank);

}


HRESULT cMusicChoice::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{



	//////////////////////////////////////////////////////////////////////////
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/MusicChoice.Te");
		m_pSprite->Entry(L"res/te/example.te");
		m_pSprite->Entry(L"res/te/fade.Te");
		m_pSprite->Entry(L"res/te/CD.Te");
		m_pSprite->Entry(L"res/te/CD1.Te");
		m_pSprite->Entry(L"res/te/mouse_effect.te"); 
		m_pSprite->Entry(L"res/te/mouse_effect2.te");
		m_pSprite->Entry(L"res/te/drum_tutorial.te"); 
		m_pSprite->Entry(L"res/te/Dialog_number.Te");
		m_pSprite->Entry(L"res/te/Dialog_number1.Te");
		m_pSprite->Entry(L"res/te/rank_number.Te");
		m_pSprite->Entry(L"res/te/allow.Te");
		m_pSprite->Entry(L"res/te/wheel.Te");
		m_pSprite->Entry(L"res/te/ava.Te");
		m_pSprite->Entry(L"res/te/drumjust_n.Te");
		m_pSprite->Entry(L"res/te/drumjust_h.Te");
		m_pSprite->Entry(L"res/te/drumjust_e.Te");
		m_pSprite->Entry(L"res/te/tudrum.Te");
		m_pSprite->Entry(L"res/te/drumswagga_n.Te");
		m_pSprite->Entry(L"res/te/drumswagga_h.te"); 
		m_pSprite->Entry(L"res/te/drumswagga_e.te"); 
		m_pSprite->Entry(L"res/te/tubase.te");
		m_pSprite->Entry(L"res/te/baseswagga_n.te");
		m_pSprite->Entry(L"res/te/baseswagga_h.te");
		m_pSprite->Entry(L"res/te/baseswagga_e.te"); 
		m_pSprite->Entry(L"res/te/basejust_h.te");
		m_pSprite->Entry(L"res/te/basejust_e.te"); 
		m_pSprite->Entry(L"res/te/jembe just normal.te"); 
		m_pSprite->Entry(L"res/te/jembe just easy.te"); 
		m_pSprite->Entry(L"res/te/jembe swagga tu.te"); 
		m_pSprite->Entry(L"res/te/jembe swagga hard.te"); 
		m_pSprite->Entry(L"res/te/jembe swagga normal.te"); 
		m_pSprite->Entry(L"res/te/jembe swagga easy.te"); 
		m_pSprite->Entry(L"res/te/jembe just hard.te"); 
		m_pSprite->Entry(L"res/te/basejust_n.te"); 





	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate = new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"res/ta/mouse_effect.ta");
	}
	if(m_pMulti == NULL)
	{
		m_pMulti = new KGRenderMulti(m_pAnimate);
	}
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"swagga_sample",  L"/res/sound/Music/swagga_sample.wav");
		m_pSound->Entry(L"just_sample",  L"/res/sound/Music/just_sample.wav");
		m_pSound->Entry(L"practice_sample", L"/res/sound/Music/practice_sample.wav");

		//m_pSound->isPlay(L"swagga");
	}
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768),L"cursor01", L"cursor02",L"cursor01");
	}
	if(m_pDialog == NULL)
	{
		m_pDialog			= new KGDialog(m_pSprite, 0, this);
		m_pDialog->AddTimeBar(10, L"", D3DXVECTOR3(0, 0, 0), 0.5f);
		m_pDialog->AddButton(500,L"left",L"left",L"left",L"left",D3DXVECTOR3(-100,-100,0),true);
	}
	if(m_pDialog1 == NULL)
	{
		m_pDialog1   = new KGDialog(m_pSprite,0,0);
		m_pDialog1->AddNumber(100,L"Dnum_",D3DXVECTOR3(460,710,0),-25);
	}
	if(m_pRank == NULL)
	{
		m_pRank   = new cRank();
	}
	m_pDialog->GetTimeBar(10)->SetDisable(true);

	m_MusicState			= 0;
	m_Icheck				= 1; // 0 쉬움 1보통 2 어려움
	m_SelectCD				= 1;
	m_fFadeTime = 0;
	m_fAlpha = 0;
	m_iRank    = 0 ;
	m_iO		= 0;
	return S_OK;
}


HRESULT cMusicChoice::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pDialog1);
	return S_OK;
}


void cMusicChoice::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	SAFE_ONLOSTDEVICE(m_pDialog1);
}


void cMusicChoice::OnDestroyDevice(void* pUserContext)
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pMulti);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog1);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pRank);

}


void cMusicChoice::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	SAFE_ONFRAMEMOVE(m_pDialog);
	SAFE_ONFRAMEMOVE(m_pDialog1);
	if(m_SelectCD != 1)
		m_pDialog1->GetNumber(100)->SetVisible(true);
	else
		m_pDialog1->GetNumber(100)->SetVisible(false);
	m_pDialog1->GetNumber(100)->SetNumber(m_iRank);
	if(m_SelectCD != 1)
	{
		if(m_Icheck == 0)
			LEVEL = EASY;
		if(m_Icheck == 1)
			LEVEL = NORMAL;
		if(m_Icheck == 2)
			LEVEL = HARD;
	}
	if(PLAYCHOICE == DRUM)
	{
		switch(m_SelectCD)
		{
		case 2:
			{
				if(LEVEL == EASY)
				{
					m_pRank->Rank_Load(L"res/DRUMJUSTEASYRANK.txt",0);

				}
				if(LEVEL == NORMAL)
				{
					m_pRank->Rank_Load(L"res/DRUMJUSTNORMALRANK.txt",0);

				}
				if(LEVEL == HARD)
				{
					m_pRank->Rank_Load(L"res/DRUMJUSTHARDRANK.txt",0);

				}
				break;

			}
		case 0:
			{
				if(LEVEL == EASY)
				{
					m_pRank->Rank_Load(L"res/DRUMSWAGGAEASYRANK.txt",0);
				}
				if(LEVEL == NORMAL)
				{
					m_pRank->Rank_Load(L"res/DRUMSWAGGANORMALRANK.txt",0);
				}
				if(LEVEL == HARD)
				{
					m_pRank->Rank_Load(L"res/DRUMSWAGGAHARDRANK.txt",0);
				}
				break;


			}
		}
	}

	if(PLAYCHOICE == JEMBE)
	{
		switch(m_SelectCD)
		{
		case 2:
			{
				if(LEVEL == EASY)
				{
					m_pRank->Rank_Load(L"res/JEMBEJUSTEASYRANK.txt",0);

				}
				if(LEVEL == NORMAL)
				{
					m_pRank->Rank_Load(L"res/JEMBEJUSTNORMALRANK.txt",0);

				}
				if(LEVEL == HARD)
				{
					m_pRank->Rank_Load(L"res/JEMBEJUSTHARDRANK.txt",0);

				}
				break;

			}
		case 0:
			{
				if(LEVEL == EASY)
				{
					m_pRank->Rank_Load(L"res/JEMBESWAGGAEASYRANK.txt",0);
				}
				if(LEVEL == NORMAL)
				{
					m_pRank->Rank_Load(L"res/JEMBESWAGGANORMALRANK.txt",0);
				}
				if(LEVEL == HARD)
				{
					m_pRank->Rank_Load(L"res/JEMBESWAGGAHARDRANK.txt",0);
				}
				break;


			}
		}
	}
	if(PLAYCHOICE == BASE)
	{
		switch(m_SelectCD)
		{
		case 2:
			{
				if(LEVEL == EASY)
				{
					m_pRank->Rank_Load(L"res/BASEJUSTEASYRANK.txt",0);
				}
				if(LEVEL == NORMAL)
				{
					m_pRank->Rank_Load(L"res/BASEJUSTNORMALRANK.txt",0);

				}
				if(LEVEL == HARD)
				{
					m_pRank->Rank_Load(L"res/BASEJUSTHARDRANK.txt",0);

				}
				break;
			}
		case 0:
			{
				if(LEVEL == EASY)
				{
					m_pRank->Rank_Load(L"res/BASESWAGGAEASYRANK.txt",0);
				}
				if(LEVEL == NORMAL)
				{
					m_pRank->Rank_Load(L"res/BASESWAGGANORMALRANK.txt",0);
				}
				if(LEVEL == HARD)
				{
					m_pRank->Rank_Load(L"res/BASESWAGGAHARDRANK.txt",0);
				}
				break;
			}
		}
	}
	if(m_SelectCD == 1)
	{
		LEVEL = EASY;
	}
	if(m_SelectCD == 0)
	{
		m_pSound->Play(L"swagga_sample", false, 0, DSBPLAY_LOOPING);
		m_pSound->Stop(L"just_sample");
		m_pSound->Stop(L"practice_sample");

		//m_pSound->Stop(L"swagga"); // 튜토리얼때
	}
	if(m_SelectCD == 2) // 2가 저스트
	{
		m_pSound->Play(L"just_sample", false, 0, DSBPLAY_LOOPING);
		m_pSound->Stop(L"swagga_sample");
		m_pSound->Stop(L"practice_sample");

		//m_pSound->Stop(L"swagga"); // 튜토리얼때
	}
	if(m_SelectCD == 1) // 튜토리얼 
	{
		m_pSound->Play(L"practice_sample", false, 0, DSBPLAY_LOOPING);
		m_pSound->Stop(L"just_sample");
		m_pSound->Stop(L"swagga_sample");
		//m_pSound->Stop(L"swagga"); // 튜토리얼때
	}
	if(!m_pDialog->GetTimeBar(10)->GetDisable())
	{
		m_fFadeTime += fElapsedTime;
		if(m_fFadeTime > 0.000001f)
		{
			m_iO+=60;
			m_fFadeTime = 0;
		}

	}

	m_iRank    = m_pRank->m_Ranking[0].nRank;
	if(m_SelectCD == 1)
		m_iRank = 0;

}


void cMusicChoice::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));
	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{	// 1 = 튜톨  // 2 // 스웨거 ?  0// 저스트
		m_pSprite->Render(L"back", D3DXVECTOR3(0,0,0), D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"wheel",D3DXVECTOR3(250,-24,0), D3DXCOLOR(1,1,1,1));

		if(m_SelectCD == 0) // 저스트
		{
			if(LEVEL == EASY)
			{
				m_pSprite->Render(L"just-easy",D3DXVECTOR3(m_vPos.x, m_vPos.y,0),D3DXToRadian(m_iO),D3DXCOLOR(1,1,1,1));
				m_pSprite->Render(L"swagga-normal",D3DXVECTOR3(m_vPos.x-400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
				m_pSprite->Render(L"pr",D3DXVECTOR3(m_vPos.x+400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
			}
			if(LEVEL == NORMAL)
			{
				m_pSprite->Render(L"just-normal",D3DXVECTOR3(m_vPos.x, m_vPos.y,0),D3DXToRadian(m_iO),D3DXCOLOR(1,1,1,1));
				m_pSprite->Render(L"swagga-normal",D3DXVECTOR3(m_vPos.x-400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
				m_pSprite->Render(L"pr",D3DXVECTOR3(m_vPos.x+400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
			}
			if(LEVEL == HARD)
			{
				m_pSprite->Render(L"just-hard",D3DXVECTOR3(m_vPos.x, m_vPos.y,0),D3DXToRadian(m_iO),D3DXCOLOR(1,1,1,1));
				m_pSprite->Render(L"swagga-normal",D3DXVECTOR3(m_vPos.x-400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
				m_pSprite->Render(L"pr",D3DXVECTOR3(m_vPos.x+400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
			}
		}
		if(m_SelectCD == 1) // 튜톨
		{
			m_pSprite->Render(L"just-normal",D3DXVECTOR3(m_vPos.x-400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));
			m_pSprite->Render(L"swagga-normal",D3DXVECTOR3(m_vPos.x+400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
			m_pSprite->Render(L"pr",D3DXVECTOR3(m_vPos.x, m_vPos.y,0),D3DXToRadian(m_iO),D3DXCOLOR(1,1,1,1));
		}
		if(m_SelectCD == 2) // 
		{
			if(LEVEL == EASY)
			{
				m_pSprite->Render(L"swagga -easy",D3DXVECTOR3(m_vPos.x, m_vPos.y,0),D3DXToRadian(m_iO),D3DXCOLOR(1,1,1,1));
				m_pSprite->Render(L"just-normal",D3DXVECTOR3(m_vPos.x+400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
				m_pSprite->Render(L"pr",D3DXVECTOR3(m_vPos.x-400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
			}
			if(LEVEL == NORMAL)
			{
				m_pSprite->Render(L"swagga-normal",D3DXVECTOR3(m_vPos.x, m_vPos.y,0),D3DXToRadian(m_iO),D3DXCOLOR(1,1,1,1));
				m_pSprite->Render(L"just-normal",D3DXVECTOR3(m_vPos.x+400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
				m_pSprite->Render(L"pr",D3DXVECTOR3(m_vPos.x-400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
			}
			if(LEVEL == HARD)
			{
				m_pSprite->Render(L"swagga-hard",D3DXVECTOR3(m_vPos.x, m_vPos.y,0),D3DXToRadian(m_iO),D3DXCOLOR(1,1,1,1));
				m_pSprite->Render(L"just-normal",D3DXVECTOR3(m_vPos.x+400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
				m_pSprite->Render(L"pr",D3DXVECTOR3(m_vPos.x-400, m_vPos.y,0),D3DXCOLOR(1,1,1,1));	
			}

		}


		switch(PLAYCHOICE)
		{
		case DRUM:
		{
		switch(m_SelectCD)
		{
		case 0:
		{
		if(LEVEL == EASY)
		{
		m_pSprite->Render(L"drumjust_e",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == NORMAL)
		{
		m_pSprite->Render(L"drumjust_n",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == HARD)
		{
		m_pSprite->Render(L"drumjust_h",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		break;
		}
		case 2:
		{
		if(LEVEL == EASY)
		{
		m_pSprite->Render(L"drumswagga_e",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == NORMAL)
		{
		m_pSprite->Render(L"drumswagga_n",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == HARD)
		{
		m_pSprite->Render(L"drumswagga_h",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		break;
		}
		case 1:
		{
		m_pSprite->Render(L"tudrum",D3DXVECTOR3(0,580,0), D3DXCOLOR(1,1,1,1));
		break;
		}
		}
		break;
		}
		break;
		case JEMBE:
		{
		switch(m_SelectCD)
		{
		case 0:
		{
		if(LEVEL == EASY)
		{
		m_pSprite->Render(L"jembe just easy",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == NORMAL)
		{
		m_pSprite->Render(L"jembe just normal",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == HARD)
		{
		m_pSprite->Render(L"jembe just hard",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		break;
		}
		case 2:
		{
		if(LEVEL == EASY)
		{
		m_pSprite->Render(L"jembe swagga easy",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == NORMAL)
		{
		m_pSprite->Render(L"jembe swagga normal",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == HARD)
		{
		m_pSprite->Render(L"jembe swagga hard",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		break;
		}
		case 1:
		{
		m_pSprite->Render(L"jembe tu",D3DXVECTOR3(0,580,0), D3DXCOLOR(1,1,1,1));
		break;
		}
		}
		break;
		}
		break;
		case BASE:
		{
		switch(m_SelectCD)
		{
		case 0:
		{
		if(LEVEL == EASY)
		{
		m_pSprite->Render(L"basejust_e",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == NORMAL)
		{
		m_pSprite->Render(L"BASE JUST NORMAL",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == HARD)
		{
		m_pSprite->Render(L"basejust_h",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		break;
		}
		case 2:
		{
		if(LEVEL == EASY)
		{
		m_pSprite->Render(L"baseswagga_e",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == NORMAL)
		{
		m_pSprite->Render(L"baseswagga_n",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		if(LEVEL == HARD)
		{
		m_pSprite->Render(L"baseswagga_h",D3DXVECTOR3(0,575,0), D3DXCOLOR(1,1,1,1));
		}
		break;
		}
		case 1:
		{
		m_pSprite->Render(L"tubase",D3DXVECTOR3(0,580,0), D3DXCOLOR(1,1,1,1));
		break;
		}
		}
		break;
		}
		break;
		}
		if(m_SelectCD != 1)
		{
			if(LEVEL ==EASY )
			{
				m_pSprite->Render(L"easy",D3DXVECTOR3(460,380,0), D3DXCOLOR(1,1,1,1));
			}
			if(LEVEL == NORMAL)
			{
				m_pSprite->Render(L"normal",D3DXVECTOR3(460,380,0), D3DXCOLOR(1,1,1,1));
			}
			if(LEVEL == HARD)
			{
				m_pSprite->Render(L"hard",D3DXVECTOR3(460,380,0), D3DXCOLOR(1,1,1,1));
			}
		}
		SAFE_ONFRAMERENDER(m_pDialog);
		SAFE_ONFRAMERENDER(m_pDialog1);
		SAFE_ONFRAMERENDER(m_pMulti);
		SAFE_ONFRAMERENDER(m_pCursor);

		m_pSprite->Render(L"black", D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,m_fAlpha));
		V(pd3dDevice->EndScene());
	}
}


void cMusicChoice::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{

	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case VK_RIGHT:
		{
			if(!m_pDialog->GetTimeBar(10)->GetDisable()) return;
			m_SelectCD +=1;
			if(m_SelectCD > 2)
				m_SelectCD = 0;
			m_Icheck = 1;
			break;
		}
	case VK_LEFT:
		{
			if(!m_pDialog->GetTimeBar(10)->GetDisable()) return;

			m_SelectCD -=1;
			if(m_SelectCD < 0)
				m_SelectCD = 2;
			m_Icheck = 1;
			break;
		}
	case VK_UP:
		{
			if(!m_pDialog->GetTimeBar(10)->GetDisable()) return;
			if(m_SelectCD != 1)
			{
				m_Icheck +=1;
				if(m_Icheck > 2)
					m_Icheck = 0;
			}
			break;
		}
	case VK_DOWN:
		{
			if(!m_pDialog->GetTimeBar(10)->GetDisable()) return;
			if(m_SelectCD != 1)
			{
				m_Icheck -=1;
				if(m_Icheck < 0)
					m_Icheck = 2;
			}
			break;

		}
	case VK_RETURN:

		if(m_pDialog->GetTimeBar(10)->GetDisable())
		{
			m_pDialog->GetTimeBar(10)->Reset();
		}
		break;
	}


}


void cMusicChoice::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
						   bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	m_vMPos.x = xPos;
	m_vMPos.y = yPos;
	SAFE_ONMOUSE(m_pDialog);

	SAFE_ONMOUSE(m_pCursor);
	//KGOutputDebugStringW(L"%f %f\n",m_vMPos.x,m_vMPos.y);
	if(nMouseWheelDelta > 0)
	{
		for(int i=0;i<=50;i++)
		{
			m_dcheck[i] = L_Inter(-100,0,i*0.01);
		}
		m_SelectCD +=1;
		if(m_SelectCD)
			m_SelectCD;
		if(m_SelectCD > 2)
			m_SelectCD = 0;
		m_Icheck = 1;


	}
	if(nMouseWheelDelta < 0)
	{
		m_SelectCD -=1;
		if(m_SelectCD)
			m_SelectCD;
		if(m_SelectCD < 0)
			m_SelectCD = 2;
		m_Icheck = 1;

	}
	if(bButtonDown)
	{
		m_pMulti->Entry(L"mouse_effect", D3DXVECTOR3(xPos-100,yPos-60,0), true, 1); // 임펙트이다.

		if(bLeftButtonDown)
		{
			if(m_vMPos.x > 450 && m_vMPos.x < 680 &&  m_vMPos.y  > 155 && m_vMPos.y  < 480)
			{
				if(m_pDialog->GetTimeBar(10)->GetDisable())
				{
					m_pDialog->GetTimeBar(10)->Reset();
				}
			}
		}
		if(bRightButtonDown)
		{

		}
	}
}


LRESULT cMusicChoice::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	SAFE_ONMSGPROC(m_pDialog);
	return uMsg;
}
double cMusicChoice:: L_Inter(double x1, double x2, double t)
{
	return (x1+((x2-x1)*t));
}
void cMusicChoice::OnEvent(UINT id, int xPos, int yPos)
{
	switch(id)
	{

	case 500:
		cMain()->Trans(L"mode");
		break;
	case 10:
		switch(m_SelectCD)
		{
		case 0:
			MUSIC = SWAGGA;				
			if(PLAYCHOICE == DRUM)		
				cMain()->Trans(L"drum");
			if(PLAYCHOICE == JEMBE)
				cMain()->Trans(L"jembe");
			if(PLAYCHOICE == BASE)
				cMain()->Trans(L"base");
			break;
		case 2:
			MUSIC = JUST;			
			if(PLAYCHOICE == DRUM)		
				cMain()->Trans(L"drum");
			if(PLAYCHOICE == JEMBE)
				cMain()->Trans(L"jembe");
			if(PLAYCHOICE == BASE)
				cMain()->Trans(L"base");
			break;
		case  1:
			MUSIC =PRACTICE;
			if(PLAYCHOICE == DRUM)		
				cMain()->Trans(L"drum"); 
			if(PLAYCHOICE == JEMBE)
				cMain()->Trans(L"jembe");
			if(PLAYCHOICE == BASE)
				cMain()->Trans(L"base"); 
			break;
		}
	}
}


