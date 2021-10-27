#include <stdio.h>
#include "quaternion.h"

#define PI 3.1415926

struct ObjectState
{
	bool can_join;				// czy moze grac
	Vector3 vPos;             // polozenie obiektu (�rodka geometrycznego obiektu) 
	quaternion qOrient;       // orientacja (polozenie katowe)
	Vector3 vV, vA;            // predkosc, przyspiesznie liniowe
	Vector3 vV_ang, vA_ang;   // predkosc i przyspieszenie liniowe
	float steering_angle;               // kat skretu kol w radianach (w lewo - dodatni)
};

// Klasa opisuj�ca obiekty ruchome
class MovableObject
{
public:
	int iID;                  // identyfikator obiektu

	ObjectState state;

	float F, Fb;               // si�y dzia�aj�ce na obiekt: F - pchajaca do przodu, Fb - w prawo
	float breaking_factor;    // stopie� hamowania Fh_max = friction*Fy*ham
	float Fy;                 // si�a nacisku na podstaw� pojazdu - gdy obiekt styka si� z pod�o�em (od niej zale�y si�a hamowania)
	float steer_wheel_speed;      // pr�dko�� kr�cenia kierownic�
	bool if_keep_steer_wheel;       // czy kierownica jest trzymana (pr�dko�� mo�e by� zerowa, a kierownica trzymana w pewnym po�o�eniu nie wraca do po�. zerowego)

	float mass_own;				  // masa obiektu	
	float length, width, height; // rozmiary w kierunku lokalnych osi x,y,z
	float clearance;           // wysoko�� na kt�rej znajduje si� podstawa obiektu
	float front_axis_dist;           // odleg�o�� od przedniej osi do przedniego zderzaka 
	float back_axis_dist;             // odleg�o�� od tylniej osi do tylniego zderzaka	
	float steer_wheel_ret_speed;    // pr�dko�� powrotu kierownicy po puszczeniu

public:
	MovableObject();          // konstruktor
	~MovableObject();
	void ChangeState(ObjectState state);          // zmiana stateu obiektu
	ObjectState State();        // metoda zwracajaca state obiektu
	void Simulation(float dt);  // symulacja ruchu obiektu w oparciu o biezacy state, przylozone sily
	// oraz czas dzialania sil. Efektem symulacji jest nowy state obiektu 
	void DrawObject();			   // odrysowanie obiektu					
};

// Klasa opisuj�ca env, po kt�rym poruszaj� si� obiekty
class Environment
{
public:
	float **height_map;          // wysoko�ci naro�nik�w oraz �rodk�w p�l
	float ***d;            // warto�ci wyrazu wolnego z r�wnania p�aszczyzny dla ka�dego tr�jk�ta
	Vector3 ***Norm;       // normalne do p�aszczyzn tr�jk�t�w
	float field_size;    // length boku kwadratowego pola na mapie
	long number_of_rows, number_of_columns; // liczba wierszy i kolumn mapy (kwadrat�w na wysoko�� i szeroko��)     
	Environment();
	~Environment();
	float DistFromGround(float x, float z);      // okre�lanie wysoko�ci dla punktu o wsp. (x,z) 
	void Draw();	                      // odrysowywanie envu   
	void DrawInitialisation();               // tworzenie listy wy�wietlania
	int ReadMap(char filename[128]);
};
