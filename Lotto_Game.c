
/* Date started: 20/2/2016
    Author: Mohamad Zabad
    Programming assignment 2
   Program that simulates a lotto game  */

#include <stdio.h>
#include <stdlib.h>                               // Used for the clear screen command
#include <conio.h>                                // Used so we can use colors
#include <windows.h>                              // Used for the Sleep/Delay

// Area for defines  
#define TIME 0
#define SIZE 7                                    // The arrays are 7 positions so we can use one position as an auxiliary


// Prototypes
void greeting(void);                              // Used to display a greeting
int menu(void);                                   // Used to display the menu  and pass back the user's selected option to the main.
int select_option(void);                          // Used for reading in the answer for the menu and sending it to the menu function.
void menu_option(int);                            // Used to select a certain option of the menu and calling the appropiate function

void numbers_in(int *, int *, int *);
void numbers_out(int*, int);
void numbers_out_ordered(int*, int);              // Each functions does one of the program's option
void check_win(int*, int*, int, int, int);
void display_frequency(int*, int);
void exit_msg(void);

void press_enter(int);                           // Simple function used for a "Press enter to go back" message
void message_wait(int);                          // Function that waits a certain amout of time and then goes back to the menu


// Global declaration area
int access_case_two;                              // Variable used to determine if the first option was ran or not
int chosen_numbers[SIZE] ;                        // The 7th position of this array is used as an auxiliary in the sorting function
int chosen_numbers_copy[SIZE];


main()
{
    // Declaration area
    int option_answer_two;
    
    // Code area
    greeting();
    do
    {
        option_answer_two=menu();
    }
    while(option_answer_two != 6);                // It repeats until the user decides to exit                                    
    
    
}// end main

void greeting(void)
{
    for(int sec=3; sec>TIME; sec--)                 // Animation for the start of the program
    {
        system("cls");
        printf("\n\t\t\t\t\tWelcome to the Lotto game!\n \n");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\tThe game will load in ");
        textcolor(LIGHTGREEN);
        cprintf("%d", sec);
        printf("...");
        Sleep(1100);
    }
} // end greeting

int menu(void)
{
    // Declaration area
    int option_answer;
    
    // Code area
    system("cls");
    
    printf("1. Play the Lotto\n");
    printf("2. Display the numbers \n");
    printf("3. Sort the numbers\n");
    printf("4. Check if the numbers are right\n");           // Change this AND FORMAT IT
    printf("5. Display the frequency of the numbers\n");
    printf("6. Exit the program\n\n");
    printf("Please choose one of the following options: ");
    
    option_answer=select_option();             // Storing the return value from select_option
    menu_option(option_answer);                // Calling the function that determines which function is next
    return(option_answer);                     // Returning the value of the user option
} // end menu

int select_option(void)
{
    // Declaration area
    int menu_answer=0;
    
    // Code area
    do                                             // Loop that takes input from the user and error checks it
    {
        scanf("%d", &menu_answer);
        flushall();
        if((menu_answer<1) || (menu_answer>6))
        {
            printf("\n");
            textcolor(LIGHTRED);
            cprintf("I don't recognize this option. Please try again ");
        }
        
    }
    while((menu_answer<1) || (menu_answer>6));
    return(menu_answer);                           // Returning the valid input from the user to the menu function
} // End of select_option 

void menu_option(int selected_option)
{
    // declaration area
    int counter=0, bonus=0;
    int winning_numbers[SIZE]={1,3,5,7,9,11,42};   
    static int frequency[42];                      // Declared as static so it saves everytime there's a run through the game without closing it
 
    
    // Code area
    switch(selected_option)
    {
        case 1:
        {
            numbers_in(chosen_numbers, chosen_numbers_copy, frequency);                               // Calling the 1st function
            access_case_two=1;
            break;
        }  // End case 1
        
        case 2:
        {
            numbers_out(chosen_numbers, access_case_two);                                             // Calling the 2nd function   
            break;
        } // End case 2
        
        case 3:
        {
            numbers_out_ordered(chosen_numbers_copy, access_case_two);                                // Calling the 3rd function
            break;
        } // End case 3
        
        case 4:
        {
            check_win(winning_numbers, chosen_numbers_copy, counter, bonus, access_case_two);         // Calling the 4th function
            break;
        } // End case 4
        
        case 5:
        {
            display_frequency(frequency, access_case_two);                                            // Calling the 5th function
            break;
        } // End case 5
        
        case 6:
        {
            exit_msg();                                                                               // Calling the 6th function
            break;
        } // End case 6
                                                                                                      // There is no need for a default because we have error checking
    }// End of the switch
}// End menu option

