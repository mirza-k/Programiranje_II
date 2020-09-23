#include<iostream>
using namespace std;

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Datum
{
	int _dan;
	int _mjesec;
	int _godina;
public:
	int GetDan() const { return _dan; }
	int GetMjesec() const { return _mjesec; }
	int GetGodina() const { return _godina; }

	Datum(int d, int m, int g) : _dan(d), _mjesec(m), _godina(g) {}
	void Info ()
	{
		cout << _dan << "." << _mjesec << "." << _godina << endl;
	}

};

enum TipNaplate { PoOsobi, Jednokratno, PoNocenju };
const char* niz[] = { "Po osobi ", "Jednokratno", "Po nocenju" };
class Usluga
{
	char* _naziv;
	double _cijena;
	TipNaplate _tipNaplate;
public:
	int GetCijena() const { return _cijena; }

	//konst kopije//
	Usluga(const Usluga& u) {
		_naziv = AlocirajNizKaraktera(u._naziv);
		_cijena = u._cijena;
		_tipNaplate = u._tipNaplate;
	}

	Usluga& operator= (const Usluga& u) {
		_naziv = AlocirajNizKaraktera(u._naziv);
		_cijena = u._cijena;
		_tipNaplate = u._tipNaplate;
		return *this;
	}

	Usluga() : _cijena(0), _tipNaplate(TipNaplate(0)) { _naziv = nullptr; }
	Usluga(const char* naziv, int cijena, TipNaplate tipNaplate) :
		_cijena(cijena), _tipNaplate(tipNaplate)
	{
		_naziv = AlocirajNizKaraktera(naziv);
	}

	~Usluga()
	{
		delete[] _naziv;
		_naziv = nullptr;
	}

	void Info()
	{
		cout << "Naziv usluge: " << _naziv << endl;
		cout << "Cijena: " << _cijena << endl;
	}

	friend ostream& operator<<(ostream& cout, const Usluga& u);

};
ostream& operator<<(ostream& cout, const Usluga& u) {
	cout << "Naziv -> " << u._naziv << endl;
	cout << "Cijena -> " << u._cijena << endl;
	cout << "Tip naplate -> " << niz[PoNocenju] << endl;
	return cout;
}

enum TipSmjestaja { StudioApartman, SingleRoom, DoubleRoom, SuperiorApartman };
const char* TipSmjestajaString[] = { "StudioApartman", "SingleRoom", "DoubleRoom", "SuperiorApartman" };


class Smjestaj
{
	int _broj; //Broj sobe, apartmana
	TipSmjestaja* _tipSmjestaja;
	int _maxBrojOsoba;
	double _cijenaPoOsobi;
public:

	int GetCijena() const { return _cijenaPoOsobi; }
	int GetBroj() const { return _broj; }
	int GetMaxBrojOsoba() const{ return _maxBrojOsoba; }

	//operator=//
	Smjestaj& operator=(const Smjestaj& smj) 
	{
		_broj = smj._broj;
		delete _tipSmjestaja;
		_tipSmjestaja = new TipSmjestaja(*smj._tipSmjestaja);
		_maxBrojOsoba = smj._maxBrojOsoba;
		_cijenaPoOsobi = smj._cijenaPoOsobi;
		return *this;
	}

	Smjestaj() : _broj(0), _tipSmjestaja(nullptr), _maxBrojOsoba(0), _cijenaPoOsobi(0) {}

	Smjestaj(int broj, TipSmjestaja tip, int maxBrojOsoba, double cijenaPoOsobi) :
		_broj(broj), _tipSmjestaja(new TipSmjestaja(tip)), _maxBrojOsoba(maxBrojOsoba), _cijenaPoOsobi(cijenaPoOsobi)
	{
	}

	~Smjestaj()
	{
		delete _tipSmjestaja;
		_tipSmjestaja = nullptr;
	}

	Smjestaj(const Smjestaj& smj){
		_broj = smj._broj;
		_tipSmjestaja = new TipSmjestaja(*smj._tipSmjestaja);
		_maxBrojOsoba = smj._maxBrojOsoba;
		_cijenaPoOsobi = smj._cijenaPoOsobi;
	}

	void Info() const
	{
		cout << "Broj sobe: " << _broj << endl;
		cout << "Tip smjestaja: " << TipSmjestajaString[*_tipSmjestaja] << endl;
		cout << "Kapacitet smjestaja: " << _maxBrojOsoba << endl;
		cout << "Cijena po osobi: " << _cijenaPoOsobi << endl;

	}

};

