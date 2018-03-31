// CMPE 225 GAME				Prepared by:
                                //Burak CANBAZ     150308024
#include <iomanip>              //Onur KARTAL      150308027
#include "stdafx.h"             //Can �smail ���Z  150308006
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <time.h>
using namespace std;
#include "Enemy.h"
#include "GameObject.h"
#include "Player.h"
#include "Character.h"
#include "FinishPoint.h"
#include "Gold.h"
int sign1(int num)                  //Bize uzakl�k i�in positif bir de�er d�nd�r�yor.//
{
	return num < 0 ? num*(-1) : num;
}

bool uzakl�k(Player oyuncu, int i, int j)    //Uzakl���n x ve y kordinatlar�n� hesapl�yor.//
{
	int xuz, yuz;
	xuz = sign1(oyuncu.getxcoordinate() - i);
	yuz = sign1(oyuncu.getycoordinate() - j);
	return (xuz <= 1 && yuz <= 1);
}
void sis(int &x, int &y, int hareket)
{
	switch (hareket)		// Bu k�s�mda e�er ekran�n en son k�sm�na gelinirse karakteri ayn� do�rulta en ba�a yada sona atmak i�in bize de�er �retiyorr//
	{												
	case 1:
		x = (x - 1 + 10) % 10;
		break;
	case 2:
		x = (x + 1 + 10) % 10;
		break;
	case 3:
		y = (y + 1 + 10) % 10;
		break;
	case 4:
		y = (y - 1 + 10) % 10;
		break;
	}
}
void hareket(Player &oyuncu, int hareket)
{
	int x, y;
	x = oyuncu.getxcoordinate();
	y = oyuncu.getycoordinate();					//Bu fonksiyon bir �st fonksiyonda �retti�imiz de�ere g�re bizim hareketimizi sa�l�yor//
	sis(x, y, hareket);								
	oyuncu.setxcoordinate(x);
	oyuncu.setycoordinate(y);
}


int pvsdsvs(Player *oyuncu, Enemy *enemy)
{
	int  d,a = 0,t;
	int flag = 0;
	double odamage,edamage, ohealth, oarm;
	ohealth = oyuncu->gethealth();									//Bu fonksiyon bizim sava� dinamiklerimizi i�eriyor.Oyuncunun yada d��man�n can�na
	oarm = oyuncu->getarmor();										//g�re d�nen bir d�ng�m�z var kullan�c�ya se�enek sunuyor ve ona g�re gerekli i�lemleri uyguluyor.
	enemy->information();											//Daha sonras�nda d��man�n nas�l bir hamle yapaca��na karar veren fonksiyon �a��r�l�yor.
	while (oyuncu->gethealth()>0 && enemy->gethealth()>0)			//Bu i�lem iki taraftan birisi �l�nceye kadar devam ediyor.E�er d��man �l�rse d��man�n rondom olarak atanm�� 
		                                                            //experience de�erini kendi experience miktar�m�za ekliyoruz.Bunun yan�nda pot kazanma �ans�m�z� kontrol ediyoruz.
	{
		cout << endl;
		cout << "1 for ATTACK , 2 to DRINK POTION:  ";
		cin >> flag;
		switch (flag)
		{
		case 1:
			odamage = oyuncu->attack();
			enemy->takedamage(odamage);
			if (enemy->gethealth() <= 0)
			{
				enemy->sethealth(0);
			}cout << endl << "You applied: " << odamage << " to the enemy. Enemy's current health: " << enemy->gethealth() << endl;
			
			break;
		
		case 2:
		
			oyuncu->drinkpotion();
			break;
		}
		if (enemy->gethealth() > 0) {
			d = enemy->decideaction();
			if (d == 1) {
				edamage = enemy->enemyatack();
				oyuncu->takedamage(edamage);
				if (oyuncu->getisalive()!=true)
				{
					oyuncu->sethealth(0);
				}
				cout << endl << "Enemy ATTACK applied: " << edamage << " To the player. Player's current health: " << oyuncu->gethealth() << endl;

			}
			else if (d == 2)
			{
				if (enemy->getpotioncount() > 0) {
					enemy->drinkpotion();
				}

				else if (enemy->getpotioncount() <= 0) {
					cout << "Enemy decided to ATACK" << endl;
					edamage = enemy->enemyatack();
					oyuncu->takedamage(edamage);
					cout << endl << "Enemy applied: " << edamage << " To the player. Player's current health: " << oyuncu->gethealth() << endl;

				}
			}
		}
	}
			
	if (enemy->getisalive()==false)
	{
		cout << endl << "Your enemy has perished from this world" << endl;
		oyuncu->setexperience(oyuncu->getexperience() + enemy->getexperienceamount());
		
		t = rand() % 100 + 1;
		if (t <= 30) {
			oyuncu->setpotioncount(oyuncu->getpotioncount() + 1);
			cout << "----YOU EARN 1 POTION---";
		}
		cout << "Player Winnnn you collect experience.";
		oyuncu->levelup();
		oyuncu->setarmor(0);
		return a+1;

	}
	else if (oyuncu->getisalive()==false)
	{
		cout << "You have perished from this world, Game over!!!" << endl;
		return a;
	}

}


