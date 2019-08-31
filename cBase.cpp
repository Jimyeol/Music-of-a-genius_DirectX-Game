#include "cBase.h"


cBase::cBase()
{
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
	m_pSingle				= NULL;
	m_pDialog				= NULL;
	m_pDialog2				= NULL;
	m_pSound				= NULL;
	m_pCursor				= NULL;
	m_pEnegy				= NULL;
	m_pMulti				= NULL;

	m_dwChage_time			= 0;
	m_nBaseState			= -1;
	m_nResultNote			= 0	;
	good					= 0;
	m_nClickState			= -1;

	for(int i=0; i<EFFECT; i++)
	{
		m_pEffect[i] = NULL;
	}
	for(int i=0; i<BASECLICK_MAX; i++)
	{
		m_pBaseClick[i] = NULL;
	}
	for(int i=0; i<CLICK; i++)
	{
		m_pClickWhat[i] = NULL;
	}
	m_nXCheck				= 0;
	m_nYCheck				= 0;
	Judge_Bar_X				= 815;			//노드바의 X값
	Judge_Bar_Y				= 768;			//노드바의 Y값
	Judger_rBar = KGRect(Judge_Bar_X-209.f, Judge_Bar_Y-68.f, Judge_Bar_X+209.f, Judge_Bar_Y+10.5f); //노드바 판정바에 렉트값. 초기화


}


