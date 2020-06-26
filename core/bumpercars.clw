; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Multiplayer
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "bumpercars.h"

ClassCount=7
Class1=CBumpercarsApp
Class2=CBumpercarsDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_MULTIPLAYER
Resource2=IDR_MAINFRAME
Resource3=IDD_CHOOSECAR_DIALOG
Class4=Multiplayer
Resource4=IDD_BUMPERCARS_DIALOG
Class5=Options
Resource5=IDD_ABOUTBOX
Class6=choosetrack
Resource6=IDD_CHOOSETRACK_DIALOG
Class7=choosecar
Resource7=IDD_OPTIONS_DIALOG

[CLS:CBumpercarsApp]
Type=0
HeaderFile=bumpercars.h
ImplementationFile=bumpercars.cpp
Filter=N

[CLS:CBumpercarsDlg]
Type=0
HeaderFile=bumpercarsDlg.h
ImplementationFile=bumpercarsDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_HELPBUTTON

[CLS:CAboutDlg]
Type=0
HeaderFile=bumpercarsDlg.h
ImplementationFile=bumpercarsDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=10
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_BUMPERCARS_DIALOG]
Type=1
Class=CBumpercarsDlg
ControlCount=9
Control1=IDC_STATIC,static,1342242830
Control2=IDC_PLAY,{D7053240-CE69-11CD-A777-00DD01143C57},1342242816
Control3=IDCANCEL,{D7053240-CE69-11CD-A777-00DD01143C57},1342242816
Control4=IDC_OPTIONS,{D7053240-CE69-11CD-A777-00DD01143C57},1342242816
Control5=IDC_CHOOSECAR,{D7053240-CE69-11CD-A777-00DD01143C57},1342242816
Control6=IDC_CHOOSETRACK,{D7053240-CE69-11CD-A777-00DD01143C57},1342242816
Control7=IDC_MULTIPLAYER,{D7053240-CE69-11CD-A777-00DD01143C57},1342242816
Control8=IDC_HELPBUTTON,button,1342242816
Control9=IDC_MEDIAPLAYER1,{22D6F312-B0F6-11D0-94AB-0080C74C7E95},1342242816

[DLG:IDD_MULTIPLAYER]
Type=1
Class=Multiplayer
ControlCount=21
Control1=IDCANCEL,button,1342242816
Control2=IDC_CREATE,button,1342242816
Control3=IDC_JOIN,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_CHATBOX,listbox,1084293377
Control8=IDC_MESSAGE,edit,1082196096
Control9=IDC_SEND,button,1073807360
Control10=IDC_STARTGAME,button,1073807360
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CONNECTED,edit,1350631552
Control13=IDC_MPLAYERNAME1,static,1342308352
Control14=IDC_MPLAYERNAME2,static,1342308352
Control15=IDC_MPLAYERTRACK,static,1342308352
Control16=IDC_MPLAYERNO,static,1342308352
Control17=IDC_STATIC,button,1342177287
Control18=IDC_MPLAYERMODE,static,1342308352
Control19=IDC_IPX,button,1342242825
Control20=IDC_TCPIP,button,1342242825
Control21=IDC_DPLAYCONTROL1,{EF4CC33A-EE02-4C52-800A-DB5F40AB119C},1073807360

[CLS:Multiplayer]
Type=0
HeaderFile=Multiplayer.h
ImplementationFile=Multiplayer.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DPLAYCONTROL1
VirtualFilter=dWC

[DLG:IDD_CHOOSECAR_DIALOG]
Type=1
Class=choosecar
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CCPLAYER1,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_CCPLAYER2,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_PLAYER1CAR,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_PLAYER2CAR,static,1342308352

[DLG:IDD_CHOOSETRACK_DIALOG]
Type=1
Class=choosetrack
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO1,button,1342177289
Control5=IDC_STATIC,static,1342177294
Control6=IDC_RADIO2,button,1342177289
Control7=IDC_RADIO3,button,1342177289
Control8=IDC_RADIO4,button,1342177289
Control9=IDC_STATIC,static,1342177294
Control10=IDC_STATIC,static,1342177294
Control11=IDC_STATIC,static,1342177294

[CLS:choosetrack]
Type=0
HeaderFile=choosetrack.h
ImplementationFile=choosetrack.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=choosetrack

[DLG:IDD_OPTIONS_DIALOG]
Type=1
Class=Options
ControlCount=21
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PLAYERNAME1,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_PLAYERNAME2,edit,1350631552
Control8=IDC_STATIC,button,1342177287
Control9=IDC_RADIO1,button,1342177289
Control10=IDC_RADIO2,button,1342177289
Control11=IDC_STATIC,button,1342177287
Control12=IDC_RADIO3,button,1342308361
Control13=IDC_RADIO4,button,1342177289
Control14=IDC_RADIO0,button,1342177289
Control15=IDC_STATIC,button,1342177287
Control16=IDC_LAPS,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_TIME,edit,1350631552
Control21=IDC_STATIC,static,1342308352

[CLS:Options]
Type=0
HeaderFile=Options.h
ImplementationFile=Options.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LAPS
VirtualFilter=dWC

[CLS:choosecar]
Type=0
HeaderFile=choosecar.h
ImplementationFile=choosecar.cpp
BaseClass=CDialog
Filter=D
LastObject=IDCANCEL
VirtualFilter=dWC

