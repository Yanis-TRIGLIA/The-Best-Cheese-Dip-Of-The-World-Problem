#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cassert>
#include <atomic>
#include <experimental/random>

using namespace std;
unsigned nbKitchenAssistantsWaitingForHelps = 0;
unsigned nbCheeseHuntersThatCameBack = 0;
mutex kitchenAssistantsMutex;
mutex cheeseHuntersMutex;
mutex threeStarsSwissChefMutex;


void getHelp(){}

void helpKitchenAssistants(){}

void giveCheese(){}

void prepareCheeseFondue(){}

void commingBackFromCheeseHunt(){
    cheeseHuntersMutex.lock();
    ++nbCheeseHuntersThatCameBack;
    cheeseHuntersMutex.unlock();
}

void cheeseHunter(unsigned i){
    //the cheese hunter is seeking for the best cheese.
    chrono::microseconds val (experimental::fundamentals_v2::randint(2000, 20000));
    this_thread::sleep_for(val);
    commingBackFromCheeseHunt();
    /*
     * ToDo : waint until threeStarsSwissChef call prepareCheeseFondue then call giveCheese
     */
    cout << "je suis le chasseur de fromage N°: " << i << " et je donne mon fromage" << endl;
        giveCheese();
}

void kitchenAssistant(){}

void threeStarsSwissChef(){}

int main()
{
    return 0;
}
