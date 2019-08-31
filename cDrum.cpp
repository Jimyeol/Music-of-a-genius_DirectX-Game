#include "cDrum.h"

cDrum::cDrum()
{

	m_pSprite				= NULL;
	m_pSound				= NULL;
	m_pAnimate				= NULL;
	m_pDialog				= NULL;
	m_pDialog2				= NULL;
	m_pMouse				= NULL;
	m_pCombo				= NULL;
	m_pCursor				= NULL;
	m_pMulti				= NULL;
	
	m_nCombo				= 0;
	m_nDrumState			= -1;
	m_fTimeShake			= 0.f;
	good					= 0;

	m_bShake				= false;
	for(int i=0; i<DRUMCLICK_MAX; i++)
	{
		m_pSingle[i] = NULL;
	}
	m_pComboNumber			= NULL;
	m_Node_Number			= 0;
	m_nXCheck				= 0;
	m_ComboTime				= 0.f;
	m_nYCheck				= 0;
	Judge_Bar_X				= 935.f;		//노드바의 X값
	Judge_Bar_Y				= 166.f;			//노드바의 Y값
	Judger_rBar = KGRect(Judge_Bar_X-62.f, Judge_Bar_Y-62.f, Judge_Bar_X+62.f, Judge_Bar_Y+62.f); //노드바 판정바에 렉트값. 초기화

}



cDrum::~cDrum()
{
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pCombo);
	SAFE_DELETE(m_pMouse);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pMulti);
	

	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	for(int i=0; i<DRUMCLICK_MAX; i++)
	{
		SAFE_DELETE(m_pSingle[i]);
	}
	if(m_pDrumNote != NULL)
	{
		for(int i= 0;i<m_Node_Number;i++)
		{
			SAFE_DELETE(m_pDrumNote[i]);
		}
		for(int i=0;i<m_Node_Number;i++)
			SAFE_DELETE_ARRAY(m_pDrumNote);
	}
	SAFE_DELETE(m_pComboNumber);
	if(good < 1 )
	{
		if(cMain()->DrumSound)
			cMain()->DrumSound->drop();
	}



	//컨트롤 쉬프트 f9
}	

