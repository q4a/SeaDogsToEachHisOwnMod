// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������, "+ GetSexPhrase("������� �������","���� ����") +"?", "���� �� ������, "+ GetSexPhrase("���������","��������") +"? ������� ���� �������..."), "����� �������?", "��-��, ������ ��� �� ��� ���� � �� �� - �������...",
                          ""+ GetSexPhrase("��, ����� �� �������� �����-������ �������� ����? � �� � ���� ��� ������������ � ��������� ���� ������ ������������ ������...","��, ����� �� �������� �����-������ �������� ����? ��������� �� ������, ��-��...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������...", "��, �� ������..."), "�� ����... ��� ��������...",
                      "�� ��, ������������� � ������ ���... ������.", "�� ������... � ������ ���...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> ����� ��������
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				link.l1 = "��������, ������, ��� ����� ������� �� ��� ����. ������ �� ������� � ����� ���������, � � ���� ����. �� ������ ��� ������?";
                link.l1.go = "Gigolo";
			}	
			//<-- ����� ��������
		break;
		
		//--> ����� ��������
		case "Gigolo":
			dialog.text = "�������, �������. ����� ������� ���� �����? �� ���������� ���� ����-������, ��� ���� �� �����?";
			link.l1 = "��� �� ��� �����. ��� ����� ������� �� ����� ������.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "�� ������ � ���� ������ �������?";
			link.l1 = "������ ������, � �� ��������� � ��� �������. � ������ ����, ��� ��� ������� ��������� ����������� � ������ ������.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "������... �����, � ������ ������ ������? ������ ������� ���� �� ������������?";
			link.l1 = "��... ��� ������� � ����, �, �����, ���� �� ������ �������� � ����� ���� �����, ������� �� ����� ������ ����� ������.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "��� ����� �������� ��������� � ������������� �������. ������ ������� � ���� ����� ������.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "��� �� �� ����. ��� ������, �������, ����� ������ ���, ��� ��������, � ���������� ��������� ��������. ��� ����� ��������. �� ���� � ��� ���� ����� ����� ��������� ���� ����� ����, � �� ������� ������.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "��... ���������� �����. �� � �� ������ ������������ �� ����� �������. ���, ����� ������.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "���! � ���� ������ ��� ����� �����. ����� �������� � ����� ��������� �����.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "��, � �����-��, ��� � ���� - � ��� �������� �����, ������� �� ��������� �� ������, ������� � � ��������. �� ���� ���� �������� ��������� - �� ����� �������. �� ���� � ��� ���� ����� ��������� ��� ������ ������� ����.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "��� �������. ���, ����� ������.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "���! � ���� ������ ��� ����� �����. ����� �������� � ����� ��������� �����.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "��, �� �� ���� ����� ��������, ���������. � ��� ��� �� ��� ������� ������������� - ��� ������ ���������� �� ���������� ������� ����� ��������. �� ���� � ������ ���� �������� �������� ������ � ��������� ������ ���� � �� ������� ������.";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "��... ���������� �����. �� � �� ������ ������������ �� ����� �������. ���, ����� ������.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "���! � ���� ������ ��� ����� �����. ����� �������� � ����� ��������� �����.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "��� ���? ��������, ����� �� ������ ������? ��� �������, � ��� ����� ������� - ���� ����� ������������� �������, ������ ��� ���� ��������� ������. �� ���� ��� ���� �������� - � ������ ����. � ���� ��� ������ ����.";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "��� �������. ���, ����� ������.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "���! � ���� ������ ��� ����� �����. ����� �������� � ����� ��������� �����.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "�������, �������. ������� ����������� � ����������� ����� ������ � ����� ����� ����. ����� ��� ������ ��������� �� ����� ���� ����. ���� �� �������� ������ �� �������� - �� �������� ������ ������, � ����� ���� �������� ����� ���������� ������\n� �� ������� �������� � ��� ���-������... ������������, ����� �������� � ���� ����������. �� ����� �� �����������, � ������ ������������.";
			link.l1 = "�� ���������. � ���� ��� ������� ��� �����, � �� ��� ����-�� ���. � ����������� ������ � �� ������. ����� �������!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
