#include <cstdio>

using ll = long long int;

ll gcd(ll a, ll b){return b ? gcd(b, a % b) : a; }

void f(ll &x, ll &y){
    ll g = gcd(x, y);
    x /= g, y /= g;
}

void solve(){
    ll x, y, a, b;
    scanf("%lld%lld%lld%lld", &x, &y, &a, &b);
    f(x, y);
    ll t = x + y;
    int ans = 1;
    while(t % 2 == 0) t >>= 1, ++ans;
    if(t != 1){
        puts("-1");
    }else{
        printf("%d\n", ans);
    }
}

int main(){
    int T; scanf("%d", &T);
    while(T--){
        solve();
    }
}
