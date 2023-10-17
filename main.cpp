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

void helpKitchenAssistants(){
    kitchenAssistantsMutex.lock();
    //curently helping kitchen assistants -> ToDO : remember to change waiting values
    cout << "j'aide 3 assistant" << endl;

    chrono::microseconds val (experimental::fundamentals_v2::randint(0, 2000));
    this_thread::sleep_for(val);

    //unpile kitchen assistants from the kitchenAssistantWaitingForHelps counter
    if (nbKitchenAssistantsWaitingForHelps >= 3)
    {
        nbKitchenAssistantsWaitingForHelps = nbKitchenAssistantsWaitingForHelps - 3;
        for(int j = 0; j < 3; ++j){
            kitchenAssistantLockerMutex[orderedQueue[j]].unlock();
        }
        orderedQueue.erase(orderedQueue.begin(), orderedQueue.begin()+3);
    }
    else
        cout << "erreur au niveaux du nombre d'assistant demandant de l'aide"<< endl;

    kitchenAssistantsMutex.unlock();
}

void giveCheese(){
    // must get called by cheese hunter when 3 stars swiss chef calls prepareCheeseFondue
}

void prepareCheeseFondue(){
    cout << "la fondue est prête" << endl;
    kitchenAssistantsMutex.lock();
}

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

void threeStarsSwissChef(){
    while (true){
        threeStarsSwissChefMutex.lock();
        if(nbCheeseHuntersThatCameBack == 9)
        {
            prepareCheeseFondue();
            // signal to cheese hunter
            break;
        }else if(nbKitchenAssistantsWaitingForHelps >= 3){
            //cout << "je suis le chef de cuissine et il y a " << nbKitchenAssistantsWaitingForHelps << " qui attende mon aide" << endl;
            helpKitchenAssistants();
        }
        threeStarsSwissChefMutex.unlock();
    }
}

int main()
{
    thread threeStarsSwissChefThread (threeStarsSwissChef);

    thread cheeseHunter1Thread(cheeseHunter, 1);
    thread cheeseHunter2Thread(cheeseHunter, 2);
    thread cheeseHunter3Thread(cheeseHunter, 3);
    thread cheeseHunter4Thread(cheeseHunter, 4);
    thread cheeseHunter5Thread(cheeseHunter, 5);
    thread cheeseHunter6Thread(cheeseHunter, 6);
    thread cheeseHunter7Thread(cheeseHunter, 7);
    thread cheeseHunter8Thread(cheeseHunter, 8);
    thread cheeseHunter9Thread(cheeseHunter, 9);


    thread kitchenAssistant1Thread (kitchenAssistant, 0);
    thread kitchenAssistant2Thread (kitchenAssistant, 1);
    thread kitchenAssistant3Thread (kitchenAssistant, 2);
    thread kitchenAssistant4Thread (kitchenAssistant, 3);
    thread kitchenAssistant5Thread (kitchenAssistant, 4);
    thread kitchenAssistant6Thread (kitchenAssistant, 5);
    thread kitchenAssistant7Thread (kitchenAssistant, 6);
    thread kitchenAssistant8Thread (kitchenAssistant, 7);
    thread kitchenAssistant9Thread (kitchenAssistant, 8);
    thread kitchenAssistant10Thread (kitchenAssistant, 9);


    threeStarsSwissChefThread.join();

    cheeseHunter1Thread.join();
    cheeseHunter2Thread.join();
    cheeseHunter3Thread.join();
    cheeseHunter4Thread.join();
    cheeseHunter5Thread.join();
    cheeseHunter6Thread.join();
    cheeseHunter7Thread.join();
    cheeseHunter8Thread.join();
    cheeseHunter9Thread.join();

    kitchenAssistant1Thread.join();
    kitchenAssistant2Thread.join();
    kitchenAssistant3Thread.join();
    kitchenAssistant4Thread.join();
    kitchenAssistant5Thread.join();
    kitchenAssistant6Thread.join();
    kitchenAssistant7Thread.join();
    kitchenAssistant8Thread.join();
    kitchenAssistant9Thread.join();
    kitchenAssistant10Thread.join();
    return 0;
}
