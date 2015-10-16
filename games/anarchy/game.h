// Generated by Creer at 10:46PM on October 16, 2015 UTC, git hash: '98604e3773d1933864742cb78acbf6ea0b4ecd7b'
// Two player grid based game where each player tries to burn down the other player's buildings. Let it burn!

#ifndef JOUEUR_ANARCHY_GAME_H
#define JOUEUR_ANARCHY_GAME_H

#include "anarchy.h"
#include "../../joueur/baseGame.h"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add addtional #includes(s) here.
// <<-- /Creer-Merge: includes -->>

/// <summary>
/// Two player grid based game where each player tries to burn down the other player's buildings. Let it burn!
/// </summary>
class Anarchy::Game : public Joueur::BaseGame
{
    friend Anarchy::GameManager;

    protected:
        virtual void deltaUpdateField(const std::string& fieldName, boost::property_tree::ptree& delta);
        Game() { this->name = "Anarchy"; };
        ~Game() {};

    public:
        /// <summary>
        /// How many bribes players get at the beginning of their turn, not counting their burned down Buildings.
        /// </summary>
        int baseBribesPerTurn;

        /// <summary>
        /// All the buildings in the game.
        /// </summary>
        std::vector<Anarchy::Building*> buildings;

        /// <summary>
        /// The current Forecast, which will be applied at the end of the turn.
        /// </summary>
        Anarchy::Forecast* currentForecast;

        /// <summary>
        /// The player whose turn it is currently. That player can send commands. Other players cannot.
        /// </summary>
        Anarchy::Player* currentPlayer;

        /// <summary>
        /// The current turn number, starting at 0 for the first player's turn
        /// </summary>
        int currentTurn;

        /// <summary>
        /// All the forecasts in the game, indexed by turn number.
        /// </summary>
        std::vector<Anarchy::Forecast*> forecasts;

        /// <summary>
        /// The width of the entire map along the vertical (y) axis.
        /// </summary>
        int mapHeight;

        /// <summary>
        /// The width of the entire map along the horizontal (x) axis.
        /// </summary>
        int mapWidth;

        /// <summary>
        /// The maximum amount of fire value for any Building.
        /// </summary>
        int maxFire;

        /// <summary>
        /// The maximum number of turns before the game will automatically end.
        /// </summary>
        int maxTurns;

        /// <summary>
        /// The next Forecast, which will be applied at the end of your opponent's turn. This is also the Forecast WeatherStations can control this turn.
        /// </summary>
        Anarchy::Forecast* nextForecast;

        /// <summary>
        /// List of all the players in the game.
        /// </summary>
        std::vector<Anarchy::Player*> players;

        /// <summary>
        /// A unique identifier for the game instance that is being played.
        /// </summary>
        std::string session;


        // <<-- Creer-Merge: fields -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        // you can add addtional fields(s) here. None of them will be tracked or updated by the server.
        // <<-- /Creer-Merge: fields -->>


        // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        // you can add addtional method(s) here.
        // <<-- /Creer-Merge: methods -->>
};

#endif
