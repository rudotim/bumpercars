# Microsoft Developer Studio Generated NMAKE File, Based on bumpercars.dsp
!IF "$(CFG)" == ""
CFG=bumpercars - Win32 Debug
!MESSAGE No configuration specified. Defaulting to bumpercars - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "bumpercars - Win32 Release" && "$(CFG)" != "bumpercars - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "bumpercars - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\bumpercars.exe"


CLEAN :
	-@erase "$(INTDIR)\bumpercars.obj"
	-@erase "$(INTDIR)\bumpercars.pch"
	-@erase "$(INTDIR)\bumpercars.res"
	-@erase "$(INTDIR)\bumpercarsDlg.obj"
	-@erase "$(INTDIR)\car.obj"
	-@erase "$(INTDIR)\choosetrack.obj"
	-@erase "$(INTDIR)\commandbutton.obj"
	-@erase "$(INTDIR)\functions.obj"
	-@erase "$(INTDIR)\mainplay.obj"
	-@erase "$(INTDIR)\Multiplayer.obj"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\playcontrol1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Track.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\bumpercars.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bumpercars.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\bumpercars.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bumpercars.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=dinput.lib ddraw.lib dxguid.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\bumpercars.pdb" /machine:I386 /out:"$(OUTDIR)\bumpercars.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bumpercars.obj" \
	"$(INTDIR)\bumpercarsDlg.obj" \
	"$(INTDIR)\car.obj" \
	"$(INTDIR)\choosetrack.obj" \
	"$(INTDIR)\commandbutton.obj" \
	"$(INTDIR)\functions.obj" \
	"$(INTDIR)\mainplay.obj" \
	"$(INTDIR)\Multiplayer.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\playcontrol1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Track.obj" \
	"$(INTDIR)\bumpercars.res"

"$(OUTDIR)\bumpercars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\bumpercars.exe" "$(OUTDIR)\bumpercars.bsc"


CLEAN :
	-@erase "$(INTDIR)\bumpercars.obj"
	-@erase "$(INTDIR)\bumpercars.pch"
	-@erase "$(INTDIR)\bumpercars.res"
	-@erase "$(INTDIR)\bumpercars.sbr"
	-@erase "$(INTDIR)\bumpercarsDlg.obj"
	-@erase "$(INTDIR)\bumpercarsDlg.sbr"
	-@erase "$(INTDIR)\car.obj"
	-@erase "$(INTDIR)\car.sbr"
	-@erase "$(INTDIR)\choosetrack.obj"
	-@erase "$(INTDIR)\choosetrack.sbr"
	-@erase "$(INTDIR)\commandbutton.obj"
	-@erase "$(INTDIR)\commandbutton.sbr"
	-@erase "$(INTDIR)\functions.obj"
	-@erase "$(INTDIR)\functions.sbr"
	-@erase "$(INTDIR)\mainplay.obj"
	-@erase "$(INTDIR)\mainplay.sbr"
	-@erase "$(INTDIR)\Multiplayer.obj"
	-@erase "$(INTDIR)\Multiplayer.sbr"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\Options.sbr"
	-@erase "$(INTDIR)\playcontrol1.obj"
	-@erase "$(INTDIR)\playcontrol1.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Track.obj"
	-@erase "$(INTDIR)\Track.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\bumpercars.bsc"
	-@erase "$(OUTDIR)\bumpercars.exe"
	-@erase "$(OUTDIR)\bumpercars.ilk"
	-@erase "$(OUTDIR)\bumpercars.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\bumpercars.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\bumpercars.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bumpercars.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\bumpercars.sbr" \
	"$(INTDIR)\bumpercarsDlg.sbr" \
	"$(INTDIR)\car.sbr" \
	"$(INTDIR)\choosetrack.sbr" \
	"$(INTDIR)\commandbutton.sbr" \
	"$(INTDIR)\functions.sbr" \
	"$(INTDIR)\mainplay.sbr" \
	"$(INTDIR)\Multiplayer.sbr" \
	"$(INTDIR)\Options.sbr" \
	"$(INTDIR)\playcontrol1.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Track.sbr"

"$(OUTDIR)\bumpercars.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=ddraw.lib dinput.lib dxguid.lib winmm.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\bumpercars.pdb" /debug /machine:I386 /out:"$(OUTDIR)\bumpercars.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\bumpercars.obj" \
	"$(INTDIR)\bumpercarsDlg.obj" \
	"$(INTDIR)\car.obj" \
	"$(INTDIR)\choosetrack.obj" \
	"$(INTDIR)\commandbutton.obj" \
	"$(INTDIR)\functions.obj" \
	"$(INTDIR)\mainplay.obj" \
	"$(INTDIR)\Multiplayer.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\playcontrol1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Track.obj" \
	"$(INTDIR)\bumpercars.res"

"$(OUTDIR)\bumpercars.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("bumpercars.dep")
!INCLUDE "bumpercars.dep"
!ELSE 
!MESSAGE Warning: cannot find "bumpercars.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "bumpercars - Win32 Release" || "$(CFG)" == "bumpercars - Win32 Debug"
SOURCE=.\bumpercars.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\bumpercars.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\bumpercars.obj"	"$(INTDIR)\bumpercars.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\bumpercars.rc

"$(INTDIR)\bumpercars.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\bumpercarsDlg.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\bumpercarsDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\bumpercarsDlg.obj"	"$(INTDIR)\bumpercarsDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\car.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\car.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\car.obj"	"$(INTDIR)\car.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\choosecar.cpp
SOURCE=.\choosetrack.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\choosetrack.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\choosetrack.obj"	"$(INTDIR)\choosetrack.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\commandbutton.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\commandbutton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\commandbutton.obj"	"$(INTDIR)\commandbutton.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\functions.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\functions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\functions.obj"	"$(INTDIR)\functions.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\mainplay.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\mainplay.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\mainplay.obj"	"$(INTDIR)\mainplay.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\Multiplayer.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\Multiplayer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\Multiplayer.obj"	"$(INTDIR)\Multiplayer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\Options.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\Options.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\Options.obj"	"$(INTDIR)\Options.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\picture1.cpp
SOURCE=.\playcontrol1.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\playcontrol1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\playcontrol1.obj"	"$(INTDIR)\playcontrol1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\bumpercars.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\bumpercars.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\bumpercars.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\bumpercars.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Track.cpp

!IF  "$(CFG)" == "bumpercars - Win32 Release"


"$(INTDIR)\Track.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ELSEIF  "$(CFG)" == "bumpercars - Win32 Debug"


"$(INTDIR)\Track.obj"	"$(INTDIR)\Track.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bumpercars.pch"


!ENDIF 


!ENDIF 

