# hsptest - HSP3スクリプトでテストを書くためのフレームワーク

HSP3言語で書かれたプログラムをテストするためのフレームワークです。pytestのような使い心地を目指しています。現在開発途中です。

## インストール

以下の手順でhsptestをインストールすることができます。

1. HSP3をインストールします
2. HSP3インストールフォルダ(例：`C:/hsp36`)を環境変数PATHに追加します
3. [Releases](https://github.com/mass-0910/hsptest/releases/latest)からhsptest.zipをダウンロードします
4. hsptest.zipを解凍し、中に含まれているファイルを以下のように移動してください
   |移動するファイル|移動先フォルダ|
   |---|---|
   |`hsptest.exe`|HSP3インストールフォルダ直下 (例：`C:\hsp36`)|
   |`common`内の全ての`.as`ファイル|HSP3インストールフォルダの`common`フォルダ (例：`C:\hsp36\common`)|

## 使い方

以下のコマンドでhsptestを実行できます。

```
hsptest
```

hsptestは、カレントディレクトリに置かれている`test`を名前に含む`.hsp`スクリプトファイルをテストスクリプトとして認識し、それらを実行します。テストスクリプトが別のフォルダに置かれてある場合は、そのフォルダを引数で指定することができます。

```
hsptest path/to/testfolder
```

## テストスクリプトの書き方

hsptestで実行されるテストは、テスト一つに対して一つのサブルーチンで記述する必要があります。テストサブルーチンのラベル名は、`*test`から始まるものである必要があります。以下の例のようにテストスクリプトを記述してください。

```
#include "assertion.as" ; 各種assertionをincludeする

;ラベル名は*testXXX...のような名前にしてください
;テストサブルーチン
*test1
    b = 2
    a = 10 / b
    assertEqual a, 5, "a is not 5"
    return

;テストサブルーチン
*test2
    s = "test"
    strrep s, "t", "s"
    mes s
    assertEqual s, "sess"
    return

;テストサブルーチン
*test3
    zero = 0
    divide_0 = 1 / zero ;0割りを発生させる
    return
```

テストごとにhsp3clランタイムのインスタンスが起動するため、他のテストサブルーチンで発生した変数代入やエラーなどは現在実行してるテストサブルーチンには影響しません。テストサブルーチン内でなにかのエラーが発生した場合、またはassertionが失敗したとき、そのテストは失敗となります。

hsptestが実行終了すると、以下のような出力がされます。テストサブルーチンのラベル名、テスト結果、エラー行数、エラーの種類、pass/failの数、テストに掛かった時間が表示されます。
```
HSP 3.6.0.7, hsptest 0.4
test1@test_example.hsp: PASS
test2@test_example.hsp: PASS
test3@test_example.hsp: FAIL at line 22 of test_example.hsp: Divided by 0
======= 1 failed, 2 passed in 0.27 seconds =======
```

## `assertion.as`の使い方

`common`フォルダに入れていただいた`assertion.as`は、世界に数多あるテストフレームワークで使用されている各種assertion命令を再現するためのマクロ定義ファイルです。これをテストスクリプト内でincludeしていただくと、以下のようなassertion命令が使用できます。[]で書かれてある引数は省略可能です。

|assertion命令|引数|説明|例|
|---|---|---|---|
|assertTrue|p1[,p2]|p1がtrue(非0)のとき成功。p2はエラー説明|`assertTrue a == 1, "a is not 1"`|
|assertFalse|p1[,p2]|p1がfalse(0)のとき成功。p2はエラー説明|`assertFalse a > 0, "a is positive"`|
|assertEqual|p1,p2[,p3]|p1とp2が同値のとき成功。p3はエラー説明|`assertEqual a, b, "a is not same as b"`|
|assertNear|p1,p2,[p3][,p4]|p1とp2の差がp3以下のとき成功。p3のデフォルト値は0.0001。p4はエラー説明|`assertNear a, b, , "a is far from b"`|