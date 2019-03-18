#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct NodeDesc *Node;
typedef struct NodeDesc
{
    char kind;        // plus, minus, times, divide, number, var
    int val;          // number: value
    Node left, right; // plus, minus, times, divide: children
} NodeDesc;
static FILE *f, *o;
static int ch;
static unsigned int val;
enum
{
    plus,
    minus,
    times,
    divide,
    mod,
    lparen,
    rparen,
    number,
    var,
    eof,
    illegal
};
static void SInit(char *input, char *output)
{
    ch = EOF;
    f = fopen(input, "r+t");
    o = fopen(output, "w+");
    if (f != NULL)
        ch = getc(f);
}
static void Number()
{
    val = 0;
    while (('0' <= ch) && (ch <= '9'))
    {
        val = val * 10 + ch - '0';
        ch = getc(f);
    }
}
static int SGet()
{
    register int sym;

    while ((ch != EOF) && (ch <= ' '))
        ch = getc(f);
    switch (ch)
    {
    case EOF:
        sym = eof;
        break;
    case '+':
        sym = plus;
        ch = getc(f);
        break;
    case '-':
        sym = minus;
        ch = getc(f);
        break;
    case '*':
        sym = times;
        ch = getc(f);
        break;
    case '/':
        sym = divide;
        ch = getc(f);
        break;
    case '%':
        sym = mod;
        ch = getc(f);
        break;
    case '(':
        sym = lparen;
        ch = getc(f);
        break;
    case ')':
        sym = rparen;
        ch = getc(f);
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        sym = number;
        Number();
        break;
    default:
        sym = illegal;
    }
    return sym;
}
static int sym;
static Node Expr();
static Node Factor()
{
    register Node res;
    assert((sym == number) || (sym == var) || (sym == lparen));
    if (sym == number)
    {
        res = malloc(sizeof(NodeDesc));
        res->kind = number;
        res->val = val;
        res->left = NULL;
        res->right = NULL;
        sym = SGet();
    }
    else if (sym == var)
    {
        res = malloc(sizeof(NodeDesc));
        res->kind = var;
        res->val = -1;
        res->left = NULL;
        res->right = NULL;
        sym = SGet();
    }
    else
    {
        sym = SGet();
        res = Expr();
        assert(sym == rparen);
        sym = SGet();
    }
    return res;
}
static Node Term()
{
    register Node root, res;

    root = Factor();
    while ((sym == times) || (sym == divide) || (sym == mod))
    {
        res = malloc(sizeof(NodeDesc));
        res->kind = sym;
        res->val = -1;
        sym = SGet();
        res->left = root;
        res->right = Factor();
        root = res;
    }
    return root;
}
static Node Expr()
{
    register Node root, res;

    root = Term();
    while ((sym == plus) || (sym == minus))
    {
        res = malloc(sizeof(NodeDesc));
        res->kind = sym;
        res->val = -1;
        sym = SGet();
        res->left = root;
        res->right = Term();
        root = res;
    }
    return root;
}
static void AsmGenerator(Node root)
{
    if (root != NULL)
    {
        AsmGenerator(root->left);
        AsmGenerator(root->right);
        switch (root->kind)
        {
        case plus:
            // printf("lw $t0, 4($sp)\n");
            // printf("add $a0, $t0, $a0\n");
            // printf("addiu $sp, $sp, 4\n");
            fputs("lw $t0, 4($sp)\r\n", o);
            fputs("add $a0, $t0, $a0\r\n", o);
            fputs("addiu $sp, $sp, 4\r\n", o);
            break;
        case minus:
            // printf("lw $t0, 4($sp)\n");
            // printf("sub $a0, $t0, $a0\n");
            // printf("addiu $sp, $sp, 4\n");
            fputs("lw $t0, 4($sp)\r\n", o);
            fputs("sub $a0, $t0, $a0\r\n", o);
            fputs("addiu $sp, $sp, 4\r\n", o);
            break;
        case times:
            // printf("lw $t0, 4($sp)\n");
            // printf("mul $a0, $t0, $a0\n");
            // printf("addiu $sp, $sp, 4\n");
            fputs("lw $t0, 4($sp)\r\n", o);
            fputs("mul $a0, $t0, $a0\r\n", o);
            fputs("addiu $sp, $sp, 4\r\n", o);
            break;
        case divide:
            // printf("lw $t0, 4($sp)\n");
            // printf("div $t0, $a0\n");
            // printf("mflo $a0\n");
            // printf("addiu $sp, $sp, 4\n");
            fputs("lw $t0, 4($sp)\r\n", o);
            fputs("div $t0, $a0\r\n", o);
            fputs("mflo $a0\r\n", o);
            fputs("addiu $sp, $sp, 4\r\n", o);
            break;
        case mod:
            // printf("lw $t0, 4($sp)\n");
            // printf("div $t0, $a0\n");
            // printf("mfhi $a0\n");
            // printf("addiu $sp, $sp, 4\n");
            fputs("lw $t0, 4($sp)\r\n", o);
            fputs("div $t0, $a0\r\n", o);
            fputs("mfhi $a0\r\n", o);
            fputs("addiu $sp, $sp, 4\r\n", o);
            break;
        case number:
            // printf("sw $a0, 0($sp)\n");
            // printf("addiu $sp, $sp, -4\n");
            // printf("li $a0, %d\n", root->val);
            fputs("sw $a0, 0($sp)\r\n", o);
            fputs("addiu $sp, $sp, -4\r\n", o);
            fputs("li $a0, ", o);
            fprintf(o, "%d", root->val);
            fputs("\r\n", o);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    register Node result;

    if (argc == 3)
    {
        SInit(argv[1], argv[2]);
        sym = SGet();
        result = Expr();
        assert(sym == eof);
        fclose(f);
        fputs(".text # text section\r\n", o);
        fputs(".globl main # call main by SPIM\r\n", o);
        fputs("main:\r\n", o);
        AsmGenerator(result);
        fputs("li $v0, 1 # for printing an integer result\r\n", o);
        fputs("syscall # for printing an integer result\r\n", o);
        fputs("li $v0, 10 # for correct exit (or termination)\r\n", o);
        fputs("syscall # for correct exit (or termination)\r\n", o);
        fclose(o);
    }
    else
    {
        printf("usage: expreval <filename>\n");
    }
}