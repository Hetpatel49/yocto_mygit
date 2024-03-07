/*this is header.h file*/
typedef struct ticket
{
	int16_t ticketno;
	int16_t screen;
	char *movie;
	char *seat;
	char *time;
	char *date;
	int16_t price;
} ticket_t;

ticket_t *tickets;
char **history;
void delete(ticket_t *);
extern int history_pointer;
extern int ticket_pointer;
void set_history(int, ticket_t *);
void init(ticket_t *);
int screen_choice(char *, char *);
int16_t selectoption(void);
int selectmovie(ticket_t *);
char seatchar(int);
int16_t str_to_int(char[]);
void print_available_seats();
void reservation(int *, ticket_t *);
void cancel(int **);
void print_ticket(ticket_t *);
