//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("debugger.res");
USEFORM("main_form.cpp", main);
USEFORM("options_form.cpp", FormOptions);
USEFORM("connect_form.cpp", frmConnect);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(Tmain), &main);
                 Application->CreateForm(__classid(TFormOptions), &FormOptions);
                 Application->CreateForm(__classid(TfrmConnect), &frmConnect);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
