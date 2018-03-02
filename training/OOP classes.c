#include <iostream>

class Aircraft {
private:
    int speed , mass , size;

public:
    Aircraft () {
        speed = 10;
        mass = 20;
        size = 15;
        get ();
        printf("\n");
    }
    void message () {
        printf ("it's working!!\n");
    }
    void set (int param_speed, int param_mass , int param_size) {
        speed = param_speed;
        mass = param_mass;
        size = param_size;
    }
    void get () {
        printf("%s%d%s%d%s%d\n","speed is ",speed,", mass is ",mass,", size is ",size);
    }
};

int main()
{
    Aircraft tu100;
    tu100.message();
    tu100.set (0,0,0);
    tu100.get ();
    Aircraft bullet;
    bullet.set (5000,2000,400);
    bullet.get();

    return 0;
}
