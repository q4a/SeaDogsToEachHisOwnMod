// ������ ������, ����� �� ����
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------���� angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //������� ������� ������������
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //���� ����������� ������� �����. � npchar.angry.name ������� �������!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------���� angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
			// Addon 2016-1 Jason ��������� ������� ���� 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "�, �����, ������� ������? ���� ���� �� ���, �������, ���������� ���������� ���! ���� ����, � �� ����, �� ������, �� ������, �� ��������� ����� �� ����! ��� ���� ��������� �����, �� �� � �����, ��������?";
					link.l1 = "���, �� � �����... ������, � ������ �������, ��� ������ �� ����. � ���� ��������. �������� ������ ��� �� �����, � ����� � ������������ ��������� ���������... ������� ����� ����� ��������� � ��������� �����.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason ���
			// ���� ���� ��������, �� � ������� ���� � ���� ������ � ������ ������
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "� ���� �� ��� ����?";
				link.l1 = "�����������, ������. ��, ����. �������� � ���������.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "������ ������?";
				link.l1 = "��.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "� ��� � �������� ���������! ���� �������, ���� ����� ����� � ������� ��� �������� ������. �� ������ ����� ����������, ��-��?!";
				link.l1 = "��� �����, ��-��. ��� ������������?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "������ �������!..";
				link.l1 = "������, �������� �����. �� ���� � ������, � ���� �� ����� �������� �����...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "� ��� � ��� �������� ���������!";
				link.l1 = "��-��! ��������� ��� ��������!";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("� ���� ���� �� ���? ���? ����� ���� ������!","��, " + pchar.name + "! � ���� ���� �� ���? ���? ����� �� �������� ����.") +"",
                         "� ������� ���� ���������.", "���� � ��������� � ����, �� �� ����������� ��������� ����!",
                         "��-�-��, ��� ��� ������ �� ��������, ���� ��� �������.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� �����.",
                                               "�������, ������...",
                                               "������, ������...",
                                               "��...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("� ���� ����� �������? ��������� ���� ��������? ��� ������ ��� �� ����, ��������, ��� ��� ����� ���� �������� ������ ���������.", "��, ��������, ������, �� ��� �����. ���� �������� ������? ������ �� �������� - ����� ���� ������ ������. ���� ������ ���������!");
				link.l1 = RandPhraseSimple("��������, � ���� ��������� ��������...", "������ ��� ������ ��� ��������...");
				link.l1.go = "pirate_town";
				break;
			}
			// ���� - ��������� ��������� ���������
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason ��������� ������� ���� 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "������, ������� �� ������ ������� �� ����? � ������� ������ ����� �������, � ������� �� �����-�� ������ �� ���������, �� ��� ������, �� � �� ���� ���� �����, ������! ��� ������ ���� ������ �� �����������?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "����� ���� � �������, ������. ��� ������ ���� ������ �� ����������� ��� ����?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason ��������� �������
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "� ��� ������... ��� �� � ���� �� ������� ������-������ ��������� ������?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "� ������ ���� ���� �� �������.";
				link.l2.go = "Mtraxx_silktrade";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("� ���� ����� �������? ��������� ���� ��������? ��� ������ ��� �� ����, ��������, ��� ��� ����� ���� �������� ������ ���������.", "��, ��������, ������, �� ��� �����. ���� �������� ������? ������ �� �������� - ����� ���� ������ ������. ���� ������ ���������!");
				link.l1 = RandPhraseSimple("��������, � ���� ��������� ��������...", "������ ��� ������ ��� ��������...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason ���
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "�����, ������ �������!..";
				link.l1 = "������, �������� �����. �� ���� � ������, � ���� �� ����� �������� �����...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "��� ���� ������, ��������!";
				link.l1 = "� � ����. ������� �� ������� �������������� ���������!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "�������, ��������! ������ ��������?";
				link.l1 = "���� � ����, ������. ���������!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "� ��� � �������� ���������! ���� �������, ���� ����� ����� � ������� ��� �������� ������. �� ������ ����� ����������, ��-��?!";
				link.l1 = "��� �����, ��-��. ��� ������������?";
				link.l1.go = "patria_10";
				break;
			}
			// ���� ���� ��������, �� � ������� ���� � ���� ������ � ������ ������
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "� ���� �� ��� ����?";
				link.l1 = "�����������, ������. ��, ����. �������� � ���������.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "������ ������?";
				link.l1 = "��.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "� ��� � �������� ���������! ���� �������, ���� ����� ����� � ������� ��� �������� ������. �� ������ ����� ����������, ��-��?!";
				link.l1 = "��� �����, ��-��. ��� ������������?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "������ �������!..";
				link.l1 = "������, �������� �����. �� ���� � ������, � ���� �� ����� �������� �����...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "� ��� � ��� �������� ���������!";
				link.l1 = "��-��! ��������� ��� ��������!";
				link.l1.go = "patria_x29";
				break;
			}
			// ���� ��������
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "��� ���� ������, ��������! ��� � ���� ���� ������?";
				link.l1 = "������, � ���� � ���� ���� ��������. �� ����, ��������� �� ����� ���� �������, �� ��� ��� ��� ����� ����� ���� ������.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "��, ��� � ��, "+pchar.name+". � ������ ������ ��������. ������ ������ �������� ���� ����� ��������� � ��������...";
				link.l1 = "�� ����� ������ ���, ��� ��, ��� ��, ��� �������� ������� ��������. ��� ���?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason ��������� �������
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "� ������ ���� ���� �� �������.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", ��� ���� ������! ����� ���������"+ GetSexPhrase("","�") +" �� ���� ���?",
                         "�� ��� ���� ���?", "����� ��� ����� ������������? ���� ���� ������ ������, �� �������� ������!",
                         "�� "+ GetSexPhrase("������� �����","������� �������") +", ������� ���� ����. �� �������� � ������������� � ����� � ������ �� �����.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��, ����������, ������ ��� ��������"+ GetSexPhrase("","�") +", ���������. ������ �� ���� ���.",
                                               "������, ������ ���...",
                                               "������, ������, ������...",
                                               "��� ���� ������, �������"+ GetSexPhrase("��","���") +"!!!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== ������ ����� ���� ���, ������� ������� � ������� =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("������ ����� ���� ���!!! ��� ��� �� ����� ��������?! ��, ������, "+ GetSexPhrase("��������","�������") +"...", "��, �� ���� ��� ��� ���������?! �����, �������"+ GetSexPhrase("","�") +" �������� ����? ��, ����� ���� �����...", "������, �� ���� ��� �����"+ GetSexPhrase("","��") +"? �� �� ���"+ GetSexPhrase("","����") +", �����������! ��, ������, ��� �� �������"+ GetSexPhrase("","�") +", ����"+ GetSexPhrase("��","��") +"...");
			link.l1 = LinkRandPhrase("������!!", "��������!!", "�-���, ����!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== ���� ��� angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("����� ���","��������") +" ������!", "��� �� ����� ����!");
			link.l1 = "��...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //����������� ����� 10 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "���� �� ����� ��������� ���� �� ���� ������� �����������. ������ ��������� ����� ���� ����� ���������...";
        			link.l1 = "� �����"+ GetSexPhrase("","�") +".";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("�� ���� ������� ������"+ GetSexPhrase("","�") +", �������� �������.", "� �� ���� � ����� ��������, ��� ��� ���� ����� ���� �� ����������.");
			link.l1 = RandPhraseSimple("�� ��� ������...", "��, �� ��� ��...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //����������� ����� 10 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "�������, ������ �� �� ������ �������� ���� ������� �����������, ����� ��� �������� ���� �����. ���������, ��� ��� ����� ����� ���������.";
        			link.l1 = "������, �� ������ ���� ������ - �� ����...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= ���� ��� angry =============================
		
//--> -----------------------------���� - ��������� ��������� ����������� �����---------------------------
		case "Temptation":
			dialog.text = "��! ��� ��� �� - ����� ������? ������ �� ������ �����, �������. ������ ��� ��� ��������� � ����� �������� �������������, � ���-�� ��� ������� ��� ������� ��� ����. �������� �� �������� �����������...";
			link.l1 = "��� � ������ ���� �������. ����� ���� �� �� �������. ��������� �� �����. � ������ ��� ������ ���������...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "������ ��� �����. ��������������, ��� �� ����� ������ ��������� ������� ������ ����� � ������ ������ �� ������ '����������'. � ���� ������ �� ������ ���� �������� ����������� ���������� � ������. ���������� �������� �������, ��� ����� �����.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "������ ������! ��� ������ ����� ��������?! � ��� �� � �����, ��� ��� ������ �������?!";
			link.l1 = "����� ����� - ������� � ��� ���� �����. � �������� � ���, ��� '����������' ���� ����� ������ � ����� ������ ������, ������� �� ���� ���������. ���� ����������� ��� ������� ����, �� ���� ������.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "������ �� �������! ��-�� ��� ����� ����� �������� �������?";
			link.l1 = "� ����� �������������� � ��������� ��������. � ������� � ���� ���������, ���� �� �� � �����. �� � ������ �������� ������ ������� �������� �� ������ ����. �� ������, ��� � ������ ������ ������� ������ ��, � ������� ���������� ��������.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //���� 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "���! �� �� ����� ������ ��� ������ ������ ��� � ���������� �.�. - ��������� �����, �������������� �������...";
			link.l1 = "��� ����������. ������� ����� ��-��������. �� ��������� �� ��������� ����� � ����� ��� ����� � �����-�����, ����� ����� �������� � �����, � �����. � ���� ���� �������������� �������������� ���� ��������� - � ������� ����� � ��������� ��������� �����, �������������� �����, � ������� � ���������� ��������� �����.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "���� ������! ��� ������ ���������? � ����� ����� ��� ��� ������������?";
			link.l1 = "�� ����������� ������ �� ����� ���������� ��������. � �� ���-��� ���, ��������� � ���� ������. ��, � �� ����, ��� � �� ��������, �� ������������ �� ���, ������� ����� ������. ������� ����. ���, ��� ������ �������� ������, �� ������� '�� �����'.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "��� ��� �������?! � ������� ��� �� �����!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // ����� ���
			{
				link.l1 = "������� �����, ��� � ��� ����, � ��������� �������� ����. � ����� ����������� �� ����. ������ ���� �������� ������ �� ��������. ������, �� ������ ���� ����� �� ������ �� ������� �������? ��� ��� ������ �������.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "������� �����, ��� � ��� ����, ��� � ��������� �������� ����. � ����� ����������� �� ����. ������ ���� �������� ������ �� ��������. ��, � ���������, ������ ��� ����...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "������� �����! � ������ ������ ����� ����� ��������� �� ��� ����� ������... � ���� � ����� ������� � ��� ����������! ��� �� ��������! ���, ������ ��� �������.";
			link.l1 = "��� � ������! ������ �� ������ ����� ������ � ����.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // ���� �������
			dialog.text = "��� �����...  � ��� �������, �� ������������� �������� �����?";
			link.l1 = "��. � � �� �������. �����, ������, �� �������!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "����?! ��� ��� ���������? ���� ������� ����������?";
			link.l1 = "���. � ������ ����� ������� ��� ������, ��� ������. �� �� ���� ��� �������... ������, ������� �������, ��� �� ������ ������ ������� ����� ����� ����������� ��������. ��������� ������ ��������� ��� �������. �������� �� �� ������ ���� ����?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "���! �� ��� �����������? ���� ������ �������� - ������� �����! ���� �� �����, ��� � ��������.";
			link.l1 = "����� ������. � ���, ��� �� ����������.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // ���� �������
			dialog.text = "���, ����� ��� �������. ������� ��� ��������. ��� � �������, �� ���� ���� ����������?";
			link.l1 = "��. ������ ��. �����, ������, �� �������!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "��, � �� �������� ����� ����� ������� � ���� ���� �������������. ���, ������ ���� ������ � �������.";
			link.l1 = "�� ��������! ����� �������!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("�� �������� 300 ��������");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason ��������� ������� ���� 17/1
		case "Temptation_13":
			dialog.text = "��, �� ��� ��������� ��� �������� ������� ����� ������ �� ������... ��������, ����� �� ���� ����? � ��� ��, ������� ����������������? ������ ���-�� ��� ������� ��� �������...";
			link.l1 = "��� � ������ ���� �������. ����� ���� �� �� �������. ��������� �� �����. � ������ ��� ������ ���������...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "��-��-��, �� ������������ � ������� �������, �����? � ���, � ��� ������� �� ��������� ������ �������� � ����, ������ �� ����? ��, ��������� ������!";
			link.l1 = "������, �����, �������, ������� ����� � �������. ������ � ��� ����� ����, � ��� ���� ����� ������, ������ ������� ���������. �� ���� ����� ������ ����� ���������� ��������!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "�����, �����, ��������! � �����-������, �� ��������� ������: ����� �������� � ������ �������� - ���� ����, � ����� ���� - ���������... �������� � �������. �� ������ - ��� ����������, � �� ���������?";
			link.l1 = "��� �����.";
			link.l1.go = "Temptation_4";
		break;
		
		// ���� ��������
		case "shadows":
			dialog.text = "�� �������, ��� ����� - ��� ������! ����������, ��� ��� � ����?";
			link.l1 = "������, ������... ��� ������ ���. ��� �� ������ � ��� �������?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "��! ��� ��� ����� �����, ������� ���� �������� ������ ������, ������� ����������� ����� ��������. � ��� ��� ��� � �������� ������. ���� ���� ��� ��������� ������� ��� ����� ��� ������ ������� �����. �� �� ��� ����� � ����, � �������� ���� ���� ����� �������� �������� �� �������... ��� �� � ���� ��������?";
			link.l1 = "��� ����� ��� ������ ����� ����-������. ���� ����� �������� ������ ��������. ��� �����... ������ ���������.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "��� ������ �������. ���� �������� ������������� ���� ������. �� ��� �������� ������� �������� � ������� ���������� ������������ ���������� � ����� ���������� �� ������. ������ ����� �� ����� �� ��� ����� �����-�� ������, ������ �� � ��������� � ���������\n����� �� ��� ������� � ������ �������� - ��� ����� ��� ������ ������� �����. �� ����� ���� ��� ���������� �������� ������� ������, ��������.";
			link.l1 = "�� ����� ��� ������?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "��� �� ��������? �������, ���. ����� ��� ��� ���� �����? �� ���� � ���� ���� �����, � ������� ����, ������ ����� ����������� ������. ������, ��������, ������������ ����������� ��� ��� �������.";
			link.l1 = "����� ����. ����� ��� ������� ��������� - ��� �� �������� �����������. � ���� ����� �������� ���� �������.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "� ����, �� �������� ����� ������ �� �������. ����� ������. ������ ��������� ��� ���������� ������� ���������, � ���������� ������� ������������ ����������� �������� '������'...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("������ ���...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //������ �����
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... ��������� ��, ������, �����, � ��� �������� ���������� ������. ������� ������������ ���, � ������ �� ��������� �� ����� ������ � ����� �� ���-���� - ��� �� ��� ���������� �������� '�����'. ����� � �������� ��������� ����� ��� ����� ��� ���� ������������ ������� �����.";
			link.l1 = "���... � ��� �������. �����, ��� ��� ����������� ���������� ����������, ����� ����������� � ���, ��� � ���� ��� �������. �������������, �������� �������. � �� ����� ��� ��������?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "� ��� ��! ��� ������������ ������ �� ���� ��� �������, �� ��� ���, ���� �� �� ������ ��, ��������� ��������. ����� ����� ��� �� ��������. �� ������� ���������� �������� ������, ������ ��� ���� ��� ���� � ���, ����� �� ������ �� ����������� �� ����\n������ ����, ������ ��� - �� ��� ������ �� �� ������� ����� �� ��������, ��� ���� ����� ���� ��� ���� � ���� - ������ ����� �������, � '������' ��������� ���������� �� ����� ���� ������. ����, ��� ����� ��������� � ���, ��� ����� �������� ������ ������� � ����� � ��������, ������ �� �������\n� ������� �� ��������, �������� �� ����� ���������� ���������� � ��������� � ������ �����������, ���� ������� ������ �� ��������� ��������������� � ����������. �������, ��������� ���� �� ������, �� ��� �� �������� ����������� ���������� ���������. � ������ �� '�������' ������ ����� ���� ���� �� �� ����� �����. ��� � ����� �� � ��������.";
			link.l1 = "� ��������?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "�-�, ��� ���� ������ ��� ��... �� ��������� ��� ������� �� '�������', � �� ������, ��� ��� ���� �������� ��������. ����� ��������� ������� ������ � ��������� ����������� � �������� - ����� ������ �� ������ �����. ���� � ��� ��� ������ � �����������, �� � ���������� ��� �� �������\n�������� ��������� � ��� ������� ���� �������������, �� ��� ������, ����� ������, � ����� �� ������, � �������� �� ���� �����, ��� ���������� - ������ ������� ��� �� ����� ����� � ���������� ������, � ��� ���������� ����� ������� �� ���� ���������� �������� ��������� � �����\n� ����� ���� ��������� �����, ������������ � ����� ���� �� ������� - �� �� ����, ��� ��� ����� �������: �����-��������. �� ������ �������� ����� �� ������, � ���� ������ ������������� ��������� ������ ����\n����� ���� ������������� �� �� ��������, � �� ���������. ������, ���� ���� ����� ��������� ������ � ��������, �� ������ �������� �� ���� � ������ ����� ������ ��������� ���� ��������. �� ������ ���������� � ��� ��������, ��� �.";
			link.l1 = "��� ���? � ��� �� ���� �������?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "�� �������. ������ ������, �������, �� ���������� � ����, �� ��, ��� �� ���� � ���� ����� ���� �� �������� - ��� ����. �� ��� ����� ������� � ����� �������� ����, � ����� � ���� ���� - �����������, ��� ��� ��� ������� ���� ������ ��� ��� �����\n����� ����� ��������� ����� �� ������ �������, �� ������������� ����� ���� ���������� �� ���������, � ��� �����, ��� ������ ������� ������������ ����������� ���������. ��� �� ��� ������, �������� - ���� �������������� ����������\n� �����, ��� ����� �� ��� ���� ������ �������� � ����� ������, ������ ������������� �� ����� ������ ����� �� �� ������� - ��� ������ �� � ��������� ������ �����, � ����� ����� ������������ ����� � ��� ����� ����� ����������� ��������\n�� � ����� � ���� � ��� ������ ��� � �� �����. ����� �� ������ ��������� � ���, ��� � ��� �������� �����, � ������ ���, ���������� � ������, ���� ��������� ���. ��� ����� ���������� ��������� ��� ����: � ��� ������, � ��� ��������, � ��� �����, � ��� ��� �����. ������� ���.";
			link.l1 = "�� ���. ����� ���.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "���?! � �� ���������? �� ���?!";
			link.l1 = "��. ������� ����� �� ��� ������. ������, ���, �� ��������� ����� �������� � ����� ����������, ������� �������� ������, ������� ���. ����� ���� �������������. � ���� ���� ��������������.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "����������! � ��� �� ������ ������?";
			link.l1 = "�� �������� ��� ������� �������, � ����� ���� �������� � ����-�����. ������, ������, � ������ �� �� ���� ����� ������. �������, ���������� � ��������� ������ ������� ��� ������ ���������� ��������, ���������� �� ��� ��������.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "���� ������! �������������� ����� ������ �������� ����� ������� ���! �������, ��������... ������-��! ������ �������, ������ � ������� ������ �������� ���� �������� �������� �������... ������, ����� ���� �������� � ������-��������...";
			link.l1 = "�� ��� ������ � ���?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "����� � ����� ��� ����������, � �������� ���� �������� ���������� � ������ ������� ������. ��� � ����� �������� ������� ������ ������� ������. ��� ���������� �������� ������� ���������� ������ �������� - � ������� ���������� ������ � �������� ����� ������ �������� �����. ��������, �� � ��� ����� ������.";
			link.l1 = "����� ���������. ������, ���� �������� � ����� ���������� ���� ����� ���������...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "�������, ���... �����, �������, � ��� ���� �� ������ ����� �������� � ������� ��� ����� ������� �����? � ���� ���� ���� ���-���?";
			link.l1 = "��� ����� ������, ��������������, ��� ���� ��� ����� � ���� �������� ����, ������ �������� �����, � ����� ����� ������ ��� �������. ��, ��� ��� ����� ������ � ������� �������, � ������ ������ ���� ���� ����������.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "�� ���� ���� ��� ����� � ������� ������ ������ �� ����. ���-���� �������, ��� �������� ������ �� ������� ������ � �������� ����������. ��� �� ��� �� ������.";
			link.l1 = "��������, �����, � ������� ����� ���� ���-�� ���, ����������� � ���� �������? ��� ����� ��������� ������ ������!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "��... ��������, ��. ���� �� ������� ������, �� ������� ��������� ������, ��� ������� ��� ������. ���� ������, �������� ����� ����� �������� ����������, � ������� ����������� ����������� ���������� ����������. ��� ��� ������, �� ����������� ���������� ����, ������������ �������������� ������\n��� ��������� ���������� ��������� ���� � ��� �������� �����. ������� ���. ��������, ������ ������ ������� �� ���������� - �� �� �������������, ������� �� ���� ������ ������ ��������.";
			link.l1 = "� ��� ��� �� ������?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "������ ���������... ���: 21 ��. 32' �������� ������. �� ����, ��� ���� ��� �������.";
			link.l1 = "�������. �����, ������, �������� ������� �� ����������� �������. ��� ��������!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// ���� �������� ��� ���������
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// ��� ��������� �������������� ��������� ��������
			LAi_LocationDisableOfficersGen("Shore67", true);//�������� �� �������
			// � ����� ����������
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// ���������� ����� ���������� ������
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// ��� �� ��������
		case "terrapin":
			dialog.text = "��, ���-��� � ���� ��� ���� �������. ��� ��������, ������������ ������� ������������ �� ������ ���� ��-���, �� � ��������� ��������� � ������� ������� ������������. ���� ������� ��� �������� ������� - ��� ������ ����� ���� ����, �� � ������� � ��� ������. �������� ����� ������������ ���� ���������\n��� �������� ������������� ���� �������� ������� � ����� ���������� ������������ ��� ������� ������. ��� ���, �, ��������� ����� ���������� ��������� K������, � ������ - � ����� ���������� �������, ����� ������ �� ������� ������� ���� ���������� ����.";
			link.l1 = "� ��� ���?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "� ����� ����? � ����� ������, �������� � ������� �� ����. ��� ��� ������ ����� ���� �� ��������, �� ���� �� ������������� �� �������� �������������. ������ ���� - ��� ��� ������� �����, ��� ��� ��� ������ �������� ���� ����� ������.";
			link.l1 = "�� ��� ��, ��� ��� ��� ��� ����� ��������� ������ ����� - �� ���� ������� ������� ����� ����� �� ����. �������, ������! ����� � ���� ���������� �������?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "�� ����� ������. ������� ��������� ����� �� ������� ����� �������.";
			link.l1 = "����. ����� ����� ���������� � ��������!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// ��������� - � �������!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // ������� ��������� �������
		break;
		
		case "pirate_town":
            dialog.text = "������ ��������? �� �� ��� ���������, ���� �� ���������? � �����, ��������� ��� ������� ���� - � ������� �����, ����� ��� ������ ���� '�������'. ��� - ������ �������� �� ��� ������ �������.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "������, � ����� ���������.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "� ��� �����. �����.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//������� �������
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "��� � ������! ������, ��� ���� ��������� �� �����������. �� ������, � �������, �� ������ �� ������ ������ ����� ���������.";
			link.l1 = "�� ����. �� ����� ������ ��� ���������. ������...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- ��������� ������� --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "������� �������� ����������, ����� � ������ ���������. ���������� ����� � ���� ������ ������. ����������!";
				link.l1 = "���... �������.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "����� �������? ��-��! ������... �� ������������ ����, ��������, ��� ��������� ����� �� ���� �� �����. ���� �� ����� ������ ����� � ������� ������� �������� ����� - ����� ���������� �����, � �� ��� �� �������� ����������. � ����� ���� �� �� ������ �������� ������, ��� ����� ������ ������ �� ������ ������ � �������������� ����� ���� - �� ���� �� ���� �� �� ����, ��� ����� �� �� ���������. �� ��� ���?";
			link.l1 = "� ����� � ����� ��������, ������. ���� ������ � �������� �������� ���� �� �������, � � ���������� ������������ �� ���� ������ ��������� �� �����.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "���, ����� ������� �����! ������, ������, �������, ����� � ������...";
			link.l2.go = "Mtraxx_exit";
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "� ���-�� �� �����: �� ��� �����?";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "��-��, �� ��� ��, ������ �����, ����� � ����. ��� �������� � �����-������� ������� ���, ��� ����� ��������� ������� ������ �������� ������� �������, �� ��� ������, ��� �� ����� ����� ��� �������� ������. �� ������, ��� ��� ����� - ������� ������?";
			link.l1 = "������. ������ � ������� �������.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "� �����, ��������. ���� ����� �� ���� ������� �� ���������� ���������� ������� ������, � � �������� ������ ����� �������� � ������ ��� ������. ������ �� �������� �� �������, �� ��� ������ ������� ������ ������ �����. � ��� �����-�� ����������� ���������� ����������, ��� � ���� ����� �������� ������ ����� ������, ��� ������� � ���� ����������� ���� � ���������, ������ ������.";
			link.l1 = "����� �� ������ ������ ���������� ��������� ����������? ����� ��� ������� - � ������, ��� ������� ������������ ��� ����...";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "� �� �� �����, ���� �� �� �� ���������� ������ ����������. ��� ���, ��� �������, ����� ������ � ���� ���������� ����, � �� � ����� ����� �����. ��� �� � ��������� ���� �����. ����������� � �����-������� � �������� ������� � ���� �������� �������, � ��� ����� ����� ��� �������� �������. ����� ��������� ��������� - ����� ���� �������, ����� � �������� � �� ����.";
			link.l1 = "� ���� ��� ��� ���������� �������� �� ������� � �����?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "����� ������� ��� �������������� ����, ��� ���� ������� - ���� � �������.";
			link.l1 = "������. �� ���� � �����-������� �������� ��� ����������?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "���� ����� ���������� ����� �� ����� �������� ������. �������� ��� ��� � ������ - '�������� ��������'. ��� ������� �����������. � �� ����� ������� - ���������� ���� ������, � ��� ����� ����-������-������ ����� � ��������.";
			link.l1 = "��� �����, ������. ���������� � �����-�������.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // �������� � ����� �����
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "��� ��� ���������� � ����� ��������. ����������!";
			link.l1 = "���������� � � ���� ��������� �������� ������, ���� ��� ���� � ��������. ������� ��������� ��� '������' � ������� ����������. ��� ������: "+FindRussianQtyString(i)+" �������� ������.";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("�� ������ "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" �������� ������");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "���-���... �����, � �� ���� ������������ ������ ��������������, �� �������? ��� �� ��� ������ � �����? � ���������� ������������ �� ���� ������ ���� ��������� �� �����? �� ���, �����, �������, � ������ �� ��������? �� � ��������� ���� � ���, ��� �� ����� � ������ �������� "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" �������� ������. ������ ����, ��������, ���� �� ���� ���, � ����� �� ��������� ���!";
				link.l1 = "���������!..";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("�� ������ "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" �������� ������");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "�������� ������, ��������! �� ������� ���� � ������ �������: �������� ������� ���� � ������ ������ ��� ������������. �������! ���, ��� �� ������ � ����.";
				link.l1 = "��� ������ ���� ����, ������?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("�� �������� "+FindRussianQtyString(i)+" �������� ������");
			TakeNItems(pchar, "jewelry7", i);
            dialog.text = "�� �� ��������� �����, ��-��-��! �������� ������ ����. �������.";
			link.l1 = "�������, ���. ���� ��� ��������� ��� ���� � ���� ������ ��������?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_SetStat(pchar, 57, 1);
		break;
		
		case "mtraxx_10":
            dialog.text = "��� �������� ����� � ���� ������ ���� ������. � ��� ��� ������ ���������������� �����, ��� ��, � ���� �������� ���� ����������� ����. � ����� ����������� ��� ������ ��� ������ ����� ������ '�����' ��� ������������� �������� �� ����� ������� ����, �� �� ����� �������. ��� ��� �������. �������� ������, �� � �����, ��� �� �������� ����� � ������, �����, ��� ������. �������, �� ����� ����� ������ � ������ - ������ �� ���� ����� �� ����, ��-��!\n��� ���. ���� ������� ������ �������� �������� ����-�������� ����������� ������ � ����� ����, � ������� ����� ������ � �������� ��� ����� �������� ���� ������������ �����. ��� ����������� ������ � ������� ����� �� �������, ��������� �������� ��� �� ������ ������������� �������� ��� ���� ������ �������� �����. ����������, �� ����-�� � �������� ����� ������� �� ����� ��������. ���� �� �� � �����, �� ����� ����� ���������� ����������� ������, ��������� ������������ �������� ������� �������� �����, �������-�� �� ���� ����� �����\n������ ��� ����� ������, � ��� ������� - �����, �� ������ ���� ���� �� ����������. ��������-������� �������� �������� ��� �������� ���������. ����� ��� ������ ��������, ��� ���� �� ������� ����, ������� ������� �� ���� ����� �������� ������, ������ ������������ �������� ���������, ������ � �� ��� ��� �� ���������� �������� ��. ��� ��� ������ � � ���� �������� ����\n��� �� ��� �� ���� ���������? ������� �������� ����� ����� �����, � ��� ������� ������� ������������ ���� �� �������. ������� �� �����������, ������ ��������� ���� � ������ ����� ��� ����� � �������, � �������� ��������� ��� ��� � ����� ��������, �? ���� ���, �� ������� ����������... �������, ������ �������������������. ����������� � �����������, ����� ������ ������� � ������� ���, ��� � ���������� ������ � ����� �� ��� ���, ���� �� �� �������� ���������� �� ����. ����� ������������ � ����� � ������ ������ ������ ����������� � ����������� ���\n�� �� ����� ���������� ����. ��� ����������, ������ �� ��������, � � �������� �� ������� - � �������� �������� ������ ����� ����������. � � ����� �� �������� - ������ ��� �� ��� ������� �������� �� ����� �� ��������. ����� �� ������ � ���� ����, �� �� �����������: ������� �� ���� ������� ������ ������ ���� ������� ���� �� ��������. ���, ���� ���� �� ����-���������, �� ���������, � �� �� ����� ���, ����� ��� ������� ���� ���������������, ��� ���� ����� �������.";
			link.l1 = "���... ������ �����, ����������� � ����...";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "��, � ��� � "+GetFullName(pchar)+" ����������� ��������! ���������� - ��� � �����������?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "����� � ����������. ��� ������� � ����� ����-������. �� ���������� ���������� ������� ������������� �������� � ����� �������� ��� ���������� �������� �� ��� ������� �� ���� 25 �������� �� �����. ����� ����� ��������� ��� ���� � 10 �� 15 �����, �����, �� ���� ������. ������ - '�������� �����'. �� ������ ���������� ������, ��� � ����������� - � �� ������� � ���������� ��� ������, � ����� ������� ��� ��������� ������ ���� ���������������. �� �� ����� �� ��� ������, ������.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "����� � ����������. ��� ������� � ����� ����-������. �� ���������� ���������� ������� ������������� �������� � ����� �������� ��� ���������� �������� �� ��� ������� �� ���� 25 �������� �� �����. ����� ����� ��������� ��� ���� � 10 �� 15 �����, �����, �� ���� ������. ������ - '�������� �����'. ����� ������� ��� ����� ������ ������ �� ������.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "������� ���������, �������! �� ���� ���������. �� ��� ������ ����� ����� ������� ��������, �������� �������� � �������, � �� ������ ������. ����� �� ��� ����� �������� ���� - ����� ������ ����� �������� ������ �� �����, � �� �������� ���� ����."; // ������ ������� 3
			link.l1 = "������, ������. ����� ��������. � ��������� ��� ��� �����-������ ������...";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "���� ��� ���� �����. ���, �� �������.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // ������ ������� 3
				SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "���� �����, �������, �� ����������� �� �����. �� �������� ������� ������, �� � ��� �� ����� ������ �������, ��� �� ������ �� �������� ���� ���� �� ���� ������, ������� ���� �����������. �� ������� ��� ����� ����� - ����� �� ��� ����� �����, � ��� ���� ������ ������ ������ ������ ����������, ����� � ���������.";
			link.l1 = "������, ������. ����� ��������. � ��������� ��� ��� �����-������ ������...";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "��� � ��, "+pchar.name+". ��������� � ����� �������.";
			link.l1 = "����� ������ ��� �� ����, ��-��! ����������� ���� ������.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "����� ������� ������ ������ ���������� ������ ������ - 105 ������� �����. ��������� � ����������� �� 20 �������� �� �����, ���� �� ����������� ������� � ���� �� ������ ������ ������ ����. ��� � � �����. ���� ���� ���������� 525 ��������. ����� � �����, ��� �� �������� ����������� - ��� �� 1 ������� � ������. ����� �� ��������� 630 ��������. �����.";
			link.l1 = "�������������, ������!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("�� �������� 630 ��������");
			PlaySound("interface\important_item.wav");
            dialog.text = "��� ��� �� ���. �� ������ �������� �������������� ������� � ����� ����.";
			link.l1 = "���������... ���������.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "���� ���������� ����� � ��������� ����� ����� ������� ������, ��� �� 100 ������� � �����, ������ ���� � ���� ���� ��� ����� ������ ����, ������ �������� ��� ���. ���������� - �� 20 �� 100 �������, ���� - � ������� ���� �������, ������ - 24 ������� �� �����.";
			link.l1 = "������! ���� �����, ��� ������� - �������.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// �������� ������
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "������� � ���� ������?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "����� ������. ����� ������, ��� �������������� - �� 24 ������� �� �����.";
			link.l1 = "�������������!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "� ���� 100 �������. ����� ������, ��� �������������� - �� 24 ������� �� �����.";
			link.l1 = "�������������!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "��� � ������. ��, � ������ �������� � ����� ��������. ������� � ���?";
			link.l1 = "� ��� ��! � � ��� ������ ������ � ������������ ������ � ����.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "������� ���� ����, "+pchar.name+", ��� �� ������ ������� �������? � ����� ����� ���� ������� �� ���? ����, ������� � ���������� ��� ����, ��������� ��-�� ����� ����������������. �� ���� ����� �������, ��������. ����������, � �� ���� ����������� � ������, �� ������� ������ ����������.";
			link.l1 = "��� ��� �����...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40) sTemp = ".";
			else sTemp = ", � ����� �������� �������� ������ �� 40 ����.";
            dialog.text = "����� ������ �����������. ��� ������ ����� �� ��� ������ ��� ������� ������� ��� �����, ��������� � ��� ��� ��� ���������. ��� ������, �� �� ������. ��������� ��������� � ��� ������ ��� ���� ������ �����, � �������, �� ����� ������� ��� ���������. ��� ���, ��� ������ ����� ��������� �� ����� ���������� �������� �� ��������� ������� ������ ��� ������������� ���� ������� �� ������, � � ���� ���������� ����� �����. � ����� ��������� � ��������� ������� ��� ������� � ��������� � ������ � ������� �� ������� ���������. ��� �� ������ � ���� �����\n���� ������: ��������� ����������� �������, � ���������� ������� ����� ������ �������� �������� � ���� - ���, �������� ��� � ��������� ��������� � ����� ���� � ��������� �� ��� - ���. � ������ ���� ������� ���� �����, �� �� ����� �����, ������ � ��� ����������� '������' � ���� ��������. ����� ����� ����� ���� � ���� ������-�����, ��� �� ���������. ���� �� ���� �������� �� ������ �������, �� ���� ������ ��������� � �������� ������ � ��������. �� ����� ������ ���, ��� �� ��� ���������, �� ������� ��������\n�������� ����� � ��� '�������' � ��������� � ����������� � ���������, � ������ - �� ���������������, ����� ���� �� ����. ����� ������ ����� ���� �� �������� ������� � ������ ��������"+sTemp+". ������� ����?";
			link.l1 = "�������� ���. ����������� �� ��������.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
			if (!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) GiveNationLicence(HOLLAND, 40);
            dialog.text = "����� ����� �����. � �� ����� �������, �� ��������� ������ � ������� ���� �����.";
			link.l1 = "�������, ����! ������ � ���� ����������.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_3", "1");
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "� ���������, ������ ������, ��-��! ����������� � �������� ����������? ����� ��� ��� ���� ���������. �������� ������!";
			link.l1 = "��, ��� ������ ������ ��� �������� �� ������ �� ���������.";
			link.l1.go = "mtraxx_28";
		break;
		
		case "mtraxx_28":
            dialog.text = "�� ������ ���� - ����� �������. ��� �����������. � ������� ���� ��� �������� ��� ��� ��������� - ��� ����� �������. ��������� ��� ����, ����� ���������� ������, �� ������� �����: ������ ������ ��� ������� � ��� �����. ����� ������ ����������, ����� ����, � ����� �� ���������, � ����������.";
			link.l1 = "���... �����... �������. ���� ��� ������ ��� ����, ������? � ���, ����� ������ �� ������ � �� �������?..";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "����� ���� �������, ������? � ���� ������: ����� �����������, ����� ������, � ���� � ��� �������, � ���� ������� � ���� ������������ �� ����������... ���� ��� ���� ���������� ����� �����, � ���� ����������� �� ����-������ � �������� ������, ����� � ���������. ��� ��� �������. �� ������ �������� �������� ��� �������� ������ ��� ���������� ���� - ������ �����, ��� ������, ������ �� ������: ���� ������ � ����� ��������\n������� �� ����� - ����� ������ �� ������ ������ ��� �� �����. � ������ ���, �� ������ �������� - � ��������� �������� ��� �������. ���, ������, � �� ������� �� ��� ����� �����, � �� � ����������.";
			link.l1 = "������, ������. �� �������!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "�� ����! �������� ������ �� ��� ����! ���� ��� ����������, ��������, � ��, �����������, ���!";
			link.l1 = "��� ������, ������...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "����� ��� �� �� ��� ����� �� ��������� �� ��������� ���������? � ���� ��� �� ������ �������. ��� ��� ������, �������: ��� ���� ������ ������� ������ ���. ��� ������ ���� � ������ �������, �� - �����!";
			link.l1 = "��!.. ��� ����...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35) // �������
			{
				dialog.text = "���� ���� ����, "+pchar.name+", ��� �� ������?! � �� ������ - ������� �� ��� ����� �����! ��� ���� ���� ���� �� ���� � �������, � ����� �� ���������� � �������� - �� ��������, ���� �� ����� ������ �� �� ��������. ��� � ���� ������������ �� ���� � ����������, ���� �� ���� ���������� ������ �������� �� ������? � ���� �� �����, �� ���������� ������ ���� �����! ���, ��������, ��� ��� ���� ������ ���.";
				link.l1 = "�� � ����...";
				link.l1.go = "mtraxx_33";
				break;
			}
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // ���� ������
			{
				dialog.text = ""+pchar.name+", � �� ������ - ������� ����� �����. �����, ����� ����, � ���� ��� �� ���� ������� ������.";
				link.l1 = "������...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "������� ������ ������� ���, ��� �� ��� '�����' �� ������ ������. � ������������ ���� ������: �� ������� �������� - ���, � �� ���������� � ������� - ���. �� ������� ��� ���� �������. �� ��������������� �����, �� � ����, ��� ���������� ����� ��������� � ����� �� ��� ��������, ��� �� �� ����. �������� � ����� � ������ ������ ����.";
				link.l1 = "���...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "������� ������ ������� ���, ��� �� ��� '�����' �� ������ ������ - ������ �� ���� �����. ���� �� ��� ��� ���������� ����� ��� ����� - ��������, � �� � ������� � ��, ��� ��� � ������ ��������� �� ���� ����, �� ����� �����, ��� ��... ����� �������� ��������? � �� ������ ���� - �� ������ ���! ��� � ���� ������ � ���� �������, � ��� � ���� � ����� ������ ���� ���. �������. ����������!";
				link.l1 = "�� ���� ������ ��� �����, ����� ���� �� �������!.. ";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // ������� - �� ��������� ����� // ������ ������� 3
				dialog.text = "��, � ��� � ������ ������� ����� �����! ���� �� � ����� - ��� ���� ����� ��� � �� ����... �� ���, ������, ��������, ������ ��� ���� ���������� ���� � ������? ����� ����������� �� ���� �� ���� ���, �� ��� ��? ��-�� ��. ��� ��� � ����� ��� ���������� ���������, ����� ������: ������� ����� � ������� � ����� ��������� ������� � ������, � ����� ������ ������� � ���� ���� ����� ���� �� ��������� ������� ����� �� ���������� �����������. �����. �������� � ����. �����?";
				link.l1 = "�������!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "� ��� � ��� ������ ������� ����� �����, ��-��! ������� ������ ��� ������� � ����. �������� ����� �������. ���, ��� �� ���� ������� ������ �������.";
			link.l1 = "�������� ������ ��� ���� ������ ��������...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // ������ ������� 3
            dialog.text = "�� ������� ��� ����� �� ������ ��������� ��������� � ���������� ���� � ������? ��-�� ��. ������� ������ ���� �������� �� ������, ��������� ����� ��� ������. �������, �� ������ ��� �� �������. �����. �������� � ����. �����?";
			link.l1 = "�������!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "�������. � ������ �� ������ ���� �������� ��� ����� - �� � ������� �����������. �� ���� ������� ������ - ��� ��� ���������� ������������� ����������� ������� ���� ������... � ��� � ��!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// ����������� ������
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "cartridge", 40);
			LAi_SetCharacterUseBullet(sld, "cartridge");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "� ����� � ���� ������ ��� ������� - ���� ������, ����� ��������� � �� ���� ��� ��� ��������. �� ��� ����� ������ � ����� ���������, � ������� ��� ���� - ��� ��� ������. ����� � ���� �� ���� ���������� ����� ���������� - ����������� ���� � ������ ����� ������. ��������� ������ ������ ������ �������� - � ������ ����. ���� �������� ������ ����� ������, ������ ������ ����\n���������, ���� ���� ������� �������� �� ��������� ��������� �� ����� ���� �� �����, ��������� ��������� ���, ������ ����������. ��� ������� � ����-������ ����?.. ����, ��� ���. �������. �������� � ����������� ����� �������� � ����� �� ����. �����, �������! ��-��!..";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "C ������������, ������ ���������! ����� � ����� � ����������� ����� ������ �� ��������� ������� �������� ��������� ������ ����.";
			link.l1 = "�� ���� �������, ��� ������ ��� �����. ����� ��������� � ������������ ����� ����...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "����� ���� ���������� �� ���������, �������. �����. ����� ����������� � �����?";
			link.l1 = "��.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "����� ������. ����� ���������� �� ������� �������?";
			link.l1 = "������.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "����� ��� �������. ��� ��������, ��� ��� �������.";
			link.l1 = "��� ��� ��� ���� ����, ������?";
			link.l1.go = "mtraxx_44";
		break;
		
		case "mtraxx_44":
            dialog.text = "���� ������. �����. ���������� ���� ������, ���, �� ������������, �� ������� ��� ������ �������. ���������?";
			link.l1 = "��� �������, ����. ����� �������?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "��� ������� ���� � ������� �� ���� ����� ����� '�����'. ��� ����� � ���� �������, � ��� ����� ������� � ���������. ������� � �������� '�����' ��� ������������� � �� ���� - ��� ���������, ������. ���� ��� �������, ������ ����� �� ��������� � ������� � �����������. ����� ��������� - �����, ��� ���� ��� ������� ������. �� � �� ������������� ����� ��������, �������.";
			link.l1 = "������������.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "��� � ������. ����������� ��������.";
			link.l1 = "�������!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "�, ��� � �� ������� ������... ��� ��� ����. ����� ������ ����� ���� �� ������������� '�����'.";
			link.l1 = "�������... � ���� � ���� ��������, ������.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "�� �������?! ��-��! ����������!..";
			link.l1 = "������� ������� ���� ������, ��� �� ����� � �������? ������� ������� ����������� ������� ������ � ���������� �������, � ����� ������ ������ ��� ���� ������� ���������� �������� �������.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "�����. �?";
			link.l1 = "� ���������� �� ��� ������� ������� �����. ��� ��� ����� ����������, ����� �� ������ ������. ��������� � ������� � ��������� ��������� �������� ����������� ������� � ������� ������������ �������, ��� ��������� ����� ������� � ����������.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "���-���... � ��� �� ��� �������?";
			link.l1 = "����������. ��-������, ������ ���� ����������, � ��-������, � ����� �������� ��� ������ � ����� ���������...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "����, ��� ��������.";
			link.l1 = "�����. ������� ���, � �� ��� ����� - ��������� ������ ����� �� ����� ��������, ������� �� �� ��������. ����� ���������� �� ����� � ���������� � �������... �� � ��������� �������� �� ���� ��������� � ������. � ��������� ������. ������ ��� ������ �� ��������� ��������� ��������� ������� �� ����� � ������� ��������.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "� ���� ���������, �������, ������� ������, � ������� ��������� �� �����.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "���. ��� �� ���� ���� �� �������� ��������, ��� ��� ������� ������� ���������� �� ����. ������ ��� ��� ��� �������: �� ��������� �������� ����� ����, ��� ��� ��� ������� ��������. ���� ��������� ��������� �� �������� ������� �������, �� �������� ��� �� �������.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "���. ��� �� ���� ���� �� �������� ��������, ��� ��� ������� ������� ���������� �� ����. ������ ��� ������� ���� �� ���. �� ���� �� �� ��� ��������...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "���! ������� ������� ������� �� ������! �� �� ������ ������� ������, �����! ����� �� ������, ������� ��������� ���������� � ������� �� ���� ������ � ������ �������.";
			link.l1 = "������ �������... � ��� � ���� ������� ������� ���� ���-�� �������. �� ���������, � ��� �.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "���! �����������, ��� �������� ���������, ����� ������, ��� �������� ����! �������!";
			link.l1 = "����� ������ �� ������. � ��� � ���� ������� ������� ���� ���-�� �������. �� ���������, � ��� �.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "� ������� ���� ��������. ���� �������� �������� �� ���� ������� �����. ��������� �� ���, ��� �� ��� ���-�� �����... ������� �� ���������� ��� '��������' � ���� �����. ��� �� ����� � ����?";
			link.l1 = "������ ��� ��������� '������'. �������� ���������, ������, �� �������� ������ ��������.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "��� �����, ����� ��������� �����... ������. � �����. � ��� ����, �����, � ���� ���� �������. �����?";
			link.l1 = RandSwear()+"�������, ����!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "����� �������� �������. ��� ������ ������� ��� � ��� ������� ����� �� ����� �������� ��������, �� �������� ����� �����. ������ ���� ���� ��� ����� � ������ ������. �������� ���� ������ ���������, �� � ��� ������ �� �����, ���������� ������ ��������� � ������� �� ���������, ��... � �����, �����-��������. �������� ��� �� ���������: ����� �����, ��� ������� �� ��� �����, �����, ��� ������ ������, ������ �� ������. ������������, ��� ���� ��������-��������, ������������ � ������� ����������� ������ ������, ����� ����� ����� ������ �����\n� ������� �� ����������� �������, �������� ��������� �� �������� ������� �������: �� �������� ������������ �� ������, ���� � ������� �� ������� � ������� � ��������. � �� �� ����� ����������� �� ������� � ����� � ��� �� ������. �������� �� �����, ����� �� ����� ������� ������� '�����'. ������� ������ ����� ������, � �� ������, � �� �������� - �������� �������� � ���� ��� ���������. �����, ��� ����������� ����� ����� ��������� ������� ���������, � ����� ��������� � ������ � ������, ��� ������\n��, ��� ��������, ������� ������������, � ��� �����������. ������� ������ ������ ������� � ���� ��������� ����������� ���������� � ������� ��������� - ����� ����� �������� ����� ����������, ������ ��� ��� �� ���� ����. ������ � ����� �� ���������� � �������� ������� � ����� �� ������������ ������, ������ ������������ �������� �� �� ������, ��� �� ������� �� ������ - ������ �� �����, ���� �� ����� ����� � ����, ����� ����� ��������� �� �������� � �����-�������. ����� �������, ����� � ����� �����, � ��� ��� ����\n��������� ������ �����, ��� ���� ����������� ��������� �������� ������ � ����������� �������, �� ��� ��������� �� �� ����, ������ �� ������� ������, ����� � ������� ����������� ����� ������ '�����'. ���������� ����� ������� �����, ������, � ����, � ������� ������� - ������� �������� ��� � � ������. ����������, � � ���� � �� ���������� - ���� �� ����� ����� ��� ��������� ����� ����������. ���� ������� ������ ������ ������������� � ������ �������� �������� ������� ������ �������\n�������� ��� �������� �� ���� � ��� ������ �������� � ���������������, ������ �� ������ ��� ����� ������. � ��� ������ �� �������� � ���� ������ ����: ����� ���������� ���� ��������� ��������� - ��� ���, � �� �� ���� �� ������� - ��� ���. ������, �� ������ �� � �����-�� �����, ��������� ������ ��� � ��� �������. ���, � ��������� �� ��������, �� � ��� ���� ������. � ������� ���, ������ ������� ������ �������� � ��� �� ����������\n��������� �� � ��� ���� ����� �� ���, �� ���� ���� ������ � ���������� ��������, ��� ������ �������� ���� ���������, ������������ �� ��� ���� ������ �� �������. ��� ��� ���� ��������� � �������, ����� ������� � �������, ��� ������ �������, �� � ������ ������ ���� ���������� ��� ����� ����������.";
			link.l1 = "��... �������������, ������ ������ ����� � ������ �������. ��� ������?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "���. �����. ����� �����!";
			link.l1 = "�������, ��� ��� �����������...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//������� �����
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "�, ��� ������ ������� ���������. ��� ��� � ����������� ������ ������?";
			link.l1 = "������� ��� ����. ����� ���� ������ � ���� ����.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "������.";
			link.l1 = "� ������� ������� ��������� ����� ����������� ���������� ��� ����� '����'. ���� ��������, ��� ��� ��������. �����, ��������, ��� ������������� ����������� ������.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "��... ����, ��������... � ���� ������� ����� ����� �����. ��� ���: ����� �� ��� ����� ������ - � ����������� � ������� ������ �������, ��� ������ �� �������� �����������. �������, ��� � ���������.";
			link.l1 = "������, ������. ����� ������.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "������� � ���� ������. ���� ������� ����� ���������. ���� - ��� ����������� ������� ���������� ����.";
			link.l1 = "���������� ����? ��� ���?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "��� ����� ���������� ����� � ��������. ��� � - ��������� ���, � �� ���� - ��� ����. ������, ����� ����� ��������� �������� ����� �������, ��-��! �� ���, ������� ���� ���?";
			link.l1 = "���� �� ����, ���� ����������� ������. ������, ���� - ��� �������... �������, ������!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "��? �� ����� ������������� ���������� ����, ��� ���� ���������� �������.";
			link.l1 = "��. ���� ������ ������ ������. ���� � �������� �������� �������� ��� �����.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "� ������� ��� ������ ���������?";
			link.l1 = "������� ��������� ����� ���� � ��������� ��������.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "��-��! �� ������� ��������, �����. ��� ��� ������ ���� ����?";
			if (sti(pchar.money) >= 250000 && GetCharacterItem(pchar, "gold_dublon") >= 300)
			{
				link.l1 = "���, �����: ������ ��������� ����� � ������ �������, ��� �� �������.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "��� ������ � ������� � ���� � ������� �� �������. ������ �������!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "������?";
			if (sti(pchar.money) >= 250000 && GetCharacterItem(pchar, "gold_dublon") >= 300)
			{
				link.l1 = "���, �����: ������ ��������� ����� � ������ �������, ��� �� �������.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "��-��, ��� ����!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveItems(pchar, "gold_dublon", 300);
			Log_Info("�� ������ 300 ��������");
			PlaySound("interface\important_item.wav");
            dialog.text = "����� ������. �� ������ �������. ������!";
			link.l1 = "������, �� ������� ���-������ �� ������ ������� �����?";
			link.l1.go = "mtraxx_70";
		break;
		
		case "mtraxx_70":
            dialog.text = "��. �� ��� ����� ������������� ��� ������������...";
			link.l1 = "����-����?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "���� � ���� ����������, ��� ����� ������ ��� � ���... � �� ��� ��������. ����������� ������ �� ���������. ������� ������ � ���-�����, � ��� ����� ������� ����� � ������� �� �������. ��� �������, ��� ��� ��� ��� ���������. � ������� � ����������� �� ���������, ����������� ���. ������� - �������� �� ���: ���� ������, � ��� ����������. � ����� ������������: �� ������� ������� �� ���� ������ ��� ��� ������� - ��������� ��� ���� ����, ������� � ������������\n������ ���������� �� ���, � ����� - ����� ����, � �� ����. ��� �����? ������� ����������������. � �������, ��� � ���� ���� �������, �� ���� ���� - ��������. � ������ ������. ���� ������ ���� ������ �������. �����.";
			link.l1 = "��� � ����, ����.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // �������
			{
				dialog.text = "���� ���� ����, �����, ������� ������ ���� ���������? � ���� ����� ���� � ������������ � ����� ����������, � �����, ����� ������ ����������! �� ������ ����� ���������������� �� ����! �����, ��������� �� ������� ������, � ���� ������. � ���� ����� ���� �����������������: ������� �� ��� ����� �����, � ���������� �� ������� ���������, �� ������ �� ����� - � ��� ����� ����� �������. � ������� ���� ����� ����� � �����!\n��� ���� ������� ������� ��, ��� ���������, ����� �������, ����� �����, ��� ��������. ���, ���� ��������, ��� ����� ����� �����, � �� ������� �������� ���� �� ����!";
				link.l1 = "����, ������. ��� �� �����, �� ������ �� �������!";
				link.l1.go = "mtraxx_73x";
				break;
			}
			dialog.text = "������� ������! ����������, ��� ������� ���������?";
			link.l1 = "�������� � � �� ������� ������ ���������. ��� ������ ��� � ������� �������, ����� ���� - ������ � ������. ��� ����� ������� � ���� ���������, ����� ��� �����, ���� ���, ������ � ��� ����� ������ ������ � ������� �� ������� - ���� ���������. ����� ����� ������ � ����� �������� ������: ���� �����, ���������, � ���������� ������ � ������, ������ ������, � ���������� ������� � ������� ������. ��� ���� ����� � ����, ������� ����� � ���� � �������� ������, ��� � ����� ��������� �� ���-�����.";
			link.l1.go = "mtraxx_74";
		break;
		
		case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 28, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 30, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 31, false);
		break;
		
		case "mtraxx_74":
            dialog.text = "��� �������. ������ ��� ������ �� ���� �����. ��� ����, ������� �� �����, ���� �� �� ���������, �� �� ��������: �������� � � ����, � � �������. ����� �� ������, ��� ��� ����� � �������, �� ����� ����������. � ������ ������ ������� - �� ������� ������� '����������', � ������� �������� ������, �� ��������� �������� '�����������'. �� � ��� ���� ������� ����� ���� ����, ��� ���������� � �������� � ������� ���� �� ������, ��� ��� � �� ������ ������� �������� - �� ���������. ������� �� � ��������� ������ � ������� ���������� ����.";
			link.l1 = "�� ����� ��� ��� ���� ����?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "����� ���������. �� �� � �����: ��� ������ ��������� ����� �������� ���. �� ������� ���������� �������� ��� ����� ����� �� �����. ������� ���������� �� ���� ������ - �����, ��� ��� ����� ��� ���� �����������, � ��� ������ ���������� - ��� ������. �� ����, ��� ��������� � �� - ��� ����, ��� � �������� � ��� ������ ����������, ������, ������ �� ������, ��� �� ��� ���������.";
			link.l1 = "��������� � ����� - ������ ���������...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "������! �� �� ��������� ��� ������ �� �����. �� ���� ��������� � ��������, ��� ����� �����. �� �������� ��� ��� �� ������� - ������ �� ��� ����������. � ����� ������, � ���� �� ����� ��������, � ������� ����������, ���� �� ����������. ����� �������? ���� ���� ������ ����.";
			link.l1 = "�� �������!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "������� �����, �������, ����� � ��� ���� ���������� ���������, ������ ����, ��� ������������ ���� ������� ����������� ����, ��� ��������� ������� �� �������� ����� ��������, ��� �� ��� ����� ������ �� ���� �� ����� �����. ��� ������� ������ ������� ����� ����� ����� ����� ����� ���������. ���� ������� ������ �������� ����� ���������� � ������ �� �����, � �� ����� ��� ��� ������� ������ � �������. ������ ��������� � ���� ������������ � ������, ������ � ��� ����� ���������\n������� ������ � ���� �� ������-������, �� ��� ����� ��������� - ���� ������. ��������... ��� ����� ��������, ��� ��������� ������� ���������� �������� � �����-�������, ����� ����� ������� ������-���� � - � �����. ��� �� ����� � ��������\n������ ��������� ��������� ����� �������� �� ������ � ���, �� � � ������, ������� �������, � ���� � ����� ����� �����, ��� ����-������, �� ������ � �����-�������, ��� ����� ��������������� � �������� ������� ���� ������� � �������� �� ����, ��������� ���, ��� ����� ���� � ��������\n��������� ���� - ������, ������� � �����, ����� � �������� � ����-��������, ����� ����� ���� ����� �� �������� ��� �� �����, � ������-����, ��� � �� �����, � ������ � ����-������. ����� ������ �������� ������� ���������� ��������� ������� � �������� ���������� �� ����-�������. ��� ��� � ���������� � ������� ���� �����, � ��� ������ ��� �����, ��� �����������, �������� � ���������� ���� ���� �� ������, � ������ �������� �����-�� ������� ������� ���������...";
			link.l1 = "�������, � ��� ����, ��� ��� ���������...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "���� ������, ��� �� ����� �����, �� ��� �� ������ ������. � �������� � ���� ����. ��� ������ ��� ��������� ���� �������� ������ �� ������� �����-�������, � ����� ��������� ������ ����������, ���, ���, ������� ������� �������� ��������� ������� �� ������ � ������� ������-����. �����������, ���� ������� ������ ��� �� ������, ���� ������ � ������� ������������ ������ ����������� ����������... ����� ����� ����� ����� ��� �����. ������: ����� � ��������� ������ '������'. ��� ������ � ��� ��������� - �����, ����.";
			link.l1 = "��� ��!";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "������: ��������, ����� ��������� ������ ��������� ������� ������, ��� ��� ������� ���������. ��� �� ��������� ������� ���� �� ������� ������� �����, ���� �� ���� ������. ���������� ���������� �� ��������� ���.";
			link.l1 = "�� �����? ����� �������?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "�� �������. ����� ������... ��� �����, �������� ������. �� ��������� � ����� � �� ����, � �������� ���� ���� � ���������. �������� �������, ��������� ��������� � ��� ����� � ���������. ����� ��������� ����� ����� ����� � ����. ������ ����� ������ ���� ������ ���.";
			link.l1 = "���! ��, ����!..";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "������ ������: ����������� �� '������' � ����-��������. �����������: �� ����� �������! ����� ���� ��������� ����� ���������� ��������. � ����-�������� �� ������ ������ ������� ���� �������, ����� ��� ��� � ������-����. ������� �������� �� ���� ������ ������ �� ����� �����, ���� �� ���� �����.";
			link.l1 = "���� - �� ������ ��������� �������, ������� � ����� ����� � ���� ��������� ���������! ��-��!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "������! ��� � ������ ���� ���������, � ��� � ������� ��������. ������ ��� ��. � ���������, ��������� ������: ����� �������� ������� ����� ����������� �� �������� ������� ��������, � �� ������ ��! ������� � ���� ����� � �����.";
			link.l1 = "�� ����� �������? ������ �������� ������� � ��� ���� ��������, ������ ��������� �� ����? �� ���� �������� � �����!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "���� �������������? �����, ��� ��, �� ��� ������� ������� ���������? � ���� ������ �������. ������� - �� ������ �������, �� ��� �� ������ � ������������� �����. �����?";
			link.l1 = "�����, ����.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "�������� ���� ����� ���� ������, �� � ������ ����� �������� ����. �������, ������ ������� ���� ��������. ����, ��� ����, ��� ���������?";
			link.l1 = "� �� �����, ������� � ������� ����. ��� ������������� '������' - ������?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "���� �� ��� � ����� �����������, �� ��� ����� �� ���� ������� � ����������� � ����. ������ ������ ���� ���-�� ����� ������� ��� ������ �� ������. ��� ��� �� ����� �� ������ - ������� ����� � ��� �� ���� ���� � ����-�������� - ���� ��� �� ������� � �������, �� �� ������� ������! ���� ���� ��������� ������, ��� �� ����� �� '������' - ��� ���������, ������ ��� ������ ����.";
			link.l1 = "��� ����. ������ � ����!";
			link.l1.go = "mtraxx_86";
		break;
		
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // ����� �� �������� ������, ������� ��� ���������� ��� �������
		break;
		
		case "mtraxx_87":
            dialog.text = "�� ���, �����, ������� ��� ����, ���? �?";
			link.l1 = "��, �������. ��� ��������� �������, ��� � ���� �����������. ������ �������� ����, ������ ��������� �� �����.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88":
            dialog.text = "�����, �� ����. ������. �� �������� ������, �� ������� ��������� �� �����. ����, �������, ���������� ������, �� �� ��� ��� �������, �� ����� - ��� � ������ �����, ��-��! � ���� ����� ���� �����������������: ������� �� ��� ����� ��� ������, � ���������� �� ������� ���������, �� ������ �� ����� - � ��� ����� ����� �������. � ������� ���� ����� ����� � �����!\n��� ���� ������� ������� ��, ��� ���������, ����� �������, ����� �����, ��� ��������. ���, ���� ��������, ��� � ��������� ����, � �� ������� ��������!";
			link.l1 = "���� ��� ����, ����!..";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 18, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 20, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 22, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "��-��, ����������� ������� �������! �� ������ ���� ������� �����, ��? ��-��-��! ��������� �� ���-���� ��������� �������...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // ��� �������
			{
				link.l1 = "��� �����, ����, ���������, ���� ���� ��� ��������.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "��, ��� ������ ��������� ������� ������ ������� ������ �� ���� ������.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "������� ������ �� ������, �����?";
			if (iTotalTemp < 1) link.l1 = "���... ������ �� �� ������, ����.";
			else link.l1 = "���... "+iTotalTemp+" � ������� �����...";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "��� ��������! ������� ��������� ���� �� ����, ���� �� ��� �� ��������. �����, ��� ���� ��� ��������, ���, �������, � ���� ���������, � ��� ���� ���������.";
				link.l1 = "���� ������, �������... ��� ������, ������? � �� ����?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "������ �����-��. ���� ����� �� ������ ���� ����� ���� ��� ������� � �� ����. ��������, ������� ��������� ����� ���� ���� �� ����, ���� �� ��� �� ��������. �����, ��� ���� ��� ��������, ���, �������, � ���� ���������, � ��� ���� ���������.";
				link.l1 = "���� ������, �������... �� ������� ���� ���.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "���������, �������. ���� ��������� ������� �� ����������. ��������, ������� ��������� ����� ����� �� ����, ���� �� ��� �� ��������. �����, ��� ���� ��� ��������, ���, �������, � ���� ���������, � ��� ���� ���������.";
				link.l1 = "���� ������, �������... �� ������� ���� ���.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "�������, ���� � ������ ��������. ��������, ������� ���-���� ������ ��������� ������� ������ �� ����, ���� �� ��� �� ��������. �����, ��� ���� ��� ��������, ���, �������, � ���� ���������, � ��� ���� ���������.";
				link.l1 = "����� ������!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "�������. �� ����������� ���������, ��������. � ���� ��������� ���� ��������, ��-��!";
			link.l1 = "���! � ��� ���� ������! ����� ������!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... ��� ��� �������� � ��������� �������� - �������. � ������ '������' - ���� ������.";
			link.l1 = "��� ������, ������? � �� ����?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4":
            dialog.text = "� ��� ����� � �� ����, � ��� ���� ��� � ���� ����� ��� ������. ���������� �� ������� ���������, �� ������ �� ����� - � ��� ����� ����� �������. � ������� ���� ����� ����� � �����. ��� ���� ������� ������� ��, ��� ���������, ����� �������, ����� �����, ��� ��������. ��������. ��� ���� ��������� ���������� � ����������� ������. ��� ����������� ������� �����.";
			link.l1 = "������, ����! ���� ����� ��� ������ � �� ����.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "� ������ �����, ���������! ��-��!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//������� �����
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "���-�� ��� ������ �������?";
			link.l1 = "���, �������. ��� ����������� �� ���� �����.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "���! � ��� �� � ���� �������, �����? �� �� ��, �����? ���� �� �������?";
			link.l1 = "����, ������, �������, �� �� ���� ����� ��� ������� �� ����� ���������� ��������. ��� �� � ������������ � ��������...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "�����. ��� ���� ������... ���� ������ � ���� ������� - ��� ���� ��������� ���� ��������, � ��� ���� ���������.";
			link.l1 = "���� ������, �������... ��� ������, ������? � �� ����?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "�����, �� ���, ���� ���� ��������? � �� ������ - ������� ������ �� ����� �������, � ��� ������� ����� �������� �� ���� �����. ���� ��� ���������� �� ��������, � ����� �� ���! �����!";
				link.l1 = "��...";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // ��������
			{
				dialog.text = "�����, �� ���, � ������ ���� ������ �����? ����� �� ��� ����� �� �������� �������? � ����������� �� ����, � �� ���� ���������! ���� ���� ������ ������� �� ����������, ���� ������� �� ����� ����������� - �������, ��� - ���� ��������, ����� ������ �� �������.";
				link.l1 = "��...";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "�����, �� ���� ������. � �� ������� - ������� �� ������� ��������. ��� �� ������� ��� ������ �� ���� ��������? � ����������� �� ����, � �� ���� ���������! ���� ���� ������ ������� �� �������, �� ���� �������� ������, ���� ������� �� ����� ����������� - �������, ��� - ���� ��������, ����� ������ �� �������.";
				link.l1 = "��...";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "�����, �� �� ��� �� ����������� '���������� �����' ������. �������� - ��� �� ������ �� �������� �������. �� ���, ������ ����������� ������ ������� ������? � ��� � ������� ��� ���� ���� ������� ������� ������ - ��� '������� ������', ������ ����� ������ ������. ���� ���� ������ ������� �� �������, ������-������ �����, ���� ������� �� ����� ����������� - �������, ��� - ���� ��������, ����� ������ �� �������.";
				link.l1 = "��...";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "��� ������ ���� � ������ ������� � �������, ������! ����� � �������� ������?";
			link.l1 = "�������, ����. ��� ������.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "������, ���� �� ��������� ������, ��� ����� � �������� ���������, ������� �� ��������� � ������-����?";
			link.l1 = "� ���-�� ������ ����� � ���... �������, ���������. ����� ��� ���� ������ - ��������� ���������?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "�����. ������� - ������ ������� ����� '�����', ������ �����. ��� ������ ���� ��������� ������. ������� � ����� ������ ���������, �� ��� ���������� �������: ������� - �� �������, ��� ������ ����� �� ����, ����� - �� ���� ������. �������� ��� ���������, ��� ����� �������� ������ �� ���� ���� ������� �������� �� ��������� � ��� ������ � ���. ������� �������� ������ ��������� ����� ������, ��-��. � �����, ������� �������� ���� �������. � �����, ��� ��� ���� �������.";
			link.l1 = "���. ������. ��� ����� ��������� ��������� �� ������. ����� �����, ��� ��������� ����� �����������.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "��� �����. �����, ������ � ����.";
			link.l1 = "������ �����������.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "��� �������� �������� � ���� ����� ������� ������� �������� ������� �������, ������� ����������� � �������� � ������� ����� �� ��������� �������� ������ ������� ����. ��� �� ����������� � ������ � �������������� � ������� ����� ���������, ��� ��� ���� ���������� '�������� ��������' �� ������. ������ ������ �������� �� ��������� ��������, � ����� �������� � ����� ����. �� ���� �� ����� ���� - ���������� ���������.";
			link.l1 = "����! � �� ���������? �� ����� ����� ����� ��������� �������, � ������?";
			link.l1.go = "mtraxx_95";
		break;
		
		case "mtraxx_95":
            dialog.text = "�� ������ � ���� ��� � �������. ������ ��� �� � ����� ������. �������� ������� ���� �������� ��� ������� ������� '������� ������'. ��� �� ����� ���������� � ������ ���������. ������� ������ �������, ���-����� '�����' - ������ ����� ���� ������ � ��� � ������������ ���������, ����� �� ��� �������� - ������� ������. ����� ����� ������� ��������� �� ����� �������� ���������� � ������ �� ���������� ������� ����� - ������... �������, �� ��� ���� ���������� ���������\n��� ���� � �� ���������� ��������� �� ��������� ������ �������� ���������� �� ���� � � ����� ���������. ����� ���� ������� ������ ������� � ������, � ����� ������� ���������, ��� ��, ��� � ������� ��� ������� ����. ��� �����, � ����� ���������, �� ������, ���� � ����, ��� � ��� ��� � ������� - ��� ������ '������' ����� �� ����� ����-������. ��, ���� � ���������� ���� ���� ������ ���������� ������ - ��� ��� ��������, � ����� ������ �� �������\n������ ������ ����� �������� � ������� ������ ������ ������ �� ����������. � ���� �� ���� ���������� ��� �������� � ������� ����������. ���� ��� ����� ����������, ����� ������� ������������� �������� � ����� ��������� � ��������� �� ����-������ ����. �� ������� ��� ������ �� ����� � ������ ��������� ����� � ������� � �����������. ������� ������� ��� ��������, ��-��-��!\n� ������ ���� �������, �� ������� ����� ��� � ����� �������: �������� ��������� ��������, � �� ��� ������ ���������� ������ �� ����� ������ ����. � ������� ������� ��������� ��� �������� - � ��������� ����� ������ �� ��������� � �������. ���������� �� ������ ������� ����������, � ������ � ���� - � ����. �������� �� ����� ������� - ������ ������������ ����. � ���������� ������� ��� ���, ����� �� ������� � ��������� ��� ����� ������. ��� �������?";
			link.l1 = "��� �����, ����!..";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // ������ ���������� ����������
		break;
		
		case "mtraxx_97":
            dialog.text = "�����, ��� �� ��������, ������ ���� ����! ������! ��� ������? �� �������, �������. ������, �� ����� ��������!\n����, ������ �������! ��� ���� ������ ���������, ��-��! � �� ��� �������, ������� ������! �� ���, ��� ����� ������ ��������, ������ ������ ��������! ������� ������� �� ����� �������� ����� � ���� ���������� ���������. ������� ���� ����, �� ��������! ������ ��������� �� �����! �� ����� ������, �� ����� �����! ���� �� ���!\n�����, �����, �����, �����, ��������! ��� ��� ����� ������ ����� �� �������� ����� �������, � ��� ����� ���������� ���� �� �������, ��-��-��!.. �������, ������� �����! ����, �������!..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "����, �������, ������ ����� �������� ��������, ��� ��� ������. ��������! ���� ����� ����� � ����������� ����� ������� � ��������� �������. ��������� �������� ��������� �� ������ ������ �� ������ ���������� �����. ������ ���, ��������� ����� ������� ������� ������ � �� ������� ��������� �������. ����� �� �������� ������ �� �����, ������� �� � �����. ��� �������?";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = ""+pchar.name+" � ���! ��� �� ������, � ������� ��������� ���-�� ������ ������� ��������� ������� �� ���� �����. ������������� � ���������� ��. ��� ���� ������� ���� ���������� ��� �������� ����� - �� ������� ���, ����� ��� ������� ��������� ��� ���������� ������, � ������� ���� ������ ������. � ����� �� ������, �������� �������� �� ������ ��������. ����? �����, ���� ��� �������� �������� - ���� � ���� ���������� ����������������. ��� � ���� �����, �� �����, �� ���� �� ����\n�, ����� � ������ ������� � ����� � ����. ��� ������������ ��������� ������� - ���������� ������������� �����. ���, � ����� ��������, ������ ���� � �����, ������ �� ��� �� '������� ������.' � ���: ����������� ���� ���� �������� �������� - ������� �������� � ��������� ���������. ������ ������. ���� ��� �������? ����, ��� ��. ����� ������, �������, ��-��-��!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "���, � ��������� �������� ���������. ������ � ���� �������� '������� ������' - ���� ���������� ���� ��������� � ����� ��������� ��������. ����� ���� �� ����?";
			link.l1 = "�������!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "'������� ������' ����� ������� ������� � ������ �����������, � ����� �� ���������, ������� �� ����� �� ����, ����������� � ����� ��������� � �� ������� � ���� ��� ��������. ������!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"������ ���� �������! ���, ������ �������, ��������� ����. ������ ������ ��������������, ��-��-��! �����, ��������! ����� ������ �� ���� � ���� - ����� ������ ��� ��� �������� ��������� � �������, ������� ���. �����, ���� ������ � ����������� �� ���������� � ����������� - �� ��� ������, � ����. ���������� ����� � ������ ��������� ����� ����\n�������� ������ ������� �������� - ������ ������� �� ������ ��� �� �����, ��������� ��������� ��������� � �����. ������ ����� � ������ ������ ���������������. ����� ������������ - �� ������, ��� ������, ����� �� �����.";
			link.l1 = "���! � �������������, ����!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// ��������� ����� � ������, ����������, �����
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "��� ������, �����?";
			link.l1 = "��� �������. � �������� ������������� ������� ��������� �� ������ ��������� ����� ����.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "��-��, ��� ��� �������! �� ��� �� ������?";
				link.l1 = RandSwear()+"������ �������!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "��-��, ��� ��� �������! �������� ���� ����� ���� �������� ����, �������� ���� ������ ������ - ��� ��� ����� ������ �� �������� � �������������, � ��� ����� ����� ��� - ������ � ����� �����.";
				link.l1 = "�����!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "��? �������� ����������, ���� ������!";
				link.l1 = "��� ����!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "�������! �������� ���� ����� ���� �������� ����, �������� ���� ������ ������ - ��� ��� ����� ������ �� �������� � �������������, � ��� ����� ����� ����� ��� - ������ � ����� �����.";
				link.l1 = "�����!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -325000);
            dialog.text = "����, ��������, ��������� ������, ��� � ����� �������? ������ ������� - 5000 ������� ���, � �������� � ����� ����� ��������. ����� ��� ����������, � ��� ����������� �����, �������� � �����, �������, ��� ���� � ������� ���� ��� �������.";
			link.l1 = "� ������ ��� ����?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "��������� �������� �������� � ����������� ����, � ����� ��������� '������� ������' �������� �������� ������ ������ - ���������� �����, �� ��� � ������� '�������� �������' �������� �������� ������. ��������� ������� ����� ���������� ��������� ������� ��������, �������� ���������� �� �������. �� ����� "+GetCrewQuantity(pchar)+" ������� ���������� "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" ��� ������ � "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" ����.";
			link.l1 = "��, ��� ��� �������� - ���� �� � ���� ���������? �������!..";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "���������. ����������, �������, � �������� �������! ������ ��� ����� ������ ������ - ���� ��������� ��������. ��� ����, � ��� ����� � ����, ����� �� ����� �� ���. �����, ������ ��� ���� ����� �������: �������, ������� ������� �� �������, ������������, ��� ������ ������ ����� ����� ������ �� ������ �� ��������� ����� ���������. ������ ����������� �� �������, ��� � ������� � ������ � ��� ���� ������. �� ��� ��������. ������� ���� � �� �������. � ����� ��� ������ �� ������� �� ��� �� ��������, ��-��-��!";
			link.l1 = "�����, ����. ��� ����� �������� ���������, ������� � �����-���� �������. ����� �������!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "����������, �����������! ��� �� ���� ����� �������� � �������� �����! �������� � �� ����!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason ��������� ������� ���� 17/1
		case "mtraxx_113":
            dialog.text = "���?!! ��� ��������� ���� ������������ ����������, ��� ���� �������� - ����� � ����� - ������� ���������, �������� �� ������ ���������� ���� ��� ������ ����� ����������, ������ ��� � �� ����� ���� ����?!";
			link.l1 = "������, � ������ �������. � ������ ��������� �� ����� ����������, �� ���� � ���� ������� ������� ������ ������� ���� � ��������, �� �� ���� ���. � �����.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "��, ��� � �����, �����, ��� � �������� ���� ������ ����������? ��? �����, ��� ������� ��� ������ ���, ��� ����? ������� � �������� ��� ������ ��� �������� ���������? ��-��-��! ���� ������, �����, � �� ��������� ���������� ����. �����, ����� ����� �� ��������� � ����������� ������ �������� � ��������� ��������� �� ��� �����, �� � ���� �� ������! ��-��! � ������ �������� � ���� ����!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason ���
		case "patria":
			dialog.text = "��-��, ����� �� �� ������! ����������!";
			link.l1 = "���� ���� �����, ������� �� ������ �������. ������� �� �� ������������. ���� ��� ������� ���-������. �� �� �������.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "���! ����� ������� �����! ����� ���-�� ������! ��, ����� ���������, ��� �� �����, ��� ����� �����?";
			link.l1 = "����� �� ������, ��������� ������������ �������� ����� ����� �����. ����� ������������ ��� ����������� �������� ��������, � � � ��� ������� ���� ����� �� �����. �� �������� ������� ������, ��� ��������� ��� ������ ������ ��-�� ����������, ��������, �������� � �������� �������, ����� �������� ���������, �� �� � ���� �� �����. ���� ������� ��� �����, � ���� �������������� ��� �� ����� ����������� �����.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "��-��, ����� �� �� ������! ����������!";
			link.l1 = "���� ���� �����, ������� �� ������ �������. ������� �� �� ������������. ���� ��� ������� ���-������. �� �� �������.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "���! ���� ��� �� ����� �������� �� �������? �����, ���� ������ ���������, ��� ��� �����. ����� ���������, ��� �� �����, ��� ����� �����?";
			link.l1 = "����� �� ������, ��������� ������������ �������� ����� ����� �����. ����� ������������ ��� ����������� �������� ��������, � � � ��� ������� ���� ����� �� �����. �� �������� ������� ������, ��� ��������� ��� ������ ������ ��-�� ����������, ��������, �������� � �������� �������, ����� �������� ���������, �� �� � ���� �� �����. ���� ������� ��� �����, � ���� �������������� ��� �� ����� ����������� �����.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "���-���... ������ �����!.. ������� �� ��� �������?";
			link.l1 = "���� �����: ��� ����� ������������ � ����������� �� ����-�-������. ��� �����. ���� ����������� ��� � ����-���������� � ����� ������ � ����. ������� ����� �� �� ������ � ����� �� ������, ���-���� ����, ��������... �������?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "��� �� ��� ������, ��� ������. �� ����������. ��� �� �������?";
			link.l1 = "���� ��� ��������� '������'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "���� ����� '�������� �������' �� ���������. ����� �����������. ���� �������, ������ ���� ������.";
			link.l1 = "�������. ������ ������ � �������� ��������������. ������ ��������� � ���� � ������, ��� ���������� � ���������, �� ������ �� ����, � �� ��� �������� � �����. ����� ������ � �����, ������� � �������� �������� � ����� �������. � ���� ���� ��������� ��������� ���� - ����� �����, ������� ����� ������ ���� ������� ����������� ������. ����� ��� ��� ��� ��� ������������, ��� ������ ������� ������ ���������, ������ �� � ������... ����� �������... �� ���� �������.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "��-��-��! ������ �������� ���� � ���� ����� �� ����! �� ��� ��, ����� ����� �������. �� ����������, ����� �� ��������� ���� ����� � ����� �������. ��� ��� � ����� �� ������ � �������� ����������� �������...";
			link.l1 = "��, ��� ����. ����� ��������� �������� ��� ������ �� ��� ������ � �������� � ������. ����� ������ ��������� �� ����� ������ ����� ����� �� �����.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "������. ��� ������?";
			link.l1 = "� ����� �� ��������� ������ �� �����. �� ������ ��������� �����, � �� ��� ������ ������. ���� �������, ��� �� ������� � ��������� �������� ��� ������� �� ���.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "��-��-��! ��� ��� �����! ���� ��������� - ����, � ������... ��-��-��!.. ������, ������! ��������, ����� �������� ������?";
			link.l1 = "�����. �� ���� ��� ���������.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "��-��-��! ��� ��� �����! ������� �� � ���� ��������� �� ��� �������, �? �����, ��� ����� �� ����� - � ��� ������. ������ ������.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "�����.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "������, � �������.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "�������! ��������, ����� �������� ������?";
			link.l1 = "�����. �� ���� ��� ���������.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "�� ������, �� �������. ����� ������� ����. ��� ������� ����, ��� ��������� ������, ��� �� ���.";
			link.l1 = "������. �������, ������.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "�������, ��������, ��� ��������������. �������� ������� � ���� �������, ���������� �������� ����������� ���������. �������� �������, ����� � �����. ������� � ������ � ����������� ���������. ��� � ������ ���������.";
			link.l1 = "��-��! ������ �� ����������������. �� ��� ����� �����.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "�� ������, ��� �����. ������ �� ��� �������� ����� ���������. �����.";
			link.l1 = "��� ��� ��������? ������� ������ ������� ��� ������?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "� ����� - �������!";
			link.l1 = "������� ��� ������, � ����� �����. ����� ������ ����������� �� ������. ���� �� ����� ���� ��� ����� ������.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "������������. � ������ �������� ����� ������. ������ �� ������ �����: ����, ����� ��� ������� ���������. ����� �� ��� ������� - ����������.";
			link.l1 = "��� ����. �� �������, ������!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //����� ������
			dialog.text = "��, ����������! � ��, ������!";
			link.l1 = "����.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "��� ���� �����, ������� �����������, �� �����. ��?";
			link.l1 = "��.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "�������. � ������ ���� ������, ����� ������ ������ ������ ����� ���! � �� ������� �������, �� � ��� ��� ��������!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "�����.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "��� ����! �� ������� �����...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "��-��-��! � �� �������, ���������. ������� ���� ��������������������. � ������� ������, ����� ������� �������: �� ������ ������ ����� � ������ ������� �� ��, ��� ������� � ���������� � ��������. � ���� ������� ����� ��� �������, �������� � ���������. ��-��-��! ��������� ��� �� ��������� ��� �������, �� ��� ������ ������! ��-��-��!";
			link.l1 = "�����, ����� � ���� ������.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "� �� ������� ������������ ���, �������. �� ������, ��� �. � ���� � ����� ��� ��� �����������, � ���� � �� ������� ����� � ����� - �� ���� ������. �����?";
			link.l1 = "������ �����, � �� �������� ���� ��������, ��������� ����������!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "�-��-��-��!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // ������� ������ �� ������ ������
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//�������� ���������
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// ����� � �����
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "�� ���, ������ �� ���� �������?";
			link.l1 = "������ �������...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "�-���, ������, ��� ���� ���� �������!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "�����, � �� ���� �������? ��� ������? � �� ����� ������ �������� ��� �� ������ ������ �����... ���� ������ � �����, ��� �� ������ ������...";
			link.l1 = "��� �������! ����� �����... ��� ������ ������ ������?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "� �� ���� �������? ��� ������? � �� ����� ������ �������� ��� �� ������ ������ �����... ���� ������ � �����, ��� �� ������ ������...";
			link.l1 = "��� �������! ����� �����... ��� ������ ������?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "��, ��� �� ��� �������, ���������, �������. � �����, ��� � ����� ��� ���� ���������� - ��� ��������, ��� ��������.";
			link.l1 = "��, �� � ������� �� �! ��� ��������. �����... �����, ������.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "��, �������, ��� �� ��� �������, ���������, �������. � �����, ��� � ����� ��� ��� ����������.";
			link.l1 = "��, �� � ������� �� �! ��� ��������. �����, ����� � ������... �����, ������, � ������ ������.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "���� ���� ��������� - �� ������� ������. ������ � �����, � ���� ����� � ���� ���������.";
			link.l1 = "�������, ������� ���-������.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// ����� � �����
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "�� �� ���, �������. ��� ���� ��� ���� ������ ������������ �� ��������� ���! �� ��� � �������� ��� ������������!.. ��� ��� ��� ���� �������, ��������� �� �����. ����� ���� ������.";
			link.l1 = "�����, ��� ���� ������ ����������� �� �����.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "����� ���� ������, ��������. ��-��! �������� ���� ������.";
			link.l1 = "������� �� ������, ������. �����!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "�����. ��� �� ������. �� ������ ��� ���������� �������� � ���� ������, � �� �������� �� �������.";
			link.l1 = "� ��� �� ������ ��������� ����� ����������� �� ��������. �������, ������";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "�� �� ���. ������ � �����, ��� ����� �����!";
			link.l1 = "�����������!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "�� ���� ����� ������! � � ����� ������� ��� �� ������ ������ �����! � � ���� ���������� ������ ��� ������ ������� ������ ������!";
			link.l1 = "�-���! ��� �� � ������ ������ �����? ��� ������� �!";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "���� ����� ������! � � ����� ������� ��� �� ������ ������ �����! � � ���� ���������� ������ ��� ������ ������� ������ ������!";
			link.l1 = "�-���! ��� �� � ������ ������ �����?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "��, �������, ��� �� ��� �������, ���������, �������. � �����, ��� � ����� ��� ��� ����������.";
			link.l1 = "�����, ����� � ������... �����, ������, � ������ ������.";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "��� ���� ��������, ��� �������. ���� ���� ������ ��� �� �������.";
			link.l1 = "�����... �����, ������.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "���� ���� ��������� - �� ������� ������. ������ � �����, � ���� ����� � ���� ���������.";
			link.l1 = "�������, ������� ���-������.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
	}
}