int kontrol(Player &oyuncu, int hareket, Character *map[10][10], int &gold) //Haritada bo� alan�,d��man�,biti� noktas�n� ve alt�n� kontrol ediyoruz.Biti� noktas� ise yeni har�tada y�kleniyor.
{                                                                            //Alt�n ise oyuncunun alt�n say�s� art�yor.D��mansa pvsdsvs fonksiyonunu �a��r�p d��manla sava��yor.
	char choose;
	int x, y,a;
	x = oyuncu.getxcoordinate();
	y = oyuncu.getycoordinate();
	sis(x, y, hareket);
	char sembol;
	sembol = map[x][y]->getsign();
	switch (sembol)
	{
	case 'E':
		while (true)
		{
			cout << "Do you want to fight the enemy?Y/N";
			cin >> choose;
			if (choose == 'Y')
			{
				int dvs; 
				Character *map1 = map[x][y];
				Enemy *enemy = dynamic_cast<Enemy*>(map1);
				dvs = pvsdsvs(&oyuncu, enemy);
				
			
				if (dvs == 1)
				{
					
					
					
					system("pause");
					
					map1->setsign('-');
					a = 1;
					break;
				}
				else if (dvs == 0)
				{
					system("pause");
					
					a = 0;
					break;
				}
				break;

			}
			else if (choose == 'N')
			{
				
				a = 5;

				break;
			}
		}
		return a;
		break;
	case 'G':
	{
		Character *map2 = map[x][y];
		Gold *gold1 = dynamic_cast<Gold*>(map2);
		gold = gold1->getgoldamount();
		oyuncu.setgoldcount(oyuncu.getgoldcount() + gold);
		map[x][y] = new Character('-');
		return 2;
	}
	break;
	case'F':
	{	oyuncu.setlevel(oyuncu.getlevel() + 1);
	cout << "Level up!!!" << endl;
	return 3;
	}
	break;
	default:
		return 1;
		break;
	}
}
void showmap(Character *map[10][10], Player oyuncu)  //File'dan al�nan mapi ekrana yazd�r�yoruz.
{
	int pxcor,pycor;
	pxcor = oyuncu.getxcoordinate();
	pycor = oyuncu.getycoordinate();
	cout << setw(22) << "Level:" << oyuncu.getlevel()<<endl;
	cout << setw(10) << " ";
	for (int i = 0; i < 10; i++)
	{
		cout << "- ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << setw(10) << "|";
		for (int j = 0; j < 10; j++)
		{
			if (i == pxcor&&j == pycor)
			{
				cout << oyuncu.getsign() << " ";
			}
			else if (uzakl�k(oyuncu, i, j))
			{
				cout << map[i][j]->getsign()<<" ";
			}
			else
			{
				cout << "#" << " ";
			}
		}
		cout << "|" << endl;
	}
	cout << setw(10) << " ";
	for (int i = 0; i < 10; i++)
	{
		cout << "- ";
	}
	cout << endl;
}






int main()
{
	srand(time(NULL));
	char sign1;
	ifstream fin("map.txt");
	Character *map[10][10];
	Player oyuncu('P', 9, 0);
	oyuncu.setpotioncount(5);
	oyuncu.setlevel(1);
	oyuncu.setisalive(true);
	int potamount, gldcost;
	int girdi = 1, check = 1;
	int gold;
	FinishPoint fp('F', 0, 9);
	oyuncu.setmaxhealth(1000);
	oyuncu.sethealth(1000);
	oyuncu.setarmor(20);
	oyuncu.setexperience(0);
	oyuncu.setdamage(100);
	oyuncu.setgoldcount(2000);
	oyuncu.settolevelup(2000);
	oyuncu.setcritchance(8.5);
	
	
	for (int i = 0; i < 10; i++)
	{                                                      //File'dan haritay� al�yoruz.
		for (int j = 0; j < 10; j++)
		{
			fin >> sign1;
			if (sign1 == 'E') {
				int hlth, crt,pt,exp;
				hlth = 500 + rand() % 500 + 1;
				crt = rand() % 100+1;
				pt = rand() % 3 + 1;
				exp = 300 + rand() % 200 + 1;
				map[i][j] = new Enemy('E', hlth, 20, 50, crt,pt,exp);
			}
			else if (sign1 == 'G') {
				int gldmnt;
				gldmnt = 300 + rand() % 201;
				map[i][j] = new Gold('G', gldmnt);
			}
			else if (sign1 == 'F') {
				map[i][j] = new FinishPoint('F', i, j);


			}
			else if (sign1 == '-') {
				map[i][j] = new Character('-');


			}
		}

	}
	showmap(map, oyuncu);
	cout << endl;
	while (girdi!= 6)
	{
		cout <<endl<<endl<< "Enter 1 to move up, 2 to move down, 3 to move right, 4 to move left, 5 to player's information ,6 to exit: ";
		cin >> girdi;
		if (girdi == 5)
		{
			oyuncu.information();
			continue;
		}
		if (girdi == 6)
		{
			system("CLS");
			cout << "Exited.." << endl;
			system("pause");
			break;
		}
		check = kontrol(oyuncu, girdi, map, gold);
		if (check == 0)
		{
			cout << endl << "YOU DIED!!!" << endl;
			system("pause");
			return(0);
		}
		else if (check == 1 || check == 2)
		{
			hareket(oyuncu, girdi);
			system("CLS");
		}
		showmap(map, oyuncu);
		if (check == 2)
		{
			cout << endl << "Gold collected: " << oyuncu.getgoldcount() << endl;
		}
		if (check == 3)
		{
			system("CLS");
			cout<< "---------------NEW MAP EXECUTED---------------" << endl<< endl << endl << endl << endl;
			oyuncu.setxcoordinate(10 - 1);
			oyuncu.setycoordinate(0);

			showmap(map, oyuncu);
		}
		if (check == 5)
		{
			system("CLS");
			showmap(map, oyuncu);
		}


	}

	fin.close();
	return 0;
}