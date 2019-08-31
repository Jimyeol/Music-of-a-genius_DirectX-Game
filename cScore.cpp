#include "cScore.h"

cScore::cScore()
{
	m_pSprite					= NULL;
	m_pDialog					= NULL;
	m_pSound					= NULL;
	m_pRank						= NULL;
	m_pName						= NULL;
	m_pFont						= NULL;
}


cScore::~cScore()
{
	//SAFE_DELETE(m_pName);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDialog);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pRank);
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}

}


HRESULT cScore::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	m_rank						= 0;
	Next_Time					= 0;
	m_score						= 0;
	m_miss						= 0;
	//m_pName						= NULL;
	m_pFont						= NULL;
	m_good						= 0;
	m_perfect					= 0;
	m_combo						= 0;
	m_accuracy					= 0;
	m_check						= 3000;
	m_vPos						= D3DXVECTOR3(230,550,0);
	fMake_Time					= 0;

	if(m_pFont == NULL)
	{
		m_pFont				= new KGFont(pd3dDevice);
		m_pFont->Entry(1, L"고딕", 40, 30);
		m_pFont->Entry(2, L"../res/font/K_Damage.TTF", L"휴먼태가람체", 40, 30);
	}
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/te/Dialog_number.Te");
		m_pSprite->Entry(L"res/te/Dialog_number1.Te");

		m_pSprite->Entry(L"res/te/CGEffect.te");
		m_pSprite->Entry(L"res/te/MPEffect.te");
		m_pSprite->Entry(L"res/te/RankABCD.te");
		m_pSprite->Entry(L"res/te/RankEFS.te");
		m_pSprite->Entry(L"res/te/RankInterface.te");
		m_pSprite->Entry(L"res/te/score_back.te");

	}
	//if(m_pName	== NULL)
	//{
	//	m_pName			= new KGDialog(m_pSprite, NULL, NULL);
	//	//m_pName->AddEditBox(22, m_pFont->Get(1), KGRect(520, 402, 1024, 768), D3DXCOLOR(1, 1, 1, 1), DT_NOCLIP);
	//	//m_pName->AddListBox(66,m_pFont->Get(1), KGRect(350, 0, 1024, 768)); //채팅
	//}
	if(m_pDialog == NULL)
	{
		m_pDialog		= new KGDialog(m_pSprite, NULL, NULL);
		m_pDialog->AddNumber(1, L"Dnum1_", D3DXVECTOR3(450, 200, 0),-17);
		//m_pDialog->AddNumber(2, L"Ranknum_", D3DXVECTOR3(0, 310, 0)); /////랭크 1부터 S ~~ E까지 그리저장할때 S == num_01 , A num_02 이런식으로
		m_pDialog->AddNumber(2, L"Dnum_", D3DXVECTOR3(840, 410, 0),-25); // 굿 부터 미스 콤보 
		m_pDialog->AddNumber(3, L"Dnum_", D3DXVECTOR3(840, 460, 0),-25);
		m_pDialog->AddNumber(4, L"Dnum_", D3DXVECTOR3(840, 510, 0),-25);
		m_pDialog->AddNumber(5, L"Dnum_", D3DXVECTOR3(840, 565, 0),-25);
		m_pDialog->AddNumber(6, L"Dnum_", D3DXVECTOR3(840, 620, 0),-25);
		//m_pDialog->AddNumber(7, L"Dnum_", D3DXVECTOR3(200, 50, 0),-25);
		//m_pDialog->GetNumber(7)->SetVisible(true);

		//m_pDialog->AddNumber(7, L"Dnum_", D3DXVECTOR3(600, 300, 0));
	}
	if(m_pSound == NULL)							//음악들의 초기화입니다.
	{
		m_pSound			= new KGSound(cMain()->GethWnd());
		m_pSound->Entry(L"swagga_sample",  L"/res/sound/Music/swagga_sample.wav");
		m_pSound->Entry(L"just_sample",  L"/res/sound/Music/just_sample.wav");
		m_pSound->Entry(L"practice_sample",  L"/res/sound/Music/practice_sample.wav");

	}
	if(m_pRank == NULL)
	{
		m_pRank = new cRank();
	}

	if(MUSIC == JUST)
	{
		m_pSound->Play(L"just_sample");
	}
	if(MUSIC == SWAGGA)
	{
		m_pSound->Play(L"swagga_sample");
	}
	if(MUSIC == PRACTICE)
	{
		m_pSound->Play(L"practice_sample");
	}
	return S_OK;
}
void cScore::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	//SAFE_ONFRAMEMOVE(m_pName);
	SAFE_ONFRAMEMOVE(m_pDialog);
	fMake_Time += fElapsedTime;

	if(fMake_Time  >= 0.0001) 
	{
		fMake_Time = 0;
		m_check -=120;
	}
	if(m_check < 240)
		m_check = 240;
	if(m_score != SCORE)
	{
		m_score+= 1000;
		if(m_score > SCORE)
			m_score = SCORE;
	}
	if(m_perfect != MAXPERFECT)
	{
		m_perfect++;
	}
	if(m_miss != MAXMISS)
	{
		m_miss++;
	}
	if(m_good != MAXGOOD)
	{
		m_good++;
	}
	if(m_combo != MAXCOMBO)
	{
		m_combo++;
	}
	if(m_accuracy != ((((MAXPERFECT + (MAXGOOD/2))) *100)/ MAXNODE))
	{
		m_accuracy++;
	}
	m_pDialog->GetNumber(1)->SetNumber(m_score);
	// 튜토리얼은 노트개수 7개정도 , 랭킹에 저장안되게 
	//m_pDialog->GetNumber(2)->SetNumber(m_rank);
	m_pDialog->GetNumber(2)->SetNumber(m_perfect);
	m_pDialog->GetNumber(3)->SetNumber(m_good);
	m_pDialog->GetNumber(4)->SetNumber(m_miss);
	m_pDialog->GetNumber(5)->SetNumber(m_combo);
	m_pDialog->GetNumber(6)->SetNumber(m_accuracy);
	//m_pDialog->GetNumber(7)->SetNumber(m_score);
	if(PLAYCHOICE == JEMBE)
	{
		if(MUSIC == JUST)
		{
			if(LEVEL == EASY)
			{
				rank_check(52622,41185,31748,21311,13874,6437); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
			else if(LEVEL == NORMAL)
			{
				rank_check(88999,76556,51498,34332,17166,13343); // 음악마다 A,B,C,D,E 점수가 다르니깐 

			}
			else if(LEVEL == HARD)
			{
				rank_check(125665,100000,93213,74362,53434,36456); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
		}			
		if(MUSIC == SWAGGA)
		{
			if(LEVEL == EASY)
			{
				rank_check(72512,60425,48340,36255,24170,12085); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
			else if(LEVEL == NORMAL)
			{
				rank_check(110412,92010,73608,55206,36804,18402); // 음악마다 A,B,C,D,E 점수가 다르니깐 

			}
			else if(LEVEL == HARD)
			{
				rank_check(166222,135185,104148,73111,42074,21037); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
		}
		if(MUSIC == PRACTICE)
		{
			rank_check(0,0,0,0,0,0);
		}
	}


	if(PLAYCHOICE == DRUM)
	{
		if(MUSIC == JUST)
		{
			if(LEVEL == EASY)
			{
				rank_check(72310,63456,53456,34456,25463,16737); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
			else if(LEVEL == NORMAL)
			{
				rank_check(83213,71230,64301,45463,34563,21543); // 음악마다 A,B,C,D,E 점수가 다르니깐 

			}
			else if(LEVEL == HARD)
			{
				rank_check(94556,81234,73213,63241,43213,29664); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
		}			
		if(MUSIC == SWAGGA)
		{
			if(LEVEL == EASY)
			{
				rank_check(68310,59456,49456,30456,21463,12737); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
			else if(LEVEL == NORMAL)
			{
				rank_check(79213,67230,60301,41463,30563,17543); // 음악마다 A,B,C,D,E 점수가 다르니깐 

			}
			else if(LEVEL == HARD)
			{
				rank_check(90556,76234,69213,59241,39213,25664); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
		}
		if(MUSIC == PRACTICE)
		{
			rank_check(0,0,0,0,0,0);
		}
	}

	if(PLAYCHOICE == BASE)
	{
		if(MUSIC == JUST)
		{
			if(LEVEL == EASY)
			{
				rank_check(82310,63456,53456,34456,25463,16737); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
			else if(LEVEL == NORMAL)
			{
				rank_check(93213,71230,64301,45463,34563,21543); // 음악마다 A,B,C,D,E 점수가 다르니깐 

			}
			else if(LEVEL == HARD)
			{
				rank_check(104556,81234,73213,63241,43213,29664); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
		}			
		if(MUSIC == SWAGGA)
		{
			if(LEVEL == EASY)
			{
				rank_check(78310,59456,49456,30456,21463,12737); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
			else if(LEVEL == NORMAL)
			{
				rank_check(89213,67230,60301,41463,30563,17543); // 음악마다 A,B,C,D,E 점수가 다르니깐 

			}
			else if(LEVEL == HARD)
			{
				rank_check(90556,76234,69213,59241,39213,25664); // 음악마다 A,B,C,D,E 점수가 다르니깐 
			}
		}
		if(MUSIC == PRACTICE)
		{
			rank_check(0,0,0,0,0,0);
		}
	}
}

void cScore::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		m_pSprite->Render(L"score",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Rank_Perfect",D3DXVECTOR3(463,400,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Rank_Good",D3DXVECTOR3(458,450,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Rank_Miss",D3DXVECTOR3(458,500,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Rank_MaxCombo",D3DXVECTOR3(423,550,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Rank_JudgeAverage",D3DXVECTOR3(428,600,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Persent",D3DXVECTOR3(948,620,0),D3DXCOLOR(1,1,1,1));


		switch(m_rank)
		{
		case F:
			m_pSprite->Render(L"Ranknum_07",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case E:
			m_pSprite->Render(L"Ranknum_06",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case D:
			m_pSprite->Render(L"Ranknum_05",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case C:
			m_pSprite->Render(L"Ranknum_04",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case B:
			m_pSprite->Render(L"Ranknum_03",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case A:
			m_pSprite->Render(L"Ranknum_02",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		case S:
			m_pSprite->Render(L"Ranknum_01",KGRect(m_vPos.x-m_check,m_vPos.y-m_check,m_vPos.x+m_check,m_vPos.y+m_check),D3DXCOLOR(1,1,1,1));
			break;
		}

		if(m_score == SCORE)
		{
			//m_pSprite->Render(L"이름기입란", D3DXVECTOR3(340,300,0),D3DXCOLOR(1,1,1,1));
			//m_pDialog->GetNumber(7)->SetVisible(true);
			//SAFE_ONFRAMERENDER(m_pName);
		}
		SAFE_ONFRAMERENDER(m_pDialog);

		V(pd3dDevice->EndScene());

	}
}
void cScore::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
					 bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	//SAFE_ONMOUSE(m_pName);
	if(bButtonDown)
	{
		m_score = SCORE;
		m_perfect = MAXPERFECT;
		m_miss = MAXMISS;
		m_good = MAXGOOD;
		m_combo = MAXCOMBO;
		m_accuracy = (((((MAXPERFECT + (MAXGOOD/2))) *100)/ MAXNODE));
	}
}
void cScore::rank_check(int SA,int AB,int BC,int CD ,int DE,int EF)
{	
	if(SCORE < EF)
	{
		m_rank = F;

	}
	else if(EF <= SCORE	 &&  SCORE	< DE)
	{
		m_rank = E;
	}
	else if(DE<= SCORE	 && SCORE	 < CD)
	{
		m_rank = D;
	}
	else if(CD<= SCORE	 && SCORE < BC)
	{
		m_rank = C;
	}
	else if(BC<= SCORE && SCORE < AB)
	{
		m_rank = B;
	}
	else if(AB<= SCORE && SCORE < SA)
	{
		m_rank = A;
	}
	else if(SA<= SCORE)
	{
		m_rank = S;
	}
}


void cScore::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{



	SAFE_ONKEYBOARD(m_pDialog);
	//SAFE_ONKEYBOARD(m_pName);
	switch(nChar)
	{
	case VK_RETURN:
		{
			//if(!bKeyDown) return;
			//cMain()->g_pName = m_pName->GetEditBox(22)->GetText();
			if(PLAYCHOICE == DRUM) 
			{
				if(MUSIC == JUST)
				{
					switch(LEVEL)
					{
					case EASY:
						//m_pRank->Rank_Load(L"res/DRUMJUSTEASYRANK.txt",1);
						break;
					case NORMAL:
						//m_pRank->Rank_Load(L"res/DRUMJUSTNORMALRANK.txt",1);
						break;
					case HARD:
						//m_pRank->Rank_Load(L"res/DRUMJUSTHARDRANK.txt",1);
						break;
					}
				}
				if(MUSIC == SWAGGA)
				{
					switch(LEVEL)
					{
					case EASY:
						//m_pRank->Rank_Load(L"res/DRUMSWAGGAEASYRANK.txt",1);
						break;
					case NORMAL:
						//m_pRank->Rank_Load(L"res/DRUMSWAGGANORMALRANK.txt",1);
						break;
					case HARD:
						//m_pRank->Rank_Load(L"res/DRUMSWAGGAHARDRANK.txt",1);
						break;
					}
				}
			}
			// 젬베
			if(PLAYCHOICE == JEMBE) 
			{
				if(MUSIC == JUST)
				{
					switch(LEVEL)
					{
					case EASY:
						//m_pRank->Rank_Load(L"res/JEMBEJUSTEASYRANK.txt",1);
						break;
					case NORMAL:
						//m_pRank->Rank_Load(L"res/JEMBEJUSTNORMALRANK.txt",1);
						break;
					case HARD:
						//m_pRank->Rank_Load(L"res/JEMBEJUSTHARDRANK.txt",1);
						break;
					}
				}
				if(MUSIC == SWAGGA)
				{
					switch(LEVEL)
					{
					case EASY:
						//m_pRank->Rank_Load(L"res/JEMBESWAGGAEASYRANK.txt",1);
						break;
					case NORMAL:
						//m_pRank->Rank_Load(L"res/JEMBESWAGGANORMALRANK.txt",1);
						break;
					case HARD:
						//m_pRank->Rank_Load(L"res/JEMBESWAGGAHARDRANK.txt",1);
						break;
					}
				}
			}

			if(PLAYCHOICE == BASE) 
			{
				if(MUSIC == JUST)
				{
					switch(LEVEL)
					{
					case EASY:
						//m_pRank->Rank_Load(L"res/BASEJUSTEASYRANK.txt",1);
						break;
					case NORMAL:
						//m_pRank->Rank_Load(L"res/BASEJUSTNORMALRANK.txt",1);
						break;
					case HARD:
						//m_pRank->Rank_Load(L"res/BASEJUSTHARDRANK.txt",1);
						break;
					}
				}
				if(MUSIC == SWAGGA)
				{
					switch(LEVEL)
					{
					case EASY:
						//m_pRank->Rank_Load(L"res/BASESWAGGAEASYRANK.txt",1);
						break;
					case NORMAL:
						//m_pRank->Rank_Load(L"res/BASESWAGGANORMALRANK.txt",1);
						break;
					case HARD:
						//m_pRank->Rank_Load(L"res/BASESWAGGAHARDRANK.txt",1);
						break;
					}
				}
			}
			m_pSound->Stop(L"just_sample");
			m_pSound->Stop(L"swagga_sample");
			m_pSound->Stop(L"practice_sample");
			cMain()->Trans(L"choic");
		}
		break;
	}
}

HRESULT cScore::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	SAFE_ONRESETDEVICE(m_pDialog);
	SAFE_ONRESETDEVICE(m_pFont);
	//SAFE_ONRESETDEVICE(m_pName);
	return S_OK;
}
void cScore::OnLostDevice(void* pUserContext)
{
	SAFE_ONLOSTDEVICE(m_pDialog);
	SAFE_ONLOSTDEVICE(m_pFont);
	//SAFE_ONLOSTDEVICE(m_pName);
}
void cScore::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pDialog);
	//SAFE_DELETE(m_pName);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pRank);
	if(m_pSound)
	{
		m_pSound->Stop();
		SAFE_DELETE(m_pSound);
	}

}

LRESULT cScore::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext) 
{
	//SAFE_ONMSGPROC(m_pName);

	return uMsg;
}
