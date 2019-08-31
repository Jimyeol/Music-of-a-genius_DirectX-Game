#ifndef _cDrum_H
#define _cDrum_H

#include "MyInclude.h"
#include "cDrumNote.h"
#include <irrKlang.h>

using namespace irrklang;
using namespace KG;



class cDrum : public KGScene,KGResponseDialog
{
public:
	KGSprite*				m_pSprite;
	KGSound*				m_pSound;
	KGAnimate*				m_pAnimate;
	KGRenderMulti*			m_pMulti;
	cDrumNote**				m_pDrumNote;
	KGDialog*				m_pDialog;
	KGDialog*				m_pDialog2;
	KGRenderMulti*			m_pSingle[DRUMCLICK_MAX];
	KGRenderMulti*			m_pEffect[EFFECT];
	KGRenderMulti*			m_pCombo;
	KGRenderMulti*			m_pMouse;
	KGDialog*				m_pComboNumber;
	KGCursor*				m_pCursor;
	int						m_nCCheck;
	DWORD					m_dwChage_time;
	float					Judge_Bar_X;
	float					Judge_Bar_Y;
	KGRect					Judger_rBar;
	int						m_EffectState;
	int						m_Node_Counter;
	int						m_Node_Number;
	int						Node_Index;
	int						m_nXCheck;
	int						m_nYCheck;
	int						m_nDrumState;
	float					m_ComboTime;
	int						m_nCombo;
	bool					m_bPause;
	int						m_nBackX;
	int						m_nBackX_Temp;
	int						m_nBackY;
	float					m_fTimeShake;
	bool					m_bShake;
	bool					m_bTestShake;
	int						m_iCheck;
	int						good;
	


public:

public:
	cDrum();
	~cDrum();

public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	HRESULT CALLBACK		OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);

	void CALLBACK			OnLostDevice(void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
	LRESULT CALLBACK		OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
	void CALLBACK			OnEvent(UINT id, int xPos, int yPos);
	void					Load_Node(WCHAR* pFileName);
	void					Decode_Node(FILE *pFile);
	int						F_NoteNearCheck();
	void					KeySettingCheckPark(int Number, int Key);
	void					NumberSettingCheckPark(int Number);
	void					score_OK(int effect , int combo,int score);
	void					Collusion();

};

#endif