class Gost
{
	char* _imePrezime;
	char* _kontakTelefon;
public:
//konstruktor kopije//
	Gost(const Gost& g) {
		_imePrezime = AlocirajNizKaraktera(g._imePrezime);
		_kontakTelefon = AlocirajNizKaraktera(g._kontakTelefon);
	}


	Gost(const char* imePrezime, const char* kontaktTelefon)
	{
		_imePrezime = AlocirajNizKaraktera(imePrezime);
		_kontakTelefon = AlocirajNizKaraktera(kontaktTelefon);
	}

	void Info()
	{
		cout << "Ime i prezime: " << _imePrezime << endl;
		cout << "Kontakt telefon: " << _kontakTelefon << endl;
	}

	~Gost() {
		delete[] _imePrezime; _imePrezime = nullptr;
		delete[] _kontakTelefon; _kontakTelefon = nullptr;
	}

};

int PretvaranjeDatuma(const Datum& d) {
	int temp = d.GetGodina()* 10000 + d.GetMjesec() * 100 + d.GetDan();
	return temp;
}
enum StatusRezervacije { Aktivna, Potvrdjena, BoravakUToku, Otkazana };
const char* StatusRezervacija[] = { "Aktivna","Potvrdjena","Boravak u toku","Otkazana" };
class Rezervacija
{
	Datum _pocetakBoravka;
	Datum _krajBoravka;
	Gost* _gost; //Gost koji je rezervisao smještaj
	Smjestaj _smjestaj;
	int _brojOsoba; //Ukupan broj osoba koji boravi u smjestaju
	Usluga* _usluge; //Dodatne usluge koje je gost koristio tokom boravka
	int _brojUsluga;
	double _ukupanIznos;
	StatusRezervacije _status;
public:

	~Rezervacija() {
		delete _gost; _gost = nullptr;
		delete[] _usluge;  _usluge = nullptr;
	}

	Usluga* GetUsluge() const { return _usluge; }
	int GetBrojUsluga() const { return _brojUsluga; }
	Gost GetGost() const { return *_gost; }
	StatusRezervacije GetStatus() const { return _status; }
	void SetStatus(StatusRezervacije novi) { _status = novi; }
	Datum GetPocetak() const { return _pocetakBoravka; }
	Datum GetKraj() const { return _krajBoravka; }
	Smjestaj GetSmjestaj() const { return _smjestaj; }
	int BrojOsoba() const { return _brojOsoba; }

	Rezervacija() :_pocetakBoravka(0,0,0),_krajBoravka(0,0,0),_gost(nullptr),_smjestaj(),_brojOsoba(0),_usluge(nullptr),_brojUsluga(0),_ukupanIznos(0),_status(Aktivna)
	{
	}

	Rezervacija(const Datum& d1, const Datum& d2, const Gost& g, const Smjestaj& smj, int brojOsoba):_pocetakBoravka(d1),_krajBoravka(d2)
	{
		_gost = new Gost(g);
		_smjestaj = smj;
		_brojOsoba = brojOsoba;
		_usluge = nullptr;
		_brojUsluga = 0;
		_ukupanIznos = 0;
		_status = Aktivna;
	}

	void RezervisiUslugu(const Usluga& u)
	{
		Usluga* temp = new Usluga[_brojUsluga + 1];
		for (size_t i = 0; i < _brojUsluga; i++)
		{
			temp[i] = _usluge[i];
		}

		delete[] _usluge;
		_usluge = temp;

		_usluge[_brojUsluga++] = u;
	}

	Rezervacija& operator= (const Rezervacija& rez) {
		_pocetakBoravka = rez._pocetakBoravka;
		_krajBoravka = rez._krajBoravka;
		delete _gost;
		_gost = new Gost(*rez._gost);
		_smjestaj = rez._smjestaj;
		_brojOsoba = rez._brojOsoba;
		_brojUsluga = rez._brojUsluga;
		_usluge = new Usluga[_brojUsluga];
		for (int i = 0; i < _brojUsluga; i++)
		{
			_usluge[i] = rez._usluge[i];
		}
		_ukupanIznos = rez._ukupanIznos;
		_status = rez._status;
		return *this;
	}



	friend ostream& operator<< (ostream& cout,  Rezervacija& rez);

};


ostream& operator<< (ostream& cout, Rezervacija& rez) {
	rez._pocetakBoravka.Info();
	cout << " - ";
	rez._krajBoravka.Info(); cout << endl;
	rez._gost->Info();
	rez._smjestaj.Info();
	rez._usluge->Info();
	cout << "Status rezervacije -> "<<StatusRezervacija[rez._status]<< endl;
	return cout;
}


