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
int p_data[100][6],lines,click_data[2]; //0 第幾條線 1 起點 終點 P點 是否重疊
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
	lines = 0;
	bmp      = new Graphics::TBitmap();  //建立一個新的bmp物件
	bmp_back = new Graphics::TBitmap();
	bmp_new = new Graphics::TBitmap();
	for(int i=0;i<100;i++)
		for(int j=0;j<6;j++){
			p_data[i][j] = NULL;
	}
	Clear();

	//設定控制點
	data.num_point = 3;
	data.width = 2.5;
	data.height= 2.5;
	data.brush_color = clYellow;
	data.pen_color   = clBlack;
	data.pen_size   = 1;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(DrawFlag == true){
		Label2->Caption = X;
		Label4->Caption = Y;
		if(options == 0){
			p_data[lines][2] = X;
			p_data[lines][3] = Y;
			bmp->Assign(bmp_back);
			DrawLine(lines);
			for(int i=0;i<6;i+=2)
			DrawPoint(lines,i);
			Image1->Picture->Bitmap = bmp;
		}else if(options == 1){
			p_data[lines][4] = X;    //移動P點
			p_data[lines][5] = Y;
			bmp->Assign(bmp_back);
			DrawLine(lines);
			for(int i=0;i<6;i+=2)
			DrawPoint(lines,i);
			Image1->Picture->Bitmap = bmp;
		}
	}
	if(MovePoint_flag == true){      //移動控制點
		//0 第幾條線 1點的狀態 (0重疊線 1 P點 ,2起點3終點 )
		if(click_data[1] == 0){
			p_data[click_data[0]][2] = X;
			p_data[click_data[0]][3] = Y;
			p_data[click_data[0]+1][0] = X;
			p_data[click_data[0]+1][1] = Y;
			bmp->Assign(bmp_back);
			//ShowMessage("123");
			DrawLine_double(click_data[0]);
			for (int i = 0; i < 2; i++)
				for(int j=0;j<6;j+=2)
				DrawPoint(click_data[0]+i,j);
			Image1->Picture->Bitmap = bmp;
		   //
		}else if(click_data[1] == 1){
			p_data[click_data[0]][4] = X;
			p_data[click_data[0]][5] = Y;
			bmp->Assign(bmp_back);
			DrawLine(click_data[0]);
			DrawPoint(click_data[0],0);
			DrawPoint(click_data[0],2);
			DrawPoint(click_data[0],4);
			Image1->Picture->Bitmap = bmp;
		}else if(click_data[1] == 2){
			p_data[click_data[0]][0] = X;
			p_data[click_data[0]][1] = Y;
			bmp->Assign(bmp_back);
			DrawLine(click_data[0]);
			DrawPoint(click_data[0],0);
			DrawPoint(click_data[0],2);
			Image1->Picture->Bitmap = bmp;
		}else if(click_data[1] == 3){
			p_data[click_data[0]][2] = X;
			p_data[click_data[0]][3] = Y;
			bmp->Assign(bmp_back);
			DrawLine(click_data[0]);
			for(int i=0;i<6;i+=2)
			DrawPoint(click_data[0],i);
			Image1->Picture->Bitmap = bmp;
		}

	}

}
//---------------------------------------------------------------------------
void TForm1::EndDraw(){
if(lines != 0){
	SaveDraw();
	Image1->Picture->Bitmap = bmp;
	lines = 0;
	PointEnd =true;      //結束控制點狀態
	Click_flag = false;
 	DrawFlag = false;
	for(int i=0;i<100;i++)
		for(int j=0;j<6;j++){
			p_data[i][j] = NULL;
	}
}
}
//---------------------------------------------------------------------------
void TForm1::ReDraw(int line,int mode){
	bmp->Assign(bmp_new);
	bmp_back->Assign(bmp_new);
	if(mode == 0){           //重疊線
		for(int i=1;i<=lines;i++){
			if(!(i ==line || i==line+1)){
				DrawLine(i);
			}
		}
		bmp_back->Assign(bmp);   //儲檔

	}else if(mode == 1){   //p點
		for(int i=1;i<=lines;i++){
			if(i !=line){
				DrawLine(i);
			}
			bmp_back->Assign(bmp);   //儲檔
		}
	}else if(mode == 2){       //起點
		for(int i=2;i<=lines;i++){
			DrawLine(i);
		}
		bmp_back->Assign(bmp);   //儲檔
	}else if(mode == 3){          //終點
		for(int i=1;i<lines;i++){
			DrawLine(i);
		}
		bmp_back->Assign(bmp);   //儲檔
	}
	//ShowMessage("12");
}
//---------------------------------------------------------------------------
void TForm1::SaveDraw(){
	bmp->Assign(bmp_new);//清空
	for(int i=0;i<=lines;i++)
	{
		DrawLine(i);
	}
	bmp_back->Assign(bmp);//存圖
			//Image1->Picture->Bitmap = bmp;
}
//---------------------------------------------------------------------------
void TForm1::DrawPoint(int line,int i){
	if(p_data[line][i] == NULL || p_data[line][i+1] == NULL)
	return;
	float small_pen = data.pen_size/2;
	bmp->Canvas->Brush->Color = data.brush_color;     //填滿的顏色
	if (i==4) {
		bmp->Canvas->Brush->Color = clBlack;
		bmp->Canvas->Pen->Style = psDash ; //psDot ;
		bmp->Canvas->Pen->Width = 1 ;
		bmp->Canvas->MoveTo(p_data[line][i],p_data[line][i+1]) ;       //起點
		bmp->Canvas->LineTo(p_data[line][i-2],p_data[line][i-1]) ;
		bmp->Canvas->Brush->Color = clRed;
	}
	bmp->Canvas->Pen->Style = psSolid ; //psDot ;
	bmp->Canvas->Pen->Width=data.pen_size;
	bmp->Canvas->Pen->Color = data.pen_color;         //邊框的顏色

	bmp->Canvas->Rectangle( TRect(p_data[line][i] - data.width, p_data[line][i+1] - data.height ,p_data[line][i]+data.width-small_pen+1,p_data[line][i+1]+data.height-small_pen+1)); // 畫一下顏色表示已經在Form上

}
//---------------------------------------------------------------------------

