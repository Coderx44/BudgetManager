#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
char isLeapYear;
int leapyear;
int month;
int date;
char day;
float budget;
float payables;
float income;
int incDate;
float expense;
int expDate;
float repeatingIncome;
int repeatingIncomeDate;
float repeatingExpense;
int repeatingExpenseDate;
float repeatingRent;
int repeatingRentDate;
int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *monthNames[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const char *dayNames[] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"};
enum DayOfWeek
{
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};
enum DayOfWeek today;

void dayName()
{
    switch (day)
    {
    case 'S':
        today = SUNDAY;
        break;
    case 'M':
        today = MONDAY;
        break;
    case 'T':
        today = TUESDAY;
        break;
    case 'W':
        today = WEDNESDAY;
        break;
    case 'H':
        today = THURSDAY;
        break;
    case 'F':
        today = FRIDAY;
        break;
    case 'A':
        today = SATURDAY;
    }
}
void scheduleRepeatingIncome()
{

    printf("Enter a date for the repeating Income: ");
    scanf(" %d", &repeatingIncomeDate);
    if (date < 1 || date > 31)
    {
        printf("Error: Invalid input for current date. Please enter a valid two-digit number for the date.\n");
        scheduleRepeatingIncome();
        return;
    }
    printf("Enter the recurring amount: ");
    scanf(" %f", &repeatingIncome);
    if (repeatingIncome < 0)
    {
        printf("Income cannot be negative\n\n");
        scheduleRepeatingIncome();
        return;
    }
    return;
}

void updateRepeatingIncome()
{
    char choice;
    printf("Do you really wish to update your repeating Income: ");
    scanf(" %c", &choice);
    if (choice == 'N' || choice == 'n')
        return;
    printf("Do you want to remove your existing income: ");
    scanf(" %c", &choice);
    if (choice == 'Y' || choice == 'y')
    {
        repeatingIncome = 0;
        repeatingIncomeDate = 0;
        return;
    }
    scheduleRepeatingIncome();
}

void scheduleRepeatingExpense()
{

    printf("Enter a date for the repeating Expense: ");
    scanf(" %d", &repeatingExpenseDate);
    if (date < 1 || date > 31)
    {
        printf("Error: Invalid input for current date. Please enter a valid two-digit number for the date.\n");
        scheduleRepeatingExpense();
        return;
    }
    printf("Enter the recurring amount: ");
    scanf(" %f", &repeatingExpense);
    if (repeatingExpense < 0)
    {
        printf("Expende cannot be negative\n\n");
        scheduleRepeatingExpense();
        return;
    }
    return;
}

void updateRepeatingExpense()
{
    char choice;
    printf("Do you really wish to update your repeating Expense: ");
    scanf(" %c", &choice);
    if (choice == 'N' || choice == 'n')
        return;
    printf("Do you want to remove your existing expense: ");
    scanf(" %c", &choice);
    if (choice == 'Y' || choice == 'y')
    {
        repeatingExpense = 0;
        repeatingExpenseDate = 0;
        return;
    }
    scheduleRepeatingExpense();
}

void scheduleRepeatingRent()
{

    printf("Enter the rent amount: ");
    scanf("%f", &repeatingRent);
    return;
}

void updateRepeatingRent()
{
    char choice;
    printf("Do you really wish to update your rent: ");
    scanf(" %c", &choice);
    if (choice == 'N' || choice == 'n')
        return;
    printf("Do you want to remove your existing rent: ");
    scanf(" %c", &choice);
    if (choice == 'Y' || choice == 'y')
    {
        repeatingRent = 0;
        return;
    }
    scheduleRepeatingRent();
}

void EndDay()
{

    // Days in each month (assuming non-leap year)

    bool isEOM = false;
    // Check if current year is a leap year
    if (isLeapYear == 'Y')
    {
        daysInMonth[2] = 29; // February has 29 days in a leap year
    }
    else
    {
        daysInMonth[2] = 28;
    }

    // Increment current day by 1
    (date)++;

    // Check if current day exceeds days in current month
    if (date > daysInMonth[month])
    {
        date = 1; // Reset day to 1
        month++;  // Increment month by 1

        // Check if current month exceeds 12 (December)
        if (month > 12)
        {
            month = 1; // Reset month to 1
            leapyear = (++leapyear) % 4;
            if (leapyear == 0)
            {

                isLeapYear = 'Y';
                leapyear = 0;
            }
            else
            {
                isLeapYear = 'N';
            }
        }
    }

    if (repeatingIncome > 0 && repeatingIncomeDate == date || (date > daysInMonth[month] && date == daysInMonth[month]))
    {
        budget += repeatingIncome;
    }
    if (date == daysInMonth[month] && repeatingRent > budget)
    {
        payables += repeatingRent;
    }
    else if (date == daysInMonth[month])
    {
        budget -= repeatingRent;
    }
    if (repeatingExpense > 0 && repeatingExpenseDate == date || (date > daysInMonth[month] && date == daysInMonth[month]))
    {
        if (repeatingExpense > budget)
            payables += repeatingExpense;
        else
            budget -= repeatingExpense;
    }
    switch (day)
    {
    case 'S':
        day = 'M';
        dayName();
        break;
    case 'M':
        day = 'T';
        break;
    case 'T':
        day = 'W';
        dayName();
        break;
    case 'W':
        day = 'H';
        dayName();
        break;
    case 'H':
        day = 'F';
        dayName();
        break;
    case 'F':
        day = 'A';
        dayName();
        break;
    case 'A':
        day = 'S';
        dayName();
        break;
    default:
        printf("Error: Invalid day of the week.\n");
        break;
    }
}

void EndWeek()
{
    int daysToSkip = (SATURDAY - today + 1) % 8;
    int i;
    for (i = 1; i <= daysToSkip; i++)
    {
        EndDay();
    }
}

void EndMonth()
{
    if (isLeapYear == 'Y')
    {
        daysInMonth[2] = 29; // February has 29 days in a leap year
    }
    else
    {
        daysInMonth[2] = 28;
    }
    int daysToSkip = daysInMonth[month] - date;
    if (daysToSkip == 0)
    {
        if (month == 12)
        {
            daysToSkip = 31;
        }
        else
        {
            daysToSkip = daysInMonth[month + 1];
        }
    }
    int i;
    for (i = 1; i <= daysToSkip; i++)
    {
        EndDay();
    }
}
void EndYear()
{

    int monthsToSkip = 12 - month;
    if (monthsToSkip == 0)
    {
        monthsToSkip = 12;
    }
    if (date != daysInMonth[month])
    {
        monthsToSkip++;
    }
    int i;
    for (i = 1; i <= monthsToSkip; i++)
    {
        EndMonth();
    }
}

void displayDailyIncome()
{
    bool flag = false;
    if (income > 0 && date == incDate)
    {
        printf("Today's income: PHP %f\n", income);
        flag = true;
    }
    if (repeatingIncome > 0 && repeatingIncomeDate == date)
    {
        printf("Repeating Income: PHP %f\n", repeatingIncome);
        flag = true;
    }
    if (!flag)
    {
        printf("No income logged for today.\n");
    }
}

void displayDailyExpense()
{
    bool flag = false;
    if (expense > 0 && expDate == date)
    {
        printf("Today's expense: PHP %f\n", expense);
        flag = true;
    }
    if (repeatingExpense > 0 && repeatingExpenseDate == date)
    {
        printf("Repeating Expense: PHP %f\n", repeatingExpense);
        flag = true;
    }
    if (repeatingRent > 0 && date == daysInMonth[month])
    {
        printf("Rent Expense: PHP %f\n", repeatingRent);
        flag = true;
    }

    if (!flag)
    {
        printf("No expense for today.\n");
    }
}

void displayCurrentBudget()
{
    printf("Current Remaining Budget is PHP %.2f", budget);
}

void displayPayables()
{
    printf("Current payables : PHP %.2f", payables);
}
bool LeapYear()
{
    if (isLeapYear == 'Y')
        return true;
    return false;
}
int main()
{

    printf("Is this year a leap year? (Y/N): ");
    scanf(" %c", &isLeapYear);
    isLeapYear = toupper(isLeapYear);
    if (isLeapYear != 'Y')
    {
        leapyear = 1;
    }
    printf("\nEnter current month\n"
           "1 – January\n"
           "2 – February\n"
           "3 – March\n"
           "4 – April\n"
           "5 – May\n"
           "6 – June\n"
           "7 – July\n"
           "8 – August\n"
           "9 – September\n"
           "10 – October\n"
           "11 – November\n"
           "12 – December\n\n");
    scanf("%d", &month);
    if (month < 1 || month > 12)
    {
        printf("Error: Invalid input for current month. Please enter a valid two-digit number for the month.\n");
        return 1;
    }
    printf("\nEnter current date (DD): ");
    scanf("%d", &date);

    if (date < 1 || date > 31)
    {
        printf("Error: Invalid input for current date. Please enter a valid two-digit number for the date.\n");
        return 1;
    }

    printf("\nEnter current day\n"
           "S – Sunday\n"
           "A – Saturday\n"
           "M – Monday\n"
           "T – Tuesday\n"
           "W – Wednesday\n"
           "H – Thursday\n"
           "F – Friday\n\n");
    scanf(" %c", &day);
    day = toupper(day);

    if (day != 'S' && day != 'A' && day != 'M' && day != 'T' && day != 'W' && day != 'H' && day != 'F')
    {
        printf("Error: Invalid input for current day. Please enter a valid character (S/A/M/T/W/H/F).\n");
        return 1;
    }
    dayName();
    printf("\nEnter starting budget: ");
    scanf("%f", &budget);

    if (budget < 0)
    {
        printf("Error: Invalid input for starting budget. Please enter a non-negative floating-point value.\n");
        return 1;
    }
    int choice;
    do
    {
        printf("\n\nToday is %s, %d %s\n\n", dayNames[today], date, monthNames[month]);
        if (LeapYear())
        {
            printf("This is a Leap Year.\n\n");
        }
        else
        {
            printf("This is a not a Leap Year.\n\n");
        }
        printf("\nWhat would you like to do? Select from the following\n");
        printf("1. Log income\n");
        printf("2. Log expense\n");
        if (repeatingIncome == 0)
            printf("3. Schedule repeating income\n");
        else
            printf("3. Update repeating income\n");
        if (repeatingExpense == 0)
            printf("4. Schedule repeating expense\n");
        else
            printf("4. Update repeating expense\n");
        if (repeatingRent == 0)
            printf("5. Schedule repeating rent expense\n");
        else
            printf("5. Update repeating rent expense\n");
        printf("6. Display total  daily income\n");
        printf("7. Display total daily expense\n");
        printf("8. Display current budget\n");
        printf("9. Display payables\n");
        printf("10. End the day\n");
        printf("11. Skip to end of the week\n");
        printf("12. Skip to end of the month\n");
        printf("13. Skip to end of the year\n");
        printf("14. Exit\n");
        printf("\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            // logic to log income
            printf("\nEnter amount to log income: ");
            scanf("%f", &income);
            if (income < 0)
            {
                printf("The income cannot be negative. Try again.\n");
                break;
            }
            incDate = date;
            budget += income;
            printf("Your Total budget is: PHP %.2f\n", budget);
            break;
        case 2:
            // Logic to log expense
            printf("\nEnter amount for expense: ");
            scanf("%f", &expense);
            if (expense < 0)
            {
                printf("The amount cannot be negative. Try again.\n");
                break;
            }
            if (expense > budget)
            {
                printf("Expense is greater than budget. Enter an amount less than or equal to your budget.\n");
                break;
            }
            expDate = date;
            budget -= expense;
            displayDailyExpense();
            printf("Your Total budget is: PHP %.2f\n", budget);
            break;
        case 3:
            // Logic to schedule/update repeating income
            if (repeatingIncome == 0)
                scheduleRepeatingIncome();
            else
                updateRepeatingIncome();
            break;
        case 4:
            if (repeatingExpense == 0)
                scheduleRepeatingExpense();
            else
                updateRepeatingExpense();
            break;
        case 5:
            if (repeatingRent == 0)
                scheduleRepeatingRent();
            else
                updateRepeatingRent();
            break;
        case 6:
            displayDailyIncome();
            break;
        case 7:
            displayDailyExpense();
            break;
        case 8:
            displayCurrentBudget();
            break;
        case 9:
            displayPayables();
            break;
        case 10:
            printf("==========================END OF DAY===========================\n");
            EndDay();
            printf("START DAY\n");
            printf("Today is %s, %d %s\n", dayNames[today], date, monthNames[month]);
            printf("Your Total budget is: PHP %.2f\n", budget);
            break;
        case 11:
            printf("==========================END OF WEEK===========================\n");
            EndWeek();
            printf("Today is %s, %d %s\n", dayNames[today], date, monthNames[month]);
            printf("Your Total budget is: PHP %.2f\n", budget);
            printf("Your total payables are PHP %.2f\n\n", payables);
            break;
        case 12:
            printf("==========================END OF MONTH===========================\n");
            EndMonth();
            printf("Today is %s, %d %s\n", dayNames[today], date, monthNames[month]);
            printf("Your Total budget is: PHP %.2f\n", budget);
            printf("Your total payables are PHP %.2f\n\n", payables);
            break;
        case 13:
            printf("==========================END OF YEAR===========================\n");
            EndYear();
            printf("Today is %s, %d %s\n", dayNames[today], date, monthNames[month]);
            printf("Your Total budget is: PHP %.2f\n", budget);
            printf("Your total payables are PHP %.2f\n\n", payables);
            break;
        case 14:
            printf("Exiting...\n");
            break;
        default:
            printf("Error: Invalid choice. Please enter a valid choice from the menu.\n");
            break;
        }
    } while (choice != 14);

    return 0;
}

