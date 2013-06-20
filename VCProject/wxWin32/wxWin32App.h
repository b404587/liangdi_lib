/***************************************************************
 * Name:      wxWin32App.h
 * Purpose:   Defines Application Class
 * Author:    liangdi (404579707@qq.com)
 * Created:   2013-06-20
 * Copyright: liangdi ()
 * License:
 **************************************************************/

#ifndef WXWIN32APP_H
#define WXWIN32APP_H

#include <wx/app.h>

class wxWin32App : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // WXWIN32APP_H
