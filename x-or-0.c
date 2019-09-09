#include "Header.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main(void)
{
    srand((unsigned) time(&t));
    struct player number[NUM];
    b_fill(b);
    registration(number); //Ввод имён и выбор первым игроком крестиков или ноликов
    first = (rand() % 2 + 1);
    printf("%s goes first according to a random choice!\n\n",
           number[first - 1].name);
    decorations(a); //Вывод поля игры
    
    for (i = 0; i < FIELDS; i++)
    {
        printf("%s, enter your step:\n", number[first - 1].name);
        printf("Line: ");
        line = read_step(1);
        printf("Row: ");
        row = read_step(2);
        if (b[line - 1][row - 1])
        {
            do
            {
                puts("This field is not empty! Try another one:");
                printf("Line: ");
                line = read_step(1);
                printf("Row: ");
                row = read_step(2);
            } while (b[line - 1][row - 1]);
        }
        b[line - 1][row - 1] = first;
        steps += 1;
        printf("\nPlayers made %d step%s\n", steps, (steps == 1) ? "" : "s");
        a[change(line)][change(row)] = filling_in(number, first);
        output(a);
        first = change_choice(first);
        switch(situation_analyze(b))
        {
            case 1: //Игрок 1 победил
            {
                printf("%s won! Thanks for the game! Hope to see you soon! :)\n", number[0].name); getchar(); exit(0);
            }
            case 2: //Игрок 2 победил
            {
                printf("%s won! Thanks for the game! Hope to see you soon! :) \n", number[1].name); getchar(); exit(0);
            }
            default: //Ничья
            {
                if ((steps == FIELDS) && (!(situation_analyze(b))))
                {
                    puts("Draw! Thank you for the game! Hope to see you soon :)\n"); getchar(); exit(0);
                }
            }
        }
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
