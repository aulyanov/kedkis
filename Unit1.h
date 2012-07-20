//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TSegment{
public:
int k;// k*p/2
int s;// какой именно сегмент нужен нам
TSegment();
~TSegment();
void draw(int v);
void move(int,int);
void rot(int s);
int x;
int y;
int X;
int Y;
TSegment *next;
TImage *img;
};

class TBlock{
public:
TBlock::TBlock();
int x;
int y;
TSegment *Hseg;
bool draw(int v);
bool move(int dx,int dy);
bool rot();
};

class TEngine{
public:
TEngine();
void reset();
void make(int v);
void detach();
void scan();
void del(int);
unsigned long top;
unsigned long max;
bool cells[12][26];
bool start;
TBlock *block;
TSegment *Hs;
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *MainImage;
        TImage *StPause;
        TImage *ImagePeople;
        TTimer *Timer1;
        TImage *ImRes;
        TImage *SettingImg;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall StPauseClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ImResClick(TObject *Sender);
        void __fastcall SettingImgClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
TImage **head,**hand,**food,*leg_ch;
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