cBase::~cBase()
{
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	for(int i=0; i<BASECLICK_MAX; i++)
	{
		SAFE_DELETE(m_pBaseClick[i]);
	}

	for(int i=0; i<EFFECT; i++)
	{
		SAFE_DELETE(m_pEffect[i]);
	}
	for(int i=0; i<CLICK; i++)
	{
		SAFE_DELETE(m_pClickWhat[i]);
	}
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pMulti);
	SAFE_DELETE(m_pEnegy);
	for(int i=0; i<m_nLayers; i++)
	{
		if(m_pBaseLoad != NULL)
		{
			for(int j=0; j<m_pBaseLoad[i].m_Number;j++)
			{
				SAFE_DELETE(m_pBaseLoad[i].m_pBaseNote[j]);
			}
			SAFE_DELETE_ARRAY(m_pBaseLoad[i].m_pBaseNote);
		}
	}
	for(int i=0;i<m_nLayers;i++)
		SAFE_DELETE_ARRAY(m_pBaseLoad);
	if(good < 1 )
	{
		if(cMain()->BaseSound)
			cMain()->BaseSound->drop();
	}


}
void cBase::OnDestroyDevice(void* pUserContext)
{
	for(int i=0;i<good;i++)
	{
		if(cMain()->BaseSound)
		{
			cMain()->BaseSound->drop();
			cMain()->BaseSound	= NULL;
			
		}
		good--;
	}
	for(int i=0; i<CLICK; i++)
	{
		SAFE_DELETE(m_pClickWhat[i]);
	}


	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	for(int i=0; i<BASECLICK_MAX; i++)
	{
		SAFE_DELETE(m_pBaseClick[i]);
	}
	for(int i=0; i<EFFECT; i++)
	{
		SAFE_DELETE(m_pEffect[i]);
	}
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pSingle);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pEnegy);
	SAFE_DELETE(m_pMulti);
	SAFE_DELETE(m_pCursor);
	for(int i=0; i<m_nLayers; i++)
	{
		if(m_pBaseLoad != NULL)
		{
			for(int j=0; j<m_pBaseLoad[i].m_Number;j++)
			{
				SAFE_DELETE(m_pBaseLoad[i].m_pBaseNote[j]);
			}
			SAFE_DELETE_ARRAY(m_pBaseLoad[i].m_pBaseNote);
		}
	}
	for(int i=0;i<m_nLayers;i++)
		SAFE_DELETE_ARRAY(m_pBaseLoad);


}
HRESULT cBase::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	m_nCombo = 0;
	m_nResultNote = 0;

	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/Judge.Te");
		m_pSprite->Entry(L"res/te/Instrument.Te");
		m_pSprite->Entry(L"res/te/example.te");
		m_pSprite->Entry(L"res/te/perfect.te");
		m_pSprite->Entry(L"res/te/Base_Note.te");
		m_pSprite->Entry(L"res/te/Base_Background.te");
		m_pSprite->Entry(L"res/te/CGEffect.te");
		m_pSprite->Entry(L"res/te/MPEffect.te");
		m_pSprite->Entry(L"res/te/Combo.Te");
		m_pSprite->Entry(L"res/te/Base_Default.Te");
		m_pSprite->Entry(L"res/te/Base_01.Te");
		m_pSprite->Entry(L"res/te/Base_02.Te");
		m_pSprite->Entry(L"res/te/Base_03.Te");
		m_pSprite->Entry(L"res/te/Base_04.Te");
		m_pSprite->Entry(L"res/te/BaseNotebar.Te");
		m_pSprite->Entry(L"res/te/pause.te");
		m_pSprite->Entry(L"res/te/BaseNote.te");
		m_pSprite->Entry(L"res/te/base_effect8.te");
		m_pSprite->Entry(L"res/te/number.te");
		m_pSprite->Entry(L"res/te/pause.te");
		m_pSprite->Entry(L"res/te/to_mode.te");
		m_pSprite->Entry(L"res/te/return.te");
		m_pSprite->Entry(L"res/te/Combo.te");
		m_pSprite->Entry(L"res/te/AlphaCheck.te");
		m_pSprite->Entry(L"res/te/Dialog_number1.te");
		m_pSprite->Entry(L"res/te/Push.Te");
		m_pSprite->Entry(L"res/te/mouse_effect.te"); 
		m_pSprite->Entry(L"res/te/mouse_effect2.te");
		m_pSprite->Entry(L"res/te/Base_Bar.te");

	}
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768),L"cursor01", L"cursor02",L"cursor02");
	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"res/ta/teamlogo.ta");
		m_pAnimate->Entry(L"res/ta/Effect.ta");
		m_pAnimate->Entry(L"res/ta/Combo.ta");
		m_pAnimate->Entry(L"res/ta/Base_Click.ta");
		m_pAnimate->Entry(L"res/ta/BaseEffectBang_R.ta");
		m_pAnimate->Entry(L"res/ta/BaseEffectBang_B.ta");
		m_pAnimate->Entry(L"res/ta/BaseEffectBang_Br.ta");
		m_pAnimate->Entry(L"res/ta/BaseEffectBang_Y.ta");
		m_pAnimate->Entry(L"res/ta/DrumPractice.ta");
		m_pAnimate->Entry(L"res/ta/mouse_effect.ta");
		m_pAnimate->Entry(L"res/ta/Base_bar.ta");


	}
	if(m_pSingle == NULL)
	{
		m_pSingle		= new KGRenderSingle(m_pAnimate);
	}
	if(m_pDialog == NULL)
	{
		m_pDialog		= new KGDialog(m_pSprite, NULL, NULL);
		m_pDialog->AddNumber(88, L"Dnum1_", D3DXVECTOR3(780, 170, 0));

	}
	if(m_pDialog2 == NULL)
	{
		m_pDialog2		= new KGDialog(m_pSprite, NULL, this);
		m_pDialog2->SetSprite(L"pause", D3DXVECTOR3(225, 50, 0), D3DXCOLOR(1, 1, 1, 1));
		m_pDialog2->AddButton(90, L"return", L"return_click", L"return_over", L"return_click", D3DXVECTOR3(300, 240, 0));
		m_pDialog2->AddButton(91, L"to_mode", L"to_mode_click", L"to_mode_over", L"to_mode", D3DXVECTOR3(300, 470, 0));
		m_pDialog2->SetVisible(false);
	}
	if(m_pEnegy == NULL)
	{
		m_pEnegy		= new KGDialog(m_pSprite, NULL, this);
		//게이지바
		m_pEnegy->AddProgress(10, L"게이지색깔", L"게이지바", D3DXVECTOR3(495, 0, 0), D3DXVECTOR3(496, 0, 0), 100.f, KG_LERP_BOTTOM);
		//m_pEnegy->SetDisable(true);
	}
	if(m_pMulti == NULL)
	{
		m_pMulti = new KGRenderMulti(m_pAnimate);
	}
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());

	}

	for(int i=0; i<EFFECT; i++)
	{
		if(m_pEffect[i] == NULL)
		{
			m_pEffect[i]		= new KGRenderSingle(m_pAnimate);
		}
	}

	for(int i=0; i<CLICK; i++)
	{
		if(m_pClickWhat[i] == NULL)
		{
			m_pClickWhat[i]		= new KGRenderMulti(m_pAnimate); 
		}
	}
	//갈빠노파 // 101 731

	switch(MUSIC)
	{
	case JUST:
		if(LEVEL == EASY)
			Base_Music_Load(L"res/EASYBASESWAGGA.txt");
		if(LEVEL == NORMAL)
			Base_Music_Load(L"res/BASESWAGGA.txt");
		if(LEVEL == HARD)
			Base_Music_Load(L"res/HARDBASESWAGGA.txt");
		cMain()->BaseSound = 0;
		cMain()->BaseSound = cMain()->g_pSound->play2D("res/sound/Music/just.wav", false, false , true);
		//m_pSound->Play(L"just");
		break;
	case SWAGGA:
		if(LEVEL == EASY)
			Base_Music_Load(L"res/EASYBASEJUST.txt");
		if(LEVEL == NORMAL)
			Base_Music_Load(L"res/BASEJUST.txt");
		if(LEVEL == HARD)
			Base_Music_Load(L"res/HARDBASEJUST.txt");
		cMain()->BaseSound = 0;
		cMain()->BaseSound = cMain()->g_pSound->play2D("res/sound/Music/swagga.wav", false, false , true);
		//m_pSound->Entry(L"swagga",  L"/res/sound/Music/swagga.wav");
		//m_pSound->Play(L"swagga");
		break;
	case PRACTICE:
		Base_Music_Load(L"res/BASEPRACTICE.txt");
		cMain()->BaseSound = 0;
		cMain()->BaseSound = cMain()->g_pSound->play2D("res/sound/Music/practice.wav", false, false , true);
		//m_pSound->Entry(L"just",  L"/res/sound/Music/just.wav");
		//m_pSound->Play(L"practice");
		break;
	}

	for(int i=0; i<BASECLICK_MAX; i++)
	{
		if(m_pBaseClick[i] == NULL)
		{
			m_pBaseClick[i]			= new KGRenderSingle(m_pAnimate);
		}
	}

	SCORE					= 0 ;
	NOWNODE					= 0 ;
	MAXNODE					= m_nResultNote;
	MAXPERFECT				= 0 ;
	MAXGOOD					= 0 ;
	MAXMISS					= 0 ;
	MAXCOMBO				= 0 ;
	m_dwChage_time			= 0	;
	m_bPause				= false;
	m_fProgress				= 0.f;
	return S_OK;
}


