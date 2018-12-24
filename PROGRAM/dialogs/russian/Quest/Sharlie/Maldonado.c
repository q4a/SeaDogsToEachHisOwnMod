// ������ �� ����������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "�� ���-�� �����?";
			link.l1 = "�� ���, ������.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "����, ������� "+GetFullName(pchar)+"...";
			link.l1 = "������-�� � ���� �� ������� ����������� ����� ��������... ��������, ��� ������ � ����, ��� �� ���� ��������� ���-�� ��������. ���� ���� ���� �� ���� ��������� �������, ��������? ������ �����?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "��� ��� - ������ �� ����������. ���� ��� ������ �� �������, �� ���� ��� ����� �� ������� �� ������ ����� ������. �� ��� ���� ������ ������. �� ���� ��� �����. � �� ��� �� ����� ����.";
			link.l1 = "��� � �������, �� ���� �����������, ����� ���������?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "� �� ������. ����� ���������� � ����, ��� � �������?";
			link.l1 = "�! ��� ���� ������� �� �����������! ����� ��������� ����, ������� ����� �����?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "���� �� ���������� ���������. � ����� �� � �������� �������... ������ ������ ���� ������� ���� ��������� �� �����. ��� ����� �����.";
			link.l1 = "�� ��� � ��������? ����� �������. ������ �������� �� ������ �� �������� ����, ��� � �����. ";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "� ��� � ������� �� �������� ��� �� ����, ��� ���� ������ ������. ����� ��, ����� ���� ����������� ������ ����� ��� ������ �������� ������� � ������������ ����������������� ������� ����� �� ���� �������.";
			link.l1 = "���� �� ����! �� ���, �� ���� ������ ������ �������������, ������� ��� �������� � ������ ��� �������� ������ ������? �� �� ��� �������!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "�� ���. � ������� ���.";
			link.l1 = "� ������ ��� �������� ����? ��� �� �� ��� ���������?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "���� ����� �� ������. ���, �������, � ���. ���� ����� �� �����. � �����, ������ ��� ��������� �����... ����� ����, ��� ������ ������� ����� �� ����� ������� ����� ����, ����� �������� ���, � ����� ����� ���� ������ ���������, ���� ������ ������� ������ ��������. � ������� ������ �� ��������� ��������, � ��� ���������, ��� �� ���� ��������� ������ �������� ���!";
			link.l1 = "���������������-��������� �������... ���� ������, ����� �� �� ������ �� �� ����! ������ �� ����� ��� �����? ��� ���� ��� ����?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "� ������ ���������� ������� ���, ��������� ����������� ��������� ��������. ��� ���������� ���, ����������� ���������� ��� ���!";
			link.l1 = "����... �� ������������ � ����� ��������, ���? ���������� ����� ������� ����, ��� �� ����������... �� ������ ���� ������� �� ���� � ����� �� ��������? �����! �� ������� ��������� � ��������, ��� ������!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "������� ������� ��� ���� � ������ ������ ���. � ������� � �������� � ��� ������ ����� ������� ��������� �����, ����� ������� ����� � ������� �������� ������������ ������ � ��� ���.";
			link.l1 = "� ��� ��� � ���� �������� �����, ��� ������. ����� ��� ����� ���. � ������ ��������� ��� ���� ����� ��� �����. � ��� ����� ���������� �� ���� ��� ��������� ������.";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "����� ������������. ��� �� �� ��� �� ��� ���� - ����� ����: ����� ������ ���� ������� �������, � ������� ��� ����� ����� ���� �����: ���������� ����� �� ������ � ��������. ����� ����� ����� �������� ���-���� �������.";
			link.l1 = "��. � ��������, ��� ��� ����� �������� �������... � ��� �� �� ������� ������� � ��������? �� ������ ���� ������?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "������� ���� � ��������, �� �������� �� �������� ����, ��� �������� ��� ��� �� ���������� - ����� �������� ������� � ������� ���������. �� ���� ��� ���� ������, ������ � �������. ��� ����� �������� ���� ��� �� ����� �� ������ �������\n��� ������ ���� �������� � ���� ������ �� ������� � ������ ����� �������� ������, � �� ��������� ������ ������, ���������� �������� ���. ���� ����� �����, �� ������� ������ ��� ���� � ��������, ��� �� ������ �� ����� �� ��� ����� ����.";
			link.l1 = "��� ������, ��� ���������� ������-�� ����� � ������. �� ���� �� ������ ������ ���� �� �� ����� � ���������� ���� ����? ������ ��� ����� ����� ����������� ��� �����������.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "� ��������� ������, � �� ������� � ����� � ��������� � �� �������� ������ � ����������. ����� ����, � ������� ���� �������� �� ���� �����. ����� �� �����!";
			link.l1 = "��-�����, �� ������ ������� �����, ��� ������! ��� �����������, ��� ������ ���� �������� ���������� ���, � ��� �� ������������� �� ���� ������ � ����� ������ ����! ���� �������� �� ������� �� ������ �������!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "������ ������� �������� �, � �� ���� ��������! �������� ���������� � ����������� �������, ����������� �������!..";
			link.l1 = "��, ������� ��� �� ��������� ������ � ������ ��� �����! � ���, ����������� ���������!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}