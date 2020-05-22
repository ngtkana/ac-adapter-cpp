# 概略

重み付き、乃至重みなしな木の直径を計算します。また、特に指定すると直径を達成するパスをひとつ取得することができます。

$ \mathtt { tree \unicode { 95 } diameter \<\> } $ は重みなし（辺は $ \mathtt { usize } $ ）のグラフを、
$ \mathtt { tree \unicode { 95 } diameter \<i64\> } $ は $ \mathtt { i64 } $ 型の重みを持つ（辺は $ \mathtt { pair\<usize, Weight\> } $ ) グラフを管理します。

なお、頂点数が 0 のときには実行時エラーになります。


## 型の紹介です。

- $ \mathtt { tree \unicode { 95 } diameter \<Weight\> }$: 本体です。

- $ \mathtt { no \unicode { 95 } weight } $: ユーザーが知らなくても良い型です。上記の分岐のための空構造体です。

- $ \mathtt { tree \unicode { 95 } diameter \unicode { 95 } adapter\<Weight\> } $: ユーザーが知らなくても良い型です。
辺から $ \mathtt { to } $ や $ \mathtt { weight } $ などを取る方法を知っています。
$ \mathtt { tree \unicode { 95 } diameter \<Weight\> } $ の中で使われます。


# 仕様

## 構築

### 構築方法 1: サイズを指定して、あとから $ \mathtt { insert } $ です。

- $ \mathtt { tree \unicode { 95 } diameter ( n ) } $: 頂点数 $ n $ です。グラフはまだからです。

- $ \mathtt { insert \unicode { 95 } with \unicode { 95 } weight (u, v) }$:
頂点 $ u $ と $ v $ を辺で結びます。
$ \mathtt { Weight } $ が $ \mathtt { no \unicode { 95 } weight } $ でないときに実体化するとコンパイルエラーになります。

- $ \mathtt { insert \unicode { 95 } without \unicode { 95 } weight (u, v, w) }$:
頂点 $ u $ と $ v $ を重み $ w $ の辺で結びます。
$ \mathtt { Weight } $ が $ \mathtt { no \unicode { 95 } weight } $ であるときに実体化するとコンパイルエラーになります。

TODO: 重み有りとなしで、そぐわない方のメンバ関数が、そもそも生えないようにメタプロをしても良いかもしれません。（とはいえお名前が違うほうが良いという説もです。）


### 構築方法 2: グラフを渡します。

- $ \mathtt { tree \unicode { 95 } diameter ( g ) } $: グラフを受け取ります。


## 計算

### 方法 1: 全体です。

- $ \mathtt{ build(s=0) }$: <var> s </var> からはじめます。


### 方法 2: 全体です。

- $ \mathtt{ build(s, dead) }$: 始点と頂点の死リストを受け取ります。<var> s </var> が死んでいる場合は実行時エラーです。

TODO: 実装を共通化しても良いかもしれません。


## 計算結果の取得

$ \mathtt { build () } $ を呼ぶと直径の両端点と、距離配列が初期化されます。
これを 2 回以上行うと実行時エラーです。

以下に列挙するメンバ関数は、すべて $ \mathtt { build () } $ が済んでいる前提です。

- $ \mathtt { len() } $: 直径の長さ（間の辺の重みの合計）を返します。

- $ \mathtt { extremals () } $: 直径の両端点を $ \mathtt{ s, t } $ の順で $ \mathtt { pair } $ で返します。

- $ \mathtt { verticies() } $: 直径に属する頂点の列を $ \mathtt { vec } $ で返します。重みなしの場合、この $ \mathtt { vec } $ の長さは $ \mathtt { len() } + 1 $ に一致します。

- $ \mathtt { dist } $: 使うかわからないのですが、$ t $ からの距離の情報の入ったメンバ変数です。
