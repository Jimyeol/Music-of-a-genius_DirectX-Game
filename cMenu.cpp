#include "cMenu.h"

cMenu::cMenu()
{
	m_pSprite				= NULL;
	m_pDialog				= NULL;
	m_pDialog1				= NULL;
	m_pDialog2				= NULL;
	m_pdrum					= NULL;
	m_pSound				= NULL;
	m_pCursor				= NULL;
	m_pAnimate				= NULL;
	m_pbase					= NULL;
	m_pMulti				= NULL;
	m_pRank					= NULL;
	m_pDialog_Rank			= NULL;
	m_pG_Rank				= NULL;
	m_pRank_check			= NULL;
	m_pjembe				= NULL;
	m_pFont					= NULL;
	m_ok						= NULL;
	//m_name						= NULL;

}
cMenu::~cMenu()
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog1);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pdrum);
	SAFE_DELETE(m_pbase);
	SAFE_DELETE(m_pMulti);
	SAFE_DELETE(m_pRank);
	SAFE_DELETE(m_pDialog_Rank);
	SAFE_DELETE(m_pG_Rank);
	SAFE_DELETE(m_pRank_check);
	SAFE_DELETE(m_pjembe);
	SAFE_DELETE(m_ok);
	//SAFE_DELETE(m_name);
}
HRESULT cMenu::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pFont == NULL)
	{
		m_pFont				= new KGFont(pd3dDevice);
		m_pFont->Entry(1, L"고딕", 12, 6);
		m_pFont->Entry(2, L"../res/font/K_Damage.TTF", L"휴먼태가람체", 40, 20);
	}
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"menu", L"/res/sound/Music/MainMenuSound.wav");
	}
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/Menu.Te");
		m_pSprite->Entry(L"res/te/Menu_Check.Te");
		m_pSprite->Entry(L"res/te/fade.Te");
		m_pSprite->Entry(L"res/te/mouse_effect.te"); 
		m_pSprite->Entry(L"res/te/mouse_effect2.te");
		m_pSprite->Entry(L"res/te/example.te");
		m_pSprite->Entry(L"res/te/help.Te");
		m_pSprite->Entry(L"res/te/how.Te");
		m_pSprite->Entry(L"res/te/credit.Te");
		m_pSprite->Entry(L"res/te/base_help.Te");
		m_pSprite->Entry(L"res/te/drum_help.Te");
		m_pSprite->Entry(L"res/te/Dialog_number.Te");
		m_pSprite->Entry(L"res/te/ranking.Te");
		m_pSprite->Entry(L"res/te/ranking_info.Te");
		m_pSprite->Entry(L"res/te/ranking_lnfo2.Te");
		m_pSprite->Entry(L"res/te/Dialog_number1.Te");
		m_pSprite->Entry(L"res/te/Dialog_number.Te");
		m_pSprite->Entry(L"res/te/rank_number.Te");
		m_pSprite->Entry(L"res/te/example.Te");
		m_pSprite->Entry(L"res/te/jembe_help.Te");
		m_pSprite->Entry(L"res/te/allow.Te");
		m_pSprite->Entry(L"res/te/menu_check1.Te");



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
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768),L"cursor01", L"cursor02",L"cursor02");
	}
	if(m_pDialog == NULL)
	{
		m_pDialog			= new KGDialog(m_pSprite, 0, this);
		m_pDialog->AddButton(BT_GAME, L"St", L"St_ok", L"St_check", L"St", D3DXVECTOR3(595, 205, 0),true);
		m_pDialog->AddButton(BT_RANK,L"Rank", L"Rank_ok", L"Rank_check", L"Rank", D3DXVECTOR3(555, 300, 0),true);

		m_pDialog->AddButton(BT_HELP, L"He", L"He_ok", L"He_check", L"He", D3DXVECTOR3(515, 395, 0),true);
		m_pDialog->AddButton(BT_CREATE, L"Cr", L"Cr_ok", L"Cr_check",L"Cr", D3DXVECTOR3(475, 490, 0),true);
		m_pDialog->AddButton(BT_QUIT, L"Qu", L"Qu_ok", L"Qu_check", L"Qu", D3DXVECTOR3(435, 585, 0),true);
		m_pDialog->AddTimeBar(TM_FADE, L"", D3DXVECTOR3(0, 0, 0), 0.2f);

	}
	if(m_pDialog1 == NULL)
	{
		m_pDialog1			= new KGDialog(m_pSprite, 0, this);
		m_pDialog1->SetSprite(L"test",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		m_pDialog1->SetSprite(L"How",D3DXVECTOR3(512,170,0),D3DXCOLOR(1,1,1,1));
		m_pDialog1->AddButton(10, L"drum", L"Drum_click", L"drum_over", L"drum", D3DXVECTOR3(400, 250, 0),true);
		m_pDialog1->AddButton(11, L"Jembe", L"Jembe_click", L"Jembe_over", L"Jembe", D3DXVECTOR3(400, 400, 0),true);
		m_pDialog1->AddButton(12, L"Base", L"base_click", L"Base_over",L"Base", D3DXVECTOR3(400, 550, 0),true);
		m_pDialog1->AddButton(200,L"left",L"left",L"left",L"left",D3DXVECTOR3(0,480,0),true);
		m_pDialog1->SetVisible(false);
	}
	if(m_pDialog_Rank == NULL)
	{
		m_pDialog_Rank = new KGDialog(m_pSprite,0,this);
		m_pDialog_Rank->SetSprite(L"ranking",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		m_pDialog_Rank->AddButton(20, L"drum", L"Drum_click", L"drum_over", L"drum", D3DXVECTOR3(400, 250, 0),true);
		m_pDialog_Rank->AddButton(21, L"Jembe", L"Jembe_click", L"Jembe_over", L"Jembe", D3DXVECTOR3(400, 400, 0),true);
		m_pDialog_Rank->AddButton(22, L"Base", L"base_click", L"Base_over",L"Base", D3DXVECTOR3(400, 550, 0),true);
		m_pDialog_Rank->AddButton(300,L"left",L"left",L"left",L"left",D3DXVECTOR3(0,480,0),true);

		m_pDialog_Rank->SetVisible(false);
	}
	if(m_pG_Rank == NULL)
	{
		m_pG_Rank =  new KGDialog(m_pSprite,0,this);
		m_pG_Rank->SetSprite(L"ranking",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		m_pG_Rank->AddButton(30, L"easy", L"easy_click", L"easy_over", L"easy", D3DXVECTOR3(400, 250, 0),true);
		m_pG_Rank->AddButton(31, L"normal", L"normal_click", L"normal_over", L"normal", D3DXVECTOR3(400, 400, 0),true);
		m_pG_Rank->AddButton(32, L"hard", L"hard_click", L"hard_over",L"hard", D3DXVECTOR3(400, 550, 0),true);
		m_pG_Rank->AddButton(400,L"left",L"left",L"left",L"left",D3DXVECTOR3(0,480,0),true);

		m_pG_Rank->SetVisible(false);


	}
	if(m_pRank_check == NULL)
	{
		m_pRank_check = new KGDialog(m_pSprite,0,0);
		m_pRank_check->SetSprite(L"test1",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		m_pRank_check->AddNumber(100,L"Dnum_",D3DXVECTOR3(170,200,0),-25);
		m_pRank_check->AddNumber(101,L"Dnum_",D3DXVECTOR3(170,300,0),-25);
		m_pRank_check->AddNumber(102,L"Dnum_",D3DXVECTOR3(170,400,0),-25);
		m_pRank_check->AddNumber(103,L"Dnum_",D3DXVECTOR3(170,500,0),-25);
		m_pRank_check->AddNumber(104,L"Dnum_",D3DXVECTOR3(170,600,0),-25);
		m_pRank_check->AddNumber(105,L"Dnum_",D3DXVECTOR3(640,200,0),-25);
		m_pRank_check->AddNumber(106,L"Dnum_",D3DXVECTOR3(640,300,0),-25);
		m_pRank_check->AddNumber(107,L"Dnum_",D3DXVECTOR3(640,400,0),-25);
		m_pRank_check->AddNumber(108,L"Dnum_",D3DXVECTOR3(640,500,0),-25);
		m_pRank_check->AddNumber(109,L"Dnum_",D3DXVECTOR3(640,600,0),-25);
		m_pRank_check->SetSprite(L"rank_number_1",D3DXVECTOR3(50,170,0),D3DXCOLOR(1,1,1,1));
		m_pRank_check->SetSprite(L"rank_number_2",D3DXVECTOR3(50,270,0),D3DXCOLOR(1,1,1,1));
		m_pRank_check->SetSprite(L"rank_number_3",D3DXVECTOR3(50,370,0),D3DXCOLOR(1,1,1,1));
		m_pRank_check->SetSprite(L"rank_number_4",D3DXVECTOR3(50,470,0),D3DXCOLOR(1,1,1,1));
		m_pRank_check->SetSprite(L"rank_number_5",D3DXVECTOR3(50,570,0),D3DXCOLOR(1,1,1,1));

		m_pRank_check->SetVisible(false);

	}
	if(m_pRank == NULL)
	{
		m_pRank   = new cRank();
	}
	/*if(m_name == NULL)
	{
		m_name = new KGDialog(m_pSprite,0,this);
		m_name->AddButton(123,L"name",L"name_check",L"name_over",L"name",D3DXVECTOR3(450,700,0),true);
		m_name->SetVisible(false);
	}*/
	if(m_ok == NULL)
	{
		m_ok = new KGDialog(m_pSprite,0,this);
		m_ok->AddButton(456,L"number",L"number_check",L"number_over",L"number",D3DXVECTOR3(700,700,0),true);
		m_ok->SetVisible(false);

	}
	if(m_pjembe == NULL)
	{
		m_pjembe =  new KGDialog(m_pSprite, 0, this);
		m_pjembe->SetSprite(L"jembe_help",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		m_pjembe->SetVisible(false);

	}
	if(m_pDialog2 == NULL)
	{
		m_pDialog2			= new KGDialog(m_pSprite, 0, this);
		m_pDialog2->SetSprite(L"credit",D3DXVECTOR3(512,384,0),D3DXCOLOR(1,1,1,1));
		m_pDialog2->SetVisible(false);
	}
	if(m_pdrum == NULL)
	{
		m_pdrum = new KGDialog(m_pSprite,0,this);
		m_pdrum->SetSprite(L"drum_help",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		m_pdrum->SetVisible(false);
	}
	if(m_pbase == NULL)
	{
		m_pbase = new KGDialog(m_pSprite,0,this);
		m_pbase->SetSprite(L"base_help",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		m_pbase->SetVisible(false);
	}
	m_pDialog->GetTimeBar(TM_FADE)->SetDisable(true);
	m_fFadeTime = 0;
	m_fAlpha = 0;
	menu_check	= 1;
	m_Dwtime	 =0;
	m_check	 = 0;
	PLAYCHOICE	= 0;
	m_rankck    = 0;
	for(int i=0;i<5;i++)
	{
		m_Ranking[i].nRank = -1;
		m_Ranking1[i].nRank = -1;

	}
	for(int i=0; i<NOTE_MAX; i++)
	{
		_NOTE[i].x = i*100;
		_NOTE[i].y = KGRand(520, 620);
		_NOTE_HIGH[i].x = i*100;
		_NOTE_HIGH[i].y = KGRand(244, 339);
		_NOTE[i].m_bObjectUse = false;
		_NOTE_HIGH[i].m_bObjectUse = false;
		_NOTE[i].m_fA			= 1;
		_NOTE_HIGH[i].m_fA			= 1;
		_NOTE_HIGH[i].m_fTime		= 0;
		_NOTE[i].m_fTime		= 0;



	}
	//m_nameok = 0;
	/*m_pDialog->GetButton(0)->SetSound(L"bt1", L"bt2");
	m_pDialog->GetButton(1)->SetSound(L"bt3", L"bt4");*/
	return S_OK;
}

HRESULT cMenu::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pFont);
	SAFE_ONRESETDEVICE(m_pDialog1);
	SAFE_ONRESETDEVICE(m_pDialog2);
	SAFE_ONRESETDEVICE(m_pDialog_Rank);
	SAFE_ONRESETDEVICE(m_pG_Rank);
	SAFE_ONRESETDEVICE(m_pRank_check);
	SAFE_ONRESETDEVICE(m_pdrum);
	SAFE_ONRESETDEVICE(m_pbase);
	SAFE_ONRESETDEVICE(m_pjembe);
	//SAFE_ONRESETDEVICE(m_name);
	SAFE_ONRESETDEVICE(m_ok);

	return S_OK;
}


void cMenu::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	SAFE_ONLOSTDEVICE(m_pFont);
	SAFE_ONLOSTDEVICE(m_pDialog1);
	SAFE_ONLOSTDEVICE(m_pDialog2);
	SAFE_ONLOSTDEVICE(m_pDialog_Rank);
	SAFE_ONLOSTDEVICE(m_pdrum);
	SAFE_ONLOSTDEVICE(m_pbase);
	SAFE_ONLOSTDEVICE(m_pG_Rank);
	SAFE_ONLOSTDEVICE(m_pRank_check);
	SAFE_ONLOSTDEVICE(m_pjembe);
	//SAFE_ONLOSTDEVICE(m_name);
	SAFE_ONLOSTDEVICE(m_ok);


}
void cMenu::OnDestroyDevice(void* pUserContext)
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDialog1);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pMulti);
	SAFE_DELETE(m_pdrum);
	SAFE_DELETE(m_pbase);
	SAFE_DELETE(m_pRank);
	SAFE_DELETE(m_pDialog_Rank);
	SAFE_DELETE(m_pG_Rank);
	SAFE_DELETE(m_pRank_check);
	SAFE_DELETE(m_pjembe);
	//SAFE_DELETE(m_name);
	SAFE_DELETE(m_ok);



}


