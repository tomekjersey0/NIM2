#include <curses.h>
#include <iostream>
#include <vector>

void TimedErrorExit(std::string message, int countdownTime);

class WindowClass {
    private:
        bool has_border, isShowing, isSelectable;
        int cur_w, cur_h, x, y, std_unit;
        WINDOW *win;
        void (*callback)(WINDOW * win); // Proper function pointer declaration


    public:
        WindowClass(const int _std_unit, int height, int width, int _y, int _x,  void (*_callback)(WINDOW * win) = nullptr,  bool isSelectable = true, bool isShowing = true, bool has_border = true) : 
            std_unit(_std_unit),
            y(_y),
            x(_x),
            has_border(has_border),
            isShowing(isShowing),
            isSelectable(isSelectable),
            callback(_callback) // Direct initialization
        {
            cur_h = height * std_unit;
            cur_w = width * std_unit * 2;
            y = _y * std_unit;
            x = _x * std_unit * 2;
            // Create the window only after the x, y, and dimension values have been properly normalized
            //win = newwin(cur_h, cur_w, y, x);
        }

        WINDOW * getWindow() {
            return win;
        }

        void InitWindow() {
            if (win != nullptr) {
                win = newwin(cur_h, cur_w, y, x); 
            }
            else {
                std::cerr << "Window has already been initliazed" << std::endl;
            }
        }

        void Normalize(int x_offset, int y_offset) {
            x -= x_offset;
            y -= y_offset;
        }

        void setSize(int height_stdunit, int width_stdunit) {
            cur_h = height_stdunit * std_unit;
            cur_w = width_stdunit * std_unit;
            resize_window(win, cur_h, cur_w);
        }

        void setPos (int x_stdunit, int y_stdunit) {
            x = x_stdunit * std_unit;
            y = y_stdunit * std_unit;
            mvwin(win, y, x);
        }

        int getHeight() {
            return cur_h;
        }        

        int getWidth() {
            return cur_w;
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }
        
        bool IsShowing() {
            return isShowing;
        }

        void IsShowing(bool set) {
            isShowing = set;
        }

        bool IsSelectable() {
            return isSelectable;
        }

        void IsSelectable (bool set) {
            isSelectable = set;
        }

