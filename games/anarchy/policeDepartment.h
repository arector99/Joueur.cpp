// Generated by Creer at 06:46PM on October 16, 2015 UTC, git hash: '98604e3773d1933864742cb78acbf6ea0b4ecd7b'
// Used to keep cities under control and raid Warehouses.

#ifndef JOUEUR_ANARCHY_POLICEDEPARTMENT_H
#define JOUEUR_ANARCHY_POLICEDEPARTMENT_H

#include "anarchy.h"
#include "building.h"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add addtional #includes(s) here.
// <<-- /Creer-Merge: includes -->>

/// <summary>
/// Used to keep cities under control and raid Warehouses.
/// </summary>
class Anarchy::PoliceDepartment : public Anarchy::Building
{
    friend Anarchy::GameManager;

    protected:
        virtual void deltaUpdateField(const std::string& fieldName, boost::property_tree::ptree& delta);
        PoliceDepartment() {};
        ~PoliceDepartment() {};

    public:

        // <<-- Creer-Merge: fields -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        // you can add addtional fields(s) here. None of them will be tracked or updated by the server.
        // <<-- /Creer-Merge: fields -->>

        /// <summary>
        /// Bribe the police to raid a Warehouse, dealing damage equal based on the Warehouse's current exposure, and then resetting it to 0.
        /// </summary>
        /// <param name="warehouse">The warehouse you want to raid.</param>
        /// <returns>The amount of damage dealt to the warehouse, or -1 if there was an error.</returns>
        int raid(Anarchy::Warehouse* warehouse);


        // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        // you can add addtional method(s) here.
        // <<-- /Creer-Merge: methods -->>
};

#endif