void cMenu::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	m_pSound->Play(L"menu", false, 0, DSBPLAY_LOOPING);
	SAFE_ONFRAMEMOVE(m_pDialog);
	SAFE_ONFRAMEMOVE(m_pDialog1);
	SAFE_ONFRAMEMOVE(m_pRank_check);
	for(int i=0;i<NOTE_MAX;i++)
	{
		_NOTE[i].m_fTime += fElapsedTime;
		_NOTE_HIGH[i].m_fTime += fElapsedTime;

	}
	for(int i=0;i<5;i++)
		if(m_Ranking[i].nRank > -1 && m_Ranking[i].nRank > -1)
		{
			/*if(m_nameok == 0)
			{
				m_pRank_check->GetNumber(100)->SetNumber(m_Ranking[0].nRank);
				m_pRank_check->GetNumber(101)->SetNumber(m_Ranking[1].nRank);
				m_pRank_check->GetNumber(102)->SetNumber(m_Ranking[2].nRank);
				m_pRank_check->GetNumber(103)->SetNumber(m_Ranking[3].nRank);
				m_pRank_check->GetNumber(104)->SetNumber(m_Ranking[4].nRank);
				m_pRank_check->GetNumber(105)->SetNumber(m_Ranking1[0].nRank);
				m_pRank_check->GetNumber(106)->SetNumber(m_Ranking1[1].nRank);
				m_pRank_check->GetNumber(107)->SetNumber(m_Ranking1[2].nRank);
				m_pRank_check->GetNumber(108)->SetNumber(m_Ranking1[3].nRank);
				m_pRank_check->GetNumber(109)->SetNumber(m_Ranking1[4].nRank);
			}*/
		}
		/*if(m_nameok == 1)
		{
			m_pRank_check->GetNumber(100)->SetVisible(false);
			m_pRank_check->GetNumber(101)->SetVisible(false);
			m_pRank_check->GetNumber(102)->SetVisible(false);
			m_pRank_check->GetNumber(103)->SetVisible(false);
			m_pRank_check->GetNumber(104)->SetVisible(false);
			m_pRank_check->GetNumber(105)->SetVisible(false);
			m_pRank_check->GetNumber(106)->SetVisible(false);
			m_pRank_check->GetNumber(107)->SetVisible(false);
			m_pRank_check->GetNumber(108)->SetVisible(false);
			m_pRank_check->GetNumber(109)->SetVisible(false);
		}*/
		/*if(m_nameok == 0)
		{
			m_pRank_check->GetNumber(100)->SetVisible(true);
			m_pRank_check->GetNumber(101)->SetVisible(true);
			m_pRank_check->GetNumber(102)->SetVisible(true);
			m_pRank_check->GetNumber(103)->SetVisible(true);
			m_pRank_check->GetNumber(104)->SetVisible(true);
			m_pRank_check->GetNumber(105)->SetVisible(true);
			m_pRank_check->GetNumber(106)->SetVisible(true);
			m_pRank_check->GetNumber(107)->SetVisible(true);
			m_pRank_check->GetNumber(108)->SetVisible(true);
			m_pRank_check->GetNumber(109)->SetVisible(true);

		}*/
		m_vPos			= D3DXVECTOR3(635-(menu_check*40),110+(menu_check*95),0);

		if(!m_pDialog->GetTimeBar(TM_FADE)->GetDisable())
		{
			m_fFadeTime += fElapsedTime;
			if(m_fFadeTime > 0.001f)
			{
				m_fAlpha += 0.1f;
				if(m_fAlpha > 1) m_fAlpha = 1;
				m_fFadeTime = 0;
			}

		}
		for(int i=0; i<NOTE_MAX; i++)
		{
			if(_NOTE[i].x < 890 && _NOTE[i].x > -50)
				_NOTE[i].m_bObjectUse = true;
			else
			{
				_NOTE[i].x = 8*100;
				_NOTE[i].m_bObjectUse = false;
			}
			_NOTE[i].y = 15*sin(_NOTE[i].x/30.f) + 570;

			_NOTE[i].x-=1;

			if(_NOTE_HIGH[i].x > -50 && _NOTE_HIGH[i].x < 890)
				_NOTE_HIGH[i].m_bObjectUse = true;
			else
			{
				_NOTE_HIGH[i].x = -5;
				_NOTE_HIGH[i].m_bObjectUse = false;
			}
			_NOTE_HIGH[i].y = 15*sin(_NOTE_HIGH[i].x/30.f) + 291;

			_NOTE_HIGH[i].x+=1;
		}



		for(int i=0;i<5;i++)
		{
			if(_NOTE_HIGH[i].x > 450 && _NOTE_HIGH[i].x < 520)
			{
				if(_NOTE_HIGH[i].m_fTime > 0.01)
				{
					_NOTE_HIGH[i].m_fA-= 0.1;
					_NOTE_HIGH[i].m_fTime = 0;
				}
				if(_NOTE_HIGH[i].m_fA < 0.1)
					_NOTE_HIGH[i].m_fA = 0.1;
			}
			else if(_NOTE_HIGH[i].x >= 520) 
			{
				if(_NOTE_HIGH[i].m_fTime > 0.01)
				{
					_NOTE_HIGH[i].m_fA+= 0.1;
					_NOTE_HIGH[i].m_fTime = 0;
				}
				if(_NOTE_HIGH[i].m_fA > 1)
					_NOTE_HIGH[i].m_fA = 1;

			}

			if(_NOTE[i].x < 180 && _NOTE[i].x > 150)
			{
				if(_NOTE[i].m_fTime > 0.01)
				{
					_NOTE[i].m_fA-= 0.1;
					_NOTE[i].m_fTime = 0;
				}
				if(_NOTE[i].m_fA < 0.1)
					_NOTE[i].m_fA = 0.1;
			}
			else if(_NOTE[i].x <= 180) 
			{
				if(_NOTE[i].m_fTime > 0.01)
				{
					_NOTE[i].m_fA+= 0.1;
					_NOTE[i].m_fTime = 0;
				}
				if(_NOTE[i].m_fA > 1)
					_NOTE[i].m_fA = 1;

			}
		}
		for(int i=5;i<8;i++)
		{
			if(_NOTE_HIGH[i].x > 450 && _NOTE_HIGH[i].x < 520)
			{
				if(_NOTE_HIGH[i].m_fTime > 0.01)
				{
					_NOTE_HIGH[i].m_fA-= 0.1;
					_NOTE_HIGH[i].m_fTime = 0;
				}
				if(_NOTE_HIGH[i].m_fA < 0.1)
					_NOTE_HIGH[i].m_fA = 0.1;
			}
			else if(_NOTE_HIGH[i].x >= 520) 
			{
				if(_NOTE_HIGH[i].m_fTime > 0.01)
				{
					_NOTE_HIGH[i].m_fA+= 0.1;
					_NOTE_HIGH[i].m_fTime = 0;
				}
				if(_NOTE_HIGH[i].m_fA > 1)
					_NOTE_HIGH[i].m_fA = 1;

			}


			if(_NOTE[i].x < 180 && _NOTE[i].x > 150)
			{
				if(_NOTE[i].m_fTime > 0.01)
				{
					_NOTE[i].m_fA-= 0.1;
					_NOTE[i].m_fTime = 0;
				}
				if(_NOTE[i].m_fA < 0.1)
					_NOTE[i].m_fA = 0.1;
			}
			else if(_NOTE[i].x <= 180) 
			{
				if(_NOTE[i].m_fTime > 0.01)
				{
					_NOTE[i].m_fA+= 0.1;
					_NOTE[i].m_fTime = 0;
				}
				if(_NOTE[i].m_fA > 1)
					_NOTE[i].m_fA = 1;

			}
		}
}


