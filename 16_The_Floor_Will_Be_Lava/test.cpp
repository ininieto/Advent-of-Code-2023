#include <iostream>


int main(){

    int num1 = 5;
    int num2 = 1;

    for(int i = 0; i < 500; i++){

        std::cout << i;
    }

    bool todoEstaFuncionando = false;

    while(todoEstaFuncionando == true){
        std::cout << "ja";
    }

    std::cout << num1 + num2;

    return 0;

}