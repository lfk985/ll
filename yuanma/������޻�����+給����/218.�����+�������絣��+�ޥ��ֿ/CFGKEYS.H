/*
 * New editor name:  tde, the Thomson-Davis Editor.
 * Author:           Frank Davis
 * Date:             June 5, 1991
 *
 * Show all available keys and the function connected to each key.
 */


KEY_FUNC key_func;


struct screen key_head[] = {
   {1,2,"      Key                     Current Function           " },
 {2,0,"쳐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴?" },
{15,0,"쳐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴?" },
 {16,1,"  ? = 101 Keys     = Extended Keys     = Frank's 83/84 Extended Keys"},
{17,0,"쳐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴?" },
 {18,1,"               F3 = Quit       F5 = Change Function                  "},
 {19,1,"  F7 = Print to File    F8 = Print to Printer    F10 = Save and exit "},
  { 0, 0, NULL }
};

struct screen func_head[] = {
   {1,2,"  Available Functions" },
 {2,0,"쳐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴?" },
 {9,0,"쳐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴?" },
{10,1, " <Enter> = Select   <ESC> = Abort" },
  { 0, 0, NULL }
};

struct screen print_head[] = {
{ 2,1," Printing line       Press ESC to quit. " },
  { 0, 0, NULL }
};

struct screen file_head[] = {
{ 2,1," File name for key def's : " },
  { 0, 0, NULL }
};


/*
 * Group the list of available keys by function group - not alphabetically.
 */