void cMenu::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255,255), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		m_pSprite->Render(L"Moag",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		for(int i=0; i<5; i++)
		{
			if(_NOTE[i].m_bObjectUse)
			{
				if(_NOTE[i].x > 180)
					m_pSprite->Render(L"Moag4",D3DXVECTOR3(_NOTE[i].x,_NOTE[i].y,0),D3DXCOLOR(1,1,1,_NOTE[i].m_fA));
				else if(_NOTE[i].x < 180)
					m_pSprite->Render(L"2",D3DXVECTOR3(_NOTE[i].x,_NOTE[i].y,0),D3DXCOLOR(1,1,1,_NOTE[i].m_fA));

				if(_NOTE_HIGH[i].x < 520)
					m_pSprite->Render(L"Moag5",D3DXVECTOR3(_NOTE_HIGH[i].x,_NOTE_HIGH[i].y-75,0),D3DXCOLOR(1,1,1,_NOTE_HIGH[i].m_fA));
				else if(_NOTE_HIGH[i].x > 520)
					m_pSprite->Render(L"4",D3DXVECTOR3(_NOTE_HIGH[i].x,_NOTE_HIGH[i].y-75,0),D3DXCOLOR(1,1,1,_NOTE_HIGH[i].m_fA));
			}

		}
		for(int i=5; i<8; i++)
		{
			if(_NOTE[i].m_bObjectUse)
			{
				if(_NOTE[i].x > 180)
					m_pSprite->Render(L"Moag3",D3DXVECTOR3(_NOTE[i].x,_NOTE[i].y,0),D3DXCOLOR(1,1,1,_NOTE[i].m_fA));
				else if(_NOTE[i].x < 180)
					m_pSprite->Render(L"5",D3DXVECTOR3(_NOTE[i].x,_NOTE[i].y,0),D3DXCOLOR(1,1,1,_NOTE[i].m_fA));

				if(_NOTE_HIGH[i].x < 520)
					m_pSprite->Render(L"Moag1",D3DXVECTOR3(_NOTE_HIGH[i].x,_NOTE_HIGH[i].y-75,0),D3DXCOLOR(1,1,1,_NOTE_HIGH[i].m_fA));
				else if(_NOTE_HIGH[i].x > 520)
					m_pSprite->Render(L"1",D3DXVECTOR3(_NOTE_HIGH[i].x,_NOTE_HIGH[i].y-75,0),D3DXCOLOR(1,1,1,_NOTE_HIGH[i].m_fA));
			}
		}
		/*	m_pSprite->Render(L"music_1",D3DXVECTOR3(255,564,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"music_1",D3DXVECTOR3(530,205,0),D3DXCOLOR(1,1,1,1));*/
		if(m_check  == 0)
		{
			if(menu_check == 1)
				m_pSprite->Render(L"St_check",m_vPos,D3DXCOLOR(1,1,1,1));
			else if(menu_check == 2)
				m_pSprite->Render(L"Rank_check",m_vPos,D3DXCOLOR(1,1,1,1));
			else if(menu_check == 3)
				m_pSprite->Render(L"He_check",m_vPos,D3DXCOLOR(1,1,1,1));
			else if(menu_check ==4)
				m_pSprite->Render(L"Cr_check",m_vPos,D3DXCOLOR(1,1,1,1));
			else if(menu_check == 5)
				m_pSprite->Render(L"Qu_check",m_vPos,D3DXCOLOR(1,1,1,1));
		}


		m_pSprite->Render(L"mong_fade",D3DXVECTOR3(880,4.5,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"fade_mong",D3DXVECTOR3(0,1,0),D3DXCOLOR(1,1,1,1));

		SAFE_ONFRAMERENDER(m_pDialog);
		SAFE_ONFRAMERENDER(m_pDialog1);
		SAFE_ONFRAMERENDER(m_pDialog2);
		SAFE_ONFRAMERENDER(m_pDialog_Rank);
		SAFE_ONFRAMERENDER(m_pG_Rank);
		SAFE_ONFRAMERENDER(m_pRank_check);

		SAFE_ONFRAMERENDER(m_pdrum);
		SAFE_ONFRAMERENDER(m_pbase);
		SAFE_ONFRAMERENDER(m_pjembe);
		SAFE_ONFRAMERENDER(m_ok);
		//SAFE_ONFRAMERENDER(m_name);

		SAFE_ONFRAMERENDER(m_pMulti);
		SAFE_ONFRAMERENDER(m_pCursor);
		m_pSprite->Render(L"black", D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,m_fAlpha));

		if(m_pRank_check->GetVisible() == true)
		{
			/*if(m_nameok == 1)
			{
				m_pFont->DrawText(2, NULL, m_Ranking[0].wsName, -1, KGRect(170,200,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
				m_pFont->DrawText(2, NULL, m_Ranking[1].wsName, -1, KGRect(170,300,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
				m_pFont->DrawText(2, NULL, m_Ranking[2].wsName, -1, KGRect(170,400,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
				m_pFont->DrawText(2, NULL, m_Ranking[3].wsName, -1, KGRect(170,500,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
				m_pFont->DrawText(2, NULL, m_Ranking[4].wsName, -1, KGRect(170,600,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
				m_pFont->DrawText(2, NULL, m_Ranking1[0].wsName, -1, KGRect(640,200,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
				m_pFont->DrawText(2, NULL, m_Ranking1[1].wsName, -1, KGRect(640,300,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
				m_pFont->DrawText(2, NULL, m_Ranking1[2].wsName, -1, KGRect(640,400,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
				m_pFont->DrawText(2, NULL, m_Ranking1[3].wsName, -1, KGRect(640,500,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
				m_pFont->DrawText(2, NULL, m_Ranking1[4].wsName, -1, KGRect(640,600,1024,768), DT_NOCLIP , D3DXCOLOR(0, 0, 0, 1));
			}*/
		}
		V(pd3dDevice->EndScene());
	}
}

