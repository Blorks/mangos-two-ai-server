#include "TradeCategory.h"
#include "Category.h"
#include "AhBotConfig.h"
#include "PricingStrategy.h"
#include "ServerFacade.h"
#include "SQLStorages.h"

using namespace ahbot;

bool TradeSkill::Contains(ItemPrototype const* proto)
{
    if (itemCache.find(proto->ItemId) != itemCache.end())
        return itemCache[proto->ItemId];

    if (!Trade::Contains(proto))
        return false;

    bool contains = ContainsInternal(proto);
    return itemCache[proto->ItemId] = contains;
}

bool TradeSkill::ContainsInternal(ItemPrototype const* proto)
{

    for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
    {
        SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
        if (!skillLine || skillLine->skillId != skill)
            continue;

        if (IsCraftedBy(proto, skillLine->spellId))
            return true;
    }

    for (uint32 id = 0; id < sCreatureStorage.GetMaxEntry(); ++id)
    {
        CreatureInfo const* co = sCreatureStorage.LookupEntry<CreatureInfo>(id);
        if (!co || co->TrainerType != TRAINER_TYPE_TRADESKILLS)
            continue;

        uint32 trainerId = co->TrainerTemplateId;
        if (!trainerId)
            trainerId = co->Entry;

        TrainerSpellData const* trainer_spells = sObjectMgr.GetNpcTrainerTemplateSpells(trainerId);
        if (!trainer_spells)
            trainer_spells = sObjectMgr.GetNpcTrainerSpells(trainerId);

        if (!trainer_spells)
            continue;

        for (TrainerSpellMap::const_iterator itr = trainer_spells->spellList.begin(); itr != trainer_spells->spellList.end(); ++itr)
        {
            TrainerSpell const* tSpell = &itr->second;

            if (!tSpell || tSpell->reqSkill != skill)
                continue;

            if (IsCraftedBy(proto, tSpell->spell))
                return true;
        }
    }

    for (uint32 itemId = 0; itemId < sItemStorage.GetMaxEntry(); ++itemId)
    {
        ItemPrototype const* recipe = sItemStorage.LookupEntry<ItemPrototype>(itemId);
        if (!recipe)
            continue;

        if (recipe->Class == ITEM_CLASS_RECIPE && (
            (recipe->SubClass == ITEM_SUBCLASS_LEATHERWORKING_PATTERN && skill == SKILL_LEATHERWORKING) ||
            (recipe->SubClass == ITEM_SUBCLASS_TAILORING_PATTERN && skill == SKILL_TAILORING) ||
            (recipe->SubClass == ITEM_SUBCLASS_ENGINEERING_SCHEMATIC && skill == SKILL_ENGINEERING) ||
            (recipe->SubClass == ITEM_SUBCLASS_BLACKSMITHING && skill == SKILL_BLACKSMITHING) ||
            (recipe->SubClass == ITEM_SUBCLASS_COOKING_RECIPE && skill == SKILL_COOKING) ||
            (recipe->SubClass == ITEM_SUBCLASS_ALCHEMY_RECIPE && skill == SKILL_ALCHEMY) ||
            (recipe->SubClass == ITEM_SUBCLASS_FIRST_AID_MANUAL && skill == SKILL_FIRST_AID) ||
            (recipe->SubClass == ITEM_SUBCLASS_ENCHANTING_FORMULA && skill == SKILL_ENCHANTING) ||
#ifdef MANGOSBOT_ONE
            (recipe->SubClass == ITEM_SUBCLASS_JEWELCRAFTING_RECIPE && skill == SKILL_JEWELCRAFTING) ||
#endif
#ifdef MANGOSBOT_TWO
            (recipe->SubClass == ITEM_SUBCLASS_JEWELCRAFTING_RECIPE && skill == SKILL_JEWELCRAFTING) ||
            (skill == SKILL_INSCRIPTION) ||
#endif
            (recipe->SubClass == ITEM_SUBCLASS_FISHING_MANUAL && skill == SKILL_FISHING)
            ))
        {
            for (uint32 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
            {
                if (IsCraftedBy(proto, recipe->Spells[i].SpellId))
                    return true;
            }
        }
    }

    return false;
}

bool TradeSkill::IsCraftedBySpell(ItemPrototype const* proto, uint32 spellId)
{
    SpellEntry const *entry = sServerFacade.LookupSpellInfo(spellId);
    if (!entry)
        return false;

    return IsCraftedBySpell(proto, entry);
}

bool TradeSkill::IsCraftedBySpell(ItemPrototype const* proto, SpellEntry const *entry)
{

    if (reagent)
    {
        for (uint32 x = 0; x < MAX_SPELL_REAGENTS; ++x)
        {
            if (entry->Reagent[x] <= 0)
                { continue; }

            if (proto->ItemId == entry->Reagent[x])
            {
                sLog.outDetail("%s is a reagent for %s", proto->Name1, entry->SpellName[0]);
                return true;
            }
        }
    }
    else
    {
        for (int i = 0; i < 3; ++i)
        {
            if (entry->Effect[i] == SPELL_EFFECT_CREATE_ITEM)
            {
                if (entry->EffectItemType[i] == proto->ItemId)
                {
                    sLog.outDetail("%s is crafted by %s", proto->Name1, entry->SpellName[0]);
                    return true;
                }
            }
        }
    }

    return false;
}

bool TradeSkill::IsCraftedBy(ItemPrototype const* proto, uint32 spellId)
{
    if (IsCraftedBySpell(proto, spellId))
        return true;

    SpellEntry const *entry = sServerFacade.LookupSpellInfo(spellId);
    if (!entry)
        return false;

    for (uint32 effect = EFFECT_INDEX_0; effect < MAX_EFFECT_INDEX; ++effect)
    {
        uint32 craftId = entry->EffectTriggerSpell[effect];
        SpellEntry const *craft = sServerFacade.LookupSpellInfo(craftId);
        if (!craft)
            continue;

        if (IsCraftedBySpell(proto, craft))
            return true;
    }

    return false;
}

string TradeSkill::GetName()
{
    string name;
    switch (skill)
    {
    case SKILL_TAILORING:
        name = "trade.tailoring"; break;
    case SKILL_LEATHERWORKING:
        name = "trade.leatherworking"; break;
    case SKILL_ENGINEERING:
        name = "trade.engineering"; break;
    case SKILL_BLACKSMITHING:
        name = "trade.blacksmithing"; break;
    case SKILL_ALCHEMY:
        name = "trade.alchemy"; break;
    case SKILL_COOKING:
        name = "trade.cooking"; break;
    case SKILL_FISHING:
        name = "trade.fishing"; break;
    case SKILL_ENCHANTING:
        name = "trade.enchanting"; break;
    case SKILL_MINING:
        name = "trade.mining"; break;
    case SKILL_SKINNING:
        name = "trade.skinning"; break;
    case SKILL_HERBALISM:
        name = "trade.herbalism"; break;
    case SKILL_FIRST_AID:
        name = "trade.firstaid"; break;
#ifdef MANGOSBOT_ONE
    case SKILL_JEWELCRAFTING:
        name = "trade.jewelcrafting"; break;
#endif
#ifdef MANGOSBOT_TWO
    case SKILL_JEWELCRAFTING:
        name = "trade.jewelcrafting"; break;
    case SKILL_INSCRIPTION:
        name = "trade.inscription"; break;
#endif
    }

    return reagent ? name : name + ".craft";
}

string TradeSkill::GetLabel()
{
    if (reagent)
    {
        switch (skill)
        {
        case SKILL_TAILORING:
            return "tailoring materials";
        case SKILL_LEATHERWORKING:
        case SKILL_SKINNING:
            return "leather and hides";
        case SKILL_ENGINEERING:
            return "engineering materials";
        case SKILL_BLACKSMITHING:
            return "blacksmithing materials";
        case SKILL_ALCHEMY:
        case SKILL_HERBALISM:
            return "herbs";
        case SKILL_COOKING:
            return "fish and meat";
        case SKILL_FISHING:
            return "fish";
        case SKILL_ENCHANTING:
            return "enchanting materials";
        case SKILL_MINING:
            return "ore and stone";
        case SKILL_FIRST_AID:
            return "first aid reagents";
    #ifdef MANGOSBOT_ONE
        case SKILL_JEWELCRAFTING:
            return "jewelcrafting";
    #endif
    #ifdef MANGOSBOT_TWO
        case SKILL_JEWELCRAFTING:
            return "jewelcrafting";
        case SKILL_INSCRIPTION:
            return "inscription";
    #endif
        }
    }
    else
    {
        switch (skill)
        {
        case SKILL_TAILORING:
            return "cloth items";
        case SKILL_LEATHERWORKING:
        case SKILL_SKINNING:
            return "leather items";
        case SKILL_ENGINEERING:
            return "parts and devices";
        case SKILL_BLACKSMITHING:
            return "metal items";
        case SKILL_ALCHEMY:
        case SKILL_HERBALISM:
            return "herbs";
        case SKILL_COOKING:
            return "food and drink";
        case SKILL_FISHING:
            return "fish";
        case SKILL_ENCHANTING:
            return "enchants";
        case SKILL_MINING:
            return "ore and stone";
        case SKILL_FIRST_AID:
            return "bandages";
    #ifdef MANGOSBOT_ONE
        case SKILL_JEWELCRAFTING:
            return "jewels";
    #endif
    #ifdef MANGOSBOT_TWO
        case SKILL_JEWELCRAFTING:
            return "jewels";
        case SKILL_INSCRIPTION:
            return "inscripts";
    #endif
        }
    }
}

void TradeSkill::LoadCache()
{
    if (!itemCache.empty()) return;

    QueryResult* results = CharacterDatabase.PQuery("select item, contains from ahbot_cache where category = '%s'",
            GetName().c_str());

    int count = 0;
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            uint32 item = fields[0].GetUInt32();
            uint32 contains = fields[1].GetUInt32();

            itemCache[item] = contains;
            count++;

        } while (results->NextRow());
        delete results;
    }

    if (count)
    {
        sLog.outDetail("%u cached ahbot items loaded for category %s", count, GetName().c_str());
    } else rebuildRequired = true;
}

void TradeSkill::SaveCache()
{
    if (!rebuildRequired) return;
    sLog.outBasic("Saving %u cached ahbot items for category %s", itemCache.size(), GetName().c_str());
    for (map<uint32, bool>::iterator i = itemCache.begin(); i != itemCache.end(); ++i)
    {
        uint32 itemId = i->first;
        bool contains = i->second;

        CharacterDatabase.PExecute("insert into ahbot_cache (category, item, contains) values ('%s', %u, %u)",
                GetName().c_str(), itemId, contains ? 1 : 0);
    }
    rebuildRequired = false;
}