KEY_DEFS key_defs[AVAIL_KEYS] = {
/*  available key      index into file    index into function list */
   { "     F1",                       59, 0 },
   { "     F2",                       60, 0 },
   { "     F3",                       61, 0 },
   { "     F4",                       62, 0 },
   { "     F5",                       63, 0 },
   { "     F6",                       64, 0 },
   { "     F7",                       65, 0 },
   { "     F8",                       66, 0 },
   { "     F9",                       67, 0 },
   { "     F10",                      68, 0 },
   { " ?  F11",                     133, 0 },
   { " ?  F12",                     134, 0 },
   { "     Shift + F1",               84, 0 },
   { "     Shift + F2",               85, 0 },
   { "     Shift + F3",               86, 0 },
   { "     Shift + F4",               87, 0 },
   { "     Shift + F5",               88, 0 },
   { "     Shift + F6",               89, 0 },
   { "     Shift + F7",               90, 0 },
   { "     Shift + F8",               91, 0 },
   { "     Shift + F9",               92, 0 },
   { "     Shift + F10",              93, 0 },
   { " ?  Shift + F11",             135, 0 },
   { " ?  Shift + F12",             136, 0 },
   { "     Control + F1",             94, 0 },
   { "     Control + F2",             95, 0 },
   { "     Control + F3",             96, 0 },
   { "     Control + F4",             97, 0 },
   { "     Control + F5",             98, 0 },
   { "     Control + F6",             99, 0 },
   { "     Control + F7",            100, 0 },
   { "     Control + F8",            101, 0 },
   { "     Control + F9",            102, 0 },
   { "     Control + F10",           103, 0 },
   { " ?  Control + F11",           137, 0 },
   { " ?  Control + F12",           138, 0 },
   { "     Alt + F1",                104, 0 },
   { "     Alt + F2",                105, 0 },
   { "     Alt + F3",                106, 0 },
   { "     Alt + F4",                107, 0 },
   { "     Alt + F5",                108, 0 },
   { "     Alt + F6",                109, 0 },
   { "     Alt + F7",                110, 0 },
   { "     Alt + F8",                111, 0 },
   { "     Alt + F9",                112, 0 },
   { "     Alt + F10",               113, 0 },
   { " ?  Alt + F11",               139, 0 },
   { " ?  Alt + F12",               140, 0 },
   { "     Control + @",             174, 0 },
   { "     Control + A",             175, 0 },
   { "     Control + B",             176, 0 },
   { "     Control + C",             177, 0 },
   { "     Control + D",             178, 0 },
   { "     Control + E",             179, 0 },
   { "     Control + F",             180, 0 },
   { "     Control + G",             181, 0 },
   { "     Control + H",             182, 0 },
   { "     Control + I",             183, 0 },
   { "     Control + J",             184, 0 },
   { "     Control + K",             185, 0 },
   { "     Control + L",             186, 0 },
   { "     Control + M",             187, 0 },
   { "     Control + N",             188, 0 },
   { "     Control + O",             189, 0 },
   { "     Control + P",             190, 0 },
   { "     Control + Q",             191, 0 },
   { "     Control + R",             192, 0 },
   { "     Control + S",             193, 0 },
   { "     Control + T",             194, 0 },
   { "     Control + U",             195, 0 },
   { "     Control + V",             196, 0 },
   { "     Control + W",             197, 0 },
   { "     Control + X",             198, 0 },
   { "     Control + Y",             199, 0 },
   { "     Control + Z",             200, 0 },
   { "     Control + [",             201, 0 },
   { "     Control + \\",            202, 0 },
   { "     Control + ]",             203, 0 },
   { "     Control + ^",             204, 0 },
   { "     Control + _",             205, 0 },
   { "     Alt + A",                  30, 0 },
   { "     Alt + B",                  48, 0 },
   { "     Alt + C",                  46, 0 },
   { "     Alt + D",                  32, 0 },
   { "     Alt + E",                  18, 0 },
   { "     Alt + F",                  33, 0 },
   { "     Alt + G",                  34, 0 },
   { "     Alt + H",                  35, 0 },
   { "     Alt + I",                  23, 0 },
   { "     Alt + J",                  36, 0 },
   { "     Alt + K",                  37, 0 },
   { "     Alt + L",                  38, 0 },
   { "     Alt + M",                  50, 0 },
   { "     Alt + N",                  49, 0 },
   { "     Alt + O",                  24, 0 },
   { "     Alt + P",                  25, 0 },
   { "     Alt + Q",                  16, 0 },
   { "     Alt + R",                  19, 0 },
   { "     Alt + S",                  31, 0 },
   { "     Alt + T",                  20, 0 },
   { "     Alt + U",                  22, 0 },
   { "     Alt + V",                  47, 0 },
   { "     Alt + W",                  17, 0 },
   { "     Alt + X",                  45, 0 },
   { "     Alt + Y",                  21, 0 },
   { "     Alt + Z",                  44, 0 },
   { "     Shift + Alt + A",         232, 0 },
   { "     Shift + Alt + B",         250, 0 },
   { "     Shift + Alt + C",         248, 0 },
   { "     Shift + Alt + D",         234, 0 },
   { "     Shift + Alt + E",         220, 0 },
   { "     Shift + Alt + F",         235, 0 },
   { "     Shift + Alt + G",         236, 0 },
   { "     Shift + Alt + H",         237, 0 },
   { "     Shift + Alt + I",         225, 0 },
   { "     Shift + Alt + J",         238, 0 },
   { "     Shift + Alt + K",         239, 0 },
   { "     Shift + Alt + L",         240, 0 },
   { "     Shift + Alt + M",         252, 0 },
   { "     Shift + Alt + N",         251, 0 },
   { "     Shift + Alt + O",         226, 0 },
   { "     Shift + Alt + P",         227, 0 },
   { "     Shift + Alt + Q",         218, 0 },
   { "     Shift + Alt + R",         221, 0 },
   { "     Shift + Alt + S",         233, 0 },
   { "     Shift + Alt + T",         222, 0 },
   { "     Shift + Alt + U",         224, 0 },
   { "     Shift + Alt + V",         249, 0 },
   { "     Shift + Alt + W",         219, 0 },
   { "     Shift + Alt + X",         247, 0 },
   { "     Shift + Alt + Y",         223, 0 },
   { "     Shift + Alt + Z",         246, 0 },
   { "   Alt + [",                  26, 0 },
   { "   Alt + ]",                  27, 0 },
   { "   Alt + ;",                  39, 0 },
   { "   Alt + \"",                 40, 0 },
   { "   Alt + ~",                  41, 0 },
   { "   Alt + <",                  51, 0 },
   { "   Alt + >",                  52, 0 },
   { "   Alt + ?",                  53, 0 },
   { "   Shift + Alt + [",         228, 0 },
   { "   Shift + Alt + ]",         229, 0 },
   { "   Shift + Alt + ;",         241, 0 },
   { "   Shift + Alt + \"",        242, 0 },
   { "   Shift + Alt + ~",         243, 0 },
   { "   Shift + Alt + <",         253, 0 },
   { "   Shift + Alt + >",         254, 0 },
   { "   Shift + Alt + ?",         255, 0 },
   { "     Alt + 1!",                120, 0 },
   { "     Alt + 2@",                121, 0 },
   { "     Alt + 3#",                122, 0 },
   { "     Alt + 4$",                123, 0 },
   { "     Alt + 5%",                124, 0 },
   { "     Alt + 6^",                125, 0 },
   { "     Alt + 7&",                126, 0 },
   { "     Alt + 8*",                127, 0 },
   { "     Alt + 9(",                128, 0 },
   { "     Alt + 0)",                129, 0 },
   { "     Alt + -_",                130, 0 },
   { "     Alt + =+",                131, 0 },
   { "     Shift + Alt + 1!",        206, 0 },
   { "     Shift + Alt + 2@",        207, 0 },
   { "     Shift + Alt + 3#",        208, 0 },
   { "     Shift + Alt + 4$",        209, 0 },
   { "     Shift + Alt + 5%",        210, 0 },
   { "     Shift + Alt + 6^",        211, 0 },
   { "     Shift + Alt + 7&",        212, 0 },
   { "     Shift + Alt + 8*",        213, 0 },
   { "     Shift + Alt + 9(",        214, 0 },
   { "     Shift + Alt + 0)",        215, 0 },
   { "     Shift + Alt + -_",        216, 0 },
   { "     Shift + Alt + =+",        217, 0 },
   { "     Enter",                     6, 0 },
   { " ?   Grey Enter",               29, 0 },
   { "     Backspace",                 9, 0 },
   { "     ESC",                       2, 0 },
   { "     Tab",                      12, 0 },
   { "     Shift + Enter",             7, 0 },
   { " ?   Shift + Grey Enter",       42, 0 },
   { "     Shift + Backspace",        10, 0 },
   { "     Shift + ESC",               3, 0 },
   { "     Shift + Tab",              15, 0 },
   { "     Control + Enter",           8, 0 },
   { " ?   Control + Grey Enter",     43, 0 },
   { "     Control + Backspace",      11, 0 },
   { "     Control + ESC",             4, 0 },
   { "    Control + Tab",           148, 0 },
   { "    Alt + Enter",              28, 0 },
   { " ?  Alt + Grey Enter",        166, 0 },
   { "    Alt + Backspace",          14, 0 },
   { "    Alt + ESC",                 1, 0 },
   { "   Alt + Tab",               165, 0 },
   { "     Up",                       72, 0 },
   { "     Down",                     80, 0 },
   { "     Left",                     75, 0 },
   { "     Right",                    77, 0 },
   { "     Home",                     71, 0 },
   { "     End",                      79, 0 },
   { "     PgUp",                     73, 0 },
   { "     PgDn",                     81, 0 },
   { "   Center",                   76, 0 },
   { "     Ins",                      82, 0 },
   { "     Del",                      83, 0 },
   { "     Control + Left",          115, 0 },
   { "     Control + Right",         116, 0 },
   { "     Control + Home",          119, 0 },
   { "     Control + End",           117, 0 },
   { "     Control + PgUp",          132, 0 },
   { "     Control + PgDn",          118, 0 },
   { "     Shift + Ctrl + Left",     170, 0 },
   { "     Shift + Ctrl + Right",    171, 0 },
   { "   Control + Up",            141, 0 },
   { "   Control + Down",          145, 0 },
   { "   Control + Center",        143, 0 },
   { "   Control + Ins",           146, 0 },
   { "   Control + Del",           147, 0 },
   { "     Control + Grey -",        142, 0 },
   { "     Control + Grey +",        144, 0 },
   { " ?   Control + Grey /",        149, 0 },
   { " ?   Control + Grey *",        150, 0 },
   { " ?  Alt + Grey Ins",          162, 0 },
   { " ?  Alt + Grey Del",          163, 0 },
   { " ?  Alt + Grey Home",         151, 0 },
   { " ?  Alt + Grey End",          159, 0 },
   { " ?  Alt + Grey PgUp",         153, 0 },
   { " ?  Alt + Grey PgDn",         161, 0 },
   { " ?  Alt + Grey Up",           152, 0 },
   { " ?  Alt + Grey Down",         160, 0 },
   { " ?  Alt + Grey Left",         155, 0 },
   { " ?  Alt + Grey Right",        157, 0 },
   { " ?  Alt + Grey /",            164, 0 },
   { "     Grey - (Num Lock off)",   167, 0 },
   { "     Grey + (Num Lock off)",   168, 0 }
};


