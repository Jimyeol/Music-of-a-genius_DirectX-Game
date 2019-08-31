#include "MyInclude.h"
////////////////////x, y, 넘버가 나올건지 안나올것지 true(1) = 나옴, KeyCheck
cDrumNote::cDrumNote(KGAnimate* pAnimate, KGSound* pSound, int m_Node_Counter, 
					 float x, int y, int number1, int number2, int NumberCheck, int KeyCheck, int Practice)
{
	m_Table.push_back(L"Note_A");
	m_Table.push_back(L"Note_S");
	m_Table.push_back(L"Note_D");
	m_Table.push_back(L"Note_J");
	m_Table.push_back(L"Note_K");
	m_Table.push_back(L"Note_L");

	m_pAnimate				= pAnimate;
	m_pSprite				= m_pAnimate->GetSprite();
	m_pSound				= pSound;
	for(int i=0; i<2; i++)
	{
		m_pDrumEffect[i]		= new KGRenderSingle(m_pAnimate);
	}

	m_pPracticeClick[0] = new KGRenderMulti(m_pAnimate);

	m_Node_Number			= m_Node_Counter;
	m_numberBack			= number1;
	m_numberFront			= number2;
	m_nKeyCheck				= KeyCheck;
	m_bNumberCheck			= NumberCheck;
	m_Node_x				= x;
	m_Node_y				= 161;
	AIPHABAR				= 1;
	m_nJudEffectState		= -1;
	m_nEffectState			= -1;
	m_NoteResult			= m_numberFront + m_numberBack;
	Judge_Bar_X				= 212+601;		//노드바의 X값
	Judge_Bar_Y				= 312;		//노드바의 Y값
	for(int i=0; i<EFFECT; i++)
	{
		m_pJudge[i]		= NULL;
	}
	for(int i=0; i<EFFECT; i++)
	{
		if(m_pJudge[i] == NULL)
		{
			m_pJudge[i]			= new KGRenderSingle(m_pAnimate);
		}
	}
	m_pFase					= 0;
	m_Judger_Node_Dead		= false;	//노드바가 false이면 살아있다. true이면 죽어있다.
	m_Judger_Node_Cool		= false;	//노드의 체크 (cool!)
	m_Judger_Node_Miss		= false;    //MissA!!
	m_Judger_Node_Perfect	= false;	//퍼펙트!
	m_AlphaCheck			= false;
	m_bSibal				= false;
	m_bCollusionCheck		= false;
	m_bComboRenderCheck		= false;
	m_bComboOneCheck		= false;
	m_bComboBefore			= false;
	m_bObject				= false;
	m_nMissBefore			= false;
	m_nMissBefore2			= false;
	m_bPerfectCheck			= false;
	m_Judger_Node_Cool1		= false;
	m_Judger_Node_Miss1		= false;
	m_Judger_Node_Perfect1	= false;
	m_nPractice				= Practice;
	Judge_Node_X_Check		= 0;
	m_nPracticeState		= -1;
	Judger_rNode = KGRect(m_Node_x-52.f, m_Node_y-52.f, m_Node_x+52.f, m_Node_y+52.f); //노드에 렉트값	 초기화

	m_pJudge[EFFECT_GOOD]->Entry(L"Good", D3DXVECTOR3(730.f, -45.f, 0), true, 2);
	m_pJudge[EFFECT_MISS]->Entry(L"Miss", D3DXVECTOR3(730.f, -45.f, 0), true, 2);
	m_pJudge[EFFECT_PERFECT]->Entry(L"Perfect", D3DXVECTOR3(730.f, -45.f, 0), true, 2);

	m_pPracticeClick[0]->Entry(L"put", D3DXVECTOR3(500, m_Node_y, 0.f), true, 1);


}
cDrumNote::~cDrumNote()
{
	for(int i=0; i<2; i++)
		SAFE_DELETE(m_pDrumEffect[i]);

	SAFE_DELETE(m_pPracticeClick[0]);

	for(int i=0; i<EFFECT; i++)
		SAFE_DELETE(m_pJudge[i]);




}
void cDrumNote::SetDisable(bool bDisable)
{
	m_Disable = bDisable;
}


bool cDrumNote::GetDisable()
{
	return m_Disable;
}


