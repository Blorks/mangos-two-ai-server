#pragma once

#include "CustomStrategy.h"
#include "generic/NonCombatStrategy.h"
#include "generic/RacialsStrategy.h"
#include "generic/ChatCommandHandlerStrategy.h"
#include "generic/WorldPacketHandlerStrategy.h"
#include "generic/DeadStrategy.h"
#include "generic/QuestStrategies.h"
#include "generic/LootNonCombatStrategy.h"
#include "generic/DuelStrategy.h"
#include "generic/KiteStrategy.h"
#include "generic/FleeStrategy.h"
#include "generic/FollowMasterStrategy.h"
#include "generic/RunawayStrategy.h"
#include "generic/StayStrategy.h"
#include "generic/UseFoodStrategy.h"
#include "generic/ConserveManaStrategy.h"
#include "generic/EmoteStrategy.h"
#include "generic/TankAoeStrategy.h"
#include "generic/DpsAssistStrategy.h"
#include "generic/PassiveStrategy.h"
#include "generic/GrindingStrategy.h"
#include "generic/UsePotionsStrategy.h"
#include "generic/GuardStrategy.h"
#include "generic/CastTimeStrategy.h"
#include "generic/ThreatStrategy.h"
#include "generic/TellTargetStrategy.h"
#include "generic/AttackEnemyPlayersStrategy.h"
#include "generic/MarkRtiStrategy.h"
#include "generic/MeleeCombatStrategy.h"
#include "generic/PatrolStrategy.h"
#include "generic/PullStrategy.h"
#include "generic/RangedCombatStrategy.h"
#include "generic/ReturnStrategy.h"
#include "generic/RpgStrategy.h"

namespace ai
{
    class StrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        StrategyContext()
        {
            creators["racials"] = &StrategyContext::racials;
            creators["loot"] = &StrategyContext::loot;
            creators["gather"] = &StrategyContext::gather;
            creators["emote"] = &StrategyContext::emote;
            creators["passive"] = &StrategyContext::passive;
            creators["conserve mana"] = &StrategyContext::conserve_mana;
            creators["food"] = &StrategyContext::food;
            creators["chat"] = &StrategyContext::chat;
            creators["default"] = &StrategyContext::world_packet;
            creators["ready check"] = &StrategyContext::ready_check;
            creators["dead"] = &StrategyContext::dead;
            creators["flee"] = &StrategyContext::flee;
            creators["duel"] = &StrategyContext::duel;
            creators["kite"] = &StrategyContext::kite;
            creators["potions"] = &StrategyContext::potions;
            creators["cast time"] = &StrategyContext::cast_time;
            creators["threat"] = &StrategyContext::threat;
            creators["tell target"] = &StrategyContext::tell_target;
            creators["pvp"] = &StrategyContext::pvp;
            creators["return"] = &StrategyContext::_return;
            creators["lfg"] = &StrategyContext::lfg;
            creators["custom"] = &StrategyContext::custom;
            creators["reveal"] = &StrategyContext::reveal;
            creators["collision"] = &StrategyContext::collision;
            creators["rpg"] = &StrategyContext::rpg;
            creators["sit"] = &StrategyContext::sit;
            creators["mark rti"] = &StrategyContext::mark_rti;
            creators["ads"] = &StrategyContext::possible_ads;
            creators["close"] = &StrategyContext::close;
            creators["ranged"] = &StrategyContext::ranged;
            creators["behind"] = &StrategyContext::behind;
        }

