#include <bits/stdc++.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    std::cout << ".intel_syntax noprefix" << std::endl;
    std::cout << ".global main" << std::endl;
    std::cout << "main:" << std::endl;
    std::cout << "  mov rax, " << std::atoi(argv[1]) << std::endl;
    std::cout << "  ret" << std::endl;
    return 0;
}