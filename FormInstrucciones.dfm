object FormInstrucciones: TFormInstrucciones
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Instrucciones del Juego'
  ClientHeight = 450
  ClientWidth = 550
  Color = $00FFE4E1
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 15
  object PanelMain: TPanel
    Left = 25
    Top = 20
    Width = 500
    Height = 410
    BevelOuter = bvNone
    Color = $00FFE4E1
    ParentBackground = False
    TabOrder = 0
    object LabelTitulo: TLabel
      Left = 0
      Top = 0
      Width = 500
      Height = 40
      Alignment = taCenter
      AutoSize = False
      Caption = 'INSTRUCCIONES'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -28
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelObjetivo: TLabel
      Left = 0
      Top = 45
      Width = 500
      Height = 25
      Alignment = taCenter
      AutoSize = False
      Caption = 'Objetivo: Ordenar las piezas del 1 al 8'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGray
      Font.Height = -14
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object LabelJugador1: TLabel
      Left = 20
      Top = 90
      Width = 200
      Height = 30
      Caption = 'JUGADOR 1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -21
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelControles1: TLabel
      Left = 20
      Top = 125
      Width = 220
      Height = 60
      AutoSize = False
      Caption = 'Controles: W, A, S, D'#13#10'W = Arriba'#13#10'A = Izquierda'#13#10'S = Abajo'#13#10'D = Derecha'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object LabelDeshacer1: TLabel
      Left = 20
      Top = 190
      Width = 200
      Height = 25
      Caption = 'Deshacer: Ctrl + Z'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -14
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelJugador2: TLabel
      Left = 270
      Top = 90
      Width = 200
      Height = 30
      Caption = 'JUGADOR 2'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -21
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelControles2: TLabel
      Left = 270
      Top = 125
      Width = 220
      Height = 60
      AutoSize = False
      Caption = 'Controles: Flechas'#13#10#8593' = Arriba'#13#10#8592' = Izquierda'#13#10#8595' = Abajo'#13#10#8594' = Derecha'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object LabelDeshacer2: TLabel
      Left = 270
      Top = 190
      Width = 220
      Height = 25
      Caption = 'Deshacer: Tecla menos (-)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -14
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ButtonComenzar: TButton
      Left = 150
      Top = 330
      Width = 200
      Height = 60
      Caption = #161'COMENZAR!'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = ButtonComenzarClick
    end
  end
end
