// This is where you build your AI for the Spiders game.

#include "ai.h"

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
T randomElement(std::vector<T> v);

/// <summary>
/// This returns your AI's name to the game server. Just replace the string.
/// </summary>
/// <returns>string of you AI's name.</returns>
std::string Spiders::AI::getName() {
  return "Spiders C++ Player";  // REPLACE THIS WITH YOUR TEAM NAME!
}

/// <summary>
/// This is automatically called when the game first starts, once the Game
/// object and all GameObjects have been initialized, but before any players do
/// anything.
/// </summary>
void Spiders::AI::start() { srand(time(NULL)); }

/// <summary>
/// This is automatically called every time the game (or anything in it)
/// updates.
/// </summary>
void Spiders::AI::gameUpdated() {}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if your player won, false otherwise</param>
/// <param name="reason">a string explaining why you won or lost</param>
void Spiders::AI::ended(bool won, std::string reason) {}

/// <summary>
/// This is called every time it is this AI.player's turn.
/// </summary>
/// <returns>Represents if you want to end your turn. True means end your turn,
/// False means to keep your turn going and re-call this function.</returns>
bool Spiders::AI::runTurn() {
  // This is ShellAI, it is very simple, and demonstrates how to use all the
  // game objects in Spiders

  // get a random spider to try to do things with
  Spider* spider = randomElement(player->spiders);

  if (spider->gameObjectName == "BroodMother") {
    BroodMother* broodMother = dynamic_cast<BroodMother*>(spider);
    if (rand() % 2 == 1) {  // flip a coin

      // Task: Eat a Spiderling
      if (broodMother->nest->spiders.size() > 1) {  // there is another spider
        // get a random other spider to see if it's not us
        Spider* otherSpider = randomElement(spider->nest->spiders);
        if (otherSpider != broodMother) {
          // We need a Spiderling* to feed to BroodMother::consume()
          // This is how you cast pointers in C++
          // If otherSpider can not be cast to a Spiderling* then
          // dynamic_cast will return nullptr. Always check.
          Spiderling* food = dynamic_cast<Spiderling*>(otherSpider);
          if (food != nullptr) {
            cout << broodMother->gameObjectName << " #" << broodMother->id
                 << " consuming " << food->gameObjectName << " #" << food->id
                 << endl;
            broodMother->consume(food);
          }
        }
      }
    } else {  // try to spawn a Spiderling

      // Task: Spawn a Spiderling
      if (broodMother->eggs > 0) {
        // c++11 constructs are available. Two are demostrated here.

        // This is the syntax for initializer lists.
        // (Which is different from initialization lists. That's constructors.)
        std::vector<std::string> spiderlingTypes{"Cutter", "Weaver", "Spitter"};

        // If the compiler can determine that only a sinle type can be
        // returned, then you can declare a variable to be of type "auto",
        // which means "look, compiler, we both know what it has to be, so
        // just make it that type. It's important to understand that "auto"
        // is not a real type. It's just instructing the compiler to put its
        // autism to good use for once and make the variable be of the type that
        // it has to be.
        auto randomSpiderlingType = randomElement(spiderlingTypes);
        cout << broodMother->gameObjectName << " #" << broodMother->id
             << " spawning " << randomSpiderlingType << endl;

        broodMother->spawn(randomSpiderlingType);
      }
    }
  } else {  // it is a spiderling
    auto spiderling = dynamic_cast<Spiderling*>(spider);
    // note that we could have also done the dynamic_cast at the top and checked
    // for nullptr to see if we had a Spiderling or a not-a-Spiderling, which,
    // in this case, HAS to be the BroodMother.

    if (spiderling->busy == "false") {  // not busy
      int choice = rand() % 3;

      if (choice == 0) {
        // Task: try to move somewhere
        if (spiderling->nest->webs.size() > 0) {
          auto web = randomElement(spiderling->nest->webs);
          cout << "Spiderling " << spiderling->gameObjectName << " #"
               << spiderling->id << " moving onto " << web->gameObjectName
               << " #" << web->id << endl;
          spiderling->move(web);
        }
      } else if (choice == 1) {
        // Task: try to attack something
        if (spiderling->nest->spiders.size() > 1) {  // there is a target
          Spider* otherSpider = randomElement(spiderling->nest->spiders);
          if (otherSpider->owner != spiderling->owner) {  // enemy!
            auto target = dynamic_cast<Spiderling*>(otherSpider);
            // So let's think about this. Do we need a nullptr check? The other
            // spider can't possibly be the hostile BroodMother because this
            // spiderling would already be dead. It can't possibly be the
            // friendly BroodMother because the owners match. Therefore it MUST
            // be a Spiderling. No need for nullptr check.
            cout << spiderling->gameObjectName << " #" << spiderling->id
                 << " attacking " << target->gameObjectName << " #"
                 << target->id << endl;
            spiderling->attack(target);
          }
        }
      } else {
        // Task: do a type-specific action

        if (spider->gameObjectName == "Spitter") {
          // Task: spit a web to the enemy's home nest

          auto spitter = dynamic_cast<Spitter*>(spider);
          Nest* enemysNest = player->otherPlayer->broodMother->nest;

          // let's demonstrate a c++11 style foreach loop
          Web* existingWeb = nullptr;
          for (auto& web : enemysNest->webs) {
            if (web->nestA == spitter->nest || web->nestB == spitter->nest) {
              existingWeb = web;
              break;
            }
          }

          if (existingWeb == nullptr) {
            cout << spitter->gameObjectName << " #" << spitter->id
                 << " spitting at " << enemysNest->gameObjectName << " #"
                 << enemysNest->id << endl;
            spitter->spit(enemysNest);
          }
        } else if (spider->gameObjectName == "Cutter") {
          auto cutter = dynamic_cast<Cutter*>(spider);
          if (cutter->nest->webs.size() > 0) {  // cut one of them
            Web* targetWeb = randomElement(cutter->nest->webs);
            cout << cutter->gameObjectName << " #" << cutter->id
                 << " spitting at " << targetWeb->gameObjectName << " #"
                 << targetWeb->id << endl;
            cutter->cut(targetWeb);
          } else if (spider->gameObjectName == "Weaver") {
            auto weaver = dynamic_cast<Weaver*>(spider);
            if (weaver->nest->webs.size() > 0) {  // weave a web
              // 50% of the time do a strengthening weave,
              // the other 50% of the time weaken
              Web* targetWeb = randomElement(weaver->nest->webs);

              if (rand() % 2 == 1) {
                cout << weaver->gameObjectName << " #" << weaver->id
                     << " strengthening " << targetWeb->gameObjectName << " #"
                     << targetWeb->id << endl;
                weaver->strengthen(targetWeb);
              } else {
                cout << weaver->gameObjectName << " #" << weaver->id
                     << " weakening " << targetWeb->gameObjectName << " #"
                     << targetWeb->id << endl;
                weaver->weaken(targetWeb);
              }
            }
          }
        }
      }
    }
  }

  return true;
}

// utility function, can't let the dynamic language guys have all the fun
template <typename T>
T randomElement(std::vector<T> v) {
  T nullResult;
  if (v.size() == 0) return nullResult;
  return v[rand() % v.size()];
}
