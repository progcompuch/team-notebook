const ll MOD; // MOD variable global
ll binpow(ll a, ll b){
  a %= MOD;
  ll ans=1;
  while(b > 0){
    if(b & 1)
      ans = ans * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return ans;
}