void cDrum::OnDestroyDevice(void* pUserContext)
{
	
	SAFE_DELETE(m_pCursor);
	
	for(int i=0;i<good;i++)
	{
		if(cMain()->DrumSound)
		{
			cMain()->DrumSound->drop();
			cMain()->DrumSound	= NULL;
		}
		good--;
	}

	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pDialog2);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pCombo);
	SAFE_DELETE(m_pMouse);
	SAFE_DELETE(m_pMulti);
	

	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}
	for(int i=0; i<DRUMCLICK_MAX; i++)
	{
		SAFE_DELETE(m_pSingle[i]);
	}

	if(m_pDrumNote != NULL)
	{
		for(int i= 0;i<m_Node_Number;i++)
		{
			SAFE_DELETE(m_pDrumNote[i]);
		}
		for(int i=0;i<m_Node_Number;i++)
			SAFE_DELETE_ARRAY(m_pDrumNote);
	}
	SAFE_DELETE(m_pComboNumber);



}
HRESULT cDrum::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	m_iCheck = 0;

	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/Judge.Te");				// 드럼 그림은 그림파일안에있으니 알아서하시길.
		m_pSprite->Entry(L"res/te/Instrument.Te");
		m_pSprite->Entry(L"res/te/example.te");
		m_pSprite->Entry(L"res/te/CGEffect.te");
		m_pSprite->Entry(L"res/te/MPEffect.te");
		m_pSprite->Entry(L"res/te/drum_click.te");
		m_pSprite->Entry(L"res/te/Drum_Click.te");
		m_pSprite->Entry(L"res/te/Combo.te");
		m_pSprite->Entry(L"res/te/ComboNumber.te");
		m_pSprite->Entry(L"res/te/Notes.te");
		m_pSprite->Entry(L"res/te/mouse_effect.te"); 
		m_pSprite->Entry(L"res/te/mouse_effect2.te");
		m_pSprite->Entry(L"res/te/drum_effect_Succes.te");
		m_pSprite->Entry(L"res/te/drum_effect_Fail.te");
		m_pSprite->Entry(L"res/te/love.te");
		m_pSprite->Entry(L"res/te/pause.te");
		m_pSprite->Entry(L"res/te/to_mode.te");
		m_pSprite->Entry(L"res/te/return.te");
		m_pSprite->Entry(L"res/te/Push.te");
		m_pSprite->Entry(L"res/te/score.te");
		m_pSprite->Entry(L"res/te/number.te");
		m_pSprite->Entry(L"res/te/Dialog_number1.te");
	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
		m_pAnimate->Entry(L"res/ta/Effect.ta");
		m_pAnimate->Entry(L"res/ta/Drum_Click.ta");
		m_pAnimate->Entry(L"res/ta/Combo.ta");
		m_pAnimate->Entry(L"res/ta/Drum_Click_.Ta");
		m_pAnimate->Entry(L"res/ta/mouse_effect.ta");
		m_pAnimate->Entry(L"res/ta/DrumEffect.ta");
		m_pAnimate->Entry(L"res/ta/DrumPractice.ta");
	}
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"Kick",  L"/res/sound/Drum/Kick.wav");
		m_pSound->Entry(L"Hiat",  L"/res/sound/Drum/Hiat.wav");
		m_pSound->Entry(L"Snear",  L"/res/sound/Drum/Snear.wav");

	}
	if(m_pDialog == NULL)
	{
		m_pDialog			= new KGDialog(m_pSprite, NULL, this);
		m_pDialog->AddNumber(56, L"Dnum1_", D3DXVECTOR3(420, 137, 0)); //897 50
		m_pDialog->AddNumber(59, L"jembe_", D3DXVECTOR3(80, 0, 0),-10);

		m_pDialog->GetNumber(56)->SetVisible(false);
	}
	if(m_pDialog2 == NULL)
	{
		m_pDialog2			= new KGDialog(m_pSprite, NULL, this);
		m_pDialog2->AddNumber(57, L"Combonum_", D3DXVECTOR3(905, 30, 0));//470 240 //300
		m_pDialog2->SetSprite(L"pause", D3DXVECTOR3(225, 50, 0), D3DXCOLOR(1, 1, 1, 1));
		m_pDialog2->AddButton(88, L"return", L"return_click", L"return_over", L"return_click", D3DXVECTOR3(300, 240, 0));
		m_pDialog2->AddButton(89, L"to_mode", L"to_mode_click", L"to_mode_over", L"to_mode", D3DXVECTOR3(300, 470, 0));
		m_pDialog2->SetVisible(false);

	}
	if(m_pMulti == NULL)
	{
		m_pMulti = new KGRenderMulti(m_pAnimate);
	}
	if(m_pMouse == NULL)
	{
		m_pMouse = new KGRenderMulti(m_pAnimate);
	}
	if(m_pCursor == NULL)
	{
		m_pCursor			= new KGCursor(m_pSprite);
		m_pCursor->Entry(KGRect(0,0,1024,768),L"cursor01", L"cursor02",L"cursor02");
	}
	m_pCombo = new KGRenderMulti(m_pAnimate);

	for(int i=0; i<DRUMCLICK_MAX; i++)
	{
		if(m_pSingle[i] == NULL)
		{
			m_pSingle[i]			= new KGRenderMulti(m_pAnimate);
		}
	}


	switch(MUSIC)
	{
	case JUST:
		if(LEVEL == EASY)
			Load_Node(L"res/EASYDRUMSWAGGA.txt");
		if(LEVEL ==	NORMAL)
			Load_Node(L"res/DRUMSWAGGA.txt");
		if(LEVEL == HARD)
			Load_Node(L"res/HARDDRUMSWAGGA.txt");
		cMain()->DrumSound = 0;
		cMain()->DrumSound = cMain()->g_pSound->play2D("res/sound/Music/just.wav", false, false , true);
		//m_pSound->Play(L"just");
		break;
	case SWAGGA:
		if(LEVEL == EASY)
			Load_Node(L"res/EASYDRUMJUST.txt");
		if(LEVEL == NORMAL)
			Load_Node(L"res/DRUMJUST.txt");
		if(LEVEL == HARD)
			Load_Node(L"res/HARDDRUMJUST.txt");
		cMain()->DrumSound = 0;
		cMain()->DrumSound = cMain()->g_pSound->play2D("res/sound/Music/swagga.wav", false, false , true);
		//m_pSound->Entry(L"swagga",  L"/res/sound/Music/swagga.wav");
		//m_pSound->Play(L"swagga");
		break;
	case PRACTICE:
		Load_Node(L"res/DRUMPRACTICE.txt");
		cMain()->DrumSound = 0;
		cMain()->DrumSound = cMain()->g_pSound->play2D("res/sound/Music/practice.wav", false, false , true);
		//m_pSound->Entry(L"just",  L"/res/sound/Music/just.wav");
		//m_pSound->Play(L"practice");
		break;
	}
	SCORE					= 0 ;
	NOWNODE					= 0 ;
	MAXNODE					= m_Node_Number;
	MAXPERFECT				= 0 ;
	MAXGOOD					= 0 ;
	MAXMISS					= 0 ;
	MAXCOMBO				= 0 ;
	m_dwChage_time			= 0 ;
	m_nCombo				= 0 ;
	m_nBackX				= 0 ;
	m_nBackY				= 0 ;
	m_bPause				= false;



	return S_OK;
}


