#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

typedef long long ll;
typedef std::pair<long long, long long> llPair;

using namespace std;


struct AVLNode {
	AVLNode * parent, * left, * right;
	ll l, r, current, total;
	int bf;
};

AVLNode* root;

ll sum(ll begin, ll end)
{
       if (end >= begin) 
		return ((end - begin + 1) * (end - begin + 2)) / 2;
	else
		return 0;
}

ll sum2(ll begin, ll end, ll count)
{
	return (((end - begin + 1) + (end - begin - count + 2)) * count) /  2;
}

void RR(AVLNode * A)
{
	AVLNode* B = A->right;
	AVLNode* P = A->parent;

	A->right = B->left;

	if (A->right)
		A->right->parent = A;

	B->left = A;
	B->parent = P;
	A->parent = B;

	if (P) {
		if (P->left == A)
			P->left = B;
		else
			P->right = B;
	}
	else
		root = B;

	if (B->bf == -1) {
		A->bf = 0;
		B->bf = 0;
	}
	else {
		A->bf = -1;
		B->bf = 1;
	}

	// A needs to be updated before B
	A->total = (
		((A->left)? A->left->total : 0) +
		((A->right)? A->right->total : 0) +
		A->current
	);

	B->total = (
		((B->left)? B->left->total : 0) +
		((B->right)? B->right->total : 0) +
		B->current
	);	
}

void LL(AVLNode* A)
{
	AVLNode* B = A->left;
	AVLNode* P = A->parent;

	A->left = B->right;

	if (A->left)
		A->left->parent = A;

	B->right = A;
	B->parent = P;
	A->parent = B;

	if (P) {
		if (P->left == A)
			P->left = B;
		else
			P->right = B;
	}
	else
		root = B;

	if (B->bf == 1) {
		A->bf = 0;
		B->bf = 0;
	}
	else {
		A->bf = 1;
		B->bf = -1;
	}

	A->total = (
		((A->left)? A->left->total : 0) +
		((A->right)? A->right->total : 0) +
		A->current
	);

	B->total = (
		((B->left)? B->left->total : 0) +
		((B->right)? B->right->total : 0) +
		B->current
	);		
}

void LR(AVLNode * A)
{
	AVLNode* B = A->left;
	AVLNode* C = B->right;
	AVLNode* P = A->parent;

	B->right = C->left;
	if (B->right)
		B->right->parent = B;

	A->left = C->right;
	if (A->left)
		A->left->parent = A;

	C->right = A;
	A->parent = C;
	C->left = B;
	B->parent = C;

	C->parent = P;

	if (P) {
		if (P->left == A)
			P->left = C;
		else
			P->right = C;
	}
	else 
		root = C;

	if (C->bf == 1)
		A->bf = -1;
	else
		A->bf = 0;

	if (C->bf == -1)
		B->bf = 1;
	else
		B->bf = 0;

	C->bf = 0;

	A->total = (
		((A->left)? A->left->total : 0) +
		((A->right)? A->right->total : 0) +
		A->current
	);

	B->total = (
		((B->left)? B->left->total : 0) +
		((B->right)? B->right->total : 0) +
		B->current
	);
 
	C->total = (
		((C->left)? C->left->total : 0) +
		((C->right)? C->right->total : 0) +
		C->current
	);	
}

void RL(AVLNode * A)
{
	AVLNode* B = A->right;
	AVLNode* C = B->left;
	AVLNode* P = A->parent;

	B->left = C->right;
	if (B->left)
		B->left->parent = B;

	A->right = C->left;
	if (A->right)
		A->right->parent= A;

	C->left = A;
	A->parent = C;
	C->right = B;
	B->parent = C;
	
	C->parent = P;

	if (P) {
		if (P->left == A)
			P->left = C;
		else 
			P->right = C;
	}
	else
		root = C;

	if (C->bf == -1)
		A->bf = 1;
	else
		A->bf = 0;

	if (C->bf == 1)
		B->bf = -1;
	else
		B->bf = 0;

	C->bf = 0;

	A->total = (
		((A->left)? A->left->total : 0) +
		((A->right)? A->right->total : 0) +
		A->current
	);

	B->total = (
		((B->left)? B->left->total : 0) +
		((B->right)? B->right->total : 0) +
		B->current
	);
 
	C->total = (
		((C->left)? C->left->total : 0) +
		((C->right)? C->right->total : 0) +
		C->current
	);	
}

