//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool DrawFlag,PointEnd,Click_flag,MovePoint_flag;
unsigned int options;
//0起點 1終點 2 P點
int p_data[100][6],lines,clickline;
//0 1起點 2 3終點 4 5  p點

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	DrawFlag = false;   //繪圖模式
	PointEnd = true;    //是否已結束移動控制點
	Click_flag = false;
	MovePoint_flag = false; //移動控制點模式
	lines = 1;
	bmp      = new Graphics::TBitmap();  //建立一個新的bmp物件
	bmp_back = new Graphics::TBitmap();
	bmp_new = new Graphics::TBitmap();
	Clear();

	//設定控制點
	data.num_point = 3;
	data.width = 6;
	data.height= 6;
	data.brush_color = clYellow;
	data.pen_color   = clBlack;
	data.pen_size   = 4;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(DrawFlag == true){
		//bmp->Assign(bmp_back);
		Label2->Caption = X;
		Label4->Caption = Y;
		if(options == 0){
			p_data[lines][2] = X;
			p_data[lines][3] = Y;
			DrawLine(lines);
			DrawPoint(lines);
			Image1->Picture->Bitmap = bmp;
		}else if(options == 1){
			p_data[lines][4] = X;    //移動P點
			p_data[lines][5] = Y;
			DrawLine(lines);
			DrawPoint(lines);
			Image1->Picture->Bitmap = bmp;
		}
	}
	if(MovePoint_flag == true){      //移動控制點

	//bmp->Assign(bmp_back);
		int temp;
		Label2->Caption = X;
		Label4->Caption = Y;
		if(clickline >0){
		  p_data[clickline][2] = X;
		  p_data[clickline][3] = Y;
		  p_data[clickline+1][0] = X;
		  p_data[clickline+1][1] = Y;

	 int line;
	bmp->Assign(bmp_back);
	line = clickline;
	float B_x,B_y,P1_x,P1_y;
	P1_x = p_data[line][2] - (p_data[line][4] - p_data[line][2]);
	P1_y = p_data[line][3] - (p_data[line][5] - p_data[line][3]);
	for(float t=0;t<=1;t+=0.001){
		B_x = ((1-t) * (1-t)) * p_data[line][0] + (2*t)*(1-t) * P1_x + t*t*p_data[line][2];
		B_y = ((1-t) * (1-t)) * p_data[line][1] + (2*t)*(1-t) * P1_y + t*t*p_data[line][3];
		bmp->Canvas->MoveTo(B_x,B_y) ;       //起點
		bmp->Canvas->LineTo(B_x,B_y) ;         //目前的點
	}  /*
	line = clickline+1;
	P1_x = p_data[line][2] - (p_data[line][4] - p_data[line][2]);
	P1_y = p_data[line][3] - (p_data[line][5] - p_data[line][3]);
	for(float t=0;t<=1;t+=0.001){
		B_x = ((1-t) * (1-t)) * p_data[line][0] + (2*t)*(1-t) * P1_x + t*t*p_data[line][2];
		B_y = ((1-t) * (1-t)) * p_data[line][1] + (2*t)*(1-t) * P1_y + t*t*p_data[line][3];
		bmp->Canvas->MoveTo(B_x,B_y) ;       //起點
		bmp->Canvas->LineTo(B_x,B_y) ;         //目前的點
	}
         */

			DrawPoint(clickline);
			Image1->Picture->Bitmap = bmp;
		}

		 /*
		if(options == 0){
			p_data[lines][2] = X;
			p_data[lines][3] = Y;
			DrawLine(lines);
			DrawPoint(lines);
			Image1->Picture->Bitmap = bmp;
		}else if(options == 1){
			p_data[lines][4] = X;    //移動P點
			p_data[lines][5] = Y;
			DrawLine(lines);
			DrawPoint(lines);
			Image1->Picture->Bitmap = bmp;
		}                             */
	}
}
//---------------------------------------------------------------------------
void TForm1::ReDraw(int line){
	if(line >= 1){
		bmp_back->Assign(bmp_new);
		for(int i=0;i<=lines;i++){
			if(i !=line && i!=line+1){
				DrawLine(i);
				bmp_back->Assign(bmp);   //儲檔
			}
		}
		Image1->Picture->Bitmap = bmp;
	}
}
//---------------------------------------------------------------------------
void TForm1::DrawPoint(int line){
	float small_pen = data.pen_size/2;
	bmp->Canvas->Pen->Width=data.pen_size;
	bmp->Canvas->Brush->Color = data.brush_color;     //填滿的顏色
	bmp->Canvas->Pen->Color = data.pen_color;         //邊框的顏色
	for(int i=0;i<6;i+=2){
		if(p_data[line][i] != NULL || p_data[line][i-1] != NULL)
			bmp->Canvas->Rectangle( TRect(p_data[line][i] - data.width, p_data[line][i+1] - data.height ,p_data[line][i]+data.width-small_pen+1,p_data[line][i+1]+data.height-small_pen+1)); // 畫一下顏色表示已經在Form上
	}
}
//---------------------------------------------------------------------------

void TForm1::DrawLine(int line){
	bmp->Assign(bmp_back);
	float B_x,B_y,P1_x,P1_y;
	P1_x = p_data[line][2] - (p_data[line][4] - p_data[line][2]);
	P1_y = p_data[line][3] - (p_data[line][5] - p_data[line][3]);
	for(float t=0;t<=1;t+=0.001){
		B_x = ((1-t) * (1-t)) * p_data[line][0] + (2*t)*(1-t) * P1_x + t*t*p_data[line][2];
		B_y = ((1-t) * (1-t)) * p_data[line][1] + (2*t)*(1-t) * P1_y + t*t*p_data[line][3];
		bmp->Canvas->MoveTo(B_x,B_y) ;       //起點
		bmp->Canvas->LineTo(B_x,B_y) ;         //目前的點
	}
}
//---------------------------------------------------------------------------

