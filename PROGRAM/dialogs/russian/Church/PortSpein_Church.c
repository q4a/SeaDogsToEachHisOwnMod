// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+ GetSexPhrase("my son","my daughter") +"?", "Ask, I am listening to you..."), "I am listening, speak, "+ GetSexPhrase("my son","my daughter") +"...", "And it's the third time I say to you, "+ GetSexPhrase("my son","my daughter") +", ask your question.",
                          "A clergyman has a lot of work... and you are bothering me, "+ GetSexPhrase("my son","my daughter") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, padre..."), "Have nothing to say really...",
                      "I'll ask, I'll ask... a bit later though...", "Pardon me, holy father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//���� �������
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Tell me, holy father, does the name 'Juan' say something to you?";
				link.l1.go = "Consumption";
			}
		break;
		
		//���� �������
		case "Consumption":
			dialog.text = "It doesn't, my son. There are a lot of parishioners in my own town who have that name.";
			link.l1 = "I see. I am sorry for troubling you, padre...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}


