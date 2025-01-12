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

        WindowClass(int height, int width, int y, int x, bool has_border, bool isShowing, void (*_callback)(WINDOW * win) = nullptr) : 
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
                if (callback) {
                    callback(win); // Call the callback if the window is showing
                }

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

void UpdateSelected(int& selected, int row, int col) {
    // Ensure row and col are within bounds
    if (row < 0 || row >= WindowLayout.size() || col < 0 || col >= WindowLayout[row].size()) {
        std::cerr << "Invalid row or column in UpdateSelected: row=" << row << ", col=" << col << std::endl;
        return;
    }

    // Update selected
    selected = WindowLayout[row][col];
}

void StartGame() {
    if (WindowLayout.empty() || Windows.empty()) {
        std::cerr << "Error: Window layout or windows list is empty." << std::endl;
        return;
    }

    bool gameOn = true;
    int selected = WindowLayout[0][0]; // Default to the first window
    int cur_row = 0, cur_col = 0;

    while (gameOn) {
        // Update all windows except the currently selected one
        for (int i = 0; i < Windows.size(); i++) {
            if (i != selected && Windows[i].IsShowing()) {
                Windows[i].Update();
            }
        }

        // Highlight the selected window
        if (selected >= 0 && selected < Windows.size() && Windows[selected].IsShowing()) {
            wattron(Windows[selected].getWindow(), COLOR_PAIR(2));
            Windows[selected].Update();
            wattroff(Windows[selected].getWindow(), COLOR_PAIR(2));
        }

        // Handle user input
        int c = getch();
        switch (c) {
            case KEY_LEFT:
                if (cur_col > 0) {
                    cur_col--;
                } else {
                    cur_col = WindowLayout[cur_row].size() - 1; // Wrap to the last column
                }
                break;

            case KEY_RIGHT:
                if (cur_col < WindowLayout[cur_row].size() - 1) {
                    cur_col++;
                } else {
                    cur_col = 0; // Wrap to the first column
                }
                break;

            case KEY_UP:
                if (cur_row > 0) {
                    cur_row--;
                } else {
                    cur_row = WindowLayout.size() - 1; // Wrap to the last row
                }

                // Adjust column index if the new row has fewer columns
                if (cur_col >= WindowLayout[cur_row].size()) {
                    cur_col = WindowLayout[cur_row].size() - 1;
                }
                break;

            case KEY_DOWN:
                if (cur_row < WindowLayout.size() - 1) {
                    cur_row++;
                } else {
                    cur_row = 0; // Wrap to the first row
                }

                // Adjust column index if the new row has fewer columns
                if (cur_col >= WindowLayout[cur_row].size()) {
                    cur_col = WindowLayout[cur_row].size() - 1;
                }
                break;

            default:
                gameOn = false;
                continue;
        }

        // Update selected
        UpdateSelected(selected, cur_row, cur_col);
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
   // init_color(COLOR_CYAN, 1000, 1000, 1000);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    // Initialize the windows
    resize_term(80, 80);


    WindowClass Intro = WindowClass(10, 30, 0, 0, true, true, IntroMethod);
    WindowClass Game = WindowClass(13, 26, 10, 0, true, true, GameMethod);
    WindowClass Test = WindowClass(13, 14, 10, 26, true, true);
    WindowClass Test2 = WindowClass(10, 15, 0, 30, true, true);
    WindowClass Test3 = WindowClass(10, 12, 0, 45, true, true);


    WindowLayout = {
        {0, 3, 4},
        {1, 2}
    };

    Windows.push_back(Intro);
    Windows.push_back(Game);
    Windows.push_back(Test);
    Windows.push_back(Test2);
    Windows.push_back(Test3);


    StartGame();

    getch();
    endwin();
    return 0;
}
