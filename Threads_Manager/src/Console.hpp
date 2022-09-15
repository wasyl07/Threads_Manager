#pragma once
#include <iostream>
#include <string>

using namespace std;

class Console_Handler{
    private:

    string new_message{};

    public:
    Console_Handler()
    {
        cout << "Console Initialized!";
    }
    void Display(string message_to_display)
    {
        cout << message_to_display;
    }
    void Acquire()
    {
        cin >> new_message;
    }
};