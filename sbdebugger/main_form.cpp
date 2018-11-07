//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_form.h"
#include "options_form.h"
#include "connect_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <Registry.hpp>
#include <process.h>
Tmain *main;
//---------------------------------------------------------------------------
__fastcall Tmain::Tmain(TComponent* Owner)
        : TForm(Owner)
{
}

#define REGROOT "\\Software\\ScriptBasic\\Debugger"

AnsiString __fastcall Tmain::GetRegOption(AnsiString Name)
{
  AnsiString RetVal;

  TRegistry *R = new TRegistry;
  R->RootKey = HKEY_CURRENT_USER;
  R->OpenKey(REGROOT,true);
  RetVal = R->ReadString(Name);
  R->CloseKey();
  delete R;
  return RetVal;
}
void __fastcall Tmain::SetRegOption(AnsiString Name,AnsiString Value)
{
  TRegistry *R = new TRegistry;
  R->RootKey = HKEY_CURRENT_USER;
  R->OpenKey(REGROOT,true);
  R->WriteString(Name,Value);
  R->CloseKey();
  delete R;
}


//---------------------------------------------------------------------------
int __fastcall Tmain::GetCaretLine(void)
{
  int i;
  TPoint CaretPos;

  CaretPos = source->CaretPos;
  return CaretPos.y+1;
}

