#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif
void addEC(ringsignList*& pList, int RingsignO) {
	ringsignList* temp = new ringsignList;
	temp->nRingsign = RingsignO;
	temp->pNext = NULL;
	if (pList == NULL) {
		pList = temp;
		return;
	}
	ringsignList* phead = pList;
	while (phead->pNext != NULL) {
		phead = phead->pNext;
	}
	phead->pNext = temp;
	return;
}
void deleteEnd(ringsignList*& pList) {
	if (pList->pNext == NULL) {
		pList = NULL;
		return;
	}
	ringsignList* phead = pList;
	ringsignList* ptr = nullptr;
	while (phead->pNext != NULL) {
		ptr = phead;
		phead = phead->pNext;
	}
	ptr->pNext = NULL;
}

/* đảo ngược danh sách liên kết
	ví dụ: 1 2 3 4 null thành 4 3 2 1 null
	*/
void reverseList(ringsignList*& pList) {
	ringsignList* ptr = nullptr;
	ringsignList* current = pList;
	ringsignList* next = nullptr;
	while (current != NULL)
	{
		next = current->pNext;
		current->pNext = ptr;
		ptr = current;
		current = next;
	}
	pList = ptr;
}
void deleteFirst(ringsignList*& pList) {

	ringsignList* temp = pList;
	if (pList == NULL) return;
	pList = pList->pNext;
	delete temp;
}
void plusOne(ringsignList*& pList) {
	if (pList->pNext == NULL) {
		pList->nRingsign++;
		if (pList->nRingsign == 10) {
			pList->nRingsign = 1;
			addEC(pList, 0);
		}
		return;
	}
	if (pList->nRingsign == 0) {
		deleteFirst(pList);
	}
	if (pList == NULL) {
		pList->nRingsign = 1;
		return;
	}
	reverseList(pList);
	ringsignList* phead = pList;
	while (phead != NULL) {
		phead->nRingsign++;
		if (phead->nRingsign == 10) {
			phead->nRingsign = 0;
			phead = phead->pNext;
		}
		else {
			break;
		}
	}
	reverseList(pList);
	return;
}
void deleteGollum(ringsignList*& pList, int item) {

	
	if (pList->nRingsign == item)
	{
		deleteFirst(pList);
	}
	ringsignList* phead = pList;
	ringsignList* ptr = NULL;
	while (phead != NULL) {
		if (phead->nRingsign == item) {
			ringsignList* temp = phead->pNext;
			if (ptr == NULL) {
				phead = temp;
				break;
			}
			phead = ptr;
			phead->pNext = temp;
			break;
		}
		ptr = phead;
		phead = phead->pNext;
	}
	
}
void removeItem(ringsignList*& pList, int item)
{
	/* Remove the first apperance of item in list and return true, otherwise return false */
	ringsignList* ph = pList;
	ringsignList* ptr = NULL;
	if (pList == NULL) return ;
	if (pList->nRingsign == item) {
		pList = pList->pNext;
		return;
	}

	while (ph != NULL)
	{
		if (ph->nRingsign == item) {
			ringsignList* temp = NULL;
			temp = ph->pNext;
			ptr->pNext = temp;
			return ;
		}
		ptr = ph;
		ph = ph->pNext;
	}
	return ;

}
void Gollum(ringsignList*& pList, int RingsignO) {
	if (pList == nullptr) return;
	if (pList->pNext == NULL && pList->nRingsign == RingsignO) {
		pList = NULL;
		return;
	}
	reverseList(pList);	
	removeItem(pList,RingsignO);
	reverseList(pList);
	return;
}
void Saruman(ringsignList*& pList, int item) {
	if (pList == nullptr) return;
	if (pList->pNext == NULL && pList->nRingsign == item) {
		pList = NULL;
		return;
	}
	ringsignList* phead = pList;
	while (phead != NULL) {
		if (phead->nRingsign == item) {
			removeItem(pList, item);
		}
		phead = phead->pNext;
	}
}