/*
 * list of functions that keys may be assigned to.
 */


char *avail_func[NUM_FUNC] = {
"*  *  *",                      /*   0  */
"Help",
"Rturn",
"NextLine",
"BegNextLine",
"LineDown",
"LineUp",
"CharRight",
"CharLeft",
"PanRight",
"PanLeft",
"WordRight",
"WordLeft",
"ScreenDown",
"ScreenUp",
"EndOfFile",
"TopOfFile",
"BotOfScreen",
"TopOfScreen",
"EndOfLine",
"BegOfLine",
"JumpToLine",
"CenterWindow",
"CenterLine",
"HorizontalScreenRight",
"HorizontalScreenLeft",
"ScrollDnLine",
"ScrollUpLine",
"PanUp",
"PanDn",
"ToggleOverWrite",
"ToggleSmartTabs",
"ToggleIndent",
"ToggleWordWrap",
"ToggleCRLF",
"ToggleTrailing",
"ToggleZ",
"ToggleEol",
"ToggleSync",
"ToggleRuler",
"ToggleTabInflate",
"SetTabs",
"SetLeftMargin",
"SetRightMargin",
"SetParagraphMargin",
"FormatParagraph",
"FormatText",
"LeftJustify",
"RightJustify",
"CenterJustify",
"Tab",
"BackTab",
"ParenBalance",
"BackSpace",
"DeleteChar",
"StreamDeleteChar",
"DeleteLine",
"DelEndOfLine",
"WordDelete",
"AddLine",
"SplitLine",
"JoinLine",
"DuplicateLine",
"AbortCommand",
"UndoLine",
"UndoDelete",
"ToggleSearchCase",
"FindForward",
"FindBackward",
"RepeatFindForward1",
"RepeatFindForward2",
"RepeatFindBackward1",
"RepeatFindBackward2",
"ReplaceString",
"DefineDiff",
"RepeatDiff",
"MarkBox",
"MarkLine",
"MarkStream",
"UnMarkBlock",
"FillBlock",
"NumberBlock",
"CopyBlock",
"KopyBlock",
"MoveBlock",
"OverlayBlock",
"DeleteBlock",
"SwapBlock",
"BlockToFile",
"PrintBlock",
"BlockExpandTabs",
"BlockCompressTabs",
"BlockIndentTabs",
"BlockTrimTrailing",
"BlockUpperCase",
"BlockLowerCase",
"BlockRot13",
"BlockFixUUE",
"BlockEmailReply",
"BlockStripHiBit",
"SortBoxBlock",
"DateTimeStamp",
"EditFile",
"DirList",
"File",
"Save",
"SaveAs",
"SetFileAttributes",
"EditNextFile",
"DefineGrep",
"RepeatGrep",
"RedrawScreen",
"SizeWindow",
"SplitHorizontal",
"SplitVertical",
"NextWindow",
"PreviousWindow",
"ZoomWindow",
"NextHiddenWindow",
"SetMark1",
"SetMark2",
"SetMark3",
"GotoMark1",
"GotoMark2",
"GotoMark3",
"RecordMacro",
"PlayBack",
"SaveMacro",
"LoadMacro",
"ClearMacro",
"Pause",
"Quit",
"NextDirtyLine",
"PrevDirtyLine",
"FindRegX",
"RepeatFindRegX",
"RepeatFindRegXBackward",
"DefineRegXGrep",
"TwoCharKey"
};
