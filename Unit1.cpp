//---------------------------------------------------------------------------

#include <vcl.h>
#include <time.h>
#include "IniFiles.hpp"
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TEngine *eng; //основной класс
TIniFile *ini = new TIniFile("max.ini");
using namespace std;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)            //конструктор формы
{
Form1->SettingImg->Picture->LoadFromFile("bmp/setting.bmp");
Form1->ImRes->Picture->LoadFromFile("bmp/reset.bmp");
Form1->MainImage->Canvas->Brush->Color=clBlack;
Form1->MainImage->Canvas->Rectangle(0,0,300,625);
Form1->StPause->Picture->LoadFromFile("bmp/start.bmp");
Form1->ImagePeople->Canvas->Brush->Color=clBlack;
Form1->ImagePeople->Canvas->Rectangle(0,0,121,353);
head= new TImage *[4];
  for (int i=0;i<4;i++){
  head[i]=new TImage(Form1);
  head[i]->Parent=Form1;
  head[i]->Top=i*25+200;
  head[i]->Left=i*25+325;
  head[i]->Height=25;
  head[i]->Width=25;
  head[i]->Picture->LoadFromFile("bmp/head"+IntToStr(i)+".bmp");
  }
hand= new TImage *[4];
  for (int i=0;i<4;i++){
  hand[i]=new TImage(Form1);
  hand[i]->Parent=Form1;
  hand[i]->Top=i*25+250;
  hand[i]->Left=i*25+325;
  hand[i]->Height=25;
  hand[i]->Width=25;
  hand[i]->Picture->LoadFromFile("bmp/hand"+IntToStr(i)+".bmp");
  }
food= new TImage *[4];
  for (int i=0;i<4;i++){
  food[i]=new TImage(Form1);
  food[i]->Parent=Form1;
  food[i]->Top=i*25+300;
  food[i]->Left=i*25+325;
  food[i]->Height=25;
  food[i]->Width=25;
  food[i]->Picture->LoadFromFile("bmp/food"+IntToStr(i)+".bmp");
  }

  leg_ch=new TImage(Form1);
  leg_ch->Parent=Form1;
  leg_ch->Top=350;
  leg_ch->Left=325;
  leg_ch->Height=25;
  leg_ch->Width=25;
  leg_ch->Picture->LoadFromFile("bmp/leg_ch0.bmp");

Form1->MainImage->Canvas->Pen->Color=clSilver;
Form1->MainImage->Canvas->Pen->Width=0.1;
  for (int i=0;i<13;i++){
    Form1->MainImage->Canvas->MoveTo(i*25,0);
    Form1->MainImage->Canvas->LineTo(i*25,625);
  }
  for (int i=0;i<25;i++){
    Form1->MainImage->Canvas->MoveTo(0,i*25);
    Form1->MainImage->Canvas->LineTo(300,i*25);
  }
eng=new TEngine();
//----------------
 srand(static_cast<unsigned>(time(NULL)));
 int var= rand()%8;
eng->make(var);

eng->max=ini->ReadInteger("max","max",0);
Form1->Timer1->Interval=ini->ReadInteger("speed","speed",1000);
Form1->Caption="“вой –≈«ульт: "+IntToStr(eng->top)+" ћј с –≈«ультат: "+IntToStr(eng->max);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ImResClick(TObject *Sender)
{
eng->detach();
eng->reset();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SettingImgClick(TObject *Sender)
{
Form1->Enabled=false;
Form2->Visible=true;
Form2->Edit1->Text=ini->ReadInteger("speed","speed",1000);
eng->detach();
eng->reset();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key==VK_END){
if (!eng->start){
Form1->StPause->Picture->LoadFromFile("bmp/stop.bmp");
}
else{
Form1->StPause->Picture->LoadFromFile("bmp/start.bmp");
}
eng->start=!eng->start;
Form1->Timer1->Enabled=eng->start;
}

if (eng->start)
switch (Key){
  case VK_LEFT:
  eng->block->move(-1,0);
  break;
  case VK_RIGHT:
  eng->block->move(1,0);
  break;
  case VK_DOWN:
  eng->block->move(0,1);
  break;
  case VK_UP:
  eng->block->rot();
  break;
  case VK_DELETE:{
  eng->detach();
  eng->reset();
  break;
  }
}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if (!eng->block->move(0,1)){
 srand(static_cast<unsigned>(time(NULL)));
 int var= rand()%8;
  eng->detach();
  eng->scan();
  eng->make(var);
}
//eng->block->rot();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StPauseClick(TObject *Sender)    //кнопка старт
{
if (!eng->start){
Form1->StPause->Picture->LoadFromFile("bmp/stop.bmp");
}
else{
Form1->StPause->Picture->LoadFromFile("bmp/start.bmp");
}
eng->start=!eng->start;
Form1->Timer1->Enabled=eng->start;
}
//---------------------------------------------------------------------------
//все что относитс€ к классу TEngine
TEngine::TEngine(){
for (int i=0;i<12;i++){
  for (int j=0;j<25;j++){
  cells[i][j]=false;
  }
}
for (int i=0;i<12;i++)
  cells[i][25]=true;
start = false;
block=new TBlock();
Hs=NULL;
top=0;
}

void TEngine::scan(){
bool b;
for (int j=0;j<25;j++){
b=true;
  for (int i=0;i<12;i++){
    if (cells[i][j]==false)
      b=false;
  }
if (b==true){
  Form1->Timer1->Enabled=false;
  del(j);
  Form1->Timer1->Enabled=true;
}
}
}

void TEngine::del(int y){
TSegment *buf,*p;
buf=Hs;
while (buf!=NULL){
  if (buf->Y==y){
   if (buf->img!=NULL){
    delete buf->img;
    buf->img=NULL;
    cells[buf->X][buf->Y]=false;
   }
  }
buf=buf->next;
}
top++;
Form1->Caption="“вой –≈«ульт: "+IntToStr(top)+" ћј с –≈«ультат: "+IntToStr(max);
}

void TEngine::reset(){
start=!start;
Form1->StPause->Picture->LoadFromFile("bmp/start.bmp");
Form1->Timer1->Enabled=false;

if (top>max){
  ini->WriteInteger("max","max",top);
  max=top;                                //сохранение в ини файл максимального
}

top=0;
Form1->Caption="“вой –≈«ульт: "+IntToStr(top)+" ћј с –≈«ультат: "+IntToStr(max);

TSegment *b;
while (Hs!=NULL){
  b=Hs->next;
  delete Hs;
  Hs=b;
}
for (int i=0;i<12;i++)
  for (int j=0;j<25;j++)
    cells[i][j]=false;

 srand(static_cast<unsigned>(time(NULL)));
 int var= rand()%8;
eng->make(var);
}

void TEngine::make(int v){
  block->x=5;
  block->y=2;
  if (!block->draw(v)){
    detach();
    reset();
    ShowMessage("»гра о ќЌ„иЌЌа!");
  }
}

void TEngine::detach(){
TSegment *buf;
buf=block->Hseg;
  while (buf!=NULL){
  cells[buf->X][buf->Y]=true;
  buf=buf->next;
  }
buf=block->Hseg;
  while (buf->next!=NULL){
  buf=buf->next;
  }
buf->next=Hs;
Hs=block->Hseg;
}

//все что относитс€ к классу TBlock
TBlock::TBlock(){
  Hseg=NULL;
  x=5;
  y=2;
}

bool TBlock::rot(){
TSegment *buf;
buf=Hseg;
int bx,by;
  while (buf!=NULL){
  bx=x+(buf->y);
  by=y-(buf->x);
    if ((bx<0)||(bx>11))         // тут проверка на вхождение в поле по икс
      return false;
    if (eng->cells[bx][by]==true)          //проверка по сетке
      return false;
  buf=buf->next;
  }
buf=Hseg;
  while (buf!=NULL){
  int p=buf->x;
  buf->x=(buf->y);
  buf->y=-p;
  buf->X=x+(buf->x);
  buf->Y=y+(buf->y);
  buf->img->Top=buf->Y*25;
  buf->img->Left=buf->X*25;
    if (buf->k>=3)
      buf->k=0;
    else
      buf->k++;
  switch (buf->s){
    case 0:
    buf->img->Picture=Form1->head[buf->k]->Picture;
    break;
    case 2:
    buf->img->Picture=Form1->hand[buf->k]->Picture;
    break;
    case 4:
    buf->img->Picture=Form1->food[buf->k]->Picture;
    break;
  }
  buf=buf->next;
  }
return true;
}

bool TBlock::move(int dx,int dy){
TSegment *buf;
buf=Hseg;
  while (buf!=NULL){
  int bx,by;
  bx=buf->X+dx;
  by=buf->Y+dy;
    if ((bx<0)||(bx>11))         // тут проверка на вхождение в поле по икс
      return true;
    if (eng->cells[bx][by]==true)          //проверка по сетке
      return false;
  buf=buf->next;
  }

  buf=Hseg;
  while (buf!=NULL){               //непосредственное перемешение
  buf->X+=dx;
  buf->Y+=dy;
  buf->img->Top=buf->Y*25;
  buf->img->Left=buf->X*25;
  buf=buf->next;
  }
x+=dx;
y+=dy;
return true;
}

bool TBlock::draw(int v){         //формирование блоков будет происходить именно тут
TSegment *buf;
Hseg=new TSegment();
Hseg->draw(1);
  switch (v){
    case 0:{
    //
    break;
    }
    case 1:{
    Hseg->next=new TSegment();
    Hseg->next->draw(0);
    break;
    }
    case 2:{
    Hseg->next=new TSegment();
    buf=Hseg->next;
    buf->draw(0);
     buf->next=new TSegment();
     buf->next->draw(2);
    break;
    }
    case 3:{
    Hseg->next=new TSegment();
    buf=Hseg->next;
    buf->draw(0);
     buf->next=new TSegment();
     buf=buf->next;
     buf->draw(2);
       buf->next=new TSegment();
       buf=buf->next;
       buf->draw(3);
    break;
    }
    case 4:{
    Hseg->next=new TSegment();
    buf=Hseg->next;
    buf->draw(0);
       buf->next=new TSegment();
       buf=buf->next;
       buf->draw(3);
         buf->next= new TSegment();
         buf=buf->next;
         buf->draw(4);
    break;
    }
    case 5:{
    Hseg->next=new TSegment();
    buf=Hseg->next;
    buf->draw(0);
     buf->next=new TSegment();
     buf=buf->next;
     buf->draw(2);
       buf->next=new TSegment();
       buf=buf->next;
       buf->draw(3);
         buf->next= new TSegment();
         buf=buf->next;
         buf->draw(4);
    break;
    }
    case 6:{
    Hseg->next=new TSegment();
    buf=Hseg->next;
    buf->draw(0);
       buf->next=new TSegment();
       buf=buf->next;
       buf->draw(3);
    break;
    }
    case 7:{
    Hseg->next=new TSegment();
    buf=Hseg->next;
    buf->draw(2);
       buf->next=new TSegment();
       buf=buf->next;
       buf->draw(3);
         buf->next= new TSegment();
         buf=buf->next;
         buf->draw(4);
    break;
    }
  }
buf=Hseg;
while (buf!=NULL){
 if (eng->cells[buf->X][buf->Y]==true)
   return false;
 else
   return true;
buf=buf->next;
}
}

//все что относитс€ к классу TSegment
TSegment::TSegment(){
  next = NULL;
}

void TSegment::draw(int v){
s=v;
k=0;
img=new TImage(Form1);
img->Parent=Form1;
img->Height=25;
img->Width=25;
switch (v){
 case 0:{
 img->Picture=Form1->head[0]->Picture;
 x=-1; y=0;
 break;
 }
 case 1:{
 img->Picture=Form1->leg_ch->Picture;
 x=0; y=0;
 break;
 }
 case 2:{
 img->Picture=Form1->hand[0]->Picture;
 x=0; y=1;
 break;
 }
 case 3:{
 img->Picture=Form1->leg_ch->Picture;
 x=1;y=0;
 break;
 }
 case 4:{
 img->Picture=Form1->food[0]->Picture;
 x=2; y=0;
 break;
 }
}
Y=y+2;
X=x+5;
img->Top=Y*25;
img->Left=X*25;
}

TSegment::~TSegment(){
delete img;
}


