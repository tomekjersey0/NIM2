#include <curses.h>
#include <iostream>
#include <vector>
#include <chrono>

enum MODE {
    MOVING, INTERACTING
};

enum COLOR {
    NORMAL = 1,
    SELECTED_MOVING = 2,
    SELECTED_INTERACTING = 3
};

class RipplePrint;

class WindowClass {
    private:
        bool has_border, isShowing, isSelectable;
        int cur_w, cur_h, x, y, std_unit;
        COLOR BorderColor;
        WINDOW *win;
        void (*content)(WindowClass * win); // Proper function pointer declaration
        std::vector<RipplePrint*> Ripples;

        std::vector<WindowClass> * Windows;

    public:
        WindowClass(std::vector<WindowClass> * _Windows, const int _std_unit, int height, int width, int _y, int _x,  void (*_content)(WindowClass * parent) = nullptr,  bool isSelectable = true, bool isShowing = true, bool has_border = true) : 
            Windows(_Windows),
            std_unit(_std_unit),
            y(_y),
            x(_x),
            has_border(has_border),
            isShowing(isShowing),
            isSelectable(isSelectable),
            content(_content) // Direct initialization
        {
            win = nullptr;
            cur_h = height * std_unit;
            cur_w = width * std_unit * 2;
            y = _y * std_unit;
            x = _x * std_unit * 2;

            Windows->push_back(*this);
        }

        std::vector<RipplePrint*> getRipples();
        void setBorderColor(COLOR color);
        void AddRipple(RipplePrint* rip);
        WINDOW * getWindow();
        void InitWindow();
        void Normalize(int x_offset, int y_offset);
        void setSize(int height_stdunit, int width_stdunit);
        void setPos (int x_stdunit, int y_stdunit);
        int getRippleCount();
        int getHeight();       
        int getWidth();
        int getX();
        int getY();
        bool IsShowing();
        void IsShowing(bool set);
        bool IsSelectable();
        void IsSelectable (bool set) ;
        void Update();
};

void TimedErrorExit(std::string message, int countdownTime=3);
void SetTerminalSize(std::vector<WindowClass>& Windows);

std::vector<WindowClass> Windows;
std::vector<std::vector<int>> WindowLayout;

class RipplePrint 
{
    private:
        std::string text, nowText;
        int progress, x, y;
        bool done, looping;
        double delay, interval;
        COLOR color;
        std::chrono::_V2::system_clock::time_point startTime;
        WindowClass * parent;
        WINDOW * win;

