@echo off

@rem 注意1：このバッチファイルはテストスクリプト(test_***.hsp)が含まれているフォルダに配置してください。

@rem 注意2：このバッチファイルはC:\hsp3*フォルダにHSP3がインストールされていることを想定して書かれてあります。
@rem C:\hsp3*以外の場所にHSP3をインストールしている場合、以下の変数にインストールフォルダへのパスを代入してください。
set hsp_dir=

@rem Cドライブ直下からHSPインストールフォルダを探す
if not defined hsp_dir (
    for /D %%a in (C:\hsp3*) do (
        set hsp_dir=%%a
    )
)

@rem インストールフォルダを取得できなかったらエラー表示して終了
if not defined hsp_dir (
    echo HSP3のインストールフォルダが見つかりませんでした。
    echo %0をメモ帳などのエディタで開き、7行目のhsp_dir変数に、ご自分のPCのHSP3インストールフォルダへのパスを書き込んでください。
    echo 例）set hsp_dir=%USERPROFILE%\hsp36
    pause
    exit /B 1
)

@rem hsptest実行
%hsp_dir%\hsptest.exe -v -l hsptest_log.txt -s

pause