void numbers_in(int *chosen_array, int *chosen_array_copy, int *frequency_array) 
{
    //Declaration area
    int repeating;
    
    // Code area
    system("cls");
    for( int index=0; index<6; index++)
    {                                             
        switch(index)                                 // Switch that displays different messages for the input
        {
            case 0:
            {
                printf("Choose your 1st number: ");
                break;
            }
            case 1:
            {
                printf("Choose your 2nd number: ");
                break;
            }
            case 2:
            {
                printf("Choose your 3rd number: ");
                break;
            }
            case 3: case 4: case 5: 
            {
                printf("Choose your %d",index+1);
                printf("th number: ");
                break;
            }
            
        } // End switch        
        
        do
        {
            repeating=0;
            do                                            // Do while that determines if the input is an integer and if it is between 1 and 42  
            {
                *(chosen_array+index)= 100;               // 100 is just a random number that is out of our condition's bounds
                scanf("%d", chosen_array+index);                          
                flushall();
                if((*(chosen_array+index)<1) || (*(chosen_array+index)>42))
                {
                    textcolor(LIGHTRED);
                    cprintf("The input is not valid!");
                    printf("\n");
                }
            }while((*(chosen_array+index)<1) || (*(chosen_array+index)>42)); // End inner do while
                
                
            for(int k=0; k<index; k++)                    // Structure that compares the new number with the ones that were entered before
            {
                if(*(chosen_array+index) == chosen_array[k])
                {
                    repeating=1;
                    break;
                }
            }
            
            if(repeating==1)
            {                                              // Entering the numbers conditions
                textcolor(LIGHTRED);
                cprintf("You have already entered this number");
                printf("\n");
            }
        } while(repeating==1);                             // End outer do while
        
        *(chosen_array_copy + index)= *(chosen_array + index);    // Making a copy of the array for the third option
        (*(frequency_array + *(chosen_array + index)))++;         // Incrementin the frequency of each number on their position                      
    } // End for
}// End numbers_in

void numbers_out(int *array, int condition)
{
    //Code area
    system("cls");
    if(condition==1)                                       // if statement that determines if the first option was ran before
    {
        printf("\nThe numbers you chose are: ");
        for( int index=0; index<6; index++)                // Displaying the chosen numbers    
        {
            textcolor(WHITE);
            cprintf("%d ", *(array + index));
        }
        
        press_enter(8);                                     // Calling the press_enter function
    }
    else
    {                                                      // In case the first option was not ran the function that displays an error message will be ran
        message_wait(4);
    }
    system("cls");
} // End numbers_out

void numbers_out_ordered(int *array, int condition)
{
    // Code area
    system("cls");
    if(condition==1)                                                // if statement that determines if the first option was ran before         
    {
        for(int index=0; index<5; index++)
        {                                                           // These two loops compare select the elements from the array copy
            for(int index_two=index+1; index_two<6; index_two++)
            {
                if( *(array + index)>*(array + index_two))          // If statement that sorts the copy of the array
                {
                    *(array + 6)=*(array + index);
                    *(array + index)=*(array + index_two );      
                    *(array + index_two)=*(array + 6);
                }
            } // End inner for
        }// End 1st for
        
        
        printf("The ordered numbers are: ");
        for(int index=0; index<6; index++)                          // Loop that displays the ordered numbers
        {
            textcolor(WHITE);
            cprintf("%d ", *(array + index));
        }
        
        press_enter(27);                                             // Function used to display the "enter to go back" message
        
    }
    else
    {
        message_wait(3);                                             // Calling the funtion to display the timed message
    } // End else
    system("cls");
} // End numbers_out_ordered