void __fastcall Tmain::SetStateRunning(void)
{
  state->SimpleText       = "running";
  GlobalVariablesUpToDate = false;
  LocalVariablesUpToDate  = false;
  SourceUpToDate          = false;
  DebuggedProgramState    = running;
  DisableDebuggerCommands();
}
void __fastcall Tmain::SetStateWaiting(void)
{
  state->SimpleText = "waiting";
  menuConnect->Enabled    = false;
  menuDisconnect->Enabled = true;
  menuStep->Enabled       = true;
  menuRun->Enabled        = true;
  menuBreak->Enabled      = true;
  menuStack->Enabled      = true;
  DebuggedProgramState    = waiting;
  EnableDebuggerCommands();
}
void __fastcall Tmain::SetStateConnected(void)
{
  state->SimpleText = "connected";
  menuConnect->Enabled    = false;
  menuDisconnect->Enabled = true;
  menuStep->Enabled       = true;
  menuRun->Enabled        = true;
  menuBreak->Enabled      = true;
  menuStack->Enabled      = true;
  EnableDebuggerCommands();
  TraceTimer->Enabled = false;
}
void __fastcall Tmain::SetStateDisconnected(void)
{
  state->SimpleText = "disconnected";
  menuConnect->Enabled    = true;
  menuDisconnect->Enabled = false;
  menuStep->Enabled       = false;
  menuRun->Enabled        = false;
  menuBreak->Enabled      = false;
  menuStack->Enabled      = false;
  DisableDebuggerCommands();
  TraceTimer->Enabled = false;
}
void __fastcall Tmain::SetStateConnecting(void)
{
  state->SimpleText = "connecting...";
  menuConnect->Enabled    = false;
  menuDisconnect->Enabled = true;
  menuStep->Enabled       = false;
  menuRun->Enabled        = false;
  menuBreak->Enabled      = false;
  menuStack->Enabled      = false;
  TraceTimer->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall Tmain::ColorSourceLines(void)
{
  int i;
  int NextLineStartPos;
  TTextAttributes *attrib;
  int LineBeforePos;
  int LineAfterPos;
  char S[2];

  if( ! source->Lines->Count )return;
  if( SourceUpToDate )return;
  SourceUpToDate = true;
  if( SmallRepaint )
  {
    SmallRepaint = false;
    source->SelStart = SourceLineStart[PreviousLine - 1] ;
    source->SelLength = source->Lines->Strings[PreviousLine - 1].Length() ;
    source->SelAttributes = source->DefAttributes;
    source->SelStart = SourceLineStart[CurrentLine - 1] ;
    NextLineStartPos = SourceLineStart[CurrentLine - 1] ;
    source->SelLength = source->Lines->Strings[CurrentLine - 1].Length() ;
    attrib = source->SelAttributes;
    attrib->Style = attrib->Style << fsUnderline;
    source->SelAttributes = attrib;
  }else{// full repaint
    for( i=0 ; i < source->Lines->Count ; i++ ){
      source->SelStart = SourceLineStart[ i ] ;
      source->SelLength = source->Lines->Strings[i].Length() ;
      attrib = source->DefAttributes;
      attrib->Color = clBlack;
      source->SelAttributes = attrib;

      if( BreakPoint[i+1] ){// color the line with breakpoint color
        source->SelStart = SourceLineStart[ i ] ;
        source->SelLength = source->Lines->Strings[i].Length() ;
        attrib = source->SelAttributes;
        attrib->Color = clRed;
        source->SelAttributes = attrib;
        }

      if( CurrentLine == i+1 ){// color the line with the current line color
        source->SelStart = SourceLineStart[ i ] ;
        NextLineStartPos = SourceLineStart[ i ] ;
        source->SelLength = source->Lines->Strings[i].Length() ;
        attrib = source->SelAttributes;
        attrib->Style = attrib->Style << fsUnderline;
        source->SelAttributes = attrib;
        }
      }
    }
/*  Here we play a little trick. We edit the text from the program, forcing the
    control to scroll the RichEdit to show the actual line.
*/

  source->SelStart = NextLineStartPos ;
  source->SelLength = 1;
  source->GetSelTextBuf(S,2);
  source->SelStart = NextLineStartPos ;
  source->SelLength = 1;
  source->SetSelTextBuf(" ");
  source->SelStart = NextLineStartPos ;
  source->SelLength = 1;
  source->SetSelTextBuf(S);

  source->SelStart = NextLineStartPos ;
  source->SelLength = source->Lines->Strings[CurrentLine-1].Length();
  attrib = source->SelAttributes;
  attrib->Style = attrib->Style << fsUnderline;
  source->SelAttributes = attrib;
  source->SelStart = NextLineStartPos ;
  source->SelLength = 0;
  source->CaretPos.x = 0;
  source->CaretPos.y = CurrentLine - 1;
}
//---------------------------------------------------------------------------
void __fastcall Tmain::Connect2BASIC(int BeSilent)
{
  try {
    socket->Open();
    }
  catch(Exception &e){}

  menuConnect->Enabled = ! socket->Active;
  menuDisconnect->Enabled = socket->Active;
  state->SimpleText = "connecting...";
}
//---------------------------------------------------------------------------
void __fastcall Tmain::Disconnect2BASIC(void)
{
  socket->Socket->SendText("q\r\n");
  try {
    socket->Close();
    }
  catch(Exception &e){}
}
//---------------------------------------------------------------------------
void __fastcall Tmain::FormCreate(TObject *Sender)
{
  Connect2BASIC(1);
  source->Lines->Clear();
  GlobalVariablesUpToDate = false;
  LocalVariablesUpToDate = false;
  GlobalVariableDisplay->ColWidths[1] = GlobalVariableDisplay->Width -
                                            GlobalVariableDisplay->ColWidths[0] -10;
  LocalVariableDisplay->ColWidths[1]  = LocalVariableDisplay->Width  -
                                            LocalVariableDisplay->ColWidths[0]  -10;
  SmallRepaint = false;

  // get geometry parameters
  DeltaW_MainForm_m_RichEdit = main->Width - source->Width;
  DeltaH_MainForm_m_RichEdit = main->Height - source->Height;
  GVTX = main->Width  - Label1->Left;
  GVTY = main->Height - Label1->Top;
  LVTX = main->Width  - Label2->Left;
  LVTY = main->Height - Label2->Top;
  GVDX = main->Width  - GlobalVariableDisplay->Left;
  GVDY = main->Height - GlobalVariableDisplay->Top;
  LVDX = main->Width  - LocalVariableDisplay->Left;
  LVDY = main->Height - LocalVariableDisplay->Top;
  VDDL = LocalVariableDisplay->Left - // gap between the variable displays
         (GlobalVariableDisplay->Left+GlobalVariableDisplay->Width);
  GVCHKD = gvundef->Left - GlobalVariableDisplay->Left;
  LVCHKD = lvundef->Left - LocalVariableDisplay->Left;
}
//---------------------------------------------------------------------------
void __fastcall Tmain::mainOnResize(TObject *Sender)
{
  source->Width  = main->Width  - DeltaW_MainForm_m_RichEdit ;
  source->Height = main->Height - DeltaH_MainForm_m_RichEdit;
  Label1->Top = main->Height -GVTY ;
  Label2->Top = main->Height -LVTY ;
  GlobalVariableDisplay->Top = main->Height -GVDY ;
  LocalVariableDisplay->Top = main->Height -LVDY ;
  LocalVariableDisplay->Width =  (source->Width - VDDL) / 2;
  GlobalVariableDisplay->Width = (source->Width - VDDL) / 2;
  LocalVariableDisplay->Left = GlobalVariableDisplay->Left + GlobalVariableDisplay->Width + VDDL;
  GlobalVariableDisplay->ColWidths[1] = GlobalVariableDisplay->Width -
                                            GlobalVariableDisplay->ColWidths[0] -10;
  LocalVariableDisplay->ColWidths[1]  = LocalVariableDisplay->Width  -
                                            LocalVariableDisplay->ColWidths[0]  -10;
  Label1->Left = GlobalVariableDisplay->Left;
  Label2->Left = LocalVariableDisplay->Left;
  gvundef->Left = GlobalVariableDisplay->Left + GVCHKD;
  lvundef->Left = LocalVariableDisplay->Left  + LVCHKD;
  gvundef->Top =  Label1->Top ;
  lvundef->Top =  Label2->Top ;
}
//---------------------------------------------------------------------------
void __fastcall Tmain::menuConnectClick(TObject *Sender)
{
  Connect2BASIC(0);
}
//---------------------------------------------------------------------------
void __fastcall Tmain::menuDisconnectClick(TObject *Sender)
{
  Disconnect2BASIC();
}
//---------------------------------------------------------------------------
void __fastcall Tmain::disconnectClick(TObject *Sender)
{
  Disconnect2BASIC();
}
//---------------------------------------------------------------------------
void __fastcall Tmain::Exit1Click(TObject *Sender)
{
  Disconnect2BASIC();
  exit(0);
}
//---------------------------------------------------------------------------
void __fastcall Tmain::socketOnRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
  int SourceIndex;
  int ThisLineHasBreakPoint;
  int ThisLineNumber;

  menuConnect->Enabled = ! socket->Active;
  menuDisconnect->Enabled = socket->Active;
  SocketBuffer = socket->Socket->ReceiveText();
  while( SocketBuffer.Length() > 0 ){
    int i = SocketBuffer.Pos("\r\n");
    if( i == 0 )i = SocketBuffer.Pos("\n\r");
    if( i == 0 )i = SocketBuffer.Pos("\n");
    if( i == 0 )i = SocketBuffer.Pos("\r");
    if( i == 0 )i = SocketBuffer.Length()+1;
    AnsiString CommandLine = SocketBuffer.SubString(1,i-1);
    SocketBuffer = SocketBuffer.Delete(1,i-1);
    while( SocketBuffer.SubString(1,1) == "\r" ||
           SocketBuffer.SubString(1,1) == "\n" )
      SocketBuffer = SocketBuffer.Delete(1,1);

    if( CommandLine == "." ){
      source->SetFocus();
      if( SourceLines.Length == 0 )socket->Socket->SendText("l -\r\n");
      if( ! LocalVariablesUpToDate ){
        socket->Socket->SendText("L\r\n");
        LocalVariablesUpToDate = true;
        LocalVariableDisplay->RowCount = 2;
        LocalVariableDisplay->Cells[0][1] = "";
        LocalVariableDisplay->Cells[1][1] = "";
        }
      if( ! GlobalVariablesUpToDate ){
        socket->Socket->SendText("G\r\n");
        GlobalVariablesUpToDate = true;
        GlobalVariableDisplay->RowCount = 2;
        GlobalVariableDisplay->Cells[0][1] = "";
        GlobalVariableDisplay->Cells[1][1] = "";
        }
      if( ! sourceInitialized && SourceLines.Length ){
        int i;
        source->Lines->Clear();
        int ThisLineStart = 0;
        SourceLineStart.Length = SourceLines.Length;
        for( i = 1 ; i < SourceLines.Length ; i++ ){
          source->Lines->Add(SourceLines[i]);
          SourceLineStart[i-1] = ThisLineStart;
          ThisLineStart += source->Lines->Strings[i-1].Length()+2;
          }
        sourceInitialized = true;
//        CurrentLine =  1;
        ColorSourceLines();
        }
       SetStateWaiting();
      continue;
      }
    i = CommandLine.Pos(":");
    if( i == 0 )continue;
    AnsiString Attribute = CommandLine.SubString(1,i-1);
    AnsiString Value = CommandLine.Delete(1,i+1);  
    if( Attribute == "Application" ){
      if( Value != "sbdbg 1.0" ){
        MessageBox(NULL,"Unknown server type. Disconnecting...","Bad server",MB_OK | MB_ICONSTOP);
        Disconnect2BASIC();
        return;
        }
      continue;
      }
    if( Attribute == "Message" ){
//      MessageBox(NULL,("Debug Message: "+Value).c_str(),"DebugMessage",MB_OK);
      continue;
      }  
    if( Attribute == "Version" ){
      if( Value != "1.0" ){
        MessageBox(NULL,"Unknown server version. Disconnecting...","Bad server",MB_OK | MB_ICONSTOP);
        Disconnect2BASIC();
        return;
        }
      continue;
      }
    if( Attribute == "Source-File-Count" ){
      SourceFileNr = Value.ToInt();
      SourceFiles = new AnsiString [SourceFileNr];
      SourceIndex  = 0;
      continue;
      }
    if( Attribute == "Source-File" ){
      if( SourceIndex >= SourceFileNr )continue; // ignore the rest of the file names
      SourceFiles[SourceIndex++] = Value;
      continue;
      }
    if( Attribute == "Current-Line" ){
      if( CurrentLine != Value.ToInt() ){
        CurrentLine = Value.ToInt();
        ColorSourceLines();
        }
      continue;
      }
    if( Attribute == "Break-Point" ){
      ThisLineHasBreakPoint = Value.ToInt();
      continue;
      }
    if( Attribute == "Line-Number" ){
      ThisLineNumber = Value.ToInt();
      continue;
      }
    if( Attribute == "Line" ){
      if( SourceLines.Length <= ThisLineNumber )SourceLines.Length = ThisLineNumber+1;
      if( BreakPoint.Length <=  ThisLineNumber )BreakPoint.Length = ThisLineNumber+1;
      SourceLines[ThisLineNumber] = Value;
      BreakPoint[ThisLineNumber] = ThisLineHasBreakPoint == 1;
      }
    if( Attribute == "Global-Variable-Name" ){
      if( Value.SubString(1,6) == "main::" )
        Value = Value.Delete(1,6);
      GlobalVariableDisplay->Cells[0][GlobalVariableDisplay->RowCount-1] = Value;
      continue;
      }
    if( Attribute == "Global-Variable-Value" ){
      if( gvundef->Checked && Value == "undef" ){
        GlobalVariableDisplay->Cells[1][GlobalVariableDisplay->RowCount-1] = "";
        GlobalVariableDisplay->Cells[0][GlobalVariableDisplay->RowCount-1] = "";
        }else{
        GlobalVariableDisplay->Cells[1][GlobalVariableDisplay->RowCount-1] = Value;
        GlobalVariableDisplay->RowCount++;
        }
      continue;
      }
    if( Attribute == "Local-Variable-Name" ){
      if( Value.SubString(1,6) == "main::" )
        Value = Value.Delete(1,6);
      LocalVariableDisplay->Cells[0][LocalVariableDisplay->RowCount-1] = Value;
      continue;
      }
    if( Attribute == "Local-Variable-Value" ){
      if( lvundef->Checked && Value == "undef" ){
        LocalVariableDisplay->Cells[1][LocalVariableDisplay->RowCount-1] = "";
        LocalVariableDisplay->Cells[0][LocalVariableDisplay->RowCount-1] = "";
        }else{
        LocalVariableDisplay->Cells[1][LocalVariableDisplay->RowCount-1] = Value;
        LocalVariableDisplay->RowCount++;
        }
      continue;
      }
    }
  }
