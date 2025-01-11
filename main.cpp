#include <curses.h>
#include <iostream>
#include <vector>

class WindowClass {
    private:
        bool has_border, isShowing;
        int cur_w, cur_h, x, y;
        WINDOW *win;
        void (*callback)(WINDOW * win); // Proper function pointer declaration

    public:
        WINDOW * getWindow() {
            return win;
        }
        
        bool IsShowing() {
            return isShowing;
        }

        void IsShowing(bool set) {
            isShowing = set;
        }

        WindowClass(int height, int width, int y, int x, bool has_border, bool isShowing, void (*_callback)(WINDOW * win)) : 
            cur_h(height),
            cur_w(width),
            y(y),
            x(x),
            has_border(has_border),
            isShowing(isShowing),            
            callback(_callback) // Direct initialization
        {
            win = newwin(cur_h, cur_w, y, x);
        }

        void Update() {
            if (isShowing) {
                callback(win); // Call the callback if the window is showing

                if (has_border) {
                    box(win, 0, 0); // Draw border if needed
                }

                wrefresh(win); // Refresh the window to update display
            }
        }
};

std::vector<WindowClass> Windows;
std::vector<std::vector<int>> WindowLayout;

void RipplePrint(WINDOW * win, const char* text, int delay) {
    for (int i = 0; text[i] != '\0'; i++) {
        mvwprintw(win, 1, 1, "%c", text[i]);
        refresh();
    }
}

void IntroMethod(WINDOW * win) {
    mvwprintw(win, 1, 1, "Welcome to the Game!");
}

void GameMethod(WINDOW * win) {
    mvwprintw(win, 1, 1, "Game is now showing!");
}

void TestMethod(WINDOW * win) {
    mvwprintw(win, 1, 1, "Testing testing...");
}

void UpdateSelected(int& selected, int row, int col, int& prevSelected) {
    // Get previous selected coords
    int prev_row = -1, prev_col = -1;
    bool prevFound = false;
    for (int i = 0; i < WindowLayout.size(); i++) {
        for (int j = 0; j < WindowLayout[i].size(); j++) {
            if (WindowLayout[i][j] == prevSelected) {
                prev_row = i;
                prev_col = j;
                prevFound = true;
                break;
            }
        }
        if (prevFound) break;
    }

    // Normal case, directly inline columns
    if (col < WindowLayout[row].size()) {
        prevSelected = selected;  // Update prevSelected
        selected = WindowLayout[row][col];
        return;
    }

    // Clarifying check, column not directly inline
    if (col >= WindowLayout[row].size()) {
        int temp = selected;
        // If moving back to the previous row, go to the same window
        if (row == prev_row) {
            selected = prevSelected;
            prevSelected = temp;
        } else {
            selected = WindowLayout[row].back();  // Move to the last item in the current row
            prevSelected = temp;
        }
        return;    
    }
}

void StartGame() {
    bool gameOn = true;
    int selected = 0;
    int prevSelected = -1;
    int cur_col, cur_row;

    bool foundSelected = false;
    for (int i = 0; i < WindowLayout.size(); i++) {
        for (int j = 0; j < WindowLayout.at(i).size(); j++) {
            if (WindowLayout[i][j] == selected) {
                cur_col = j;
                cur_row = i;
                foundSelected = true;
                break;
            }
        }
        if (foundSelected) break;
    }

    // Ensure that Windows is not empty before proceeding
    if (Windows.empty()) {
        std::cerr << "Error: No windows available." << std::endl;
        return;  // Early return if no windows to manage
    }

    while (gameOn) {
        for (int i = 0; i < Windows.size(); i++) {
            if (Windows.at(i).IsShowing() && selected != i) {
                Windows.at(i).Update();
            }
        }
        // Change color of selected window
        if (selected >= 0 && selected < Windows.size()) {
            if (Windows.at(selected).IsShowing()) {
                wattron(Windows.at(selected).getWindow(), COLOR_PAIR(2));
                Windows.at(selected).Update();
                wattroff(Windows.at(selected).getWindow(), COLOR_PAIR(2));
            }
        }

        // Do user input
        int c = getch();
        switch (c) {
            case KEY_LEFT:
                if (cur_col > 0) {
                    // Move to the previous column in the current row
                    cur_col--;
                } else {
                    // Wrap around to the last column in the current row
                    cur_col = WindowLayout[cur_row].size() - 1;
                }
                UpdateSelected(selected, cur_row, cur_col, prevSelected);
                break;

            case KEY_RIGHT:
                if (cur_col == WindowLayout[cur_row].size()-1) {
                    cur_col = 0;
                }
                else {
                    cur_col++;
                }
                UpdateSelected(selected, cur_row, cur_col, prevSelected);
                break;

            case KEY_UP:
                if (cur_row == 0) {
                    cur_row = WindowLayout.size()-1;
                } else {
                    cur_row--;
                }
                UpdateSelected(selected, cur_row, cur_col, prevSelected);
                break;

            case KEY_DOWN:
                if (cur_row == WindowLayout.size()-1) {
                    cur_row = 0;
                } else {
                    cur_row++;
                }
                UpdateSelected(selected, cur_row, cur_col, prevSelected);
                break;
            
            default:
                gameOn = false;
        }

        // Add a simple delay to prevent an infinite loop from hogging CPU resources
        napms(100);
    }
}

void TimedErrorExit(std::string errorMessage, int countdownTime) {
    printw("%s", errorMessage.c_str());
    refresh();
    for (int i = countdownTime; i > 0; i--) {
        printw("%d", i);
        refresh();
        napms(250);
        for (int j = 0; j < 3; j++) {
            printw(".");
            refresh();
            napms(250);
        }
        napms(250);
    }
}

int main() {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    // Initialize colors
    if (!has_colors()) {
        TimedErrorExit("Error: Colors not available. Closing. ", 3);
        return -1;
    }
    if (!can_change_color()) {
        TimedErrorExit("Error: Cannot change colors. Closing. ", 3);
        return -1;
    }

    init_color(COLOR_WHITE, 700, 700, 700);
    init_color(COLOR_CYAN, 1000, 1000, 1000);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    // Initialize the windows
    resize_term(80, 80);


    WindowClass Intro = WindowClass(10, 40, 0, 0, true, true, IntroMethod);
    WindowClass Game = WindowClass(13, 26, 10, 0, true, true, GameMethod);
    WindowClass Test = WindowClass(13, 14, 10, 26, true, true, TestMethod);

    WindowLayout = {
        {0},
        {1, 2}
    };

    Windows.push_back(Intro);
    Windows.push_back(Game);
    Windows.push_back(Test);

    StartGame();

    getch();
    endwin();
    return 0;
}
