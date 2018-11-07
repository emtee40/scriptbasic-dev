object main: Tmain
  Left = 329
  Top = 228
  Width = 708
  Height = 578
  Caption = 'ScriptBasic Debugger'
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
    0000000000000000000000000000000000199999999999100000000000000000
    0019999999999999100000000000000000199999999999999100000000000000
    0000199900000099991000000000000000001999000000099990000000000000
    0000199900000000999100000000000000001999000000001991000000000000
    0000199900000000199900000000000000001999000000001999000000000000
    0000199900000000199900000000000000001999000000001999000000000000
    0000199900000000199900000000000000001999000000009991000000000000
    0000199900000001999000000000000000001999000000099910000000000000
    0000199900000199990000000000000000199999999999999100000000000000
    0019999999999999100000000000000000199999999999100000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    800FFFFF8003FFFF8001FFFF83C0FFFF83E0FFFF83E0FFFF83E0FFFF83C0FFFF
    8001FFFF8003FFFF8007FFFF8383FFFF83C1FFFF83C1E01F83C1000780010003
    80030F83800F3FC1FFFF7FC1FFFFFF01FFFFF001FFFFC003FFFF8007FFFF001F
    FFFF01FFFFFF07FFFFFF07FBFFFF03E3FFFF8003FFFFC003FFFFF00FFFFF}
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnResize = mainOnResize
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 360
    Width = 75
    Height = 13
    Caption = 'Global variables'
  end
  object Label2: TLabel
    Left = 368
    Top = 360
    Width = 71
    Height = 13
    Caption = 'Local variables'
  end
  object source: TRichEdit
    Left = 8
    Top = 0
    Width = 681
    Height = 353
    Cursor = crIBeam
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    HideScrollBars = False
    Lines.Strings = (
      'source')
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
  end
  object state: TStatusBar
    Left = 0
    Top = 507
    Width = 700
    Height = 17
    Panels = <>
    SimplePanel = True
  end
  object GlobalVariableDisplay: TStringGrid
    Left = 8
    Top = 384
    Width = 337
    Height = 105
    ColCount = 2
    DefaultRowHeight = 16
    FixedCols = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    ParentFont = False
    TabOrder = 2
    ColWidths = (
      64
      69)
  end
  object LocalVariableDisplay: TStringGrid
    Left = 352
    Top = 384
    Width = 337
    Height = 105
    ColCount = 2
    DefaultRowHeight = 16
    FixedCols = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    ParentFont = False
    TabOrder = 3
  end
  object gvundef: TCheckBox
    Left = 104
    Top = 360
    Width = 73
    Height = 17
    Caption = 'hide undef'
    TabOrder = 4
    OnClick = gvundefClick
  end
  object lvundef: TCheckBox
    Left = 448
    Top = 360
    Width = 81
    Height = 17
    Caption = 'hide undef'
    TabOrder = 5
    OnClick = lvundefClick
  end
  object socket: TClientSocket
    Active = False
    Address = '127.0.0.1'
    ClientType = ctNonBlocking
    Host = '127.0.0.1'
    Port = 6647
    OnConnect = socketOnConnect
    OnDisconnect = socketDisconnect
    OnRead = socketOnRead
    OnError = socketOnError
    Left = 24
    Top = 56
  end
  object MainMenu1: TMainMenu
    Left = 24
    Top = 24
    object File1: TMenuItem
      Caption = '&File'
      object menuConnect: TMenuItem
        Caption = '&Connect'
        ShortCut = 16451
        OnClick = menuConnectClick
      end
      object Connectto1: TMenuItem
        Caption = 'Connect &to'
        ShortCut = 16468
        OnClick = Connectto1Click
      end
      object Open1: TMenuItem
        Caption = '&Run program'
        ShortCut = 16466
        OnClick = Open1Click
      end
      object menuDisconnect: TMenuItem
        Caption = '&Disconnect'
        ShortCut = 16452
        OnClick = menuDisconnectClick
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
      end
    end
    object menuStep: TMenuItem
      Caption = '&Step'
      object Step1: TMenuItem
        Caption = 'Step'
        ShortCut = 121
        OnClick = Step1Click
      end
      object StepInto1: TMenuItem
        Caption = 'Step Into'
        ShortCut = 122
        OnClick = StepInto1Click
      end
      object StepOut1: TMenuItem
        Caption = 'Step Out'
        ShortCut = 123
        OnClick = StepOut1Click
      end
    end
    object menuRun: TMenuItem
      Caption = '&Run'
      object Run1: TMenuItem
        Caption = 'Run'
        ShortCut = 116
        OnClick = Run1Click
      end
      object Runtocursor1: TMenuItem
        Caption = 'Run to cursor'
        ShortCut = 16506
        OnClick = Runtocursor1Click
      end
      object RUNtocursor2: TMenuItem
        Caption = 'RUN to cursor'
        ShortCut = 16505
        OnClick = RUNtocursor2Click
      end
      object Trace1: TMenuItem
        Caption = 'Trace'
        ShortCut = 117
        OnClick = Trace1Click
      end
      object StopTrace1: TMenuItem
        Caption = 'Stop Trace'
        ShortCut = 8309
        OnClick = StopTrace1Click
      end
      object menuStop: TMenuItem
        Caption = 'Stop'
        ShortCut = 8308
        OnClick = menuDisconnectClick
      end
    end
    object menuBreak: TMenuItem
      Caption = '&Break'
      object ToggleBreakpoint1: TMenuItem
        Caption = 'Toggle Breakpoint'
        RadioItem = True
        ShortCut = 120
        OnClick = ToggleBreakpoint1Click
      end
      object RemoveAllBreakpoints1: TMenuItem
        Caption = 'Remove All Breakpoints'
        OnClick = RemoveAllBreakpoints1Click
      end
    end
    object menuStack: TMenuItem
      Caption = 'S&tack'
      object StackUp1: TMenuItem
        Caption = 'Stack Up'
        ShortCut = 113
        OnClick = StackUp1Click
      end
      object StackDown1: TMenuItem
        Caption = 'Stack Down'
        ShortCut = 114
        OnClick = StackDown1Click
      end
      object StackBottom1: TMenuItem
        Caption = 'Stack Bottom'
        ShortCut = 115
        OnClick = StackBottom1Click
      end
    end
    object menuOptions: TMenuItem
      Caption = '&Options'
      OnClick = menuOptionsClick
    end
  end
  object TraceTimer: TTimer
    Enabled = False
    OnTimer = TraceStep
    Left = 24
    Top = 88
  end
  object OpenFile: TOpenDialog
    Left = 24
    Top = 120
  end
end
