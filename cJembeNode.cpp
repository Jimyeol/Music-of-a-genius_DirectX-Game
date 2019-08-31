#include "MyInclude.h"
// 저스트 끝..
// 스웨거 작업..
cJembeNode::cJembeNode(KGAnimate*  pAnimate,KGSound*pSound,KGDialog* pDialog)
{

	Make_Time				= 0;
	Score_Time				= 0;
	m_pAnimate				= pAnimate;
	m_pSprite				= pAnimate->GetSprite();
	m_pDialog				= pDialog;
	m_Mradius				= 15; // 마우스 지름 15
	radius					= 15;
	m_pSound				= pSound;
	Combo					= 0; 
	Num						= 0;
	check					= 0;
	Effect_Time				= 0;
	jembe_back				= 0;
	back_Time				= 0;
	fDown					= 0.025;
	m_IMax_Combo			= 0;
	back_check				= 0;
	m_ilow					= 11;
	switch(MUSIC)
	{
	case JUST:
		if(LEVEL == EASY)
			LoadNode(L"res/EASYJEMBEJUST.txt");
		if(LEVEL ==	NORMAL)
			LoadNode(L"res/JEMBEJUST.txt");
		if(LEVEL == HARD)
			LoadNode(L"res/HARDJEMBEJUST.txt");
		cMain()->JembeSound = cMain()->g_pSound->play2D("res/sound/Music/just.wav", false, false , true);
		break;
	case SWAGGA:
		if(LEVEL == EASY)
			LoadNode(L"res/EASYJEMBESWAGGA.txt");
		if(LEVEL == NORMAL)
			LoadNode(L"res/JEMBESWAGGA.txt");
		if(LEVEL == HARD)
			LoadNode(L"res/HARDJEMBESWAGGA.txt");
		cMain()->JembeSound = cMain()->g_pSound->play2D("res/sound/Music/swagga.wav", false, false , true);
		//m_pSound->Play(L"swagga");
		break;
	case PRACTICE:
		LoadNode(L"res/JEMBEPRACTICE.txt");
		cMain()->JembeSound = cMain()->g_pSound->play2D("res/sound/Music/practice.wav", false, false , true);
		//m_pSound->Play(L"practice");
		break;
	}

}
cJembeNode::~cJembeNode()
{
	SAFE_DELETE_ARRAY(m_Node);
	if(cMain()->JembeSound)
	{
		cMain()->JembeSound->drop();
	}
}
void cJembeNode::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE_ARRAY(m_Node);
}
HRESULT cJembeNode::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	return S_OK;
}
HRESULT cJembeNode::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{

	return S_OK;
}

void cJembeNode::OnLostDevice(void* pUserContext)
{

}

