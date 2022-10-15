#include "header.h"

void createClient(){
    system("./cliente");
}

int main(int argc, char const *argv[])
{
    vector <thread> threads;
    for (size_t i = 0; i < 9; i++)
    {
        threads.push_back(thread(createClient));
    }

    for (unsigned int i = 0; i < 9; i++)
	{
		threads[i].join();
	}
    
    return 0;
}
