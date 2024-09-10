//---------------------------------------------------------------------------

#ifndef prozorH
#define prozorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "pomocna.h"
#include <vector>
#include <list>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Slika;
	TButton *ButtonOcisti;
	TEdit *EditBrojTacaka;
	TRadioButton *RadioDodajTacku;
	TButton *ButtonNadjiPresjekeDuzi;
	TButton *ButtonGenerisiDuzi;
	void __fastcall SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);

	void __fastcall ButtonOcistiClick(TObject *Sender);

	void __fastcall ButtonPresjekDuziClick(TObject *Sender);



	void __fastcall SlikaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ButtonGenerisiHorVerDuziClick(TObject *Sender);
	void __fastcall ButtonPresjekHorVerDuziClick(TObject *Sender);
	void __fastcall ButtonNadjiPresjekeDuziClick(TObject *Sender);
	void __fastcall ButtonGenerisiDuziClick(TObject *Sender);

private:	// User declarations
	vector<Tacka> tacke;
	vector<Tacka> konveksni_omotac;
	vector<Tacka> poligon;
	bool zavrsen_poligon;
	vector<Duz> duzi;
	vector<pair<int, int>> dijagonale;
	bool drugi_klik = false;

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
