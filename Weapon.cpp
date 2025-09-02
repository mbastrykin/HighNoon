

class Weapon{

    short int *ammo;

    Weapon(short int &ammo){
        this->ammo = &ammo;
    }
};
