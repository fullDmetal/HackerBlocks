#include        "algorithm"
#include        "iostream"
#include        "numeric"
#include        "iomanip"
#include        "cstring"
#include        "math.h"
#include        "bitset"
#include        "string"
#include        "vector"
#include        "ctime"
#include        "queue"
#include        "stack"
#include        "map"
#include        "set"

#include        "ext/pb_ds/assoc_container.hpp" // Common file
#include        "ext/pb_ds/tree_policy.hpp" // Including tree_order_statistics_node_update
#include        "ext/pb_ds/detail/standard_policies.hpp"

using namespace std;
using namespace __gnu_pbds;


#define          f first
#define          lgn 25
#define          endl '\n'
#define          sc second
#define          N (int)2e5+5
#define          pb push_back
#define          mod 1000000007
#define          ld long double
#define          vi vector<int>
#define          eb emplace_back
#define          vpii vector<pii>
#define          mii map<int,int>
#define          int long long 
#define          pii pair<int,int>
#define          pq priority_queue
#define          BLOCK (int)sqrt(N)
#define          test(x) while(x--)
#define          all(x) begin(x),end(x)
#define          allr(x) rbegin(x),rend(x)
#define          fo(i,a,n) for(int i=a;i<n;i++)
#define          rfo(i,n,a) for(int i=n;i>=a;i--)
#define          FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define          time() cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n"
#define          PI acos(-1.0)
#define 		 bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)

typedef tree< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > 
OS ;

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
     const char* comma = strchr (names + 1, ',');
     cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}

inline void INP()
{
	#ifndef ONLINE_JUDGE
	    freopen("input.txt","r",stdin);   
	    freopen("output.txt","w",stdout);
	#endif 
}

const int inf = 0x3f3f3f3f;
const int INF = 0x3f3f3f3f3f3f3f3f;

int n,q;
mii F;
vi a;


int f(int n) 
{
	if (F.count(n)) return F[n];
	int k=n/2;
	if (n%2==0) 
	{ // n=2*k
		return F[n] = (f(k)*f(k) + f(k-1)*f(k-1)) % mod;
	} else 
	{ // n=2*k+1
		return F[n] = (f(k)*f(k+1) + f(k-1)*f(k)) % mod;
	}
}

vi segTree(4*N);

void build( int v = 1, int tl = 0 , int tr = n-1 )
{
	if( tl == tr )
	{
		segTree[v] = a[tl]%mod;
		return;
	}

	int tm = tl+tr>>1;

	build( v<<1 , tl , tm);
	build( v<<1|1 , tm+1 , tr);

	segTree[v] = __gcd( segTree[v<<1] , segTree[v<<1|1] )%mod;
}

int query(int l, int r , int v = 1, int tl = 0 , int tr = n - 1)
{
	if( l > tr or r < tl ) return 0;

	if( tl >= l and tr <= r )
	{
		return segTree[v];
	}

	int tm = tl+tr>>1;

	int xx = query( l , r , v<<1 , tl , tm );
	int yy = query( l , r , v<<1|1 , tm+1, tr );

	return __gcd(xx,yy)%mod;
}

void go()
{
	cin >> n >> q;
	a.resize(n+1);
	int mx = 0;

	fo(i,0,n)
	{
		cin >> a[i];
	}

	build();

	while( q--)
	{
		int l , r;
		cin >> l >> r;
		l--;
		r--;

		cout << f(query(l , r) - 1)%mod << endl;
	}
}

int32_t main()
{
	INP(); 
	FAST;     
	int t=1; 
	// cin>>t;
	F[0] = F[1] = 1;
	test(t) go();
}

