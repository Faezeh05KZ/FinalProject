#ifndef INVISIBLEMAN_HPP
#define INVISIBLEMAN_HPP

#include <string>
#include <memory>
#include <vector>
#include <set>
#include "Item.hpp"
#include "Monster.hpp"

class InvisibleMan : public Monster 
{
    public:

        InvisibleMan(const std::string& startingLocation);
        
        void usePower(GameManager& gameManager) override;
        bool canBeDefeated(const GameManager& gameManager) const override;
        
        bool addEvidence(const std::shared_ptr<Item>& item);
        bool allEvidenceCollected() const;
        const std::set<std::string>& getEvidenceLocations() const; 

        int getTaskProgress() const override { return collectedEvidence.size(); }
        int getRequiredTaskProgress() const override { return 5; }

    private:
    
        std::set<std::string> evidenceLocations;
        std::vector<std::shared_ptr<Item>> collectedEvidence;
};

#endif
