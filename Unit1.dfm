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
    ExplicitLeft = 8
    ExplicitWidth = 635
    ExplicitHeight = 439
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