class Hotel
{
	char* _naziv;
	//Ponuda smještaja
	Smjestaj* _smjestaji;
	int _brojSmjestaja;
	//Rezervacije hotela (protekle, aktivne i nadolazeće)
	Rezervacija* _rezervacije;
	int _brojRezervacija;
	static int _stopaPDV;
public:
	~Hotel() {
		delete[] _naziv; _naziv = nullptr;
		delete[] _smjestaji; _smjestaji = nullptr;
		delete[] _rezervacije; _rezervacije = nullptr;
	}

	Hotel(const char* naziv) : _smjestaji(nullptr), _brojSmjestaja(0),
		_rezervacije(nullptr), _brojRezervacija(0)
	{
		_naziv = AlocirajNizKaraktera(naziv);
	}


	Hotel& operator+=(const Smjestaj& smj) {
		for (int i = 0; i < _brojSmjestaja; i++)
		{
			if (smj.GetBroj() == _smjestaji[i].GetBroj()) {
				cout << "Ne moze se dodati vise smjestaja pod istim brojem." << endl;
				return *this;
			}
		}
		Smjestaj* temp = new Smjestaj[_brojSmjestaja + 1];
		for (int i = 0; i < _brojSmjestaja; i++)
		{
			temp[i] = _smjestaji[i];
		}
		temp[_brojSmjestaja] = smj;
		delete[] _smjestaji;
		_smjestaji = temp;
		_brojSmjestaja++;
		cout << "Smjestaj uspjesno dodan." << endl;
		return *this;
	}
	//Funkcija koja vrši ispis podataka o svim slobodnim smještajima hotela u zadatom periodu.
	//hotel1.IspisiSlobodneSmjestaje(Datum(24, 10, 2018), Datum(1, 11, 2018));

	bool DaLiJeSlobodanSmjestaj(const Datum& d1, const Datum& d2, const Smjestaj& smj) 
	{
		int OD2 = PretvaranjeDatuma(d1);
		int DO2 = PretvaranjeDatuma(d2);
		//int OD1 = PretvaranjeDatuma(_pocetakBoravka);
		//int DO1 = PretvaranjeDatuma(_krajBoravka);
		for (int i = 0; i < _brojRezervacija; i++)
		{
			if (_rezervacije[i].GetSmjestaj().GetBroj() == smj.GetBroj()) {
			int OD1 = PretvaranjeDatuma(_rezervacije[i].GetPocetak());
            int DO1 = PretvaranjeDatuma(_rezervacije[i].GetKraj());
			if (OD2 <OD1 && DO2 > OD1)
			{
				return false;
			}
			if (OD2<DO1 && DO2 > DO1)
			{
				return false;
			}
			if (OD2<OD1 && DO2>DO1)
			{
				return false;
			}
			if (OD2 > OD1 &&DO2 < DO1)
			{
				return false;
			}
			return true;
			}
		}
		return true;
	}


	void IspisiSlobodneSmjestaje(const Datum& d1, const Datum& d2) {
		for (int i = 0; i < _brojSmjestaja; i++)
		{
			if (DaLiJeSlobodanSmjestaj(d1, d2, _smjestaji[i])) {
				_smjestaji[i].Info(); cout << endl;
			}
		}
	}

	//

	bool DodajRezervaciju(const Rezervacija& rez) {
		//if (DaLiJeSlobodanSmjestaj(rez.GetPocetak(), rez.GetKraj(), rez.GetSmjestaj()) == false) {
		//	cout << "Smjestaj nije slobodan." << endl;
		//	return false;
		//}
		//if (rez.GetSmjestaj().GetMaxBrojOsoba() < rez.BrojOsoba()) {
		//	cout << "Nedovoljan kapacitet." << endl;
		//	return false;
		//}
		Rezervacija* temp = new Rezervacija[_brojRezervacija + 1];
		for (int i = 0; i < _brojRezervacija; i++)
		{
			temp[i] = _rezervacije[i];
		}
		temp[_brojRezervacija] = rez;
		delete[] _rezervacije;
		_rezervacije = temp;
		_brojRezervacija++;
		return true;
	}

