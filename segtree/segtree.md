## 構築

- $ \mathtt{ segtree(n, init=Monoid::id()) } $: サイズと初期値を指定です。

- $ \mathtt{ lazy \unicode{95} set( i, x ) } $: 葉に値をセットしますが、構築をしません。

- $ \mathtt{ build } $: 構築をします。

- $ \mathtt{ resize(n, init=Monoid::id()) } $: サイズと初期値を指定です。$ \mathtt { segtree } $を$ vector $に入れたいときなど、デフォルト構築をはさみたい場面で使います。


## オブザーバー

- $ \mathtt{ size() } $: 構築で指定したサイズです。

- $ \mathtt{ fold(l, r) } $: 開区間$ [ l, r [ $で畳み込みをします。

- $ \mathtt{ get(i) }$: 添字$ i $にある値を取得です。

- $ \mathtt{ to \unicode{95} vec() }$: $ \mathtt{ vector } $ に値をコレクトします。


## 更新

- $ \mathtt{ set(i, x) } $: 添字$ i $の値を$ x $に変更します。

- $ \mathtt{ add(i, x) } $: 添字$ i $の値を$ \mathtt{ get (i) + x } $に変更します。

- $ \mathtt{ sub(i, x) } $: 添字$ i $の値を$ \mathtt{ get (i) - x } $に変更します。

- $ \mathtt{ mul(i, x) } $: 添字$ i $の値を$ \mathtt{ get (i) * x } $に変更します。

- $ \mathtt{ div(i, x) } $: 添字$ i $の値を$ \mathtt{ get (i) / x } $に変更します。

- $ \mathtt{ map(i, f) } $: 添字$ i $の値を$ \mathtt{ f( get (i) ) } $に変更します。