HRESULT cDrum::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pDialog2);
	return S_OK;
}


void cDrum::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	SAFE_ONLOSTDEVICE(m_pDialog2);
}



void cDrum::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	Judger_rBar = KGRect(Judge_Bar_X-80.f, Judge_Bar_Y-62.f, Judge_Bar_X+90.f, Judge_Bar_Y+80.f); //노드바 판정바에 렉트값.

	m_ComboTime += fElapsedTime;
	m_fTimeShake += fElapsedTime;

	//--------------------------------------------------------------
	//m_nCCheck = F_NoteNearCheck();//제일 가까운거를 체크하는 함수4
	m_iCheck = F_NoteNearCheck();
	Collusion();
	//---------------------------------------------------------------


	SAFE_ONFRAMEMOVE(m_pDialog);
	SAFE_ONFRAMEMOVE(m_pDialog2);

	m_pDialog->GetNumber(56)->SetNumber(m_nCombo);

	m_pDialog->GetNumber(59)->SetNumber(SCORE);
	//m_pDialog2->GetNumber(57)->SetNumber(m_nCombo);
	for(int i=0; i<m_Node_Number; i++)
	{
		if(m_pDrumNote[i]->m_bComboRenderCheck == true)
		{

			m_pDrumNote[i]->m_bComboRenderCheck = true;

			m_pDialog->SetVisible(true);
			if(m_ComboTime >= 2.f)
			{
				m_pDialog->SetVisible(false);
				m_ComboTime = 0;
			}
		}

	}
	for(int i=0; i<m_Node_Number; i++)
	{
		if(m_pDrumNote[i]->m_Node_x > 0)
		{
			m_pDrumNote[i]->m_bObject = true;
		}
		if(m_pDrumNote[i]->m_bComboBefore == true)
		{
			m_pDrumNote[i]->m_bComboBefore = false;
		}
		SAFE_ONFRAMEMOVE(m_pDrumNote[i]);

	}



	if(NOWNODE == MAXNODE)
	{
		if(m_dwChage_time == 0)
			m_dwChage_time = GetTickCount();
		else if(GetTickCount() - m_dwChage_time > 3000)
		{
			m_dwChage_time	= 0;
			cMain()->DrumSound->stop();
			cMain()->Trans(L"score");
			good++;
		}
	}

	if(AIPHABAR <= 0)
	{
		AIPHABAR = 1;
		cMain()->DrumSound->stop();
		cMain()->Trans(L"score");
		good++;
	}



}


void cDrum::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 111, 111, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		m_pSprite->Render(L"Drum", D3DXVECTOR3(m_nBackX, m_nBackY, 0), D3DXCOLOR(1, 1, 1, 1));//788
		m_pSprite->Render(L"Drum_Bar", D3DXVECTOR3((float)0, (float)100, (float)0), D3DXCOLOR(1, 1, 1, AIPHABAR));//판정줄은 이곳에 출력
		


		for(int i=m_Node_Number-1; i>=0; i--)
		{
			if(m_pDrumNote[i]->m_Node_x > -1 && m_pDrumNote[i]->m_Node_x < 1120)
				SAFE_ONFRAMERENDER(m_pDrumNote[i]);

			if(m_pDrumNote[i]->m_bComboRenderCheck == true)
				SAFE_ONFRAMERENDER(m_pCombo);
			if(m_pDrumNote[i]->m_bComboBefore)
			{
				SAFE_ONFRAMERENDER(m_pCombo);
				m_pDrumNote[i]->m_bComboBefore = false;
			}
		}
		if(m_nDrumState != -1)
		{
			SAFE_ONFRAMERENDER(m_pSingle[m_nDrumState]);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		SAFE_ONFRAMERENDER(m_pDialog);
		SAFE_ONFRAMERENDER(m_pDialog2);

		SAFE_ONFRAMERENDER(m_pMouse);

		//m_pSprite->Render(L"RectCheck", Judger_rBar, D3DXCOLOR(1, 1, 1, 1));
		m_pSprite->Render(L"score", D3DXVECTOR3(0,0,0), D3DXCOLOR(1, 1, 1, 1));

		if(m_nCombo > 2)
		{
			m_pSprite->Render(L"combo01", D3DXVECTOR3(370,80,0), D3DXCOLOR(1, 1, 1, 1));
			m_pDialog->GetNumber(56)->SetVisible(true);
		}
		else if(m_nCombo < 2)
		{
			//m_pDialog->SetVisible(false);
		}
		SAFE_ONFRAMERENDER(m_pMulti);

		SAFE_ONFRAMERENDER(m_pCursor);

		V(pd3dDevice->EndScene());
	}
}


