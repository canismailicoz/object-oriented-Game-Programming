#include "stdafx.h"
#include "Player.h"
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;


double Player::attack() {    //Karakterimizin kritik �ans�n� kontrol edip,ona g�re bir hasar g�nderiyoruz.
	double num;


	num = rand() % 100 ;
	if (num <=getcritchance()) {
		cout <<endl<<endl<< "#####Critical Attack#####" << endl << endl;
		return (getdamage()*2);

	}
	else {
		return (getdamage());
	}

}

void Player::information() { //Karakterin bilgileri ekrana bast�r�l�yor.
	cout <<endl<<endl<<endl<<"Player Level is:" << getlevel() << endl;
	cout << "Experience is:" << getexperience() << endl;
	cout << "Maxhealth:" << getmaxhealth() << endl;
	cout << "Health is:" << gethealth() << endl;
	cout << "Armor is:" << getarmor() << endl;
	cout << "Damage is:" << getdamage() << endl;
	cout << "Potions is:" << getpotioncount()<<endl;
	cout << "Gold count is: " << getgoldcount() << endl << endl << endl;

}
void Player::drinkpotion() { // Elimizdeki pot say�s�n� kontrol edip,e�er potumuz varsa sa�l���m�z� 500 artt�r�yoruz.


	if (getpotioncount() > 0) {
		sethealth(gethealth() + 500);
		if (gethealth() > getmaxhealth()) {
			sethealth(getmaxhealth());
		}
		setpotioncount(getpotioncount() - 1);
		cout << "Player health is: " << gethealth() <<endl<<"Remaining pot number is:"<<getpotioncount()<< endl;
	}

	
	else if (getpotioncount() <= 0){
		cout << "You have not anyy potion you must make atacak" << endl;
		attack();
		}
		
	}


void Player::addexperience(int e) {   //D��mana rondom atanm�� experience de�erini karakterimizin experience de�eriyle toplay�p,set ediyoruz.

	setexperience(getexperience() + e);



}
void Player::levelup() {    //Karakterin level atlamas� i�in gerekli olan experience de�erini kontrol edip,yeni level de�erlerini artt�r�p g�ncelliyoruz.
	int num2;

	if (getexperience() >= gettolevelup()) {

		num2 = getexperience() % gettolevelup();
		setlevel(getlevel() + 1);
		setexperience(num2);
		sethealth(gethealth() + 300);
		setmaxhealth(getmaxhealth() + 300);
		setarmor(getarmor() + 3);
		setcritchance(getcritchance() + 0.5);
		setdamage(getdamage() + 30);
		settolevelup(gettolevelup() + 1000);
		cout << "You have leveled up" << endl;
	}

}
void Player::setxcoordinate(int x) {
	xcoordinate = x;
}
int Player::getxcoordinate() {
	return xcoordinate;
}
void Player::setycoordinate(int y) {
	ycoordinate = y;
}
int Player::getycoordinate() {
	return ycoordinate;
}
void Player::setgoldcount(int gcc) {
	goldcount = gcc;
}
int Player::getgoldcount() {
	return goldcount;
}
void Player::setlevel(int l) {
	level = l;
}
int Player::getlevel() {
	return level;
}
void Player::setexperience(int ex) {
	experience = ex;
}
int Player::getexperience() {
	return experience;
}
void Player::settolevelup(int tlu) {
	tolevelup = tlu;
}
int Player::gettolevelup() {
	return tolevelup;
}
Player::Player()
{
}

Player::Player(char ps, int x, int y)
{
	sign = ps;
	xcoordinate = x;
	ycoordinate = y;
}


Player::~Player()
{
}
