# hsptest - HSP3スクリプトでテストを書くためのフレームワーク

[![test](https://github.com/mass-0910/hsptest/actions/workflows/test.yml/badge.svg)](https://github.com/mass-0910/hsptest/actions/workflows/test.yml)

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

### コマンドラインオプション

hsptestを実行する際に以下のオプションを指定できます。

|オプション|引数|説明|
|---|---|---|
|`-v`, `--verbose`||テスト結果ごとに結果を出力します|
|`-s`, `--stdout`||テスト実行中にHSPランタイムから出力された文字列を表示します|
|`-l`, `--logfile`|LOGFILE|LOGFILEで指定したファイルにテストログを出力します|
|`-r`, `--runtime`|RUNTIME|テストを実行するデフォルトのランタイム名を指定します。ランタイム名はランタイム実行ファイルから`.exe`を除いたものです（例：`hsp3`, `hsp3utf`, `hsp3cl`など）|
|`-h`, `--help`||ヘルプを表示します|
|`--version`||hsptestのバージョン情報を表示します|
<!-- |`-j`, `--junitxml`|p1|p1で指定したファイルにJUnit形式のログを出力します(未実装)| -->


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


## hsptestの出力

hsptestが実行終了すると、以下のような出力がされます。
```
hsptest test
```
![image](https://user-images.githubusercontent.com/53329734/185728062-e691c608-75f7-492d-ad7e-7c7bf10cb797.png)

実行の際に`-v`オプションを追加すると、それぞれのテストの結果と、テスト失敗の原因が出力されます。
```
hsptest -v test
```
![image](https://user-images.githubusercontent.com/53329734/185728084-efd6a2d4-ec9c-4412-85f9-e24f97f96210.png)

さらに、`-l LOGFILE`オプション（`LOGFILE`は出力するログファイルへのパス）を指定すると、より詳細なログデータがファイルに出力されます

```
hsptest -l hogehoge.log test
```

## `assertion.as`の使い方

`common`フォルダに入れていただいた`assertion.as`は、世界に数多あるテストフレームワークで使用されている各種assertion命令を再現するためのマクロ定義ファイルです。これをテストスクリプト内でincludeしていただくと、以下のようなassertion命令が使用できます。[]で囲われている引数は省略可能です。

|assertion命令|引数|説明|例|
|---|---|---|---|
|assertTrue|p1[,p2]|p1がtrue(非0)のとき成功。p2はエラー説明|`assertTrue a == 1, "a is not 1"`|
|assertFalse|p1[,p2]|p1がfalse(0)のとき成功。p2はエラー説明|`assertFalse a > 0, "a is positive"`|
|assertEqual|p1,p2[,p3]|p1とp2が同値のとき成功。p3はエラー説明|`assertEqual a, b, "a is not same as b"`|
|assertNear|p1,p2,[p3][,p4]|p1とp2の差がp3以下のとき成功。p3のデフォルト値は0.0001。p4はエラー説明|`assertNear a, b, , "a is far from b"`|

## アノテーションによるテストの設定

テストスクリプトに記述したテストサブルーチンには、それぞれタイムアウトやランタイム指定などの設定を記述することができます。これをhsptestではアノテーションと呼びます。

アノテーションは**テストサブルーチンラベルの1行前に、`;@`で始まるコメントとして記述できます**。

```
;@ runtime=hsp3, timeout=10
*test_subroutine
    mes "このテストはhsp3.exeランタイムで実行され、10秒でタイムアウトします。"
    return
```

アノテーションは以下の通りに記述する必要があります。（文字間の空白文字は入れなくても大丈夫です。）
```
;@ <設定項目1> = <値>, <設定項目2> = <値>, ...
```

使用できるアノテーションの設定項目は以下のとおりです。
|設定項目|説明|
|---|---|
|runtime|このテストが実行されるランタイム名を指定します。ランタイム名はランタイム実行ファイルから`.exe`を除いたものです。（例：`hsp3`, `hsp3utf`, `hsp3cl`など）|
|timeout|このテストのタイムアウト時間を数値で指定します。小数点を含むこともできます。タイムアウトしたテストは失敗したものとして扱われます。単位は秒[s]です。|
|ignore|このテストをhsptestが無視するかどうかを指定します。値が`true`の場合、このテストは無視されます。それ以外の値の場合は実行されます。|