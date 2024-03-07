//this is the source code file of the project

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//init function to initialize the ticket structure
void init(ticket_t *t)
{
	t->ticketno = 0;
	t->screen = 0;
	t->movie = (char *)calloc(30, sizeof(char));
	t->seat = (char *)calloc(2, sizeof(char));
	t->time = (char *)calloc(15, sizeof(char));
	t->date = (char *)calloc(10, sizeof(char));
	t->price = 0;
}

//delete function to free the memory allocated to the ticket structure
void delete(ticket_t *t)
{
	free(t->movie);
	free(t->seat);
	free(t->time);
	free(t->date);
}

int16_t ticketid = 100;		 // ticket id to uniquely identify the ticket
int history_pointer = 0; // pointer to keep track of the history maximum 10 history can be stored
int ticket_pointer = 0;	 // pointer to keep track of the tickets maximum 300 tickets can be stored

void set_history(int action, ticket_t *t)
{
	if (action == 0)
	{
		int j = snprintf(history[history_pointer++], 100, "BOOKED\t\t| ID:%d\tScreen:%d\tMovie:%s\tSeat:%s\t\tDate:%s\t\tTime:%s\n", t->ticketno, t->screen, t->movie, t->seat, t->date, t->time);
	}

	else
	{
		int j = snprintf(history[history_pointer++], 100, "CANCELLED\t| ID:%d\tScreen:%d\tMovie:%s\tSeat:%s\t\tDate:%s\t\tTime:%s\n", t->ticketno, t->screen, t->movie, t->seat, t->date, t->time);
	}
}

int16_t selectoption(void)
{
	int16_t choice;
	printf("  ==================================================\n");
	printf("                      EIC CINEMA\n");
	printf("  ==================================================\n");
	printf("||             1- Book ticket                       ||\n");
	printf("||             2- Cancel ticket                     ||\n");
	printf("||             3- View history                      ||\n");
	printf("||             4- View available seats              ||\n");
	printf("||             5- Exit                              ||\n");
	printf("  ==================================================\n");
	printf("Enter your choice: ");
	if(scanf("%hd", &choice) != 1)
	{
  		printf("Invalid input!\n");
  		exit(1);
	}

	return choice;
}

int selectmovie(ticket_t *t)
{
	int16_t i;
	printf("\n\n");
	printf("Which movie you want to see?\n");
	printf("----------------------------\n");
	printf("press 1 for Lagan special\n\n");
	printf("press 2 for Hurry Om Hurry\n\n");
	scanf("%hd", &i);
	if (i == 1)
	{
		strcpy(t->movie, "Lagan special");
		t->price = 1000;
		t->screen = 1;
	}
	else if (i == 2)
	{
		strcpy(t->movie, "Hurry Om Hurry");
		t->price = 500;
		t->screen = 2;
	}

	int16_t time;
	printf("\nAvailable timings:\n1. 10:00 to 13:00\n2. 14:00 to 17:00\n3. 19:00 to 22:00\n");
	printf("Choose the time:");
	scanf("%hd", &time);

	if (time == 1)
	{
		strcpy(t->time, "10:00 to 13:00");
	}

	else if (time == 2)
	{
		strcpy(t->time, "14:00 to 17:00");
	}

	else if (time == 3)
	{
		strcpy(t->time, "19:00 to 22:00");
	}

	else
	{
		printf("Invalid choice\n");
	}

	return screen_choice(t->time, t->movie);
}

int screen_choice(char *time, char *movie)
{
	if (strcmp(time, "10:00 to 13:00") == 0 && strcmp(movie, "Lagan special") == 0)
		return 0;
	else if (strcmp(time, "14:00 to 17:00") == 0 && strcmp(movie, "Lagan special") == 0)
		return 1;
	else if (strcmp(time, "19:00 to 22:00") == 0 && strcmp(movie, "Lagan special") == 0)
		return 2;
	else if (strcmp(time, "10:00 to 13:00") == 0 && strcmp(movie, "Hurry Om Hurry") == 0)
		return 3;
	else if (strcmp(time, "14:00 to 17:00") == 0 && strcmp(movie, "Hurry Om Hurry") == 0)
		return 4;
	else if (strcmp(time, "19:00 to 22:00") == 0 && strcmp(movie, "Hurry Om Hurry") == 0)
		return 5;

	return -1;
}