HRESULT cBase::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pDialog2);
	SAFE_ONRESETDEVICE(m_pEnegy);
	return S_OK;
}


void cBase::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	SAFE_ONLOSTDEVICE(m_pDialog2);
	SAFE_ONLOSTDEVICE(m_pEnegy);
}




void cBase::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	if(m_fProgress >= 100)
	{
		cMain()->Trans(L"score");
		cMain()->BaseSound->stop();

	}
	SAFE_ONFRAMEMOVE(m_pDialog);
	SAFE_ONFRAMEMOVE(m_pDialog2);
	SAFE_ONFRAMEMOVE(m_pEnegy);
	m_pDialog->GetNumber(88)->SetNumber(m_nCombo);//m_nCombo

	m_pEnegy->GetProgress(10)->SetPos(m_fProgress);
	for(int i=0; i<m_nLayers; i++)
		m_pBaseLoad[i].OnFrameMove(pd3dDevice, fTime, fElapsedTime, pUserContext);

	if(NOWNODE == MAXNODE)
	{
		if(m_dwChage_time == 0)
			m_dwChage_time = GetTickCount();
		else if(GetTickCount() - m_dwChage_time > 3000)
		{
			m_dwChage_time	= 0;
			cMain()->Trans(L"score");
			cMain()->BaseSound->stop();

			if(good < 1)
				good++;
		}
	}


}


void cBase::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;
	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));
	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{

		m_pSprite->Render(L"Back_Background", D3DXVECTOR3(0, 0, 0.f), D3DXCOLOR(1, 1, 1, 1));//788

		if(m_nBaseState != -1)
		{
			SAFE_ONFRAMERENDER(m_pBaseClick[m_nBaseState]);
		}
		m_pSprite->Render(L"게이지바", D3DXVECTOR3(495, 0, 0.f), D3DXCOLOR(1, 1, 1, 1));
		SAFE_ONFRAMERENDER(m_pEnegy);

		SAFE_ONFRAMERENDER(m_pDialog);
	

		for(int i=0; i<m_nLayers; i++)
		{
			m_pBaseLoad[i].OnFrameRender(pd3dDevice, fTime, fElapsedTime, pUserContext);
			for(int j=0; j<m_pBaseLoad[i].m_Number; j++)
			{
				if(m_pBaseLoad[i].m_pBaseNote[j]->m_bComboBefore)
				{
					m_pBaseLoad[i].m_pBaseNote[j]->m_bComboBefore = false;
				}
			}
		}

		if(m_nCombo >= 2)
		{
			m_pSprite->Render(L"combo01", D3DXVECTOR3(700,300,0), D3DXCOLOR(1, 1, 1, 1));
			m_pDialog->SetVisible(true);
		}
		else if(m_nCombo < 2)
		{
			m_pDialog->SetVisible(false);
		}

		if(m_nBaseState != -1)
			SAFE_ONFRAMERENDER(m_pEffect[m_nBaseState]);

		for(int i=0; i<CLICK; i++)
		{
			SAFE_ONFRAMERENDER(m_pClickWhat[i]);
		}

		SAFE_ONFRAMERENDER(m_pDialog2);
		SAFE_ONFRAMERENDER(m_pMulti);
		SAFE_ONFRAMERENDER(m_pCursor);
		//m_pSprite->Render(L"RectCheck", Judger_rBar, D3DXCOLOR(1, 1, 1, 1));

		V(pd3dDevice->EndScene());
	}




}


