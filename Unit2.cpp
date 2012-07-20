//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "IniFiles.hpp"

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
TIniFile *ini = new TIniFile("max.ini");
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
Form1->Enabled=true;
ini->WriteInteger("speed","speed",StrToInt(Form2->Edit1->Text));
Form1->Timer1->Interval=StrToInt(Form2->Edit1->Text);
}
//---------------------------------------------------------------------------