void cDrum::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	SAFE_ONKEYBOARD(m_pDialog);
	SAFE_ONKEYBOARD(m_pDialog2);
	if(m_bPause == true) return;
	
	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case '0':
		NumberSettingCheckPark(0);
		break;
	case '1':
		NumberSettingCheckPark(1);
		break;
	case '2':
		NumberSettingCheckPark(2);
		break;
	case '3':
		NumberSettingCheckPark(3);
		break;
	case '4':
		NumberSettingCheckPark(4);
		break;
	case '5':
		NumberSettingCheckPark(5);
		break;
	case '6':
		NumberSettingCheckPark(6);
		break;
	case '7':
		NumberSettingCheckPark(7);
		break;
	case '8':
		NumberSettingCheckPark(8);
		break;
	case '9':
		NumberSettingCheckPark(9);
		break;
	case 'A':
		m_nDrumState = 1;
		m_bShake = true;
		m_pSingle[1]->Entry(L"S", D3DXVECTOR3(327, 500, 0), true, 1);
		m_pSound->Play(L"Kick");
		KeySettingCheckPark(22, 1);
		break;
	case 'S':
		m_nDrumState = 0;
		m_pSingle[0]->Entry(L"D", D3DXVECTOR3(430, 484, 0), true, 1);
		m_pSound->Play(L"Hiat");
		KeySettingCheckPark(22, 2);
		break;
	case 'D':
		m_nDrumState = 2;
		m_pSingle[2]->Entry(L"F", D3DXVECTOR3(484, 370, 0), true, 1);
		m_pSound->Play(L"Snear");
		KeySettingCheckPark(22, 3);
		break;
	case 'J':
		m_nDrumState = 3;
		m_pSingle[3]->Entry(L"J", D3DXVECTOR3(538, 511, 0), true, 1);
		m_pSound->Play(L"Kick");
		KeySettingCheckPark(22, 4);
		break;
	case 'K':
		m_nDrumState = 4;
		m_pSingle[4]->Entry(L"K", D3DXVECTOR3(601, 371, 0), true, 1);
		m_pSound->Play(L"Hiat");
		KeySettingCheckPark(22, 5);
		break;
	case 'L':
		m_nDrumState = 1;
		m_pSingle[1]->Entry(L"L", D3DXVECTOR3(740, 540, 0), true, 1);
		m_pSound->Play(L"Snear");
		KeySettingCheckPark(22, 6);
		break;
	case VK_ESCAPE:
		{
			if(!m_bPause)
			{
				cMain()->DrumSound->setIsPaused(true);
				m_bPause = true;
				m_pDialog2->SetVisible(true);
			}
			break;
		}
	default:
		break;
	}
}


void cDrum::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{

	SAFE_ONMOUSE(m_pDialog);
	SAFE_ONMOUSE(m_pDialog2);
	SAFE_ONMOUSE(m_pCursor);
	
	if(bButtonDown)
	{
		m_pMulti->Entry(L"mouse_effect", D3DXVECTOR3(xPos-100,yPos-60,0), true, 1); // 임펙트이다.

	}
	m_nXCheck = xPos;
	m_nYCheck = yPos;

}
LRESULT cDrum::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	SAFE_ONMSGPROC(m_pDialog);
	SAFE_ONMSGPROC(m_pDialog2);
	return uMsg;
}

