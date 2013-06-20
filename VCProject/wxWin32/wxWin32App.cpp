/***************************************************************
 * Name:      wxWin32App.cpp
 * Purpose:   Code for Application Class
 * Author:    liangdi (404579707@qq.com)
 * Created:   2013-06-20
 * Copyright: liangdi ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wxWin32App.h"
#include "wxWin32Main.h"

#ifdef _MSC_VER 
#ifdef NDEBUG
#pragma comment(lib, "wxexpat.lib")
#pragma comment(lib, "wxjpeg.lib")
#pragma comment(lib, "wxmsw29u.lib")
#pragma comment(lib, "wxmsw29u_gl.lib")
#pragma comment(lib, "wxpng.lib")
#pragma comment(lib, "wxregexu.lib")
#pragma comment(lib, "wxscintilla.lib")
#pragma comment(lib, "wxtiff.lib")
#pragma comment(lib, "wxzlib.lib")
#else
#pragma comment(lib, "wxexpatd.lib")
#pragma comment(lib, "wxjpegd.lib")
#pragma comment(lib, "wxmsw29ud.lib")
#pragma comment(lib, "wxmsw29ud_gl.lib")
#pragma comment(lib, "wxpngd.lib")
#pragma comment(lib, "wxregexud.lib")
#pragma comment(lib, "wxscintillad.lib")
#pragma comment(lib, "wxtiffd.lib")
#pragma comment(lib, "wxzlibd.lib")
#endif
#endif


IMPLEMENT_APP(wxWin32App);

bool wxWin32App::OnInit()
{
    wxWin32Frame* frame = new wxWin32Frame(0L, _("wxWidgets Application Template"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}
