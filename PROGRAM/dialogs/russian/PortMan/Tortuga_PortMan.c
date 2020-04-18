
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "Sorry!"), "Sorry!", "Pardon!", "Sorry!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "Good day. I am looking for Francois Gontier. His corvette '" + pchar.questTemp.Slavetrader.ShipName + "' must has been here in your harbor.";
                link.l1.go = "Tortuga_ratP_1";
            }
			
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("Hm... I have to disappoint you. Corvette '" + pchar.questTemp.Slavetrader.ShipName + " hasn't ever been here and Francois Gontier hasn't registered.", "You have already asked  about this and I've answered.", "I tell you that you have already asked about this Gontier.", "I ask you to don't bother me!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thanks. I'll do that.", "Hm, well...", "Yes, I have really asked ...", "Pardon, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  
}


