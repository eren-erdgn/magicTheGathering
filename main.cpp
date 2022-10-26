#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <memory>

class Card{
protected:
    std::string name;
    int greenManaCost;
    int blackManaCost;
    int redManaCost;
    int whiteManaCost;
    int isDestroyed;
    bool isTapped;
    int armorRating;
    int attackPower;
    bool hasFirstStrike;
    int greenMana=0;
    int blackMana=0;
    int redMana=0;
    int whiteMana=0;
    int blueMana=0;
    int totalManaCost;
public:

    Card(){
        name="";

        greenManaCost=0;
        blackManaCost=0;
        redManaCost=0;
        whiteManaCost=0;
        totalManaCost=0;
        isDestroyed=0;
        isTapped=false;
        armorRating=0;
        attackPower=0;
    }
    Card(std::string n,int greenMC,int blackMC,int redMC,int whiteMC,int totalMC){
        name=n;
        greenManaCost=greenMC;
        blackManaCost=blackMC;
        redManaCost=redMC;
        whiteManaCost=whiteMC;
        totalManaCost=totalMC;


    }
    Card(std::string n,int greenMC,int blackMC,int redMC,int whiteMC,int totalMC,int aP,int aR){
        name=n;
        greenManaCost=greenMC;
        blackManaCost=blackMC;
        redManaCost=redMC;
        whiteManaCost=whiteMC;
        totalManaCost=totalMC;
        isDestroyed=0;
        isTapped=false;
        armorRating=aR;
        attackPower=aP;
    }

    ~Card(){    //Destructor

    }
    bool cardHasFirstStrike(){
        return hasFirstStrike;
    }
    bool cardIsTapped(){
        return isTapped;
    }

    int cardIsDestroyed(){
        return isDestroyed;
    }


    std::string getName(){
        return name;
    }

    int getBlackMana(){
        return blackMana;
    }
    int getWhiteMana(){
        return whiteMana;
    }
    int getGreenMana(){
        return greenMana;
    }
    int getBlueMana(){
        return blueMana;
    }
    int getRedMana(){
        return redMana;
    }

    int getGreenManaCost(){
        return greenManaCost;
    }
    int getBlackManaCost(){
        return blackManaCost;
    }
    int getRedManaCost(){
        return redManaCost;
    }
    int getWhiteManaCost(){
        return whiteManaCost;
    }
    int getTotalManaCost(){
        return totalManaCost;
    }
    void setMana(){
        this->blueMana=0;
        this->whiteMana=0;
        this->whiteMana=0;
        this->redMana=0;
        this->blackMana=0;
        this->greenMana=0;
    }


    void checkManaColoursAndDecrease(){
        if(blueMana>0){
            blueMana--;
        }
        else if(whiteMana>0){
            whiteMana--;
        }
        else if(greenMana>0){
            greenMana--;
        }
        else if(redMana>0){
            redMana--;
        }
        else if(blackMana>0){
            blackMana--;
        }
    }

    void dealDamage(int attackCardAttackPower,int attackCardArmorRating){


        if (attackCardAttackPower >= armorRating && attackPower >= attackCardArmorRating) {
            isDestroyed = 1;
            std::cout << "Attack card and defence card are dead" << std::endl;
        } else if (attackCardAttackPower >= armorRating && attackPower < attackCardArmorRating) {
            std::cout << "Attack card is alive.Defence card is dead" << std::endl;
            isDestroyed = 2;
        } else if (attackPower >= attackCardArmorRating && attackCardAttackPower < armorRating) {
            std::cout << "Defence card is alive.Attack card is dead" << std::endl;
            isDestroyed = 3;
        } else {
            std::cout << "Defence card is alive.Attack card is alive" << std::endl;
        }

    }
    virtual void attack(std::shared_ptr<Card> defenceCard,std::shared_ptr<class player> enemy){

    }
};
class landCard:public Card{
protected:

public:

    landCard():Card(){

    }
    landCard(std::string n,int greenMC,int blackMC,int redMC,int whiteMC,int totalMC):Card(n,greenMC,blackMC,redMC,whiteMC,totalMC){

    }

    ~landCard(){
    }



};