	bool DaLiPostojiRezervacija(const Rezervacija& rez) {
		int OD2 = PretvaranjeDatuma(rez.GetPocetak());
		int DO2 = PretvaranjeDatuma(rez.GetKraj());
		for (int i = 0; i < _brojRezervacija; i++)
		{
			if (_rezervacije[i].GetSmjestaj().GetBroj() == rez.GetSmjestaj().GetBroj()) {
				int OD1 = PretvaranjeDatuma(_rezervacije[i].GetPocetak());
				int DO1 = PretvaranjeDatuma(_rezervacije[i].GetKraj());
				if (OD2 == OD1 && DO2 == DO1)
					return true;
			}
		}
		return false;
	}

	void PotvrdiRezervaciju( Rezervacija& rez) {
		for (int i = 0; i < _brojRezervacija; i++)
		{
			if (DaLiPostojiRezervacija(rez)) {
				rez.SetStatus(Potvrdjena);
				cout << "Potvrdjena." << endl;
				return;
			}
		}
		cout << "Rezervacija nije potvrdjena." << endl;
	}

	void CheckIn( Rezervacija& rez) {
		for (int i = 0; i < _brojRezervacija; i++)
		{
			if (DaLiPostojiRezervacija(rez))
			{
				if (rez.GetStatus() == Potvrdjena) {
					rez.SetStatus(BoravakUToku);
					cout << "Rezervacija checkirana." << endl;
					return;
				}

			}
		}
		cout << "Rezervacija nije checkirana." << endl;
	}

	int BrojacSmjestaja(const Datum& d1, const Datum& d2, const Smjestaj& smj) {
		int ODmain = PretvaranjeDatuma(d1);
		int DOmain = PretvaranjeDatuma(d2);
		int br = 0;
		for (int i = 0; i < _brojRezervacija; i++)
		{
			if (_rezervacije[i].GetSmjestaj().GetBroj() == smj.GetBroj()) 
			{
				int ODfja = PretvaranjeDatuma(_rezervacije[i].GetPocetak());
				int DOfja = PretvaranjeDatuma(_rezervacije[i].GetKraj());
				if ((ODfja<ODmain && DOfja>ODmain) || (ODfja<DOmain && DOfja>DOmain) || (ODfja<ODmain && DOfja>DOmain) || (ODfja>ODmain && DOfja<DOmain))
				{
					br++;
				}
			}
		}
		return br;
	}


Smjestaj GetNajTrazenijiSmjestaj(const Datum& d1, const Datum& d2) {
	int temp = 0, min = 0, indeksSmjestaja=0;
	for (int i = 0; i <_brojSmjestaja ; i++)
	{
		temp = BrojacSmjestaja(d1, d2, _smjestaji[i]);
		if (temp > min) {
			min = temp;
			indeksSmjestaja = i;
		}
	}
	return _smjestaji[indeksSmjestaja];
}
//	//Pronalazi i ispisuje podate o VIP gostu (onaj koji je u sumi utrošio najviše novca u hotelu u trenutnoj godini - 2018).
//	hotel1.PronadjiVIPGosta().Info();

int PotroseniNovac(const Rezervacija& rez) {
	int temp = 0;
	int OD = PretvaranjeDatuma(rez.GetPocetak());
	int DO = PretvaranjeDatuma(rez.GetKraj());
	int razlika = DO - OD;
	for (int i = 0; i < rez.GetBrojUsluga(); i++)
	{
		temp+=rez.GetUsluge()->GetCijena();
	}
	temp += rez.GetSmjestaj().GetCijena() *razlika;
	return temp;
}

Gost PronadjiVIPGosta() {
	int ukupno = 0, min = 0, indeks = 0;
	for (int i = 0; i < _brojRezervacija; i++)
	{
		ukupno = PotroseniNovac(_rezervacije[i]);
		if (ukupno > min) {
			min = ukupno;
			indeks = i;
		}
	}
	return _rezervacije[indeks].GetGost();
}


};






int Hotel::_stopaPDV = 17;

