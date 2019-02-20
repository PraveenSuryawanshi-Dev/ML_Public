#include <stdio.h>
#include <string>
#include <iostream>

typedef enum _ALPHABETS_
{
	A=1,    B,     C,     D,     E,

	F,     G,     H,     I,     J,

	K,     L,     M,     N,     O,

	P,     Q,     R,     S,     T,

	U,     V,     W,     X,     Y,     Z

}ALPHABETS;

int main(int argc, char *argv[])
{
	int i = 1;

	int choice = 0;

	while (argc != i)
	{
		choice = atoi(argv[i]);

		switch (ALPHABETS(choice))
		{

		case A:printf("A");break;

		case B:printf("B"); break;

		case C:printf("C"); break;

		case D:printf("D"); break;

		case E:printf("E"); break;

		case F:printf("F"); break;

		case G:printf("G"); break;

		case H:printf("H"); break;

		case I:printf("I"); break;

		case J:printf("J"); break;
					 
		case K:printf("K"); break;

		case L:printf("L"); break;

		case M:printf("M"); break;

		case N:printf("N"); break;

		case O:printf("O"); break;
					 
		case P:printf("P"); break;

		case  Q:printf("Q"); break;

		case R:printf("R"); break;

		case S:printf("S"); break;

		case T:printf("T"); break;
					 
		case U:printf("U"); break;

		case V:printf("V"); break;

		case W:printf("W"); break;

		case X:printf("X"); break;

		case Y:printf("Y"); break;

		case Z:printf("Z"); break;

		default:
			break;
		}

		i++;
	}
}