void TForm1::DrawLine_double(int line){
	//bmp->Assign(bmp_back);
	bmp->Canvas->Pen->Width=2;
	bmp->Canvas->Brush->Color =clBlack;
	float B_x_1,B_y_1,P1_x_1,P1_y_1,B_x_2,B_y_2,P1_x_2,P1_y_2,Bx_1,By_1,Bx_2,By_2,range;
	P1_x_1 = p_data[line][2] - (p_data[line][4] - p_data[line][2]);
	P1_y_1 = p_data[line][3] - (p_data[line][5] - p_data[line][3]);
	P1_x_2 = p_data[line+1][2] - (p_data[line+1][4] - p_data[line+1][2]);
	P1_y_2 = p_data[line+1][3] - (p_data[line+1][5] - p_data[line+1][3]);

	Bx_1 = ((1-0) * (1-0)) * p_data[line][0] + (2*0)*(1-0) * P1_x_1 + 0*0*p_data[line][2];
	By_1 = ((1-0) * (1-0)) * p_data[line][1] + (2*0)*(1-0) * P1_y_1 + 0*0*p_data[line][3];
	Bx_2 = ((1-0) * (1-0)) * p_data[line+1][0] + (2*0)*(1-0) * P1_x_2 + 0*0*p_data[line+1][2];
	By_2 = ((1-0) * (1-0)) * p_data[line+1][1] + (2*0)*(1-0) * P1_y_2 + 0*0*p_data[line+1][3];
	range = 0.01;
	for(float t=range;t<=1;t+=range){
		B_x_1 = ((1-t) * (1-t)) * p_data[line][0] + (2*t)*(1-t) * P1_x_1 + t*t*p_data[line][2];
		B_y_1 = ((1-t) * (1-t)) * p_data[line][1] + (2*t)*(1-t) * P1_y_1 + t*t*p_data[line][3];
		B_x_2 = ((1-t) * (1-t)) * p_data[line+1][0] + (2*t)*(1-t) * P1_x_2 + t*t*p_data[line+1][2];
		B_y_2 = ((1-t) * (1-t)) * p_data[line+1][1] + (2*t)*(1-t) * P1_y_2 + t*t*p_data[line+1][3];
		bmp->Canvas->MoveTo(Bx_1,By_1) ;       //起點
		bmp->Canvas->LineTo(B_x_1,B_y_1) ;
		bmp->Canvas->MoveTo(Bx_2,By_2) ;       //起點
		bmp->Canvas->LineTo(B_x_2,B_y_2) ;         //目前的點
		B_x_1 = Bx_1;
		B_y_1 = By_1;
		B_x_2 = Bx_2;
		B_y_2 = By_2;

	}
}
//---------------------------------------------------------------------------

