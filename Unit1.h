//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <dir.h>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ActnColorMaps.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TMainMenu *MainMenu1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N1;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TMenuItem *Save1;
	TMenuItem *N15;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *N19;
	TPanel *Panel1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton5;
	TColorDialog *ColorDialog1;
	TPanel *Panel2;
	TSavePictureDialog *SavePictureDialog1;
	TMenuItem *N20;
	TMenuItem *N21;
	TMenuItem *N22;
	TPanel *Panel3;
	TSpeedButton *SpeedButton6;
	TStatusBar *StatusBar1;
	TMenuItem *N23;
	TSpeedButton *SpeedButton7;
	TPanel *Panel4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall Save1Click(TObject *Sender);
	void __fastcall N15Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall Panel2Click(TObject *Sender);
	void __fastcall N21Click(TObject *Sender);
	void __fastcall N22Click(TObject *Sender);
	void __fastcall Panel3Click(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall SpeedButton7Click(TObject *Sender);
	void __fastcall Panel4Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void TForm1::Clear();
	Graphics::TBitmap *bmp,*bmp_back,*bmp_new;     //建立一個新的bitmap
	void DrawPoint(int,int);
	void DrawLine(int);
	void DrawLine_double(int,int);
	void SelPoint(int,int);
	void ReDraw(int,int);
	void SaveDraw();
	void EndDraw();
	void ShowPoint(int,int);
	void LinkPoint(int,int);
	void SaveImage(Graphics::TBitmap *,AnsiString);
	void GetRGB(Graphics::TBitmap *, int , int , int *, int *, int *);
	void FloodFill(Graphics::TBitmap *, Graphics::TBitmap *,
					TColor,int,int);
	void FloodFill_stack(int,int);

	AnsiString AppPath,PicPath;

	bool DrawFlag,PointEnd,Click_flag,MovePoint_flag,end_draw,key_flag,Revers_flag,Sync_flag;
	//畫圖模式               第二次點  移動控制點模式                              暫時無用
	unsigned int options,PenMode;
	//0起點 1終點 2 P點   0檢示模式  1移動控制點模式  2刪除控制點模式
	int p_data[100][8],lines,click_data[2]; //0 第幾條線 1 起點 終點 P點 是否重疊
	//0 1起點 2 3終點 4 5  p點
	double len1;     //暫時無用

struct stack_data
{
	int width;
	int height;
	int cR,cG,cB;
	int pR,pG,pB;
	Graphics::TBitmap *Target;
	TColor f_color;
}stack_data;

	struct point_data
	{
		int num_point;
		float width;
		float height;
		TColor brush_color;
		TColor pen_color;
		float pen_size;
	}data;

	struct line_d
	{
		TColor pen_color;
		float pen_size;
		TColor bg_color;
	}line_data;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
