//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "connect_form.h"
#include "main_form.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmConnect *frmConnect;
//---------------------------------------------------------------------------
__fastcall TfrmConnect::TfrmConnect(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmConnect::bntOKClick(TObject *Sender)
{
  main->socket->Host = host->Text;
  main->socket->Port = port->Text.ToInt();
  main->SetRegOption("connecthost",host->Text);
  main->SetRegOption("connectport",port->Text);
  Close();
  Hide();
  main->Connect2BASIC(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmConnect::btnCancelClick(TObject *Sender)
{
  Close();
  Hide();
}
//---------------------------------------------------------------------------

void __fastcall TfrmConnect::FormCreate(TObject *Sender)
{
  host->Text = main->GetRegOption("connecthost");
  port->Text = main->GetRegOption("connectport");
        
}
//---------------------------------------------------------------------------