void check_win(int *winning_array, int *normal_array_copy, int counter_one, int counter_two, int condition)
{
    // Declaration area
    int index, index2;
    
    // Code area
    if(condition==1)                                                             // if statement that determines if the first option was ran before        
    {
        system("cls");
        for( index=0; index<SIZE-1;index++)
        {
            for( index2=0; index2<SIZE-1; index2++)
            {
                if(*(winning_array + index)== *(normal_array_copy + index2))     // This block counts how many winning numbers did the user guess
                {
                    counter_one++;
                    break;
                }
            }
        }
        
        for( index=SIZE-1; index>0;index--)                                     // Going from SIZE-1 to 0 because the array is sorted in an ascending order and this will be more efficient
        {
            if(*(normal_array_copy + index) == *(winning_array + 6))            // This block determines if the bonus number was guessed
            {
                counter_two=1;
                break;
            }
        }
        
        printf("\n  You got ");
        textcolor(LIGHTGREEN);
        cprintf("%d", counter_one);
        printf(" numbers right and ");                                          // Displaying the number of correct and wrong numbers
        textcolor(LIGHTRED);
        cprintf("%d", 6-counter_one);
        printf(" wrong.\n");
        
        if(counter_two==1)
        {
            printf("  You guessed the bonus number!\n");
        }
        else                                                                    // This block informs the user wether he/she guessed the bonus number
        {
            printf("  You didn't guess the bonus number.\n");
        }
        
        textcolor(WHITE);
        switch(counter_one)                                                     // Switch statement that decides if the user won anything.
        {
            case 3:
            {
                if(counter_two==1)
                {
                    
                    cprintf("     You won a Cinema Ticket! ");
                }
                else
                {
                    cprintf("     You are not a winner :(");
                }
                break;
            }
            case 4:
            {
                if(counter_two==1)
                {
                    cprintf("     You won a Weekent Away!");
                }
                else
                {
                    cprintf("     You won a Night out!");
                }
                break;
            }
            case 5:
            {
                if(counter_two==1)
                {
                    cprintf("     You won a new car!");
                }
                else
                {
                    cprintf("     You won a Holiday!");
                }
                break;
            }
            case 6:
            {
                
                cprintf("     You won the JACKPOT!");
                break;
            }
            default:
            {
                cprintf("     You did not win anything  :(");
            }
        } // End of switch
        
        press_enter(8);                 // Calling the press_enter function
        system("cls");
    }
    else
    {
        system("cls");
        message_wait(3);
    }// end else
}// End check_win

void display_frequency(int *frequency_array, int condition)
{
    if(condition==1)                                                                 // if statement that determines if the first option was ran before    
    {
        system("cls");
        printf("The frequency of the numbers are: \n");
        for(int index=0; index<43; index++)
        {
            if(*(frequency_array + index)>0)                                         // Block that displays the frequency of the numbers
            {
                if(*(frequency_array + index)==1)
                {
                    textcolor(LIGHTCYAN);
                    printf("The number ");
                    cprintf("%d",index);
                    textcolor(WHITE);
                    printf(" has been entered ");
                    cprintf("%d",  *(frequency_array + index));                      // Special case for the nubmbers that have been entered only once
                    printf(" time\n");
                }
                else
                {
                    textcolor(LIGHTCYAN);
                    printf("The number ");
                    cprintf("%d",index);
                    textcolor(WHITE);
                    printf(" has been entered ");
                    cprintf("%d",  *(frequency_array + index));
                    printf(" times\n");
                }// End else
            }// End outer if
        }// end for loop
        
        
        press_enter(2);                  // calling the press_enter function
    }
    else
    {
        message_wait(3);                 // Calling the message_wait function
    } // End else    
}// End display_frequency

void exit_msg(void)
{
    for(int sec=3; sec>TIME; sec--)                    // Exit animation
    {
        system("cls");
        printf("\n\tThe program will close in ");
        textcolor(LIGHTGREEN);
        cprintf("%d", sec);
        printf("...");
        Sleep(1000);
    }
}// end exit_msg

void press_enter(int a)
{
    for(int var=0; var<a;var++)                        
    {
        printf("\n");                         // Block that puts a certain number of end lines
    }
    textcolor(WHITE);
    cprintf("[Press enter to go back]");     
    getchar();
}// End press_enter

void message_wait(int period)
{
    for(int sec=period; sec>TIME; sec--)        
    {
        textcolor(LIGHTRED);
        cprintf("Choose your numbers first!\n");
        printf("\nThe program will continue in ");          // It displays an animation for few seconds
        textcolor(LIGHTGREEN);
        cprintf("%d", sec);
        printf("...");
        Sleep(1000);
        system("cls");
    }
    
}// End message_wait