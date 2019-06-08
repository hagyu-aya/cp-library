
// T: 要素の型, E: 作用素の型
template<typename T, typename E>
class SegmentTree{
    using F = function<T(T, T)>;
    using G = function<T(T, E)>;
    using H = function<E(E, E)>;
    using P = function<E(E, int)>;
    vector<T> node; // セグ木本体
    vector<E> lazy; // 遅延評価
    F f; // 要素を合成する関数
    G g; // 要素に作用素を作用させる関数
    H h; // 作用素を合成する関数
    P p; // p(e, n) = 作用素e(∈E)をn回作用させたときの値
    T e_T; // (T, f)の単位元
    E e_E; // (E, h)の単位元で、g(t, e_E) = tを満たす
    int n; // nは2のべき乗で、n/2 < 要素数 <= nを満たす

    // [l, r)を表すk番目のノードの遅延評価を行う
    void eval(int k, int l, int r){
        if(lazy[k] == e_E) return;
        if(k < n-1){
            lazy[k*2+1] = h(lazy[k*2+1], lazy[k]);
            lazy[k*2+2] = h(lazy[k*2+2], lazy[k]);
        }
        node[k] = g(node[k], p(lazy[k], r - l));
        lazy[k] = e_E;
    }

    // a, b, x: 区間[a, b)に作用させたい値
    // k, l, r: 更新する、[l, r)を管理するノードk
    // 戻り値: xを作用させたあとの[a, b)における実際の値(node[k] + lazy[k]*length)
    T update(int a, int b, E x, int k, int l, int r){
        eval(k, l, r);
        if(r <= a || b <= l) return node[k];
        if(a <= l && r <= b){
            lazy[k] = h(lazy[k], x);
            return g(node[k], p(lazy[k], r-l));
        }
        return node[k] = f(update(a, b, x, 2*k+1, l, (l+r) / 2), update(a, b, x, 2*k+2, (l+r)/2, r));
    }
    
    // a, b: 求めたいf(...f(a, a+1), ...), b)
    // k, l, r: 更新する、[l, r)を管理するノードk
    T accumulate(int a, int b, int k, int l, int r){
        if(b <= l || r <= a) return e_T;
        eval(k, l, r);
        if(a <= l && r <= b) return node[k];
        return f(accumulate(a, b, 2*k+1, l, (l+r) / 2), accumulate(a, b, 2*k+2, (l+r) / 2, r));
    }

public:
    SegmentTree(int _n, F _f, G _g, H _h, P _p, T _e_T, E _e_E, vector<T> data){
        f = _f;
        g = _g;
        h = _h;
        p = _p;
        e_T = _e_T;
        e_E = _e_E;
        n = 1;
        while(n < _n) n *= 2;
        node.resize(2*n-1, e_T);
        lazy.resize(2*n-1, e_E);
        for(int i = 0; i < data.size(); ++i){
            node[i+n-1] = data[i];
        }
        for(int i = n-2; i >= 0; --i){
            node[i] = f(node[2*i+1], node[2*i+2]);
        }
    }

    T update(int a, int b, E x){
        return update(a, b, x, 0, 0, n);
    }

    T accumulate(int a, int b){
        return accumulate(a, b, 0, 0, n);
    }

    T operator[](int k){
        return accumulate(k, k+1);
    }
};

