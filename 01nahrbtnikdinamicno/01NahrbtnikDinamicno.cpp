// 01NahrbtnikDinamicno.cpp : Defines the entry point for the console application.
//

/* Karmen Unuk
OA_N0000819_sklop4_naloga1: 0/1 nahrbtnik z dinamiènim programiranjem */

/* Napišite program, ki poišèe optimalno zasedenost 0/1 nahrbtnika na dinamièen naèin. */

#include "stdafx.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class CPar
{
public:
	CPar(int aV, int aC);
	~CPar(void);
	int v;
	int c;
};

class CSeznamParov
{
public:
	CSeznamParov(void);
	~CSeznamParov(void);
	vector<CPar*> Seznam;
	bool Vsebuje(CPar* aP);
	void DodajPar(CPar* aP);
	CPar* VrniPar(int aI);
	int VrniVelikost();
	void IzpisSeznamovParov();
};

class CNahrbtnik
{
public:
	CNahrbtnik(int aN, int aV);
	~CNahrbtnik(void);
	CSeznamParov** S;
	CSeznamParov* Z;
	int V;	//volumen nahrbtnika
	int n;	//stevilo predmetov
	int* Napolni(CSeznamParov* aPre);
	CPar* Najboljsi(CSeznamParov* aS);
	void Zdruzi(int aI, CSeznamParov* aK);
	int MaxVolumen(CSeznamParov* aS);
	void Spremeni(CPar* &aP, int aV, int aC);
	void Obrni1(vector<CPar*> &aP);
	CSeznamParov* Novi(int aI, CPar* aP);
};

CPar::CPar(int aV, int aC)
{
	v = aV;
	c = aC;
}

CPar::~CPar(void)
{
}

CSeznamParov::CSeznamParov(void)
{
	vector<CPar* > Seznam;
}

CSeznamParov::~CSeznamParov(void)
{
}

bool CSeznamParov:: Vsebuje(CPar* aP)
{
	for(int i = 0; i < VrniVelikost(); i++){
		if(Seznam.at(i)->v == aP->v && Seznam.at(i)->c == aP->c){
			return true;
		}
	}
	return false;
}

void CSeznamParov:: DodajPar(CPar* aP)
{
	if(!Vsebuje(aP)){
		Seznam.push_back(aP);
	}else{
		cout << "Je z vpisano v seznam!" << endl;
	}
}

void CSeznamParov:: IzpisSeznamovParov()
{
	for(int i = 0; i< VrniVelikost(); i++){
		CPar* aE = VrniPar(i);
		cout << aE->v << " " << aE->c << "  ";
	}
	cout << endl;
}

CPar* CSeznamParov:: VrniPar(int aI)
{
	return Seznam.at(aI);
}

int CSeznamParov:: VrniVelikost()
{
	return Seznam.size();
}

CNahrbtnik::CNahrbtnik(int aN, int aV)
{
	n = aN;
	V = aV;
	S = new CSeznamParov*[n+1];
	for(int i=0; i<n+1; i++)
		S[i] = new CSeznamParov();
}

CNahrbtnik::~CNahrbtnik(void)
{
}

CSeznamParov* CNahrbtnik:: Novi(int aI, CPar* aP)
{
	CSeznamParov* aSe;
	aSe = new CSeznamParov();
	for(int i = 0; i < S[aI]->VrniVelikost(); i++){
		CPar* aE = S[aI]->VrniPar(i);
		CPar* aN = new CPar(aE->v + aP->v, aE->c + aP->c);
		aSe->DodajPar(aN);
	}
	return aSe;
}

int* CNahrbtnik:: Napolni(CSeznamParov* aPre)
{
	CPar* aP = new CPar(0,0);
	S[0]->DodajPar(aP);
	cout << "S[0]: ";
	S[0]->IzpisSeznamovParov(); 
	for(int i = 1; i< n+1; i++){
		CPar* aPar = aPre->VrniPar(i-1);
		Z = Novi(i-1, aPar);
		cout << "Z[" << i << "]: ";
		Z->IzpisSeznamovParov();
		Zdruzi(i, Z);
		cout << "S[" << i << "]: ";
		S[i]->IzpisSeznamovParov();
	}
	CPar* aR;
	aR = Najboljsi(S[n]);	//najdeš par z najveèjo ceno in dobrim volumnom
	cout << "Najboljsi: " << aR->v << " " << aR->c << endl;
	int* Resitev;
	Resitev = new int[n];
	int j = n; 
	while(j>0){
		if(S[j-1]->Vsebuje(aR) == false){
			Resitev[j-1] = 1;
			CPar* aT = aPre->VrniPar(j-1);
			CPar* aE = new CPar(aR->v - aT->v, aR->c - aT->c);
			//cout << aE->v << " " << aE->c << endl;
			Spremeni(aR, aE->v, aE->c);
		}else{
			Resitev[j-1] = 0;
		}
		j--;
	}
	return Resitev;
}

