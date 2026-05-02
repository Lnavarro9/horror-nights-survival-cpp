#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {
    int health = 100;
    int fear = 0;
    int energy = 100;
    int time = 19; // 7 PM
    int housesCompleted = 0;
    int ridesCompleted = 0;
};

void showStatus(const Player& player);
void showMenu();
void hauntedHouse(Player& player);
void rideAttraction(Player& player);
void getFood(Player& player);
void rest(Player& player);
void randomEvent(Player& player);
bool gameOver(const Player& player);
void showEnding(const Player& player);

int main() {
    srand(time(0));

    Player player;
    int choice;

    cout << "=====================================\n";
    cout << " HALLOWEEN HORROR NIGHTS: SURVIVE\n";
    cout << "=====================================\n";
    cout << "Survive from 7 PM until 2 AM.\n";
    cout << "Keep your health, energy, and fear under control.\n";

    while (!gameOver(player)) {
        showStatus(player);
        showMenu();

        cin >> choice;

        switch (choice) {
        case 1:
            hauntedHouse(player);
            break;
        case 2:
            rideAttraction(player);
            break;
        case 3:
            getFood(player);
            break;
        case 4:
            rest(player);
            break;
        case 5:
            cout << "\nYou chose to leave the park early.\n";
            showEnding(player);
            return 0;
        default:
            cout << "\nInvalid choice. Try again.\n";
        }

        if (!gameOver(player)) {
            randomEvent(player);
        }
    }

    showEnding(player);
    return 0;
}

void showStatus(const Player& player) {
    cout << "\n---------- PLAYER STATUS ----------\n";
    cout << "Time: " << player.time << ":00\n";
    cout << "Health: " << player.health << endl;
    cout << "Fear: " << player.fear << endl;
    cout << "Energy: " << player.energy << endl;
    cout << "Haunted Houses Completed: " << player.housesCompleted << endl;
    cout << "Rides Completed: " << player.ridesCompleted << endl;
    cout << "-----------------------------------\n";
}

void showMenu() {
    cout << "\nWhat do you want to do?\n";
    cout << "1. Enter a Haunted House\n";
    cout << "2. Ride an Attraction\n";
    cout << "3. Get Food\n";
    cout << "4. Rest\n";
    cout << "5. Leave Park\n";
    cout << "Choose an option: ";
}

void hauntedHouse(Player& player) {
    cout << "\nYou enter a terrifying haunted house...\n";

    player.fear += 20;
    player.energy -= 15;
    player.time += 1;
    player.housesCompleted++;

    cout << "You survived the house, but your fear increased.\n";
}

void rideAttraction(Player& player) {
    cout << "\nYou head toward a ride to calm down...\n";

    player.fear -= 10;
    player.energy -= 10;
    player.time += 1;
    player.ridesCompleted++;

    if (player.fear < 0) {
        player.fear = 0;
    }

    cout << "The ride helped lower your fear.\n";
}

void getFood(Player& player) {
    cout << "\nYou grab food and recharge.\n";

    player.health += 15;
    player.energy += 20;
    player.time += 1;

    if (player.health > 100) {
        player.health = 100;
    }

    if (player.energy > 100) {
        player.energy = 100;
    }

    cout << "Food restored your health and energy.\n";
}

void rest(Player& player) {
    cout << "\nYou find a quiet spot to rest.\n";

    player.energy += 25;
    player.fear -= 15;
    player.time += 1;

    if (player.energy > 100) {
        player.energy = 100;
    }

    if (player.fear < 0) {
        player.fear = 0;
    }

    cout << "Rest helped you recover.\n";
}

void randomEvent(Player& player) {
    int event = rand() % 5 + 1;

    cout << "\nRandom Event: ";

    switch (event) {
    case 1:
        cout << "A scare actor jumps out at you! Fear +15\n";
        player.fear += 15;
        break;
    case 2:
        cout << "You find an energy drink! Energy +15\n";
        player.energy += 15;
        if (player.energy > 100) player.energy = 100;
        break;
    case 3:
        cout << "A long line drains your patience. Energy -10\n";
        player.energy -= 10;
        break;
    case 4:
        cout << "You found a shortcut! No penalty.\n";
        break;
    case 5:
        cout << "A chainsaw scare zone gets intense! Fear +10, Health -5\n";
        player.fear += 10;
        player.health -= 5;
        break;
    }
}

bool gameOver(const Player& player) {
    if (player.health <= 0) {
        return true;
    }

    if (player.fear >= 100) {
        return true;
    }

    if (player.energy <= 0) {
        return true;
    }

    if (player.time >= 26) { // 2 AM
        return true;
    }

    return false;
}

void showEnding(const Player& player) {
    cout << "\n========== GAME OVER ==========\n";

    if (player.health <= 0) {
        cout << "You ran out of health and had to leave the park.\n";
    }
    else if (player.fear >= 100) {
        cout << "Your fear reached 100. You panicked and left the park!\n";
    }
    else if (player.energy <= 0) {
        cout << "You ran out of energy and could not continue.\n";
    }
    else if (player.time >= 26) {
        cout << "You survived until 2 AM!\n";
    }
    else {
        cout << "You left the park early.\n";
    }

    cout << "\nFinal Stats:\n";
    cout << "Health: " << player.health << endl;
    cout << "Fear: " << player.fear << endl;
    cout << "Energy: " << player.energy << endl;
    cout << "Haunted Houses Completed: " << player.housesCompleted << endl;
    cout << "Rides Completed: " << player.ridesCompleted << endl;

    if (player.time >= 26 && player.fear < 100 && player.health > 0 && player.energy > 0) {
        cout << "\nResult: YOU SURVIVED THE NIGHT!\n";
    }
    else {
        cout << "\nResult: Better luck next night...\n";
    }

    cout << "===============================\n";
}