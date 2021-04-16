#include <future>
#include <cstdio>
#include <graphics.h>
#include <thread>

void gerak2()
{
    int xpos = 10, ypos = 330;
    for (int i = 0; i < 400; i++)
    {
        circle(i, ypos, 40);
        delay(7);
        cleardevice();
        if (i == 100)
        {
            break;
        }
    }
}
void gerak()
{
    int xpos = 300, ypos = 10;
    for (int i = 0; i < 400; i++)
    {
        circle(xpos, i, 40);
        delay(7);
        cleardevice();
        // std::future<void> fut = std::async(std::launch::deferred, gerak2);
        // fut.get();
    }
}

void infinity()
{
    while (1)
    {
        circle(100, 100, 30);
    }
}
int main()
{
    int xpos = 300, ypos = 10;
    initwindow(400, 400);

    while (!kbhit())
    {
        std::thread t1(gerak);
        std::thread t2(gerak2);
        std::thread t3(infinity);
        t1.join();
        t2.join();
        // delay(1000);
        t3.join();
        // gerak();
        // ypos++;
        // circle(100, 100, 30);
        // std::async(std::launch::async, infinity);
        // std::async(std::launch::async, circle, 100, 100, 30);
        // // circle(xpos, ypos, 40);
        // std::async(std::launch::async, gerak);
        // gerak();
        delay(10);
        cleardevice();
    }
    closegraph();
    return 0;
}
