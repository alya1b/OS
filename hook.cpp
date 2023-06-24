#include <iostream>
#include <fstream>
#include <linux/input.h>

int main()
{
    std::string device = "/dev/input/event4";
    std::ifstream input(device, std::ios::binary);

    if (!input)
    {
        std::cerr << "Failed to open device: " << device << std::endl;
        return 1;
    }

    input_event ev;
    while (true)
    {
        if (input.read(reinterpret_cast<char*>(&ev), sizeof(ev)))
        {
            if (ev.type == EV_KEY && ev.value == 1)
            {
                std::cout << "Key pressed: " << ev.code << std::endl;
            }
        }
    }

    input.close();

    return 0;
}
