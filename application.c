#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

int main()
{
    tickets = calloc(300, sizeof *(tickets));
    int **seat;          // total 6 screens adn 50 seats in each screen
    int16_t choice;      // to select the option
    int16_t price = 500; // price of each ticket with default value
    int i;
    seat = calloc(6, sizeof(*seat)); // allocating memory for 6 screens
    for (i = 0; i < 6; i++)
        seat[i] = calloc(50, sizeof *(seat[i]));
    int x; // to exit the loop

    history = (char **)calloc(10, sizeof(char *)); // allocating memory for history records
    for (i = 0; i < 10; i++)
        *(history + i) = (char *)calloc(100, sizeof(char)); // allocating memory for each history string record

    while (x != 5)
    {
        choice = selectoption();

        switch (choice)
        {
        case 1:
        {
            int total_tickets = 0;
            printf("Enter total number of tickets to buy:");
            scanf("%d", &total_tickets);
            while (total_tickets--)
            {
                ticket_t ticket;
                init(&ticket);
                int selected_screentime;
                selected_screentime = selectmovie(&ticket);
                reservation(seat[selected_screentime], &ticket);
                tickets[ticket_pointer++] = ticket;
            }
            break;
        }

        case 2:
        {
            cancel(seat);
            break;
        }

        case 3:
        {
            for (int i = 0; i < history_pointer; i++)
                printf("%s\n", *(history + i));
            break;
        }

        case 4:
        {
            printf("Screen 1: Lagan special\nScreen 2: Hurry Om Hurry\nEnter Screen No.: ");
            int screen, time;
            scanf("%d", &screen);
            printf("Available timings:\n1. 10:00 to 13:00\n2. 14:00 to 17:00\n3. 19:00 to 22:00\n");
            printf("Choose the time:");
            scanf("%d", &time);
            if (screen == 1 && time == 1)
                print_available_seats(seat[0]);
            else if (screen == 1 && time == 2)
                print_available_seats(seat[1]);
            else if (screen == 1 && time == 3)
                print_available_seats(seat[2]);
            else if (screen == 2 && time == 1)
                print_available_seats(seat[3]);
            else if (screen == 2 && time == 2)
                print_available_seats(seat[4]);
            else if (screen == 2 && time == 3)
                print_available_seats(seat[5]);

            else
                printf("Invalid choice\n");
            break;
        }

        case 5:
        {
            x = 5;
            break;
        }

        default:
        {
            printf("Choice not available\n");
            break;
        }
        }
	
    }
}
