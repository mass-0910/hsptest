# hsptest - HSP3スクリプトでテストを書くためのフレームワーク

HSP3言語で書かれたプログラムをテストするためのフレームワークです。pytestのような使い心地を目指しています。現在開発途中です。

## インストール

以下の手順でhsptestをインストールすることができます。

1. [Releases](https://github.com/mass-0910/hsptest/releases/latest)からhsptest.zipをダウンロードする
2. hsptest.exeが含まれるフォルダを環境変数PATHに登録する

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

hsptestが実行終了すると、以下のような出力がされます。テストサブルーチンのラベル名、テスト結果、エラー行数、エラーの種類、pass/failの数が表示されます。
```
test1@test_example.hsp: PASS
test2@test_example.hsp: PASS
test3@test_example.hsp: FAIL at line 22: Divided by 0
======= 1 failed, 2 passed =======
```

## `assertion.as`の使い方

`common`フォルダに入れていただいた`assertion.as`は、世界に数多あるテストフレームワークで使用されている各種assertion命令を再現するためのマクロ定義ファイルです。これをテストスクリプト内でincludeしていただくと、以下のようなassertion命令が使用できます。[]で書かれてある引数は省略可能です。

|assertion命令|引数|説明|例|
|---|---|---|---|
|assertTrue|p1[,p2]|p1がtrue(非0)のとき成功。p2はエラー説明|`assertTrue a == 1, "a is not 1"`|
|assertFalse|p1[,p2]|p1がfalse(0)のとき成功。p2はエラー説明|`assertFalse a > 0, "a is positive"`|
|assertEqual|p1,p2[,p3]|p1とp2が同値のとき成功。p3はエラー説明|`assertEqual a, b, "a is not same as b"`|
|assertNear|p1,p2,[p3][,p4]|p1とp2の差がp3以下のとき成功。p3のデフォルト値は0.0001。p4はエラー説明|`assertNear a, b, , "a is far from b"`|

## LICENSES

- hsp3cl.exe
- hspext.dll
- hspcmp.dll

これらのファイルはOnion Software様の製品であり、以下のライセンスで公開されています。

```
Hot Soup Processor (HSP)
Copyright (C) 1997-2021, Onion Software/onitama, all rights reserved.
Made with base technology of OpenHSP.


OpenHSP
Copyright (C) 1997-2021, Onion Software/onitama.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. 
Neither the name of the Onion Software nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

ソースコード形式かバイナリ形式か、変更するかしないかを問わず、以下の条件を満たす場合に限り、再頒布および使用が許可されます。 

・ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、および下記免責条項を含めること。 
・バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の資料に、上記の著作権表示、本条件一覧、および下記免責条項を含めること。 
・書面による特別の許可なしに、本ソフトウェアから派生した製品の宣伝または販売促進に、Onion Softwareの名前またはコントリビューターの名前を使用してはならない。 

本ソフトウェアは、著作権者およびコントリビューターによって「現状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、および特定の目的に対する適合性に関する暗黙の保証も含め、またそれに限定されない、いかなる保証もありません。著作権者もコントリビューターも、事由のいかんを問わず、 損害発生の原因いかんを問わず、かつ責任の根拠が契約であるか厳格責任であるか（過失その他の）不法行為であるかを問わず、仮にそのような損害が発生する可能性を知らされていたとしても、本ソフトウェアの使用によって発生した（代替品または代用サービスの調達、使用の喪失、データの喪失、利益の喪失、業務の中断も含め、またそれに限定されない）直接損害、間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害について、一切責任を負わないものとします。 
```