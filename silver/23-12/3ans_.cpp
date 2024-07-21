#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m, X[2 * N], *x = X + N;
char c[N];
int Cnt[2 * N], *cnt = Cnt + N, pos, res, ans;

void get()
{
	pos = res = 0;
	memset(Cnt, 0, sizeof(Cnt));
	for(int i = 1; i <= m; i++)
		if(c[i] == 'L') pos--;
		else if(c[i] == 'R') pos++;
		else if(++cnt[pos] == 1 && x[pos]) res++;
	ans = max(res, ans);
}

void get_l_to_r()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++, ans = max(ans, res);
		else if(c[i] == 'R') pos--;
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			if(++cnt[pos + 2] == 1 && x[pos + 2]) res++;
		}
}

void get_l_to_f()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++, ans = max(ans, res + (!cnt[pos] && x[pos]));
		else if(c[i] == 'R') pos--;
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			if(++cnt[pos + 1] == 1 && x[pos + 1]) res++;
		}
}

void get_r_to_l()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++;
		else if(c[i] == 'R') pos--, ans = max(ans, res);
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			if(++cnt[pos - 2] == 1 && x[pos - 2]) res++;
		}
}

void get_r_to_f()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++;
		else if(c[i] == 'R') pos--, ans = max(ans, res + (!cnt[pos] && x[pos]));
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			if(++cnt[pos - 1] == 1 && x[pos - 1]) res++;
		}
}

void get_f_to_l()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++;
		else if(c[i] == 'R') pos--;
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			ans = max(ans, res);
			if(++cnt[pos - 1] == 1 && x[pos - 1]) res++;
		}
}

void get_f_to_r()
{
	get();
	for(int i = m; i; i--)
		if(c[i] == 'L') pos++;
		else if(c[i] == 'R') pos--;
		else
		{
			if(!--cnt[pos] && x[pos]) res--;
			ans = max(ans, res);
			if(++cnt[pos + 1] == 1 && x[pos + 1]) res++;
		}
}

int main()
{
    freopen("3.in", "r", stdin);
    freopen("3.out", "w", stdout);
	cin >> n >> m;
	for(int i = 1, a; i <= n; i++) scanf("%d", &a), x[a] = 1;
	scanf("%s", c + 1);
	
	get();
	get_l_to_r();
	get_l_to_f();
	get_r_to_l();
	get_r_to_f();
	get_f_to_l();
	get_f_to_r();
	
	cout << ans << endl;
	return 0;
}