class  enchantmentCard:public Card{
protected:

public:
    enchantmentCard():Card(){

    }
    enchantmentCard(std::string n,int greenMC,int blackMC,int redMC,int whiteMC,int totalMC):Card(n,greenMC,blackMC,redMC,whiteMC,totalMC){

    }

    ~enchantmentCard(){

    }


};
class  sorceryCard:public Card{
protected:

public:

    sorceryCard():Card(){

    }
    sorceryCard(std::string n,int greenMC,int blackMC,int redMC,int whiteMC,int totalMC):Card(n,greenMC,blackMC,redMC,whiteMC,totalMC){

    }

    ~sorceryCard(){

    }



};

class player: public Card{
protected:

    int playerHP;


public:

    std::vector<std::shared_ptr<Card>> hand;
    std::vector<std::shared_ptr<Card>> board;
    std::vector<std::shared_ptr<Card>> library;
    std::vector<std::shared_ptr<Card>> discard;

    std::vector<std::shared_ptr<Card>>::iterator handPtr;


    player(){
        playerHP=0;
    }

    player(int pH):playerHP(pH){

    }


    player(const player &p){

        playerHP=p.playerHP;
        hand=p.hand;
        board=p.board;
        library=p.library;

    }

    ~player(){

    }


    void lowerPlayerHp(int attackPower){
        playerHP=playerHP-attackPower;
    }


    int PlayerHp(){
        return playerHP;
    }




    void getManas(std::shared_ptr<player> &player1){
        std::cout<<"BlueMana= "<<player1->getBlueMana()<<std::endl;
        std::cout<<"GreenMana=  "<<player1->getGreenMana()<<std::endl;
        std::cout<<"BlackMana= "<<player1->getBlackMana()<<std::endl;
        std::cout<<"RedMana= "<<player1->getRedMana()<<std::endl;
        std::cout<<"WhiteMana= "<<player1->getWhiteMana()<<std::endl;

    }


    void beginningDraw(){

        auto deckBack = library.begin();
        for(int i=0; i<7;i++){
            hand.emplace_back(*(deckBack));
            library.erase(deckBack);
        }

    }

    void libraryToHand(){
        if(hand.size()<7){
            auto deckBack = library.begin();
            hand.emplace_back(*(deckBack));
            library.erase(deckBack);
        }
    }


    int payment(std::string cardName){
        for(handPtr=hand.begin(); handPtr<hand.end(); ++handPtr){
            if((*handPtr)->getName()==cardName){
                if(blackMana>=(*handPtr)->getBlackManaCost() && whiteMana>=(*handPtr)->getWhiteManaCost() && greenMana>=(*handPtr)->getGreenManaCost() && redMana>=(*handPtr)->getRedManaCost() ) {
                    blackMana -= (*handPtr)->getBlackManaCost();
                    whiteMana -=  (*handPtr)->getWhiteManaCost();
                    greenMana -= (*handPtr)->getGreenManaCost();
                    redMana -= (*handPtr)->getRedManaCost();

                    for(int j=0;j<((*handPtr)->getTotalManaCost()-((*handPtr)->getBlackManaCost()+(*handPtr)->getWhiteManaCost()+(*handPtr)->getRedManaCost() + (*handPtr)->getGreenManaCost()));j++){
                        checkManaColoursAndDecrease();
                    }

                    board.emplace_back(*handPtr);
                    hand.erase(handPtr);

                    return 1;
                }
                else return 0;
            }
        }
    }

    void playLand(std::string cardName) {
        if (cardName == "Plains" || cardName == "Island" || cardName == "Swamp" || cardName == "Mountain" ||
            cardName == "Forest") {

            for (handPtr = hand.begin(); handPtr < hand.end(); ++handPtr) {
                if ((*handPtr)->getName() == cardName) {
                    board.emplace_back((*handPtr));
                    hand.erase(handPtr);
                    break;
                }
            }
            std::cout << "You played a landCard" << std::endl;
        }
    }

    void tapLand(std::string cardName){
        if (cardName == "Plains"){
            ++whiteMana;
        }
        else if(cardName=="Mountain"){
            ++redMana;
        }
        else if(cardName=="Island"){
            ++blueMana;
        }
        else if(cardName=="Forest"){
            ++greenMana;
        }
        else if(cardName=="Swamp"){
            ++blackMana;
        }
    }


