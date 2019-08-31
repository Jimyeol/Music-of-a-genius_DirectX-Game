#ifndef _CDRUMNOTE_H
#define _CDRUMNOTE_H


#include <vector>
using namespace std;
using namespace KG;

enum
{
	EFFECTSUCCESS = 0,
	EFFECTFAIL,
};


class cDrumNote: public KGScene,KGResponseDialog
{
public:
	vector<KGString>		m_Table;
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGSound*				m_pSound;
	KGRenderSingle*			m_pDrumEffect[2];
	KGRenderMulti*			m_pPracticeClick[1];

	float					m_pFase;

	KGRenderSingle*			m_pJudge[EFFECT];
	int						m_nJudEffectState;

	int						m_Node_Number;
	int						Judge_Bar_X;
	int						Judge_Bar_Y;
	float						m_Node_x;
	int						m_Node_y;
	int						m_numberBack;
	int						m_numberFront;
	bool					m_AlphaCheck;
	int						m_NoteResult;
	KGRect					Judger_rNode;
	bool					m_Judger_Node_Dead;
	bool					m_Judger_Node_Cool;
	bool					m_Judger_Node_Miss;
	bool					m_Judger_Node_Perfect;
	bool					m_Judger_Node_Cool1;
	bool					m_Judger_Node_Miss1;
	bool					m_Judger_Node_Perfect1;
	int						Judge_Node_X_Check;
	bool					m_bSibal;
	bool					m_bObject;
	bool					m_bCollusionCheck;
	int						m_nKeyCheck;
	int						m_bNumberCheck;
	bool					m_bComboRenderCheck;
	bool					m_bComboOneCheck;
	bool					m_bComboBefore;
	bool					m_nMissBefore;
	bool					m_nMissBefore2;
	int						m_nEffectState;
	int						m_nPractice;
	bool					m_bPerfectCheck;
	int						m_nPracticeState;




	bool					m_Disable;
public:
	cDrumNote(KGAnimate* pAnimate, KGSound* pSound, int m_Node_Counter, 
		float x, int y, int number1, int number2, int NumberCheck, int KeyCheck, int Practice);
	~cDrumNote();

public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void					SetDisable(bool bDisable);
	bool					GetDisable();
	void					Judge_Funtion(int result);
	void					GetNumber(int number1, int number2);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void					KeyCheckRender(int Key);
	int						GetY();
	//IMPLEMENT_GET_SET(bool, Disable);
};

#endif