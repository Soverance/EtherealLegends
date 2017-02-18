// © 2014 - 2016 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Ethereal.h"
#include "LoadingScreen.h"

#define LOCTEXT_NAMESPACE "EtherealText"

void ULoadingScreen::HintConfig()
{
	FText Hint1 = LOCTEXT("Hint1", "Weapons  and  Armor  have  four  grades  of  quality  to  help  determine  their  power :  Common ,  Uncommon ,  Rare ,  and  Epic .");
	HintList.Add(Hint1);
	FText Hint2 = LOCTEXT("Hint2", "The  rarest  items  are  dropped  from  boss  enemies .");
	HintList.Add(Hint2);
	FText Hint3 = LOCTEXT("Hint3", "Enemies  can  hear  your  footsteps .  Step  carefully  to  avoid  them !");
	HintList.Add(Hint3);
	FText Hint4 = LOCTEXT("Hint4", "To  become  more  powerful,  gain  levels ,  equip  new  gear ,  and  find  new  spells  and  items.");
	HintList.Add(Hint4);
	FText Hint5 = LOCTEXT("Hint5", "You  can  lock  on  to  enemies  during  combat  for  more  accurate  targeting .");
	HintList.Add(Hint5);
	FText Hint6 = LOCTEXT("Hint6", "Toggle  sprinting  off  to  prevent  all  footstep  noise .");
	HintList.Add(Hint6);
	FText Hint7 = LOCTEXT("Hint7", "Increase  your  Defense  by  holding  the  ' BLOCK '  button .");
	HintList.Add(Hint7);
	FText Hint8 = LOCTEXT("Hint8", "Hold  down  the  ' ACTION '  button  to  continuously  attack .");
	HintList.Add(Hint8);
	FText Hint9 = LOCTEXT("Hint9", "Find  and  equip  better  gear  to  unlock  new  and  more  powerful  abilities.");
	HintList.Add(Hint9);
	FText Hint10 = LOCTEXT("Hint10", "Only  one  consumable  item  may  be  active  at  a  time .");
	HintList.Add(Hint10);
	FText Hint11 = LOCTEXT("Hint11", "You  may  carry  up  to  99  of  each  consumable  item .");
	HintList.Add(Hint11);
	FText Hint12 = LOCTEXT("Hint12", "You  must  equip  spells  before  you  can  cast  them .");
	HintList.Add(Hint12);
	FText Hint13 = LOCTEXT("Hint13", "You  may  equip  up  to  six  spells  at  a  time .");
	HintList.Add(Hint13);
	FText Hint14 = LOCTEXT("Hint14", "Become  more  powerful  by  gaining  levels ,  binding  new  gear ,  and  finding  new  spells .");
	HintList.Add(Hint14);
	FText Hint15 = LOCTEXT("Hint15", "There  are  three  available  weapon  types :  One - Handed ,  Two - Handed ,  and  Ranged .");
	HintList.Add(Hint15);
	FText Hint16 = LOCTEXT("Hint16", "You  may  equip  one  weapon  of  each  type .");
	HintList.Add(Hint16);
	FText Hint17 = LOCTEXT("Hint17", "Swap  between  equipped  weapons  using  the  ' CYCLE '  buttons .");
	HintList.Add(Hint17);
	FText Hint18 = LOCTEXT("Hint18", "One - Handed  users  may  also  equip  a  shield .  Ranged  users  must  also  equip  Ammo .");
	HintList.Add(Hint18);
	FText Hint19 = LOCTEXT("Hint19", "Use  the  Map  to  indicate  various  points  of  interest  within  an  area .");
	HintList.Add(Hint19);
	FText Hint20 = LOCTEXT("Hint20", "Reraise  allows  you  to  get  up  in  the  same  spot  you  died ,  and  also  prevents  enemies  from  regenerating  health .");
	HintList.Add(Hint20);
	FText Hint21 = LOCTEXT("Hint21", "Many  armors  have  special  effects  that  activate  when  equipped .");
	HintList.Add(Hint21);
	FText Hint22 = LOCTEXT("Hint22", "Some  items  are  only  available  in  shops .  Others  can  only  be  found  out  in  the  world .");
	HintList.Add(Hint22);
}

#undef LOCTEXT_NAMESPACE
