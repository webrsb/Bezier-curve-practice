//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool DrawFlag,PointEnd;
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
	PointEnd = true;
	bmp      = new Graphics::TBitmap();  //建立一個新的bmp物件
	bmp_back = new Graphics::TBitmap();
	Clear();

	//設定控制點
	data.num_point = 3;
	data.width = 10;
	data.height= 10;
	data.brush_color = clYellow;
	data.pen_color   = clBlack;
	data.pen_size   = 4;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	Label2->Caption = X;
	Label4->Caption = Y;
	if(DrawFlag == true){
		X1 = X;
		Y1 = Y;
		DrawLine(X0,Y0,X1,Y1);      //目前的點
		DrawPoint(X1,Y1);
		DrawPoint(X0,Y0);
		Image1->Picture->Bitmap = bmp;
	}
}

//---------------------------------------------------------------------------
void TForm1::DrawPoint(int X,int Y){
	float small_pen = data.pen_size/2;
	bmp->Canvas->Pen->Width=data.pen_size;
	bmp->Canvas->Brush->Color = data.brush_color;     //填滿的顏色
	bmp->Canvas->Pen->Color = data.pen_color;         //邊框的顏色
	bmp->Canvas->Rectangle( TRect(X - data.width, Y - data.height ,X+data.width-small_pen+1,Y+data.height-small_pen+1)); // 畫一下顏色表示已經在Form上
}
//---------------------------------------------------------------------------

void TForm1::DrawLine(int X0,int Y0,int X1,int Y1){
		bmp->Assign(bmp_back);
		bmp->Canvas->MoveTo(X0,Y0) ;       //起點
		bmp->Canvas->LineTo(X1,Y1) ;         //目前的點
}
//---------------------------------------------------------------------------

void TForm1::MovePoint(int X,int Y){
	float small_pen = data.pen_size/2;
	if(X >= X0 - data.width - small_pen && Y >= Y0 - data.height - small_pen && X <= X0+data.width-small_pen+1 && Y<= Y0+data.height-small_pen+1){
		int tmp;
		tmp = X0;
		X0 = X1;
		X1 = tmp;
		tmp = Y0;
		Y0 = Y1;
		Y1 = tmp;
		DrawFlag = true;
	}else if(X >= X1 - data.width - small_pen && Y >= Y1 - data.height - small_pen && X <= X1+data.width-small_pen+1 && Y<= Y1+data.height-small_pen+1){
		DrawFlag = true;
	}else{
		PointEnd =true;
		DrawLine(X0,Y0,X1,Y1);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
		DrawFlag = false;
		Image1->Picture->Bitmap = bmp;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(PointEnd == true){
		X0 = X1 =X;          //記錄起點
		Y0 = Y1 =Y;
		bmp_back->Assign(bmp);        //記錄點陣圖
		DrawPoint(X0,Y0);
		Image1->Picture->Bitmap = bmp;
		DrawFlag = true;
		PointEnd = false;
	}else{
		MovePoint(X,Y);
    }

	Label6->Caption = X0;
	Label8->Caption = Y0;
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
