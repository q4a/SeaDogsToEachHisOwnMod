
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Brethren, there's an enemy in the ranks of the Inquisition!", "Raise alarm, brethren!!!");
					link.l1 = "Indeed, the enemies of the Inquisition are on the alert...";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hello there, "+ GetSexPhrase("my son","my daughter") +". What brings you here?..", "I am glad to see you in our abode, "+ GetSexPhrase("my son","my daughter") +". . What brings you here?"),
							""+ GetSexPhrase("My son","My daughter") +", we had already talked today. Do you need anything else?", ""+ GetSexPhrase("My son","My daughter") +", the acolytes of our order are not known for their limitless patience. So, let me ask you once again: is there anything you need?",
							RandPhraseSimple("Not only are you idling - you're distracting others from their duties. I am not speaking another word.", ""+ GetSexPhrase("My son","My daughter") +", I am not fond of pointless and senseless talks. I am not speaking another word."), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Just dropped in..", "Totally  full of business..."), 
							"Oh, no, Father......", "No, padre, I just wanted to speak...", RandPhraseSimple("Hmm...", "Well, as you wish, Father..."), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //����� �� �������
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "Goddammit, that's a spy! Seize him!!!";
					link.l1 = "Caramba!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("This is a guarded cell, and it is strictly off-limits.", "Don't even think about entering - it is punishable by death.", "Just one step into this cell - and you're done for.");
					link.l1 = RandPhraseSimple("I see, soldier.", "I see...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //�����������
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Ho-ho, isn't it funny to watch those hypocrites going straight to hell?!", "Oh my, did someone really dare to challenge them?!", "They tortured me to near death, and I'll be going soon...");
					link.l1 = RandPhraseSimple("Heh!", "Arrgh...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Those hypocrites are totally inhuman. They shall burn in hell for everything they'd done to us...", "They were torturing and tormenting me every day! And I am not guilty in our Lord's face!", "My cellmate died yesterday... They were torturing him on the rack for two days... And how much is left for me?..");
					link.l1 = RandPhraseSimple("Hmm... Well, I don't know...", "Oh, I see...");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}