char seatchar(int i)
{
	return i <= 4 ? 'A' : i <= 9 ? 'B'
					  : i <= 14	 ? 'C'
					  : i <= 19	 ? 'D'
					  : i <= 24	 ? 'E'
					  : i <= 29	 ? 'F'
					  : i <= 34	 ? 'G'
					  : i <= 39	 ? 'H'
					  : i <= 44	 ? 'I'
								 : 'J';
}

int16_t str_to_int(char c[])
{
	int16_t offset = 0;
	char a = c[0];
	offset = (a == 'A' ? 0 : a == 'B' ? 1
						 : a == 'C'	  ? 2
						 : a == 'D'	  ? 3
						 : a == 'E'	  ? 4
						 : a == 'F'	  ? 5
						 : a == 'G'	  ? 6
						 : a == 'H'	  ? 7
						 : a == 'I'	  ? 8
									  : 9);

	return offset * 5 + (c[1] - '0') - 1;
}

void print_available_seats(int *array)
{
	int16_t i;
	printf("\n\t  SCREEN\n\n\n");
	for (i = 0; i < 50; i++)
	{
		char c = seatchar(i);

		if (i % 5 == 0 && i != 0)
		{
			printf("\n\n");
		}

		if (array[i] == 0)
		{
			printf("%c%d\t", c, (i % 5) + 1);
		}

		else
		{
			printf("\t");
		}
	}

	printf("\n");
}

void reservation(int *array, ticket_t *t)
{
	int16_t i;
	char *seat;
	seat = (char *)calloc(2, sizeof(char));

	print_available_seats(array);

	printf("\nWhich seat number you want? ");
	scanf("%s", seat);
	int16_t arrayseat = str_to_int(seat);

	if (!(seat[0]-'A' >= 0 && seat[0]-'A' <= 9) || !(seat[1]-'0' >= 1 && seat[1]-'0' <= 5) || array[arrayseat] == 1)
	{
		printf("Seat unavailable\n\n");
	}

	else
	{

		t->seat = seat;
		printf("Your total amount=%d\n", t->price);
		int approval;
		printf("Press '1/0' to confirm\n\t1=Yes\n\t0=No\n\n");
		scanf("%d", &approval);

		if (approval == 1)
		{
			array[arrayseat] = 1;
			tickets[ticketid % 100] = *t;
			t->ticketno = ticketid++;
			strcpy(t->date, "14/02/2024");
			set_history(0, t);
			print_ticket(t);
		}
	}
}

void cancel(int **seat)
{
	int16_t seatno, i, stop;
	printf("Please enter your ticket number: ");
	scanf("%hd", &seatno);

	for (i = 0; i < 300; i++)
	{
		if (i == ticket_pointer)
			break;
		if (seatno == tickets[i].ticketno)
		{
			stop = 5;
			printf("%d seat has been cancelled\n\n", tickets[i].ticketno);
			int screen = tickets[i].screen;
			char *time;
			time = calloc(15, sizeof(char));
			strcpy(time, tickets[i].time);
			int s = str_to_int(tickets[i].seat);
			if (screen == 1)
			{
				if (strcmp(time, "10:00 to 13:00") == 0)
					seat[0][s] = 0;
				else if (strcmp(time, "14:00 to 17:00") == 0)
					seat[1][s] = 0;
				else
					seat[2][s] = 0;
			}

			else
			{
				if (strcmp(time, "10:00 to 13:00") == 0)
					seat[3][s] = 0;
				else if (strcmp(time, "14:00 to 17:00") == 0)
					seat[4][s] = 0;
				else
					seat[5][s] = 0;
			}

			free(time);
			set_history(1, &tickets[i]);
			i = 300;
		}
	}
	if (stop != 5)
		printf("Incorrect ticket number!\n");
}

void print_ticket(ticket_t *t)
{
	printf("\n\n");
	printf("==============================================================\n");
	printf("|------------------------EIC CINEMA--------------------------|\n");
	printf("==============================================================\n");
	printf(" Ticket No: %d \t\t\t\tMovie Ticket\n", t->ticketno);
	printf("==============================================================\n");
	printf(" Screen: %d\t\t\t\t\t%s\n", t->screen, t->movie);
	printf(" Seat: %c/%c\n", t->seat[0], t->seat[1]);
	printf(" Time: %s\n", t->time);
	printf(" Date: %s\t\t\t\tPrice: %d\n", t->date, t->price);
	printf("==============================================================\n");
	printf("==============================================================\n");
	printf("\n");
	return;
}
