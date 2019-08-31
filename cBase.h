#ifndef _cBase_H
#define _cBase_H

#include "MyInclude.h"
#include "cBaseLoad.h"
#include <irrKlang.h>

using namespace irrklang;
using namespace KG;
#define CLICK 5


enum
{
	BAR_D = 0,
	BAR_F,
	BAR_J,
	BAR_K,
	BAR_SPACE,
};
class cBaseLoad;
class cBase : public KGScene,KGResponseDialog
{
public:

	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGRenderSingle*			m_pSingle;
	KGRenderSingle*			m_pEffect[EFFECT];
	KGRenderMulti*			m_pClickWhat[CLICK];
	cBaseLoad*				m_pBaseLoad;
	KGRenderMulti*			m_pMulti;

	KGDialog*				m_pDialog;
	KGDialog*				m_pDialog2;
	KGDialog*				m_pEnegy;
	KGCursor*				m_pCursor;
	KGSound*				m_pSound;
	KGRenderSingle*			m_pBaseClick[BASECLICK_MAX];
	int						m_nBaseState;
	int						m_nLayers;
	int						Node_Index;
	int						Judge_Bar_X;
	int						Judge_Bar_Y;
	KGRect					Judger_rBar;
	bool					m_bPause;
	DWORD					m_dwChage_time;
	int						m_nXCheck;
	int						m_nYCheck;
	int						m_nCombo;
	int						m_nResultNote;
	int						good;
	int						m_nClickState;

	float					m_fProgress;

public:


public:
	cBase();
	~cBase();


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
	void					Base_Music_Load(const WCHAR *pFileName);
	void					DecodeBase(FILE* fp);
	void					KeySettingCheckPark(int Key = 0);
	void CALLBACK			OnEvent(UINT id, int xPos, int yPos);
	void					score_OK(int effect , int combo,int score);

};

#endif