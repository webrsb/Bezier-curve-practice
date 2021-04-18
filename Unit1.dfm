object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #35997#33586#26354#32218
  ClientHeight = 449
  ClientWidth = 660
  Color = clCream
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnShortCut = FormShortCut
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 660
    Height = 449
    Align = alClient
    OnMouseDown = Image1MouseDown
    OnMouseMove = Image1MouseMove
    OnMouseUp = Image1MouseUp
    ExplicitLeft = 48
    ExplicitTop = -8
  end
  object Label1: TLabel
    Left = 192
    Top = 406
    Width = 70
    Height = 19
    Caption = 'PenMode:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 280
    Top = 406
    Width = 9
    Height = 19
    Caption = '1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = []
    ParentFont = False
  end
  object Button2: TButton
    Left = 472
    Top = 400
    Width = 75
    Height = 25
    Caption = #31227#21205#31680#40670
    TabOrder = 0
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 553
    Top = 400
    Width = 75
    Height = 25
    Caption = #21034#38500#31680#40670
    TabOrder = 1
    OnClick = Button3Click
  end
  object Button1: TButton
    Left = 391
    Top = 400
    Width = 75
    Height = 25
    Caption = #27298#31034#27169#24335
    TabOrder = 2
    OnClick = Button1Click
  end
  object MainMenu1: TMainMenu
    AutoHotkeys = maManual
    Left = 184
    Top = 72
    object N11: TMenuItem
      Caption = #27284#26696
      object N2: TMenuItem
        AutoHotkeys = maManual
        Caption = #38283#26032#27284#26696
        OnClick = N2Click
      end
      object N3: TMenuItem
        AutoHotkeys = maManual
        Caption = #23436#25104#32362#22294
        OnClick = N3Click
      end
      object N12: TMenuItem
        Caption = #38626#38283
        OnClick = N12Click
      end
    end
    object N13: TMenuItem
      Caption = #32232#36655
      object N14: TMenuItem
        Caption = #21034#38500#19978#19968#26781#32218
        Enabled = False
        OnClick = N14Click
      end
    end
    object N1: TMenuItem
      AutoHotkeys = maManual
      Caption = #37628#31558#31895#32048
      Enabled = False
      object N4: TMenuItem
        Caption = #31895
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = #20013#31561
        OnClick = N5Click
      end
      object N6: TMenuItem
        Caption = #32048
        OnClick = N6Click
      end
    end
    object N7: TMenuItem
      AutoHotkeys = maManual
      Caption = #37628#31558#38991#33394
      Enabled = False
      object N8: TMenuItem
        Caption = #40657#33394
        OnClick = N8Click
      end
      object N9: TMenuItem
        Caption = #32005#33394
        OnClick = N9Click
      end
      object N10: TMenuItem
        Caption = #34253#33394
        OnClick = N10Click
      end
    end
  end
end