void cMenu::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	if(!m_pDialog->GetTimeBar(TM_FADE)->GetDisable()) return;

	SAFE_ONKEYBOARD(m_pDialog);
	SAFE_ONKEYBOARD(m_pDialog1);
	SAFE_ONKEYBOARD(m_pDialog2);
	SAFE_ONKEYBOARD(m_pDialog_Rank);
	SAFE_ONKEYBOARD(m_pG_Rank);
	SAFE_ONKEYBOARD(m_pRank_check);


	SAFE_ONKEYBOARD(m_pdrum);
	SAFE_ONKEYBOARD(m_pbase);
	SAFE_ONKEYBOARD(m_pjembe);
	//SAFE_ONKEYBOARD(m_name);
	SAFE_ONKEYBOARD(m_ok);
	if(!bKeyDown) return;

	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case VK_UP:
		{
			m_check = 0;

			if(m_pDialog1->GetVisible()) return;
			if(m_pDialog2->GetVisible()) return;
			if(m_pDialog_Rank->GetVisible()) return;
			if(m_pRank_check->GetVisible()) return;
			menu_check -=1;
			if(menu_check < 1)
				menu_check = 5;
			break;

		}
	case VK_DOWN:
		{
			m_check = 0;

			if(m_pDialog1->GetVisible()) return;
			if(m_pDialog2->GetVisible()) return;
			if(m_pDialog_Rank->GetVisible()) return;
			if(m_pRank_check->GetVisible()) return;
			menu_check +=1;
			if(menu_check > 5)
				menu_check = 1;
			break;

		}
	case VK_RETURN:
		{

			if(menu_check < 1)  return ;
			if(m_pDialog1->GetVisible()) return;
			if(m_pDialog2->GetVisible()) return;
			if(m_pDialog_Rank->GetVisible()) return;
			if(m_pRank_check->GetVisible()) return;
			if(m_check != 0) return;
			if(menu_check == 2)
			{
				m_pDialog_Rank->SetVisible(true);
				SetDisable(true);
			}
			if(menu_check == 4)
			{
				m_pDialog2->SetVisible(true);
				SetDisable(true);
			}
			if(menu_check == 3)
			{
				m_pDialog1->SetVisible(true);
				SetDisable(true);
			}
			if(menu_check != 3 && menu_check != 4 && menu_check  != 2)
			{
				if(m_pDialog->GetTimeBar(TM_FADE)->GetDisable())
				{
					m_pDialog->GetTimeBar(TM_FADE)->Reset();
					SetDisable(true);
				}
			}
			break;
		}
	}

}	