//---------------------------------------------------------------------------




// this function is called when the user tries to alter the text


void __fastcall Tmain::socketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
  SetStateDisconnected();
  source->Lines->Clear();
}
//---------------------------------------------------------------------------


void __fastcall Tmain::socketOnError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
  ErrorCode = 0;
  socket->Close();
  SetStateDisconnected();
}
//---------------------------------------------------------------------------

void __fastcall Tmain::socketOnConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
  SetStateConnected();
  sourceInitialized = false;
  SourceLines.Length = 0;
  BreakPoint.Length = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tmain::DisableDebuggerCommands()
{
  Step1->Enabled = false;
  StepInto1->Enabled = false;
  StepOut1->Enabled = false;
  Run1->Enabled = false;
  Runtocursor1->Enabled = false;
  RUNtocursor2->Enabled = false;
  Trace1->Enabled = false;
}
void __fastcall Tmain::EnableDebuggerCommands()
{
  Step1->Enabled = true;
  StepInto1->Enabled = true;
  StepOut1->Enabled = true;
  Run1->Enabled = true;
  Runtocursor1->Enabled = true;
  RUNtocursor2->Enabled = true;
  Trace1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall Tmain::Step1Click(TObject *Sender)
{
  PreviousLine = CurrentLine;
  SmallRepaint = true;
  socket->Socket->SendText("S\r\n");
  SetStateRunning();
}
//---------------------------------------------------------------------------

void __fastcall Tmain::StepInto1Click(TObject *Sender)
{
  PreviousLine = CurrentLine;
  SmallRepaint = true;
  socket->Socket->SendText("s\r\n");
  SetStateRunning();
}
//---------------------------------------------------------------------------

void __fastcall Tmain::Runtocursor1Click(TObject *Sender)
{
  AnsiString S;
  int i = GetCaretLine();
  S = S.sprintf("r %d\r\n",i);
  PreviousLine = CurrentLine;
  SmallRepaint = true;
  socket->Socket->SendText(S);
  SetStateRunning();
}
//---------------------------------------------------------------------------

void __fastcall Tmain::RUNtocursor2Click(TObject *Sender)
{
  AnsiString S;
  int i = GetCaretLine();
  S = S.sprintf("R %d\r\n",i);
  PreviousLine = CurrentLine;
  SmallRepaint = true;
  socket->Socket->SendText(S);
  SetStateRunning();
}
//---------------------------------------------------------------------------

void __fastcall Tmain::ToggleBreakpoint1Click(TObject *Sender)
{
  int i = GetCaretLine();
  AnsiString S;
  BreakPoint[i] = ! BreakPoint[i];
  if( BreakPoint[i] )
     S = S.sprintf("b %d\r\n",i);
  else
     S = S.sprintf("B %d\r\n",i);
  // move the cursor to the start of the line
  while( source->CaretPos.x > 0 )source->SelStart --;
  // select the line
  source->SelLength = source->Lines->Strings[i-1].Length();
  // get attributes of the line as it is now
  TTextAttributes *attrib = source->SelAttributes;
  // alter the color of the line
  if( BreakPoint[i] )// color the line with breakpoint color
    attrib->Color = clRed;
  else
    attrib->Color = clBlack;
  // put the new color onto the line
  source->SelAttributes = attrib;
  // stop selection
  source->SelLength = 0;

  socket->Socket->SendText(S);
}
//---------------------------------------------------------------------------

void __fastcall Tmain::Run1Click(TObject *Sender)
{
  PreviousLine = CurrentLine;
  SmallRepaint = true;
  socket->Socket->SendText("r\r\n");
  SetStateRunning();
}
//---------------------------------------------------------------------------

void __fastcall Tmain::StepOut1Click(TObject *Sender)
{
  PreviousLine = CurrentLine;
  SmallRepaint = true;
  socket->Socket->SendText("o\r\n");
  SetStateRunning();

}
//---------------------------------------------------------------------------

void __fastcall Tmain::StackUp1Click(TObject *Sender)
{
  PreviousLine = CurrentLine;
  SmallRepaint = true;
  SourceUpToDate = false;
  socket->Socket->SendText("u\r\n");
  LocalVariablesUpToDate = false;
}
//---------------------------------------------------------------------------

void __fastcall Tmain::StackDown1Click(TObject *Sender)
{
  PreviousLine = CurrentLine;
  SmallRepaint = true;
  SourceUpToDate = false;
  socket->Socket->SendText("d\r\n");
  LocalVariablesUpToDate = false;
}
//---------------------------------------------------------------------------

void __fastcall Tmain::StackBottom1Click(TObject *Sender)
{
  PreviousLine = CurrentLine;
  SmallRepaint = true;
  SourceUpToDate = false;
  socket->Socket->SendText("D\r\n");
  LocalVariablesUpToDate = false;
}
//---------------------------------------------------------------------------

void __fastcall Tmain::Trace1Click(TObject *Sender)
{
  TraceTimer->Enabled = true;
  AnsiString interval = GetRegOption("tracetime");
  if( 0 == interval.Length() )interval = "1000";
  TraceTimer->Interval = interval.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall Tmain::StopTrace1Click(TObject *Sender)
{
  TraceTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tmain::TraceStep(TObject *Sender)
{
  // step only if the program waits for a step command
  // if the program runs for a longer period (e.g.: sleep or external module
  // is called and does not return soon) then we should not queue up several
  // step commands in the socket buffer
  if( DebuggedProgramState == waiting ){
    PreviousLine = CurrentLine;
    SmallRepaint = true;
    socket->Socket->SendText("s\r\n");
    }
  SetStateRunning();
  TraceTimer->Enabled = true;
  AnsiString interval = GetRegOption("tracetime");
  if( 0 == interval.Length() )interval = "1000";
  TraceTimer->Interval = interval.ToInt();
}
//---------------------------------------------------------------------------




void __fastcall Tmain::menuOptionsClick(TObject *Sender)
{
  FormOptions->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tmain::Open1Click(TObject *Sender)
{
  AnsiString CommandLine = GetRegOption("commandline");
  AnsiString S;
  char *FileName;

  OpenFile->Filter = "Basic (*.bas)|*.BAS|Scriba (*.sb)|*.SB|All files (*.*)|*.*";
  OpenFile->Execute();
  FileName = OpenFile->FileName.c_str();
  S = GetRegOption("commandline");
  spawnl(P_DETACH,S.c_str()," -i ","sdbg ",FileName,NULL);
  Sleep(500);
  Connect2BASIC(0);
}
//---------------------------------------------------------------------------

void __fastcall Tmain::RemoveAllBreakpoints1Click(TObject *Sender)
{
  AnsiString S;
  int i;

  for( i=0 ; i < BreakPoint.Length ; i++ )
    BreakPoint[i] = false;
  S = S.sprintf("B\r\n",i);
  SourceUpToDate = false;
  PreviousLine = CurrentLine;
  SmallRepaint = false;
  socket->Socket->SendText(S);

}
//---------------------------------------------------------------------------


void __fastcall Tmain::Connectto1Click(TObject *Sender)
{
  frmConnect->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tmain::gvundefClick(TObject *Sender)
{
  if( socket->Active )
    socket->Socket->SendText("G\r\n");
  GlobalVariablesUpToDate = true;
  GlobalVariableDisplay->RowCount = 2;
  GlobalVariableDisplay->Cells[0][1] = "";
  GlobalVariableDisplay->Cells[1][1] = "";
}
//---------------------------------------------------------------------------

void __fastcall Tmain::lvundefClick(TObject *Sender)
{
  if( socket->Active )
    socket->Socket->SendText("L\r\n");
  LocalVariablesUpToDate = true;
  LocalVariableDisplay->RowCount = 2;
  LocalVariableDisplay->Cells[0][1] = "";
  LocalVariableDisplay->Cells[1][1] = "";
}
//---------------------------------------------------------------------------