    private:
        static Strategy* behind(PlayerbotAI* ai) { return new SetBehindCombatStrategy(ai); }
        static Strategy* ranged(PlayerbotAI* ai) { return new RangedCombatStrategy(ai); }
        static Strategy* close(PlayerbotAI* ai) { return new MeleeCombatStrategy(ai); }
        static Strategy* mark_rti(PlayerbotAI* ai) { return new MarkRtiStrategy(ai); }
        static Strategy* tell_target(PlayerbotAI* ai) { return new TellTargetStrategy(ai); }
        static Strategy* threat(PlayerbotAI* ai) { return new ThreatStrategy(ai); }
        static Strategy* cast_time(PlayerbotAI* ai) { return new CastTimeStrategy(ai); }
        static Strategy* potions(PlayerbotAI* ai) { return new UsePotionsStrategy(ai); }
        static Strategy* kite(PlayerbotAI* ai) { return new KiteStrategy(ai); }
        static Strategy* duel(PlayerbotAI* ai) { return new DuelStrategy(ai); }
        static Strategy* flee(PlayerbotAI* ai) { return new FleeStrategy(ai); }
        static Strategy* dead(PlayerbotAI* ai) { return new DeadStrategy(ai); }
        static Strategy* racials(PlayerbotAI* ai) { return new RacialsStrategy(ai); }
        static Strategy* loot(PlayerbotAI* ai) { return new LootNonCombatStrategy(ai); }
        static Strategy* gather(PlayerbotAI* ai) { return new GatherStrategy(ai); }
        static Strategy* emote(PlayerbotAI* ai) { return new EmoteStrategy(ai); }
        static Strategy* passive(PlayerbotAI* ai) { return new PassiveStrategy(ai); }
        static Strategy* conserve_mana(PlayerbotAI* ai) { return new ConserveManaStrategy(ai); }
        static Strategy* food(PlayerbotAI* ai) { return new UseFoodStrategy(ai); }
        static Strategy* chat(PlayerbotAI* ai) { return new ChatCommandHandlerStrategy(ai); }
        static Strategy* world_packet(PlayerbotAI* ai) { return new WorldPacketHandlerStrategy(ai); }
        static Strategy* ready_check(PlayerbotAI* ai) { return new ReadyCheckStrategy(ai); }
        static Strategy* pvp(PlayerbotAI* ai) { return new AttackEnemyPlayersStrategy(ai); }
        static Strategy* _return(PlayerbotAI* ai) { return new ReturnStrategy(ai); }
        static Strategy* lfg(PlayerbotAI* ai) { return new LfgStrategy(ai); }
        static Strategy* custom(PlayerbotAI* ai) { return new CustomStrategy(ai); }
        static Strategy* reveal(PlayerbotAI* ai) { return new RevealStrategy(ai); }
        static Strategy* collision(PlayerbotAI* ai) { return new CollisionStrategy(ai); }
        static Strategy* rpg(PlayerbotAI* ai) { return new RpgStrategy(ai); }
        static Strategy* sit(PlayerbotAI* ai) { return new SitStrategy(ai); }
        static Strategy* possible_ads(PlayerbotAI* ai) { return new PossibleAdsStrategy(ai); }
    };

    class MovementStrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        MovementStrategyContext() : NamedObjectContext<Strategy>(false, true)
        {
            creators["follow"] = &MovementStrategyContext::follow_master;
            creators["stay"] = &MovementStrategyContext::stay;
            creators["runaway"] = &MovementStrategyContext::runaway;
            creators["flee from adds"] = &MovementStrategyContext::flee_from_adds;
            creators["guard"] = &MovementStrategyContext::guard;
            creators["patrol"] = &MovementStrategyContext::patrol;
        }

    private:
        static Strategy* guard(PlayerbotAI* ai) { return new GuardStrategy(ai); }
        static Strategy* patrol(PlayerbotAI* ai) { return new PatrolStrategy(ai); }
        static Strategy* follow_master(PlayerbotAI* ai) { return new FollowMasterStrategy(ai); }
        static Strategy* stay(PlayerbotAI* ai) { return new StayStrategy(ai); }
        static Strategy* runaway(PlayerbotAI* ai) { return new RunawayStrategy(ai); }
        static Strategy* flee_from_adds(PlayerbotAI* ai) { return new FleeFromAddsStrategy(ai); }
    };

    class AssistStrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        AssistStrategyContext() : NamedObjectContext<Strategy>(false, true)
        {
            creators["dps assist"] = &AssistStrategyContext::dps_assist;
            creators["dps aoe"] = &AssistStrategyContext::dps_aoe;
            creators["tank aoe"] = &AssistStrategyContext::tank_aoe;
            creators["grind"] = &AssistStrategyContext::grind;
        }

    private:
        static Strategy* dps_assist(PlayerbotAI* ai) { return new DpsAssistStrategy(ai); }
        static Strategy* dps_aoe(PlayerbotAI* ai) { return new DpsAoeStrategy(ai); }
        static Strategy* tank_aoe(PlayerbotAI* ai) { return new TankAoeStrategy(ai); }
        static Strategy* grind(PlayerbotAI* ai) { return new GrindingStrategy(ai); }
    };

    class QuestStrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        QuestStrategyContext() : NamedObjectContext<Strategy>(false, true)
        {
            creators["quest"] = &QuestStrategyContext::quest;
            creators["accept all quests"] = &QuestStrategyContext::accept_all_quests;
        }

    private:
        static Strategy* quest(PlayerbotAI* ai) { return new DefaultQuestStrategy(ai); }
        static Strategy* accept_all_quests(PlayerbotAI* ai) { return new AcceptAllQuestsStrategy(ai); }
    };
};
