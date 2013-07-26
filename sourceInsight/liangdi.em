macro MultiLineComment()  
{  
    hwnd = GetCurrentWnd()  
    selection = GetWndSel(hwnd)  
    LnFirst = GetWndSelLnFirst(hwnd)      //取首行行号  
    LnLast = GetWndSelLnLast(hwnd)      //取末行行号  
    hbuf = GetCurrentBuf()  
   
    if(GetBufLine(hbuf, 0) == "//magic-number:tph85666031"){  
        stop  
    }  
   
    Ln = Lnfirst  
    buf = GetBufLine(hbuf, Ln)  
    len = strlen(buf)  
   
    while(Ln <= Lnlast) {  
        buf = GetBufLine(hbuf, Ln)  //取Ln对应的行  
        if(buf == ""){                    //跳过空行  
            Ln = Ln + 1  
            continue  
        }  
   
        if(StrMid(buf, 0, 1) == "/") {       //需要取消注释,防止只有单字符的行  
            if(StrMid(buf, 1, 2) == "/"){  
                PutBufLine(hbuf, Ln, StrMid(buf, 2, Strlen(buf)))  
            }  
        }  
   
        if(StrMid(buf,0,1) != "/"){          //需要添加注释  
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
            sel.lnFirst = sel.lnFirst – 1  
            sel.lnLast = sel.lnLast – 1  
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
	sz = "** 函数名称: "
	
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

        InsBufLine(hbuf, ln, "** 功能描述: ")
        ln = ln + 1

        InsBufLine(hbuf, ln, "** 输入参数: ")
        ln = ln + 1

        InsBufLine(hbuf, ln, "** 输出参数: ")
        ln = ln + 1

        InsBufLine(hbuf, ln, "** 返 回 值   : ")
        ln = ln + 1
	

	/* if owner variable exists, insert Owner: name */
	if (strlen(szMyName) > 0)
       {
                InsBufLine(hbuf, ln, "** 作    者       :  @szMyName@")                 
        }
        else
        {
                InsBufLine(hbuf, ln, "** 作    者       :  ")                 
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

        InsBufLine(hbuf, ln, "** 日    期       :  @Year@年@Month@月@szDay@日")
        ln = ln + 1

 

        InsBufLine(hbuf, ln, "** 版    本       :  1.0")
        ln = ln + 1


        //InsBufLine(hbuf, ln, "** 修改日期  版本号   修改人  修改内容")
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
        InsBufLine(hbuf, 1, "** 版权所有:  Copyright (c) 2013-2100  ********************             ")
        filename = GetBufName(hbuf)
        InsBufLine(hbuf, 2, "** 文件名称:  ")//@filename@")
        InsBufLine(hbuf, 3, "** 文件标识: ")
        InsBufLine(hbuf, 4, "** 内容摘要:  ")
        InsBufLine(hbuf, 5, "** 当前版本:  v1.0")

        /* if owner variable exists, insert Owner: name */
        if (strlen(szMyName) > 0)
        {
        sz = "** 作      者     :  @szMyName@"

        }
        else
        {
        sz = "** 作      者     :"
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


        InsBufLine(hbuf, 7,   "** 完成日期: @Year@年@Month@月@szDay@日")
        InsBufLine(hbuf, 8,   "** 修改记录: ")
        InsBufLine(hbuf, 9,   "** 修改记录: ")
        InsBufLine(hbuf, 10, "** 修改日期: ")
        InsBufLine(hbuf, 11, "** 版本号      : ")
        InsBufLine(hbuf, 12, "** 修改人      : ")
        InsBufLine(hbuf, 13, "** 修改内容: ")
        InsBufLine(hbuf, 14, "***************************************************************************/")
 
}