void CNahrbtnik::Spremeni(CPar* &aP, int aV, int aC)
{
	aP->v = aV;
	aP->c = aC;
}

void CNahrbtnik:: Obrni1(vector<CPar*> &aP)
{
	int aI = 0; 
	int aJ = aP.size()-1;
	for(int i = 0; i < (aP.size())/2; i++){
		CPar* aZ = aP.at(aI);
		aP.at(aI) = aP.at(aJ);
		aP.at(aJ) = aZ;
		aJ--;
		aI++;
	}
}

int CNahrbtnik:: MaxVolumen(CSeznamParov* aS)
{
	int aM = (aS->VrniPar(0))->v;
	for(int i = 0; i < aS->VrniVelikost(); i++){
		if(aM < (aS->VrniPar(i))->v){
			aM =(aS->VrniPar(i))->v;
		}
	}
	return aM;
}

CPar* CNahrbtnik:: Najboljsi(CSeznamParov* aS)
{
	vector<int> aMax;	//ustvarjaš vektor indeksov, iz katerega kasneje prebereš katere pare lahko raziskuješ
	int aV = MaxVolumen(aS);
	for(int i = 0; i< aS->VrniVelikost(); i++){
		if(aV == (aS->VrniPar(i))->v){
			aMax.push_back(i); 
		}
	}
	CPar* max = aS->VrniPar(aMax.at(0));
	for(int j = 1; j < aMax.size(); j++){
		if((aS->VrniPar(aMax.at(j))->c) > max->c)
			max = aS->VrniPar(aMax.at(j));
	}
	return max;
} 

void CNahrbtnik:: Zdruzi(int aI, CSeznamParov* aK)
{
	for(int j = 0; j< S[aI-1]->VrniVelikost(); j++){		//prepišeš vse pare iz predhodnega S-a, nato pa jim dodaš še ne obstojeèe iz Z-ja
		CPar* aP = S[aI-1]->VrniPar(j);
		S[aI]->DodajPar(aP);
	}
	for(int i = 0; i < aK->VrniVelikost(); i++){
		if(!S[aI]->Vsebuje(aK->VrniPar(i)) && aK->VrniPar(i)->v <= V){
			S[aI]->DodajPar(aK->VrniPar(i));
		}
	}
}




CNahrbtnik* Izpisi (char* ime, vector<int> &aVo, vector<int> &aCe){
 ifstream dat(ime);
 int aS;
 int aVO;
 int aV;
 int aC;
 if (dat.is_open()){
	dat>>aS;
	dat>>aVO;
	cout << "Stevilo elementov: " << aS << endl;
	cout << "Volumen nahrbtnika: " << aVO << endl;
	cout << endl;
	CNahrbtnik* nahr = new CNahrbtnik(aS,aVO);
	if(dat.good()){
	 for(int i = 0; i< aS; i++){
			  dat>>aV;
			  dat>>aC;
			  aVo.push_back(aV);
			  aCe.push_back(aC);
	 }
	}
	dat.close();
	return nahr;
 }
 else
	 cout<<"Napaka pri odpiranju datoteke!";
}
void Izpis(int* aV, int aN)
{
	for(int i = 0; i < aN; i++){
		cout << aV[i] << " ";
	}
	cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> PredmetiV;
	vector<int> PredmetiC;
	CNahrbtnik* N = Izpisi("N.txt", PredmetiV, PredmetiC);
	CSeznamParov* Predmeti;
	Predmeti = new CSeznamParov();
	for(int i = 0; i< PredmetiV.size(); i++){
		CPar* aP = new CPar(PredmetiV.at(i),PredmetiC.at(i));
		Predmeti->DodajPar(aP);
	}
	Predmeti->IzpisSeznamovParov();
	int* aR = N->Napolni(Predmeti);
	Izpis(aR, Predmeti->VrniVelikost());

	cin.ignore();
	cin.get();
	return 0;
}