void TForm1::DrawLine(int line){
	bmp->Canvas->Pen->Width=2;
	bmp->Canvas->Brush->Color =clBlack;
	//bmp->Assign(bmp_back);
	float B_x,B_y,P1_x,P1_y,B_x_2,B_y_2,range;
	P1_x = p_data[line][2] - (p_data[line][4] - p_data[line][2]);
	P1_y = p_data[line][3] - (p_data[line][5] - p_data[line][3]);
	B_x = ((1-0) * (1-0)) * p_data[line][0] + (2*0)*(1-0) * P1_x + 0*0*p_data[line][2];
	B_y = ((1-0) * (1-0)) * p_data[line][1] + (2*0)*(1-0) * P1_y + 0*0*p_data[line][3];
	range = 0.01;
	for(float t=range;t<=1;t+=range){
		B_x_2 = ((1-t) * (1-t)) * p_data[line][0] + (2*t)*(1-t) * P1_x + t*t*p_data[line][2];
		B_y_2 = ((1-t) * (1-t)) * p_data[line][1] + (2*t)*(1-t) * P1_y + t*t*p_data[line][3];
		bmp->Canvas->MoveTo(B_x,B_y);       //起點
		bmp->Canvas->LineTo(B_x_2,B_y_2) ;
		B_x = B_x_2;
		B_y = B_y_2;
	}
}
//---------------------------------------------------------------------------

void TForm1::MovePoint(int X,int Y){
	float small_pen = data.pen_size/2;
	if(X >= p_data[1][0] - data.width - small_pen && Y >= p_data[1][1] - data.height - small_pen && X <= p_data[1][0]+data.width-small_pen+1 && Y<= p_data[1][1]+data.height-small_pen+1){
		   //0 第幾條線 1點的狀態 (0重疊線 1 P點 ,2起點3終點 )
			click_data[0] = 1;
			click_data[1] = 2;
			ReDraw(1,2);
			MovePoint_flag = true;
			return;
	}else if(X >= p_data[lines][2] - data.width - small_pen && Y >= p_data[lines][3] - data.height - small_pen && X <= p_data[lines][2]+data.width-small_pen+1 && Y<= p_data[lines][3]+data.height-small_pen+1){
			click_data[0] = lines;
			click_data[1] = 3;
			ReDraw(lines,3);
			MovePoint_flag = true;
			return;
	}else{
		for(int i=lines;i>=0;i--){
			//終點檢查
			if(X >= p_data[i][2] - data.width - small_pen && Y >= p_data[i][3] - data.height - small_pen && X <= p_data[i][2]+data.width-small_pen+1 && Y<= p_data[i][3]+data.height-small_pen+1){
				click_data[0] = i;
				click_data[1] = 0;
				ReDraw(i,0);
				MovePoint_flag = true;
				   //	ShowMessage("重點");
				return;
			//P點檢查
			}else if(X >= p_data[i][4] - data.width - small_pen && Y >= p_data[i][5] - data.height - small_pen && X <= p_data[i][4]+data.width-small_pen+1 && Y<= p_data[i][5]+data.height-small_pen+1){
				click_data[0] = i;
				click_data[1] = 1;
				ReDraw(i,1);
				MovePoint_flag = true;
				return;
			}
		}
	}
		SaveDraw();
		lines ++ ;
		p_data[lines][0] = p_data[lines-1][2];
		p_data[lines][1] = p_data[lines-1][3];
		PointEnd =true;      //結束控制點狀態
		p_data[lines][2] = p_data[lines][4] = X;          //終點座標
		p_data[lines][3] = p_data[lines][5] = Y;          //P點等於終點
		DrawLine(lines);
		for(int i=0;i<6;i+=2)
		DrawPoint(lines,i);
		Image1->Picture->Bitmap = bmp;
		options = 1;
		DrawFlag = true;
		PointEnd = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
		DrawFlag = false;
		if(MovePoint_flag == true){
			SaveDraw();
			MovePoint_flag = false;
		}
		for(int i=0;i<=lines;i++)
		for(int j=0;j<6;j+=2)
		DrawPoint(i,j);
		Image1->Picture->Bitmap = bmp;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(PointEnd == true){  //畫圖模式
		if(Click_flag == false){    //所有的開始
			lines ++ ;
			p_data[lines][0] = X ;
			p_data[lines][1] = Y ;
			p_data[lines][2] = X ;
			p_data[lines][3] = Y ;
			bmp_back->Assign(bmp);        //記錄點陣圖
			bmp_new->Assign(bmp);
			DrawPoint(lines,0);         //顯示控制點
			Image1->Picture->Bitmap = bmp;  //顯示結果
			Click_flag = true; //已設置起點
		}else{             //第二次按下
			p_data[lines][2] = X ;
			p_data[lines][3] = Y ;
			p_data[lines][4] = X ;
			p_data[lines][5] = Y ;
			//X1 = X2 = X;          //終點座標
			//Y1 = Y2 = Y;          //P點等於終點
			bmp->Assign(bmp_back);
			DrawLine(lines);
			for(int i=0;i<6;i+=2)
			DrawPoint(lines,i);
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
		SaveDraw();
		Image1->Picture->Bitmap = bmp;
		lines = 0;
		Click_flag = false;
		DrawFlag = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	ReDraw(2,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	Image1->Picture->Bitmap = bmp_new;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Image1->Picture->Bitmap = bmp_back;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	EndDraw();
}
//---------------------------------------------------------------------------

