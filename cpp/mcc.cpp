#include <bits/stdc++.h>

enum class TokenKind
{
    TK_RESERVED,
    TK_NUM,
    TK_EOF,
};

class Token
{
public:
    TokenKind kind;
    Token *next;
    int val;
    std::string str;
};

Token *token;

void error(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

bool consume(char op)
{
    if (token->kind != TokenKind::TK_RESERVED || token->str[0] != op)
    {
        return false;
    }
    token = token->next;
    return true;
}

void expect(char op)
{
    if (token->kind != TokenKind::TK_RESERVED || token->str[0] != op)
    {
        error("'%c'ではありません。", op);
    }
    token = token->next;
}

int expect_number()
{
    if (token->kind != TokenKind::TK_NUM)
    {
        error("数ではありません");
    }
    int val = token->val;
    token = token->next;
    return val;
}

bool at_eof()
{
    return token->kind == TokenKind::TK_EOF;
}

Token *new_token(TokenKind kind, Token *cur, char *str)
{
    Token *tok = new Token();
    tok->kind = kind;
    tok->str = str;
    cur->next = tok;
    return tok;
}

Token *tokenize(char *p)
{
    Token head;
    head.next = NULL;
    Token *cur = &head;

    while (*p)
    {
        if (isspace(*p))
        {
            p++;
            continue;
        }

        if (*p == '+' || *p == '-')
        {
            cur = new_token(TokenKind::TK_RESERVED, cur, p++);
            continue;
        }

        if (isdigit(*p))
        {
            cur = new_token(TokenKind::TK_NUM, cur, p);
            cur->val = strtol(p, &p, 10);
            continue;
        }

        error("トークナイズできません");
    }
    new_token(TokenKind::TK_EOF, cur, p);
    return head.next;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    token = tokenize(argv[1]);

    // char *p = argv[1];

    std::cout << ".intel_syntax noprefix" << std::endl;
    std::cout << ".global main" << std::endl;
    std::cout << "main:" << std::endl;

    std::cout << "  mov rax, " << expect_number() << std::endl;

    while (!at_eof())
    {
        if (consume('+'))
        {
            std::cout << "  add rax, " << expect_number() << std::endl;
            continue;
        }
        expect('-');
        std::cout << "  sub rax, " << expect_number() << std::endl;
    }

    std::cout << "  ret" << std::endl;
    return 0;
}