    void handToBoard(int cardSize) {
        int x=0;
        int y=0;
        std::cout<<"Which cards do you want to play?"<<std::endl;
        std::string cardName;
        for (int k = 0; k < cardSize; ++k) {
            std::cin >> cardName;
            for (int i = 0; i < hand.size(); i++) {
                if (cardName == hand[i]->getName() ) {
                    if(getBlackMana()>=hand[i]->getBlackManaCost() || getWhiteMana()>=hand[i]->getWhiteManaCost()||getRedMana()>=hand[i]->getRedManaCost()||getGreenMana()>=hand[i]->getGreenManaCost()){
                        if (cardName == "Forest" || cardName == "Island" || cardName == "Plains" || cardName == "Mountain" ||cardName == "Swamp") {
                            x = 2;
                            break;
                        }
                        if (cardName=="Soldier"||cardName=="Armored_Pegasus"||cardName=="White_Knight"||cardName=="Angry_Bear"||cardName=="Guard"||cardName=="Werewolf"||cardName=="Skeleton"||cardName=="Ghost"||cardName=="Black_Knight"||cardName=="Orc_Maniac"||cardName=="Hobgoblin"||cardName=="Vampire"){
                            if(payment(cardName)==1){
                                std::cout<<"You played creatureCard"<<std::endl;
                            }
                            else{
                                std::cout<<"You don't have enough mana"<<std::endl;
                                std::cout<<"Enter another card"<<std::endl;
                                ++cardSize;
                            }
                            x = 1;
                            break;
                        }
                        if (cardName=="Rage"||cardName=="Holy_War"||cardName=="Holy_Light"||cardName=="Unholy_War"||cardName=="Restrain"||cardName=="Slow"){
                            if(payment(cardName)==1){
//                                for(int j=0;j<hand[i]->getTotalManaCost()-(hand[i]->getBlackManaCost()+hand[i]->getWhiteManaCost()+hand[i]->getRedManaCost()+hand[i]->getGreenManaCost());j++){
//                                    checkManaColoursAndDecrease();
//                                }
                                std::cout<<"You played enchantmentCard"<<std::endl;
                            }
                            else{
                                std::cout<<"You don't have enough mana"<<std::endl;
                                std::cout<<"Enter another card"<<std::endl;
                                ++cardSize;
                            }
                            x = 1;
                            break;
                        }
                        if (cardName=="Disenchant"||cardName=="Lightning_Bolt"||cardName=="Flood"||cardName=="Reanimate"||cardName=="Plague"||cardName=="Terror"){
                            if(payment(cardName)==1){
//                                for(int j=0;j<hand[i]->getTotalManaCost()-(hand[i]->getBlackManaCost()+hand[i]->getWhiteManaCost()+hand[i]->getRedManaCost()+hand[i]->getGreenManaCost());j++){
//                                    checkManaColoursAndDecrease();
//                                }
                                std::cout<<"You played sorceryCard"<<std::endl;
                            }
                            else{
                                std::cout<<"You don't have enough mana"<<std::endl;
                                std::cout<<"Enter another card"<<std::endl;
                                ++cardSize;
                            }
                            x = 1;
                            break;
                        }

                    }
                }
                if(cardName=="Skip"){
                    std::cout << "You skipped" << std::endl;
                    x = 1;
                    break;
                }



            }
            if (x == 0) {
                std::cout << "No valid card name try again" << std::endl;
                cardSize++;
            }

            if(x==2){
                std::cout<<"You can't play another land Card in this round"<<std::endl;
                cardSize++;
            }

            x=0;
        }
    }


    void moveToDiscardPile(int i){

        auto deckBack = board.begin();
        discard.emplace_back(*(deckBack + i));
        board.erase(deckBack + i);
    }



    int numberOfCreatureCardsOnBoard(){
        int x=0;
        std::string cardName;
        for (int i = 0; i < board.size(); i++) {
            cardName=board[i]->getName();
            if (cardName == "Soldier"){
                x++;
            }
            else if (cardName == "Armored_Pegasus"){
                x++;
            }
            else if (cardName == "White_Knight"){
                x++;
            }
            else if (cardName == "Angry_Bear"){
                x++;
            }
            else if (cardName == "Werewolf"){
                x++;
            }
            else if (cardName == "Skeleton"){
                x++;
            }
            else if (cardName == "Ghost"){
                x++;
            }
            else if (cardName == "Black_Knight"){
                x++;
            }
            else if (cardName == "Orc_Maniac"){
                x++;
            }
            else if (cardName == "Hobgoblin"){
                x++;
            }
            else if (cardName == "Vampire"){
                x++;
            }

        }
        return x;
    }



};
class creatureCards: public Card{
protected:

