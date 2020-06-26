# Microsoft Developer Studio Project File - Name="bumpercars" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=bumpercars - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bumpercars.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bumpercars.mak" CFG="bumpercars - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bumpercars - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "bumpercars - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bumpercars - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 dinput.lib ddraw.lib dxguid.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\Program Files\Microsoft Visual Studio\VC98\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /u
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ddraw.lib dinput.lib dxguid.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"C:\Program Files\Microsoft Visual Studio\VC98\Lib"

!ENDIF 

# Begin Target

# Name "bumpercars - Win32 Release"
# Name "bumpercars - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bumpercars.cpp
# End Source File
# Begin Source File

SOURCE=.\bumpercars.rc
# End Source File
# Begin Source File

SOURCE=.\bumpercarsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\car.cpp
# End Source File
# Begin Source File

SOURCE=.\choosecar.cpp
# End Source File
# Begin Source File

SOURCE=.\choosetrack.cpp
# End Source File
# Begin Source File

SOURCE=.\commandbutton.cpp
# End Source File
# Begin Source File

SOURCE=.\functions.cpp
# End Source File
# Begin Source File

SOURCE=.\mainplay.cpp
# End Source File
# Begin Source File

SOURCE=.\Multiplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Options.cpp
# End Source File
# Begin Source File

SOURCE=.\playcontrol1.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Track.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bumpercars.h
# End Source File
# Begin Source File

SOURCE=.\bumpercarsDlg.h
# End Source File
# Begin Source File

SOURCE=.\car.h
# End Source File
# Begin Source File

SOURCE=.\choosecar.h
# End Source File
# Begin Source File

SOURCE=.\choosetrack.h
# End Source File
# Begin Source File

SOURCE=.\commandbutton.h
# End Source File
# Begin Source File

SOURCE=.\functions.h
# End Source File
# Begin Source File

SOURCE=.\mainplay.h
# End Source File
# Begin Source File

SOURCE=.\Multiplayer.h
# End Source File
# Begin Source File

SOURCE=.\Options.h
# End Source File
# Begin Source File

SOURCE=.\playcontrol1.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Track.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bumpercars.ico
# End Source File
# Begin Source File

SOURCE=.\res\bumpercars.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Cars.ico
# End Source File
# Begin Source File

SOURCE=.\maps\junkyardthumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menuback.bmp
# End Source File
# Begin Source File

SOURCE=.\maps\metalthumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\playb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\playd.bmp
# End Source File
# Begin Source File

SOURCE=.\maps\thnksthumb.bmp
# End Source File
# Begin Source File

SOURCE=.\maps\track256thumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\track256thumb.bmp
# End Source File
# End Group
# End Target
# End Project
# Section bumpercars : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section bumpercars : {D7053240-CE69-11CD-A777-00DD01143C57}
# 	2:21:DefaultSinkHeaderFile:commandbutton.h
# 	2:16:DefaultSinkClass:CCommandButton
# End Section
# Section bumpercars : {917E2CBA-2A02-4B73-A6E9-829675046372}
# 	2:5:Class:CPlayControl
# 	2:10:HeaderFile:playcontrol1.h
# 	2:8:ImplFile:playcontrol1.cpp
# End Section
# Section bumpercars : {4C599241-6926-101B-9992-00000B65C6F9}
# 	2:21:DefaultSinkHeaderFile:image.h
# 	2:16:DefaultSinkClass:CImage
# End Section
# Section bumpercars : {04598FC4-866C-11CF-AB7C-00AA00C08FCF}
# 	2:5:Class:CCommandButton
# 	2:10:HeaderFile:commandbutton.h
# 	2:8:ImplFile:commandbutton.cpp
# End Section
# Section bumpercars : {6EFAC6F0-4252-43C8-8EAC-61F49198D400}
# 	2:21:DefaultSinkHeaderFile:playcontrol1.h
# 	2:16:DefaultSinkClass:CPlayControl
# End Section
# Section bumpercars : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section bumpercars : {4C599243-6926-101B-9992-00000B65C6F9}
# 	2:5:Class:CImage
# 	2:10:HeaderFile:image.h
# 	2:8:ImplFile:image.cpp
# End Section
