/***************************************************************
 * Name:      wxWin32Main.h
 * Purpose:   Defines Application Frame
 * Author:    liangdi (404579707@qq.com)
 * Created:   2013-06-20
 * Copyright: liangdi ()
 * License:
 **************************************************************/

#ifndef WXWIN32MAIN_H
#define WXWIN32MAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wxWin32App.h"

class wxWin32Frame: public wxFrame
{
    public:
        wxWin32Frame(wxFrame *frame, const wxString& title);
        ~wxWin32Frame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // WXWIN32MAIN_H
