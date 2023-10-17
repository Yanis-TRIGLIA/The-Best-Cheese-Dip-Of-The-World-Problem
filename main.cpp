#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <experimental/random>

using namespace std;

unsigned nbKitchenAssistantsWaitingForHelps = 0;
unsigned nbCheeseHuntersThatCameBack = 0;
mutex kitchenAssistantsMutex;
mutex cheeseHuntersMutex;
mutex threeStarsSwissChefMutex;
vector<mutex> kitchenAssistantLockerMutex(10);
vector<unsigned> orderedQueue;

void getHelp(unsigned i){
    kitchenAssistantLockerMutex[i].lock();
    kitchenAssistantsMutex.lock();
    cout << "je suis le commis N°: " << i << " et je demmande de l'aide" << endl;
        ++nbKitchenAssistantsWaitingForHelps;
    orderedQueue.push_back(i);
    cout << "il y a " << nbKitchenAssistantsWaitingForHelps << " assistant qui ont bessoin d'aide"<<endl;
    kitchenAssistantsMutex.unlock();
}

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

void kitchenAssistant(unsigned i){
    while(true){
        //simulate the fact that a kitchen assistant need help by random
        unsigned rand = experimental::fundamentals_v2::randint(0, 100);
        if ( rand <= 10){
            getHelp(i);
        }else{
            // if the kitchen Assistant doesn't need help, it wait for random time to avoid having all the kitchenAssistants needing help everytime
            chrono::microseconds val (experimental::fundamentals_v2::randint(200, 2000));
            this_thread::sleep_for(val);
        }
    }
}

void threeStarsSwissChef(){}

int main()
{

    return 0;
}
