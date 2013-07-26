macro MultiLineComment()  
{  
    hwnd = GetCurrentWnd()  
    selection = GetWndSel(hwnd)  
    LnFirst = GetWndSelLnFirst(hwnd)      //ȡ�����к�  
    LnLast = GetWndSelLnLast(hwnd)      //ȡĩ���к�  
    hbuf = GetCurrentBuf()  
   
    if(GetBufLine(hbuf, 0) == "//magic-number:tph85666031"){  
        stop  
    }  
   
    Ln = Lnfirst  
    buf = GetBufLine(hbuf, Ln)  
    len = strlen(buf)  
   
    while(Ln <= Lnlast) {  
        buf = GetBufLine(hbuf, Ln)  //ȡLn��Ӧ����  
        if(buf == ""){                    //��������  
            Ln = Ln + 1  
            continue  
        }  
   
        if(StrMid(buf, 0, 1) == "/") {       //��Ҫȡ��ע��,��ֹֻ�е��ַ�����  
            if(StrMid(buf, 1, 2) == "/"){  
                PutBufLine(hbuf, Ln, StrMid(buf, 2, Strlen(buf)))  
            }  
        }  
   
        if(StrMid(buf,0,1) != "/"){          //��Ҫ���ע��  
            PutBufLine(hbuf, Ln, Cat("//", buf))  
        }  
        Ln = Ln + 1  
    }  
   
    SetWndSel(hwnd, selection)  
} 

macro AddMacroComment()  
{  
    hwnd=GetCurrentWnd()  
    sel=GetWndSel(hwnd)  
    lnFirst=GetWndSelLnFirst(hwnd)  
    lnLast=GetWndSelLnLast(hwnd)  
    hbuf=GetCurrentBuf()  
   
    if(LnFirst == 0) {  
            szIfStart = ""  
    }else{  
            szIfStart = GetBufLine(hbuf, LnFirst-1)  
    }  
    szIfEnd = GetBufLine(hbuf, lnLast+1)  
    if(szIfStart == "#if 0" && szIfEnd == "#endif") {  
            DelBufLine(hbuf, lnLast+1)  
            DelBufLine(hbuf, lnFirst-1)  
            sel.lnFirst = sel.lnFirst �C 1  
            sel.lnLast = sel.lnLast �C 1  
    }else{  
            InsBufLine(hbuf, lnFirst, "#if 0")  
            InsBufLine(hbuf, lnLast+2, "#endif")  
            sel.lnFirst = sel.lnFirst + 1  
            sel.lnLast = sel.lnLast + 1  
    }  
   
    SetWndSel( hwnd, sel )  
}  

macro CommentSingleLine()  
{  
    hbuf = GetCurrentBuf()  
    ln = GetBufLnCur(hbuf)  
    str = GetBufLine (hbuf, ln)  
    str = cat("/*",str)  
    str = cat(str,"*/")  
    PutBufLine (hbuf, ln, str)  
}  

macro CommentSelStr()  
{  
    hbuf = GetCurrentBuf()  
    ln = GetBufLnCur(hbuf)  
    str = GetBufSelText(hbuf)  
    str = cat("/*",str)  
    str = cat(str,"*/")  
    SetBufSelText (hbuf, str)  
} 

