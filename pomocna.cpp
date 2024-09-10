//---------------------------------------------------------------------------

#pragma hdrstop
#include <cmath>
#include "pomocna.h"
//---------------------------------------------------------------------------

int Orijentacija(Tacka A, Tacka B, Tacka C) {
	double p = A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y);
	if (p > 0) {
		return -1;
	}
	if (p < 0) {
		return 1;
	}
	return 0;
}

double udaljenost(const Tacka& a, const Tacka& b) {
		return hypot(b.x - a.x, b.y - a.y);
	}


bool Tacka::operator<(Tacka t2) {
	if (this->x == t2.x)
		return this->y < t2.y;
	return this->x < t2.x;
}

bool Tacka::operator==(Tacka t2) {
	return this->x == t2.x && this->y == t2.y;
}

double Tacka::operator-(Tacka t2) {
	return sqrt(pow((this->x - t2.x), 2) + pow((this->y - t2.y), 2));
}

void Tacka::Crtaj(TImage* Slika, TColor boja, int velicina) {
	Slika->Canvas->Brush->Color=boja;
	Slika->Canvas->Ellipse(x-velicina, y-velicina, x+velicina, y+velicina);
    Slika->Canvas->Brush->Color=clBlack;
}

void Duz::Crtaj(TImage* Slika, TColor boja, int velicina) {
	Slika->Canvas->Brush->Color=boja;
	Slika->Canvas->Pen->Color=boja;
	// A.Crtaj(Slika, boja, velicina);
	// B.Crtaj(Slika, boja, velicina);

	Slika->Canvas->MoveTo(A.x, A.y);
	Slika->Canvas->LineTo(B.x, B.y);

	Slika->Canvas->Brush->Color=clBlack;
    Slika->Canvas->Pen->Color=clBlack;
}

void Pravougaonik::Crtaj(TImage* Slika, TColor boja, int velicina) {
	Slika->Canvas->Brush->Color=boja;
	Slika->Canvas->Pen->Color=boja;
	Tacka gl(xmin, ymin), dl(xmin, ymax), gd(xmax, ymin), dd(xmax, ymax);

	Slika->Canvas->MoveTo(gl.x, gl.y);
	Slika->Canvas->LineTo(dl.x, dl.y);

	Slika->Canvas->MoveTo(dl.x, dl.y);
	Slika->Canvas->LineTo(dd.x, dd.y);

	Slika->Canvas->MoveTo(dd.x, dd.y);
	Slika->Canvas->LineTo(gd.x, gd.y);

	Slika->Canvas->MoveTo(gd.x, gd.y);
	Slika->Canvas->LineTo(gl.x, gl.y);

	Slika->Canvas->Brush->Color=clBlack;
    Slika->Canvas->Pen->Color=clBlack;
}

bool Duz::horizontalna() {
	return this->A.y == this->B.y;
}

bool Duz::vertikalna() {
	return this->A.x == this->B.x;
}

void iscrtajPoligon(vector<Tacka> &tacke, TImage *Slika) {

	for(int i=0; i < tacke.size(); i++) {
		tacke[i].Crtaj(Slika, clBlue);
		int naredna = (i + 1) % tacke.size();
		Duz(tacke[i], tacke[naredna]).Crtaj(Slika);
	}
}


bool daLiSeDuziSijeku(Duz d1, Duz d2) {
	bool uslov1 = (Orijentacija(d2.A, d2.B, d1.A) != Orijentacija(d2.A, d2.B, d1.B));
	bool uslov2 = (Orijentacija(d1.A, d1.B, d2.A) != Orijentacija(d1.A, d1.B, d2.B));
	return uslov1 && uslov2;
}




void pomjeriIteratorNaprijed(list<int>::iterator &it, list<int> &lista) {
	it++;
	if (it == lista.end()) {
		it = lista.begin();
	}
}

void pomjeriIteratorNazad(list<int>::iterator &it, list<int> &lista) {
	if (it == lista.begin()) {
		it = --lista.end();
	}
	else {
		it--;
	}
}


Tacka presjekPravih(Duz d1, Duz d2) {
	Tacka A=d1.A, B=d1.B, C=d2.A, D=d2.B;

	// Line AB represented as a1x + b1y = c1
	double a1 = B.y - A.y;
	double b1 = A.x - B.x;
	double c1 = a1*(A.x) + b1*(A.y);

	// Line CD represented as a2x + b2y = c2
	double a2 = D.y - C.y;
	double b2 = C.x - D.x;
	double c2 = a2*(C.x)+ b2*(C.y);

	double determinant = a1*b2 - a2*b1;

	if (determinant == 0)
	{
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
		return Tacka(FLT_MAX, FLT_MAX);
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
		return Tacka(x, y);
	}
}

bool izmedju(int x, int xmin, int xmax) {
	return x >= xmin && x <= xmax;
}






#pragma package(smart_init)