void TForm1::MovePoint(int X,int Y){
	float small_pen = data.pen_size/2;
	for(int i=1;i<=lines;i++){
		if(i == 1 && X >= p_data[i][0] - data.width - small_pen && Y >= p_data[i][1] - data.height - small_pen && X <= p_data[i][0]+data.width-small_pen+1 && Y<= p_data[i][1]+data.height-small_pen+1){
			bmp_back->Assign(bmp_new);
			for(int i=2;i<=lines;i++){
				DrawLine(i);
				bmp_back->Assign(bmp);   //儲檔
			}
			Image1->Picture->Bitmap = bmp;
			 //ShowMessage("第一點到起點");
			 clickline = i;
			return;
		}else{
			if(X >= p_data[i][0] - data.width - small_pen && Y >= p_data[i][1] - data.height - small_pen && X <= p_data[i][0]+data.width-small_pen+1 && Y<= p_data[i][1]+data.height-small_pen+1){
				int tmp;
				tmp = p_data[i][0];
				p_data[i][0] = p_data[i][2];
				p_data[i][2] = tmp;
				tmp = p_data[i][1];
				p_data[i][1] = p_data[i][3];
				p_data[i][3] = tmp;
				options = 0;
				MovePoint_flag = true;
				ReDraw(i);
				clickline = i;
				//ShowMessage("點到起點");
				return;
			}else if(X >= p_data[i][2] - data.width - small_pen && Y >= p_data[i][3] - data.height - small_pen && X <= p_data[i][2]+data.width-small_pen+1 && Y<= p_data[i][3]+data.height-small_pen+1){
				if(i == lines){
					bmp_back->Assign(bmp_new);
					for(int i=1;i<lines;i++){
						DrawLine(i);
						bmp_back->Assign(bmp);   //儲檔
					}
				Image1->Picture->Bitmap = bmp;
				//ShowMessage("最後的終點");
				}else{
					options = 0;
					MovePoint_flag = true;
					ReDraw(i);
					//ShowMessage("點到終點") ;
				}
				clickline = i;
				return;
			}else if(X >= p_data[i][4] - data.width - small_pen && Y >= p_data[i][5] - data.height - small_pen && X <= p_data[i][4]+data.width-small_pen+1 && Y<= p_data[i][5]+data.height-small_pen+1){
				options = 1;
				MovePoint_flag = true;
				ReDraw(-i);
				//ShowMessage("點到P點");
				clickline = -i;
				return;
			}
		}
	}
		DrawLine(lines); //將最終圖畫上去
		bmp_back->Assign(bmp);//存圖
		lines ++ ;
		p_data[lines][0] = p_data[lines-1][2];
		p_data[lines][1] = p_data[lines-1][3];
		PointEnd =true;      //結束控制點狀態
		p_data[lines][2] = p_data[lines][4] = X;          //終點座標
		p_data[lines][3] = p_data[lines][5] = Y;          //P點等於終點
		DrawLine(lines);
		DrawPoint(lines);
		Image1->Picture->Bitmap = bmp;
		options = 1;
		DrawFlag = true;
		PointEnd = false;
		//bmp_back->Assign(bmp_new);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
		DrawFlag = false;
		MovePoint_flag = false;
		for(int i=1;i<=lines;i++)
		DrawPoint(i);
		Image1->Picture->Bitmap = bmp;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(PointEnd == true){
		if(Click_flag == false){    //所有的開始
			p_data[lines][0] = X ;
			p_data[lines][1] = Y ;
			p_data[lines][2] = X ;
			p_data[lines][3] = Y ;
			bmp_back->Assign(bmp);        //記錄點陣圖
			bmp_new->Assign(bmp);
			DrawPoint(lines);         //顯示控制點
			Image1->Picture->Bitmap = bmp;  //顯示結果
			Click_flag = true; //已設置起點
		}else{             //第二次按下
			p_data[lines][2] = X ;
			p_data[lines][3] = Y ;
			p_data[lines][4] = X ;
			p_data[lines][5] = Y ;
			//X1 = X2 = X;          //終點座標
			//Y1 = Y2 = Y;          //P點等於終點
			DrawLine(lines);
			DrawPoint(lines);
			Image1->Picture->Bitmap = bmp;
			options = 1;
			DrawFlag = true;
			PointEnd = false;
		}
	}else{                  //控制點模式
		MovePoint(X,Y);
	}
	Label6->Caption = p_data[lines][0];
	Label8->Caption = p_data[lines][1];
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
	bmp->Canvas->Pen->Width=3;
	bmp->Canvas->Rectangle( TRect(0, 0,Image1->Width,Image1->Height));
	Image1->Picture->Bitmap = bmp;
}
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Image1->Picture->Bitmap = bmp;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShortCut(TWMKey &Msg, bool &Handled)
{
	if(Msg.CharCode ==  27){
		PointEnd =true;      //結束控制點狀態
		DrawLine(lines);
		Click_flag = false;
		DrawFlag = false;
		Image1->Picture->Bitmap = bmp;

	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
		  bmp->Assign(bmp_new);//存圖
		  DrawLine(1);
		  DrawPoint(1);
		  Image1->Picture->Bitmap = bmp;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
			bmp->Assign(bmp_new);//存圖
		  DrawLine(2);
		  DrawPoint(2);
		  Image1->Picture->Bitmap = bmp;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Image1->Picture->Bitmap = bmp_back;
}
//---------------------------------------------------------------------------

