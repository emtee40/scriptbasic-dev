//---------------------------------------------------------------------------

#ifndef main_formH
#define main_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ScktComp.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tmain : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *source;
        TClientSocket *socket;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *menuConnect;
        TMenuItem *menuDisconnect;
        TMenuItem *Exit1;
        TStatusBar *state;
        TMenuItem *menuStep;
        TMenuItem *Step1;
        TMenuItem *StepInto1;
        TMenuItem *StepOut1;
        TMenuItem *Run1;
        TMenuItem *Runtocursor1;
        TMenuItem *RUNtocursor2;
        TMenuItem *ToggleBreakpoint1;
        TMenuItem *StackUp1;
        TMenuItem *StackDown1;
        TMenuItem *StackBottom1;
        TMenuItem *menuRun;
        TMenuItem *menuBreak;
        TMenuItem *menuStack;
        TMenuItem *Trace1;
        TMenuItem *StopTrace1;
        TTimer *TraceTimer;
        TMenuItem *menuStop;
        TStringGrid *GlobalVariableDisplay;
        TStringGrid *LocalVariableDisplay;
        TLabel *Label1;
        TLabel *Label2;
        TMenuItem *Open1;
        TMenuItem *Connectto1;
        TMenuItem *menuOptions;
        TOpenDialog *OpenFile;
        TMenuItem *RemoveAllBreakpoints1;
        TCheckBox *gvundef;
        TCheckBox *lvundef;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall menuConnectClick(TObject *Sender);
        void __fastcall menuDisconnectClick(TObject *Sender);
        void __fastcall mainOnResize(TObject *Sender);
        void __fastcall disconnectClick(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall socketOnRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall socketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall socketOnError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall socketOnConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall Step1Click(TObject *Sender);
        void __fastcall StepInto1Click(TObject *Sender);
        void __fastcall Runtocursor1Click(TObject *Sender);
        void __fastcall RUNtocursor2Click(TObject *Sender);
        void __fastcall ToggleBreakpoint1Click(TObject *Sender);
        void __fastcall Run1Click(TObject *Sender);
        void __fastcall StepOut1Click(TObject *Sender);
        void __fastcall StackUp1Click(TObject *Sender);
        void __fastcall StackDown1Click(TObject *Sender);
        void __fastcall StackBottom1Click(TObject *Sender);
        void __fastcall Trace1Click(TObject *Sender);
        void __fastcall StopTrace1Click(TObject *Sender);
        void __fastcall TraceStep(TObject *Sender);
        void __fastcall menuOptionsClick(TObject *Sender);
        AnsiString __fastcall GetRegOption(AnsiString Name);
        void __fastcall SetRegOption(AnsiString Name,AnsiString Value);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall RemoveAllBreakpoints1Click(TObject *Sender);
        void __fastcall Connectto1Click(TObject *Sender);
        void __fastcall Connect2BASIC(int BeSilent);
        void __fastcall gvundefClick(TObject *Sender);
        void __fastcall lvundefClick(TObject *Sender);
private:	// User declarations
        void __fastcall Disconnect2BASIC(void);
        void __fastcall ColorSourceLines(void);
        int  __fastcall GetCaretLine(void);
        void __fastcall SetStateRunning(void);
        void __fastcall SetStateWaiting(void);
        void __fastcall SetStateConnected(void);
        void __fastcall SetStateConnecting(void);
        void __fastcall SetStateDisconnected(void);
        void __fastcall DisableDebuggerCommands(void);
        void __fastcall EnableDebuggerCommands(void);
        AnsiString SocketBuffer;
        int SourceFileNr;
        DynamicArray<AnsiString> SourceLines;
        DynamicArray<bool> BreakPoint;
        DynamicArray<int> SourceLineStart;
        AnsiString *SourceFiles;
        bool sourceInitialized;
        bool GlobalVariablesUpToDate;
        bool LocalVariablesUpToDate;
        bool SourceUpToDate;
        bool SmallRepaint;
        int CurrentLine;
        int PreviousLine;
        typedef enum _enumState
        {
                waiting,
                running
        } enumState;
        enumState DebuggedProgramState;
        // geometry parameters to follow form resize
        int DeltaW_MainForm_m_RichEdit;
        int DeltaH_MainForm_m_RichEdit;
        int GVTY,GVTX,LVTY,LVTX,GVDY,GVDX,LVDY,LVDX,VDDL,GVCHKD,LVCHKD;
public:		// User declarations
        __fastcall Tmain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tmain *main;
//---------------------------------------------------------------------------
#endif