int main()
{

#pragma region Hotel

	const int brojUsluga(5);
	Hotel hotel1("Hotel Mostar");

	Usluga* usluge[brojUsluga];
	usluge[0] = new Usluga("Parking", 5, TipNaplate(1));
	usluge[1] = new Usluga("Dorucak", 10, TipNaplate(0));
	usluge[2] = new Usluga("Rucak", 15, TipNaplate(0));
	usluge[3] = new Usluga("Wellness & SPA", 40, TipNaplate(2));
	usluge[4] = new Usluga("Veseraj", 10, TipNaplate(2));

	Smjestaj apartman(10, TipSmjestaja(0), 5, 30);
	Smjestaj soba1(1, TipSmjestaja(1), 2, 20);
	Smjestaj soba2(2, TipSmjestaja(2), 4, 20);
	Smjestaj soba3(3, TipSmjestaja(0), 3, 15);
	Smjestaj soba4(4, TipSmjestaja(0), 4, 15);
	Smjestaj soba5(5, TipSmjestaja(0), 2, 15);

	//Funkciju za dodavanje smjestajnih kapaciteta hotela. Hotel ne moze imati više smještaja
	//pod istim brojem.
	hotel1 += apartman;
	hotel1 += soba1;
	hotel1 += soba2;
	hotel1 += soba3;
	hotel1 += soba4;
	hotel1 += soba5;

	////Funkcija koja vrši ispis podataka o svim slobodnim smještajima hotela u zadatom periodu.
	hotel1.IspisiSlobodneSmjestaje(Datum(24, 10, 2018), Datum(1, 11, 2018));

	//Ispis dodatnih usluga
	for (size_t i = 0; i < brojUsluga; i++)
	{
		cout << *usluge[i] << endl;
	}
	system("CLS");
#pragma endregion

#pragma region RezervacijaGost1

	Gost gost1("Marija Perić", "033/222-555");
	Rezervacija rezervacija1(Datum(12, 1, 2018),Datum(22, 2, 2018), gost1, soba1, 3);
	Rezervacija rezervacija2(Datum(11, 1, 2018),Datum(15, 1, 2018), gost1, soba4, 2);
	Rezervacija rezervacija3(Datum(5, 1, 2018),Datum(10, 1, 2018), gost1, soba2, 2);
	Rezervacija rezervacija4(Datum(8, 1, 2018),Datum(22, 1, 2017), gost1, soba4, 2);
	rezervacija1.RezervisiUslugu(*usluge[0]); //Parking
	rezervacija1.RezervisiUslugu(*usluge[1]); //Doručak za 3 osobe


	////Funkcija kojom se dodaje nova rezervacija pod uslovom da smjestaj nije zauzet u trazenom periodu 
	////i da kapacitet smještaja nije manji od broja osoba. Funkcija treba da ispiše sve uslove koje rezervacija
	////ne ispunjava.
	if (hotel1.DodajRezervaciju(rezervacija1))
		cout << "Uspjesno ste rezervisali smjestaj." << endl;
	else
		cout << "Rezervacija smjestaja nije uspjela." << endl;
	if (hotel1.DodajRezervaciju(rezervacija2))
		cout << "Uspjesno ste rezervisali smjestaj." << endl;
	else
		cout << "Rezervacija smjestaja nije uspjela." << endl;	
	if (hotel1.DodajRezervaciju(rezervacija3))
		cout << "Uspjesno ste rezervisali smjestaj." << endl;
	else
		cout << "Rezervacija smjestaja nije uspjela." << endl;	
	if (hotel1.DodajRezervaciju(rezervacija4))
		cout << "Uspjesno ste rezervisali smjestaj." << endl;
	else
		cout << "Rezervacija smjestaja nije uspjela." << endl;


	hotel1.PotvrdiRezervaciju(rezervacija2); //Prije nego se gosti prijave u hotel rezervacija mora biti potvrđena.
	hotel1.CheckIn(rezervacija2); //Mijenja status rezervacije na BoravakUToku, pod uslovom da je ista prethodno potvrđena.


	///*Vrši ispis računa sa svim stavkama rezervacije (posebno stavka za smještaj, a posebno za sve usluge sa
	//	pripadajućim cijenama, te ukupnim iznosom računa na kraju). Parametar tipa bool govori da li je potrebno obračunati
	//	PDV po utvrđenoj stopi na ukupan iznos računa te na sve stavke pojedinačno.*/
	//hotel1.CheckOut(rezervacija1, true);

#pragma endregion

#pragma region RezervacijaGost2
	Gost gost2("Adijan Marić", "066/111-333");

//
//#pragma endregion
//
//	//Napomena: Za potrebe testiranje funkcija u nastavku dopuniti testni program.
//
//	//Pronalazi i vraća podatke o najtraženijem smještaju hotela (onaj koji je najviše puta rezervisan u datom periodu)
	hotel1.GetNajTrazenijiSmjestaj(Datum(1, 1, 2018), Datum(24, 1, 2018)).Info();
//
//	//Pronalazi i ispisuje podate o VIP gostu (onaj koji je u sumi utrošio najviše novca u hotelu u trenutnoj godini - 2018).
	hotel1.PronadjiVIPGosta().Info();
//
	for (size_t i = 0; i < brojUsluga; i++)
	{
		delete usluge[i];
	}

	system("pause");

	return 0;
}




