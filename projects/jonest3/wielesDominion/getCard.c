#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>

const char* getCardName(enum CARD card){
   switch(card){
	case curse: return  "curse";
	case estate: return "estate";
	case duchy: return "duchy";
	case province: return "province";
	case copper: return "copper";
	case silver: return "silver";
	case gold: return "gold";
	case adventurer: return "adventurer";
	case council_room: return "council_room";
	case feast: return "feast";
	case gardens: return "gardens";
	case mine: return "mine";
	case remodel: return "remodel";
	case smithy: return "smithy";
	case village: return "village";
	case baron: return "baron";
	case great_hall: return "great_hall";
	case minion: return "minion";
	case steward: return "steward";
	case tribute: return "tribute";
	case ambassador: return "ambassador";
	case cutpurse: return "cutpurse";
	case embargo: return "embargo";
	case outpost: return "outpost";
	case salvager: return "salvager";
	case sea_hag: return "sea_hag";
	case treasure_map: return "treasure_map";
   }
   return "error";
}
