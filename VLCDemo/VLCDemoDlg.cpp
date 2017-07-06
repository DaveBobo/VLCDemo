// VLCDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VLCDemo.h"
#include "VLCDemoDlg.h"
// #include "vlc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

char* EncodeToUTF8(const char* mbcsStr) 
{ 
	 wchar_t*  wideStr; 
	 char*   utf8Str; 
	 int   charLen; 

	 charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0); 
	 wideStr = (wchar_t*) malloc(sizeof(wchar_t)*charLen); 
	 MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen); 

	 charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL); 

	 utf8Str = (char*) malloc(charLen);

	 WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);

	 free(wideStr); 
	 return utf8Str;
} 

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
		ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVLCDemoDlg dialog

CVLCDemoDlg::CVLCDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVLCDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVLCDemoDlg)
	m_VideoPath = _T("");
	m_isRTSP = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
 	m_vlcInst = NULL;
 	m_vlcMedia = NULL;
 	m_vlcMplay = NULL;
 	m_bNew = true;
	m_bIsRtsp = true;
// 	m_playerTimer = 0;
	
// 
// 	const char* const m_vlcArgs[] = {
//               "-I", "dummy", /* Don't use any interface */
//               "--ignore-config", /* Don't use VLC's config */ 
// 				};
// 
// 	libvlc_exception_init(&m_vlcEx);
// 	m_vlcInst = libvlc_new(sizeof(m_vlcArgs) / sizeof(m_vlcArgs[0]), m_vlcArgs, &m_vlcEx);
}

void CVLCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVLCDemoDlg)
	DDX_Control(pDX, IDC_VOLUME, m_SliderVolume);
	DDX_Control(pDX, IDC_PLAYTIME, m_SliderPlayer);
	DDX_Text(pDX, IDC_VIDEO_PATH, m_VideoPath);
	DDX_Check(pDX, IDC_ISRTSP, m_isRTSP);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVLCDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CVLCDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_SELECT_VIDEO, OnSelectVideo)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
	ON_EN_CHANGE(IDC_VIDEO_PATH, OnChangeVideoPath)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_ISRTSP, OnIsrtsp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVLCDemoDlg message handlers

BOOL CVLCDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetWindowText("vlcRTSP");
	/*char *vlc_argv[100];
	int vlc_argc = 0;
	vlc_argv[vlc_argc++] = "--ignore-config";

	m_vlcInst = libvlc_new (vlc_argc, vlc_argv);*/

	m_SliderPlayer.SetRange(0, 1000);
	m_SliderPlayer.SetPos(0);

	m_SliderVolume.SetRange(0,100);
	m_SliderVolume.SetPos(100);

	m_vlcInst = libvlc_new(0, NULL);

	//初始化Check控件为选中,暂停、进度控制等默认会灰色
	((CButton*)GetDlgItem(IDC_ISRTSP))->SetCheck(TRUE);
	GetDlgItem(IDC_SELECT_VIDEO)->EnableWindow(false);
	GetDlgItem(IDC_PLAYTIME)->EnableWindow(false);
	GetDlgItem(IDC_PAUSE)->EnableWindow(false);
	//GetDlgItem(IDC_IPADDRESS1)->EnableWindow(false);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVLCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVLCDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	//设置播放窗口为黑色
#if 1
	CBrush *oldBursh, brNew;
	HWND hWnd = GetDlgItem(IDC_STATIC_PIC)->GetSafeHwnd();
	brNew.CreateSolidBrush(RGB(0, 0, 0));		
	HDC hDC = ::GetDC(hWnd);
	CDC *pDC = CDC::FromHandle(hDC);
	oldBursh = pDC->SelectObject(&brNew);	

	CRect rect2;
	::GetClientRect(hWnd, &rect2);	 
	pDC->Rectangle(rect2);
	pDC->SelectObject(oldBursh);
#endif
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVLCDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CVLCDemoDlg::OnPlay() 
{
	//if(m_bNew == true)
	
	UpdateData(true);
	if (m_VideoPath == "")
	{
		return;
	}
	if(m_bNew == true)
	{
		if(m_vlcMplay != NULL)
		{
			libvlc_media_player_release(m_vlcMplay);
		}
		if (m_bIsRtsp == false)
		{
			//本地文件
			m_vlcMedia = libvlc_media_new_path (m_vlcInst, EncodeToUTF8(m_VideoPath.GetBuffer(0)));
		}
		else
		{
			//m_vlcMedia = libvlc_media_new_location(m_vlcInst,m_VideoPath.GetBuffer(0));
			m_vlcMedia = libvlc_media_new_location(m_vlcInst, m_VideoPath.GetBuffer(0));
		}
		
		m_vlcMplay = libvlc_media_player_new_from_media (m_vlcMedia);
		HWND hwnd = GetDlgItem(IDC_STATIC_PIC)->GetSafeHwnd();
		libvlc_media_player_set_hwnd (m_vlcMplay, hwnd);
		libvlc_media_release(m_vlcMedia);
		m_bNew = false;
	}

	libvlc_media_player_play (m_vlcMplay);
	if (m_bIsRtsp == false)
	{
		m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);
		m_playerTimer = SetTimer(100,1*100,NULL);
	}
}

