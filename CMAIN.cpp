#include "CMAIN.h"

IMPLEMENT_MAIN(CMAIN);

CMAIN::CMAIN() : KGEmotion(L"MOAG", 1024, 768)
{
	g_MusicState = 0;
	g_InstrumentState= 1;
	g_AlphaBar				= 1;
	g_DrumCombo				= 0;
	g_score					= 0;
	g_nownode				= 0;
	g_maxnode				= 0;
	g_test					= 0;
	g_perfect				= 0;
	g_good					= 0;
	g_miss					= 0;
	g_maxcombo				= 0;
	g_Ilevel				= 1;
	m_pMain					= this;
	g_pSound = createIrrKlangDevice();
	DrumSound				= 0 ;
	JembeSound				= 0;
	BaseSound				= 0;

#if defined(NDEBUG)
	SetFullScreenBackBufferWidthAtModeChange(1024);
	SetFullScreenBackBufferHeightAtModeChange(768);
	SetOverrideWidth(1024);
	SetOverrideHeight(768);
	SetOverrideFullScreen(true);
	SetHandleAltEnter(false);
	SetHandleDefaultHotkeys(false);
	SetShowMsgBoxOnError(true);
	SetShowCursorWhenFullScreen(false);
#endif
}


CMAIN::~CMAIN()
{
	g_pSound->drop();
	
}

void CMAIN::Create()
{
	Entry(L"logo", new cLogo);
	Entry(L"menu", new cMenu);
	Entry(L"mode", new cMode);
	Entry(L"jembe",new cJembe);
	Entry(L"choic",new cMusicChoice);
	Entry(L"drum", new cDrum);
	Entry(L"base", new cBase);
	Entry(L"rank",new cRank);
	Entry(L"score",new cScore);



}


void CMAIN::Init()
{
	Trans(L"logo");
}