; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVLCDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VLCDemo.h"

ClassCount=3
Class1=CVLCDemoApp
Class2=CVLCDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_VLCDEMO_DIALOG

[CLS:CVLCDemoApp]
Type=0
HeaderFile=VLCDemo.h
ImplementationFile=VLCDemo.cpp
Filter=N

[CLS:CVLCDemoDlg]
Type=0
HeaderFile=VLCDemoDlg.h
ImplementationFile=VLCDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_ISRTSP

[CLS:CAboutDlg]
Type=0
HeaderFile=VLCDemoDlg.h
ImplementationFile=VLCDemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VLCDEMO_DIALOG]
Type=1
Class=CVLCDemoDlg
ControlCount=11
Control1=IDC_VIDEO_PATH,edit,1350631552
Control2=IDC_SELECT_VIDEO,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PLAY,button,1342242816
Control5=IDC_PAUSE,button,1342242816
Control6=IDC_STOP,button,1342242816
Control7=IDC_PLAYTIME,msctls_trackbar32,1342242840
Control8=IDC_VOLUME,msctls_trackbar32,1342242840
Control9=IDC_STATIC_PIC,static,1342177543
Control10=IDC_BTN_TEST,button,1342242816
Control11=IDC_ISRTSP,button,1342242819

