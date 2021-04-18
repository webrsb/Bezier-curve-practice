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
	TButton *Button2;
	TButton *Button3;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button2Click(TObject *Sender);
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
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);


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
	void ShowPoint();
	void LinkPoint(int,int);

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