void cMenu::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{


	SAFE_ONMOUSE(m_pDialog);
	SAFE_ONMOUSE(m_pDialog1);
	SAFE_ONMOUSE(m_pDialog2);
	SAFE_ONMOUSE(m_pDialog_Rank);
	SAFE_ONMOUSE(m_pG_Rank);
	SAFE_ONMOUSE(m_pRank_check);
	SAFE_ONMOUSE(m_pCursor);
	//SAFE_ONMOUSE(m_name);
	SAFE_ONMOUSE(m_ok);
	SAFE_ONMOUSE(m_pdrum);
	SAFE_ONMOUSE(m_pbase);
	SAFE_ONMOUSE(m_pjembe);
	if(m_pDialog->GetButton(BT_GAME)->GetOvered())
		m_check = 1;
	if(m_pDialog->GetButton(BT_RANK)->GetOvered())
		m_check = 1;
	if(m_pDialog->GetButton(BT_HELP)->GetOvered())
		m_check = 1;
	if(m_pDialog->GetButton(BT_CREATE)->GetOvered())
		m_check = 1;
	if(m_pDialog->GetButton(BT_QUIT)->GetOvered())
		m_check = 1;
	if(bButtonDown)
	{
		if(m_pdrum->GetVisible() == true || m_pbase->GetVisible() == true || m_pjembe->GetVisible() == true )
		{
			m_pdrum->SetVisible(false);
			m_pbase->SetVisible(false);
			m_pjembe->SetVisible(false);
			m_Dwtime				= 0 ;

		}

		if(m_ok->GetButton(456)->GetOvered() == false  && m_pRank_check->GetVisible() == true )
		{
			m_ok->SetVisible(false);
			//m_name->SetVisible(false);
			m_pRank_check->SetVisible(false);
			m_Dwtime				= 0 ;
			//m_nameok				= 0;

		}
		if(m_pDialog2->GetVisible() == true)
		{
			m_pDialog2->SetVisible(false);
		}
		if(m_pDialog1->GetVisible() == false && m_pDialog2->GetVisible() == false && m_pDialog_Rank->GetVisible() == false && m_pG_Rank->GetVisible() == false && m_pRank_check->GetVisible() == false &&
			m_pbase->GetVisible() == false && m_pbase->GetVisible() == false && m_pjembe->GetVisible() == false )
		{
			SetDisable(false);
		}

		m_pMulti->Entry(L"mouse_effect", D3DXVECTOR3(xPos-100,yPos-60,0), true, 1); // 임펙트이다.
	}
}


