## 概要

定数項が $ 0 $ でない、次数 $ 1 $ 以上の多項式 f ( q ) \in K [ q ] $ による剰余環上の演算です。

また、最高次も $ 0 $ でないと受け付けないようになっております。


## メンバ変数

- $ \mathtt { qd } $: $ d $ が $ f $ の字数だとして、 $ q ^ d $ を $ f $ で割ったあまりです。

- $ \mathtt { qinv } $: $ q $ の逆元です。


## メンバ関数

- $ \mathtt{ normalize(a) } $: $ a $ のサイズを調整します。

- $ \mathtt{ mul(a, b) } $: $ a b \bmod f $ です。

- $ \mathtt{ pow(a, b) } $: $ a ^  b \bmod f $ です。


## 例：漸化式

$ a $ が漸化式 $ a _ { n + d } = \sum _ { i = 1 } ^ d c _ { i } a _ { n + d - i } $ （ただし、$ c _ { d } \neq 0 $）に従うとしましょう。そしてその母関数を $ A $ と書きます。
さらにこれを配る DP で計算するときの初期値を $ P _ A $（これは $ d $ 次未満です。）、$ Q (q) = 1 - \sum _ { i = 1 } ^ d c _ { i } q ^ i $ と置くと、$ A = P _ A / Q $ となります。

さて、$ n $ 番目を求めるために、$ A $ を $ n $ 回シフトしたものを $ B $ と置きましょう。これも同じ漸化式に従いますから、$ P _ B = B \cdot Q $ も $ d $ 次未満です。
ここで、$ A = q^n \cdot B + A \vert _ { < d } $ ですから、これに $ Q $ を掛けると、$ P _ A = q ^ n \cdot O _ B + A \vert _ { < d } \cdot Q $ が得られます。
さらに $ Q $ による剰余をとると、$ P _ A = q ^ n \cdot P _ B \pmod Q $ ですから、$ P _ B = q ^ { - n } \cdot P _ A \pmod Q $ となります。
一方 $ P _ B $ は $ d $ 次未満であることもわかっていますから、これで確定することができます。

ところでいま知りたかったのは $ a _ n = [1] B $ でした。しかし、$ Q $ は定数項が $ 1 $ ですから、これは $ [1] P _ B $ に等しいです。


