# hsptest - HSP3スクリプトでテストを書くためのフレームワーク

[![test](https://github.com/mass-0910/hsptest/actions/workflows/test.yml/badge.svg)](https://github.com/mass-0910/hsptest/actions/workflows/test.yml)

HSP3言語で書かれたプログラムをテストするためのフレームワークです。pytestのような使い心地を目指しています。現在開発途中です。

## インストール

hsptestは以下の手順でインストールしてください。

1. HSP3インストールフォルダ(例：`C:/hsp36`)を環境変数PATHに追加します
2. [Releases](https://github.com/mass-0910/hsptest/releases/latest)からhsptest.zipをダウンロードします
3. hsptest.zipを解凍し、中に含まれる`install.bat`を実行します。

## バッチファイル(`run_hsptest.bat`)の使い方

`run_hsptest.bat`をエクスプローラからダブルクリックすることで、hsptestの実行が開始します。  
コマンドプロンプトが起動され、テストスクリプトを実行した結果が表示されます。

また、hsptest_log.txtというファイルが生成され、その中にテストのログが出力されます。

開発中にコマンドを叩かないスタイルの方は是非お使いください。

## コマンドラインからの使い方

以下のコマンドでhsptestを実行できます。  

```powershell
hsptest
```

引数無しでhsptestを実行すると、実行したカレントディレクトリ内の全てのテストスクリプト（ファイル名にtestが含まれるhspスクリプトファイル）を実行し、テストします。

テストスクリプトが別のフォルダに置かれてある場合は、そのフォルダを引数で指定することができます。

```powershell
hsptest path/to/testfolder
```

引数にはテストスクリプトを直接指定することもでき、その場合は指定したスクリプト内のテストのみを実行します。

```powershell
hsptest path/to/test.hsp # test.hsp内のテストのみを実行
```

引数にはディレクトリまたはファイルを複数指定することもできます。

```powershell
hsptest path/to/testfolder1 path/to/testfolder2 # testfolder1とtestfolder2の中身を連続でテストする
```
## hsptestユーザマニュアルのリンク

hsptestの詳しい使い方は、[hsptestユーザマニュアル](https://github.com/mass-0910/hsptest/wiki/hsptest%E3%83%A6%E3%83%BC%E3%82%B6%E3%83%9E%E3%83%8B%E3%83%A5%E3%82%A2%E3%83%AB)をご覧ください。