#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>

#define MAX 20 // Initialization of values
#define max_life_obj 5


typedef int paths[MAX][MAX]; // Declaration of type table
typedef int life[max_life_obj];
typedef char inv[max_life_obj];

int i, x, y, n, place_inv, xp_robot1, rep_ph;
bool exits, command_error;
char name[50], end_name[50], line_break;
life hearts = {1, 1, 0, 0, 0};
life around = {1,1,1,1};
inv inventory = {'n', 'n', 'n', 'n', 'n'};
char *filelang = "";

/* Creation of matrix */
paths labyrinth = {{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                   {3, 0, 3, 0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 3, 7, 0, 0, 3, 3, 3},
                   {3, 0, 3, 0, 9, 0, 0, 0, 3, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 3},
                   {3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 3, 0, 0, 3},
                   {3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
                   {3, 0, 0, 11, 3, 15, 3, 0, 3, 3, 3, 3, 3, 3, 9, 0, 0, 0, 3, 3},
                   {3, 0, 10, 0, 3, 3, 3, 0, 3, 0, 3, 0, 0, 14, 13, 0, 0, 3, 3, 3},
                   {3, 0, 3, 8, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 3, 3, 0, 0, 3, 3},
                   {3, 0, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 3},
                   {3, 0, 3, 0, 0, 0, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 0, 0, 0, 3},
                   {3, 0, 3, 3, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 3, 3, 3, 3},
                   {3, 0, 0, 0, 3, 8, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
                   {3, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 9, 3},
                   {3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 0, 0, 3},
                   {3, 3, 3, 0, 9, 0, 0, 0, 0, 0, 0, 0, 3, 9, 3, 3, 0, 0, 0, 3},
                   {3, 3, 0, 0, 0, 3, 3, 0, 5, 3, 3, 3, 3, 6, 3, 0, 0, 0, 0, 3},
                   {3, 3, 7, 0, 12, 0, 3, 0, 3, 3, 3, 0, 0, 0, 3, 0, 3, 3, 0, 3},
                   {3, 0, 0, 0, 3, 3, 3, 0, 0, 3, 0, 0, 3, 0, 3, 3, 3, 7, 0, 3},
                   {3, 2, 0, 3, 3, 0, 0, 0, 1, 0, 0, 3, 3, 0, 0, 0, 8, 0, 0, 3},
                   {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}};


/* Write a line of document text */
/* index : the number of the line and those should writen */
void display(int index)
{
    FILE *in_file = fopen(filelang, "r");

    struct stat sb;
    stat(filelang, &sb);

    char *file_contents = malloc(sb.st_size);

    for (i = 0; i < index; i++)
    {
        fscanf(in_file, "%[^\n] ", file_contents);
    }
    setlocale(LC_ALL, "");
    printf("%s\n", file_contents);

    fclose(in_file);
}

void display_no_n(int index)
{
    FILE *in_file = fopen(filelang, "r");

    struct stat sb;
    stat(filelang, &sb);

    char *file_contents = malloc(sb.st_size);

    for (i = 0; i < index; i++)
    {
        fscanf(in_file, "%[^\n] ", file_contents);
    }
    setlocale(LC_ALL, "");
    printf("%s", file_contents);

    fclose(in_file);
}

/* Permit forward in the matrix */
/* Decrease x of 1 */
void north()
{
    if (labyrinth[x - 1][y] == 4)
    {
        display(28);
    }

    else
    {
        x--;
    }
}

/* Permit backward in the matrix */
/* Increase x of 1 */
void south()
{
    if (labyrinth[x + 1][y] == 4)
    {
        display(28);
    }

    else
    {
        x++;
    }
}

/* Permit turn at left in the matrix */
/* Decrease y of 1 */
void west()
{
    if (labyrinth[x][y - 1] == 4)
    {
        display(28);
    }
    else
    {
        y--;
    }
}

/* Permit turn at right in the matrix */
/* Increase y of 1 */
void east()
{
    if (labyrinth[x][y + 1] == 4)
    {
        display(28);
    }

    else
    {
        y++;
    }
}

void error()
{
    display(29);
}

void break_lines()
{
    display(122);
    scanf("%c", line_break);
    getchar();
}

/* display wallaround the character */
void is_near(int i, int j)
{
    int i2, j2;
    for(i2 = i-1 ; i2 < i+2 ; i2++ )
    {
        for(j2 = j-1 ; j2 < j+2 ; j2++ )
        {
            if (labyrinth[i2][j2] == 3)
        {
            labyrinth[i2][j2] = 4;
        }
        }
    }
}

void display_map(bool exits)
{
    int i, j;
    is_near(x, y);
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
        {
            if (labyrinth[i][j] == 4)
            {
                printf("◘ "); // Walls
            }

            else if ((labyrinth[i][j] == 7 || labyrinth[i][j] == 2) && exits == true)
            {
                printf("♅ "); // Point of end if you find the compass
            }

            else if (i == x && j == y)
            {
                printf("웃");
            }

            else
            {
                printf("ㅤ");
            }
        }
        printf(" \n");
    }
}

/*Display the number of hearts you have*/
void disp_life()
{
    for (i = 0; i < max_life_obj; i++)
    {
        if (hearts[i] == 1)
        {
            printf("❤ ");
        }
        else
        {
            printf("♡ ");
        }
    }
    printf("\n");
}

void add_heart()
{
    i = 0;
    while (i != -1 && i < max_life_obj)
    {
        if (hearts[i] == 1)
        {
            i++;
        }

        else
        {
            hearts[i] = 1;
            i = -1;
        }
    }
    display(30);
    disp_life();
    break_lines();
}

void remove_heart()
{
    i = 0;
    while (i != -1)
    {
        if (hearts[i] == 1)
        {
            i++;
        }

        else
        {
            hearts[i - 1] = 0;
            i = -1;
        }
    }
    display(37);
    disp_life();
}

void test_find_life()
{
    /* increase the hearts*/
    if(labyrinth[x][y] != -1)
    {
        if (labyrinth[x][y] == 9) 
        {
            add_heart(hearts);
            labyrinth[x][y] = -1;
        }
    }
}

int count_hearts()
{
    int count;
    count = 0;
    while(hearts[count] == 1)
    {
        count++;
    }
    return count;
}

bool in_inventory(char object)
{
    bool is_in;
    i = 0;
    is_in = false;

    if (object == 'c')
    {
        object = 'k';
    }
    if (object == 'g')
    {
        object = 'p';
    }
    if (object == 'l')
    {
        object = 's';
    }

    while (is_in == false && i < max_life_obj)
    {
        if (inventory[i] == object)
        {
            is_in = true;
        }
        i++;
    }
    return is_in;
}

bool inv_is_void()
{
    bool is_void;
    is_void = true;
    for (i = 0; i < max_life_obj; i++)
    {
        if (inventory[i] != 'n')
        {
            is_void = false;
        }
    }
    return is_void;
}

//Display your items when it's necessary
void disp_inv()
{
    display_no_n(82);
    
    if (in_inventory('k') == true)
    {
        display_no_n(79);
    }
    if (in_inventory('p') == true)
    {
        display_no_n(80);
    }
    if (in_inventory('s') == true)
    {
        display_no_n(81);
    }
    printf("\n");
}

//Display the name of the item you just found
void display_name_inv(char name)
{
    if (name == 's')
    {
        display(76);
    }
    else if (name == 'k')
    {
        display(77);
    }
    else if (name == 'p')
    {
        display(78);
    }
}


//Put in your inventory the item only if you want
void put_in_inv(char object)
{
    char rep_obj;
    do
    {
        command_error = false;
        for (n = 49; n < 52; n++)
        {
            display(n);
        }
        scanf("%c", &rep_obj);
        rep_obj = toupper(rep_obj);
        switch(rep_obj)
        {
            case 'O':
            case 'Y':
                if (object == 'b')
                {
                    display(36);
                    remove_heart();
                    getchar();
                }
                else
                {   
                    display_name_inv(object);
                    inventory[place_inv] = getchar();
                    inventory[place_inv] = object;
                    disp_inv();
                    place_inv++;
                }
                break;

            case 'N':
                display(53);
                getchar();
                break;

            default :
                error();
                getchar();
                command_error = true;
                break;
            
        }
        break_lines();
    }while (command_error == true);
}


void fight1()
{
    int xp_human;
    char arme, rep_att;
    xp_human = 10;
    xp_robot1 = 15;
    display(48);
    do
    {
        if (inv_is_void() == true)
        {
                display(68);
                rep_att = 'N';
        }
        else
        {
            for (n = 54; n < 57; n++)
            {
                display(n);
            }
            scanf("%c", &rep_att);
            rep_att = toupper(rep_att);
        }
        
        switch (rep_att)
        {

        case 'O':
        case 'Y':
            getchar();
            disp_inv();
            scanf("%c", &arme);
            
                do
                {
                    if (in_inventory(arme) == false)
                    {
                        arme = 'e';
                    }
                    
                    arme = toupper(arme);

                    command_error = false;
                    switch (arme)
                    {
                    case 'P':
                    case 'G':
                        getchar();
                        xp_robot1 = xp_robot1 - 5;
                        break;

                    case 'K':
                    case 'C':
                        getchar();
                        xp_robot1 = xp_robot1 - 4;
                        break;

                    case 'S':
                    case 'L':
                        getchar();
                        xp_robot1 = xp_robot1 - 6;
                        break;

                    case 'E':
                        getchar();
                        display(83);
                        command_error = true;
                        disp_inv();
                        scanf("%c", &arme);
                        break;
                    }
                }while(command_error == true);
            
                
                if (xp_robot1 > 0)
                {
                    xp_human = xp_human - rand() % 2;
                }
                printf("XP robot : %d \n", xp_robot1);
                display(66);
                printf("XP %s : %d\n", name, xp_human);
                break;
            

        case 'N':
            display(57);
            display(58);
            scanf("%d", &rep_ph);
            if (rep_ph == 1)
            {
                xp_robot1 = xp_robot1 - 4;
            }
            else if (rep_ph == 2)
            {
                xp_robot1 = xp_robot1 - 3;
            }
            getchar();

            if (xp_robot1 > 0)
            {
                xp_human = xp_human - rand() % 6;
            }
            printf("XP robot : %d \n", xp_robot1);
            display(66);
            printf("XP %s : %d\n", name, xp_human);
            break;

        default:
            error();
            getchar();
            break;
        }

    } while (xp_robot1 > 0 && xp_human > 0);

    if (xp_human > 0)
    {
        display(60);
    }
    else if (xp_human <= 0)
    {
        display(67);
        remove_heart(hearts);
        labyrinth[18][8] = 4;
        display(123);
    }
}


void enig()
{
    int rep_enig;
    char rep_rec;
    for (n = 69; n < 73; n++)
    {
        display(n);
    }

    scanf("%d", &rep_enig);
    if (rep_enig == 3)
    {
        display(73);
        getchar();
        break_lines();
    }
    else
    {
        display(74);
        remove_heart(hearts);
        if (count_hearts() > 0)
        {
            do
            {   
                getchar();
                command_error = false; 
                for (i = 86; i < 89; i++)
                {
                    display(i);
                }
                scanf("%c", &rep_rec);
                rep_rec = toupper(rep_rec);
                switch(rep_rec)
                {
                    case 'Y':
                    case 'O':
                            enig();
                            getchar();
                            break; 
                    case 'N':
                            display(90);
                            remove_heart();
                            getchar();
                            break;
                    default:
                            error();
                            command_error = true;
                            break;
                }
            }while(command_error == true); 
        }
    }
}

void enig2()
{
    int rep_car;
    char rep_rece;
    for (i = 92; i < 95; i++)
    {
        display(i);
    }
    for (i = 95; i < 118; i++)
    {
        display(i);
    }
    scanf("%d", &rep_car);

    if (rep_car == 16)
    {
        display(118);
        break_lines();
        
    }
    else if (rep_car >= 13 && rep_car <= 19)
    {
        display(119);
        getchar();
        break_lines();
        enig2();
    }
    else
    {
        getchar();
        display(120);
        remove_heart(hearts);
        if (count_hearts() > 0)
        {
            do
            {   
                command_error = false; 
                for (i = 86; i < 89; i++)
                {
                    display(i);
                }
                scanf("%c", &rep_rece);
                rep_rece = toupper(rep_rece);
                switch(rep_rece)
                {
                    case 'Y':
                    case 'O':
                            enig2();
                            getchar();
                            break; 
                    case 'N':
                            display(90);
                            remove_heart();
                            getchar();
                            break;
                    default:
                            error();
                            command_error = true;
                            break;
                }
            }while(command_error == true); 
        }
    }
    
}

//test if you are in a place of interaction
void test_position()
{
    switch(labyrinth[x][y])
    {
        case 1 :
            fight1();
            break;
        case 14 : 
            put_in_inv('p');
            break;
        case 5 : 
            put_in_inv('k');
            break;
        case 6 :
            put_in_inv('s');
            break;
        case 8 :
            put_in_inv('b');
            break;
        case 13:
            enig();
            break;
        case 10 :
            enig2();
            break;
        case 15 : 
            display(38);
            exits = true;
            break_lines();
            break;

        /* teleportation */
        case 11:
            x = 2;
            y = 18;
            display(45);
            break_lines();
            break;

        case 12:
            x = 16;
            y = 15;
            display(45);
            break_lines();
            break;
    }
    
    labyrinth[x][y] = -1;
}
    

//To know where are the walls around you to display the paths
void wall_around(int x, int y)
{

    if (labyrinth[x - 1][y] != 4)
    {
        around[0]=1;
    }
    else
    {
        around[0]=0;
    }
    
    if (labyrinth[x + 1][y] != 4)
    {
        around[1]=1;
    }
    else
    {
        around[1]=0;
    }
    
    if (labyrinth[x][y + 1] != 4)
    {
        around[2]=1;
    }
    else
    {
        around[2]=0;
    }

    if (labyrinth[x][y - 1] != 4)
    {
        around[3]=1;
    }
    else
    {
        around[3]=0;
    }

}

//Display the directions you can go
void disp_paths()
{
    int i2;
    wall_around(x,y);
    display_no_n(31);
    for(i2 = 0 ; i2 < 4 ; i2++)
    {
        if(around[i2] == 1)
        {
            display_no_n(32+i2);
            printf(".. ");
        }
    }
    printf("\n");
}

/*Display the paths we can go*/
void advance()
{
    display_map(exits);
    display(8);
    display(9);
    disp_paths();
    display(11);
} 

//Upper your name for the end message
char *upper(char *name, char *end_name)
{
    int k;

    for (k = 0; name[k]; k++)
        end_name[k] = (toupper(name[k]));
    return end_name;
}

//Register your name
void nom()
{
    display(1);
    scanf("%[^\n]", name);

    getchar();

    display(2);
    printf("%s", name);
}

//Message of the good end
void winner()
{
    upper(name, end_name);
    printf("%s ", name);
    display(18);
    printf("❝%s, %s, %s ", name, name, end_name);
    for (n = 19; n < 23; n++)
    {
        display(n);
    }
}

//Message of the bad end
void death()
{
    printf("%s ", name);
    for (n = 24; n < 28; n++)
    {
        display(n);
    }
}

int main()
{
    int win, dead;
    char choice, lang[3], rep[20];

    /* initialization of values */
    x = 10; // The coordinates of x at the start
    y = 10; // The coordinates of y at the strat
    win = 2;
    dead = 7;
    exits = false;
    place_inv = 0;

    /*Choice of language */
    do
    {
        printf("Choose a language : fr / gb\n");
        scanf("%s", lang);
        upper(lang, lang);
        if (strcmp(lang, "FR") == 0)
        {
            filelang = "francais.txt";
        }
        else if (strcmp(lang, "GB") == 0)
        {
            filelang = "english.txt";
        }
        else
        {
            printf("Unrecognized language\n");
        }
        *lang = getchar();
    } while (strcmp(filelang, "") == 0);

    nom();

    /* Display the context */
    for (n = 3; n < 8; n++)
    {
        display(n);
    }
    break_lines();

    do
    {
        /* test if we have already walked on a site  */
        if(labyrinth[x][y] != -1)
        { 
            test_position();
            labyrinth[x][y] = -1;
        }

        if(count_hearts() > 0)
        {
            advance();
            scanf("%c", &choice);
            choice = toupper(choice);

            /* The different choice possible of the player */
            switch (choice)
            {

            case 'N':
                north();
                choice = getchar();
                break;

            case 'S':
                south();
                choice = getchar();
                break;

            case 'O':
            case 'W':
                west();
                choice = getchar();
                break;

            case 'E':
                east();
                choice = getchar();
                break;

            default:
                error();
                break;
            }
            test_find_life();
        }
    }while (labyrinth[x][y] != win && labyrinth[x][y] != dead && count_hearts(hearts) > 0);

 
    /* Display the sentence of victory */
    if (labyrinth[x][y] == win)
    {
        winner();
    }

    /* Display the sentence of defeat */
    else if (labyrinth[x][y] == dead)
    {
        death();
    }
    else if (count_hearts(hearts) == 0)
    {
        display(84);
    }
    printf("\n");
    display(121);
    scanf("%c",line_break);
    return 0;
}