#pragma once

#include <optional>
#include <vector>
#include <optional>

#include "Eyes.h"
#include "Hands.h"

class Brain
{
public:
    int m_search_attempts = 7;

    Brain(::Eyes &eyes, ::Hands &hands) :
        m_state             {State::NextTarget},
        m_previous_state    {State::Undefined},
        m_eyes              {eyes},
        m_hands             {hands},
        m_search_attempt    {0},
        m_first_attack      {true}
    {}

    const std::vector<::Eyes::NPC> &NPCs() const        { return m_npcs; }
    const std::vector<::Eyes::FarNPC> &FarNPCs() const  { return m_far_npcs; }
    const std::optional<::Eyes::Me> &Me() const         { return m_me; }
    const std::optional<::Eyes::Target> &Target() const { return m_target; }

    void Init();
    void Process();

private:
    enum class State
    {
        Undefined   = 0,
        NextTarget  = 1,
        NearSearch  = 2,
        FarSearch   = 3,
        Check       = 4,
        Attack      = 5,
        PickUp      = 6
    };

    State m_state;
    State m_previous_state;
    ::Eyes &m_eyes;
    ::Hands &m_hands;
    std::set<std::uint32_t> m_ignored_npc_ids;
    int m_search_attempt;
    bool m_first_attack;

    std::vector<::Eyes::NPC> m_npcs;
    std::vector<::Eyes::FarNPC> m_far_npcs;
    std::optional<::Eyes::Me> m_me;
    std::optional<::Eyes::Target> m_target;

    const ::Eyes::NPC *UnselectedNPC() const;
    const ::Eyes::NPC *SelectedNPC() const;
    const ::Eyes::NPC *HoveredNPC() const;
    const ::Eyes::FarNPC *FarNPC() const;
    std::vector<const ::Eyes::NPC *> FilteredNPCs() const;

    void IgnoreNPC(std::uint32_t npc_id)    { m_ignored_npc_ids.insert(npc_id); }
    void ClearIgnoredNPCs()                 { m_ignored_npc_ids.clear(); }
};