void cDrumNote::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	m_pFase += fElapsedTime;

	Judger_rNode = KGRect(m_Node_x-40.f, m_Node_y-40.f, m_Node_x+40.f, m_Node_y+40.f); //노드에 렉트값
	cDrum* pDrum = (cDrum*)cMain()->GetCurrent();

	SRANDOM();
	if(m_bNumberCheck == 1)	
	{
		if(m_numberBack+m_numberFront >= 10)		//만약 뒤숫자와 앞숫자를 더했을경우 10보다 큰경우 다시 랜덤값을 조정
		{
			m_numberBack = RANDOM(0, 9);
			m_numberFront = RANDOM(0, 9);
			m_NoteResult = m_numberBack+m_numberFront;
		}
	}



	if(!m_Judger_Node_Dead && (!m_Judger_Node_Cool || !m_Judger_Node_Perfect))
	{
		if(pDrum->m_pDialog2->GetVisible() == false)
			m_Node_x += 3.5f;
		else
			m_Node_x += 0.f;

	}

	if(m_Judger_Node_Dead)
	{
		m_Node_x += 0.f;
		if(m_nMissBefore2 == false)
		{
			m_nMissBefore = true;
			m_nMissBefore2 = true;
		}
	}





	if(pDrum->m_pDialog2->GetVisible() == false)
	{
		if(m_Node_x >= 1024.f )							//저장한 X값이 1024보다 작으면 미스
		{
			if(m_AlphaCheck == false)
			{
				m_AlphaCheck = true;

			}
			m_Judger_Node_Miss = true;
			m_Judger_Node_Miss1 = true;
			m_Judger_Node_Dead = true;
			m_bObject = false;
			if(m_nMissBefore == true)
			{
				m_nMissBefore = false;
				NOWNODE++;
				MAXMISS++;
				pDrum->m_nCombo = 0;
				if(AIPHABAR > 0)
				{
					AIPHABAR -= 0.03;
				}
				m_nEffectState = EFFECTFAIL;
				m_pDrumEffect[EFFECTFAIL]->Entry(L"DrumEffFai", D3DXVECTOR3(860, 90, 0), true, 1);
			}
		}

		if(m_bComboOneCheck == true)
		{
			pDrum->m_nCombo++;
			m_nEffectState = EFFECTSUCCESS;
			m_pDrumEffect[EFFECTSUCCESS]->Entry(L"DrumEffSuc", D3DXVECTOR3(m_Node_x-50, m_Node_y-50, 0), true, 1);
			DRUMCOMBO++;
			MAXCOMBO++;
			if(AIPHABAR < 1)
				AIPHABAR += 0.03;
			if(AIPHABAR >= 1)
				AIPHABAR = 1;
			SCORE++;
			NOWNODE++;

			if(m_Judger_Node_Perfect)
			{
				MAXPERFECT++;
				pDrum->score_OK(EFFECT_GOOD, pDrum->m_nCombo, 103);
			}
			if(m_Judger_Node_Cool)
			{
				MAXGOOD++;
				pDrum->score_OK(EFFECT_GOOD, pDrum->m_nCombo, 51);
			}
			if(m_Judger_Node_Miss)
			{
				MAXMISS++;
			}
			m_bComboBefore	= true;
			m_bComboOneCheck = false;
		}
		if(m_Judger_Node_Cool)
		{
			m_nJudEffectState = EFFECT_GOOD;
			m_Judger_Node_Cool1 = false;
		}
		if(m_Judger_Node_Miss)
		{
			m_nJudEffectState = EFFECT_MISS;
			m_Judger_Node_Miss1 = false;
		}
		if(m_Judger_Node_Perfect)
		{
			m_nJudEffectState = EFFECT_PERFECT;
			m_Judger_Node_Perfect1 = false;
		}

	}


}


void cDrumNote::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	//m_pSprite->Render(L"Note_A", D3DXVECTOR3(m_Node_x, 50, 0), D3DXCOLOR(1, 1, 1, 1));
		KeyCheckRender(m_nKeyCheck);
		GetNumber(m_numberBack, m_numberFront);
	if(m_nEffectState > -1)
		SAFE_ONFRAMERENDER(m_pDrumEffect[m_nEffectState]);

	if(m_nPractice == 1)
	{
		if(m_Node_x > 896 && m_Node_x <= 1012)
			SAFE_ONFRAMERENDER(m_pPracticeClick[0]);
	}

	if(m_nJudEffectState > -1)
		SAFE_ONFRAMERENDER(m_pJudge[m_nJudEffectState]);



}


