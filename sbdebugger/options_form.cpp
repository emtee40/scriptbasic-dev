//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "options_form.h"
#include "main_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOptions *FormOptions;
//---------------------------------------------------------------------------
__fastcall TFormOptions::TFormOptions(TComponent* Owner)
        : TForm(Owner)
{
  commandline->Text = main->GetRegOption("commandline");
  traceDt->Text = main->GetRegOption("tracetime");
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::btnCancelClick(TObject *Sender)
{
  FormOptions->Close();
  FormOptions->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::btnOKClick(TObject *Sender)
{
  btnApplyClick(Sender);
  btnCancelClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::btnApplyClick(TObject *Sender)
{
  main->SetRegOption("commandline",commandline->Text);
  main->SetRegOption("tracetime",traceDt->Text);
  main->SetRegOption("fontface",font->Font->Name);
  main->SetRegOption("fontsize",font->Font->Size);
  main->SetRegOption("fontcolor",font->Font->Color);
  main->SetRegOption("fontcharset",font->Font->Charset);
  AnsiString FontStyle = "";
  if( font->Font->Style.Contains(fsBold) )FontStyle += "b";
  if( font->Font->Style.Contains(fsItalic) )FontStyle += "i";
  if( font->Font->Style.Contains(fsUnderline) )FontStyle += "u";
  if( font->Font->Style.Contains(fsStrikeOut) )FontStyle += "s";
  main->SetRegOption("fontstyle",FontStyle);
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::btnBrowseClick(TObject *Sender)
{
  OpenScriba->Filter = "Executable (*.exe)|*.EXE|All files (*.*)|*.*";
  OpenScriba->Execute();
  commandline->Text = OpenScriba->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::traceDtKeyPress(TObject *Sender, char &Key)
{
 if( Key >= '0' && Key <= '9' )return;
 if( Key == '\b' )return;
 Key = '0';        
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::btnFontClick(TObject *Sender)
{
 font->Execute();        
}
//---------------------------------------------------------------------------

