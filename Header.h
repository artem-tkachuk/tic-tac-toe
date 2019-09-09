#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define Header_h
#define N 5
#define NUM 2
#define MAX 30
#define FIELDS 9
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct player
{
    char name[MAX];
    int choice;
};
int i, j, result;
char a[N][N];
int b[N - 2][N - 2];
time_t t;
int first_choice;
int steps = 0;
int line, row;
int first;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void output(char a[N][N]);
void first_fill(char a[N][N]);
void b_fill(int b[N - 2][N - 2]);
char * s_gets(char * s, unsigned short k);
void eatline(void);
int x_or_o(void);
void enter_name(unsigned short l);
struct player registration(struct player number[NUM]);
void decorations(char a[N][N]);
int scan_int(void);
int situation_analyze(int b[N - 2][N - 2]);
int read_step(int n);
int change(int a);
int change_choice(int a);
char filling_in(struct player * number, int first);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void menu(void)
{
    puts("Welcome to\"X - 0\" game! At first, please, enter players' names "
         "and then choose X or 0 for the first player!");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void output(char a[N][N])
{

    for (i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            printf("%4c", a[i][j]);
        puts("\n");
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void first_fill(char a[N][N])
{
    for (i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            a[i][j] = ' ';
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void decorations(char a[N][N])
{
    first_fill(a);
    for (i = 1; i < N; i += 2)
    {   for (j = 0; j < N; j++)
        a[i][j] = '-';
    }
    for (j = 1; j < N; j += 2)
    {
        for (i = 0; i < N; i++)
            a[i][j] = '|';
    }
    output(a);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void enter_name(unsigned short l)
{
    printf("Enter %hu%s player's name:\n", l, (l == 1) ? "st" : "nd");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct player registration(struct player number[NUM])
{
    menu();

    enter_name(1);
    s_gets(number[0].name, MAX);
    number[0].choice = x_or_o();

    enter_name(2);
    s_gets(number[1].name, MAX);
    number[1].choice = (number[0].choice == 1) ? 2 : 1;
    printf("Well, %s, You play with %s, and %s plays with %s.\n\nWarning! Players"
           " should enter their steps horizonatlly and then vertically "
           "(At First enter line, press [Enter], enter row, "
           "tab [Enter])\n\n", number[0].name,
           (number[0].choice == 1) ? "X" : "0", number[1].name,
           (number[1].choice == 1) ? "X" : "0");
    puts("Let's begin!\n");
    return *number;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int x_or_o(void)
{
    int k;
    puts("Enter 1 to play with X and 2 to play with 0:");
    k = scan_int();
    while ((k != 1) && (k != 2))
    {
        k = scan_int();
    }
    if (k == 1)
        return 1;
    else
        return 2;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
char * s_gets(char * s, unsigned short k)
{
    char * ret_val;
    char * find;

    ret_val = fgets(s, k, stdin);
    if (ret_val)
    {
        find = strchr(s, '\n');
        if (find)
            *find = '\0';
        else
            eatline();
    }
    return ret_val;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eatline(void)
{
    while (getchar() != '\n')
        continue;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int scan_int(void)
{
    char s[N];
    s_gets(s, N);
    int l = atoi(s);
    if ((l == 1) || (l == 2))
        return l;
    else
    {
        do
        {
            puts("You didn't enter 1 or 2! Please, try again!\n"
            "Enter 1 to play with X and 2 to play with 0:");
            s_gets(s, N);
            l = atoi(s);

        } while ((l != 2) && (l != 1));
        return l;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int situation_analyze(int b[N - 2][N - 2])
{
    if (((b[0][0] == 1) && (b[0][1] == 1) && (b[0][2] == 1)) ||
        ((b[1][0] == 1) && (b[1][1] == 1) && (b[1][2] == 1)) ||
        ((b[2][0] == 1) && (b[2][1] == 1) && (b[2][2] == 1)) ||
        ((b[0][0] == 1) && (b[1][0] == 1) && (b[2][0] == 1)) ||
        ((b[0][1] == 1) && (b[1][1] == 1) && (b[2][1] == 1)) ||
        ((b[0][2] == 1) && (b[1][2] == 1) && (b[2][2] == 1)) ||
        ((b[0][0] == 1) && (b[1][1] == 1) && (b[2][2] == 1)) ||
        ((b[0][2] == 1) && (b[1][1] == 1) && (b[2][0] == 1)))
            return 1; //Выигрывает первый игрок
    else if (((b[0][0] == 2) && (b[0][1] == 2) && (b[0][2] == 2)) ||
             ((b[1][0] == 2) && (b[1][1] == 2) && (b[1][2] == 2)) ||
             ((b[2][0] == 2) && (b[2][1] == 2) && (b[2][2] == 2)) ||
             ((b[0][0] == 2) && (b[1][0] == 2) && (b[2][0] == 2)) ||
             ((b[0][1] == 2) && (b[1][1] == 2) && (b[2][1] == 2)) ||
             ((b[0][2] == 2) && (b[1][2] == 2) && (b[2][2] == 2)) ||
             ((b[0][0] == 2) && (b[1][1] == 2) && (b[2][2] == 2)) ||
             ((b[0][2] == 2) && (b[1][1] == 2) && (b[2][0] == 2)))
        return 2; //Выигрывает второй игрок
    else
        return 0; //Ничья
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void b_fill(int b[N - 2][N - 2])
{
    for (i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            b[i][j] = 0;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int read_step(int n)
{
    char s[N];
    s_gets(s, N);
    int l = atoi(s);
    if ((l == 1) || (l == 2) || (l == 3))
        return l;
    else
    {
        do
        {
            printf("You didn't enter 1, 2 or 3! Please, try"
                   "again!\n%s", (n == 1) ? "Line: " : "Row: ");
            s_gets(s, N);
            l = atoi(s);
        } while ((l != 2) && (l != 1) && (l != 3));
        return l;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int change(int a)
{
    if (a == 1)
        return (a - 1);
    else if (a == 3)
        return (a + 1);
    else
        return a;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int change_choice(int a)
{
    if (a == 1)
        return 2;
    else
        return 1;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
char filling_in(struct player * number, int first)
{
    if (number[first - 1].choice == 1)
        return 'X';//filling_in()
    else
        return '0';
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