void cDrumNote::Judge_Funtion(int result)
{
	//cDrum* pDrum = (cDrum*)cMain()->GetCurrent();

	cDrum* pDrum = (cDrum*)cMain()->GetCurrent();
	Judge_Node_X_Check = m_Node_x;		// 스페이스바를 누른 그순간의 X값을 저장

	if(m_bComboOneCheck == false)
		m_bComboOneCheck = true;
	if(m_NoteResult == result)
	{
		m_Judger_Node_Dead = true;				//노드를 없애고
		if(m_Judger_Node_Dead)
		{
			m_Node_x += 0;
		}

		if(Judge_Node_X_Check >= 853 && Judge_Node_X_Check <= 900 || Judge_Node_X_Check >= 961 && Judge_Node_X_Check <= 1011)//저장한 X값이 758보다 크면 쿨
		{
			m_Judger_Node_Cool = true;										//쿨 트루
			m_Judger_Node_Perfect = false;
			m_Judger_Node_Miss = false;	
			m_Judger_Node_Miss1 = false;
			m_Judger_Node_Cool1 = true;										//쿨 트루
			m_Judger_Node_Perfect1 = false;
			m_nJudEffectState = EFFECT_GOOD;
			DRUMCOMBO++;

		}
		if(Judge_Node_X_Check > 900 && Judge_Node_X_Check <= 960) //저장한 X값이 758보다 크고 858보다 작으면 퍼펙
		{
			m_Judger_Node_Cool = false;										//쿨 트루
			m_Judger_Node_Perfect = true;
			m_Judger_Node_Miss = false;
			m_Judger_Node_Cool1 = false;										//쿨 트루
			m_Judger_Node_Perfect1 = true;
			m_Judger_Node_Miss1 = false;
			m_bPerfectCheck = false;
			DRUMCOMBO++;
		}							//퍼펙 트루
	}
	if(result > 10)
	{
		m_Judger_Node_Dead = true;				//노드를 없애고

		if(m_Judger_Node_Dead)
		{
			m_Node_x += 10;
		}
		if(Judge_Node_X_Check >= 851 && Judge_Node_X_Check <= 896 || Judge_Node_X_Check >= 961 && Judge_Node_X_Check <= 1011)			//저장한 X값이 758보다 크면 쿨
		{
			m_Judger_Node_Cool = true;										//쿨 트루
			m_Judger_Node_Perfect = false;
			m_Judger_Node_Miss = false;
			m_Judger_Node_Miss1 = false;
			m_Judger_Node_Cool1 = true;										//쿨 트루
			m_Judger_Node_Perfect1 = false;
			m_nJudEffectState = EFFECT_GOOD;
			pDrum->score_OK(EFFECT_GOOD, pDrum->m_nCombo, 51);
			DRUMCOMBO++;

		}
		if(Judge_Node_X_Check > 896 && Judge_Node_X_Check <= 960) //저장한 X값이 758보다 크고 858보다 작으면 퍼펙
		{
			m_Judger_Node_Cool = false;										//쿨 트루
			m_Judger_Node_Perfect = true;
			m_Judger_Node_Miss = false;
			m_Judger_Node_Cool1 = false;										//쿨 트루
			m_Judger_Node_Perfect1 = true;
			m_Judger_Node_Miss1 = false;
			m_bPerfectCheck = false;
			pDrum->score_OK(EFFECT_GOOD, pDrum->m_nCombo, 103);
			DRUMCOMBO++;
		}
	}
}


void cDrumNote::GetNumber(int number1, int number2)
{
	if(m_bNumberCheck == 1)
	{
		switch(m_numberBack)
		{
		case 0:
			m_pSprite->Render(L"num_00", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 1:
			m_pSprite->Render(L"num_01", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 2:
			m_pSprite->Render(L"num_02", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 3:
			m_pSprite->Render(L"num_03", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 4:
			m_pSprite->Render(L"num_04", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 5:
			m_pSprite->Render(L"num_05", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 6:
			m_pSprite->Render(L"num_06", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 7:
			m_pSprite->Render(L"num_07", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 8:
			m_pSprite->Render(L"num_08", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 9:
			m_pSprite->Render(L"num_09", D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		}
		switch(m_numberFront)
		{
		case 0:
			m_pSprite->Render(L"num_00", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 1:
			m_pSprite->Render(L"num_01", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 2:
			m_pSprite->Render(L"num_02", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 3:
			m_pSprite->Render(L"num_03", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 4:
			m_pSprite->Render(L"num_04", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 5:
			m_pSprite->Render(L"num_05", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 6:
			m_pSprite->Render(L"num_06", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 7:
			m_pSprite->Render(L"num_07", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 8:
			m_pSprite->Render(L"num_08", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		case 9:
			m_pSprite->Render(L"num_09", D3DXVECTOR3(m_Node_x+30, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));//788
			break;
		}
	}
}


void cDrumNote::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	}
}


void cDrumNote::KeyCheckRender(int Key)
{
	if(!m_Judger_Node_Dead)
	{
		m_pSprite->Render(m_Table[Key-1].c_str(), D3DXVECTOR3(m_Node_x, m_Node_y, 0.f), D3DXCOLOR(1, 1, 1, 1));
	}
}


int cDrumNote::GetY()
{
	if(m_Judger_Node_Dead == true)
	{
		return -999999999;
	}
	return m_Node_x;

} 