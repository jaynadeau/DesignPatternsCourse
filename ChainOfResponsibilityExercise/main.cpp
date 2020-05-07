//
// Chain of Responsibility Coding Exercise
//
//     You are given a game scenario with classes Goblin and GoblinKing. Pleaase implement the following rules:
//
//         - A Goblin has base 1 attack/1 defense (1/1), a GoblinKing is 3/3.
//         - When the GoblinKing is in play, every other Goblin gets a +1 attack.
//         - Goblins get +1 to defense for every other Goblin in play (a GoblinKing is a Goblin).
//
//     Example:
//  
//         - Suppose you have 3 ordinary Goblins in play. Each one is a 1/3 (1/1 + 0/2 defense bonus).
//         - A GoblinKing comes into play. Now every ordinary Goblin is a 2/4 (1/1 + 0/3 defense bonus from each other + 1/0 from the GoblinKing).
//         - Meanwhile, the GoblinKing itself is a 3/6 (3/3 + 0/3 defense bonus from the other Goblins).
//
//     Here is an example of the kind of test that will be run on the system:
//
//         Game game;
//         Goblin goblin{game};
//         game.creatures.push_back(&goblin);
//         ASSERT_EQ(1, goblin.get_attack());
//         ASSERT_EQ(1, goblin.get_defense());
//

#include <iostream>
#include <vector>
using namespace std;

struct Creature;
struct Game
{
  vector<Creature*> creatures;
  int goblinKingCount{0};
};

struct StatQuery
{
  enum Statistic { attack, defense } statistic;
  int result{0};
};

class CreatureModifier
{
public:
    CreatureModifier(Game& game, Creature& creature, StatQuery& query)
    : game{game},
      creature{creature},
      query{query}
    {
    }

    virtual ~CreatureModifier() = default;

protected:
    Game& game;
    Creature& creature;
    StatQuery& query;
private:
};

// plus one attack for all other Goblins...
class GoblinKingModifier : public CreatureModifier
{
public:
    GoblinKingModifier(Game& game, Creature& creature, StatQuery& query)
    : CreatureModifier{game, creature, query}
    {
        if(query.statistic == StatQuery::attack)
        {
            query.result += game.goblinKingCount;
        }
    }

private:
};

// plus one defense for all Goblins including GoblinKings...
class GoblinModifier : public CreatureModifier
{
public:
    GoblinModifier(Game& game, Creature& creature, StatQuery& query)
    : CreatureModifier{game, creature, query}
    {
        if(query.statistic == StatQuery::defense)
        {
            for(auto creature : game.creatures)
            {
                if(&this->creature != creature)
                {
                    query.result += 1;
                }
            }
        }
    }

private:
};

struct Creature
{
protected:
  Game& game;
  int base_attack, base_defense;

public:
  Creature(Game &game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
                                                            base_defense(base_defense) {}

    virtual ~Creature() = default;

  virtual int get_attack() = 0;
  virtual int get_defense() = 0;
};

class Goblin : public Creature
{
public:
  Goblin(Game &game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

  Goblin(Game &game) : Creature(game, 1, 1) {}

  int get_attack() override {
      StatQuery query{StatQuery::attack, base_attack};
      GoblinKingModifier{game, *this, query};
      return query.result;
  }

  int get_defense() override {
      StatQuery query{StatQuery::defense, base_defense};
      GoblinModifier{game, *this, query};
      return query.result;
  }
};

class GoblinKing : public Goblin
{
public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) 
  {
      game.goblinKingCount++;
  }

  int get_attack() override {
      StatQuery query{StatQuery::attack, base_attack};
      return query.result;
  }

  int get_defense() override {
      StatQuery query{StatQuery::defense, base_defense};
      GoblinModifier{game, *this, query};
      return query.result;
  }
};

int main(int argc, char* argv[])
{
    Game game;
    Goblin goblin1{game};
    Goblin goblin2{game};
    Goblin goblin3{game};
    GoblinKing gk1{game};
    GoblinKing gk2{game};
    game.creatures.push_back(&gk1);
    game.creatures.push_back(&gk2);
    game.creatures.push_back(&goblin1);
    game.creatures.push_back(&goblin2);
    game.creatures.push_back(&goblin3);
    cout << "Goblin1 attack: " << goblin1.get_attack() << " Goblin1 defense: " << goblin1.get_defense() << endl;
    cout << "Goblin2 attack: " << goblin2.get_attack() << " Goblin2 defense: " << goblin2.get_defense() << endl;
    cout << "Goblin3 attack: " << goblin3.get_attack() << " Goblin3 defense: " << goblin3.get_defense() << endl;
    cout << "GoblinKing attack: " << gk1.get_attack() << " GoblinKing defense: " << gk1.get_defense() << endl;
    cout << "GoblinKing attack: " << gk2.get_attack() << " GoblinKing defense: " << gk2.get_defense() << endl;

    return 0;
}

