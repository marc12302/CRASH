#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <ncurses.h>

using namespace std;

float generateNumber() {
    int percentage = rand() % 100 + 1;

    if (percentage <= 50) {
        return 1 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2 - 1)));
    } else if (percentage <= 70) {
        return 2 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (10 - 2)));
    } else if (percentage <= 80) {
        return 10 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (100 - 10)));
    } else {
        return 100 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1000 - 100)));
    }
}

void game(float& deposit, float current_bet) {
    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    srand(static_cast<unsigned int>(std::time(0)));

    float multiplier = 1.0;
    printw("IMPORTANT: PRESS 's' TO STOP THE MULTIPLIER AND TAKE YOUR MONEY IF YOU'RE LUCKY\n");
    refresh();
    usleep(1000000);

    float random_number = generateNumber();
    float final_multiplier = 1.0;


    for (; multiplier < 2000; multiplier += 0.01) {
        clear();

        if (multiplier > random_number) {
            attron(COLOR_PAIR(1));
            mvprintw(0, 0, "[BOOM] The multiplier crashed at x%.2f", multiplier);
            attroff(COLOR_PAIR(1));
            refresh();
            final_multiplier = 0.0;
            break;
        }

        attron(COLOR_PAIR(2));
        mvprintw(1, 0, "Multiplier: x%.2f", multiplier);
        attroff(COLOR_PAIR(2));
        refresh();
        usleep(50000);


        nodelay(stdscr, TRUE);
        int ch = getch();
        if (ch == 's') {
            final_multiplier = multiplier;
            deposit += current_bet * multiplier;
            clear();
            attron(COLOR_PAIR(2));
            mvprintw(0, 0, "You stopped at multiplier: x%.2f", multiplier);
            attroff(COLOR_PAIR(2));
            refresh();
            break;
        }
    }


    float profit = (current_bet * final_multiplier) - current_bet;
    if (final_multiplier > 0.0) {
        mvprintw(2, 0, "Your profit is: $%.2f", profit);
    } else {
        mvprintw(2, 0, "You lost your bet.");
    }

    refresh();


    nodelay(stdscr, FALSE);
    printw("\nPress any key to continue...");
    getch();

    endwin();
}

int main() {
    system("clear");

    float current_bet, deposit = 100;

    while (true) {
        cout << "[.] Your deposit is: $" << deposit << endl;
        cout << "[.] Place your bet: $";
        cin >> current_bet;

        if (current_bet > deposit) {
            cout << "[!] You can't bet more than your deposit\n";
            continue;
        }
        if (current_bet > 10000) {
            cout << "[!] Your bet can't be higher than $10,000\n";
            continue;
        }
        if (current_bet < 5) {
            cout << "[!] Your bet can't be lower than $5\n";
            continue;
        }

        deposit -= current_bet;
        game(deposit, current_bet);
        cout << "[.] Your updated deposit is: $" << deposit << endl;

        char play_again;
        cout << "[?] Do you want to play again? (y/n): ";
        cin >> play_again;
        if (play_again != 'y') {
            system("clear");
            break;
        }
    }

    cout << "Thanks for playing! Your final deposit is: $" << deposit << endl;
    return 0;
}
