//---------------------------------------------------------------------------

#ifndef options_formH
#define options_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:	// IDE-managed Components
        TButton *btnCancel;
        TButton *btnOK;
        TButton *btnApply;
        TLabel *Label3;
        TEdit *commandline;
        TButton *btnBrowse;
        TOpenDialog *OpenScriba;
        TLabel *Label4;
        TEdit *traceDt;
        TLabel *Label5;
        TFontDialog *font;
        TButton *btnFont;
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnApplyClick(TObject *Sender);
        void __fastcall btnBrowseClick(TObject *Sender);
        void __fastcall traceDtKeyPress(TObject *Sender, char &Key);
        void __fastcall btnFontClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