void CVLCDemoDlg::OnSelectVideo() 
{
	// TODO: Add your control notification handler code here
	
	TCHAR BASED_CODE szFilter[] = _T("Video Files All Files (*.*)|*.*||");
	CFileDialog fileDlg (TRUE, _T("Video file"), _T(""), OFN_FILEMUSTEXIST, szFilter, this);
	if(fileDlg.DoModal() == IDOK)
	{
		m_VideoPath = fileDlg.GetPathName();
		m_bNew = true;
	}
	UpdateData(FALSE);
}

void CVLCDemoDlg::OnPause() 
{
	// TODO: Add your control notification handler code here
 	if(m_vlcMplay != NULL)
 		libvlc_media_player_pause(m_vlcMplay);
}

void CVLCDemoDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	if (m_vlcMplay == NULL)
	{
		return;
	}
 	libvlc_media_player_stop(m_vlcMplay);
 	m_bNew = true;
	m_vlcMplay = NULL;
 	//libvlc_exception_clear(&m_vlcEx);
	if (m_vlcMedia != NULL)
	{
		libvlc_media_release(m_vlcMedia);
	}
	if (m_vlcMplay != NULL)
	{
		libvlc_media_player_release(m_vlcMplay);
	}
	KillTimer(100);
	m_SliderPlayer.SetPos(0);
	OnPaint();
}

void CVLCDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 100)
	{
		libvlc_time_t m_CurTime = libvlc_media_player_get_time(m_vlcMplay);
		//float fPos = libvlc_media_player_get_position(m_vlcMplay, &m_vlcEx);
		m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);
 		int m_npos = m_CurTime*1000/m_TotalTime;
 		m_SliderPlayer.SetPos(m_npos);
	}
	if(libvlc_Ended == libvlc_media_player_get_state(m_vlcMplay))//获取播放状态的函数,如果是结束就发送stop命令，更改状态。
		OnStop();

	CDialog::OnTimer(nIDEvent);
}

//拖动进度条控制
 void CVLCDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
 {
 	if (pScrollBar->GetSafeHwnd() == m_SliderPlayer.GetSafeHwnd())
 	{
		if (m_vlcMplay != NULL)
		{
			libvlc_time_t m_CurTime;
			m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);
			double pos = m_SliderPlayer.GetPos()/1000.0;
			m_CurTime = m_TotalTime * pos;
			libvlc_media_player_set_time(m_vlcMplay,m_CurTime);
		}
 	}
	else if (pScrollBar->GetSafeHwnd() == m_SliderVolume.GetSafeHwnd())
 	{
 		if (m_vlcMplay != NULL)
 		{
			int iVolume = m_SliderVolume.GetPos();
			libvlc_audio_set_volume(m_vlcMplay,iVolume);//取值范围为0-50
 		}
 	} 
	else
 	{
 		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
 	}
 }

void CVLCDemoDlg::OnBtnTest() 
{
	// TODO: Add your control notification handler code here
//  	libvlc_audio_set_volume(m_vlcMplay,200);
	//libvlc_set_fullscreen(m_vlcMplay,2);
//   	int i  = libvlc_get_version();
//   	CString str;
//  	str.Format("%d",i);
//   	MessageBox(str);
// // 	
}

// void CVLCDemoDlg::OnStaticPic() 
// {
// 	// TODO: Add your control notification handler code here
// 	MessageBox("tset");
// }

// void CVLCDemoDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
// {
// 	// TODO: Add your message handler code here and/or call default
// 
// 		CRect pin;
// 		GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&pin);
// 		ScreenToClient(&pin); 
// 		
// 		if(pin.PtInRect(point))
// 			AfxMessageBox("str");
// 		else
// 			AfxMessageBox("stdfsdfr");
// 	
// 	CDialog::OnLButtonDblClk(nFlags, point);
// }

//捕获Esc实现全屏
BOOL CVLCDemoDlg::PreTranslateMessage(MSG* pMsg)
{	
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN) 
		{
			//SetFullScreen();
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CVLCDemoDlg::OnChangeVideoPath() 
{
	//当文本框中的值被修改后，应该标示文件为新文件
	m_bNew = true;
}

void CVLCDemoDlg::OnIsrtsp() 
{
	// TODO: Add your control notification handler code here
	if(true == ((CButton *)GetDlgItem(IDC_ISRTSP))->GetCheck())
	{
		//rtsp
		GetDlgItem(IDC_SELECT_VIDEO)->EnableWindow(false);
		GetDlgItem(IDC_PLAYTIME)->EnableWindow(false);
		GetDlgItem(IDC_PAUSE)->EnableWindow(false);
		m_bIsRtsp = true;
	}
	else
	{
		GetDlgItem(IDC_SELECT_VIDEO)->EnableWindow(true);
		GetDlgItem(IDC_PLAYTIME)->EnableWindow(true);
		GetDlgItem(IDC_PAUSE)->EnableWindow(true);
		m_bIsRtsp = FALSE;
	}
}
