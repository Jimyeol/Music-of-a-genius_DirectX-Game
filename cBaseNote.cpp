#include "cBaseNote.h"


cBaseNote::cBaseNote(KGAnimate* pAnimate, int Node_Index, float x, float y, int KeyNumber)
{
	m_Table.push_back(L"Note_D");
	m_Table.push_back(L"Note_F");
	m_Table.push_back(L"Note_K");
	m_Table.push_back(L"Note_J");
	m_Table.push_back(L"Note_Spase");

	m_pAnimate				= pAnimate;
	m_pSprite				= m_pAnimate->GetSprite();
	m_pBangEffect			= NULL;
	m_nNoteKind				= Node_Index;
	m_nNoteX = 0;
	m_nNoteX = 0;
	m_nKeyNumber			= KeyNumber;
	m_nNoteX = x;
	m_nNoteY = y*-285;
	Judge_Node_X_Check		= 0; //400 50
	m_check					= 0;
	m_nJudEffect			= -1;
	m_Judger_Node_Dead		= false;
	m_bCollusionCheck		= false;
	m_Judger_Node_Cool		= false;
	m_Judger_Node_Perfect	= false;
	m_bComboOneCheck		= false;
	m_bComboBefore			= false;				//콤보체크용
	m_Judger_Node_Miss		= false;
	m_nMissBefore			= false;
	m_nMissBefore2			= false;
	for(int i=0; i<EFFECT; i++)
		m_pEffect[i]		= new KGRenderMulti(m_pAnimate);

	m_pPracticeClick[0] = new KGRenderMulti(m_pAnimate);

	m_pEffect[EFFECT_GOOD]->Entry(L"Good", D3DXVECTOR3(816-110, 400.f, 0), true, 2);
	m_pEffect[EFFECT_MISS]->Entry(L"Miss", D3DXVECTOR3(816-110, 400.f, 0), true, 2);
	m_pEffect[EFFECT_PERFECT]->Entry(L"Perfect", D3DXVECTOR3(816-110, 400.f, 0), true, 2);


	Judger_rNode = KGRect(m_nNoteX-47.f, m_nNoteY-25.f, m_nNoteX+47.f, m_nNoteY+25.f); //노드에 렉트값	 초기화


	if(m_pBangEffect == NULL)
		m_pBangEffect = new KGRenderMulti(m_pAnimate);

	m_pPracticeClick[0]->Entry(L"put", D3DXVECTOR3(700, 500, 0.f), true, 1);


}


cBaseNote::~cBaseNote()
{
	SAFE_DELETE(m_pBangEffect);
	for(int i=0; i<EFFECT; i++)
		SAFE_DELETE(m_pEffect[i]);

	SAFE_DELETE(m_pPracticeClick[0]);
}


void cBaseNote::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	m_check += fElapsedTime;

	cBase* pBase = (cBase*)cMain()->GetCurrent();
	if(pBase->m_bPause == false)
	{
		if(!m_Judger_Node_Dead)
		{
			m_nNoteY += 5.f;					//노드가 움직이는 부분


			if(m_nNoteY >= 780.f)
			{
				m_Judger_Node_Miss = true;
				m_Judger_Node_Dead = true;
				if(m_Judger_Node_Dead)
				{
					m_nNoteY += 0.f;
					if(m_nMissBefore2 == false)
					{
						m_nMissBefore = true;
						m_nMissBefore2 = true;
					}
				}

				if(m_nMissBefore == true)
				{
					pBase->m_nCombo = 0;
					NOWNODE++;
					MAXMISS++;
					if(pBase->m_fProgress >= 100)
						pBase->m_fProgress = 100;
					else if(pBase->m_fProgress < 100)
						pBase->m_fProgress += 3.f;

					m_nMissBefore = false;
				}
				//
			}
		}
		if(m_bComboOneCheck == true)
		{
			pBase->m_nCombo++;
			MAXCOMBO++;
			NOWNODE++;
			SCORE++;

			if(pBase->m_fProgress <= 0)
				pBase->m_fProgress = 0;
			else if(pBase->m_fProgress < 100)
				pBase->m_fProgress -= 5.f;


			switch(m_nKeyNumber)
			{
			case 1:
				m_pBangEffect->Entry(L"BaseEffectBang_Br", D3DXVECTOR3(m_nNoteX-70, m_nNoteY-55, 0), true, 1);
				break;
			case 2:
				m_pBangEffect->Entry(L"BaseEffectBang_R", D3DXVECTOR3(m_nNoteX-70, m_nNoteY-55, 0), true, 1);
				break;
			case 3:
				m_pBangEffect->Entry(L"BaseEffectBang_Y", D3DXVECTOR3(m_nNoteX-70, m_nNoteY-55, 0), true, 1);
				break;
			case 4:
				m_pBangEffect->Entry(L"BaseEffectBang_B", D3DXVECTOR3(m_nNoteX-70, m_nNoteY-55, 0), true, 1);
				break;
			case 5:
				m_pBangEffect->Entry(L"BaseEffectBang_R", D3DXVECTOR3(m_nNoteX-230, m_nNoteY-55, 0), true, 1);
				m_pBangEffect->Entry(L"BaseEffectBang_R", D3DXVECTOR3(m_nNoteX-110, m_nNoteY-55, 0), true, 1);
				m_pBangEffect->Entry(L"BaseEffectBang_Y", D3DXVECTOR3(m_nNoteX-20, m_nNoteY-55, 0), true, 1);
				m_pBangEffect->Entry(L"BaseEffectBang_B", D3DXVECTOR3(m_nNoteX+70, m_nNoteY-55, 0), true, 1);
				break;

			}
			if(m_Judger_Node_Perfect)
			{
				MAXPERFECT++;
				pBase->score_OK(EFFECT_PERFECT, pBase->m_nCombo, 103);
			}
			if(m_Judger_Node_Cool)
			{
				
				MAXGOOD++;
				pBase->score_OK(EFFECT_GOOD, pBase->m_nCombo, 51);
			}
			if(m_Judger_Node_Miss)
			{
			}

			m_bComboBefore	= true;
			m_bComboOneCheck = false;

		}

		if(m_Judger_Node_Cool)
		{
			m_nJudEffect = EFFECT_GOOD;
		}
		if(m_Judger_Node_Miss)
		{
			m_nJudEffect = EFFECT_MISS;
		}
		if(m_Judger_Node_Perfect)
		{
			m_nJudEffect = EFFECT_PERFECT;
		}
	}
	else
	{
		m_nNoteY += 0;
	}





	Judger_rNode = KGRect(m_nNoteX-47.f, m_nNoteY-25.f, m_nNoteX+47.f, m_nNoteY+25.f); //노드에 렉트값	 초기화

}


