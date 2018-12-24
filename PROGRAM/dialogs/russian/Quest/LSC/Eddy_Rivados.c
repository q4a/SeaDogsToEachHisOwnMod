// ����� ����� ������� - ������ ����
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "��� ���� ����� �� ���������� �������, ����� �������?";
			link.l1 = "� ������ ���������� � ������. ������, ���� �������.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "��� �������������� ����� ������� � ������ �������� ��������! ������� ��������� � ���, ��� �� ��� ���� ������. ��� �������, � ��� ����� � �, � ���������� ����� ����� �����. ������� �������������: ������ ����, �� �� ������ ����, ����� ����� �������.";
			link.l1 = ""+GetFullName(pchar)+". ����, �����, ������� ��� ������� ��� ���. �� ������ �������� ���������� ��� ���...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "� �� ��� ������. ������ �� ������ �������� �������� ��� ������� ������� ��� �����-���� �����������. ������ �� ����� ��������������, � �� ����� ���� ������ ���� � ������. �� ���� �������� � ���������: ��� ��� ��������� �����, ��� ��� ������ �� ���� ��������, � �� ��� ������ �� ����������, ������ ��� ��� ���� �����.";
			link.l1 = "����. ������� �� ������ �����, ����! � ������ ������� ��� ���������� � ���������.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("�������, ��� �� ������ � ����� ������ ����, ������ �������. � ��� ��� �� ����������?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("������� ����������, ��� �� �� ����. ��� ���, ������?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("�������, ������� ���� ������������ �� ��� ��-�� ����� ������ ��������������� � �������. ��� ��� �� ���������?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> �������������� ����
		case "Total_info": // ���� ������
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "����� ����? �� ���? � ����� ��� �����! ������, ������� �������, ������ ����, ��� �� ������...";
				link.l1 = "� ���� ��� ���� ������, ����. � ������� ������ ������������ - � ������ � �� ���������.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "��� ���� ������, "+pchar.name+"? ����� �������?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "����, �� �� ������, ���� �� �� ������� ����� ������� - ��������� ����? �� ���� ���������, �� ������ ���� ���.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "�������� ��� ��������� � ����� �������.";
				link.l2.go = "rivados";
			}
			link.l9 = "�� ������� ������ �������� ���. ������ ����� ���� ����������������.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "��������� ����? ���, ������ � �� ����. �� �� �������� �������, �� � ����������� ���� ��� ��� � ������� �� ����. ������ ���� � ��������, �� ��� � ������� ������ �� ����, ��������� �� �� ���������� �� �� �������.";
			link.l1 = "�������...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "���� ������� �������� ����� �����, � ��� ������ ������ �� �������. ����� �������� ����� ���������� �������� �� ��������� ���������� ����, ��������� ���������, �� ���������� ������� ��������. ����� ������ �� ���, '���������', ���� ��������� ����������� ������� ���������� �����������, ����������� �� �� ������ � ������, � ���������� � �����. ����� ��� ��� ���� ������� �� ����� ����� �������\n�� ����� ���������� �� �������� ��������� �������� ����� � ������ ���������. � ���������, ��������� ���������� �� ������ � ������� ���������� ��������� � ��� ������, � ���� �����������. ������� ������� ������������ � ��������� - ��������� ��� � ����� � ��������� � �������� ������� �� ����� � ������. � ��� �� ����� ������ �����������, � ������� �������� ������ �����\n����� ���������� ���� ������ �� �������, ��� ��������� ������� - '���-��������' � '��������' ���� �� ��� � ����������� ����� �������. �� ����� ���� ���� �������� ������� ����� ��� �����, ��� � ����������, �� ��� ������ �������� � �����. ������ ���������� ����� ���� ������� ������� ������ � ������� ���� ����� ��� '�������', � ����� ���������� ����� �� ������� ����� ��������.";
			link.l1 = "����� ���������� �������... �������!";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- �������������� ����
		
		case "capper":
			dialog.text = "��� ����� ����, ����� �������, �� ���������� �������?";
			link.l1 = "���� ����� "+GetFullName(pchar)+", � � ������ � ����������� ������� �� �������� �������. ��� ����� ���������� � ������ ����. ��� � �������, ��� ��.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "��, � ������ ����, ��� ������ ����. ������, ��� �������� ����� �� ����.";
			link.l1 = "� ������ �� '���������' ��������� ��� ������� �� ����� �������. ������� ����� ��� ����������.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "��� ����� ������� �������. ������� - ��� �������� �����, ��� ������� �������� ��� ���������. �� ��� � �������, ������� ���-�� ����� �� ��� �������?";
			link.l1 = "������. �� ������ ������ ��� ���������� � ��������... ����� ������ ����. ������ � ���� �������� �������������� ���������...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "���������, ����� �������.";
			link.l1 = "������ ������ ��������, � ���� - �������� ��� ������, ������� �� ������� �������� � ����� ��-��� �������� ��������. �� ������, ��� ��� ������� �������� ��������. ������� �� ������ ����� ���������. �� ���������� ��� �������� ���������� �������� �� ���������� ��������� � ������������ ������ ��������.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "���� ����� ������ �������, �� ���������. ������� � ���������?";
			link.l1 = "��. ��� ���������� ��� �����. ������ ������� ��� ������ �������� ��������� ������ �� �������. ����� ������ ��������, ����� ���������� �����������, ���� ��� ������ �� �����������. ������� ���� ��� �������� ������ � '���������' - ���� �� ���� ��������. ��� ����, ������� ��������� ����� � ������. �����.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "������ ����� ������, ����������� �� '��������' � �������� ��������. � ���� ��� ����� ���� ��� �����������.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "��� ������ �� �������... � ���� ��� ���� ������? ���� ������� ����� ����� �������� ������� ���� �� �������? ������ �� ��� �� ����������� �������?";
			link.l1 = "������ ������, ��� ����� �������� ��� ������... �� ����� ������� �� ������ ���������� - ������� ���� ���� � ���� ������. ��� �������� ������ �����, ������������ � ����� � ���������� ������ ��������. ��� ���� ������� �����, ��� �������� ������� ���. ��, � ���: ������� ����� � ����� �� �������� �������� ������ �������. �� ������ ���� �����?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "����� �������� ����� ��� �������, ��� ������� ������. �� ���������� �� '��������' ����������. �� ���������� ����� � �������� ���������. ���� ��� � ������ ����� ������������ ������ �������� - �� ������� �� ����� �����, ��� ����� ���� �������\n������! ������ � ����� � ����� �� ����� ������, ����� �� �� ������� �������� �����. � � ��������� ����������� �� '��������'!";
			link.l1 = "�����, ����. � �����: ��� ����� ������ ���� �������!";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//������� �������
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "������� ��������! �� �� ������, ����� �������, � �� ������� � ����� �������� � ����� ������� ���� ������ �������!";
			link.l1 = "� ����� ���. ��� ������ �����?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "� �������� ������� ���������, ����� ����: �� ������ ��� �� ����� �������, � �� �������... � ������! ��������� ������ ������. ������ � ��� � ������ ���� ��� �������. �� �� ����������, �� ������� ��������, �������������, �������� ����� ����� ����� � ���� �� ��� ������ �� ���������� ��������.";
			link.l1 = "��... ������� �� �� ����, ��� � '���������' ��� ������?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "�� �� �������� �� ����. �� ��������� �� ������� ������...";
			link.l1 = "����. � ����������� �������� ������ ����. �����, ����� �����! ������ �� ����� � ������ ��� �������.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "� ������� ���� ����. �� �� �� ����� ����������� �� ��� �� ������� ���������� �����... ������ ������ ���� �� �������� ������ � �������� �������. ������ �� ������ ������ ������������ �� ���� ���������\n���� ������� ������ ������� ���� ��� ���������� �������. �������� ��������, �������������� � ����� �������, ���� ���� ����������. �������� � ���, ���� � ���� � ��� ���� �����. ����� ������� �������� ��� ���������, ��� � ������ ��� ��������.";
			link.l1 = "������.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "������! �� �������� ����, �� � ����� � ���� �� ����� ��������� �����, ������� �� ������, ����� �� ���������. �� ������ ��, � � ������. ��� ���. �����, ���������� ��� �������� ��� ���� ��������, ����� ����.";
			link.l1 = "��! ��������, � �������� - ��� ������� ������ �������� ������...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "�� ������ �������� ����� � ���, ����� ����. ��� ������� ����� ��������� �� ����. ����� ����!";
			link.l1 = "� ���� ����, ����...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //���� �� ������ �� �������� �������
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // � �����
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ���� �����
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // ������� ���� � �������� �������
			AddSimpleRumourCityTip("�������? �������� ������� ��������� ��� ��������: ������ ������� ���� ��� �� ������ �������� � ���������� ������ �������!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("�������� ������ - ������� ���������� ������� �� '��������'! �������, ��� ��������, ��� ������, ����� � ������� � ��������...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("�������� - ������ �������, �� ������ ��? ������� �� ������� ������ ��������! ��, ������ ����, ������, �������� ����...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}