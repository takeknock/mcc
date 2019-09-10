#include <bits/stdc++.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    char *p = argv[1];

    std::cout << ".intel_syntax noprefix" << std::endl;
    std::cout << ".global main" << std::endl;
    std::cout << "main:" << std::endl;
    std::cout << "  mov rax, " << std::strtol(p, &p, 10) << std::endl;

    while (*p)
    {
        if (*p == '+')
        {
            p++;
            std::cout << "  add rax, " << std::strtol(p, &p, 10) << std::endl;
            continue;
        }
        if (*p == '-')
        {
            p++;
            std::cout << "  sub rax, " << std::strtol(p, &p, 10) << std::endl;
            continue;
        }

        std::fprintf(stderr, "予期しない文字です: '%c'\n", *p);
        return 1;
    }

    std::cout << "  ret" << std::endl;
    return 0;
}