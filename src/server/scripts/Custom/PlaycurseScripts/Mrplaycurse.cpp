
#include "ScriptPCH.h"

enum Spells
{
    SPELL_SCHILD         		= 75381,
    SPELL_KETTE					= 75362,
	SPELL_STRAMPELN				= 64639,
	SPELL_NATURBOMBE         	= 64650
};

class boss_mrplaycurse : public CreatureScript
{
public:
    boss_mrplaycurse() : CreatureScript("boss_mrplaycurse") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_mrplaycurseAI (pCreature);
    }

    struct boss_mrplaycurseAI : public ScriptedAI
    {
        boss_mrplaycurseAI (Creature *c) : ScriptedAI(c)
        { }

		uint64 t_schild;
		uint64 t_kette;       
		uint64 t_explosion;
		uint64 t_stomp;
		
        void Reset()
        {
			t_schild = 8000;
			t_kette = 10000;
            t_explosion = 20000;
			t_stomp = 25000;
        }

        void EnterCombat(Unit* /*who*/)
        {
           me->MonsterYell("Ihr wagt es mich zu stören? Schickt euch meine Frau Mrs. Playcurse?", 0, 0);
           me->MonsterYell("Richtet ihr aus das ich mich nie wieder rasieren werde.!", 0, 0);
        }

        void JustDied(Unit* /*killer*/)
        {
          me->MonsterSay("Ahhh...Ich habe versagt...Jetzt muss ich mich doch rasieren....!",0,0);
        }
      
        void KilledUnit(Unit *)
        {
             switch (urand(1,3))
             {
                   case 1:
                        me->MonsterYell("Nun habe ich einen von euch getötet hahahaha......Das war zu einfach !", 0, 0);
                   break;
                   case 2:
                       me->MonsterYell("Ihr seid einfach zu schwach! Müsst ihr etwa nochmal in die Playcurse shopping Mall?", 0, 0);
                   break;
                   case 3:
                       me->MonsterYell("Schon müde geworden ??? Ihr solltet mal mehr für den Server Voten!", 0, 0);
                  break;
             }
        }
        
        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;
				
			if (t_schild <= diff) //Kettenblitzschlagschild
			{
				DoCast(me->GetVictim(), SPELL_SCHILD);
				t_schild = 8000;
			} else t_schild -= diff;
				
			if (t_kette <= diff) //Erster Spell
			{
				DoCast(me->GetVictim(), SPELL_KETTE);
				t_kette = 10000;
			} else t_kette -= diff;
				
			if (t_explosion <= diff) //Zweiter Spell
            {
                DoCast(me->GetVictim(), SPELL_NATURBOMBE);
                t_explosion = 20000;
            } else t_explosion -= diff;
			
            if (t_stomp <= diff) //Dritter Spell
            {
                DoCast(me->GetVictim(), SPELL_STRAMPELN);
                t_stomp = 25000;
            } else t_stomp -= diff;

            DoMeleeAttackIfReady();
        }
    };

};

void AddSC_boss_mrplaycurse()
{
     new boss_mrplaycurse();
}