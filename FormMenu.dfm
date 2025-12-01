object FormMenu: TFormMenu
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Rompecabezas - Menú Principal'
  ClientHeight = 500
  ClientWidth = 700
  Color = clMoneyGreen
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWhite
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 15
  object PanelMain: TPanel
    Left = 100
    Top = 80
    Width = 500
    Height = 340
    BevelOuter = bvNone
    Color = clMoneyGreen
    ParentBackground = False
    TabOrder = 0
    object LabelTitulo: TLabel
      Left = 0
      Top = 30
      Width = 500
      Height = 70
      Alignment = taCenter
      AutoSize = False
      Caption = 'ROMPECABEZAS'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -48
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelSubtitulo: TLabel
      Left = 0
      Top = 100
      Width = 500
      Height = 40
      Alignment = taCenter
      AutoSize = False
      Caption = 'Juego de 2 Jugadores'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGray
      Font.Height = -24
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object ButtonIniciar: TButton
      Left = 150
      Top = 200
      Width = 200
      Height = 60
      Caption = 'Iniciar Juego'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Segoe UI'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = ButtonIniciarClick
    end
  end
end
