/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
	ListNode *inc(ListNode** node) {
		ListNode *current = *node;
		*node = (*node)->next;
		return current;
	}

	ListNode *merge(ListNode *a, ListNode *b, int length, ListNode **last) {	
		int count_a = 0, count_b = 0;
		ListNode *head, *current;
		current = head = a->val > b->val ? (count_b++, inc(&b)) : (count_a++, inc(&a));
		while (count_a < length && b != NULL && count_b < length)
		{
			current->next = a->val > b->val ? (count_b++, inc(&b)) : (count_a++, inc(&a));
			current = current->next;
		}
		if (count_a == length)   // fisrt part has been merged
			while (b != NULL && count_b < length)
			{
				current->next = inc(&b);
				count_b++;
				current = current->next;
			}
		else                     // next part has been merged
			while (count_a < length)
			{
				current->next = inc(&a);
				count_a++;
				current = current->next;
			}
		current->next = b;      // connected the subsequent part list which have not been merged
		*last = current;
		return head;
	}

public:
    ListNode* sortList(ListNode* head) {
        int length = 1, num = 0;
		ListNode *current = head, *first, *next, *trail = NULL;
		while (current != NULL && ++num)    // calculate the number of elements in list
			current = current->next;
		while (length < num)
		{
			first = next = head;
			int count = 0;
			while (count++ < length && next != NULL)
				next = next->next;
			if (next == NULL)
				break;
			head = merge(first, next, length, &trail);
			current = trail;   first = current->next;
			while (first != NULL)
			{
				count = 0;
				next = first;
				while (count++ < length && next != NULL)
					next = next->next;
				if (next == NULL)
					break;
				current->next = merge(first, next, length, &trail);
				current = trail;
				first = current->next;
			}
			length *= 2;
		}
		return head;
    }
};
