//---------------------------------------------------------------------------

#ifndef connect_formH
#define connect_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmConnect : public TForm
{
__published:	// IDE-managed Components
        TEdit *host;
        TLabel *Label1;
        TEdit *port;
        TButton *bntOK;
        TButton *btnCancel;
        void __fastcall bntOKClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmConnect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConnect *frmConnect;
//---------------------------------------------------------------------------
#endif
