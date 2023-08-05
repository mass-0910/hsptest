@echo off

@rem HSPインストールフォルダを取得する
if "%1"=="" (
    for /D %%a in (C:\hsp3*) do (
        set hsp_dir=%%a
    )
) else (
    if not exist "%1" (
        echo %1 ：フォルダが見つかりません
        pause
        exit /B 1
    )
    set hsp_dir=%1
)

@rem インストールフォルダを取得できなかったらエラー表示して終了
if not defined hsp_dir (
    echo HSP3のインストールフォルダが見つかりませんでした。
    echo このバッチファイルの引数にHSP3のインストールフォルダのパスを入力してください。
    echo 例）> install.bat C:\hsp36
    pause
    exit /B 1
)

@rem hsptestのインストールを開始する
echo %hsp_dir%にhsptestのインストールを開始します。
copy /Y hsptest.exe %hsp_dir%
copy /Y common\* %hsp_dir%\common

if %ERRORLEVEL% neq 0 (
    echo hsptestのインストールに失敗しました。
    pause
    exit /B 1
)

echo hsptestのインストールが完了しました。
pause