void cBase::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	SAFE_ONKEYBOARD(m_pDialog);
	SAFE_ONKEYBOARD(m_pDialog2);
	SAFE_ONKEYBOARD(m_pEnegy);

	if(m_bPause == true) return;
	
	
	
	
	
	
	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case 'D':
		m_nBaseState = 0;
		m_pBaseClick[0]->Entry(L"A", D3DXVECTOR3(0, 238, 0), true, 1);
		m_pClickWhat[BAR_D]->Entry(L"Brown_Bar", D3DXVECTOR3(607, 0, 0), true, 1);
		KeySettingCheckPark(0);
		break;
	case 'F':
		m_nBaseState = 1;
		m_pBaseClick[1]->Entry(L"B", D3DXVECTOR3(0, 238, 0), true, 1);
		m_pClickWhat[BAR_F]->Entry(L"Red_Bar", D3DXVECTOR3(711, 0, 0), true, 1);
		KeySettingCheckPark(1);
		break;
	case 'J':
		m_nBaseState = 2;
		m_pBaseClick[2]->Entry(L"C", D3DXVECTOR3(0, 238, 0), true, 1);
		m_pClickWhat[BAR_J]->Entry(L"Yellow_Bar", D3DXVECTOR3(815, 0, 0), true, 1);
		KeySettingCheckPark(2);
		break;
	case 'K':
		m_nBaseState = 3;
		m_pBaseClick[3]->Entry(L"D", D3DXVECTOR3(0, 238, 0), true, 1);
		m_pClickWhat[BAR_K]->Entry(L"Blue_Bar", D3DXVECTOR3(919, 0, 0), true, 1);
		KeySettingCheckPark(3);
		break;

	case VK_SPACE:
		m_pClickWhat[BAR_SPACE]->Entry(L"Green_Bar", D3DXVECTOR3(607, 0, 0), true, 1);
		m_pClickWhat[BAR_SPACE]->Entry(L"Green_Bar", D3DXVECTOR3(710, 0, 0), true, 1);
		m_pClickWhat[BAR_SPACE]->Entry(L"Green_Bar", D3DXVECTOR3(815, 0, 0), true, 1);
		m_pClickWhat[BAR_SPACE]->Entry(L"Green_Bar", D3DXVECTOR3(919, 0, 0), true, 1);
		KeySettingCheckPark(4);
		break;
	case VK_ESCAPE:
		{
			if(!m_bPause)
			{
				cMain()->BaseSound->setIsPaused(true);
				m_bPause = true;
				m_pDialog2->SetVisible(true);
			}
			break;
		}
	}
}


void cBase::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{

	m_nXCheck = xPos;
	m_nYCheck = yPos;
	SAFE_ONMOUSE(m_pDialog);
	SAFE_ONMOUSE(m_pDialog2);
	SAFE_ONMOUSE(m_pEnegy);
	SAFE_ONMOUSE(m_pCursor);
	if(bButtonDown)
	{
		m_pMulti->Entry(L"mouse_effect", D3DXVECTOR3(xPos-100,yPos-60,0), true, 1); // 임펙트이다.
	}

}


LRESULT cBase::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return uMsg;
}

void cBase::OnEvent(UINT id, int xPos, int yPos)
{
	switch(id)
	{
	case 90:
		{
			if(m_bPause)
			{
				cMain()->BaseSound->setIsPaused(false);
				m_bPause = false;
				m_pDialog2->SetVisible(false);
			}
			break;
		}
	case 91:
		cMain()->BaseSound->stop();
		cMain()->Trans(L"mode");
		if(good < 1)
			good++;
		break;
	}

}