        void Update() {
            if (isShowing) {
                // Unnecessary really but you never know what would happen uhhh
                if (win == nullptr) {
                    // commented out because this lowk annoying asllll
                    // * Replaced by checking for nullptr win at the beginning of StartGame
                    //TimedErrorExit("Error: win is nullptr in Update()");
                    return;
                }

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

void SelectionMethod(WINDOW * win) {
    mvwprintw(win, 1, 1, "Choose your move:");
}

void ScoreMethod(WINDOW * win) {
    mvwprintw(win, 1, 1, "Score shown here...");
}

void UpdateSelected(int& selected, int row, int col, std::vector<std::vector<int>> WindowLayoutC) {
    // Ensure row and col are within bounds
    if (row < 0 || row >= WindowLayoutC.size() || col < 0 || col >= WindowLayoutC[row].size()) {
        std::cerr << "Invalid row or column in UpdateSelected: row=" << row << ", col=" << col << std::endl;
        return;
    }

    // Update selected
    selected = WindowLayoutC[row][col];
}

void StartGame() {
    if (WindowLayout.empty() || Windows.empty()) {
        TimedErrorExit("Error: Window layout or windows list is empty.");
        return;
    }

    for (auto& window : Windows) {
        if (window.getWindow() == nullptr) {
            TimedErrorExit("Error: 1 or more windows havent been initialzed");
        }
    }

    bool gameOn = true;
    int selected; // Default to the first selectable window
    int cur_row, cur_col; // Set based on selected

    // Determine selected on first available selectable window
    bool selectedFound = false;
    for (int i = 0; i < WindowLayout.size(); i++) {
        for (int j = 0; j < WindowLayout[i].size(); j++) {
            if (Windows[WindowLayout[i][j]].IsSelectable()) {
                selected = WindowLayout[i][j];
                selectedFound = true;
                break;
            }
        }
        if (selectedFound) break;
    }
    // Exit if none of the windows are selectable
    if (!selectedFound) {
        TimedErrorExit("Error: No windows are selectable. Closing. ");
        gameOn = false;
        return;
    }

    while (gameOn) {
        int w, h;
        getmaxyx(stdscr, h, w);
        mvprintw(0, 50, "term width: %d, height: %d", w, h);

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

        // Prepare WindowLayout Copy, adding only selectable windows
        std::vector<std::vector<int>> WindowLayoutC;

        // Update Copy based on selected states of Windows
        for (int i = 0; i < WindowLayout.size(); i++) {
            std::vector<int> Row;
            for (int j = 0; j < WindowLayout[i].size(); j++) {
                if (Windows[WindowLayout[i][j]].IsSelectable()) {
                    Row.push_back(WindowLayout[i][j]);
                }
            }
            if (!Row.empty()) WindowLayoutC.push_back(Row);
        }

        bool foundRowCol = false;
        // Get row and column of currently selected window
        for (int i = 0; i < WindowLayoutC.size(); i++) {
            for (int j = 0; j < WindowLayoutC[i].size(); j++) {
                if (WindowLayoutC[i][j] == selected) {
                    cur_row = i;
                    cur_col = j;
                    foundRowCol = true;
                    break;
                }
            }
            if (foundRowCol) break;
        }
        
        // Handle user input
        int c = getch();
        switch (c) {
            case KEY_LEFT:
                if (cur_col > 0) {
                    cur_col--;
                } else {
                    cur_col = WindowLayoutC[cur_row].size() - 1; // Wrap to the last column
                }
                break;
            case KEY_RIGHT:
                if (cur_col < WindowLayoutC[cur_row].size() - 1) {
                    cur_col++;
                } else {
                    cur_col = 0; // Wrap to the first column
                }
                break;

            case KEY_UP:
                if (cur_row > 0) {
                    cur_row--;
                } else {
                    cur_row = WindowLayoutC.size() - 1; // Wrap to the last row
                }

                // Adjust column index if the new row has fewer columns
                if (cur_col >= WindowLayoutC[cur_row].size()) {
                    cur_col = WindowLayoutC[cur_row].size() - 1;
                }
                break;
            case KEY_DOWN:
                if (cur_row < WindowLayoutC.size() - 1) {
                    cur_row++;
                } else {
                    cur_row = 0; // Wrap to the first row
                }

                // Adjust column index if the new row has fewer columns
                if (cur_col >= WindowLayoutC[cur_row].size()) {
                    cur_col = WindowLayoutC[cur_row].size() - 1;
                }
                break;
        }

        // Update selected
        UpdateSelected(selected, cur_row, cur_col, WindowLayoutC);
    }
}

void TimedErrorExit(std::string errorMessage, int countdownTime=3) {
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

void SetTerminalSize(std::vector<WindowClass>& Windows) {
    int lowest_y = Windows[0].getY(), lowest_x = Windows[0].getX(),
        highest_x_width = 0, highest_y_height = 0;
    for (auto& window : Windows) {
        // find lowest x and y values
        if (window.getY() < lowest_y) {
            lowest_y = window.getY();
        }
        if (window.getX() < lowest_x) {
            lowest_x = window.getX();
        }
        // find highest x + width and y + height values
        if (window.getX() + window.getWidth() > highest_x_width) {
            highest_x_width = window.getX() + window.getWidth();
        }
        if (window.getY() + window.getHeight() > highest_y_height) {
            highest_y_height = window.getY() + window.getHeight();
        }
    }
    // get size of terminal
    int termWidth = highest_x_width - lowest_x;
    int termHeight = highest_y_height - lowest_y;
    // normalize positions
    if (lowest_x != 0 || lowest_y != 0) {
        for (auto& window : Windows) {
            window.Normalize(lowest_x, lowest_y);
            // Finally Initialze the window after its x and y positions are definately within terminal bounds
            window.InitWindow();
        }
    }
    else {
        for (auto& window: Windows) {
            // Make sure to initilaze the windows anyway if they haven't been normalized
            window.InitWindow();
        }
    }

    resize_term(termHeight, termWidth);
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
        TimedErrorExit("Error: Colors not available. Closing. ");
        return -1;
    }
    if (!can_change_color()) {
        TimedErrorExit("Error: Cannot change colors. Closing. ");
        return -1;
    }

    init_color(COLOR_WHITE, 700, 700, 700);
    // * Makes the selected window color be a brighter white
    // init_color(COLOR_CYAN, 1000, 1000, 1000);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    // Input layout data based on the windows defined immediately later
    WindowLayout = {
        {0},
        {1, 2},
        {3}
    };

    // Just makes it so that after resizing to the right size, everything renders just fine. 
    // Not sure why or how this works, but it does, so that's that.
    resize_term(1000, 1000);

    const int std_unit = 10;
    //                             2, 3 --> 1, 4                    // Selectable, Showing, Border
    Windows.push_back(WindowClass(std_unit, 1, 4, 1, 2, IntroMethod));
    Windows.push_back(WindowClass(std_unit, 2, 3, 2, 2, GameMethod));
    Windows.push_back(WindowClass(std_unit, 2, 1, 2, 5, SelectionMethod));
    Windows.push_back(WindowClass(std_unit, 1, 4, 4, 2, ScoreMethod));

    // Sets size of terminal based on physical orientation of the windows in the Windows list
    // * Make sure to run this method before refreshing any windows using this system!
    // * Otherwise the windows will not be set and won't render!
    // * Program will probably also crash!
    SetTerminalSize(Windows);

    StartGame();

    getch();
    for (int i = 0; i < Windows.size(); i++) {
        delwin(Windows[i].getWindow());
    }
    endwin();
    return 0;
}