void cBaseNote::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	if(!m_Judger_Node_Dead)
	{
		if(m_nNoteY > -1 && m_nNoteY < 780)
			KeyCheckRender(m_nKeyNumber);
		//m_pSprite->Render(L"Note_Base", D3DXVECTOR3(m_nNoteX, m_nNoteY, 0.f), D3DXCOLOR(1, 1, 1, 1));
	}

	if(m_nJudEffect > -1)
		SAFE_ONFRAMERENDER(m_pEffect[m_nJudEffect]);

	SAFE_ONFRAMERENDER(m_pBangEffect);

	if(MUSIC == PRACTICE)
	{
		if(m_nNoteY > 730 && m_nNoteY <= 762)
			SAFE_ONFRAMERENDER(m_pPracticeClick[0]);
	}

	//m_pSprite->Render(L"RectCheck", Judger_rNode, D3DXCOLOR(1, 1, 1, 1));

}
void cBaseNote::KeyCheck()
{
	cBase* pBase = (cBase*)cMain()->GetCurrent();
	///////////////////////////////////////////////////

	Judge_Node_X_Check = m_nNoteY;		// 스페이스바를 누른 그순간의 X값을 저장

	m_Judger_Node_Dead = true;				//노드를 없애고

	if(m_bComboOneCheck == false)
		m_bComboOneCheck = true;

	if(m_Judger_Node_Dead)
		m_nNoteY += 0;

	if(Judge_Node_X_Check >= 715 && Judge_Node_X_Check <= 726 || Judge_Node_X_Check < 715)			//저장한 X값이 758보다 크면 쿨
	{
		m_Judger_Node_Cool = true;										//쿨 트루
		m_Judger_Node_Perfect = false;
		m_Judger_Node_Miss = false;
		//MAXGOOD++;
		//
	}
	if(Judge_Node_X_Check > 726 && Judge_Node_X_Check <= 762) //저장한 X값이 758보다 크고 858보다 작으면 퍼펙
	{
		m_Judger_Node_Cool = false;										//쿨 트루
		m_Judger_Node_Perfect = true;
		m_Judger_Node_Miss = false;
		
		//MAXPERFECT++;
		//
	}


}


void cBaseNote::KeyCheckRender(int Key)
{
	/*if(!m_Judger_Node_Dead)
	{
	m_pSprite->Render(m_Table[Key-1].c_str(), D3DXVECTOR3(m_nNoteX, m_nNoteY, 0.f), D3DXCOLOR(1, 1, 1, 1));
	}*/

	switch(Key)
	{
	case 1:
		m_pSprite->Render(L"Note_D", D3DXVECTOR3(m_nNoteX, m_nNoteY, 0.f), D3DXCOLOR(1, 1, 1, 1));
		break;
	case 2:
		m_pSprite->Render(L"Note_F", D3DXVECTOR3(m_nNoteX, m_nNoteY, 0.f), D3DXCOLOR(1, 1, 1, 1));
		break;
	case 3:
		m_pSprite->Render(L"Note_J", D3DXVECTOR3(m_nNoteX, m_nNoteY, 0.f), D3DXCOLOR(1, 1, 1, 1));
		break;
	case 4:
		m_pSprite->Render(L"Note_K", D3DXVECTOR3(m_nNoteX, m_nNoteY, 0.f), D3DXCOLOR(1, 1, 1, 1));
		break;
	case 5:
		m_pSprite->Render(L"Note_SPACE", D3DXVECTOR3(m_nNoteX, m_nNoteY, 0.f), D3DXCOLOR(1, 1, 1, 1));
		break;

	}
}
