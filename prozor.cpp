//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "pomocna.cpp"
#include "prozor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	zavrsen_poligon = false;
	Slika->Canvas->Brush->Color=clWhite;
	Slika->Canvas->FillRect(TRect(0,0,Slika->Width,Slika->Height));
	Slika->Canvas->Brush->Color=clBlack;
	Slika->Canvas->FrameRect(TRect(0,0,Slika->Width,Slika->Height));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Tacka nova = Tacka(X, Y);


	tacke.push_back(nova);
	nova.Crtaj(Slika, clBlue);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonOcistiClick(TObject *Sender)
{
	Slika->Canvas->Brush->Color=clWhite;
	Slika->Canvas->FillRect(TRect(0,0,Slika->Width,Slika->Height));
	Slika->Canvas->Brush->Color=clBlack;
	Slika->Canvas->FrameRect(TRect(0,0,Slika->Width,Slika->Height));
	tacke.clear();
	konveksni_omotac.clear();
	poligon.clear();
	zavrsen_poligon = false;
	dijagonale.clear();
	duzi.clear();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonPresjekDuziClick(TObject *Sender)
{
	int n(duzi.size());

	if (n < 2) {
		return;
	}

	Duz duz1(duzi[n-1]), duz2(duzi[n-2]);
	if (daLiSeDuziSijeku(duz1, duz2)) {
		ShowMessage("Duzi se sijeku!");
	}
	else {
		ShowMessage("Duzi se ne sijeku!");
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------




//-------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm1::SlikaMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	string koordinate = "X: " + to_string(X) + " Y: " + to_string(Y);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonGenerisiHorVerDuziClick(TObject *Sender)
{
	int broj_duzi = EditBrojTacaka->Text.ToInt();
	for (int i = 0; i < broj_duzi; i++) {
		int x1,x2,y1,y2;
		if (rand() % 2 == 0) { // horizontalna
			x1 = rand() % Slika->Width;
			x2 = rand() % Slika->Width;
			y1 = rand() % Slika->Height;
			y2 = y1;
		}
		else { // vertikalna
			y1 = rand() % Slika->Height;
			y2 = rand() % Slika->Height;
			x1 = rand() % Slika->Width;
			x2 = x1;
		}
		Duz nova(Tacka(x1, y1), Tacka(x2, y2));
		nova.Crtaj(Slika, clBlue);
		nova.A.Crtaj(Slika, clRed);
		nova.B.Crtaj(Slika, clRed);
		duzi.push_back(nova);
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ButtonPresjekHorVerDuziClick(TObject *Sender)
{
	priority_queue<pair<Duz*, Tacka>, vector<pair<Duz*, Tacka>>, HorVerDuziPoX> eventi;

	for(int i=0; i<duzi.size(); i++) {
		if (duzi[i].horizontalna()) {
			eventi.push({&duzi[i], duzi[i].A});
			eventi.push({&duzi[i], duzi[i].B});
		}
		else {
			eventi.push({&duzi[i], duzi[i].A});
		}
	}

	set<Duz*, AktivneHorVerPoY> aktivne;
	vector<Tacka> presjeci;

	while(!eventi.empty()) {
		pair<Duz*, Tacka> trenutni = eventi.top();
		eventi.pop();

		Duz* trenutna_duz = trenutni.first;
		Tacka trenutna_tacka = trenutni.second;

		if (trenutna_duz->horizontalna()) {
			if (trenutna_tacka == trenutna_duz->A) { // pocetak H
				aktivne.insert(trenutna_duz);
			}
			else { // kraj H
				aktivne.erase(trenutna_duz);
			}
		}
		else {  // vertikalna
			double gornji_y = trenutna_duz->A.y;
			double donji_y = trenutna_duz->B.y;
			Duz temp_d1 = Duz(Tacka(0, gornji_y), Tacka(0, gornji_y));
			Duz temp_d2 = Duz(Tacka(0, donji_y), Tacka(0, donji_y));

			auto it_gornji = aktivne.lower_bound(&temp_d1);
			auto it_donji = aktivne.upper_bound(&temp_d2);

			for(auto it = it_gornji; it != it_donji; it++) {
				Tacka presjek(trenutna_duz->A.x, (*it)->A.y);
				presjeci.push_back(presjek);
				presjek.Crtaj(Slika, clYellow, 5);
			}
		}

	}

	if (presjeci.size() == 0) {
		ShowMessage("Nema presjeka!");
	}
}



void __fastcall TForm1::ButtonNadjiPresjekeDuziClick(TObject *Sender)
{
	if (tacke.empty()) {
		ShowMessage("Nema tačaka za analizu!");
		return;
	}
	Tacka A = tacke[0];
	vector<Dogadjaj> dogadjaji;
	for (auto& duz : duzi) {
		int orientA = Orijentacija(A, duz.A, duz.B);
		int orientB = Orijentacija(A, duz.B, duz.A);
		double udaljenostA = udaljenost(A, duz.A);
		double udaljenostB = udaljenost(A, duz.B);
		if (orientA > orientB) {
			swap(orientA, orientB);
			swap(udaljenostA, udaljenostB);
		}
		dogadjaji.push_back({orientA, udaljenostA, true, &duz});
		dogadjaji.push_back({orientB, udaljenostB, false, &duz});
	}
	sort(dogadjaji.begin(), dogadjaji.end());

	auto duzPoUdaljenosti = [&A](const Duz* s1, const Duz* s2) {
		double d1 = min(udaljenost(A, s1->A), udaljenost(A, s1->B));
		double d2 = min(udaljenost(A, s2->A), udaljenost(A, s2->B));
		return d1 < d2;
	};
	set<Duz*, decltype(duzPoUdaljenosti)> aktivneDuzi(duzPoUdaljenosti);
	set<Duz*> vidljiveDuzi;

	for (auto& dogadjaj : dogadjaji) {
		if (dogadjaj.jeLiPocetak) {
			aktivneDuzi.insert(dogadjaj.duz);
		} else {
			aktivneDuzi.erase(dogadjaj.duz);
		}
		if (!aktivneDuzi.empty()) {
			Duz* najblizaDuz = *aktivneDuzi.begin();
			vidljiveDuzi.insert(najblizaDuz);
		}
	}

	// Crtanje segmenata
	for (auto& duz : duzi) {
		if (vidljiveDuzi.find(&duz) != vidljiveDuzi.end()) {
			duz.Crtaj(Slika, clGreen);
		} else {
			duz.Crtaj(Slika, clRed);
		}
	}
}




//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonGenerisiDuziClick(TObject *Sender)
{

	int broj_duzi = EditBrojTacaka->Text.ToInt();
	for (int i = 0; i < broj_duzi; i++) {
		int x1, x2, y1, y2;
		bool presijeca;
		do {
			x1 = rand() % Slika->Width;
			x2 = rand() % Slika->Width;
			y1 = rand() % Slika->Height;
			y2 = rand() % Slika->Height;

			Duz nova(Tacka(x1, y1), Tacka(x2, y2));
			presijeca = false;
			for (const auto& prethodna_duz : duzi) {
				if (daLiSeDuziSijeku(nova, prethodna_duz)) {
					presijeca = true;
					break;
				}
			}
		} while (presijeca);

		Duz nova(Tacka(x1, y1), Tacka(x2, y2));
		nova.Crtaj(Slika, clBlue);
		nova.A.Crtaj(Slika, clRed);
		nova.B.Crtaj(Slika, clRed);
		duzi.push_back(nova);
	}




}

//---------------------------------------------------------------------------