ringsignList*  combat (knight& theKnight, eventList* pEvent)
{
	ringsignList* pList = NULL; 
	//fighting for honor and love here
	pList = new ringsignList();
	pList->nRingsign = theKnight.nInitRingsign;
	pList->pNext = NULL;
	//------------------------------------------------------------
	int iEvent = 1;
	int MaxHP = theKnight.HP;
	while (pEvent != NULL ) {
		if (pEvent->nEventCode == 0 || pList == NULL) {
			return pList;
		}
		if (theKnight.HP <= 0) {
			return NULL;
		}
		int b = iEvent % 10;
		int levelO = iEvent > 6 ? (b > 5 ? b : 5) : b;
		int RingsignO = pEvent->nEventCode % 10;
		/*
			Nếu level của hiệp sĩ cao hơn levelO của đối thủ, hiệp sĩ chiến
		thắng. Khi chiến thắng, hiệp sĩ sẽ đoạt ringsign của của đối thủ
		và thêm vào cuối danh sách EC của mình, ngoại trừ một số trường 
		hợp đặcbiệt sẽ có mô tả riêng bên dưới.
			Nếu level của hiệp sĩ nhỏ hơn levelO của đối thủ, hiệp sĩ sẽ thua. HP của hiệp sĩ sẽ được tính lại như sau:
				HP = HP – damage (3)
			Trong đó damage sẽ được tính như sau:
				damage = baseDamage*levelO*10 (4)
				Đối thủ baseDamage
					Quái vật Uruk-hai 1
						Ma nhẫn 1.8
						Strider 4.5
						Gollum 8.2	
						Lurtz 7.5
						Gimli 9
						Saruman 0.1

		*/
		if (pEvent->nEventCode == 7) {
			plusOne(pList);
			iEvent++;
			pEvent = pEvent->pNext;
		}
		else if (pEvent->nEventCode == 8) {
			if (theKnight.HP == MaxHP) {
				iEvent++;
				pEvent = pEvent->pNext;
			}
			// ko thu ringsign khi gap 777 va 888
			else if(MaxHP == 777 || MaxHP == 888) theKnight.HP = MaxHP;
			else  {
				theKnight.HP = MaxHP;
				deleteEnd(pList);
				iEvent++;
				pEvent = pEvent->pNext;
			}
		}
		else if(pEvent->nEventCode >= 70 && pEvent->nEventCode < 90)
		{
			iEvent++;
			pEvent = pEvent->pNext;
		}
		else if (pEvent->nEventCode < 7 || pEvent->nEventCode == 9) {
			iEvent++;
			pEvent = pEvent->pNext;
		}
		else {
			if (theKnight.level > levelO) {
				if (pEvent->nEventCode >= 90) {
					reverseList(pList);
				}
				else
				{
					if (MaxHP == 888 && ((pEvent->nEventCode >= 30 && pEvent->nEventCode < 40) || (pEvent->nEventCode >= 60 && pEvent->nEventCode < 70)))
					{
						iEvent++;
						pEvent = pEvent->pNext;
						continue;
					}
					if (MaxHP == 999) {
						if ((pEvent->nEventCode >= 10 && pEvent->nEventCode < 30) || (pEvent->nEventCode >= 60 && pEvent->nEventCode < 70))
						{
							iEvent++;
							pEvent = pEvent->pNext;
							continue;
						}
					}
					addEC(pList, RingsignO);

				}
				pEvent = pEvent->pNext;
				iEvent++;
			}
			//--------------------------Thua----------------
			else if (theKnight.level < levelO) {
					/*0 Thời gian thi thố chấm dứt đột ngột
					1X Gặp quái vật Uruk - hai
					2X Gặp Ma nhẫn(Ringrwaiths)
					3X Gặp Strider
					4X Gặp Gollum
					5X Gặp chỉ huy bóng tối Lurtz
					6X Gặp người lùn Gimli
					7 Gặp tiên nữ Arwen
					8 Gặp nữ vương Galadriel
					9X Gặp giáo chủ Saruman
					Quái vật Uruk-hai 1
						Ma nhẫn 1.8
						Strider 4.5
						Gollum 8.2	
						Lurtz 7.5
						Gimli 9
						Saruman 0.1

					*/
				double baseDamage;
				//Uruk-hai
				if (pEvent->nEventCode >= 10 && pEvent->nEventCode < 20) {
					if (MaxHP == 999) {
						iEvent++;
						pEvent = pEvent->pNext;
						continue;
					}
					baseDamage = 1;
					int damage = baseDamage * levelO * 10;
					theKnight.HP = theKnight.HP - damage;
					iEvent++;
					pEvent = pEvent->pNext;
				}
				//Ma nhẫn Ringrwaiths
				else if (pEvent->nEventCode >= 20 && pEvent->nEventCode < 30)
				{
					if (MaxHP == 999) {
						iEvent++;
						pEvent = pEvent->pNext;
						continue;
					}
					baseDamage = 1.8;
					int damage = baseDamage * levelO * 10;
					theKnight.HP = theKnight.HP - damage;
					iEvent++;
					pEvent = pEvent->pNext;
				}
					//strider
				else if (pEvent->nEventCode >= 30 && pEvent->nEventCode < 40)
				{
					if (MaxHP == 888) {
						iEvent++;
						pEvent = pEvent->pNext;
						continue;
					}
					baseDamage = 4.5;
					int damage = baseDamage * levelO * 10;
					theKnight.HP = theKnight.HP - damage;
					iEvent++;
					pEvent = pEvent->pNext;
				}
					//Gollum
				else if (pEvent->nEventCode >= 40 && pEvent->nEventCode < 50)
				{
					baseDamage = 8.2;
					int damage = baseDamage * levelO * 10;
					theKnight.HP = theKnight.HP - damage;
					if (MaxHP == 777) {
						iEvent++;
						pEvent = pEvent->pNext;
						continue;
					}
					Gollum(pList, RingsignO);
					iEvent++;
					pEvent = pEvent->pNext;
					}
					//Lurtz
				else if (pEvent->nEventCode >= 50 && pEvent->nEventCode < 60)
				{
					baseDamage = 7.5;
					int damage = baseDamage * levelO * 10;
					theKnight.HP = theKnight.HP - damage;
					if (MaxHP == 777) {
						iEvent++;
						pEvent = pEvent->pNext;
						continue;
					}
					deleteFirst(pList);
					deleteFirst(pList);
					deleteFirst(pList);
					iEvent++;
					pEvent = pEvent->pNext;
				}
					//Gimli
				else if (pEvent->nEventCode >= 60 && pEvent->nEventCode < 70)
				{
					if (MaxHP == 888 || MaxHP == 999) {
						iEvent++;
						pEvent = pEvent->pNext;
						continue;
					}
					baseDamage = 9;
					int damage = baseDamage * levelO * 10;
					theKnight.HP = theKnight.HP - damage;
					iEvent++;
					pEvent = pEvent->pNext;
				}
					//Saruman
				else if (pEvent->nEventCode >= 90) {
					baseDamage = 0.1;
					int damage = baseDamage * levelO * 10;
					theKnight.HP = theKnight.HP - damage;
					if (MaxHP == 777) {
						iEvent++;
						pEvent = pEvent->pNext;
						continue;
					}
					Saruman(pList, RingsignO);
					iEvent++;
					pEvent = pEvent->pNext;
				}

			}
			else {
				iEvent++;
				pEvent = pEvent->pNext;
			}

		}
	}
	if (theKnight.HP <= 0) {
		return NULL;
	}
  
	return pList;
}

int checkPalindrome(ringsignList* pRingsign)
{
	if (pRingsign == NULL) return 0;
	if (pRingsign->pNext == NULL) return 1;
	ringsignList* phead = pRingsign;
	ringsignList* temp = NULL;
	while (phead != NULL) {
		addEC(temp, phead->nRingsign);
		phead = phead->pNext;
	}
	reverseList(temp);
	phead = pRingsign;
	while (phead != NULL || temp != NULL) {
		if (phead->nRingsign != temp->nRingsign) {
			return 0;
		}
		phead = phead->pNext;
		temp = temp->pNext;
	}
	return 1;
}