LRESULT cMenu::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	SAFE_ONMSGPROC(m_pDialog);
	SAFE_ONMSGPROC(m_pDialog1);
	SAFE_ONMSGPROC(m_pDialog2);
	SAFE_ONMSGPROC(m_pDialog_Rank);
	SAFE_ONMSGPROC(m_pG_Rank);
	SAFE_ONMSGPROC(m_pRank_check);
	SAFE_ONMSGPROC(m_pdrum);
	SAFE_ONMSGPROC(m_pbase);
	SAFE_ONMSGPROC(m_pjembe);

	SAFE_ONMSGPROC(m_ok);
	//SAFE_ONMSGPROC(m_name);



	return uMsg;
}

void cMenu::OnEvent(UINT id, int xPos, int yPos)
{
	switch(id)
	{
	case 20:
		m_rankck = 1;
		m_pG_Rank->SetVisible(true);
		m_pDialog_Rank->GetButton(20)->SetDisable(true);
		m_pDialog_Rank->GetButton(21)->SetDisable(true);
		m_pDialog_Rank->GetButton(22)->SetDisable(true);
		break;
	case 21:
		m_rankck = 2;
		m_pG_Rank->SetVisible(true);
		m_pDialog_Rank->GetButton(20)->SetDisable(true);
		m_pDialog_Rank->GetButton(21)->SetDisable(true);
		m_pDialog_Rank->GetButton(22)->SetDisable(true);
		break;
	case 22: 
		m_rankck = 3;
		m_pG_Rank->SetVisible(true);

		m_pDialog_Rank->GetButton(20)->SetDisable(true);
		m_pDialog_Rank->GetButton(21)->SetDisable(true);
		m_pDialog_Rank->GetButton(22)->SetDisable(true);
		break;
	}
	switch(id)
	{
	case 123:
		//m_nameok = 1;
		break;
	case 456:
		//m_nameok = 0;
		break;
	case 200:
	case 300:
	case 400:
		if(m_pdrum->GetVisible() == false && m_pbase->GetVisible() == false)
		{
			m_pDialog1->SetVisible(false);
		}

		if(m_pDialog1->GetVisible() == false && m_pDialog2->GetVisible() == false && m_pDialog_Rank->GetVisible() == false && m_pG_Rank->GetVisible() == false && m_pRank_check->GetVisible() == false &&
			m_pbase->GetVisible() == false && m_pbase->GetVisible() == false && m_pjembe->GetVisible() == false )
		{
			SetDisable(false);
		}

		if(m_pG_Rank->GetVisible() == true)
		{
			m_pG_Rank->SetVisible(false);
			m_pDialog_Rank->GetButton(20)->SetDisable(false);
			m_pDialog_Rank->GetButton(21)->SetDisable(false);
			m_pDialog_Rank->GetButton(22)->SetDisable(false);

		} // 랭크  m_pRank_check  // m_pG_Rank	이지 	m_pDialog_Rank 모드
		else if(m_pRank_check->GetVisible() == true && m_pG_Rank->GetVisible() == false )
		{
			m_pRank_check->SetVisible(false);

		}
		else if(m_pDialog_Rank->GetVisible() == true && m_pG_Rank->GetVisible() == false && m_pRank_check->GetVisible() == false)
		{
			m_pDialog_Rank->SetVisible(false);
			SetDisable(false);

		}
		m_Dwtime = 0;
		break;
	case 30:
		if(m_Dwtime == 0.0)
			m_Dwtime = GetTickCount();
		else if(GetTickCount() -m_Dwtime > 40)
		{
			LEVEL = EASY;
			m_pRank_check->SetVisible(true);
			m_ok->SetVisible(true);
			//m_name->SetVisible(true);
			//m_pDialog_Rank->SetVisible(false);

			m_pDialog_Rank->GetButton(20)->SetDisable(true);
			m_pDialog_Rank->GetButton(21)->SetDisable(true);
			m_pDialog_Rank->GetButton(22)->SetDisable(true);

			SetDisable(true);

			if(m_rankck == 1)
			{
				m_pRank->Rank_Load(L"res/DRUMJUSTEASYRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				m_pRank->Rank_Load(L"res/DRUMSWAGGAEASYRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking1[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking1[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				break;

			}
			else if(m_rankck == 2)
			{
				m_pRank->Rank_Load(L"res/JEMBEJUSTEASYRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				m_pRank->Rank_Load(L"res/JEMBESWAGGAEASYRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking1[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking1[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				break;
			}
			else if(m_rankck == 3)
			{
				m_pRank->Rank_Load(L"res/BASEJUSTEASYRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				m_pRank->Rank_Load(L"res/BASESWAGGAEASYRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking1[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking1[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				break;
			}
			m_Dwtime	= 0;
		}
		break;
	case 31:
		if(m_Dwtime == 0.0)
			m_Dwtime = GetTickCount();
		else if(GetTickCount() -m_Dwtime > 40)
		{
			LEVEL = NORMAL;
			m_pRank_check->SetVisible(true);
			m_ok->SetVisible(true);
			//m_name->SetVisible(true);
			m_pDialog_Rank->GetButton(20)->SetDisable(true);
			m_pDialog_Rank->GetButton(21)->SetDisable(true);
			m_pDialog_Rank->GetButton(22)->SetDisable(true);
			SetDisable(true);
			if(m_rankck == 1)
			{
				m_pRank->Rank_Load(L"res/DRUMJUSTNORMALRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				m_pRank->Rank_Load(L"res/DRUMSWAGGANORMALRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking1[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking1[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				break;
			}
			else if(m_rankck == 2)
			{
				m_pRank->Rank_Load(L"res/JEMBEJUSTNORMALRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				m_pRank->Rank_Load(L"res/JEMBESWAGGANORMALRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking1[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking1[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				break;
			}
			else if(m_rankck == 3)
			{
				m_pRank->Rank_Load(L"res/BASEJUSTNORMALRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				m_pRank->Rank_Load(L"res/BASESWAGGANORMALRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking1[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking1[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				break;

			}

			m_Dwtime = 0;
		}
		break;
	case 32:
		if(m_Dwtime == 0.0)
			m_Dwtime = GetTickCount();
		else if(GetTickCount() -m_Dwtime > 40)
		{
			LEVEL = HARD;
			m_pRank_check->SetVisible(true);
			m_ok->SetVisible(true);
			//m_name->SetVisible(true);
			m_pDialog_Rank->GetButton(20)->SetDisable(true);
			m_pDialog_Rank->GetButton(21)->SetDisable(true);
			m_pDialog_Rank->GetButton(22)->SetDisable(true);
			SetDisable(true);
			if(m_rankck == 1)

			{
				m_pRank->Rank_Load(L"res/DRUMJUSTHARDRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				m_pRank->Rank_Load(L"res/DRUMSWAGGAHARDRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking1[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking1[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				break;

			}
			else if(m_rankck == 2)
			{
				m_pRank->Rank_Load(L"res/JEMBEJUSTHARDRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				m_pRank->Rank_Load(L"res/JEMBESWAGGAHARDRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking1[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking1[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				break;
			}
			else if(m_rankck == 3)
			{
				m_pRank->Rank_Load(L"res/BASEJUSTHARDRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				m_pRank->Rank_Load(L"res/BASESWAGGAHARDRANK.txt",0);
				for(int i=0;i<5;i++)
				{
					m_Ranking1[i].nRank = m_pRank->m_Ranking[i].nRank;
					//wcscpy(m_Ranking1[i].wsName , m_pRank->m_Ranking[i].wsName);
				}
				break;
			}
			m_Dwtime = 0;
		}
		break;

	}
	
	switch(id)
	{
	case BT_RANK:
		m_check = 0;
		if(m_pDialog1->GetVisible() == false && m_pDialog2->GetVisible() == false)
		{
			m_pDialog_Rank->SetVisible(true);
			SetDisable(true);
		}
		break;
	case BT_HELP:
		m_check = 0;
		if(m_pDialog2->GetVisible() == false && m_pDialog_Rank->GetVisible() == false)
		{
			m_pDialog1->SetVisible(true);
			SetDisable(true);
		}
		break;
	case BT_CREATE:
		m_check = 0;
		if(m_pDialog1->GetVisible() == false && m_pDialog_Rank->GetVisible() == false )
		{
			m_pDialog2->SetVisible(true);
			SetDisable(true);
		}
		break;
	case 10:
		if(m_Dwtime == 0.0)
			m_Dwtime = GetTickCount();
		else if(GetTickCount() -m_Dwtime > 40)
		{
			m_pdrum->SetVisible(true);
			SetDisable(true);
			m_Dwtime = 0;
		}
		break;
	case 11:
		if(m_Dwtime == 0.0)
			m_Dwtime = GetTickCount();
		else if(GetTickCount() -m_Dwtime > 40)
		{
			m_pjembe->SetVisible(true);
			SetDisable(true);
			m_Dwtime = 0;

		}

		break;
	case 12:
		if(m_Dwtime == 0.0)
			m_Dwtime = GetTickCount();
		else if(GetTickCount() -m_Dwtime > 40)
		{

			m_pbase->SetVisible(true);
			SetDisable(true);
			m_Dwtime = 0;

		}

		break;

	case BT_GAME:
	case BT_QUIT:
		m_check = 0;
		if(m_pDialog_Rank->GetVisible() == false)
		{
			m_pDialog->GetTimeBar(TM_FADE)->Reset();
			menu_check = id;
			SetDisable(true);
			break;
	case TM_FADE:
		switch(menu_check)
		{
		case GAME:		
			cMain()->Trans(L"mode");
			break;
		case QUIT:
			cMain()->CloseWindow();
			break;
		}
		}
	}
}
void cMenu::SetDisable(bool bDisable)
{
	m_pDialog->GetButton(BT_GAME)->SetDisable(bDisable);
	m_pDialog->GetButton(BT_RANK)->SetDisable(bDisable);
	m_pDialog->GetButton(BT_HELP)->SetDisable(bDisable);
	m_pDialog->GetButton(BT_CREATE)->SetDisable(bDisable);
	m_pDialog->GetButton(BT_QUIT)->SetDisable(bDisable);
}
