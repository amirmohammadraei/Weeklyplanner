#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Task
{
	char name [32];
	int startTime;
	int endTime;
};


void addTask();
int isValidTask( int dayIndex, char name [32], int startTime, int endTime );
void showSchedule();
void showTasks(int dayIndex);
void saveFile();
void loadFile();
void waitAndClean();


struct Task days[7][100];
int tasksCount[7];
char username[32];


int main()
{
	printf("Please enter your username: ");
	scanf("%s" , username);

	printf("\n");
	printf("Hello %s\n" , username);
	printf("\n");

	int userAnswer = 0;

	while ( 1 )
	{
		printf ( "1) New task\n" );
		printf ( "2) Show schedule\n" );
		printf ( "3) Save into file\n" );
		printf ( "4) Load from file\n" );
		printf ( "5) Exit\n" );
		printf ( "\n" );
		printf ( "Please enter your choose option number: " );
		scanf ( "%d" , &userAnswer );

		printf ( "\n" );

		if ( userAnswer == 1 )
		{
			addTask ();
		}
		else if ( userAnswer == 2 )
		{
			showSchedule ();
		}
		else if ( userAnswer == 3 )
		{
			saveFile ();
			printf ( "Successfully saved into file ! \n" );
		}
		else if ( userAnswer == 4 )
		{
			loadFile ();
			printf ( "Successfully loaded from file ! \n" );
		}
		else if ( userAnswer == 5 )
		{
			printf ( "Thank you for using this application !\n" );
			break;
		}
	}

	return( 0 );
}


void addTask ()
{
	int dayIndex = 0;
	char name [ 32 ];
	int startTime = 0;
	int endTime = 0;

	printf ( "Day index: " );
	scanf ( "%d" , &dayIndex );

	printf ( "Name: " );
	scanf ( "%s" , name );

	printf ( "Start time: " );
	scanf ( "%d" , &startTime );

	printf ( "End time: " );
	scanf ( "%d" , &endTime );

	printf ( "\n" );

	if ( isValidTask ( dayIndex , name , startTime , endTime ) == 1 )
	{
		int taskIndex = tasksCount [ dayIndex ];
		tasksCount [ dayIndex ]++;

		strcpy ( days [ dayIndex ] [ taskIndex ].name , name );

		days [ dayIndex ] [ taskIndex ].startTime = startTime;
		days [ dayIndex ] [ taskIndex ].endTime = endTime;

		printf ( "There is no error and the new task is created\n" );
	}

	printf ( "\n" );
}

int isValidTask ( int dayIndex , char name [ 32 ] , int startTime , int endTime )
{
	if ( dayIndex < 0 || 6 < dayIndex )
	{
		printf ( "Day index has to be a valid integer number from 0 to 6 !\n" );
		return 0;
	}

	if ( startTime < 0 || 86400 < startTime )
	{
		printf ( "Start time has to be a valid integer number from 0 to 86400 \n" );
		return 0;
	}
	if ( endTime < 0 || 86400 < endTime )
	{
		printf ( "End time has to be a valid integer number from 0 to 86400 \n" );
		return 0;
	}

	if ( endTime - startTime < 0 )
	{
		printf ( "End time has to be after start time !\n" );
		return 0;
	}

	for ( int i = 0; i < tasksCount [ dayIndex ]; i++ )
	{
		struct Task task = days [ dayIndex ] [ i ];

		if ( strcmp ( task.name , name ) == 0 )
		{
			printf ( "There is already a task with this name in the schedule !\n" );
			return 0;
		}

		if ( ( task.startTime < startTime && startTime < task.endTime ) || ( task.startTime < endTime && endTime < task.endTime ) )
		{
			printf ( "There is an interference with a task !\n" );
			return 0;
		}
	}

	return 1;
}

void showSchedule ()
{
    printf( "=============================================" );
    printf( "\n" );

	printf ( "0 (Saturday): " );
	showTasks ( 0 );

	printf ( "1 (Sunday): " );
	showTasks ( 1 );

	printf ( "2 (Monday): " );
	showTasks ( 2 );

	printf ( "3 (Tuesday): " );
	showTasks ( 3 );

	printf ( "4 (Wednesday): " );
	showTasks ( 4 );

	printf ( "5 (Thursday): " );
	showTasks ( 5 );

	printf ( "6 (Friday): " );
	showTasks ( 6 );

	printf( "=============================================" );

	printf ( "\n\n\n" );
}

void showTasks ( int dayIndex )
{
	if ( tasksCount [ dayIndex ] > 0 )
	{
		for ( int i = 0; i < tasksCount [ dayIndex ] - 1; i++ )
		{
			for ( int j = 0; j < tasksCount [ dayIndex ] - i - 1; j++ )
			{
				if ( days [ dayIndex ] [ j ].startTime > days [ dayIndex ] [ j + 1 ].startTime )
				{
					struct Task temp = days [ dayIndex ] [ j ];
					days [ dayIndex ] [ j ] = days [ dayIndex ] [ j + 1 ];
					days [ dayIndex ] [ j + 1 ] = temp;
				}
			}
		}

		printf ( "%s (from: %d, to: %d)" , days [ dayIndex ] [ 0 ].name , days [ dayIndex ] [ 0 ].startTime , days [ dayIndex ] [ 0 ].endTime );

		for ( int i = 1; i < tasksCount [ dayIndex ]; i++ )
		{
			printf ( " -> " );
			printf ( "%s (from: %d, to: %d)" , days [ dayIndex ] [ i ].name , days [ dayIndex ] [ i ].startTime , days [ dayIndex ] [ i ].endTime );
		}
	}

	printf ( "\n" );
}

void saveFile ()
{
	char fileName [ 32 ];
	strcpy ( fileName , username );
	strcat ( fileName , ".txt" );

	FILE* file;
	file = fopen ( fileName , "w" );

	for ( int i = 0; i < 7; i++ )
	{
		fprintf ( file , "%d\n" , tasksCount [ i ] );

		for ( int j = 0; j < tasksCount [ i ]; j++ )
		{
			fprintf ( file , "%s\n" , days [ i ] [ j ].name );
			fprintf ( file , "%d\n" , days [ i ] [ j ].startTime );
			fprintf ( file , "%d\n" , days [ i ] [ j ].endTime );
		}
	}

	fclose ( file );
}

void loadFile ()
{
	char fileName [ 32 ];
	strcpy ( fileName , username );
	strcat ( fileName , ".txt" );

	FILE* file;
	file = fopen ( fileName , "r" );

	if ( file != NULL )
	{
		char line [ 32 ];

		for ( int i = 0; i < 7; i++ )
		{
			fgets ( line , sizeof line , file );
			tasksCount [ i ] = atoi ( line );

			for ( int j = 0; j < tasksCount [ i ]; j++ )
			{
				fgets ( line , sizeof line , file );
				strtok ( line , "\n" );
				strcpy ( days [ i ] [ j ].name , line );

				fgets ( line , sizeof line , file );
				days [ i ] [ j ].startTime = atoi ( line );

				fgets ( line , sizeof line , file );
				days [ i ] [ j ].endTime = atoi ( line );
			}
		}
	}

	fclose ( file );
}

