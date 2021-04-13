#include <graphics.h>
#include <iostream>

using namespace std;

void gerak_pemain(int *x_awal, int *y_awal)
{
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        while (1)
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
            getmouseclick(WM_MOUSEMOVE, *x_awal, *y_awal);

            delay(300);
        }
    }
    cleardevice();
}

class main_char
{
private:
    int *x_pos_address;
    int *y_pos_address;
    int *size_address;
    int *hitpoints;

public:
    main_char(int *x, int *y, int *size, int *HP)
    {
        x_pos_address = x;
        y_pos_address = y;
        size_address = size;
        hitpoints = HP;
    }
    void set_pos(int x_pos, int y_pos)
    {
        *x_pos_address = x_pos;
        *y_pos_address = y_pos;
    }
    void get_pos(int *x_pos_target, int *y_pos_target)
    {
        *x_pos_target = *x_pos_address;
        *y_pos_target = *y_pos_address;
    }
    void move(int jarak_x, int jarak_y)
    {
        *x_pos_address += jarak_x;
        *y_pos_address += jarak_y;
    }
};

main()
{
    int x = 30, y = 30, xbenda = 150, ybenda = 150, size = 20, HP = 100;
    bool klik;
    // initwindow(500, 500);x
    // circle(xbenda, ybenda, 20);
    // while (!kbhit())
    // {

    //     gerak_pemain(&xbenda, &ybenda);
    //     circle(xbenda, ybenda, 20);
    // }
    // closegraph();

    // main_char AWM462(&x, &y, &size, &HP);
    // cout << "x = " << x << ", y = " << y << ", size = " << size << endl;
    // AWM462.move(20, 40);
    // cout << "x = " << x << ", y = " << y << ", size = " << size << endl;
}
