# Microsoft Developer Studio Project File - Name="WilliamsCRC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=WilliamsCRC - Win32 Debug Multithreaded
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "WilliamsCRC.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "WilliamsCRC.mak" CFG="WilliamsCRC - Win32 Debug Multithreaded"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "WilliamsCRC - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WilliamsCRC - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "WilliamsCRC - Win32 Debug pseudoUNIX" (based on "Win32 (x86) Static Library")
!MESSAGE "WilliamsCRC - Win32 Debug Multithreaded" (based on "Win32 (x86) Static Library")
!MESSAGE "WilliamsCRC - Win32 Release Multithreaded" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WilliamsCRC - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.lib"
# ADD LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.lib"

!ELSEIF  "$(CFG)" == "WilliamsCRC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.debug.lib"
# ADD LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.debug.lib"

!ELSEIF  "$(CFG)" == "WilliamsCRC - Win32 Debug pseudoUNIX"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugUnix"
# PROP BASE Intermediate_Dir "DebugUnix"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugUnix"
# PROP Intermediate_Dir "DebugUnix"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /I "$(UNIXEM)/include" /D "UNIX" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_STLSOFT_FORCE_ANY_COMPILER" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /I "$(UNIXEM)/include" /D "UNIX" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_STLSOFT_FORCE_ANY_COMPILER" /YX /FD /GZ /c
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.unix.debug.lib"
# ADD LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.unix.debug.lib"

!ELSEIF  "$(CFG)" == "WilliamsCRC - Win32 Debug Multithreaded"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMt"
# PROP BASE Intermediate_Dir "DebugMt"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMt"
# PROP Intermediate_Dir "DebugMt"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.mt.debug.lib"
# ADD LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.mt.debug.lib"

!ELSEIF  "$(CFG)" == "WilliamsCRC - Win32 Release Multithreaded"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMt"
# PROP BASE Intermediate_Dir "ReleaseMt"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMt"
# PROP Intermediate_Dir "ReleaseMt"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../wcrc" /I "../include" /I "$(STLSOFT)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.mt.lib"
# ADD LIB32 /nologo /out:"..\lib\SynesisSoftware.WilliamsCRC.1.core.vc6.mt.lib"

!ENDIF

# Begin Target

# Name "WilliamsCRC - Win32 Release"
# Name "WilliamsCRC - Win32 Debug"
# Name "WilliamsCRC - Win32 Debug pseudoUNIX"
# Name "WilliamsCRC - Win32 Debug Multithreaded"
# Name "WilliamsCRC - Win32 Release Multithreaded"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\WilliamsCRC.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "STLSoft"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT_1_10)\include\stlsoft\internal\head_version.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT_1_10)\include\stlsoft\internal\lead_version.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT_1_10)\include\stlsoft\internal\cccap\msvc.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT_1_10)\include\stlsoft\internal\cccap\obsolete.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT_1_10)\include\stlsoft\internal\safestr.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT_1_10)\include\stlsoft\smartptr\scoped_handle.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT_1_10)\include\stlsoft\stlsoft.h"
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE="..\wcrc\crcmodel.cpp"

!IF  "$(CFG)" == "WilliamsCRC - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "WilliamsCRC - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "WilliamsCRC - Win32 Debug pseudoUNIX"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "WilliamsCRC - Win32 Debug Multithreaded"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "WilliamsCRC - Win32 Release Multithreaded"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF

# End Source File
# Begin Source File

SOURCE="..\wcrc\crcmodel.h"
# End Source File
# Begin Source File

SOURCE=..\include\WilliamsCRC\WilliamsCRC.h
# End Source File
# End Group
# End Target
# End Project
