// VLCDemoDlg.h : header file
//

#if !defined(AFX_VLCDEMODLG_H__27B40B69_F36F_4AA6_BB6D_47B061A32F9A__INCLUDED_)
#define AFX_VLCDEMODLG_H__27B40B69_F36F_4AA6_BB6D_47B061A32F9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVLCDemoDlg dialog
#include "vlc.h"

class CVLCDemoDlg : public CDialog
{
// Construction
public:
	CVLCDemoDlg(CWnd* pParent = NULL);	// standard constructor
public:
// 	libvlc_instance_t* m_pInstance;
// 	libvlc_media_t* m_pMedia;
// 	libvlc_media_player_t* m_pMediaPlayer;
// 	HWND		m_hWndVideo;
 	bool		m_bNew;

// 	libvlc_exception_t		m_vlcEx;
	libvlc_instance_t*		m_vlcInst;
	libvlc_media_player_t*	m_vlcMplay;
	libvlc_media_t*			m_vlcMedia;
// 
 	libvlc_time_t m_TotalTime;
// 	UINT m_TimerReturn;
 	UINT_PTR m_playerTimer;
	bool m_bIsRtsp;

public:
	afx_msg	void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Dialog Data
	//{{AFX_DATA(CVLCDemoDlg)
	enum { IDD = IDD_VLCDEMO_DIALOG };
	CSliderCtrl	m_SliderVolume;
	CSliderCtrl	m_SliderPlayer;
	CString	m_VideoPath;
	BOOL	m_isRTSP;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVLCDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVLCDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlay();
	afx_msg void OnSelectVideo();
	afx_msg void OnPause();
	afx_msg void OnStop();
	afx_msg void OnBtnTest();
	afx_msg void OnChangeVideoPath();
	afx_msg void OnIsrtsp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VLCDEMODLG_H__27B40B69_F36F_4AA6_BB6D_47B061A32F9A__INCLUDED_)