    bool hasFirstStrike;
    bool hasTrample;
public:


    creatureCards():Card(){


        hasTrample=false;
        isDestroyed=0;
        isTapped=false;
    };

    creatureCards(std::string n,int greenMC,int blackMC,int redMC,int whiteMC,int totalMC,int aP,int aR,bool fS,bool t):Card(n,greenMC,blackMC,redMC,whiteMC,totalMC,aP,aR),hasTrample(t){

        isDestroyed=0;
        isTapped=false;
    }

    ~creatureCards() {

    }


    void attack(std::shared_ptr<Card> defenceCard,std::shared_ptr<player> enemy){

        if(this->hasTrample==1||defenceCard == nullptr){
            this->isTapped=true;
            enemy->lowerPlayerHp(this->attackPower);
            std::cout<<"There is no defence card attacking enemy"<<std::endl;
        }

        if(defenceCard != nullptr && this->hasTrample==0){
            this->isTapped=true;
            defenceCard->dealDamage(this->attackPower,this->armorRating);

        }

    }



};

int chooseObject(std::vector<std::shared_ptr<Card>> &library){
    int x;
    std::string cardName;
    std::string yesOrNo;
    int cardSize=1;
    for (int k = 0; k < cardSize; ++k) {
        std::cin >> yesOrNo;
        if (yesOrNo == "y"){
            std::cout<<"Choose a creature card"<<std::endl;
            std::cin>>cardName;
            for (int i = 0; i < library.size(); i++) {
                if (cardName == library[i]->getName()) {
                    if (cardName == "Soldier" || cardName == "Armored_Pegasus" || cardName == "White_Knight" ||
                        cardName == "Angry_Bear" || cardName == "Guard" || cardName == "Werewolf" ||
                        cardName == "Skeleton" || cardName == "Ghost" || cardName == "Black_Knight" ||
                        cardName == "Orc_Maniac" || cardName == "Hobgoblin" || cardName == "Vampire") {

                        return i;
                    }

                }


            }
        }
        if(yesOrNo=="n"){
            return 42;
        }

    }
}


void printVector(std::vector<std::shared_ptr<Card>>& library ){
    for(int i=0; i<library.size();i++){
        std::cout<<i+1<<"."<<library[i]->getName()<<std::endl;
    }
}


void shuffleTheDeck(std::vector<std::shared_ptr<Card>>& library ){
    srand(time(0));
    random_shuffle(library.begin(), library.end());

}



void combat(std::shared_ptr<player> &pAttack, std::shared_ptr<player> &pDeffense){
    if(pAttack->numberOfCreatureCardsOnBoard()>0) {

        for (int i = 0; i < pAttack->numberOfCreatureCardsOnBoard(); i++){
            int a;
            int b;
            std::cout << "Do you want to attack?y/n" << std::endl;
            a = chooseObject(pAttack->board);
            if(a==42){
                break;;
            }

            while (a != 42) {
                if(pAttack->board[a]->cardIsTapped()==0){
                    if(pDeffense->numberOfCreatureCardsOnBoard()>0){
                        std::cout << "Do you want to defence?y/n" << std::endl;
                        b = chooseObject(pDeffense->board);
                        if (b == 42) {
                            pAttack->board[a]->attack(nullptr, pDeffense);
                            std::cout << "Player1 hp" << pAttack->PlayerHp() << std::endl;
                            std::cout << "Player2 hp" << pDeffense->PlayerHp() << std::endl;
                            a = 42;
                        }
                        else {
                            if (pDeffense->board[b]->cardIsTapped() == 0) {
                                pAttack->board[a]->attack(pDeffense->board[b], pDeffense);
                                if (pDeffense->board[b]->cardIsDestroyed() == 1 ) {
                                    pAttack->moveToDiscardPile(a);
                                    pDeffense->moveToDiscardPile(b);
                                }
                                else if(pDeffense->board[b]->cardIsDestroyed() == 2){
                                    pDeffense->moveToDiscardPile(b);
                                }
                                else if(pDeffense->board[b]->cardIsDestroyed() == 3){
                                    pAttack->moveToDiscardPile(a);
                                }
                                else{
                                    break;
                                }

                                std::cout << "Player2 hp" << pDeffense->PlayerHp() << std::endl;
                                a = 42;
                            }
                            if (pDeffense->board[b]->cardIsTapped() == 1) {
                                std::cout << "This card is tapped" << std::endl;
                                continue;
                            }
                        }
                    }
                    else{
                        std::cout << "There is no creature cards for defence" << std::endl;
                        pAttack->board[a]->attack(nullptr, pDeffense);
                        std::cout << "Player1 hp" << pAttack->PlayerHp() << std::endl;
                        std::cout << "Player2 hp" << pDeffense->PlayerHp() << std::endl;
                        break;
                    }

                }

                else{
                    std::cout<<"This attack card is tapped.Try another one."<<std::endl;
                    --i;
                    break;
                }
            }

        }
    }
}