void cJembeNode::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	Make_Time += fElapsedTime;
	if(MAXNODE == 0)
	{
		MAXNODE					= Node_Max;
	}
	m_pDialog->GetNumber(1)->SetNumber(SCORE);
	m_pDialog->GetNumber(2)->SetNumber(m_IMax_Combo);
	m_pDialog->GetNumber(3)->SetNumber(((((MAXPERFECT + (MAXGOOD/2))) *100)/ MAXNODE));
	for(int i=0;i<Node_Max;i++)   //////////////////////////////// 노트 생성
	{
		if(Num == i)
		{
			if(Make_Time  >= m_Node[i].save_Time) 
			{
				//KGOutputDebugString(L"%f\n",Make_Time);
				if(m_Node[i].m_state == 0)
				{
					m_Node[i].m_state = 1;
					Num +=1;
					break;
				}
			}		
		}
	}

	/////////////////////////////////////////////////////////////
	for(int i=0;i<Node_Max;i++)///////////////////////노트의 큰원 줄어드는 시간
	{
		if(m_Node[i].m_state == 1)
		{
			if(m_Node[i].NodeCheck_Time == 0)
				m_Node[i].NodeCheck_Time = GetTickCount();
			else if(GetTickCount() - m_Node[i].NodeCheck_Time > m_ilow )
			{
				m_Node[i].NodeCheck_Time =0;
				if(m_Node[i].Node_Check > 5)
					m_Node[i].Node_Check -=1;
			}
		}

	}
	//////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	for(int i=0;i<Node_Max;i++)       /////////////////// 줄어드면 없어짐
	{
		if(m_Node[i].Node_Check == 5)
		{
			check = Combo_OK(i);
			m_Node[i].check = 3; // 없어졌을때 미스나오게하거나 안하거나
			m_Node[i].m_state = 2;
			m_Node[i].Node_Check= -1;
			Combo = 0;
			m_IMax_Combo = 0;
			MAXMISS	 +=1;
			break;
		}
	}
	////   시간 
	for(int i=0;i<Node_Max;i++)
	{
		if(m_Node[i].check != 0)
		{
			if(m_Node[i].check_Time == 0)
				m_Node[i].check_Time = GetTickCount();
			else if(GetTickCount() - m_Node[i].check_Time > 40)
			{
				m_Node[i].check_Time = 0;
				m_Node[i].check = 0;
				NOWNODE+=1;				// 없어지는 노트 
				break;
			}
		}
	}
	if(jembe_back != 0 || back_check != 0)
	{
		if(back_Time == 0)
			back_Time = GetTickCount();
		else if(GetTickCount() - back_Time > 400)
		{
			back_Time = 0;
			jembe_back = 0;
			back_check = 0;

		}
	}
	if(m_Node[check].check == 1 || m_Node[check].check == 2)
	{
		AIPHABAR += fDown;

	}
	if(m_Node[check].check == 3)
	{
		AIPHABAR -= fDown;
	}
	if(AIPHABAR >= 1)
		AIPHABAR = 1;
	else if(AIPHABAR <= 0)
		AIPHABAR = 0;
	if(AIPHABAR == 0)
	{
		NOWNODE = MAXNODE;
		for(int i=0;i<Node_Max;i++)
			m_Node[i].m_state = 2;
	}
	if(NOWNODE == MAXNODE  )		// 스코어로 넘어가는 시간
	{
		if(Score_Time == 0)
			Score_Time =GetTickCount();
		else if(GetTickCount() - Score_Time > 2000)
		{
			Score_Time	= 0;	
			cMain()->JembeSound->stop();
			cMain()->Trans(L"score");

		}
	}
}
void cJembeNode::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{

	m_pSprite->Render(L"jembe_back",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
	if(back_check == 0)
	{
		m_pSprite->Render(L"log",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
	}
	else if(back_check == 1)
	{
		m_pSprite->Render(L"log1",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
	}
	else if(back_check == 2)
	{
		m_pSprite->Render(L"log2",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
	}
	if(jembe_back == 0)
		m_pSprite->Render(L"jembe_en",D3DXVECTOR3(243,462,0),D3DXCOLOR(1,1,1,AIPHABAR));
	else if(jembe_back == 1)
		m_pSprite->Render(L"jembe_back_red",D3DXVECTOR3(243,462,0),D3DXCOLOR(1,1,1,AIPHABAR));
	else if(jembe_back == 2)
		m_pSprite->Render(L"jembe_back_blue",D3DXVECTOR3(243,462,0),D3DXCOLOR(1,1,1,AIPHABAR));
	m_pSprite->Render(L"Persent",D3DXVECTOR3(640,697,0),D3DXCOLOR(1,1,1,AIPHABAR));
	m_pSprite->Render(L"combo",D3DXVECTOR3(310,627,0),D3DXCOLOR(1,1,1,AIPHABAR));
	m_pSprite->Render(L"score",D3DXVECTOR3(750,740,0),D3DXCOLOR(1,1,1,AIPHABAR));
	for(int i=0;i<Node_Max;i++)
	{
		SAFE_ONFRAMERENDER(m_Node[i].impact);
		SAFE_ONFRAMERENDER(m_Node[i].m_pSingle);
	}

	for(int i=Node_Max-1;i>=0;i--)
	{
		if(m_Node[i].m_state == 1)
		{
			////// 첫번째는 큰노트일듯
			//// 두번째는 작은
			switch(m_Node[i].color) 
			{
			case 0:
				m_pSprite->Render(L"node_d",D3DXVECTOR3(m_Node[i].m_vPos.x-35,m_Node[i].m_vPos.y-35,0),D3DXCOLOR(1,1,1,1));
				break;
			case 1:
				m_pSprite->Render(L"node_f",D3DXVECTOR3(m_Node[i].m_vPos.x-35,m_Node[i].m_vPos.y-35,0),D3DXCOLOR(1,1,1,1));
				break;
			case 2:
				m_pSprite->Render(L"node_j",D3DXVECTOR3(m_Node[i].m_vPos.x-35,m_Node[i].m_vPos.y-35,0),D3DXCOLOR(1,1,1,1));
				break;
			case 3:
				m_pSprite->Render(L"node_k",D3DXVECTOR3(m_Node[i].m_vPos.x-35,m_Node[i].m_vPos.y-35,0),D3DXCOLOR(1,1,1,1));
				break;
			case 4:
				m_pSprite->Render(L"node_sp",D3DXVECTOR3(m_Node[i].m_vPos.x-35,m_Node[i].m_vPos.y-35,0),D3DXCOLOR(1,1,1,1));
				break;
			}
			m_pSprite->Render(L"node",KGRect(m_Node[i].m_vPos.x-m_Node[i].Node_Check,m_Node[i].m_vPos.y-m_Node[i].Node_Check,m_Node[i].m_vPos.x+m_Node[i].Node_Check,m_Node[i].m_vPos.y+m_Node[i].Node_Check),D3DXCOLOR(1,1,1,1),-1);
		} 
		if(MUSIC == PRACTICE)
		{
			if(m_Node[i].Node_Check <= 37 && m_Node[i].Node_Check > 20 && m_Node[i].m_state == 1)
			{
				if(m_Node[i].color == 0)
					m_pSprite->Render(L"D",D3DXVECTOR3(m_Node[i].m_vPos.x-105,m_Node[i].m_vPos.y-90,0),D3DXCOLOR(1,1,1,1));
				if(m_Node[i].color == 1)
					m_pSprite->Render(L"F",D3DXVECTOR3(m_Node[i].m_vPos.x-105,m_Node[i].m_vPos.y-90,0),D3DXCOLOR(1,1,1,1));
				if(m_Node[i].color == 2)
					m_pSprite->Render(L"J",D3DXVECTOR3(m_Node[i].m_vPos.x-105,m_Node[i].m_vPos.y-90,0),D3DXCOLOR(1,1,1,1));
				if(m_Node[i].color == 3)
					m_pSprite->Render(L"K",D3DXVECTOR3(m_Node[i].m_vPos.x-105,m_Node[i].m_vPos.y-90,0),D3DXCOLOR(1,1,1,1));
				if(m_Node[i].color == 4)
					m_pSprite->Render(L"SP",D3DXVECTOR3(m_Node[i].m_vPos.x-105,m_Node[i].m_vPos.y-90,0),D3DXCOLOR(1,1,1,1));

				break;
			}
		}
	}
	if(Combo < 3)
	{
		if(m_Node[check].check == 1)
		{
			m_Node[check].m_pSingle->Entry(L"perfect", D3DXVECTOR3(m_Node[check].m_vPos.x-110,m_Node[check].m_vPos.y-150,0), true, 1);
		}
		else if(m_Node[check].check == 2)
		{
			m_Node[check].m_pSingle->Entry(L"Good", D3DXVECTOR3(m_Node[check].m_vPos.x-110,m_Node[check].m_vPos.y-150,0), true, 1);
		}
		else if(m_Node[check].check == 3)
		{
			m_Node[check].m_pSingle->Entry(L"Miss", D3DXVECTOR3(m_Node[check].m_vPos.x-110,m_Node[check].m_vPos.y-150,0), true, 1);
		}

	}

	if(m_Node[check].check != 0)
	{
		if(Combo >= 3)
		{
			m_Node[check].m_pSingle->Entry(L"combo", D3DXVECTOR3(m_Node[check].m_vPos.x-130,m_Node[check].m_vPos.y,0), true, 1);		
		}
	}
	// 임펙트
	if(m_Node[check].check == 1)  
	{
		if(m_Node[check].color == 0)
		{
			m_Node[check].impact->Entry(L"jembe_effect_red", D3DXVECTOR3(m_Node[check].m_vPos.x-80,m_Node[check].m_vPos.y-60,0), true, 1); // 임펙트이다.
		}
		if(m_Node[check].color == 1)
		{
			m_Node[check].impact->Entry(L"jembe_effect_blue", D3DXVECTOR3(m_Node[check].m_vPos.x-80,m_Node[check].m_vPos.y-60,0), true, 1); // 임펙트이다.
		}	
	}
	else if(m_Node[check].check == 2)
	{
		if(m_Node[check].color == 0)
		{
			m_Node[check].impact->Entry(L"jembe_effect_red", D3DXVECTOR3(m_Node[check].m_vPos.x-80,m_Node[check].m_vPos.y-60,0), true, 1); // 임펙트이다.
		}
		if(m_Node[check].color == 1)
		{
			m_Node[check].impact->Entry(L"jembe_effect_blue", D3DXVECTOR3(m_Node[check].m_vPos.x-80,m_Node[check].m_vPos.y-60,0), true, 1); // 임펙트이다.
		}	
	}
	else if(m_Node[check].check == 3)
	{
		m_Node[check].impact->Entry(L"jembe_miss_effect", D3DXVECTOR3(m_Node[check].m_vPos.x-60,m_Node[check].m_vPos.y-45,0), true, 1); // 임펙트이다.
	}
}
void cJembeNode::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down,
						 bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	m_Mpos.x = xPos;  // 미우스좌표
	m_Mpos.y = yPos;
	if(bButtonDown)
	{
		if(m_Node[check].check == 0)
		{
			if(NoColBetween(m_Mpos,m_Mradius)) // 통빈화면 눌렀을때 
			{
				m_Node[check].impact->Entry(L"mouse_effect", D3DXVECTOR3(m_Mpos.x-100,m_Mpos.y-60,0), true, 1); // 임펙트이다.
			}
		}


	}
}
void cJembeNode::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
	if(!bKeyDown) return;
	switch(nChar)							//!< 키보드 message가 넘어온다 ex) VK_RETURN, VK_LEFT 등
	{
	case 'D':
		for(int i=0;i<Node_Max;i++)
		{
			if(m_Node[i].m_state == 1)
			{
				jembe_back = 1;
				OK(0,i);
				back_check = 1;
				check = Combo_OK(i);
				break;
			}
		}
		break;
	case 'F':
		for(int i=0;i<Node_Max;i++)
		{
			if(m_Node[i].m_state == 1)
			{
				jembe_back = 1;
				OK(1,i);
				back_check = 1;
				check = Combo_OK(i);
				break;
			}
		}
		break;
	case 'J':
		for(int i=0;i<Node_Max;i++)
		{
			if(m_Node[i].m_state == 1)
			{
				jembe_back = 2;
				OK(2,i);
				back_check = 2;
				check = Combo_OK(i);
				break;
			}
		}
		break;
	case 'K':
		for(int i=0;i<Node_Max;i++)
		{
			if(m_Node[i].m_state == 1)
			{
				jembe_back = 2;
				OK(3,i);
				back_check = 2;
				check = Combo_OK(i);
				break;
			}
		}
		break;
	case VK_SPACE:
		for(int i=0;i<Node_Max;i++)
		{
			if(m_Node[i].m_state == 1)
			{
				jembe_back = RANDOM(1,2);
				OK(4,i);
				back_check = RANDOM(1,2);
				check = Combo_OK(i);
				break;
			}
		}
		break;
	}
}


void cJembeNode::LoadNode(WCHAR* pFileName)
{
	FILE* pFile;
	WCHAR	buff[256];
	KGFindDXSDKMediaFileCch(buff,256,pFileName);
	pFile = _wfopen(buff, L"r");
	if(pFile == NULL)
		return;
	DecodeNode(pFile);
	fclose(pFile);
}

void cJembeNode::DecodeNode(FILE* pFile)
{   ///// 전체적인 노트의 크기 시간 지름 좌표 등등 
	SRANDOM();
	WCHAR pSave[256];
	fgetws(pSave, 256, pFile);
	swscanf(pSave, L"%d", &Node_Max);
	m_Node = new _Node[Node_Max];
	memset(m_Node, 0, sizeof(m_Node));
	for(int i =0; i < Node_Max; i++)
	{
		fgetws(pSave, sizeof(pSave), pFile);
		swscanf(pSave, L"%f %d",&m_Node[i].save_Time1,&m_Node[i].color);
		m_Node[i].save_Time = m_Node[i].save_Time1;
		m_Node[i].m_vPos		= D3DXVECTOR3(RANDOM(100,600),RANDOM(200,450),0);
		m_Node[i].m_state      = 0;
		m_Node[i].Node_Check	= 100;
		m_Node[i].NodeCheck_Time = 0;
		m_Node[i].check        = 0;
		m_Node[i].check_Time   = 0;
		m_Node[i].m_pSingle = new KGRenderMulti(m_pAnimate);
		m_Node[i].impact	= new KGRenderMulti(m_pAnimate);
	}
	if(MUSIC == JUST)
	{
		if( LEVEL == EASY)
		{
			PatDraw(1,4);
			PatDraw(5,9);
			PatDraw(10,14);
			PatDraw(16,19);
			PatDraw(21,24);
			PatDraw(25,28);
			PatDraw(30,33);
			PatDraw(35,39);
			PatDraw(41,44);
			PatDraw(45,49);
			PatDraw(50,54);
			PatDraw(55,59);
			PatDraw(60,63);
			PatDraw(64,68);
			PatDraw(70,76);
			PatDraw(77,81);
			PatDraw(82,86);		
		}
		else if(LEVEL == NORMAL)
		{
			PatDraw(1,5);
			PatDraw(6,9);
			PatDraw(10,14);
			PatDraw(15,20);
			PatDraw(21,25);
			PatDraw(26,30);
			PatDraw(31,34);
			PatDraw(35,39);
			PatDraw(40,43);
			PatDraw(44,47);
			PatDraw(48,52);
			PatDraw(53,57);
			PatDraw(58,61);
			PatDraw(62,66);
			PatDraw(67,71);
			PatDraw(72,76);
			PatDraw(77,81);
			PatDraw(82,86);
			PatDraw(87,92);
			PatDraw(93,97);
			PatDraw(98,102);
			PatDraw(103,107);
			PatDraw(108,112);
			PatDraw(113,117);
			PatDraw(118,122);
			PatDraw(123,127);
		}
		else if(LEVEL == HARD)
		{
			PatDraw(0,3);
			PatDraw(4,8);
			PatDraw(9,13);
			PatDraw(14,18);
			PatDraw(19,21);
			PatDraw(22,25);
			PatDraw(26,29);
			PatDraw(30,33);
			PatDraw(34,37);
			PatDraw(38,42);
			PatDraw(43,46);
			PatDraw(47,51);
			PatDraw(52,55);
			PatDraw(56,60);
			PatDraw(61,63);
			PatDraw(64,69);
			PatDraw(70,74);
			PatDraw(75,78);
			PatDraw(79,84);
			PatDraw(86,91);
			PatDraw(92,96);
			PatDraw(97,102);
			PatDraw(103,106);
			PatDraw(107,110);
			PatDraw(111,114);
			PatDraw(115,119);
			PatDraw(120,124);
			PatDraw(125,129);
			PatDraw(130,134);
			PatDraw(135,138);
			PatDraw(141,144);
			PatDraw(145,148);
			PatDraw(149,153);
			PatDraw(154,158);
			PatDraw(159,162);
			PatDraw(163,167);
			PatDraw(168,171);
			PatDraw(172,175);
			PatDraw(176,177);
		}
	}
	if(MUSIC == SWAGGA )
	{
		if( LEVEL == EASY)
		{
			PatDraw(2,3);
			PatDraw(4,5);
			PatDraw(6,10);
			PatDraw(12,13);
			PatDraw(15,17);
			PatDraw(19,21);
			PatDraw(22,23);
			PatDraw(24,25);
			PatDraw(26,27);
			PatDraw(28,31);
			PatDraw(38,39);
			PatDraw(41,42);
			PatDraw(44,45);
			PatDraw(46,47);
			PatDraw(49,51);
			PatDraw(54,55);
			PatDraw(56,59);
			PatDraw(63,64);
			PatDraw(66,67);
			PatDraw(68,69);
			PatDraw(77,78);
			PatDraw(83,84);
			PatDraw(89,90);
			PatDraw(95,96);
		}
		else if(LEVEL == NORMAL)
		{
			PatDraw(4,5);
			PatDraw(6,7);
			PatDraw(8,9);
			PatDraw(11,14);
			PatDraw(16,17);
			PatDraw(18,19);
			PatDraw(20,21);
			PatDraw(22,25);
			PatDraw(26,27);
			PatDraw(29,32);
			PatDraw(33,34);
			PatDraw(35,36);
			PatDraw(37,40);
			PatDraw(41,42);
			PatDraw(44,46);
			PatDraw(48,50);
			PatDraw(51,54);
			PatDraw(55,56);
			PatDraw(57,59);
			PatDraw(60,63);
			PatDraw(69,70);
			PatDraw(71,72);
			PatDraw(73,74);
			PatDraw(81,82);
			PatDraw(83,87);
			PatDraw(89,90);
			PatDraw(91,92);
			PatDraw(94,97);
			PatDraw(98,100);
			PatDraw(101,103);
			PatDraw(104,105);
			PatDraw(106,109);
			PatDraw(110,111);
			PatDraw(112,115);
			PatDraw(118,121);
			PatDraw(127,128);
			PatDraw(129,132);
			PatDraw(133,134);
		}
		else if(LEVEL == HARD)
		{
			PatDraw(0,2);
			PatDraw(2,3);
			PatDraw(4,5);
			PatDraw(6,8);
			PatDraw(10,11);
			PatDraw(12,14);
			PatDraw(17,19);
			PatDraw(20,21);
			PatDraw(22,24);
			PatDraw(25,27);
			PatDraw(28,30);
			PatDraw(31,32);
			PatDraw(33,34);
			PatDraw(35,38);
			PatDraw(39,43);
			PatDraw(44,46);
			PatDraw(47,48);
			PatDraw(49,53);
			PatDraw(55,57);
			PatDraw(58,60);
			PatDraw(61,62);
			PatDraw(63,64);
			PatDraw(66,69);
			PatDraw(70,71);
			PatDraw(72,73);
			PatDraw(75,76);
			PatDraw(77,80);
			PatDraw(81,86);
			PatDraw(90,91);
			PatDraw(93,95);
			PatDraw(96,97);
			PatDraw(98,100);
			PatDraw(101,103);
			PatDraw(104,105);
			PatDraw(106,110);
			PatDraw(111,114);
			PatDraw(115,117);
			PatDraw(119,121);
			PatDraw(122,124);
			PatDraw(125,127);
			PatDraw(129,132);
			PatDraw(134,136);
			PatDraw(137,140);
			PatDraw(141,142);
			PatDraw(144,145);
			PatDraw(147,148);
			PatDraw(151,155);
			PatDraw(156,157);
			PatDraw(158,161);
			PatDraw(163,165);
			PatDraw(167,168);
			PatDraw(170,173);
			PatDraw(175,176);
			PatDraw(177,179);
			PatDraw(180,184);
			PatDraw(186,187);
			PatDraw(188,189);
			PatDraw(193,195);
		}
	}
}
void cJembeNode::PatDraw(int First,int Last)
{
	m_vPatpos = D3DXVECTOR3(RANDOM(30,500),RANDOM(200,400),0);
	for(int i=First;i<=Last;i++)
		m_Node[i].m_vPos = D3DXVECTOR3(m_vPatpos.x+((i-(First-1))*35),m_vPatpos.y,0);

}
bool cJembeNode::NoColBetween(D3DXVECTOR3 m_vPos,double m_radius)
{  /// 충돌처리
	for(int i=0;i<Node_Max;i++)
	{
		return (pow(m_vPos.x - m_Node[i].m_vPos.x,2)+
			pow(m_vPos.y - m_Node[i].m_vPos.y,2)
	> pow(radius + m_radius,2));
	}
}	
int	 cJembeNode::Combo_OK(int check)
{
	return check;
}
void cJembeNode::score_OK(int effect , int combo,int score)
{		/// 스코어점수관련 굿과 퍼펙트로나눔
	if(effect == 0)
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
	else if(effect == 1)
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
void cJembeNode::OK(int color,int check)
{
	if(m_Node[check].color  == color)
	{
		if((m_Node[check].Node_Check > 33 && m_Node[check].Node_Check < 52) || (m_Node[check].Node_Check <= 21 && m_Node[check].Node_Check > 16))
		{  // 굿일때
			m_Node[check].m_state = 2;
			m_Node[check].check   = 2;
			Combo+=1;
			MAXGOOD +=1;
			if(Combo >= 3)
			{
				MAXCOMBO+=1;
				m_IMax_Combo+=1;

			}
			score_OK(0, Combo,51);
		}
		else if(m_Node[check].Node_Check <= 33 && m_Node[check].Node_Check > 20)
		{ // 퍼펙
			m_Node[check].m_state = 2;
			m_Node[check].check  = 1;
			Combo+=1;
			MAXPERFECT +=1;
			if(Combo >= 3)
			{
				MAXCOMBO+=1;
				m_IMax_Combo +=1;
			}
			score_OK(1, Combo,103);
		}
		else // 미스
		{
			m_Node[check].m_state =2;
			m_Node[check].check  = 3;
			MAXMISS		+=1;
			Combo = 0;
			m_IMax_Combo =0;
		}
	}
	if(MUSIC != PRACTICE)
	{
		if(m_Node[check].color  !=	color)  
		{
			m_Node[check].check = 3;
			m_Node[check].m_state =2;
			MAXMISS		+=1;
			Combo = 0;
			m_IMax_Combo = 0;
		}
	}
}
