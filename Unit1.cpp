//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool DrawFlag,PointEnd,Click_flag,MovePoint_flag,end_draw,key_flag;
//畫圖模式               第二次點  移動控制點模式
unsigned int options,PenMode;
//0起點 1終點 2 P點   0檢示模式  1移動控制點模式  2刪除控制點模式
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
	for(int i=0;i<100;i++)
		for(int j=0;j<6;j++){
			p_data[i][j] = NULL;
	}
	line_data.bg_color = clGray;
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
		ShowPoint();
	}
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
		ShowPoint();
	}
}
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(DrawFlag == true){        //畫控制點模式
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
			DrawLine_double(click_data[0],click_data[0]+1);
			for (int i = 0; i < 2; i++)
				for(int j=0;j<6;j+=2)
				DrawPoint(click_data[0]+i,j);
			Image1->Picture->Bitmap = bmp;
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
		}else if(click_data[1] == 4){
			p_data[click_data[0]][2] = X;
			p_data[click_data[0]][3] = Y;
			p_data[1][0] = X;
			p_data[1][1] = Y;
			bmp->Assign(bmp_back);
			DrawLine_double(click_data[0],1);
			for (int i = 0; i < 2; i++)
				for(int j=0;j<6;j+=2)
				DrawPoint(click_data[0]+i,j);
			Image1->Picture->Bitmap = bmp;
		}
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
			for(int j=0;j<6;j++){
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
	}else if(mode == 4){          //終點
		for(int i=2;i<lines;i++){
			DrawLine(i);
		}
		bmp_back->Assign(bmp);   //儲檔
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
	if (i==4) {
		bmp->Canvas->Pen->Style = psDot ; //psDot ;
		bmp->Canvas->Brush->Color = clWhite;
		bmp->Canvas->Pen->Color = clGray;
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

void TForm1::DrawLine_double(int line_1,int line_2){
	bmp->Canvas->Pen->Width=line_data.pen_size;
	bmp->Canvas->Pen->Color =line_data.pen_color;
	float B_x_1,B_y_1,P1_x_1,P1_y_1,B_x_2,B_y_2,P1_x_2,P1_y_2,Bx_1,By_1,Bx_2,By_2,range;
	P1_x_1 = p_data[line_1][2] - (p_data[line_1][4] - p_data[line_1][2]);
	P1_y_1 = p_data[line_1][3] - (p_data[line_1][5] - p_data[line_1][3]);
	P1_x_2 = p_data[line_2][2] - (p_data[line_2][4] - p_data[line_2][2]);
	P1_y_2 = p_data[line_2][3] - (p_data[line_2][5] - p_data[line_2][3]);

	Bx_1 = ((1-0) * (1-0)) * p_data[line_1][0] + (2*0)*(1-0) * P1_x_1 + 0*0*p_data[line_1][2];
	By_1 = ((1-0) * (1-0)) * p_data[line_1][1] + (2*0)*(1-0) * P1_y_1 + 0*0*p_data[line_1][3];
	Bx_2 = ((1-0) * (1-0)) * p_data[line_2][0] + (2*0)*(1-0) * P1_x_2 + 0*0*p_data[line_2][2];
	By_2 = ((1-0) * (1-0)) * p_data[line_2][1] + (2*0)*(1-0) * P1_y_2 + 0*0*p_data[line_2][3];
	range = 0.01;
	for(float t=range;t<=1;t+=range){
		B_x_1 = ((1-t) * (1-t)) * p_data[line_1][0] + (2*t)*(1-t) * P1_x_1 + t*t*p_data[line_1][2];
		B_y_1 = ((1-t) * (1-t)) * p_data[line_1][1] + (2*t)*(1-t) * P1_y_1 + t*t*p_data[line_1][3];
		B_x_2 = ((1-t) * (1-t)) * p_data[line_2][0] + (2*t)*(1-t) * P1_x_2 + t*t*p_data[line_2][2];
		B_y_2 = ((1-t) * (1-t)) * p_data[line_2][1] + (2*t)*(1-t) * P1_y_2 + t*t*p_data[line_2][3];
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

void TForm1::SelPoint(int X,int Y){
	if(lines >= 99){
		ShowMessage("你畫的線太多了，請先完成目前的繪圖");
		return;
	}
	float small_pen = data.pen_size/2;
	if(X >= p_data[1][0] - data.width - small_pen && Y >= p_data[1][1] - data.height - small_pen && X <= p_data[1][0]+data.width-small_pen+1 && Y<= p_data[1][1]+data.height-small_pen+1){
		if(PenMode == 1){
		   //0 第幾條線 1點的狀態 (0重疊線 1 P點 ,2起點3終點 4起點和終點)
			if(end_draw == false){  //起點接終點
				SaveDraw();
				lines ++ ;
				p_data[lines][0] = p_data[lines-1][2];
				p_data[lines][1] = p_data[lines-1][3];
				p_data[lines][2] = p_data[lines][4] = p_data[1][0];          //終點座標
				p_data[lines][3] = p_data[lines][5] = p_data[1][1];          //P點等於終點
				DrawLine(lines);
				for(int i=0;i<6;i+=2)
					DrawPoint(lines,i);
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
		}else if(PenMode == 2){
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
						for(int j=1;j<lines;j++){
							for(int x = 0;x<6;x++)
							p_data[j][x] = p_data[j+1][x];
						}
						 p_data[1][0] = p_data[lines][2];
						 p_data[1][1] = p_data[lines][3];
						lines --;
					}
				}else{
					for(int j=0;j<lines;j++){
						for(int x = 0;x<6;x++)
							p_data[j][x] = p_data[j+1][x];
						}
					lines --;
				}
			 }
		}
		return;
	}else if(X >= p_data[lines][2] - data.width - small_pen && Y >= p_data[lines][3] - data.height - small_pen && X <= p_data[lines][2]+data.width-small_pen+1 && Y<= p_data[lines][3]+data.height-small_pen+1){
		click_data[0] = lines;
		click_data[1] = 3;
		if(PenMode == 1){
			ReDraw(lines,3);
			MovePoint_flag = true;
		}else if(PenMode == 2){
			if (lines>1) {
				lines --;
				if(end_draw == true){
					end_draw = false;
				 }
				for(int i=1;i<=lines;i++)
					for(int j=0;j<6;j+=2)
					DrawPoint(i,j);
			}else{
				Click_flag = true; //已設置起點
				PointEnd = true;
			}
		}
		return;
	}else{
		for(int i=lines;i>=0;i--){
			//終點檢查
			if(X >= p_data[i][2] - data.width - small_pen && Y >= p_data[i][3] - data.height - small_pen && X <= p_data[i][2]+data.width-small_pen+1 && Y<= p_data[i][3]+data.height-small_pen+1){
				click_data[0] = i;
				click_data[1] = 0;
				if(PenMode == 1){
					ReDraw(i,0);
					MovePoint_flag = true;
				}else if(PenMode == 2){
					if(end_draw == true && lines <=2){  //共接點
						lines --;
						Click_flag = true; //已設置起點
						PointEnd = true;
						end_draw = false;
					}else{
						p_data[i][2] = p_data[i+1][2];
						p_data[i][3] = p_data[i+1][3];
						for(int j=i;j<lines;j++){
							for(int x = 0;x<6;x++)
							p_data[j+1][x] = p_data[j+2][x];
						}
						 p_data[i+1][0] = p_data[i][2];
						 p_data[i+1][1] = p_data[i][3];
						lines --;
					}
				}
				return;
			//P點檢查
			}else if(X >= p_data[i][4] - data.width - small_pen && Y >= p_data[i][5] - data.height - small_pen && X <= p_data[i][4]+data.width-small_pen+1 && Y<= p_data[i][5]+data.height-small_pen+1){
				if(PenMode == 1){
					ReDraw(i,0);
					click_data[0] = i;
					click_data[1] = 1;
					ReDraw(i,1);
					MovePoint_flag = true;
				}
				return;
			}
		}
	}
	LinkPoint(X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(Button==mbLeft){
		DrawFlag = false;
		if(MovePoint_flag == true){
			SaveDraw();
			MovePoint_flag = false;
		}
		if(PenMode == 1){
			for(int i=1;i<=lines;i++)  //顯示P點
			for(int j=0;j<6;j+=2)
				DrawPoint(i,j);
		}else if(PenMode == 2){
			if(PointEnd == true && Click_flag == true){
				bmp_back->Assign(bmp_new);        //記錄點陣圖
				bmp->Assign(bmp_new);
				DrawPoint(1,0);         //顯示控制點
				for(int j=2;j<6;j++)
				p_data[1][j] = NULL;
				N14->Enabled = false;
			}else{
				bmp->Assign(bmp_new);//清空
				SaveDraw();

				for(int i=1;i<=lines;i++) //不顯示P點
				for(int j=0;j<4;j+=2)
					DrawPoint(i,j);
				}
		}else if(PenMode == 0){
		   SaveDraw();
		}
		Image1->Picture->Bitmap = bmp;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(Button==mbLeft){
		if(	PointEnd == true){  //畫圖模式
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
				p_data[lines][4] = X ;
				p_data[lines][5] = Y ;
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
			if(PenMode == 1 || PenMode ==2){
				SelPoint(X,Y);
			}else if(PenMode == 0){
				LinkPoint(X,Y);
			}
		}
	}else if(Button==mbRight){
		if(!(lines <= 1 || PointEnd == true)){
			 lines --;
			 if(end_draw == true){
				end_draw = false;
		 }
		 ShowPoint();
		}else if(lines == 1){
			bmp_back->Assign(bmp_new);        //記錄點陣圖
			bmp->Assign(bmp_new);
			DrawPoint(1,0);         //顯示控制點
			Image1->Picture->Bitmap = bmp;  //顯示結果
			Click_flag = true; //已設置起點
			PointEnd = true;
			N14->Enabled = false;
		 }
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
}
//---------------------------------------------------------------------------
void TForm1::ShowPoint(){
	if(!(Click_flag == true && PointEnd == true)){
		if(PenMode == 1){
			SaveDraw();
			for(int i=1;i<=lines;i++) //顯示P點
				for(int j=0;j<6;j+=2)
					DrawPoint(i,j);
					Image1->Picture->Bitmap = bmp;
		}else if(PenMode == 2){
			SaveDraw();
			for(int i=1;i<=lines;i++) //不顯示P點
				for(int j=0;j<4;j+=2)
					DrawPoint(i,j);
					Image1->Picture->Bitmap = bmp;
		}else if(PenMode == 0){
			SaveDraw();
			Image1->Picture->Bitmap = bmp;
		}
	}else{
		DrawPoint(1,0);
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
 
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
			for(int j=0;j<6;j++)
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
ShowPoint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
line_data.pen_size = 3;
ShowPoint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
line_data.pen_size = 1.5;
ShowPoint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N8Click(TObject *Sender)
{
line_data.pen_color = clBlack;
Panel2->Color =  line_data.pen_color;
ShowPoint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N9Click(TObject *Sender)
{
line_data.pen_color = clRed;
Panel2->Color =  line_data.pen_color;
SaveDraw();
ShowPoint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N10Click(TObject *Sender)
{
line_data.pen_color = clBlue;
Panel2->Color =  line_data.pen_color;
SaveDraw();
ShowPoint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N12Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N14Click(TObject *Sender)
{
if(!(lines <= 1 || PointEnd == true)){
  lines --;
  if(end_draw == true){
	end_draw = false;
  }
  ShowPoint();
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
			for(int j=0;j<6;j++)
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


void __fastcall TForm1::N17Click(TObject *Sender)
{
	PenMode = 0;
	SpeedButton1->Down = true;
	ShowPoint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N18Click(TObject *Sender)
{
	PenMode = 1;
	SpeedButton2->Down = true;
	ShowPoint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N19Click(TObject *Sender)
{
	PenMode = 2;
	SpeedButton3->Down = true;
	ShowPoint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	PenMode = 0;
	ShowPoint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
	PenMode = 1;
	ShowPoint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
	PenMode = 2;
	ShowPoint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
	EndDraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
	if(!(lines == 0)){
		for(int i=0;i<100;i++)
			for(int j=0;j<6;j++)
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

