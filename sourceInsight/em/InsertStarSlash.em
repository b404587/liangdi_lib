/*
	Two macro commands to insert '*' and '/'.  Because of a bug in 
	Source Insight, the '*' and '/' keys on the numeric keypad do not 
	insert those characters, even if 'NumLock' is off.
	
	As with other macros, to use this:
		1. Add this macro file to your project.
		2. Run the Options->Key Assignments command.
		3. Find and select the macro name(s) in the command list
		4. Press 'Add' to bind a key to the macro.
		Now you can run the macro command

*/

macro InsertAsterisk()
{
	hbuf = GetCurrentBuf()
	if (hbuf != 0)
		SetBufSelText(hbuf, "*")
}


macro InsertSlash()
{
	hbuf = GetCurrentBuf()
	if (hbuf != 0)
		SetBufSelText(hbuf, "/")
}

