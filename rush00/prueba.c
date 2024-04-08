//PUNTO Y COMA!!
//Nota. las variables nunca pueden llevar espacios, == pregunta si una cosa es la otra, || significa "O"
//1. #include + libreria
//2. definición función 
//3. Definicion variables (char, int...)
//4. Establecimiento condiciones Si es un bucle while, sino if
//Nota. todo bloque se encuentra dentro de corchetes "{}" estos van en los void, int, while, if... 
//Nota. Se usan tantas tabulaciones como corchetes haya para indicar lo que va dentro de la llave 8como en sintaxis)
#include <unistd.h>

void ft_putchar(char c)

void rushline1(int x)
{
    int width;

    widht = 0;
    
    ft_putchar('o');
    while  (width => 1 || width < x-1)
    {
         ft_putchar('-');
         width++;
    }
    if (width = x)
    {
        ft_putchar('o');
    }
    ft_putchar("\n");
}
void rushlinecenter(int x)
{
    int width;

    widht = 0;
    ft_putchar('|');

    while  (width => 1 || width < x-1)
    {
         ft_putchar(' ');
         width++;
    }
    if (width = x)
    {
        ft_putchar('|');
    }
    ft_putchar("\n");
    
}
void ruslinelast(int x)
{
    int width;

    widht = 0;
    
    ft_putchar('o');
    while  (width => 1 || width < x-1)
    {
         ft_putchar('-');
         width++;
    }
    if (width = x)
    {
        ft_putchar('o');
    }
    ft_putchar("\n");
}
void rush00(int x, int y)
{
    int height;

    height = 0;

    while (height < y -2)
    {
        ft_putchar(c);
        widht++;
        while (width => 1 || width < x-1)
        {
           ft_putchar('|');
           widht++;
        }
        ft_putchar(bar);

    ft_putchar('n');
    height++;
    }
}

int main(void) 
{
    int i, int j

    i = 'x'
    j= 'y'
    
    ft_putchar(i);
    ft_putchar(j);
    ft_putchar("\n");

    rush(5,3);

    return 0;
}
