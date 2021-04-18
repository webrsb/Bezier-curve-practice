//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool DrawFlag,PointEnd,Click_flag;
int X0,Y0,X1,Y1,X2,Y2,options;
//0起點 1終點 2 P點
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	DrawFlag = false;
	PointEnd = true;    //是否已結束移動控制點
	Click_flag = false;
	bmp      = new Graphics::TBitmap();  //建立一個新的bmp物件
	bmp_back = new Graphics::TBitmap();
	Clear();

	//設定控制點
	data.num_point = 3;
	data.width = 3;
	data.height= 3;
	data.brush_color = clYellow;
	data.pen_color   = clBlack;
	data.pen_size   = 2;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	Label2->Caption = X;
	Label4->Caption = Y;
	if(DrawFlag == true){
		if(options == 0){
			X1 = X;
			Y1 = Y;
			DrawLine(X0,Y0,X1,Y1,X2,Y2);      //目前的點
			DrawPoint(X0,Y0);
			DrawPoint(X1,Y1);
			DrawPoint(X2,Y2);
			Image1->Picture->Bitmap = bmp;
		}else if(options == 1){
			X2 = X;    //移動P點
			Y2 = Y;
			DrawLine(X0,Y0,X1,Y1,X2,Y2);      //目前的點
			DrawPoint(X1,Y1);
			DrawPoint(X0,Y0);
			DrawPoint(X2,Y2);
			Image1->Picture->Bitmap = bmp;
		}
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

void TForm1::DrawLine(int X0,int Y0,int X1,int Y1,int X2,int Y2){
	bmp->Assign(bmp_back);
	float B_x,B_y,P1_x,P1_y;
	P1_x = X1 - (X2 - X1);
	P1_y = Y1 - (Y2 - Y1);
	for(float t=0;t<=1;t+=0.001){
		B_x = ((1-t) * (1-t)) * X0 + (2*t)*(1-t) * P1_x + t*t*X1;
		B_y = ((1-t) * (1-t)) * Y0 + (2*t)*(1-t) * P1_y + t*t*Y1;
		bmp->Canvas->MoveTo(B_x,B_y) ;       //起點
		bmp->Canvas->LineTo(B_x,B_y) ;         //目前的點
	}
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
		options = 0;
		DrawFlag = true;
	}else if(X >= X1 - data.width - small_pen && Y >= Y1 - data.height - small_pen && X <= X1+data.width-small_pen+1 && Y<= Y1+data.height-small_pen+1){
		options = 0;
		DrawFlag = true;
	}else if(X >= X2 - data.width - small_pen && Y >= Y2 - data.height - small_pen && X <= X2+data.width-small_pen+1 && Y<= Y2+data.height-small_pen+1){
		options = 1;
		DrawFlag = true;
	}else{
		PointEnd =true;      //結束控制點狀態
		DrawLine(X0,Y0,X1,Y1,X2,Y2);
		Click_flag = false;
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
		if(Click_flag == false){
			X0 = X1 =X;          //記錄起點
			Y0 = Y1 =Y;          //起點等於終點
			bmp_back->Assign(bmp);        //記錄點陣圖
			DrawPoint(X0,Y0);         //顯示控制點
			Image1->Picture->Bitmap = bmp;  //顯示結果
			Click_flag = true; //已設置起點
		}else{             //第二次按下
			X1 = X2 = X;          //終點座標
			Y1 = Y2 = Y;          //P點等於終點
			DrawLine(X0,Y0,X1,Y1,X2,Y2);
			DrawPoint(X0,Y0);
			DrawPoint(X1,Y1);
			Image1->Picture->Bitmap = bmp;
			options = 1;
			DrawFlag = true;
			PointEnd = false;
		}
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
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int P0_x,P0_y,P1_x,P1_y,P2_x,P2_y,B_x,B_y;
	P0_x = 10;
	P0_y = 50;
	P1_x = 200;
	P1_y = 50;
	P2_x = 550;
	P2_y = 125;
	bmp->Canvas->Pen->Width = 3;
	for(float t=0;t<=1;t+=0.001){        //目前的點
		B_x = ((1-t) * (1-t)) * P0_x + (2*t)*(1-t) * P1_x + t*t*P2_x;
		B_y = ((1-t) * (1-t)) * P0_y + (2*t)*(1-t) * P1_y + t*t*P2_y;
		bmp->Canvas->MoveTo(B_x,B_y) ;       //起點
		bmp->Canvas->LineTo(B_x,B_y) ;         //目前的點
	}
	Image1->Picture->Bitmap = bmp;
}
//---------------------------------------------------------------------------


