
#include <iostream>
#include <cassert>
#include <sstream>
#include <array>
#include <vector>
#include <string>
#include <random>


//call a function to destroy the objects and boards at the end of the functions so that playing again is possible!!!
//DONT FORGET TO DO THIS

using namespace std;


//this clears the buffer and allows for the user to input again after wrong input
void Buffer_Clear() {
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//overloaded function that allows for two ints or two strings to be called for the message.
string invalidMessage(int a, int b) {

    string n;
    n = "\nYou have failed to input a valid number. Please give input between " + to_string(a) + " and " + to_string(b) + "...\n";
    return n;
}
string invalidMessage(string a, string b) {

    string n;
    n = "\nYou have failed to input a valid number. Please give input between " + a + " and " + b + "...\n";
    return n;
}

//converts an integer to a string based off its ASCI value
string intToAsciiString(int number) {
    char z = char(number + 65);
    string xA;
    xA.push_back(z);
    return xA;
}

//returns the ASCI num value of the cordinate so it can be checked modially
int getY(string getString) {
    int y = (toupper(getString.at(0)) - '0');
    y = y - 17;
    return y;
}
int getX(string getString) {
    int x = getString.at(1) - '0';
    x = x - 1;
    return x;
}

//bool that returns t/f if a cord inputted is in bounds
bool validateCords(string cords, int bounds) {
    int a = getY(cords);
    if (a >= 0 && a < bounds) {
        int b = getX(cords);
        if (b >= 0 && b < bounds) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

}



bool boundValidation(int boundmax, int isValid, int boundmin = 0) {
    //std::cout << "(in boundVal)testing" << boundmax << " " << boundmin;
    if (isValid < boundmin || isValid > boundmax) {
        return false;
    }
    else
    {
        return true;
    }
}



int numValidInput(int boundmax, const string inputmessage, int boundmin = 1) {
    int temp;
    const string message = inputmessage;
    std::cout << inputmessage;
    
    std::cin >> temp;
    if (std::cin.fail()) {
        std::cout << invalidMessage(boundmin, boundmax);
    }
    else if (temp < boundmin || temp > boundmax) {
        std::cout << invalidMessage(boundmin, boundmax);

    }
    else if (temp >= boundmin && temp <= boundmax) {
        //success!
        //std::cout << "Inputted " << to_string(temp) << "!";
        Buffer_Clear();
        return temp;
    }
    else {
        std::cout << invalidMessage(boundmin, boundmax);
        
    }
    Buffer_Clear();
    return numValidInput(boundmax, inputmessage, boundmin);
}


//checks if the cordinate is in a valid input
string cordValidInput(int xybound, int xymin = 1) {


    string input;
    string a = "A1";
    string b = intToAsciiString(xybound - 1) + to_string(xybound);

    while (true)
    {
        std::cout << "Input a cordinate between " << a << " and " << b << "\nCord: ";

        std::cin >> input;

        if (std::cin.fail() || input.length() > 2 || input.length() <= 0) {
            std::cout << invalidMessage(a, b);
        }
        else if (validateCords(input, xybound)) {
            //success!?
            break;
        }
        else
        {
            std::cout << invalidMessage(a, b);
            return "XX";
        }
    }
    return input;
}

//this is the grid class, it contains the grid itself, but is generated in the player class
class BattleBoatsGrid {
private:
    //the boat is defined like this so i can easily make it custumized later
    string boat = "⛵";
    int gridLength;
    vector<vector<string>> rowValues{};
    vector<string> yAlphaNames{};
    int leftBoats = 0;

    bool hideBoats = false;
    vector<vector<string>> privateBoard{};

    string generateRow(int index) {
        string rowWIP = yAlphaNames[index] + "  ";
        for (int xInP = 0; xInP < gridLength; xInP++) {
            rowWIP = rowWIP + rowValues[xInP][index] + " ";
        }
        return rowWIP + "\n";
    }
    string generateHiddenRow(int index) {
        string rowWIP = yAlphaNames[index] + "  ";
        for (int xInP = 0; xInP < gridLength; xInP++) {
            rowWIP = rowWIP + privateBoard[xInP][index] + " ";
        }
        return rowWIP + "\n";
    }

    string generateHeader(){
        string headWIP = " ";
        string temp;
        for (int i = 0; i < gridLength; i++) {
            headWIP = headWIP + "  ";
            temp = to_string(i);
            headWIP = headWIP + temp;
        }
        return headWIP + "\n";
    }

public:
    //empty constructor
    BattleBoatsGrid() {
        gridLength = 4;
    }

    //constructor
    BattleBoatsGrid(int length) {
        gridLength = length;
        for (int i = 0; i < gridLength; i++) {
            rowValues.resize(i + 1);
            for (int j = 0; j < gridLength; j++) {
                rowValues[i].resize(j + 1);
                rowValues[i][j] = "〰";
            }
        }
        for (int a = 0; a < gridLength; a++) {
            yAlphaNames.resize(a + 1);
            yAlphaNames[a] = intToAsciiString(a);
        }
    }


    void constructHiddenBoard() {
        hideBoats = true;
        for (int i = 0; i < gridLength; i++) {
            privateBoard.resize(i + 1);
            for (int j = 0; j < gridLength; j++) {
                privateBoard[i].resize(j + 1);
                privateBoard[i][j] = "〰";
            }
        }
    }
    void catchupHiddenBoard(int a, int b) {
        if (hideBoats) {
            privateBoard[a][b] = rowValues[a][b];
        }
        else {
            //do nothing
        }
    }




    //setters
    void setBoatIcon(string newBoat) {
        boat = newBoat;
    }

    void setGridLength(int length) {
        gridLength = length;
        for (int i = 0; i < gridLength; i++) {
            rowValues.resize(i + 1);
            for (int j = 0; j < gridLength; j++) {
                rowValues[i].resize(j + 1);
                rowValues[i][j] = "〰";
            }
        }
        for (int a = 0; a < gridLength; a++) {
            yAlphaNames.resize(a + 1);
            yAlphaNames[a] = intToAsciiString(a);
        }
    }


    //getters
    string getBoatIcon() const {
        return boat;
    }
    string getHeader() {
        return generateHeader();
    }
    string getRow(int i) {
        return generateRow(i);
    }
    string getHiddenRow(int i) {
        return generateHiddenRow(i);
    }
    string getRemainingBoats() {
        return to_string(leftBoats);
    }
    int getRemainingBoatsINT() {
        return leftBoats;
    }
    int getSize() {
        return gridLength;
    }


    //silly little void statments
    void addBoat(string boatCoords) {
        int yVal = getY(boatCoords);
        int xVal = getX(boatCoords);
        rowValues[yVal][xVal] = getBoatIcon();
        leftBoats++;
        catchupHiddenBoard(yVal, xVal);
    }


    void fireShot(string coordinate) {
        int yVal = getY(coordinate);
        int xVal = getX(coordinate);
        if (isBoat(yVal, xVal)) {
            std::cout << "HIT!!!!" << endl;
            rowValues[yVal][xVal] = "🔥";
            leftBoats--;
            catchupHiddenBoard(yVal, xVal);
        }
        else {
            std::cout << "Miss!" << endl;
            rowValues[yVal][xVal] = "❎";
            catchupHiddenBoard(yVal, xVal);
        }

    }

    bool winCheck() {
        if (leftBoats == 0) {
            //WIN
            return true;
        }
        else {
            //game continues
            return false;
        }
    }

    bool isBoat(int a, int b) {
        if (rowValues[a][b] == getBoatIcon()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool isGuessable(int a, int b) {
        if (rowValues[a][b] == "❎" || rowValues[a][b] == "🔥") {
            return false;
        }
        else {
            return true;
        }
    }

    bool inBounds(string input) {
        if (getY(input) <= 0 || getY(input) >= (getSize() - 1)) {
            //the Y is out of bounds
            return false;
        }
        else {
            if (getX(input) <= 1 || getY(input) >= getSize()) {
                //the X is out of bounds
                return false;
            }
            else {
                //the target is in bounds
                return true;
            }
        }
    }



    //actualy display
    string display() {
        stringstream ss;
        ss << generateHeader();
        for (int i = 0; i < gridLength; i++) {
            ss << generateRow(i);
        }
        return ss.str();
    }


    string hiddenDisplay() {
        stringstream ss;
        ss << generateHeader();
        for (int i = 0; i < gridLength; i++) {
            ss << generateHiddenRow(i);
        }
        return ss.str();
    }




};


//this is the player class, ais and players are players, and thier grids are accessed through thier playerdata.
class Player {
    friend class BattleBoatsGrid;
private:
    string name;
    bool isAI;
    int totalBoats;
    int glength;
    BattleBoatsGrid myGrid;
    int difficulty = 0;
    int failedAttacks = 0;
    string attackTarget = "B2";
    vector<string> myBoats;
    vector<string> allTargets;


public:
    //constructor
    Player(string nameP, int length, bool ai, int howmanyboats) {
        glength = length;
        name = nameP;
        isAI = ai;
        totalBoats = howmanyboats;
        myGrid.setGridLength(length);
    }
    //setters
    void setTarget(string target) {
        allTargets.clear();
        attackTarget = target;
    }
    void addTarget(string freshTarget) {
        allTargets.push_back(freshTarget);
    }

    //getters
    string getHeader() {
        return myGrid.getHeader();
    }
    string getRow(int i) {
        return myGrid.getRow(i);
    }
    string getHiddenRow(int i) {
        return myGrid.getHiddenRow(i);
    }
    int getMax() const {
        return glength;
    }
    string getName() const {
        return name;
    }
    string getRemainingBoats() {
        return myGrid.getRemainingBoats();
    }
    int getRemainingBoatsINT() {
        return myGrid.getRemainingBoatsINT();
    }
    bool isBot() const {
        return isAI;
    }
    int getDiff() const {
        return difficulty;
    }
    int getAttacks() const {
        return failedAttacks;
    }
    string showBoat(int i) {
        return myBoats[i];
    }
    string getTarget() {
        return attackTarget;
    }
    string showTarget(int i) {
        return allTargets[i];
    }
    int howManyTargets() {
        return allTargets.size();
    }
    int howManyBoats() {
        return myGrid.getRemainingBoatsINT();
    }



    string randCords() {
        srand((unsigned int)time(NULL));
        int yA = (rand() % (glength - 1));
        string input = intToAsciiString(yA);
        int xI = (rand() % (glength - 1));
        input = input + to_string(xI);
        return input;
    }

    string randBoat() {
        string input = randCords();
        int a = getY(input);
        int b = getX(input);
        if (emptyspace(a, b)) {
            return "XX";
        }
        else {
            return input;
        }
    }
    string playerCordValidation() {
        string input = cordValidInput(glength);
        int a = getY(input);
        int b = getX(input);
        if (emptyspace(a, b)) {
            return "XX";
        }
        else {
            return input;
        }
    }
    void genBoats() {
        if (totalBoats == 1) {
            if (isAI) {
                string cords = randBoat();
                myGrid.addBoat(cords);
                myBoats.push_back(cords);
            }
            else {
                //player generation
                std::cout << "Where would you like to hide your first boat?\nPosition: ";
                string input = cordValidInput(glength);
                myGrid.addBoat(input);
                myBoats.push_back(input);
            }
        }
        else {
            //for more than 1 boat
            if (isAI) {
                //ai gen pos
                for (int i = 0; i < totalBoats; i++) {
                    string cords = randBoat();
                    if (cords == "XX") {
                        i--;
                    }
                    else {
                        myGrid.addBoat(cords);
                        myBoats.push_back(cords);
                    }
                }
            }
            else {
                //player generation
                string cords;
                for (int i = 0; i < totalBoats; i++) {
                    std::cout << "Where would you like boat #" << (i + 1) << "?" << endl;
                    cords = playerCordValidation();
                    if (cords == "XX") {
                        std::cout << endl << "You have picked a coordinate that already contained a boat... Try again." << endl;
                        i--;
                    }
                    else {
                        myGrid.addBoat(cords);
                        myBoats.push_back(cords);
                        cout << ppDisplay();
                        std::cout << endl << "Boat succesfully placed at " << cords << "!" << endl;
                    }
                }
            }
        }

    }
    bool wrongPos(int a, int b) {
        if (myGrid.isGuessable(a, b)) {
            return true;
        }
        else {
            return false;
        }
    }
    bool emptyspace(int a, int b) {
        if (myGrid.isGuessable(a, b) || myGrid.isBoat(a, b)) {
            return false;
        }
        else {
            //position is Empty!!!
            return true;
        }
    }

    string ppDisplay() {
        return (name + ": \n\n" + myGrid.display());
    }


    void fireBall(string cords) {
        myGrid.fireShot(cords);
    }

    string playerAttack(Player defender) {
        std::cout << endl << getName() << ", where do you want to attack?" << endl;


    }

    //bot attack difficuly attacks
    string botAttack(Player defender) {
        if (getDiff() == 0) {
            return randCords();
        }
        //when the ai is set a difficulty of 1-9, it'll target between 9 and 1 random spaces, and a boat you own
        else if (getDiff() <= 1 && getDiff() > 9) {
            if (defender.getRemainingBoatsINT() == 1) {
                setTarget(defender.myBoats[0]);
            }
            else {
                int totalBoats = defender.getRemainingBoatsINT();
                srand((unsigned int)time(NULL));
                setTarget(defender.myBoats[(rand() % (totalBoats - 1))]);
            }
            addTarget(getTarget());
            //actually attack now 
            int exclusions = 9 - getDiff();
            for (int i = exclusions; exclusions != 0; i--) {
                string genCords = randCords();
                if (genCords == getTarget()) {
                    i++;
                    //try again
                }
                else {
                    //new target
                    addTarget(genCords);
                }
            }
            string randtarget = (showTarget((rand() % (howManyTargets() - 1))));
            return randtarget;

        }
        else {
            //cheater bot
            return (defender.myBoats[0]);

        }
        return "F6";
    }

};

Player combat(Player pA, Player pB) {
    int turns = 0;
    //determines coinflip, has a higher chance to lose the higher the difficulty.
    std::cout << endl << "Flipping a coin to determining if " << pA.getName() << " or " << pB.getName() << " goes first.";
    std::cout << endl << "💿" << endl;
    srand((unsigned int)time(NULL));
    int coinFlip = (rand() % (pB.getDiff() + ((pB.getDiff() / 2) + 1)));
    if (coinFlip <= (pB.getDiff())) {
        //lose coinflip
        std::cout << pB.getName() << " has won the coin flip!" << endl;
        turns++;
    }
    else {
        //win coinflip
        std::cout << pA.getName() << " has won the coin flip!" << endl;
    }
    while (pA.howManyBoats() <= 0 || pB.howManyBoats() <= 0) {

        if (turns % 2 == 0) {
            //player A turn


        }
        else {
            //player B turn


        }
        turns++;
    }

    return pA;
}

string pveDisplay(Player player, Player ai) {
    stringstream pve;
    pve << player.getName() + ":";
    for (int i = 0; i < player.getMax(); i++) {
        pve << " ";
    }
    pve << ai.getName() + ":";
    pve << "\n";
    pve << player.getHeader();
    pve << "   ";
    pve << ai.getHeader();
    for (int i = 0; i < player.getMax(); i++) {
        pve << player.getRow(i);
        pve << "   ";
        pve << ai.getHiddenRow(i);
    }
    return pve.str();

}



void playerVersusAI() {
    std::cout << endl << "You have selected to Play Versus Computer!" << endl;
    string msgQgrid = "How big should the grid be?   (min 4, max 26)\nGrid Size: ";
    int uniLength = numValidInput(26, msgQgrid, 4);

    int maxBoat = ((uniLength * uniLength) / 4);
    string msgQbta = "How many boats do you want to place? (min 1, max " + to_string(maxBoat) + ")\nAmount: ";
    int uniBoat = numValidInput(maxBoat, msgQbta);

    Player player("Player", uniLength, false, uniBoat);
    player.genBoats();

    Player enemyai("CPU", uniLength, false, uniBoat);
    enemyai.genBoats();

    std::cout << endl << combat(player, enemyai).getName() << " has won!" << endl;





}
void playerVersusPlayer() {
    //for pvp


}
string howToPlay() {
    //not done, wanted to make this to explain things like the AI, pvp, and basic rules if I felt like it
    return "get good or somethink idk";
}
void closeGame() {
    cerr << endl << "closing them game...";
    cerr << endl;
    exit(0);
}
int mainMenu() {
    std::cout << "(1) Play game versus Computer" << endl;
    std::cout << "(2) Play game versus Friend (locally)" << endl;
    std::cout << "(3) How to play" << endl;
    std::cout << "(4) Close game" << endl;
    //validations and navigation
    string msgQmenu = "\nYour Input: ";
    int mainMenuResult = numValidInput(4, msgQmenu);
    if (mainMenuResult == 1) {
        return 1;
    }
    else if (mainMenuResult == 2) {
        return 2;
    }
    else if (mainMenuResult == 3) {
        return 3;
    }
    else if (mainMenuResult == 4) {
        closeGame();
    }
    else {
        cerr << "error! wrong result on main menu!";
        closeGame();
    }
    return 66;
}

string cordValidAttackInput(Player attacker, Player Defender) {
    if (attacker.isBot()) {
        //bot attack
        string botattack;


    }
    else {
        string input;
        string msgQcord;
        string a;
        string b;
        int c;
        int d;
        do {
            a = "A1";
            b = intToAsciiString(attacker.getMax()) + to_string(attacker.getMax());
            msgQcord = attacker.getName() + ", where would you to attack?\nposition: ";
            std::cin >> input;
            if (std::cin.fail()) {
                std::cout << invalidMessage(a, b);
            }
            else if (validateCords(input, attacker.getMax())) {
                std::cout << invalidMessage(a, b);
            }
            else {
                c = getY(input);
                d = getX(input);
                if (attacker.emptyspace(c, d)) {
                    //number is not guessable
                    std::cout << "You have entered in a number that was already guessed...";
                }
                else {
                    //success!?
                    break;
                }
            }
        } while (validateCords(input, attacker.getMax()));
        return input;
    }
    return "XX";
}
void damageCalc(Player attacker, Player defender) {
    string input = cordValidAttackInput(attacker, defender);
    defender.fireBall(input);
    if (defender.getRemainingBoatsINT() == 0) {
        //winner!!!
    }
    else {
        std::cout << defender.getName() << " has " << defender.getRemainingBoats() << " remaining boats...";
    }
}

int main() {
    int uniLength = 4;
    string temp;
    bool gameloop = true;

    std::cout << "GREETINGS!" << endl;
    std::cout << "Welcome to BATTLEBOATS!         (jk-edition)" << endl;

    while (gameloop) {
        int menu = mainMenu();
        if (menu == 1) {
            //add an intro message that says which optio n you chose
            playerVersusAI();
            std::cout << endl;
        }
        else if (menu == 2) {
            playerVersusPlayer();
            std::cout << endl;
        }
        else if (menu == 3) {
            std::cout << howToPlay();
            std::cout << endl;
        }
        else {
            cerr << "error! wrong result on main menu!";
            closeGame();
        }
    }
    std::cerr << "ERROR exited gameloop";


    ////everything past is here is old test code.

    //std::cout << endl << endl;

    //string msgQgrid = "How big should the grid be?   (min 4, max 26)\nGrid Size: ";
    //uniLength = numValidInput(26, msgQgrid, 4);

    //std::cout << "How big should the grid be?   (min 4, max 26)" << endl;
    //std::cout << "Grid Size: ";
    ////add validation
    //std::cin >> temp;
    //uniLength = stoi(temp);


    //std::cout << endl << endl;

    //BattleBoatsGrid playerGrid(4);

    //Player player("Player", uniLength, false, 3);


    //BattleBoatsGrid grid(4);
    //grid.addBoat("D3");
    //grid.addBoat("A1");
    //std::cout << grid.display();
    //grid.fireShot("B2");
    //grid.fireShot("A1");
    //std::cout << grid.display();

    return 0;
}
