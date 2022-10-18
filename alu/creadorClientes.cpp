#include "header.h"

void createClient(int numero){
    std::string comando = "./cliente ";
    comando += std::to_string(numero);
    system(comando.c_str());
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    vector <thread> threads;
    for (size_t i = 0; i < 9; i++)
    {
        threads.push_back(thread(createClient, rand()));
    }

    for (unsigned int i = 0; i < 9; i++)
	{
		threads[i].join();
	}
    
    return 0;
}
