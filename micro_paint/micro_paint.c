#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_zone
{
    int width;
    int height;
    char background;
}   t_zone;

typedef struct s_list
{
    char type;
    float x;
    float y;
    float width;
    float height;
    char color;
}   t_list;

void ft_putstr(char *str)
{
    int i = 0;

    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

int ft_fail(char *str)
{
    ft_putstr(str);
    return (1);
}

int ft_clear(FILE *file, char *str)
{
    fclose(file);
    if (str)
        free(str);
    return (1);
}

int ft_checklog(t_zone *zone)
{
    return ((zone->width >= 0 && zone->width <= 300) && (zone->height >= 0 && zone->height <= 300));
}

char *ft_getlog(FILE *file, t_zone *zone)
{
    int bf;
    int i = 0;
    char *str;

    bf = fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background);
    if (bf != 3)
        return (NULL);
    if (!(ft_checklog(zone)))
        return (NULL);
    str = malloc(sizeof(char) * (zone->width * zone->height));
    while (i < zone->height * zone->width)
    {
        str[i] = zone->background;
        i++;
    }
    return(str);
}

int ft_checkdata(t_list *list)
{
    return ((list->height > 0.00000000 && list->width > 0.00000000) && (list->type == 'r' || list->type == 'R'));
}

int ft_israd(float y, float x, t_list *list)
{
    float c;
    c = 1.00000000;

    if ((x < list->x) || (list->x + list->width < x) || (y < list->y) || (list->y + list->height < y))
        return (0);
    if (((x - list->x) < c) || ((list->x + list->width) - x < c) || ((y - list->y) < c) || ((list->y + list->height) - y < c))
        return (2);
    return (1);
}

void ft_getstr(char **str, t_list *list, t_zone *zone)
{
    int x;
    int y;
    int res;

    y = 0;
    while (y < zone->height)
    {
        x = 0;
        while (x < zone->width)
        {
            res = ft_israd(y, x, list);
            if ((list->type == 'r' && res == 2) || (list->type == 'R' && res))
                (*str)[(y * zone->width) +x] = list->color;
            x++;
        }
        y++;
    }
}

int ft_game(FILE *file, char **str, t_zone *zone)
{
    t_list list;
    int i;

    while ((i = fscanf(file, "%c %f %f %f %f %c\n", &list.type, &list.x, &list.y, &list.width, &list.height, &list.color)) == 6)
    {
        printf("hello\n");
        printf("i:%d\n", i);
        if (!ft_checkdata(&list))
            return (0);
        printf("hello2\n");
        ft_getstr(str, &list, zone);
    }
    printf("i:%d\n", i);
    if (i != (-1))
        return (0);
    return (1);
}

void ft_printstr(char *str, t_zone *zone)
{
    int i;

    i = 0;
    while (i < zone->height)
    {
        write(1, str + (i * zone->width), zone->width);
        write(1, "\n", 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_zone zone;
    char *str;
    FILE *file;

    // file = fopen(argv[1], "r");
    // printf("file:%p\n", file);

    if (argc != 2)
        return (ft_fail("Error: argument\n"));
    if (!(file = fopen(argv[1], "r")))
    
        return (ft_fail("1 Error: Operation file corrupted\n"));
    if (!(str = ft_getlog(file, &zone)))
        return (ft_clear(file, NULL) && ft_fail("2 Error: Operation file corrupted\n"));
    int res;
    res = ft_game(file, &str, &zone);
    printf("res:%d\n", res);
    if (!(res))
        return (ft_clear(file, str) && ft_fail("3 Error: Operation file corrupted\n"));
    ft_printstr(str, &zone);
    ft_clear(file, str);
    return (0);
}