macro InsertHeader1()
{
	// Get the owner's name from the environment variable: MYNAME.
	// If the variable doesn't exist, then the owner field is skipped.
	szMyName = getenv(MYNAME)
	
	// Get a handle to the current file buffer and the name
	// and location of the current symbol where the cursor is.
	hbuf = GetCurrentBuf()
	szFunc = GetCurSymbol()
	ln = GetSymbolLine(szFunc)

	InsBufLine(hbuf, ln, "/************************************************************");
        ln = ln +1

	// begin assembling the title string
	sz = "** ��������: "
	
	/* convert symbol name to T E X T   L I K E   T H I S */
	cch = strlen(szFunc)
	ich = 0
	/*
	while (ich < cch)
		{
		ch = szFunc[ich]
		if (ich > 0)
			if (isupper(ch))
				sz = cat(sz, "   ")
			else
				sz = cat(sz, " ")
		sz = Cat(sz, toupper(ch))
		ich = ich + 1
		}*/
		
	while (ich < cch)
	{
		ch = szFunc[ich]
		//if (ich > 0)
		//	if (isupper(ch))
		//		sz = cat(sz, " ")
			//else
			//	sz = cat(sz, " ")
		sz = Cat(sz, ch)
		ich = ich + 1
	}
		
	InsBufLine(hbuf, ln, sz)
       	ln = ln + 1

        InsBufLine(hbuf, ln, "** ��������: ")
        ln = ln + 1

        InsBufLine(hbuf, ln, "** �������: ")
        ln = ln + 1

        InsBufLine(hbuf, ln, "** �������: ")
        ln = ln + 1

        InsBufLine(hbuf, ln, "** �� �� ֵ   : ")
        ln = ln + 1
	

	/* if owner variable exists, insert Owner: name */
	if (strlen(szMyName) > 0)
       {
                InsBufLine(hbuf, ln, "** ��    ��       :  @szMyName@")                 
        }
        else
        {
                InsBufLine(hbuf, ln, "** ��    ��       :  ")                 
        }
        ln = ln + 1

        // Get current time
        szTime  = GetSysTime(1)
        Day      = szTime.Day
        Month   = szTime.Month
        Year     = szTime.Year
        if (Day < 10)
                szDay = "0@Day@"
        else
                szDay = Day  

        InsBufLine(hbuf, ln, "** ��    ��       :  @Year@��@Month@��@szDay@��")
        ln = ln + 1

 

        InsBufLine(hbuf, ln, "** ��    ��       :  1.0")
        ln = ln + 1


        //InsBufLine(hbuf, ln, "** �޸�����  �汾��   �޸���  �޸�����")
        //ln = ln + 1

        InsBufLine(hbuf, ln, "**************************************************************/")


}


/* InsertFileHeader:

   Inserts a comment header block at the top of the current function. 
   This actually works on any type of symbol, not just functions.

   To use this, define an environment variable "MYNAME" and set it
   to your email name.  eg. set MYNAME=raygr
*/

macro InsertFileHeader1()
{
	szMyName = getenv(MYNAME)
	
	hbuf = GetCurrentBuf()

        InsBufLine(hbuf, 0, "/***************************************************************************")
        InsBufLine(hbuf, 1, "** ��Ȩ����:  Copyright (c) 2013-2100  ********************             ")
        filename = GetBufName(hbuf)
        InsBufLine(hbuf, 2, "** �ļ�����:  ")//@filename@")
        InsBufLine(hbuf, 3, "** �ļ���ʶ: ")
        InsBufLine(hbuf, 4, "** ����ժҪ:  ")
        InsBufLine(hbuf, 5, "** ��ǰ�汾:  v1.0")

        /* if owner variable exists, insert Owner: name */
        if (strlen(szMyName) > 0)
        {
        sz = "** ��      ��     :  @szMyName@"

        }
        else
        {
        sz = "** ��      ��     :"
        }

        InsBufLine(hbuf, 6, sz)

        // Get current time
        szTime  = GetSysTime(1)
        Day      = szTime.Day
        Month   = szTime.Month
        Year     = szTime.Year
        if (Day < 10)
                szDay = "0@Day@"
        else
                szDay = Day               


        InsBufLine(hbuf, 7,   "** �������: @Year@��@Month@��@szDay@��")
        InsBufLine(hbuf, 8,   "** �޸ļ�¼: ")
        InsBufLine(hbuf, 9,   "** �޸ļ�¼: ")
        InsBufLine(hbuf, 10, "** �޸�����: ")
        InsBufLine(hbuf, 11, "** �汾��      : ")
        InsBufLine(hbuf, 12, "** �޸���      : ")
        InsBufLine(hbuf, 13, "** �޸�����: ")
        InsBufLine(hbuf, 14, "***************************************************************************/")
 
}

