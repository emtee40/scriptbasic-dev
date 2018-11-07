object FormOptions: TFormOptions
  Left = 253
  Top = 218
  Width = 426
  Height = 187
  Caption = 'Options'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000099999900000000000000000
    0000000999999999100000000000000000000199999999999900000000000000
    0000099999000099999000000000000000009999100000019991000000000000
    0001999100000000199900000000000000099990000000000999100000000000
    0009991000000000099910000000000000099900000000000199900000000000
    0009990000000000019990000000000000099900000000000199900000000000
    0009991000000000099910000000000000099990000000000999100000000000
    0001999100000000199900000000000000009999100000019991000000000000
    0000099999000099999000000000000000000199999999999900000000000000
    0000000999999999100000000000000000000000099999900000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    800FFFFF8003FFFF8001FFFF83C0FFFF83E0FFFF83E0FFFF83E0FFFF83C0FFFF
    8001FFFF8003FFFF8007FFFF8383FFFF83C1FFFF83C1E01F83C1000780010003
    80030F83800F3FC1FFFF7FC1FFFFFF01FFFFF001FFFFC003FFFF8007FFFF001F
    FFFF01FFFFFF07FFFFFF07FBFFFF03E3FFFF8003FFFFC003FFFFF00FFFFF}
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 8
    Top = 8
    Width = 48
    Height = 13
    Caption = 'scriba.exe'
  end
  object Label4: TLabel
    Left = 8
    Top = 40
    Width = 42
    Height = 13
    Caption = 'Trace Dt'
  end
  object Label5: TLabel
    Left = 184
    Top = 40
    Width = 13
    Height = 13
    Caption = 'ms'
  end
  object btnCancel: TButton
    Left = 8
    Top = 88
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 0
    OnClick = btnCancelClick
  end
  object btnOK: TButton
    Left = 216
    Top = 88
    Width = 81
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = btnOKClick
  end
  object btnApply: TButton
    Left = 112
    Top = 88
    Width = 81
    Height = 25
    Caption = 'Apply'
    TabOrder = 2
    OnClick = btnApplyClick
  end
  object commandline: TEdit
    Left = 88
    Top = 8
    Width = 241
    Height = 21
    TabOrder = 3
    Text = 'C:\ScriptBasic\bin\scriba'
  end
  object btnBrowse: TButton
    Left = 336
    Top = 8
    Width = 65
    Height = 25
    Caption = 'Browse'
    TabOrder = 4
    OnClick = btnBrowseClick
  end
  object traceDt: TEdit
    Left = 88
    Top = 32
    Width = 89
    Height = 21
    TabOrder = 5
    OnKeyPress = traceDtKeyPress
  end
  object btnFont: TButton
    Left = 88
    Top = 56
    Width = 89
    Height = 25
    Caption = 'Select Font'
    TabOrder = 6
    Visible = False
    OnClick = btnFontClick
  end
  object OpenScriba: TOpenDialog
    Left = 368
    Top = 8
  end
  object font: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Left = 232
    Top = 40
  end
end