    public:
        std::chrono::_V2::system_clock::time_point getStartTime() {
            return startTime;
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

        std::string getText() {
            return text;
        }

        RipplePrint(WindowClass * _parent, int _y, int _x, std::string _text,double _interval = -1, double _delay=0.05, COLOR _color=COLOR::NORMAL) : 
            parent(_parent),
            text(_text),
            x(_x),
            y(_y),
            delay(_delay),
            color(_color),
            interval(_interval)
        {
            startTime = std::chrono::system_clock::now();
            progress = 0;
            parent->AddRipple(this);
            win = parent->getWindow();
            nowText = "";
            if (_interval < 0 /* so is -1 or bogus value*/) {
                // assume it hasn't been set
                looping = false;
            }
            else {
                looping = true;
            }
        }

        void eraseRipple() {
            std::string textBlank;
            for (int i = 0; i < text.length(); i++) {
                textBlank += " ";
            }
            mvwprintw(win, y, x, textBlank.c_str());
        }

        void restartRipple() {
            eraseRipple();
            done = false;
            progress = 0;
            nowText = "";
        }

        void Update() {
            auto now = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed = now - startTime;
            double elapsedSeconds = elapsed.count();

            if (elapsedSeconds >= delay && !done) {
                nowText += text[progress];
                mvwprintw(win, y, x, nowText.c_str());
                startTime = std::chrono::system_clock::now();
                progress++;
                if (progress == text.length()) {
                    done = true;
                    progress = 0;
                }
            }

            if (looping && done) {
                if (elapsedSeconds >= interval) {
                    restartRipple();
                }
            }
        }

};

std::vector<RipplePrint*> WindowClass::getRipples() {
    return Ripples;
}

void WindowClass::setBorderColor(COLOR color) {
    BorderColor = color;
}

void WindowClass::AddRipple(RipplePrint* rip) {
    Ripples.push_back(rip);
}

WINDOW * WindowClass::getWindow() {
    return win;
}

void WindowClass::InitWindow() {
    if (win == nullptr) {
        win = newwin(cur_h, cur_w, y, x); 

        // running content in here instead of in the constructor so that that the callback can use fully updated values
        // possible dynamic content positioning and rendering
        if (content) {
            content(this); // Function that adds all the objects to the be display to the window on initialization
        }
    }
    else {
        std::cerr << "Window has already been initialized" << std::endl;
    }
}

void WindowClass::Normalize(int x_offset, int y_offset) {
    x -= x_offset;
    y -= y_offset;
}

void WindowClass::setSize(int height_stdunit, int width_stdunit) {
    cur_h = height_stdunit * std_unit;
    cur_w = width_stdunit * std_unit;
    resize_window(win, cur_h, cur_w);
}

void WindowClass::setPos (int x_stdunit, int y_stdunit) {
    int _x = x_stdunit * std_unit;
    int _y = y_stdunit * std_unit;
    if (mvwin(win, _y, _x) != ERR) {
        x = _x;
        y = _y;
    }
}

int WindowClass::getHeight() {
    return cur_h;
}        

int WindowClass::getRippleCount() {
    return Ripples.size();
}

int WindowClass::getWidth() {
    return cur_w;
}

int WindowClass::getX() {
    return x;
}

int WindowClass::getY() {
    return y;
}

bool WindowClass::IsShowing() {
    return isShowing;
}

void WindowClass::IsShowing(bool set) {
    isShowing = set;
}

bool WindowClass::IsSelectable() {
    return isSelectable;
}

void WindowClass::IsSelectable (bool set) {
    isSelectable = set;
}

void WindowClass::Update() {
    if (isShowing) {
        if (has_border) {
            wattron(win, COLOR_PAIR(BorderColor));
            box(win, 0, 0); // Draw border if needed
            wattroff(win, COLOR_PAIR(BorderColor));
        }
        //auto now = std::chrono::system_clock::now();

        for (auto rip : Ripples) {
            rip->Update();
        }

        //std::chrono::duration<double> elapsed2 = now - std::chrono::system_clock::now();
        //double elapsedSeconds2 = elapsed2.count();
        //mvwprintw(win, 1, 1, "all ripples time: %f seconds / ripple count: %d", elapsed2, Ripples.size());

        wrefresh(win); // Refresh the window to update display
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

void MoveWindow(int KEY_DIR, std::vector<std::vector<int>> WindowLayoutC, int& cur_row, int& cur_col) {
    switch (KEY_DIR) {
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
}

void StartGame() {
    if (WindowLayout.empty() || Windows.empty()) {
        TimedErrorExit("Error: Window layout or windows list is empty.");
        return;
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
                Windows[i].setBorderColor(COLOR::NORMAL);
                Windows[i].Update();
            }
        }

        // Highlight the selected window
        if (selected >= 0 && selected < Windows.size() && Windows[selected].IsShowing()) {
            switch (mode) {
                case MODE::MOVING:
                    Windows[selected].setBorderColor(COLOR::SELECTED_MOVING);
                    break;
                case MODE::INTERACTING:
                    Windows[selected].setBorderColor(COLOR::SELECTED_INTERACTING);
                    break;

            }
            Windows[selected].Update();
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
            MoveWindow(c, WindowLayoutC, cur_row, cur_col);
        } else
        // Interact with the window if the mode is different
        if (mode == MODE::INTERACTING) {
            // Press ESCAPE to exit to moving mode
            if (c == 27) {
                mode = MODE::MOVING;
            }
        }

        // Update selected
        UpdateSelected(selected, cur_row, cur_col, WindowLayoutC);

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
        return -1;
    }
    if (!can_change_color()) {
        TimedErrorExit("Error: Cannot change colors. Closing. ");
        return -1;
    }

    init_color(COLOR_WHITE, 700, 700, 700);
    // * Makes the selected window color be a brighter white
    // init_color(COLOR_CYAN, 1000, 1000, 1000);

    // Default text Color
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    // Moving selected color
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    // Interacting selected color
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

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

    WindowClass(&Windows, std_unit, 1, 4, 0, 0, [](WindowClass* parent) {
        new RipplePrint(parent, 2, 2, "Intro", 1);
    });

    WindowClass(&Windows, std_unit, 2, 3, 1, 0, [](WindowClass* parent) {
        new RipplePrint(parent, 2, 2, "Game", 0.5);
    });

    WindowClass(&Windows, std_unit, 2, 1, 1, 3, [](WindowClass* parent) {
        new RipplePrint(parent, 2, 2, "Select", 2);
    });

    WindowClass(&Windows, std_unit, 1, 4, 3, 0, [](WindowClass* parent) {
        new RipplePrint(parent, 2, 2, "Score");
    });

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
