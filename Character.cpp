#include "stdafx.h"
#include "Character.h"
#include <iomanip>
void Character::takedamage(double damageamount) {    //Al�nan zarara g�re armordan kontrol edip sa�l�ktan d���r�l�yor.
	                                                 
	if (armor > 0) {
		armor =armor-damageamount;
		health = health + armor;
	}
	else if (armor <= 0) {
		health = health - damageamount;
		}


}
void Character::drinkpotion() {}

void Character::sethealth(double h) {
	health = h;
}
double Character::gethealth() {
	return health;
}
void Character::setmaxhealth(double mh) {
	maxhealth = mh;
}
double Character::getmaxhealth() {
	return maxhealth;
}
void Character::setarmor(double a) {
	armor = a;
}
double Character::getarmor() {
	return armor;
}
void Character::setdamage(double d) {
	damage = d;
}
double Character::getdamage() {
	return damage;
}
void Character::setcritchance(double cc) {
	critchance = cc;
}
double Character::getcritchance() {
	return critchance;
}
void Character::setpotioncount(int p) {

	potioncount = p;
}
int Character::getpotioncount() {
	return potioncount;
}
void Character::setisalive(bool ia) {
	isalive = ia;
}
bool Character::getisalive() {  //Karakterlerin ya�ay�p ya�amad���n� kontrol ediyoruz,bool bir de�er g�nderiliyor.
	if (health > 0) {
		return true;
	}
	else if(health<=0){
		return false;
	}
}

Character::Character()
{
}

Character::Character(char sgn)
{
	sign = sgn;
}
Character::~Character()
{
}
