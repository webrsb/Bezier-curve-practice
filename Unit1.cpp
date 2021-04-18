//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool DrawFlag,LineEnd;
TImage **points;
int X0,Y0,X1,Y1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	DrawFlag = false;
	LineEnd  = true;
	bmp      = new Graphics::TBitmap();  //建立一個新的bmp物件
	bmp_back = new Graphics::TBitmap();
	//設定控制點
	data.num_point = 3;
	data.width = 10;
	data.height= 10;
	data.brush_color = clYellow;
	data.pen_color   = clBlack;
	data.pen_size   = 2;

	Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	Label2->Caption = X;
	Label4->Caption = Y;
	if(DrawFlag == true){
		bmp->Assign(bmp_back);
		bmp->Canvas->MoveTo(X0,Y0) ;       //起點
		bmp->Canvas->LineTo(X1,Y1) ;         //目前的點
		Image1->Picture->Bitmap = bmp;
		points[1]->Left = X - data.width/2;
		points[1]->Top = Y - data.height/2;
		X1 = X;
		Y1 = Y;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	DrawFlag = false;
	LineEnd = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(LineEnd == true){
		points[0]->Left = X - data.width/2;//控制點的位置
		points[0]->Top = Y - data.height/2;
		points[1]->Left = X - data.width/2;
		points[1]->Top = Y - data.height/2;
		bmp_back->Assign(bmp);        //記錄點陣圖
		DrawFlag = true;
		X0 = X1 =X;          //記錄起點
		Y0 = Y1 =Y;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Clear();
}
//---------------------------------------------------------------------------
void TForm1::Clear(){
	bmp->Height= Image1->Height;
	bmp->Width = Image1->Width;
	bmp->Canvas->Brush->Color = clGray;     //填滿的顏色
	bmp->Canvas->Pen->Color = clBlack;         //邊框的顏色
	bmp->Canvas->Pen->Width=5;
	bmp->Canvas->Rectangle( TRect(0, 0,Image1->Width,Image1->Height));
	Image1->Picture->Bitmap = bmp;
}
void __fastcall TForm1::Button2Click(TObject *Sender)
{

points = new TImage*[data.num_point];  // 這裡的雙*是指標的陣列，不是2維陣列
float small_pen = data.pen_size/2;
for (int i=0 ; i<data.num_point ; ++i)
{
  // 因為是指標陣列所以在取用方法與屬性時，得用ptr->或(*ptr).方法
  points[i] = new TImage(this);
  points[i]->AutoSize = false;
  points[i]->Left = 100*i + 10*(i+1); // 要擺放的位置x軸
  points[i]->Top = 20;  // 要擺放的位置y軸
  points[i]->Canvas->Pen->Width=data.pen_size;
  points[i]->Canvas->Brush->Color = data.brush_color;     //填滿的顏色
  points[i]->Canvas->Pen->Color = data.pen_color;         //邊框的顏色
  points[i]->Height = data.height; // 影像物件的高度
  points[i]->Width = data.width;  // 影像物件的寬度
  points[i]->OnMouseDown  = pointsMouseDown;
  points[i]->Tag=i;
  points[i]->Parent=this;  // 要擺放的Form 或 Container
  points[i]->Canvas->Rectangle( TRect(small_pen, small_pen,data.width-small_pen+1,data.height-small_pen+1)); // 畫一下顏色表示已經在Form上
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pointsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y){
	TImage *pointshow=(TImage*)Sender;
	int NO = pointshow->Tag;
   /*	if(NO == 0){
		int tmp;
		tmp = X0;
		X0 = X1;
		X1 = tmp;
		tmp = Y0;
		Y0 = Y1;
		Y1 = tmp;
		DrawFlag = true;
	}           */
	DrawFlag = true;
}
