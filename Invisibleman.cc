#include "Invisibleman.hpp"
#include "GameManager.hpp"
#include "GameUtils.hpp"
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;


InvisibleMan::InvisibleMan(const string& startingLocation)
    : Monster("Invisible Man", MonsterType::INVISIBLE_MAN, startingLocation, 6) 
    {
    evidenceLocations = {"Inn", "Barn", "Institute", "Laboratory", "Mansion"};
}

bool InvisibleMan::addEvidence(const shared_ptr<Item>& item)
{
    if (collectedEvidence.size() < evidenceLocations.size() &&  evidenceLocations.count(item->getOriginalLocation())) 
    {
        collectedEvidence.push_back(item);
        return true;
    }

    return false;
}

bool InvisibleMan::allEvidenceCollected() const 
{
    return collectedEvidence.size() >= evidenceLocations.size();
}

const set<string>& InvisibleMan::getEvidenceLocations() const 
{
    return evidenceLocations;
}

bool InvisibleMan::canBeDefeated(const GameManager& gameManager) const {
    return allEvidenceCollected() && 
           gameManager.getHeroAtLocation(currentLocation) != nullptr;
}

void InvisibleMan::usePower(GameManager& gameManager) {
    cout << "Invisible Man uses Stalk Unseen!" << endl;
    auto nearestVillager = gameManager.findNearestTarget(currentLocation);
    if (nearestVillager.type == TargetType::VILLAGER) {
        string nextStep = currentLocation;
        for (int i = 0; i < 2; ++i) {
            string tempStep = gameManager.getGameMap()->findShortestPath(
                nextStep, nearestVillager.location);
            if (tempStep != nextStep) {
                nextStep = tempStep;
            } 
            else {
                break; 
            }
        }
        
        if (!nextStep.empty() && nextStep != currentLocation) {
            currentLocation = nextStep;
            cout << "Invisible Man stalks 2 spaces towards " << nearestVillager.name 
                 << ", now at " << currentLocation << endl;
        }
    }
}