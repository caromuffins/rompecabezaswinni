object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Rompecabezas - Juego'
  ClientHeight = 600
  ClientWidth = 900
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  KeyPreview = True
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 15
  object LabelJugador1: TLabel
    Left = 120
    Top = 50
    Width = 150
    Height = 30
    Caption = 'JUGADOR 1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -21
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelJugador2: TLabel
    Left = 550
    Top = 50
    Width = 150
    Height = 30
    Caption = 'JUGADOR 2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -21
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelGanador: TLabel
    Left = 0
    Top = 0
    Width = 900
    Height = 600
    Alignment = taCenter
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -64
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    Layout = tlCenter
    Visible = False
  end
  object ButtonDesordenar: TButton
    Left = 370
    Top = 520
    Width = 160
    Height = 50
    Caption = 'Desordenar Piezas'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = ButtonDesordenarClick
  end
  object ButtonVolverMenu: TButton
    Left = 750
    Top = 520
    Width = 130
    Height = 50
    Caption = 'Volver al Menu'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = ButtonVolverMenuClick
  end
  object ButtonJugarDeNuevo: TButton
    Left = 350
    Top = 350
    Width = 200
    Height = 60
    Caption = 'Jugar de Nuevo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -18
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    Visible = False
    OnClick = ButtonJugarDeNuevoClick
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 800
    Top = 30
  end
end
