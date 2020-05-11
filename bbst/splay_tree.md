## 構造体$ \mathtt { splay \unicode { 95 } node } $

### 構築

- $ \mathtt { splay \unicode { 95 } node() } $: ポインタをすべて$ \mathtt { nullptr } $で初期化し、サイズを$ 1 $にし、値をデフォルト構築します。

- $ \mathtt { splay \unicode { 95 } node(x) } $: ポインタをすべて$ \mathtt { nullptr } $で初期化し、サイズを$ 1 $にし、値を$ x $で初期化します。


### オブザーバー

- $ \mathtt { state() } $: 自分が何者であるのかを知らしめます。

- $ \mathtt { lsize() } $: 左の子のサイズを返します。いない場合は$ 0 $です。

- $ \mathtt { rsize() } $: 右の子のサイズを返します。いない場合は$ 0 $です。

- $ \mathtt { to \unicode {95} vec() } $: 値を順番に$ \mathtt { vector } $に入れて返します。

- $ \mathtt { to \unicode {95} vec \unicode {95} with (f) } $: 関数$ f: \mathtt{ splay \unicode { 95 } node } \rightarrow T$ で射影した結果を$ \mathtt{ vector }$に入れて返します。


### 更新

- $ \mathtt { update() } $: $ \mathtt{ size } $と$ \mathtt{ acc }$ を更新です。子の情報が正しいとき、私の情報も正しくなります。

- $ \mathtt { set(x) } $: 自分の値を$ x $にセットし、$ \mathtt{ update() }$を呼びます。


### 変形ロボとしての基本動作

- $ \mathtt { rotate() } $: 回転をして、自分を一つ上に挙げます。親がいない場合は実行時エラーです。操作の終了語、親、自分の$ \mathtt { update() } $が呼ばれます。

- $ \mathtt { splay() } $: 自分が根になるまで、自分や親の$ \mathtt { rotate() } $を呼び続けます。


### 平衡順序木の操作

- $ \mathtt { get(i) } $: 自分の部分木のうち、ひだりから$ i $番目のものを探して根まで持っていき、それへのポインターを返します。

- $ \mathtt { partition \unicode { 95 } point ( f ) } $: 術語 $f : \mathtt{ splay \unicode {95} node } \rightarrow \mathtt{ bool } $ を受け取り、$[ 0, i [ $で$ \mathtt{ true }$、$ [ i, \mathtt{ size } [ $で$ \mathtt{ false }$ となるような$ i $ を返します。ただし区分化されている必要があります。

- $ \mathtt { merge(l, r) } $: $ r $の左下に$ l $をつけます。

- $ \mathtt { merge \unicode { 95 } from \unicode { 95 } three (l, c, r) }$: $r$ の左下に $c$、その左下に$l$をつけます。

- $ \mathtt { split(i) } $: 自分の部分木を、左側$ i $個、右側$ \mathtt{ size } - i$個に分けます。どちらかが$ 0 $個になる場合は、そちらは$ \mathtt{ nullptr }$です。また$ \mathtt{ size } $よりも大きな$ i $を指定すると、実行時エラーです。

- $ \mathtt { split \unicode { 95 } into \unicode { 95 } three (l, r) }$: 同様に、$l$個、$r - l$個、$\mathtt{ size } - r$個に分けます。


## 値の集約

- $ \mathtt { fold(l, r) } $: 自分の部分木の中で$ [l, r[ $に対応する添字部分の値を集約します。添字がおかしいときには実行時エラーです。


## 構造体 $ \mathtt { splay \unicode { 95 } tree } $

中身は$ unique \unicode { 95 } ptr $の$ \mathtt {vector}$ と、根の添字番号です。空のときには根は$ -1 $ ( = `std::numeric_limits<std::size_t>::max()`) になっています。

### 構築

- $ \mathtt { splay \unicode { 95 } tree (n) } $: $n$個のノードが左下から右上に向かって一直線になったスプレー木を構築します。ノードはデフォルト構築されたあと、$ \mathtt { merge } $が呼ばれます。

- $ \mathtt { splay \unicode { 95 } tree (a) } $: 値の入った$ \mathtt {vector} $を受け取り、スプレー木を構築します。


### オブザーバー（ $\mathtt{ const }$ がついているとは限りません。）

- $ \mathtt{ empty() } $: 空ならば$ \mathtt { true } $です。

- $ \mathtt{ size() } $: サイズを返します。

- $ \mathtt{ get(i) } $: $i$ 番目の値を返します。

- $ \mathtt{ fold \unicode {95} all() }$: すべてを畳み込んだ値を返します。空ならば$ \mathtt { id }$ですし、空でなければ根の$ \mathtt { acc } $です。

- $ \mathtt{ fold(l, r) }$: 区間 $[l, r[$ を畳み込んだ値を返します。

- $ \mathtt{ partion \unicode { 95 } point (f) } $: 空ならば$ 0 $です。空でなければ根の同名のメンバ関数を呼びます。

- $ \mathtt{ lower \unicode { 95 } bound (x, cmp=less) }$: ソート済みであるとして、値が$ x $以上の最も左の添字を返します。存在しない場合は$ \mathtt{ size } $を返します。内部では$ \mathtt { partition \unicode {95} point } $に転送をしています。

- $ \mathtt{ upper \unicode { 95 } bound (x, cmp=less) }$: ソート済みであるとして、値が$ x $を超える最も左の添字を返します。存在しない場合は$ \mathtt{ size } $を返します。内部では$ \mathtt { partition \unicode {95} point } $に転送をしています。

- $ \mathtt{ to \unicode {95} vec() }$: 値を$ \mathtt{ vector }$にコレクトします。

- $ \mathtt{ to \unicode {95} vec \unicode {95 } with(f) }$: 関数$ f: \mathtt{ splay \unicode {95} node } \rightarrow T $で射影した結果を$ \mathtt { vector } $にコレクトです。

### 更新

- $ \mathtt{ set(i, x) } $: $ i $ 番目の値を$ x $にセットします。

- $ \mathtt{ add(i, x) } $: $ i $ 番目の値を$ mathtt{get}(i) + x $にセットします。

- $ \mathtt{ sub(i, x) } $: $ i $ 番目の値を$ mathtt{get}(i) - x $にセットします。

- $ \mathtt{ mul(i, x) } $: $ i $ 番目の値を$ mathtt{get}(i) * x $にセットします。

- $ \mathtt{ div(i, x) } $: $ i $ 番目の値を$ mathtt{get}(i) / x $にセットします。

- $ \mathtt{ map(i, f) } $: $ i $ 番目の値を$ f(mathtt{get}(i)) $にセットします。