void checkGame(std::shared_ptr<player> &player1, std::shared_ptr<player> &player2){
    if(player1->library.size()==0){
        std::cout<<"player 1's library is empty! Player 2 won!"<<std::endl;
        std::cout<<"player 1's HP is "<<player1->PlayerHp()<<std::endl;
        std::cout<<"player 2's HP is "<<player2->PlayerHp()<<std::endl;
        std::cout<<"GAME OVER"<<std::endl;


    }
    else if(player2->library.size()==0){
        std::cout<<"Player 2's library is empty! Player 1 won "<<std::endl;
        std::cout<<"Player 1's HP is "<<player1->PlayerHp()<<std::endl;
        std::cout<<"Player 2's HP is "<<player2->PlayerHp()<<std::endl;
        std::cout<<"GAME OVER"<<std::endl;


    }
    else if(player1->PlayerHp()==0){
        std::cout<<"Player 1 is dead! Player 2 won!"<<std::endl;
        std::cout<<"Player 1's HP is "<<player1->PlayerHp()<<std::endl;
        std::cout<<"Player 2's HP is "<<player2->PlayerHp()<<std::endl;
        std::cout<<"GAME OVER"<<std::endl;


    }
    else if(player2->PlayerHp()==0){
        std::cout<<"Player 2 is dead! Player 1 won!"<<std::endl;
        std::cout<<"Player 1's HP is "<<player1->PlayerHp()<<std::endl;
        std::cout<<"Player 2's HP is "<<player2->PlayerHp()<<std::endl;
        std::cout<<"GAME OVER"<<std::endl;


    }
}

