object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 439
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 635
    Height = 439
    Align = alClient
    OnMouseDown = Image1MouseDown
    OnMouseMove = Image1MouseMove
    OnMouseUp = Image1MouseUp
    ExplicitLeft = 8
  end
  object Label1: TLabel
    Left = 16
    Top = 412
    Width = 29
    Height = 19
    Caption = 'Left:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 51
    Top = 412
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 142
    Top = 412
    Width = 29
    Height = 19
    Caption = 'Top:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 177
    Top = 412
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 16
    Top = 387
    Width = 22
    Height = 19
    Caption = 'X0:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 44
    Top = 387
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 142
    Top = 387
    Width = 21
    Height = 19
    Caption = 'Y0:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label8: TLabel
    Left = 169
    Top = 387
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label9: TLabel
    Left = 16
    Top = 362
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label10: TLabel
    Left = 67
    Top = 362
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label11: TLabel
    Left = 122
    Top = 362
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label12: TLabel
    Left = 169
    Top = 362
    Width = 9
    Height = 19
    Caption = '0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Button1: TButton
    Left = 312
    Top = 406
    Width = 75
    Height = 25
    Caption = #28165#38500#30059#24067
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 393
    Top = 406
    Width = 75
    Height = 25
    Caption = #30059#32218
    TabOrder = 1
  end
  object Button3: TButton
    Left = 458
    Top = 335
    Width = 95
    Height = 25
    Caption = 'bmp_back=bmp'
    TabOrder = 2
  end
  object Button4: TButton
    Left = 474
    Top = 406
    Width = 75
    Height = 25
    Caption = 'bmp_back'
    TabOrder = 3
  end
  object Button5: TButton
    Left = 458
    Top = 366
    Width = 95
    Height = 25
    Caption = 'bmp = bmp_back'
    TabOrder = 4
  end
  object Button6: TButton
    Left = 552
    Top = 406
    Width = 75
    Height = 25
    Caption = 'bmp'
    TabOrder = 5
  end
end
