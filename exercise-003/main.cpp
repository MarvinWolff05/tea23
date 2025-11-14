#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>

enum class State
{
    Closed,          // Garagentor zu
    Open,            // Garagentor offen
    MovingUp,        // Fahre hoch
    MovingDown,      // Fahre runter
    StoppedUp,       // Stop auf dem Weg nach oben
    StoppedDown      // Stop auf dem Weg nach unten
};

const char* to_string(State s)
{
    switch (s)
    {
    case State::Closed:      return "Garagentor zu";
    case State::Open:        return "Garagentor offen";
    case State::MovingUp:    return "Fahre hoch";
    case State::MovingDown:  return "Fahre runter";
    case State::StoppedUp:   return "Stop auf dem Weg nach oben";
    case State::StoppedDown: return "Stop auf dem Weg nach unten";
    }
    return "Unbekannt";
}

// Übergangslogik des Automaten
void handle_event(State& state, bool button, bool limitTop, bool limitBottom)
{
    switch (state)
    {
    case State::Open:
        if (button)
            state = State::MovingDown;
        break;

    case State::Closed:
        if (button)
            state = State::MovingUp;
        break;

    case State::MovingDown:
        if (limitBottom)               // Endschalter unten
            state = State::Closed;
        else if (button)               // Taste während der Fahrt
            state = State::StoppedDown;
        break;

    case State::MovingUp:
        if (limitTop)                  // Endschalter oben
            state = State::Open;
        else if (button)               // Taste während der Fahrt
            state = State::StoppedUp;
        break;

    case State::StoppedDown:
        if (button)                    // Taste: Richtung umkehren
            state = State::MovingUp;
        break;

    case State::StoppedUp:
        if (button)                    // Taste: Richtung umkehren
            state = State::MovingDown;
        break;
    }
}

auto main(int /*argc*/, char** argv) -> int
{
    fmt::print("Garage Controller gestartet ({})\n", argv[0]);

    State state = State::Closed;   // Startzustand: Tor zu

    fmt::print("Befehle:\n");
    fmt::print("  t = Taste druecken\n");
    fmt::print("  o = Endschalter oben wird betaetigt\n");
    fmt::print("  u = Endschalter unten wird betaetigt\n");
    fmt::print("  q = Programm beenden\n\n");

    char cmd{};
    while (true)
    {
        fmt::print("\nAktueller Zustand: {}\n", to_string(state));
        fmt::print("Eingabe [t/o/u/q]: ");
        std::cin >> cmd;

        if (!std::cin)
            break;
        if (cmd == 'q')
            break;

        bool button      = (cmd == 't');
        bool limitTop    = (cmd == 'o');
        bool limitBottom = (cmd == 'u');

        handle_event(state, button, limitTop, limitBottom);
    }

    fmt::print("\nProgramm beendet.\n");
    return 0;
}
