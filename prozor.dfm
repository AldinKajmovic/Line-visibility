object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 673
  ClientWidth = 1073
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  TextHeight = 13
  object Slika: TImage
    Left = 73
    Top = 56
    Width = 761
    Height = 449
    OnMouseDown = SlikaMouseDown
    OnMouseMove = SlikaMouseMove
  end
  object ButtonOcisti: TButton
    Left = 248
    Top = 536
    Width = 105
    Height = 33
    Caption = 'O'#269'isti'
    TabOrder = 0
    OnClick = ButtonOcistiClick
  end
  object EditBrojTacaka: TEdit
    Left = 840
    Top = 56
    Width = 90
    Height = 21
    TabOrder = 1
    Text = '20'
  end
  object RadioDodajTacku: TRadioButton
    Left = 856
    Top = 96
    Width = 113
    Height = 17
    Caption = 'Dodaj ta'#269'ku'
    Checked = True
    TabOrder = 2
    TabStop = True
  end
  object ButtonNadjiPresjekeDuzi: TButton
    Left = 73
    Top = 536
    Width = 136
    Height = 33
    Caption = 'Odredi koje se du'#382'i vide'
    TabOrder = 3
    OnClick = ButtonNadjiPresjekeDuziClick
  end
  object ButtonGenerisiDuzi: TButton
    Left = 944
    Top = 56
    Width = 121
    Height = 34
    Caption = 'Generi'#353'i du'#382'i'
    TabOrder = 4
    OnClick = ButtonGenerisiDuziClick
  end
end