int main() {
    std::shared_ptr<player>player1=std::make_shared<player>(15);
    std::shared_ptr<player>player2=std::make_shared<player>(15);
    std::shared_ptr<landCard> Plains = std::make_shared<landCard>("Plains",0,0,0,0,0);
    std::shared_ptr<landCard> Forest = std::make_shared<landCard>("Forest",0,0,0,0,0);
    std::shared_ptr<landCard> Island = std::make_shared<landCard>("Island",0,0,0,0,0);
    std::shared_ptr<landCard> Swamp = std::make_shared<landCard>("Swamp",0,0,0,0,0);
    std::shared_ptr<landCard> Mountain = std::make_shared<landCard>("Mountain",0,0,0,0,0);
    std::shared_ptr<creatureCards> Soldier = std::make_shared<creatureCards>("Soldier",0,0,0,1,1,1,1,0,0);
    std::shared_ptr<creatureCards> Armored_Pegasus = std::make_shared<creatureCards>("Armored_Pegasus",0,0,0,1,2,1,2,0,0);
    std::shared_ptr<creatureCards> White_Knight = std::make_shared<creatureCards>("White_Knight",0,0,0,2,2,2,2,1,0);
    std::shared_ptr<creatureCards> Angry_Bear = std::make_shared<creatureCards>("Angry_Bear",1,0,0,0,3,3,2,0,1);
    std::shared_ptr<creatureCards> Guard = std::make_shared<creatureCards>("Guard",0,0,0,2,4,2,5,0,0);
    std::shared_ptr<creatureCards> Werewolf = std::make_shared<creatureCards>("Werewolf",1,0,0,1,4,4,6,0,1);
    std::shared_ptr<creatureCards> Skeleton = std::make_shared<creatureCards>("Skeleton",0,1,0,0,1,1,1,0,0);
    std::shared_ptr<creatureCards> Ghost = std::make_shared<creatureCards>("Ghost",0,1,0,0,2,2,1,0,0);
    std::shared_ptr<creatureCards> Black_Knight = std::make_shared<creatureCards>("Black_Knight",0,2,0,0,2,2,2,1,0);
    std::shared_ptr<creatureCards> Orc_Maniac = std::make_shared<creatureCards>("Orc_Maniac",0,0,1,0,3,4,1,0,0);
    std::shared_ptr<creatureCards> Hobgoblin = std::make_shared<creatureCards>("Hobgoblin",0,1,1,0,3,3,3,0,0);
    std::shared_ptr<creatureCards> Vampire = std::make_shared<creatureCards>("Vampire",0,1,0,0,4,6,3,0,0);
    std::shared_ptr<sorceryCard> Disenchant = std::make_shared<sorceryCard>("Disenchant",0,0,0,1,2);
    std::shared_ptr<sorceryCard> Lightning_Bolt = std::make_shared<sorceryCard>("Lightning_Bolt",1,0,0,0,2);
    std::shared_ptr<sorceryCard> Flood = std::make_shared<sorceryCard>("Flood",1,0,0,1,3);
    std::shared_ptr<sorceryCard> Reanimate = std::make_shared<sorceryCard>("Reanimate",0,1,0,0,1);
    std::shared_ptr<sorceryCard> Plague = std::make_shared<sorceryCard>("Plague",0,1,0,0,3);
    std::shared_ptr<sorceryCard> Terror = std::make_shared<sorceryCard>("Terror",0,1,0,0,2);
    std::shared_ptr<enchantmentCard> Rage = std::make_shared<enchantmentCard>("Rage",1,0,0,0,1);
    std::shared_ptr<enchantmentCard> Holy_War = std::make_shared<enchantmentCard>("Holy_War",0,0,0,1,2);
    std::shared_ptr<enchantmentCard> Holy_Light = std::make_shared<enchantmentCard>("Holy_Light",0,0,0,1,2);
    std::shared_ptr<enchantmentCard> Unholy_War = std::make_shared<enchantmentCard>("Unholy_War",0,1,0,0,2);
    std::shared_ptr<enchantmentCard> Restrain = std::make_shared<enchantmentCard>("Restrain",0,0,1,0,3);
    std::shared_ptr<enchantmentCard> Slow = std::make_shared<enchantmentCard>("Slow",0,1,0,0,1);

    player1->library.emplace_back(Plains);
    player1->library.emplace_back(Plains);
    player1->library.emplace_back(Plains);
    player1->library.emplace_back(Plains);
    player1->library.emplace_back(Plains);
    player1->library.emplace_back(Forest);
    player1->library.emplace_back(Forest);
    player1->library.emplace_back(Forest);
    player1->library.emplace_back(Island);
    player1->library.emplace_back(Soldier);
    player1->library.emplace_back(Soldier);
    player1->library.emplace_back(Soldier);
    player1->library.emplace_back(Armored_Pegasus);
    player1->library.emplace_back(Armored_Pegasus);
    player1->library.emplace_back(White_Knight);
    player1->library.emplace_back(White_Knight);
    player1->library.emplace_back(Angry_Bear);
    player1->library.emplace_back(Guard);
    player1->library.emplace_back(Werewolf);
    player1->library.emplace_back(Disenchant);
    player1->library.emplace_back(Lightning_Bolt);
    player1->library.emplace_back(Flood);
    player1->library.emplace_back(Flood);
    player1->library.emplace_back(Rage);
    player1->library.emplace_back(Holy_War);
    player1->library.emplace_back(Holy_Light);


    player2->library.emplace_back(Swamp);
    player2->library.emplace_back(Swamp);
    player2->library.emplace_back(Swamp);
    player2->library.emplace_back(Swamp);
    player2->library.emplace_back(Swamp);
    player2->library.emplace_back(Mountain);
    player2->library.emplace_back(Mountain);
    player2->library.emplace_back(Mountain);
    player2->library.emplace_back(Island);
    player2->library.emplace_back(Skeleton);
    player2->library.emplace_back(Skeleton);
    player2->library.emplace_back(Skeleton);
    player2->library.emplace_back(Ghost);
    player2->library.emplace_back(Ghost);
    player2->library.emplace_back(Black_Knight);
    player2->library.emplace_back(Black_Knight);
    player2->library.emplace_back(Orc_Maniac);
    player2->library.emplace_back(Hobgoblin);
    player2->library.emplace_back(Vampire);
    player2->library.emplace_back(Reanimate);
    player2->library.emplace_back(Plague);
    player2->library.emplace_back(Terror);
    player2->library.emplace_back(Terror);
    player2->library.emplace_back(Unholy_War);
    player2->library.emplace_back(Restrain);
    player2->library.emplace_back(Slow);

    std::string cardName;
    int cardSize;
    int round=0;
    shuffleTheDeck(player1->library);
    shuffleTheDeck(player2->library);
    player1->beginningDraw();
    player2->beginningDraw();


    while(true){
        if(round%2==0){

            player1->setMana();

            player1->libraryToHand();

            std::cout<<"Player1's turn"<<std::endl;
            std::cout<<"----------"<<std::endl;
            player1->getManas(player1);
            std::cout<<"----------"<<std::endl;
            printVector(player1->hand);
            std::cout<<"----------"<<std::endl;
            printVector(player1->board);
            std::cout<<"----------"<<std::endl;

            std::cout<<"Play a land Card"<<std::endl;
            std::cin>>cardName;
            player1->playLand(cardName);

            std::cout<<"How many cards will you tap?"<<std::endl;
            std::cin>>cardSize;
            std::cout<<"Which cards do you want to tap?"<<std::endl;

            for(int i=0 ; i<cardSize; ++i){
                std::cin>>cardName;
                player1->tapLand(cardName);
            }

            player1->getManas(player1);

            std::cout<<"How many cards will you play?"<<std::endl;
            std::cin>>cardSize;


            player1->handToBoard(cardSize);

            player1->getManas(player1);

            combat(player1,player2);

            if(player1->library.size()==0 || player2->library.size()==0 || player2->PlayerHp()==0 || player2->PlayerHp()==0){
                checkGame(player1,player2);
                break;
            }
            printVector(player1->hand);
            std::cout<<"----------"<<std::endl;
            player1->getManas(player1);


            std::cout<<"How many cards will you play?"<<std::endl;
            std::cin>>cardSize;

            player1->handToBoard(cardSize);

            std::cout<<"Left Manas:"<<std::endl;
            player1->getManas(player1);



        }

        else{

            player2->setMana();

            player2->libraryToHand();

            std::cout<<"Player2's turn"<<std::endl;
            std::cout<<"----------"<<std::endl;
            player2->getManas(player2);
            std::cout<<"----------"<<std::endl;
            printVector(player2->hand);
            std::cout<<"----------"<<std::endl;
            printVector(player2->board);
            std::cout<<"----------"<<std::endl;


            std::cout<<"Play a land Card"<<std::endl;
            std::cin>>cardName;
            player2->playLand(cardName);

            std::cout<<"How many cards will you tap?"<<std::endl;
            std::cin>>cardSize;
            std::cout<<"Which cards do you want to tap?"<<std::endl;
            for(int i=0 ; i<cardSize; ++i){
                std::cin>>cardName;
                player2->tapLand(cardName);
            }

            player2->getManas(player2);


            std::cout<<"How many cards will you play?"<<std::endl;
            std::cin>>cardSize;
            player2->handToBoard(cardSize);

            player2->getManas(player2);

            combat(player2,player1);

            if(player1->library.size()==0 || player2->library.size()==0 || player2->PlayerHp()==0 || player2->PlayerHp()==0){
                checkGame(player1,player2);
                break;
            }

            printVector(player2->hand);
            std::cout<<"----------"<<std::endl;
            player2->getManas(player2);
            std::cout<<"How many cards will you play?"<<std::endl;
            std::cin>>cardSize;
            player2->handToBoard(cardSize);
            std::cout<<"Left Manas:"<<std::endl;
            player2->getManas(player2);
        }


        round++;


    }

    return 0;
}