void cDrum::OnEvent(UINT id, int xPos, int yPos)
{
	switch(id)
	{
	case 88:
		{
			if(m_bPause)
			{
				cMain()->DrumSound->setIsPaused(false);
				m_bPause = false;
				m_pDialog2->SetVisible(false);
			}
			break;
		}
	case 89:
		cMain()->DrumSound->stop();
		cMain()->Trans(L"mode");
		good++;
		break;
	}

}

void cDrum::Load_Node(WCHAR *pFileName)
{
	FILE* pFile;

	WCHAR	buff[256];

	KGFindDXSDKMediaFileCch(buff,256,pFileName);

	pFile = _wfopen(buff, L"r");

	if(pFile == NULL)
		return;

	Decode_Node(pFile);

	fclose(pFile);
}

void cDrum::Decode_Node(FILE *pFile)
{
	SRANDOM();
	WCHAR pSave[256];
	fgetws(pSave, 256, pFile);

	float		x;			
	int			y;			
	int			NumberCheck;
	int			KeyCheck;
	int			m_nPractice;

	swscanf(pSave, L"%d %d", &m_Node_Counter, &m_nPractice) ;
	m_Node_Number = m_Node_Counter;
	m_pDrumNote = new cDrumNote*[m_Node_Number];

	for(int i = 0 ; i < m_Node_Number ; i++ )
	{
		fgetws(pSave, sizeof(pSave), pFile) ;
		swscanf(pSave, L"%f %d %d %d", &x, &y, &NumberCheck, &KeyCheck) ;
		m_pDrumNote[i] = new cDrumNote( m_pAnimate, m_pSound, i, x, 144, RANDOM(0, 9), 
			RANDOM(0, 9), NumberCheck, KeyCheck, m_nPractice);
	}

}



int cDrum::F_NoteNearCheck()
{
	int temp = -9999999;
	int check = -1;
	for(int i=0; i<m_Node_Number; i++)
	{
		if(m_pDrumNote[i]->GetY() > temp)
		{
			temp = m_pDrumNote[i]->GetY();
			check = i;
		}
	}
	return check;
}


void cDrum::Collusion()
{
	if(m_iCheck != -1)
	{
		if(Judger_rBar.isOverlap(m_pDrumNote[m_iCheck]->Judger_rNode))
		{
			if(!m_pDrumNote[m_iCheck]->m_bCollusionCheck)
			{
				m_pDrumNote[m_iCheck]->m_bCollusionCheck = true;
			}
		}
	}

}


void cDrum::KeySettingCheckPark(int Number = 0, int Key = 0)
{
	int m_nNumber			= Number;
	int m_nKey				= Key;

	if(m_iCheck != -1)
	{
		if(m_pDrumNote[m_iCheck]->m_bCollusionCheck)
		{
			if(!m_pDrumNote[m_iCheck]->m_Judger_Node_Dead) 
			{
				if(m_pDrumNote[m_iCheck]->m_nKeyCheck == m_nKey)
				{
					m_pDrumNote[m_iCheck]->Judge_Funtion(m_nNumber);
					m_pDrumNote[m_iCheck]->m_Judger_Node_Dead = true;
				}
				else if(m_pDrumNote[m_iCheck]->m_nKeyCheck != m_nKey)
				{
					if(AIPHABAR > 0)
					{
						AIPHABAR -= 0.03;
					}
					m_nCombo = 0;
				}
			}
		}

	}
} 
/*for(int i=0; i<m_Node_Number; i++)
{
m_pDrumNote[i]->m_bComboRenderCheck = true;
if(m_pDrumNote[i]->m_bNumberCheck == 0)
{
if(m_pDrumNote[i]->m_bCollusionCheck)
{
if(!m_pDrumNote[i]->m_Judger_Node_Dead)	
{
if(m_pDrumNote[i]->m_nKeyCheck == m_nKey)
m_pDrumNote[i]->Judge_Funtion(m_nNumber);


}
}
}
}*/


void cDrum::NumberSettingCheckPark(int Number = 0)
{
	int m_nNumber			= Number;

	for(int i=0; i<m_Node_Number; i++)
	{
		m_pDrumNote[i]->m_bComboRenderCheck = true;
		if(m_pDrumNote[i]->m_bNumberCheck == 1)	
		{
			if(m_pDrumNote[i]->m_nKeyCheck == 0)
			{
				if(!m_pDrumNote[i]->m_Judger_Node_Dead)
				{
					m_pDrumNote[i]->Judge_Funtion(m_nNumber);
				}
			}
		}
	}
}


void cDrum::score_OK(int effect , int combo,int score)
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