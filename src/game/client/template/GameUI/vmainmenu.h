//========= Copyright � 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=====================================================================================//

#ifndef __VMAINMENU_H__
#define __VMAINMENU_H__

#include "basemodui.h"
#include "VFlyoutMenu.h"

namespace BaseModUI {


#define SAVE_FILENAME			"autosave.sav"
#define SAVE_DIRNAME				"SAVE"

class MainMenu : public CBaseModFrame, public IBaseModFrameListener, public FlyoutMenuListener
{
	DECLARE_CLASS_SIMPLE( MainMenu, CBaseModFrame );

public:
	MainMenu(vgui::Panel *parent, const char *panelName);
	~MainMenu();

#ifdef _X360
	void Activate();
#endif //_X360

	void UpdateVisibility();

	MESSAGE_FUNC_CHARPTR( OpenMainMenuJoinFailed, "OpenMainMenuJoinFailed", msg );
	
	//flyout menu listener
	virtual void OnNotifyChildFocus( vgui::Panel* child );
	virtual void OnFlyoutMenuClose( vgui::Panel* flyTo );
	virtual void OnFlyoutMenuCancelled();

protected:
	virtual void ApplySchemeSettings(vgui::IScheme *pScheme);
	virtual void OnCommand(const char *command);
	virtual void OnKeyCodePressed(vgui::KeyCode code);
	virtual void OnThink();
	virtual void OnOpen();
	virtual void RunFrame();
	virtual void PaintBackground();

	void	Demo_DisableButtons( void );

private:
	static void AcceptNewGameCallback( void *var );
	static void AcceptContinueGameCallback( void *var );
	static void AcceptSaveOverCallback( void *var );
	static void AcceptLoadCallback( void *var );
	static void AcceptCommentaryRulesCallback( void *var );
	static void AcceptSplitscreenDisableCallback( void *var );
	static void AcceptVersusSoftLockCallback( void *var );
	static void AcceptQuitGameCallback( void *var );

	bool CheckSaveFile();
	void SetFooterState();

	enum MainMenuQuickJoinHelpText
	{
		MMQJHT_NONE,
		MMQJHT_QUICKMATCH,
		MMQJHT_QUICKSTART,
	};
	
	int					m_iQuickJoinHelpText;
};

}

#endif // __VMAINMENU_H__