void insertAVL(ll lside, ll rside)
{
	ll intervals = sum(lside, rside);

	AVLNode* newNode = new AVLNode;
	newNode->left = newNode->right = newNode->parent = NULL;
	newNode->bf = 0;
       	newNode->current = newNode->total = intervals;
	newNode->l = lside;
	newNode->r = rside;

	AVLNode* v = root;

	if (!v) {
		root = newNode;
		return;
	}
	
	while (true) {
		v->total += intervals;

		if (lside < v->l) {
			if (!v->left) {
				v->left = newNode;
				newNode->parent = v;
				break;
			}
			v = v->left;
		}
		else {
			if (!v->right) {
				v->right = newNode;
				newNode->parent = v;
				break;
			}
			v = v->right;
		}
	}

	AVLNode* w;
	bool force_balance;

	if (v->bf)
		v->bf = 0;
	else {
		if (v->left == newNode)
			v->bf = 1;
		else
			v->bf = -1;

		// going up
		w = v->parent;
		force_balance = false;

		while (w) {
			if (w->bf) {
				force_balance = true;
				break;
			}
			if (w->left == v)
				w->bf = 1;
			else
				w->bf = -1;
			v = w;
			w = w->parent;
		}

		if (force_balance) {
			if (w->bf == 1) {
				if (w->right == v)
					w->bf = 0;
				else if (v->bf == -1)
					LR(w);
				else
					LL(w);
			}
			else {
				if (w->left == v)
					w->bf = 0;
				else if (v->bf == 1)
					RL(w);
				else
					RR(w);
			}
		}
	}
}

//  slow 
llPair find_deleteWORKS(ll begin, ll end, ll position) {
	ll a, b;

	ll j = end - begin + 1;

	while (position > j) {
		position -= j;
		j--;
	}

	a = end - j + 1;
	b = a + position -1;

	printf("%lld %lld\n", a, b);
	return make_pair(a, b);
}


llPair find_delete(ll begin,  ll end, ll position) {
	ll l = begin;
	ll p = end;

	while (l < p) {
		ll s = (l + p) / 2;
//		cout << "BIN: " << sum2(l, end, s - l + 1) << " " << sum2(s+1, end, end - s + 1) << endl;
		ll sum_mid = sum2(l, end, s - l + 1);// - sum2(s + 1,end, end - s + 1);
//		cout << "BINSEARCH: " << l << " " << s << " " << p << " position: " << position << "sum: " << sum_mid << endl; 
		if (position >  sum_mid) {
			position -= sum_mid;
			l = s + 1;
		}
		else
			p = s;
	}

	printf("%lld %lld\n", l, l + position -1);
	return make_pair(l, l + position - 1);
}


void findNode(ll i)
{
	AVLNode* v = root;

	ll lson;
	while (true) {
		lson = 0;
		if (v->left) {
			lson = v->left->total;
			if (lson >= i) {
				v = v->left;
				continue;
			}
		}
		//cout << " " << lson << " " << v->current << " " << i << endl;
		if (lson + v->current >= i) {
			i -= lson;
			break;
		}
		i -= lson + v->current;
		v = v->right;
	}

	//cout << v->l << "..." << v->r << endl; 
	llPair delete_interval = find_delete(v->l, v->r, i);
	//if (delete_interval != find_deleteWORKS(v->l, v->r, i))
	//	cout << "ZLE !!!!" << endl;
	//else
	//	cout << "DOBRZE!!!!!!" << endl;

	ll del_l = delete_interval.first;
	ll del_r = delete_interval.second;

	if ((v->l == del_l) && (v->r == del_r)) {
		// delete node;
		ll old_value = v->current;
		v->current = 0;

		while (v) {
			v->total -= old_value;
			v = v->parent;
		}
	}
	else if (v->l == del_l) {

		ll old_val = v->current;
		v->current = sum(del_r + 1, v->r);
		ll difference = old_val - v->current;
		v->l = del_r + 1;

		while (v) {
			v->total -= difference;
			v = v->parent;
		}
	}
	else if(v->r == del_r) {
		ll old_val = v->current;
		v->current = sum(v->l, del_l - 1);
		ll difference = old_val - v->current;
		v->r = del_l - 1;

		while (v) {
			v->total -= difference;
			v = v->parent;
		}
	} else {
		ll old_intervals = v->current;
		v->current = sum(v->l, del_l - 1);
		ll difference = old_intervals - v->current;
		ll old_r = v->r;
		v->r = del_l - 1;
		while (v) {
			v->total -= difference;
			v = v->parent;
		}
		insertAVL(del_r + 1, old_r);
	}

	printf("%lld\n", (root->total));
}

void TraverseTree(AVLNode * v, ll level) {
	if (v) {
		cout << level << ": " << v->l << " " << v->r << " " << v->total << " " << v->current << endl;
		TraverseTree(v->left, level+1);
		TraverseTree(v->right, level+1);
	}
}

int main()
{
	ll n;
	scanf("%lld", &n);
	printf("%lld\n", sum(1, n));

	root = NULL;
	insertAVL(1, n);

	while (true) {
		ll input;
		scanf("%lld", &input);

		if (input == -1)
			break;
		
		findNode(input + 1);

//	TraverseTree(root, 0);
	}
}
