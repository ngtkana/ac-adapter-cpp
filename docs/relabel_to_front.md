# 計算量

$ \Theta( V ^ 3 ) $ です。


# API

## コンストラクタ `relabel_to_front(std::size_t n, std::size_t s, std::size_t t)`

頂点数 `n`、始点 `s`、終点 `t` を指定です。


## `void insert(std::size_t u, std::size_t v, Flow w)`

`u` から `v` への、容量 `w` の辺を追加です。


## `Flow run()`

中身のフローネットワークを最大流になるように変形し、最大流の流量を返します。


