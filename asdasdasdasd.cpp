#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits>
#include <ctime>
#include <cstring>

using namespace std;



template <typename Tip, typename TipPoretka>
class Gomila
{
protected:
    Tip* Elementi; // Elementi niza
    int kapacitet; // Maksimalna velièina gomile
    int velicina; // Broj elemenata u gomili
    int duzinaNiza;
    void PopraviDolje(int i);
    void PopraviGore(int i);
    void Zamjeni (int i, int j);
    void operator =(const Gomila&); // Zaštita za op. dodjele
    Gomila(const Gomila&); // Zaštita za konstruktor kopije
public:
    void print()
    {
        for (int i = 0 ;i < velicina; i++)
            std::cout << Elementi[i] << ' ';
        std::cout << '\n';
    }
    Gomila (int maxduzina):velicina(0),kapacitet(maxduzina),
        Elementi(new Tip[maxduzina]) {}
    ~Gomila()
    {
        delete [] Elementi;
    }
    int Velicina() const
    {
        return velicina;
    }
    bool JeLiList(int i) const
    {
        return (i >= velicina/2) && (i < velicina);
    }
    int LijevoDijete(int i) const   // Pozicija lijevog djeteta
    {
        return 2*i+1;
    }
    int DesnoDijete(int i) const   // Pozicija desnog djeteta
    {
        return 2*i+2;
    }
    int Roditelj(int i) const   // Pozicija roditelja
    {
        return (i-1)/2;
    }
    void StvoriGomilu(); // Stvaranje gomile iz neureðenog niza
    void UmetniUGomilu(const Tip& x); // Umetanje u gomilu
    Tip IzbaciPrvi(); // Izbacivanje prvog el.
    Tip Izbaci(int i); // Izbacivanje el. na poziciji i
    void PromjeniKljuc(int i, Tip& x); // Promjena kljuèa
    int DajVelicinu() const
    {
        return velicina;    // Vraæa velièinu gomile
    }
    int DajDuzinuNiza() const
    {
        return duzinaNiza;    // Vraæa dužinu niza
    }
    void Ucitaj(int); // Uèitavanje u niz
    void Prikazi(int) const; // Prikaz sadržaja u nizu
};
class MaxTip   // Tip poretka za Max-gomilu
{
public:
    static bool prior(int x, int y)
    {
        return x > y;
    }
};
class MinTip   // Tip poretka za Min-gomilu
{
public:
    static bool prior(int x, int y)
    {
        return x < y;
    }
};

template <typename Tip, typename TipPoretka> // Izmjena pozicija
void Gomila<Tip,TipPoretka>::Zamjeni (int i, int j)
{
    Tip tmp(Elementi[i]);
    Elementi[i]=Elementi[j];
    Elementi[j]=tmp;
}
template <typename Tip, typename TipPoretka> // Popravljanje spuštanjem
void Gomila<Tip,TipPoretka>::PopraviDolje(int i)
{
    while (!JeLiList(i))
    {
        int veci=LijevoDijete(i);
        int dd=DesnoDijete(i);
        if ((dd<velicina) && TipPoretka::prior(Elementi[dd],Elementi[veci]))
            veci=dd;
        if (TipPoretka::prior(Elementi[i],Elementi[veci])) return;
        Zamjeni(i,veci);
        i=veci;
    }
}
template <typename Tip, typename TipPoretka> // Popravljanje podizanjem
void Gomila<Tip,TipPoretka>::PopraviGore(int i)
{
    while ((i != 0) && (TipPoretka::prior(Elementi[i],
                                          Elementi[Roditelj(i)])))
    {
        Zamjeni(i,Roditelj(i));
        i=Roditelj(i);
    }
}
template <typename Tip, typename TipPoretka> // Stvaranje gomile
void Gomila<Tip,TipPoretka>::StvoriGomilu()
{
    velicina=duzinaNiza;
    for (int i=velicina/2; i>=0; i--)
        PopraviDolje(i);
}
template <typename Tip, typename TipPoretka> // Umetanje u gomilu
void Gomila<Tip,TipPoretka>::UmetniUGomilu(const Tip& x)
{
    if (velicina > kapacitet-1)
        throw "Gomila je puna";
    Elementi[velicina++]=x;
    PopraviGore(velicina-1);
}
template <typename Tip, typename TipPoretka> // Izbacivanje prvog elem.
Tip Gomila<Tip,TipPoretka>::IzbaciPrvi()
{
    if(velicina==0)
        throw "\nGomila je prazna!\n";
    Zamjeni(0,--velicina);
    if (velicina!=0)
        PopraviDolje(0);
    return Elementi[velicina];
}
template <typename Tip, typename TipPoretka> // Izbacivanje el. na poz. i
Tip Gomila<Tip,TipPoretka>::Izbaci(int i)
{
    if (i < 0 || i >= velicina)
        throw "\nPogresan indeks!\n";
    Zamjeni(i,--velicina);
    PopraviGore(i);
    PopraviDolje(i);
    return Elementi[velicina];
}
template <typename Tip, typename TipPoretka> // Promjena vrijednosti kljuèa
void Gomila<Tip,TipPoretka>::PromjeniKljuc(int i, Tip& x)
{
    if (!TipPoretka::prior(x,Elementi[i]))
    {
        cout<<"Greska\n";
        return;
    }
    Elementi[i]=x;
    PopraviGore(i);
}
template <typename Tip,typename TipPoretka> // Uèitavanje u niz
void Gomila<Tip,TipPoretka>::Ucitaj (int n)
{
    velicina=0;
    for (int i=0; i<n; i++)
    {
        int x;
        cin >> x;
        Elementi[i]=x;
    }
    duzinaNiza=n;
}
template <typename Tip,typename TipPoretka> // Prikaz sadržaja niza
void Gomila<Tip,TipPoretka>::Prikazi (int n) const
{
    for (int i=0; i<n; i++)
    {
        cout << Elementi[i] << endl;
    }
}



int main()
{
    Gomila<int, MaxTip> g(6);

    g.Ucitaj(6);
    g.StvoriGomilu();
    g.print();

    return 0;
}
