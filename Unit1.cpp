//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   //存檔專用
	char buffer[128];
	AnsiString PicName="111.bmp";
	bmp=NULL;
	getcwd(buffer,128);
	AppPath=buffer;
	AppPath+="\\";
	//Label1->Caption=AppPath;
	PicPath=AppPath;

	DrawFlag = false;   //繪圖模式
	PointEnd = true;    //是否已結束移動控制點
	Click_flag = false;
	MovePoint_flag = false; //移動控制點模式
	end_draw = false;//停止新圖模式
	key_flag = false;
	lines = 0;
	PenMode = 1; //移動控制點模式
	bmp      = new Graphics::TBitmap();  //建立一個新的bmp物件
	bmp_back = new Graphics::TBitmap();
	bmp_new = new Graphics::TBitmap();
	bmp->PixelFormat=pf24bit;
	bmp_back->PixelFormat=pf24bit;
	bmp_new->PixelFormat=pf24bit;
	for(int i=0;i<100;i++)
		for(int j=0;j<8;j++){
			p_data[i][j] = NULL;
	}
	line_data.bg_color = clGray;
	stack_data.f_color = clRed;
	Clear();
	bmp_back->Assign(bmp);        //記錄點陣圖
	bmp_new->Assign(bmp);
	//設定控制點
	data.num_point = 3;
	data.width = 2.5;
	data.height= 2.5;
	data.brush_color = clYellow;
	data.pen_color   = clBlack;
	data.pen_size   = 1;

	line_data.pen_color = clBlack;
	line_data.pen_size = 3;

	Panel2->Color =  line_data.pen_color;
	Panel3->Color =  line_data.bg_color;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Save1Click(TObject *Sender)
{
EndDraw();
SaveImage(Image1->Picture->Bitmap,PicPath) ;
}
//---------------------------------------------------------------------------
void TForm1::SaveImage(Graphics::TBitmap *Bmp,AnsiString Path)
{
	SavePictureDialog1->InitialDir = Path;
	SavePictureDialog1->DefaultExt = Path;
	if(SavePictureDialog1->Execute()){
		Bmp->SaveToFile(SavePictureDialog1->FileName);
		ShowMessage("存檔成功");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel2Click(TObject *Sender)
{
	TColor lineColor;
	if(ColorDialog1->Execute()){
		lineColor = ColorDialog1->Color;
		line_data.pen_color = lineColor;
		Panel2->Color = lineColor;
		SaveDraw();
		ShowPoint(0,0);
	}
	Image1->Picture->Bitmap = bmp;  //顯示結果
	Image1->Picture->Bitmap = bmp;  //顯示結果
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel3Click(TObject *Sender)
{
	TColor bgColor;
	if(ColorDialog1->Execute()){
		bgColor = ColorDialog1->Color;
		line_data.bg_color  = bgColor;
		Panel3->Color = bgColor;
		SaveDraw();
		ShowPoint(0,0);
	}
}
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	int tmp_x,tmp_y;
   //	double m1,ata1,m1_x,m1_y,sin1,cos1;

	StatusBar1->Panels->Items[3]->Text = FloatToStr(X);
	StatusBar1->Panels->Items[4]->Text = FloatToStr(Y);
	if(DrawFlag == true){        //畫控制點模式
		if(options == 0){
			p_data[lines][2] = X;
			p_data[lines][3] = Y;
			bmp->Assign(bmp_back);
			DrawLine(lines);
			ShowPoint(1,lines);
			Image1->Picture->Bitmap = bmp;
		}else if(options == 1){
			p_data[lines][6] = X;
			p_data[lines][7] = Y;
			p_data[lines][4] = p_data[lines][2] - (X - p_data[lines][2]) ;
			p_data[lines][5] = p_data[lines][3] - (Y - p_data[lines][3]) ;
			bmp->Assign(bmp_back);
			DrawLine(lines);
			ShowPoint(1,lines);
			Image1->Picture->Bitmap = bmp;
		}
	}
	if(MovePoint_flag == true){      //移動控制點
		//0 第幾條線 1點的狀態 (0重疊線 1 P_1點 ,2起點3終點 5 P_2點)
		tmp_x = X - p_data[click_data[0]][2];
		tmp_y = Y - p_data[click_data[0]][3];

	   /*	m1_x = p_data[click_data[0]][2] - X;  //相對座標長度
		m1_y = p_data[click_data[0]][3] - Y;

		if(m1_x == 0){ //垂直
			StatusBar1->Panels->Items[0]->Text = "垂直";
		}else if(m1_y == 0){  //水平
			StatusBar1->Panels->Items[0]->Text = "水平";
		}else{      //傾斜
			m1 = m1_y /m1_x;      //斜率
			ata1 = atan(m1);      //求弳度
			StatusBar1->Panels->Items[0]->Text = FloatToStr((ata1*180)/3.1415926);
			sin1 = sin(ata1);
			cos1 = cos(ata1);
		}                           */
		if(click_data[1] == 0){
			p_data[click_data[0]][2] = X;
			p_data[click_data[0]][3] = Y;
			p_data[click_data[0]+1][0] = X;
			p_data[click_data[0]+1][1] = Y;
			p_data[click_data[0]][4] += tmp_x;
			p_data[click_data[0]][5] += tmp_y;
			p_data[click_data[0]][6] += tmp_x;
			p_data[click_data[0]][7] += tmp_y;
			bmp->Assign(bmp_back);
			DrawLine_double(click_data[0],click_data[0]+1);
			ShowPoint(1,click_data[0]);
			Image1->Picture->Bitmap = bmp;
		}else if(click_data[1] == 1){
			p_data[click_data[0]][4] = X;
			p_data[click_data[0]][5] = Y;

		   //	p_data[click_data[0]][6] = len1*cos1;
		   //	p_data[click_data[0]][7] = len1*sin1;
			bmp->Assign(bmp_back);
			DrawLine(click_data[0]);
			if(click_data[0]!=lines)
			DrawLine(click_data[0]+1);
			ShowPoint(1,click_data[0]);
			Image1->Picture->Bitmap = bmp;
		}else if(click_data[1] == 2){
			p_data[click_data[0]][0] = X;
			p_data[click_data[0]][1] = Y;
			bmp->Assign(bmp_back);
			DrawLine(click_data[0]);
			ShowPoint(2,click_data[0]);   //起點2
			Image1->Picture->Bitmap = bmp;
		}else if(click_data[1] == 3){
			p_data[click_data[0]][2] = X;
			p_data[click_data[0]][3] = Y;
			p_data[click_data[0]][4] += tmp_x;
			p_data[click_data[0]][5] += tmp_y;
			p_data[click_data[0]][6] += tmp_x;
			p_data[click_data[0]][7] += tmp_y;
			bmp->Assign(bmp_back);
			DrawLine(click_data[0]);
			ShowPoint(3,click_data[0]); //終點3
			Image1->Picture->Bitmap = bmp;
		}else if(click_data[1] == 4){         //前後連結點
			p_data[click_data[0]][2] = X;
			p_data[click_data[0]][3] = Y;
			p_data[click_data[0]][4] += tmp_x;
			p_data[click_data[0]][5] += tmp_y;
			p_data[click_data[0]][6] += tmp_x;
			p_data[click_data[0]][7] += tmp_y;
			p_data[1][0] = X;
			p_data[1][1] = Y;
			bmp->Assign(bmp_back);
			DrawLine_double(click_data[0],1);
			ShowPoint(4,click_data[0]); //相接4
			Image1->Picture->Bitmap = bmp;
		}else if(click_data[1] == 5){
			p_data[click_data[0]][6] = X;
			p_data[click_data[0]][7] = Y;
			if(Sync_flag == false){
				len1 = sqrt( (p_data[click_data[0]][4] - p_data[click_data[0]][2])*(p_data[click_data[0]][4] - p_data[click_data[0]][2]) + (p_data[click_data[0]][5] - p_data[click_data[0]][3])*(p_data[click_data[0]][5] - p_data[click_data[0]][3])           );
                Sync_flag = true;
			}
			StatusBar1->Panels->Items[1]->Text = FloatToStr(len1);
			//p_data[click_data[0]][4] = len1 * cos1;
			//p_data[click_data[0]][5] = len1 * sin1;
			bmp->Assign(bmp_back);
			DrawLine(click_data[0]);
			if(click_data[0]!=lines){
				DrawLine(click_data[0]+1);
			}
			ShowPoint(1,click_data[0]);
			Image1->Picture->Bitmap = bmp;
		}
	}
}
//---------------------------------------------------------------------------
void TForm1::ShowPoint(int mode,int line){
	if(mode == 0 && line == 0){      //全顯示模式
		if(!(Click_flag == true && PointEnd == true)){
			if(PenMode == 1){
				SaveDraw();
				for(int i=1;i<=lines;i++) //顯示P點
				for(int j=6;j>=0;j-=2)
						DrawPoint(i,j);
					   //	Image1->Picture->Bitmap = bmp;
			}else if(PenMode == 2){
				SaveDraw();
				for(int i=1;i<=lines;i++) //不顯示P點
					for(int j=2;j>=0;j-=2)
						DrawPoint(i,j);
					   //	Image1->Picture->Bitmap = bmp;
			}else if(PenMode == 0){    //不顯示點
				SaveDraw();
				Image1->Picture->Bitmap = bmp;
			}else if(PenMode == 3){
				SaveDraw();
				for(int i=1;i<=lines;i++) //顯示P點
					for(int j=6;j>=0;j-=2)
						DrawPoint(i,j);
			   //	Image1->Picture->Bitmap = bmp;
			}
		}else if(Click_flag == false && DrawFlag == true && PointEnd == false){
			SaveDraw();
			DrawPoint(lines,0);
		}else{            //顯示一個點
			DrawPoint(1,0);
		  //	Image1->Picture->Bitmap = bmp;
		}
	}else if(mode == 1){   //重點
		DrawPoint(line-1,6);
		DrawPoint(line,6);
		DrawPoint(line,4);
		DrawPoint(line+1,4);
		for (int i = 0; i < 2; i++)
			for(int j=0;j<4;j+=2)
			DrawPoint(line+i,j);
	}else if(mode == 2){  //起點
		for(int i=0;i<6;i+=2)
		DrawPoint(line,i);
	}else if(mode == 3){  //終點
		for(int i=0;i<8;i+=2)
		DrawPoint(line,i);
			DrawPoint(line-1,6);
	}else if(mode == 4){  //前後相接
		DrawPoint(line-1,6);
		DrawPoint(line,6);
		DrawPoint(line,4);
		DrawPoint(1,4);
		for (int i = 0; i < 2; i++)
			for(int j=0;j<4;j+=2)
			DrawPoint(1,j);
	}
}
//---------------------------------------------------------------------------
void TForm1::EndDraw(){
	if(!(lines == 0)){
		SaveDraw();
		bmp_new->Assign(bmp);
		Image1->Picture->Bitmap = bmp;
		lines = 0;
		PointEnd =true;      //結束控制點狀態
		Click_flag = false;
		DrawFlag = false;
		end_draw = false;
		for(int i=0;i<100;i++)
			for(int j=0;j<8;j++){
			p_data[i][j] = NULL;
		}
		N14->Enabled = false;
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
			if(i !=line && i !=line+1){
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
	}else if(mode == 4){          //終點
		for(int i=2;i<lines;i++){
			DrawLine(i);
		}
		bmp_back->Assign(bmp);   //儲檔
	}else if(mode == 5){   //p點
		for(int i=1;i<=lines;i++){
			if(i !=line && i !=line+1){
				DrawLine(i);
			}
			bmp_back->Assign(bmp);   //儲檔
		}
	}
}
//---------------------------------------------------------------------------
void TForm1::SaveDraw(){
	if(!(Click_flag == true && PointEnd == true)){
		bmp->Assign(bmp_new);//清空
		for(int i=1;i<=lines;i++)
		{
			DrawLine(i);
		}
		bmp_back->Assign(bmp);//存圖
	}else{        //只有點的狀態
		bmp->Assign(bmp_new);//清空
		bmp_back->Assign(bmp);//存圖
	}
}
//---------------------------------------------------------------------------
void TForm1::DrawPoint(int line,int i){
	if(p_data[line][i] == NULL || p_data[line][i+1] == NULL)
	return;
	float small_pen = data.pen_size/2;
	bmp->Canvas->Brush->Color = data.brush_color;
	if(i<4){    //繪製黃點
		bmp->Canvas->Pen->Style = psSolid ; //psDot ;
		bmp->Canvas->Pen->Width=data.pen_size;
		bmp->Canvas->Pen->Color = data.pen_color;         //邊框的顏色
		bmp->Canvas->Rectangle( TRect(p_data[line][i] - data.width, p_data[line][i+1] - data.height ,p_data[line][i]+data.width-small_pen+1,p_data[line][i+1]+data.height-small_pen+1)); // 畫一下顏色表示已經在Form上
	}else if(i == 4){
		if(!(p_data[line][4] == p_data[line][2] && p_data[line][5] == p_data[line][3])){ // P點與終點相同
		bmp->Canvas->Pen->Style = psDot ; //psDot ;
			bmp->Canvas->Brush->Color = clWhite;
			bmp->Canvas->Pen->Color = clGray;              //繪製虛線
			bmp->Canvas->Pen->Width = 1;
			bmp->Canvas->MoveTo(p_data[line][i],p_data[line][i+1]) ;       //起點
			bmp->Canvas->LineTo(p_data[line][i-2],p_data[line][i-1]) ;
			if(Revers_flag == true){
				int n = i+2;
				bmp->Canvas->MoveTo(p_data[line][n],p_data[line][n+1]) ;       //起點
				bmp->Canvas->LineTo(p_data[line][i-2],p_data[line][i-1]) ;
				bmp->Canvas->Brush->Color = clRed;
				bmp->Canvas->Pen->Style = psSolid ; //psDot ;
				bmp->Canvas->Pen->Width=data.pen_size;
				bmp->Canvas->Pen->Color = data.pen_color;         //邊框的顏色
				bmp->Canvas->Rectangle( TRect(p_data[line][n] - data.width, p_data[line][n+1] - data.height ,p_data[line][n]+data.width-small_pen+1,p_data[line][n+1]+data.height-small_pen+1)); // 畫一下顏色表示已經在Form上
			}																	//繪製紅點
			bmp->Canvas->Brush->Color = clRed;
			bmp->Canvas->Pen->Style = psSolid ; //psDot ;
			bmp->Canvas->Pen->Width=data.pen_size;
			bmp->Canvas->Pen->Color = data.pen_color;         //邊框的顏色
			bmp->Canvas->Rectangle( TRect(p_data[line][i] - data.width, p_data[line][i+1] - data.height ,p_data[line][i]+data.width-small_pen+1,p_data[line][i+1]+data.height-small_pen+1)); // 畫一下顏色表示已經在Form上
		}
	}else if(i == 6){
		if(!(p_data[line][6] == p_data[line][2] && p_data[line][7] == p_data[line][3])){ // P點與終點相同
			bmp->Canvas->Pen->Style = psDot ; //psDot ;
			bmp->Canvas->Pen->Width = 1;
			bmp->Canvas->Brush->Color = clWhite;                //繪製虛線
			bmp->Canvas->Pen->Color = clGray;
			bmp->Canvas->MoveTo(p_data[line][i-4],p_data[line][i-3]) ;       //起點
			bmp->Canvas->LineTo(p_data[line][i],p_data[line][i+1]) ;																//繪製紅點
			bmp->Canvas->Brush->Color = clRed;
			bmp->Canvas->Pen->Style = psSolid ; //psDot ;
			bmp->Canvas->Pen->Width=data.pen_size;
			bmp->Canvas->Pen->Color = data.pen_color;         //邊框的顏色
			bmp->Canvas->Rectangle( TRect(p_data[line][i] - data.width, p_data[line][i+1] - data.height ,p_data[line][i]+data.width-small_pen+1,p_data[line][i+1]+data.height-small_pen+1)); // 畫一下顏色表示已經在Form上		}
		}
	}
}
//---------------------------------------------------------------------------

void TForm1::DrawLine_double(int line_1,int line_2){
	bmp->Canvas->Pen->Width=line_data.pen_size;
	bmp->Canvas->Pen->Color =line_data.pen_color;
	float B_x_1,B_y_1,P1_x_1,P1_y_1,B_x_2,B_y_2,P1_x_2,P1_y_2,P2_x_1,P2_y_1,P2_x_2,P2_y_2,Bx_1,By_1,Bx_2,By_2,range;
	P1_x_1 = p_data[line_1][4];
	P1_y_1 = p_data[line_1][5];
	P1_x_2 = p_data[line_2][4];
	P1_y_2 = p_data[line_2][5];
	P2_x_1 = p_data[line_1][4];
	P2_y_1 = p_data[line_1][5];
	P2_x_2 = p_data[line_2][4];
	P2_y_2 = p_data[line_2][5];
	if(line_1 != 1){
		P1_x_1 = p_data[line_1-1][6];
		P1_y_1 = p_data[line_1-1][7];
	}
	if(line_2 != 1){
		P1_x_2 = p_data[line_2-1][6];
		P1_y_2 = p_data[line_2-1][7];
	}
	Bx_1 = p_data[line_1][0];
	By_1 = p_data[line_1][1];
	Bx_2 = p_data[line_2][0];
	By_2 = p_data[line_2][1];
	range = 0.01;
	for(float t=range;t<=1;t+=range){
		B_x_1 = p_data[line_1][0] *((1-t) * (1-t) * (1-t))+ 3*P1_x_1 *t*((1-t)*(1-t))+ 3*P2_x_1*(t*t)*(1-t)+p_data[line_1][2]*(t*t*t);
		B_y_1 = p_data[line_1][1] *((1-t) * (1-t) * (1-t))+ 3*P1_y_1 *t*((1-t)*(1-t))+ 3*P2_y_1*(t*t)*(1-t)+p_data[line_1][3]*(t*t*t);
		B_x_2 = p_data[line_2][0] *((1-t) * (1-t) * (1-t))+ 3*P1_x_2 *t*((1-t)*(1-t))+ 3*P2_x_2*(t*t)*(1-t)+p_data[line_2][2]*(t*t*t);
		B_y_2 = p_data[line_2][1] *((1-t) * (1-t) * (1-t))+ 3*P1_y_2 *t*((1-t)*(1-t))+ 3*P2_y_2*(t*t)*(1-t)+p_data[line_2][3]*(t*t*t);

		bmp->Canvas->MoveTo(Bx_1,By_1) ;       //起點
		bmp->Canvas->LineTo(B_x_1,B_y_1) ;
		bmp->Canvas->MoveTo(Bx_2,By_2) ;       //起點
		bmp->Canvas->LineTo(B_x_2,B_y_2) ;         //目前的點
		Bx_1 = B_x_1;
		By_1 = B_y_1;
		Bx_2 = B_x_2;
		By_2 = B_y_2;
	}
}
//---------------------------------------------------------------------------

void TForm1::DrawLine(int line){
	bmp->Canvas->Pen->Width=line_data.pen_size;
	bmp->Canvas->Pen->Color =line_data.pen_color;
	float B_x,B_y,P1_x,P1_y,P2_x,P2_y,B_x_2,B_y_2,range;
	P2_x = p_data[line][4];
	P2_y = p_data[line][5];
	P1_x = p_data[line][4];
	P1_y = p_data[line][5];
	if(line != 1){
		P1_x = p_data[line-1][6];
		P1_y = p_data[line-1][7];
	}
	B_x = p_data[line][0];
	B_y = p_data[line][1];
	range = 0.01;
	for(float t=range;t<=1;t+=range){
	   B_x_2 = p_data[line][0] *((1-t) * (1-t) * (1-t))+ 3*P1_x *t*((1-t)*(1-t))+ 3*P2_x*(t*t)*(1-t)+p_data[line][2]*(t*t*t);
	   B_y_2 = p_data[line][1] *((1-t) * (1-t) * (1-t))+ 3*P1_y *t*((1-t)*(1-t))+ 3*P2_y*(t*t)*(1-t)+p_data[line][3]*(t*t*t);
		bmp->Canvas->MoveTo(B_x,B_y);       //起點
		bmp->Canvas->LineTo(B_x_2,B_y_2) ;
		B_x = B_x_2;
		B_y = B_y_2;
	}
}
//---------------------------------------------------------------------------

void TForm1::SelPoint(int X,int Y){
	Sync_flag = false;
	Revers_flag = false;
	if(lines >= 99){
		ShowMessage("你畫的線太多了，請先完成目前的繪圖");
		return;
	}
	float small_pen = data.pen_size/2;
	if(X >= p_data[1][0] - data.width - small_pen && Y >= p_data[1][1] - data.height - small_pen && X <= p_data[1][0]+data.width-small_pen+1 && Y<= p_data[1][1]+data.height-small_pen+1){
		if(PenMode == 1){    //頭尾切線模式
		   //0 第幾條線 1點的狀態 (0重疊線 1 P點 ,2起點3終點 4起點和終點)
			if(end_draw == false){  //起點接終點
				Revers_flag = true;;
				SaveDraw();
				lines ++ ;
				p_data[lines][0] = p_data[lines-1][2];
				p_data[lines][1] = p_data[lines-1][3];
				p_data[lines][2] = p_data[lines][4] = p_data[1][0];          //終點座標
				p_data[lines][3] = p_data[lines][5] = p_data[1][1];          //P點等於終點
				p_data[lines][6] = p_data[1][0];
				p_data[lines][7] = p_data[1][1];
				DrawLine(lines);
				ShowPoint(4,lines);
					Image1->Picture->Bitmap = bmp;
					DrawFlag = true;
					PointEnd = false;
					end_draw = true;
			}else{
					click_data[0] = lines;
					click_data[1] = 4;
					ReDraw(lines,4);
					MovePoint_flag = true;
			}
		}else if(PenMode == 2){   //刪除錨點模式
			if(lines == 1){
				if(Click_flag == true && PointEnd == true){
					EndDraw();
				}else{
					p_data[1][0] = p_data[1][2];
					p_data[1][1] = p_data[1][3];
					Click_flag = true; //已設置起點
					PointEnd = true;
				}
			}else{
				if(end_draw == true){
					if(end_draw == true && lines <=2){  //共接點
						lines --;
						Click_flag = true; //已設置起點
						PointEnd = true;
						end_draw = false;
						 p_data[1][0] = p_data[2][0];
						 p_data[1][1] = p_data[2][1];
					}else{
						p_data[lines][2] = p_data[1][2];
						p_data[lines][3] = p_data[1][3];
						p_data[lines][4] = p_data[1][4];
						p_data[lines][5] = p_data[1][5];
						p_data[lines][6] = p_data[1][6];
						p_data[lines][7] = p_data[1][7];
						for(int j=1;j<lines;j++){
							for(int x = 0;x<8;x++)
							p_data[j][x] = p_data[j+1][x];
						}
						 p_data[1][0] = p_data[lines][2];
						 p_data[1][1] = p_data[lines][3];
						for(int j=0;j<8;j++)     //清除資料
						p_data[lines][j] = NULL;
						lines --;
					}
				}else{
					for(int j=0;j<lines;j++){
						for(int x = 0;x<8;x++)
							p_data[j][x] = p_data[j+1][x];
						}
					lines --;
				}
			 }
		}else if(PenMode == 3){  //起點移動
			if(end_draw == false){
				ReDraw(1,2);
				click_data[0] = 1;
				click_data[1] = 2;
				MovePoint_flag = true;
            }else{
				click_data[0] = lines;
				click_data[1] = 4;
				ReDraw(lines,4);
				MovePoint_flag = true;
			}
		}
		return;
	}else if(X >= p_data[lines][2] - data.width - small_pen && Y >= p_data[lines][3] - data.height - small_pen && X <= p_data[lines][2]+data.width-small_pen+1 && Y<= p_data[lines][3]+data.height-small_pen+1){
		click_data[0] = lines;
		click_data[1] = 3;
		if(PenMode == 3){    //終點移動
			ReDraw(lines,3);
			MovePoint_flag = true;
		}else if(PenMode == 1){
			p_data[lines][6] = p_data[lines][2];
			p_data[lines][7] = p_data[lines][3];
			bmp->Assign(bmp_back);
			DrawLine(lines);
			ShowPoint(0,0);
			Image1->Picture->Bitmap = bmp;
		}else if(PenMode == 2){     //終點刪除
			if (lines>1) {
				for(int j=0;j<8;j++)     //清除資料
				p_data[lines][j] = NULL;
				lines --;
				if(end_draw == true){
					end_draw = false;
				 }
				for(int i=1;i<=lines;i++)
					ShowPoint(3,lines);
			}else{
				Click_flag = true; //已設置起點
				PointEnd = true;
			}
		}
		return;
	}else{
		for(int i=lines;i>=0;i--){
			//終點檢查   重點
			if(X >= p_data[i][2] - data.width - small_pen && Y >= p_data[i][3] - data.height - small_pen && X <= p_data[i][2]+data.width-small_pen+1 && Y<= p_data[i][3]+data.height-small_pen+1){
				click_data[0] = i;
				click_data[1] = 0;
				if(PenMode == 1 || PenMode == 3){    //重點移動
					ReDraw(i,0);
					MovePoint_flag = true;
				}else if(PenMode == 2){        //終點刪除
					if(end_draw == true && lines <=2){  //共接點
						for(int j=0;j<8;j++)
						p_data[lines][j] = NULL;
						lines --;
						Click_flag = true; //已設置起點
						PointEnd = true;
						end_draw = false;
					}else{
						p_data[i][2] = p_data[i+1][2];
						p_data[i][3] = p_data[i+1][3];
						p_data[i][4] = p_data[i+1][4];
						p_data[i][5] = p_data[i+1][5];
						p_data[i][6] = p_data[i+1][6];
						p_data[i][7] = p_data[i+1][7];
						for(int j=i;j<lines;j++){
							for(int x = 0;x<8;x++){
								p_data[j+1][x] = p_data[j+2][x];
							}
						}
						 p_data[i+1][0] = p_data[i][2];
						 p_data[i+1][1] = p_data[i][3];
						lines --;
					}
				}
				return;
			//P點檢查
			}else if(X >= p_data[i][4] - data.width - small_pen && Y >= p_data[i][5] - data.height - small_pen && X <= p_data[i][4]+data.width-small_pen+1 && Y<= p_data[i][5]+data.height-small_pen+1){
				if(PenMode == 1 || PenMode == 3){  //P點移動
					click_data[0] = i;
					click_data[1] = 1;
					ReDraw(i,1);
					MovePoint_flag = true;
				}
				return;
			}else if(X >= p_data[i][6] - data.width - small_pen && Y >= p_data[i][7] - data.height - small_pen && X <= p_data[i][6]+data.width-small_pen+1 && Y<= p_data[i][7]+data.height-small_pen+1){
				if(PenMode == 1 || PenMode == 3){  //P點移動
					click_data[0] = i;
					click_data[1] = 5;
					ReDraw(i,5);
					MovePoint_flag = true;
				}
				return;
			}
		}
	}
	Revers_flag = true;
	if(PenMode == 1 || PenMode == 2){   //增加線段
		LinkPoint(X,Y);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Revers_flag = false;
	if(Button==mbLeft){
		if(PenMode == 0 || PenMode == 1 || PenMode == 2 || PenMode == 3){
			DrawFlag = false;
			if(MovePoint_flag == true){
				SaveDraw();
				MovePoint_flag = false;
			}
			ShowPoint(0,0);
			Image1->Picture->Bitmap = bmp;
		}else if(PenMode == 4){
			bmp_new->Assign(bmp);
			Image1->Picture->Bitmap = bmp;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(Button==mbLeft){
		Revers_flag = true;
		if(PointEnd == true && (PenMode == 0 || PenMode == 1 || PenMode == 2)){  //畫圖模式
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
				float small_pen = data.pen_size/2;
				if(X >= p_data[1][0] - data.width - small_pen && Y >= p_data[1][1] - data.height - small_pen && X <= p_data[1][0]+data.width-small_pen+1 && Y<= p_data[1][1]+data.height-small_pen+1){
				   if(PenMode == 2){
						EndDraw();
					return;
			   }
			}
				N14->Enabled = true;
				p_data[lines][2] = X ;
				p_data[lines][3] = Y ;
				p_data[lines][4] = p_data[lines][2] - (X - p_data[lines][2]) ;
				p_data[lines][5] = p_data[lines][3] - (Y - p_data[lines][3]) ;
				p_data[lines][6] = X;
				p_data[lines][7] = Y;
				bmp->Assign(bmp_back);
				DrawLine(lines);
				options = 1;
				DrawFlag = true;
				PointEnd = false;
				ShowPoint(3,lines);
				Image1->Picture->Bitmap = bmp;
			}
		}else if(PenMode == 4){
			if(CheckBox1->Checked == true){
				unsigned int Time1 = GetTickCount();
				FloodFill(bmp,bmp,stack_data.f_color,X,Y);
				unsigned int Time2 = GetTickCount();
				ShowMessage(Time2 - Time1);
			}else{
				FloodFill(bmp,bmp,stack_data.f_color,X,Y);
			}
		}else{                  //控制點模式
			if(PenMode == 1 || PenMode ==2 || PenMode ==3){
				SelPoint(X,Y);
			}else if(PenMode == 0){
				LinkPoint(X,Y);
			}
		}
	}else if(Button==mbRight && (PenMode == 0 || PenMode == 1 || PenMode == 2)){
		N14Click(Sender);
	}
}
//---------------------------------------------------------------------------
void TForm1::LinkPoint(int X,int Y){
		SaveDraw();
		if(end_draw == false && lines >=1){
			lines ++ ;
			p_data[lines][0] = p_data[lines-1][2];
			p_data[lines][1] = p_data[lines-1][3];
			PointEnd =true;      //結束控制點狀態
			p_data[lines][2] = X;     //終點座標
			p_data[lines][3] = Y;
			p_data[lines][4] = p_data[lines][2] - (X - p_data[lines][2]) ;
			p_data[lines][5] = p_data[lines][3] - (Y - p_data[lines][3]) ;
			p_data[lines][6] = X;      //P點等於終點
			p_data[lines][7] = Y;
			DrawLine(lines);
			options = 1;
			DrawFlag = true;
			PointEnd = false;
			ShowPoint(3,lines);
			Image1->Picture->Bitmap = bmp;
		}
}
//---------------------------------------------------------------------------
void TForm1::Clear(){
	EndDraw();
	bmp->Height= Image1->Height;
	bmp->Width = Image1->Width;
	bmp->Canvas->Brush->Color = line_data.bg_color;     //填滿的顏色
	bmp->Canvas->Pen->Color = clBlack;         //邊框的顏色
	bmp->Canvas->Pen->Width=0;
	bmp->Canvas->Rectangle( TRect(0, 0,Image1->Width,Image1->Height));
	//bmp->LoadFromFile("mlp.bmp");
	bmp_back->Assign(bmp);
	bmp_new->Assign(bmp);
	Image1->Picture->Bitmap = bmp;
}
void __fastcall TForm1::FormShortCut(TWMKey &Msg, bool &Handled)
{
	if(Msg.CharCode ==  13){
	 if(key_flag == false){
		key_flag =true;
	 }else{
		key_flag =false;
		EndDraw();
	 }
	}
	if(Msg.CharCode ==  27){
	 if(key_flag == false){
		key_flag =true;
	 }else{
		key_flag =false;
		if(!(lines == 0)){
		for(int i=0;i<100;i++)
			for(int j=0;j<8;j++)
				p_data[i][j] = NULL;
		SaveDraw();
		bmp_new->Assign(bmp);
		Image1->Picture->Bitmap = bmp;
		lines = 0;
		PointEnd =true;      //結束控制點狀態
		Click_flag = false;
		DrawFlag = false;
		end_draw = false;
		N14->Enabled = false;
		}

	 }
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	ReDraw(2,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
	Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
	EndDraw();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N4Click(TObject *Sender)
{
line_data.pen_size = 5;
ShowPoint(0,0);
  Image1->Picture->Bitmap = bmp;  //顯示結果
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
line_data.pen_size = 3;
ShowPoint(0,0);
  Image1->Picture->Bitmap = bmp;  //顯示結果
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
line_data.pen_size = 1.5;
ShowPoint(0,0);
  Image1->Picture->Bitmap = bmp;  //顯示結果
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N8Click(TObject *Sender)
{
line_data.pen_color = clBlack;
Panel2->Color =  line_data.pen_color;
ShowPoint(0,0);
  Image1->Picture->Bitmap = bmp;  //顯示結果
	Image1->Picture->Bitmap = bmp;  //顯示結果
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N9Click(TObject *Sender)
{
line_data.pen_color = clRed;
Panel2->Color =  line_data.pen_color;
SaveDraw();
ShowPoint(0,0);
Image1->Picture->Bitmap = bmp;  //顯示結果
  Image1->Picture->Bitmap = bmp;  //顯示結果
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N10Click(TObject *Sender)
{
line_data.pen_color = clBlue;
Panel2->Color =  line_data.pen_color;
SaveDraw();
ShowPoint(0,0);
  Image1->Picture->Bitmap = bmp;  //顯示結果
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N12Click(TObject *Sender)
{
  Close();   //關閉程式
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N14Click(TObject *Sender)
{
if(!(lines <= 1 || PointEnd == true)){

	for(int i=0;i<8;i++)
	  p_data[lines][i] = NULL;
  lines --;
  if(end_draw == true){
	end_draw = false;
  }
  ShowPoint(0,0);
  Image1->Picture->Bitmap = bmp;  //顯示結果
  }else if(lines == 1){
			bmp_back->Assign(bmp_new);        //記錄點陣圖
			bmp->Assign(bmp_new);
			DrawPoint(1,0);         //顯示控制點
			Image1->Picture->Bitmap = bmp;  //顯示結果
			Click_flag = true; //已設置起點
			PointEnd = true;
		N14->Enabled = false;
  }else{
	  ShowMessage("無法還原");
  }
}
//---------------------------------------------------------------------------
 //放棄目前繪圖

void __fastcall TForm1::N15Click(TObject *Sender)
{
	if(!(lines == 0)){
		for(int i=0;i<100;i++)
			for(int j=0;j<8;j++)
				p_data[i][j] = NULL;
		SaveDraw();
		bmp_new->Assign(bmp);
		Image1->Picture->Bitmap = bmp;
		lines = 0;
		PointEnd =true;      //結束控制點狀態
		Click_flag = false;
		DrawFlag = false;
		end_draw = false;
		N14->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	PenMode = 0;
	ShowPoint(0,0);
	Image1->Picture->Bitmap = bmp;
	SpeedButton1->Down = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
	PenMode = 1;
	ShowPoint(0,0);
	Image1->Picture->Bitmap = bmp;
	SpeedButton2->Down = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
	PenMode = 2;
	ShowPoint(0,0);
	Image1->Picture->Bitmap = bmp;
	SpeedButton3->Down = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
	PenMode = 3;
	ShowPoint(0,0);
	Image1->Picture->Bitmap = bmp;
	SpeedButton6->Down = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N21Click(TObject *Sender)
{
	Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N22Click(TObject *Sender)
{
	Form3->ShowModal();
}

//---------------------------------------------------------------------------
void TForm1::GetRGB(Graphics::TBitmap *Bmp, int X, int Y, int *r, int *g, int *b)
{
  Byte *ptr;
  int col;

  col=X*3;

  ptr=(Byte *)Bmp->ScanLine[Y];

  *r=ptr[col+2];
  *g=ptr[col+1];
  *b=ptr[col];


}

void TForm1::FloodFill(Graphics::TBitmap *Source, Graphics::TBitmap *Target,TColor PColor,int Px,int Py)
{
  Byte *tptr;
  int width, height;
  int R,G,B,Pr,Pg,Pb,col;
  GetRGB(Source,Px,Py,&R,&G,&B);//得到目前的RGB
  Pr = GetRValue(PColor);  //將要填的色存起來
  Pg = GetGValue(PColor);
  Pb = GetBValue(PColor);
  if(Pr == R && Pg == G && Pb == B)   //相同顏色不填
  return;
  width =Source->Width;
  height=Source->Height; //避免超出範圍
  stack_data.width = width;
  stack_data.height = height;
  stack_data.Target = Target;
  stack_data.cR = R;
  stack_data.cG = G;
  stack_data.cB = B;
  stack_data.pR = Pr;
  stack_data.pG = Pg;
  stack_data.pB = Pb;
  if(RadioButton1->Checked == true)
	FloodFill_stack(Px,Py);
  else if(RadioButton2->Checked == true)
	FloodFill_queue_plus(Px,Py);
}
//---------------------------------------------------------------------------
void TForm1::FloodFill_stack(int Inx,int Iny){
	int col;
	Byte *tptr,*oR,*oG,*oB;
	//在範圍內
	if(Inx<0 ||Inx>=stack_data.width || Iny<0 || Iny>=stack_data.height)
		return;
  //Image1->Picture->Bitmap = bmp;
  //Delay(0);
	col=(Inx<<1)+Inx;
	tptr=(Byte *)stack_data.Target->ScanLine[Iny];
	oR = &tptr[col+2];  //暫存RGB
	oG = &tptr[col+1];
	oB = &tptr[col];
	if(*oR != stack_data.cR || *oG != stack_data.cG || *oB != stack_data.cB)
		return;
	*oR = stack_data.pR;
	*oG = stack_data.pG;
	*oB = stack_data.pB;
	FloodFill_stack(Inx-1,Iny);
	FloodFill_stack(Inx,Iny-1);
	FloodFill_stack(Inx+1,Iny);
	FloodFill_stack(Inx,Iny+1);
}
//---------------------------------------------------------------------------
void TForm1::FloodFill_queue(int Inx,int Iny){
	int q[10000000][2],nx,ny,index;
	int col;
	Byte *tptr,*oR,*oG,*oB;
	q[0][0] = Inx;
	q[0][1] = Iny;
	index = 1;
	do{
		index --;
		nx = q[index][0];
		ny = q[index][1];
		if(nx<0 ||nx>=stack_data.width || ny<0 || ny>=stack_data.height)
			continue;
		col=(nx<<1)+nx;
		tptr=(Byte *)stack_data.Target->ScanLine[ny];
		oR = &tptr[col+2];  //暫存RGB
		oG = &tptr[col+1];
		oB = &tptr[col];
		if(*oR != stack_data.cR || *oG != stack_data.cG || *oB != stack_data.cB)
			continue;
		*oR = stack_data.pR;
		*oG = stack_data.pG;
		*oB = stack_data.pB;
		q[index][0] = nx-1;
		q[index][1] = ny;
		index ++;
		q[index][0] = nx+1;
		q[index][1] = ny;
		index ++;
		q[index][0] = nx;
		q[index][1] = ny-1;
		index ++;
		q[index][0] = nx;
		q[index][1] = ny+1;
		index ++;
	}while(index>0);
}
//---------------------------------------------------------------------------
void TForm1::FloodFill_queue_plus(int Inx,int Iny){
	int **q,num_t,nx,ny,index,col;
	Byte *tptr,*oR,*oG,*oB;
	num_t = stack_data.width * stack_data.height*3 ;
	q = new int*[num_t];
	for(int i=0; i<num_t; i++)
		q[i] = new int[3];
	q[0][0] = Inx;
	q[0][1] = Iny;
	q[0][2] = 4;
	index = 1;
	do{
		index --;
		nx = q[index][0];
		ny = q[index][1];
		if(nx<0 ||nx>=stack_data.width || ny<0 || ny>=stack_data.height)
			continue;
		col=(nx<<1)+nx;
		tptr=(Byte *)stack_data.Target->ScanLine[ny];
		oR = &tptr[col+2];  //暫存RGB
		oG = &tptr[col+1];
		oB = &tptr[col];
		if(*oR != stack_data.cR || *oG != stack_data.cG || *oB != stack_data.cB)
			continue;
		*oR = stack_data.pR;
		*oG = stack_data.pG;
		*oB = stack_data.pB;
		switch(q[index][2]){
			case 0:
				q[index][0] = nx-1;
				q[index][1] = ny;
				q[index][2] = 0;
				index ++;
				q[index][0] = nx;
				q[index][1] = ny-1;
				q[index][2] = 2;
				index ++;
				q[index][0] = nx;
				q[index][1] = ny+1;
				q[index][2] = 3;
			break;
			case 1:
				q[index][0] = nx+1;
				q[index][1] = ny;
				q[index][2] = 1;
				index ++;
				q[index][0] = nx;
				q[index][1] = ny-1;
				q[index][2] = 2;
				index ++;
				q[index][0] = nx;
				q[index][1] = ny+1;
				q[index][2] = 3;
			break;
			case 2:
				q[index][0] = nx-1;
				q[index][1] = ny;
				q[index][2] = 0;
				index ++;
				q[index][0] = nx+1;
				q[index][1] = ny;
				q[index][2] = 1;
				index ++;
				q[index][0] = nx;
				q[index][1] = ny-1;
				q[index][2] = 2;
			break;
			case 3:
				q[index][0] = nx-1;
				q[index][1] = ny;
				q[index][2] = 0;
				index ++;
				q[index][0] = nx+1;
				q[index][1] = ny;
				q[index][2] = 1;
				index ++;
				q[index][0] = nx;
				q[index][1] = ny+1;
				q[index][2] = 3;
			break;
			default:
				q[index][0] = nx-1;
				q[index][1] = ny;
				q[index][2] = 0;
				index ++;
				q[index][0] = nx+1;
				q[index][1] = ny;
				q[index][2] = 1;
				index ++;
				q[index][0] = nx;
				q[index][1] = ny-1;
				q[index][2] = 2;
				index ++;
				q[index][0] = nx;
				q[index][1] = ny+1;
				q[index][2] = 3;
		}

		index ++;
	}while(index>0);
		for(int i=num_t-1;i>=0;i--)
		  delete q[i];
		delete q;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
	PenMode = 4;
	SpeedButton7->Down = true;
	EndDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel4Click(TObject *Sender)
{
	TColor f_color;
	if(ColorDialog1->Execute()){
		f_color = ColorDialog1->Color;
		stack_data.f_color = f_color;
		Panel4->Color = f_color;
	}
}
void __fastcall TForm1::SpeedButton7MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if(Panel5->Visible == true)
		Panel5->Visible = false;
	else if(Shift.Contains(ssCtrl)){
		if(Panel5->Visible == false)
			Panel5->Visible = true;
	}
}
//---------------------------------------------------------------------------





