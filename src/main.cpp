#include "WindowClass.h"
#include "RipplePrint.h"
#include "RippleList.h"
#include "RippleItem.h"

void TimedErrorExit(std::string message, int countdownTime=3);
void SetTerminalSize(std::vector<WindowClass>& Windows);

std::vector<WindowClass> Windows;
std::vector<std::vector<int>> WindowLayout;

void UpdateSelected(int& selected, int row, int col, std::vector<std::vector<int>> WindowLayoutC) {
    // Ensure row and col are within bounds
    if (row < 0 || row >= WindowLayoutC.size() || col < 0 || col >= WindowLayoutC[row].size()) {
        std::cerr << "Invalid row or column in UpdateSelected: row=" << row << ", col=" << col << std::endl;
        return;
    }

    // Update selected
    selected = WindowLayoutC[row][col];
}

void MoveWindow(int KEY_DIR, const std::vector<std::vector<int>>& WindowLayoutC, int& cur_row, int& cur_col, int& selected) {
    switch (KEY_DIR) {
        case 'h':
        case KEY_LEFT:
            if (cur_col > 0) {
                cur_col--;
            } else {
                cur_col = WindowLayoutC[cur_row].size() - 1; // Wrap to the last column
            }
            break;
        case 'l':
        case KEY_RIGHT:
            if (cur_col < WindowLayoutC[cur_row].size() - 1) {
                cur_col++;
            } else {
                cur_col = 0; // Wrap to the first column
            }
            break;
        case 'k':
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
        case 'j':
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

    UpdateSelected(selected, cur_row, cur_col, WindowLayoutC);
}

void StartGame() {
    if (WindowLayout.empty() || Windows.empty()) {
        TimedErrorExit("Error: Window layout or windows list is empty.");
    }

    for (auto& window : Windows) {
        if (window.getWindow() == nullptr) {
            TimedErrorExit("Error: 1 or more windows haven't been initialzed");
        }
    }

    bool gameOn = true;
    MODE mode = MODE::MOVING;
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
    }

    while (gameOn) {

        // Update all windows
        for (int i = 0; i < Windows.size(); i++) {
            if (!Windows[i].IsShowing())
                continue;
            if (i == selected) {
                if (mode == MODE::MOVING) {
                    Windows[i].setBorderColor(COLOR::SELECTED_MOVING);
                } else if (mode == MODE::INTERACTING) {
                    Windows[i].setBorderColor(COLOR::SELECTED_INTERACTING);
                }
            } else {
                Windows[i].setBorderColor(COLOR::NORMAL);
            }
            Windows[i].Update();
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

        // Move the window if in move window mode
        if (mode == MODE::MOVING) {
            // Press ENTER to interact with the selected window
            if (c == 10) {
                mode = MODE::INTERACTING;
            }
            MoveWindow(c, WindowLayoutC, cur_row, cur_col, selected);
        } else

        // Interact with the window if the mode is different
        if (mode == MODE::INTERACTING) {
            // Press ESCAPE to exit to moving mode
            if (c == 27) {
                mode = MODE::MOVING;
            }
        }
      
        if (c == 'q') {
            gameOn = false;
        }

        if (c == KEY_RESIZE) {
            SetTerminalSize(Windows);
            refresh();
        }

        napms(10);
    }
}

void TimedErrorExit(std::string errorMessage, int countdownTime /* = 3*/) {
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
    std::exit(EXIT_FAILURE);
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
            // Finally Initialize the window after its x and y positions are definitely within terminal bounds
            window.InitWindow();
        }
    }
    else {
        for (auto& window: Windows) {
            // Make sure to initialize the windows anyway if they haven't been normalized
            window.InitWindow();
        }
    }

    resize_term(termHeight, termWidth);
}

void InitColors() {
    // Make sure ts matches the enum COLOR in enums.h
    init_color(COLOR_WHITE, 700, 700, 700);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_CYAN, COLOR_BLACK);
    init_pair(9, COLOR_YELLOW, COLOR_BLACK);    
}

int main() {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    
    // Initialize colors
    if (!has_colors()) {
        TimedErrorExit("Error: Colors not available. Closing. ");
    }
    if (!can_change_color()) {
        TimedErrorExit("Error: Cannot change colors. Closing. ");
    }

    InitColors();

    // Input layout data based on the windows defined immediately later
    WindowLayout = {
        {0},
        {1, 2},
        {3}
    };

    // Just makes it so that after resizing to the right size, everything renders just fine. 
    // Not sure why or how this works, but it does, so that's that.
    resize_term(1000, 1000);

    WindowClass(&Windows, 1, 4, 0, 0, [](WindowClass* parent) {
        new RipplePrint(parent, 2, 2, "Intro", 2, COLOR::RED);
        new RippleList(parent, 4, 3, [](RippleList* parent) {
            new RippleItem(parent, "Start", COLOR::GREEN);
            new RippleItem(parent, "Settings", COLOR::YELLOW);
            new RippleItem(parent, "Exit", COLOR::RED);
        }, 2, ORIENTATION::VERTICAL);
    });

    WindowClass(&Windows, 2, 3, 1, 0, [](WindowClass* parent) {
        new RipplePrint(parent, 2, 2, "Game", 2, COLOR::GREEN);
        new RipplePrint(parent, 3, 2, "Settings", 2, COLOR::YELLOW);
        new RipplePrint(parent, 4, 2, "Exit", 2, COLOR::RED);
    });

    WindowClass(&Windows, 2, 1, 1, 3, [](WindowClass* parent) {
        new RipplePrint(parent, 2, 2, "Select", 1.7, COLOR::BLUE);
    });

    WindowClass(&Windows, 1, 4, 3, 0, [](WindowClass* parent) {
        new RipplePrint(parent, 2, 2, "Score", 1.7, COLOR::MAGENTA);
    });
    // Sets size of terminal based on physical orientation of the windows in the Windows list
    // * Make sure to run this method before refreshing any windows using this system!
    // * Otherwise the windows will not be set and won't render!
    // * Program will probably also crash!
    SetTerminalSize(Windows);

    StartGame();

    getch();
    endwin();
    return 0;
}
