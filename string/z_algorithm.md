## 仕様

文字列 s 対して、Z 配列を求めます。定義は

$
     z _ i = \max \left\{
         j \in [ i, { \rm len } (s) ] :
         s _ { k - i } = s _ { k } \ ( \forall k \in [i, j[ )
     \right\} - i
$

です。