void cBase::Base_Music_Load(const WCHAR *pFileName)
{
	WCHAR					FileNameBuffer[256];
	WCHAR					m_cLine[100];
	WCHAR					m_cString[100];

	KGFindDXSDKMediaFileCch(FileNameBuffer, 256, pFileName);

	FILE*	fp = NULL;

#pragma warning ( disable : 4996)

	fp	= _wfopen(FileNameBuffer, L"rt");

	if(fp == NULL)
	{
		KGOutputDebugString(L"맵 로딩 실패\n");
		return;
	}

	while(!feof(fp))
	{
		fgetws(m_cLine, sizeof(m_cLine), fp);
		swscanf(m_cLine, L"%s", m_cString);

		if(wcscmp(m_cString, L"//") == 0)
			continue;

		if(wcscmp(m_cString, L"[NOTEINFO]") == 0)
			DecodeBase(fp);
	}
	fclose(fp);

}
void cBase::DecodeBase(FILE* fp)
{
	WCHAR cLine[255];
	WCHAR ctemp[255];
	WCHAR strData[255];

	int nLayers = 0;

	memset(cLine, 0, sizeof(cLine));
	memset(ctemp, 0, sizeof(ctemp));
	fgetws(cLine, sizeof(cLine), fp);
	swscanf(cLine, L"%d",  &nLayers);

	m_pBaseLoad = new cBaseLoad[nLayers];

	if(!m_pBaseLoad)
		return;

	m_nLayers = nLayers;

	for(int i=0; i<nLayers; i++)
	{
		int NoteNumber;
		int KeyNumber = 0;


		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf(cLine, L"%s %d", m_pBaseLoad[i].m_LoadName, &KeyNumber);

		memset(cLine, 0, sizeof(cLine));
		fgetws(cLine, sizeof(cLine), fp);
		swscanf(cLine, L"%d", &NoteNumber);//182

		cMain()->g_test = NoteNumber;
		m_pBaseLoad[i].m_Number = NoteNumber;
		m_nResultNote += NoteNumber;

		m_pBaseLoad[i].m_pBaseNote = new cBaseNote*[NoteNumber];

		for(int j=0; j<NoteNumber; j++)
		{
			float x;
			float y;
			fgetws(strData, 100, fp) ;
			swscanf(strData, L"%f %f", &x, &y) ;
			m_pBaseLoad[i].m_pBaseNote[j] = NULL;
			m_pBaseLoad[i].m_pBaseNote[j] = new cBaseNote( m_pAnimate, i, x, y, KeyNumber);
		}
	}

	return;
}

void cBase::KeySettingCheckPark(int Key)
{
	int m_nKey				= Key;

	for(int i=0; i<m_nLayers; i++) 
	{
		for(int j=0; j<m_pBaseLoad[i].m_Number; j++)
		{
			if(Judger_rBar.isOverlap(m_pBaseLoad[i].m_pBaseNote[j]->Judger_rNode))		//노드가 판정부분에 충돌이 되어있다면
			{
				m_pBaseLoad[i].m_pBaseNote[j]->m_bCollusionCheck = true;
			}
			if(m_pBaseLoad[i].m_pBaseNote[j]->m_bCollusionCheck)
			{
				if(!m_pBaseLoad[i].m_pBaseNote[j]->m_Judger_Node_Dead)	
				{
					if(m_pBaseLoad[i].m_pBaseNote[j]->m_nNoteKind == m_nKey)
						m_pBaseLoad[i].m_pBaseNote[j]->KeyCheck();
				}
			}
		}
	}
}


void cBase::score_OK(int effect , int combo,int score)
{		/// 스코어점수관련 굿과 퍼펙트로나눔
	if(effect == EFFECT_GOOD)
	{
		if(combo < 3)
			SCORE+= score;
		else if(combo == 3)
			SCORE += score*2;
		else if(combo == 4)
			SCORE += score*3;
		else if(combo == 5)
			SCORE += score*4;
		else if(combo >= 6)
			SCORE += score*5;
	}
	else if(effect == EFFECT_PERFECT)
	{
		if(combo < 3)
			SCORE+=score;
		else if(combo == 3)
			SCORE +=score*2;
		else if(combo == 4)
			SCORE +=score*4;
		else if(combo == 5)
			SCORE +=score*6;
		else if(combo >= 6)
			SCORE +=score*8;
	}
}