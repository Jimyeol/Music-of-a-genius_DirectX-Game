#ifndef _cBaseNote_H
#define _cBaseNote_H

#include "MyInclude.h"
#include <KGEmotion.h>
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "KGEmotionD.lib")
#else
#pragma comment(lib, "KGEmotion.lib")
#endif
using namespace KG;

#include <vector>
using namespace std;

class cKey;

class cBaseNote
{
public:
	vector<KGString>		m_Table;
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGRenderMulti*			m_pBangEffect;
	KGRenderMulti*			m_pEffect[EFFECT];
	KGRenderMulti*			m_pPracticeClick[1];
	int						m_nJudEffect;
	int						m_nNoteKind;
	float					m_nNoteX;
	float					m_nNoteY;
	bool					m_bComboBefore;
	bool					m_bComboOneCheck;
	KGRect					Judger_rNode;
	int						Judge_Node_X_Check;
	bool					m_Judger_Node_Dead;
	bool					m_bCollusionCheck;
	bool					m_Judger_Node_Cool;
	bool					m_Judger_Node_Perfect;
	bool					m_Judger_Node_Miss;
	bool					m_bObject;
	int						m_nKeyNumber;
	bool					m_nMissBefore;
	bool					m_nMissBefore2;
	float					m_check;


public:
	

public:
	cBaseNote();
	cBaseNote(KGAnimate* pAnimate, int Node_Index, float x, float y, int KeyNumber);
	~cBaseNote();


public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void					KeyCheck();
	void					KeyCheckRender(int Key);
	
};

#endif